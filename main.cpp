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
    if (x == 0)
      val.push_back(0);
    else {
      while (x > 0) {
        val.push_back(x % 10);
        x /= 10;
      }
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
    px += 3;
  }
};

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  initscr();
  curs_set(0);
  refresh();
  // Define base time point
  auto next_tick = std::chrono::steady_clock::now();
  int height, width, start_y, start_x;
  height = 100;
  width = 200;
  start_x = 5;
  start_y = 2;

  WINDOW *win = newwin(height, width, start_y, start_x);
  for (int i = 10; i >= 1; i--) {
    next_tick += std::chrono::seconds(1);
    wclear(win);
    IntLargeRep I1(win, start_y, start_x);
    I1.int_printer(i);
    wrefresh(win);
    std::this_thread::sleep_until(next_tick);
  }
  next_tick += std::chrono::seconds(2);
  wclear(win);
  wrefresh(win);
  printw("Surprise!!!! 10 seconds just passed. \n");
  refresh();
  std::this_thread::sleep_until(next_tick);
  endwin();
}
