#imfinfo('Dibujo60x60.jpg');

D = './Images/';
files = glob('./Images/*')
S = dir(fullfile(D,'*.jpg')); % pattern to match filenames.

for k = 1:numel(S)
  F = fullfile(D,S(k).name);
  ImageOrig = imread(F);
  ImageRGB = imresize(ImageOrig,[60,60]);

  [Files, Columnes] = size(ImageRGB);
  Columnes = Columnes / 3;

  imshow(ImageRGB);
  
  c = 0;
  strRGB = "";

  for i = 1:Columnes
    for j = 1:Files
      c = c+1;
      pixelRGB = impixel(ImageRGB,i,j);
      R = pixelRGB(2); #la tira de leds es GRB
      G = pixelRGB(1);
      B = pixelRGB(3);
      
      strR = strcat("leds[",num2str(c),"].red = ", num2str(R), ";");
      strG = strcat("leds[",num2str(c),"].green = ", num2str(G), ";");
      strB = strcat("leds[",num2str(c),"].blue = ", num2str(B), ";");

      strRGB = strcat(strRGB,strR,strG,strB);
      #strRGB = strcat(strRGB, "leds[", num2str(c), "].setRGB(", num2str(R), ",", num2str(G), ",", num2str(B), ");");
    endfor
  endfor

  NewFile = strcat(S(k).name, ".txt");
  #save("-text", NewFile, strRGB);
  save text.txt strRGB;
endfor  

