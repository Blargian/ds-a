#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <utility>

using std::vector;

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  
  vector<int> cnt(points.size(),0);
  vector<std::pair<int,int>> segments; 

  for(auto i = starts.begin(); i < starts.end(); i++) {
    auto index = std::distance(starts.begin(),i);
    segments.push_back(std::make_pair(starts[index],ends[index]));  
  };

  std::sort(segments.begin(), segments.end(), [](std::pair<int,int> a, std::pair<int,int> b){ return a.first < b.first;});
  //std::sort(points.begin(), points.end());

  auto p_it = points.begin();
  for (p_it; p_it < points.end(); ++p_it) {
    int count = 0;
    auto seg_it = segments.begin();
    for (seg_it ; seg_it < segments.end() ; ++seg_it){
      if (seg_it->first <= *p_it && *p_it <= seg_it->second ){
        count++;
	      cnt[std::distance(points.begin(),p_it)] = count;
      } else {
        if(count>0) {
          segments.erase(segments.begin(),seg_it-1);
          break;
        }      
      }
    }
  }
  return cnt;
}


int main() {
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
