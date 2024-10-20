#include "TestManager.h"

void TestManager::LoadTests()
{
    // Example implementation: load tests from a JSON file
    ifstream file("tests.json");
    json j;
    file >> j;

    for (auto& categoryJson : j) {
        categories.push_back(categoryJson["category"]); // Add category name

        vector<Test> testList; // Create a list for tests in this category

        Test test(categoryJson["category"]); // Create a test object for the category
        for (auto& questionJson : categoryJson["questions"]) {
            vector<string> options = questionJson["options"].get<vector<string>>();
            test.addQuestion(questionJson["questionText"], options, questionJson["correctAnswer"]);
        }

        testList.push_back(test); // Add the test to the list
        tests.push_back(testList); // Add the list of tests to the main tests vector
    }
}

void TestManager::DisplayCategories()
{
    cout << "Available Categories:" << endl;
    for (int i = 0; i < categories.size(); i++) {
        cout << i << ": " << categories[i] << endl; // Show category index and name
    }
}

void TestManager::DisplayTests(int categoryIndex)
{
    if (categoryIndex < 0 || categoryIndex >= tests.size()) {
        cout << "Invalid category index." << endl;
        return;
    }

    cout << "Available Tests in " << categories[categoryIndex] << ":" << endl;
    for (size_t i = 0; i < tests[categoryIndex].size(); ++i) {
        cout << i << ": " << tests[categoryIndex][i].category << endl; // Show test index and name
    }
}

int TestManager::GetTestCount(int categoryIndex)
{
    if (categoryIndex >= 0 && categoryIndex < tests.size()) {
        return tests[categoryIndex].size();
    }
    return 0; // Return 0 if categoryIndex is invalid}
}
Test TestManager::GetTest(int categoryIndex, int testIndex)
{
    if (categoryIndex >= 0 && categoryIndex < tests.size() &&
        testIndex >= 0 && testIndex < tests[categoryIndex].size()) {
        return tests[categoryIndex][testIndex];
    }
    throw std::out_of_range("Invalid test index");
}