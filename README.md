![Master Interface Control Key for Yogurt Exploitation](https://github.com/QuantumSheep/mickey/blob/master/logo.png)

Remote Administration Tool called MICKYE which stand for Master Interface Control Key for Yogurt Exploitation.  
Don't question the name, it doesn't matter.

## Dependencies
- GTK 3
    - VTE 2.91
- Sqlite 3

## Tested operating systems
| Operating System | Status |
|------------------|--------|
| Windows          | ❌     |
| MacOS            | ❔      |
| Arch Linux       | ❔      |
| CentOS           | ❔      |
| Debian / Ubuntu  | ✔️     |
| Fedora           | ❔      |
| Gentoo           | ❔      |
| openSUSE         | ❔      |

# How to compile?
Dependencies can be installed running `install_dep.sh`.  
MICKYE has Makefiles so you can use `make` command to compile the project, client and server has their own Makefile at the root of their respective directories. Then executables will be created.
