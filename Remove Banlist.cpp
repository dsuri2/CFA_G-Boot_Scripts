#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio> // for std::remove and std::rename

bool shouldRemoveLine(const std::string& line) {
    // Trim leading whitespace
    size_t start = line.find_first_not_of(" \t");
    if (start == std::string::npos) return false;

    std::string trimmed = line.substr(start);

    // Remove lines starting with (PREMIUM or (STANDARD
    if (trimmed.find("(PREMIUM") == 0 || trimmed.find("(STANDARD") == 0)
        return true;

    // Remove line if it is limited
    if (trimmed.find("global.CardLimidet[CardStat] = 1") != std::string::npos)
        return true;

     // Remove line if it is banned
     if (trimmed.find("global.CardBanned[CardStat] = 1") != std::string::npos)
     return true;

    return false;
}

void cleanFile(const std::string& filePath) {
    std::ifstream in(filePath.c_str());
    if (!in) {
        std::cerr << "Error: Could not open " << filePath << "\n";
        return;
    }

    std::string tempPath = filePath + ".tmp";
    std::ofstream out(tempPath.c_str());
    if (!out) {
        std::cerr << "Error: Could not write to temp file.\n";
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (!shouldRemoveLine(line)) {
            out << line << "\n";
        }
    }

    in.close();
    out.close();

    std::remove(filePath.c_str());
    std::rename(tempPath.c_str(), filePath.c_str());

    std::cout << "Cleaned: " << filePath << "\n";
}

int main() {
    std::vector<std::string> files = {
        "Kagero.txt",
        "Tachikaze.txt",
        "Narukami.txt",
        "Murakumo.txt",
        "Nubatama.txt",
        "Dark Irregulars.txt",
        "Spike Brothers.txt",
        "Pale Moon.txt",
        "Gear Chronicle.txt",
        "Shadow Paladin.txt",
        "Gold Paladin.txt",
        "Oracle.txt",
        "Royal Paladin.txt",
        "Anger Feather.txt",
        "Genesis.txt",
        "Megacolony.txt",
        "Great Nature.txt",
        "Neo Nectar.txt",
        "Aqua Force.txt",
        "Granblue.txt",
        "Bermuda.txt",
        "Nova Grappler.txt",
        "Dimension Police.txt",
        "Link Joker.txt",
        "Cray Elemental.txt"
    };

    for (size_t i = 0; i < files.size(); ++i) {
        cleanFile(files[i]);
    }

    return 0;
}
