clear all;
pkg load image;

  file = 'Estrella7.png';
  ImageOrig = imread(file);
  ImageRGB = imresize(ImageOrig,[30,30]);
  #ImageRGB = ImageOrig;
  ImageHSV = rgb2hsv (ImageRGB);
  
  vectorHSV = "";
  Columnes = 30;

  while Columnes >= 1    
    #Files parelles
    Files = 30;
    while Files >= 1
      H = ImageHSV(Files, Columnes, 1);      
      S = ImageHSV(Files, Columnes, 2);
      V = ImageHSV(Files, Columnes, 3);
    
      vectorHSV = strcat(vectorHSV, "{", num2str(round(H*255)), "," , num2str(round(S*255)) , "," , num2str(round(V*255)) ,"},");    
      Files = Files - 1;
    endwhile
    
    Columnes = Columnes - 1;
    #Files senars
    Files = 1;
    while Files <= 30
      H = ImageHSV(Files, Columnes, 1);
      S = ImageHSV(Files, Columnes, 2);
      V = ImageHSV(Files, Columnes, 3);
      
      vectorHSV = strcat(vectorHSV, "{", num2str(round(H*255)), "," , num2str(round(S*255)) , "," , num2str(round(V*255)) ,"},");      
      Files = Files + 1;    
    endwhile
    
    Columnes = Columnes -1;
  endwhile
    
  save Estrella7HSV_30x30.txt vectorHSV;
  
  imshow(ImageRGB);