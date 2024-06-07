add_library(resultwidget
    resultswidget.h resultswidget.cpp
    resultline.h resultline.cpp)
target_link_libraries(resultwidget Qt6::Widgets)


add_library(inputwidget
    inputwidget.h inputwidget.cpp
    chemicaltextedit.h chemicaltextedit.cpp
    chemicallabel.h chemicallabel.cpp)
target_link_libraries(inputwidget Qt6::Widgets)
