#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <fstream>
using namespace std;

struct Node
{
	char ch;
	int freq;
	int ASC;
	Node *left, *right;
};
// Function for new node
Node* getNode(char ch, int freq, int ASC,  Node* left, Node* right)
{
	Node* node = new Node;
	node->ch = ch;
	node->freq = freq;
	node->ASC = ASC;
	node->left = left;
	node->right = right;
	return node;
}
// Comparision for pq
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		// highest priority item has lowest frequency
		if (l->freq != r->freq) {
			return l->freq > r->freq;
		}
		
		if (l->freq == r->freq) {
			return l->ASC > r->ASC;
		}
	}
};

// generate code
void encode1(Node* root, string str,unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode1(root->left, str+"0", huffmanCode);
	encode1(root->right, str+"1", huffmanCode);
}


// Builds Huffman Tree output files
void buildHuffmanTree(string text)
{
//count frequency
	unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

	// priority queue
	priority_queue<Node*, vector<Node*>, comp> pq;

	// add node for each char
	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, pair.first, nullptr, nullptr));
	}

	while (pq.size() > 1)
	{
		// merge two node with lowest freq
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();

		// add the merged new node
		int sum = left->freq + right->freq;
		int X = 0;
		if(left->ASC<right->ASC) {
			X=left->ASC;
		} else {X = right->ASC;
		}
		if (left->ASC<right->ASC) {
			pq.push(getNode('\0', sum, X, left, right));
		}
		else {pq.push(getNode('\0', sum, X, right, left));
		}
	}

	Node* root = pq.top();


	unordered_map<char, string> huffmanCode;
	encode1(root, "", huffmanCode);
	double sum, count, i = 0;
	string str2 = text;
	sort(str2.begin(), str2.end());
	str2.erase(unique(str2.begin(), str2.end()), str2.end());

	//output.txt
	ofstream outfile1("code.txt");	
	for (auto pair = huffmanCode.begin(); pair != huffmanCode.end(); ++pair) {
		if (str2[i]==' ') {
			outfile1<<  "Space: " << huffmanCode[str2[i]] << '\n';
		} else {
		outfile1<< str2[i] << ": " << huffmanCode[str2[i]] << '\n';}
		sum += pair->second.length()*(freq[pair->first]);
		count+=(freq[pair->first]);
		i++;
	}
	outfile1<<fixed;
	outfile1<<setprecision(2);
	outfile1<<"Ave = "<< sum/count << " bits per symbol"; 
	outfile1.close();

	// print encoded string
	string str = "";
	for (char ch: text) {
		str = str + huffmanCode[ch];
	}
	ofstream outfile("encodemsg.txt");
//	if (str.length()>80) {
//	outfile<<str.substr(0,80) << "\n" << str.substr(80,str.length()) ;
//	}
//	else {
	    outfile<<str;
//	}
	outfile.close();
	
}



// Huffman coding algorithm
int main(int argc, char** argv)
{
	ifstream myfile (argv[1]);
	string line;
	
	if (myfile.is_open()) {
	    while (getline(myfile,line)) {
	    string text = line; 
	}
	myfile.close();
	}
	buildHuffmanTree(line);

	return 0;
}

