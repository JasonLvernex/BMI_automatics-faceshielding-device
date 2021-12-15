function [ answ ] = RMS( binned_signal )

[R C] = size(binned_signal);
answ = zeros(1,C);

for i = 1:C

   answ(1,i)=(1/R)*sum( abs(power(binned_signal(:,i),2)));
	
end

end