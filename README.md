To execute the calculator, please start the exe on a windows OS. (It is supposed to work independently) In case it doesn't work make sure that all nessesary the librarys are installed in the default locations or copy the Text from the Main.c in to codblocks.




When the program starts, it executes a series of operations to create and display a simple calculator window and to handle user interactions. Here's a step-by-step explanation of what happens:

1. Initialization of WNDCLASS Structure (Start of main function):**
   - The WNDCLASS structure named wc is initialized to zero. This structure is used to define properties of the window class such as its style, icon, cursor, and the window procedure (WindowProc) that will handle messages for windows of this class.

2. *Registering the Window Class:*
   - The RegisterClass function is called with &wc as an argument. This registers the window class with the system, making it possible to create windows based on this class.

3. *Creating the Main Application Window:*
   - CreateWindowEx is called to create a window of the "CalculatorClass" class. This function sets up the window with specified styles, title, dimensions, and other properties. The handle to this window is stored in hwnd.

4. *Displaying the Window:*
   - ShowWindow is called with hwnd and SW_SHOWNORMAL, making the window visible on the screen with its default size and position.

5. *Entering the Message Loop:*
   - A MSG structure named msg is declared for holding message information.
   - The program enters a message loop with GetMessage. This loop keeps running, retrieving messages from the application's message queue.
   - For each retrieved message, TranslateMessage potentially translates keyboard messages, and DispatchMessage sends the message to the appropriate window procedure.

6. **Handling Messages in WindowProc:**
   - Inside WindowProc, different messages are handled based on their type. For example, WM_CREATE is handled to create the edit control and buttons, WM_COMMAND handles button clicks, and WM_DESTROY posts a quit message.

7. *User Interactions:*
   - When the user interacts with the window (e.g., clicks a button), messages are sent to WindowProc. These messages are processed accordingly — for example, button clicks result in updating the display or performing calculations.

8. *Program Termination:*
   - If the user closes the window, a WM_DESTROY message is sent, leading to PostQuitMessage(0) being called. This posts a WM_QUIT message to the message queue.
   - When GetMessage retrieves the WM_QUIT message, the message loop exits, and the program proceeds to terminate.

This Calculator will automaticly remove unnecessary zeros and commas of ther is no nessesary 12,00 to 12 . It will calculate always just on 2 decimal after comma.







Loading the Executable:

The operating system loads the executable file into memory.
The program's entry point, typically the main function, is identified.
Initialization of the Windows Environment:

The main function initializes the Windows environment by registering a window class (CalculatorClass) using the RegisterClass function.
Creating the Main Window:

The CreateWindowEx function is called to create the main window with specified attributes such as class, title ("Simple Calculator"), position, and size.
Displaying the Main Window:

The ShowWindow function is called to make the main window visible on the screen.


The task.json file is like an instruction manual for a robot in Visual Studio Code. It tells the program how to build and run your code. It contains specific instructions and settings for these tasks. Developers can modify it to ensure that their project functions correctly.
