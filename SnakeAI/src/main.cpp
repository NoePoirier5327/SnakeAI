#include "headers/layer.hpp"
#include <iostream>

int main()
{
  Layer *layer = new Layer(2);

  std::vector<double> input = {0, 1};
  std::vector<double> weight = {1, 1};

  layer->feed_forward(input, weight);
  std::cout << layer->display() << std::endl;

  delete layer;

  return 0;
}
