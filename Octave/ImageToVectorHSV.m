clear all;
pkg load image;

  file = 'Estrella7.png';
  ImageOrig = imread(file);
  ImageRGB = imresize(ImageOrig,[60,60]);
  ImageHSV = rgb2hsv (ImageRGB);
  
  vectorHSV = "";
  Columnes = 60;

  while Columnes >= 1    
    #Files parelles
    Files = 60;
    while Files >= 1
      H = ImageHSV(Files, Columnes, 1);      
      S = ImageHSV(Files, Columnes, 2);
      V = ImageHSV(Files, Columnes, 3);
    
      vectorHSV = strcat(vectorHSV, "{", num2str(H) , "," , num2str(S) , "," , num2str(V) ,"},");    
      Files = Files - 1;
    endwhile
    
    Columnes = Columnes - 1;
    #Files senars
    Files = 1;
    while Files <= 60
      H = ImageHSV(Files, Columnes, 1);
      S = ImageHSV(Files, Columnes, 2);
      V = ImageHSV(Files, Columnes, 3);
      
      vectorHSV = strcat(vectorHSV, "{", num2str(H) , "," , num2str(S) , "," , num2str(V) ,"},");      
      Files = Files + 1;    
    endwhile
    
    Columnes = Columnes -1;
  endwhile
    
  save Estrella7HSV.txt vectorHSV;
  
  imshow(ImageRGB);