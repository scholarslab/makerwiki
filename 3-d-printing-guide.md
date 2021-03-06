<!-- TITLE: 3D Printing Guide -->
<!-- SUBTITLE: A comprehensive tutorial on 3D printing, adapted from the "Technologist Training" document, written by Nicolas Dalton  -->

# Why this is here
This guide is here to provide an eternal resource for Technologists of the Makerspace. The biggest challenge about jumping into a job like this is all the new information. Working at the Makerspace is truly a learning experience, so we wanted to share our insights and tips on how to use the tools in the Makerspace effectively. A lot of times, we will make decisions based on intuition, and this guide is here to give you a basic sense of what that intuition looks like. Happy printing!

# List of Topics:
Use the scrolling list on the left to skip to your topic of interest, or read the whole thing and become a 3D printing wizard!

# Choosing a Printer
# Using Slicers
## Choosing a slicer
Choosing a slicing software to use mostly comes down to what printer you would like to use. You can slice for any of the printers in the Makerspace using Simplify 3D on the PC. 

If you are using the TAZ, you can also choose to use Cura Lulz on either desktop
If you are using the Ultimaker, you can use Cura, Cura Lulz, or Simplify3D.
	Note that vanilla Cura is a little clunky and can be hard to use.
If you are using the Makerbot Replicator, you must use Simplify 3D on the PC!
* Use the "The Doge" profile. It is customized for our printer. Also, remember not to hit save after you are finished slicing a particular object, as this overrides the default printing profiles.

## Slicing Settings
The most important settings that control the quality of your print are
* Layer Height
* Percent Infill
* Number of Shells
* Rafting
* Brimming/Skirting
### Layer Height
Layer Height is the Z-axis resolution of the print, a larger value means the print will go fast, but the print might be lower quality. In the Makerspace, we have some examples of this. A good mean value is .2-.25

![Res 1 Pt 1](/uploads/3-d-printing-guide/res-1-pt-1.png "Res 1 Pt 1")
### Percent Infill
This parameter describes the internal "density" of the print. It can affect time, but its not a huge player. It plays a strong role in determining strength, but on a logarithmic time scale. So for example, 100% infil is not that much stronger than 50% infill. Essentially, you get big jumps in strength when infill is low, and progressively smaller increases in strength for the same increased in infill. A good mean value is about 20-25%

![Smith 2](/uploads/3-d-printing-guide/smith-2.png "Smith 2")

### Number of Shells
This setting has a medium effect on time, but has a strong effect on strength. A good number is 2-3 for most prints. For prints where strength is critical, consider 5-10.

![Smith 5](/uploads/3-d-printing-guide/smith-5.png "Smith 5")

### Rafting
This setting is more on/off than setting a number. Turn it on when you have a poorly shaped print base, but it can leave strong scarring on the bottom of your print. It can also be tough to remove. To make it a little easier to handle, consider lowering the "density" of the rafting to help the removal. Helps to prevent peeling at the corners of prints. 

Example of Good Rafting:

![Main Qimg 6706 Ee 1 D 4848 B 0 Cec 431 B 4315 Fbf 8 Bee C](/uploads/3-d-printing-guide/main-qimg-6706-ee-1-d-4848-b-0-cec-431-b-4315-fbf-8-bee-c.jpg "Main Qimg 6706 Ee 1 D 4848 B 0 Cec 431 B 4315 Fbf 8 Bee C")

Bad Rafting:

![Raft No Removable En](/uploads/3-d-printing-guide/raft-no-removable-en.jpg "Raft No Removable En")

### Skirting and Brimming
Brimming prints extra circumferential material that is attached to the edge of the print. It is great for preventing peeling without resorting to rafting. Adjust the number of brims for extra support. Usually 2-3 is ok, bump to 5-6 if necessary. Peel off or use an X-acto to remove

![Brimming](/uploads/3-d-printing-guide/brimming.png "Brimming")

Skirting is a way to "prime the pump" of the extruder. It extrudes an extra few cm of material before the print begins. We almost always have this setting turned on, as it does not have any negative impacts and almost always is necessary. Helps to get a clean first layer.

![Skirting](/uploads/3-d-printing-guide/skirting.png "Skirting")
# Determining if a Model is Suitable for Printing
## The Contact with the Print Bed
A great first place to start when you are evaluating a model for printability is the contact area between the model and the print bed. What you are looking for is a flat surface with not too much surface area. 

![First Layer](/uploads/3-d-printing-guide/first-layer.png "First Layer")

What do you do if the model has poor contact with the print bed?
* Use support material
* Sink the model into the print bed in the slicing software
* Don't print it
* Explain to the patron that even with modifications, there is no guarantee that the print will come out good. 

### Example of a model with poor contact area:

![Bad Model](/uploads/3-d-printing-guide/bad-model.png "Bad Model")

### Example of a model with good contact area:

![Good Model](/uploads/3-d-printing-guide/good-model.png "Good Model")

### However
You can have a model that at first glance, appears to have a good contact area. However, it can be deceiving. In this model, the bottom is indeed square, but the bottom, instead of being flat and smooth, was composed of hundreds of dots. That resulted in the following. 

![Really Bad](/uploads/3-d-printing-guide/really-bad.png "Really Bad")

### How to avoid this
* Check the bottom layer in the slicer-generated preview
* Make sure it is smooth
* Add a raft so that there is small rafting of material to give a smooth interface
* Don't print it

## Overhang
Given the following shape, you can have 3 different scenarios
![Overhang](/uploads/3-d-printing-guide/overhang.png "Overhang")
### Angle is > 45 degrees
Perfectly fine. There shouldnt be any problems
### Angle is = 45 degrees
Starts to get risky. Consider taking measures to prevent failure
### Angle is < 45 degrees
Gets more risky. A model with this bad of an overhang will almost definitely need preventative measures. Consider adding support material. Some prints _might_ not need the support. Preventative measures include support material or layer height reduction. 
# Changing the Extruder on a TAZ 5
* [Official documentation](https://ohai.lulzbot.com/project/flexystruder-v2-install-lulzbot-taz-5/)

### Cut the filament
Use a pair of pliers to snip the filament coming from the top of the extruder. Or you can remove it.
### Disconnect the extruder cable
_Carefully_ remove the cable connecting the extruder to the TAZ. Be careful not to bend/break the pins on the end of the connection.
### Remove the registration screw
Use one of the allen wrenches in the tool box to unscrew the registration screw. This is the only thing actually holding the extruder head to the printer.
### Lift out the old extruder
Gently lift the old extruder out of the cradle. Be careful not to bend/break the cable connections in this step. Place the old extruder into its box.
### Insert the new extruder
Gently lower the new extruder into the cradle. Be careful not to bend/break the cable connections in this step.
### Replace the registration screw
Be careful that it properly aligns with the screw hole in the cradle.
### Re-connect the extruder cables
Carefully align and reconnect the electronic cables making sure that they align
### Flash the firmware
If it is connected to the desktop, disconnect the TAZ from the desktop computer. Once it is **disconnected**, begin the process of changing the tool head in Cura Lulz by selecting Machines->Lulzbot TAZ 5 -> Change Extruder. Follow through the steps, entering the correct parameters for our TAZ printer. At the end, select Flash the Firmware. **THEN** connect the TAZ to the desktop PC and make sure the flashing process begins and completes before removing the cable connection. 
### Calibrate the Z-axis
Loosen the black thumb screw located on the left side of the printer by at least one full turn. This screw determines the Z-height when the printer is "homed". If the printer is not properly homed in the Z-axis, it can drag the hot end through the bed, damaging the printer, or be too high, making the print quality low. Take out the calibration tool, or a piece of paper if you don't have one. The Makerspace calibration tool has a small piece of blue tape on the proper-thickness edge. Continue to tighten the screw and re-home the TAZ until the edge barely slides under the hot end without scraping it. Tighten the screw in increments of 1/4 - 1/2 turns.
### You're ready to print!
Now load the proper filament for the extruder head you are using and begin to print.