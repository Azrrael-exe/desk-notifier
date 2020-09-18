import re
import logging
from flask import Flask, request, jsonify
from serial import Serial

from settings import DEVICE_PORT
from services.desk_notifier import DeskNotifier, Notification

app = Flask(__name__)

logging.basicConfig(format='%(asctime)s:%(levelname)s:%(message)s', level=logging.INFO)


uart = Serial(port=DEVICE_PORT, baudrate=115200) if DEVICE_PORT else None
notifier = DeskNotifier(port=uart, header=0x7E)


@app.route('/', methods=['GET'])
def get():
    return jsonify([notification.to_dict() for notification in notifier.notifications])


@app.route('/add', methods=['POST'])
def add():
    req = request.get_json()
    notification = Notification(id=req.get('notification_id'), color=req.get('color', [0, 0, 0]))
    return jsonify(notifier.add_notification(notification=notification))


@app.route('/clear', methods=['POST'])
def clear():
    req = request.get_json()
    return jsonify(notifier.clear_notification(notification_id=req.get('notification_id')))


if __name__ == '__main__':
    logging.info('Server started.')
    logging.info(f'Device Running on port {DEVICE_PORT}')
    app.run(debug=False, host="0.0.0.0", port=8080)
