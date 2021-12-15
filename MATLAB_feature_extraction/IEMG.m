function [ answ ] = IEMG( binned_signal )

[R C] = size(binned_signal);
answ = zeros(1,C);

for i = 1:C

   answ(1,i)= sum(abs(binned_signal(:,i)));
	
end

end