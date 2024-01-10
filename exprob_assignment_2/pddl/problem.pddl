(define (problem task)
    (:domain ROSbot)
    (:objects
        rob - robot
        wp0 wp1 wp2 wp3 wp4 - waypoint
        m11 m12 m13 m15 - marker
    )
    (:init
        (robot_at rob wp0)
        (not (visited wp1))
        (not (visited wp2))
        (not (visited wp3))
        (not (visited wp4))
        (visible m11 wp1)
        (visible m12 wp2)
        (visible m13 wp3)
        (visible m15 wp4)
        (= (detected-markers) 1)
        (= (reached-waypoints) 1)
    )

    (:goal 
        (and
            (visited wp1)
            (visited wp2)
            (visited wp3)
            (visited wp4)
            (found m11)
            (found m12)
            (found m13)
            (found m15)
            (homing wp0)
        )
    )
)
