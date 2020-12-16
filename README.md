# Assignment 2 - Castle Defense

## Castle Defense
Attention brave and noble engineers! Castle CSE is under attack by Enemies from Frankie the Fox's Lair. Queen Chicken, First of Her Name, Protector of the Realm, Lecturer in Charge for COMP1511, has commissioned you to build Her defenses and protect Her Castle.

In this assignment, you will be implementing Castle Defense, a program that simulates an imaginary Realm that is under attack. You will be creating Lands in the Realm as well as building Towers to defend a Castle.

The Enemies will spawn from their Lair and move towards the Castle through the Lands. As the Enemies move, they will be attacked by the towers, which both harms the Enemies and depletes the towers. If the Enemies reach the Castle, they will damage it.

Your program will be managing Enemy movement as they pass through the Lands. It will also be managing the use of Towers against the Enemies and any damage the Castle receives.

Note: If this assignment appears daunting, fear not! The Queen's chosen human (Marc in lectures) will be demonstrating many of the techniques necessary to begin your tasks. Her loyal subjects (the Tutors) will also be teaching some of the techniques in detail in Labs. During Week 8, a great deal of the course will be dedicated to helping you get started with this assignment.

### The Realm
The realm is a struct that contains all of the objects that will be used in this assignment. Those are: Lands, The Lair, The Castle, Towers and Enemies. Your job is to manage the Realm, and everything it contains.

The Realm struct has a pointer to the Castle, whence Queen Chicken and her Loyal subjects look down upon their kingdom. It also has a pointer to the lair, from which Frankie the Fox sends his feindish Enemies. Every location in the Realm lies on a linked list that starts at The Castle, and goes down to The Lair. Locations can have one of four types:
 - Castle: The Castle, which is always the first node in the linked list. If the Enemies can reach The Castle, they will deal damage to it.
 - Land: A place where Enemies can gather.
 - Tower: A defense, built by you, to attack Enemies
 - Lair: The place from which Enemies are sent by Frankie

Your code should ensure that at the start of the program, the Castle points to the Lair, and the Lair points to NULL. Your code should then ensure that the Castle is always connected (through other locations) to the Lair; and that the Lair points to NULL.

To ensure this is true, you will never be given a test case where you are asked to put a tower after the Lair. (More details on adding towers later)

As an additional restriction to make the assignment's rules simpler, there will never be two locations with the same name. 

### Enemies
In these dark times, the realm is under attack. Fiendish Enemies regularly appear at their Lair and make their way, one location at a time, towards The Castle.

An Enemy is represented by a struct which records their name, their maximum health and their current health (as integers). These structs should also be set up so that the Enemies can be joined together in a linked list.

Enemies will always be at a location, which is represented by a linked list of Enemies at every location in The Realm. Linked lists of Enemies are always listed in alphabetical order.

An Enemy dies when it has zero or less health. It then is removed from the linked list that contained it and its memory is freed.

There will never be two enemies in the realm with the same name.

### Towers
As mentioned before, locations in the realm can be Towers. Towers are able to reduce the HP of any Enemy at their Location. They can only be used a fixed number of times. When they run out of uses, they convert back into lands.

Towers have two important properties:
 - Power: How much an Enemy's HP is reduced when the Tower attacks. This is a whole number, greater than zero.
 - Uses: A count of how many times a Tower can be used before it reverts to being a land. This is a whole number, greater than zero.

### The Castle
t the start of the list is The Castle. Enemies that manage to reach The Castle will deal damage to it; and if they move beyond the castle they are removed from the realm.

The Castle starts off with STARTING_CASTLE_HP health. If an Enemy damages The Castle, it causes The Castle's health to decrease by that Enemy's remaining health.

```
Note: Nothing special should happen when the castle goes below 0 HP. It can go negative if enough damage is dealt to it.
```

### The Game
When the game starts, two locations are automatically created - the Castle and the Lair. You will then be given a list of locations on standard input, one per line. The order of the locations as standard input is the same order they will have starting from Castle and proceeding to Lair. These locations will be strings that do not contain any spaces, dashes or square brackets. When the list of locations is complete, an empty line will be input.

After this, a prompt will appear. You will type in commands to indicate changes to the state of the Realm. These commands will all start with a character as the command, then a space, then possibly some additional information about the command. There are three special commands, which are already implemented in the Starter Code provided. They consist of:
 - ?: Print a list of all possible commands.
 - q: Quit the program.
 - /: Do nothing, this line is treated as a comment.
 
 
## Your Task: Implementation
Your task for this assignment is to write the functions that will manage the state of the Realm. All of these functions are contained inside the file realm.c. You will also have to write functions in test_realm.c to check your code works. 

### Starter Code
The starter code consists of the following files:
 - main.c contains the main function for the assignment. It will scan the program's input, then call the functions you will write. You must not change this file.
 - realm.h contains the definitions of all the functions you will be writing. It also contains useful constants and type definitions. You must not change this file.
 - realm.c contains empty functions which you will need to implement. It already contains some functions. It is strongly recommended that you use these. This file is where you will write your own code.
 - test_realm.h contains the prototypes of the testing functions in test_realm.c. You must not change this file
 - test_realm.c contains an alternative main function as well as template code that you will modify to make your own tests. This file is where you will write your own test cases.
 - capture.h contains the definition of a function that allows you to capture the output of your own code, to use in testing. It can only be used in test_realm.c, and will not be available in realm.c. You must not change this file.
 - capture.c contains the implementation of functions that allow you to capture the output of your own code, to use in testing. You must not change this file.

To run your code interactively, you should use the command:
```sh
$ dcc -o castle_defense realm.c main.c
$ ./castle_defense
```
To run your tests (written in test_realm.c), you should use the command:
```sh
$ dcc -o test_castle realm.c test_realm.c capture.c
$ ./test_castle
```

### Allowed C Features
In this assignment, there are two restrictions on C Features:
 - You must follow the rules explained in the Style Guide.
 - You may not use the function fnmatch, or import fnmatch.h.

It is recommended to only use features that have been taught in COMP1511. Course work in Week 8 will have a particular focus on assistance for this assignment and you will not need any of the subject material from Weeks 9 or 10.

If you choose to disregard this advice, you must still follow the Style Guide. You also may be unable to get help from course staff if you use features not taught in COMP1511.

### Input Commands
Input to your program will be via standard input (similar to typing into a terminal). You do not need to read this input yourself. Your functions in realm.c will be called by main.c with the input already scanned in.

Your code should not print or scan from the terminal (standard input or output). Do not use or add any printf or scanf in realm.c unless it's temporary and for debugging purposes. All printing and scanning has already been implemented for you in the starter code.

You can assume that input will be handled for you, and that you will never be given an invalid argument to one of your functions (except as described below).

Details of how this input will relate to the functions you call are given below:


## Stage One
Stage one involves adding new locations to the realm, as well as being able to print out the game state.

### Adding to the Realm
In realm.c you have been given two function stubs (a stub is an unimplemented function):
```sh
static Location new_location(char *name) {
    return NULL;
}

int add_location(Realm realm, char *name) {
    return 42;
}
```
These two functions should be implemented as described below.

new_location should use malloc to allocate memory for a new Location node. It should then set up it's name (and any other fields you decide you need throughout the assignment).
 - Note that the word "static" on this function will make it accessible within this file, but not elsewhere. We often use static on helper functions that are not part of the header file and aren't used by any other parts of the program. Static will not significantly change how you will use this function.
 - The new_realm function (already implemented in the starter code) uses the new_location function. The new_realm function does not need changing for this stage, but you may want to add code to it at a later stage.

add_location will be given a Realm and a Location name. It will then insert a new location node directly before the Lair in the linked list of locations. It returns the number of locations in the linked list.

These functions will never receive invalid inputs. 

### Printing Out the Realm
In realm.c you have been given the function stub:
```sh
void print_realm(Realm realm) {
}
```
as well as four fully implemented functions:
```sh
void print_tower(char *name, int power, int uses, Effect effect);
void print_land(char *name);
void print_castle(char *name, int defense);
void print_enemy(char *name, int cur_hp, int max_hp);
```

print_realm will be given a realm, and will print out information about that realm. You should use the functions given in the starter code to print it out, instead of calling printf yourself.

Specifically, print_realm will list locations in order from The Castle to The Lair. If there are any enemies at a location, it will list them in order before listing the next location.

Note: the castle starts off with STARTING_CASTLE_HP, so in the early stages, you will need to pass defense as STARTING_CASTLE_HP. You will not need the print_tower and print_enemy functions until Stage 2. 

Run the tests for this stage with:
```sh
$ 1511 autotest-stage 01 ass2_castle_defense
```


## Stage Two
Stage Two has two new commands. They involve adding enemies to a location, and adding Towers to protect the realm.

### Add Enemies
When running the program, you can use the following command to add a new enemy:
```
e location_name name HP
// for instance
e Lair EnemyName 4
```
Which means "Create a new enemy, at the location location_name, called name, with maximum HP hp.

You have been given the function stub, which will be called by main.c when the above command has been given:
```sh
int new_enemy(Realm realm, char *location_name, char *name, int hp) {
}
```
Your job is to implement this function, such that the code does the following:

Given a realm, the name of a Location in the realm, and some stats about a new enemy, you should (in this order):
 - Find the Location called location_name. If one does not exist, return ERROR_NO_LOCATION
 - Ensure that the stats you have been given for HP are not below 1. If they are, return ERROR_INVALID_STAT.
 - Place a new enemy, with the given stats, directly after the last enemy at the location you found above.
 - Return SUCCESS to indicate success.

You are guaranteed that you will only receive enemies in sorted order, and will never receive the same enemy name twice. You do not need to check this. This means that for any list of enemies, strcmp(enemy->name, enemy->next->name) will be strictly less than zero. This guarantee will only be relevant for Stage 4. 

### New Towers
When running the program, you can use the following command to add a new tower:
```
t prev_name name power uses
// for instance
t Castle NewTower 2 2
```
Which means "Create a new tower, directly below the Location prev_name , called name, that causes power damage to each enemy at it, and that can be used uses times".
You have been given the function stub, which will be called by main.c:
```sh
int new_tower(Realm realm, char *prev_name, char *name, int power, int uses){
}
```
Your job is to implement this function, such that the code does the following:

Given a realm, the name of a Location in the realm, and some stats about a new tower, you should:
 - Find the Location called prev_name. If one does not exist, return ERROR_NO_LOCATION
 - Ensure that the stats you have been given for power and uses are not below 1. If they are, return ERROR_INVALID_STAT.
 - Place a new tower, with the given stats, directly after the location which you found above. This tower is inserted into the linked list, which adds an element and does not replace the Location prev_name.
 - Return SUCCESS to indicate success.

Run the tests for this stage with:
```sh
$ 1511 autotest-stage 02 ass2_castle_defense
```


## Stage Three
### Freeing Memory and Destroying the Realm
When you quit the program (using the special command q), the following stub function will be called to free your list.
```sh
void destroy_realm(Realm realm);
```
calling this function should free:
 - Each Enemy
 - Each Location
 - The Realm struct
 - Any other memory you have allocated using malloc


### Advancing Enemies
When running the program, you can use the following command to move all enemies along.
```sh
n
```
This is called a "tick" in game design (as in, the "tick" of a clock). You have also been given the following function stub:
```sh
int advance_enemies(Realm realm) {
}
```
advance_enemies will go through the realm, moving each enemy from their current Location to the Location above in the linked list. Should any enemies go above the castle, they should be removed from the realm, and destroyed. You should return the number of enemies removed this way at the end of the function. The Lair should be empty of enemies after this, all of them having moved to the next Location in the list. 

### Damage
When running the program, you can use the following command to deal damage to Enemies and The Castle. It will also use up "uses" from any Towers that deal damage to enemies.

You can deal damage using the following command:
```
d
```
This will call the following function stub:
```sh
int apply_damage(Realm realm) {
}
```
Go through each Location in the realm, and do the following if the Location is a Tower:
 - Go through each Enemy at that Tower, and reduce it's HP by the Tower's power. If an enemy's HP is equal to or less than zero, remove it from the list of Enemies at that location
 - Reduce that Tower's number of uses left by 1, if it did damage to an enemy.
 - If that Tower now has no uses remaining, convert it into a Land. It should no longer have any effect on enemies that pass through it. 

apply_damage should also cause the Castle's defense to decrease, by the sum of the HP of each enemy currently at the Castle. For instance, if the Castle had an enemy with 3 HP, and one with 5 HP, the Castle's defense would decrease by 8.

apply_damage returns the number of enemies damaged this way.

Run the tests for this stage with:
```sh
$ 1511 autotest-stage 03 ass2_castle_defense
```


## Stage Four
Stage Four involves applying buffs ("changes in stats") to different parts of the realm. It also uses the concept of a "search", which is described below:

### Searching
```
This has changed since the spec was released.
In the initial version, we asked for an "exact match", when the sample solution and autotests implemented a "prefix match". We have updated the specification to describe an prefix match; however, we will not write any tests during Stage 4 that confirm you wrote a prefix match rather than an exact match. In Stage 5, where there is already an autotest that relies on prefix matching, we will assume you have written a prefix match.
```

Stage Four and Five rely on the concept of a search, described by a search_term. The simplest case is just a word, which should try find an prefix match. A prefix match is one where the word starts with the search term. For instance, searching for "hi" in the array {"hiya", "JBhi-fi", "JBHi-Fi", "hi", "HI", "phi"} would find "hiya" and "hi".

There is a special syntax we can use in a search, however, called a "character class". This lets you say "Any of these characters". A character class is wrapped in square brackets, like this: [abc]. That character class means "either a or b or c". Note that a character class takes the place of a single character, so h[abc]k would match "hak" or "hck" but not "hack".

There is also a shorthand in character classes for a group of characters: [a-m] means "match any character with an ascii value equal to or above 'a', and less than or equal to 'm'". In other words, it would match lowercase letters before 'n'.

You can mix and match these styles, so [0-9abD-F] would mean "match a character between '0' and '9', or 'a', or 'b', or a character between 'D' and 'F'.

You may assume that search terms always have matching '[' and ']' characters, and that '-' will never be the first or last character in a character-class. The character classes [] and (for example) [f-d] are both valid, but would never match anything.

You may also assume that locations and enemies will never have '[', '-' or ']' in their name. You do not need to check this. Until July 23, an autotest had contained an enemy with a '-', but this autotest has been altered to replace the '-' with a '_'.

### Buffs
You may use the following command to apply a buff. It is explained below
```
b search_term buff_type buff_amount
```
Using this command will call the following function stub:
```sh
int apply_buff(Realm realm, char *search_term, Buff buff, int amount) {
}
```
This means to apply the buff described by buff_type to everything matching search_term

Run the tests for this stage with:
```sh
$ 1511 autotest-stage 04 ass2_castle_defense
```


## Stage Five
```
This stage has very few tests! This stage has 2 tests, one for each effect. They do not necessarily cover every edge case. You should test it with other inputs, and compare your solution against the reference solution.
```
### Effects
You may use the following command to change a tower's effect. It is explained below.
```
f search_term effect_type
```
Using this command will call the following function stub:
```sh
int apply_effect(Realm realm, char *search_term, Effect effect) {
}
```
This means to apply the effect described by effect_type to every tower matching search_term

This function should return the number of towers that match the search_term

There are two effects you can apply, as well as the EFFECT_NONE which removes any special effect from a tower.

All towers start with EFFECT_NONE when they are created. Enemies move from that Tower to the next as normal.

When a tower's effect becomes something other than EFFECT_NONE, enemies move from that Tower in a different way. The specifics depend on which effect is applied to a tower, and is described below

Note that these Effects only change the way Enemies move. A Tower that has an effect will still deal damage and lose uses when applying damage, regardless of any effect they have. A Tower that is reduced to 0 uses and reverts to a Land will lose any Effects it has.

Run the tests for this stage with:
```sh
$ 1511 autotest-stage 05 ass2_castle_defense
```


## Testing
It is important to test your program thoroughly to make sure it can manage different situations. 

### Writing your own Automated Tests
As you implement functions in realm.c, you will encounter autotests in that ask you to implement test_realm.c.

test_realm.c is a file that contains a main function that is not the same as the interactive program in main.c. Instead, it runs a series of automatic tests on the functionality provided by realm.h and realm.c. You should not change this main function.

Your main function will call other functions that look like this:
```sh
void test_add_location(void) {
    printf("Test whether this add_location follows the spec: ");

    // Test 1: Does add_location's return value count the Castle & Lair?

    Realm test_realm = new_realm();

    int num_locations = add_location(test_realm, "Location");
    if (num_locations != 3) {
        printf(DOES_NOT_FOLLOW_SPEC);
        return;
    }

    // Test 2: Does add_location return the correct amount for lots of locations?

    // TODO: Change Here

    // Test 3: Add your own test, and explain it below:
    // ........

    // TODO: Change Here

    printf(FOLLOWS_SPEC);
}
```
Your job is to fill in the spaces where it says "Change Here" with a series of C statements that check whether the functions in realm.c work.

As you can see in Test 1, some of these functions have already been partially implemented to show you what you should do

Some functions will ask you to specifically test something (in this case, to make sure add_location returns the correct amount if you call it many times).

Some functions will ask you to decide on your own test. You should describe what you are testing, and then write a test for that thing.

Note that you can only test functions by checking their return values, and their output to the terminal. You cannot access the fields of a struct, nor can you redefine the structs from realm.c in test_realm.c. Doing so may cause you to lose marks.

You can test your tests yourself, by compiling it against your realm.c.

This is what you will see when you compile the starter code/tests. 
```sh
$ dcc -o test_castle test_realm.c realm.c capture.c
$ ./test_castle
================== Castle Defense Tests ==================
Test whether this add_location follows the spec: Does Not Follow Spec.
Test whether this print_realm follows the spec: Does Not Follow Spec.
Test whether this new_enemy follows the spec: Follows Spec.
Test whether this new_tower follows the spec: Follows Spec.
Test whether this apply_damage follows the spec: Follows Spec.
```
New (as of 22nd July): You are now able to compile your test code against our broken code. To do so, run 1511 build-test-castle test_realm.c -o test_realm.

You can then choose one of the "defects" that our test code supports, and the test solution will misbehave. 
```sh
$ 1511 build-test-castle test_realm.c -o test_realm
$ ./test_realm

================== Castle Defense Tests ==================
To use this test program, you should use:
./test_realm DEFECT
Where DEFECT is one of:
 - MANY_LOCATIONS
 - WRONG_HP
 - NO_LAIR_ENEMY
 - TOWER_AFTER_TOWER
 - DAMAGE_NO_DESTROY
 - NONE
 - NONE
$ ./test_realm DAMAGE_NO_DESTROY

================== Castle Defense Tests ==================
Test whether this add_location follows the spec: Follows Spec.
Test whether this print_realm follows the spec: Follows Spec.
Test whether this new_enemy follows the spec: Follows Spec.
Test whether this new_tower follows the spec: Follows Spec.
Test whether this apply_damage follows the spec: Does Not Follow Spec.
Test whether this apply_buff follows the spec: Follows Spec.
```

#### Capture
This term, we have given you two extra files -- capture.c and capture.h. These files define the CAPTURE macro. Macros are not covered in this course and as a result, you do not need to understand these files.

You can use them to capture what a function prints and put it into a string. This is useful if you combine it with the print_realm function, since you can then test the realm is as you expect.

The header of capture.h describes how to use it.
```
// This file contains the `CAPTURE()` macro. To use this macro,
// you should define a large, empty string. Lets say your string is:
//   char str[MAX_LENGTH];
// Then you can do the following:
//   CAPTURE(my_function(), str, MAX_LENGTH)
// Which will put the output of `my_function()` into str.
```

### Autotests
As usual autotest is available with some simple tests - but your own tests in test_realm may be more useful at pinpointing exactly which functions are and aren't working.
```sh
$ 1511 autotest castle_defense
```
If you wish to use autotest to view only a specific stage of the assignment, you can use autotest-stage. The following example shows how to autotest stage 1 but you can replace the stage number with any stage you would like to test.
```sh
$ 1511 autotest-stage 01 castle_defense
```

### Reference Implementation
If you have questions about what behaviour your program should exhibit, we have provided a sample solution for you to use.
```sh
$ 1511 castle_defense
```
