#include "orgtree.h"
#include <algorithm>
#include <iostream>
using namespace std;

//I the undersigned promise that the submitted assignment is my own work. While I was
//free to discuss ideas with others, the work contained is my own. I recognize that
//should this not be the case; I will be subject to penalties as outlined in the course
//syllabus.
//Name: Omar Yusuf
//Red ID: 823877555




/**
 * Check if an employee is present in an organization chart.
 *
 * @param  head the head / root Employee of the organization chart
 * @param  e_id the employee id being searched
 * @return      true or false
 * @see
 */
bool Orgtree::isEmployeePresentInOrg(Employee* head, int e_id) {
    // Write your recursive implementation here

    // Important: Your implementation MUST use the recursive approach
    // as required in the assignment 3 prompt to avoid penalties.

//cout << "the num looked for is " << e_id <<endl;
    // base case 1: empty organization chart
    if (head == NULL){
        return false;
    }





    // base case 2: if the employee is found, return true
    if((head -> getEmployeeID()) ==  e_id){
        return true;
    }



    // search employee from each child of the head
    // return true if the employee is found in one of the child subtree


    //for loop to check all the direct reports of head
    for(int i = 0; i < head ->getDirectReports().size(); ++i){

        //bool to hold the result of checking all the nodes in the tree by recursion
        bool result = isEmployeePresentInOrg(head -> getDirectReports().at(i),  e_id);

        //if the int is found result will equal true and  return true
        if(result == true){
            return true;
        }
    }
    // if not found, return false
    return false;
}

/**
 * Find the level of an employee in an organization chart / tree.
 *
 * <p>
 * The head / root of the org chart has a level of 0, children of the head have
 * a level of head plus 1, and so on and so forth...
 *
 * <p>
 * Assumption: e_id is unique among all employee IDs
 *
 * @param  head      the head / root Employee of the organization chart
 * @param  e_id      the employee id being searched
 * @param  headLevel the level of the head employee of the organization
 * @return    level of the employee in the org chart
 *      returns Employee::NOT_FOUND if e_id is not present
 * @see
 */
int Orgtree::findEmployeeLevel(Employee* head, int e_id, int headLevel) {
    // Write your recursive implementation here.

    // Important: Your implementation MUST use the recursive approach
    // as required in the assignment 3 prompt to avoid penalties.

    // base case 1: empty organization chart
    if (head == NULL){
        return -1;
    }

    // base case 2: the employee is found, returns the employee level

    if (head -> getEmployeeID() == e_id){
        return headLevel;
    }
    // search employee from each child of the head

    //for loop to check all the nodes in the tree
    for(int i = 0; i < head ->getDirectReports().size(); ++i){

        //recurssion occur that  check each level to see if the node exist in that level
        int height = findEmployeeLevel(head -> getDirectReports().at(i),  e_id,  headLevel + 1);

        //if the height doesnt equal -1 the e_id exist and return the height that is found
        if (height != -1){
            return height;
        }


    }

    // if not found
    return Employee::NOT_FOUND;
}

/**
 * Find the closest shared manager of two employees e1 and e2.
 *
 * <p>
 * There are two possible organizational relationships between two employees in the org chart:
 * case 1: e1 or e2 is a manager of the other employee;
 * case 2: e1 or e2 is not a manager of the other employee, they have at least one shared manager
 *
 * Employee 1 is a manager of employee 2 if employee 1 is an ancestor of employee 2 in the organization chart
 *
 * <p>
 * Assumption: e1_id and e2_id are unique among all employee IDs
 *
 * @param  head  the head / root Employee of the organization chart
 * @param  e1_id id of employee 1 being searched
 * @param  e2_id id of employee 2 being searched
 * @return   closest shared manager in the org chart between employee e1 and employee e2
 *               if e1 is present and e2 is not, returns e1
 *               if e2 is present and e1 is not, returns e2
 *               if neither e1 or e2 is present, returns empty employee
 * @see
 */
Employee* Orgtree::findClosestSharedManager(Employee* head, int e1_id, int e2_id) {
    // Write your recursive implementation here

    // Important: Your implementation MUST use the recursive approach
    // as required in the assignment 3 prompt to avoid penalties.

    // base case 1: empty organization chart
    if (head == NULL){
        return NULL;
    }

    // base case 2: either e1_id or e2_id is the same as the head / root
    if (head -> getEmployeeID() == e1_id || head -> getEmployeeID() == e2_id){
        return head;
    }

    // Traverse through each direct report of the head to find where e1 is and where e2 is
    // recursively check if e1_id or e2_id exists in one of the child trees from the head / root
    for(int i = 0; i < head ->getDirectReports().size(); ++i){

        //if the tree has both node
        if(isEmployeePresentInOrg(head,e1_id) && isEmployeePresentInOrg(head,e2_id) ){


            //hold to check if both value are found in the manager
            int check = 0;
            for(int j = 0; j < head ->getDirectReports().size(); ++j){

                //check if the current head has the two int are in its directory
                if(head -> getDirectReports().at(j) -> getEmployeeID() == e1_id || head -> getDirectReports().at(j)-> getEmployeeID() == e2_id){
                    check = check + 1;
                }

                //if check equal 2 then the directory of head holds both int and return this head
                if(check == 2){
                    return head;
                }

                //if the one of the directory hold by the current head holds both value resend to recursion else it returns head
                if(isEmployeePresentInOrg(head-> getDirectReports().at(i),e1_id) && isEmployeePresentInOrg(head-> getDirectReports().at(i),e2_id)){
                    return(findClosestSharedManager(head -> getDirectReports().at(i),e1_id,  e2_id));
                }
                else{

                    return(head);
                }
            }
        }
        else{

            //if it has one of the node just keep recursion till they find where the node is
            if(isEmployeePresentInOrg(head -> getDirectReports().at(i),e1_id) || isEmployeePresentInOrg(head -> getDirectReports().at(i),e2_id)){
                return(findClosestSharedManager(head -> getDirectReports().at(i),e1_id,  e2_id));
            }

        }



    }

    // if e1_id is found in one subtree and e2_id is found in another subtree,
    // update the closest shared manager to the current head node


    // if e1_id and e2_id exist in a same subtree, return first encountered node in e1_id or e2_id

    // if not found, this would happen when either e1_id or e2_id is present in the tree
    return nullptr;
}



/**
 * Calculate the number of managers between employee e1 and employee e2.
 *
 * <p>
 * The number of managers between employee e1 and employee e2 can be calculated by:
 *  number of edges between employee 1 and closest shared manager +
 *  number of edges between employee 2 and closest shared manager - 1
 *
 * <p>
 * Assumption: e1_id and e2_id are unique among all employee IDs
 *
 * @param  head  the head / root Employee of the organization chart
 * @param  e1_id id of employee 1 being searched
 * @param  e2_id id of employee 2 being searched
 * @return   number of managers between employee e1 and employee e2
 *           returns Employee::NOT_FOUND if either e1 or e2 is not present in the chart
 * @see
 */
int Orgtree::findNumOfManagersBetween(Employee* head, int e1_id, int e2_id) {

    // Write your implementation here. You do NOT need to use recursive approach here.

    // Use the above functions wherever you need to implement this function.

    // Continue only if both employee nodes e1_id and e2_id are in the org chart tree
    // otherwise, return Employee::NOT_FOUND


    //check if both int employeeId is in the tree
    if(isEmployeePresentInOrg(head,e1_id) && isEmployeePresentInOrg(head,e2_id) ){


        // The number of managers between employee e1 and employee e2 can be calculated by:
        // number of edges between e1_id and closest shared manager +
        // number of edges between e2_id and closest shared manager - 1
        int numEdgeE1 = findEmployeeLevel(head,  e1_id, 0) -  findEmployeeLevel(head, findClosestSharedManager(head, e1_id, e2_id)->getEmployeeID(), 0);
        int numEdgeE2 = findEmployeeLevel(head,  e2_id, 0) -  findEmployeeLevel(head, findClosestSharedManager(head, e1_id, e2_id)->getEmployeeID(), 0);
        return (numEdgeE1 + numEdgeE2 - 1);
    }
    else return Employee::NOT_FOUND;



}

/** Recursively delete a tree
 *  The proper implementation of this function is also needed for
 *  passing the valgrind memory leaking test.
 *
 * <p>
 * Starting from the head / root node, recursively deallocate
 * the memory of the descendants. DO NOT worry about removing them from
 * the vector directReports
 *
 * Use post order traversal:
 * Delete / deallocate the children recursively
 * Delete / deallocate the current node after deleting its children
 *     Before deleting the current node, print its employee ID and a new line
 *     This part will be autograded as well as manually inspected for grading
 *
 * For example, with the following org chart, the post order traversal
 * order would be 5 6 2 7 8 3 1, and the nodes should be deleted in that order
 *             1
 *           /    \
 *           2    3
 *          / \  / \
 *          5 6  7 8
 *
 * @param  head  the head / root Employee of the organization chart
 * @return   None
 *
 * @see
 */
void Orgtree::deleteOrgtree(Employee* head) {
    // Write your recursive implementation here

    // Important: Your implementation MUST use the recursive approach
    // as required in the assignment 3 prompt to avoid penalties.

    // base case: empty tree or organization chart
    if(head == NULL){

    }else{
        //if the current head has no directories print and delete it
        if(head -> getDirectReports().size() == 0){

            // print current node's employee ID and a new line
            cout << head ->  getEmployeeID() << " ";

            // delete the current node after deleting its children
            delete head;


        }
        else{
            for(int i = 0; i < head ->getDirectReports().size(); ++i){

                //if the current head has directories send it to recursion wiht the next node to be head

                deleteOrgtree(head -> getDirectReports().at(i));





            }
            // print current node's employee ID and a new line
            cout << head ->  getEmployeeID() << " ";


            // delete the current node after deleting its children
            delete head;
        }


    }

}