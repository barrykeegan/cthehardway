#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_DATA 512
#define MAX_ROWS 100

//Define a struct (possibly should be called record) to store details
//at address "id". This struct will store the id and whether set or not.
//When in create mode set will be set to 1 and the name will be stored
//in name (max length 512 chars) and email will be stored in email (same max).
struct Address
{
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

//When a database is used, it makes enough space in memory for the full
//database each time, 100 rows.
struct Database
{
    struct Address rows[MAX_ROWS];
};

//A connection to a database contains a pointer to the file where the 
//database is read from and written too, and also a pointer to the 
//database in memory.
struct Connection
{
    FILE *file;
    struct Database *db;
};

void Database_close(struct Connection *conn);

//die() function created to help program terminate gracefully on reaching
//certain errors. Message to be displayed passed to die function.
void die(const char *message, struct Connection *conn)
{
    Database_close(conn);

    if (errno)
    {
        perror(message);
    }
    else
    {
        printf("ERROR: %s\n", message);
    }

    //exit with non-zero to indicate erroneous termination of program
    exit(1);
}

//function to print a row of the database, row passed to function for printing
void Address_print(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

//load database. function passed in conn which includes pointer to file and db
void Database_load(struct Connection *conn)
{
    //Read conn->file into conn->db. Store result of read attempt in rc
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    //rc contains number of items of size struct Database read.
    //In this case if read was successful rc should equal 1. If rc does not
    //equal one, then error has occurred and control passed to die() for
    //graceful termination.
    if (rc != 1)
    {
        die("Failed to load database.", conn);
    }
}

//This function
//
struct Connection *Database_open(const char *filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn)
    {
        die("Memory error", conn);
    }

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db)
    {
        die("Memory error", conn);
    }

    if (mode == 'c')
    {
        conn->file = fopen(filename, "w");
    }
    else
    {
        conn->file = fopen(filename, "r+");
        if (conn->file)
        {
            Database_load(conn);
        }
    }

    if (!conn->file)
    {
        die("Failed to open the file", conn);
    }

    return conn;
}

void Database_close(struct Connection *conn)
{
    if (conn)
    {
        if(conn->file)
        {
            fclose(conn->file);
        }
        if(conn->db)
        {
            free(conn->db);
        }
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1)
    {
        die("Failed to write database.", conn);
    }

    rc = fflush(conn->file);
    if (rc == -1)
    {
        die("Cannot flush database", conn);
    }
}

void Database_create(struct Connection *conn)
{
    int i = 0;

    for (i=0; i < MAX_ROWS; i++)
    {
        //make a prototype to initialise it
        struct Address addr = {.id = i, .set = 0};
        //then just assign it
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if(addr->set)
    {
        die("Already set, delete it first", conn);
    }
    addr->set = 1;
    //WARNING: bug, read the "How to Break" and fix this
    char *res = strncpy(addr->name, name, MAX_DATA);
    //demonstrate the strncpy bug
    if (!res)
    {
        die("Name copy failed", conn);
    }

    res = strncpy(addr->email, email, MAX_DATA);
    if (!res)
    {
        die("Email copy failed", conn);
    }
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if (addr->set)
    {
        Address_print(addr);
    }
    else
    {
        die("ID is not set", conn);
    }
}

void Database_delete(struct Connection *conn, int id)
{
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for (i = 0; i < MAX_ROWS; i++)
    {
        struct Address *cur = &db->rows[i];

        if (cur->set)
        {
            Address_print(cur);
        }
    }
}

int main(int argc, char * argv[])
{
    printf("argc = %d\n", argc);
    if (argc<3)
    {
        die("USAGE:\
           \nex17 <dbfile> c [[MAX_ROWS] MAX_DATA]\
           \nex17 <dbfile> s <id> <name> <email>\
           \nex17 <dbfile> g <id>\
           \nex17 <dbfile> d <id>\
           \nex17 <dbfile> l", NULL);
    }

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection  *conn = Database_open(filename, action);
    int id =0;

    if(argc>3)
    {
        id = atoi(argv[3]);
    }
    
    if(id >= MAX_ROWS)
    {
        die("There's not that many records.", conn);
    }

    switch (action)
    {
      case 'c':

         Database_create(conn);
         Database_write(conn);
         break;

      case 'g':
         if(argc != 4)
         {
             die("Need an ID to get", conn);
         }
         Database_get(conn, id);
         break;
     case 's':
        if (argc != 6)
        {
            die("Need id, name, email to set", conn);
        }

        Database_set(conn, id, argv[4], argv[5]);
        Database_write(conn);

        break;
    case 'd':
        if(argc != 4)
        {
            die("Need id to delete", conn);
        }

        Database_delete(conn, id);
        Database_write(conn);
        break;
    case 'l':
        Database_list(conn);
        break;
    default:
        die("Invalid action: c=create, g=get, s=set, d=del, l=list", conn);
    }

    Database_close(conn);

    return 0;
}
