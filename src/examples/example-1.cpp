#include "../../external/fast-csv/csv.h"
#include <format>
#include <iostream>
#include <string>

int main()
{

    io::CSVReader<3> reader("src/examples/products.csv");

    reader.read_header(io::ignore_extra_column, "name", "price", "quantity");

    std::string name = "";
    double price = 0;
    int quantity = 0;

    while (reader.read_row(name, price, quantity))
    {
        double total = price * quantity;
        std::cout << std::format("{}\t{}\n", name, total);
    }
    return 0;
}