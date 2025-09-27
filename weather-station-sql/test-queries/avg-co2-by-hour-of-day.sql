SELECT
    -- Extract just the hour from the timestamp
    strftime('%H:00', timestamp, 'unixepoch') AS hour_of_day,
    ROUND(AVG(temperature), 1) AS avg_temp,
    ROUND(AVG(co2), 0) AS avg_co2,
    ROUND(AVG(tvoc), 0) AS avg_tvoc
FROM
    sensor_data
WHERE
    co2 IS NOT NULL -- Exclude any null values
GROUP BY
    hour_of_day
ORDER BY
    avg_co2;
    --hour_of_day;