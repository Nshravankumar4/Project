cmake_minimum_required(VERSION 3.16)
project(AutomotiveCluster VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6 or Qt5
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick Gui Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Gui Network)

set(CLUSTER_SOURCES
    src/main.cpp
    src/viewmodels/ClusterViewModel.cpp
    src/viewmodels/ClusterViewModel.h
    src/services/CanSimulator.cpp
    src/services/CanSimulator.h
)

set(md_files
    CMakeLists.txt.md
    src/main.cpp.md
    src/VehicleServiceMain.cpp.md
    src/services/CanSimulator.cpp.md
    src/services/CanSimulator.h.md
    src/services/MockCanServer.cpp.md
    src/services/MockCanServer.h.md
    src/viewmodels/ClusterViewModel.cpp.md
    src/viewmodels/ClusterViewModel.h.md
    qml/main.qml.md
    qml/Speedometer.qml.md
)

set(SERVICE_SOURCES
    src/VehicleServiceMain.cpp
    src/services/MockCanServer.cpp
    src/services/MockCanServer.h
)

# Qt6/Qt5 specific target setup
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    # 1. Automotive Cluster (GUI Client)
    qt_add_executable(AutomotiveCluster
        MANUAL_FINALIZATION
        ${CLUSTER_SOURCES}
        ${md_files}
    )
    
    # QML files
    set(QML_FILES
        qml/main.qml
        qml/Speedometer.qml
    )
    
    if(COMMAND qt_policy)
        qt_policy(SET QTP0001 NEW)
        qt_policy(SET QTP0004 OLD)
    endif()

    qt_add_qml_module(AutomotiveCluster
        URI ClusterApp
        VERSION 1.0
        QML_FILES ${QML_FILES}
    )

    qt_import_qml_plugins(AutomotiveCluster)
    qt_finalize_executable(AutomotiveCluster)
    
    # 2. Vehicle Service (Background IPC Server)
    qt_add_executable(VehicleService ${SERVICE_SOURCES})

else()
    # Qt5 alternative
    add_executable(AutomotiveCluster ${CLUSTER_SOURCES} ${md_files})
    target_link_libraries(AutomotiveCluster PRIVATE Qt5::Core Qt5::Quick Qt5::Gui Qt5::Network)
    
    add_executable(VehicleService ${SERVICE_SOURCES})
    target_link_libraries(VehicleService PRIVATE Qt5::Core Qt5::Network)
endif()

# Link Libraries
target_link_libraries(AutomotiveCluster PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Network
)

target_link_libraries(VehicleService PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
)

