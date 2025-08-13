#include "headers/mlp.hpp"
#include <iostream>

int main()
{
  std::vector<int> net_shape = {4, 4, 4, 1};
  MLP *network = new MLP(net_shape, 2);

  std::vector<std::vector<double>> inputs = {{0, 1}, {1, 0}, {1, 1}, {0, 0}};
  std::vector<std::vector<double>> targets = {{1}, {1}, {0}, {0}};
  
  std::cout << "Entrainement du réseau";

  for (int i = 0; i < 100000; i++)
    for (int j = 0; j < 4; j++)
    {
      network->feed_forward(inputs[j]);
      network->backward_propagate(targets[j], 0.1);
    }

  std::cout << "\nTest de l'entrainement !\nOpérande numéro 1 : ";
  int a; std::cin >> a;

  std::cout << "Opérande numéro 2 : ";
  int b; std::cin >> b;

  std::vector<double> test_input;
  test_input.push_back(a);
  test_input.push_back(b);
  
  network->feed_forward(test_input);
  std::cout << "\nRésultat : \n" << network->display();

  delete network;
  return 0;
}
