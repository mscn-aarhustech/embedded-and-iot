-- 

SELECT
    strftime('%Y-%m-%d %H:%M:%S', timestamp, 'unixepoch') AS datetime,
    co2,
    tvoc,
    temperature
FROM
    sensor_data
ORDER BY
    co2 DESC -- Sort hi to low
LIMIT 10;