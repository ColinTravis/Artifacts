// Speak&Spell Battery Lid
// 2012-12-26 Bernhard Slawik (http://www.bernhardslawik.de)
EPS = 0.005;
thick = 1.0;
space = 1.5;

lidWidth = 59.0;
lidLength = 59.0;
lidRecess = 2.0;	// Recess of lid borders on upper layer
lidOver = 2.0;	// How far the lid s under the chassis

fixPress = 0.0;
fixWidth = 20.0 - 2*space;
fixToothHeight = 10.0;
fixHeight = fixToothHeight +14.0;	// From bottom to "tooth" inside chassis
fixDepth = 2.5;	// Height of "tooth"
fixRecess = 2.0;
fixThick = 0.75;	// Thickness of flexible stuff
fixToothThick = fixRecess + 1.5;

bossThick = 5.0;
bosses = 2;
angle=0;
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
		cube([fixWidth + 2*space, fixPress + EPS, thick*2 + 2*EPS]);
	}

	// Back hanger
	//@TODO: Slant it for easier printing
	translate([lidRecess + space, lidLength - EPS, thick])
	cube([lidWidth - 2*lidRecess - 2*space, lidOver + EPS, thick]);
	

	// Fixer
	translate([lidWidth/2 - fixWidth/2, fixRecess - sin(angle)*fixToothHeight, thick])
	rotate([-angle,0,0])
	cube([fixWidth, fixThick, fixToothHeight]);

	for (i=[0:bosses-1])
	translate([- ((bosses-1)*fixWidth/bosses)/2+(fixWidth/bosses)*i, 0, 0])
	intersection() {
		translate([lidWidth/2 - thick/2, fixRecess - sin(angle)*fixToothHeight + fixThick, -bossThick/2])
		rotate([45,0,0])
		cube([thick, bossThick, bossThick]);

		translate([lidWidth/2 - thick/2, fixRecess - sin(angle)*fixToothHeight + fixThick, thick])
		cube([thick, bossThick, bossThick]);
	}

/*
	translate([lidWidth/2 - fixWidth/2, fixRecess - sin(angle)*fixToothHeight + fixThick, thick])
	rotate([-angle+4.5,0,0])
	cube([fixWidth, fixThick, fixToothHeight + thick/2]);
*/




	// Anti-tooth
	translate([lidWidth/2 - fixWidth/2, fixRecess - fixToothThick, fixToothHeight + space/2])
	rotate([-5.0, 0, 0])
	cube([fixWidth, fixToothThick + fixThick, thick*2]);

	intersection() {
		translate([lidWidth/2 - fixWidth/2, fixRecess - thick*2, fixToothHeight + thick])
		rotate([-45.0, 0, 0])
		cube([fixWidth, thick*4, thick*3]);

		translate([lidWidth/2 - fixWidth/2, fixRecess - fixToothThick + thick, fixToothHeight + thick - thick*3])
		cube([fixWidth, fixToothThick - fixThick, thick*3]);
	}



}

//intersection() {
lid();
//translate([0, -10, 0])	cube([100, 20,50]);}