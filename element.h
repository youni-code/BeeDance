#ifndef ELEMENT_H
#define ELEMENT_H
#include <QString>
#include <complex>

class Element
{
    QString symbol;
    unsigned long count_nucleons;

    double conc;
    double mass;
    long atomic_number;

    std::complex<double> bc;
    std::complex<double> bi;
    double sigma_a;

    std::complex<double> bc_error;
    std::complex<double> bi_error;

    double coh_xs;
    double inc_xs;
    double scatt_xs;

public:

    void set_mass(double value) 					{ mass = value; }
    void set_concentrate(double co) 				{ conc = co; }
    void set_atomicNumber(unsigned long atom) 		{ atomic_number = atom; }
    void set_bc(std::complex<double> value) 		{ bc = value; }
    void set_bi(std::complex<double> value) 		{ bi = value; }
    void set_sigmaa(double value) 					{ sigma_a = value; }


    void setCohxs(double value) { coh_xs = value; }
    void setIncxs(double val) { inc_xs = val; }
    void setScattxs(double value) { scatt_xs = value; }


    QString getSymbol() const { return symbol; }
    double get_mass() const { return mass; }
    double get_concentrate() const { return conc; }
    unsigned long get_countNucleons() const { return count_nucleons; }
    unsigned long get_atomicNumber() const { return atomic_number;  }
    std::complex<double> getCohb() const { return bc; }
    std::complex<double> getIncb() const { return bi;  }
    double getCohxs() const { return coh_xs;  }
    double getScatxs() const { return scatt_xs;  }
    double getAbsxs() const { return sigma_a;  }



    Element(QString, unsigned long, unsigned long = 0);
    bool operator<(const Element&) const;

};

#endif // ELEMENT_H
