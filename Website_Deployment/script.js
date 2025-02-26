const speedSlider = document.querySelector("#speedSlider");
const metalDetectorSensorValue = document.querySelector("#metal-detector-sensor-value");
const metalDetectorAlertText = document.querySelector("#metal-detector-alert-text");
const metalDetectorDetectedText = document.querySelector("#metal-detector-detected-text");

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
video.src = `http://${prompt("Enter ESP32CAM Video Link :")}/1600x1200.mjpeg`;
// http://192.168.137.17/1600x1200.mjpeg (Example Link)

const esp32ip = prompt("Enter ESP32 RC Control IP:");
const websocketvalue = `ws://${esp32ip}:81`;
// ws://192.168.29.1:81 (Example websocketvalue)
let socket = new WebSocket(websocketvalue);

socket.onmessage = function (event) {
    if (event.data.startsWith("metal-detector-value:")) {
        let metalDetectorValue = Number.parseInt(event.data.substring(22));
        metalDetectorSensorValue.textContent = metalDetectorValue.toString();
        if (metalDetectorValue > 50) {
            metalDetectorAlertText.textContent = "Metal Detected!";
            metalDetectorAlertText.style.color = "#ff4c76";
            metalDetectorDetectedText.textContent = "Yes";
        } else {
            metalDetectorAlertText.textContent = "No Metal Detected!";
            metalDetectorAlertText.style.color = "#e3ad19";
            metalDetectorDetectedText.textContent = "No";
        }
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