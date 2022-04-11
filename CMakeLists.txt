cmake_minimum_required(VERSION 3.16)
project(jaqubsuite)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Find the QtWidgets library
find_package(Qt5Core REQUIRED)

find_package(Qt5Widgets CONFIG REQUIRED)

find_package(KF5 "5.86.0" REQUIRED COMPONENTS
    CoreAddons
    I18n
    XmlGui
    Completion
    ItemModels
    ItemViews
    Service
    ConfigWidgets
    TextWidgets
    Notifications
)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)



set(jaqubsuite_SRC
  src/main.cpp
  src/jaqubsuite.cpp
  src/connection_dialog.cpp
  src/connection_chat_window.cpp
  src/connection_postal_window.cpp

)

include_directories(${CMAKE_INSTALL_PREFIX}/include/jaqubsuite)
# Tell CMake to create the helloworld executable
add_executable(jaqubsuite ${jaqubsuite_SRC})
# Use the Widgets module from Qt 5.
target_link_libraries(jaqubsuite  
    jaqubsuite_pa
    Qt5::Widgets 
    KF5::XmlGui 
    KF5::I18n 
    KF5::CoreAddons 
    KF5::Completion 
    KF5::TextWidgets 
    KF5::ItemModels 
    KF5::ItemViews
    KF5::ConfigWidgets
    KF5::Notifications

)

# Install the executable
install(TARGETS jaqubsuite DESTINATION bin)

install(FILES jaqubsuite.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
install(FILES src/JaqubSuiteui.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/jaqubsuite)
install(FILES jaqubsuite.notifyrc DESTINATION ${KNOTIFYRC_INSTALL_DIR})
