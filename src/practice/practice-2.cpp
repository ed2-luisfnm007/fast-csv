#include "../../external/fast-csv/csv.h"

#include <iostream>

int main()
{
    io::CSVReader<5,
                  io::trim_chars<' ', '\t'>,
                  io::double_quote_escape<';', '"'>,
                  io::throw_on_overflow,
                  io::single_line_comment<'#'>>
            reader("src/practice/csv/empleados.csv");

    reader.set_header("id", "nombre", "edad", "ciudad", "salario");
    int id;
    std::string nombre;
    int edad;
    std::string ciudad;
    double salario;

    while (reader.read_row(id, nombre, edad, ciudad, salario))
    {
        std::cout << id << "\t" << nombre << "\t" << edad << "\t" << ciudad << "\t" << salario
                  << "\n";
    }

    return 0;
}
