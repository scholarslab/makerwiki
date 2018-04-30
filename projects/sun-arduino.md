<!-- TITLE: (WiP) Arduino-Controlled Sun Model-->
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


# Inspirations!
This project was brought to me by Dan Foulds, a good friend (and DM!) of mine. He wanted to create a small model of the Sun that could be used in for Dungeons and Dragons for our game. But, he also wanted it to have several cool light patterns that would correlate to different situations in the game. Essentially, he had this idea and wanted me to help him make it real. The goal: A 3D printed, LED-filled, controllable, independently powered model of the Sun.
# First steps!
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

## Step 1: Let there be light
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



## Step 2: Make the light good
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

## Step 3: Controlling and Cool Patterns

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


## Step 4: Making it random.
So despite my ultimate ability to make things look amazing, Dan was just not satisfied. He did not just want a static pattern, but a dynamic, randomly fluctuating distribution of lights so that the orb would really look like the sun. Sometimes a spot would be red, sometimes orange. This was perhaps the most challenging aspect of the code from a design/CS standpoint.

I went through 3 iterations of code for this process before getting something that satisfied the specification.

The first attempt involved keeping track of both the up/down state (increasing brightness or decreasing brightness) and the color state (red, yellow, orange). The code then looped through the arrays and assigned the next value of the LED according to its corresponding entries in the array. However, this code was far too inefficient. This required multiple array accesses for each LED (of which there were 60), and then multiple if-conditional statements about the current state of that LED to determine what its next value should be. Maybe on a faster processor, this amount of control would not be excessive, but on the tiny little nano, the light color changing became sluggish. 

The second iteration was barely better, and it was not until the third iteration that I found a working solution. I put all the LEDs into 6 groups, each group of 10 LEDs would have its own state values. I also made big improvements to the control structure that determined what the next value of an LED should be. This decreased the number of array accesses and vastly increased the speed of the system. Instead of checking the color state, then the increasing/decreasing state, I had it check the increasing/decreasing state first, then the color state. In terms of combinatorics, this sounds identical. But the Arduino switch() conditional is fairly computationally expensive, and having if-then statements inside of a switch() is much worse practically than a switch() inside of if-then. 

The choice of 6 groups was arbitrary, but it having 6 groups of 10 lights each seemed like reasonable values.

### Minor Optimizations
* Using arrays of bytes instead of arrays of ints. Ints use up more memory than bytes, so using bytes instead of ints (especially as a global variable) for small numbers is a nice little optimization that while not neccessary in this project, might be a necessary change in a more sophisticated project.
* Using layers of helper methods. This is not (necessarily) an optimization of speed, but rather of readibility and compiling. By using helper methods for certain operations such as `void changeState(int group)`, it makes the code easier to read. Someone with less experience doesn't need to understand how that deep code inside of the method works, but having names like `changeState` makes it very clear what is happening and let's them copy it. It also means the assembly file is smaller, so it decreases storage size.
* Do the calculation of states **once** and then iterate through all the lights, updating them accoording to their group.

# TO DO
Upload models on Thingiverse, post many pictures, post code, etc.

[video](/uploads/arduino-sun-project/video-1519528979-twinkling-light-strips.mp4){.video}