#include "../../external/fast-csv/csv.h"
#include <iostream>

using TSVReader = io::CSVReader<4,
                                io::trim_chars<' ', '\t'>,
                                io::no_quote_escape<'\t'>,
                                io::throw_on_overflow,
                                io::single_line_comment<'#'>>;

int main()
{
    TSVReader reader("src/practice/csv/practice-6.tsv");
    reader.set_header("order_id", "item_sku", "quantity", "unit_price");

    int order_id;
    std::string item_sku;
    int quantity;
    double unit_price;

    double total = 0;

    while (true)
    {
        try
        {
            if (!reader.read_row(order_id, item_sku, quantity, unit_price))
                break;

            total += quantity * unit_price;
        }
        catch (const io::error::no_digit &e)
        {
            std::cerr << ">> ERROR: " << e.what() << "\n";
            continue;
        }
    }

    std::cout << ">> TOTAL: " << total << "\n";

    return 0;
}