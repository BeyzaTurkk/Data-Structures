#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iterator>
#include "doublelinklist.h"
#include "objects.h"


using namespace std;

// nodes to create a stack, using template func to be able  use different kind of values
template <typename T>
struct Stack_Node {
    T data;
    Stack_Node* next;
    Stack_Node(const T& data) : data(data), next(nullptr) {}
};

//stack implementation without using STL
template <typename T>
struct Stack {
    Stack_Node<T>* top_node;
    int stack_size;

    Stack() : top_node(nullptr), stack_size(0) {}

    ~Stack() {
        while (!is_empty()) {
            pop();
        }
    }

     T top() const {
        if (!is_empty()) {
            return top_node->data;
        }
        else {
            cout<<"Stack is empty!" << endl;
        }
    }
    
    bool is_empty() const {
        return top_node == nullptr;
    }

    void push(const T& data) {
        Stack_Node<T>* new_node = new Stack_Node<T>(data);
        new_node->next = top_node;
        top_node = new_node;
        ++stack_size;
    }

    void pop() {
        if (!is_empty()) {
            Stack_Node<T>* old = top_node;
            top_node = top_node->next;
            delete old;
            --stack_size;
        }
        else {
             cout<<"Stack is empty!"<<endl;
        }
    }


};

void game_is_not_going_to_over_until_i_win(GameState &current_state) //simulates the game by exploring different actions and their consequences
{
    Stack<GameState> state_stack;
    state_stack.push(current_state);

    if (current_state.win){

        cout << "YOU HAVE WON THE GAME!!" << endl;
        return;
    }

    while (!state_stack.is_empty()){
    
        GameState current_state = state_stack.top();
        state_stack.pop();

       // current_state.print_situation();

        for (int action = 1; action <= 5; ++action)
        {
            for (int object = 0; object < current_state.rooms.get(current_state.room_id)->room_objects.elemcount; ++object)
            {
                GameState new_state = current_state;
                int result = new_state.advance(action, object);

                if (new_state.win)
                {
                    cout << "YOU HAVE WON THE GAME!!" << endl;
                    return;
                }
                if (result != 0)
                {
                    if (new_state.room_id != current_state.room_id)// To push only changing room actions, to be able to use necessary scenerios 
                    {
                        
                        state_stack.push(new_state);  
                    }
                    else if (result > 0)
                    {
                        game_is_not_going_to_over_until_i_win(new_state); //recursively call to iterate every possible scenerio 

                        return;
                    }
                }
            }
        }
    }
}

int main()
{
    GameState first_state;
    first_state.create_init_state();
    game_is_not_going_to_over_until_i_win(first_state);

    /*while (!first_state.lose && !first_state.win)
    {
        first_state.print_situation();
        int action, object;
        cout << "Select action: 1-Open 2-Look At 3-Pick Up 4- Misbehave 5- Talk To: ";
        cin >> action;
        cout << "Select object: ";
        cin >> object;
         first_state.advance(action, object);//You may use effectID to check whether your last action changed something...
    }*/
    

    return 0;
}



