#include "headers/NN.hpp"
#include <iostream>

int main()
{
  Neuron *neurone = new Neuron();

  double input[3] = {3, 0, 1};
  double weight[3] = {3, -0.6, 0.2};

  neurone->feed_forward(input, weight);
  std::cout << neurone->display() << std::endl;

  delete neurone;
  return 0;
}
