English | [العربية](README.ar.md)

# Bank System — C++ Console App 🏦

A console client-records manager with full CRUD (Create, Read, Update, Delete) built in C++, where every record is saved to and loaded from a text file.

> Project 1 of **Algorithms & Problem Solving Level 3** (Course 7 of Dr. Mohammed Abu-Hadhoud's programming roadmap).

## Features

- Add a new client (account number, PIN code, name, phone, balance) — blocks duplicate account numbers
- Show every client in a clean, aligned table
- Find a single client by account number
- Update an existing client's info, with a confirmation prompt before saving
- Delete a client, with a confirmation prompt before removing
- All data persists in `ClientRecord.txt` — nothing is lost between runs
- The menu keeps returning to itself after every action, until you choose Exit

## Sample Menu

```
____________________________________________________
____________________________________________________
		Main Menue Screen 
____________________________________________________
____________________________________________________
	[1] Show Client List.
	[2] Add New Client.
	[3] Delete Client.
	[4] Update Client Info.
	[5] Find Client.
	[6] Exit.
____________________________________________________
____________________________________________________
```

## How to Run

```bash
g++ main.cpp -o bank_system
./bank_system
```

> This program uses a Linux-specific system call (`system("clear")`) to clear the screen, so it runs best on Linux/macOS terminals.

## Concepts Practiced

- File I/O (`fstream`) for full CRUD persistence
- `vector` to hold all loaded records in memory
- A custom line format — fields joined with a `#//#` separator, then split back apart to read them
- Delete and Update both work by rewriting the whole file: a text file has no way to erase or resize a single line, so the safe move is writing every kept/updated record into a fresh copy
- `struct` to group a client's fields, `enum` for the menu options
- Pass-by-reference (`&`) to update the in-memory list without copying it
- Recursion — the program returns to the main menu by calling itself again, not a loop

## Author

**Ahmad Slik** — 17 y/o self-taught AI builder, currently following Dr. Mohammed Abu-Hadhoud's programming roadmap.

- Portfolio: [ahmadslik.netlify.app](https://ahmadslik.netlify.app)
- GitHub: [@AhmadSlik](https://github.com/AhmadSlik)
