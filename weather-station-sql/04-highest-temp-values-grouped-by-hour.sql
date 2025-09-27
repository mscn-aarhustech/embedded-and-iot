
-- Hent de ti varmeste timer

SELECT
    strftime('%Y-%m-%d %H:00', timestamp, 'unixepoch') as hour,
    temperature as avg_temp,
    count(*) as num_values
FROM
    sensor_data
WHERE
    temperature < 100
GROUP BY
    hour
ORDER BY
    avg_temp DESC
LIMIT 10