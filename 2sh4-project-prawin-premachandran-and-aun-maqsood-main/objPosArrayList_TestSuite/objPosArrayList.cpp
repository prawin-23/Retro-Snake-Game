#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[arrayCapacity];
    sizeList = 0;
    sizeArray = arrayCapacity;





}

objPosArrayList::~objPosArrayList()
{
     delete[] aList;

}

int objPosArrayList::getSize()
{
        return sizeList;



}

void objPosArrayList::insertHead(objPos thisPos)
{
    for (int i = sizeList; i >0; i--){
        aList[i] = aList[i -1];
    }
    aList[0] = thisPos;
    aList[0].symbol = thisPos.symbol;

    sizeList++;

}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (sizeList == sizeArray){
        return;
    }
    aList[sizeList] = thisPos;
    aList[sizeList].symbol = thisPos.symbol;

    sizeList++;


}

void objPosArrayList::removeHead()
{
    if (sizeList == 0){
        return;
    }
    for (int i = 0; i < sizeList -1; i++){
        aList[i] = aList[i+1];
    }
    sizeList--;
}

void objPosArrayList::removeTail()
{
     if (sizeList == 0){
        return;
    }
    sizeList--;

}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if (sizeList == 0){
        return;
    }
    returnPos = aList[0];
    


}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if (sizeList == 0){
        return;
    }
    returnPos = aList[sizeList -1];

}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
     if(sizeList == 0 || index < 0 || index >= sizeList)
    {
        return;
    }
    returnPos = aList[index];



}