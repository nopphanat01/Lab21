#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <commctrl.h>

#define ID_NUM1 1
#define ID_NUM2 2
#define ID_ADD 3
#define ID_SUBTRACT 4
#define ID_MULTIPLY 5
#define ID_DIVIDE 6

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

HWND hwndNum1, hwndNum2, hwndAdd, hwndSubtract, hwndMultiply, hwndDivide;

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);

    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = CreateSolidBrush(RGB(255, 165, 0));

    if (!RegisterClassEx(&wincl))
        return 0;

    hwnd = CreateWindowEx(
        0,                   
        szClassName,         
        _T("My Calculator"),       
        WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT,       
        CW_USEDEFAULT,       
        250,                 
        200,                 
        HWND_DESKTOP,        
        NULL,                
        hThisInstance,       
        NULL                 
    );

    ShowWindow(hwnd, nCmdShow);

    while (GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

void ShowResult(int result) {
    HWND hWndResult = CreateWindowEx(
        0, _T("STATIC"), _T("Result"),
        WS_VISIBLE | WS_POPUP | WS_CAPTION | WS_SYSMENU,
        100, 100, 300, 150,
        NULL, NULL, NULL, NULL
    );

    RECT rect = { 0, 0, 300, 150 };

    HDC hdc = GetDC(hWndResult);
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
    FillRect(hdc, &rect, hBrush);
    DeleteObject(hBrush);
    ReleaseDC(hWndResult, hdc);

    TCHAR buffer[50];
    wsprintf(buffer, _T("Result: %d"), result);

    CreateWindowEx(
        0, _T("STATIC"), buffer,
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        0, 0, 300, 150,
        hWndResult, NULL, NULL, NULL
    );

    HDC hdcText = GetDC(hWndResult);
    SetTextColor(hdcText, RGB(0, 0, 0));
    SetBkMode(hdcText, TRANSPARENT);
    TextOut(hdcText, 50, 50, buffer, _tcslen(buffer));
    ReleaseDC(hWndResult, hdcText);
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
            hwndNum1 = CreateWindowEx(0, _T("EDIT"), _T(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                20, 20, 100, 25, hwnd, (HMENU)ID_NUM1, NULL, NULL);

            hwndNum2 = CreateWindowEx(0, _T("EDIT"), _T(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                20, 60, 100, 25, hwnd, (HMENU)ID_NUM2, NULL, NULL);

            hwndAdd = CreateWindowEx(0, _T("BUTTON"), _T("+"),
                WS_CHILD | WS_VISIBLE,
                140, 20, 50, 25, hwnd, (HMENU)ID_ADD, NULL, NULL);

            hwndSubtract = CreateWindowEx(0, _T("BUTTON"), _T("-"),
                WS_CHILD | WS_VISIBLE,
                140, 60, 50, 25, hwnd, (HMENU)ID_SUBTRACT, NULL, NULL);

            hwndMultiply = CreateWindowEx(0, _T("BUTTON"), _T("*"),
                WS_CHILD | WS_VISIBLE,
                140, 100, 50, 25, hwnd, (HMENU)ID_MULTIPLY, NULL, NULL);

            hwndDivide = CreateWindowEx(0, _T("BUTTON"), _T("/"),
                WS_CHILD | WS_VISIBLE,
                140, 140, 50, 25, hwnd, (HMENU)ID_DIVIDE, NULL, NULL);
            break;

        case WM_COMMAND:
            {
                if (LOWORD(wParam) == ID_ADD || LOWORD(wParam) == ID_SUBTRACT ||
                    LOWORD(wParam) == ID_MULTIPLY || LOWORD(wParam) == ID_DIVIDE) {

                    TCHAR num1[20], num2[20];
                    GetWindowText(hwndNum1, num1, 20);
                    GetWindowText(hwndNum2, num2, 20);

                    int n1 = _ttoi(num1);
                    int n2 = _ttoi(num2);
                    int result = 0;

                    switch (LOWORD(wParam)) {
                        case ID_ADD: result = n1 + n2; break;
                        case ID_SUBTRACT: result = n1 - n2; break;
                        case ID_MULTIPLY: result = n1 * n2; break;
                        case ID_DIVIDE:
                            if (n2 != 0) {
                                result = n1 / n2;
                            } else {
                                MessageBox(NULL, _T("Cannot divide by zero!"), _T("Error"), MB_OK | MB_ICONERROR);
                                return 0;
                            }
                            break;
                    }

                    ShowResult(result);
                }
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
