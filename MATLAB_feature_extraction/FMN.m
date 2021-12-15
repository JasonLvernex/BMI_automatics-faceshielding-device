function [ answ ] = FMN( binned_signal )
% Returns the mean PSD in each bin

[R C] = size(binned_signal);
answ = zeros(1,C);

for i = 1:C
    %%[Pxx, W] = pwelch(binned_signal(:,i));
    %%answ(1,i) = (sum(W.*Pxx))/(sum(Pxx));
    answ(1,i)=abs( sum(R.* power(fft(binned_signal(:,i),32),2))/sum(power(fft(binned_signal(:,i),32),2)));
end

end



