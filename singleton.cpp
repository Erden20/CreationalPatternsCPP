#include <iostream>
#include <map>
#include <string>
#include <mutex>
#include <fstream>
using namespace std;

class ConfigurationManager {
private:
    static ConfigurationManager* instance;  
    static std::mutex mtx;                  
    map<string, string> settings;           

    ConfigurationManager() {
        cout << "[ConfigurationManager] Инициализация..." << endl;
    }

public:
    
    ConfigurationManager(const ConfigurationManager&) = delete;
    ConfigurationManager& operator=(const ConfigurationManager&) = delete;

   
    static ConfigurationManager* GetInstance() {
        lock_guard<mutex> lock(mtx);
        if (instance == nullptr) {
            instance = new ConfigurationManager();
        }
        return instance;
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "[Ошибка] Не удалось открыть файл: " << filename << endl;
            return;
        }
        string key, value;
        while (file >> key >> value) {
            settings[key] = value;
        }
        cout << "[OK] Настройки загружены из файла: " << filename << endl;
        file.close();
    }

    
    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (auto& pair : settings) {
            file << pair.first << " " << pair.second << "\n";
        }
        cout << "[OK] Настройки сохранены в файл: " << filename << endl;
        file.close();
    }

    
    void set(const string& key, const string& value) {
        settings[key] = value;
    }

    string get(const string& key) {
        if (settings.find(key) != settings.end())
            return settings[key];
        return "[Не найдено]";
    }

   
    void printAll() {
        cout << "\n=== Текущие настройки ===\n";
        for (auto& s : settings)
            cout << s.first << " = " << s.second << endl;
    }
};


ConfigurationManager* ConfigurationManager::instance = nullptr;
std::mutex ConfigurationManager::mtx;


int main() {
    setlocale(LC_ALL, "Russian");

    ConfigurationManager* config1 = ConfigurationManager::GetInstance();
    config1->set("theme", "dark");
    config1->set("volume", "80");
    config1->saveToFile("settings.txt");

    ConfigurationManager* config2 = ConfigurationManager::GetInstance();
    config2->loadFromFile("settings.txt");
    config2->printAll();

    cout << "\nАдрес config1: " << config1 << endl;
    cout << "Адрес config2: " << config2 << endl;
    cout << "(Одинаковые — Singleton работает)\n";

    return 0;
}
