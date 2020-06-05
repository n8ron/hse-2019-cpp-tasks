#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include <climits>
#include <queue>

constexpr int32_t MAX_CODE = 1 << CHAR_BIT;

namespace huffman_tree {

class HuffmanNode final {
public:
    HuffmanNode(int32_t frequency, std::optional<unsigned char> symbol) noexcept : frequency_(frequency), symbol_(symbol) {}
    HuffmanNode(std::unique_ptr<HuffmanNode> left, std::unique_ptr<HuffmanNode> right) noexcept : frequency_(left->frequency_ + right->frequency_)
                                                                                    , symbol_(std::nullopt)
                                                                                    , left_(std::move(left))
                                                                                    , right_(std::move(right)) {}
    int get_frequency() const noexcept;
    bool is_leaf() const noexcept;
    HuffmanNode& get_left() noexcept;
    HuffmanNode& get_right() noexcept;
    unsigned char get_symbol() const noexcept;
    
private:

    int32_t frequency_ = 0;
    std::optional<unsigned char> symbol_ = {};
    std::unique_ptr<HuffmanNode> left_;
    std::unique_ptr<HuffmanNode> right_;
};

class HuffmanTree final {
public:
    explicit HuffmanTree(std::vector<int32_t>);
    HuffmanNode& get_root() noexcept;
    const std::vector<std::vector<bool>>& get_codes() const noexcept;
private:
     
    static HuffmanNode extract_min_node(std::queue<HuffmanNode>&, std::queue<HuffmanNode>&); 

    void get_codes_from_tree(HuffmanNode&, std::vector<bool>&);

    std::unique_ptr<HuffmanNode> root_ = nullptr;

    std::vector<std::vector<bool>> symbol_to_codes_ = std::vector<std::vector<bool>> (MAX_CODE);
};

}
#endif
