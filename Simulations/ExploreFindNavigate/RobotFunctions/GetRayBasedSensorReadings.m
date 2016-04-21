function s = GetRayBasedSensorReadings(robot, arena)

s = robot.Sensors;
s(1) = GetLRFReading(s(1),arena);  %% Only one sensor (LRF) in this example

end


