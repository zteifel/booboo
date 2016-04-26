function b = BrainStep(robot, time);

b = robot.Brain;

%%%%%%%%%%%%%%%% FSM: %%%%%%%%%%%%%%%%%%%

% 0. Walk a distance
% 1. Look for cylinder
% 2. Navigate to cylinder
% 3. Place robot to catch cylinder



if (b.CurrentState == 0)
  b.LeftMotorSignal = b.ForwardMotorSignal;
  b.RightMotorSignal = b.ForwardMotorSignal;
  
  timeDiff = time - b.TimePoint;
  if (timeDiff >= 3)
    b.CurrentState = 1;
    b.TimePoint = time;
  end
  
elseif (b.CurrentState == 1)
  
  if (~b.FoundCylinder)
    b.LeftMotorSignal = -b.TurnMotorSignal;
    b.RightMotorSignal = b.TurnMotorSignal;
    sonarReading = robot.RayBasedSensors(1).RayLengths(2);
    if (sonarReading ~= -1)
      if (~b.SonarReading)
        b.SonarReading = 1;
        b.NumberOfSonarReadings = time/0.01;
      end
    else
      if (b.SonarReading)
        b.SonarReading = 0;
        b.FoundCylinder = 1;
        b.NumberOfSonarReadings = time/0.01 - b.NumberOfSonarReadings;
        b.LeftMotorSignal = 0;
        b.RightMotorSignal = 0;
        disp('Found Cylinder!')
      else
        timeDiff = time - b.TimePoint;
        if (timeDiff >= b.OneLapTime)
          b.CurrentState = 0;
          b.TimePoint = time;
        end
      end
    end
    
    
  else
    if (b.Steps <= b.NumberOfSonarReadings*2)
      b.LeftMotorSignal = b.TurnMotorSignal;
      b.RightMotorSignal = -b.TurnMotorSignal;
      b.Steps = b.Steps + 1;
    else
      b.CurrentState = 2;
    end
  end
  
  
elseif (b.CurrentState == 2)
  
  b.LeftMotorSignal = b.ForwardMotorSignal;
  b.RightMotorSignal = b.ForwardMotorSignal;
  
  leftIRReading = robot.RayBasedSensors(2).Reading;
  rightIRReading = robot.RayBasedSensors(3).Reading;
  
  if (leftIRReading > rightIRReading)
    b.LeftMotorSignal = 0;
  elseif (leftIRReading < rightIRReading)
    b.RightMotorSignal = 0;
  end
  
  
end




