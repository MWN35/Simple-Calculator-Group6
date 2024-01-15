Loading the Executable:

The operating system loads the executable file into memory.
The program's entry point, typically the main function, is identified.
Initialization of the Windows Environment:

The main function initializes the Windows environment by registering a window class (CalculatorClass) using the RegisterClass function.
Creating the Main Window:

The CreateWindowEx function is called to create the main window with specified attributes such as class, title ("Simple Calculator"), position, and size.
Displaying the Main Window:

The ShowWindow function is called to make the main window visible on the screen.
