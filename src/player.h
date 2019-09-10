//
// Created by marcj on 3/6/2019.
//

#ifndef FINAL_PROJECT_PLAYER_H
#define FINAL_PROJECT_PLAYER_H

#endif //FINAL_PROJECT_PLAYER_H

// DO NOT CHANGE ANYTHING IN THIS FILE

#pragma once

#include <iostream>

// A player or lack thereof.
enum class Player
{
    red,
    blue,
    neither,
};

// Prints a player in a manner suitable for debugging.
std::ostream& operator<<(std::ostream&, Player);
