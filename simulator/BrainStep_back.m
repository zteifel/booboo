function b = BrainStep(robot, time);

b = robot.Brain;

rayGoal = 0.3;
err = 0.05;
corner_err = 0.02;

fastWheel = @(g,r) (r < g) + (2/(rayGoal-1)*(leftRay-1)-1)*(r >= g);
slowWheel = @(g,r) (r < g)*(2/(rayGoal-1)*(rightRay-1)-1) + (g >= rayGoal);

leftRay = robot.RayBasedSensors(1).Reading;
rightRay = robot.RayBasedSensors(2).Reading;
tmpState = b.CurrentState;

if b.CurrentState == 0 % Looking for wall
  if rightRay >= rayGoal+0.05 || leftRay >= rayGoal+0.05
    if rightRay >= leftRay
      b.CurrentState = 1;
    else
      b.CurrentState = 2;
    end
    b.LeftMotorSignal = 0;
    b.RightMotorSignal = 0;
  else
    b.LeftMotorSignal = b.ForwardMotorSignal;
    b.RightMotorSignal = b.ForwardMotorSignal;
  end
elseif b.CurrentState == 1 % Following wall to the right
  if leftRay == 0 && rightRay == 0
    b.CurrentState = 0;
  elseif abs(leftRay - rayGoal) < err && abs(rightRay - rayGoal) < err
    b.CurrentState = 3;
    b.LeftMotorSignal = 0;
    b.RightMotorSignal = 0;
  else
    % Turn Left
    if rightRay > rayGoal
      b.LeftMotorSignal = (2/(rayGoal-1)*(rightRay-1)-1)*b.ForwardMotorSignal;
      b.RightMotorSignal = 1*b.ForwardMotorSignal;
    % Turn Right;
    else
      b.LeftMotorSignal = b.ForwardMotorSignal;
      b.RightMotorSignal = (2*rightRay/rayGoal-1)*b.ForwardMotorSignal;
    end
  end
elseif b.CurrentState == 2 % Follow wall to the left
  if leftRay == 0 && rightRay == 0
    b.CurrentState = 0;
  elseif abs(leftRay - rayGoal) < err && abs(rightRay - rayGoal) < err
    b.CurrentState = 3;
    b.LeftMotorSignal = 0;
    b.RightMotorSignal = 0;
  else
    % Turn Right
    if leftRay > rayGoal
      b.LeftMotorSignal = 1*b.ForwardMotorSignal;
      b.RightMotorSignal = (2/(rayGoal-1)*(leftRay-1)-1)*b.ForwardMotorSignal;
    % Turn Left
    else
      b.LeftMotorSignal =  (2*leftRay/rayGoal-1)*b.ForwardMotorSignal;
      b.RightMotorSignal = b.ForwardMotorSignal;
    end
  end
elseif b.CurrentState == 3
  rayGoal = (rayGoal+robot.Radius)*cos(robot.RayBasedSensors(1).RelativeAngle);
  if b.PreviousState == 3 && ...
      abs(rightRay-rayGoal) < corner_err && ...
        abs(leftRay-rayGoal) < corner_err
    b.LeftMotorSignal = 0;
    b.RightMotorSignal = 0;
    b.CurrentState = 4;
  elseif b.PreviousState == 1 % Rotate right
    b.LeftMotorSignal = b.RotateMotorSignal;
    b.RightMotorSignal = -b.RotateMotorSignal;
    b.LeftMotorSignal
  elseif b.PreviousState == 2 % Rotate Left
    b.LeftMotorSignal = -b.RotateMotorSignal;
    b.RightMotorSignal = b.RotateMotorSignal;
  elseif b.PreviousState == 3
  end
elseif b.CurrentState == 4
  if b.PreviousState == 3
    disp('I am in the corner!')
  end
end

b.PreviousState = tmpState;
