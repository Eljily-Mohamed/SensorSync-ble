#! /usr/bin/python3
#=======================================================================
# $ ./ble.py  02:80:e1:00:00:ab
#=======================================================================
from bluepy.btle import UUID, Peripheral, ADDR_TYPE_PUBLIC, DefaultDelegate
from tkinter import *
import argparse
import time
import struct
import binascii
#=======================================================================
def STM32_UUID(val):
    return UUID("0000%04X-0000-1000-8000-00805F9B34FB" % val)
 
ENVIRONMENT_SERVICE_UUID = 0x181A
E_TempColor_CHAR_UUID    = 0x2A63
E_TEMPERATURE_CHAR_UUID = 0x2A6E
#E_HUMIDITY_CHAR_UUID    = 0x2A6F
 
LED_SERVICE_UUID = 0xFF10
LEDSTATE_CHAR_UUID  = 0xFF11
LEDSWITCH_CHAR_UUID = 0xFF12
 
CCCD_UUID = 0x2902
 
e_temperature_handle = None
e_TempColor_handle = None
m_tap_handle = None
 
ledswitch_handle = None
ledstate_handle = None
 
ledstate = 0
data_temperature=0
data_state=0
data_TempColor=0
 
#=======================================================================
#                LED Service
#=======================================================================
class LedService():
    serviceUUID = STM32_UUID(LED_SERVICE_UUID )
    ledswitch_char_uuid = STM32_UUID(LEDSWITCH_CHAR_UUID)
    ledstate_char_uuid = STM32_UUID(LEDSTATE_CHAR_UUID)
     
    def __init__(self, periph):
        self.periph = periph
        self.led_service = None
        self.ledswitch_char = None
        self.ledswitch_cccd = None
        self.ledstate_char = None
        self.ledstate_cccd = None
     
    def enable(self):
        """ Enables the class by finding the service and its characteristics. """
        global ledswitch_handle
        global ledstate_handle
 
        if self.led_service is None:
            self.led_service = self.periph.getServiceByUUID(self.serviceUUID)
        if self.ledswitch_char is None:
            self.ledswitch_char = self.led_service.getCharacteristics(self.ledswitch_char_uuid)[0]
            ledswitch_handle = self.ledswitch_char.getHandle()     
        if self.ledstate_char is None:
            self.ledstate_char = self.led_service.getCharacteristics(self.ledstate_char_uuid)[0]
            ledstate_handle = self.ledstate_char.getHandle()
            self.ledstate_cccd = self.ledstate_char.getDescriptors(forUUID=CCCD_UUID)[0]
 
    def set_ledswitch_notification(self, state):
        if self.ledswitch_cccd is not None:
            if state == True:
                self.ledswitch_cccd.write(b"\x01\x00", True)
            else:
                self.ledswitch_cccd.write(b"\x00\x00", True)
 
    def set_ledstate_notification(self, state):
        if self.ledstate_cccd is not None:
            if state == True:
                self.ledstate_cccd.write(b"\x01\x00", True)
            else:
                self.ledstate_cccd.write(b"\x00\x00", True)
                 
    def set_switch_led_on(self):
           self.ledswitch_char.write(b"\x01", True)             
 
    def set_switch_led_off(self):
           self.ledswitch_char.write(b"\x00", True)  
 
    def disable(self):
        set_ledswitch_notification(False)
        set_ledstate_notification(False)
 
#=======================================================================
#            Environment Service Class
#=======================================================================
class EnvironmentService():
    serviceUUID =           STM32_UUID(ENVIRONMENT_SERVICE_UUID)
    temperature_char_uuid = STM32_UUID(E_TEMPERATURE_CHAR_UUID)
    TempColor_char_uuid =    STM32_UUID(E_TempColor_CHAR_UUID)
 
    def __init__(self, periph):
        self.periph = periph
        self.environment_service = None
        self.temperature_char = None
        self.temperature_cccd = None
        self.TempColor_char = None
        self.TempColor_cccd = None
 
    def enable(self):
        """ Enables the class by finding the service and its characteristics. """
        global e_temperature_handle
        global e_TempColor_handle
 
        if self.environment_service is None:
            self.environment_service = self.periph.getServiceByUUID(self.serviceUUID)
        if self.temperature_char is None:
            self.temperature_char = self.environment_service.getCharacteristics(self.temperature_char_uuid)[0]
            e_temperature_handle = self.temperature_char.getHandle()
            self.temperature_cccd = self.temperature_char.getDescriptors(forUUID=CCCD_UUID)[0]
        if self.TempColor_char is None:
            self.TempColor_char = self.environment_service.getCharacteristics(self.TempColor_char_uuid)[0]
            e_TempColor_handle = self.TempColor_char.getHandle()
            self.TempColor_cccd = self.TempColor_char.getDescriptors(forUUID=CCCD_UUID)[0]
 
    def set_temperature_notification(self, state):
        if self.temperature_cccd is not None:
            if state == True:
                print("temperature write")              
                self.temperature_cccd.write(b"\x01\x00", True)
            else:
                self.temperature_cccd.write(b"\x00\x00", True)
 
    def set_TempColor_notification(self, state):
        if self.TempColor_cccd is not None:
            if state == True:
                print("TempColor write")
                self.TempColor_cccd.write(b"\x01\x00", True)
            else:
                self.TempColor_cccd.write(b"\x00\x00", True)
 
    def disable(self):
        set_temperature_notification(False)
        set_TempColor_notification(False)
 
#=======================================================================
#                MyDelegate Class
#=======================================================================
class MyDelegate(DefaultDelegate):
     
    def handleNotification(self, hnd, data):
        global data_TempColor,data_temperature, data_state
        if (hnd == e_temperature_handle): 
            concat_dat = binascii.b2a_hex(data[::-1])   # [::-1] reverse the string
            temp_f = float(int(concat_dat,16))/10                      
            print("Temp received:" + str(temp_f))
            data_temperature = temp_f              
             
        elif (hnd == e_TempColor_handle):        
            concat_dat = binascii.b2a_hex(data[::-1])
            TempColor_f = float(int(concat_dat,16))
            print("TempColor received:" + str(TempColor_f))
            data_TempColor = TempColor_f
 
        elif (hnd == ledstate_handle):   
            data_state = data
 
#=======================================================================
#                Bleiot Class
#=======================================================================
class Bleiot(Peripheral):
    """
    Bleiot module. Instance the class and enable to get access to the Bleiot Sensors.
    The addr of your device has to be know, or can be found by using the hcitool command line 
    tool, for example. Call "> sudo hcitool lescan" and your bleiot's address should show up.
    """
    def __init__(self, addr):
        Peripheral.__init__(self, addr, addrType=ADDR_TYPE_PUBLIC)
        self.environment = EnvironmentService(self)
        self.led = LedService(self)
 
#=======================================================================
#                Functions
#=======================================================================
def askFordatas():
    bleiot.waitForNotifications(args.t)
    strTemperature.set(str(data_temperature) + ' °C')
    strTempColor.set(str(data_TempColor) + ' Kelvin ')   
    strLedState.set(str(data_state) + ' --- ' + time.ctime())  
    ui.after(1,askFordatas)
     
def onPushSwitch():
    global ledstate
    if ledstate == 0:
        print("switch on")
        bleiot.led.set_switch_led_on()
        ledstate = 1
    else:
        print("switch off")
        bleiot.led.set_switch_led_off()
        ledstate = 0
         
#=======================================================================
#                Main Function
#=======================================================================
if  __name__ == "__main__" :
    parser = argparse.ArgumentParser()
    parser.add_argument('mac_address', action='store', help='MAC address of BLE peripheral')
    parser.add_argument('-n', action='store', dest='count', default=0, type=int, help="Number of times to loop data")
    parser.add_argument('-t',action='store',type=float, default=0.1, help='time between polling')
     
    args = parser.parse_args()
 
    print('Connecting to ' + args.mac_address)
    bleiot = Bleiot(args.mac_address)
    print(bleiot)
    print('Connected...')
    bleiot.setDelegate(MyDelegate())
     
    print('Enabling selected sensors...')   
    bleiot.environment.enable()
    bleiot.environment.set_temperature_notification(True)
    bleiot.environment.enable()
    bleiot.environment.set_TempColor_notification(True)       
    bleiot.led.enable()
    bleiot.led.set_ledstate_notification(True)    
     
    print('All requested sensors and notifications are enabled...')
    time.sleep(1.0)    
    #-------------------------------------------------------------------
    ui=Tk()
    ui.title("BLEIOT")
    ui.geometry("200x200")
 
    labelTemperature=Label(ui, text="Temperature", font=("Arial", 10), fg="black")
    labelTemperature.pack()
  
    strTemperature = StringVar()
    TemperatureEntry=Entry(ui, textvariable=strTemperature)
    TemperatureEntry.pack()
     
    labelTempColor=Label(ui, text="TempColor", font=("Arial", 10), fg="black")
    labelTempColor.pack()
  
    strTempColor=StringVar()
    TempColorEntry=Entry(ui, textvariable=strTempColor)
    TempColorEntry.pack()
     
    switchButton=Button(ui, text="SWITCH LED", font=("Arial",10, "bold"), bg="seagreen3", fg="black", bd=3, relief=RAISED, command=onPushSwitch)
    switchButton.pack()
     
    strLedState=StringVar()
    strLedEntry=Entry(ui, textvariable=strLedState)
    strLedEntry.pack() 
     
    ui.after(1,askFordatas)
     
    ui.mainloop()  
     
