#include <string>
#include <fstream>
#include <iostream>

void print(const std::string& text, std::ostream& out = std::cout); //выводит файлы в стандартный поток
void print(const std::string& text, std::ofstream& out); //выводит файлы в файл
