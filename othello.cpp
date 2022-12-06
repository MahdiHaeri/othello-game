#include <iostream>
#include <string>

using namespace std;

#define SIZE 8
#define PLAYER_1 'B'
#define PLAYER_2 'R'
#define BLANK '-'
#define TARGET '*'

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
      cout << char('A' + i ) << ' ';
    }
    cout << endl;
    for (int i = 0; i < SIZE; i++) {
      cout << i + 1 << ' ';
      for (int j = 0; j < SIZE; j++) {
        cout << map[i][j] << ' ';
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
        }
      }
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

    set_placeables();
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

  bool is_there_in_map(int i, int j) {
    if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
      return true;
    }
    return false;
  }

  char player_turn() {
    return turn % 2 == 0 ? PLAYER_1 : PLAYER_2;
  }

  void print_info() {
    cout << "turn: " << turn << " Player: " << player_turn() << endl;
    cout << "player_score_1: " << player_score_1 << endl << "player_score_2: " << player_score_2 << endl;
  }

  int player_score_1 = 0;
  int player_score_2 = 0;
  int turn = 0;
  Map *map;
private:
};

class Othello_game {
public:
  Othello_game() {
    map = new Map();
    game_control = new Game_control(map);
  }

  void start_game() {
    while (game_control->turn < 60) {
      print_game();
      int i = get_input_i();
      int j = get_input_j();
      game_control->turn++;
    }
  }

  int change_charater_to_number(char charater) {
    return int(charater - 'A');
  }

  int get_input_i() {
    int i;
    cin >> i;
    return i;
  }

  int get_input_j() {
    char _j;
    cin >> _j;
    int j = change_charater_to_number(_j);
    return j;
  }

  void print_game() {
    game_control->update_placeable();
    game_control->print_info();
    map->print_map();
  }


  Map *map;
  Game_control *game_control;
private:

};


int main(int argc, char const *argv[]) {
  Othello_game game;
  game.start_game();
  return 0;
}
