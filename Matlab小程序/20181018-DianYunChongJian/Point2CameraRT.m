clc;
clear;
% 将相机坐标系点云换回世界坐标系
% 乔根转台拍摄的IR图,用Dr.Ren标定库计算的外参数
% DP图外参
% 第一个状态时的相机外参数
% R0 = [[0.0494727219122, 0.969851248483, 0.238623145572];...
%       [-0.0127454968202, 0.239509294177, -0.970810409047];...
%       [-0.998694148425, 0.0449872628531, 0.0242104127098]];
% T0 = [-391.053145708; 1001.30050159; 1022.46014578];
% 第二个状态时的相机外参数
% R1 = [[0.0592721305579, 0.996806610454, 0.0535107082248];...
%       [-0.0135697029008, 0.054404563514, -0.998426765783];...
%       [-0.998149626911, 0.0584527572014, 0.0167510439449]];
% T1 = [-34.5042159498;  1071.01894536;  1035.75220292];

% IR图外参
% 第一个状态时的相机外参数
R0 = [[0.0520242351365,  -0.996237794669,  -0.0693089852177];...
      [-0.00106228008242,  -0.0694581356953,  0.997584301674];...
      [-0.998645257596,  -0.0518249347242,  -0.00467178995018]];
T0 = [-208.303945998;   1030.0946286;     1045.16871407];
% 第二个状态时的相机外参数
R1 = [[0.0521452321004,  -0.969268041272,  -0.240417010501];...
      [-0.000785283287561,  -0.240784264707,  0.970578343669];...
      [-0.998639203166,  -0.0504222375419,  -0.0133169013632]];
T1 = [-238.521015068   1023.4685633     1043.73627552];

%RC = R0' * R1;
%TC = R0' * (T1-T0);

iFrameIndex = 1;
filename1 = ['./pointcloud/pointcloud0', num2str(iFrameIndex),'.asc'];
PTC = load(filename1);
[M, N] = size(PTC);
filenameW = ['./pointcloud/World-pointcloud0', num2str(iFrameIndex),'.asc'];
fid = fopen(filenameW, 'w');
for j = 1 : M
    % 重建出来的点
    XC = PTC(j,1:3);
    % 从相机坐标系换算回世界坐标系
    % W = R * C + T
    XW = R1 * XC' + T1;
    fprintf(fid, '%f  %f  %f\n', XW(1,1), XW(2,1), XW(3,1));
end
fclose(fid);