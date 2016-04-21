%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% TestRunRobot: a sample program, illustrating the use
% of the ARSim functions (v1.1.9)
%
% (c) Mattias Wahde, 2006, 2007, 2011
%
% Send bug reports to: mattias.wahde@chalmers.se
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear all;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Add ARSim to the search path:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if strcmp(computer,'PCWIN')
  path(path,'.\RobotFunctions');
  path(path,'.\ResultFunctions');
  path(path,'.\PlotFunctions');
  path(path,'.\ArenaFunctions');
else
  path(path,'./RobotFunctions');
  path(path,'./ResultFunctions');
  path(path,'./PlotFunctions');
  path(path,'./ArenaFunctions');
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Generate arena:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
arenaSize = [-5 5 -5 5]; 
arenaObject1 = CreateArenaObject('arenaObject1',[[1 1.5]; [1 0.7]; [1.9 0.7]; [1.9 1.5]]);
arenaObject2 = CreateArenaObject('arenaObject2',[[-5.0 -5.0]; [-4.8 -5.0]; [-4.8 5.0]; [-5.0 5.0]]);
arenaObject3 = CreateArenaObject('arenaObject3',[[-4.8 -5.0]; [4.8 -5.0]; [4.8 -4.8]; [-4.8 -4.8]]);
arenaObject4 = CreateArenaObject('arenaObject4',[[5.0 -5.0]; [4.8 -5.0]; [4.8 5.0]; [5.0 5.0]]);
arenaObject5 = CreateArenaObject('arenaObject5',[[-4.8 5.0]; [4.8 5.0]; [4.8 4.8]; [-4.8 4.8]]);
arenaObject6 = CreateArenaObject('arenaObject6',[[2 -2]; [2 -1.5]; [3 -1.5]; [3 -2]]);
arenaObject7 = CreateArenaObject('arenaObject7',[[-3 -2]; [-3 -1.5]; [-2.5 -1.5]; [-2.5 -2]]);
arenaObject8 = CreateArenaObject('arenaObject8',[[-2 1.5]; [-2 3]; [-1.5 3]; [-1.5 1.5]]);
testArena = CreateArena('arena',arenaSize,[arenaObject1; arenaObject2; arenaObject3;...
                                           arenaObject4; arenaObject5; arenaObject6;...
                                           arenaObject7; arenaObject8]);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Generate robot:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%
% Brain:
%%%%%%%%%%%%%%%%%%
brain = CreateBrain;

%%%%%%%%%%%%%%%%%%
% LRF:
%%%%%%%%%%%%%%%%%%
size = 0.0500;
numberOfRays = 15;
openingAngle = 3.1415926535;
range = 4.0000;
sigma = 0.001;
lrfSensor = CreateLRF('lrfSensor',size,numberOfRays,openingAngle,range,sigma);

%%%%%%%%%%%%%%%%%%%%
% Odometer:
%%%%%%%%%%%%%%%%%%%%
sigma = 0.00025;     % Measures the odometric drift
odometer = CreateOdometer('odometer',sigma);

%%%%%%%%%%%%%%%%%%%%
% Motors:
%%%%%%%%%%%%%%%%%%%%
leftMotor = CreateMotor('leftMotor');
rightMotor = CreateMotor('rightMotor');
mass = 3.0000;
momentOfInertia = 0.2000;
radius = 0.2000;
wheelRadius = 0.1000;

%% Robot with LRF and odometer:
   testRobot = CreateRobot('TestRobot',mass,momentOfInertia,radius,wheelRadius, ...
                       [lrfSensor],[leftMotor rightMotor],odometer,[],brain);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Miscellaneous simulation parameters
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
showPlot = true;
plotStep = 10;
recordResults = true;
testRobot.ShowSensorRays = true;
testRobot.ShowOdometricGhost = true;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Initialization:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

position = [-3.2000 0.0000];
heading = 0.0000;
velocity = [0.0000 0.0000];
angularSpeed = 0.0000;

testRobot = SetPositionAndVelocity(testRobot, position, heading, velocity, angularSpeed);
if (~isempty(testRobot.Odometer))
 testRobot.Odometer = CalibrateOdometer(testRobot);
end

if (showPlot)
 plotHandle = InitializePlot(testRobot, testArena);
end
if (recordResults)
 motionResults = InitializeMotionResults(testRobot);
end

maxSteps = 2500;
dt = 0.01;
time = 0.0;
collided = false;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Main loop:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

i=1;
while ((i < maxSteps) & (~collided))
   testRobot.RayBasedSensors = GetRayBasedSensorReadings(testRobot,testArena);
   if (~isempty(testRobot.Odometer))
    testRobot.Odometer = GetOdometerReading(testRobot,dt);
   end 
   if (~isempty(testRobot.Compass))
    testRobot.Compass = GetCompassReading(testRobot,dt);
   end  
   testRobot.Brain = BrainStep(testRobot, time);
   testRobot = MoveRobot(testRobot,dt);

   time = i*dt;
   if (recordResults)
    motionResults = AddMotionResults(motionResults,time,testRobot); 
   end

   i = i + 1;

   collided = CheckForCollisions(testArena, testRobot);

   if ((mod(i,plotStep)==0) && showPlot)
    ShowRobot(plotHandle,testRobot);
   end
end
