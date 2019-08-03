from flask import render_template, request
from flask_socketio import emit
from app import app, py, data

with app.test_request_context():
    py.Init()

@app.route('/')
def index():
    return render_template('index.html')

@app.errorhandler(404)
def page_not_found():
    return render_template('404.html', page=request.path), 404

@socketio.on('connect')
def on_connect():
    print("Connnected")

    # Set initial values
    getValues()

@socketio.on('update_setpoint')
def on_setpoint(msg):
    data.SetCurrentSetpoint(FtoC(float(msg['temp'])))
    getValues()

@socketio.on("new_state")
def on_state(msg):
    data.SetEnabled(bool(msg["state"]))
    getValues()

@socketio.on("request_update")
def on_request_update():
    getValues()

def getValues():
    emit('new_setpoint', {'temp': CtoF(data.GetCurrentSetpoint())})
    emit('new_state', {'state': data.GetEnabled()})
    emit('new_temp', {'temp': CtoF(data.GetCurrentTemperature())})
    emit('new_relay_state', {'relay': data.GetRelayState()})

def FtoC(tempF):
    tempC = (tempF - 32) * (5/9)
    return tempC

def CtoF(tempC):
    tempF = (tempC * (9/5)) + 32
    return tempF

