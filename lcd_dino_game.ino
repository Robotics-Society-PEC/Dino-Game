
#include <LiquidCrystal.h>

#define dinasour_position 2


int game_start = 0;
int nearest_tree = 15;
int dinasour_line = 0;
int Jump = 0;
bool did_jump = false;

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);


byte tree[8] = { B00100,
                 B00101,
                 B00101,
                 B10101,
                 B10110,
                 B01100,
                 B00100,
                 B00100
               };

byte dina[8] = { B00111,
                 B00100,
                 B00111,
                 B00100,
                 B00100,
                 B01100,
                 B10010,
                 B10010
               };
void jump()
{ if (game_start)
  {
    Jump = 1;

  } else {
    game_start = 1;
    lcd.clear();
    lcd.write((uint8_t)1);
    nearest_tree = 15;
  }

}

void setup() {


  lcd.createChar(0, tree);
  lcd.createChar(1, dina);
  lcd.begin(16, 2);
  lcd.print("press to start");




  pinMode(2 , INPUT);
  attachInterrupt(digitalPinToInterrupt(2), jump,  FALLING);
}



void loop() {





  while (game_start) {
    if (nearest_tree < 0)
    {
      nearest_tree = 15;
    }
    did_jump = false;
    lcd.clear();
    if (Jump) {
      lcd.setCursor(dinasour_position , 0);
      Jump = 0;
      did_jump = true;
    } else {
      lcd.setCursor(dinasour_position , 1);
    }

    lcd.write((uint8_t)1);

    lcd.setCursor(nearest_tree , 1);
    lcd.write((uint8_t)0);


    if (nearest_tree == dinasour_position && !did_jump )
    {
      // collison
      did_jump = false;
      game_start = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("game over");
      lcd.setCursor(0, 1);
      lcd.print("press again");
      break;
    }

    nearest_tree --;
    delay(250);

  }


}
