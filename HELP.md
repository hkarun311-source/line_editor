**`HELP.md`**
```markdown
# Line Editor Command Reference

- `insert <line> <text>`: Inserts text at the specified line number.
  - Example: `insert 1 Hello World`
- `delete <line>`: Deletes the line at the specified number.
  - Example: `delete 1`
- `display`: Prints the full document with line numbers.
- `search <phrase>`: Searches for a phrase (case-insensitive).
  - Example: `search hello`
- `replace <old> <new>`: Replaces occurrences of `old` with `new`.
  - Example: `replace World REVA`
- `save <filename>`: Saves current document to a file.
  - Example: `save doc.txt`
- `load <filename>`: Loads document from a file.
  - Example: `load doc.txt`
- `help`: Shows the command list.
- `exit`: Quits the editor.