# tish - the tiny shell

As the name implies, <span style="color:purple">**tish**</span> is a tiny command line shell built for POSIX-compliant systems, that has a similar functionality
to [GNU Bash](https://www.gnu.org/software/bash/), but currently lacking a lot
of features like an actual syntax for running more complex commands or scripts.

#### **Important disclaimer!**
I built this for a project at my university and I do not know if I will *really* keep developing this, so don't really take this seriously :) . Still,
please leave some feedback on this as it would help me a lot.

#### **Note!**
If you want to try this out you need to have [GNU Readline](https://tiswww.case.edu/php/chet/readline/rltop.html) and [Starship](https://starship.rs/)
installed. I initially wanted to do this as low-level as possible, but I gave
up and chose to use **readline** as even <code>bash</code> uses it, and Starship's prompt is just too convenient, pretty and fast.

## Installation
Install the shell with:
```
git clone https://github.com/RCX777/tish
chmod +x ./install.sh
./install.sh
```

Unninstall with:
```
chmod +x ./unninstall.sh
./unninstall.sh
```
#### **Note!**
There are **no guarantees** for this to compile and **run properly** on your machine. It also *shouldn't* do any damage but still, use this shell at your own risk. 😘

## Running tish
Once installed, run <code>tish</code> from your current shell to try tish out!

### Dependencies
- **readline** and <code>starship</code> (for the prompt)
- some common *nix system utilities (currently <code>mktemp</code>), in addition to the basic POSIX utilities (<code>cat</code>, <code>cut</code>, <code>dirname</code>, <code>ls</code>, <code>mkdir</code>, <code>mkfifo</code>, <code>rm</code>, <code>sort</code>, <code>tee</code>, <code>tr</code>, <code>uname</code> and <code>sed</code> at least, but the full **coreutils** plus <code>find</code> and <code>awk</code> is preferred)
## Current features
- A runtime command history (empty commands don't get stored)
- Some built-in commands (currently <code>cd</code>, <code>exit</code>, <code>clear</code>)
- Support for piping commands (pipe symbol is <code>|</code>)
- Running commands as arguments if the <code>-c</code> flag is specified
- Autocompletion of arguments to files in the current directory
## Documentation
For running a command using this, use the following: <code>tish -c command</code>
### Built-in command list
- <code>cd</code> -> Works as you expect, '~' works even without any alias support.
- <code>clear</code> -> Clears the screen. If you want to preserve the scrollback buffer,
use the <code>-x</code> flag.
- <code>exit</code> -> Pretty obvious. (Note: you cannot specify exit flags) 
- <code>help</code> -> TODO

