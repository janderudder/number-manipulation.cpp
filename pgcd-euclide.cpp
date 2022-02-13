/*
    Variante de l'algorithme d'Euclide pour le PGCD de deux entiers relatifs,
    selon

    Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest et
    Clifford Stein, Introduction à l'algorithmique, Dunod, 2004, 2e éd.,
    (ISBN 2 10 003922 9)

*/
#include <array>
#include <cmath>
#include <iostream>
#include <string_view>



////////////////////////////////////////////////////////////////////////////////
using Number = unsigned long long;



////////////////////////////////////////////////////////////////////////////////
static struct
{
    bool debug = false;
}options;



////////////////////////////////////////////////////////////////////////////////
auto parseInput(int const argc, char const* const* argv)-> std::array<Number, 2>
{
    int numbersIndex = 1;

    for (int i=numbersIndex; i<argc; ++i)
    {
        auto const argument = std::string_view{argv[i]};

        if (std::atoi(argument.data()) == 0 && argument[0] != '0')
        {
            ++numbersIndex;
            if (argument == "--debug" || argument == "-d") {
                options.debug = true;
            }
            else if (argument == "--") {

            }
            else {
                std::cerr << "unrecognized argument: " << argument << "\n";
            }
        }
    }

    auto const strToAbsNum = [](const char* str) -> Number {
        return std::abs(std::atoi(str));
    };

    return {
        strToAbsNum(argv[numbersIndex]),
        strToAbsNum(argv[numbersIndex+1])
    };
}



////////////////////////////////////////////////////////////////////////////////
auto sortAB(Number const n1, Number const n2) -> std::array<Number, 2>
{
    if (n1 < n2) {
        return {n2, n1};
    }
    return {n1, n2};
}



////////////////////////////////////////////////////////////////////////////////
Number pgcd(Number const n1, Number const n2)
{
    auto const [a, b] = sortAB(n1, n2);

    if (options.debug) {
        std::cerr << "pgcd(" << n1 << ", " << n2 << ")\n";
        std::cerr << "  a = " << a << "\n";
        std::cerr << "  b = " << b << "\n";
    }

    if (b==0) {
        return a;
    }
    return pgcd(b, a%b);
}



////////////////////////////////////////////////////////////////////////////////
int main(int const argc, char const* const* argv)
{
    if (argc < 3) {
        std::cerr << "Please pass two whole numbers as argument.\n";
        return EXIT_FAILURE;
    }

    auto const [a, b] = parseInput(argc, argv);
    auto const p = pgcd(a, b);

    std::cout << "pgcd: " << p << "\n";

    return EXIT_SUCCESS;
}
