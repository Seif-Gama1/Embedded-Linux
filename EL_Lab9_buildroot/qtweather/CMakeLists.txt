cmake_minimum_required(VERSION 3.16)

project(Weather_app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appWeather_app
    main.cpp
)

set(CMAKE_AUTORCC ON)

qt_add_qml_module(appWeather_app
    URI Weather_app
    QML_FILES
        Main.qml
        WeatherDetailItem.qml
        HourlyForecastDelegate.qml
    RESOURCES
        background.jpg
        air.png
        fog.png
        heavy-rain.png
        humidity.png
        rainy.png
        windy.png
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appWeather_app PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appWeather_app
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appWeather_app
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)

install(TARGETS appWeather_app
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
