async function toggleLed() {
  const res = await fetch('/toggle');
  const on = await res.text();
  document.getElementById('state').textContent = on === "1" ? "ON" : "OFF";
}

window.onload = toggleLed;
