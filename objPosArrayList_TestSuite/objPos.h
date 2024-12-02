#ifndef OBJPOS_H
#define OBJPOS_H

// Not really a C++ thing
typedef struct 
{
    int x;
    int y;
} Pos;

class objPos
{
    public:
        Pos* pos;        
        char symbol;

        objPos();
        objPos(int xPos, int yPos, char sym);
        
        // Rule of Six
        objPos(const objPos& other); // Copy Constructor
        objPos& operator=(const objPos& other); // Copy Assignment Operator
        ~objPos(); // Destructor
        objPos(objPos&& other) noexcept; // Move Constructor 
        objPos& operator=(objPos&& other) noexcept; // Move Assignment Operator

        // Methods
        void setObjPos(const objPos& o);        
        void setObjPos(int xPos, int yPos, char sym);  
        void setPosition(int x, int y);
        void setSymbol(char sym);
        int getX() const; // Getter for x-coordinate
        int getY() const; // Getter for y-coordinate
        char getSymbol() const; // Getter for symbol

        bool isPosEqual(const objPos* refPos) const;
        char getSymbolIfPosEqual(const objPos* refPos) const;
};

#endif
