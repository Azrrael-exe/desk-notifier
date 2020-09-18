import re
import os
from serial.tools import list_ports

RUNNING_OS = os.getenv('OS', 'MACOS')
DEVICE_PORT = os.getenv('DEVICE_PORT', None)

if not DEVICE_PORT:
    ports = list_ports.comports()
    if ports:
        ports_mask = {
            'WINDOWS': re.compile(r"COM\w+"),
            'LINUX': re.compile(r"/dev/tty\w+"),
            'MACOS': re.compile(r"/dev/cu.usbmodem\w+"),
        }
        try:
            DEVICE_PORT = [port.device for port in ports if ports_mask[RUNNING_OS].match(port.device)][0]
        except Exception as e:
            pass
