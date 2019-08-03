from flask import Flask
from flask_socketio import SocketIO
import SousVide

app = Flask(__name__)
socketio = SocketIO(app)

py = SousVide.Py
data = SousVide.Data

from app import routes, models
