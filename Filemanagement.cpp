#include <windows.h>
#include <commdlg.h>
#include <fstream>
#include <string>

#define ID_PATH_EDIT 100
#define ID_SELECT    105
#define ID_EDIT      101
#define ID_READ      102
#define ID_WRITE     103
#define ID_APPEND    104

HWND hPathEdit, hEdit;
std::string currentPath;

void ShowError(const char* msg) {
    MessageBoxA(NULL, msg, "Error", MB_ICONERROR);
}

std::string OpenFileDialog(bool save) {
    char filename[MAX_PATH] = {0};
    OPENFILENAMEA ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "Text Files\0*.txt\0All Files\0*.*\0\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
    if (save) {
        ofn.Flags &= ~OFN_FILEMUSTEXIST;
        ofn.Flags |= OFN_OVERWRITEPROMPT;
        if (!GetSaveFileNameA(&ofn)) return "";
    } else {
        if (!GetOpenFileNameA(&ofn)) return "";
    }
    return std::string(filename);
}

void SelectFile() {
    std::string path = OpenFileDialog(false);
    if (path.empty()) return;
    currentPath = path;
    SetWindowTextA(hPathEdit, currentPath.c_str());
}

void ReadFile() {
    if (currentPath.empty()) {
        currentPath = OpenFileDialog(false);
        if (currentPath.empty()) return;
        SetWindowTextA(hPathEdit, currentPath.c_str());
    }
    std::ifstream ifs(currentPath);
    if (!ifs) { ShowError("Cannot open file for reading."); return; }
    std::string content((std::istreambuf_iterator<char>(ifs)), {});
    SetWindowTextA(hEdit, content.c_str());
}

void WriteFile(bool append) {
    if (currentPath.empty() && !append) {
        currentPath = OpenFileDialog(true);
        if (currentPath.empty()) return;
        SetWindowTextA(hPathEdit, currentPath.c_str());
    }
    if (currentPath.empty()) {
        ShowError("No file selected.");
        return;
    }
    std::ofstream ofs;
    ofs.open(currentPath, append ? std::ios::app : std::ios::trunc);
    if (!ofs) { ShowError("Cannot open file for writing."); return; }
    int len = GetWindowTextLengthA(hEdit);
    std::string text;
    text.resize(len);
    GetWindowTextA(hEdit, &text[0], len + 1);
    ofs << text;
    MessageBoxA(NULL,
        append ? "Appended successfully." : "Saved successfully.",
        "Info", MB_OK);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowA("STATIC", "File:", WS_CHILD | WS_VISIBLE, 10, 10, 30, 20, hWnd, NULL, NULL, NULL);
        hPathEdit = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            50, 10, 380, 20, hWnd, (HMENU)ID_PATH_EDIT, NULL, NULL);
        CreateWindowA("BUTTON", "Select", WS_CHILD | WS_VISIBLE, 440, 10, 50, 20, hWnd, (HMENU)ID_SELECT, NULL, NULL);
        hEdit = CreateWindowExA(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL,
            10, 40, 480, 300, hWnd, (HMENU)ID_EDIT, NULL, NULL);
        CreateWindowA("BUTTON", "Read", WS_CHILD | WS_VISIBLE, 10, 350, 80, 30, hWnd, (HMENU)ID_READ, NULL, NULL);
        CreateWindowA("BUTTON", "Write", WS_CHILD | WS_VISIBLE, 100, 350, 80, 30, hWnd, (HMENU)ID_WRITE, NULL, NULL);
        CreateWindowA("BUTTON", "Append", WS_CHILD | WS_VISIBLE, 190, 350, 80, 30, hWnd, (HMENU)ID_APPEND, NULL, NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wp)) {
        case ID_SELECT: SelectFile(); break;
        case ID_READ:   ReadFile();   break;
        case ID_WRITE:  WriteFile(false); break;
        case ID_APPEND: WriteFile(true);  break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcA(hWnd, msg, wp, lp);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {
    WNDCLASSA wc = {};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInst;
    wc.lpszClassName = "FileIOClass";
    RegisterClassA(&wc);

    HWND hWnd = CreateWindowA(wc.lpszClassName, "Win32 File Manager",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT, 520, 430,
        NULL, NULL, hInst, NULL);

    ShowWindow(hWnd, nCmdShow);
    MSG msg;
    while (GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return 0;
}