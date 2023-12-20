#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

using std::vector;

//merges two arrays back into one 
long long merge(std::vector<int> &arr, int left, int mid, int right) {
  int i = left, j = mid, k=0;
  long long invCount = 0;
  std::vector<int> temp(right - left + 1);

  while ((i < mid) && (j <= right)) {
    if (arr[i] <= arr[j]) {
      temp[k] = arr[i];
      ++k;
      ++i;
    } else 
    {
      temp[k] = arr[j];
      invCount += (mid - i);
      ++k;
      ++j;
    }
  }

  while (i < mid) {
    temp[k] = arr[i];
    ++k;
    ++i;
  }
 
  while (j <= right) {
    temp[k] = arr[j];
    ++k;
    ++j;
  }
 
  for (i = left, k = 0; i <= right; i++, k++) {
    arr[i] = temp[k];
  }

  return invCount;
}

long long mergeSort(vector<int> &a, size_t left, size_t right) {
  long long number_of_inversions = 0;
  
  if (right > left) {
    int mid = (right + left) / 2;
    number_of_inversions = mergeSort(a, left, mid);
    number_of_inversions += mergeSort(a, mid + 1, right);
    number_of_inversions += merge(a, left, mid + 1, right);
  }
  return number_of_inversions;
}

//O(n^2) time complexity solution -> naive 
long long get_number_of_inversions_naive(const std::vector<int> &a) {
  long long number_inversions = 0;

  for (auto it_outer = a.begin(); it_outer < a.end(); it_outer++) {
    for (auto it_inner = it_outer+1; it_inner < a.end(); it_inner++) {
      if ( *it_inner < *it_outer)
        number_inversions++;
    }
  }

  return number_inversions;

}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  vector<int> b(a.size());
  std::cout << mergeSort(a, 0, a.size()-1) << '\n';
}
