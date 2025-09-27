
-- Hent de første 10 rækker med temperatur data
-- Sorter descending (størst til mindst)
-- Begræns temperatur værdier 

SELECT
    strftime('%Y-%m-%d %H:%M:%S', timestamp, 'unixepoch') as datetime,
    temperature
FROM
    sensor_data
WHERE
    temperature < 100
ORDER BY
    temperature DESC
LIMIT 10