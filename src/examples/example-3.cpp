#include "../../external/fast-csv/csv.h"

#include <iostream>
#include <string>

int main()
{
    try
    {
        io::CSVReader<4,
                      io::trim_chars<' ', '\t'>,
                      io::double_quote_escape<',', '"'>,
                      io::throw_on_overflow,
                      io::single_line_comment<'#'>>
                reader("src/examples/empleados_invalidos.csv");

        reader.read_header(io::ignore_no_column, "id", "nombre", "edad", "salario");

        int id;
        std::string nombre;
        int edad;
        double salario;

        while (reader.read_row(id, nombre, edad, salario))
        {
            if (id <= 0)
            {
                std::cerr << "ID inválido en fila: " << reader.get_file_line() << "\n";
                continue;
            }

            if (nombre.empty())
            {
                std::cerr << "Nombre vacío en fila: " << reader.get_file_line() << "\n";
                continue;
            }

            if (edad < 0 || edad > 120)
            {
                std::cerr << "Edad inválida en fila: " << reader.get_file_line() << "\n";
                continue;
            }

            std::cout << id << ' ' << nombre << ' ' << edad << " " << salario << '\n';
        }
    }
    catch (const io::error::missing_column_in_header &e)
    {
        std::cerr << "Header incompleto: " << e.what() << '\n';
    }
    catch (const io::error::duplicated_column_in_header &e)
    {
        std::cerr << "Header duplicado: " << e.what() << '\n';
    }
    catch (const io::error::too_few_columns &e)
    {
        std::cerr << "Fila incompleta: " << e.what() << '\n';
    }
    catch (const io::error::too_many_columns &e)
    {
        std::cerr << "Fila con columnas extra: " << e.what() << '\n';
    }
    catch (const io::error::no_digit &e)
    {
        std::cerr << "Número inválido: " << e.what() << '\n';
    }
    catch (const io::error::integer_overflow &e)
    {
        std::cerr << "Overflow: " << e.what() << '\n';
    }
    catch (const io::error::escaped_string_not_closed &e)
    {
        std::cerr << "Comillas inválidas: " << e.what() << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}