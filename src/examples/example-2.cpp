#include "../../external/fast-csv/csv.h"
#include <format>
#include <iostream>
#include <string>
#include <vector>

struct Product
{
    int code;
    std::string name;
    double price;
    int quantity;
};

int main()
{
    io::CSVReader<4> reader("src/examples/csv/products.csv");

    reader.read_header(io::ignore_extra_column, "code", "name", "price", "quantity");

    std::vector<Product> products;

    Product product;

    while (reader.read_row(product.code, product.name, product.price, product.quantity))
    {
        products.push_back(product);
    }

    for (const auto &p : products)
    {
        std::cout << std::format("{}\t{}\t{}\t{}\n", p.code, p.name, p.price, p.quantity);
    }
}
