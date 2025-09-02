#include "headers/global.hpp"

double rng(double min, double max)
{
  // Création d'un moteur aléatoire static (il n'est appelée qu'une seule fois durant la compilation)
  static std::random_device rd;
  static std::mt19937 gen(rd());

  // création d'une distribution uniforme réelle
  std::uniform_real_distribution<double> dis(min, max);

  // On renvoie le nombre généré aléatoirement
  return dis(gen);
}

// Fonctions d'activation
// Sinusoïde
//double f(double x) { return sin(x); }
//double f_prime(double x) { return cos(x); }
// Sigmoïde
double f(double x) { return (1/(1 + exp(-1 * x))); }
double f_prime(double x) { return exp(-1 * x) / pow(1 + exp(-1 * x) , 2); }
