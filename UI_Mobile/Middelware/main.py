from bluepy.btle import UUID, Peripheral, ADDR_TYPE_PUBLIC, DefaultDelegate
import argparse
import time
import binascii
from pymongo import MongoClient
import sys

# MongoDB setup
mongo_client = MongoClient("mongodb+srv://mohamedeljily2005:sdjk3q2C0Wmai7YL@emb-ble.xawcghv.mongodb.net/?retryWrites=true&w=majority&appName=emb-ble")
db = mongo_client.get_database('temp')
collection = db['temperaturedatas']

def STM32_UUID(val):
    return UUID("0000%04X-0000-1000-8000-00805F9B34FB" % val)
 
ENVIRONMENT_SERVICE_UUID = 0x181A
E_TempColor_CHAR_UUID    = 0x2A63
E_TEMPERATURE_CHAR_UUID = 0x2A6E
CCCD_UUID = 0x2902

e_temperature_handle = None
e_TempColor_handle = None
 
data_temperature = 0
data_TempColor = 0
 
class EnvironmentService():
    def __init__(self, periph):
        self.periph = periph
        self.environment_service = None
        self.temperature_char = None
        self.temperature_cccd = None
        self.TempColor_char = None
        self.TempColor_cccd = None
 
    def enable(self):
        """ Enables the class by finding the service and its characteristics. """
        global e_temperature_handle, e_TempColor_handle
 
        if self.environment_service is None:
            self.environment_service = self.periph.getServiceByUUID(STM32_UUID(ENVIRONMENT_SERVICE_UUID))
        if self.temperature_char is None:
            self.temperature_char = self.environment_service.getCharacteristics(STM32_UUID(E_TEMPERATURE_CHAR_UUID))[0]
            e_temperature_handle = self.temperature_char.getHandle()
            self.temperature_cccd = self.temperature_char.getDescriptors(forUUID=CCCD_UUID)[0]
        if self.TempColor_char is None:
            self.TempColor_char = self.environment_service.getCharacteristics(STM32_UUID(E_TempColor_CHAR_UUID))[0]
            e_TempColor_handle = self.TempColor_char.getHandle()
            self.TempColor_cccd = self.TempColor_char.getDescriptors(forUUID=CCCD_UUID)[0]
 
    def set_temperature_notification(self, state):
        if self.temperature_cccd is not None:
            if state:
                print("Temperature notifications enabled")
                self.temperature_cccd.write(b"\x01\x00", True)
            else:
                print("Temperature notifications disabled")
                self.temperature_cccd.write(b"\x00\x00", True)
 
    def set_TempColor_notification(self, state):
        if self.TempColor_cccd is not None:
            if state:
                print("TempColor notifications enabled")
                self.TempColor_cccd.write(b"\x01\x00", True)
            else:
                print("TempColor notifications disabled")
                self.TempColor_cccd.write(b"\x00\x00", True)
 
    def disable(self):
        self.set_temperature_notification(False)
        self.set_TempColor_notification(False)
 
 
class MyDelegate(DefaultDelegate):
    def handleNotification(self, hnd, data):
        global e_temperature_handle, e_TempColor_handle

        if hnd == e_temperature_handle:
            concat_dat = binascii.b2a_hex(data[::-1])
            temp_f = float(int(concat_dat, 16)) / 10
            print("Temperature received:", temp_f)

            # Save temperature data to MongoDB
            try:
                temperature_entry = {
                    "type": "temperature",
                    "value": temp_f,
                    "timestamp": time.time()
                }
                collection.insert_one(temperature_entry)
                

            except Exception as e:
                print("Error inserting temperature into MongoDB:", e)

        elif hnd == e_TempColor_handle:
            concat_dat = binascii.b2a_hex(data[::-1])
            TempColor_f = float(int(concat_dat, 16))
            print("TempColor received:", TempColor_f)

            # Save temperature color data to MongoDB
            try:
                TempColor_entry = {
                    "type": "temperature_color",
                    "value": TempColor_f,
                    "timestamp": time.time()
                }
                collection.insert_one(TempColor_entry)


            except Exception as e:
                print("Error inserting temperature color into MongoDB:", e)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('mac_address', action='store', help='MAC address of BLE peripheral')
    parser.add_argument('-t', action='store', type=float, default=0.1, help='Time between polling')

    args = parser.parse_args()

    print('Connecting to', args.mac_address)
    peripheral = None
    try:
        peripheral = Peripheral(args.mac_address, ADDR_TYPE_PUBLIC)

        # Discover services and characteristics
        environment_service = EnvironmentService(peripheral)
        environment_service.enable()

        # Enable notifications
        environment_service.set_temperature_notification(True)
        environment_service.set_TempColor_notification(True)

        # Set delegate and wait for notifications
        peripheral.setDelegate(MyDelegate())
        print('Notifications enabled. Waiting for data...')

        while True:
            peripheral.waitForNotifications(args.t)

    except KeyboardInterrupt:
        print("Keyboard interrupt detected. Exiting...")

    finally:
        if peripheral:
            peripheral.disconnect()
        sys.exit(0)
