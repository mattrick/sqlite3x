#include <iostream>

#include <sqlite3x/sqlite3x.hpp>

struct Functor
{
	void operator() ()
	{
		std::cout << "I'm not expecting any arguments. Not at all. T_T" << std::endl;
	}
};

void Function(int id)
{
	std::cout << id << " ";
}

int main(int argc, const char** argv)
{
	SQLite3x::DB db("sqlite3x.db");

	db.Exec("CREATE TABLE IF NOT EXISTS %s (%s INT, %s TEXT);", "example", "id", "name");

	db.Query("INSERT INTO example VALUES (?, ?);")->Bind(2, "Me")->Execute();
	db.Query("INSERT INTO example VALUES (%d, \"%s\");", 4, "You")->Execute();
	db.Query("INSERT INTO example VALUES (%d, ?);", 2)->Bind("Me again")->Execute();

	db.Query("SELECT NULL FROM example LIMIT 1;")->Execute(Functor());

	db.Query("SELECT * FROM example;")->Execute(&Function);

	db.Query("SELECT * FROM example WHERE %s=?;", "id")->Bind(2)->Execute([](int id, std::string name){ std::cout << std::endl << "Hello, my name is " << name << " and I'm id " << id; });

	return 0;
}