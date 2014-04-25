/* source: http://www.csl.mtu.edu/cs1141/www/examples/sqlite/sqlite_insert.c */
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

/*
 * In this example, we'll open a simple inventory database, create an
 * inventory table if one is required, insert some data into the database
 * and then prompt the user to save the changes or roll them back.
 *
 * This demo uses sqlite3_exec() for table creation and select queries,
 * but uses prepare/step/finalize for inserts. This way, we can bind
 * new values into the query after it is prepared avoiding issues with
 * Little Bobby Tables (see http://xkcd.com/327/)
 */

/*
 * Note: This code isn't ANSI-compliant C. I've left variable definitions
 * close to where they're used to improve the overall flow of the example.
 * It should be possible to move them to the top of the code, though, at
 * which point ANSI compliance should be restored.
 */

/*
 * To compile:
 *    gcc -lsqlite3 -o insert sqlite_insert.cpp
 * (the -lsqlite3 instructs the linker to link in the sqlite library, which
 * isn't normally considered when looking for unmet dependencies)
 *
 * To run:
 *    ./insert
 */

/* callback function for SELECT queries. More on this later */
int callback(void *param, int numCols, char **col, char **colName);

int main(){
  
  int col_width[] = {5, 0}; // column widths for display purposes
  
  /*
   * In the proud tradition of C libraries, we set up a sqlite database
   * 'object' which then gets passed into most of the functions.
   */
  sqlite3 *db;
  
  int rc; // return code from sqlite functions

  /*
   * regardless of how we're accessing a database, we always have to
   * open the database before we use it, and close it where we're done
   */
  rc = sqlite3_open("inventory.sqlite", &db);
  
  /* always check to make sure the function you called was successful */
  if( rc != SQLITE_OK ){
    /* we'll get here if there was a problem */
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db); /* remember to clean up the database */
    exit(1);
  }
  
  /*
   * sqlite3_open will automatically create the database if it doesn't
   * already exist. if that happens, we need to create the table. of
   * course, if the database already exists overwriting the data would
   * be a Bad Thing
   *
   * CREATE TABLE will never overwrite an existing table. under normal
   * operation, it will fail with an error if it finds a table with
   * the same name. IF NOT EXISTS means that the query will 'work'
   * (that is, not error out) if the table exists already, with the
   * end result that once we get past this query we are guaranteed to
   * have a working table.
   */
  char createdb[] =
  "CREATE TABLE IF NOT EXISTS 'inventory' ('quantity' 'INTEGER', 'item' 'TEXT');";
  
    char *zErrMsg = 0;  /* this'll get pointed at error messages, if applicable */
  
  /* now we run our query */
  rc = sqlite3_exec(
    db,           /* db object on which to act, as returned by sqlite3_open */
    createdb,     /* a char[] containing the query to execute */
    0,            /* no need for a callback function if we don't return results */
    0,            /* no need for params to callback fcn if we don't have one */
    &zErrMsg      /* pointer to char[] in which to store an error message */
  );
  
  /* once again, check for errors */
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);  /* this alloc'ed by sqlite, so free the same way */
    sqlite3_close(db);
    exit(1);
  }
  
  /*
   * Transactions allow a bunch of commands to be executed or rolled
   * back as a single unit. SELECT sees any changes made in the transaction
   * but nothing actually gets committed to hard starage until the
   * transaction is committed.
   *
   * start a transaction by executing the query BEGIN. everything
   * executed between the BEGIN and the next COMMIT or ROLLBACK will
   * be treated as part of a single transaction
   */
  char trans = 'n';
  printf("enable transactions? ");
  scanf("%c", &trans);
  
  if (trans == 'y') {
    sqlite3_exec(db, "BEGIN;", 0, 0, &zErrMsg);
  }
  if( rc!=SQLITE_OK ){
    /* once again, checking for problems and cleaning up, if need be */
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
    sqlite3_close(db);
    exit(1);
  }
  
  /*
   * we can now be sure that the database has the tables we need
   * time to insert some data, no?
   *
   * We'll use a simple loop to fetch data from the user, one
   * record at a time. when we've got enough data, we'll move on
   */
  
  char desc[30];    /* item description. could be a larger array, if need be */
  int qty;          /* quantity of items on-hand */
  char conf;        /* used to store confirmation data from user */
  
  
    /*
   * Prepare will let us put placeholders into a query to be
   * filled in later using the various forms of bind(). We don't
   * need to do this when we control the entire query, but we
   * want to make sure a malicious user can't screw up our database.
   * We could try and sanitize the user input, but we still run
   * the risk of something slipping through and being treated as
   * executable SQL.
   *
   * Preparing first and binding later means that the user's data
   * hasn't arrived in the query when it gets prepared, so there's
   * absolutely no chance of the user injecting something nasty
   * into the query.
   *
   * You can specify placeholders using ?, but it's a little nicer
   * to use the :VVV format, which means we can reuse values, and
   * look up value positions by name.
   *
   * Note that, once we prepare the statement we can reuse it
   * as many times as we want.
   */
  sqlite3_stmt * item_insert;
  char insert_query[] = "INSERT INTO inventory (item, quantity) VALUES (:ITEM, :QTY);";
  rc = sqlite3_prepare_v2(db, insert_query, sizeof(insert_query), &item_insert, NULL);
  
  if( rc ){ /* incidentally, SQLITE_OK == 0, so anything not OK is true */
    fprintf(stderr, "Couldn't prepare query: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(1);
  }
  
    
  while(1) {
    /*
     * get new information from user
     * This version doesn't suppose spaces in the description.
     * use, eg, fgets if you want spaces to be included
     */
    printf("Please enter an item description: ");
    scanf("%29s", desc); 
    printf("How many do we have? ");
    scanf("%i", &qty);
    
    
    /*
     * sqlite provides type-specific bind functions for all of its
     * supported data types. All forms take three parameters:
     *    a statement to bind data to
     *    the index of the placeholder to be filled (numbered from 1)
     *    the data to bind in
     * The text and blob varients also need a count of the number
     * of bytes to bind (-1 to read until first null-termination),
     * and a function to call to destroy the data. SQLITE_STATIC
     * tells sqlite that it doesn't need to free the memory itself
     */
    rc = sqlite3_bind_text(item_insert, 1, desc, -1, SQLITE_STATIC);
    
    if( rc!=SQLITE_OK ){
      fprintf(stderr, "Can't bind in description: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      exit(1);
    }
    
    rc = sqlite3_bind_int(item_insert, 2, qty);
    
    if( rc!=SQLITE_OK ){
      fprintf(stderr, "Can't bind in quantity: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      exit(1);
    }
    
    /* step can run queries that don't return values, too */
    rc = sqlite3_step(item_insert);
    if (rc != SQLITE_DONE) {
      fprintf(stderr, "Couldn't step the query: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      exit(1);
    }
    
    
    /*
     * you *must* reset the statement before binding in new values.
     * bind will fail if you call step() and fail to reset() before
     * binding the next time
     */
    rc = sqlite3_reset(item_insert);
    if (rc != SQLITE_OK) {
      fprintf(stderr, "Couldn't reset the statement: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      exit(1);
    }
    
    /* see if user wants to insert another item */
    printf("Insert another? ");
    scanf("%1s", &conf);
    if(conf == 'n') { break; }
  }
  
  /*
   * We have to finalize the statement when we're done with it.
   * failing to do so results in a sizable (~15KB) memory leak
   */
  rc = sqlite3_finalize(item_insert);
  if( rc ) {
    fprintf(stderr, "Can't finalize statement: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(1);
  }
  
  
  /*
   * At this point, you have to take my word for it that the data was
   * inserted. let's do a select to prove it's in there
   */
  printf("\nNow displaying contents of inventory\n\n");
  printf(" |  Qty  | Item\n");
  printf(" |-------|-------\n");
  
  /* note that we're passing a callback function and chunk of data this time */
  rc = sqlite3_exec(db, "SELECT * FROM inventory;", callback, col_width, &zErrMsg);
  
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
    sqlite3_close(db);
    exit(1);
  }
  
  /*
   * If we have transactions turned on, we need to give the
   * user the option to either save the changes or roll them back
   */
  if(trans == 'y') {
    printf("save changes? ");
    scanf("%s", &conf);
    
    /*
     * Committing a transaction commits it to long-term storage, making
     * whatever occured in the transaction permanent.
     *
     * Rolling back, by contrast, undoes any changes made during the transaction
     */
    if (conf == 'y') {
      sqlite3_exec(db, "COMMIT;", 0, 0, &zErrMsg);
    }
    else {
      sqlite3_exec(db, "ROLLBACK;", 0, 0, &zErrMsg);
    }
    
    if( rc!=SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      sqlite3_close(db);
      exit(1);
    }
    
    /* and here's proof that things worked as expected */
    printf("\nContents of inventory after save/rollback\n\n");
    printf(" |  Qty  | Item\n");
    printf(" |-------|-------\n");
    
    rc = sqlite3_exec(db, "SELECT * FROM inventory;", callback, col_width, &zErrMsg);
  }
  
  /*
   * just like we always need to finalize statements, we always have
   * to close out a db object when we're done with it. This is like
   * closing out a file, but can't be handled automatically by the OS
   *
   * sqlite can tolerate a database being left in an un-closed state,
   * but generally isn't at all happy about it.
   */
  sqlite3_close(db);
  
  return 0;
}

/*
 * This is a callback function for use by sqlite3_exec. You can have
 * as many of these as you want / need, so long as the prototype matches.
 *
 * received parameters are:
 *    *param    : a void pointer provided as arg 4 to the
 *                sqlite3_exec call. Useful if you need to
 *                get other data into / out of the function
 *    numCols   : Number of columns returned by the query
 *    **col     : Array of char[] containing values in the row
 *    **colName : Array of char[] containing column names
 *
 * Note that sqlite returns text regardless of the actual type of the column.
 * If you want / need numeric forms, you'll have to convert the text to them
 */
int callback(void *param, int numCols, char **col, char **colName)
{
  int i;
  int *col_width = (int *)param;  /* not necessary, but handy */
  
  /* print the contents of this row */
  for(i=0; i<numCols; i++){
    printf(" | %*s", col_width[i], col[i]);
  }
  printf("\n");
  
  return 0;
}

