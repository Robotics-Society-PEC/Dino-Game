/*
*Robotics Pec
*robotics@pec.edu.in
*
*                    GNU GENERAL PUBLIC LICENSE
*                       Version 3, 29 June 2007
*
*Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
*Everyone is permitted to copy and distribute verbatim copies
*of this license document, but changing it is not allowed.
*
*The GNU General Public License is a free, copyleft license for
*software and other kinds of works.
*
*THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
*APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
*HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
*OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
*THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
*PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
*IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
*ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
*/


/*
  Dino game on arduino

  This sketch Demonstrates how to use a 16x2 lCD display, 
  to recreate the legendary Chrome dino game
  
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 7
 * LCD D5 pin to digital pin 6
 * LCD D6 pin to digital pin 5
 * LCD D7 pin to digital pin 4
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.
*/

// include the library code:
#include <LiquidCrystal.h>

// defined the pins for the LCD
#define RS 12
#define EN 11
#define D4 7
#define D5 6
#define D6 5
#define D7 4

// defined button pin for input
#define BTN_PIN 2

// defined dinasour position as 2
#define dinasour_position 2

// variable to check if game is started or stopped
int game_start = 0;

// variables for the tree position
int tree0 = 0;
int tree1 = 0;
int tree2 = 0;
int tree3 = 0;

// variable to know the position of treethat has collided
int collision_tree = 0;

// variable is set when the dinasour jumps
int Jump = 0;
// variable is set after the jump variable to avoid collision
bool did_jump = false;
// variable to store the score
int score = 0;
// variable to store the score
int high_score = 0;
// variable to define the animation of dinasour
int motion = 0;
// this variable defines delay in each step in ms
// reducing this variable increases the game speed
int game_speed = 300;

// initialize the library by assosicating any needed LCD interface pins
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);


// defined binaries for the tree
byte tree[8] = { 0B00100,
                 0B00101,
                 0B00101,
                 0B10101,
                 0B10110,
                 0B01100,
                 0B00100,
                 0B00100
                 };

// defined binaries for dinasour animation
byte dina1[8] = { 0B00111,
                  0B00100,
                  0B00111,
                  0B00100,
                  0B00100,
                  0B01100,
                  0B10010,
                  0B10000
                  };

byte dina2[8] = { 0B00111,
                  0B00100,
                  0B00111,
                  0B00100,
                  0B00100,
                  0B01100,
                  0B10010,
                  0B00010
                  };

// defined a function to spawn a new tree 
void spawnTree(int &tree, int &tree_previous){
      randomSeed(analogRead(A0));
      tree = random(4,12) + tree_previous;
}

// defined a function to display the tree
void displayTree(int &tree){
  if(tree <=16){
    lcd.setCursor(tree , 1);
    lcd.write((uint8_t)0); 
  }
}

// defined a function to display the dinasour motion
void displayDinasour(){
  if(motion){
    lcd.write((uint8_t)1);
    motion--;
    }
    else{
      lcd.write((uint8_t)2);
      motion++;
    }
}

// defined a function to check if the dinasour collided with a tree
bool collisionCheck(int &tree){
  if(tree == dinasour_position){
    collision_tree = tree;
  }
  return (tree == dinasour_position);
}

// function to read button input and initiate jump if game is running if not then start the game
void jump(){ 
  if (game_start){
    Jump = 1;
  } 
  else {
    game_start = 1;

    // spawn the 4 trees when the game starts
    tree0 = 15;
    spawnTree(tree1,tree0);
    spawnTree(tree2,tree1);
    spawnTree(tree3,tree2);
  }
}

// Setup
void setup() {
  // Create the character for the dinasour and tree
  lcd.createChar(0, tree);
  lcd.createChar(1, dina1);
  lcd.createChar(2, dina2);
  
  // initialised the LCD
  lcd.begin(16, 2);
  lcd.print("Press to start");
  
  // defined the button pin as input and set up an intrrupt on falling edge 
  pinMode(BTN_PIN , INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), jump,  FALLING);
}

// Super loop
void loop() {

  // Check if game_start variable is set if yes then start the game
  while (game_start) {
    
    //if the tree position is less than 0 then respawn the tree 
    if(tree0 < 0){
      spawnTree(tree0,tree3);
    }

    if(tree1 < 0){
      spawnTree(tree1,tree0);
    }

    if(tree2 < 0){
      spawnTree(tree2,tree1);
    }

    if(tree3 < 0){
      spawnTree(tree3,tree2);
    }

    // set did_jump variable to 0 
    did_jump = false;
    
    // cleared display to display new frame
    lcd.clear();

    // if button is pressed, do the jump animation and set did_jump variable to true
    if (Jump){
      lcd.setCursor(dinasour_position , 0);
      Jump = 0;
      did_jump = true;
    } 
    else{
      lcd.setCursor(dinasour_position , 1);
    }

    // display the dinasour
    displayDinasour();

    // if the tree is position is less than 16 then only display it
    // This is done to avoid avoid false tree appearing on middle display
    displayTree(tree0);
    displayTree(tree1);
    displayTree(tree2);
    displayTree(tree3);
    
    // do a collision check if the dinsour collided with a tree  
    // collision is detected
    if((collisionCheck(tree0) || collisionCheck(tree1) ||collisionCheck(tree2) ||collisionCheck(tree3)) && !did_jump ){
      
      // if current score is greater than high score then change the high score
      if(score > high_score){
        high_score=score;
      }

      // stop the game
      game_start = 0;
      
      // collision animation BEGIN
      // dispaly the dinasour and the tree 
      lcd.clear();
      lcd.setCursor(collision_tree+1,1);
      lcd.write((uint8_t)0);
      lcd.setCursor(collision_tree,1);
      lcd.write((uint8_t)1);

      // wait for some time and clear the display
      delay(300);
      lcd.clear();
      delay(600);
      
      // display the dinasour and the tree
      lcd.setCursor(collision_tree+1,1);
      lcd.write((uint8_t)0);
      lcd.setCursor(dinasour_position,1);
      lcd.write((uint8_t)1);

      // wait for some time and clear the display
      delay(600);
      lcd.clear();
      delay(500);

      // display the dinasourr and the tree
      lcd.setCursor(collision_tree+1,1);
      lcd.write((uint8_t)0);
      lcd.setCursor(dinasour_position,1);
      lcd.write((uint8_t)1);
      // collision animation END

      // clear the display and wait for some time to display high score
      delay(600);
      lcd.clear();
      delay(600);

      // display the high score
      lcd.print("High Score: ");
      lcd.print(high_score);
      lcd.setCursor(0, 1);
      lcd.print("Score: ");
      lcd.print(score);

      // wait for some time
      delay(1500);
      lcd.clear();
      delay(400);

      // write play again on screen
      lcd.setCursor(0, 0);
      lcd.print("Press Again to");
      lcd.setCursor(0, 1);
      lcd.print("Play");
      score =0;
      break;
    }
    else{
      // increment the score counter if collision did not occur
      score++;
    }
    
    // decrease the distance of all the trees by 1
    tree0 --;
    tree1 --;
    tree2 --;
    tree3 --;

    // delay for time defined by game_speed, before the next frame is rendered
    delay(game_speed);
  }
}
