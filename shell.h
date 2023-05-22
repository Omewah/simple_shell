#ifndef _SHELL_H
#define _SHELL_H

#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".MYshell_history"
#define HIST_MAX	4096
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/**
 * struct LIST_STRINGIN - a singly linked list structure
 * @nnumIN: the nth input number variable
 * @stringIN: string variable node structure
 * @next_nodeIN: the next node pointer
 */
typedef struct LIST_STRINGIN
{
	int nnumIN;
	char *stringIN;
	struct LIST_STRINGIN *next_nodeIN;
} list_t;

/**
 * struct passintel - a struct contained with pseudo arguments
 * @strargIN: string containing arguements gotten from the getline function
 * @strargvIN: arrays of strings to be generated from the string argument
 * @strpathIN: the path for the current command input
 * @strarg_counterIN: appends the number of arguments in a string
 * @linecounterIN: a counter that prints the number of errors in a line
 * @_errnum: the will print the exit error code
 * @MYlinecount_flagIN: this is a counter for the input line
 * @MYfilename: the file name of the program
 * @MYenvIron: local copy of environ linked list
 * @historynodeIN: a function that contains the history node
 * @alias_nodeIN: the function that contains the alias node
 * @MYenviron_checker: a checker if the environment changes
 * @MYcmd_status: prints the status of the previous executed command input
 * @MYcmd_buffer: a pointer that points to the command buffer
 * @MYcmd_buffer_types: prints the buffer command type
 * @MYreadfiledes: a file descriptor that reads the line input
 * @MYhistory_counter: the counter for history line number
 * @environ: an updated copy of environ from the environ Linked List
 */
typedef struct passintel
{
	char *strargIN;
	char **strargvIN;
	char *strpathIN;
	int strarg_counterIN;
	unsigned int linecounterIN;
	int _errnum;
	int MYlinecount_flagIN;
	char *MYfilename;
	list_t *MYenvIron;
	list_t *historynodeIN;
	list_t *alias_nodeIN;
	char **environ;
	int MYenviron_checker;
	int MYcmd_status;
	char **MYcmd_buffer;
	int MYcmd_buffer_types;
	int MYreadfiledes;
	int MYhistory_counter;
} intel_t;

#define INTEL_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct BUILT_IN - struct contains builtin string commands and its functions
 * @MYtypes_IN: the command flag built in the struct
 * @MYfunctionIN: the struct command function
 */
typedef struct BUILT_IN
{
	char *MYtypes_IN;
	int (*MYfunctionIN)(intel_t *);
} built_in_tables;



int _shell_pfunc(intel_t *, char **);
int locate_builtin_pfunc(intel_t *);
void locate_cmd_pfunc(intel_t *);
void fork_cmd_pfunc(intel_t *);
int _cmdexe_pfunc(intel_t *, char *);
char *_dupchars_pfunc(char *, int, int);
char *locate_path_pfunc(intel_t *, char *, char *);
void _errputs_pfunc(char *);
int _errputchar_pfunc(char);
int _putfiledes_pfunc(char c, int fd);
int _putsfiledes_pfunc(char *str, int fd);
int _lenstrn_pfunc(char *);
int _comparestr_pfunc(char *, char *);
char *checkpoint_pfunc(const char *, const char *);
char *_concatstr_pfunc(char *, char *);
char *_copystr_pfunc(char *, char *);
char *_doublestr_pfunc(const char *);
void _puts_pfunc(char *);
int _putchar_pfunc(char);
char *_copystrn_pfunc(char *, char *, int);
char *_concatstrn_pfunc(char *, char *, int);
char *_findstrchar_pfunc(char *, char);
char **splitstr_pfunc(char *, char *);
char **splitstrn_pfunc(char *, char);
char *_set_constmem_pfunc(char *, char, unsigned int);
void _strfree_pfunc(char **);
void *_memredis_pfunc(void *, unsigned int, unsigned int);
int _pmemfree_pfunc(void **);
int _shellact_pfunc(intel_t *);
int _defchar_pfunc(char, char *);
int _syllab_pfunc(int);
int _atoi_pfunc(char *);
int _atoierr_pfunc(char *);
void _prterror_pfunc(intel_t *, char *);
int ddprint_pfunc(int, int);
char *ddconvert_pfunc(long int, int, int);
void hashdel_pfunc(char *);
int _shellexit_pfunc(intel_t *);
int _changedir_pfunc(intel_t *);
int _procdir_pfunc(intel_t *);
int _shellhist_pfunc(intel_t *);
int _alias_pfunc(intel_t *);
ssize_t _getIN_pfunc(intel_t *);
int _lineIN_pfunc(intel_t *, char **, size_t *);
void sigintH_pfunc(int);
void _intel_clear(intel_t *);
void _intel_set(intel_t *, char **);
void _intel_free(intel_t *, int);
char *getenvIN(intel_t *, const char *);
int _currenv(intel_t *);
int _envset_pfunc(intel_t *);
int _envunset_pfunc(intel_t *);
int load_list_pfunc(intel_t *);
char **environcp_pfunc(intel_t *);
int envunset_pfunc(intel_t *, char *);
int envset_pfunc(intel_t *, char *, char *);
char *_hist_pfunc(intel_t *intel);
int _histw_pfunc(intel_t *intel);
int _histr_pfunc(intel_t *intel);
int _histlist_pfunc(intel_t *intel, char *buf, int linecount);
int _histlink_pfunc(intel_t *intel);
list_t *nodeplus(list_t **, const char *, int);
list_t *nodeplusE(list_t **, const char *, int);
size_t _printL_pfunc(const list_t *);
int del_nodeIN(list_t **, unsigned int);
void nodefree_pfunc(list_t **);
size_t _lgtLL_pfunc(const list_t *);
char **_strlist_pfunc(list_t *);
size_t printLL_pfunc(const list_t *);
list_t *nodeST_pfunc(list_t *, char *, char);
ssize_t nodeIX_pfunc(list_t *, list_t *);
int defchain_pfunc(intel_t *, char *, size_t *);
void extchain_pfunc(intel_t *, char *, size_t *, size_t, size_t);
int subalias(intel_t *);
int subvars(intel_t *);
int substringIN(char **, char *);

extern char **environ;

#endif
