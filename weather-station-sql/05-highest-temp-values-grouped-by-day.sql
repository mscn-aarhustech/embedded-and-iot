
-- Hent de ti varmeste dage

SELECT
    strftime('%Y-%m-%d', timestamp, 'unixepoch') as day,
    temperature as avg_temp,
    count(*) as num_values
FROM
    sensor_data
WHERE
    temperature < 100
GROUP BY
    day
ORDER BY
    avg_temp DESC
LIMIT 10