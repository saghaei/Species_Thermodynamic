#ifndef THERMO_H
#define THERMO_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include <map>

class Thermo {
public:
Thermo(std::string);
void readCoefficients(std::ifstream&);
void printDetails();
double he(const double&);      // [kJ/kmol]
double dhf(void);              // [kJ/kmol]
double h0(void) const;         // [kJ/kmol]
double h(const double&);       // [kJ/kmol]
double s(const double&);       // [kJ/kmol-K]
double u(const double&);       // [kJ/kmol]
double cp(const double&);      // [kJ/kmol-K]
double cv(const double&);      // [kJ/kmol-K]
double k(const double&);       // [Dimentionless]
double mw(void);               // [kg/kmol]
double he_m(const double&);    // [kJ/kmol]
double dhf_m(void);            // [kJ/kg]
double h0_m(void);             // [kJ/kg]
double h_m(const double&);     // [kJ/kg]
double s_m(const double&);     // [kJ/kg-K]
double u_m(const double&);     // [kJ/kg]
private:
size_t index=1;
char formula[10];
char identification[7];
double a_H[7];
double a_L[7];
double temp[3];
std::map<std::string, unsigned> elements;
std::map<std::string, double> weights = {{"H",  01.00794},
				         {"C",  12.01070},
				         {"O",  15.99900},
				         {"N",  14.00670},
				         {"S",  32.06500},
				         {"AR", 39.94800}};
const double R = 8.3144598;		 // [kJ/kmol-K]
};

#endif
