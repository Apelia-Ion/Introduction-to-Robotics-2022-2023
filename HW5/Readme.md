# :video_game: Homework 5 - Game Menu - :video_game:
The menu should include the following functionality:  
1. When powering up a game, a greeting message should be shown for a few moments.  
2. Should contain roughly the following categories:  
  (a) Start game, starts the initial level of your game  
  (b) Highscore:  
    - Initially, we have 0.  
    – Update it when the game is done. Highest possible score should be achieved by starting at a higher level.  
    – Save the top 5+ values in EEPROM with name and score.  
  (c) Settings:  
    – Enter name. The name should be shown in highscore. Maybe somewhere else, as well?    
    – Starting level: Set the starting level value. The idea is to be able to start from a higher level as well. Can be replaced with difficulty.    
    – LCD contrast control (optional, it replaces the potentiometer). Save it to eeprom.  
    – LCD brightness control (mandatory, must change LED wire that’s directly connected to 5v). Save it to eeprom.  
    – Matrix brightness control (see function setIntesnity from the ledControl library). Save it to eeprom.  
    – Sounds on or off. Save it to eeprom.  
    – Extra stuff can include items specific to the game mechanics, or other settings such as chosen theme song etc. Again, save it to eeprom.  
  (d) About: should include details about the creator(s) of the game. At least game name, author and github link or user (use scrolling text?)  
  (e) How to play: short and informative description  
3. While playing the game: display all relevant info  
    – Lives  
    – Level  
    – Score  
    – Time?  
    – Player name?  
    – etc  
4. Upon game ending:  
  (a) Screen 1: a message such as ”Congratulations on reaching level/score X”. ”You did better than y people.”. etc. Switches to screen 2 upon interaction (button press) or after a few moments.  
  (b) Screen 2: display relevant game info: score, time, lives left etc. Must inform player if he/she beat the highscore. This menu should only be closed by the player, pressing a button.  
  
  # Picture of the setup  
  
  # Link to video showcasing functionality  
