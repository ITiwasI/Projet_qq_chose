#include <Arduino.h>

#include "grid.hpp"
#include "row.hpp"

Grid::Grid()
{
    grid = new Row*[6];
    for (int i=0; i<6; i++)
    {
        grid[i] = new Row();
    }
}

Grid::~Grid()
{
    for (int i=0; i<6; i++)
    {
        delete grid[i];
    }
    delete[] grid;
}

void Grid::DisplayGrid()
{
    Serial.println(" ");
    Serial.println("Voici la grille de jeu :");
    for (int i=0; i<6; i++) 
    {
        for (int j=0; j<7; j++)
        {
            Serial.print(grid[i]->elements[j]);
            Serial.print(" ");
        }
        Serial.println(" ");
    }
}

void Grid::AddPiece(char Player, int C) 
{
    for (int i=5; i>=0; i--)
    {
        if (grid[i]->elements[C] == '-')
        {
            switch (Player)
            {
                case 'A':
                    grid[i]->elements[C] = 'X';
                    break;
                case 'B':
                    grid[i]->elements[C] = 'O';
                    break;
            }
            return;
        }
    }
    Serial.println(" ");
    Serial.println("Colonne deja remplie !");
}


bool Grid::isGridFull()
{
    bool Full = true;
    for (int i=0; i<6; i++) 
    {
        for (int j=0; j<7; j++)
        {
            if ((grid[i]->elements[j]) == '-')
            {
                Full = false;
            }
        }
    }
    return Full;
}


char Grid::isWinner() // retourne X si A gagne, O si B gagne, / si pas de gagnant
{
    for (int i=0; i<6; i++) // on parcourt sur les lignes
    {
        for (int j=0; j<7; j++) // on parcourt sur les colonnes
        {
            char CurrentPiece = (grid[i] -> elements[j]);
            
            if (CurrentPiece == '-')
            {
                continue;
            }

            if (j+3 < 7) // Verifications horizontales
            {
                if ((CurrentPiece == (grid[i] -> elements[j+1])) && (CurrentPiece == (grid[i] -> elements[j+2])) && (CurrentPiece == (grid[i] -> elements[j+3])))
                {
                    return CurrentPiece;
                }
            }
            
            if (i+3 < 6) // Verifications verticales
            {
                if ((CurrentPiece == (grid[i+1] -> elements[j])) && (CurrentPiece == (grid[i+2] -> elements[j])) && (CurrentPiece == (grid[i+3] -> elements[j])))
                {
                    return CurrentPiece;
                }
            }

            if ((i+3 < 6) && (j+3 < 7)) // Verifications diagonales descentes bas-droite
            {
                if  ((CurrentPiece == (grid[i+1] -> elements[j+1])) && (CurrentPiece == (grid[i+2] -> elements[j+2])) && (CurrentPiece == (grid[i+3] -> elements[j+3])))
                {
                    return CurrentPiece;
                }

            }

            if ((i+3 < 6) && (j-3 >= 0)) // Verifications diagonales montantes bas-gauche
            {
                if  ((CurrentPiece == (grid[i+1] -> elements[j-1])) && (CurrentPiece == (grid[i+2] -> elements[j-2])) && (CurrentPiece == (grid[i+3] -> elements[j-3])))
                {
                    return CurrentPiece;
                }
            }

        }
    }
    return '/';  
}