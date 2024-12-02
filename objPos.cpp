#include "objPos.h"

// Default constructor
objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; // NULL character
}

// Parameterized constructor
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Copy constructor
objPos::objPos(const objPos& other)
{
    pos = new Pos; // Allocate memory for pos
    pos->x = other.pos->x;
    pos->y = other.pos->y;
    symbol = other.symbol; // Copy symbol
}

// Copy assignment operator
objPos& objPos::operator=(const objPos& other)
{
    if (this != &other) { // Self-assignment check
        *pos = *(other.pos); // Copy contents of Pos
        symbol = other.symbol; 
    }
    return *this;
}

// Move constructor
objPos::objPos(objPos&& other) noexcept
    : pos(other.pos), symbol(other.symbol)
{
    other.pos = nullptr; // Transfer ownership
}

// Move assignment operator
objPos& objPos::operator=(objPos&& other) noexcept
{
    if (this != &other) { // Self-assignment check
        delete pos; // Free current resources
        pos = other.pos;
        symbol = other.symbol;

        other.pos = nullptr; // Nullify source
    }
    return *this;
}

// Destructor
objPos::~objPos()
{
    delete pos; // Deallocate memory for pos
}

// Set position and symbol using another objPos
void objPos::setObjPos(const objPos& o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}


// Setter methods
void objPos::setPosition(int x, int y) {
    pos->x = x;
    pos->y = y;
}

void objPos::setSymbol(char sym) {
    symbol = sym;
}


// Set position and symbol directly
void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Get the x-coordinate
int objPos::getX() const
{
    return pos->x;
}

// Get the y-coordinate
int objPos::getY() const
{
    return pos->y;
}

// Get symbol
char objPos::getSymbol() const
{
    return symbol;
}

// Check if positions are equal
bool objPos::isPosEqual(const objPos* refPos) const
{
    if (refPos == nullptr) return false; // Null safety check
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

// Get symbol if positions are equal
char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    return isPosEqual(refPos) ? symbol : 0;
}


