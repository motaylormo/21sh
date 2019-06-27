This is my version of the **[42](https://www.42.us.org/)** cadet project `21sh`. `21sh` is a group project, and I (**mtaylor**) did this project with **[callen](https://github.com/MrChafeits)**. Credit to him where it is due.

# 21sh
The second version of **[minishell](https://github.com/motaylormo/minishell)**, with more features.

# Features
### Minishell
<details><summary></summary>

* The executable are those you can find in the paths indicated in the `PATH` variable
* You must deal correctly with the `PATH` and the environment
* You must implement a series of builtins:
	* `echo`
	* `cd`
	* `setenv`
	* `unsetenv`
	* `env`
	* `exit`
* You must implement expansion of variable references `$` and the tilde `~`
* Management of signals and in particular `C-c` (`SIGINT`)
* Management of execution rights in the `PATH` environment variable
</details>

### 21sh
<details><summary></summary>

* The `C-d` and `C-c` keys combination features for line edition and process execution
* The `;` command line separator
* Pipes `|`
* The 4 following redirections which follow the general format of `[n]redir-op word`:
  * Redirecting Input
	* `[n]<word`  : open file 'word' for reading on the specified file descriptor (2.7.1)
  * Redirecting Output
	* `[n]>word`  : create and/or open file 'word' for writing on the specified file descriptor (2.7.2)
  * Appending Redirected Output
	* `[n]>>word` : create and/or open file 'word' for appending on the specified file descriptor (2.7.3)
  * Here-Document
	* `[n]<<word` : redirects subsequent lines read by the shell to the input of a command (2.7.4)
* File descriptor aggregation
  * Duplicating Input File Descriptor
	* `[n]<&word` : duplicate one input file descriptor from another, or close one. (2.7.5)
  * Duplicating Output File Descriptor
	* `[n]>&word` : duplicate one output file descriptor from another, or close one. (2.7.6)
  * Open File Descriptors for Reading and Writing
	* `[*n*]<>*word*` : open file that is the expansion of *word* for reading and writing on *n* or stdin if *n* is unspecified. (2.7.7)
* A line editing feature using the `termcaps` library. You must at least implement the following features
	* Edit the line where the cursor is located
	* Move the cursor left and right to be able to edit the line at a specific location. Obviously new characters have to be inserted between the existing ones similarly to a classic shell.
		* Move directly by word towards the left or the right using `C-left`(`M-b`) and `C-right`(`M-b`) or any other reasonable combination of keys.
		* Go directly to the beginning or the end of a line by pressing `home`(`C-a`) and `end`(`C-e`).
	* Use up and down arrows to navigate through the command history which we will then be able to edit if we feel like it (the line, not the history)
	* Cut, copy, and/or paste all or part of a line using the key sequence you prefer.
        * `C-k` : cut/kill current line contents from cursor position to the end of the line, into the temp-buffer.
        * `C-y` : paste/yank the current temp-buffer/kill-ring contents to cursor position.
        * `C-d` : forward delete character, similarly to how the `delete` functions.
        * `C-w` : cut/kill the immediately preceeding word into the temp-buffer, including any trailing whitespace.
	* Write AND edit a command over a few lines. In that case, we would love that `C-up`(`C-p`) and `C-down`(`C-n`) allow to go from one line to another in the command while remaining in the same column or otherwise the most appropriate column.
	* Completely manage quotes and double quotes, even on several lines (expansions excluded).
        * `'` Single quotes suppress normal expansions and preserve whitespace in the enclosed string
        * `"` Double quotes preserve whitespace and allow for variable expansion but not tilde expansion

[important reference](http://pubs.opengroup.org/onlinepubs/9699919799/)

</details>
