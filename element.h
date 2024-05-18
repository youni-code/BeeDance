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

    double bc_;
    double bi_;
    double bc_error_;
    double bi_error_;

    std::complex<double> bc_comp_;
    std::complex<double> bi_comp_;
    std::complex<double> bc_comp_error_;
    std::complex<double> bi_comp_error_;

    double sigma_a_;
    double sigma_i_;
    double sigma_a_error_;
    double sigma_i_error_;

    bool is_conc_;
    bool is_mass_;
    bool is_atomic_mass_;

    bool is_bc_;
    bool is_bi_;
    bool is_sigma_a_;
    bool is_sigma_i_;

public:
    bool is_empty() const { return symbol_ == ""; }

    void mass(double);
    void concentrate(double co) 				{ conc_ = co; is_conc_ = true; }
    void number(unsigned long atom) 		{ atomic_number_ = atom; is_atomic_mass_ = true; }

    void bc_comp(std::complex<double>);
    void bi_comp(std::complex<double>);

    void sigma_a(double);
    void sigma_a_err(double value) 			{ sigma_a_error_ = value; }

    void sigma_i(double);
    void sigma_i_err(double value) 			{ sigma_i_error_ = value; }

    void bc_comp_err(std::complex<double> value) 	{ bc_comp_error_ = value; }
    void bi_comp_err(std::complex<double> value) 	{ bi_comp_error_ = value; }


    QString symbol()            const { return symbol_; }
    double mass()               const { return mass_; }
    double concentrate()        const { return conc_; }
    unsigned long nucleons()    const { return count_nucleons_; }
    unsigned long number()      const { return atomic_number_;  }

    std::complex<double> bc_comp() const { return bc_comp_; }
    std::complex<double> bi_comp() const { return bi_comp_;  }

    double sigma_a() const { return sigma_a_;  }
    double sigma_i() const { return sigma_i_;  }

    std::complex<double> bc_comp_err()  const { return bc_comp_error_; }
    std::complex<double> bi_comp_err()  const { return bi_comp_error_;  }
    double sigma_a_err()                const { return sigma_a_error_;  }
    double sigma_i_err()                const { return sigma_i_error_;  }

    bool is_mass()      const { return is_mass_; }
    bool is_sigma_a()   const { return is_sigma_a_; }
    bool is_sigma_i()   const { return is_sigma_i_; }
    bool is_bc()        const { return is_bc_; }
    bool is_bi()        const { return is_bi_; }



    Element(QString, unsigned long, unsigned long = 0);
    Element() : Element("", 0) { }
    bool operator==(const Element&) const;
    bool operator!=(const Element&) const;

};

#endif // ELEMENT_H
