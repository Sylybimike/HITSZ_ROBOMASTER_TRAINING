function show_front(x,y,z)
time_seq = 1:100;
x = x(:,1:100);
y = y(:,1:100);
z = z(:,1:100);
figure(9);
plot(time_seq,x,'r');
hold on;
plot(y,'b');
hold on;
plot(z,'g');
legend('g_{hat}','g0','R_{Mz}');

