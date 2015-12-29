/* Node is defined as :
typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
} node; */

int balanceFactor(node* root)
{
    int left = -1;
    int right = -1;
    if(root != NULL){
        //cout<<"ROOT<"<<root->val<<"> ";
        if(root->left != NULL){
            left = root->left->ht;
          //  cout<<"left ht="<<left<<" ";
        }
        if(root->right != NULL){
            right = root->right->ht;
            //cout<<"right ht="<<right<<" ";
        }
    }
    //cout<<"bf="<<left-right<<endl;
    return left - right;
}

int calculateHeight(node * root)
{
    int left = -1;
    int right = -1;
    if(root != NULL){
        if(root->left != NULL)
            left = root->left->ht;
        if(root->right != NULL)
            right = root->right->ht;
        return max(left,right) + 1;
    }
    return 0;
}

void recalculateHeights(node * root)
{
    if(root != NULL){
        recalculateHeights(root->left);
        recalculateHeights(root->right);
        root->ht = calculateHeight(root);
    }
}

node * insertValue(node* root, int val)
{
    if(root == NULL){
        root = new node();
        root->val = val;
        root->left = NULL;
        root->right = NULL;
    }else if(val > root->val){
        root->right = insertValue(root->right, val);
    }else if(val < root->val){
        root->left = insertValue(root->left, val);
    }else{
        //cout<<"Value is equal!"<<endl;
    }
    recalculateHeights(root);
    return root;
}

node * left_left(node* root)
{
    node * left_child = root->left;
    node * right_child = root->right;
    node * left_right_child = root->left->right;

    root->left = left_right_child;
    left_child->right = root;
    root = left_child;
    
    recalculateHeights(root);
    
    return root;
}

node * left_right(node* root)
{
    node * left_child = root->left;
    node * left_right_child = root->left->right;
    node * left_right_left_child = root->left->right->left;
    root->left = left_right_child;
    left_child->right = left_right_left_child;
    left_right_child->left = left_child;
    
    recalculateHeights(root);
    
    root = left_left(root);
    
    return root;
}

node * right_right(node * root)
{
    node * right_child = root->right;
    node * left_child = root->left;
    node * right_left_child = root->right->left;
    
    root->right = right_left_child;
    right_child->left = root;
    root = right_child;
    
    recalculateHeights(root);
    
    return root;
}

node * right_left(node * root)
{
    node * right_child = root->right;
    node * right_left_child = root->right->left;
    node * right_left_right_child = root->right->left->right;
    
    root->right = right_left_child;
    right_child->left = right_left_right_child;
    right_left_child->right = right_child;
    
    recalculateHeights(root);
    
    root = right_right(root);
    
    return root;
}

node * rebalance(node * root)
{
    if(root != NULL)
    {
        root->left = rebalance(root->left);
        root->right = rebalance(root->right);
        
        int bf = balanceFactor(root);
        if(bf < -1 || bf > 1){
            // needs rebalance
            // which case?
            if(bf > 1){
                // left-right || left-left
                int left_bf = balanceFactor(root->left);
                if(left_bf < 0){
                    // left-right
                    root = left_right(root);
                }else{
                    // left-left
                    root = left_left(root);
                }
            }else{
                // right-left || right-right
                int right_bf = balanceFactor(root->right);
                if(right_bf > 0){
                    // right-left
                    root = right_left(root);
                }else{
                    // right-right
                    root = right_right(root);
                }
            }
            recalculateHeights(root);
        }
    }
    return root;
}

void printTree(node * root)
{
    if(root != NULL){
        cout<<root->val<<"(BF="<<balanceFactor(root)<<") ";
        
        printTree(root->left);
        printTree(root->right);
    }
}

node * insert(node * root,int val)
{
    recalculateHeights(root);
   // insert the element in the corresponding position
    insertValue(root, val);
    // rebalance (4 cases)
    root = rebalance(root);
    return root;
}
