-- Weather data grouped by month

SELECT
  strftime('%Y-%m', timestamp, 'unixepoch') AS month,
  ROUND(AVG(temperature), 1) AS avg_temp,
  ROUND(AVG(humidity), 1) AS avg_humidity,
  ROUND(AVG(pressure), 1) AS avg_pressure,
  ROUND(AVG(co2), 1) AS avg_co2,
  ROUND(AVG(tvoc), 1) AS avg_tvoc
FROM
  sensor_data
GROUP BY
  month
ORDER BY
  month DESC;