# Charlie the Dog

Have the function `CharlietheDog(strArr)` read the array of string stored in `strArr` which will be a 4x4 matric of the characters 'C', 'H', 'F', 'O', where the C represents Charlie the dog, H represents its home, F represents dog food, and O represents an empty space in the grid. Your goal is to figure out the least amount of moves required to get Charlie to grab each piece of food in the grid by moving up, down, left, or right, and then make it home right after. Charlie cannot move on the home before all pieces of food have been collected.

For example: if strArr is `["FOOF", "OCOO", "OOOH", "FOOO"]`, then this looks like the following grid:

```
FOOF
OCOO
OOOH
FOOO
```

For the input above, the least amount of steps where the dog can reach each piece of food, and then return home is 11 steps, so your program should return the number 11. The grid will always contain between 1 and 8 pieces of food.

```
Examples:
Input ["OOOO", "OOFF", "OCHO", "OFOO"]
Output 7

Input ["FOOO", "OCOH", "OFOF", "OFOO"]
Output 10
```
