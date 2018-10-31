clc;
clear;
%==============================================
% ��ȡCMR��ʽ�궨���
param = zeros(6,1);
fid = fopen('./data/campar.cmr', 'r');
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
%==============================================
% �����ؽ�
fpointcloud = fopen('.\pointcloud\pointcloud03.asc', 'w');
Depth = load('.\data\d03.txt');
% M���� N����
[M, N] = size(Depth);
X = zeros(480*640, 3);    %�ؽ�����ά������
for j = 1 : M
  for i = 1 : N
    z = Depth(j,i);
    x = (i - param(5)) * z / param(3);
    y = (j - param(6)) * z / param(4);
    X(j*N+i,3) = z;
    X(j*N+i,2) = y;
    X(j*N+i,1) = x;
    if z < 2000
      fprintf(fpointcloud, '%f  %f  %f\r\n', x, y, z);
    end
  end
end
fclose(fpointcloud);