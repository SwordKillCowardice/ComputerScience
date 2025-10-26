SELECT DISTINCT(A.name) FROM people AS A WHERE A.id IN
(SELECT B.person_id FROM stars AS B WHERE B.movie_id IN
(SELECT C.movie_id FROM stars AS C WHERE C.person_id =
(SELECT D.id FROM people AS D WHERE D.name = 'Kevin Bacon' AND D.birth = 1958)))
AND (A.name <> 'Kevin Bacon' OR (A.name = 'Kevin Bacon' AND A.birth <> 1958));
