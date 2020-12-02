% MATLAB Code to find peaks for every 5000 cycles of durability test
% Written by Marisa Lim

% Loading file - opens a window for user to select .txt file

clc
clear

%[name, path] = uigetfile('*.txt', 'Select file to open');
% 
%file = [path, name];

% Load data
%data = load(file);
%csvwrite(file, data); % To remove any headerlines and get the first column
filename1 = '_nrp finger 42113 cycles.txt';
fileID1 = fopen(filename1);
data1 = textscan(fileID1, '%f %f');
fclose(fileID1);
x1(:,1) = data1{:,1};% c: cycle vector
x1(:,2) = data1{:,2};% x: pressure data in kPa

filename2 = '_nrp finger 11137 cycles_.txt';
fileID2 = fopen(filename2);
data2 = textscan(fileID2, '%f %f');
fclose(fileID2);
x2(:,1) = data2{:,1}+42113+1;% c: cycle vector
x2(:,2) = data2{:,2};

filename3 = '_nrp finger 14959 cycles_.txt';
fileID3 = fopen(filename3);
data3 = textscan(fileID3, '%f %f');
fclose(fileID3);
x3(:,1) = data3{:,1}+42113+11137+2; % c: cycle vector
x3(:,2) = data3{:,2};% x: pressure data in kPa

filename4 = '_nrp finger 3103 cycles_.txt';
fileID4 = fopen(filename4);
data4 = textscan(fileID4, '%f %f');
fclose(fileID4);
x4(:,1) = data4{:,1}+42113+11137+14959+3; % c: cycle vector
x4(:,2) = data4{:,2};% x: pressure data in kPa

x = cat(1, x1, x2, x3, x4);

last_cycle = x(end,1);
n_cycles = fix(last_cycle/5000) + 1; % number of cycles we are interested in (floor division)

% Create an array with only the cycles and time instants we are interested in
for i = 1:n_cycles % loop through the cycle array
    [index, cycle] = find(x(:,1) == (1+5000*(i-1)));
    final((1+500*(i-1) : (1+500*(i-1)+499)), 2) = x((index(1):index(500)), 2);
end

plot(final, 'b');

% % Find peaks
% [pks, locs] = findpeaks(final(:,2));
