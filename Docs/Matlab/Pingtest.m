%% Plot stuff
% 6
%rho = [ 311 311 311 311 312 312 312 312 312 311 27 23 23 23 24 27 39 27 27 25 25 25 26 27 27 312 312 312 292 291 290 290 290 291 293 312 312 311 312 312 312 312 312 311 311 311 311 311 311 311];
%rho = [311 311 311 311 312 312 312 312 312 311 311 43 42 43 44 311 311 311 311 45 44 44 44 43 44 45 47 311 311 276 272 271 269 269 269 270 271 312 312 312 311 311 311 311 311 311 311 311 311 311];
%rho = [311 311 311 311 312 312 312 312 312 311 311 65 312 312 312 312 312 64 62 61 61 60 60 61 62 63 311 260 257 250 248 247 247 247 248 33 33 312 312 312 312 311 311 311 311 311 311 311 312 312];

%4
%rho = [202 202 203 311 311 312 312 312 312 312 311 311 311 311 311 311 265 263 263 264 264 264 296 297 300 311 311 311 311 311 311 311 311 311 312 312 312 312 312 311 311 205 203 202 200 201 200 200 201 201];

%5
%rho = [ 311 311 311 311 312 312 312 312 312 23 22 21 21 23 45 46 311 311 311 311 311 311 311 311 213 312 312 311 311 311 311 311 311 311 312 312 312 312 312 312 312 311 311 311 312 312 312 312 312 311];
rho = [311 311 311 311 312 312 312 64 65 41 41 42 63 64 65 311 312 312 312 312 312 312 312 311 311 312 312 312 312 312 312 311 311 311 311 311 311 311 311 311 311 311 311 311 311 312 312 312 312 312];

%theta = linspace(0, 2*pi, length(rho));
%plot(theta, rho,'-*')

%% Begin to filter

theta = linspace(0, 2*pi, length(rho));

% Merge data
data = [theta; rho];

% Compute differential
diffData = zeros(size(data(1,:)));
diffData(1) = data(2,1) - data(2,end);
for i=2:size(data,2)
    diffData(i) = data(2,i) - data(2,i-1);
end

% Filter distance threshold
i = 1;
while i <= size(data,2)
    if data(2,i) > 100
        data(:,i) = [];
        diffData(i) = [];
        i = i - 1;
    end
    i = i + 1;
end

% Filter absolute difference threshold
s = size(diffData,2);
threshDiffData = [linspace(1,s,s); diffData];
i = 1;
while i <= size(threshDiffData,2)
    if abs(threshDiffData(2,i)) < 15
        threshDiffData(:,i) = [];
        i = i - 1;
    end
    i = i + 1;
end

% Plot
clf
hold on
plot(data(1,:), data(2,:),'-*')
plot(data(1,:), diffData,'-*')
plot(data(1,threshDiffData(1,:)), threshDiffData(2,:),'o')
plot(data(1,:), zeros(size(data(1,:))),'-k')
