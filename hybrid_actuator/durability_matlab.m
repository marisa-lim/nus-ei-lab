% MATLAB Code to find peaks for every 5000 cycles of durability test
% Written by Marisa Lim

% Loading file - opens a window for user to select .txt file

clc
clear

[name, path] = uigetfile('*.txt', 'Select file to open');

file = [path, name];

% Load data
data = textread(file, '%f', 'headerlines', 1); % To remove any headerlines and get the first column
% x: pressure data in kPa
x = data(2:2:end);
% c: cycle vector
c = data(1:2:end);

fz = %sampling frequency
T = 1/fz %sampling period
% t: time vector (conversion from cycle to time instant)
dur = %full duration of experiment in seconds
t = linspace(0, dur, T) % t array should be same length as the c array

% To see full plot of data
% plot(c, x, 'b');

% Loop to find peak in every 5000th cycle starting from cycle 1
last_cycle = t(end);
n_cycles = fix(last_cycle/5000) % number of cycles we are interested in (floor division)

% Each cycle is 6 second: 3 seconds valve on, 3 seconds valve off
n_rows = n_cycles * (6/T) % number of rows expected in final array
cycle_arr = ones(n_rows, 2) % only 2 columns - [t,x]

% Create an array with only the cycles and time instants we are interested in
for i = 0:length(c) % loop through the cycle array
  if c(i) == 1 % if within first cycle
    cycle_arr(i,0) = t(i); % first column is corresponding time instant
    cycle_arr(i,1) = x(i); % second column is corresponding pressure value
  elseif mod(c(i)/5000) == 0 % if within every 5000th cycle
    cycle_arr(i,0) = t(i); % first column is corresponding time instant
    cycle_arr(i,1) = x(i); % second column is corresponding pressure value
  end
end

% Print the cycle_arr
disp(cycle_arr);

% Find peaks
[pks,locs] = findpeaks(cycle_arr);
% Plot graph showing peaks
x_axis = cycle_arr(:,0)
y_axis = cycle_arr(:,1)
plot(t,y_axis,t(locs),pks,'or')
xlabel('Time (s)')
ylabel('Pressure (kPa)')
