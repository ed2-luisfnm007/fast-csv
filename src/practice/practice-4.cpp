#include "../../external/fast-csv/csv.h"
#include <cstdint>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main()
{
    fs::path file = fs::path(EXAMPLE_DIR) / "practice-4.csv";
    try
    {
        io::CSVReader<6,
                      io::trim_chars<' ', '\t'>,
                      io::double_quote_escape<';', '"'>,
                      io::throw_on_overflow,
                      io::single_and_empty_line_comment<'#'>>
                reader(file.string());

        reader.read_header(io::ignore_missing_column,
                           "producto",
                           "codigo",
                           "cantidad",
                           "precio",
                           "estado",
                           "categoria");

        if (!reader.has_column("producto"))
        {
            std::cerr << "Error: la columna 'producto' es obligatoria.\n";
            return 1;
        }

        if (!reader.has_column("codigo"))
        {
            std::cerr << "Error: la columna 'codigo' es obligatoria.\n";
            return 1;
        }

        if (!reader.has_column("cantidad"))
        {
            std::cerr << "Error: la columna 'cantidad' es obligatoria.\n";
            return 1;
        }

        if (!reader.has_column("precio"))
        {
            std::cerr << "Error: la columna 'precio' es obligatoria.\n";
            return 1;
        }

        std::string producto = "";
        int codigo = 0;
        std::uint64_t cantidad = 0;
        double precio = 0;
        char estado = 'A';
        std::string categoria = "SIN CATEGORIA";

        int total = 0;
        int accepted = 0;
        int unaccepted = 0;
        while (reader.read_row(
                producto, codigo, cantidad, precio, estado, categoria))
        {
            total++;
            if (precio <= 0)
            {
                std::cerr << "Columna 'precio' invalida en la fila: "
                          << reader.get_file_line() << "\n";
                unaccepted++;
                continue;
            }

            if (estado != 'A' && estado != 'D')
            {
                std::cerr << "Columna 'estado' invalida en la fila: "
                          << reader.get_file_line() << "\n";
                unaccepted++;
                continue;
            }

            if (estado != 'A')
            {
                unaccepted++;
                continue;
            }

            accepted++;

            std::string category = (categoria.empty()) ? "SIN CATEGORIA"
                                                       : categoria;

            std::cout << producto << "\t" << codigo << "\t" << cantidad << "\t"
                      << precio << "\t" << estado << "\t" << category << "\n";
        }

        std::cout << "\nTotal: " << total << "\n";
        std::cout << "Aceptados: " << accepted << "\n";
        std::cout << "Rechazados: " << unaccepted << "\n";
    }
    catch (const io::error::header_missing &e)
    {
        std::cerr << "ERROR: " << e.what() << "\n";
    }
    catch (const io::error::duplicated_column_in_header &e)
    {
        std::cerr << "ERROR: " << e.what() << "\n";
    }
    catch (const io::error::extra_column_in_header &e)
    {
        std::cerr << "ERROR: " << e.what() << "\n";
    }
    catch (const io::error::can_not_open_file &e)
    {
        std::cerr << "ERROR: " << e.what() << "\n";
    }
    catch (const io::error::integer_overflow &e)
    {
        std::cerr << "ERROR: " << e.what() << "\n";
    }
    catch (const io::error::no_digit &e)
    {
        std::cerr << "ERROR: " << e.what() << "\n";
    }
    catch (const io::error::invalid_single_character &e)
    {
        std::cerr << "ERROR:" << e.what() << "\n";
    }
    catch (const io::error::escaped_string_not_closed &e)
    {
        std::cerr << "ERROR: " << e.what() << "\n";
    }
    catch (const io::error::integer_must_be_positive &e)
    {
        std::cerr << "ERROR: " << e.what() << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "ERROR: " << e.what() << "\n";
    }

    return 0;
}
