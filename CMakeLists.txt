cmake_minimum_required(VERSION 3.16)

project(meu_estoque VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Quick Sql Concurrent Qml QuickControls2 REQUIRED)

qt_add_executable(appmeu_estoque
    main.cpp
    entity/item.h entity/item.cpp
    use_case/getestoqueusecase.h use_case/getestoqueusecase.cpp
    use_case/cadastrodeitemusecase.h use_case/cadastrodeitemusecase.cpp
    use_case/setitemvolumeusecase.h use_case/setitemvolumeusecase.cpp
    data/databaseconnection.h data/databaseconnection.cpp
    data/database/database.h data/database/database.cpp
    data/mapper/itemmapper.h data/mapper/itemmapper.cpp
    data/repository/estoquerepository.h data/repository/estoquerepository.cpp
    model/estoquemodel.h model/estoquemodel.cpp
)

qt_add_qml_module(appmeu_estoque
    URI meu_estoque
    VERSION 1.0
    QML_FILES
    main.qml
    qml/components/Card.qml
    qml/components/ItemVolumeController.qml
    qml/screens/HomeScreen.qml
    qml/screens/AddItemScreen.qml
    SOURCES model/estoquemodel.h model/estoquemodel.cpp
)

set_target_properties(appmeu_estoque PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appmeu_estoque
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appmeu_estoque
    PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Sql
    Qt6::Concurrent
    Qt6::Qml
    Qt6::QuickControls2
)
