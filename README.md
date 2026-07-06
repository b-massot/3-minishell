*This project has been created as part of the 42 curriculum by <bmassot>bmassot & <ajenren>ajeanren*

# README

Readme for minishell project, part of rank 3 in the main cursus.

# Description

Minishell is a shell but mini. Idea is to build a functional shell with the followed requirements (version 10.0):

- Display a prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
- Use at most one global variable to indicate a received signal. Consider the implications: this approach ensures that your signal handler will not access your main data structures.
- Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or (semicolon).
- Handle ’ (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.
- Handle " (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for $ (dollar sign).
- Implement the following redirections: >, <, >>, <<
- Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
- Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
- Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
- Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
- In interactive mode: ctrl-C displays a new prompt on a new line; ctrl-D exits the shell; ctrl-\ does nothing.
- Your shell must implement the following built-in commands: echo with option -n; cd with only a relative or absolute path; pwd with no options; export with no options; unset with no options; env with no options or arguments; exit with no options

## Overview of the contents
1. Pipeline
2. Step 1 — Reading the line
3. Step 2 — Tokenisation
4. Step 3 — Token list & syntax check
5. Step 4 — Variable expansion
6. Step 5 — Parsing & AST construction
7. Step 6 — Execution
8. Signal handling
9. Builtins
10. Memory management


## Pipeline

```
User input
       │
       ▼
┌───────────────────┐
│  read_shell_line()|  readline() in interactive mode
│  (srcs/main.c)    │ 
└──────┬────────────┘
       │  char *line
       ▼
┌──────────────────────────┐
│  split_shell()           │  Split into raw tokens 
│ (srcs/parse/tokenize/)   │  (["ls", "-la", ">", "out.txt"])
└──────┬───────────────────┘   Respects single and double quotes
       │  char **split
       ▼
┌──────────────────────────┐
│  build_token_list()      │  Build the t_token linked list
│  (srcs/parse/tokenize/)  │  Assign type (WORD/PIPE/REDIR_*)
│  + check_syntax()        │  Validate syntax
└──────┬───────────────────┘
       │  t_token *
       ▼
┌────────────────────────┐
│  expand_all_tokens()   │  Replace $VAR, $?, strip quotes
│  (srcs/parse/expand/)  │  PIPE and REDIR tokens untouched
└──────┬─────────────────┘
       │  t_token * (modified)
       ▼
┌──────────────────────┐
│  parse()             │  Build the AST recursively
│  (srcs/parse/)       │  parse_pipe() → parse_exec_node()
└──────┬───────────────┘
       │  t_cmd *ast
       ▼
┌──────────────────────────┐
│  run_ast()               │  Execute the tree
│  (srcs/exec/ast_exec.c)  │  Builtin → direct / External → fork+execve
└──────┬───────────────────┘
       │  int exit_code
       ▼
  last_exit (reused as $? on the next iteration)
```

## Step 1 — Reading the line

**File:** `main.c` → `read_shell_line()`

```
readline("URSShell $> ")  ← interactive mode only
add_history(line)         ← store in readline history
```

---

## Step 2 — Tokenisation

**Files:** `srcs/parse/tokenize/split.c` + `srcs/parse/tokenize/split_count.c`

The raw line is split into **tokens**, respecting quotes.

```
Input: "echo 'hello world' | grep foo > out.txt"

count_tokens() → 7 tokens (pre-allocates the array)

split_shell() → extracts one by one:

  [0] "echo"
  [1] "'hello world'"   ← space preserved by quotes
  [2] "|"
  [3] "grep"
  [4] "foo"
  [5] ">"
  [6] "out.txt"
  [7] NULL
```

### Splitting rules (`word_len`)

```
Character encountered            Action
──────────────────────────       ──────────────────────────────────────
' (outside double quotes)        toggle in_squote
" (outside single quotes)        toggle in_dquote
space/tab (outside quotes)       END of token
| < > (outside quotes)           END of token
| < > (inside quotes)            part of the token → ignored
```

### Operator length (`op_len`)

```
>> or <<  →  2 characters
|  >  <   →  1 character
```

---
## Step 3 — Token list & syntax check

**Files:** `srcs/parse/tokenize/list.c` + `srcs/parse/syntax/check_syntax.c`

### Building the list (`build_token_list`)

Each raw string from the `split` array becomes a `t_token` node:

```c
typedef struct s_token {
    char           *value;   // "grep", "|", ">"...
    t_token_type    type;    // WORD / PIPE / REDIR_IN / REDIR_OUT / REDIR_APPEND / HEREDOC
    int             quoted;  // 0=unquoted  1=single  2=double
    struct s_token *next;
} t_token;
```

### Syntax validation (`check_syntax`)

After the list is built it is validated:

```
Rule                                        Invalid example
──────────────────────────────────────      ─────────────────
Empty list                                  (empty line)
First token == PIPE                         | ls
PIPE followed by another PIPE               ls || grep
Redirection not followed by a WORD          ls >
Redirection followed by an operator         ls > | grep
Last token is a redirection operator        ls >
```

---
## Step 4 — Variable expansion

**Files:** `srcs/parse/expand/expand.c` + `srcs/parse/expand/expand_utils.c` + `srcs/parse/expand/expand_helpers.c`

Only `WORD` tokens are expanded. Operators (`PIPE`, `REDIR_*`) are skipped.

```
t_token list:
  WORD "echo"        → no $ or quotes → unchanged
  WORD "$HOME/docs"  → expansion → "/home/ajenren/docs"
  PIPE "|"           → skipped
  WORD "'$VAR'"      → single quote → expansion suppressed → "$VAR" literal
  WORD '"$USER"'     → double quote → expansion active → "ajeanren"
```

### Logic of `expand_and_strip` (single pass)

```
For each character in the string:

  ' (outside double quotes) ?  →  toggle quote='\''  →  continue (char consumed)
  " (outside single quotes) ?  →  toggle quote='"'   →  continue (char consumed)
  $ followed by a non-space, and not inside single quotes?
      → handle_dollar()
          s[i+1] == '?' → ft_itoa(last_exit)      ← $?
          otherwise     → extract_var_name()
                          get_var_value(env)   ← $VAR
  otherwise             → copy the character as-is

  append_piece() concatenates each piece into result
```

### Example

```
Input   : "Hello $USER, exit=$?"   (last_exit=42, USER=ajr)
           ↓
$USER   → "ajr"
$?      → "42"
           ↓
Output  : "Hello ajr, exit=42"
```

---

## Step 5 — Parsing & AST construction

**Files:** `srcs/parse/parsing.c` + `srcs/parse/parser_exec.c` + `srcs/parse/struct_cmd.c`

### AST nodes

In the AST all nodes share a `type` field at the start of the struct:

```
t_cmd (base)
  │
  ├── t_execcmd   type == EXEC
  │     argv[0..N]  →  ["ls", "-la", NULL]
  │
  ├── t_redircmd  type == REDIR_IN / REDIR_OUT / REDIR_APPEND / HEREDOC
  │     file       →  "out.txt"
  │     mode       →  O_WRONLY | O_CREAT | O_TRUNC
  │     fd         →  STDOUT_FILENO
  │     cmd        →  → t_cmd (command to redirect)
  │
  └── t_pipecmd   type == PIPE
        left       →  → t_cmd
        right      →  → t_cmd
```

### `parse_pipe()` — right recursion

```
parse_pipe(current):
  left = parse_exec_node(current)    ← reads up to the next PIPE
  if current token == PIPE:
      advance current
      right = parse_pipe(current)    ← RECURSION → reads the rest
      return pipecmd(left, right)
  else:
      return left
```

The recursion associates to the **right**:
`a | b | c` becomes `PIPE(a, PIPE(b, c))` and not `PIPE(PIPE(a, b), c)`.

### `parse_exec_node()` — building an EXEC node

```
For each token (until PIPE or end of list):
  non-empty WORD   →  argv[i++] = ft_strdup(value)
  empty WORD       →  skipped (result of empty $VAR expansion)
  REDIR_*          →  parse_redir() wraps the current node
argv[i] = NULL
```

### Exemple

**Cmd :**`ls -la | grep foo > out.txt`
```
PIPE
├── left  : EXEC { argv=["ls", "-la", NULL] }
└── right : REDIR_OUT { file="out.txt", fd=1
              └── cmd → EXEC { argv=["grep", "foo", NULL] }
            }
```

---
## Step 6 — Execution

**Files:** `srcs/exec/ast_exec.c` + `srcs/exec/cmd_dispatch.c` + `srcs/exec/io.c` + `srcs/exec/path.c` + `srcs/exec/exec_simple.c` + `srcs/exec/child_process.c` + `srcs/parse/redir/heredoc.c`

### `run_ast()` — entry point

```
run_ast(ast):
  if ast->type == EXEC AND is_builtin(argv):
      exec_builtin()        ← run DIRECTLY in the parent process
                               (required for cd, export, exit...)
  else:
      fork()
      child  : signal(SIGINT/SIGQUIT, SIG_DFL)  ← restore default handlers
               run_cmd(ast)                     ← point of no return
      parent : setup_signal(2)                  ← ignore Ctrl+C while waiting
               wait_and_status(pid)
```
### `run_cmd()` — recursive dispatcher

```
run_cmd(cmd):
  EXEC    →  run_exec()      resolve path, call execve
  PIPE    →  exec_pipe()     create a pipe + 2 forks
  HEREDOC →  exec_heredoc()  fork a child that reads stdin until delimiter
  REDIR_* →  exec_redir()    open file, dup2, run_cmd(inner cmd)
```

### Pipe execution (`io.c`)

```
exec_pipe(pcmd):
    pipe(fd)          ← fd[0]=read end, fd[1]=write end

    fork() → left child:
        dup2(fd[1], STDOUT)   ← stdout → write into pipe
        close(fd[0], fd[1])
        run_cmd(pcmd->left)   ← point of no return

    fork() → right child:
        dup2(fd[0], STDIN)    ← stdin ← read from pipe
        close(fd[0], fd[1])
        run_cmd(pcmd->right)  ← point of no return (recursive if PIPE)

    parent:
        close(fd[0], fd[1])
        waitpid(left)
        waitpid(right)  → exit with right child's exit code
```

### PATH resolution (`path.c`)

```
get_cmd_path("grep"):
  cmd contains '/' ?  →  ft_strdup(cmd)       ← absolute/relative path
  otherwise:
      get_path()      →  "/usr/bin:/bin:..."   ← already strips "PATH=" prefix
      ft_split(path, ':')  →  ["/usr/bin", "/bin", ...]
      for each dir:
          full = dir + "/" + cmd
          access(full, X_OK) == 0 ?  →  return full
      return NULL  →  "command not found" + exit(127)
```

### Heredoc execution (`srcs/parse/redir/heredoc.c`)

```
exec_heredoc(rcmd):
    pipe(fd)
    fork() → child: heredoc_child_simple(fd[1], delim)
        signal(SIGINT, SIG_DFL)  ← default signal handler
        read stdin line by line with readline("> ")
        write each line into fd[1]
        if line == delimiter → free(line), close(fd), exit(0)
        if Ctrl+C/EOF → close(fd), exit(130)

    parent:
        close(fd[1])                           ← parent doesn't write
        waitpid(child, &status, 0)            ← wait for child completion
        setup_signal(0)                        ← restore signal handlers
        if child exited 130 → exit(130)       ← propagate Ctrl+C
        dup2(fd[0], STDIN_FILENO)            ← redirect stdin to pipe
        close(fd[0])
        run_cmd(rcmd->cmd)                    ← execute with heredoc as stdin
```

---

## Signal handling

**File:** `srcs/signals/signal.c`

```
setup_signal(mode):

  mode 0 — interactive parent (in readline)
      SIGINT  → parent_sa()   ← Ctrl+C: new line + redraw prompt
      SIGQUIT → SIG_IGN       ← Ctrl+\ ignored

  mode 1 — ignore all (used inside heredoc wait)
      SIGINT  → SIG_IGN
      SIGQUIT → SIG_IGN

  mode 2 — after fork, waiting for child
      SIGINT  → child_sa()    ← Ctrl+C: simple newline (no readline)
      SIGQUIT → SIG_IGN

  mode 3 — heredoc child reading stdin
      SIGINT  → heredoc_sa()  ← sets g_signal=1, closes stdin, new line
      SIGQUIT → SIG_IGN
```

```
Ctrl+C in interactive mode (mode 0):
  parent_sa()
    write("\n")
    rl_replace_line("", 0)   ← clear the current input line
    rl_on_new_line()
    rl_redisplay()           ← redraw the prompt

Ctrl+C when parent waits for child (mode 2):
  child_sa()
    write("\n")              ← simple newline, child handles the exit
```

---

## Builtins

**Files:** `srcs/exec/builtin.c` + `srcs/exec/builtin_*.c`

Builtins run **in the parent process** (no fork) because they need to modify the shell's own state (`cd` changes the current directory, `export` modifies the environment, `exit` terminates the process).

```
is_builtin(argv)  →  checks if argv[0] ∈ {echo, cd, pwd, export, unset, env, exit}

exec_builtin(ecmd):
  "echo"   →  builtin_echo()    handles -n / -nn / -nnn
  "cd"     →  builtin_cd()       HOME / OLDPWD / path
  "pwd"    →  builtin_pwd()      reads $PWD (preserves symlinks)
  "env"    →  builtin_env()      prints environ[]
  "export" →  builtin_export()   no arg: declare -x ; with arg: setenv()
  "unset"  →  builtin_unset()    unsetenv()
  "exit"   →  exec_exit()        validates code, exit(code % 256)
```

### `cd` detail

```
cd (no arg)   →  target = $HOME
cd -          →  target = $OLDPWD
cd <path>     →  target = argv[1]

chdir(target):
  success:
      setenv("OLDPWD", previous $PWD)
      setenv("PWD", getcwd())
  failure:
      ENOTDIR → "Not a directory"
      other   → "No such file or directory"
```

### `export` detail

```
export (no arg):
    copy environ[] → bubble sort → print "declare -x NAME=\"value\""

export NAME=value:
    is_valid_identifier(NAME)  ← first char alpha/_, rest alphanum/_
    setenv(NAME, value, 1)
```

---

## Memory management

**Files:** `srcs/memory/free.c` + `srcs/memory/cleanup.c`

### Freeing the AST (`free_cmd`)

```
free_cmd(cmd):
  NULL          →  return
  type == EXEC  →  free_exec()
                     free each argv[i]
                     free argv[]
                     free cmd
  type == PIPE  →  free_pipe()
                     free_cmd(left)   ← recursive
                     free_cmd(right)  ← recursive
                     free cmd
  else (REDIR)  →  free_redir()
                     free_cmd(inner cmd)  ← recursive
                     free file
                     free cmd
```

### Freeing tokens (`free_token_list`)

```
while current:
    next = current->next
    free(current->value)
    free(current)
    current = next
```

### readline cleanup (`readline_cleanup`)

Called once on shell exit:
```
clear_history()       ← clears command history
rl_clear_history()    ← frees readline's internal memory
rl_free_line_state()  ← frees the current line state
```

---

# Instruction

Clone repository
```bash
git clone <url.git> minishell
cd minishell
```

Compile and use minishell
```bash
Make
./minishell
$> ls -la
```

## Hidden cmd

Special cmd for URSshell
```bash
./minishell
$> comrade
```

Special cmd for Chants
```bash
./minishell
$> hymne
```

Special cmd for stopping Chants
```bash
./minishell
$> hymne_stop
```

# Ressources

Ressources use for minshell project

## Web ressources

- (Minishell: Building a mini-bash (a 42 project))[https://medium.com/@zouhairlrs/minishell-building-a-mini-bash-a-42-project-5dc20d671fbb]
- (minishell by GibbonTech Yassine Khomsi)[https://www.gibbontech.com/ecole42/minishell/index.html]
- (mysh)[https://github.com/Swoorup/mysh]
- (Bash man)[https://www.man7.org/linux/man-pages//man1/bash.1.html]
- (environnement variables)[https://www.geeksforgeeks.org/linux-unix/environment-variables-in-linux-unix/]
- (Programming with GNU Readline)[https://web.mit.edu/gnu/doc/html/rlman_2.html]
- (Abstract syntax tree)[https://en.wikipedia.org/wiki/Abstract_syntax_tree]
- (minishell_ast)[https://github.com/pmouhali/minishell_ast]

## Videos
- (Recursive Descent Parsing)[https://www.youtube.com/watch?v=SToUyjAsaFk&list=PL2POs8ZJ4I2JJK3lICRW0b-L2y9mLiDmU&index=4]
- (shell explain)[https://www.youtube.com/watch?v=ubt-UjcQUYg&list=PL2POs8ZJ4I2JJK3lICRW0b-L2y9mLiDmU&index=2]
- (What Is An Abstract Syntax Tree, With WealthFront Engineer Spencer Miskoviak)[https://www.youtube.com/watch?v=wINY109MG10]
- (Parsing Explained - Computerphile)[https://www.youtube.com/watch?v=bxpc9Pp5pZM]

## Art and other
- (ascii art)[https://www.asciiart.eu/text-to-ascii-art#google_vignette]
- (Makefile cheat sheet)[https://gist.github.com/evertrol/4b6fd05f3b6be2b331c60638b1af7101]

# AI Tools

Due to the lack of understanding regarding some parts of the shell functions, Claude and Copilote were a good help in the comprehension of the AST, readline library, signals, some build-in and debugging.

# Special thanks
Thanks to our colleagues for their advices and inputs to crash our minishell and makes it better. Thanks to Garance, Théo, Max, Thijs, Cédric and the others.