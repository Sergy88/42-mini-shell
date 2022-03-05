#ifndef MINI_SHELL_H
#define MINI_SHELL_H

/* unchecked */
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

/* readline */
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/* signals */
#include <signal.h>

/* utils */
#include <stdlib.h>

# define PROMPT "minishell:"
# define BIN_SUCCEED 0
# define BIN_PERM_ERR 1
# define BIN_NOT_FOUND 2
# define BIN_IS_DIR 3
#ifndef PATH_MAX
# define PATH_MAX 1024
#endif

enum type{
	NONE, //default set
	ARG, //word
	FILE_IN_OP, //word == '<'
	HERE_DOC_OP, // word == '<<'
	FILE_OUT_OP, //word == '>'
	FILE_OUT_APPEND_OP, //word == '>>'
	IN_FILE, // word following '<'
	LIM, // word following '<<'
	OUT_FILE, // word following '>'
	FILE_OUT_APPEND // word following '>>'
};

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef struct s_command{
	char *cmd_line;
	t_list *element;
} t_command;

typedef struct s_word{
	char *val;
	enum type t;
} t_word;

int parse(void);
int launch_commands();

/* global env */
//extern char **g_data.env;

typedef struct s_data
{
	char	**env;
	int 	ret_val;
}	t_data;

extern t_data g_data;

/* signals */
void	hook_signals();

/* common utils */
char	**ft_split(char const *s, char c);
int		consider_empty(char *str);
char	*ft_strdup(const char *s);
int		ft_str_arr_size(char **char_arr);
int		parse_environment(char **env);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int 	launch_commands(t_list **commands);
char	**ft_split_spaces(char const *s);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*get_env_var(char **var_arr, const char *key);
char	*ft_strjoin(char *s1, char *s2);
void    ft_put_err(const char *str);
void	ft_put_err_cmd(const char *cmd, const char *str);
void	ft_put_err_sh_cmd(const char *cmd, const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_keycmp(const char *s1, const char *s2);
void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
int		have_first_last_char(char *string, char ch);
char	**ft_split_multiple_del(char const *s, char *del);


/* simple checks*/
int is_delim(char i);

/* launching utils */
int	assemble_path(char *bin_name, char **paths, char **assembled_path);
void	ft_wait_status();
int		ft_exe(t_list *command, t_list *commands);
int		is_built_in(t_list *cmd_lst);
int		launch_built_in(t_list *command, t_list *cmd_list);
void	launch_forked(t_list *command_lst, int fd[2], int std_io[2], int cmd_count);


/*builtins*/
int		ft_cd(char **argv);
int		ft_pwd(void);
int		ft_env(void);
int		ft_exit(char **params, t_list *cmd_to_free);
int		ft_echo(char **argv);
int		ft_export(char **argv);
int 	ft_unset(char **argv);

/* parse */
t_list *parse_input(char **input);
int		set_types(t_list *elements);
int is_file_in_op(t_list *pList);
int is_here_doc(t_list *pList);
int is_file_out_append(t_list *pList);
int is_file_out_op(t_list *pList);
int is_file_out_append_op(t_list *pList);
int is_in_file(t_list *pList);
int is_lim(t_list *pList);
int is_out_file(t_list *pList);
int is_arg(t_list *pList);
t_word *get_word_by_type(t_list *cmd, enum type t);
int	here_doc_fd(char *delim);
void delete_all_files();
int is_quotes_open(char *str);
void change_quote_flags(int q_flags[2], const char *ch);
char *str_insert(char *big, char *pos, char *lit);
void ft_substitution(char **str_p);
void	ft_unquote(char **str_p);
void	skip_arg(char *line, int *c_pos);
void	skip_redir(char *line, int *pos);
int is_quotes(const char *str);
int cpy_unquote(char *src, char *dst);
char	**ft_split_quotes(char const *s);
int	have_empty_cmds(t_list *commands_list);
int		is_inconsiderable(char ch);

/* list utils */
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void*));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split_pipes(char const *s);

/* dao */
t_command *get_cmd(t_list *lst);
t_word		*get_word(t_list *lst);
char **get_args(t_list *command);
char *get_word_str(t_list *lst);
char *get_cmd_str(t_list *lst);
enum type get_word_type(t_list *lst);

/* memutils */
void free_cmds(t_list **cmds);
void free_word(void* word);
void free_cmd(void* cmd);
void free_str_arr(char ** str_arr);
void free_all(t_list *cmds);
void free_all_but_hist(t_list *cmds);

/* debug */
void print_word(t_list *word);
void print_cmds(t_list *cmd);
void print_str_arr(char **str_arr);

/* redirect */
int setup_fd(t_list *command, int pInt[2]);




#endif
