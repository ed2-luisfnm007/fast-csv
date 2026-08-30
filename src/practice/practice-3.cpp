#include "../../external/fast-csv/csv.h"

#include <format>
#include <iostream>
#include <string>

int main()
{
    try
    {

        io::CSVReader<5,
                      io::trim_chars<' ', '\t'>,
                      io::double_quote_escape<',', '"'>>
                reader("src/practice/practice-3-files/practice-3(2).csv");

        reader.read_header(io::ignore_extra_column | io::ignore_missing_column,
                           "id",
                           "nombre",
                           "edad",
                           "salario",
                           "bono");

        int id;
        std::string nombre;
        int edad;
        double salario;
        double bono;

        if (!reader.has_column("id"))
        {
            std::cerr << "Error: la columna OBLIGATORIA id no existe\n";
            return 1;
        }

        if (!reader.has_column("nombre"))
        {
            std::cerr << "Error: la columna OBLIGATORIA nombre no existe\n";
            return 1;
        }

        if (!reader.has_column("edad"))
        {
            std::cerr << "Error: la columna OBLIGATORIA edad no existe\n";
            return 1;
        }

        if (!reader.has_column("salario"))
        {
            std::cerr << "Error: la columna OBLIGATORIA salario no existe\n";
            return 1;
        }

        bool hasBonus = reader.has_column("bono");

        while (reader.read_row(id, nombre, edad, salario, bono))
        {
            std::string bonus = (hasBonus) ? std::to_string(bono) : "SIN BONO";

            std::cout << std::format(
                    "{}\t{}\t{}\t{}\t{}\n", id, nombre, edad, salario, bonus);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}