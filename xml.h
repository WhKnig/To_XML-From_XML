// func.h
#pragma once
#include <string>
#include <limits>

/// @brief Исключение для случая, когда объект пустой
class NullException {};

/// @brief Основной класс программы для работы с XML и словарем
class Vocab
{
private:
    /// @brief Структура для хранения слова, его значения и выделения
    struct Vcb {
        char *word;          ///< Указатель на слово (макс. 20 символов)
        std::string meaning; ///< Значение слова
        unsigned emp;        ///< Выделение (положение важного символа в слове)
    };

    Vcb thing; ///< Экземпляр структуры Vcb, хранит текущее слово

public:
    /// @brief Конструктор по умолчанию
    Vocab();

    /// @brief Деструктор, освобождает выделенную память
    ~Vocab();

    /// @brief Основное меню программы
    /// @return Возвращает выбранный пользователем пункт меню
    static int get_main();

    /// @brief Формирует XML-строку из структуры Vcb и имени узла
    /// @param exp Структура Vcb
    /// @param name Имя узла XML в виде строки
    /// @return XML-представление структуры Vcb
    std::string get_xml(const Vcb& exp, const std::string& name);

    /// @brief Формирует XML-строку из структуры Vcb и имени узла
    /// @param exp Структура Vcb
    /// @param name Указатель на строку с именем узла XML
    /// @param nameLength Длина строки имени
    /// @return XML-представление структуры Vcb
    std::string to_xml(const Vcb& exp, const char* name, size_t nameLength);

    /// @brief Формирует XML-строку из структуры Vcb и имени узла
    /// @param exp Структура Vcb
    /// @param name Указатель на строку с именем узла XML
    /// @return XML-представление структуры Vcb
    std::string to_xml(const Vcb& exp, const char* name);

    /// @brief Формирует XML-строку из структуры Vcb и имени узла
    /// @param exp Структура Vcb
    /// @param name Имя узла XML в виде строки
    /// @return XML-представление структуры Vcb
    std::string to_xml(const Vcb& exp, const std::string& name);

    /// @brief Извлекает структуру Vcb из строки XML
    /// @param xml Строка XML
    /// @return Структура Vcb
    static Vocab::Vcb get_exp(const std::string& xml);

    /// @brief Извлекает структуру Vcb из строки XML
    /// @param xml Указатель на строку XML
    /// @param xmlLen Длина строки XML
    /// @return Структура Vcb
    static Vocab::Vcb from_xml(const char* xml, size_t xmlLen);

    /// @brief Извлекает структуру Vcb из строки XML
    /// @param xml Указатель на строку XML
    /// @return Структура Vcb
    static Vocab::Vcb from_xml(const char* xml);

    /// @brief Извлекает структуру Vcb из строки XML
    /// @param xml Строка XML
    /// @return Структура Vcb
    static Vocab::Vcb from_xml(const std::string& xml);

    /// @brief Генерирует XML из текущих данных
    void to_xml();

    /// @brief Загружает данные из XML
    void from_xml();

    /// @brief Очищает текущие данные
    void erase();
};
