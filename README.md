This is my version of the **[42](https://www.42.us.org/)** cadet project `21sh`. `21sh` is a group project, and I (**mtaylor**) did this project with **[callen](https://github.com/MrChafeits)**. Credit to him where it is due.

# 21sh
The second version of **[minishell](https://github.com/motaylormo/minishell)**, with more features.

# Features
### Minishell
<details><summary></summary>

* You must manage the errors without using `errno`, by displaying a message adapted to the error output
* The executable are those you can find in the paths indicated in the `PATH` variable
* Deal correctly with the `PATH` and the environment
* Implement a series of builtins:
	* `echo`
	* `cd`
	* `setenv`
	* `unsetenv`
	* `env`
	* `exit`
* Implement expansion of variable references `$` and the tilde `~`
</details>

### 21sh
<details><summary></summary>

* The `C-d` (EOF) and `C-c` (`SIGINT`) keys combination features for line edition and process execution
* The `;` command line separator
* Pipes `|`
* The 4 following redirections which follow the general format of `[n]redir-op word`:

| ? | ? | ? | ?
| - | - | - | -
| Redirecting Input  | `[n]<word` | open file _word_ for reading on the specified file descriptor | 2.7.1
| Redirecting Output | `[n]>word` | create and/or open file _word_ for writing on the specified file descriptor | 2.7.2
| Appending Redirected Output | `[n]>>word` | create and/or open file _word_ for appending on the specified file descriptor | 2.7.3
| Here-Document | `[n]<<word` | redirects subsequent lines read by the shell to the input of a command | 2.7.4

* File descriptor Duplication

| ? | ? | ? | ?
| - | - | - | -
| Duplicating Input File Descriptor | `[n]<&word` | duplicate one input file descriptor from another, or close one | 2.7.5
| Duplicating Output File Descriptor | `[n]>&word` | duplicate one output file descriptor from another, or close one | 2.7.6
| Open File Descriptors for Reading and Writing | `[n]<>word` | open file that is the expansion of _word_ for reading and writing on _n_ or stdin if _n_ is unspecified | 2.7.7

A line editing feature using the `termcaps` library. Implement at least the following features:
* Edit the line where the cursor is located:

| ? | ? | ?
| - | - | -
| `delete` | `C-d` | forward delete character
| `backspace` | | backward delete character

* Move the cursor and be able to edit the line at a specific location:

| ? | ? | ?
| - | - | -
| `left` | | move cursor 1 character left
| `right` | | move cursor 1 character right
| `C-left` | `M-b` | move cursor 1 word left
| `C-right` | `M-f` | move cursor 1 word right
| `home` | `C-a` | move cursor to beginning of line
| `end` | `C-e` | move cursor to end of line

* Use `up` and `down` arrows to navigate through the command history which we will then be able to edit (the line, not the history)
* Cut, copy, and/or paste all or part of a line using the key sequence you prefer:

| ? | ?
| - | -
| `C-k` | cut current line from cursor position to the end of the line
| `C-w` | cut the immediately preceeding word, including any trailing whitespace.
| `C-y` | paste the current temp-buffer contents to cursor position

* Write AND edit a command over a few lines. In that case, we would love that `C-up`(`C-p`) and `C-down`(`C-n`) allow to go from one line to another in the command while remaining in the same column or otherwise the most appropriate column.
* Completely manage quotes and double quotes, even on several lines (expansions excluded).
	* `'` Single quotes suppress normal expansions and preserve whitespace in the enclosed string
	* `"` Double quotes preserve whitespace and allow for variable expansion but not tilde expansion

[important reference](http://pubs.opengroup.org/onlinepubs/9699919799/)

</details>
