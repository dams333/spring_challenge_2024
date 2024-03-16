-- SQL request(s)​​​​​​‌​‌​‌‌​‌‌‌‌​‌​‌‌​‌‌​​‌​​​ below
SELECT
    u.NEWCOLOR as color,
    COUNT(u.NEWCOLOR) as count
FROM pixels as p
INNER JOIN pixelUpdates as u
    ON u.PIXELID = p.ID
    AND u.UPDATEDAT != p.FIRSTPAINTEDAT
GROUP BY color
ORDER BY count DESC
