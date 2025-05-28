# FILE-MANAGEMENT-TOOL

*COMPANY*: CODTECH IT SOLUTIONS

*NAME*: VAIBHAV SINGH

*INTERN ID*: CT06DK432

*DOMAIN*: C++ Programming

*DURATION*: 6 WEEKS

*MENTOR*: NEELA SANTOSH



## Description

This lightweight Win32 C++ application provides a graphical interface for selecting, reading, writing, and appending to text files on Windows.
Written using the native Win32 API in Visual Studio Code and compiled with MinGW, it demonstrates fundamental file-handling techniques alongside standard GUI programming patterns.
Tested on Windows 11 and expected to work on earlier versions (Windows 7/8/10).

This is **not just a basic utility**, but also a **learning tool** — helping beginners and intermediate programmers understand the mechanics of file I/O in C++ via the Windows API.

## Features

* **File Selection** via native Windows Open/Save dialogs
* **Read**, **Write**, and **Append** capabilities for `.txt` files
* Clean, fixed-size GUI (non-resizable) for simplicity
* MessageBox-based alerts and error reporting
* Minimal dependencies: no external libraries required


## Requirements

* Windows OS (7, 8, 10, or 11)
* MinGW compiler (GCC recommended)
* Visual Studio Code (or any text editor)
* Windows SDK headers (included with most toolchains)

## Build Instructions

1. Clone this repository:

   ```bash
   git clone https://github.com/yourusername/FILE-MANAGEMENT-TOOL.git
   cd FILE-MANAGEMENT-TOOL
   ```
2. Compile using MinGW:

   ```bash
   g++ -std=c++17 Filemanagement.cpp -lgdi32 -o Filemanagement.exe
   ```

## Usage

1. Run `Filemanagement.exe`.
2. Click **Select** to choose or create a `.txt` file.
3. Use **Read** to load file contents, edit in the main text box.
4. Press **Write** to overwrite or **Append** to add to the file.
5. You'll receive confirmation messages or error alerts as needed.

## Code Overview

* **Filemanagement.cpp** — Contains the full Win32 C++ implementation.
* Major Components:

  * `OpenFileDialog(bool save)`: Handles file selection.
  * `ReadFile()`, `WriteFile(bool append)`: Perform file I/O.
  * `WndProc(...)`: Processes GUI messages (buttons, creation, etc).
  * `WinMain(...)`: Entry point for the application.

## Limitations & Future Enhancements

**Known Limitations:**

* ANSI-only: UTF-8/Unicode support not included.
* Non-resizable window.
* Lacks "Save As", drag-and-drop, or file type recognition.

**Possible Enhancements:**

* Unicode/wide character support.
* Add keyboard shortcuts (Ctrl+S to Save, etc.).
* Add file encoding detection.
* Improve UI layout using resizable elements.

---

📌 *This tool is useful for anyone learning Windows API or implementing simple desktop utilities. Whether you are a student, educator, or hobbyist — the FILE MANAGEMENT TOOL helps you understand C++ file I/O in a hands-on manner.*
