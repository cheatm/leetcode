#include <iostream>
#include <vector>

using namespace std;

struct TSNode{
    int val;
    TSNode * left;
    TSNode * right;
    int rcount;
    int count;
    int depth;

    TSNode(int _val): val(_val){
        left = NULL;
        right=NULL;
        rcount = 0;
        count = 1;
        depth = 1;
    }

    int ldepth(){
        if(left!=NULL) return left->depth;
        else return 0;
    }

    int rdepth(){
        if(right!=NULL) return right->depth;
        else return 0;
    }

    TSNode * lrotation(TSNode * root) {
        TSNode * temp;
        if(root->left->ldepth() > root->left->rdepth()){
            // LL
            temp = root;
            
            root = root->left;
            temp -> left = root->right;
            root -> left = temp;
            root->rcount = root->rcount + temp->count + temp->rcount;
            return root;
        }else{
            // LR
            temp = root-> left -> right;

            root -> left-> right = temp->left;
            temp -> left = root->left;

            root -> left = temp->right;
            
            temp -> right = root;

            temp -> left -> rcount = temp -> left -> rcount - temp->rcount - temp-> count;
            temp -> rcount = temp -> rcount + root->count + root->rcount;
            return temp;
        }
    }

    int add(int _val){
        if(_val<val){
            if(left==NULL){
                left = new TSNode(_val);
                if(right==NULL){
                    depth++;
                }
                return count + rcount;
            }else{
                // return left->add(_val) + count + rcount ;
                int result = left->add(_val);
                if(left->ldepth() - left->rdepth()>1){
                    left = lrotation(left);

                }
                return result + count + rcount;
                
            }
        }else if(val < _val){
            rcount++;
            if(right==NULL){
                right = new TSNode(_val);
                if(left==NULL){
                    depth++;
                }
                return right->rcount;
            }else{
                int result = right->add(_val);
                if(rdepth() - ldepth() > 1) {
                    
                }else{
                    return result;
                }

            }
        }else{
            count++;
            return rcount;
        }
    }
};


class Solution {
public:
    int reversePairs(vector<int>& nums) {
        if(nums.size()<2){
            return 0;
        }
        
        int result = 0;
        TSNode tree(nums[0]);
        for(int i=1; i < nums.size(); i++){
            result = result + tree.add(nums[i]);
        }

        return result;
    }
};


int main(){
    vector<int> nums({7,5,6,4});

    Solution solution;
    int r = solution.reversePairs(nums);
    cout << r << endl;

}
