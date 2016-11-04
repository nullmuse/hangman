#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>


void main_menu(void) { 
    char manglyph[3][5] = {"  0"," /|\\"," / \\"}; 
    WINDOW *w;
    char list[4][14] = { "New Game", "Load Game", "Player Stats", "Quit"};
    char item[13];
    int ch, i = 0; 
    int width = 15;
    int height = 10;
    int startx,starty; 
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLUE);
    init_pair(2,COLOR_BLUE,COLOR_WHITE);
    init_pair(3,COLOR_RED,COLOR_WHITE);
    struct winsize max; 
    ioctl(0,TIOCGWINSZ, &max);
    starty = max.ws_row / 2;
    startx = max.ws_col / 2;
    w = newwin(height,width,starty,startx);
    wattron(w, COLOR_PAIR(1));
    box(w,'+','='); 
    wattron(w, COLOR_PAIR(1));
    for(i=0;i<4;i++) { 
          wattroff(w, A_STANDOUT);
           wattron(w, COLOR_PAIR(1)); 
          sprintf(item, " %-12s", list[i]);
          mvwprintw(w, i+1, 1, "%s", item);
          }
     sprintf(item, " %-12s", " ");
     mvwprintw(w, i+1, 1, "%s", item); 
     for(i=0;i<=4;i++) {
          wattroff(w, A_STANDOUT); 
           wattron(w, COLOR_PAIR(1));
       sprintf(item, "   %-8s  ", manglyph[i]); 
       mvwprintw(w, i+6, 1, "%s", item);    
    }

     
    i = 0;
    wattron(w, COLOR_PAIR(3));
    wattron(w, A_STANDOUT);
    sprintf(item, " %-12s", list[i]);
    mvwprintw(w, i+1, 1, "%s", item);
    wattron(w, COLOR_PAIR(1));
    wattroff(w, A_STANDOUT); 
    //wrefresh(w);
    noecho(); 
    keypad(w, TRUE); 
    curs_set(0); 
    while(ch != 'q') {
       ch = wgetch(w); 
       sprintf(item, " %-12s", list[i]); 
       mvwprintw(w, i+1, 1, "%s", item); 
       switch(ch) { 
           case KEY_UP:
               i--;
               i = (i <0) ? 3: i; 
               break;
           case KEY_DOWN:
               i++;
               i = (i > 3) ? 0: i; 
               break; 
            case 10:
               if(i == 3)
                  ch = 'q';
                  break;

        }
        wattron(w, A_STANDOUT); 
         wattron(w, COLOR_PAIR(3));
        sprintf(item, " %-12s", list[i]); 
        mvwprintw(w, i+1, 1, "%s", item);
        
         wattron(w, COLOR_PAIR(3));
         wattroff(w, A_STANDOUT); 
        wattron(w, COLOR_PAIR(1));
	
}
        delwin(w);
        char* thi = getenv("HOME"); 
        printf("%s\n",thi);  
}




int main(void) { 

initscr(); 

main_menu(); 
endwin(); 

}
