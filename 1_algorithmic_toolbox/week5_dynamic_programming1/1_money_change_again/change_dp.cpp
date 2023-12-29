#include <iostream>
#include <iostream>
#include <vector>
#include <limits>

int get_change(int money) {
  std::vector<int> denominations = {1,3,4};

  std::vector<int> MinNumCoins(money+1);
  for (int m=1; m<=money; m++) {
    MinNumCoins[m] = std::numeric_limits<int>::max();
    for (int i=0; i < denominations.size(); i++) {
      if (m >= denominations[i]) {
        int NumCoins = MinNumCoins[m-denominations[i]] + 1;
	if (NumCoins < MinNumCoins[m]) {
	  MinNumCoins[m] = NumCoins;
	}
      }
    }
  }
  return MinNumCoins.back(); 
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
