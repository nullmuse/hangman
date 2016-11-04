#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <time.h>

int gloc = 0;
int gnoose = 0; 

int draw_part(WINDOW *w, int part, int loc) { 
int i,min; 
wattroff(w, COLOR_PAIR(1));

switch (part) { 
 

	case 0:
          mvwprintw(w, 2, 12, "%s", "-----");
          mvwprintw(w, 3, 12, "%s", "|O o|");
          mvwprintw(w, 4, 12, "%s", "| ~ |");
          mvwprintw(w, 5, 12, "%s", "-----");
          i = 4;
          break; 

        case 1:
         for(i=1;i<8;i++) { 
            mvwprintw(w, i + loc, 14, "%s", "|"); 
         }
         break; 

        case 2:
           min = 1;
           for(i=1;i<6;i++) {
            mvwprintw(w, i + loc, 14 - min++, "%s", "/");
         }
         break;
        
        case 3:
            min = 1;
           for(i=1;i<6;i++) {
            mvwprintw(w, i + loc, 14 + min++, "%s", "\\");
         }
         break;

} 

     wrefresh(w);
      wattron(w, COLOR_PAIR(1));

      return i + 1;

}


int draw_word(WINDOW *w,int loc, char *wurd) { 
   wattroff(w, COLOR_PAIR(1));
   mvwprintw(w, loc + 1, 10, "%s", wurd);
   wrefresh(w); 
   wattron(w, COLOR_PAIR(1));
   return loc + 1; 
}

int terminal_scroll(WINDOW *w) { 
int i,k; 
char *tmp = malloc(30); 
memset(tmp,0,30); 
for(k=1;k < 5;k++) {  
if(k > 1) {
for(i = 1; i > 30; i++) {  
wmove(w,k,i);
tmp[i] = wgetch(w);
}
draw_word(w,k - 1,tmp); 
memset(tmp,0,30); 
}
for(i = 1; i > 30; i++) {
wmove(w,k,i);
wdelch(w);
}
} 
free(tmp);
wrefresh(w); 
return 0;  
     
}

int terminal_handler(WINDOW *w, char *wurd) { 
   int retloc = draw_word(w,gloc,wurd); 
   if(retloc > 5) {
   terminal_scroll(w); 
   return retloc - 1; 
   } 
   gloc++;
   return retloc; 
}


int guess_compare(WINDOW *w, char *guess, char *wurd, char *testwurd) { 
     int i,in = 0; 
     int wlen = strlen(wurd);   
     for(i = 0; i < wlen; ++i) { 
        if(guess[0] == wurd[i]) { 
           in++;
           testwurd[i] = wurd[i]; 
        }
      }
     terminal_handler(w,testwurd); 
     return in; 
}






int main_menu(void) { 
    char manglyph[3][5] = {"  0"," /|\\"," / \\"}; 
    WINDOW *w;
    char list[4][13] = { "New Game","Load Game", "Stats", "Quit"};
    char *item = malloc(14); 
    int ch, i = 0; 
    int retval = 0; 
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
          snprintf(item, 14," %-13s", list[i]);
          mvwprintw(w, i+1, 1, "%s", item);
          memset(item,0,13); 
          }

 
     snprintf(item, 14," %-13s", "            ");
     mvwprintw(w, i+1, 1, "%s", item); 
     for(i=0;i<3;++i) {
          wattroff(w, A_STANDOUT); 
           wattron(w, COLOR_PAIR(1));
       snprintf(item,14, "   %-13s", manglyph[i]); 
       mvwprintw(w, i+6, 1, "%s", item);    
       memset(item,0,13); 
    }
      //snprintf(item, 14," %-13s", "            ");
      //mvwprintw(w, i+5, 1, "%s", item);
   
    i = 0;
    memset(item,0,13); 
    wattron(w, COLOR_PAIR(3));
    wattron(w, A_STANDOUT);
    snprintf(item,14," %-13s", list[i]);
    mvwprintw(w, i+1, 1, "%s", item);
    wattron(w, COLOR_PAIR(1));
    wattroff(w, A_STANDOUT); 
    wrefresh(w);
    noecho(); 
    keypad(w, TRUE); 
    curs_set(0); 
    while(ch != 'q') {
       ch = wgetch(w); 
       snprintf(item,14," %-13s", list[i]); 
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
                  retval = i; 
                  ch = 'q';
                  break;
                
               
        }
        wattron(w, A_STANDOUT); 
         wattron(w, COLOR_PAIR(3));
        snprintf(item,13," %-12s", list[i]); 
        mvwprintw(w, i+1, 1, "%s", item);
        
         wattron(w, COLOR_PAIR(3));
         wattroff(w, A_STANDOUT); 
        wattron(w, COLOR_PAIR(1));
	
}
        delwin(w);
        refresh(); 
        return retval; 
}





int main(void) { 

int menuret = 0; 

initscr(); 

menuret = main_menu(); 

switch(menuret) { 

case 0:
   menuret = game_menu(); 
   break; 
case 3:
   endwin(); 
   break;
}
if(menuret == 1)
endwin(); 

}
int game_menu(void) {
    char manglyphs[6][5] = {"0"," /","|","\\","/","\\"};
    WINDOW *w,*w2;
    char list[4][13] = { "New Game", "Load Game", "Stats", "Quit"};
    char *item = malloc(2);
    item[1] = 0; 
    int ch, i = 0;
    char *win = "You win!"; 
    char *lose = "You lose punk."; 
    char *testwurd = "testwurd"; 
    int retval = 0;
    char *checkstring = malloc(strlen(testwurd) + 1); 
    memset(checkstring,0,strlen(testwurd) + 1); 
    memset(checkstring,'_',strlen(testwurd));
    int width = 30;
    int curspos = 0;
    int height = 30;
    int width2 = 70;
    int height2 = 10;
    int startx1,starty1,startx2,starty2;
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLUE);
    init_pair(2,COLOR_BLUE,COLOR_WHITE);
    init_pair(3,COLOR_RED,COLOR_WHITE);
    int loc,loc2; 
    struct winsize max;
    ioctl(0,TIOCGWINSZ, &max);
    starty1 = max.ws_row / 5;
    startx1 = max.ws_col / 4;
    starty2 = max.ws_row - 10; 
    startx2 = max.ws_col / 4;
    w = newwin(height,width,starty1,startx1);
    w2 = newwin(height2,width2,starty2,startx2);
    wattron(w, COLOR_PAIR(1));
    box(w,'+','=');
    wattron(w2, COLOR_PAIR(1));
    box(w2,'+','='); 
    wrefresh(w); 
    wrefresh(w2);
    sleep(1);
    while(ch != '<') {
       ch = wgetch(w);
       item[0] = ch; 
    if(!guess_compare(w2, item, testwurd, checkstring)) { 
       if(gnoose == 0)
        loc = draw_part(w,gnoose++,0);
       else if(gnoose == 1)
        loc2 = draw_part(w,gnoose++,loc); 
       else if(gnoose < 4)
        draw_part(w,gnoose++,loc); 
       else
        draw_part(w,(gnoose++) - 2,loc2 + 3); 
       } 
    
    wrefresh(w);
    if(gnoose >= 6) { 
    terminal_handler(w2,lose); 
    sleep(2);
    delwin(w); 
    delwin(w2); 
    return 1; 
    }
    if(!strcmp(testwurd,checkstring)) { 
    terminal_handler(w2,win);
    sleep(2);
    delwin(w);
    delwin(w2);
    return 1;
    }

}
}
    /* wattron(w, COLOR_PAIR(1));
    for(i=0;i<4;i++) {
          wattroff(w, A_STANDOUT);
           wattron(w, COLOR_PAIR(1));
          snprintf(item, 14," %-13s", list[i]);
          mvwprintw(w, i+1, 1, "%s", item);
          memset(item,0,13);
          }

     snprintf(item, 14," %-13s", "            ");
     mvwprintw(w, i+1, 1, "%s", item);
     for(i=0;i<3;++i) {
          wattroff(w, A_STANDOUT);
           wattron(w, COLOR_PAIR(1));
       snprintf(item,14, "   %-13s", manglyph[i]);
       mvwprintw(w, i+6, 1, "%s", item);
       memset(item,0,13);
    }
      //snprintf(item, 14," %-13s", "            ");
      //mvwprintw(w, i+5, 1, "%s", item);

    i = 0;
    memset(item,0,13);
    wattron(w, COLOR_PAIR(3));
    wattron(w, A_STANDOUT);
    snprintf(item,14," %-13s", list[i]);
    mvwprintw(w, i+1, 1, "%s", item);
    wattron(w, COLOR_PAIR(1));
    wattroff(w, A_STANDOUT);
    wrefresh(w);
    noecho();
    keypad(w, TRUE);
    curs_set(0);
    
    while(ch != 'q') {
       ch = wgetch(w);
       snprintf(item,14," %-13s", list[i]);

      }
        wattron(w, A_STANDOUT);
         wattron(w, COLOR_PAIR(3));
        snprintf(item,13," %-12s", list[i]);
        mvwprintw(w, i+1, 1, "%s", item);

         wattron(w, COLOR_PAIR(3));
         wattroff(w, A_STANDOUT);
        wattron(w, COLOR_PAIR(1));

}
        delwin(w);
        char* thi = getenv("HOME");
        printf("%s\n",thi);
        return retval;
}

*/
