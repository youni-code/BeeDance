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
    std::complex<double> coh_b;
    std::complex<double> inc_b;
    double coh_xs;
    double inc_xs;
    double scatt_xs;
    double abs_xs;


    bool is_isotope; // является ли элемент изотопом или суммарный химический элемент

    bool is_conc;
    bool is_atomic_number;
    bool is_coh_b;
    bool is_coh_xs;
    bool is_inc_b;
    bool is_inc_xs;
    bool is_scatt_xs;
    bool is_abs_xs;
    bool is_mass;

    void initialize();

public:

    bool setMass(double);
    bool setConc(double);
    bool setAtomicNumber(unsigned long);
    bool setCohb(std::complex<double>);
    bool setIncb(std::complex<double>);
    bool setCohxs(double);
    bool setIncxs(double);
    bool setScattxs(double);
    bool setAbsxs(double);

    QString getSymbol() const;
    double getMass() const;
    double getConc() const;
    unsigned long getCountNucleons() const;
    unsigned long getAtomicNumber() const;
    std::complex<double> getCohb() const;
    std::complex<double> getIncb() const;
    double getCohxs() const;
    double getScatxs() const;
    double getAbsxs() const;

    bool isConc() const;
    bool isIsotope() const;
    bool isCohb() const;
    bool isIncb() const;
    bool isCohxs() const;
    bool isInxs() const;
    bool isScattxs() const;
    bool isAbsxs() const;
    bool isMass() const;


    Element(QString, unsigned long, unsigned long = 0);
    bool operator<(const Element&) const;

};

#endif // ELEMENT_H
