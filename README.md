# Vicsek-Model-Simulator
A Visual Studio Project to simulate the Vicsek Model with a UI.
The project is implemented using QT.

Compiler Process::
Change the directory to current dir.
1.>qmake -project
2.>qmake
3.>make
4.>debug\[program-name].exe


File Introduction:
Bird.h------Model the particle using Bird class.
Dialogs.[h/cpp]------A panel to set some parameters.
DrawWindow.[h/cpp]------A panel to draw the birds in the field.
main.cpp------The entry of the program.
PlotSettings.[h/cpp]------Set some properties of the plot panel.
plotter.[h/cpp]------A panel to draw the statistics of the particles, such as the group number.
