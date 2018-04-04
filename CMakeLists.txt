cmake_minimum_required(VERSION 3.0) # Указывает последнюю доступную вам версию CMake.

set(CMAKE_CXX_STANDARD 11) # Устанавливает значение переменных CMake cache и enviroment на указанные значения
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTS "Build tests" OFF)

project(print) # project(<имя> VERSION <версия> LANGUAGES CXX) Устанавливает имя, версию и язык для проекта

add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp) # Добавляем статическую библиотеку, используя указанный ресурс

target_include_directories(print PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
) #добавление каталогов для цели

if(BUILD_EXAMPLES)
  file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp") #Выводит типы указанных файлов
  foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES}) # Оценивает группу команд для каждого значения в списке.
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE) # Получение компонента из полного имени файла
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE}) #Синтаксис: add_executable(<имя> <список исходников...>), добавляет исполняемый файл из указанного источника 
    target_link_libraries(${EXAMPLE_NAME} print) # используется  для добавления статических и динамических библиотек, от которых зависит цель
    install(TARGETS ${EXAMPLE_NAME}
      RUNTIME DESTINATION bin
    ) # Генерирует правила установки для проекта.
  endforeach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
endif()

install(TARGETS print
    EXPORT print-config
    ARCHIVE DESTINATION lib # Указывает директорию на диске ,куда будет установлен файл
    LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)
install(EXPORT print-config DESTINATION cmake)
if(BUILD_TESTS)
enable_testing()
file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
target_link_libraries(check ${PROJECT_NAME} ${DEPENDS_LIBRARIES})
add_test(NAME check COMMAND check "-s" "-r" "compact" "--use-colour" "yes") 
endif()
