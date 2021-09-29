clear
syms s;
%定义系统传递函数Hs = 120/(8.3*s+1)/(6.2*s+1);
num = 120;
den = [51.46,14.5,1];
%定义输入序列长度
seq_length = 2044;

%获取输入M序列和白噪声
input_seq  = Generate_M_Seq;
input_noise = Nor_noise(0,1,seq_length);


%获得系统响应并绘图
t = 0:1:seq_length-1;
output_seq = lsim(tf(num,den),input_seq,t);
figure(1);
plot(t,output_seq)

%信号叠加,白噪声转置
final_seq = output_seq + input_noise';
figure(2);
plot(t,final_seq)

%redefine
u = input_seq';
z = final_seq;
Np = 2^9-1;
r = 3;
T0 = 1;
T1 = 8.3;
T2 = 6.2;
K = 120;
a = 1;

%计算互相关函数
R= zeros(1,Np);
R_Mz = zeros(1,Np);
for i=1:Np
    for j=Np+1:(r+1)*Np
        R(i) = R(i)+u(j-i)*z(j);
    end
    R_Mz(i)=R(i)/(r*Np);
end
c = -R_Mz(Np-1);
k = 1:Np;

g0 = K/(T1-T2) *(exp(-k*T0/T1)-exp(-k*T0/T2));
g_hat = Np/(Np+1) * (R_Mz+c);
delta_g = sqrt(sum((g0-g_hat).^2)/sum(g0.^2));
figure(3)
plot(g_hat', 'b');
hold on;
plot(g0, 'g');
legend('g_{hat}', 'g(k)');
