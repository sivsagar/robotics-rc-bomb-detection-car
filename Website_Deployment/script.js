let socket = new WebSocket("ws://ESP32_IP:81");

socket.onmessage = function (event) {
    if (event.data.startsWith("Sensor:")) {
        console.log("Sensor Data Stream : " + event.data);
    }
};

function sendCommand(command) {
    socket.send(command);
}