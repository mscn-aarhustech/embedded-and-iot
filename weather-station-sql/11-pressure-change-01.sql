
WITH DeltaPressure AS 
(
  SELECT
    strftime('%Y-%m-%d %H:%M:%S', timestamp, 'unixepoch') AS datetime,
    pressure,
    LAG(pressure, 1, pressure) OVER (ORDER BY timestamp) AS prev_pressure
  FROM
    sensor_data
)

select 
  *
FROM
  DeltaPressure
LIMIT 10;

-- SELECT
--   strftime('%Y-%m-%d %H:%M', timestamp, 'unixepoch') AS time,
--   prev_pressure as prev_prs,
--   pressure,
--   ROUND(pressure - prev_pressure, 2) AS pressure_change
-- FROM
--   DeltaPressure
-- ORDER BY
--   abs(pressure_change) DESC
-- LIMIT 20;