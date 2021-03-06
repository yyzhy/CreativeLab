clc;
clear;
% 求解RT矩阵
% PT1
PT1 = [[-653.507538 381.212730 4064.000000];
       [-720.050251 617.185930 4094.000000];
       [-514.447236 624.195980 4095.000000];
       [-342.989950 672.529313 4015.000000];
       [-506.666667 1133.333333 3980.000000]];
% PT2
PT2 = [[-588.306533 371.917923 4037.000000];
       [-659.177554 604.812395 4057.000000];
       [-447.628141 617.184255 4049.000000];
       [-267.336683 668.341709 3990.000000];
       [-451.624791 1135.703518 3965.000000]];

%CPT1
CPT1 = mean(PT1);

%CPT2
CPT2 = mean(PT2);

COV = zeros(3,3);
for v = 1 : 5
  tmp1 = PT1(v,:);
  tmp2 = PT2(v,:);
  A = (tmp1 - CPT1)' * (tmp2 - CPT2);
  COV = COV + A;
end

[U,S,V] = svd(COV);

R = U * V';
E = zeros(3,3);
E(1,1) = 1;
E(2,2) = 1;
E(3,3) = det(R);
R = U * E * V';
disp(R);

