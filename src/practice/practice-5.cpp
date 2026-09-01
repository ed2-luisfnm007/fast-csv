#include "../../external/fast-csv/csv.h"
#include <algorithm>
#include <format>
#include <iostream>
#include <string>

using ComplexCsvReader = io::CSVReader<4,
                                       io::trim_chars<' ', '\t'>,
                                       io::double_quote_escape<',', '"'>>;

int main()
{

    ComplexCsvReader reader("src/practice/csv/practice-5.csv");

    reader.read_header(io::ignore_extra_column,
                       "order_id",
                       "customer_name",
                       "shipping_address",
                       "status");

    int order_id;
    std::string customer_name;
    std::string shipping_address;
    std::string status;

    while (reader.read_row(order_id, customer_name, shipping_address, status))
    {
        if (std::ranges::find(shipping_address, '#') != shipping_address.end())
        {
            continue;
        }

        if (status == "CANCELLED")
            continue;

        std::cout << std::format(
                "{} {} {}\n", order_id, customer_name, shipping_address);
    }

    return 0;
}