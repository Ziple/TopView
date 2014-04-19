function [ P, e, k ] = LevenbergMarquardt( yobs, x, numCoeffs )
%LEVENBERGMARQUARDT Summary of this function goes here
%   Detailed explanation goes here
    e1 = 10^-15;
    e2 = 10^-15;
    e3 = 10^-15;
    tau = 10^-3;
    kmax = 100;
    
    P = zeros( numCoeffs, 1 );
    
    J = Jacobian( P, x );
    Jt = J';
    A =  Jt * J;
    Id = eye( size(A,1) );
    
    e = yobs - ApplyPolynom( P, x );
    g = Jt * e;
    
    k = 0;
    nu = 2;
    stop = max(abs(g)) < e1;
    mu = Mu( A, tau );
    
    while( (stop ~= true) && (k < kmax) )
        
        k = k+1;
        rho = 1;
        
        cont = true;
        while(cont)
            dp = (A + mu * Id) \ g;
            if( dot(dp,dp) < e2*e2*dot(P,P) )
                stop = true;
            else
                pnew = P + dp;
                enew = yobs - ApplyPolynom( pnew, x );
                
                rho = ( dot( e, e ) - dot( enew, enew ) )/(dp' * (mu * dp + g) );
                
                if( rho > 0 )
                    P = pnew;
                    % A doesn't change
                    e = enew;
                    g = Jt * e;
                    
                    stop = ( max( abs(g)) < e1) || (dot(e,e) < e3);
                    mu = mu * max( [ 1/3 (1- (2*rho-1)^3) ] );
                    nu = 2;
                else
                    mu = mu * nu;
                    nu = nu * 2;
                end
            end
            
            cont = (rho <= 0 ) && (stop == false);
        end
    end
    
end

function [ J ] = Jacobian( P, x )

    N = size( x, 1 );
    D = size( P, 1 );
    J = zeros( N, D );
    
    for i=1:N
        for k=1:D
            J(i,k) = x(i)^(k-1);
        end
    end
end

function [ mu ] = Mu( A, tau )
    N = size(A,1);
    
    mu = 0;
    for i=1:N
        
        mut = A(i,i);
        
        if( mut > mu )
            mu = mut;
        end
    end
    
    mu = mu * tau;
end

