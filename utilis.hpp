/*

Utilis header:
Contains useful functions for the backend files

*/

#ifndef UTILIS_H
    #define UTILIS_H
#endif

#include <fstream>
#include <filesystem>
#include <string.h>

// Function to read the contents of a file
char* readFile(const char* path, char* result, size_t length)
{
    // Exit if the file doesn't exist
    if(!std::filesystem::exists(path)) return nullptr;

    // Open the file
    std::ifstream file(path, std::ios::binary);
    if(!file) return nullptr;

    // Check and solve length conflicts
    size_t file_size = std::filesystem::file_size(path);

    if(file_size >= length) file_size = length - 1;

    // Read the file
    if(!file.read(result, file_size)) return nullptr;

    result[file_size] = '\0';

    std::cout << result << "\n";

    return result;
}

// Function to check if a file is in a directory or any of its subdirectories
bool fileIncluded(char* file_path, char directory_path[])
{
    // Get the file and direcotry absolute paths solving the .. direcotry
    std::filesystem::path file = std::filesystem::weakly_canonical(std::filesystem::absolute(file_path));
    std::filesystem::path directory = std::filesystem::weakly_canonical(std::filesystem::absolute(directory_path));

    // Compare the two paths
    auto mismatches = std::mismatch(directory.begin(), directory.end(), file.begin());

    // Return weather the directory path is a substring of the filepath
    return mismatches.first == directory.end();
}

// Function that returns a pointer to the stert of the last extension in a filename
const char* getFileExtension(const char* filename)
{
    // Find the last dot to appear in the string
    const char* lastDot = strrchr(filename, '.');

    // Retun nullptr if there is no dot or it's a hidden file (which starts widtha a dot)
    if(!lastDot || lastDot == filename) return nullptr;

    // Create a pointer to next character in the string after the last dot
    const char* result = lastDot+1;

    // Return nullptr if the string ends with a dot
    if(*result == '\0') return nullptr;

    // Return the pointer previously created and checked
    return result;
}