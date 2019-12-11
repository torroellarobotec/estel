clear all;
pkg load image;

  file = 'EstrellaDeNavidad.jpg';
  ImageOrig = imread(file);
  ImageRGB = imresize(ImageOrig,[58,58]);
  #ImageRGB = ImageOrig;
  ImageHSV = rgb2hsv (ImageRGB);
  
  vectorHSV = "";
  Columnes = 58;

  while Columnes >= 1    
    #Files parelles
    Files = 58;
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
    while Files <= 58
      H = ImageHSV(Files, Columnes, 1);
      S = ImageHSV(Files, Columnes, 2);
      V = ImageHSV(Files, Columnes, 3);
      
      vectorHSV = strcat(vectorHSV, "{", num2str(round(H*255)), "," , num2str(round(S*255)) , "," , num2str(round(V*255)) ,"},");      
      Files = Files + 1;    
    endwhile
    
    Columnes = Columnes -1;
  endwhile
    
  save EstrellaDeNavidad_HSV_58x58.txt vectorHSV;
  
  imshow(ImageRGB);