# Line Editor Documentation & Help Manual

Welcome to the **C Line Editor** manual. This application is a minimal, terminal-driven text editor that operates on individual lines using a dynamic linked-list data structure in memory.

---

## Command Reference Summary

| Command | Arguments | Description |
| :--- | :--- | :--- |
| `p` | *None* | Display the entire document with line numbers |
| `i` | `<line_number>` | Insert a new line at the target 1-based index |
| `d` | `<line_number>` | Delete a line at the target 1-based index |
| `/` | `<query>` | Search for a case-sensitive substring across all lines |
| `s` | `<filename>` | Save the document to a text file on disk |
| `l` | `<filename>` | Load lines from a text file on disk into memory |
| `w` | *None* | Display document statistics (line count & word count) |
| `h` | *None* | Print the short in-program help menu |
| `q` | *None* | Free all allocated memory and quit the application |

---

## Detailed Command Instructions & Examples

### 1. Display Document (`p`)
Prints all lines currently stored in memory. Each line is prefixed with its 1-based index formatted neatly as `line_num | text`.

* **Syntax:** `p`
* **Edge Case:** If no lines exist, it prints `[Document is empty]`.
* **Example:**
  ```text
  ed> p
     1 | Welcome to the Line Editor
     2 | Built using a Linked List in C