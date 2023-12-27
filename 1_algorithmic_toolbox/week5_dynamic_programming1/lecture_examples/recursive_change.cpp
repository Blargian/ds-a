// An example showing the recursive solution to the money chain problem
// This solution works but could be slow 

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <cassert>
#include <exception>

int GreedyChange(int money, std::vector<int> coins) {
  
  std::vector<int> change;

  while (money > 0) {
    auto it = coins.begin();
    while(it!=coins.end()){
      if(*it > money) {
        break;
      }
      it++;
    }
    it--;
    int coin = *it;
    change.push_back(coin);
    money = money - coin;
  }
  return change.size();

}


int RecursiveChange(const int money, const std::vector<int> coins) {
  if (money == 0)
    return 0;
  int MinNumCoins = std::numeric_limits<int>::max(); 
  for (int i=0; i<coins.size(); i++) {
    if (money >= coins[i]) {
      int NumCoins = RecursiveChange(money - coins[i],coins);
      if (NumCoins+1 < MinNumCoins)
        MinNumCoins = NumCoins + 1;
    }
  }
  return MinNumCoins;
}

int main() {
  int money;
  int n_denominations = 0;
  std::vector<int> denominations; 

  std::cout << "enter money: ";
  std::cin >> money; 
  std::cout << "enter number of denominations: ";
  std::cin >> n_denominations;
  
  int temp = 0; 
  for(int i = 0; i<n_denominations; i++) {
    std::cin >> temp;
    denominations.push_back(temp);
  }

  // This is used to find the first case for which Greedy returns the incorrect minimum
  for(int i=0; i<money; i++) {
    std::cout << i << std::endl;
    int greedy = GreedyChange(i,denominations);
    std::cout << "greedy: " << greedy << std::endl;
    int recursive = RecursiveChange(i,denominations);
    std::cout << "recursive: " << recursive << std::endl;
    assert(greedy==recursive);
  }

  // comment the code above and uncomment below if you want to try out a single implementation
  
  //int min_coins = GreedyChange(money,denominations);
  //int min_coins = RecursiveChange(money,denominations);
  //std::cout << "minimum number of coins: " << min_coins;
  return 0;
}
