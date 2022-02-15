#include <iostream>
#include <string>


constexpr auto tetradeToBin(std::uint8_t const& t) -> std::string_view
{
    switch (t & 0x0f)
    {   default:
        case 0x00: return "0000"; case 0x08: return "1000";
        case 0x01: return "0001"; case 0x09: return "1001";
        case 0x02: return "0010"; case 0x0a: return "1010";
        case 0x03: return "0011"; case 0x0b: return "1011";
        case 0x04: return "0100"; case 0x0c: return "1100";
        case 0x05: return "0101"; case 0x0d: return "1101";
        case 0x06: return "0110"; case 0x0e: return "1110";
        case 0x07: return "0111"; case 0x0f: return "1111";
    }
}



std::string byteToBin(std::uint8_t const b)
{
    return std::string{tetradeToBin(b>>4)} + std::string{tetradeToBin(b)};
}



template <typename T>
std::string toBinaryString(T const& value)
{
    std::string bitString;
    auto const& uintValue = reinterpret_cast<std::uint64_t const&>(value);

    size_t byteIndex=0;
    size_t const byteCount = sizeof(T);

    while (byteIndex < byteCount) {
        bitString += byteToBin(uintValue >> (8*(byteCount-byteIndex-1)));
        ++byteIndex;
    }
    return bitString;
}



int main(int const argc, char** argv)
{
    if (argc<2) {
        std::cout << "Please enter a real number as program argument.\n";
        return -1;
    }

    bool optDecompose = false;
    std::string_view arg {argv[1]};
    if (argc>2) {
        if (arg=="--decompose" || arg=="-d") {
            optDecompose = true;
            arg = argv[2];
        }
    }

    float const value = std::atof(arg.data());
    std::cout<<"value: "<<value<<"\n";

    auto const binString = toBinaryString(value);

    if (!optDecompose) {
        std::cout<<"stored: "<<binString<<"\n";
    }
    else {
        std::cout<<"sign : "<<binString[0]<<"\n";
        std::cout<<"exp  : "<<binString.substr(1,8)<<"\n";
        std::cout<<"mant.: "<<binString.substr(9)<<"\n";
    }
}
