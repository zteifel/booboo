function s = GetRayBasedSensorReadings(robot, arena)

s = robot.Sensors;
s(1) = GetLRFReading(s(1),arena);  %% Only one sensor (LRF) in this example
s(2) = GetIRSensorReading(s(2),arena);
s(3) = GetIRSensorReading(s(3),arena);

end


