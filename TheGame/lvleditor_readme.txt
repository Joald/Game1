For now it is used to set a level's name, its Shape, NPCs, and players' entrypoint.

Coordinates are temporarily handled so that the 2 numbers you put in as a fraction of a coordinate work like this:

In the level's area of the 2d world we have screenWidth*4 x screenHeight*3 pixels.

This is a number set in code and dependent on the default desktop resolution.

If you are asked to "Enter the fraction of level width that is the current point's x coordinate."
it means you are to enter two numbers. First of them will be multiplied by screenWidth (because it's the x coordinate)
and the product will be divided by the second one you enter.
What comes ot of it is a number that is scaled accordingly to resolution.

