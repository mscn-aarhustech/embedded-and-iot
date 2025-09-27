
-- Hent de første 10 rækker med temperatur data
-- Sorter descending (størst til mindst)

SELECT
    strftime('%Y-%m-%d %H:%M:%S', timestamp, 'unixepoch') as datetime,
    temperature
FROM
    sensor_data
ORDER BY
    temperature DESC
LIMIT 10