const speedSlider = document.querySelector("#speedSlider");
const metalDetectorSensorValue = document.querySelector("#metal-detector-sensor-value")

speedSlider.addEventListener("input", function () {
    const sliderValue = speedSlider.value;
    console.log("Speed Slider Value: " + sliderValue);
    const sendSpeed = `${sliderValue}`;
    sendCommand(sendSpeed);
});

speedSlider.addEventListener("mouseout", () => {
    speedSlider.blur();
});


const video = document.querySelector("#espCamStream");
video.src = "http://192.168.137.20/1600x1200.mjpeg";
let socket = new WebSocket("ws://192.168.137.78:81");

socket.onmessage = function (event) {
    if (event.data.startsWith("metal-detector-value:")) {
        metalDetectorSensorValue.textContent = event.data.substring(22);
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
        case ' ':
            sendCommand('stop');
            break;
    }
});