#ifndef DS18B20_H
#define DS18B20_H

#include <iostream>
#include <dirent.h>
#include <string>
#include <sys/types.h>
#include <errno.h>
#include <fstream>
#include <vector>
#include <sstream>

///
/// \brief The DS18B20 class provides an interface for the DS18B20 temperature sensor
///
class DS18B20{
public:
    ///
    /// \brief discover - Find the ID assigned to the connected sensor
    /// \return Sensor ID
    ///
    std::string discover();

    ///
    /// \brief read - Take a reading
    /// \param sensor - Sensor ID
    /// \return Temperature in C
    ///
    float read(std::string sensor);

private:
    static const std::string DevicesPath;
    static const std::string SensorPartialPath;
    static const std::string ReadPath;

    struct split{
      enum empties_t { empties_ok, no_empties };
    };

    template <typename Container>
    Container& split(Container& result, const std::string& s, const char& delimiter, split::empties_t empties = split::empties_ok ){
        result.clear();
        std::istringstream ss(s);
        while (!ss.eof()){
          typename Container::value_type field;
          std::getline(ss, field, delimiter);
          if ((empties == split::no_empties) && field.empty()) continue;
          result.push_back( field );
        }
        return result;
    }
};

#endif // DS18B20_H
