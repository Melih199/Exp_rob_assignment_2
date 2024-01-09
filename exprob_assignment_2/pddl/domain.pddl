(define (domain ROSbot)

(:requirements 
	:strips 
	:fluents 
	:typing 
	:disjunctive-preconditions 
	:durative-actions)


(:types 	
		robot
		waypoint
		marker
)


(:predicates
		(robot_at ?v - robot ?wp - waypoint)
		(visited ?wp - waypoint)
		(found ?m - marker)
		(visible ?m - marker ?wp - waypoint)
		(homing ?wp - waypoint)
	      
)

(:functions      
		(reached-waypoints)
		(detected-markers)
)


(:durative-action goto_waypoint
		:parameters (?v - robot ?from ?to - waypoint)
		:duration (= ?duration 30)
		:condition (and (at start (robot_at ?v ?from)))
	        :effect (and 
	        		(at start (not (robot_at ?v ?from))) 
				(at end (robot_at ?v ?to))
				(at end (visited ?to))
				(at end (decrease (reached-waypoints) 1)))
)

(:durative-action search_marker
                :parameters (?v - robot ?wp - waypoint ?m - marker)
		:duration (= ?duration 10)
		:condition (and (at start (robot_at ?v ?wp))
				(at start (visible ?m ?wp)))
	        :effect (and 
				(at end (found ?m))
				(at end (decrease (detected-markers) 1)))
)

(:durative-action home
		:parameters (?v - robot ?from - waypoint ?to - waypoint)
		:duration (= ?duration 30)
		:condition (and (at start (robot_at ?v ?from))
				(at start (= (reached-waypoints) 0))
				(at start (= (detected-markers) 0)))

	        :effect (and 
				(at start (not (robot_at ?v ?from))) 
				(at end (robot_at ?v ?to))
				(at end (homing ?to))
				(at end (visited ?to))))



)
