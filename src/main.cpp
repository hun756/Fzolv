#include <cstdio>
#include <vector.hpp>

int main(int argc, char const *argv[])
{
    static_cast<void>(fprintf(stdout, "%s\n", "Hi from Fzolv :)"));
    static_cast<void>(fprintf(stdout, "%s\n", "===============>"));

    auto poit1 = Fzolv::Vector2<float>();
    poit1.x = 1.5F;
    poit1.y = 3.5F;

    static_cast<void>(fprintf(stdout, "{ %s : %f , %s : %f }", "X", poit1.x, "Y", poit1.y));
    return 0;
}
