% PID tuning using Genetic algorithm on SRV02 Rotary Servo Base Unit
% Script with simulation parameters

% For example (one of the best solution):
% Fitness function of the best chromosome: -0.15227026
% 6.721516 17.068499 0.055976 
% Time taken: 0.164199[s]

DCtfNum = [0.1284];                     % Numerator of the CD motor Transfer function
CDtfDen = [0.0021 0.084 0];             % Denominator of the DC motor Transfer function

% One of the best parameters obtained: PID = [7.922499 18.522621 0.096701];    
PID = [6.371828 11.205383 0.422472];    % Parameters of the PID regulator (Kp, Ti and Td)
Kp = PID(1);
Ti = PID(2);
Td = PID(3);

%% Run this section to plot results

sim('DCmotor.slx', 1.4) % most basic way to simulate with command script.

figure(1)
plot(tout, simout(:,1))
hold on
grid on
plot(tout, simout(:,2))
title("DC motor control")
xlabel("t")
ylabel("position (theta)")
legend("DC motor position output","DC motor position input")