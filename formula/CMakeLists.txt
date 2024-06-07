add_library(formula
    formula.cpp formula.h
    subformula.cpp subformula.h
    datatablesld.cpp datatablesld.h
    chemicalformulaelement.cpp chemicalformulaelement.h
    element.cpp element.h)
    
    
# target_link_libraries(formula Qt6::Widgets)
target_link_libraries(formula Qt6::Core)
