#ifndef ELEMENT_H
#define ELEMENT_H
#include <QString>
#include <complex>
#include <QDebug>

class Element
{
    QString symbol_;
    unsigned long count_nucleons_;

    double conc_;
    double mass_;
    long atomic_number_;

    std::complex<double> bc_;
    std::complex<double> bi_;
    double sigma_a_;
    double sigma_i_;

    std::complex<double> bc_error_;
    std::complex<double> bi_error;
    double sigma_a_error;


    bool is_conc;
    bool is_mass;
    bool is_atomic_mass;

    bool is_bc;
    bool is_bi;
    bool is_sigma_a;
    bool is_sigma_i;

public:
    bool is_empty() { return symbol_ == "";};

    void set_mass(double);
    void set_concentrate(double co) 				{ conc_ = co; }
    void set_atomic_number(unsigned long atom) 		{ atomic_number_ = atom; }

    void set_bc(std::complex<double>);
    void set_bi(std::complex<double>);
    void set_sigmaa(double);
    void set_sigmai(double);

    void set_bc_error(std::complex<double> value) 	{ bc_error_ = value; }
    void set_bi_error(std::complex<double> value) 	{ bi_error = value; }
    void set_sigmaa_error(double value) 			{ sigma_a_error = value; }


    QString get_symbol() const { return symbol_; }
    double get_mass() const { return mass_; }
    double get_concentrate() const { return conc_; }
    unsigned long get_countNucleons() const { return count_nucleons_; }
    unsigned long get_atomicNumber() const { return atomic_number_;  }

    std::complex<double> get_bc() const { return bc_; }
    std::complex<double> get_bi() const { return bi_;  }
    std::complex<double> get_sigma_a() const { return sigma_a_;  }

    std::complex<double> get_bc_error() const { return bc_error_; }
    std::complex<double> get_bi_error() const { return bi_error;  }
    std::complex<double> get_sigma_a_error() const { return sigma_a_;  }


    Element(QString, unsigned long, unsigned long = 0);
    bool operator==(const Element&) const;
    bool operator!=(const Element&) const;

};

#endif // ELEMENT_H
