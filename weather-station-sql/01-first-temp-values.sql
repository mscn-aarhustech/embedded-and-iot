
-- Hent de første 10 rækker med temperatur data

SELECT
    strftime('%Y-%m-%d %H:%M:%S', timestamp, 'unixepoch') as datetime,
    temperature
FROM
    sensor_data
ORDER BY
    datetime
LIMIT 10