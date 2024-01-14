#include<iostream>
#include <string>
#include <vector>
#include <array>
using namespace std;
struct Node{
    float c;
    int p;
    Node* Next;
};
const int array_size=30;

array<string,array_size> splitString(const std::string& input, const std::string& delimiters) {
    array<string,array_size> result;
    size_t startPos = 0;
    size_t foundPos;
    int index=0;
    string sign;
    while ((foundPos = input.find_first_of(delimiters, startPos)) != std::string::npos) {
        std::string substring = input.substr(startPos, foundPos - startPos);
        if (!substring.empty()) {
            result[index]=(sign+substring);
        }
        sign = input[foundPos];
//        cout<<"sign: "<< sign<<endl;
        startPos = foundPos + 1;
        index++;
    }

    std::string lastSubstring = input.substr(startPos);
    if (!lastSubstring.empty()) {

        result[index]=(sign+lastSubstring);
    }

    return result;
}

void create_node(const array<string,array_size>& v, array<Node*,array_size>& vn) {
    Node* prevNode = nullptr;

    for (int i = 0; i < v.size(); i++) {
        if (!v[i].empty()) {
            float c;
            int p;
            size_t xPos = v[i].find('x');

            if (xPos == string::npos) {
                string substr = v[i].substr(0, xPos);
                if (!substr.empty()) {
                    c = stof(substr);
                    p = 0;
                }

            } else {
                size_t caretPos = v[i].find('^');

                if (caretPos == string::npos) {
                    p = 1;
                } else {
                    p = stoi(v[i].substr(caretPos + 1));
                }
                string substr = v[i].substr(0, xPos);
                c = stof(substr);
            }

            Node *newNode = new Node{c, p, nullptr};

            if (prevNode != nullptr) {
                prevNode->Next = newNode;
            }

            vn[i] = newNode;
            prevNode = newNode;
        }
    }
}
array<Node*,array_size> sort_nodes(array<Node*,array_size>& nodes) {
    array<Node*,array_size> sorted_nodes={nullptr};
    for (int i = 0; i < array_size; i++) {
        Node* biggest_node = nullptr;
        int index_of_biggest=0;
        for (int j = 0; j < array_size; j++) {
            if (nodes[j] != nullptr) {
                if (biggest_node == nullptr || nodes[j]->p > biggest_node->p) {
                    biggest_node = nodes[j];
                    index_of_biggest=j;
                }
            }
        }
        nodes[index_of_biggest]= nullptr;
        sorted_nodes[i]=biggest_node;
        if(i!=0&&sorted_nodes[i]!= nullptr){
            sorted_nodes[i-1]->Next=sorted_nodes[i];
        }
    }


    return sorted_nodes;
}
void sumNodesWithSameP(std::array<Node*, array_size>& nodes) {
    int c =0;
    for(int i=0;i<=nodes.size();i++){
        if(nodes[i]!= nullptr){
        for (int j=i+1;j<=nodes.size();j++){
            if(nodes[j]!= nullptr) {
                if (nodes[i]->p == nodes[j]->p) {
//                    cout << "c: " << nodes[j]->c << " p: " << nodes[j]->p << " next: " << nodes[j]->Next << endl;
                    nodes[i]->c += nodes[j]->c;
                    nodes[i]->Next = nodes[j]->Next;
//                    cout << "p c: " << nodes[i]->c << " p p: " << nodes[i]->p << " p next: " << nodes[i]->Next << endl;
                    nodes[j] = nullptr;
                    c++;
                }
            }

        }
        }

    }
}
void show_last_result(array<Node*,array_size>nodes){
    cout<<"last result: "<<endl;
    for(const auto node:nodes){
        if (node!= nullptr){

        if(node->p!=0){
            if(node->c>0){
                if(node->p!=1){

                    cout<<"+"<<node->c<<"x"<<"^"<<node->p;
                }
                else{
                    cout<<"+"<<node->c<<"x";

                }
            }
            else{
                if(node->p!=1){

                    cout<<node->c<<"x"<<"^"<<node->p;
                }
                else{
                    cout<<node->c<<"x";

                }
            }
        }
        else{
            if(node->c>0){
                cout<<"+"<<node->c<<endl;
            }
            else{
                cout<<"-"<<node->c<<endl;
            }
        }
        }

    }
}
int main() {
    string input;
//    input="15x+2x^2";
    getline(cin, input);
    array<string,array_size> result = splitString(input, "+-");
    array<Node*,array_size> nodes={nullptr};

    create_node(result, nodes);
    sumNodesWithSameP(nodes);
    nodes = sort_nodes(nodes);
    for (const auto& node : nodes) {
        if (node!= nullptr)
        cout << "c: " << node->c << " p: " << node->p <<" next: "<<node->Next<< endl;
    }
    show_last_result(nodes);

}
