#ifndef CHESS_H
#define CHESS_H

enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
enum Color { WHITE, BLACK, NONE };

// for loop to instantiate the sensors
// Each chip contains 16 pins

class Square {
    Piece piece;
    Color color;
    int num;
    int x, y;

public:
    void setSpace(Square*);
    void setEmpty();
    void setPieceAndColor(Piece, Color, int squareNum);
    Piece getPiece();
    Color getColor();
    void setX(int ex) { x = ex; }
    void setY(int why) { y = why; }
    int getX() { return x; }
    int getY() { return y; }
    int getNum() {return num;}
    Square();
};

class Board {
    Square square[8][8];
    Color turn=WHITE;
    const int ROW = 8;
    const int COL = 8;

    const int LED_BOARD[8][8] = {
      { 0,  1,  2,  3,  4,  5,  6,  7},
      {15, 14, 13, 12, 11, 10,  9,  8},
      {16, 17, 18, 19, 20, 21, 22, 23},
      {31, 30, 29, 28, 27, 26, 25, 24},
      {32, 33, 34, 35, 36, 37, 38, 39},
      {47, 46, 45, 44, 43, 42, 41, 40},
      {48, 49, 50, 51, 52, 53, 54, 55},
      {63, 62, 61, 60, 59, 58, 57, 56}
    };

    bool moveKing(Square* thisKing, Square* thatSpace);
    bool moveQueen(Square* thisQueen, Square* thatSpace);
    bool moveBishop(Square* thisBishop, Square* thatSpace);
    bool moveKnight(Square* thisKnight, Square* thatSpace);
    bool moveRook(Square* thisRook, Square* thatSpace);
    bool movePawn(Square* thisPawn, Square* thatSpace);

    bool makeMove(int x1, int y1, int x2, int y2);

public:
    Square* getSquare(int x, int y) {
        return &square[x][y];
    }
    Square* getSquareByNum(int num){
        for (int i = 0; i < 8; i++){
          for (int j = 0; j < 8; j++){
            if(num == square[i][j].getNum()){
              return &square[i][j];
            }
          }
        }
    }
    void setSquare(Square * s, int x, int y) {
        square[x][y] = *s;
    }
    bool doMove();
    void setBoard();
    bool playGame();
    int checkBoard();

    void kingMoves(int x, int y);
    void queenMoves(int x, int y);
    void bishopMoves(int x, int y);
    void knightMoves(int x, int y);
    void rookMoves(int x, int y);
    void pawnMoves(int x, int y, int enemy);
};

#endif
