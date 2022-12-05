#include <iostream>
#include <string>

using namespace std;

#define SIZE 9
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
        if (i == 0 && j == 0) {
          map[i][j] = ' ';
        } else if (j == 0) {
          map[i][j] = '0' + i;
        } else if (i == 0) {
          map[i][j] = 'A' + j - 1;
        } else {
          map[i][j] = '-';
        }
      }
    }
  }

  void print_map() {
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        cout << map[i][j] << ' ';
      }
      cout << endl;
    }
  }

  char map[SIZE][SIZE];
private:
};

int main(int argc, char const *argv[]) {
  Map map;

  map.print_map();
  return 0;
}
