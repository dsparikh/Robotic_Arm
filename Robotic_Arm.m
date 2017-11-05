%MTE 204 Project: Phase 1 Part 1 Gausss-Seidel Method
%By: Dhrumilkumar Parikh
clear; clc;
format('long','g');
syms t2;

%x and y target position of the arm in mm
x = 200;
y = 0;
psi = degtorad(0);

%Length of the 3 links in mm
L1 = 105;
L2 = 100;
L3 = 130;
X = x - L3*cos(psi);
Y = y - L3*sin(psi);

t2 = acos((X^2 + Y^2 - L1^2 - L2^2)/(2*L1*L2)); 
t1 = atan2(Y,X) - atan2((L2*sin(t2)),(L1 + L2*cos(t2)));
t3 = psi - t1 - t2;

radtodeg(t1)
radtodeg(t2)
radtodeg(t3)

