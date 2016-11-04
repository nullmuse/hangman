#include <ncurses.h>

int main(void) { 

    WINDOW *w;
    char list[4][14] = { "New Game", "Load Game", "Player Stats", "Quit"};
    char item[7];
    int ch, i = 0; 
    int width = 10;
    int height = 3;
    int starty = (LINES ); 
    int startx = (COLS);
    initscr(); 
    w = newwin(10, 15,30,50); 
    box(w,starty,startx); 
    
    for(i=0;i<4;i++) { 
       if(i ==0)
          wattron(w, A_STANDOUT); 
       else
          wattroff(w, A_STANDOUT); 
       sprintf(item, "%-15s", list[i]); 
       mvwprintw(w, i+1, 2, "%s", item); 
    }

    wrefresh(w); 

    i = 0; 
    noecho(); 
    keypad(w, TRUE); 
    curs_set(0); 
    while((ch = wgetch(w)) != 'q') { 
       sprintf(item, "%-15s", list[i]); 
       mvwprintw(w, i+1, 2, "%s", item); 
       switch(ch) { 
           case KEY_UP:
               i--;
               i = (i <0) ? 3: i; 
               break;
           case KEY_DOWN:
               i++;
               i = (i > 3) ? 0: i; 
               break; 

        }
        wattron(w, A_STANDOUT); 
        sprintf(item, "%-15s", list[i]); 
        mvwprintw(w, i+1, 2, "%s", item);
        wattroff(w, A_STANDOUT); 
}
        delwin(w);
        endwin();
        printf("%i %i\n",starty, startx); 
}

