#include "ds18b20.h"
#define debug std::cout << "DS18B20: "

std::string DS18B20::discover(){
    std::string sensorPath = "";
    DIR* devicesDir = opendir(DevicesPath);
    if(devicesDir != NULL){
        dirent* sensorDir = readdir(devicesDir);
        std::string item;

        while(sensorDir != NULL){
            item = sensorDir->d_name;
            size_t found = item.find(SensorPartialPath);

            if(found != std::string::npos){
                sensorPath = item;
                break;
            }
            sensorDir = readdir(devicesDir);
        }

        closedir(devicesDir);
    }else{
        int errsv = errno;
        debug << "error opening sensor directory " << errsv << std::endl;
    }

    return sensorPath;
}

float DS18B20::read(std::string sensor){
    float temp = 0;

    std::string path(DevicesPath);
    path.append("/");
    path.append(sensor);
    path.append("/");
    path.append(ReadPath);

    std::ifstream tempStream;
    tempStream.open(path);

    std::string statusLine;
    std::getline(tempStream, statusLine);

    std::vector<std::string> statusList;
    split(statusList, statusLine, ' ');
    if((statusList[statusList.size() - 1]).compare("YES") == 0){
        std::string dataLine;
        std::getline(tempStream, dataLine);

        std::vector<std::string> dataList;
        split(dataList, dataLine, '=');
        if(dataList.size() == 2){
            std::istringstream iss(dataList[1]);
            int temp1000 = 0;
            iss >> temp1000;
            temp = temp1000 / 1000.f;
        }
    }

    tempStream.close();

    return temp;
}
