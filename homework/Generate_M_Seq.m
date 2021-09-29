function result = Generate_M_Seq
clc
clear
M = [1,0,0,0,0,0,1,0,0];
Np = 2^9-1;
u = zeros(1,4*Np);
for i = 1:4*Np
    m = xor(M(9),M(5));
    for j = 9:-1:2
        M(j) = M(j-1);
    end
    M(1) = m;
    u(i) = M(9);
end
a = 1;
for i = 1:4*Np
    u(i) = (1-2*u(i))*a;
end
result = u;
end