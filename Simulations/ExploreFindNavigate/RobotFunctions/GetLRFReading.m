function s = GetLRFReading(sensor,arena);

s = sensor;

%% Find ray readings:
x = s.Position(1);
y = s.Position(2);
deltaGamma = s.OpeningAngle/(s.NumberOfRays-1);
for i = 1:s.NumberOfRays
 beta = s.AbsoluteAngle - 0.5*s.OpeningAngle + (i-1)*deltaGamma;
 if (beta < -pi)
  beta = beta + 2*pi;
 elseif (beta > pi)
  beta = beta - 2*pi;
 end
 s.RayDirections(i) = beta;
 distance = GetDistanceToNearestObject(beta, x, y, arena);
 if (distance < s.Range) 
   errorFreeReading = distance;
   noisyReading = errorFreeReading*(1 + randn*s.Sigma);
   if (noisyReading < 0.0)
    s.RayLengths(i) = 0.0
   elseif (noisyReading > s.Range)
    s.RayLengths(i) = s.Range;
   else
    s.RayLengths(i) = noisyReading;
   end
 else
   s.RayLengths(i) = -1;
 end

s.Reading = 0.0; % not used.
 
end
