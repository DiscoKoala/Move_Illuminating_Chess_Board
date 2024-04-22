#include <Adafruit_NeoPixel.h>
#include "chess.h"

void loop() {
  Board b;
  b.setBoard();
  b.playGame();
  delay(5000);
}
