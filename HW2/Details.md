# Homework #2
# Task Requirements
Deadline (hard):  Your respective lab in week October 31 - November6.  You must have the Git ready and the assignment turned in beforethe lab.  
As was described in the course, the homework consists of the following:  

•Components: 5 LEDs, 1 button, 1 buzzer, resistors and wires (per logic) 

•General  description:Building  the  traffic  lights  for  a  crosswalk.   You will use 2 LEDs to represent the traffic lights for people (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green). See the states it needs to go through.  If anything is not clear, ask.  Also,see the uploaded video (the intervals are different, but the states flow isthe same).  It’s a traffic lights system for people and cars - don’t overthink it. 

The system has the following states: 

1.State 1(default, reinstated after state 4 ends):  green light for cars,red  light  for  people,  no  sounds.   Duration:  indefinite,  changed  bypressing the button 
2.State 2(initiated by counting down 8 seconds after a button press):the  light  should  be  yellow  for  cars,  red  for  people  and  no  sounds.Duration:  3 seconds.
3.State 3(initiated after state 2 ends):  red for cars, green for peopleand a beeping sound from the buzzer at a constant interval. Duration:8 seconds. 
4.State 4(initiated after state 3 ends):  red for cars,blinking greenfor people and a beeping sound from the buzzer,  at a constant in-terval,  faster than the beeping in state 3.  This state should last 4seconds.Be  careful:  pressing  the  button  in  any  state  other  than  state  1  should NOT yield any actions.  

•Publishing task:You must add the code to the Github repo and continueupdating the readme with at least the following details (but feel free tobe more creative).  I recommend using dropdowns in the readme, for eachproject, if you feel the readme is too cluttered:https://gist.github.com/citrusui/07978f14b11adada364ff901e27c7f611.  
1.Task Requirements  
2.Picture of the setup  
3.Link to video showcasing functionality (I recommend youtube,  butanything I can access is fine)  
4.Remember to publish the video in the correct orientation.  Don’t dothis:https://youtu.be/Y8H0PlUtcto5. Hand in the homework on MS teams when done - aka when Git is up to date

•Coding task:Coding style is of utmost importance.  You must have aperfectly clean code in order to receive the maximum grade.  An importantcoding challenge present in this task is using millis() instead of delay(). However, remember that the bulk of the grade is if the projectsworks. Do not tend to small details unless you have the entire functionality done. 

# Picture of the setup

# Link to video showcasing functionality
