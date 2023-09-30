#include <string>

namespace Filesystem {

class file {
public:
    int GetId() const { return id; }
    auto &GetName() const { return FileName_; }

private:
    int id;
    std::string FileName_;
};

struct Permissions {
    bool read_;
    bool write;
    bool Execute;
};

} // namespace Filesystem

int main() {

    auto permissions =
        Filesystem::Permissions{.read_ = true, .write = true, .Execute = false};
    (void)permissions;
    return 0;
}
