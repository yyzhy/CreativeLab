clc;
clear;
% 通过小球的标定结果，验证导出的全局点是否准确
% 小球标定结果
% QiaoGen标定的R是右乘矩阵
R = [[0.999987, 0.0015626, 0.00494834];...
      [-0.00239816, 0.984805, 0.173648];...
      [-0.00460181, -0.173657, 0.984795]];
T = [0; -11.9991; -183.609];
Rx = zeros(3,3);
ax = 10 * pi / 180;
Rx(1,1) = 1;
Rx(2,2) = cos(ax);
Rx(2,3) = sin(ax);
Rx(3,2) = -sin(ax);
Rx(3,3) = cos(ax);

%第一个位置时标定板上点的坐标
X0 = load('.\data\qPOINT0.txt');
%X0 = load('.\data\PointList00.txt');
%第二个位置时标定板上点的坐标
X1 = load('.\data\qPOINT1.txt');
%X1 = load('.\data\PointList01.txt');
%把点转到转轴坐标系 
for i = 1 : 9
  pt0 = X0(i,:);
  pt1 = X1(i,:);
  pt0_R = (pt0 * R + T');
  pt1_R = (pt1 * R + T') * Rx;
  err = pt0_R - pt1_R;
  disp(num2str(sqrt(dot(err,err'))));
end

