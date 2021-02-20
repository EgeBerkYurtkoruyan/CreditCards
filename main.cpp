//
//  main.cpp
//  CS204_hw2
//
//  Created by Ege Berk Yurtkoruyan on 19.02.2020.
//
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/* THIS PART IS TAKEN FROM THE HW2.pdf FILE OF THE HOMEWORK */
struct node{
  
    int month, year;
    vector<string> cards;
    node* next;
    
};
/* END OF THE PART TAKEN FROM HW2.pdf FILE */


bool CheckCardNumber(string card_no){
//    THIS FUNCTION CONTROLS IF THE INPUT CARD NUMBER IS VALID OR NOT.
//    THIS FUNCTION WILL BE SUMMONED IF THE USER PICKS 2 FROM THE MENU.
    if(card_no.length() != 16){
        return false;
    }else{
    
        for(int i = 0 ; i < 16 ; i++ ){
            if ( card_no[i] > '9' || '0' > card_no[i] )
                return false;
        }
        return true;
    }
    
}


bool checkNode(node* node_ptr , int m, int y , node* & ptr_exists ){
//    THIS FUNCTION WILL CHECK IF THE NODE WITH THE EXPIRATION DATE HAS BEEN CREATED OR NOT.
//    THIS FUNCTION ALSO RETURNS THE POINTER THAT IS POINTING TO THE NODE WITH SAME EXP. DATE THAT HAS BEEN CREATED.
    while(node_ptr != NULL){
        if((m == node_ptr -> month) && (y == node_ptr -> year)){
            ptr_exists = node_ptr;
            return true;
        }
        node_ptr = node_ptr->next;
    }
    return false;
}


bool Card_exists(node* ptr , string card){
//    THIS FUNCTION WILL RETURN TRUE IF CARD EXISTS IN A NODE AND ALSO WILL PRINT THE MESSAGE NECCESARY.
//    THIS FUNCTION WILL BE USEFUL WHEN THE USER INPUT IS 2 AND USER ENTERED A VALID CARD NUMBER.
    while(ptr != NULL){
        for(int i = 0 ; i < ptr->cards.size(); i++){
            if(ptr->cards[i] == card){
                cout << "There exists a credit card given number " << card << " with expiration date: " << ptr->month
                << " " << ptr->year << endl << endl;
                return true;
            }
        }
        ptr = ptr-> next;
    }
    cout << "There is no credit card with given credit card number: " << card << endl << endl;
    return false;
}


int DeleteNode(int m , int y , node* & ptr){
//    THIS FUNCTION WILL DELETE THE NODE WITH THE GIVEN MONTH AND YEAR VALUES.
//    THIS FUNCTION DELETES THE NODE AND CONECTS THE NODE BEHIND THE DELETED NODE WITH THE NEXT ONE IN ORDER TO MAINTAIN THE LINKED LIST AS ONE PIECE.
    node * start = ptr;
    node* ptr2;
    ptr2 = NULL;
    while (ptr != NULL) {
        
        if (ptr-> month == m && ptr -> year == y){
            
            node* garbage;
//            the garbage pointer is used to delete the node by appending it into the pointer that has m and y values and using the 'delete' command
            if(ptr2 == NULL){
                
                garbage = ptr;
                cout << "Node with expiration date " << m << " " << y << " and the following credit cards have been deleted!" << endl;
                
                    for(int i = 0 ; i < ptr->cards.size() ; i++){
                        cout << i+1 << ") " << ptr->cards[i] << endl;
                    }
                cout << endl;
                ptr = ptr-> next;
                if(garbage == start)
                    ptr = start->next;
                else
                    ptr = start;
                delete garbage;
                return 0;
            }else{
                garbage = ptr;
                cout << "Node with expiration date " << m << " " << y << " and the following credit cards have been deleted!" << endl;
                
                    for(int i = 0 ; i < ptr->cards.size() ; i++){
                        cout << i+1 << ") " << ptr->cards[i] << endl;
                    }
                cout << endl;
                ptr2-> next = ptr-> next;
                ptr = ptr-> next;
                if(garbage == start)
                    ptr = start->next;
                else
                    ptr = start;
                delete garbage;
                return 0;
            }
            
        }else{
            ptr2 = ptr;
            ptr = ptr-> next;
        }
    }
    cout << endl << "There is no node with expiration date " << m << " " << y << ", nothing deleted!" << endl << endl;
    ptr = start;
    return 0;
}


void Sort_and_print(node* ptr){
    int min_m = 0 , min_y = 0 , m = 12, y=9999;
//    m and y values should be the biggest possible in order to minimize them step y step until they are the values we seek.
    
     if(ptr->cards.size()){
        
        node* ptr2;
        ptr2 = ptr;
        
        node* ptr3;
        
        node* start;
        start = ptr;
    
   

        while(ptr2 != NULL){
            while(ptr != NULL){
                if(((ptr-> month < m && ptr->year == y) || ptr->year < y) && (min_y < ptr->year || (min_y == ptr-> year && min_m < ptr->month))){
                    m = ptr-> month;
                    y = ptr-> year;
                    ptr3 = ptr;
                }
                
                ptr = ptr->next;
            }
            if(y != 9999){
                cout << "Expiration Date: " << m << " " << y << endl;
                for(int i = 0 ; i < ptr3->cards.size() ; i++){
                    cout << i+1 << ") " << ptr3->cards[i] << endl;
                }
                cout << "-------------------" << endl << endl;
            }
            min_y = y;
            min_m = m;
            m = 12;
            y = 9999;
            ptr = start;
            ptr2 = ptr2->next;
            }
    }else{
//        this part wil be activated if there is no node to list.
        cout << "List is empty!" << endl<< endl;
    }
}

void delete_all(node* ptr){
    
    node*garbage;
    
    while(ptr != NULL){
        garbage = ptr;
        ptr = ptr-> next;
        delete garbage;
    }
    delete ptr;
}

int main() {
    
    ifstream file;
    string fileName;
    
    do{
        cout << "Please enter file name: ";
        cin >> fileName;
        
        file.open(fileName.c_str());
        
        if(file.fail())
            cout << "Cannot find a file named " << fileName << endl;
        
    }while(file.fail());
    
    string line , card_no;
    int m, y;
    node* ptr1 = new node;
    ptr1 -> next = NULL;
    node* ptr_temp ;
    node* head;
    head = ptr1;
    
    
    while(getline(file,line)){
        
        stringstream ss(line);
        ss >> card_no >> m >> y;
        
        if(checkNode(head, m, y, ptr_temp)){
//          IF THERE HAS BEEN A NODE CREATED WITH SAME EXP. date
            ptr_temp ->cards.push_back(card_no);
            cout << "Node with expiration date" << m << " " << y << " already exists" << endl;
            
        }else{
//          IF THE NODE HAS NOT BEEN CREATED.
            ptr1-> month = m;
            ptr1-> year = y;
            ptr1-> cards.push_back(card_no);
            ptr1-> next = new node;
            ptr1 = ptr1-> next;
            ptr1-> next = NULL;
//           I could have used constructors but i get syntax errors when i tried to do them the way i saw on the slides.
            cout << "New node is created with expiration date: " << m << " " << y << endl;
            
        }
    
        cout << "Credit card " << card_no << " added to node " << m << " " << y << endl;
        cout << "***************" << endl << endl;
    }
        int input;
        do{
        cout << "1)Display List" << endl
        << "2)Card Search via Credit Number" << endl
        << "3)Delete Card with respect to Expiration Date" << endl
        << "4)Exit" << endl << endl;
        
        cout << "Please choose option from the menu: " ;
            cin >> input ;
            if(input == 1){
            cout << endl;
            Sort_and_print(head);
                
            }else if(input == 2){
                cout << endl;
                string card_input;
                do{
                    cout << "Please enter the credit card number: " ;
                    cin >> card_input;
                    if(!CheckCardNumber(card_input))
                        cout << "Invalid format!" << endl;
                }while(!CheckCardNumber(card_input));
    
                Card_exists(head,card_input);
                
            }else if(input == 3){
                cout << endl;
                int month_input, year_input;
                bool Not_deleted = true ;
                
                do {
                    cout << "Please enter month and year: ";
                    
                    if(cin >> month_input >> year_input){
                       
                        if (month_input > 12){
                            cout << "Invalid Date!" << endl;
                        }else{
                            DeleteNode(month_input, year_input, head);
                            Not_deleted = false;
                        }
                    
                    }else{
                        
                        cout << "Invalid Date!" << endl;
                        string error;
                        
                        bool mi = month_input , yi = year_input;
//                      the bool variables mi and yi is used to determine if only one or both inputs cannot be an int value. and clearing them by .clear() function.
                        
                        if (mi || yi){
                            cin.clear();
                            cin >> error;
                        }else{
                            cin.clear();
                            cin >> error;
                            cin.clear();
                            cin >> error;
                            }
                    
                        }
                    
                }while(Not_deleted);
                
            }
        }while(input != 4);
    
    delete_all(head);
    cout << "Terminating!!!" << endl;
    return 0;
}
