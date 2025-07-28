#include "headers/mlp.hpp"
#include <iostream>

int main()
{
  std::vector<int> net_shape = {4, 4, 4, 1};
  MLP *network = new MLP(net_shape, 2);

  std::vector<double> input = {0, 1};
  network->feed_forward(input);

  std::cout << network->display();

  delete network;

  return 0;
}
