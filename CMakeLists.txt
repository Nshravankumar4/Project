cmake_minimum_required(VERSION 3.16)
project(AutomotiveCluster VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Quick Gui Network)

# -------------------------------------------------------------
# TARGET 1: The Automotive Cluster (GUI Client)
# -------------------------------------------------------------
set(CLUSTER_SOURCES
    src/main.cpp
    src/viewmodels/ClusterViewModel.cpp
    src/viewmodels/ClusterViewModel.h
    src/services/CanSimulator.cpp
    src/services/CanSimulator.h
    src/utils/Logger.h
)

qt_add_executable(AutomotiveCluster MANUAL_FINALIZATION ${CLUSTER_SOURCES})

# Embed all QML files into the executable
if(COMMAND qt_policy)
    qt_policy(SET QTP0001 NEW)
    qt_policy(SET QTP0004 OLD)
endif()

qt_add_qml_module(AutomotiveCluster
    URI ClusterApp
    VERSION 1.0
    QML_FILES
        qml/main.qml
        qml/DialGauge.qml
        qml/AdasCenter.qml
        qml/Telltales.qml
        qml/InfoMenu.qml
        qml/AlertPopup.qml
)

target_link_libraries(AutomotiveCluster PRIVATE Qt6::Core Qt6::Quick Qt6::Gui Qt6::Network)
qt_import_qml_plugins(AutomotiveCluster)
qt_finalize_executable(AutomotiveCluster)

# -------------------------------------------------------------
# TARGET 2: The Vehicle Service (IPC Hardware Daemon Server)
# -------------------------------------------------------------
set(SERVICE_SOURCES
    src/VehicleServiceMain.cpp
    src/services/MockCanServer.cpp
    src/services/MockCanServer.h
)

qt_add_executable(VehicleService ${SERVICE_SOURCES})
target_link_libraries(VehicleService PRIVATE Qt6::Core Qt6::Network)

# -------------------------------------------------------------
# TARGET 3: Documentation (So .md files show up in Qt Creator)
# -------------------------------------------------------------
set(DOC_FILES
    README.md
    docs/AdasCenter.qml.md
    docs/AlertPopup.qml.md
    docs/CanSimulator.cpp.md
    docs/CanSimulator.h.md
    docs/ClusterViewModel.cpp.md
    docs/ClusterViewModel.h.md
    docs/DialGauge.qml.md
    docs/InfoMenu.qml.md
    docs/Logger.h.md
    docs/main.cpp.md
    docs/main.qml.md
    docs/MockCanServer.cpp.md
    docs/MockCanServer.h.md
    docs/Telltales.qml.md
    docs/VehicleServiceMain.cpp.md
)
add_custom_target(StudyGuides SOURCES ${DOC_FILES})
