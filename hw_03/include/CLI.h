#ifndef CLI_H_
#define CLI_H_

#include <vector>
#include <string> 
#include <stdexcept>

namespace cli {

enum class Mode {
    extract, compress
};

struct ArgParseException final : public std::logic_error {
    using std::logic_error::logic_error;
};

class CLI final {
public:
    CLI(std::vector<std::string> command);
    const std::string& get_input_file() const noexcept;
    const std::string& get_output_file() const noexcept;
    Mode get_mode() const noexcept;
private:
    std::string input_;
    std::string output_;
    Mode mode_;
    std::vector<std::string> command_;
};

}
#endif
