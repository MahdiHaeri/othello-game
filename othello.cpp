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

  int change_charater_to_number(char charater) {
    return int(charater - 'A');
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

int main(int argc, char const *argv[]) {
  Map map;

  map.print_map();
  return 0;
}
