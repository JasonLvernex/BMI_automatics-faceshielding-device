clear;
clc;


filename = 'C:\Users\lenovo\Desktop\1213-2.txt';                      %???
%filename = 'C:\Users\lenovo\Desktop\1128-5.txt';
delimiterIn = ' ';                          %????
%length(datas(:,1))

headerlinesIn =10;                           %???? headerlinesIn+1 ????????
%headerlinesIn =2846; % suitable for 1128-5
%headerlinesIn =2841; % suitable for 1128-6
% if mod(length(datas(:,1)),10)~=0
%     headerlinesIn=headerlinesIn-mod(length(datas(:,1)),10);
% end
fileread=importdata(filename,delimiterIn,headerlinesIn);
datass=fileread.data;

title={'flag_labelx','FMN1','FMD1','MFMD1','MFMN1','MMAV11'...
    ,'MMAV21','MAV1','SSI1','WAMP1', 'WL1','ZC1','IEMG1'...
    ,'VAR1','SSC1','RMS1','FR1','FMN2','FMD2','MFMD2','MFMN2','MMAV12'...
    ,'MMAV22','MAV2','SSI2','WAMP2', 'WL2','ZC2','IEMG2'...
    ,'VAR2','SSC2','RMS2','FR2'};

result_table=table(datass(:,33),datass(:,1),datass(:,2),datass(:,3),datass(:,4),datass(:,5)...
    ,datass(:,6),datass(:,7),datass(:,8),datass(:,9), datass(:,10),datass(:,11),datass(:,12)...
    ,datass(:,13),datass(:,14),datass(:,15),datass(:,16),datass(:,17),datass(:,18),datass(:,19),datass(:,20),datass(:,21)...
    ,datass(:,22),datass(:,23),datass(:,24),datass(:,25), datass(:,26),datass(:,27),datass(:,28)...
    ,datass(:,29),datass(:,30),datass(:,31),datass(:,32),  'VariableNames',title)

% ????
writetable(result_table, 'C:\Users\lenovo\Desktop\feature extraction_matlab\1213-2-A.csv');
