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
enum AppState {
  TimerRunning,
  TimerPaused,
  EditDurationFocus,
  EditDurationShortBreak,
  EditDurationLongBreak
};

// Duration is in seconds
void print_time(WINDOW *win, int sy, int sx, int duration) {
  IntLargeRep timer_rep(win, sy, sx);
  int min = duration / 60;
  int sec = duration % 60;
  timer_rep.int_printer(min);
  timer_rep.colon_printer();
  timer_rep.int_printer(sec);
}

// Notification sending fucntion
void sendNotificationWithIcon(const std::string &title,
                              const std::string &message,
                              const std::string &iconPath) {
#if defined(_WIN32)
  // Windows: Loads the custom file path directly into the NotifyIcon object
  // Requires an absolute path to a .ico file for best results
  std::string cmd =
      "powershell -Command \"[void] "
      "[System.Reflection.Assembly]::LoadWithPartialName('System.Windows.Forms'"
      "); "
      "$objNotifyIcon = New-Object System.Windows.Forms.NotifyIcon; "
      "try { $objNotifyIcon.Icon = New-Object System.Drawing.Icon('" +
      iconPath +
      "') } "
      "catch { $objNotifyIcon.Icon = "
      "[System.Drawing.SystemIcons]::Information; } " // Fallback icon
      "$objNotifyIcon.BalloonTipTitle = '" +
      title +
      "'; "
      "$objNotifyIcon.BalloonTipText = '" +
      message +
      "'; "
      "$objNotifyIcon.Visible = $True; "
      "$objNotifyIcon.ShowBalloonTip(5000);\"";
  std::system(cmd.c_str());

#elif defined(__APPLE__)
  // macOS: Bundles the notification with an 'app' icon wrapper
  // Note: Standard AppleScript notification command doesn't allow random file
  // paths easily, but you can point it to an installed Application icon (e.g.,
  // "Terminal", "Finder")
  std::string cmd = "osascript -e 'display notification \"" + message +
                    "\" with title \"" + title + "\" sound name \"default\"'";
  std::system(cmd.c_str());

#elif defined(__linux__)
  // Linux: The '-i' switch accepts absolute paths to .png, .jpg, or system icon
  // names
  std::string cmd = "notify-send -i \"" + iconPath + "\" \"" + title + "\" \"" +
                    message + "\"";
  std::system(cmd.c_str());
#endif
}
int main(int argc, char **argv) {
// Assets handling
#if defined(_WIN32)
  std::string myIcon =
      "C:\\path\\to\\icon.ico"; // Windows strictly prefers .ico files
#else
  std::string myIcon =
      "~/pomo_cli/icon.png"; // Linux/macOS work perfectly with .png
#endif
  setlocale(LC_ALL, "");
  initscr();
  curs_set(0);
  start_color();
  noecho();
  // Basic window Definition and  alignment
  int screen_width, screen_height;
  getmaxyx(stdscr, screen_height, screen_width);
  int window_height, window_width;
  window_height = 20;
  window_width = screen_width / 3;
  WINDOW *application_window =
      newwin(window_height, window_width, 1, 2 * screen_width / 5);
  WINDOW *timer_window = newwin(5, window_width, 3, 2 * screen_width / 5);
  refresh();

  // Title Display
  init_pair(1, COLOR_RED, COLOR_BLACK);
  wattron(application_window, COLOR_PAIR(1));
  mvwprintw(application_window, 0, 0, "Pomodoro Timer");
  wrefresh(application_window);
  wattroff(application_window, COLOR_PAIR(1));

  // removes non-blocking input(Input can be taken simulataneously while doing
  // something else)
  nodelay(stdscr, true);
  // State
  AppState global_state = AppState::TimerPaused;
  int dur_state = 0;
  // Timer state
  int focus_duration = 25 * 60;
  int long_break_duration = 15 * 60;
  int short_break_duration = 5 * 60;
  int timer_duration_left = focus_duration;
  // Looped logic(continuos input)
  char c = getch();
  while (c != 'q' && c != 'Q') {

    auto time_tracker =
        std::chrono::steady_clock::now() + std::chrono::seconds(1);
    if ((c == 'p' || c == 'P') && global_state == AppState::TimerRunning)
      global_state = AppState::TimerPaused;
    if (global_state == AppState::TimerPaused) {
      switch (c) {
      case 's':
      case 'S':
        global_state = AppState::TimerRunning;
        break;
      case 'f':
      case 'F':
        global_state = AppState::EditDurationFocus;
        break;
      case 'b':
      case 'B':
        global_state = AppState::EditDurationShortBreak;
        break;
      case 'l':
      case 'L':
        global_state = AppState::EditDurationLongBreak;
        break;
      default:
        break;
      }
    }

    // Menu Options Display
    switch (global_state) {
    case AppState::TimerRunning:
      mvwprintw(application_window, 8, 0,
                "p:pause                              ");
      mvwprintw(application_window, 9, 0, "q:quit               ");
      mvwprintw(application_window, 10, 0, "                          ");
      mvwprintw(application_window, 11, 0, "                         ");
      mvwprintw(application_window, 12, 0, "      ");
      break;
    case AppState::TimerPaused:
      mvwprintw(application_window, 8, 0,
                "s:start                                 ");
      mvwprintw(application_window, 9, 0, "f:set focus duration");
      mvwprintw(application_window, 10, 0, "b:set short break duration");
      mvwprintw(application_window, 11, 0, "l:set long break duration");
      mvwprintw(application_window, 12, 0, "q:quit");
      break;
    case AppState::EditDurationFocus:
      mvwprintw(application_window, 8, 0,
                "Enter duration(in minutes):              ");
      mvwprintw(application_window, 9, 0, "                     ");
      mvwprintw(application_window, 10, 0, "                          ");
      mvwprintw(application_window, 11, 0, "                         ");
      mvwprintw(application_window, 12, 0, "      ");
      break;
    case AppState::EditDurationShortBreak:
      mvwprintw(application_window, 8, 0,
                "Enter duration(in minutes):              ");
      mvwprintw(application_window, 9, 0, "                     ");
      mvwprintw(application_window, 10, 0, "                          ");
      mvwprintw(application_window, 11, 0, "                         ");
      mvwprintw(application_window, 12, 0, "      ");
      break;
    case AppState::EditDurationLongBreak:
      mvwprintw(application_window, 8, 0,
                "Enter duration(in minutes):              ");
      mvwprintw(application_window, 9, 0, "                     ");
      mvwprintw(application_window, 10, 0, "                          ");
      mvwprintw(application_window, 11, 0, "                         ");
      mvwprintw(application_window, 12, 0, "      ");
      break;
    default:
      break;
    }
    wrefresh(application_window);
    if (global_state == AppState::TimerRunning) {
      if (timer_duration_left > 0) {
        timer_duration_left--;
        std::this_thread::sleep_until(time_tracker);
      } else {
        global_state = AppState::TimerPaused;
        dur_state = (dur_state + 1) % 8;
        if (dur_state == 7) {
          timer_duration_left = long_break_duration;
          sendNotificationWithIcon("Take a break", "Take a long break", myIcon);
        } else if (dur_state % 2 == 0) {
          timer_duration_left = focus_duration;
          sendNotificationWithIcon("Break is over", "Get to work", myIcon);
        } else {
          timer_duration_left = short_break_duration;
          sendNotificationWithIcon("Take a break", "Take a short break",
                                   myIcon);
        }
      }
      wclear(timer_window);
    } else if (global_state != AppState::TimerPaused) {
      echo();
      wmove(application_window, 8, 29);
      wrefresh(application_window);
      char c = wgetch(application_window);
      int duration_val = 0;
      while (c != '\n') {
        duration_val *= 10;
        duration_val += c - '0';
        c = wgetch(application_window);
      }
      duration_val *= 60;
      switch (global_state) {
      case AppState::EditDurationFocus:
        focus_duration = duration_val;
        break;
      case AppState::EditDurationLongBreak:
        long_break_duration = duration_val;
        break;
      case AppState::EditDurationShortBreak:
        short_break_duration = duration_val;
        break;
      default:
        break;
      }
      noecho();
      global_state = AppState::TimerPaused;
      if (dur_state == 7) {
        timer_duration_left = long_break_duration;
      } else if (dur_state % 2 == 0) {
        timer_duration_left = focus_duration;
      } else {
        timer_duration_left = short_break_duration;
      }
      wclear(timer_window);
    }
    print_time(timer_window, 0, 0, timer_duration_left);
    c = getch();
  }

  endwin();
}
