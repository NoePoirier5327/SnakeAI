#include "headers/mlp.hpp"
#include <iostream>

int main()
{
  std::vector<int> net_shape = {4, 5, 4, 1};
  MLP *network = new MLP(net_shape, 2);

  std::vector<std::vector<double>> inputs = {{0, 1}, {1, 0}, {1, 1}, {0, 0}};
  std::vector<std::vector<double>> targets = {{1}, {1}, {0}, {0}};
  
  std::cout << "Entrainement du réseau" << std::endl;
  
  std::cout << "Avant back_propagation -> 0, 1" << std::endl;
  network->feed_forward(inputs[0]);
  std::cout << network->display();

  //std::cout << "\nApprentissage de réseau" << std::endl;
  //network->backward_propagate({1}, 0.1);
  //std::cout << network->display();

  std::cout << "Après back propagation -> 0, 1" << std::endl;
  network->feed_forward(inputs[0]);
  std::cout << network->display();

  delete network;
  return 0;
}
