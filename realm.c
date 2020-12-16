// Assignment 2 19T2 COMP1511: Castle Defense
//
// This program was written by @abara15 (GitHub)
// on 30-07-2019
//
// Version 1.0.0 (2019-07-22): Assignment released.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "realm.h"

////////////////////////////////////////////////////////////////////////

// `struct realm` represents a realm, which represents the state of the
// entire program. It is mainly used to point to a linked list of 
// locations, though you may want to add other fields to it.
//
// You may need to add fields to struct realm.
struct realm {
    struct location *castle;
    struct location *lair;
};

// `struct location` represents a location, which could be a land,
// a tower, or a castle. Each of those places has a different type
// of information that this struct will need to store.
//
// You will need to add fields to struct location.
struct location {
    char name[MAX_NAME_LENGTH];
    struct enemy *enemies;
    struct location *next;
    int type;
    int power;
    int uses;
    int hp;

};

// `struct enemy` represents an enemy, which will move through the
// realm (to each location). Towers can deal damage to it, and
// it can deal damage to the Castle.
//
// You will need to add fields to struct enemy.
struct enemy {
    char name[MAX_NAME_LENGTH];
    struct enemy *next;
    int current_hp;
    int max_hp;
};

// Add any other structs you define here.

////////////////////////////////////////////////////////////////////////

// Function prototypes for helper functions
static Location new_location(char *name);
static void print_tower(char *name, int power, int uses, Effect effect);
static void print_land(char *name);
static void print_castle(char *name, int defense);
static void print_enemy(char *name, int cur_hp, int max_hp);

// Add prototypes for any extra functions you create here.

////////////////////////////////////////////////////////////////////////

// You need to implement the following 2 functions.
// In other words, write code to make the function work as described 
// in realm.h.

// Create a new realm, and return a pointer to it.
Realm new_realm(void) {
    struct realm *realm = malloc(sizeof(struct realm));
    realm->lair = new_location("Lair");
    realm->castle = new_location("Castle");
    realm->castle->hp = STARTING_CASTLE_HP;
    realm->castle->type = TYPE_CASTLE;

    if (realm->lair != NULL && realm->castle != NULL) {
        realm->lair->next = realm->castle;
    }

    return realm;
}

static Location new_location(char *name) {

    // TODO: Make this create a location and return a pointer to it.
    // Allocate memory for new Location node.
    Location loc = malloc(sizeof(struct location));

    // Set up its name.
    strcpy(loc->name,name);
    loc->enemies = NULL;
    loc->next = NULL;
    loc->type = TYPE_LAND;

    // Return a pointer to the location.
    return loc;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add a new location to the realm.
void add_location(Realm realm, char *name) {

    // Note: you should use the new_location function here.
    // Create a new location node, and set it at the lair.
    struct location *current = realm->lair;

    // This will get us to the linked list before castle.
    while (current->next != realm->castle) {
        current = current->next;
    }

    // Create a new location using the memory created in the function.
    struct location *new_loc = new_location(name);

    // Points the linked list before castle to the new location.
    current->next = new_loc;
    
    // Points the new location to the castle.
    new_loc->next = realm->castle;

}

// Print out the realm.
void print_realm(Realm realm) {

    // Note: you should use the provided print functions here.
    // Start location is the lair.
    Location current = realm->lair;

    // While the location exists.
    while (current->next != NULL) {
        // Resets curr_enemy to start of list.
        Enemy curr_enemy = current->enemies;
        if (current->type == TYPE_LAND) {
            // Print land if type_land.
            print_land(current->name);
        } else if (current->type == TYPE_TOWER) {
            // Print tower if type_tower.
            print_tower(current->name, current->power, current->uses, EFFECT_NONE);
        }
        // Loops through our enemy list to print enemies.
        while (curr_enemy != NULL) {
            print_enemy(curr_enemy->name, curr_enemy->current_hp, curr_enemy->max_hp);
            curr_enemy = curr_enemy->next;
        }
        // Increment to next location.
        current = current->next;
    }

    // Prints castle - last location.
    print_castle(current->name, realm->castle->hp);
    // Prints enemies that are in the castle location.
    Enemy curr_enemy = current->enemies;
    while (curr_enemy != NULL) {
        print_enemy(curr_enemy->name, curr_enemy->current_hp, curr_enemy->max_hp);
        curr_enemy = curr_enemy->next;
    }

}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add a new tower to the realm.
int new_tower(Realm realm, char *prev_name, char *name, int power, int uses) {

    // Start location is the lair.
    Location current = realm->lair;

    // Check that stats are valid.
    if (power < 1 || uses < 1) {
        return ERROR_INVALID_STAT;
    }

    // Create memory for new tower and assign stats to struct.
    Location new_tower_loc = new_location(name);
    new_tower_loc->type = TYPE_TOWER;
    new_tower_loc->power = power;
    new_tower_loc->uses = uses;
    new_tower_loc->enemies = NULL;
    new_tower_loc->next = NULL;

    // Will increment to next location until prev_name
    // and current location name are the same.
    while (strcmp(prev_name,current->name) != 0) {
        Location next = current->next;
        if (next == NULL) {
            return ERROR_NO_LOCATION;
        }
        current = current->next;
    }

    // Now at location we need to add tower at.
    // Assigns new tower location to our current location and returns success.
    new_tower_loc->next = current->next;
    current->next = new_tower_loc;

    return SUCCESS;

}

// Add an enemy to the realm.
int new_enemy(Realm realm, char *location_name, char *name, int hp) {

    // Set start location at lair.
    Location current = realm->lair;

    // Check that stats are valid.
    if (hp < 1) {
        return ERROR_INVALID_STAT;
    }

    // Compare current location name to the location name input.
    while (strcmp(current->name, location_name)) {
        if (current->next == NULL) {
            // If string compare loop has not ended yet and the next element in the
            // list is NULL, there is no location.
            return ERROR_NO_LOCATION;
        }
        current = current->next;
    }

    // Create memory for a new enemy and copy stats into struct.
    Enemy enemy_new = malloc(sizeof(struct enemy));
    strcpy(enemy_new->name, name);
    enemy_new->current_hp = hp;
    enemy_new->max_hp = enemy_new->current_hp;
    //strcpy(name, enemy_new->name);
    enemy_new->next = NULL;

    // New enemy.
    Enemy curr_enemy = current->enemies;

    // If null, put new enemy in the enemies struct.
    if (curr_enemy == NULL) {     
        current->enemies = enemy_new;
        return SUCCESS;
    } else if (curr_enemy != NULL) {
        while (curr_enemy->next != NULL) {
            curr_enemy = curr_enemy->next;
        }
        curr_enemy->next = enemy_new;
        return SUCCESS;
    }

    // If the function hasn't been stopped by a return,
    // then there is no location and it will return the error.
    return ERROR_NO_LOCATION;

}

// Advance enemies towards the castle.
int advance_enemies(Realm realm) {
    Location current = realm->lair;
    int i = 0;

    // Initial case for advancing enemies at lair and saving prev loc temp variable
    Enemy temp_enem = current->next->enemies;
    current->next->enemies = current->enemies;
    current->enemies = NULL;
    current = current->next;

    //Creates temp to store the enemies and move them to next location.
    while (current->next != NULL) {
        Enemy temp_enem_next = current->next->enemies;
        current->next->enemies = temp_enem;
        temp_enem = temp_enem_next;
        current = current->next;
    }

    // For the enemies that go past the castle.
    Enemy curr_enem = temp_enem;
    while (curr_enem != NULL) {
        i++;
        curr_enem = curr_enem->next;
    }

    // Frees the enemies that need to be removed.
    curr_enem = temp_enem;
    while (curr_enem != NULL) {
        Enemy temp_free = curr_enem;
        curr_enem = curr_enem->next;
        free(temp_free);
    }

    // Return number of enemies removed i.e. pass the castle.
    return i;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

// Apply damage from the enemies at each tower to that tower.
int apply_damage(Realm realm) {

    // Set start location at lair.
    Location current = realm->lair;

    int enemy_count = 0;
    while (current != NULL) {
        if (current->type == TYPE_TOWER && current->enemies != NULL) {
            Enemy curr_enemy = current->enemies;
            while (curr_enemy != NULL) {
                // Reduce the enemy's HP by the tower's power.
                curr_enemy->current_hp = curr_enemy->current_hp - current->power;
                
                // Apply damage returns the number of enemies damaged this way.
                enemy_count++;
                // If HP < 0, remove enemy from list and free that memory.
                // Overdeep nesting - wouldn't work in function so leave here.
                if (curr_enemy->current_hp <= 0) {
                    Enemy temp_enemy = curr_enemy;
                    if (curr_enemy == current->enemies) {
                        current->enemies = curr_enemy->next;
                    }
                    //curr_enemy->next = curr_enemy;
                    curr_enemy = curr_enemy->next;
                    free(temp_enemy);
                } else {
                    // Next enemy in list
                    curr_enemy = curr_enemy->next;
                }
            }
            // Need to reduce tower's uses by 1 if it does damage to enemy.
            current->uses = current->uses - 1;
            // If tower has no more uses remaining, convert it to land.
            if (current->uses <= 0) {
                current->type = TYPE_LAND;
            }
        }
        if (current->type == TYPE_CASTLE && current->enemies != NULL) {
            Enemy curr_enemy = current->enemies;
            while (curr_enemy != NULL) {
                // Reduce castle's HP by the enemy's current HP.
                realm->castle->hp = realm->castle->hp - curr_enemy->current_hp;
                // Next enemy in list
                curr_enemy = curr_enemy->next;
            }
        }
        // Next location in list
        current = current->next;
    }

    return enemy_count;
    
}

// Destroy the realm, and free any associated memory.
void destroy_realm(Realm realm) {

    // Set start location at lair.
    Location curr_loc = realm->lair;

    while (curr_loc != NULL) {
        // Set start enemy at top of enemies list.
        Enemy curr_enemy = curr_loc->enemies;
        while (curr_enemy != NULL) {
            // Create temp for enemy and store curr_enemy,
            // increment curr_enemy and free the original enemy.
            Enemy temp_enemy = curr_enemy;
            curr_enemy = curr_enemy->next;
            // Free the enemy.
            free(temp_enemy);
        }
        // Create temp for location and store curr_loc,
        // increment curr_loc and free the original location.
        Location temp_loc = curr_loc;
        curr_loc = curr_loc->next;
        // Free the location.
        free(temp_loc);
    }
    // Free the realm.
    free(realm);

}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Apply the specified buff to the relevant towers or enemies.
int apply_buff(Realm realm, char *search_term, Buff buff, int amount){
    return 0;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// Apply the specified effect to each tower whose name matches the
// specified search term.
int apply_effect(Realm realm, char *search_term, Effect effect) {
    return 0;
}

////////////////////////////////////////////////////////////////////////

// Add definitions for your own functions below.
// Make them static to limit their scope to this file.



////////////////////////////////////////////////////////////////////////
//                    Provided print functions                        //
//         NOTE: YOU SHOULD NOT MODIFY THE FOLLOWING FUNCTIONS        //
////////////////////////////////////////////////////////////////////////

static void print_tower(char *name, int power, int uses, int effect) {
    printf("%32s [pow: %3d | uses: %3d]", name, power, uses);
    if (effect == EFFECT_NONE) printf(" {%c}", EFFECT_NONE_CHAR);
    if (effect == EFFECT_ICE) printf(" {%c}", EFFECT_ICE_CHAR);
    if (effect == EFFECT_BOUNCE) printf(" {%c}", EFFECT_BOUNCE_CHAR);
    printf("\n");
}

static void print_land(char *name) {
    printf("%32s [____________________]\n", name);
}

static void print_castle(char *name, int defense) {
    printf("%32s [Castle Defenses: %3d]\n", name, defense);
}

static void print_enemy(char *name, int cur_hp, int max_hp) {
    printf("%40s [hp: %d/%d]\n", name, cur_hp, max_hp);
}

////////////////////////////////////////////////////////////////////////
//              End of provided print functions                       //
////////////////////////////////////////////////////////////////////////


/*//////////////////////////////////////////////////////////////////////
//                          To-Do List                                //
////////////////////////////////////////////////////////////////////////
Stage 1:
    - Adding to the realm < DONE >
    - Printing out the realm < DONE >
Stage 2:
    - New Towers < DONE >
    - Add Enemies < DONE >
    - Advancing Enemies < DONE >
Stage 3:
    - Damage < DONE >
    - Freeing memory and destroying realm < DONE >
Stage 4:
    - Searching - NOT_DOING
    - Buffs - NOT_DOING
Stage 5:
    - Effects - NOT_DOING
////////////////////////////////////////////////////////////////////////
//                          End of To-Do List                         //
//////////////////////////////////////////////////////////////////////*/
