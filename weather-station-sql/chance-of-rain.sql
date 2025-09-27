-- Chance of rain?

-- It rains when:
-- Pressure drops
-- Pressure is low
-- Humidity rises
-- Temperature drops

WITH HourlyData AS 
(
    SELECT
        strftime('%Y-%m-%d %H:00', timestamp, 'unixepoch') AS hour,
        ROUND(AVG(pressure), 1) AS avg_prs,
        ROUND(AVG(humidity), 1) AS avg_hum,
        ROUND(AVG(temperature), 1) AS avg_tmp
    FROM
        sensor_data
    WHERE
        pressure > 950 AND pressure < 1050 AND
        humidity > 0 AND humidity < 100 AND
        temperature > -50 AND temperature < 100
    GROUP BY
        hour
    ORDER BY
        hour DESC
),

HourlyDataPrev AS
(
    SELECT
        hour,
        avg_prs,
        LAG(avg_prs, 1) OVER (order by hour) AS prev_prs,
        avg_hum,
        LAG(avg_hum, 1) OVER (order by hour) AS prev_hum,
        avg_tmp,
        LAG(avg_tmp, 1) OVER (order by hour) AS prev_tmp
    FROM
      HourlyData  
),

HourlyDataDiff AS
(
    SELECT
        hour,
        avg_prs,
        avg_hum,
        avg_tmp,
        ROUND(avg_prs - prev_prs, 1) as prs_diff,
        ROUND(avg_hum - prev_hum, 1) as hum_diff,
        ROUND(avg_tmp - prev_tmp, 1) as tmp_diff
    FROM
        HourlyDataPrev
)

select
    *
FROM
    HourlyDataDiff
WHERE
    
