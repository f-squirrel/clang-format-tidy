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

    auto permissions    = Filesystem::Permissions{};
    permissions.Execute = false;
    permissions.write   = false;
    permissions.read_   = true;

    return 0;
}
