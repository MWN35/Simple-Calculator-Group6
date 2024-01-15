#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void EvaluateExpression(HWND hwnd);
void OnButtonClick(int buttonID, HWND hwnd);
int EvaluateArithmeticExpression(const char *expression, double *result);

HWND hwndEdit;
HWND hwndButton[17];  // Increased to 17 for the new button

void AddText(char *text) {
    int len = GetWindowTextLength(hwndEdit);
    SendMessage(hwndEdit, EM_SETSEL, len, len);
    SendMessage(hwndEdit, EM_REPLACESEL, 0, (LPARAM)text);
}

void EvaluateExpression(HWND hwnd) {
    int len = GetWindowTextLength(hwndEdit);
    char *buffer = (char *)malloc(len + 1);
    GetWindowText(hwndEdit, buffer, len + 1);

    double result;
    if (EvaluateArithmeticExpression(buffer, &result)) {
        // Successfully evaluated the expression
        char resultBuffer[64];
        int resultLength = snprintf(resultBuffer, sizeof(resultBuffer), "%.2f", result);

        // Remove trailing zeros and the dot if necessary
        char *dotPosition = strchr(resultBuffer, '.');
        if (dotPosition != NULL) {
            char *end = resultBuffer + resultLength - 1;

            // Remove trailing zeros
            while (*end == '0' && end > dotPosition) {
                *end = '\0';
                end--;
            }

            // Remove the dot if there are no decimal places after it
            if (*end == '.') {
                *end = '\0';
            }
        }

        char finalBuffer[256];
        snprintf(finalBuffer, sizeof(finalBuffer), "%s = %s", buffer, resultBuffer);

        SetWindowText(hwndEdit, finalBuffer);
    } else {
        // Failed to evaluate the expression
        MessageBox(hwnd, "Invalid expression", "Error", MB_OK | MB_ICONERROR);
        SetWindowText(hwndEdit, ""); // Reset the text field on error
    }

    free(buffer);
}

int EvaluateArithmeticExpression(const char *expression, double *result) {
    // Simple arithmetic expression evaluation
    // This example supports addition, subtraction, multiplication, and division
    char operator;
    int numRead;

    numRead = sscanf(expression, "%lf%c%lf", result, &operator, result + 1);

    if (numRead == 3) {
        double tempResult;  // Use a temporary variable

        switch (operator) {
            case '+':
                tempResult = *result + result[1];
                break;
            case '-':
                tempResult = *result - result[1];
                break;
            case '*':
                tempResult = *result * result[1];
                break;
            case '/':
                if (result[1] != 0.0) {
                    tempResult = *result / result[1];
                } else {
                    // Division by zero
                    return 0;
                }
                break;
            default:
                // Invalid operator
                return 0;
        }

        // Update the result after evaluating the expression
        *result = tempResult;
        return 1;
    } else if (numRead == 1) {
        // Single operand (e.g., "x" or "123")
        return 1;
    } else {
        // Invalid expression format
        return 0;
    }
}

void OnButtonClick(int buttonID, HWND hwnd) {
    char buttonText[2] = {0};

    // Check if the current text is a result
    int len = GetWindowTextLength(hwndEdit);
    if (len > 0) {
        char *buffer = (char *)malloc(len + 1);
        GetWindowText(hwndEdit, buffer, len + 1);

        // Check if the last character is '='
        if (buffer[len - 1] == '=') {
            // Clear the text and start a new equation
            SetWindowText(hwndEdit, "");
        }

        free(buffer);
    }

    // Continue with the normal behavior
    if (buttonID < 10) {
        sprintf(buttonText, "%d", buttonID);
    } else {
        // Für Operationen, Punkt und Gleichheitszeichen
        switch (buttonID) {
            case 10:
                sprintf(buttonText, "+");
                break;
            case 11:
                sprintf(buttonText, "-");
                break;
            case 12:
                sprintf(buttonText, "*");
                break;
            case 13:
                sprintf(buttonText, "/");
                break;
            case 14:
                sprintf(buttonText, ".");
                break;
            case 15:
                // Gleichheitszeichen auswerten
                EvaluateExpression(hwnd);
                return;
            case 16:
                // Reset button
                SetWindowText(hwndEdit, "");
                return;
        }
    }

    AddText(buttonText);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND:
            if (HIWORD(wParam) == BN_CLICKED) {
                int buttonID = LOWORD(wParam);
                OnButtonClick(buttonID, hwnd);
            }
            break;

        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE) {
                // Clear the text window when the Escape key is pressed
                SetWindowText(hwndEdit, "");
            }
            break;

        case WM_CREATE:
            hwndEdit = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_MULTILINE,
                                      10, 10, 200, 30, hwnd, NULL, NULL, NULL);

            char buttonLabels[17][3] = {  // Increased to 17 for the new button
                "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", 
                "+", "-", "*", "/", ".", "=",
                "C"  // Label for the new button
            };

            for (int i = 0; i < 17; i++) {
                hwndButton[i] = CreateWindow("BUTTON", buttonLabels[i], WS_CHILD | WS_VISIBLE,
                                             10 + (i % 4) * 50, 50 + (i / 4) * 50, 50, 50, hwnd, (HMENU)i, NULL, NULL);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

int main() {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "CalculatorClass";
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, "CalculatorClass", "Simple Calculator", WS_OVERLAPPEDWINDOW,
                               100, 100, 300, 400, NULL, NULL, GetModuleHandle(NULL), NULL);

    ShowWindow(hwnd, SW_SHOWNORMAL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
