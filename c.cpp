#include <iostream>
#include <cmath>
#include <cstdlib> // Pour malloc et free

int main() {
    size_t bufferSize = 200; // Taille initiale pour l'entrée utilisateur
    char* input = (char*)malloc(bufferSize * sizeof(char)); // Allocation dynamique de mémoire

    if (!input) {
        std::cerr << "Erreur : Impossible d'allouer la mémoire !" << std::endl;
        return 1;
    }

    std::cout << "Entrez un calcul (ex : 5+3*2-4/2, sqrt(9), sin(90), cos(0), pow(2,3)): ";
    std::cin.getline(input, bufferSize); // Lecture de l'entrée utilisateur

    double result = 0.0; // Résultat final
    char operation = '+'; // Opération par défaut
    double currentNumber = 0.0; // Nombre en cours de traitement

    char* ptr = input; // Pointeur pour parcourir la chaîne

    while (*ptr != '\0') {
        // Ignorer les espaces
        while (*ptr == ' ') {
            ptr++;
        }

        // Gestion des fonctions spéciales
        if (*ptr == 's' && *(ptr + 1) == 'q' && *(ptr + 2) == 'r' && *(ptr + 3) == 't' && *(ptr + 4) == '(') {
            ptr += 5; // Passer "sqrt("
            currentNumber = strtod(ptr, &ptr); // Lire le nombre
            if (*ptr == ')') {
                currentNumber = sqrt(currentNumber);
                ptr++; // Passer ')'
            } else {
                std::cerr << "Erreur : Parenthèse manquante pour sqrt !" << std::endl;
                free(input); // Libération de mémoire avant de quitter
                return 1;
            }
        } else if (*ptr == 's' && *(ptr + 1) == 'i' && *(ptr + 2) == 'n' && *(ptr + 3) == '(') {
            ptr += 4; // Passer "sin("
            currentNumber = strtod(ptr, &ptr); // Lire le nombre
            if (*ptr == ')') {
                currentNumber = sin(currentNumber * M_PI / 180); // Convertir en radians
                ptr++; // Passer ')'
            } else {
                std::cerr << "Erreur : Parenthèse manquante pour sin !" << std::endl;
                free(input);
                return 1;
            }
        } else if (*ptr == 'c' && *(ptr + 1) == 'o' && *(ptr + 2) == 's' && *(ptr + 3) == '(') {
            ptr += 4; // Passer "cos("
            currentNumber = strtod(ptr, &ptr); // Lire le nombre
            if (*ptr == ')') {
                currentNumber = cos(currentNumber * M_PI / 180); // Convertir en radians
                ptr++; // Passer ')'
            } else {
                std::cerr << "Erreur : Parenthèse manquante pour cos !" << std::endl;
                free(input);
                return 1;
            }
        } else if (*ptr == 'p' && *(ptr + 1) == 'o' && *(ptr + 2) == 'w' && *(ptr + 3) == '(') {
            ptr += 4; // Passer "pow("
            double base = strtod(ptr, &ptr); // Lire la base
            if (*ptr == ',') {
                ptr++; // Passer ','
                double exponent = strtod(ptr, &ptr); // Lire l'exposant
                if (*ptr == ')') {
                    currentNumber = pow(base, exponent);
                    ptr++; // Passer ')'
                } else {
                    std::cerr << "Erreur : Parenthèse manquante pour pow !" << std::endl;
                    free(input);
                    return 1;
                }
            } else {
                std::cerr << "Erreur : Syntaxe incorrecte pour pow !" << std::endl;
                free(input);
                return 1;
            }
        } else if ((*ptr >= '0' && *ptr <= '9') || *ptr == '.') {
            // Lire un nombre
            currentNumber = strtod(ptr, &ptr);
        } else {
            std::cerr << "Erreur : Entrée invalide !" << std::endl;
            free(input);
            return 1;
        }

        // Appliquer l'opération précédente
        switch (operation) {
            case '+':
                result += currentNumber;
                break;
            case '-':
                result -= currentNumber;
                break;
            case '*':
                result *= currentNumber;
                break;
            case '/':
                if (currentNumber == 0) {
                    std::cerr << "Erreur : Division par zéro !" << std::endl;
                    free(input);
                    return 1;
                }
                result /= currentNumber;
                break;
            default:
                std::cerr << "Erreur : Opérateur invalide !" << std::endl;
                free(input);
                return 1;
        }

        // Ignorer les espaces
        while (*ptr == ' ') {
            ptr++;
        }

        // Lire l'opération suivante
        if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/') {
            operation = *ptr;
            ptr++;
        } else if (*ptr != '\0' && *ptr != ')') {
            std::cerr << "Erreur : Entrée invalide !" << std::endl;
            free(input);
            return 1;
        }
    }

    std::cout << "Résultat : " << result << std::endl;

    free(input); // Libération de mémoire avant de quitter
    return 0;
}
