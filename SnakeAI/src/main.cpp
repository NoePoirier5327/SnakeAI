#include "headers/mlp.hpp"
#include <iostream>

int main()
{
  std::vector<int> net_shape = {6, 8, 8, 8, 1};
  MLP network = MLP(net_shape, 2);

  std::vector<std::vector<double>> inputs = {{0, 1}, {1, 0}, {1, 1}, {0, 0}};
  std::vector<std::vector<double>> targets = {{1}, {1}, {0}, {0}};
  
  network.train(inputs, targets, 1000000, 0.1);
  
  std::cout << "Test de l'entrainement sur une logique XOR." << std::endl;
  std::cout << "quitter avec -> CTRL-C" << std::endl; 

  int a,b;
  std::vector<double> test = {1, 1};
  std::vector<double> outputs;
  while (1)
  {
    std::cout << "Opérande numéro 1 : "; std::cin >> a;
    std::cout << "Opérande numéro 2 : "; std::cin >> b;
    test[0] = a; test[1] = b;

    outputs = network.feed_forward(test);
    std::cout << "Réponse : " << (outputs[0] >= 0.5) << std::endl;
    //std::cout << network.display();
  }

  return 0;
}
