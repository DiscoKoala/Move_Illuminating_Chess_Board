#include "chess.h"
#include "sensors.h"

#include <Adafruit_NeoPixel.h>
#include <Adafruit_MCP23X17.h>

#define LED_PIN    6

#define LED_COUNT 96

// LED Strip
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Switch chips
Adafruit_MCP23X17 mcp1;
Adafruit_MCP23X17 mcp2;
Adafruit_MCP23X17 mcp3;
Adafruit_MCP23X17 mcp4;

void setup() {
  strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();             // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)

  Serial.begin(9600);

  // Initialize MCP chip objects
  if (!mcp1.begin_I2C(0x20)) {
    Serial.println("Error0.");
    while (1);
  }

  if (!mcp2.begin_I2C(0x21)) {
    Serial.println("Error1.");
    while (1);
  }

  if (!mcp3.begin_I2C(0x22)) {
    Serial.println("Error2.");
    while (1);
  }

  if (!mcp4.begin_I2C(0x23)) {
    Serial.println("Error3.");
    while (1);
  }

  // Using pinMode for Chip 1
  mcp1.pinMode(HS0, INPUT);
  mcp1.pinMode(HS1, INPUT);
  mcp1.pinMode(HS2, INPUT);
  mcp1.pinMode(HS3, INPUT);
  mcp1.pinMode(HS4, INPUT);
  mcp1.pinMode(HS5, INPUT);
  mcp1.pinMode(HS6, INPUT);
  mcp1.pinMode(HS7, INPUT);
  mcp1.pinMode(HS8, INPUT);
  mcp1.pinMode(HS9, INPUT);
  mcp1.pinMode(HS10, INPUT);
  mcp1.pinMode(HS11, INPUT);
  mcp1.pinMode(HS12, INPUT);
  mcp1.pinMode(HS13, INPUT);
  mcp1.pinMode(HS14, INPUT);
  mcp1.pinMode(HS15, INPUT);

  // Using pinMode for Chip 2
  mcp2.pinMode(HS16, INPUT);
  mcp2.pinMode(HS17, INPUT);
  mcp2.pinMode(HS18, INPUT);
  mcp2.pinMode(HS19, INPUT);
  mcp2.pinMode(HS20, INPUT);
  mcp2.pinMode(HS21, INPUT);
  mcp2.pinMode(HS22, INPUT);
  mcp2.pinMode(HS23, INPUT);
  mcp2.pinMode(HS24, INPUT);
  mcp2.pinMode(HS25, INPUT);
  mcp2.pinMode(HS26, INPUT);
  mcp2.pinMode(HS27, INPUT);
  mcp2.pinMode(HS28, INPUT);
  mcp2.pinMode(HS29, INPUT);
  mcp2.pinMode(HS30, INPUT);
  mcp2.pinMode(HS31, INPUT);

  // Using pinMode for Chip 3
  mcp3.pinMode(HS32, INPUT);
  mcp3.pinMode(HS33, INPUT);
  mcp3.pinMode(HS34, INPUT);
  mcp3.pinMode(HS35, INPUT);
  mcp3.pinMode(HS36, INPUT);
  mcp3.pinMode(HS37, INPUT);
  mcp3.pinMode(HS38, INPUT);
  mcp3.pinMode(HS39, INPUT);
  mcp3.pinMode(HS40, INPUT);
  mcp3.pinMode(HS41, INPUT);
  mcp3.pinMode(HS42, INPUT);
  mcp3.pinMode(HS43, INPUT);
  mcp3.pinMode(HS44, INPUT);
  mcp3.pinMode(HS45, INPUT);
  mcp3.pinMode(HS46, INPUT);
  mcp3.pinMode(HS47, INPUT);

  // Using pinMode for Chip 4
  mcp4.pinMode(HS48, INPUT);
  mcp4.pinMode(HS49, INPUT);
  mcp4.pinMode(HS50, INPUT);
  mcp4.pinMode(HS51, INPUT);
  mcp4.pinMode(HS52, INPUT);
  mcp4.pinMode(HS53, INPUT);
  mcp4.pinMode(HS54, INPUT);
  mcp4.pinMode(HS55, INPUT);
  mcp4.pinMode(HS56, INPUT);
  mcp4.pinMode(HS57, INPUT);
  mcp4.pinMode(HS58, INPUT);
  mcp4.pinMode(HS59, INPUT);
  mcp4.pinMode(HS60, INPUT);
  mcp4.pinMode(HS61, INPUT);
  mcp4.pinMode(HS62, INPUT);
  mcp4.pinMode(HS63, INPUT);
}

Square::Square() {
  piece = EMPTY;
  color = NONE;
}

void Square::setSpace(Square* space) {
  color = space->getColor();
  piece = space->getPiece();
}

void Square::setEmpty() {
  color = NONE;
  piece = EMPTY;
}

Piece Square::getPiece() {
  return piece;
}

Color Square::getColor() {
  return color;
}

void Square::setPieceAndColor(Piece p, Color c, int squareNum) {
  piece = p;
  color = c;
  num = squareNum;
}

bool Board::doMove() {
  int x1, x2, y1, y2;
  int squareNum = -1;
  bool stop = false;

  // Get coordinates of the square where piece was lifted.
  // Get coordinates of the square that piece was moved to.
  // If the move is valid, update the state of the board.
  // If move in not valid, keep lights lit unless piece is moved back.
  while (!stop) {

    // TODO: loop through board return square number
    // Use square number to determine turn and x,y coordinates.
    // Map from square number to x,y
    // Read through array, return true if sensor is tripped. false otherwise.

    // Continuously loop through the board  to check for changes in sensor states.
    while(squareNum < 0){
      squareNum = checkBoard();
    }

    // Get x,y coordinates for a given square
    x1 = getSquareByNum(squareNum)->getX();
    y1 = getSquareByNum(squareNum)->getY();

    if (getSquare(x1, y1)->getColor() == turn) {
        
        switch(getSquare(x1, y1)->getPiece()){
          case KING: kingMoves(y1, x1); break;
          case QUEEN: queenMoves(y1, x1); break;
          case BISHOP: bishopMoves(y1, x1); break;
          case KNIGHT: knightMoves(y1, x1); break;
          case ROOK: rookMoves(y1, x1); break;
          case PAWN: pawnMoves(y1, x1); break;
          default: Serial.println("Something went wrong in the switch statement in makeMove()"); break;
        }
      if (makeMove(x1, y1, x2, y2) == false) {
        continue;
      } else {
        stop = true;
      }
    } 
    // else {
    //   // Handle not the player's turn
    // }
  }
  if (getSquare(x2, y2)->getPiece() == KING) {
    if (getSquare(x1, y1)->getColor() == WHITE) {
      // White wins
      return false;
    } else {
      // Black wins
      return false;
    }
  }

  if (turn == BLACK) {
    turn = WHITE;
  } else {
    turn = BLACK;
  }

  return true;
}

void Board::setBoard() {
  // Set initial board configuration
  square[0][0].setPieceAndColor(ROOK, WHITE, 0);
  square[1][0].setPieceAndColor(KNIGHT, WHITE, 1);
  square[2][0].setPieceAndColor(BISHOP, WHITE, 2);
  square[3][0].setPieceAndColor(KING, WHITE, 3);
  square[4][0].setPieceAndColor(QUEEN, WHITE, 4);
  square[5][0].setPieceAndColor(BISHOP, WHITE, 5);
  square[6][0].setPieceAndColor(KNIGHT, WHITE, 6);
  square[7][0].setPieceAndColor(ROOK, WHITE, 7);

  square[0][7].setPieceAndColor(ROOK, BLACK, 56);
  square[1][7].setPieceAndColor(KNIGHT, BLACK, 57);
  square[2][7].setPieceAndColor(BISHOP, BLACK, 58);
  square[3][7].setPieceAndColor(QUEEN, BLACK, 59);
  square[4][7].setPieceAndColor(KING, BLACK, 60);
  square[5][7].setPieceAndColor(BISHOP, BLACK, 61);
  square[6][7].setPieceAndColor(KNIGHT, BLACK, 62);
  square[7][7].setPieceAndColor(ROOK, BLACK, 63);

  int l = 8;
  for (int i = 0; i < 8; i++){
    square[i][1].setPieceAndColor(PAWN, WHITE, l);
    l++;
  }

  l = 48;
  for (int i = 0; i < 8; i++)
  {
    square[i][6].setPieceAndColor(PAWN, BLACK, l);
    l++;
  }

  int k = 16;
  for (int i = 2; i < 6; i++)
  {
    for (int j = 0; j < 8; j++)
      square[j][i].setPieceAndColor(EMPTY, NONE, k);
      k++;
  }

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
    {
      square[i][j].setX(i);
      square[i][j].setY(j);
    }
}

bool Board::playGame() {
  // Execute game loop
  return doMove();
}

bool Board::moveKing(Square* thisKing, Square* thatSpace) {

  // off board inputs should be handled elsewhere (before this)
  // squares with the same color should be handled elsewhere (before this)

  // If piece is put back turn off lights, return false, and continue turn
  if(thatSpace->getX() == thisKing->getX() && thatSpace->getY() == thisKing->getY()){
    strip.clear();
    return false;
  }

  if (abs(thatSpace->getX() - thisKing->getX()) == 1)
    if (abs(thatSpace->getY() - thisKing->getY()) == 1)
    {
      thatSpace->setSpace(thisKing);
      thisKing->setEmpty();
      strip.clear();
      return true;
    }
    else
      return false;
  else
    return false;
}

bool Board::moveQueen(Square* thisQueen, Square* thatSpace) {
  int queenX = thisQueen->getX();
  int queenY = thisQueen->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();
  int yIncrement;
  int xIncrement;

  bool invalid = false;

  // Placing piece back down 
  if (queenX == thatX && queenY == thatY){
    strip.clear();
    return false;
  }

  if (queenX != thatX || queenY != thatY)
  {
    if (queenX == thatX)
    {
      yIncrement = (thatY - queenY) / (abs(thatY - queenY));
      for (int i = queenY + yIncrement; i != thatY; i += yIncrement)
      {
        if (square[thatX][i].getColor() != NONE)
          return false;
      }
    }
    else if (queenY == thatY)
    {
      xIncrement = (thatX - queenX) / (abs(thatX - queenX));
      for (int i = queenX + xIncrement; i != thatX; i += xIncrement)
      {
        if (square[i][thatY].getColor() != NONE)
          return false;
      }
    }
    else if (abs(queenX - thatX) == abs(queenY - thatY))
    {
      xIncrement = (thatX - queenX) / (abs(thatX - queenX));
      yIncrement = (thatY - queenY) / (abs(thatY - queenY));

      for (int i = 1; i < abs(queenX - thatX); i++)
      {
        if (square[queenX + xIncrement * i][queenY + yIncrement * i].getColor() != NONE)
          return false;
      }
    }
    else
      return false;
  }

  if (invalid == false)
  {
    thatSpace->setSpace(thisQueen);
    thisQueen->setEmpty();
    strip.clear();
    return true;
  }
  else
  {
    return false;
  }

}

bool Board::moveBishop(Square* thisBishop, Square* thatSpace) {

  int bishopX = thisBishop->getX();
  int bishopY = thisBishop->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();
  bool invalid = false;
  Square* s;

  if (bishopX == thatX && bishopY == thatY){
    strip.clear();
    return false;
  }

  if (abs(bishopX - thatX) == abs(bishopY - thatY))
  {
    int xIncrement = (thatX - bishopX) / (abs(thatX - bishopX));
    int yIncrement = (thatY - bishopY) / (abs(thatY - bishopY));

    for (int i = 1; i < abs(bishopX - thatX); i++)
    {
      if (square[bishopX + xIncrement * i][bishopY + yIncrement * i].getColor() != NONE)
        return false;
    }
  }
  else
    return false;

  if (invalid == false)
  {
    thatSpace->setSpace(thisBishop);
    thisBishop->setEmpty();
    strip.clear();
    return true;
  }
  else
  {
    return false;
  }

}

bool Board::moveKnight(Square* thisKnight, Square* thatSpace) {
  int knightX = thisKnight->getX();
  int knightY = thisKnight->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();

  // Placing piece back down
  if (knightX == thatX && knightY == thatY){
    strip.clear();
    return false;
  }

  if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2))
  {
    thatSpace->setSpace(thisKnight);
    thisKnight->setEmpty();
    strip.clear();
    return true;
  }
  else
  {
    return false;
  }

}

bool Board::moveRook(Square* thisRook, Square* thatSpace) {
  // Move rook logic
  int rookX = thisRook->getX();
  int rookY = thisRook->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();
  bool invalid = false;

  // Placing piece back down
  if (rookX == thatX && rookY == thatY){
    strip.clear();
    return false;
  }
  if (rookX != thatX || rookY != thatY)
  {
    if (rookX == thatX)
    {
      int yIncrement = (thatY - rookY) / (abs(thatY - rookY));
      for (int i = rookY + yIncrement; i != thatY; i += yIncrement)
      {
        if (square[thatX][i].getColor() != NONE)
          return false;
      }
    }
    else if (rookY == thatY)
    {
      int xIncrement = (thatX - rookX) / (abs(thatX - rookX));
      for (int i = rookX + xIncrement; i != thatX; i += xIncrement)
      {
        if (square[i][thatY].getColor() != NONE)
          return false;
      }
    }
    else
      return false;
  }
  if (invalid == false)
  {
    thatSpace->setSpace(thisRook);
    thisRook->setEmpty();
    strip.clear();
    return true;
  }
  else
  { // Return some error or something. Probably return false;
    // Maybe make square flash if move isn't valid?
    Serial.println("That is an invalid move for rook");
    return false;
  }

}

bool Board::movePawn(Square* thisPawn, Square* thatSpace) {
  // Move pawn logic
  bool invalid = false;
  int pawnX = thisPawn->getX();
  int pawnY = thisPawn->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();

  // Placing piece back
  if(pawnX == thatX && pawnY == thatY){
    strip.clear();
    return false;
  }

  if (thisPawn->getColor() == WHITE)
  {
    if (pawnX == thatX && thatY == pawnY + 1 && thatSpace->getColor() == NONE)
    {
      thatSpace->setSpace(thisPawn);
      thisPawn->setEmpty();
      strip.clear();
      return true;
    }
    else if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY + 1 == thatY && thatSpace->getColor() == BLACK)
    {
      thatSpace->setSpace(thisPawn);
      thisPawn->setEmpty();
      strip.clear();
      return true;
    }
    else
      return false;
  }
  else if (thisPawn->getColor() == BLACK)
  {
    if (pawnX == thatX && thatY == pawnY - 1 && thatSpace->getColor() == NONE)
    {
      thatSpace->setSpace(thisPawn);
      thisPawn->setEmpty();
      strip.clear();
      return true;
    }
    else if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY - 1 == thatY && thatSpace->getColor() == WHITE)
    {
      thatSpace->setSpace(thisPawn);
      thisPawn->setEmpty();
      strip.clear();
      return true;
    }
    else
      return false;
  }
  else
    return false;

}

bool Board::makeMove(int x1, int y1, int x2, int y2) {
  
  // Make move logic
  Square* src = getSquare(x1, y1);
  Square* dest = getSquare(x2, y2);

  switch (src->getPiece())
  {
    case KING: return moveKing(src, dest); break;
    case QUEEN: return moveQueen(src, dest); break;
    case BISHOP: return moveBishop(src, dest); break;
    case KNIGHT: return moveKnight(src, dest); break;
    case ROOK: return moveRook(src, dest); break;
    case PAWN: return movePawn(src, dest); break;
    case EMPTY: Serial.println("You do not have a piece there"); return false; break;
    default: Serial.println("Something went wrong in the switch statement in makeMove()"); break;
  }
  return false;
}

void Board::kingMoves(int y_coord, int x_coord){
  uint32_t color = strip.Color(255,255,255); // define color to be used (white)

  strip.setPixelColor(LED_BOARD[y_coord][x_coord], color);
  strip.setPixelColor(LED_BOARD[y_coord][x_coord+1], color);
  strip.setPixelColor(LED_BOARD[y_coord][x_coord-1], color);
  strip.setPixelColor(LED_BOARD[y_coord+1][x_coord], color);
  strip.setPixelColor(LED_BOARD[y_coord-1][x_coord], color);
  
  strip.setPixelColor(LED_BOARD[y_coord+1][x_coord+1], color);
  strip.setPixelColor(LED_BOARD[y_coord-1][x_coord-1], color);
  strip.setPixelColor(LED_BOARD[y_coord-1][x_coord+1], color);
  strip.setPixelColor(LED_BOARD[y_coord+1][x_coord-1], color);

  strip.show();
};

void Board::queenMoves(int y_coord, int x_coord){
  uint32_t color = strip.Color(255,255,255); // define color to be used (white)

  int dif = y_coord - x_coord;
  int sum = y_coord + x_coord;
  
  for(int i = 0; i<COL; i++){
    for(int j = 0; j<ROW; j++){
      if(dif == i-j){
        strip.setPixelColor(LED_BOARD[i][j], color); // Set color
      }
      if(sum == i+j){
        strip.setPixelColor(LED_BOARD[i][j], color); // Set color
      }
      if(y_coord == i || x_coord == j){
        strip.setPixelColor(LED_BOARD[i][j], color); // Set color
      }
    }
  }
  strip.show();
};

void Board::bishopMoves(int y_coord, int x_coord){
  uint32_t color = strip.Color(255,255,255); // define color to be used (white)

  int dif = y_coord - x_coord;
  int sum = y_coord + x_coord;
  
  for(int i = 0; i<COL; i++){
    for(int j = 0; j<ROW; j++){
      if(dif == i-j){
        strip.setPixelColor(LED_BOARD[i][j], color); // Set color
      }
      if(sum == i+j){
        strip.setPixelColor(LED_BOARD[i][j], color); // Set color
      }
    }
  }
  strip.show();
};

void Board::knightMoves(int y_coord, int x_coord){
  uint32_t color = strip.Color(255,255,255); // define color to be used (white)

  strip.setPixelColor(LED_BOARD[y_coord][x_coord], color);
  strip.setPixelColor(LED_BOARD[y_coord+2][x_coord+1], color);
  strip.setPixelColor(LED_BOARD[y_coord+1][x_coord+2], color);
  strip.setPixelColor(LED_BOARD[y_coord-1][x_coord+2], color);
  strip.setPixelColor(LED_BOARD[y_coord-2][x_coord+1], color);
  
  strip.setPixelColor(LED_BOARD[y_coord-2][x_coord-1], color);
  strip.setPixelColor(LED_BOARD[y_coord-1][x_coord-2], color);
  strip.setPixelColor(LED_BOARD[y_coord+1][x_coord-2], color);
  strip.setPixelColor(LED_BOARD[y_coord+2][x_coord-1], color);

  strip.show();
};

void Board::rookMoves(int y_coord, int x_coord){
  uint32_t color = strip.Color(255,255,255); // define color to be used (white)
  
  for(int i = 0; i<COL; i++){
    for(int j = 0; j<ROW; j++){
      if(y_coord == i || x_coord == j){
        strip.setPixelColor(LED_BOARD[i][j], color); // Set color
      }
    }
  }

  strip.show();
};

void Board::pawnMoves(int y_coord, int x_coord){
  uint32_t color = strip.Color(255,255,255); // define color to be used (white)

  // if(enemy){
  //   strip.setPixelColor(LED_BOARD[y_coord][x_coord], color);
  //   strip.setPixelColor(LED_BOARD[y_coord+1][x_coord], color);
  //   strip.setPixelColor(LED_BOARD[y_coord+1][x_coord+1], color);
  //   strip.setPixelColor(LED_BOARD[y_coord+1][x_coord-1], color);
  // } else{
  strip.setPixelColor(LED_BOARD[y_coord][x_coord], color);
  strip.setPixelColor(LED_BOARD[y_coord+1][x_coord], color);
  // }
  
  strip.show();
};

// Add logic to only check squares with pieces
int Board::checkBoard(){

  // Read digital inputs for Chip 1 (MCP23017)
  for (int i = 0; i <= 15; i++) {
      int hallState = mcp1.digitalRead(i);
      if (hallState == LOW) {
        if(getSquareByNum(i)->getPiece() != NONE){
          return i;
        }
      }
  }

  // Read digital inputs for Chip 2 (MCP23017)
  for (int i = 16; i <= 31; i++) {
      int hallState = mcp2.digitalRead(i);
      if (hallState == LOW) {
        if(getSquareByNum(i)->getPiece() != NONE){
          return i;
        }
      }
  }

  // Read digital inputs for Chip 3 (MCP23017)
  for (int i = 32; i <= 47; i++) {
      int hallState = mcp3.digitalRead(i);
      if (hallState == LOW) {
        if(getSquareByNum(i)->getPiece() != NONE){
          return i;
        }
      }
  }

  // Read digital inputs for Chip 4 (MCP23017)
  for (int i = 48; i <= 63; i++) {
      int hallState = mcp4.digitalRead(i);
      if (hallState == LOW) {
        if(getSquareByNum(i)->getPiece() != NONE){
          return i;
        }
      }
  }
  return -1;
}


