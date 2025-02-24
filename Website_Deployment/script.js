let socket = new WebSocket("ws://ESP32_IP:81");

socket.onmessage = function (event) {
    if (event.data.startsWith("Sensor:")) {
        console.log("Sensor Data Stream : " + event.data);
    }
};

function sendCommand(command) {
    socket.send(command);
}

document.addEventListener('keydown', function (event) {
    switch (event.key) {
        case 'ArrowUp':
            sendCommand('forward');
            break;
        case 'ArrowLeft':
            sendCommand('left');
            break;
        case 'ArrowRight':
            sendCommand('right');
            break;
        case 'ArrowDown':
            sendCommand('backward');
            break;
    }
});