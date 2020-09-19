from unittest import TestCase
from unittest.mock import Mock
from services.desk_notifier import Notification, DeskNotifier


class TestNotification(TestCase):
    def test_properties(self):
        notification = Notification(id=0x0A, color=[0xF1, 0xF2, 0xF3])

        self.assertEqual(notification.id, 0x0A)
        self.assertEqual(notification.red, 0xF1)
        self.assertEqual(notification.green, 0xF2)
        self.assertEqual(notification.blue, 0xF3)


class TestDeskNotifier(TestCase):
    def test_desk_notifier(self):

        port = Mock()
        port.write._return_value = None

        desk_notifier = DeskNotifier(port=port, header=0x7E)

        notification = Notification(id=0x0A, color=[0x00, 0x00, 0x64])

        payload = desk_notifier._build_payload(
            header=0x7E, command=DeskNotifier.CREATE, notification=notification
        )

        self.assertEqual(
            payload, bytearray([0x7E, 0x05, 0x1C, 0x0A, 0x00, 0x00, 0x64, 0x75])
        )

        del notification

        notifications_ids = [0x0A, 0x1A, 0x2A]
        notifications = [
            Notification(id=id, color=[0, 0, 0]) for id in notifications_ids
        ]

        for notification in notifications:
            desk_notifier.add_notification(notification=notification)

        self.assertEqual(len(desk_notifier.notifications), 3)
        
        desk_notifier.clear_notification(notification_id=notifications[0].id)
        
        self.assertEqual(len(desk_notifier.notifications), 2)
        self.assertFalse((notifications[0] in desk_notifier.notifications))
        self.assertTrue((notifications[1] in desk_notifier.notifications))
