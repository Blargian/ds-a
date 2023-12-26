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

// This was my original attempt, however
// the edge case below causes the algorithm 
// to return an incorrect result

// 3 3
// 1 1
// -2 5
// 3 5
// 3 5 -2

// should give: 2 2 1

vector<int> fast_count_segments_flawed(vector<int> starts, vector<int> ends, vector<int> points) {
  
  vector<int> cnt(points.size(),0);
  vector<std::pair<int,int>> segments; 

  for(auto i = starts.begin(); i < starts.end(); i++) {
    auto index = std::distance(starts.begin(),i);
    segments.push_back(std::make_pair(starts[index],ends[index]));  
  };

  std::sort(segments.begin(), segments.end(), [](std::pair<int,int> a, std::pair<int,int> b){ return a.first < b.first;});

  auto p_it = points.begin();
  for (p_it; p_it < points.end(); ++p_it) {
    int count = 0;
    auto seg_it = segments.begin();
    for (seg_it ; seg_it < segments.end() ; ++seg_it){
      if ((seg_it->first <= *p_it && *p_it <= seg_it->second) || (seg_it->first == *p_it) || (seg_it->second == *p_it)){
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

typedef enum point_type {
  start,
  point,
  end,
} point_type;

typedef struct Element {
  Element(int v, point_type p) : value(v), type_of_point(p) {};
  int value;
  point_type type_of_point;
} Element;

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  
  assert(starts.size() == ends.size());

  vector<int> cnt(points.size(),0);
  vector<std::pair<int,int>> segments; 
  
  // utility vector which combines starts and ends into segments
  for(auto i = starts.begin(); i < starts.end(); i++) {
    auto index = std::distance(starts.begin(),i);
    segments.push_back(std::make_pair(starts[index],ends[index]));  
  };

  // sort segments and points in ascending order
  std::sort( segments.begin(), segments.end(), [](std::pair<int,int> a, std::pair<int,int> b ){ return a.first < b.first; });
  vector<int> points_ordered;
  std::copy( points.begin(), points.end(), std::back_inserter(points_ordered) );

  // add everything into one array 
  vector<Element> elements;
  for( auto seg_it = segments.begin(); seg_it < segments.end(); ++seg_it ) {
    elements.push_back(Element(seg_it->first,start));
    elements.push_back(Element(seg_it->second,end));
  }  
  for( auto p_it = points_ordered.begin(); p_it < points_ordered.end(); ++p_it ) {
    elements.push_back(Element(*p_it,point));
  }

  // sort elements such that if an end and a point are equal, point should be first
  std::sort(elements.begin(),elements.end(),[](Element a, Element b)
  {
    if (a.value == b.value) {
      return static_cast<int>(a.type_of_point) < static_cast<int>(b.type_of_point); // return according to ordering of enum point_type
    } else {
      return a.value < b.value;
    }   
  });

  int count = 0;
  for ( auto el_it = elements.begin(); el_it != elements.end(); ++el_it ) {
    if (el_it->type_of_point == start) {
      count++;
    } else if (el_it->type_of_point == end) {
      count--;
    } else if (el_it->type_of_point == point) {

      auto it = std::unique(points.begin(), points.end());
      bool wasUnique = (it == points.end());

      if(wasUnique) {
        auto index = std::distance(points.begin(),std::find(points.begin(),points.end(),el_it->value));
        cnt[index] = count;
      } else {
      // taking into account that points can have duplicates 
      it = points.begin();
      while(it!=points.end()) {
        it = std::find(it,points.end(),el_it->value);
        auto index = std::distance(points.begin(),it);
        if(it!=points.end())
          cnt[index] = count;
          it++;
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

