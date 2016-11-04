#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <time.h>
#include "word_mongler.h"
#include <unistd.h>
int gloc = 1;
int gnoose = 0; 
char *gterm[5] = {NULL, NULL, NULL, NULL, NULL};  
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


int draw_word(WINDOW *w,int loc, char *wurd, int store) { 
   wattroff(w, COLOR_PAIR(1));
   if(store) {
   char *bufitem = malloc(strlen(wurd) + 1);
   strncpy(bufitem,wurd,strlen(wurd) + 1); 
   if(gterm[loc - 1] != NULL) { 
    free(gterm[loc - 1]);  
   } 
   gterm[loc - 1] = bufitem; 
  }
   mvwprintw(w, loc, 3, "%s", wurd);
   wattron(w, COLOR_PAIR(1));
   return loc + 1; 
}

int terminal_scroll(WINDOW *w) { 
int i,k,l; 
char *space = "                            ";
char *tmp = malloc(20); 
char *cont;
//wmove(w,1,1); 
//free(gterm[0]); 
for(i = 0; i < 4; i++) { 
gterm[i - 1] = gterm[i]; 
}
memset(tmp,0,20); 
for(k=1;k < 5;k++) {  
//wmove(w,k,1);
draw_word(w,k,space,0);
}
//wmove(w,
for(k = 1; k < 5; k++) {
draw_word(w,k,gterm[k - 1],0);
} 
free(tmp);
wrefresh(w); 
return 0;  
     
}

int terminal_handler(WINDOW *w, char *wurd) { 
   if (gloc  == 5) { 
    terminal_scroll(w); 
    draw_word(w,gloc,wurd,1);  
    wrefresh(w);
    return gloc; 
   } 
   draw_word(w,gloc,wurd,1); 
   gloc++;
   wrefresh(w);
   return gloc; 
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




while(menuret != 3)  {
initscr(); 
menuret = main_menu(); 
switch(menuret) { 

case 0: 
   clear(); 
   refresh();  
   menuret = game_menu(); 
   break; 

case 2:
   clear();
   refresh();  
   read_stats();
   sleep(3);
   endwin();
   return; 
   
case 3:
   endwin();
   return; 
}
clear();   
refresh();
endwin(); 
}
}

int game_menu(void) {
    WINDOW *w,*w2;
    char *item = malloc(2);
    item[1] = 0; 
    int ch, i = 0;
    char *win = "You win!"; 
    char *lose = "You lose punk."; 
    char *testwurd = word_mongler(); 
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
    mvwprintw(w2, 6, 3, "%s", testwurd);
    wrefresh(w2);  
    sleep(2);
    delwin(w); 
    delwin(w2);
    refresh();
    free(testwurd);
    free(checkstring); 
    return 1; 
    }
    if(!strcmp(testwurd,checkstring)) { 
    terminal_handler(w2,win);
    sleep(2);
    delwin(w);
    delwin(w2);
    refresh();
    free(testwurd);
    free(checkstring);
    return 1;

    }


}
}
