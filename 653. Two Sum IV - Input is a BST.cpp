/*
Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.

Example 1:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9

Output: True
Example 2:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28

Output: False
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        vector<int> ino;
        inotra(root,ino);
        int l=0,r=ino.size()-1;
        while(l<r){
            int sum=ino[l]+ino[r];
            if(sum==k) return true;
            if(sum<k) ++l;
            if(sum>k) --r;
        }
        return false;
    }
    void inotra(TreeNode *r,vector<int> &v){
        if(r){
            inotra(r->left,v);
            v.push_back(r->val);
            inotra(r->right,v);
        }
    }
};
