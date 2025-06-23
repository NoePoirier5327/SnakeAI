#include "headers/layer.hpp"
#include <iostream>

int main()
{
  Layer *layer = new Layer(2);

  double input[3] = {3, 0, 1};
  double weight[3] = {3, 1, 1};

  layer->feed_forward(input, weight);
  std::cout << layer->display() << std::endl;

  delete layer;

  return 0;
}
