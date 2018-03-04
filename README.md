# attic

attic is a small program that allows you to use a local program globally.

### How it works
When attic is setup it creates an install directory at /usr/local/attic. When you install a program attic copies the file to this directory, then creates a symlink to /usr/local/bin. This way the program is globally available and attic can keep track of what has been installed.

This is useful for using locally built programs as attic takes care of moving the file and performing necessary actions.

### Commands
* attic install [FILE]  -- Makes the program globally available.
* attic uninstall [NAME]    -- Removes the previously installed program.
* attic link [NAME]     -- Symlinks a program that was previously installed to /usr/local/bin.
* attic unlink [NAME]   -- Removes the symlink from /usr/local/bin.
* attic list    -- Lists all programs that have been installed with attic.
* attic setup   -- Performs any necessary setup tasks for attic function. This should only be run once when attic is installed.

### Installation
Coming soon.

### License
attic is available under the [MIT License](https://github.com/cszatma/attic/tree/master/LICENSE).

### Contributing
Contributions are welcome. Feel free to open an issue or submit a pull request.