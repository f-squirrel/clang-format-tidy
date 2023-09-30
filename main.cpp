#include <string>
#include <vector>

namespace Filesystem { // CamelCase instead of lower_case

enum class Permissions : uint8_t { READ, WRITE, execute };

struct User {
    std::string name_; // redundant suffix _ for public member
    int Id = 0;        // CamelCase instead of lower_case
    Permissions permissions;
};

class file { // lower_case instead of CamelCase
public:
    file(int id, const std::string &file_name,
         const std::vector<User> access_list)
        : id{id}, FileName_{file_name}, access_list_{access_list} {}

    int GetId() const // CamelCase instead of lower_case
    {
        return id;
    }
    auto &getName() const // camelBack instead of lower_case
    {
        return FileName_;
    }

    const std::vector<User> &access_list() const { return access_list_; }

private:
    int id;                // missing suffix _
    std::string FileName_; // CamelCase instead of lower_case
    std::vector<User> access_list_;
};

} // namespace Filesystem

int main() {

    auto user        = Filesystem::User{};
    user.name_       = "user";
    user.permissions = Filesystem::Permissions::execute;

    auto file = Filesystem::file{0, "~/home/user/file", {user}};

    return 0;
}
