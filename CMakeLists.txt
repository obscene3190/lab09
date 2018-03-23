cmake_minimum_required(VERSION 3.0) // Указывает последнюю доступную вам версию CMake.

set(CMAKE_CXX_STANDARD 11) // Set a CMake, cache or environment variable to a given value.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EXAMPLES "Build examples" OFF)

project(print) // project(<имя> VERSION <версия> LANGUAGES CXX) Set a name, version, and enable languages for the entire project.

add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp) // Добавляем цель - статическую библиотеку | Add a library to the project using the specified source files.

target_include_directories(print PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
) //добавления путей поиска заголовков, от которых зависит цель | Add include directories to a target.

if(BUILD_EXAMPLES)
  file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp") //Выводит типы указанных файлов | File manipulation command.
  foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES}) //Evaluate[оценивает] a group of commands for each value in a list.
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE) // Get a specific component of a full filename.
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE}) //Синтаксис: add_executable(<имя> <список исходников...>), целью является исполняемый файл, Add an executable to the project using the specified source files. 
    target_link_libraries(${EXAMPLE_NAME} print) // используется  для добавления статических и динамических библиотек, от которых зависит цель
    install(TARGETS ${EXAMPLE_NAME}
      RUNTIME DESTINATION bin
    ) //This command generates installation rules for a project. Executables[исполняемые файлы] are treated[рассматриваются] as RUNTIME
  endforeach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
endif()

install(TARGETS print
    EXPORT print-config
    ARCHIVE DESTINATION lib // Specify the directory on disk to which a file will be installed
    LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)
install(EXPORT print-config DESTINATION cmake)
