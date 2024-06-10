#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

// Функция для чтения словаря из файла
std::vector<std::string> readDictionary(const std::string& filename) {
    std::vector<std::string> dictionary;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл словаря: " << filename << std::endl;
        return dictionary;
    }

    std::string word;
    while (std::getline(file, word)) {
        dictionary.push_back(word);
    }

    file.close();
    return dictionary;
}

// Функция для создания частотной карты символов в слове
std::unordered_map<char, int> createFrequencyMap(const std::string& word) {
    std::unordered_map<char, int> freqMap;
    for (char ch : word) {
        ++freqMap[ch];
    }
    return freqMap;
}

// Функция для проверки, можно ли составить слово target из букв слова source
bool canFormWord(const std::string& source, const std::string& target) {
    std::unordered_map<char, int> sourceFreq = createFrequencyMap(source);
    std::unordered_map<char, int> targetFreq = createFrequencyMap(target);

    for (const auto& pair : targetFreq) {
        char ch = pair.first;
        int count = pair.second;
        if (sourceFreq[ch] < count) {
            return false;
        }
    }
    return true;
}

int main() {
    std::string dictionaryFile = "russian_nouns.txt"; // Замените на путь к вашему файлу словаря
    std::string inputWord;

    std::cout << "Введите слово: ";
    std::cin >> inputWord;

    // Чтение словаря
    std::vector<std::string> dictionary = readDictionary(dictionaryFile);

    // Вектор для хранения слов, которые можно составить
    std::vector<std::string> matchingWords;

    // Проверка каждого слова из словаря
    for (const std::string& word : dictionary) {
        if (canFormWord(inputWord, word)) {
            matchingWords.push_back(word);
        }
    }

    // Сортировка найденных слов по длине в порядке убывания
    std::sort(matchingWords.begin(), matchingWords.end(), [](const std::string& a, const std::string& b) {
        return b.length() < a.length();
        });

    // Вывод результатов
    std::cout << "Слова, которые можно составить из \"" << inputWord << "\":" << std::endl;
    for (const std::string& word : matchingWords) {
        std::cout << word << std::endl;
    }

    return 0;
}