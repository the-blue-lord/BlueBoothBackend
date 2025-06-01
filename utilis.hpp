/*

Utilis header:
Contains useful functions for the backend files

*/

#ifndef UTILIS_H
    #define UTILIS_H
#endif

#include <fstream>
#include <filesystem>

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
    if(!file.read(result, length)) return nullptr;

    result[length] = '\0';

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