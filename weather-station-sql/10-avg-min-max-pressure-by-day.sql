SELECT
  strftime('%Y-%m-%d', timestamp, 'unixepoch') AS day,
  ROUND(AVG(pressure), 1) AS avg_pressure,
  ROUND(MIN(pressure), 1) AS min_pressure,
  ROUND(MAX(pressure), 1) AS max_pressure
FROM
  sensor_data
GROUP BY
  day
ORDER BY
  day DESC;