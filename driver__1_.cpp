#include "orgtree.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**
 * THIS DRIVER FILE IS ONLY A START!
 * IT IS CRITICAL THAT YOU ADD YOUR
 * OWN TEST CASES. MOST CASES ARE
 * HIDDEN ON GRADESCOPE.
 */

/**
 * Print whether the given test case passed or failed
 * @param didPass - The test condition (true to pass, false to fail)
 * @param message - Description of what is being tested
 */
void assert(bool didPass, string message) {
    if (didPass) {
        cout << "Passed: " << message << endl;
    } else {
        cout << "FAILED: " << message << endl;
        // Halts execution, comment out to
        // continue testing other parts
        exit(EXIT_FAILURE);
    }
}

//TODO
int main(int argc, char **argv) {
    /*
     * Construct the following organization chart for testing
     *                1
     *           /    \    \
     *           2    3    4
     *          / \  / \   \
     *          5 6  7 8   9
     *         /   \       \
     *         10  11      12
     */
    //creates  heads for Employee
    Employee *head = new Employee(1, vector<int>{2, 3, 4});
    Employee *e2 = head->getDirectReports().at(0);
    Employee *e3 = head->getDirectReports().at(1);
    Employee *e4 = head->getDirectReports().at(2);


    //create directories for each head
    e2->addDirectReports(vector<int>{5, 6});
    e3->addDirectReports(vector<int>{7, 8});
    e4->addDirectReport(9);

    //give values to these new list with the directories
    Employee *e5 = e2->getDirectReports().at(0);
    Employee *e6 = e2->getDirectReports().at(1);
    Employee *e9 = e4->getDirectReports().at(0);

    e5->addDirectReport(10);
    e6->addDirectReport(11);
    e9->addDirectReport(12);
    Employee *e8 =  e3->getDirectReports().at(0);

    // Begin Testing
    // A few sample testing code are provided below

    // TODO Test all Orgtree functions
    //      according to the specifications in the comment section ABOVE each function signature.

    // IMPORTANT: You should also construct at aleast one different chart
    // Also make sure to check edge cases, such as empty chart, or one employee chart.

    // Test isEmployeePresentInOrg function

    //check if 6 return true as its in the tree
    bool employeePresent = Orgtree::isEmployeePresentInOrg(head, 6);
    assert(employeePresent, "ID 6 Present in tree");

    //check if 6 return false as its not in the tree
    employeePresent = Orgtree::isEmployeePresentInOrg(head, -2);
    assert(employeePresent == false, "ID -2 Not present in tree");

    //check if 6 return true as its in the tree
    employeePresent = Orgtree::isEmployeePresentInOrg(head, 1);
    assert(employeePresent, "ID 1 Present in tree");

    //check if a NULL head will return false
    employeePresent = Orgtree::isEmployeePresentInOrg(NULL, 4);
    assert(employeePresent == false, "Head is Not present in tree");


    // Test findEmployeeLevel function
    //return 1 as ID 4 exist in level 1 of the tree
    int employeeLevel = Orgtree::findEmployeeLevel(head, 4, 0);
    assert(employeeLevel == 1, "Level of ID 4 returns " + to_string(employeeLevel) + ", expected 1");

    //return 0 as ID 1  exist in level 0 of the tree
    employeeLevel = Orgtree::findEmployeeLevel(head, 1, 0);
    assert(employeeLevel == 0, "Level of ID 1 returns " + to_string(employeeLevel) + ", expected 0");

    //return 2 as ID 7  exist in level 2 of the tree
    employeeLevel = Orgtree::findEmployeeLevel(head, 7, 0);
    assert(employeeLevel == 2, "Level of ID 7 returns " + to_string(employeeLevel) + ", expected 0");

    //return -1 as ID 25 doesnt exist in the tree
    employeeLevel = Orgtree::findEmployeeLevel(head, 25, 0);
    assert(employeeLevel == -1, "Level of ID 25 returns " + to_string(employeeLevel) + ", expected -1");

    //return -1 as Head is NULL
    employeeLevel = Orgtree::findEmployeeLevel(NULL, 4, 0);
    assert(employeeLevel == -1, "NULL head returns " + to_string(employeeLevel) + ", expected -1");
    //TODO...

    // Test findClosestSharedManager function
    // Call the function with certain combination of the arguments
    // Assert / verify the returned Employee* has the expected Employee ID
    //TODO...

    //the commonHead return manager e5 as 20 doesnt exist so it returns the node that holds 5
    Employee *commonHead = Orgtree::findClosestSharedManager(head, 5, 20);
    assert(commonHead == e5, "the closest shared manager is  5");

    //the commonHead return the manager e6 as 35 doesnt exist so it returns the node that holds 6
    commonHead = Orgtree::findClosestSharedManager(head, 35, 6);
    assert(commonHead == e6, "the closest shared manager is  6");

    //the commonHead return manager of the whole tree as thats the common head of 2 and 3
    commonHead = Orgtree::findClosestSharedManager(head, 2, 3);
    assert(commonHead == head, "the closest shared manager is  1");

    //the commonHead return manager e2 as thats the common head of 5 and 6
    commonHead = Orgtree::findClosestSharedManager(head, 5, 6);
    assert(commonHead == e2, "the closest shared manager is  2");

    //the commonHead return manager of the whole tree as thats the common head of 10 and 7
    commonHead = Orgtree::findClosestSharedManager(head, 10, 7);
    assert(commonHead == head, "the closest shared manager is  1");

    //the commonHead return manager e2 as thats the common head of 10 and 6
    commonHead = Orgtree::findClosestSharedManager(head, 10, 6);
    assert(commonHead == e2, "the closest shared manager is  2");

    //the commonHead return NULL as the head is NULL
    commonHead = Orgtree::findClosestSharedManager(NULL, 10, 6);
    assert(commonHead == NULL, "the closest shared manager is  NULL as the head is NULL");


    // Test findNumOfManagersBetween function

    //checking the Managers between 10 and 11 which should return 3
    int numManagers = Orgtree::findNumOfManagersBetween(head, 10, 11);
    assert(numManagers == 3, "Managers between 10 and 11 returns " + to_string(numManagers) + ", expected 3");

    //checking the Managers between 1 and 10 which should return 2
    numManagers = Orgtree::findNumOfManagersBetween(head, 1, 10);
    assert(numManagers == 2, "Managers between 1 and 10 returns " + to_string(numManagers) + ", expected 2");

    //checking the Managers between 1 and 10 which should return -1 as 0 doesnt exist in the tree
    numManagers = Orgtree::findNumOfManagersBetween(head, 0, 10);
    assert(numManagers == -1, "Managers between 0 and 10 returns " + to_string(numManagers) + ", expected -1");

    //checking the Managers between 8 and -5 which should return -1 as -5 doesnt exist in the tree
    numManagers = Orgtree::findNumOfManagersBetween(head, 8, -5);
    assert(numManagers == -1, "Managers between 8 and -5 returns " + to_string(numManagers) + ", expected -1");

    //checking the Managers between 1 and 5 which should return -1 as head is NULL
    numManagers = Orgtree::findNumOfManagersBetween(NULL, 1, 5);
    assert(numManagers == -1, "Managers between 1 and 5 returns " + to_string(numManagers) + ", expected -1");
    // Test deleteOrgtree function
    // VERY IMPORTANT: Related to valgrind memory leaking detection testing,
    // You MUST call your deleteOrgtree function at the end of this driver testing code
    // to delete all the allocated memory for the tree.

    //prints the tree in postorder transversal and deletes each nodes after printing
    Orgtree::deleteOrgtree(head);

    // Use the printed employee ID along the sequence of deletion to verify your implementation
    // This part will be autograded as well as manually inspected for grading

    cout << endl << "All test cases passed!" << endl;

    // Return EXIT_SUCCESS exit code
    exit(EXIT_SUCCESS);
}