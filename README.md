# ECE387Midterm

Mary Floren
ECE 387 Midterm
Spring 2016

For my midterm project I ordered a pair of of glasses that have a panel of LEDS across the front in place of where the lenseswould be. I ordered these from hackaday.com and a box came of multiple parts with assembly required. 

The controller board of these glasses is located on the right earpiece that can be connected to the computer through a USB cable. These glasses come with two different controller boards. One is preprogrammed and cycles through a few basic light patterns on the LED panel, and the other does not contain any preprogramming of the LEDs and is the "hackable" LED board that allows for customization because it has several i/0 ports. I also ordered an audio sensor and  will program the LED display to respond to audio input, such as music, and display patterns in response to the input. The audio sensor consists of a small microphone and a graphic equilizer display filter, which is a CMOS chip that will split audio into different bands of the audio spectrum and convert it into the dc equivalent. I will use the board that does not have any current programming of the LEDs to do this because my code will be quite a bit different from the preprogrammed code. It will contain instructions that have to interpret information from the audio sensor and then communicate with different parts of the LED board corresponding to specific inputs. 
Since the on-board processor is equipped with an Arduino-compatible bootloader, I will use Arduino software to program these glasses. When the project is over, I can test the functionality by playing music and seeing if the LED panel responds correctly.  
