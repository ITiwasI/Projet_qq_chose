#include <Arduino.h>
#include "row.hpp"

Row::Row()
{
    dim = 7;
    elements = new char[dim];
    for (int i=0; i<dim; i++) 
    {
        elements[i] = '-';
    }
}

Row::~Row()
{
    delete[] elements;
}

void Row::DisplayRow()
{
    for (int i=0; i<dim; i++)
    {
        Serial.print(elements[i]);
        Serial.print(" ");
    }
    Serial.println(" ");
}

