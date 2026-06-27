#include <chrono>
#include <ncurses.h>
#include <thread>

int main(int argc, char **argv) {
  initscr();
  refresh();
  // Define base time point
  auto next_tick = std::chrono::steady_clock::now();
  for (int i = 10; i >= 1; i--) {
    next_tick += std::chrono::seconds(1);
    clear();
    printw("%d seconds left\n", i);
    refresh();
    std::this_thread::sleep_until(next_tick);
  }
  next_tick += std::chrono::seconds(2);
  clear();
  printw("Surprise!!!! 10 seconds just passed. \n");
  refresh();
  std::this_thread::sleep_until(next_tick);
  endwin();
}
