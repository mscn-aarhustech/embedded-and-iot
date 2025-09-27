
-- CTE's
WITH HourlyPressureAverage AS (
  SELECT
    strftime('%Y-%m-%d %H:00', timestamp, 'unixepoch') AS hour,
    MIN(timestamp) AS hour_timestamp,
    AVG(pressure) AS avg_pressure
  FROM
    sensor_data
  WHERE
    pressure > 900 AND pressure < 1100
  GROUP BY
    hour
),

HourlyPressureChange AS (
  SELECT
    hour,
    avg_pressure,
    LAG(avg_pressure, 1, avg_pressure) OVER (ORDER BY hour_timestamp) AS prev_avg_pressure
  FROM
    HourlyPressureAverage
)

-- Query
SELECT
  hour AS event_time,
  ROUND(prev_avg_pressure, 2) AS prev_avg_pressure,
  ROUND(avg_pressure, 2) AS current_avg_pressure,
  ROUND(avg_pressure - prev_avg_pressure, 2) AS pressure_change_hpa
FROM
  HourlyPressureChange
WHERE
  -- Apply your filter for the magnitude of the change
  abs(pressure_change_hpa) > 1.0 AND abs(pressure_change_hpa) < 5.0
ORDER BY
    --hour
  abs(pressure_change_hpa) DESC
LIMIT 20;