#include "doctest.h"
#include "Huffman.h"

using namespace huffman_tree;

TEST_CASE("test ordinary constructor") {
    HuffmanNode node(1 , 'c');
    CHECK(node.get_symbol() == 'c');
    CHECK(node.get_frequency() == 1);
    CHECK(node.is_leaf());
    HuffmanNode node1 = {2, 'b'};
    CHECK(node1.get_symbol() == 'b');
    CHECK(node1.get_frequency() == 2);
    CHECK(node1.is_leaf());
} 

TEST_CASE("test constructor from 2 nodes") {
    HuffmanNode node1(1 , 'c');
    HuffmanNode node2(2 , 'd');
    HuffmanNode node3(std::make_unique<HuffmanNode>(std::move(node1)), std::make_unique<HuffmanNode>(std::move(node2)));
    CHECK(node3.get_left().get_symbol() == 'c');
    CHECK(node3.get_right().get_symbol() == 'd');
    CHECK(node3.get_left().get_frequency() == 1);
    CHECK(node3.get_right().get_frequency() == 2);
    CHECK(!node3.is_leaf());
    CHECK(node3.get_frequency() == 3);
    CHECK(node3.get_left().is_leaf());
    CHECK(node3.get_right().is_leaf());
} 

TEST_CASE("test rvalue constructor") {
    HuffmanNode node(1, 'c');
    HuffmanNode node1(std::move(node));
    CHECK(node1.is_leaf()); 
    CHECK(node1.get_frequency() == 1);
    CHECK(node1.get_symbol() == 'c');
}

TEST_CASE("test rvalue operator=") {     
    HuffmanNode node(6, ' ');
    HuffmanNode node1(4, 's');
    node1 = std::move(node);
    CHECK(node1.is_leaf()); 
    CHECK(node1.get_frequency() == 6);
    CHECK(node1.get_symbol() == ' ');
}

TEST_CASE("test tree with 0 elem") {   
    std::vector<int32_t> v(256, 0);
    HuffmanTree tree(v);
    std::vector<std::vector<bool>> a = tree.get_codes();
    for (int32_t i = 0; i < 256; i++) {
        CHECK(a[i] == std::vector<bool> {});
    }
}

TEST_CASE("test tree with only 1 elem") {   
    std::vector<int32_t> v(256, 0);
    v[static_cast<unsigned char> ('a')] = 5;  
    HuffmanTree tree(v);
    std::vector<std::vector<bool>> a = tree.get_codes();
    for (int32_t i = 0; i < 256; i++) {
        if (static_cast<unsigned char>(i) == 'a') {
            CHECK(a[i]== std::vector<bool> {true});
        }
        else {
            CHECK(a[i] == std::vector<bool> {});
        }
    }
}

TEST_CASE("test tree with only 2 elem") {   
    std::vector<int32_t> v(256, 0);
    v[static_cast<unsigned char> ('a')] = 6;  
    v[static_cast<unsigned char> ('b')] = 7; 
    HuffmanTree tree(v);
    std::vector<std::vector<bool>> a = tree.get_codes();
    for (int32_t i = 0; i < 256; i++) {
        if (static_cast<unsigned char>(i) == 'a') {
            CHECK(a[i] == std::vector<bool> {false});
        }
        else if (static_cast<unsigned char>(i) == 'b') {
            CHECK(a[i] == std::vector<bool> {true});
        }
        else {
            CHECK(a[i] == std::vector<bool> {});
        }
    }
}

TEST_CASE("test tree with biggest elem") {   
    std::vector<int32_t> v(256, 0);
    v[static_cast<unsigned char> ('s')] = 4;  
    v[static_cast<unsigned char> ('d')] = 2;
    v[static_cast<unsigned char> ('f')] = 2;
     
    HuffmanTree tree(v);
    std::vector<std::vector<bool>> a = tree.get_codes();
    for (int32_t i = 0; i < 256; i++) {
        if (static_cast<unsigned char>(i) == 's') {
            CHECK(a[i] == std::vector<bool> {true});
        }
        else if (static_cast<unsigned char>(i) == 'd') {
            CHECK(a[i] == std::vector<bool> {false, false});
        }
        else if (static_cast<unsigned char>(i) == 'f') {
            CHECK(a[i] == std::vector<bool> {false, true});
        }
        else {
            CHECK(a[i] == std::vector<bool> {});
        }
    }
}
