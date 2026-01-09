#include "four_in_a_raw.h"
#include "../../components/joystick/joystick.h"

four_in_a_raw::four_in_a_raw() : game() {
}

four_in_a_raw::~four_in_a_raw() {
}

void four_in_a_raw::moveRight() {
    for (int i = 0; i < 7; i++) {
        if (board[6][i] == player) {
            if (i < 6) { // Ensure we don't go out of bounds
                board[6][i] = 0; // Clear current position
                board[6][i + 1] = player; // Move right
            }
            break; // Exit loop after moving
        }
    }
}

void four_in_a_raw::moveLeft() {
    for (int i = 0; i < 7; i++) {
        if (board[6][i] == player) {
            if (i > 0) { // Ensure we don't go out of bounds
                board[6][i] = 0; // Clear current position
                board[6][i - 1] = player; // Move left
            }
            break; // Exit loop after moving
        }
    }
}

void four_in_a_raw::showBoard() {
    Serial.println("");
    Serial.println("");
    Serial.println("");
    for (int i = 6; i >=0; i--) {
        for (int j = 0; j < 7; j++) {
            Serial.print(board[i][j]);
            Serial.print(" ");
        }
        Serial.println();
    }
}

void four_in_a_raw::init(void) {
    end = false;
    joystick_four_in_a_raw.init();
    Serial.println("Initializing Four In A Row game...");
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            board[i][j] = 0; // 0 indicates empty cell
        }
    }
    board[6][3] = 1; // placement cursor for player 1
    this->player = 1; // Start with player 1
    Serial.println("Game initialized.");
    this->showBoard();
}

void four_in_a_raw::endGame() {
    this->showBoard();
    Serial.print("Player ");
    Serial.print(player);
    Serial.println(" wins!");
    end=true;
    delay(1000);
    Serial.println("Game Over. To restart the game press the button.");
    int restart=0;
    while(restart==0){
        if (joystick_four_in_a_raw.isButtonPressed()){
            restart=1;
            this->init();
        }
    }
    delay(1000);
}

void four_in_a_raw::run(void) {
    if (end) {
        return;
    }
    bool change = false;
    int position = 0;
    int last_piece_row = -1;
    int last_piece_col = -1;
    if (joystick_four_in_a_raw.isButtonPressed()) {
        change = true;
        // Placeholder for drop logic: find placement cursor for current player
        for (int j = 0; j < 7; j++) {
            if (board[6][j] == player) {
                position = j;
                break;
            }
        }
        // If the top playable cell (row 5) is occupied the column is full — ignore button press.
        if (board[5][position] != 0) {
            return; // exit run(); 'continue' can't be used here outside a loop
        }

        // Drop the piece to the lowest empty cell in the column (rows 0..5)
        for (int r = 0; r <= 5; r++) {
            if (board[r][position] == 0) {
                board[r][position] = player;
                last_piece_row = r;
                last_piece_col = position;
                break;
            }
        }

        // Clear placement cursor at bottom row (row 6)
        board[6][position] = 0;
        
        // Check for win condition
        //vertical
        int count = 0;
        for (int r = 0; r < 6; r++) {
            if (board[r][last_piece_col] == player) {
                count++;
            }else {
                count = 0;
            }
            if (count == 4) {
                this->endGame();
                return;
            }
        } 
        //horizontal
        count = 0;
        for (int c = 0; c < 7; c++) {
            if (board[last_piece_row][c] == player) {
                count++;
            }else {
                count = 0;
            }
            if (count == 4) {
                this->endGame();
                return;
            }
        }

        //diagonale bas_gauche_haut_droite
        count = 0;
        int start_row = last_piece_row;
        int start_col = last_piece_col;
        while (start_row < 5 && start_col > 0) {
            start_row++;
            start_col--;
        }
        while (start_row >= 0 && start_col < 7) {
            if (board[start_row][start_col] == player) {
                count++;
            } else {
                count = 0;
            }
            if (count == 4) {
                this->endGame();
                return;
            }
            start_row--;
            start_col++;
        }

        //diagonale haut_gauche_bas_droite
        count = 0;
        start_row = last_piece_row;
        start_col = last_piece_col;
        while (start_row > 0 && start_col > 0) {
            start_row--;
            start_col--;
        }
        while (start_row < 7 && start_col < 7) {
            if (board[start_row][start_col] == player) {
                count++;
            } else {
                count = 0;
            }
            if (count == 4) {
                this->endGame();
                return;
            }
            start_row++;
            start_col++;
        }
        


        // Switch player
        if (player == 1) {
            player = 2;
        } else {
            player = 1;
        }

        // Set placement cursor for the next player at the bottom row
        board[6][position] = player;
        delay(300); // Debounce delay for button press
        change = true;
    }
    if (joystick_four_in_a_raw.readInputX() > 100) {
        moveRight();
        change = true;
    }
    if(joystick_four_in_a_raw.readInputX() < -100) {
        moveLeft();
        change = true;
    }
    if (change) {
        showBoard();
    }
    delay(200);
}
