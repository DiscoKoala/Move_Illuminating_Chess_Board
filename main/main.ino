#include <Adafruit_NeoPixel.h>
#include "chess.h"

void loop() {
  Board b;
  bool newgame = true;
  char buffer[1];

  while(newgame){
    b.setBoard();

    while(b.playGame()){
      Serial.println("New game? y for yes, anything else for no");
      Serial.readBytes(buffer, 1);

      if(buffer[0] != 'y'){
        newgame = false;
      }

    }
  }
  
  delay(5000);
}
