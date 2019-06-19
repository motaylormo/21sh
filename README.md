This is my version of the **[42](https://www.42.us.org/)** cadet project `21sh`. `21sh` is a group project, and I (**mtaylor**) did this project with **[callen](https://github.com/MrChafeits)**. Credit to him where it is due.

# 21sh
The second version of **[minishell](https://github.com/motaylormo/minishell)**, with more features.

# Features
### Minishell
<details>

* The executable are those you can find in the paths indicated in the `PATH` variable
* You must deal correctly with the `PATH` and the environment
* You must implement a series of builtins:
	* `echo`
	* `cd`
	* `setenv`
	* `unsetenv`
	* `env`
	* `exit`
* You must manage expansions `$` and `~`
* Management of signals and in particular `ctrl-C`
* Management of execution rights in the `PATH`
</details>

<details><summary><h3>21sh</h3></summary>

* The `ctrl-D` and `ctrl-C` keys combination features for line edition and process execution
* The `;` command line separator
* Pipes `|`
* The 4 following redirections `<`, `>`, `<<`, and `>>`
* File descriptor aggregation
* A line edition feature using the `termcaps` library. You must at least manage the following features
	* Edit the line where the cursor is located
	* Move the cursor left and right to be able to edit the line at a specific location. Obviously new characters have to be inserted between the existing ones similarly to a classic shell.
	* Use up and down arrows to navigate through the command history which we will then be able to edit if we feel like it (the line, not the history)
	* Cut, copy, and/or paste all or part of a line using the key sequence you prefer.
	* Move directly by word towards the left or the right using `ctrl-LEFT` and `ctrl-RIGHT` or any other reasonable combination of keys.
	* Go directly to the beginning or the end of a line by pressing home and end.
	* Write AND edit a command over a few lines. In that case, we would love that `ctrl-UP` and `ctrl-DOWN` allow to go from one line to another in the command while remaining in the same column or otherwise the most appropriate column.
	* Completely manage quotes and double quotes, even on several lines (expansions excluded).

</details>
