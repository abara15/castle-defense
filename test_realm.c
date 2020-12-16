// Assignment 2 19T2 COMP1511: Castle Defense
// test_realm.c
//
// This file allows you to automatically test the functions you
// implement in realm.c.
//
// This program was written by @abara15 (GitHub)
// on 09-07-2019
//
// Version 1.0.0: Assignment released.

#include <stdio.h>
#include <assert.h>

#include "realm.h"

static void test_new_realm();
void test_print_realm();
void test_add_location();
// My tests
void test_add_location_five();
void test_valid_towers();
void test_invalid_stat_towers();
void test_invalid_name_towers();
void test_valid_enemy();
void test_invalid_stat_enemy();
void test_invalid_name_enemy();
void test_advance_enemy_to_next_loc();
void test_advance_enemy_past_castle();
void test_damage_enemies();
void test_damage_enemies_HP();
void test_damage_enemies_towers();

int main(void) {
    printf("\n================== Castle Defense Tests ==================\n");
    test_new_realm();
    test_print_realm();
    test_add_location();
    // My Tests
    // Stage 1 - Adding to the Realm
    test_add_location_five();
    // Stage 2 - New Towers
    test_valid_towers();
    test_invalid_stat_towers();
    test_invalid_name_towers();
    // Stage 2 - Add Enemies
    test_valid_enemy();
    test_invalid_stat_enemy();
    test_invalid_name_enemy();
    // Stage 2 - Advancing Enemies
    test_advance_enemy_to_next_loc();
    test_advance_enemy_past_castle();
    // Stage 3 - Damage
    test_damage_enemies();
    test_damage_enemies_HP();
    test_damage_enemies_towers();
}

////////////////////////////////////////////////////////////////////////
//                  Castle Defense Test Functions                     //
////////////////////////////////////////////////////////////////////////


// This function checks that a realm is actually being created.
void test_new_realm() {
    printf(">> Testing new_realm\n");

    printf("... Creating new realm.\n");
    Realm realm = new_realm();

    printf("... Checking it is not null.\n");
    assert(realm != NULL);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}




////////////////////////////////////////////////////////////////////////
//                Printing Out the Realm Test Functions               //
////////////////////////////////////////////////////////////////////////


// This function will print out an empty realm - it should not crash.
void test_print_realm() {
    printf(">> Testing print_realm\n");
    Realm realm = new_realm();

    printf("... This should show an empty realm - it should not crash.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}




////////////////////////////////////////////////////////////////////////
//               Adding to the Realm Test Functions                   //
////////////////////////////////////////////////////////////////////////


// This function will add new locations and try to print them.
void test_add_location() {
    printf(">> Testing add_location.\n");
    Realm realm = new_realm();

    printf("... Adding locations.\n");
    add_location(realm, "First_Location");
    add_location(realm, "Second_Location");
    add_location(realm, "Third_Location");

    printf("... This should show an realm with three extra locations.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}

// This function will add five new locations to the realm and try to print them.
void test_add_location_five() {
    printf(">> Testing add_location for five locations.\n");
    Realm realm = new_realm();

    printf("... Adding five locations.\n");
    add_location(realm, "Roundhouse");
    add_location(realm, "Tyree");
    add_location(realm, "Red Centre");
    add_location(realm, "Quad");
    add_location(realm, "Library");

    printf("... This should show an realm with five extra locations.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}




////////////////////////////////////////////////////////////////////////
//                      New Towers Test Functions                     //
////////////////////////////////////////////////////////////////////////


// This function will add new locations and towers with valid arguments
// to the realm and try to print them.
void test_valid_towers() {
    printf(">> Testing new_tower for valid towers.\n");
    Realm realm = new_realm();

    printf("... Adding locations.\n");
    add_location(realm, "LocationOne");
    add_location(realm, "LocationTwo");
    add_location(realm, "LocationThree");
    new_tower(realm, "LocationOne", "TowerOne", 1, 10);
    new_tower(realm, "LocationOne", "TowerTwo", 5, 8);
    new_tower(realm, "LocationTwo", "TowerThree", 15, 50);
    new_tower(realm, "LocationTwo", "TowerFour", 7, 25);
    new_tower(realm, "LocationThree", "TowerFive", 3, 7);
    new_tower(realm, "LocationThree", "TowerSix", 14, 42);

    printf("... This should show an realm with three extra "
            "locations, each with two valid towers.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}

// This function will add new locations to the realm and try to print them. It will also
// try and add a tower with invalid powers and uses, which should return invalid stat.
void test_invalid_stat_towers() {
    printf(">> Testing new_tower for towers with invalid powers and/or uses.\n");
    Realm realm = new_realm();

    printf("... Adding locations.\n");
    add_location(realm, "Quad");
    add_location(realm, "Tyree");
    add_location(realm, "Roundhouse");
    new_tower(realm, "Quad", "TowerOne", 1, 10);
    new_tower(realm, "Quad", "TowerTwo", -5, -8);
    new_tower(realm, "Tyree", "TowerThree", 15, 50);
    new_tower(realm, "Tyree", "TowerFour", 0, 0);
    new_tower(realm, "Roundhouse", "TowerFive", 3, 7);
    new_tower(realm, "Roundhouse", "TowerSix", -14, 42);

    printf("... This should show an realm with three extra locations, "
            "each with one valid tower. Each location will also "
            "attempt to add an invalid tower, which should not print.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}

// This function will add new locations to the realm and try to print them. It will 
// also try and add a tower with an invalid previous name, which should return no
// location.
void test_invalid_name_towers() {
    printf(">> Testing new_tower for towers with invalid previous names.\n");
    Realm realm = new_realm();

    printf("... Adding locations.\n");
    add_location(realm, "LocationOne");
    add_location(realm, "LocationTwo");
    add_location(realm, "LocationThree");
    new_tower(realm, "Quad", "TowerOne", 1, 10);
    new_tower(realm, "Quad", "TowerTwo", 5, 8);
    new_tower(realm, "Tyree", "TowerThree", 15, 50);
    new_tower(realm, "Tyree", "TowerFour", 1, 10);
    new_tower(realm, "Roundhouse", "TowerFive", 3, 7);
    new_tower(realm, "Roundhouse", "TowerSix", 14, 42);

    printf("... This should show an realm with three extra locations. "
            "No tower should print as none of them have valid "
            "previous names.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}




////////////////////////////////////////////////////////////////////////
//                     Add Enemies Test Functions                     //
////////////////////////////////////////////////////////////////////////

// This function will add new locations to the realm and try to print them.
// It will also try and add a tower and enemy to each location and Lair.
void test_valid_enemy() {
    printf(">> Testing new_enemy for valid enemies.\n");
    Realm realm = new_realm();

    printf("... Adding locations.\n");
    add_location(realm, "LocationOne");
    add_location(realm, "LocationTwo");
    new_tower(realm, "LocationOne", "TowerOne", 1, 10);
    new_tower(realm, "LocationTwo", "TowerTwo", 5, 8);
    new_enemy(realm, "Lair", "EnemyLair", 100);
    new_enemy(realm, "LocationOne", "EnemyOne", 5);
    new_enemy(realm, "LocationOne", "EnemyTwo", 32);
    new_enemy(realm, "LocationTwo", "EnemyThree", 50);
    new_enemy(realm, "LocationTwo", "EnemyFour", 10);

    printf("... This should show an realm with three two locations, "
            "each with a valid tower and two enemies. It should also "
            "show an enemy in the Lair.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}

// This function will add new locations and towers to the realm and try to
// print them. It will also try and add an enemy with invalid stats, which
// should return invalid stat.
void test_invalid_stat_enemy() {
    printf(">> Testing new_enemy for enemies with invalid stats.\n");
    Realm realm = new_realm();

    printf("... Adding locations.\n");
    add_location(realm, "LocationOne");
    add_location(realm, "LocationTwo");
    new_tower(realm, "LocationOne", "TowerOne", 1, 10);
    new_tower(realm, "LocationTwo", "TowerTwo", 5, 8);
    new_enemy(realm, "LocationOne", "EnemyOne", -5);
    new_enemy(realm, "LocationTwo", "EnemyTwo", 0);

    printf("... This should show an realm with two extra locations, each with a "
            "valid tower. It should not print the enemy, which has invalid stats.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}

// This function will add new locations and towers to the realm and try to print them.
// It will also try and add an enemy with an invalid previous name, which should return
// no location.
void test_invalid_name_enemy() {
    printf(">> Testing new_enemy for enemies - one with an invalid previous name.\n");
    Realm realm = new_realm();

    printf("... Adding locations.\n");
    add_location(realm, "LocationOne");
    add_location(realm, "LocationTwo");
    new_tower(realm, "LocationOne", "TowerOne", 1, 10);
    new_tower(realm, "LocationTwo", "TowerTwo", 5, 8);
    new_enemy(realm, "LocationOne", "EnemyOne", 5);
    new_enemy(realm, "Dungeon", "EnemyTwo", 10);

    printf("... This should show an realm with two extra locations, "
            "each with a valid tower. It should print the first, "
            "but not the second enemy, which has an invalid previous name.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}




////////////////////////////////////////////////////////////////////////
//                  Advancing Enemies Test Functions                  //
////////////////////////////////////////////////////////////////////////

// This function will add new locations and enemies to the realm and try to
// print them. It will advance the enemies to their next location.
void test_advance_enemy_to_next_loc() {
    printf(">> Testing advance_enemies for enemies.\n");
    Realm realm = new_realm();

    printf("... Adding locations.\n");
    add_location(realm, "LocationOne");
    add_location(realm, "LocationTwo");
    new_enemy(realm, "Lair", "EnemyLair", 100);
    new_enemy(realm, "LocationOne", "EnemyOne", 5);
    new_enemy(realm, "LocationOne", "EnemyTwo", 32);
    new_enemy(realm, "LocationTwo", "EnemyThree", 50);
    new_enemy(realm, "LocationTwo", "EnemyFour", 10);

    printf("... This should show an realm with three two locations, "
            "each with a two enemies. It should also show an enemy "
            "in the Lair.\n");
    
    print_realm(realm);

    advance_enemies(realm);

    printf("... This should show the same realm, however with the "
            "enemies at their next respective location.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}

// This function will add new locations and enemies to the realm and try to
// print them. It will advance the enemies past the castle.
void test_advance_enemy_past_castle() {
    printf(">> Testing advance_enemies enemies advancing past the castle.\n");
    Realm realm = new_realm();

    printf("... Adding locations.\n");
    add_location(realm, "LocationOne");
    add_location(realm, "LocationTwo");
    new_enemy(realm, "Castle", "EnemyOne", 5);
    new_enemy(realm, "Castle", "EnemyTwo", 32);
    new_enemy(realm, "Castle", "EnemyThree", 50);
    new_enemy(realm, "Castle", "EnemyFour", 10);

    printf("... This should show an realm with three two "
            "locations, each with two enemies.\n");
    
    print_realm(realm);

    advance_enemies(realm);

    printf("... This should show the same realm, however with "
            "no enemies as they have advanced past the castle.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}




////////////////////////////////////////////////////////////////////////
//                       Damage Test Functions                        //
////////////////////////////////////////////////////////////////////////

// This function will add new locations, towers and enemies to the realm
// and try to print them. It should then damage the enemies.
void test_damage_enemies() {
    printf(">> Testing apply_damage.\n");
    Realm realm = new_realm();

    printf("... Adding locations.\n");
    add_location(realm, "LocationOne");
    add_location(realm, "LocationTwo");
    new_tower(realm, "LocationOne", "TowerOne", 1, 10);
    new_tower(realm, "LocationTwo", "TowerTwo", 5, 8);
    new_enemy(realm, "TowerOne", "EnemyOne", 5);
    new_enemy(realm, "TowerOne", "EnemyTwo", 12);
    new_enemy(realm, "TowerTwo", "EnemyThree", 32);
    new_enemy(realm, "TowerTwo", "EnemyFour", 9);

    printf("... This should show an realm with two extra locations, "
            "each with two towers containing two enemies.\n");

    print_realm(realm);

    apply_damage(realm);

    printf("... This should show the same realm, with the HP of "
            "the enemies reduced by the tower's power.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}

// This function will add new locations, towers and enemies to the realm and try
// to print them. It should damage the enemies, and remove those enemies whose HP's
// have gone below zero.
void test_damage_enemies_HP() {
    printf(">> Testing apply_damage to remove enemies whose HP is below zero.\n");
    Realm realm = new_realm();

    printf("... Adding locations.\n");
    add_location(realm, "LocationOne");
    add_location(realm, "LocationTwo");
    new_tower(realm, "LocationOne", "TowerOne", 7, 2);
    new_tower(realm, "LocationTwo", "TowerTwo", 5, 8);
    new_enemy(realm, "TowerOne", "EnemyOne", 5);
    new_enemy(realm, "TowerOne", "EnemyTwo", 45);
    new_enemy(realm, "TowerTwo", "EnemyThree", 5);
    new_enemy(realm, "TowerTwo", "EnemyFour", 32);

    printf("... This should show an realm with two extra locations, "
            "each with two towers containing two enemies.\n");

    print_realm(realm);

    apply_damage(realm);

    printf("... This should show the same realm, with the HP of the enemies "
            "reduced by the tower's power. Enemies whose HP's have gone below "
            "zero not print.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}

// This function will add new locations, towers and enemies to the realm
// and try to print them. It should damage the enemies, and convert
// towers with no uses left to land.
void test_damage_enemies_towers() {
    printf(">> Testing apply_damage.\n");
    Realm realm = new_realm();

    printf("... Adding locations.\n");
    add_location(realm, "LocationOne");
    add_location(realm, "LocationTwo");
    new_tower(realm, "LocationOne", "TowerOne", 1, 10);
    new_tower(realm, "LocationTwo", "TowerTwo", 5, 1);
    new_enemy(realm, "TowerOne", "EnemyOne", 5);
    new_enemy(realm, "TowerOne", "EnemyTwo", 12);
    new_enemy(realm, "TowerTwo", "EnemyThree", 32);
    new_enemy(realm, "TowerTwo", "EnemyFour", 9);

    printf("... This should show an realm with two extra locations, "
            "each with two towers containing two enemies.\n");

    print_realm(realm);

    apply_damage(realm);

    printf("... This should show the same realm, with the HP of the "
            "enemies reduced by the tower's power. Towers with no "
            "uses left should be converted to land.\n");

    print_realm(realm);

    printf("... Destroying realm.\n");
    destroy_realm(realm);
}
