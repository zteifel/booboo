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
close all;
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
% Arena walls
arenaObject1 = CreateArenaObject('arenaObject1',[[-5.0 -5.0]; [-4.8 -5.0]; [-4.8 5.0]; [-5.0 5.0]]);
arenaObject2 = CreateArenaObject('arenaObject2',[[-4.8 -5.0]; [4.8 -5.0]; [4.8 -4.8]; [-4.8 -4.8]]);
arenaObject3 = CreateArenaObject('arenaObject3',[[5.0 -5.0]; [4.8 -5.0]; [4.8 5.0]; [5.0 5.0]]);
arenaObject4 = CreateArenaObject('arenaObject4',[[-4.8 5.0]; [4.8 5.0]; [4.8 4.8]; [-4.8 4.8]]);

% Cylinders
cylinderRadius = 0.15;
arenaObject5 = CreateArenaObject('arenaObject5',cylinderRadius*[cos(linspace(0,2*pi,50)); sin(linspace(0,2*pi,50))]');

testArena = CreateArena('arena',arenaSize,[arenaObject1; arenaObject2;...
                                           arenaObject3; arenaObject4;...
                                           arenaObject5]);

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
numberOfRays = 3;
openingAngle = 52.6/180*pi; 
range = 1.0;
sigma = 0.001;
lrfSensor = CreateLRF('lrfSensor',size,numberOfRays,openingAngle,range,sigma);

%%%%%%%%%%%%%%%%%%%%
% IR sensors
%%%%%%%%%%%%%%%%%%%
sensor1RelativeAngle = 0.7854;
sensor2RelativeAngle = -0.7854;
size = 0.0500;
numberOfRays = 3;
openingAngle = 2.300;
range = 0.4;
c1 = 0.0300;
c2 = 0.1000;
sigma = 0.0200;
sensor1 = CreateIRSensor('sensor1',sensor1RelativeAngle,size,...
                          numberOfRays,openingAngle,range,c1,c2,sigma);
sensor2 = CreateIRSensor('sensor2',sensor2RelativeAngle,size,...
                          numberOfRays,openingAngle,range,c1,c2,sigma);

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
                       [lrfSensor sensor1 sensor2],[leftMotor rightMotor],odometer,[],brain);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Miscellaneous simulation parameters
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
showPlot = true;
plotStep = 10;
recordResults = true;
testRobot.ShowSensorRays = true;
testRobot.ShowOdometricGhost = false;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Initialization:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

position = [-3.2000 0.0000];
heading = pi/8;
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

maxSteps = 10000;
dt = 0.01;
time = 0.0;
collided = false;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Main loop:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
halfLap = 0;
i=1;
while ((i < maxSteps) & (~collided))
   testRobot.RayBasedSensors = GetRayBasedSensorReadings(testRobot,testArena);
%    if (~isempty(testRobot.Odometer))
%     testRobot.Odometer = GetOdometerReading(testRobot,dt);
%    end 
%    if (~isempty(testRobot.Compass))
%     testRobot.Compass = GetCompassReading(testRobot,dt);
%    end  
   testRobot.Brain = BrainStep(testRobot, time);
   testRobot = MoveRobot(testRobot,dt);

   time = i*dt;
   if (recordResults)
    motionResults = AddMotionResults(motionResults,time,testRobot); 
   end
   
%    if ((halfLap == 1) && (motionResults.Heading(end) > 0))
%      break
%    end
%    
%    if (motionResults.Heading(end) < 0)
%      halfLap = 1;
%    end
     

   i = i + 1;

   collided = CheckForCollisions(testArena, testRobot);

   if ((mod(i,plotStep)==0) && showPlot)
    ShowRobot(plotHandle,testRobot);
   end
end
