#include <string>
#include <fstream>
#include <iostream>

void print(const std::string& text, std::ostream& out = std::cout); //выводит текст в стандартный поток
void print(const std::string& text, std::ofstream& out); //выводит текст в файл
