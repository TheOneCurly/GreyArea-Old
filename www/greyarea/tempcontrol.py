import RPi.GPIO as GPIO
import configparser
import glob
from threading import Thread, Event
from time import sleep

# Global status variables
running = False
setpoint = 0
current_temp = 0
relay_state = False

def F_to_C(tempF):
    return (tempF - 32) / 1.8
    
def C_to_F(tempC):
    return (tempC * 1.8) + 32

class ControlThread(Thread):
    def __init__(self):
        # Load Settings
        config = configparser.ConfigParser()
        config.read('config.ini')

        # Pinout
        self.relay_pin = int(config['Pinout']['RelayPin'])
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.relay_pin, GPIO.OUT)
        
        #https://learn.adafruit.com/adafruits-raspberry-pi-lesson-11-ds18b20-temperature-sensing/ds18b20
        self.base_dir = '/sys/bus/w1/devices/'
        self.device_file = ""
    
        # Tuning
        self.P = int(config['Tuning']['P'])
        self.I = int(config['Tuning']['I'])
        self.D = int(config['Tuning']['D'])
        
        self.setpoint = int(config['Settings']['Setpoint'])
        
        super(ControlThread, self).__init__()

    def __set_relay(self, closed):
        if(closed):
            GPIO.output(self.relay_pin, GPIO.LOW)
        else:
            GPIO.output(self.relay_pin, GPIO.HIGH)

    def __detect_temp_sensor(self):
        device_folders = glob.glob(self.base_dir + '28*')
        if(len(device_folders) > 0):
            self.device_file = device_folder[0] + '/w1_slave'

    def __read_temp_raw(self):
        f = open(self.device_file, 'r')
        lines = f.readlines()
        f.close()
        return lines
 
    def __read_temp(self):
        if self.device_file != "":
            lines = self.__read_temp_raw()
            while lines[0].strip()[-3:] != 'YES':
                sleep(0.2)
                lines = self.__read_temp_raw()
            equals_pos = lines[1].find('t=')

            if equals_pos != -1:
                temp_string = lines[1][equals_pos+2:]
                temp_c = float(temp_string) / 1000.0
                return temp_c
        else:
            self.__detect_temp_sensor()

        return 0

    def control_routine(self):
        # Close relay
        self.__set_relay(False)

        currentError = 0
        
        lastError = 0
        errorIntegral = 0
        errorDerivative = 0

        PIDResult = 0
        
        while True:
            currentTemperature = self.__read_temp()
            print("Current Temperature: " + str(currentTemperature))
            print("Current Control Setpoint: " + str(F_to_C(self.setpoint)))

            currentError = F_to_C(self.setpoint) - currentTemperature
        
            errorIntegral += currentError
            if errorIntegral > 50:
                errorIntegral = 51
            elif errorIntegral < -50:
                errorIntegral = -50

            errorDerivative = currentError - lastError
            
            PIDResult = (self.P*currentError) + (self.I*errorIntegral) + (self.D*errorDerivative)

            if PIDResult > 500:
                PIDResult = 500
            elif PIDResult < -500:
                PIDResult = -500
            
            print("Calculated PID: " + str(PIDResult))

            # Set relay
            if PIDResult > 0:
                self.__set_relay(True);
            else:
                self.__set_relay(False);

            sleep(1)
            
    def run(self):
        self.control_routine()
