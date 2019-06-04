// Speak&Spell Battery Lid
// 2012-12-26 Bernhard Slawik (http://www.bernhardslawik.de)
EPS = 0.005;
thick = 1.0;
space = 1.0;

lidWidth = 59.0;
lidLength = 59.0;
lidRecess = 2.0;	// Recess of lid borders on upper layer
lidOver = 2.0;	// How far the lid s under the chassis

fixPress = 6;
fixWidth = 20.0;
fixToothHeight = 10.0;
fixHeight = fixToothHeight +14.0;	// From bottom to "tooth" inside chassis
fixDepth = 2.5;	// Height of "tooth"
fixRecess = 5;
fixThick = 0.5;	// Thickness of flexible stuff
fixToothThick = fixRecess + 1.0;
fixToothOver = 1.0;
angle=25;
module lid() {
	difference() {
		union() {
			// Main layers
			cube([lidWidth, lidLength, thick]);

			translate([lidRecess, lidRecess, thick])
			cube([lidWidth - 2*lidRecess, lidLength - 1*lidRecess, thick]);
		}

		// Fixer
		translate([lidWidth/2 - fixWidth/2 - space, -EPS, -EPS])
		cube([fixWidth + 2*space, fixRecess + fixPress + EPS, thick*2 + 2*EPS]);
	}

	// Back hanger
	//@TODO: Slant it for easier printing
	translate([lidRecess + space, lidLength - EPS, thick])
	cube([lidWidth - 2*lidRecess - 2*space, lidOver + EPS, thick]);
	

	// Fixer
	translate([lidWidth/2 - fixWidth/2, fixRecess + fixThick + fixPress, 0])
	cube([fixWidth, thick*2, fixHeight]);

	translate([lidWidth/2 - fixWidth/2, fixRecess + fixThick + fixPress - thick*1, thick*2])
	rotate([-45,0,0])
	cube([fixWidth, thick*2, thick*2]);


	translate([lidWidth/2 - fixWidth/2, fixRecess - sin(angle)*fixToothHeight, space])
	rotate([-angle,0,0])
	cube([fixWidth, thick, fixToothHeight + space]);

	translate([lidWidth/2 - fixWidth/2, fixRecess, fixToothHeight+space])
	rotate([-27.8,0,0])
	cube([fixWidth, fixThick, fixHeight - fixToothHeight]);

	// Anti-tooth
	translate([lidWidth/2 - fixWidth/2, fixRecess - fixToothThick - fixToothOver, fixToothHeight + space/2])
	rotate([-5.0, 0, 0])
	cube([fixWidth, fixToothThick + thick + fixToothOver, thick]);

	// Finger thinger
	translate([lidWidth/2 - fixWidth/2, fixRecess - sin(angle)*fixToothHeight - thick, 0])
	cube([fixWidth, thick,thick]);



}

lid();