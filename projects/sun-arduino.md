<!-- TITLE: (WiP) Arduino-Controlled Sun Model-->
<!-- SUBTITLE: An Arduino-Controlled model of the Sun as a prop for a tabletop RPG -->

# Details
Name: Nicolas Dalton
Contact Info: nsd4fr@virginia.edu. I am happy to talk to you about this project!
Level of Completion: Complete, but not polished
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

Once we settled on the moon model, I cut it up in Meshmixer, hollowing it out so that we could put lights on the inside and cutting a lid onto it so that we could insert the lights and then glue it shut. (put our models on Thingiverse and link them here)

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

[video](/uploads/arduino-sun-project/video-1517678096.mp4){.video}


# TO DO
Upload models on Thingiverse, post many pictures, post code, etc.