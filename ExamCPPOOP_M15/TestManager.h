#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include "FileManager.h"
#include "Test.h" // Assuming you have a Test class defined elsewhere
using namespace std;
class TestManager
{
public : 
    TestManager() {
        LoadTests();
    }
    vector<string> categories; // List of category names
    vector<vector<Test>> tests; // Corresponding tests for each category

    void LoadTests(); // Load tests from a file or define them
    void DisplayCategories(); // Display available categories
    void DisplayTests(int categoryIndex); // Display tests in a selected category
    int GetTestCount(int categoryIndex);
    Test GetTest(int categoryIndex, int testIndex); // Get a specific test
};

