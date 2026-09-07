# C Line Editor

Portfolio Building — Studio Course 3rd Semester Coding Competition.

## Team Members
- Arun H Kalamuddi
- Anubhav Tiwari


## Data Structure Choice & Justification
- **Data Structure:** Singly Linked List of dynamic strings (`LineNode`).
- **Justification:** Avoids the $O(N)$ memory-shifting cost of contiguous arrays when inserting or deleting lines in the middle of a document. Dynamically allocates memory on demand, removing arbitrary line limits.

## Implemented Features
### Core Features
- **Insert a line (`i <n>`):** Inserts arbitrary line text at a 1-based index, dynamically shifting node links.
- **Delete a line (`d <n>`):** Deallocates and removes a line by index, reconnecting surrounding nodes.
- **Display document (`p`):** Formats and prints all stored lines alongside line numbers.
- **Save / Load (`s <file>` / `l <file>`):** Serializes memory contents to a `.txt` file and reads external documents back into the list.

### Bonus Features
- **Search (`/ <query>`):** Performs substring matching across every line node and outputs matched line numbers.
- **Document Statistics (`w`):** Dynamically computes and reports total lines and word counts.

## How to Compile & Run

### Linux / macOS / WSL:
```bash
gcc -Wall -Wextra -std=c99 main.c -o line_editor
./line_editor