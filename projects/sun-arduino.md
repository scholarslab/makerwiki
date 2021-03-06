<!-- TITLE: Arduino-Controlled Sun Model-->
<!-- SUBTITLE: An Arduino-Controlled model of the Sun as a prop for a tabletop RPG -->

# Details
Name: Nicolas Dalton
Contact Info: nsd4fr@virginia.edu. I am happy to talk to you about this project!
Level of Completion: Complete, but not polished
Duration: 3 Months
The Goal: A working protoype
Project Cost: Around $20
Technologies used in this project: 3D Printing, Arduino Electronics, Programming
Tools used in this project:
* Form2
* Arduino IDE
* Soldering Iron
* Meshmixer


To see the final product, scroll down to the very bottom of this page!


### Versions
Through this page, I go through the many steps it took to get to the final product. I give examples of what my pseudocode or approach looks like during given iterations of the project, but trying to post full files and blocks of working code corresponding to where I was is simply not worth the effort. At the end, I post my wiring diagram, working code, and Thingiverse links where you can find all models of the 3D printed parts of this project. Thanks for reading!

# Inspirations!
This project was brought to me by Dan Foulds, a good friend (and DM!) of mine. He wanted to create a small model of the Sun that could be used in for Dungeons and Dragons for our game. But, he also wanted it to have several cool light patterns that would correlate to different situations in the game. Essentially, he had this idea and wanted me to help him make it real. The goal: A 3D printed, LED-filled, controllable, independently powered model of the Sun.
# First steps
The first challenge was finding a model of the sun. We wanted it to have the correct "look". As in, it had to be kinda bumpy and have the correct topography to emulate the Sun properly. We ended up going with a [Moon model from Thingiverse](https://www.thingiverse.com/thing:2344879). (I'll use we in this guide, but really I mean Dan would tell me what he wanted and I would do the work.)

Once we settled on the moon model, I cut it up in Meshmixer, hollowing it out so that we could put lights on the inside and cutting a lid onto it so that we could insert the lights and then glue it shut. 

We 3D printed it on the Form2 in Clear (V2) resin and cleaned it up. You can find the Model and images on my [Thingiverse Listing for the model](https://www.thingiverse.com/thing:2886096)


# Now the hard part...
The next step of the project was to get the LEDs working. I bought a [1meter length of LED addressable lights](https://www.amazon.com/gp/product/B01D1DRJ0G/ref=oh_aui_detailpage_o02_s01?ie=UTF8&psc=1) off of Amazon and got to work. 

## Quick Side Note about Material
I was interesting in doing several things with Arduino microcontrollers at this point, so I went ahead and got a full range of supplies for it, some of which I used in this project. 

* [Elegoo Starter Arduino Kit](https://www.amazon.com/gp/product/B01D8KOZF4/ref=oh_aui_detailpage_o02_s00?ie=UTF8&psc=1)
* [3 Pack of Arduino Nano Microcontrollers](https://www.amazon.com/gp/product/B0713XK923/ref=oh_aui_detailpage_o02_s01?ie=UTF8&psc=1)
* [Arduino Nano Dev Mounting](https://www.amazon.com/gp/product/B00X3L2RJK/ref=oh_aui_detailpage_o02_s01?ie=UTF8&psc=1)
* [4-Battery Holder](https://www.amazon.com/gp/product/B019XT18IQ/ref=oh_aui_detailpage_o01_s00?ie=UTF8&psc=1)
I used a Nano board for this project. At the start, I did not know whether the Arduino itself would be inside the Sun model or not, so I wanted to have something that was small enough to fit inside the sun if necessary, but still robust enough that I could use the extras I had with other projects. I ended up not putting the Nano inside the sun, so you can really use any Arduino controller (Uno, Nano, etc.) with the design I provide.  Also, I bought the Elegoo kit for the same reason. I knew I was interested in getting more involved with Arduino and wanted a good range of supplies. I think that the only thing from the Elegoo kit that I actually used is some resistors later in the project. 

# Step 1: Let there be light
The first step of this part of the project is just MAKING IT LIGHT UP. Because microcontrollers cannot handle a large electrical load (each pin can only give about 30 mA of current), I started very small, with only 2 LEDs at the front of the strip. Each **individual** LED when it is at **full brightness** (full RGB, producing white light at max intensity) draws about 30mA of current, so I knew that only lighting up 2 LEDs in only one color at a low intensity would not surpass this metric.

Dan had the following in mind for the LEDs
* A mix of Yellow, Orange, and Red 
* Soft glow (so some kind of light diffusion would be necessary)
* Pulsing colors, to emulate the natural ebb and flow of the Sun's surface colors

In order to control the LEDs, I decided to use the [FastLED library](http://fastled.io/) which is compatible with the light strip I used (see above).

This is an early version of the lights when I was playing around with RGB values to see what had the right shade of orange/yellow/red.

[video](/uploads/arduino-sun-project/video-1517678096.mp4){.video}

Once I was able to power the whole strip, I got some basic color changing working.

[video](/uploads/arduino-sun-project/video-1517883823.mp4){.video}


As you can see, half the lights are Yellow(ish) and half are Red. This was adjusted later of course.



# Step 2: Make the light good
Now that sounds like an easy step, but this step (combined with the next) took up most of the duration of the project. Now that I had two LED's working, I needed to get the whole strip lit up. For that, I ordered the 4-battery holder that is listed above. 4 AA batteries (4 x 1.5V = 6V, but realistically 5V after a small amount of use) power the LED strip, and the Arduino is powered separately by a cable to a computer. It is possible to power the entire system indepently, but the LED strip eats up the current from the batteries, leaving no extra power for the Nano controller. To power the Arduino, I would probably need to have 5 batteries, or just have two different power supplies. 

Over time, I developed various methods of making the lights go up and down. 

The first method I used had some pseudocode like this. Because Yellow, Orange, and Red are all "Red" colors, I am able to take advantage of using the brightness of other colors as a fraction of the brightness of Red.

```c_cpp
for(int brightness = 0; brightness < 255; brightness = brightness + 1){
  setRedLEDs(brightness);
  setYellowLEDs(brightness/2);
  setOrangeLEDs(255 - brightness);
}
for(int brightness = 255; brightness > 0; brightness = brightness - 1)[
  setRedLEDs(brightness);
  setYellowLEDs(brightness/2);
  setOrangeLEDs(255 - brightness);
}
```

Essentially, the brightness variable is a reference point for calculating the brightness for each set of LEDs. For each loop, the brightness value is incremented by 1, then the brightnesses of each LED are appropriately recalculated. `setOrangeLEDs(255 - brightness)` means that the orange LEDs are the opposite brightness as the red LEDs. When `brightness` is 1, red LEDs will have brightness 1, and orange LEDs will have brightness 254. In addition, I had the LEDs spaced in increments of 3. So LED 1 is red, LED 2 is yellow, LED 3 is orange, LED 4 is red, etc. This is what that looked like inside the 3D printed sun.

[video](/uploads/arduino-sun-project/video-1517977588-all-lights-working-basic-pattern.mp4){.video}

# Step 3: Controlling and Cool Patterns

Since the project had been pretty painless up to this point, I asked Dan if there was anything special that he wanted. Maybe there were special circumstances in the Boss Fight that might require some cool colors/patterns. He gave me three different conditions (in addition to the normal Orange/Yellow/Red pulsing).

1. A bright blue/white flash, starting from completely off and ramping up to max brightness
2. The normal pulsing increases in speed for about 5 seconds, then the full sphere goes bright red
3. Purple swirling that goes around the sphere

So now I had to consider how to code and implement control structures into the system. I decided to give each condition a button, each connecting to its own pin on the Nano. This follows the basic [button Arduino tutorial.](https://www.arduino.cc/en/Tutorial/Button) But I still had to control the arduino somehow. The code I settled on looked something like this. 

Quick Note about Arduino Code: The loop() method is essentially the main() method of the system. The chunk of code in the loop() method will continue to iterate as long as the arduino is powered. 


```c_cpp
loop(){
  int pressedSwitch = -1;
  if(blueAndWhiteButton.isPressed() == true){
    pressedSwitch = 1;
  }
  if(redFlashButton.isPressed() == true){
    pressedSwitch = 2;
  }
  if(purpleSwirlsButton.isPressed() == true){
    pressedSwitch = 3;
  }
  
  switch(pressedSwitch)
    case: -1
    do normalPulse();
    case: 1
    do blueAndWhite();
    case: 2
    do redFlash();
    case: 3
    do purpleSwirls();
}
```

This basic control structure is what I used throughout the project. It works pretty well, as when the system enters the method of each behavior, it does not read in anymore input until the behavior method finishes executing. In addition, the line `int switchPressed = -1;`  means that the system defaults the normal Red/Yellow/Orange behavior. One thing I changed later was that the `normalPulse()` method would only activate one "step" of changing the LEDs. Instead of going through a full up-down cycle, it would only execute one step up, or one step down, depending on the state of the system. That way you dont have to hold down the buttons and wait, but you can instantly get a response from the system. 

This is what those behaviors look like. Pardon the audio, it was a demo video for Dan. 

[video](/uploads/arduino-sun-project/video-1518282892-lights-in-ball-with-buttons.mp4){.video}


I looked at a lot of code online for making interesting patterns and such on these kinds of light strips. I wrote my own code for the normal pulsing, the blue/white flash, and the red flash, but I used code from [tweaking4all.com's guide](https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/) for the purple swirling effect, as it involves an interesting sinusoidal function. See the "Running Lights" pattern in the website. This website also has a great tutorial for setting up the LED strip with the power source and Arduino in the circuit. I relied on this guide early on for designing the circuit. 


# Step 4: Making it random.
So despite my ultimate ability to make things look amazing, Dan was just not satisfied. He did not just want a static pattern, but a dynamic, randomly fluctuating distribution of lights so that the orb would really look like the sun. Sometimes a spot would be red, sometimes orange. This was perhaps the most challenging aspect of the code from a design/CS standpoint.

I went through 3 iterations of code for this process before getting something that satisfied the specifications from Dan.

The first attempt involved keeping track of both the up/down state (increasing brightness or decreasing brightness) and the color state (red, yellow, orange). The code then looped through the arrays and assigned the next value of the LED according to its corresponding entries in the array. However, this code was far too inefficient. This required multiple array accesses for each LED (of which there were 60), and then multiple if-conditional statements about the current state of that LED to determine what its next value should be. Maybe on a faster processor, this amount of control would not be excessive, but on the tiny little nano, the light color changing became sluggish. 

The second iteration was barely better, and it was not until the third iteration that I found a working solution. I put all the LEDs into 6 groups, each group of 10 LEDs would have its own state values. I also made big improvements to the control structure that determined what the next value of an LED should be. This decreased the number of array accesses and vastly increased the speed of the system. Instead of checking the color state, then the increasing/decreasing state, I had it check the increasing/decreasing state first, then the color state. In terms of combinatorics, this sounds identical. But the Arduino switch() conditional is fairly computationally expensive, and having if-then statements inside of a switch() is much worse practically than a switch() inside of if-then. 

The choice of 6 groups was arbitrary, but it having 6 groups of 10 lights each seemed like reasonable values.

This is what the LED strip looks like with this code. It is much more "twinkly" than previous versions. Even though at first I thought the amount of work required to randomize the lights would not be worth it, it did look great once I got it working. (Still not worth the work though.)

[video](/uploads/arduino-sun-project/video-1519528979-twinkling-light-strips.mp4){.video}

### Minor Optimizations
* Using arrays of bytes instead of arrays of ints. Ints use up more memory than bytes, so using bytes instead of ints (especially as a global variable) for small numbers is a nice little optimization that while not neccessary in this project, might be a necessary change in a more sophisticated project.
* Using layers of helper methods. This is not (necessarily) an optimization of speed, but rather of readibility and compiling. By using helper methods for certain operations such as `void changeState(int group)`, it makes the code easier to read. Someone with less experience doesn't need to understand how that deep code inside of the method works, but having names like `changeState` makes it very clear what is happening and let's them copy it. It also means the assembly file is smaller, so it decreases storage size.
* Do the calculation of states **once** and then iterate through all the lights, updating them accoording to their group.
# Finishing Touches
In the end, we decided to pad the inside of the sphere with tissues to help in diffusing the light. We considered cotton balls, toilet paper, and normal paper towels. 

I designed a really simple control box using Inventor. It is literally a box with 3 holes in it that sits on top of the arduino/battery pack. This made the design a _little_ more clean, but not that much.

I soldered long wires to the end of the LED strip to have running between the orb and the breadboard.

# The Final Product
Now I know I give Dan a hard time throughout this process for making me do all the work, but I will say, the final product would not have been very special at all without his work. He did an amazing job 3D printing/painting all the dungeon tiles and assembling the whole thing on the board with dry-ice fog. Its a little hard to see the exact colors of the orb in the low light, but this is a great view of the epic battle our characters faced. [That's me in the background of the video :) ]

![29829868 871030426401857 1564642725 O](/uploads/arduino-sun-project/29829868-871030426401857-1564642725-o.jpg "29829868 871030426401857 1564642725 O")

[video](/uploads/arduino-sun-project/video-1522463659-at-dnd.mp4){.video}

(I'll hopefully have a quick demo vid soon to show off what it looks like on the board with all the light patterns and stuff)
# Thoughts 
* Make sure you have fresh batteries before presenting the final product (or at least bring some spares). I had done so much testing on a single set of AAs that they died about halfway through the encounter. A shame, but it was awesome nonetheless.
* Do not concern yourself with inexperience. Jump right in! Before this project, I had very little experience with the Arduino environment. However, I have taken several programming classes that make learnign the Arduino "language" pretty trivial. My experience with circuits was much poorer. I had never made my own circuit, and I would even argue that I still did not in this project, as all I did was assemble smaller circuits that I took from other sources. There is tons of documentation for Arduino projects, and it's **super easy** to find someone who has done something "close enough" to yours for you to modify and improve!
* If you want someone else to work on your project idea/are working on a project based on someone else's idea, make your goals/specification for the project very clear and explicit. This is kind of a note directed at Dan. He's a great guy sometimes, but his lack of programming / electronics knowledge did make it a little challenging to communicate some of the limitations I was working with. Sometimes it felt like he would tell me what I was showing him was "_almost_ perfect" then want to make a change that required me to revisit my basic assumptions/designs, as happened with the randomness thing. In the end, I learned that it's also important to ask the person you're working with more questions about what they **actually** want rather than trying to work with semi-clear ideas and ending up costing yourself a lot of time. 
* Make sure you have everything properly connected to ground. Y'all electrical engineers know what I mean.
## What I might do differently
* One thing I would change if I was still working on the project is to add an interruption so that pressing a fourth button would snap the system out of whatever "special" behavior it was in and return it to the normal pulsing behavior. This was not neccessary under the specifications for what we wanted, but would be interesting later. You could use it as a timer for the PC's to solve a problem, and when they solve it, it cuts out the special behavior.
# My Files
The terrain/tiles that Dan used he bought from somewhere, so those are not available here for free (obvi)
[Thingiverse Listing](https://www.thingiverse.com/thing:2886096) Includes
* Sun (both parts)
* Stand
* Control box

**A** version of my code is here, but for the most updated version, check out my Github
[Suncode 6: The final code I used](/uploads/arduino-sun-project/suncode-6.ino "Suncode 6")

[The most up-to-date version is here](https://github.com/nsd4fr/Arduino-Sun)

Circuit Diagram:

![Wiringdiagram](/uploads/arduino-sun-project/wiringdiagram.png "Wiringdiagram")
