
directory_name = 'C:\Users\H\Emo';
files = dir(directory_name);

fileIndex = find(~[files.isdir]);
fileIndex = fileIndex(randperm(length(fileIndex)));

emo = zeros(654,1);
fac = zeros(654,1);
% ln = zeros(327,136);
% emoo = zeros(377,1);
%  s = rng('shuffle');
  r = randperm(654);
%  lnn = zeros(377,98);
 ln1 = zeros(654,98);
%  lnr = zeros(327,14);
%  ln3 = zeros(327,94);
 %ln2 = zeros(327,34);
%land = zeros(68,2,327);

%fileName =  files(fileIndex(1)).name(1:end-11)
%% sort(randi(350,1,23),'ascend')
%r = sort(randperm(27),'ascend');
rIndex = 1;
%  mi = 0;
for i = 1:length(fileIndex)
    
    fileName = ['C:\Users\H\Emo\',files(fileIndex(i)).name];
    emo(i) = importdata(fileName);
    if(emo(i) == 2)
          continue
    end
        
    fileName =  ['C:\Users\H\Landmark\' files(fileIndex(i)).name(1:end-11) 'landmarks.txt'];
    c = textscan(fopen(fileName),'%s ');
%     fileName =  ['C:\Users\H\FACS\' files(fileIndex(i)).name(1:end-11) 'facs.txt'];
%     c1 = textscan(fopen(fileName),'%s ');
    fclose('all');
%     k = str2double(c{1});
%     ln(i,:) = k; 
% add Neutral
%     if i <= 50 
%         emo(377-mi) = 0;
%         fileName =  ['C:\Users\H\Landmark\' files(fileIndex(i)).name(1:end-14) '01_landmarks.txt'];
%         c = textscan(fopen(fileName),'%s ');
%         fclose('all');
%         kkk =  str2double(c{1}(17:18)); 
%         k = str2double(c{1}(35:end)); % without Shape
%         j = k(1:20);
%         l = k(27:end);
%         n = cat(1,kkk,j,l);
%         ln1(377-mi,:) = n;
%         mi = mi+1;
%         
%     end

 

    
%% without Nose
% kk =  str2double(c{1}(1:2)); 
kkk =  str2double(c{1}(17:18)); 
% kkkk =  str2double(c{1}(33:34)); 
k = str2double(c{1}(35:end)); % without Shape
j =  k(1:20);%%%
l =  k(27:end);%%%
n = cat(1,kkk,j,l);
ln1(i,:) = n;

%%%remove some points
% j1 = k(1:2);
% j2 = k(5:6);
% j3 = k(9:10);
% j4 = k(11:12);
% j5 = k(15:16);
% j6 = k(19:20);
% l =  k(27:end);%%%
% d0 = k(27:60);
% d1 = k(63:64);
% d2 = k(69:70); 
% d3 = k(75:76); 
% d4 = k(81:82); 
% s1 = k(87:88);
% s2 = k(91:92);
% s3 = k(95:96);
% s4 = k(99:100);
%j1,j2,j3,j4,j5,j6
%,d0d1,d2,d3,d4
%,s1,s2,s3,s4
% d = combine(j,l);
% if i <= 73
    
s = files(fileIndex(i)).name(1:end-11);
sss = s(16:end-1);
 ss =dec2hex(hex2dec(sss)-1);
% dec2hex(ss)
% dec2hex(ss)

fileName =  ['C:\Users\H\Landmark\' files(fileIndex(i)).name(1:end-20) '000000' ss  '_landmarks.txt'];
if exist(fileName, 'file') ==2
c = textscan(fopen(fileName),'%s ');
    fclose('all');
    kkk =  str2double(c{1}(17:18)); 
% kkkk =  str2double(c{1}(33:34)); 
k = str2double(c{1}(35:end)); % without Shape
j =  k(1:20);%%%
l =  k(27:end);%%%
n = cat(1,kkk,j,l);
fileName = ['C:\Users\H\Emo\',files(fileIndex(i)).name];
    emo(655 - i) = importdata(fileName);
    if(emo(655 - i) == 2)
          continue
    end
ln1(655 - i,:) = n;
    
end
%%%related to other ways 
%%% but with less accuracy
% end
%   scatter(ln1(i,1:2:end),ln1(i,2:2:end))
%  c;
% for a = 1:length(arr)
%     count = a-1;
% %% 1_brow
% x = ln1(i,1:2:10);
% y = ln1(i,2:2:10);
% bw = poly2mask(x,y,640,490);
% % figure, imshow(bw)
% 
% region = regionprops(bw, arr(a));
% celt = struct2cell(region);
% lnr(i,count*7+1) = celt{1,1};
% %% 2_brow
% x = ln1(i,11:2:20);
% y = ln1(i,12:2:20);
% bw = poly2mask(x,y,640,490);
% % figure, imshow(bw)
% 
% region = regionprops(bw, arr(a));
% celt = struct2cell(region);
% lnr(i,count*7+2) = celt{1,1};
% %% nose
% x = ln1(i,21:2:32);
% y = ln1(i,22:2:32);
% bw = poly2mask(x,y,640,490);
% % figure, imshow(bw)
% 
% region = regionprops(bw, arr(a));
% celt = struct2cell(region);
% lnr(i,count*7+3) = celt{1,1};
% %% 1_eye
% x = ln1(i,33:2:44);
% y = ln1(i,34:2:44);
% bw = poly2mask(x,y,640,490);
% % figure, imshow(bw)
% 
% region = regionprops(bw, arr(a));
% celt = struct2cell(region);
% 
% lnr(i,count*7+4) = celt{1,1};
% %% 2_eye
% x = ln1(i,45:2:56);
% y = ln1(i,46:2:56);
% bw = poly2mask(x,y,640,490);
% % figure, imshow(bw)
% 
% region = regionprops(bw, arr(a));
% celt = struct2cell(region);
% 
% lnr(i,count*7+5) = celt{1,1};
% %% Outer_Mouth
% x = ln1(i,57:2:80);
% y = ln1(i,58:2:80);
% bw = poly2mask(x,y,640,490);
% % figure, imshow(bw)
% 
% region = regionprops(bw, arr(a));
% celt = struct2cell(region);
% 
% lnr(i,count*7+6) = celt{1,1};
% %% inner_Mouth
% x = ln1(i,81:2:96);
% y = ln1(i,82:2:96);
% if  int64(ln1(i,93)) == int64(ln1(i,85))&&int64(ln1(i,91)) == int64(ln1(i,87)) && int64(ln1(i,92)) == int64(ln1(i,88))
%     lnr(i,count*7+7) = 0 ;
% 
% else
% bw = poly2mask(x,y,640,490);
% % figure, imshow(bw)
% 
% region = regionprops(bw, arr(a));
% celt = struct2cell(region);
% 
% lnr(i,count*7+7) = celt{1,1};
% end
% end
%%
% % %k = str2double(c{1});
% % %ln(i,:) = k;
% land(:,:,i) = importdata(fileName);

% Do stuff
%  scatter(ln1(i,1:2:end),ln1(i,2:2:end))
%  figure
%  scatter(ln1(i,57:2:80),ln1(i,58:2:80))
%  figure
%  scatter(ln1(i,81:2:end),ln1(i,82:2:end))
end
%%  rabomize
% % % for i=1:length(ln)
% % %    lnn(i,:) =  ln(r(i),:);
% % %    emoo(i) =  emo(r(i));
% % % end  
%%procrustes
% %  [mtx3,mtx4] = procrustes(ln1(1,:),ln1(5,:));
% %  [mtx5,mtx6] = procrustes(ln1(1,:),ln1(300,:));
% % 
% % for i = 1:length(fileIndex)
% %  [mtx1,mtx2,transform] = procrustes(ln1(2,:),ln1(i,:));
% %      
% %         ln3(i,:) = mtx2;
% %      
% % end
%% sin 
% disp(length(ln))
% disp(length(ln(i,:)))
% for i = 1:length(ln)
%     for a = 1:length(ln(i,:))
%         ln(i,a) = cos(ln(i,a));
%     end
% end
%% lines distance 61 right for 200 sample(100 test)
% n = 1;
% disp(length(ln))
% for i = 1:length(ln)
%     for a = 1:4:136  %136 for ln 84 for ln1
%         ln2(i,n) = distance([ln(i,a),ln(i,a+1)],[ln(i,a+2),ln(i,a+3)]);
%         n = n + 1;
%     end
%     n = 1;
% end
%%
% % % % for i=10:10:100
%     figure
%    scatter(ln1(30,1:2:end),ln1(30,2:2:end))
  
% % end
res = 0;
% Train = zeros(18,1);
% Trainx = zeros(18,98);
for m =1:100
    nn =1;
    mm=1;
    for i=1:length(ln1)
        if ln1(r(i),:)==0
            mm = mm+1;
        else
            
       emoo(nn) =  emo(r(i));
       lnn(nn,:) =  ln1(r(i),:);
       nn =nn+1;
        end
    end 
holdoutCVP = cvpartition(emoo,'holdout',100);
X_Train = lnn(holdoutCVP.training,:);
y_Train = emoo(holdoutCVP.training);
X_Test =  lnn(holdoutCVP.test,:);
y_Test =  emoo(holdoutCVP.test);
% X_Train1 = combine(X_Trai,Trainx);
% y_Train1 = combine(y_Trai,Train);
%     for i=1:length(X_Train1)
%        X_Train(i,:) =  X_Train1(r(i),:);
%        y_Train(i) =  y_Train1(r(i));
%     end 
%t = templateTree('type','regression');
%%%%%'Bag',200,'tree','type','classification' 
%%%%% 54 right 46 Wrong

%%%% 'AdaBoostM2',200
%%%% 48  right 52 Wrong 
%%
% ada = fitensemble(X_Train,y_Train,'AdaBoostM2',200,'tree');
% adb = compact(ada);
% L = loss(adb,X_Train,y_Train)
%%
% adb = fitcknn(X_Train,y_Train);
%%
% [label] = predict(ada,X_Test);
%% SVM 85
% label = multisvm(X_Train, y_Train, X_Test); 
%% DAC 92 ,'Gamma',0.003,0.0085
 ada = fitcdiscr(X_Train,y_Train,'Gamma',0.0035 );
%  tic
 [label , score, cost] = predict(ada,X_Test);
% toc%% accuracy
% % Training Error
% resuberror = resubLoss(ada)
% resuberror * ada.NumObservations


x = 0;
for i =1:100
    if label(i)==y_Test(i)
        x = x+1;
    
    end
end
res =  x+res;

 end
 re = res/100
 
%%% some tests
% % % % % % % % % % % % %  
% % % % % % % % % % % % 
% % %  arr(a)
% % 
% % %   s = X_Test(1,:);
% % %   c = clock;
% % %  predict(ada,s)
% % %  c1 = clock;
% % %  jk = c1-c
% % % isfield(region,'Area')
% % % isnumeric(celt{1,1})
% % % h = region.arr(a);
% % X_Test1 =[2.9674159e+02,4.3731687e+02,2.0084730e+02,1.8111123e+02,2.1360765e+02,1.6803730e+02,2.3282239e+02,1.6763548e+02,2.5211445e+02,1.6923483e+02,2.7112909e+02,1.7146098e+02,3.0661052e+02,1.7326064e+02,3.2624633e+02,1.7315687e+02,3.4567479e+02,1.6998112e+02,3.6497386e+02,1.7215486e+02,3.7604215e+02,1.8680144e+02,2.9133633e+02,2.7764101e+02,2.6628236e+02,2.8618197e+02,2.7903213e+02,2.9047157e+02,2.9205100e+02,2.9341787e+02,3.0425757e+02,2.8986943e+02,3.1560158e+02,2.8434655e+02,2.2176093e+02,2.0660771e+02,2.3709049e+02,1.9967059e+02,2.5337788e+02,2.0352770e+02,2.6250353e+02,2.1723636e+02,2.4732897e+02,2.1742725e+02,2.3232688e+02,2.1654962e+02,3.1189532e+02,2.1671679e+02,3.2105649e+02,2.0261024e+02,3.3769726e+02,1.9900100e+02,3.5240709e+02,2.0707330e+02,3.4175643e+02,2.1682234e+02,3.2677745e+02,2.1666074e+02,2.5849804e+02,3.4338586e+02,2.6227847e+02,3.2517732e+02,2.7481488e+02,3.1448854e+02,2.9018798e+02,3.1864806e+02,3.0457089e+02,3.1451780e+02,3.1741142e+02,3.2366748e+02,3.2541681e+02,3.3794660e+02,3.2417796e+02,3.6110344e+02,3.1427201e+02,3.8141909e+02,2.9420265e+02,3.8929032e+02,2.7427438e+02,3.8359335e+02,2.6312141e+02,3.6495576e+02,2.6272574e+02,3.4259152e+02,2.7285619e+02,3.2468248e+02,2.9043866e+02,3.2571687e+02,3.0795452e+02,3.2450870e+02,3.2009648e+02,3.3851852e+02,3.1186156e+02,3.6034715e+02,2.9313554e+02,3.7077381e+02,2.7397899e+02,3.6200237e+02] ;
% %  score = predict(ada,X_Test1)
% % mn = [174.15398782999478,154.3384599696855,172.3034178225945,172.95013533379554,174.20964236230802,191.48759127203738,178.61726372003176,210.53744966077778,186.97433694206933,226.60732852399198,198.76273657882876,239.1341441851905,212.6568113754963,248.7358026247129,228.88341687653528,252.10745443853347,244.8824238138443,248.86399234812995,258.27098889633453,239.18382422733833,269.6594296266021,226.88717160703538,277.819205366402,211.29124731661136,282.55324157506493,192.97781165826797,285.1009108828334,174.72424275909654,283.946070576847,156.09899968363007,274.34731519851994,145.93067339494445,266.2091879389094,140.9885042640011,252.95556317967083,141.20667306765228,242.43416956821096,143.4320708552974,185.84177047464877,144.77085667228351,194.79539212456797,139.99486343332254,208.3156978350503,140.60729617464978,218.88915115561315,143.14919527655104,193.16015804265538,157.44181064543469,203.70891111098123,153.24417830619808,214.78766786148506,157.5060710668005,203.63570354212595,160.05367332672773,204.06218341941334,156.5054030817284,266.9347535309172,158.4844613797929,256.9243604091603,153.98805454681923,245.53540623910482,157.8870066978451,256.69464366077733,160.79555284412766,256.39887830254344,157.22626894712909,230.48878621448836,153.1187085349048,217.85873503977436,176.1300987510299,212.7271141111117,184.39312721715504,217.06290616439932,190.24823330533312,230.00062066234918,192.40541765641495,242.6020321769612,190.56504238936924,246.99980659937327,184.88177420171013,242.2976421813916,176.516955087425,230.47407509018944,168.20533827781443,221.33913443246593,186.8374839617597,238.75726031959164,187.16660583350037,207.41075248727145,210.588720584082,215.2927646939218,205.63320903951097,223.84003388695797,203.62839178955517,229.6955050554852,204.85957830554543,235.5049998440161,203.79719147879354,243.70311461906,206.0057994613999,250.94712109398745,211.12789285548743,245.75319454863273,217.44501357505536,238.89396279525732,221.37939035414283,229.36838332203797,222.46689809922552,219.76663556066612,221.17438816527945,212.68053899868616,217.07361008710438,218.59937790112403,213.74842171802842,229.45433282006735,215.19086363938004,240.12293400318674,213.99311419718128,240.2790160585354,209.2414317313132,229.57263250162873,209.25954466064337,218.65396516758733,208.93951393004295,230.40681289662976,182.73528436295325,197.71105655994353,154.47509358512943,210.07292319693317,154.32518882587695,209.50597516166596,159.12812118925078,197.97175987689226,159.2638691169937,262.7237535523409,155.39337094707034,250.48819154882622,154.8533273396721,250.84868817658813,159.7044894585024,262.28677751471946,160.150745511876];
% % mmm = [226.22375784455105, 242.6577230676644, 278.4461053137857, 124.07207157690769, 268.39064517728474, 117.07353987497233, 252.81759982661686, 117.28409958664037, 240.74526520087457, 120.13262396957477, 178.96559706290898, 122.91603818316169, 188.09063845912263, 116.37829628378958, 203.00631724441627, 116.9132570667054, 214.75742766050956, 119.96272797185078, 186.889996744342, 137.6628449294917, 197.96671904503347, 132.64265072943232, 210.68591009795628, 136.9911037148629, 198.2655717320576, 139.13826180791827, 269.7824268181837, 138.39903608241076, 258.20007874726264, 133.13534076415158, 245.60554617210613, 137.34011913388397, 257.9075343028864, 139.66895615528418, 207.15669872298096, 162.19174560286172, 211.69486265189965, 168.260780619874, 226.31492214888442, 170.98511024434956, 242.06559165622843, 168.6832180363757, 246.945641431862, 162.62543906221026, 199.37625059415672, 189.67834681287042, 208.38204931941718, 182.74952765923783, 219.39641283042394, 180.66828112605103, 226.54187819068784, 181.8374875585205, 233.83601993594934, 180.83246901907148, 245.54233659282147, 183.19548807285122, 255.66867271752164, 190.37678015721661, 249.18119128779944, 200.56712337144268, 239.63029368470367, 206.76723050486925, 226.44694590154393, 208.48435605862213, 213.7096578986048, 206.42801054960262, 205.03739790226317, 199.97578256014737, 212.52859619944243, 198.84588488180282, 226.5808385413609, 201.31905977503857, 241.2710269223944, 199.20168761806227, 241.27309413593912, 186.4887627819805, 226.6183240317876, 186.51091790158793, 212.6053200703903, 186.11928471288553, 225.8522069086039, 159.68270290445923, 191.63867447348113, 134.28912308662285, 205.01716349546845, 133.7799277494463, 204.59772258074872, 138.32238218816352, 192.2785171649317, 138.78814347662563, 264.7228146032847, 134.8918597949762, 251.14195959096855, 134.19208495028275, 251.57844158083418, 138.75877183661177, 264.05279744477184, 139.43289169260606];
% % i = mn(15:16);%0->13     14=0
% % %-1
% % mn = mn(31:end);%16->30  2->14
% % k = mn(1:24);
% % l = mn(27:34);   %-1
% % %q = mn(29:34);   %-3
% % w = mn(41:50);
% % mn = mn(59:end);
% % mn = cat(2,i,k,l,w,mn);
% % 
% % figure('Name', 'Display Results')
% % subplot(1,2,1)
% % scatter(mn(1:2:end),mn(2:2:end),'MarkerFaceColor','r')
% % subplot(1,2,2)
% % scatter(mmm(1:2:end),mmm(2:2:end),'MarkerFaceColor','c')
% % % score = predict(ada,mn)
% % save('X_Train.txt', 'X_Train', '-ASCII','-append');
% % save('y_Train.txt', 'y_Train', '-ASCII','-append');
% % save('X_Test.txt', 'X_Test', '-ASCII','-append');
% % save('y_Test.txt', 'y_Test', '-ASCII','-append');

% 
% % lnn(:,99) = emoo;
% % csvwrite('nvse.csv',lnn)
