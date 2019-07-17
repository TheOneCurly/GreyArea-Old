#include "ds18b20.h"
#define debug std::cout << "DS18B20: "

const std::string DS18B20::DevicesPath = "/sys/bus/w1/devices";
const std::string DS18B20::SensorPartialPath = "28-";
const std::string DS18B20::ReadPath = "w1_slave";

std::string DS18B20::discover(){
    std::string sensorPath = "";

    DIR* devicesDir = opendir(DevicesPath.c_str());
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
        debug << "error opening sensor directory " << errsv;
    }

    return sensorPath;
}

float DS18B20::read(std::string sensor){
    float temp = 0;

    std::ifstream tempStream;
    tempStream.open((DevicesPath + "/" + sensor + "/" + ReadPath).c_str());

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
