cmake_minimum_required(VERSION 3.16)

set(QT_VERSION_MAJOR 6)

project(BrickGame VERSION 1.0.0 LANGUAGES CXX C)

# Установим C++ стандарт
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем автоматическую обработку MOC, UIC и RCC файлов
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/brick_game/tetris/Model/Helpers/Model_templates.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Найдем необходимые модули Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

# Отладочная информация
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

# Автоматически найдем все исходные файлы в директории src
file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/brick_game/**/*.cpp"
    "${CMAKE_SOURCE_DIR}/brick_game/**/*.c"
    "${CMAKE_SOURCE_DIR}/gui/desktop/*.cpp"
    "${CMAKE_SOURCE_DIR}/gui/desktop/*.c"
)

# Автоматически найдем все заголовочные файлы в директории include
file(GLOB_RECURSE HEADER_FILES
    "${CMAKE_SOURCE_DIR}/brick_game/**/*.hpp"
    "${CMAKE_SOURCE_DIR}/brick_game/**/*.h"
    "${CMAKE_SOURCE_DIR}/gui/desktop/*.hpp"
    "${CMAKE_SOURCE_DIR}/gui/desktop/*.h"
)

# Автоматически найдем все файлы интерфейсов пользователя
file(GLOB UI_FILES
    "${CMAKE_SOURCE_DIR}/gui/desktop/*.ui"
)

# Создаем исполняемый файл
add_executable(BrickGame_desktop
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${UI_FILES}
    gui/desktop/resource.qrc
)

# Линковка с библиотеками Qt
target_link_libraries(BrickGame_desktop PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)