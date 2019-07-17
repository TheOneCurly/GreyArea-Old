from flask import Flask, render_template, request
from flask_socketio import SocketIO, emit
from threading import Thread, Event
import tempcontrol

app = Flask(__name__)
socketio = SocketIO(app)

@app.route('/')
def index():
    return render_template('index.html')

#@app.errorhandler(404)
#def page_not_found():
#    return render_template('404.html', page=request.path), 404

@socketio.on('connect')
def on_connect():
    print("Connnected")

    # Set initial values
    emit('new_setpoint', {'temp': 115})
    emit('new_state', {'state': "Off"})
    emit('new_temp', {'temp': 110})
    emit('new_relay_state', {'relay': "Closed (Energized)"})
        
@socketio.on('update_setpoint')
def on_setpoint(msg):
    

#thread = tempcontrol.ControlThread()
#thread.start()

if __name__ == '__main__':
    socketio.run(app, debug=True, host='0.0.0.0')
