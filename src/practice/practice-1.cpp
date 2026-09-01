#include "../../external/fast-csv/csv.h"
#include <format>
#include <iostream>
#include <vector>

struct Venta
{
    std::string producto;
    double precio;
    int cantidad;
    std::string sucursal;
};

int main()
{
    io::CSVReader<4> reader("src/practice/csv/ventas.csv");

    reader.read_header(io::ignore_extra_column, "producto", "precio", "cantidad", "sucursal");

    std::vector<Venta> sells;
    Venta sell;

    while (reader.read_row(sell.producto, sell.precio, sell.cantidad, sell.sucursal))
    {
        sells.push_back(sell);
    }

    double total = 0;

    for (const Venta &v : sells)
    {
        if (v.sucursal != "SPS")
            continue;

        total += v.precio * v.cantidad;

        if ((v.precio * v.cantidad) <= 2000)
            continue;

        std::cout << std::format("{}\t{}\t{}\t{}\n", v.producto, v.precio, v.cantidad, v.sucursal);
    }

    std::cout << std::format("Total SPS: {:.2f}\n", total);
}
