SELECT title FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE movies.id IN
(SELECT stars.movie_id FROM stars WHERE person_id =
(SELECT people.id FROM people WHERE name = 'Chadwick Boseman'))
ORDER BY -rating LIMIT 5;
