/* source: http://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm  */
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *data, int argc, char **argv, char **azColName){
	int i;
	if (data != NULL)
		fprintf(stderr, "%s: ", (const char*)data);
	for(i=0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

static int execute_sql(sqlite3 *db, char *sql) {
	int rc = 0;
	char *zErrMsg = 0;

	printf("------------------------------------------------------------\n");
	printf("execute sql command: %s\n", sql);
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error[%d]: %s\n", rc, zErrMsg);
		sqlite3_free(zErrMsg);
		return 1;
	}else{
		fprintf(stdout, "execute successfully\n");
	}

	return 0;
}

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *sql_create;
   char *sql_insert;
   char *sql_select;
   char *sql_update;
   char *sql_delete;

   int rc;

   rc = sqlite3_open("test.db", &db);

   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

	/* Create SQL statement */
   sql_create = "CREATE TABLE IF NOT EXISTS COMPANY("  \
				 "ID INT PRIMARY KEY     NOT NULL," \
				 "NAME           TEXT    NOT NULL," \
				 "AGE            INT     NOT NULL," \
				 "ADDRESS        CHAR(50)," \
				 "SALARY         REAL );";
   if (0 != execute_sql(db, sql_create)) return 0;

   /* insert statement */
   sql_insert = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
				 "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
				 "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
				 "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
				 "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
				 "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
				 "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
				 "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

   if (0 != execute_sql(db, sql_insert)) goto END_DB;

   /* Select statement */
   sql_select = "SELECT * from COMPANY";

   if (0 != execute_sql(db, sql_select)) goto END_DB;

   /* Create merged SQL statement */
   sql_update = "UPDATE COMPANY set SALARY = 25000.00 where ID=1; " \
				 "SELECT * from COMPANY";

   if (0 != execute_sql(db, sql_update)) goto END_DB;


   /* Delete statement */
   sql_delete = "DELETE from COMPANY where ID=2; " \
				 "SELECT * from COMPANY";

   if (0 != execute_sql(db, sql_delete)) goto END_DB;


END_DB:
   sqlite3_close(db);

   return 0;
}
