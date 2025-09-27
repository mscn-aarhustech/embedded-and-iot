SELECT
  CASE strftime('%w', timestamp, 'unixepoch')
    WHEN '0' THEN 'Sunday'
    WHEN '1' THEN 'Monday'
    WHEN '2' THEN 'Tuesday'
    WHEN '3' THEN 'Wednesday'
    WHEN '4' THEN 'Thursday'
    WHEN '5' THEN 'Friday'
    ELSE 'Saturday'
  END AS day_of_week,
  strftime('%Y-%m-%d', timestamp, 'unixepoch') AS full_date,
  temperature
FROM
  sensor_data
LIMIT 5;