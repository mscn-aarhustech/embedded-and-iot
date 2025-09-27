SELECT
    -- Find the first and last timestamps in a human-readable format
    strftime('%Y-%m-%d %H:%M', MIN(timestamp), 'unixepoch') AS first_reading,
    strftime('%Y-%m-%d %H:%M', MAX(timestamp), 'unixepoch') AS last_reading,
    -- Count the total number of data points
    COUNT(*) AS total_readings,
    -- Calculate key stats for temperature
    ROUND(AVG(temperature), 1) AS avg_temp,
    ROUND(MIN(temperature), 1) AS min_temp,
    ROUND(MAX(temperature), 1) AS max_temp,
    -- Calculate key stats for CO2
    ROUND(AVG(co2), 0) AS avg_co2,
    ROUND(MIN(co2), 0) AS min_co2,
    ROUND(MAX(co2), 0) AS max_co2
FROM
    sensor_data;