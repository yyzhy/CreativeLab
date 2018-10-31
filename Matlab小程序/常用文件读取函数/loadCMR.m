function [R,T] = loadCMR(filename)
%LOADCMR Summary of this function goes here
%   Detailed explanation goes here
%   ��ȡCMR��ʽ�궨���
param = zeros(6,1);
fid = fopen(filename, 'r');
lines = textscan(fid, '%s','delimiter', '\n');
base = 0;
% ��ȡ10���ڲ���
% param(3)=����   param(4)=����  param(5)=x/2+dx   param(6)=y/2-dy
line = lines{1}{base+2};    % ��ȡ�ڶ�������
lineData = sscanf(line, '%f', [1 10]);
param(3)=lineData(1);param(4)=lineData(1);param(5)=320+lineData(2);param(6)=240-lineData(3);
% ��ȡƽ��ʸ��T
line = lines{1}{base + 3};
lineData = sscanf(line,'%f',[1 3]);
T=lineData';
% ��ȡ��ת����R
R=zeros(3,3);
line = lines{1}{base + 4};
lineData = sscanf(line,'%f',[1 3]);
R(1,:)=lineData;
line = lines{1}{base + 5};
lineData = sscanf(line,'%f',[1 3]);
R(2,:)=lineData;
line = lines{1}{base + 6};
lineData = sscanf(line,'%f',[1 3]);
R(3,:)=lineData;
fclose(fid);
end

