# CGrep

This is a simple command-line utility written in C that searches for a specified pattern within the files of a directory. It works similarly to `grep` but is implemented from scratch using basic file handling and string manipulation in C.

## Features
- **Recursive Search**: Searches for the given pattern in all files within a directory, including subdirectories.
- **Case Sensitivity Option**: Supports case-sensitive and case-insensitive searches.
- **Line-by-Line Search**: Displays the line number and content where the pattern is found.

## Requirements
- A C compiler (e.g., GCC)
- Standard C library

## Usage

### Compile the Program
To compile the program, use the following command:
```bash
gcc -o text_search grep.c
```

### Run the Program
The program takes three arguments:
1. `pattern` - The text string to search for.
2. `directory` - The directory to search within.
3. `--ignore-case` (optional) - If provided, the search will be case-insensitive.

#### Example 1: Case-sensitive search
To search for the pattern "example" in the `/home/user/documents` directory:
```bash
./text_search example /home/user/documents
```

#### Example 2: Case-insensitive search
To search for the pattern "example" in the `/home/user/documents` directory, ignoring case:
```bash
./text_search example /home/user/documents --ignore-case
```

## How It Works
1. **`to_lower` Function**: Converts a string to lowercase to support case-insensitive searching.
2. **`search_in_file` Function**: Opens each file, reads it line by line, and checks if the pattern exists within the line. It prints the line number and content if a match is found.
3. **`search_in_directory` Function**: Recursively searches through directories and calls `search_in_file` for each file encountered.
4. **Command-Line Arguments**: The program accepts a `pattern`, a `directory` to search, and optionally an `--ignore-case` flag to make the search case-insensitive.

## Example Output
For a case-sensitive search for the pattern "example" in a directory:
```
Found in /home/user/documents/file1.txt: Line 12: This is an example line.
Found in /home/user/documents/file2.txt: Line 5: Another example here.
```

For a case-insensitive search:
```
Found in /home/user/documents/file1.txt: Line 12: This is an Example line.
Found in /home/user/documents/file2.txt: Line 5: Another example here.
```

## Notes
- The program skips the special `.` and `..` directories during recursive searches.
- Files that cannot be opened will be skipped, and an error message will be displayed.
- The program only supports regular files and directories; symbolic links and other file types are ignored.

## License
This program is open source and can be freely used, modified, and distributed.
```

### Explanation of Key Sections:

- **Requirements**: This section mentions the necessary tools and environment to compile and run the program.
- **Usage**: Provides clear instructions on how to compile and run the program, including examples for both case-sensitive and case-insensitive searches.
- **How It Works**: Describes the core logic of the program and the purpose of each function.
- **Example Output**: Shows what the user can expect when the program runs successfully.
- **Notes**: Additional details about the program's behavior, such as skipping directories and handling errors.
