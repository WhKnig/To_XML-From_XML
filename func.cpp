#include <iostream>
#include <regex>
#include <limits>
#include <cstring>
#include <algorithm>
#include "xml.h"


Vocab::Vocab() : thing({nullptr, "", 0}) {}

Vocab::~Vocab() {
    erase();
}

int Vocab::get_main()
{
    int n;
    while (true) {
        std::cout << "1. To XML\n";
        std::cout << "2. From XML\n";
        std::cout << "3. Exit\n";
        std::cout << "-> ";
        std::cin >> n;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please enter a number.\n";
            continue;
        }
        else if (std::cin.eof()) {
            std::cin.clear();
            n = 3;
            break;
        }
        break;
    }
    return n;
}

void Vocab::erase() {
    if (thing.word != nullptr) {
        delete[] thing.word;
        thing.word = nullptr;
    }
    thing.meaning.clear();
    thing.emp = 0;
}

template <class T>
T getNum(T min, T max) {
    T a;
    while (true) {
        std::cin >> a;

        if (std::cin.eof())
            throw std::runtime_error("EOF detected. Exiting...");
        else if (std::cin.bad())
            throw std::runtime_error("Stream error during input");
        else if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input; please enter a valid number!" << std::endl;
        } else if (a < min || a > max) {
            std::cout << "Number is out of range (" << min << " - " << max << "); please enter again!" << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return a;
        }
    }
}

std::string Vocab::to_xml(const Vcb& exp, const char* name, size_t nameLength) {
    std::string nameStr(name, nameLength);
    std::string xml = get_xml(exp, nameStr);
    return xml;
}

std::string Vocab::to_xml(const Vcb& exp, const char* name) {
    std::string xml = get_xml(exp, std::string(name));
    return xml;
}

std::string Vocab::to_xml(const Vcb& exp, const std::string& name) {
    std::string xml = get_xml(exp, name);
    return xml;
}


std::string Vocab::get_xml(const Vcb& exp, const std::string& name) {
    std::string xml = "<" + name + ">";
    xml += "<word>" + std::string(thing.word) + "</word>";
    xml += "<meaning>" + thing.meaning + "</meaning>";
    xml += "<emphasis>" + std::to_string(thing.emp) + "</emphasis>";
    xml += "</" + name + ">\n";
    return xml;
}


int select_pereg() {
    int n;
    while (true) {
        std::cout << "1. Char *\n";
        std::cout << "2. Char + size_t\n";
        std::cout << "3. String\n";
        std::cout << "-> ";
        std::cin >> n;

        if (std::cin.eof()) {
            std::cin.clear();
            std::cout << "EOF detected, exiting...\n";
            exit(0);
        }

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please enter a number.\n";
            continue;
        }
        break;
    }
    return n;
}


void Vocab::to_xml() {
    if (thing.word != nullptr || !thing.meaning.empty()) {
        erase();
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string temp;

    std::cout << "Input word: ";
    if (!std::getline(std::cin, temp)) {
        if (std::cin.eof()) {
            std::cout << "EOF detected, exiting...\n";
            exit(0);
        }
        std::cerr << "Error reading word input!" << std::endl;
        return;
    }

    while (temp.length() > 20) {
        std::cout << "Not more than 20 symbols!!!\n";
        std::cout << "Input word: ";
        if (!std::getline(std::cin, temp)) {
            std::cerr << "Error reading word input!" << std::endl;
            return;
        }
    }

    thing.word = new char[temp.length() + 1];
    std::strcpy(thing.word, temp.c_str());

    std::cout << "Input meaning: ";
    if (!std::getline(std::cin, thing.meaning)) {
        std::cerr << "Error reading meaning input!" << std::endl;
        return;
    }

    std::cout << "Input emphasis: ";
    try {
        thing.emp = getNum<unsigned>(1, std::strlen(thing.word));
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return;
    }

    std::cout << "Input name: ";
    std::string name;
    if (!std::getline(std::cin, name)) {
        std::cerr << "Error reading name input!" << std::endl;
        return;
    }

    std::string xml = {};
    int n = select_pereg();
    switch (n) {
        case 1: {
            char* name2 = new char[name.length() + 1];
            std::strcpy(name2, name.c_str());
            xml = to_xml(thing, name2);
            delete[] name2;
            break;
        }
        case 2: {
            char* name1 = new char[name.length() + 1];
            std::strcpy(name1, name.c_str());
            size_t nl = name.length();
            xml = to_xml(thing, name1, nl);
            delete[] name1;
            break;
        }
        case 3: {
            xml = to_xml(thing, name);
            break;
        }
        default:
            std::cout << "No such point\n";
            break;
    }

    if (!xml.empty()) {
        std::cout << "\n\nGenerated XML:\n" << xml << std::endl;
    }
}

Vocab::Vcb Vocab::from_xml(const char* xml, size_t xmlLen)
{
    std::string tp_xml(xml, xmlLen);

    std::transform(tp_xml.begin(), tp_xml.end(), tp_xml.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    Vocab::Vcb temp = get_exp(tp_xml);
    return temp;
}

Vocab::Vcb Vocab::from_xml(const char* xml)
{
    std::string tp_xml(xml);
    std::transform(tp_xml.begin(), tp_xml.end(), tp_xml.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    Vocab::Vcb temp = get_exp(tp_xml);
    return temp;
}

Vocab::Vcb Vocab::from_xml(const std::string& xml)
{
    std::string tp_xml = xml;
    std::transform(tp_xml.begin(), tp_xml.end(), tp_xml.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    Vocab::Vcb temp = get_exp(tp_xml);
    return temp;
}

Vocab::Vcb Vocab::get_exp(const std::string& xml) {
    Vocab::Vcb temp;
    std::regex xmlPattern(R"(<(\w+)>\s*<word>([^<]+)</word>\s*<meaning>([^<]+)</meaning>\s*<emphasis>(\d+)</emphasis>\s*</\1>)");

    std::smatch matches;
    if (std::regex_search(xml, matches, xmlPattern)) {
        std::string word = matches[2].str();
        std::string meaning = matches[3].str();
        unsigned emphasis = std::stoi(matches[4].str());

        temp.word = new char[word.length() + 1];
        std::strcpy(temp.word, word.c_str());
        temp.meaning = meaning;
        temp.emp = emphasis;
    } else {
        std::cout << "Invalid XML format.\n";
    }

    return temp;
}

void Vocab::from_xml() {
    if (!thing.meaning.empty() || thing.word != nullptr) {
        erase();
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Input XML-string (without new line symbols): ";
    std::string xml;
    if (!std::getline(std::cin, xml)) {
        if (std::cin.eof()) {
            std::cout << "EOF detected, exiting...\n";
            exit(0);
        }
        std::cerr << "Error reading XML input!" << std::endl;
        return;
    }


    thing = {nullptr, "", 0};

    int n = select_pereg();

    switch (n) {
        case 1: {
            char* xml2 = new char[xml.length() + 1];
            std::strcpy(xml2, xml.c_str());
            thing = from_xml(xml2);
            delete[] xml2;
            break;
        }
        case 2: {
            char* xml1 = new char[xml.length() + 1];
            std::strcpy(xml1, xml.c_str());
            size_t nl = xml.length();
            thing = from_xml(xml1, nl);
            delete[] xml1;
            break;
        }
        case 3: {
            thing = from_xml(xml);
            break;
        }
        default:
            std::cout << "No such point\n";
            break;
    }

    if (thing.word == nullptr || thing.meaning.empty() || thing.emp == 0) {
        std::cout << "Error parsing XML or uninitialized value.\n";
        return;
    }

    std::cout << "Parsed XML successfully!\n";
    std::cout << "Word: " << thing.word << "\n";
    std::cout << "Meaning: " << thing.meaning << "\n";
    std::cout << "Emphasis: " << thing.emp << "\n";
}

