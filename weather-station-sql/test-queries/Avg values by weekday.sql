SELECT
  CASE strftime('%w', timestamp, 'unixepoch')
    WHEN '0' THEN 'Sunday'
    WHEN '1' THEN 'Monday'
    WHEN '2' THEN 'Tuesday'
    WHEN '3' THEN 'Wednesday'
    WHEN '4' THEN 'Thursday'
    WHEN '5' THEN 'Friday'
    ELSE 'Saturday'
  END AS day_of_week,
  ROUND(AVG(temperature), 1) AS avg_temp,
  ROUND(AVG(humidity), 1) AS avg_humidity,
  ROUND(AVG(pressure), 1) AS avg_pressure,
  ROUND(AVG(co2), 1) AS avg_co2,
  ROUND(AVG(tvoc), 1) AS avg_tvoc
FROM
  sensor_data
GROUP BY
  day_of_week
ORDER BY
  -- ROUND(AVG(temperature), 1);
  -- ROUND(AVG(humidity), 1),
  -- ROUND(AVG(pressure), 1);
  ROUND(AVG(co2), 1);
  -- ROUND(AVG(tvoc), 1);
  --strftime('%w', timestamp, 'unixepoch');