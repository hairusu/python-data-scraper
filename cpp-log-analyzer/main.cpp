#include <iostream>
#include <fstream>
#include <string>
#include <map>

// Struct to store parsed log statistics
struct LogStats {
    int totalLines = 0;
    int infoCount = 0;
    int warningCount = 0;
    int errorCount = 0;
};

void processLogLine(const std::string& line, LogStats& stats) {
    stats.totalLines++;
    if (line.find("[INFO]") != std::string::npos) {
        stats.infoCount++;
    } else if (line.find("[WARNING]") != std::string::npos) {
        stats.warningCount++;
    } else if (line.find("[ERROR]") != std::string::npos) {
        stats.errorCount++;
    }
}

void generateReport(const LogStats& stats, const std::string& outputFilename) {
    std::ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not create output report file.\n";
        return;
    }

    outFile << "========================================\n";
    outFile << "       SYSTEM LOG ANALYSIS REPORT       \n";
    outFile << "========================================\n";
    outFile << "Total Log Entries Processed : " << stats.totalLines << "\n";
    outFile << "INFO Messages              : " << stats.infoCount << "\n";
    outFile << "WARNING Messages           : " << stats.warningCount << "\n";
    outFile << "ERROR Messages             : " << stats.errorCount << "\n";
    outFile << "----------------------------------------\n";
    
    double errorRate = stats.totalLines > 0 
        ? (static_cast<double>(stats.errorCount) / stats.totalLines) * 100.0 
        : 0.0;
        
    outFile << "Error Rate                 : " << errorRate << "%\n";
    outFile << "========================================\n";

    outFile.close();
    std::cout << "Report successfully generated: " << outputFilename << "\n";
}

int main() {
    std::string inputFilename;
    char choice;

    do {
        std::cout << "\n--- C++ Log File Analyzer ---\n";
        std::cout << "Enter log file path (e.g., sample.log): ";
        std::cin >> inputFilename;

        std::ifstream inFile(inputFilename);
        if (!inFile.is_open()) {
            std::cout << "Error opening file '" << inputFilename << "'. Please make sure the file exists.\n";
        } else {
            LogStats stats;
            std::string line;

            while (std::getline(inFile, line)) {
                processLogLine(line, stats);
            }
            inFile.close();

            std::cout << "\nProcessing completed.\n";
            generateReport(stats, "log_summary_report.txt");
        }

        std::cout << "\nDo you want to analyze another log file? (y/n): ";
        std::cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    std::cout << "Exiting C++ Log Analyzer. Have a great day!\n";
    return 0;
}