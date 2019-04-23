#ifndef TWOPHASEBST_H
#define TWOPHASEBST_H

#include <iostream>
#include <string>
#include <stack>
#include <list>
// do not add any other library.
// modify parts as directed by assignment text and comments here.

template <class T>
class TwoPhaseBST {
private: //do not change
    struct SecondaryNode {
        std::string key;
        T data;
        SecondaryNode *left;
        SecondaryNode *right;

        SecondaryNode(const std::string &k, const T &d, SecondaryNode *l, SecondaryNode *r);
    };

    struct PrimaryNode {
        std::string key;
        PrimaryNode *left;
        PrimaryNode *right;
        SecondaryNode *rootSecondaryNode;

        PrimaryNode(const std::string &k, PrimaryNode *l, PrimaryNode *r, SecondaryNode *rsn);
    };

public: // do not change.
    TwoPhaseBST();
    ~TwoPhaseBST();

    TwoPhaseBST &insert(const std::string &primaryKey, const std::string &secondaryKey, const T &data);
    TwoPhaseBST &remove(const std::string &primaryKey, const std::string &secondaryKey);
    TwoPhaseBST &print(const std::string &primaryKey = "", const std::string &secondaryKey = "");
    T *find(const std::string &primaryKey, const std::string &secondaryKey);

private: // you may add your own utility member functions here.
    void destructNode(PrimaryNode * &root);
    void destructNode(SecondaryNode * &root);
    
    TwoPhaseBST<T>::PrimaryNode *findPrim(TwoPhaseBST<T>::PrimaryNode* look, const std::string & key){
	    if (look == NULL){
			return NULL;
		}
		else if ( look->key.compare(key) == 0 ){
			return look;
		}
		else {
			PrimaryNode* tmp;
			tmp = findPrim(look->left, key);
			if ( tmp ){
				return tmp;
			}
			else {
				return findPrim(look->right, key);
			}
		}
	}
	
	TwoPhaseBST<T>::SecondaryNode *findSec(TwoPhaseBST<T>::SecondaryNode* look, const std::string & key){
	    if (look == NULL){
			return NULL;
		}
		else if ( look->key.compare(key) == 0 ){
			return look;
		}
		else {
			SecondaryNode* tmp;
			tmp = findSec(look->left, key);
			if ( tmp ){
				return tmp;
			}
			else {
				return findSec(look->right, key);
			}
		}
	}


	void printHelper( PrimaryNode* node, int & n ){
		if (node == NULL) {
			return ;
		}
		else {
			printHelper(node->left, n);
			if ( n == 1 ){
				std::cout << ", ";
			}
			printPrim(node);
			n = 1;
			printHelper(node->right, n);
		}
	}

	void printPrim( PrimaryNode* prim ){
		int x = 0;
		std::cout << "\"" << prim->key <<"\" : " ;
		std::cout << "{";
		printSec( prim->rootSecondaryNode, x );
		std::cout << "}";
	}

	void printSec( SecondaryNode* sec, int & n ){
		if (sec == NULL) {
			return ;
		}
		else {
			printSec( sec->left, n );
			if (n == 1){
				std::cout << ", ";
			}
			std::cout <<"\""<< sec->key <<"\" : \""<< sec->data <<"\"";
			n = 1;
			printSec( sec->right, n );
		}
	}

	TwoPhaseBST<T>::SecondaryNode *findPrevSec(TwoPhaseBST<T>::SecondaryNode* look, TwoPhaseBST<T>::SecondaryNode* element){
		if ( look == NULL ){
			return NULL;
		}
		else if (look->left == element or look->right == element){
			return look;
		}
		else {
			SecondaryNode* tmp;
			tmp = findPrevSec( look->left, element );
			if ( tmp ){
				return tmp;
			}
			else {
				return findPrevSec( look->right, element );
			}
		}
	}

private: // do not change.
    PrimaryNode *root; //designated root.

    // do not provide an implementation. TwoPhaseBST's are not copiable.
    TwoPhaseBST(const TwoPhaseBST &);
    const TwoPhaseBST &operator=(const TwoPhaseBST &);
};

template <class T>
TwoPhaseBST<T>::SecondaryNode::SecondaryNode(const std::string &k, const T &d, SecondaryNode *l, SecondaryNode *r)
        : key(k), data(d), left(l), right(r) {}

template <class T>
TwoPhaseBST<T>::PrimaryNode::PrimaryNode(const std::string &k, PrimaryNode *l, PrimaryNode *r, SecondaryNode *rsn)
        : key(k), left(l), right(r), rootSecondaryNode(rsn) {}

template <class T>
TwoPhaseBST<T>::TwoPhaseBST() : root(NULL) {}

template <class T>
TwoPhaseBST<T>::~TwoPhaseBST() {
    destructNode(root);
}

template <class T>
TwoPhaseBST<T> &
TwoPhaseBST<T>::insert(const std::string &primaryKey, const std::string &secondaryKey, const T &data) {
	if (root == NULL){
		SecondaryNode* tmp2 = new SecondaryNode(secondaryKey, data, NULL, NULL);
		PrimaryNode* tmp = new PrimaryNode(primaryKey, NULL, NULL, tmp2);
		root = tmp;
	}
	else {
		PrimaryNode* tmpx = root;
		int k = 0;
		while(tmpx){
			if (primaryKey.compare(tmpx->key) < 0 ){
				if (tmpx->left == NULL) {
					k = 1;
					break;
				}
				else {
					tmpx = tmpx->left;					
				}

			}
			else if (primaryKey.compare(tmpx->key) > 0 ){
				if (tmpx->right == NULL) {
					k = 2;
					break;
				}
				else {
					tmpx = tmpx->right;					
				}
			}
			else {
				break;
			}
		}
		//std::cout << tmpx->key << std::endl;
		if (tmpx->key == primaryKey){ // FOUND
			SecondaryNode* newsec = new SecondaryNode(secondaryKey, data, NULL, NULL);
			int z = 0;
			
			SecondaryNode* rootsec = tmpx ->rootSecondaryNode;
			
			while (rootsec){
				//std::cout << rootsec->key<< " "<<secondaryKey.compare(rootsec->key) << std::endl;
				if ( secondaryKey.compare(rootsec->key) < 0 ){
					if (rootsec -> left == NULL){
						z = 1;
						break;
					}
					else {
						rootsec = rootsec->left;
					}
				}
				else if ( secondaryKey.compare(rootsec->key) > 0 ){
					if (rootsec -> right == NULL){
						z = 2;
						break;
					}
					else {
						rootsec = rootsec->right;
					}
				}
				
				else {
					std::cout << "HATA" << std::endl;
					break;
				}
			}
			
			if (z == 1){
				rootsec->left = newsec;
			}
			else if (z == 2){
				rootsec->right = newsec;
			}		
		}
		
		else {
			SecondaryNode* newsec = new SecondaryNode(secondaryKey, data, NULL, NULL);
			PrimaryNode* newprim = new PrimaryNode(primaryKey, NULL, NULL, newsec);
			if (k == 1){
				tmpx->left = newprim;
			}
			else if (k == 2){
				tmpx->right = newprim;
			}
		}
		
		
	}
	return *this;
}

template <class T>
TwoPhaseBST<T> &
TwoPhaseBST<T>::remove(const std::string &primaryKey, const std::string &secondaryKey) {
		PrimaryNode* tmp = findPrim(root, primaryKey);
		if (tmp){
			SecondaryNode* tmp2 = findSec(tmp->rootSecondaryNode,secondaryKey);
			if (tmp2){
				//std::cout << "left,right of root: " << root->rootSecondaryNode->left << " " << root->rootSecondaryNode->right << std::endl;
				if (tmp->rootSecondaryNode == tmp2){
					//std::cout << "root silinecek node a esit " << tmp2->key << std::endl;
					//std::cout << "left,right : " << tmp2->left << " " << tmp2->right << std::endl;
					if (tmp2 -> left == NULL and tmp2->right == NULL){
						//std::cout << "iki child da null" << std::endl;
						tmp->rootSecondaryNode = NULL;
						delete tmp2;
					}
					else if (tmp2 -> left == NULL or tmp2->right == NULL){
						if (tmp2->left == NULL){
							tmp->rootSecondaryNode = tmp2->right;
						}
						else {
							tmp->rootSecondaryNode = tmp2->left;
						}
						delete tmp2;
					}
					else { // BOTH IS FULL
						//std::cout << "iki child var" << std::endl;
						SecondaryNode* leftchild = tmp2->left;
						
						while (leftchild->right != NULL){
							leftchild = leftchild->right;
						}
						SecondaryNode* prevOfLeft = findPrevSec(tmp->rootSecondaryNode, leftchild);
						
						//std::cout << "onceki ve left" << prevOfLeft->key << " "<< leftchild->key << std::endl;

						SecondaryNode* leftofleft = leftchild->left;
						tmp->rootSecondaryNode = new SecondaryNode(leftchild->key, leftchild->data, tmp2->left, tmp2->right);
						
						if (prevOfLeft->left == leftchild){
							if (leftofleft!=NULL){
								tmp->rootSecondaryNode->left = leftofleft;
							}
							else {
								tmp->rootSecondaryNode->left = NULL;
							}
							
						}
						else if (prevOfLeft->right == leftchild){
							if (leftofleft!=NULL){
								prevOfLeft->right = leftofleft;
							}
							else {
								prevOfLeft->right = NULL;
							}
							
						}
						delete leftchild;
						delete tmp2;
					}
				}
				else if ( tmp2 ->left == NULL and tmp2->right == NULL ){ //leaf node
					//std::cout << "silinecek node leaf node " << tmp2->key << std::endl;
					SecondaryNode* prevNode = findPrevSec(tmp->rootSecondaryNode, tmp2);
					//std::cout << prevNode->key << std::endl;
					if (prevNode->left == tmp2){
						prevNode->left = NULL;
					}
					else if (prevNode->right == tmp2){
						prevNode->right = NULL;
					}
					delete tmp2;
				}
				else if ( tmp2 ->left == NULL or tmp2->right == NULL ){ //one child
					//std::cout << "one child li node siliniyor "<< tmp2->key << std::endl;
					if ( tmp2->left == NULL ){ //left null	
						SecondaryNode* prevNode = findPrevSec(tmp->rootSecondaryNode, tmp2);
						if (prevNode->left == tmp2){
							prevNode->left = tmp2->right;
						}
						else if (prevNode->right == tmp2){
							prevNode->right = tmp2->right;
						}
					}
					else { // right null
						SecondaryNode* prevNode = findPrevSec(tmp->rootSecondaryNode, tmp2);
						if (prevNode->left == tmp2){
							prevNode->left = tmp2->left;
						}
						else if (prevNode->right == tmp2){
							prevNode->right = tmp2->left;
						}
					}
					delete tmp2;
				}
				else if ( tmp2 ->left != NULL and tmp2->right != NULL ){ // two children
					//std::cout << "two childli node siliniyor " << tmp2->key << std::endl;
					SecondaryNode* leftchild = tmp2->left;
					SecondaryNode* beftmp2 = findPrevSec(tmp->rootSecondaryNode, tmp2);
					
					while (leftchild->right != NULL){
						leftchild = leftchild->right;
					}
					SecondaryNode* prevOfLeft = findPrevSec(tmp->rootSecondaryNode, leftchild);
					
					SecondaryNode* newtmp2 = new SecondaryNode(leftchild->key,leftchild->data,tmp2->left,tmp2->right);
					
					if (beftmp2->left == tmp2){
						beftmp2->left = newtmp2;
					}
					else if (beftmp2->right == tmp2){
						beftmp2->right = newtmp2;
					}
					
					prevOfLeft = findPrevSec(tmp->rootSecondaryNode,leftchild);
					
					if (prevOfLeft->left == leftchild){
						if (leftchild->left!=NULL){
							prevOfLeft->left = leftchild->left;
						}
						else {
							prevOfLeft->left = NULL;
						}
						
					}
					else if (prevOfLeft->right == leftchild){
						if (leftchild->left!=NULL){
							prevOfLeft->right = leftchild->left;
						}
						else {
							prevOfLeft->right = NULL;
						}	
					}
					delete tmp2;
					delete leftchild;
					//std::cout << tmp->rootSecondaryNode->key << " " << 	tmp->rootSecondaryNode->left->key << " " << tmp->rootSecondaryNode->left->left << std::endl;
				}
			}
		}
		return *this;
}

template <class T>
TwoPhaseBST<T> &TwoPhaseBST<T>::print(const std::string &primaryKey, const std::string &secondaryKey) {
	if ( primaryKey != "" and secondaryKey != "" ){
		PrimaryNode* tmp = findPrim(root, primaryKey);
		
		if (tmp){
			SecondaryNode* tmp2 = findSec(tmp->rootSecondaryNode,secondaryKey);
			if (tmp2){
				std::cout << "{\"" << tmp->key << "\" : {\""<<tmp2->key<<"\" : \""<<tmp2->data<<"\"}}"<<std::endl;
			}
			else {
				std::cout << "{}" << std::endl;
			}
		}
		else {
			std::cout << "{}" << std::endl;
		}
		
	}
	else if ( primaryKey != "" and secondaryKey == "" ){
		PrimaryNode* tmp = findPrim(root, primaryKey);
		if ( tmp ){
			std::cout << "{";
			printPrim(tmp);
			std::cout << "}" << std::endl;
		}
		else {
			std::cout << "{}" << std::endl;
		}
	}
	else if ( primaryKey == "" and secondaryKey == "" ){
		int x = 0;
		std::cout << "{";
		printHelper(root, x);
		std::cout << "}" << std::endl;
	}
	else {
		
	}
	
	return *this;
	

}

template <class T>
T *TwoPhaseBST<T>::find(const std::string &primaryKey, const std::string &secondaryKey) {
	PrimaryNode* tmp = findPrim(root, primaryKey);
	if ( tmp ){
		SecondaryNode* tmp2 = findSec(tmp->rootSecondaryNode,secondaryKey);
		if ( tmp2 ){
			return &tmp2->data;
		}
	}
	return NULL;
}

template <class T>
void TwoPhaseBST<T>::destructNode(TwoPhaseBST::PrimaryNode * &root)
{
    if (root == NULL)
        return;

    destructNode(root->left);
    destructNode(root->right);

    destructNode(root->rootSecondaryNode);

    delete root;

    root = NULL;
}

template <class T>
void TwoPhaseBST<T>::destructNode(TwoPhaseBST::SecondaryNode * &root)
{
    if (root == NULL)
        return;

    destructNode(root->left);
    destructNode(root->right);

    delete root;

    root = NULL;
}

#endif //TWOPHASEBST_H
