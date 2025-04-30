#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cstdio> // for std::remove and std::rename

// Convert an integer to a string without using std::to_string (for older versions of C++)
std::string intToString(int num) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d", num);
    return std::string(buffer);
}

// Generate replacements for global.CardInClan[CardStat]
std::vector<std::pair<std::string, std::string>> generateReplacements() {
    std::vector<std::pair<std::string, std::string>> replacements;

    // Auto-generated mappings
    std::vector<std::pair<int, int>> idMappings = {
        {107, 12}, {109, 17}, {111, 19}, {110, 20}, {108, 23},
        {116, 11}, {115, 14}, {117, 18}, {118, 26}, {104, 1},
        {105, 5},  {102, 10}, {101, 15}, {103, 16}, {106, 21},
        {122, 2},  {123, 7},  {124, 9},  {121, 3},  {119, 8},
        {120, 13}, {112, 4},  {113, 6},  {114, 24}, {100, 25}
    };

    // Using a regular loop instead of structured bindings
    for (size_t i = 0; i < idMappings.size(); ++i) {
        int from = idMappings[i].first;
        int to = idMappings[i].second;
        std::string find = "global.CardInClan[CardStat] = " + intToString(from);
        std::string replace = "global.CardInClan[CardStat] = " + intToString(to);
        replacements.push_back(std::make_pair(find, replace));
    }

    // Manual additions for special cases
    // United Sanctuary
    replacements.push_back(std::make_pair("global.CardInClan2[CardStat] = 102", "global.CardInClan2[CardStat] = 10"));
    replacements.push_back(std::make_pair("global.CardInClan3[CardStat] = 103", "global.CardInClan3[CardStat] = 16"));
    replacements.push_back(std::make_pair("global.CardInClan4[CardStat] = 104", "global.CardInClan4[CardStat] = 1"));
    replacements.push_back(std::make_pair("global.CardInClan5[CardStat] = 105", "global.CardInClan5[CardStat] = 5"));
    replacements.push_back(std::make_pair("global.CardInClan6[CardStat] = 106", "global.CardInClan6[CardStat] = 21"));

    // Dark Zone
    replacements.push_back(std::make_pair("global.CardInClan2[CardStat] = 116", "global.CardInClan2[CardStat] = 11"));
    replacements.push_back(std::make_pair("global.CardInClan3[CardStat] = 117", "global.CardInClan3[CardStat] = 18"));
    replacements.push_back(std::make_pair("global.CardInClan4[CardStat] = 118", "global.CardInClan4[CardStat] = 26"));

    // Star Gate
    replacements.push_back(std::make_pair("global.CardInClan2[CardStat] = 113", "global.CardInClan2[CardStat] = 6"));
    replacements.push_back(std::make_pair("global.CardInClan3[CardStat] = 114", "global.CardInClan3[CardStat] = 24"));

    // Zoo
    replacements.push_back(std::make_pair("global.CardInClan2[CardStat] = 123", "global.CardInClan2[CardStat] = 7"));
    replacements.push_back(std::make_pair("global.CardInClan3[CardStat] = 124", "global.CardInClan3[CardStat] = 9"));

    // Dragon Empire
    replacements.push_back(std::make_pair("global.CardInClan2[CardStat] = 108", "global.CardInClan2[CardStat] = 23"));
    replacements.push_back(std::make_pair("global.CardInClan3[CardStat] = 109", "global.CardInClan3[CardStat] = 17"));
    replacements.push_back(std::make_pair("global.CardInClan4[CardStat] = 110", "global.CardInClan4[CardStat] = 20"));
    replacements.push_back(std::make_pair("global.CardInClan5[CardStat] = 111", "global.CardInClan5[CardStat] = 19"));

    // Magallanica
    replacements.push_back(std::make_pair("global.CardInClan2[CardStat] = 120", "global.CardInClan2[CardStat] = 13"));
    replacements.push_back(std::make_pair("global.CardInClan3[CardStat] = 121", "global.CardInClan3[CardStat] = 3"));

    return replacements;
}

// Replace lines in-place using a temporary file
void findAndReplaceInPlace(const std::string& inputFile,
                           const std::vector<std::pair<std::string, std::string>>& replacements) {
    std::ifstream in(inputFile);
    if (!in) {
        std::cerr << "Error: Cannot open " << inputFile << " for reading.\n";
        return;
    }

    std::string tempFile = inputFile + ".tmp";
    std::ofstream out(tempFile);
    if (!out) {
        std::cerr << "Error: Cannot open temp file for writing.\n";
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        for (size_t i = 0; i < replacements.size(); ++i) {
            const std::string& toFind = replacements[i].first;
            const std::string& toReplace = replacements[i].second;

            size_t pos = 0;
            while ((pos = line.find(toFind, pos)) != std::string::npos) {
                line.replace(pos, toFind.length(), toReplace);
                pos += toReplace.length();
            }
        }
        out << line << "\n";
    }

    in.close();
    out.close();

    // Overwrite original file
    if (std::remove(inputFile.c_str()) != 0) {
        std::cerr << "Error: Could not remove original file " << inputFile << "\n";
        return;
    }
    if (std::rename(tempFile.c_str(), inputFile.c_str()) != 0) {
        std::cerr << "Error: Could not rename temp file to original name\n";
        return;
    }

    std::cout << "Modified: " << inputFile << "\n";
}

int main() {
    std::vector<std::string> files = {
        "Kagero EX.txt",
    "Tachikaze EX.txt",
    "Narukami EX.txt",
    "Murakumo EX.txt",
    "Nubatama EX.txt",
    "Dark Irregulars EX.txt",
    "Spike Brothers EX.txt",
    "Pale Moon EX.txt",
    "Gear Chronicle EX.txt",
    "Shadow Paladin EX.txt",
    "Gold Paladin EX.txt",
    "Oracle Think Tank EX.txt",
    "Royal Paladin EX.txt",
    "Angel Feather EX.txt",
    "Genesis EX.txt",
    "Megacolony EX.txt",
    "Great Nature EX.txt",
    "Neo Nectar EX.txt",
    "Aqua Force EX.txt",
    "Granblue EX.txt",
    "Bermuda Triangle EX.txt",
    "Nova Grappler EX.txt",
    "Dimension Police EX.txt",
    "Link Joker EX.txt",
    "Cray Elemental EX.txt"
    };

    auto replacements = generateReplacements();

    for (size_t i = 0; i < files.size(); ++i) {
        findAndReplaceInPlace(files[i], replacements);
    }

    return 0;
}
