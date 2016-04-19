function b = CreateBrain;

%% Variables:

leftMotorSignal = 0;
rightMotorSignal = 0;
currentState = 0;
previousState = 0;
speedRatio = 1;

%% Parameters:

forwardMotorSignal = 0.8;
rotateMotorSignal = 0.6;
approachMotorSignal = 0.55;
sensorTarget = 0.2;
positionErr = 0.045;
angleErr = 0.1;

b = struct('LeftMotorSignal',leftMotorSignal,...
           'RightMotorSignal',rightMotorSignal,...
           'CurrentState',currentState, ...
           'PreviousState', previousState, ...
           'ForwardMotorSignal', forwardMotorSignal, ...
           'RotateMotorSignal', rotateMotorSignal, ...
           'SensorTarget', sensorTarget, ...
           'PositionErr', positionErr, ...
           'AngleErr', angleErr);
