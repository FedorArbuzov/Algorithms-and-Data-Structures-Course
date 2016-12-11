#include <iostream>
#include "rb.cpp"

// create method
void RB_tree::Create(){
    RB_tree();
}

// delete all tree
void RB_tree::Delete() {
    del(root);

}

// function for delete
void RB_tree::del(nd_rb *root_loc) {
    if(root_loc == nullptr){
        return;
    }
    else{
        del(root_loc->left);
        del(root_loc->right);
        delete root_loc;
    }
}

void RB_tree::remove(int k){

    if(root == nullptr){
        return;
    }

    else{

        nd_rb *root_loc = root;
        nd_rb *child1 = nullptr;
        nd_rb *child2 = nullptr;

        bool not_found = true;

        while(root_loc != nullptr && not_found){

            if(root_loc->key == k){
                not_found = false;
            }

            if(not_found){
                if(root_loc->key < k){
                    root_loc = root_loc->right;
                }
                else{
                    root_loc = root_loc->left;
                }
            }

            return;
        }

        if(not_found){
        }
        else{
            if(root_loc->left == nullptr || root_loc->right == nullptr){
                child1 = root_loc;
            }
            else{
                child1 = successor(p);
            }

            if(root_loc->left != nullptr){
                child2 = root_loc->left;
            }
            else{
                if(root_loc->right != nullptr){
                    child2 = root_loc->right;
                }
                else{
                    child2 = nullptr;
                }
            }

            if(child2 != nullptr){
                child2->parent = child1->parent;
            }

            if(child1->parent == nullptr){
                root = q;
            }
            else{
                if(child1==child1->parent->left)
                    child1->parent->left=child2;
                else
                    child1->parent->right=child2;
            }
            if(child1 != root_loc){
                root_loc->color=child1->color;
                root_loc->key=child1->key;
            }
            if(child1->color == true){
                delfix(child2);
            }
        }

    }
}

int main() {
    RB_tree *rb1 = new RB_tree();
    rb1->Create();
    return 0;
}