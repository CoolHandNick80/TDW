# TDW

Developed with Unreal Engine 5

Using GAS framework

For player the Ability System Component reside on PlayerState, for the enemies the Ability System Component reside on the character.

Implemented LeapSlam ability.

Ability takes the mouse cursor location and make the player jump at that location using attack speed multiplied for an alpha value (hardcoded for testing to the value of 40) as horizontal Speed.

Using the distance between player location and the target location the duration of the movement can be desumed and by this vertical speed is obtained.

Using parabolic movement functions Velocity can be assigned frame by frame directly, using the player tick.

When player land off get the enemy characters within the ability radius and apply them damage using a gameplay effect.
