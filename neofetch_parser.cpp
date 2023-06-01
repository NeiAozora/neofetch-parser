/*
 * MIT License
 * 
 * Copyright (c) 2023 Ahmad Fauzan <noxindocraft@gmail.com 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <map>
#include <sstream>
#include <algorithm>
#include <regex>

// Function to escape special characters in a string
std::string escapeString(const std::string& input) {
    std::ostringstream ss;
    for (char ch : input) {
        switch (ch) {
            case '\"':
                ss << "\\\"";
                break;
            case '\\':
                ss << "\\\\";
                break;
            case '\b':
                ss << "\\b";
                break;
            case '\f':
                ss << "\\f";
                break;
            case '\n':
                ss << "\\n";
                break;
            case '\r':
                ss << "\\r";
                break;
            case '\t':
                ss << "\\t";
                break;
            default:
                ss << ch;
                break;
        }
    }
    return ss.str();
}

std::string jsonPrettyPrint(const std::string& json) {
    std::stringstream prettyJson;
    std::stack<char> braces;
    int indentationLevel = 0;
    bool inQuotes = false;

    for (char c : json) {
        if (c == '"' && (braces.empty() || braces.top() != '\\')) {
            inQuotes = !inQuotes;
        }

        if (inQuotes) {
            prettyJson << c;
            continue;
        }

        switch (c) {
            case '{':
            case '[':
                braces.push(c);
                prettyJson << c << std::endl << std::setw(4 * braces.size()) << std::setfill(' ');
                indentationLevel = braces.size();
                break;

            case '}':
            case ']':
                braces.pop();
                prettyJson << std::endl << std::setw(4 * braces.size()) << std::setfill(' ') << c;
                indentationLevel = braces.size();
                break;

            case ',':
                prettyJson << c << std::endl << std::setw(4 * indentationLevel) << std::setfill(' ');
                break;

            case ':':
                prettyJson << c << ' ';
                break;

            default:
                prettyJson << c;
                break;
        }
    }

    return prettyJson.str();
}

// Function to convert a map to a JSON string
std::string jsonEncode(const std::map<std::string, std::string>& data) {
    std::ostringstream ss;
    ss << "{";

    auto it = data.begin();
    while (it != data.end()) {
        ss << "\"" << escapeString(it->first) << "\": \"" << escapeString(it->second) << "\"";
        ++it;
        if (it != data.end()) {
            ss << ",";
        }
    }

    ss << "}";
    return ss.str();
}

// Function to find the position of a key within a string
std::string findKeyPositionInString(const std::vector<std::string>& keys, const std::string& str) {
    std::string lowercaseStr = str;
    std::transform(lowercaseStr.begin(), lowercaseStr.end(), lowercaseStr.begin(), ::tolower);

    for (const std::string& key : keys) {
        std::string lowercaseKey = key;
        std::transform(lowercaseKey.begin(), lowercaseKey.end(), lowercaseKey.begin(), ::tolower);
        size_t found = lowercaseStr.find(lowercaseKey);
        if (found != std::string::npos) {
            return std::to_string(found);
        }
    }

    return "-1";
}

// Function to get the index of an element containing a substring
int getKeyOffsetBySubstring(const std::vector<std::string>& arr, const std::string& substring) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].find(substring) != std::string::npos) {
            return i;
        }
    }
    return -1;
}

// Function to extract the last word from a string
std::string getLastWordFromString(const std::string& str) {
    std::vector<std::string> words;
    std::string word;
    std::stringstream stream(str);

    while (stream >> word) {
        words.push_back(word);
    }

    if (!words.empty()) {
        return words.back();
    }
    return "";
}

// Function to remove ANSI escape codes from a string
std::string removeAnsiEscapeCodes(const std::string& str) {
    std::regex pattern("\\x1B\\[[0-9;-]*[A-Za-z]");
    return std::regex_replace(str, pattern, "");
}

// Function to parse neofetch output and generate JSON
std::string parseNeofetchOutput(const std::string& output) {
    std::vector<std::string> labels = {
        "OS",
        "Host",
        "Kernel",
        "Uptime",
        "Packages",
        "Shell",
        "Resolution",
        "DE",
        "WM",
        "WM Theme",
        "Terminal",
        "CPU",
        "GPU",
        "Memory"
    };

    std::map<std::string, std::string> parsedInfo;

    std::vector<std::string> lines;
    std::stringstream neofetchOutputStream(output);
    std::string line;

    while (std::getline(neofetchOutputStream, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    int titleArrayPos = getKeyOffsetBySubstring(lines, "----") - 1;
    std::string title = getLastWordFromString(lines[titleArrayPos]);

    parsedInfo["title"] = title;

    for (const std::string& line : lines) {
        std::string strPosition = findKeyPositionInString(labels, line);

        if (strPosition == "-1") {
            continue;
        }

        size_t separatorPos = line.find(':');

        std::string label = line.substr(0, separatorPos);
        std::string value = line.substr(separatorPos + 1);

        label = label.substr(label.find_first_not_of(" \t"));
        label = label.substr(0, label.find_last_not_of(" \t") + 1);
        
        std::transform( label.begin(), 
                        label.end(), 
                        label.begin(), 
                        [](unsigned char c) { 
                            return std::tolower(c); 
                        });


        value = value.substr(value.find_first_not_of(" \t"));
        value = value.substr(0, value.find_last_not_of(" \t") + 1);

        if (!label.empty()) {
            parsedInfo[label] = value;
        }
    }

    return jsonEncode(parsedInfo);
}

void printHelp() {
    std::cout << "Usage: parse_neofetch [OPTIONS]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << std::left << std::setw(20) << "  --load-from FILE"
              << "Specify the input file (default file name: output)" << std::endl;
    std::cout << std::left << std::setw(20) << "  -o FILE, --output FILE"
              << "Specify the output file (default file name: parsed_result.json)" << std::endl;
    std::cout << std::left << std::setw(20) << "  --json-pretty"
              << "Format the JSON output with indentation and line breaks" << std::endl;
    std::cout << std::left << std::setw(20) << "  --help, -h"
              << "Display this help message" << std::endl;
    std::cout << std::endl;
    std::cout << "Description:" << std::endl;
    std::cout << "  This program parses neofetch output and generates JSON data." << std::endl;
    std::cout << "  The output can be optionally formatted using JSON pretty print." << std::endl;
    std::cout << "  If you know PHP, you get the idea ;)" << std::endl;
}

int main(int argc, char* argv[]) {
    std::string inputFileName = "output";
    std::string outputFileName = "parsed_result.json";
    bool useJsonPrettyPrint = false;

    // Process command-line arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "--load-from" || arg == "-l" && i + 1 < argc) {
            inputFileName = argv[i + 1];
            i++;
        } else if (arg == "-o" && i + 1 < argc || arg == "--output" && i + 1 < argc) {
            outputFileName = argv[i + 1];
            i++;
        } else if (arg == "--json-pretty") {
            useJsonPrettyPrint = true;
        } else if (arg == "--help" || arg == "-h") {
            printHelp();
            return 0;
        } else {
            std::cerr << "Invalid option: " << arg << std::endl;
            printHelp();
            return 1;
        }
    }

    // Read input from file
    std::ifstream inputFile(inputFileName);
    if (!inputFile) {
        std::cerr << "Failed to open the file: " << inputFileName << std::endl;
        return 1;
    }

    std::string neofetchOutput((std::istreambuf_iterator<char>(inputFile)),
                               std::istreambuf_iterator<char>());

    neofetchOutput = removeAnsiEscapeCodes(neofetchOutput);

    // Parse neofetch output
    std::string json = parseNeofetchOutput(neofetchOutput);

    // Apply JSON pretty print if enabled
    if (useJsonPrettyPrint) {
        json = jsonPrettyPrint(json);
    }

    // Write output to file
    std::ofstream outputFile(outputFileName);
    if (!outputFile) {
        std::cerr << "Failed to open the file: " << outputFileName << std::endl;
        return 1;
    }

    outputFile << json;
    outputFile.close();
    std::cout << "JSON data written to: " << outputFileName << std::endl;

    return 0;
}
