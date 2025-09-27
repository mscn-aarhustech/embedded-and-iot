SELECT
  strftime('%Y-%m-%d %H:00', timestamp, 'unixepoch') AS hour,
  ROUND(AVG(pressure), 1) AS avg_pressure,
  ROUND(MIN(pressure), 1) AS min_pressure,
  ROUND(MAX(pressure), 1) AS max_pressure
FROM
  sensor_data
GROUP BY
  hour
ORDER BY
  hour DESC;