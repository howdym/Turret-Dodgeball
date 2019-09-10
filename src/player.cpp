//
// Created by marcj on 3/6/2019.
//

#include "player.h"

std::ostream& operator<<(std::ostream& os, Player p) {
    if (p == Player::red) {
        return os << "R";
    } else if (p == Player::blue) {
        return os << "B";
    } else {
        return os << "_";
    }
}
