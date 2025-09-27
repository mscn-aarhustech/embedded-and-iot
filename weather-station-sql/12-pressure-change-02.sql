
WITH PressureChanges AS 
(
  SELECT
    timestamp,
    pressure,
    LAG(pressure, 1, pressure) OVER (ORDER BY timestamp) AS prev_pressure
  FROM
    sensor_data
)

SELECT
  strftime('%Y-%m-%d %H:%M', timestamp, 'unixepoch') AS event_time,
  prev_pressure as prev_pressure,
  pressure as current_pressure,
  ROUND(pressure - prev_pressure, 2) AS pressure_change
FROM
  PressureChanges
WHERE
  pressure > 900 and 
  pressure < 1100 and 
  abs(pressure_change) > 1.0 and 
  abs(pressure_change) < 5.0
ORDER BY
  abs(pressure_change) DESC
LIMIT 20;