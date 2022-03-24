#include <queue>
#include <vector>
#include <fstream>
#include "Helper.hpp"
#include "HCTree.hpp"
#include <stdio.h>
#include <stack>
using namespace std;


        /**
         * Use the Huffman algorithm to build a Huffman coding tree.
         * PRECONDITION: freqs is a vector of ints, such that freqs[i] is the frequency of occurrence of byte i in the input file.
         * POSTCONDITION: root points to the root of the trie, and leaves[i] points to the leaf node containing byte i.
         */

         
         void print(struct HCNode* node)
         {
               if (node == NULL)
                 return;
                print(node->c0);
              cout << "Symbol: " << node -> symbol << endl;
              cout << "Count of nodes: " << node -> count << endl;
              print(node->c1);
         }

        void HCTree::build(const vector<int>& freqs)
        {
                priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
                for(unsigned int i = 0; i < freqs.size();i++)
                {
                        if(freqs[i] != 0)
                        {
                        unsigned char c = i;
                        HCNode* node = new HCNode(freqs[i],c);
                        leaves[i] = node;
                        pq.push(node);
                        }
                }
                while(pq.size() > 1)
                {
                        HCNode* left = pq.top();
                        pq.pop();
                        HCNode* right = pq.top();
                        pq.pop();
                        HCNode* node = new HCNode(left -> count + right -> count, left -> symbol);
                        node -> c0= left;
                        node -> c1 = right;
                        left -> p = node;
                        right -> p = node;
                        pq.push(node);
                        root = pq.top();
                }
               
                //cout << root -> symbol;
             //   print(root);

        }

        void del(struct HCNode* node)
         {
               if (node == NULL)
                 return;
                del(node->c0);
              del(node->c1);
              delete node;
         }


        HCTree::~HCTree()
         {
            del(root);
            root = NULL;
           
         }


        /**
         * Write to the given FancyOutputStream the sequence of bits coding the given symbol.
         * PRECONDITION: build() has been called, to create the coding tree, and initialize root pointer and leaves vector.
         */
        void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const
        {
                stack<int> st;
                HCNode* curr;
                unsigned int num = (unsigned int)symbol;
                curr = leaves[num];
                while(curr != root)
                {
                        HCNode* p2 = curr -> p;
                        if(curr == p2 -> c0)
                        {
                                st.push(0);
                              //  cout << "0";
                        }
                        else
                        {
                                st.push(1);
                               // cout << "1";
                        }
                        curr = p2;
                }
                while(st.size() != 0)
                {
                       //cout << st.top();
                        out.write_bit(st.top());
                        st.pop();
                }
        }

        /**
         * Return symbol coded in the next sequence of bits from the stream.
         * PRECONDITION: build() has been called, to create the coding tree, and initialize root pointer and leaves vector.
         */
        unsigned char HCTree::decode(FancyInputStream & in) const
        {
                HCNode* curr = HCTree::root;
                while(true)
                {
                        if(in.read_bit() == 0)
                        {
                                curr = curr -> c0;
                        }
                        else
                        {
                                curr = curr -> c1;
                        }
                        for(unsigned int i = 0; i < leaves.size(); i++)
                        {
                                if(leaves.at(i) == curr)
                                {
                                  //cout << curr -> symbol;      
                                  return curr -> symbol;
                                }
                        }
    
                }
        }

