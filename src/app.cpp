# include <iostream>
# include <stdio.h>
# include <filesystem>
# include <string>
# include <list>
# include <cctype>
namespace fs = std::filesystem;

std::string appVersion = "1.0";
std::vector<std::string> modifyVideos;
std::string outputVideoDestination;
std::string modifyThisVideoTemp;

int recieveVideoFiles() {
    std::string isCorrectVideos = "";
    int whichVideoIsFucked = 0;
    for (int i = 1; i != 11; i++) {
        std::cout << "Video " << i << "/10 > ";
        modifyThisVideoTemp = "";
        std::getline(std::cin, modifyThisVideoTemp);
        if (modifyThisVideoTemp == "finish") {
            break;
        } else {
            modifyVideos.push_back(modifyThisVideoTemp);
            modifyThisVideoTemp = "";
        }
    }

    std::cout << "The videos to modify are:";

    for (int i = 0; i != modifyVideos.size(); i++) {
        std::cout << "\n" << modifyVideos[i];
    }

    std::cout << "\n\nIs this correct? (y / n) > ";
    std::getline(std::cin, isCorrectVideos);
    isCorrectVideos = tolower(isCorrectVideos[0]);
    if (isCorrectVideos == "n") {
        std::cout << "\nLet's try that again.\n\n";
        return -1;
    } else if (isCorrectVideos == "y") {
        std::cout << "\nGreat!\n\n";
    }
    return 0;
}

int main() {
    int recieveVideoFilesOutput = 0;
    std::cout << "Welcome to FFMPEG Tool\n==================================================\nVersion " << appVersion << "\n\n";
    std::cout << "Drag and drop a video file (type 'finish' to stop)\n\n";
    for (int i = 0; i != 999; i++) {
        recieveVideoFilesOutput = recieveVideoFiles();
        if (recieveVideoFilesOutput == -1) {
            // Retry
        }
    }
    return 0;
}