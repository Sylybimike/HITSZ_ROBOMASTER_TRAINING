function result = Nor_noise(exp,var,length)
yita=zeros(1,length); 
for i = 1:length 
    epsilon = rand(1,12); 
    epsilon_sum = sum(epsilon);
    yita(i) = exp + var*(epsilon_sum -6 ); 
end
% x_label = 1:1:100; 
% plot(x_label,yita); 
result = yita;
end