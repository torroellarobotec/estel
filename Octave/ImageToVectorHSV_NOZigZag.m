clear all;
pkg load image;

  file = 'estel-deg-cua.png';
  ImageOrig = imread(file);
  ImageRGB = imresize(ImageOrig,[1,142]);
  ImageHSV = rgb2hsv (ImageRGB);
  
  vectorHSV = "";

  Files = 1;
  while Files <= 1    
    Columnes = 1;
    while Columnes <= 142
      H = ImageHSV(Files, Columnes, 1);      
      S = ImageHSV(Files, Columnes, 2);
      V = ImageHSV(Files, Columnes, 3);
    
      vectorHSV = strcat(vectorHSV, "{", num2str(round(H*255)), "," , num2str(round(S*255)) , "," , num2str(round(V*255)) ,"},");    
      Columnes = Columnes + 1;
    endwhile
    
    Files = Files + 1;
  endwhile
    
  save EstelDegCuaHSV.txt vectorHSV;
  
  imshow(ImageRGB);