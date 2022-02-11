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
  auto median = quickselect(newPoints,left,right,(left+right)/2,depth);
  KDTreeNode* newNode = new KDTreeNode(newPoints[median]);
  newNode->left = recursiveConstructor(newPoints,left,median-1,(depth+1)%Dim);
  newNode->right = recursiveConstructor(newPoints,median+1,right,(depth+1)%Dim);
  return newNode;
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& newPoints,int left, int right, unsigned pivotIndex, unsigned dim){
  //setup
auto pivotPoint = newPoints[pivotIndex];
  //swap pivot to end
swap(newPoints[pivotIndex],newPoints[right]);
//
auto storeindex = left;
//loop to sort into greater / less than.
for(int i = left; i<right; i++){
  if(smallerDimVal(newPoints[i],pivotPoint,dim)){
    swap(newPoints[storeindex],newPoints[i]);    //
    storeindex++;
    }
}
  swap(newPoints[right],newPoints[storeindex]);
  return pivotIndex;
}



template <int Dim>
unsigned KDTree<Dim>::quickselect(vector<Point<Dim>>& newPoints,int left, int right, unsigned k,unsigned dim){
  
  if(left == right){return left;}
  
  auto pivotIndex = k;
  pivotIndex = partition(newPoints,left,right,pivotIndex,dim);
  
  if(k == pivotIndex){return k;}
  
  else if(k < pivotIndex){return quickselect(newPoints,left,right,pivotIndex - 1,dim);}
  else{return quickselect(newPoints,left,right,pivotIndex + 1,dim);}

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
    nearest = findNearestHelper1(root,query,nearest,0);
    return findNearestHelper2(root,query,nearest);
    
}
//climbs down the tree, finding deepest close node.
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestHelper1(KDTreeNode* current, const Point<Dim>& query, Point<Dim>& best, int depth) const{
  if(current->left == NULL && current->right == NULL ){
    //we have reached a leaf. we need to know if we should replace now.
    auto result = current->point;
    if(shouldReplace(query,best,result)){return result;}
    else{return best;}
  }
  bool Leftchecker = true;
  bool Rightchecker = true;
  if(current->left == NULL) {Leftchecker = false;}
  if(current->right == NULL) {Rightchecker = false;}

  if(Rightchecker && !Leftchecker){
    return findNearestHelper1(current->right,query,best,(depth+1)%Dim);
  }
  if(Leftchecker && !Rightchecker){
    return findNearestHelper1(current->left,query,best,(depth+1)%Dim);
  }
  //if axis is less than, go left, else go right.
  if(current->point[depth%Dim] < query[depth%Dim]){return findNearestHelper1(current->left,query,best,(depth+1)%Dim);}
  else{return findNearestHelper1(current->left,query,best,(depth+1)%Dim);}

  return best;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestHelper2(KDTreeNode* current, const Point<Dim>& query, Point<Dim>& best) const{
    return query;

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