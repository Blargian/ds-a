#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

// does not provide the correct answer. eg) 8 incorrect
int GreedyCalculator(int n) {
  int num_operations = 0;
  int current_num = 1;
  while (current_num < n) {
    if (current_num <= n/3) {
      current_num = 3*current_num;
    } else if (current_num <= n/2) {
      current_num = 2*current_num;
    } else {
      current_num = 1 + current_num;
    }
    num_operations++;
  }
  return num_operations;
}

// suffers from the same problem as the one above. eg) 8 incorrect 
vector<int> optimal_sequence(int n) {
  std::vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

vector<int> optimal_sequence_fast(int n) {
  std::vector<int> sequence;
  while (n >= 1) {
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n-1;
    }
  }
  reverse(sequence.begin(),sequence.end());
  return sequence;
}

vector<int> optimal_sequence_recursive(vector<int>& sequence, int n) {
  sequence.push_back(n);
  if(n==1) {
    reverse(sequence.begin(),sequence.end());
  } else {
    if(n % 3 == 0) {
      optimal_sequence_recursive(sequence,n/3);
    } else if (n % 2 == 0) {
      optimal_sequence_recursive(sequence,n/2);
    } else {
      optimal_sequence_recursive(sequence,n-1);
    }
  }
  return sequence;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> sequence; 
  sequence = optimal_sequence_recursive(sequence,n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
  //std::cout << GreedyCalculator(n) << std::endl;
}
