#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/*  Buffers */
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024

/* Command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Convert_number */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - Singly linked list.
 * @num: Field number.
 * @str: String.
 * @next: Pointer to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - pseudo-arguements.
 * @arg: Arguments string.
 * @argv: Aray of strings.
 * @history: History.
 * @path: String path.
 * @argc: Argument count.
 * @line_count: Error count.
 * @err_num: Error code.
 * @env_changed: On if the environment was changed.
 * @status: Return status of the last exec'd command.
 * @cmd_buf: Pointer to cmd_buf.
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: The file descriptor to read line input.
 * @histcount: The history line number count.
 * @linecount_flag: Counting input lines.
 * @fname: File name.
 * @env: Environment
 * @environ: Modified copy of environment.
 * @alias: Alias node.
 */
typedef struct passinfo
{
	char *arg;
	int err_num;
	int linecount_flag;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - Containing a builtin string.
 * @type: Builtin command flag.
 * @func: Function.
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* File 1*/
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* File 2 */
int _mycd(info_t *);
int _myexit(info_t *);
int _myhelp(info_t *);

/* File 3 */
int _myalias(info_t *);
int _myhistory(info_t *);

/* File 4 */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int populate_env_list(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);

/* File 5 */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* File 6 */
int _erratoi(char *);
char *convert_number(long int, int, int);
void remove_comments(char *);
void print_error(info_t *, char *);
int print_d(int, int);

/* File 7 */
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);

/* File 8 */
ssize_t get_input(info_t *);
void sigintHandler(int);
int _getline(info_t *, char **, size_t *);

/* File 9 */
char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);
int _unsetenv(info_t *, char *);

/* File 10 */
void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);

/* File 11 */
char *get_history_file(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);

/* File 12 */
list_t *add_node(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);

/* File 13 */
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);

/* File 14 */
int bfree(void **);
/* File 15 */
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);

/* File 16 */
void ffree(char **);
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);

/* File 17 */
int hsh(info_t *, char **);
void find_cmd(info_t *);
int find_builtin(info_t *);
void fork_cmd(info_t *);

/* File 18 */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* File 19 */
char *_strcpy(char *, char *);
void _puts(char *);
char *_strdup(const char *);
int _putchar(char);

/* File 20 */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* File 21 */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_string(char **, char *);
int replace_alias(info_t *);
int replace_vars(info_t *);

/* loophsh */
int loophsh(char **);

#endif
