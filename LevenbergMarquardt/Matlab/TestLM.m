close all;

numSamples = 1000;

P = [ 0.12; 0.26; 1.52 ];

x = 2.0 * ( 0.5 - rand( numSamples, 1 ) );
y = ApplyPolynom( P, x );

figure;
plot( x, y, '.' );
title('Polynomial curve');

% Guess the coefficients
sig = 0.01;
yobs = y + sig * rand( numSamples, 1 );

[ Pg, e, steps ] = LevenbergMarquardt( yobs, x, 3 );
yfit = ApplyPolynom( Pg, x );

hold on;
plot( x, yfit, 'r.' );
title('Fitted Polynomial curve');