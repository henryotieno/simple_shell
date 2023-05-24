#ifndef _SHELL_H_
#define _SHELL_H_

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>

/*compile and run programs*/
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024

/*differentiating commands*/
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3


/*convert_number()constants*/
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/*to define strtok() and getline()*/
#define USE_STRTOK 0
#define USE_GETLINE 0

/*size and name of history file*/
#define HIST_MAX 4096
#define HIST_FILE ".simple_shell_history"

/*declares global variable: environ*/

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: field number
 * @next: next node
 * @str: string
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains the arguments
 * @env_changed: when environ shifts
 * @status: return condition
 * @linecount_flag: counts line
 * @cmd_buf: address when chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: file reader
 * @histcount: no. of history lines
 * @err_num: exit error code
 * @arg: geline string
 * @argv: arg array of strings
 * @path: path
 * @argc: no. of args
 * @line_count: no. of errors
 * @fname: name of file
 * @env: environ duplicate
 * @environ: changed environ
 * @history: history node
 * @alias: alias node
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_x;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}
/**
 * struct builtin - has two functions
 * @type: command flag for builtin
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_x *);
} builtin_table;

/*for toem_atoi.c */
int av (info_x *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);


/*for toem_vars.c */
int is_chain(info_x *, char *, size_t *);
void check_chain(info_x *, char *, size_t *, size_t, size_t);
int replace_alias(info_x *);
int replace_vars(info_x *);
int replace_string(char **, char *);

/*for toem_shloop.c */
int hsh(info_x *, char **);
int find_builtin(info_x *);
void find_cmd(info_x *);
void fork_cmd(info_x *);

/*for toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);


/*for toem_exits.c */
char *_cpystrn(char *, char *, int);
char *_cattstrn(char *, char *, int);
char *_strchr(char *, char);


/*for toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/*for toem_history.c */
char *get_history_file(info_x *info);
int write_history(info_x *info);
int read_history(info_x *info);
int build_history_list(info_x *info, char *buf, int linecount);
int renumber_history(info_x *info);


/*for toem_getinfo.c */
void clear_info(info_x *);
void set_info(info_x *, char **);
void free_info(info_x *, int);


/*for toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/*for toem_environ.c */
char *_getenv(info_x *, const char *);
int _theenv(info_x *);
int _thesetenv(info_x *);
int _theunsetenv(info_x *);
int populate_env_list(info_x *);


/*for toem_getline.c */
ssize_t get_input(info_x *);
int _getline(info_x *, char **, size_t *);
void sigintHandler(int);


/*for toem_getenv.c */
char **fetch_environ(info_x *);
int _unsetenv(info_x *, char *);
int _setenv(info_x *, char *, char *);

/*for toem_getinfo.c */
void clear_info(info_x *);
void set_info(info_x *, char **);
void free_info(info_x *, int);


/*for toem_memory.c */
int bfree(void **);

/*for toem_parser.c */
int is_cmd(info_x *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_x *, char *, char *);


/*for toem_exits.c */
char *_cpystrn(char *, char *, int);
char *_cattstrn(char *, char *, int);
char *_strchr(char *, char);


/*for toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/*for loophsh.c */
int loophsh(char **);

/*for toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);


/*for toem_builtin.c */
int _theexit(info_x *);
int _thecd(info_x *);
int _thehelp(info_x *);


/*for toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/*for toem_errors1.c */
int _erratoi(char *);
void print_error(info_x *, char *);
int print_y(int, int);
char *change_number(long int, int, int);
void remove_comments(char *);


/*for toem_builtin1.c */
int _thehistory(info_x *);
int _myalias(info_x *);


/*for toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

#endif

