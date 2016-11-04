#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>




int main(void) { 

    WINDOW *w;
    char list[4][14] = { "New Game", "Load Game", "Player Stats", "Quit"};
    char item[7];
    int ch, i = 0; 
    int width = 10;
    int height = 3;
    int startx,starty; 
    struct winsize max; 
    ioctl(0,TIOCGWINSZ, &max);
    starty = max.ws_row / 2;
    startx = max.ws_col / 2;
    initscr(); 
    w = newwin(10,15,starty,startx); 
    box(w,'+','='); 
    
    for(i=0;i<4;i++) { 
       if(i ==0)
          wattron(w, A_STANDOUT); 
       else
          wattroff(w, A_STANDOUT); 
       sprintf(item, "%-12s", list[i]); 
       mvwprintw(w, i+2, 2, "%s", item); 
    }

    wrefresh(w); 

    i = 0; 
    noecho(); 
    keypad(w, TRUE); 
    curs_set(0); 
    while((ch = wgetch(w)) != 'q') { 
       sprintf(item, "%-12s", list[i]); 
       mvwprintw(w, i+2, 2, "%s", item); 
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
        sprintf(item, "%-12s", list[i]); 
        mvwprintw(w, i+2, 2, "%s", item);
        wattroff(w, A_STANDOUT); 
}
        delwin(w);
        endwin();
        char* thi = getenv("HOME"); 
        printf("%s\n",thi);  
}

