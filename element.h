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
    double sigma_a_error;

    double coh_xs;
    double inc_xs;
    double scatt_xs;

public:

    void set_mass(double value) 					{ mass = value; }
    void set_concentrate(double co) 				{ conc = co; }
    void set_atomic_number(unsigned long atom) 		{ atomic_number = atom; }

    void set_bc(std::complex<double> value) 		{ bc = value; }
    void set_bi(std::complex<double> value) 		{ bi = value; }
    void set_sigmaa(double value) 					{ sigma_a = value; }

    void set_bc_error(std::complex<double> value) 	{ bc_error = value; }
    void set_bi_error(std::complex<double> value) 	{ bi_error = value; }
    void set_sigmaa_error(double value) 			{ sigma_a_error = value; }



    void setCohxs(double value) { coh_xs = value; }
    void setIncxs(double val) { inc_xs = val; }
    void setScattxs(double value) { scatt_xs = value; }


    QString get_symbol() const { return symbol; }
    double get_mass() const { return mass; }
    double get_concentrate() const { return conc; }
    unsigned long get_countNucleons() const { return count_nucleons; }
    unsigned long get_atomicNumber() const { return atomic_number;  }

    std::complex<double> get_bc() const { return bc; }
    std::complex<double> get_bi() const { return bi;  }
    std::complex<double> get_sigma_a() const { return sigma_a;  }

    std::complex<double> get_bc_error() const { return bc_error; }
    std::complex<double> get_bi_error() const { return bi_error;  }
    std::complex<double> get_sigma_a_error() const { return sigma_a;  }


    double getCohxs() const { return coh_xs;  }
    double getScatxs() const { return scatt_xs;  }
    double getAbsxs() const { return sigma_a;  }



    Element(QString, unsigned long, unsigned long = 0);
    bool operator==(const Element&) const;
    bool operator!=(const Element&) const;
    // bool operator<(const Element&) const;

};

#endif // ELEMENT_H
