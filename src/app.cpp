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
    modifyVideos = {};
    std::string isCorrectVideos = "";
    int whichVideoIsFucked = 0;
    for (int i = 1; i != 11; i++) {
        std::cout << "Video " << i << "/10 > ";
        modifyThisVideoTemp = "";
        std::getline(std::cin, modifyThisVideoTemp);
        if (modifyThisVideoTemp == "finish") {
            break;
        } else if (modifyThisVideoTemp == "quit") {
            std::cout << "Exiting the program...";
            exit(0);
        } else {
            fs::path temporaryPathToAddVideo(modifyThisVideoTemp);
            if (!fs::is_regular_file(temporaryPathToAddVideo)) {
                std::cout << "\nNot a file or file doesn't exist, please drag and drop a valid file\n\n";
                i -= 1;
            } else {
                modifyVideos.push_back(modifyThisVideoTemp);
                modifyThisVideoTemp = "";
            }
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
        std::cout << "\nSorry about that. Let's try that again.\n\n";
        return -1;
    } else if (isCorrectVideos == "y") {
        std::cout << "\nGreat! Let's begin.\n\n";
        return 0;
    } else {
        std::cout << "\nNot a valid response. Assuming you meant 'n', let's try that again.\n\n";
        return -1;
    }
}

int main() {
    int recieveVideoFilesOutput = 0;
    std::cout << "Welcome to FFMPEG Tool\n==================================================\nVersion " << appVersion << "\n\n";
    std::cout << "Drag and drop a video file (type 'finish' to stop, type 'quit' to exit)\n\n";
    for (int i = 0; i != 999; i++) {
        recieveVideoFilesOutput = recieveVideoFiles();
        if (recieveVideoFilesOutput == 0) {
            break;
        }
    }
    return 0;
}