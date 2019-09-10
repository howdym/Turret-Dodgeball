# Proposal: Dodgeball War

## Synopsis

### Elements

Our game will have 4 main elements:

A stationary interface at the top of the screen that displays the health of each player and the amount of
currency they each own

A circular red ball and blue ball, representing each player, controllable by each user

An array of red player’s turrets and blue player’s turrets that are upgradeable and grows as each player builds
more

An array of red bullets and blue bullets that are fired from the turrets and will bounce upon first collision
and are destroyed upon the next

### Goal

The game comprises of two players and is competitive. Each player’s goal is to get the opposing player’s
character to zero health whilst still surviving. A player will lose health when a bullet of the opposing color
collides with his/her character. The game ends when one player’s health reaches zero.

### Gameplay

Each player will start off with *some* amount of currency and *some* amount of health, displayed at an interface
above the game screen. Each player will be able to control their character within the bounds of the corresponding
half of the screen— the left half for player red and the right half for player blue. Players can spend currency
to build turrets and the turrets will be built wherever the player is located. The turrets will fire bullets at a
constant rate with *random* velocity towards the opposing side. Players can also upgrade turrets by attempting to
build a turret on an existing turret. An upgraded turret will fire bullets that travel at a faster speed. Players
will gain currency either by having a friendly bullet hit the opposing player or by having bullets collide with
the corresponding boundary of the screen— player red will earn currency by having bullets hit the left side of
the screen and player blue will earn currency by having bullets hit the right side of the screen. Bullets will
bounce upon collision and will be destroyed upon second collision.

## Functional Requirements

1. Each character is controllable by keyboard— player red will be controlled by ‘WSDA’ and player blue will be
controlled by arrow keys.
2. Each character cannot go past the boundaries of the screen and also cannot go past their respective half of
the screen— the left side for player red and the right side for player blue.
3. Each player can build turrets by pressing a designated key— [space] for player red and ‘/’ for player blue—
and the turret will be stationary from the location of where the character built the turret.
4. If a turret already exists at the location where a player wants to build a turret, pressing the designated
key will upgrade the turret instead so that it will fire bullets with greater speed and turn a darker shade of
red or blue.
5. Turrets will shoot bullets at a rate of once per 300 updates and a constant max speed dependent on upgrade
level (10 + 2(n - 1) = speed, s.t. n = level).
6. The direction of each bullet fired from a turret will be *random*.
7. Bullets being shot have the ability to collide with the boundaries of the screen as well as the players;
however, they will be able to travel through (over) turrets and other bullets (over or under by chance).
8. Bullets upon first collision will bounce— the x-velocity and y-velocity will both be reversed— but upon
second collision will be destroyed.
9. If a bullet collides with the left or right boundary of the screen, the red player or blue player respectively
will gain *some* currency.
10. There will be red player bullets and blue player bullets and when an opposing bullet collides with a player,
said player will lose *some* health and the opposing player will gain *some* money.
11. Turrets will cost a *set or varied* amount of *money* to be placed or upgraded.
12. If a player loses a certain amount of *health*, that player will lose the game.
13. Each player’s currency and health must be constantly tracked, updated, and displayed above the top boundary
of the game screen.
14. When the game ends, the game screen will clear and will display the winner of the game; the currency and
health interface will remain as well.

## Open Questions

Are we allowed to use Prof. Tov’s homework code as well as code we have written in the past?
How do we keep track of time elapsed in order to fire bullets at a constant rate?
Will adjustments be made to the Cmake file if we create more cpp files for additional classes and structs?
How do we create certain shapes, particularly a sideways triangle for turrets?
How much health and currency should each player start with?
How do we randomize the direction of fired bullets within a range?
How will currency and costs scale?
How fast should bullets and players move?
What should the size of the turrets, players, and bullets be?
