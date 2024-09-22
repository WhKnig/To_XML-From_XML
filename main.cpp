#include <iostream>
#include <algorithm>
#include "xml.h"

int main() {
    Vocab exp;
    int n;
    while (true) {
        try {
            n = Vocab::get_main();
            switch (n) {
                case 1:
                    exp.to_xml();
                    break;
                case 2:
                    exp.from_xml();
                    break;
                case 3:
                    return 0;
                default:
                    std::cout << "No such point\n";
            }
        }
        catch (const std::bad_alloc &ba) {
            std::cerr << "Not enough memory" << std::endl;
            exp.erase();
            std::cin.clear();
        }
        catch (NullException e) {
            std::cout << "Exp is null!\n";
            std::cin.clear();
        }
        catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
            std::cin.clear();
        }
    }
}