SELECT title FROM movies WHERE movies.id IN
(SELECT A.movie_id FROM stars AS A
JOIN stars AS B ON A.movie_id = B.movie_id
WHERE A.person_id = (SELECT people.id FROM people WHERE name = 'Bradley Cooper')
AND B.person_id = (SELECT people.id FROM people WHERE name = 'Jennifer Lawrence'));
