function b = BrainStep(robot, time);

b = robot.Brain;

%%%%%%%%%%%%%%%% FSM: %%%%%%%%%%%%%%%%%%%%
if (b.CurrentState == 0) % Forward motion
 b.LeftMotorSignal = b.ForwardMotorSignal;
 b.RightMotorSignal = b.ForwardMotorSignal;
end


