SELECT name FROM people WHERE people.id IN
(SELECT person_id FROM stars WHERE movie_id =
(SELECT movies.id FROM movies WHERE title = 'Toy Story'));
