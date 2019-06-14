#include <vector>
template<typename ValType>
class TreeNode {

public:
    ValType value;
    std::vector<TreeNode<ValType> *> children;
    TreeNode(ValType val):value(val) {}
    TreeNode(ValType val,std::vector<TreeNode<ValType>*> _children):value(val),children(_children) {}
    void add_child(TreeNode<ValType> *child){
        children.push_back(child);
    }
};
