# :capital_abcd: :1234: HOMEWORK 4 :capital_abcd: :1234:  

# Task Requirements

•Components: a  joystick,  a  4  digit  7-segment  display,  a  74hc595  shift register  

•General Description:  
Use the joystick to move through the 4 digit 7segment displays digits, press the button to lock in on the current digitand use the other axis to increment or decrement the number.  Keep thebutton pressed to reset all the digit values and the current position to thefirst digit in the first state.The system has the following states:  
1.First state:you can use a joystick axis to cycle through the 4 digits;using the other axis does nothing.  A blinking decimal point showsthe current digit position.  When pressing the button, you lock in onthe selected digit and enter the second state.  
2.Second state:in this state, the decimal point stays always on, nolonger blinking and you can no longer use the axis to cycle throughthe  4  digits.   Instead,  using  the  other  axis,  you  can  increment  ondecrement  the  number  on  the  current  digit  IN  HEX  (aka  from  0to F, as in the lab).  Pressing the button again returns you to theprevious state.  Also, keep in mind that when changing the number, you  must  increment  it  for  each  joystick  movement  -  it  should  notwork continuosly increment if you keep the joystick in one position (aka with joyMoved).  
3.  Reset:  toggled by long pressing the buttononly in the first state.When resetting, all the digits go back to 0 and the current positionis set to the first (rightmost) digit, in the first state.

#  Picture of the setup
![20221113_212626](https://user-images.githubusercontent.com/79162778/201541967-80760647-e67c-461c-a834-5cf022d35fab.jpg)


# Link to video showcasing functionality
https://youtube.com/shorts/1ZTTf7xqs2w
