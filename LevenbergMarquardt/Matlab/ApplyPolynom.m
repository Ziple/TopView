function [ y ] = ApplyPolynom( P, x )
%APPLYPOLYNOM Summary of this function goes here
%   Detailed explanation goes here

    numSamples = size(x,1);
    numCoeffs = size(P,1);
    
    y = zeros( numSamples, 1 );
    o = ones( numSamples, 1 );
    for k=numCoeffs:-1:1%zero indexed in labview
        y = y .* x + P(k) .* o;
    end
end

