# Overview
This is an outline of the the goals of this project and its composition.
This is not official documentation about it. That will be generated after and will reside in separate a separate file.

### Primary Goal
Have an easy way to globally use a local executable.

For example:
* A program you built that you want to run globally
* A project that you cloned from github and you want to use it and/or test it

## Commands
List of commands to be implemented
* install - Primary command "installs" the executable by symlinking it to /usr/local/bin
* uninstall - Removes an installed program
* list - List all programs that have been installed with attic
* update - Replace an existing program with a newer version
* purge - Delete everything
* help - Will display information on the commands available and what they do

Ideally would like to add a way to easily uninstall attic and remove all files associated with it

Would also like to add a way to have multiple versions of a program.
This would be especially useful for testing a product which is one of the main purposes of this tool.
This however is is not the priority at this time.

## Layout
attic will setup a directory located at /usr/local/attic
It will store all installed programs here to that it can easily keep track of and manage them.
It will then symlink each program to /usr/local/bin to make it globally available for use.

attic will also generate a directory at ~/.attic
This will contain all configuration. There should be options that the user can change such as:
* Install location - while attic will always symlink to /usr/local/bin the location where attic stores its copies of everything can be changed from /usr/local/attic

More will be added as they come to mind. Again this is not a priority at this point but more of a nice to have once the basic functionality is present.

## Installation
Will have a basic install script that will compile attic and setup the aforementioned directories.
As previously mentioned will also have a way of uninstalling and deleting all the generated directories and files. Programs that are a pain to properly uninstall suck! Will probably add the option to only delete all files if desired.