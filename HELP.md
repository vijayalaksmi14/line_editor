# C Line Editor - Usage Guide

## Commands & Usage

### 1. Insert Line (`I`)
Inserts text at a specific 1-based line number.
* **Syntax:** `I <line_number> <text>`
* **Example:** `I 1 Hello World`

### 2. Delete Line (`D`)
Deletes the line at the specified line number.
* **Syntax:** `D <line_number>`
* **Example:** `D 1`

### 3. Display Document (`P`)
Prints all lines currently stored in memory along with line numbers.
* **Syntax:** `P`

### 4. Save File (`S`)
Saves the document content to a text file.
* **Syntax:** `S <filename>`
* **Example:** `S document.txt`

### 5. Quit (`Q`)
Exits the editor safely.
* **Syntax:** `Q`