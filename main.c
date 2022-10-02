#include <stdlib.h>
#include <ncurses.h>
#include "fun.h"
#include "fun.c"

#define DIM 3

int main (void){
    int c;
    int mossa;
    int fine = 0;
    WINDOW * new_win;
    
    int **table = random_game3(DIM); //crea una matrice di dimensione variabile
    
    initscr(); // screen initialisation functions initialises all implementation data structures
    raw();
    cbreak(); //disable line buffering, characters typed by the user are immediately available to the application
    
    
    new_win = newwin(10,50,7,10); //creates and returns a pointer to a new window
    keypad(new_win, TRUE); //It enables the reading of function keys like F1, F2, arrow keys etc.
    
    wprintw(new_win,"\n BENVENUTO NEL GIOCO DEL' 8\n\n"); 
    stampa(table,DIM,new_win); //print the game
    search_zero(table,DIM); //found zero position
    
    //finchè fine è uguale a zero il gioco non è finito quindi cicla
    while(!fine){
        
        mvwprintw(new_win,7,1,"USA LE FRECCE PER SPOSTARE I NUMERI!!");
        
        //crea un box
        box(new_win,0,0);
        //cerca la posizione della casella vuota
        
        //wgetch cattura il carattere ascii e restituisce il suo valore intero
        mossa = wgetch(new_win);
        
        if(valida(table,mossa,DIM)){
            
            wclear(new_win); //clear the window
            muovi(table,mossa);//moves number
            wprintw(new_win,"\n\n\n");
            stampa(table,DIM,new_win);
            wrefresh(new_win);
            
            //check if the game is complete
            fine = risolto2(table,DIM);
        }
        else{
            
            //wclear(new_win);
            mvwprintw(new_win, 1, 1,"La mossa inserita non è valida\n\n");
            
            stampa(table,3,new_win);
            wrefresh(new_win); // non ho capito bene a che serve refresh
        }
    }
    
    box(new_win,0,0);
    mvwprintw(new_win,7,1," Complimenti Hai completato il gioco");
    wgetch(new_win);
    endwin();
    return 0;
}

//provaprova