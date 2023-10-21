#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for file manipulation */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* to manipulate inputs */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/*AlphaNumeric Transfering function() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* Function for Command input */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - a data structure for linking strings
 * @num: the number field
 * @str: a string
 * @next: a pointer to mark the next element
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - a custom data type to store information,
 * @arg: the shell input or command for the interactive mode
 * @argv:the commandline input from the non interactive mode
 * @path: the path to the binary executable
 * @argc: input count from the command line argument
 * @line_count: a counter fo the line numbers
 * @err_num: the information number received as status of error
 * @linecount_flag: Status conunt for the line information
 * @fname: the name assigned to the program
 * @env: list of the environmental variable as stored by the shell
 * @environ: the customised copy of the local enviroment
 * @history: the information hub of all previous events
 * @alias: hte node alternative name
 * @env_changed: status of the enviroment
 * @status: status report of previous command
 * @cmd_buf: pointer to the previous command
 * @cmd_buf_type: logic type of the command buffer;
 * @readfd: the file to be read to the structure
 * @histcount: the number of line added to the history
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
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - a structurer for string manupulation
 * @type: the specifier for the string
 * @func: A pointer to the info function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
void wem(int filedescriptor, const char *prog_name, const char *filename);
int h_shell(info_t *, char **);
int find_bltin(info_t *);
void find_inputcmd(info_t *);
void fork_inputcmd(info_t *);

/* toem_parser.c */
int is_inputcmd(info_t *, char *);
char *dupp_chars(char *, int, int);
char *find_shellpath(info_t *, char *, char *);

/* loophsh.c */
int loop_shell(char **);

/* toem_errors.c */
void _shellputs(char *);
int _shelleputchar(char);
int _shellputfd(char c, int fd);
int _shellputsfd(char *str, int fd);

/* toem_string.c */
int _stringlength(char *);
int _stringcmp(char *, char *);
char *st_with(const char *, const char *);
char *_stringcat(char *, char *);

/* toem_string1.c */
char *_stringcopy(char *, char *);
char *_stringdupper(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_stringncopy(char *, char *, int);
char *_stringncat(char *, char *, int);
char *_stringchr(char *, char);

/* toem_tokenizer.c */
char **stringtow(char *, char *);
char **stringtow2(char *, char);

/* toem_realloc.c */
char *_memoryset(char *, char, unsigned int);
void forcefree(char **);
void *_myrealloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bytefree(void **);

/* toem_atoi.c */
int myinteract(info_t *);
int myis_delim(char, char *);
int _myisalpha(int);
int _myatoi(char *);

/* toem_errors1.c */
int _myerratoi(char *);
void print_myerror(info_t *, char *);
int print_myd(int, int);
char *convert_mynumber(long int, int, int);
void remove_mycomments(char *);

/* toem_builtin.c */
int _amyexit(info_t *);
int _amycd(info_t *);
int _amyhelp(info_t *);

/* toem_builtin1.c */
int _amyhistory(info_t *);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _amyalias(info_t *);

/*toem_getline.c */
ssize_t myget_input(info_t *);
int _mygetline(info_t *, char **, size_t *);
void mysigintHandler(int);

/* toem_getinfo.c */
void myclear_info(info_t *);
void set_myinfo(info_t *, char **);
void free_myinfo(info_t *, int);

/* toem_environ.c */
char *_mygetenv(info_t *, const char *);
int _amyenv(info_t *);
int _amysetenv(info_t *);
int _amyunsetenv(info_t *);
int mypopulate_env_list(info_t *);

/* toem_getenv.c */
char **myget_environ(info_t *);
int _myunsetenv(info_t *, char *);
int _mysetenv(info_t *, char *, char *);

/* toem_history.c */
char *myget_history_file(info_t *info);
int mywrite_history(info_t *info);
int myread_history(info_t *info);
int mybuild_history_list(info_t *info, char *buf, int linecount);
int myrenumber_history(info_t *info);

/* toem_lists.c */
list_t *myadd_node(list_t **, const char *, int);
list_t *myadd_node_end(list_t **, const char *, int);
size_t myprint_list_str(const list_t *);
int mydelete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t mylist_len(const list_t *);
char **mylist_to_strings(list_t *);
size_t myprint_list(const list_t *);
list_t *mynode_starts_with(list_t *, char *, char);
ssize_t myget_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_mychain(info_t *, char *, size_t *);
void check_mychain(info_t *, char *, size_t *, size_t, size_t);
int replace_myalias(info_t *);
int replace_myvars(info_t *);
int replace_mystring(char **, char *);

#endif
