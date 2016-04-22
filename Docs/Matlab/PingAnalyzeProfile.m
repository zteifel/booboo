rho = [311 311 311 311 312 312 312 64 65 41 41 42 63 64 65 311 312 312 312 312 312 312 312 311 311 312 312 312 312 312 312 311 311 311 311 311 311 311 311 311 311 311 311 311 311 312 312 312 312 312];

index = linspace(1,size(rho,2),size(rho,2));

data = [index; rho];
dataLen = size(data,2);

prevIndex = @(i, len) mod(i-2, len)+1;
nextIndex = @(i, len) mod(i, len)+1;

sortedData = sortrows(data',2)';

nearestIndex = sortedData(1,1);
leftIndex = prevIndex(nearestIndex, dataLen);
rightIndex = nextIndex(nearestIndex, dataLen);
length = 0;

while abs( data(2,leftIndex) - data(2,nearestIndex) ) < 5 % Alternatively: use derivative
    leftIndex = prevIndex(leftIndex, dataLen);
    length = length + 1;
end

while abs( data(2,rightIndex) - data(2,nearestIndex) ) < 5 % Alternatively: use derivative
    rightIndex = nextIndex(rightIndex, dataLen);
    length = length + 1;
end

meanIndex = mod(round(leftIndex + length/2), dataLen)+1;

clf
hold on
plot(data(1,:), data(2,:), '-*')
plot(meanIndex, 0, '*')
