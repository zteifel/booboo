function b = BrainStep(robot, time);

b = robot.Brain;

wheelAwayFromWall = @(g,r) (r < g) + (2/(g-1)*(r-1)-1)*(r >= g);
wheelTowardsWall = @(g,r) (r < g)*(2*r/g-1) + (r >= g);

leftRay = robot.RayBasedSensors(1).Reading;
rightRay = robot.RayBasedSensors(2).Reading;

tmpState = b.CurrentState;

if b.CurrentState == 0 % Looking for a wall

  if rightRay > 0 || leftRay > 0
    b.CurrentState = 1;
  else
    b.LeftMotorSignal = b.ForwardMotorSignal;
    b.RightMotorSignal = b.ForwardMotorSignal;
  end

elseif b.CurrentState == 1 % Start alignment with wall.

  if rightRay > b.SensorTarget || leftRay > b.SensorTarget
    if rightRay >= leftRay
      b.CurrentState = 2;
    else
      b.CurrentState = 3;
    end
  elseif leftRay == 0 || rightRay == 0
    b.CurrentState = 0;
  else
    if rightRay >= leftRay
      b.LeftMotorSignal = b.RotateMotorSignal;
      b.RightMotorSignal = b.ForwardMotorSignal;
    else
      b.LeftMotorSignal = b.ForwardMotorSignal;
      b.RightMotorSignal = b.RotateMotorSignal;
    end
  end

elseif b.CurrentState == 2 % Following wall to the right

  if leftRay == 0 && rightRay == 0
    b.CurrentState = 0;
  elseif abs(leftRay-rightRay) < b.PositionErr
    b.CurrentState = 4;
  else
    if leftRay > 0
      b.LeftMotorSignal = ...
        wheelAwayFromWall(b.SensorTarget,rightRay)*b.RotateMotorSignal;
      b.RightMotorSignal = ...
        wheelTowardsWall(b.SensorTarget,rightRay)*b.RotateMotorSignal;
    else
      b.LeftMotorSignal = ...
        wheelAwayFromWall(b.SensorTarget,rightRay)*b.ForwardMotorSignal;
      b.RightMotorSignal = ...
        wheelTowardsWall(b.SensorTarget,rightRay)*b.ForwardMotorSignal;
    end
  end

elseif b.CurrentState == 3 % Follow wall to the left

  if leftRay == 0 && rightRay == 0
    b.CurrentState = 0;
  elseif abs(leftRay - rightRay) < b.PositionErr
    b.CurrentState = 4;
  else
    if rightRay > 0
      b.LeftMotorSignal = ...
        wheelTowardsWall(b.SensorTarget,leftRay)*b.RotateMotorSignal;
      b.RightMotorSignal = ...
        wheelAwayFromWall(b.SensorTarget,leftRay)*b.RotateMotorSignal;
    else
      b.LeftMotorSignal = ...
        wheelTowardsWall(b.SensorTarget,leftRay)*b.ForwardMotorSignal;
      b.RightMotorSignal = ...
        wheelAwayFromWall(b.SensorTarget,leftRay)*b.ForwardMotorSignal;
    end
  end

elseif b.CurrentState == 4 % In corner, adjust heading

  notWithinWallAlignRange = ...
    leftRay > b.SensorTarget + b.PositionErr && ...
    rightRay > b.SensorTarget + b.PositionErr;
  withinCornerAngleRange = abs(leftRay-rightRay) < b.AngleErr;

  if b.PreviousState == 4 && notWithinWallAlignRange && withinCornerAngleRange
    b.LeftMotorSignal = 0;
    b.RightMotorSignal = 0;
    b.CurrentState = 5;
  elseif b.PreviousState == 2 % Rotate right
    b.LeftMotorSignal = b.RotateMotorSignal;
    b.RightMotorSignal = -b.RotateMotorSignal;
  elseif b.PreviousState == 3 % Rotate Left
    b.LeftMotorSignal = -b.RotateMotorSignal;
    b.RightMotorSignal = b.RotateMotorSignal;
  end

end

b.PreviousState = tmpState;
