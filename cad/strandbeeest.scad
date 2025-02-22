$fa=0.5;
$fs=0.5;

thickness=2;
width=8;
post_radius=2.5;

tol = 0.4;

module link(length, width=width, thickness=thickness, post_radius=post_radius, post_height=thickness,hole=false,label=false) {
	translate([0,-width/2,0])
		difference() {
			union() {
				cube([length, width, thickness]);

				translate([0,width/2,0])
					cylinder(h=thickness,r=width/2);

				translate([length,width/2,0])
					cylinder(h=thickness,r=width/2);

				translate([0,width/2,0])
					cylinder(h=post_height+thickness,r=post_radius-tol);

				translate([length,width/2,0])
					cylinder(h=post_height+thickness,r=post_radius-tol);

			}

			if (hole) {
				translate([0,width/2,0])
					cylinder(h=post_height+thickness,r=post_radius+tol);

				translate([length,width/2,0])
					cylinder(h=post_height+thickness,r=post_radius+tol);
			}
			
			if (label) {
				translate([length/2,width/8,3*thickness/4])
				linear_extrude(thickness/4)
					text(str(length),size=2);
			}
		}
}

module triangle(l1, l2, l3, width=width, thickness=thickness, post_height=thickness, post_radius=post_radius, hole=false, label=false) {
	link(l1, width=width, thickness=thickness, post_height=post_height, post_radius=post_radius, hole=hole, label=label);
	rotate([0,0,180-acos((l2*l2-l1*l1-l3*l3)/(2*l1*l3))])
		link(l3, width=width, thickness=thickness, post_height=post_height, post_radius=post_radius, hole=hole, label=label);
	translate([l1,0,0]) rotate([0,0,acos((l3*l3-l1*l1-l2*l2)/(2*l1*l2))])
		link(l2, width=width, thickness=thickness, post_height=post_height, post_radius=post_radius, hole=hole, label=label);
}

translate([50,0,0]) triangle(55.8,41.5,40.1, post_height=5,label=false);
translate([50,50,0]) triangle(36.7, 65.7, 49.0, post_height=5,label=false);

translate([0,00,0]) link(length=39.3,hole=true,label=false);
translate([0,10,0]) link(length=39.4,hole=true,label=false);
translate([0,20,0]) link(length=50.0,hole=true,label=false);
translate([0,30,0]) link(length=61.9,hole=true,label=false);
