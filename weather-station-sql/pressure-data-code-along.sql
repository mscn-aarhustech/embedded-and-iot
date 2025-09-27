
-- Common Table Expression CTE

WITH HourlyPressure AS 
(
    SELECT
        strftime('%Y-%m-%d %H:00', timestamp, 'unixepoch') AS hour,
        ROUND(AVG(pressure), 1) AS avg_pressure
    FROM
        sensor_data
    WHERE
        pressure > 950 AND
        pressure < 1050
    GROUP BY
        hour
    ORDER BY
        hour DESC
),

HourlyPressureDiff AS
(
    SELECT
        hour,
        avg_pressure,
        LAG(avg_pressure, 1) OVER (order by hour) AS prev_pressure
    FROM
        HourlyPressure
)

SELECT 
    hour,
    ROUND(ABS(avg_pressure - prev_pressure), 1) as delta_pressure
FROM
    HourlyPressureDiff
WHERE
  delta_pressure > 1.0 and 
  delta_pressure < 5.0
ORDER BY
    delta_pressure DESC
LIMIT
    10