const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>LED Control</title>
  <style>
    body { font-family: sans-serif; text-align: center; margin-top: 50px; }
    button { font-size: 1.5em; padding: 10px 30px; margin: 10px; cursor: pointer; }
    #state { font-size: 1.2em; margin-top: 20px; }
  </style>
</head>
<body>
  <h1>LED Control</h1>
  <button onclick="toggleLED()" id="toggleBtn">...</button>
  <p id="state">Checking status...</p>

  <script>
    function render(isOn) {
      document.getElementById('toggleBtn').textContent = isOn ? 'Turn Off' : 'Turn On';
      document.getElementById('state').textContent = 'LED is currently ' + (isOn ? 'ON' : 'OFF');
    }

    async function toggleLED() {
      const res = await fetch('/toggle');
      const data = await res.json();
      render(data.state === 1);
    }

    async function updateFromServer() {
      const res = await fetch('/status');
      const data = await res.json();
      render(data.state === 1);
    }

    updateFromServer();
  </script>
</body>
</html>
)rawliteral";