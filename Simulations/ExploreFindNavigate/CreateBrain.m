function b = CreateBrain;

%% ADD CODE BELOW:


%% Variables:

leftMotorSignal = 0;
rightMotorSignal = 0;
currentState = 0;

%% Parameters:



b = struct('LeftMotorSignal',leftMotorSignal,...
           'RightMotorSignal',rightMotorSignal,...
           'CurrentState',currentState);