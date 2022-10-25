# Homework #1  

# Task Requirements
Deadline (hard):    
Your respective lab in the week of October 24-30.As was described in the laboratory, the homework consists of the following:  
•Components:  RBG  LED  (1  minimum),  potentiometers  (3  minimum), resistors and wires (per logic)  
•Technical Task:Use a separat potentiometer in controlling each of thecolor of the RGB led (Red,Green andBlue).The control must be donewithdigital electronics(aka you must read the value of the potentiome-ter with Arduino, and write a mapped value to each of the pins connectedto the led.  
•Publishing task:You must add the code to the Git repo and continueupdating the readme with at least the following details (but feel free tobe more creative):  
1.  Task Requirements  
2.  Picture of the setup  
3.  Link to video showcasing functionality (I recommend youtube,  butanything I can access is fine)  
4.  Remember to publish the video in the correct orientation.  Don’t dothis:https://youtu.be/Y8H0PlUtcto5.Hand in the homework on MS teams when done - aka whengit is up to date  
•Coding task:Coding style is of utmost importance.  You must have aperfectly clean code in order to receive the maximum grade.  Keep in mindthat magic numbers are not accepted, although you might see them in thelab (as a trade-off for speed).  Remember to be consistent in your style,check  the  style  guide  and  the  provided  style  document  and  use  correctspacing.Example used in lab which would not yield the maximum grade:  ”analog-Write(ledPin, potValue / 4) or ”voltage = potValue * 5.0 / 1023.0”.Mistakes observed there:  
1.  ”potValue / 4” is not precise, since the value does not always splitinto 4 perfectly.  Use themap() function    
2.  We calculate the value inside the analogWrite function   
3.potValueandpotPinare not ideal naming versions. What happensif you change your potentiomer with a slider?  (a slider has the sameoutput range, so no change to the code would be needed - if writtencorrectly)4. 4is  a  magic  number.5.0and1023.0are  magic  numbers.   Theyshould be replaced with constants, such asmaxAnalogValue, max-VoltageValue etc  

# Picture of the setup:
![20221025_232720](https://user-images.githubusercontent.com/79162778/197879955-f770254f-0910-49e1-a922-af982c2cc92c.jpg)
# Link to the video:
 https://youtu.be/K3GXn9-0YPw
