-- SQL request(s) below
SELECT
    u.NEWCOLOR as color,
    COUNT(u.NEWCOLOR) as count
FROM pixelUpdates u
JOIN pixels p ON p.ID = u.PIXELID
where p.FIRSTPAINTEDAT != u.UPDATEDAT
GROUP BY u.NEWCOLOR
ORDEr BY COUNT(u.NEWCOLOR) DESC
