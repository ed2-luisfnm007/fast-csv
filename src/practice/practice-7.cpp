#include "../../external/fast-csv/csv.h"
#include "../../external/nlohmann/json.hpp"
#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>

using ComplexCsvReader = io::CSVReader<3,
                                       io::trim_chars<' ', '\t'>,
                                       io::double_quote_escape<',', '"'>>;
using TSVReader = io::CSVReader<4,
                                io::trim_chars<' ', '\t'>,
                                io::no_quote_escape<'\t'>,
                                io::throw_on_overflow,
                                io::single_line_comment<'#'>>;

namespace nl = nlohmann;
namespace fs = std::filesystem;

int main()
{

    fs::path file1 = fs::path(EXAMPLE_DIR) / "practice-5.csv";

    ComplexCsvReader reader(file1);
    reader.read_header(
            io::ignore_extra_column, "order_id", "customer_name", "status");

    int order_id;
    std::string customer_name;
    std::string status;

    std::unordered_map<int, std::string> valid_orders;

    while (reader.read_row(order_id, customer_name, status))
    {
        std::cout << order_id << " " << customer_name << " " << status << "\n";
        if (status != "COMPLETED")
            continue;

        valid_orders[order_id] = customer_name;
    }

    fs::path file2 = fs::path(EXAMPLE_DIR) / "practice-6.tsv";

    TSVReader tsv_reader(file2);
    tsv_reader.set_header("order_id", "item_sku", "quantity", "unit_price");

    int order_id2;
    std::string item_sku;
    int quantity;
    double unit_price;

    std::map<std::string, double> sales_by_customer;

    while (true)
    {
        try
        {
            if (!tsv_reader.read_row(order_id2, item_sku, quantity, unit_price))
                break;

            if (!valid_orders.contains(order_id2))
                continue;

            std::string customer = valid_orders[order_id2];
            double subtotal = quantity * unit_price;

            sales_by_customer[customer] += subtotal;
        }
        catch (const io::error::no_digit &e)
        {
            std::cerr << ">> ERROR: " << e.what() << "\n";
            continue;
        }
    }

    nl::json document;

    auto now = std::chrono::system_clock::now();
    std::string date = std::format("{:%Y-%m-%d}", now);
    document["report_date"] = date;

    nl::json summary = nl::json::array();
    for (const auto &[customer, amount] : sales_by_customer)
    {
        summary.push_back({{"customer", customer}, {"total_spent", amount}});
    }

    document["customers_summary"] = summary;

    fs::path file3 = fs::path(EXAMPLE_DIR) / "customer_sales_report.json";

    std::ofstream out(file3);

    out << document.dump(2);

    out.close();
    return 0;
}