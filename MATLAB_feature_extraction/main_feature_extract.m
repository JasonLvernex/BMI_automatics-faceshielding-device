%this is the main application of the feature extraction
%%READ DATA FROM TXT
clear;
clc;
global fileread;
global datas;
global pointer_data epoch_num;
global v1 v2 F;
global flag_labelx FMD1 FMD2 FMN1 FMN2...
       FR1 FR2 MAV1 MAV2 MAVS1 MAVS2 MFMD1...
       MFMD2 MFMN1 MFMN2 MMAV11 MMAV12 ...
       MMAV21 MMAV22 SSC1 SSC2 SSI1 SSI2 ...
       WAMP1 WAMP2 WL1 WL2 ZC1 ZC2 IEMG1 IEMG2...
       VAR1 VAR2 RMS1 RMS2;
   
filename = 'C:\Users\lenovo\Desktop\1128-6.txt';                      %???
%filename = 'C:\Users\lenovo\Desktop\1128-5.txt';
delimiterIn = ' ';                          %????
%length(datas(:,1))

headerlinesIn =2846;                           %???? headerlinesIn+1 ????????
%headerlinesIn =2846; % suitable for 1128-5
%headerlinesIn =2841; % suitable for 1128-6
if mod(length(datas(:,1)),10)~=0
    headerlinesIn=headerlinesIn-mod(length(datas(:,1)),10);
end
fileread=importdata(filename,delimiterIn,headerlinesIn);
datas=fileread.data;
%%data sigmentation
%every ten data are a package for segmentation
%disp(datas(:,1));

%%
%%plot the figure
polt_trigger=0;%whether to plot or not
if polt_trigger==1
x=linspace(1,length(datas(:,1)),length(datas(:,1)));
plot(x,datas(:,1),'b')
hold on;
plot(x,datas(:,2),'r')
hold on;
plot(x,datas(:,3)*50,'y*','linewidth',1)
hold on;
xlabel('time/ms');ylabel('amplitude/mV')
legend('V1','V2','TRIGGER');
end

%%
pointer_data=1;
epoch_num=1;
train_trigger=1; %the switch to trigger extraction 1:run 0:not run
if train_trigger==1

while pointer_data<=(length(datas(:,1)))
    v1=datas(pointer_data:pointer_data+9,1);
    %disp(v1);
    v2=datas(pointer_data:pointer_data+9,2);
    %disp(v2);
    F=datas(pointer_data:pointer_data+9,3);
    %disp(F);
    flag_labelx(epoch_num)=flag_label(F);
    FMD1(epoch_num)=FMD(v1);
    FMD2(epoch_num)=FMD(v2);
    FMN1(epoch_num)=FMN(v1);
    FMN2(epoch_num)=FMN(v2);
    FR1(epoch_num)=FR(v1);
    FR2(epoch_num)=FR(v2);
    MAV1(epoch_num)=MAV(v1);
    MAV2(epoch_num)=MAV(v2);
    %MAVS1(epoch_num)=MAVS(v1);
    %MAVS2(epoch_num)=MAVS(v2);    
    MFMD1(epoch_num)=MFMD(v1);
    MFMD2(epoch_num)=MFMD(v2);
    MFMN1(epoch_num)=MFMN(v1);
    MFMN2(epoch_num)=MFMN(v2); 
    MMAV11(epoch_num)=MMAV1(v1);
    MMAV12(epoch_num)=MMAV1(v2);
    MMAV21(epoch_num)=MMAV2(v1);
    MMAV22(epoch_num)=MMAV2(v2);
    SSC1(epoch_num)=SSC(v1,150);
    SSC2(epoch_num)=SSC(v2,150);
    SSI1(epoch_num)=SSI(v1);
    SSI2(epoch_num)=SSI(v2);
    WAMP1(epoch_num)=WAMP(v1,200);%threshold
    WAMP2(epoch_num)=WAMP(v2,170);
    WL1(epoch_num)=WL(v1);
    WL2(epoch_num)=WL(v2);
    ZC1(epoch_num)=ZC(v1);
    ZC2(epoch_num)=ZC(v2);
    IEMG1(epoch_num)=IEMG(v1);
    IEMG2(epoch_num)=IEMG(v2);
    VAR1(epoch_num)=VAR(v1);
    VAR2(epoch_num)=VAR(v2);
    RMS1(epoch_num)=RMS(v1);
    RMS2(epoch_num)=RMS(v2);
    
    pointer_data=pointer_data+10;%we can achieve overlaping here by adjusting param
    epoch_num=epoch_num+1;
    disp(epoch_num-1);
    %disp(pointer_data-9);
end
end

%%
%%csv file creating
creat_file=1; %trigger to create the csv file 1:run 0:don't run
if creat_file==1
% csvwrite('C:\Users\lenovo\Desktop\feature extraction_matlab\1128-5.cvs',flag_labelx');
% dlmwrite('C:\Users\lenovo\Desktop\feature extraction_matlab\1128-5.cvs',FMD1','delimiter',',','-append',1,1);
% dlmwrite('C:\Users\lenovo\Desktop\feature extraction_matlab\1128-5.cvs',FMD2','delimiter',',','-append',1,2);
% ???????
% ??????1-n??????????????
% BD1=1:51;
% BD2=BD1.';

% ???
title={'flag_labelx','FMN1','FMD1','MFMD1','MFMN1','MMAV11'...
    ,'MMAV21','MAV1','SSI1','WAMP1', 'WL1','ZC1','IEMG1'...
    ,'VAR1','SSC1','RMS1','FR1','FMN2','FMD2','MFMD2','MFMN2','MMAV12'...
    ,'MMAV22','MAV2','SSI2','WAMP2', 'WL2','ZC2','IEMG2'...
    ,'VAR2','SSC2','RMS2','FR2'};

%?????????
% VariableNames ????????
result_table=table(flag_labelx.',FMN1.',FMD1.',MFMD1.',MFMN1.',MMAV11.'...
    ,MMAV21.',MAV1.',SSI1.',WAMP1.', WL1.',ZC1.',IEMG1.'...
    ,VAR1.',SSC1.',RMS1.',FR1.',FMN2.',FMD2.',MFMD2.',MFMN2.',MMAV12.'...
    ,MMAV22.',MAV2.',SSI2.',WAMP2.', WL2.',ZC2.',IEMG2.'...
    ,VAR2.',SSC2.',RMS2.',FR2.',  'VariableNames',title)

% ????
writetable(result_table, 'C:\Users\lenovo\Desktop\feature extraction_matlab\1128-5-A.csv');
end
