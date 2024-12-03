
#include "objPosArrayList.h"
#include <iostream> // Add this for std::cerr and std::endl
#include <stdexcept> // For exception handling
objPosArrayList::objPosArrayList()
    : aList(new objPos[ARRAY_MAX_CAP]), listSize(0), arrayCapacity(ARRAY_MAX_CAP)
{
    // Ensure all elements are initialized to default objPos
    for (int i = 0; i < arrayCapacity; i++)
    {
        aList[i] = objPos(); // Default constructor 
    }
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; // Free dynamically allocated memory
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize >= arrayCapacity)
        throw std::overflow_error("List is at maximum capacity.");

    // Shift elements right to make room at the head
    for (int i = listSize; i > 0; --i)
    {
        aList[i] = aList[i - 1];
    }

    aList[0] = thisPos; // Insert at the head
    ++listSize;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize >= arrayCapacity)
        throw std::overflow_error("List is at maximum capacity.");

    aList[listSize] = thisPos; // Insert at the tail
    ++listSize;
}

void objPosArrayList::removeHead()
{
    if (listSize == 0)
        throw std::underflow_error("List is empty, cannot remove head.");

    // Shift elements left to remove the head
    for (int i = 0; i < listSize - 1; ++i)
    {
        aList[i] = aList[i + 1];
    }

    aList[listSize - 1] = objPos(); // Reset the last element to default
    --listSize;
}

void objPosArrayList::removeTail()
{
    if (listSize == 0)
        throw std::underflow_error("List is empty, cannot remove tail.");

    aList[listSize - 1] = objPos(); // Reset the last element to default
    --listSize;
}

objPos objPosArrayList::getHeadElement() const
{
    if (listSize == 0)
        throw std::underflow_error("List is empty, cannot get head element.");

    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    if (listSize == 0)
        throw std::underflow_error("List is empty, cannot get tail element.");

    return aList[listSize - 1];
}

objPos& objPosArrayList::getElement(int index) const {
    return aList[index];  // Return the element by reference
}
