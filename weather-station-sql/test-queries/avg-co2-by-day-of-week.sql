SELECT
    -- Use a CASE statement to get the day name from the day number
    CASE strftime('%w', timestamp, 'unixepoch')
        WHEN '0' THEN 'Sunday'
        WHEN '1' THEN 'Monday'
        WHEN '2' THEN 'Tuesday'
        WHEN '3' THEN 'Wednesday'
        WHEN '4' THEN 'Thursday'
        WHEN '5' THEN 'Friday'
        ELSE 'Saturday'
    END AS day_of_week,
    ROUND(AVG(co2), 0) AS avg_co2,
    ROUND(AVG(tvoc), 0) AS avg_tvoc
FROM
    sensor_data
GROUP BY
    day_of_week
ORDER BY
    avg_co2;
    --strftime('%w', timestamp, 'unixepoch'); -- Order by weekday number