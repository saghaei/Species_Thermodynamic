#include <iostream>
#include "Thermo.hpp"

int main() {
system("clear");

std::string name;
double temperature = 298.15;

std::cout << "Enter species name: ";
std::cin >> name;
Thermo *spc(new Thermo(name));

spc->printDetails();

std::cout << "Enter temperature: ";
std::cin >> temperature;

std::cout << "\n--------------- Molar ---------------\n" << std::endl;
std::cout << std::fixed << std::setprecision(0);
std::cout << "h_eng: " << spc->he(temperature) << std::endl;
std::cout << "  dhf: " << spc->dhf() << std::endl;
std::cout << "   h0: " << spc->h0() << std::endl;
std::cout << "    h: " << spc->h(temperature) << std::endl;
std::cout << "    u: " << spc->u(temperature) << std::endl;
std::cout << std::fixed << std::setprecision(2);
std::cout << "    s: " << spc->s(temperature) << std::endl;

std::cout << "\n--------------- Mass ----------------\n" << std::endl;
std::cout << std::fixed << std::setprecision(0);
std::cout << "h_eng: " << spc->he_m(temperature) << std::endl;
std::cout << "  dhf: " << spc->dhf_m() << std::endl;
std::cout << "   h0: " << spc->h0_m() << std::endl;
std::cout << "    h: " << spc->h_m(temperature) << std::endl;
std::cout << "    u: " << spc->u_m(temperature) << std::endl;
std::cout << std::fixed << std::setprecision(2);
std::cout << "    s: " << spc->s_m(temperature) << std::endl;

std::cout << "\n   Cp: " << spc->cp(temperature) << std::endl;
std::cout << "   Cv: " << spc->cv(temperature) << std::endl;
std::cout << "    k: " << spc->k(temperature) << std::endl;
std::cout << "   mw: " << spc->mw() << std::endl;

delete spc;

return 0;
}
