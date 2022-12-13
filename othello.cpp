#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <random>

using namespace std;

#define SIZE 8
#define MAX_TURN (SIZE * SIZE - 4)
#define PLAYER_1 'Y'
#define PLAYER_2 'R'
#define BLANK '-'
#define TARGET '*'

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define __RESET   "\033[0m"
#define __BLACK   "\033[30m"      /* Black */
#define __RED     "\033[31m"      /* Red */
#define __GREEN   "\033[32m"      /* Green */
#define __YELLOW  "\033[33m"      /* Yellow */
#define __BLUE    "\033[34m"      /* Blue */
#define __MAGENTA "\033[35m"      /* Magenta */
#define __CYAN    "\033[36m"      /* Cyan */
#define __WHITE   "\033[37m"      /* White */
#define __BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define __BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define __BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define __BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define __BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define __BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define __BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define __BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
//!

#define __PLAYER_COLOR_1 __YELLOW
#define __PLAYER_COLOR_2 __BOLDRED
#define __BORDER_COLOR __BOLDWHITE

class Map {
public:
  Map() {
    config_map();
  }

  void config_map() {
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        map[i][j] = BLANK;
      }
      insert(PLAYER_1, SIZE / 2 - 1, SIZE / 2 - 1);
      insert(PLAYER_1, SIZE / 2, SIZE / 2);
      insert(PLAYER_2, SIZE / 2, SIZE / 2 - 1);
      insert(PLAYER_2, SIZE / 2 - 1, SIZE / 2);
    }
  }


  void print_map() {
    cout << "  ";
    for (int i = 0; i < SIZE; i++) {

      cout << __BORDER_COLOR << char('A' + i ) << ' ' << __RESET; // print by white color
    }
    cout << endl;
    for (int i = 0; i < SIZE; i++) {
      cout << __BORDER_COLOR << i + 1 << ' ' << __RESET; //  print by white color
      for (int j = 0; j < SIZE; j++) {
        if (map[i][j] == PLAYER_1) {
          cout << __PLAYER_COLOR_1;
        } else if (map[i][j] == PLAYER_2) {
          cout << __PLAYER_COLOR_2;
        } else if (map[i][j] == TARGET) {
          cout << __GREEN;
        }
        cout << map[i][j] << ' ';
        cout << __RESET;
      }
      cout << endl;
    }
  }

  void insert(char charater, int i, int j) {
    map[i][j] = charater;
  }

  char map[SIZE][SIZE];
private:
};

class Game_control {
public:
  Game_control(Map *_map) {
    map = _map;
  }

  int go(int i, int j, int p, int q, int k) {
    if (!is_there_in_map(i + p, j + q)) {
      return -100;
    } else if (map->map[i + p][j + q] == BLANK || map->map[i + p][j + q] == TARGET) {
      return -100;
    } else if (map->map[i + p][j + q] == player_turn()) {
      return k;
    }
    return go(i + p, j + q, p, q, k + 1);
  }

  bool is_placeable(int i, int j) {
    for (int p = -1; p <= 1; p++) {
      for (int q = -1; q <= 1; q++) {
        if (go(i, j, p, q, 0) > 0) {
          return true;
        }
      }
    }
    return false;
  }

  void set_placeables() {
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        if (map->map[i][j] == BLANK && is_placeable(i, j)) {
          map->insert(TARGET, i, j);
          targets.push_back(pair(i, j));
        }
      }
    }
  }

  bool is_there_in_targets(int i, int j) {
    for (int k = 0; k < targets.size(); k++) {
      if (targets[k].first == i && targets[k].second == j) {
        return true;
      }
    }
    return false;
  }

  void turn_discs(int i, int j) {
    for (int p = -1; p <= 1; p++) {
      for (int q = -1; q <= 1; q++) {
        int go_direction = go(i, j, p, q, 0);
        if (go_direction > 0) {
          calculate_scores(go_direction);
          int x = i, y = j;
          for (int k = 1; k <= go_direction; k++) {
            x += p;
            y += q;
            map->map[x][y] = player_turn();
          }
        }
      }
    }
  }

  void calculate_scores(int score) {
    if (player_turn() == PLAYER_1) {
      player_score_1 += score;
      player_score_2 -= score;
    } else {
      player_score_1 -= score;
      player_score_2 += score;
    }
  }


  void update_placeable() {
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        if (map->map[i][j] == TARGET) {
          map->map[i][j] = BLANK;
        }
      }
    }
    targets.clear();

    set_placeables();
  }


  bool is_there_in_map(int i, int j) {
    if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
      return true;
    }
    return false;
  }

  char player_turn() {
    return turn % 2 == 0 ? PLAYER_2 : PLAYER_1;
  }

  string player_color() {
    if (player_turn() == PLAYER_1) {
      return __PLAYER_COLOR_1;
    } else {
      return __PLAYER_COLOR_2;
    }
  }

  void print_info() {
    cout << "turn: " << turn << " Player: " << player_color() << player_turn() << __RESET <<  __PLAYER_COLOR_1  << " player_score_1: " << player_score_1 << __RESET << __PLAYER_COLOR_2 << " player_score_2: " << player_score_2  << __RESET << endl;
  }

  int player_score_1 = 2;
  int player_score_2 = 2;
  int turn = 1;
  Map *map;
  vector<pair<int, int>> targets;
private:
};

class Othello_game {
public:
  Othello_game() {
    map = new Map();
    game_control = new Game_control(map);
  }

  void start_game() {
    while (game_control->turn <= MAX_TURN) {
      system("clear");
      print_game();
      int i, j;
      if (game_control->player_turn() == PLAYER_2) {
        cout << "please wait for bot... " << endl;
        system("sleep 1.5");
        pair<int, int> random_choice = choice_random();
        i = random_choice.first;
        j = random_choice.second;
      } else {
        i = get_input_i();
        j = get_input_j();
        if (!game_control->is_there_in_targets(i, j)) {
          cout << "Incorrect intput! Please try again." << endl;
          system("sleep .5");
          start_game();
        }
      }

      game_control->turn_discs(i, j);
      map->insert(game_control->player_turn(), i, j);
      if (game_control->player_turn() == PLAYER_1) {
        game_control->player_score_1++;
      } else {
        game_control->player_score_2++;
      }
      game_control->turn++;
    }
  }

  int change_charater_to_number(char charater) {
    return int(charater - 'A');
  }

  int get_input_i() {
    int i;
    cin >> i;
    return i - 1;
  }

  int get_input_j() {
    char _j;
    cin >> _j;
    int j = change_charater_to_number(_j);
    return j;
  }

  void print_game() {
    game_control->print_info();
    game_control->update_placeable();
    map->print_map();
  }

  pair<int, int> choice_random() {
    int random = rand() % game_control->targets.size();
    return game_control->targets[random];
  }

  Map *map;
  Game_control *game_control;
private:

};

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  Othello_game game;
  game.start_game();
  return 0;
}
