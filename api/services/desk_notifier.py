from typing import List, Union
from serial import Serial


class Notification:
    def __init__(self, id: int, color: List[int]):
        self.__id = id
        self.__color = color

    @property
    def id(self):
        return self.__id

    @property
    def red(self):
        return self.__color[0]

    @property
    def green(self):
        return self.__color[1]

    @property
    def blue(self):
        return self.__color[2]
    
    def to_dict(self):
        return {
            'notification_id': self.id,
            'color': {
                'red': self.red,
                'green': self.green,
                'blue:': self.blue,
            }
        }
    
    def __hash__(self):
        return self.id.__hash__()

    def __eq__(self, other):
        if isinstance(other, Notification):
            return self.__hash__() == other.__hash__()

        return False

class DeskNotifier:

    CREATE = "create"
    CLEAR = "clear"

    def __init__(self, header: int, port: Union[Serial, None] = None):
        self.__port = port
        self.__header = header
        self.__notifications = []

    def add_notification(self, notification: Notification):
        if notification not in self.__notifications:
            if self.__port:
                self.__port.write(
                    self._build_payload(
                        header=self.__header,
                        command=DeskNotifier.CREATE,
                        notification=notification,
                    )
                )
            self.__notifications.append(notification)
            return True
        return False

    def clear_notification(self, notification_id: int):

        notification = [
            notification
            for notification in self.__notifications
            if notification.id == notification_id
        ]
        
        print(notification)
        
        if notification:
            if self.__port:
                self.__port.write(
                    self._build_payload(
                    header=self.__header,
                    command=DeskNotifier.CLEAR,
                    notification=notification[0],
                    )
                )
            self.__notifications.pop(self.__notifications.index(notification[0]))
            return True
        return False

    @property
    def notifications(self):
        return self.__notifications
    
    @staticmethod
    def _build_payload(header: int, command: str, notification: Notification):
        valid_comands = [DeskNotifier.CREATE, DeskNotifier.CLEAR]
        if command in valid_comands:
            message = [header]
            payload = []
            if command.lower() == DeskNotifier.CREATE:
                cmd = 0x1C
                payload = [
                    cmd,
                    notification.id,
                    notification.red,
                    notification.green,
                    notification.blue,
                ]

            elif command.lower() == DeskNotifier.CLEAR:
                cmd = 0x2C
                payload = [cmd, notification.id]

            message.append(len(payload))
            message += payload
            message += [(0xFF - sum(payload)) & 0xFF]
            print(message)
            return bytearray(message)
        else:
            raise ValueError(f"{command} is not a valid Command")
