$fa=0.1;
$fs=0.1;

thickness=2;
width=5;
post_radius=2;

tol = 0.1;

module link(length, width=width, thickness=thickness, post_radius=post_radius, post_height=thickness,hole=false) {
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
			
			translate([length/2,width/8,3*thickness/4])
			linear_extrude(thickness/4)
				text(str(length),size=2);
		}
}

module triangle(l1, l2, l3, hole=false) {
	link(l1, hole=hole);
	rotate([0,0,180-acos((l2*l2-l1*l1-l3*l3)/(2*l1*l3))])
		link(l3, hole=hole);
	translate([l1,0,0]) rotate([0,0,acos((l3*l3-l1*l1-l2*l2)/(2*l1*l2))])
		link(l2, hole=hole);
}

translate([50,0,0]) triangle(55.8,41.5,40.1);
translate([50,50,0]) triangle(36.7, 65.7, 49.0);

translate([0,00,0]) link(length=39.3,hole=true);
translate([0,10,0]) link(length=39.4,hole=true);
translate([0,20,0]) link(length=50.0,hole=true);
translate([0,30,0]) link(length=61.9,hole=true);
