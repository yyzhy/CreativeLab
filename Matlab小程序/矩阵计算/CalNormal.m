% 点云法向估计
% zhouyez
% 2018.12.12
clc;
clear;
ptCloud = load('.\data\BEFORE_NORMAL01.asc');
[rows, cols] = size(ptCloud);

ptCloud2 = pointCloud(ptCloud(:,1:3));
normals = pcnormals(ptCloud2, 9);

for v = 1:rows
  if normals(v,3) > 0
    normals(v,3) = normals(v,3) * (-1);
    normals(v,2) = normals(v,2) * (-1);
    normals(v,1) = normals(v,1) * (-1);
  end
end

x = ptCloud2.Location(1:10:end,1);
y = ptCloud2.Location(1:10:end,2);
z = ptCloud2.Location(1:10:end,3);
u = normals(1:10:end,1);
v = normals(1:10:end,2);
w = normals(1:10:end,3);

% quiver3(x,y,z,u,v,w);
% hold off;

M = [ptCloud(:,1:3) normals];
save aa.txt -ascii M