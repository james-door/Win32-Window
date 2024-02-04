#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <sstream>
#include <tchar.h>


#define HANDLE_RETURN(err) LogIfFailed(err, __FILE__, __LINE__)

std::stringstream Win32ErrorLog;

inline void LogIfFailed(bool err, const char* file, int line)
{
    if (err)
    {
        DWORD error = GetLastError();
        LPVOID lpMsgBuf;
        FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            error,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPSTR)&lpMsgBuf,
            0, NULL);


        std::string message = "File: " + std::string(file) + "\n\nMessage: " + std::string((char*)lpMsgBuf) + "\n\nLine: " + std::to_string(line);
        LocalFree(lpMsgBuf);

        Win32ErrorLog << message;
    }
}
void displayErrorMessage(std::string error) {

    MessageBoxA(NULL, error.c_str(), NULL, MB_OK);

}

//Message Procedure
LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    //Register a window class
    WNDCLASSEX winClass = {};
    winClass.cbSize = sizeof(WNDCLASSEX);
    winClass.style = CS_HREDRAW | CS_VREDRAW;
    winClass.lpfnWndProc = WndProc;
    winClass.cbClsExtra = 0;
    winClass.cbWndExtra = 0;
    winClass.hInstance = hInstance;
    winClass.hIcon = NULL;
    winClass.hCursor = LoadCursor(hInstance, NULL);
    winClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    winClass.lpszMenuName = NULL;
    winClass.lpszClassName = _T("window");
    winClass.hIconSm = LoadIcon(hInstance, NULL);

    HANDLE_RETURN(RegisterClassEx(&winClass) == 0);


    //Fill windowArea RECT with Client area
    constexpr LONG defaultWindowWidth = 990;
    constexpr LONG defaultWindowHeight = 540;
    RECT windowArea = {};
    windowArea.left = 0;
    windowArea.top = 0;
    windowArea.right = defaultWindowWidth;
    windowArea.bottom = defaultWindowHeight;

    //Find window area from the client 
    HANDLE_RETURN(AdjustWindowRect(&windowArea, WS_OVERLAPPEDWINDOW, TRUE) == 0);
    int windowAreaWidth = static_cast<int>(windowArea.right - windowArea.left);
    int windowAreaHeight = static_cast<int>(windowArea.bottom - windowArea.top);
    //Find centre of screen coordinates
    int displayWidth = GetSystemMetrics(SM_CXSCREEN);
    int displayHeight = GetSystemMetrics(SM_CYSCREEN);
    int centreX = (displayWidth - windowAreaWidth) / 2;
    int centreY = (displayHeight - windowAreaHeight) / 2;

    //Create the window
    HWND windowHandle = CreateWindowEx(NULL, _T("window"), _T("My Window"), WS_OVERLAPPEDWINDOW, centreX, centreY,
        windowAreaWidth, windowAreaHeight, NULL, NULL, hInstance, nullptr);
    HANDLE_RETURN(windowHandle == NULL);

    
    ShowWindow(windowHandle, SW_SHOW);
    //Message Loop
    MSG windowMsg= {};
    while (windowMsg.message != WM_QUIT) {
        GetMessage(&windowMsg, NULL, 0, 0);
        DispatchMessage(&windowMsg);
    }








    if (!Win32ErrorLog.str().empty()) {
        displayErrorMessage("Win32 Errors:\n\n" + Win32ErrorLog.str());
    }

	return 0;
}
