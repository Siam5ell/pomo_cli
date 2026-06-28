#include <chrono>
#include <ncurses.h>
#include <thread>

class IntLargeRep {
  WINDOW *win;
  int sx, sy;
  int px, py;

  void large_zero() {
    mvwprintw(win, py, px, "██████");
    for (int i = 0; i < 3; i++) {
      mvwprintw(win, py + i + 1, px, "█    █");
    }
    mvwprintw(win, py + 4, px, "██████");
    px += 6;
  }

  void large_one() {
    for (int i = 0; i < 5; i++) {
      mvwprintw(win, py + i, px, "██");
    }
    px += 2;
  }

  void large_two() {
    mvwprintw(win, py + 0, px, "██████");
    mvwprintw(win, py + 1, px, "     █");
    mvwprintw(win, py + 2, px, "██████");
    mvwprintw(win, py + 3, px, "█     ");
    mvwprintw(win, py + 4, px, "██████");
    px += 6;
  }

  void large_three() {
    mvwprintw(win, py + 0, px, "██████");
    mvwprintw(win, py + 1, px, "     █");
    mvwprintw(win, py + 2, px, "██████");
    mvwprintw(win, py + 3, px, "     █");
    mvwprintw(win, py + 4, px, "██████");
    px += 6;
  }

  void large_four() {
    mvwprintw(win, py + 0, px, "█    █");
    mvwprintw(win, py + 1, px, "█    █");
    mvwprintw(win, py + 2, px, "██████");
    mvwprintw(win, py + 3, px, "     █");
    mvwprintw(win, py + 4, px, "     █");
    px += 6;
  }

  void large_five() {
    mvwprintw(win, py + 0, px, "██████");
    mvwprintw(win, py + 1, px, "█     ");
    mvwprintw(win, py + 2, px, "██████");
    mvwprintw(win, py + 3, px, "     █");
    mvwprintw(win, py + 4, px, "██████");
    px += 6;
  }

  void large_six() {
    mvwprintw(win, py + 0, px, "██████");
    mvwprintw(win, py + 1, px, "█     ");
    mvwprintw(win, py + 2, px, "██████");
    mvwprintw(win, py + 3, px, "█    █");
    mvwprintw(win, py + 4, px, "██████");
    px += 6;
  }

  void large_seven() {
    mvwprintw(win, py + 0, px, "█████");
    mvwprintw(win, py + 1, px, "    █");
    mvwprintw(win, py + 2, px, "   █ ");
    mvwprintw(win, py + 3, px, "  █ ");
    mvwprintw(win, py + 4, px, " █ ");
    px += 5;
  }

  void large_eight() {
    mvwprintw(win, py + 0, px, "██████");
    mvwprintw(win, py + 1, px, "█    █");
    mvwprintw(win, py + 2, px, "██████");
    mvwprintw(win, py + 3, px, "█    █");
    mvwprintw(win, py + 4, px, "██████");
    px += 6;
  }

  void large_nine() {
    mvwprintw(win, py + 0, px, "██████");
    mvwprintw(win, py + 1, px, "█    █");
    mvwprintw(win, py + 2, px, "██████");
    mvwprintw(win, py + 3, px, "     █");
    mvwprintw(win, py + 4, px, "██████");
    px += 6;
  }

public:
  IntLargeRep(WINDOW *w1, int sy, int sx)
      : win(w1), py(sy), px(sx), sx(sx), sy(sy) {}
  void int_printer(unsigned int x) {
    std::vector<int> val;
    if (x == 0) {
      val.push_back(0);
      val.push_back(0);
    } else {
      while (x > 0) {
        val.push_back(x % 10);
        x /= 10;
      }
      if (val.size() < 2)
        val.push_back(0);
    }
    for (auto itr = val.rbegin(); itr != val.rend(); itr++) {
      int digit = *itr;
      switch (digit) {
      case 0:
        large_zero();
        break;
      case 1:
        large_one();
        break;
      case 2:
        large_two();
        break;
      case 3:
        large_three();
        break;
      case 4:
        large_four();
        break;
      case 5:
        large_five();
        break;
      case 6:
        large_six();
        break;
      case 7:
        large_seven();
        break;
      case 8:
        large_eight();
        break;
      case 9:
        large_nine();
        break;
      default:
        break;
      }
      wrefresh(win);
      px += 1;
    }
    px += 3;
  }
  std::pair<int, int> nextline() { return {sy + 5, sx}; }
  void colon_printer() {
    mvwprintw(win, py + 1, px, " █ ");
    mvwprintw(win, py + 2, px, "   ");
    mvwprintw(win, py + 3, px, " █ ");
    px += 7;
    wrefresh(win);
  }
};

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  initscr();
  curs_set(0);
  start_color();
  noecho();
  int screen_width, screen_height;
  getmaxyx(stdscr, screen_height, screen_width);
  int window_height, window_width;
  window_height = 20;
  window_width = screen_width / 3;
  WINDOW *application_window =
      newwin(window_height, window_width, 1, 2 * screen_width / 5);
  refresh();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  wattron(application_window, COLOR_PAIR(1));
  mvwprintw(application_window, 0, 0, "Pomodoro Timer");
  wrefresh(application_window);
  wattroff(application_window, COLOR_PAIR(1));
  IntLargeRep timer_rep(application_window, 2, 0);
  timer_rep.int_printer(20);
  timer_rep.colon_printer();
  timer_rep.int_printer(0);
  mvwprintw(application_window, 8, 0, "s:start");
  mvwprintw(application_window, 9, 0, "p:pause");
  mvwprintw(application_window, 10, 0, "f:set focus duration");
  mvwprintw(application_window, 11, 0, "b:set short break duration");
  mvwprintw(application_window, 12, 0, "l:set long break duration");
  mvwprintw(application_window, 13, 0, "q:quit");
  wrefresh(application_window);
  refresh();
  char c = getch();
  while (c != 'q') {
    c = getch();
  }
  endwin();
}
