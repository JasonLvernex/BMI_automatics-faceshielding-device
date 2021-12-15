function [answ]=flag_label(binned_signal)
% this returns the label of the bin
% when the total flag exceed the half of the bin, this action is labeled as
% activated
[R C] = size(binned_signal);
answ = 0;
for i = 1:C
    answ = binned_signal(:,i)+answ;
end

if answ > 3
    answ=1;
else
    answ=0;
end

end