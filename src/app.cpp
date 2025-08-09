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
std::vector<std::string> outputVideoFilenames;
std::string modifyThisVideoTemp;

int receiveVideoFiles() {
    modifyVideos = {};
    std::string isCorrectVideos = "";
    int whichVideoIsFucked = 0;
    for (int i = 1; i != 11; i++) {
        std::cout << "Video " << i << "/10 > ";
        modifyThisVideoTemp = "";
        std::getline(std::cin, modifyThisVideoTemp);
        if (modifyThisVideoTemp.find("\"") == -1) {
            std::string modifyThisVideoTempFirstRemoved = modifyThisVideoTemp.erase(modifyThisVideoTemp.front());
            std::string modifyThisVideoTempLastRemoved = modifyThisVideoTempFirstRemoved.erase(modifyThisVideoTempFirstRemoved.back());
            modifyThisVideoTemp = modifyThisVideoTempLastRemoved;
        }
        if (modifyThisVideoTemp == "finish") {
            if (modifyVideos.empty()) {
                std::cout << "Please insert at least 1 video or type 'quit' to exit the program.\n\n";
                return -1;
            }
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
        std::cout << "\nGreat!\n\n";
        return 0;
    } else {
        std::cout << "\nNot a valid response. Assuming you meant 'n', let's try that again.\n\n";
        return -1;
    }
}

int receiveOutputDestination() {
    std::string yOrNCorrectDir = "";
    outputVideoDestination = "";
    std::cout << "> ";
    std::getline(std::cin, outputVideoDestination);
    fs::path outputVideoPath(outputVideoDestination);
    if (outputVideoDestination.empty()) {
        std::cout << "Please insert a valid path. If the path doesn't exist, it will be created in the exact absolute path you typed as a folder.\n\n";
        return -1;
    } else {
        if (!fs::is_directory(outputVideoPath)) {
            try {
                fs::create_directory(outputVideoPath);
                return 0;
            } catch (int e) {
                std::cout << "Directory doesn't exist, and the program could not create it. Please try another path that exists and you have permission to write to.\n\n";
                return -1;
            }
        } else {
            std::cout << "Confirmation: the modified video(s) should be placed in the following directory: ";
            std::cout << outputVideoPath;
            std::cout << "\nIs this correct? (y / n) > ";
            std::getline(std::cin, yOrNCorrectDir);
            yOrNCorrectDir = tolower(yOrNCorrectDir[0]);
            if (yOrNCorrectDir == "n") {
                std::cout << "\nSorry about that. Insert a valid path.\n\n";
                return -1;
            } else if (yOrNCorrectDir == "y") {
                std::cout << "\nGreat!\n\n";
                return 0;
            } else {
                std::cout << "\nNot a valid response. Assuming you meant 'n', let's try that again.\n\n";
            }
            return 0;
        }
    }
}

int receiveOutputFileName() {
    outputVideoFilenames = {};
    std::string outputVideoTemporaryFname;
    char dot = '.';
    for (int eachVideo = 1; eachVideo != modifyVideos.size() + 1; eachVideo++) {
        outputVideoTemporaryFname = "";
        std::cout << "Video " << eachVideo << "/" << modifyVideos.size() << " > ";
        std::getline(std::cin, outputVideoTemporaryFname);
        if (outputVideoTemporaryFname.empty()) {
            std::cout << "\nFilename cannot be empty.\n\n";
            eachVideo -= 1;
        } else {
            if (outputVideoTemporaryFname.find(".") == -1 || outputVideoTemporaryFname.back() == dot) {
                std::cout << "Could not detect any valid file extensions. Please try again.\n";
                eachVideo -= 1;
            } else {
                outputVideoFilenames.push_back(outputVideoTemporaryFname);
            }
        }
    }
    return 0;
}

int programIntelligentCLI() {
    std::string mYC = "";
    std::string vbitr = "default";
    std::string venco = "default";
    std::string abitr = "default";
    std::string aenco = "default";
    std::string crfcn = "default";
    std::string framr = "default";
    for (int i = 0; i != 1000; i++) {
        std::cout << "\n";
    }
    std::cout << "\n\nType 'quit' to exit the program. Type 'begin' to start modifying all the videos. You can use the following modifications:\n\n(vb) Video bitrate\n(ve) Video encoder\n(ab) Audio bitrate\n(ae) Audio encoder\n(crf) CRF constant\n(fps) Framerate\n\n";
    std::getline(std::cin, mYC);
    if (mYC == "quit") {
        std::cout << "Discarding all changes and exiting the program...";
        exit(0);
    } else if (mYC == "begin") {
        std::cout << "All " << modifyVideos.size() << " videos will be modified with the following parameters:\n";
        std::cout << "Video birate: " << vbitr << "\nVideo encoder: " << venco << "\nAudio bitrate: " << abitr << "\nAudio encoder: " << aenco << "\nCRF constant: " << crfcn << "\nFramerate: " << framr;
    }
    return 0;
}

int main() {
    int receiveVideoFilesOutput = 0;
    int receiveOutputDestinationOutput = 0;
    int receiveOutputFilenameOutput = 0;
    int programIntelliCLIOutput = 0;
    std::cout << "Welcome to FFMPEG Tool\n==================================================\nVersion " << appVersion << "\n\n";
    std::cout << "Drag and drop a video file (type 'finish' to stop, type 'quit' to exit)\n\n";
    for (int i = 0; i != 999; i++) {
        receiveVideoFilesOutput = receiveVideoFiles();
        if (receiveVideoFilesOutput == 0) {
            break;
        }
    }
    std::cout << "Now, you will have to choose where we should place the modified video files.\n";
    std::cout << "Do not include the filename in your selection. You will be able to choose the output filename later.\n\n";
    for (int i = 0; i != 999; i++) {
        receiveOutputDestinationOutput = receiveOutputDestination();
        if (receiveOutputDestinationOutput == 0) {
            break;
        }
    }
    std::cout << "Finally, select the filename for each video.\n";
    std::cout << "Include the file extension you want the video to be in (for example, .mp4, .mov, .mkv, .avi, etc.)\n\n";
    for (int i = 0; i != 999; i++) {
        receiveOutputFilenameOutput = receiveOutputFileName();
        if (receiveOutputDestinationOutput == 0) {
            break;
        }
    }
    for (int i = 0; i != 999; i++) {
        programIntelliCLIOutput = programIntelligentCLI();
        if (programIntelliCLIOutput == 0) {
            break;
        }
    }
    return 0;
}