#include "Huffman.h"
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <queue>

namespace huffman_tree {

int HuffmanNode::get_frequency() const noexcept {
    return frequency_;
}

bool HuffmanNode::is_leaf() const noexcept {
    return left_ == nullptr &&
           right_ == nullptr;
}

HuffmanNode& HuffmanNode::get_left() noexcept {
    assert(left_ != nullptr);
    return *left_;
}

HuffmanNode & HuffmanNode::get_right() noexcept {
    assert(right_ != nullptr);
    return *right_;
}

unsigned char HuffmanNode::get_symbol() const noexcept {
    assert(this != nullptr);
    return symbol_.value();
}


HuffmanNode& HuffmanTree::get_root() noexcept {
    assert(root_ != nullptr);
    return *root_;
}

void HuffmanTree::get_codes_from_tree(HuffmanNode& node, std::vector<bool>& current_code) {
    if (node.is_leaf()) {
        symbol_to_codes_[node.get_symbol()] = current_code; 
        return;
    }
    current_code.push_back(true);
    get_codes_from_tree(node.get_right(), current_code);
    current_code.back() = false;
    get_codes_from_tree(node.get_left(), current_code);
    current_code.pop_back();
}

HuffmanNode HuffmanTree::extract_min_node(std::queue<HuffmanNode>& new_nodes,
                                      std::queue<HuffmanNode>& old_nodes) {
    if (new_nodes.size() == 0 || (old_nodes.size() > 0 
          && old_nodes.front().get_frequency() < new_nodes.front().get_frequency())) {
        HuffmanNode min_node = std::move(old_nodes.front());
        old_nodes.pop();
        return min_node;
    }
    else {
        HuffmanNode min_node = std::move(new_nodes.front());
        new_nodes.pop();
        return min_node;
    }
}

HuffmanTree::HuffmanTree(std::vector<int32_t> symbol_to_frequency) {
    std::vector<std::pair<int32_t, unsigned char>> sorted_symb;
    for (int32_t ch = 0; ch < MAX_CODE; ch++) {
        if (symbol_to_frequency[ch] != 0) {
            sorted_symb.push_back({symbol_to_frequency[ch], static_cast<unsigned char>(ch)});
        }
    }
    std::sort(sorted_symb.begin(), sorted_symb.end());
    std::queue<HuffmanNode> new_nodes;
    std::queue<HuffmanNode> old_nodes;
    for (const auto[fr, ch] : sorted_symb) {
        HuffmanNode node(fr, ch);
        old_nodes.push(std::move(node));
    }
    while (old_nodes.size() + new_nodes.size() > 1u) {
        HuffmanNode fst = std::move(extract_min_node(new_nodes, old_nodes));
        HuffmanNode snd = std::move(extract_min_node(new_nodes, old_nodes));
        new_nodes.push(std::move(HuffmanNode{std::make_unique<HuffmanNode>(std::move(fst)),
                                             std::make_unique<HuffmanNode>(std::move(snd))}));
    } 
    if (old_nodes.size() != 0) {
        swap(old_nodes, new_nodes);
    }
    //if tree is not empty
    if (new_nodes.size() == 1u) {
        root_ = std::make_unique<HuffmanNode>(std::move(new_nodes.front()));
        std::vector<bool> code;
        if (root_->is_leaf()) {
            code.push_back(true);
        }
        get_codes_from_tree(*root_, code);
    }
}

const std::vector<std::vector<bool>>& HuffmanTree::get_codes() const noexcept {
    return symbol_to_codes_;
}

}
