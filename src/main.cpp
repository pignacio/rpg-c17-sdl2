#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/cereal.hpp>
#include <fstream>
#include <iostream>
#include <vector>


class Test {
  public:
    explicit Test(int x, int y) : _x{x}, _y{y} {}

    template <class Archive>
    void serialize(Archive &ar, [[gnu::unused]] uint32_t version) {
        std::cout << "serialize:Version: " << version << std::endl;
        ar(CEREAL_NVP(_x));
        if (version > 1) {
            ar(CEREAL_NVP(_y));
        }
    }

    void lala() const {
        std::cout << "Values are: " << _x << ", " << _y << std::endl;
    }

  private:
    int _x;
    int _y;
};

CEREAL_CLASS_VERSION(Test, 2); // NOLINT

auto main() -> int {
    Test test{101, 203};
    {
        std::ofstream out{"/tmp/test2.bin"};
        cereal::BinaryOutputArchive ar{out};
        ar(CEREAL_NVP(test));
    }

    std::ifstream instream{"/tmp/test2.bin"};
    cereal::BinaryInputArchive inar{instream};

    Test otest{1, 2};
    otest.lala();

    inar(CEREAL_NVP(otest));
    otest.lala();

    return 0;
}
