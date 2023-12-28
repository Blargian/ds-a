// Implementation of dynamic programming approach to the money change problem
#include <iostream>
#include <vector>
#include <limits>

int DpRecursive(const int money, const std::vector<int> denominations) {
  std::vector<int> MinNumCoins(money); 
  for (int m=1; m < money+1; m++) {
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
  return MinNumCoins[money]; 
}

int main() {
  int money,n;
  std::vector<int> denominations;
  std::cout << "enter money: ";
  std::cin >> money;
  std::cout << "enter coin denominations n: ";
  std::cin >> n;
  for (int i=0; i<n; i++) {
    int temp;
    std::cin >> temp; 
    denominations.push_back(temp);
  }

  int min_coins = DpRecursive(money,denominations);
  std::cout << "min_coins: " << min_coins << std::endl; 
}








