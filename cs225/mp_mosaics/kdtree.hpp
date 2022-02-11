/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) {return true;}
    if (second[curDim] < first[curDim]) {return false;}
    return first < second;

}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double potentialSum = 0;
    double currentBestSum = 0;
    for(int i = 0; i < Dim; i++){
      //instead of including .math i did the simple way.
     potentialSum += (potential[i] - target[i])*(potential[i] - target[i]);
     currentBestSum += (currentBest[i] - target[i])*(currentBest[i] - target[i]);
    }
    if(potentialSum == currentBestSum) {return currentBest > potential;} //tiebreak lol
    return currentBestSum > potentialSum;
    //no need to square root for comparison; square root of a larger thing will always be larger than a square root of a smaller thing;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
  size = 0;
  if(newPoints.empty()){return;}
  auto points_2 = newPoints;
  root = recursiveConstructor(points_2,0,newPoints.size()-1,0);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::recursiveConstructor(vector<Point<Dim>>& newPoints,int left,int right,int depth){
  if(left > right){return NULL;}
  size++;
  size_t medinadex = (left+right)/2;
  auto median = quickselect(newPoints,left,right,medinadex,depth);
  KDTreeNode* newNode = new KDTreeNode(median);
  newNode->left = recursiveConstructor(newPoints,left,medinadex-1,(depth+1)%Dim);
  newNode->right = recursiveConstructor(newPoints,medinadex+1,right,(depth+1)%Dim);
  return newNode;
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& newPoints,int left, int right, unsigned pivotIndex, unsigned dim){
  //setup
  auto pivotPoint = newPoints[pivotIndex];
  swap(newPoints[pivotIndex], newPoints[right]);  // Move pivot to end
  size_t storeIndex = left;
  for(int i = left; i < right; i++){
    if(smallerDimVal(newPoints[i], pivotPoint, dim)){
      swap(newPoints[storeIndex], newPoints[i]);
      storeIndex++;
    }
  }
  swap(newPoints[right], newPoints[storeIndex]);  // Move pivot to its final place
  return storeIndex;
}



template <int Dim>
Point<Dim> KDTree<Dim>::quickselect(vector<Point<Dim>>& newPoints,int left, int right, unsigned k,unsigned dim){
  
  if(left == right){return newPoints[left];}
  
  auto pivotIndex = k;
  pivotIndex = partition(newPoints,left,right,pivotIndex,dim);
  
  if(k == pivotIndex){return newPoints[k];}
  
  else if(k < pivotIndex){return quickselect(newPoints,left,pivotIndex-1,k,dim);}
  else{return quickselect(newPoints,pivotIndex+1,right,k,dim);}

}



  template <int Dim>
  KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
    /**
   * @todo Implement this function!
   */
  //why does this have to be recursive :(
    copy(root,other.root);
    size = other.size;
    //ig this isn't so ugly.hmmm

}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if(this != NULL){clear(root);}
  copy(this->root, rhs.root);
  size = rhs.size;
  


  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  clear(this->root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> nearest = root->point;
    Point<Dim> temp = query;
    findNN(root,nearest,temp,0);
    return nearest;
}
//climbs down the tree, finding deepest close node.
template <int Dim>
void KDTree<Dim>::findNN(KDTreeNode* curRoot, Point<Dim> &currentBest, Point<Dim> &query, int dim) const{
    if(curRoot == NULL){return;}
    //setup which
    KDTreeNode* first;
    KDTreeNode* second;
    if(smallerDimVal(curRoot->point, query, dim))
    {first = curRoot->right;}
    else{first = curRoot->left;}
    
    if(first == curRoot->left)
    {second = curRoot->right;}
    else{second = curRoot->left;}

    findNN(first, currentBest, query, (dim + 1) % Dim);
    if(shouldReplace(query, currentBest, curRoot->point)){
      currentBest = curRoot->point;
    }
//god bless the ama slides
//end of part 1. beginning of part 2
    double radius = 0.0;
    //squaredDist
    for(int i = 0; i < Dim; i++){
      radius += (currentBest[i] - query[i]) * (currentBest[i] - query[i]);
    }
    //splitDist
    double splitDist =  (curRoot->point[dim] - query[dim]) * (curRoot->point[dim] - query[dim]);
    if(radius >= splitDist){
      findNN(second, currentBest, query, (dim + 1) % Dim);
    }
}


template <int Dim>
void KDTree<Dim>::assignHalves(KDTreeNode * current, const Point<Dim>& query, int depth, KDTreeNode* & first, KDTreeNode* & second){
//whoops
}



//recursive copy (yes it's necessary, no i don't want it to be)
template <int Dim>
void KDTree<Dim>::copy(KDTreeNode * first, KDTreeNode * second) {
	first = new KDTreeNode();
	first->point = second->point;
	copy(first->left, second->left);
	copy(first->right, second->right);
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode * first) {
	if (first == NULL) return;
	if (first->left != NULL) clear(first->left);
	if (first->right != NULL) clear(first->right);
	delete first;
	first = NULL;
}