function [R,T] = loadRT(filename)
%LOADRT Summary of this function goes here
%   Detailed explanation goes here
fid = fopen(filename, 'r');
lines = textscan(fid, '%s','delimiter', '\n');
base = 0;
% ��ȡ��ת����R
R=zeros(3,3);
line = lines{1}{base + 1};
lineData = sscanf(line,'%f',[1 3]);
R(1,:)=lineData;
line = lines{1}{base + 2};
lineData = sscanf(line,'%f',[1 3]);
R(2,:)=lineData;
line = lines{1}{base + 3};
lineData = sscanf(line,'%f',[1 3]);
R(3,:)=lineData;
% ��ȡƽ��ʸ��T
line = lines{1}{base + 4};
lineData = sscanf(line,'%f',[1 3]);
T=lineData';
fclose(fid);
end

