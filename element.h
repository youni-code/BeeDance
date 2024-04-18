#ifndef ELEMENT_H
#define ELEMENT_H
#include <QString>
#include <complex>

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
    std::complex<double> bi_error_;
    double sigma_a_error_;


    bool is_conc;
    bool is_mass;
    bool is_atomic_mass;

    bool is_bc;
    bool is_bi;
    bool is_sigma_a;
    bool is_sigma_i;

public:
    bool is_empty() { return symbol_ == "";};

    void mass(double);
    void concentrate(double co) 				{ conc_ = co; }
    void number(unsigned long atom) 		{ atomic_number_ = atom; }

    void bc(std::complex<double>);
    void bi(std::complex<double>);
    void sigma_a(double);
    void sigma_i(double);

    void bc_err(std::complex<double> value) 	{ bc_error_ = value; }
    void bi_err(std::complex<double> value) 	{ bi_error_ = value; }
    void sigma_a_err(double value) 			{ sigma_a_error_ = value; }


    QString symbol() const { return symbol_; }
    double mass() const { return mass_; }
    double concentrate() const { return conc_; }
    unsigned long nucleons() const { return count_nucleons_; }
    unsigned long number() const { return atomic_number_;  }

    std::complex<double> bc() const { return bc_; }
    std::complex<double> bi() const { return bi_;  }
    double sigma_a() const { return sigma_a_;  }
    double sigma_i() const { return sigma_i_;  }

    std::complex<double> bc_err() const { return bc_error_; }
    std::complex<double> bi_err() const { return bi_error_;  }
    std::complex<double> sigma_a_err() const { return sigma_a_;  }





    Element(QString, unsigned long, unsigned long = 0);
    bool operator==(const Element&) const;
    bool operator!=(const Element&) const;

};

#endif // ELEMENT_H
