clc;
clear;
% ͨ��С��ı궨�������֤������ȫ�ֵ��Ƿ�׼ȷ
% С��궨���
% QiaoGen�궨��R���ҳ˾���
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

%��һ��λ��ʱ�궨���ϵ������
X0 = load('.\data\qPOINT0.txt');
%X0 = load('.\data\PointList00.txt');
%�ڶ���λ��ʱ�궨���ϵ������
X1 = load('.\data\qPOINT1.txt');
%X1 = load('.\data\PointList01.txt');
%�ѵ�ת��ת������ϵ 
for i = 1 : 9
  pt0 = X0(i,:);
  pt1 = X1(i,:);
  pt0_R = (pt0 * R + T');
  pt1_R = (pt1 * R + T') * Rx;
  err = pt0_R - pt1_R;
  disp(num2str(sqrt(dot(err,err'))));
end

