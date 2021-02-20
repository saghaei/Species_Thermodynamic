#include "Thermo.hpp"
const size_t step=324;
const size_t comment=166;

Thermo::Thermo(std::string name) {

bool nameExist = false;
char tmpName[10];
char nameRef[10];

unsigned short nameLength = (name.size() < 10 ? name.size() : 10);
strncpy(tmpName, name.data(), nameLength);
tmpName[nameLength] = '\0';

for(int cntr=0 ; tmpName[cntr] != 0 ; cntr++)
if(tmpName[cntr] <= 122 && tmpName[cntr] >= 97)
tmpName[cntr] -= 32;

if(strcmp(tmpName, "END") == 0) {
std::cerr << "END is not name of type." << std::endl;
exit(1);
}

std::ifstream inFile("database.dat", std::ios::in);
if(!inFile) {
std::cerr << "\"Error: File 'database.dat' could not be located.\"" << std::endl;
exit(1);
}

inFile.seekg(0, std::ios::end);
size_t sizeOfFile=inFile.tellg();

inFile.seekg(comment, std::ios::beg);
do {
inFile.getline(nameRef, 10, ' ');
if(strcmp(nameRef, tmpName) == 0) {
nameExist = true;
break;
}
inFile.seekg(index*step+comment, std::ios::beg);
index++;
} while(inFile.tellg() < sizeOfFile);
if(nameExist == false) {
std::cerr << tmpName << " does not found in database." << std::endl;
exit(1);
}

strncpy(formula, tmpName, nameLength);
formula[nameLength] = '\0';

readCoefficients(inFile);
}


void Thermo::readCoefficients(std::ifstream& inFile) {
size_t indx = (index-1)*step+comment;
char iden[7];
char lmnts[21];
char tempMin[8];
char tempMax[9];
char tempMid[9];
char aLH[16];

inFile.seekg(indx+18);
inFile.read(iden, 6);
iden[6] = '\0';
strncpy(identification, iden, sizeof(iden));

inFile.seekg(indx+24);
inFile.read(lmnts, 20);
lmnts[20] = '\0';

std::string tmpStr;
std::string tmpQty;
for(int cntr=0 ; cntr < 21 ; cntr++) {
if((tmpQty[0] && lmnts[cntr] <= 90 && lmnts[cntr] >= 65) || cntr==20) {
elements[tmpStr] = std::stoi(tmpQty);
tmpStr = "";
tmpQty = "";
}
if(lmnts[cntr] <= 90 && lmnts[cntr] >= 65) {
tmpStr += *(lmnts+cntr);
continue;
}
if(lmnts[cntr] <= 57 && lmnts[cntr] >= 48) {
tmpQty += *(lmnts+cntr);
}
}

inFile.seekg(indx+48);
inFile.getline(tempMin, 8, ' ');
tempMin[7] = '\0';
temp[0] = std::atof(tempMin);

inFile.seekg(indx+57);
inFile.getline(tempMax, 9, ' ');
tempMax[8] = '\0';
temp[2] = std::atof(tempMax);

inFile.seekg(indx+67);
inFile.getline(tempMid, 9, ' ');
tempMid[8] = '\0';
temp[1] = std::atof(tempMid);

inFile.seekg(indx+81);
inFile.read(aLH, 15);
aLH[15] = '\0';
a_H[0] = std::atof(aLH);

inFile.seekg(indx+96);
inFile.read(aLH, 15);
aLH[15] = '\0';
a_H[1] = std::atof(aLH);

inFile.seekg(indx+111);
inFile.read(aLH, 15);
aLH[15] = '\0';
a_H[2] = std::atof(aLH);

inFile.seekg(indx+126);
inFile.read(aLH, 15);
aLH[15] = '\0';
a_H[3] = std::atof(aLH);

inFile.seekg(indx+141);
inFile.read(aLH, 15);
aLH[15] = '\0';
a_H[4] = std::atof(aLH);

inFile.seekg(indx+162);
inFile.read(aLH, 15);
aLH[15] = '\0';
a_H[5] = std::atof(aLH);

inFile.seekg(indx+177);
inFile.read(aLH, 15);
aLH[15] = '\0';
a_H[6] = std::atof(aLH);

inFile.seekg(indx+192);
inFile.read(aLH, 15);
aLH[15] = '\0';
a_L[0] = std::atof(aLH);

inFile.seekg(indx+207);
inFile.read(aLH, 15);
aLH[15] = '\0';
a_L[1] = std::atof(aLH);

inFile.seekg(indx+222);
inFile.read(aLH, 15);
aLH[15] = '\0';
a_L[2] = std::atof(aLH);

inFile.seekg(indx+243);
inFile.read(aLH, 15);
aLH[15] = '\0';
a_L[3] = std::atof(aLH);

inFile.seekg(indx+258);
inFile.read(aLH, 15);
aLH[15] = '\0';
a_L[4] = std::atof(aLH);

inFile.seekg(indx+273);
inFile.read(aLH, 15);
aLH[15] = '\0';
a_L[5] = std::atof(aLH);

inFile.seekg(indx+288);
inFile.read(aLH, 15);
aLH[15] = '\0';
a_L[6] = std::atof(aLH);
}

void Thermo::printDetails() {
std::map<std::string, unsigned>::iterator itr;

 std::cout << "Elements: ";
for(itr=elements.begin() ; itr!=elements.end() ; itr++)
std::cout << std::right << std::setw(2) << itr->first << ':' << std::left << std::setw(2) << itr->second << "   ";

std::cout << std::right << "\nSpecies formula: " << formula << std::endl;
std::cout << "Identification code: " << identification << std::endl;

std::cout << std::setprecision(1) << std::fixed;
std::cout << "\nCoefficients between  " << temp[0] << " to " << temp[1] << " [K]" << std::endl;
std::cout << std::setprecision(8) << std::scientific;
for(int i=0 ; i<7 ; i++)
std::cout << 'a' << i+1 << ": " << std::setw(15) << a_L[i] << std::endl;

std::cout << std::setprecision(1) << std::fixed;
std::cout << "\nCoefficients between " << temp[1] << " to " << temp[2] << " [K]" << std::endl;
std::cout << std::setprecision(8) << std::scientific;
for(int i=0 ; i<7 ; i++)
std::cout << 'a' << i+1 << ": " << std::setw(15) << a_H[i] << std::endl;
std::cout << std::endl;
}

double Thermo::he(const double& T) {
double enthalpy=0;
double *coefficients;
if(T >= temp[0] && T <= temp[1])
coefficients = a_L;
else if(T > temp[1] && T <= temp[2])
coefficients = a_H;
else {
std::cerr << "Temperature " << T << " for " << formula << " is not specified." << std::endl;
exit(1);
}

for(int cntr=0 ; cntr<5 ; cntr++)
enthalpy += *(coefficients+cntr)*pow(T,cntr)/(cntr+1);
enthalpy += *(coefficients+5)/T;
enthalpy *= (R*T);

return enthalpy;
}

double Thermo::dhf(void) {
return this->he(298.15);
}

double Thermo::h0(void) const {
return a_L[5]*R;
}

double Thermo::h(const double& T) {
return (this->he(T) - this->h0());
}

double Thermo::s(const double& T) {
double entropy=0;
double *coefficients;
if(T >= temp[0] && T <= temp[1])
coefficients = a_L;
else if(T > temp[1] && T <= temp[2])
coefficients = a_H;
else {
std::cerr << "Temperature " << T << " for " << formula << " is not specified." << std::endl;
exit(1);
}
entropy += *coefficients*log(T);
for(int cntr=1 ; cntr<5 ; cntr++)
entropy += *(coefficients+cntr)*pow(T,cntr)/cntr;
entropy += *(coefficients+6);
entropy *= R;
return entropy;
}

double Thermo::u(const double& T) {
return this->h(T)-R*T;
}

double Thermo::cp(const double& T) {
double cp=0;
double *coefficients;
if(T >= temp[0] && T <= temp[1])
coefficients = a_L;
else if(T > temp[1] && T <= temp[2])
coefficients = a_H;
else {
std::cerr << "Temperature " << T << " for " << formula << " is not specified." << std::endl;
exit(1);
}
for(int cntr=0 ; cntr<5 ; cntr++)
cp += *(coefficients+cntr)*pow(T,cntr);
cp *= R;
return cp;
}

double Thermo::cv(const double& T) {
return (cp(T)-R);
}

double Thermo::k(const double& T) {
return cp(T)/(cp(T)-R);
}

double Thermo::mw() {
double mw=0;
std::map<std::string, unsigned>::iterator itr;
for(itr=elements.begin() ; itr!=elements.end() ; itr++)
if(weights.find(itr->first) != weights.end())
mw += itr->second * weights[itr->first];
return mw;
}

double Thermo::he_m(const double& T) {
return he(T)/mw();
}

double Thermo::dhf_m(void) {
return dhf()/mw();
}

double Thermo::h0_m(void) {
return h0()/mw();
}

double Thermo::h_m(const double& T) {
return h(T)/mw();
}

double Thermo::s_m(const double& T) {
return s(T)/mw();
}

double Thermo::u_m(const double& T) {
return u(T)/mw();
}
