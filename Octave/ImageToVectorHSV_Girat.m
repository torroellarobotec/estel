clear all;
pkg load image;

  file = 'estel.jpg';
  ImageOrig = imread(file);
  ImageRGB = imresize(ImageOrig,[60,60]);
  ImageHSV = rgb2hsv (ImageRGB);
  
  vectorHSV = "";
  Columnes = 60;

  while Columnes >= 1    
    #Files parelles
    Files = 60;
    while Files >= 1
      H = ImageHSV(Columnes, Files, 1);      
      S = ImageHSV(Columnes, Files, 2);
      V = ImageHSV(Columnes, Files, 3);
    
      vectorHSV = strcat(vectorHSV, "{", num2str(round(H*255)), "," , num2str(round(S*255)) , "," , num2str(round(V*255)) ,"},");    
      Files = Files - 1;
    endwhile
    
    Columnes = Columnes - 1;
    #Files senars
    Files = 1;
    while Files <= 60
      H = ImageHSV(Columnes, Files, 1);
      S = ImageHSV(Columnes, Files, 2);
      V = ImageHSV(Columnes, Files, 3);
      
      vectorHSV = strcat(vectorHSV, "{", num2str(round(H*255)), "," , num2str(round(S*255)) , "," , num2str(round(V*255)) ,"},");      
      Files = Files + 1;    
    endwhile
    
    Columnes = Columnes -1;
  endwhile
    
  save estelHSV_Girat.txt vectorHSV;
  
  imshow(ImageRGB);