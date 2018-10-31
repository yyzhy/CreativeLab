clc;
clear;
% 验证Dr.REN库导出的全局点精度
% 乔根转台拍摄的IR图,用Dr.Ren标定库计算的外参数
% 第一个状态时的相机外参数
R0 = [[0.0494727219122, 0.969851248483, 0.238623145572];...
      [-0.0127454968202, 0.239509294177, -0.970810409047];...
      [-0.998694148425, 0.0449872628531, 0.0242104127098]];
T0 = [-391.053145708; 1001.30050159; 1022.46014578];
% 第二个状态时的相机外参数
R1 = [[0.0592721305579, 0.996806610454, 0.0535107082248];...
      [-0.0135697029008, 0.054404563514, -0.998426765783];...
      [-0.998149626911, 0.0584527572014, 0.0167510439449]];
T1 = [-34.5042159498;  1071.01894536;  1035.75220292];

% 导入摄影测量的全局点坐标
ExtPoint = load('./data12/extPoints.asc');
[MExt, NExt] = size(ExtPoint);

% 导入相机坐标系下重建的标志点坐标
C_Data0 = load('./data12/0-PointList00.txt');
C_Data1 = load('./data12/1-PointList01.txt');
X_C0 = C_Data0(:,2:4);
X_C1 = C_Data1(:,2:4);
[M0, N0] = size(X_C0);
[M1, N1] = size(X_C0);

% 计算第一个状态时全局点误差
err0 = zeros(M0,5);
for j = 1 : M0
  % Dr.Ren标定库里的R是左乘的
  % W = RC + T
  XW = R0 * X_C0(j,:)' + T0;
  iId = C_Data0(j,1);
  for k = 1 : MExt
    if iId == ExtPoint(k,1)
      XW_Ext = ExtPoint(k,2:4);
      e = XW' - XW_Ext;
      err0(j,1) = iId;
      err0(j,2:4) = e;
      err0(j,5) = sqrt(dot(e,e'));
      clear e;
    end
  end
end

% 计算第二个状态时全局点误差
err1 = zeros(M1,5);
for j = 1 : M1
  % Dr.Ren标定库里的R是左乘的
  % W = RC + T
  XW = R1 * X_C1(j,:)' + T1;
  iId = C_Data1(j,1);
  for k = 1 : MExt
    if iId == ExtPoint(k,1)
      XW_Ext = ExtPoint(k,2:4);
      e = XW' - XW_Ext;
      err1(j,1) = iId;
      err1(j,2:4) = e;
      err1(j,5) = sqrt(dot(e,e'));
      clear e;
    end
  end
end

x0 = err0(:,1);
plot(x0, err0(:,5),'ro--');
hold on;
x1 = err1(:,1);
plot(x1, err1(:,5),'bx--');

