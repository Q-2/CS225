/**
 * @file huffman_tree.cpp
 * Implementation of a Huffman Tree class.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

#include "huffman_tree.h"

using namespace std;

HuffmanTree::HuffmanTree(vector<Frequency> frequencies)
{
    std::stable_sort(frequencies.begin(), frequencies.end());
    buildTree(frequencies);
    vector<bool> path;
    buildMap(root_, path);
}

HuffmanTree::HuffmanTree(const HuffmanTree& other)
{
    copy(other);
}

HuffmanTree::HuffmanTree(BinaryFileReader& bfile)
{
    root_ = readTree(bfile);
    vector<bool> path;
    buildMap(root_, path);
}

HuffmanTree::~HuffmanTree()
{
    clear(root_);
}

const HuffmanTree& HuffmanTree::operator=(const HuffmanTree& rhs)
{
    if (this != &rhs) {
        clear(root_);
        copy(rhs);
    }
    return *this;
}

void HuffmanTree::clear(TreeNode* current)
{
    if (current == NULL)
        return;
    clear(current->left);
    clear(current->right);
    delete current;
}

void HuffmanTree::copy(const HuffmanTree& rhs)
{
    root_ = copy(rhs.root_);
}

HuffmanTree::TreeNode* HuffmanTree::copy(const TreeNode* current)
{
    if (current == NULL)
        return NULL;
    TreeNode* node = new TreeNode(current->freq);
    node->left = copy(current->left);
    node->right = copy(current->right);
    return node;
}

HuffmanTree::TreeNode* HuffmanTree::removeSmallest(queue<TreeNode*>& singleQueue,
                                                    queue<TreeNode*>& mergeQueue)
{

    /**
     * 
     *
     * Remove the smallest TreeNode * from the two queues given as
     * parameters. The entries on the queues are in sorted order, so the
     * smaller of the two queues heads is the smallest item in either of
     * the queues. Return this item after removing it from its queue.
     */
    TreeNode* theNode;
    TreeNode* singleNode;
    TreeNode* mergeNode;
    if(!singleQueue.empty() && mergeQueue.empty()) {
        auto i = singleQueue.front();
        singleQueue.pop();
        return i;
        }
    if(singleQueue.empty() && !mergeQueue.empty()) {
        auto i = mergeQueue.front();
        mergeQueue.pop();
        return i;
        }
    if(singleQueue.empty() && mergeQueue.empty()) {auto i = NULL;}
    if(singleQueue.front()->freq < mergeQueue.front()->freq) {
        auto i = singleQueue.front();
        singleQueue.pop();
        return i;
        }
    else{
        auto i = mergeQueue.front();
        mergeQueue.pop();
        return i;
        }













    //check the original queue for the smallest value it has
   /** for(queue<TreeNode*> singleTemp ; !singleQueue.empty();) {
        //base case
        if(singleTemp.empty()) {
            singleNode = singleQueue.front();
            singleTemp.push(singleQueue.front());
            singleQueue.pop();
            continue;
        }
        //general case
        if(singleQueue.front()->freq < singleNode->freq) {
            singleTemp.push(singleNode);
            singleTemp.push(singleQueue.front());
            singleNode = singleQueue.front();
            singleQueue.pop();
            continue;
        }
        //if not smaller
        singleTemp.push(singleQueue.front());
        singleQueue.pop();
        //if singlequeue is empty, exit. reinstate. toss the temp. better for memory this way.
        if(singleQueue.empty()) {
            singleQueue = singleTemp;
            break;
        }
        continue;
    }
    //same loop but for merge now!!!!!
    for(queue<TreeNode*> mergeTemp ; !mergeQueue.empty();) {
        //base case
        if(mergeTemp.empty()) {
            mergeNode = mergeQueue.front();
            mergeTemp.push(mergeQueue.front());
            mergeQueue.pop();
            continue;
        }
        //general case
        if(mergeQueue.front()->freq < mergeNode->freq) {
            mergeTemp.push(mergeNode);
            mergeTemp.push(mergeQueue.front());
            mergeNode = mergeQueue.front();
            mergeQueue.pop();
            continue;
        }
        //if not smaller
        mergeTemp.push(mergeQueue.front());
        mergeQueue.pop();
        //if mergequeue is empty, exit. reinstate. toss the temp. better for memory this way.
        if(mergeQueue.empty()) {
            mergeQueue = mergeTemp;
            break;
        }
        continue;
    }
    //we got the two smallest of the two; now we just gotta put back the one that's bigger, and return the smaller
    if(singleNode < mergeNode) {
        mergeQueue.push(mergeNode);
        return singleNode;
    }
    else{
        singleQueue.push(singleNode);
        return mergeNode;
    }
    //it's a whole lot of writing but really it isn't that bad!!!!
**/
}   



void HuffmanTree::buildTree(const vector<Frequency>& frequencies)
{
    queue<TreeNode*> singleQueue; // Queue containing the leaf nodes
    queue<TreeNode*> mergeQueue;  // Queue containing the inner nodes

    for(unsigned int i = 0; i < frequencies.size(); i++ ){
        TreeNode* cur = new TreeNode(frequencies[i]);
        singleQueue.push(cur);
    }
    while((singleQueue.size() + mergeQueue.size()) > 1) {
        auto first = removeSmallest(singleQueue,mergeQueue);
        auto second = removeSmallest(singleQueue,mergeQueue);
        TreeNode* third = new TreeNode(Frequency(first->freq.getFrequency() + second->freq.getFrequency()));
        third->left = first;
        third->right = second;
        mergeQueue.push(third);
    }
    root_ = mergeQueue.front();

    /**
     * First, place all of the leaf nodes into the singleQueue in
     * increasing order of frequency. Note: frequencies is already sorted
     * for you.
     *
     * Next, until there is only one node on the two queues (that is, one
     * of the queues is empty and one has a single node), remove the two
     * smallest entries from the two queues. Then, create a new internal
     * node with these nodes as children, whose frequency is the sum of
     * these two children's frequencies. Place the new internal node onto
     * the back of the mergeQueue.
     *
     * Finally, when there is a single node left, it is the root. Assign it
     * to the root and you're done!
     */

}

string HuffmanTree::decodeFile(BinaryFileReader& bfile)
{
    stringstream ss;
    decode(ss, bfile);
    return ss.str();
}

void HuffmanTree::decode(stringstream& ss, BinaryFileReader& bfile)
{
    TreeNode* current = root_;
    while (bfile.hasBits()) {

        if(bfile.getNextBit()) {
            current = current->right;
        }
        else{
            current = current->left;
        }
        if(current->left == NULL && current->right == NULL) {
            ss << current->freq.getCharacter();
            current = root_;
        }
        /**
         *
         *
         * This code is reading in all of the bits in the binary file
         * given. After reading a bit, we go left if the bit was a 0 (or
         * false), and we go right if the bit was a 1 (or true).
         *
         * Special case: if we are at a leaf node, we should "print" its
         * character to the stringstream (with operator<<, just like cout)
         * and start traversing from the root node again.
         */
    }
}

void HuffmanTree::writeTree(BinaryFileWriter& bfile)
{
    writeTree(root_, bfile);
}

void HuffmanTree::writeTree(TreeNode* current, BinaryFileWriter& bfile)
{
    if(!current->left && !current->right){
        bfile.writeBit(true);
        bfile.writeByte(current->freq.getCharacter());
    }
    else{
        bfile.writeBit(0);
        writeTree(current->left,bfile);
        writeTree(current->right,bfile);
        
    }
    /**
     * @todo Your code here!
     *
     * This code is writing the current HuffmanTree in a compressed format
     * to the given BinaryFileWriter. The strategy for doing so is as
     * follows:
     *      1. If we are a leaf node, write the bit "1" followed by the
     *         byte that is the character of this node.
     *      2. If we are an internal node, writ the bit "0", and then
     *         encode the left and right subtree, recursively.
     *
     * Note that we don't encode the frequencies in this compressed
     * version: this is fine, as the structure of the tree still reflects
     * what the relative frequencies were.
     */
}

HuffmanTree::TreeNode* HuffmanTree::readTree(BinaryFileReader& bfile)
{
    while(bfile.hasBits()){
        if(bfile.getNextBit()){
            TreeNode* leaf = new TreeNode(Frequency(bfile.getNextByte(),0));
            return leaf;
        }
        else{
            TreeNode* stem = new TreeNode(0);
            stem->left = readTree(bfile);
            stem->right = readTree(bfile);
            return stem;
        }
    }
    return NULL;
    /**
     * @todo Your code here!
     *
     * This code is reading a HuffanTree in from a file in the format that
     * we wrote it above. The strategy, then, is as follows:
     *      1. If the file has no more bits, we're done.
     *      2. If we read a 1 bit, we are a leaf node: create a new
     *         TreeNode with the character that is the next byte in the
     *         file (its frequency should be 0, since we are ignoring
     *         frequency data now).
     *      3. If we read a 0 bit, create a new internal node (with
     *         frequency 0, since we are ignoring them now, and set its left
     *         child and right children to be the subtrees built recursively.
     *      4. Your function should return the TreeNode it creates, or NULL
     *         if it did not create one.
     */


}

void HuffmanTree::buildMap(TreeNode* current, vector<bool>& path)
{
    // Base case: leaf node.
    if (current->left == NULL && current->right == NULL) {
        bitsMap_[current->freq.getCharacter()] = path;
        return;
    }

    // Move left
    path.push_back(false);
    buildMap(current->left, path);
    path.pop_back();

    // Move right
    path.push_back(true);
    buildMap(current->right, path);
    path.pop_back();
}

void HuffmanTree::printInOrder() const
{
    printInOrder(root_);
    cout << endl;
}

void HuffmanTree::printInOrder(const TreeNode* current) const
{
    if (current == NULL)
        return;
    printInOrder(current->left);
    cout << current->freq.getCharacter() << ":" << current->freq.getFrequency()
         << " ";
    printInOrder(current->right);
}

void HuffmanTree::writeToFile(const string& data, BinaryFileWriter& bfile)
{
    for (auto it = data.begin(); it != data.end(); ++it)
        writeToFile(*it, bfile);
}

void HuffmanTree::writeToFile(char c, BinaryFileWriter& bfile)
{
    vector<bool> bits = getBitsForChar(c);
    for (auto it = bits.begin(); it != bits.end(); ++it)
        bfile.writeBit(*it);
}

vector<bool> HuffmanTree::getBitsForChar(char c)
{
    return bitsMap_[c];
}

// class for generic printing

template <typename TreeNode>
class HuffmanTreeNodeDescriptor
    : public GenericNodeDescriptor<HuffmanTreeNodeDescriptor<TreeNode>>
{
  public:
    HuffmanTreeNodeDescriptor(const TreeNode* root) : subRoot_(root)
    { /* nothing */
    }

    string key() const
    {
        std::stringstream ss;
        char ch = subRoot_->freq.getCharacter();
        int freq = subRoot_->freq.getFrequency();

        // print the sum of the two child frequencies
        if (ch == '\0')
            ss << freq;
        // print the leaf containing a character and its count
        else {
            if (ch == '\n')
                ss << "\\n";
            else
                ss << ch;
            ss << ":" << freq;
        }
        return ss.str();
    }

    bool isNull() const
    {
        return subRoot_ == NULL;
    }
    HuffmanTreeNodeDescriptor left() const
    {
        return HuffmanTreeNodeDescriptor(subRoot_->left);
    }
    HuffmanTreeNodeDescriptor right() const
    {
        return HuffmanTreeNodeDescriptor(subRoot_->right);
    }

  private:
    const TreeNode* subRoot_;
};

int HuffmanTree::height(const TreeNode* subRoot) const
{
    if (subRoot == NULL)
        return -1;
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

void HuffmanTree::print(std::ostream& out) const
{
    int h = height(root_);
    if (h > _max_print_height) {
        out << "Tree is too big to print. Try with a small file (e.g. "
               "data/small.txt)"
            << endl;
        return;
    }

    printTree(HuffmanTreeNodeDescriptor<TreeNode>(root_), out);
}

Frequency
HuffmanTree::testRemoveSmallest(vector<Frequency> single,
                                vector<Frequency> merge)
{
    queue<TreeNode*> singleQueue;
    queue<TreeNode*> mergeQueue;
    for (auto it = single.begin(); it != single.end(); ++it) {
         singleQueue.push(new TreeNode(*it));
    }
    for (auto it = merge.begin(); it != merge.end(); ++it) {
         mergeQueue.push(new TreeNode(*it));
    }

    TreeNode* testNode = removeSmallest(singleQueue, mergeQueue);
    Frequency testFreq = testNode->freq;

    delete testNode;
    while (!singleQueue.empty()) {
        delete singleQueue.front();
        singleQueue.pop();
    }
    while (!mergeQueue.empty()) {
        delete mergeQueue.front();
        mergeQueue.pop();
    }

    return testFreq;
}
