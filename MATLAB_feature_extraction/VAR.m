function [ answ ] = VAR( binned_signal )

[R C] = size(binned_signal);
answ = zeros(1,C);
 ave=MAV(binned_signal);
for i = 1:C

   answ(1,i)=sum( abs(power(binned_signal(:,i),2)-ave));
	
end

end