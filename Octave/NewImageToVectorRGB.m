  #file = 'estel.jpg';
  #file = 'EscutTorroella.png';
  #file = 'Montgri.jpg';
  file = 'estel.jpg';
  ImageOrig = imread(file);
  ImageRGB = imresize(ImageOrig,[60,60]);

  #[Files, Columnes] = size(ImageRGB);
  #Columnes = Columnes / 3;
  
  #c = 3600;
  vectorRGB = "";
  Columnes = 60;

  while Columnes >= 1    
    #Files parelles
    Files = 60;
    while Files >= 1
      pixelRGB = impixel(ImageRGB, Columnes, Files);
      R = pixelRGB(1); 
      G = pixelRGB(2);
      B = pixelRGB(3);          
      vectorRGB = strcat(vectorRGB, "{", num2str(R) , "," , num2str(G) , "," , num2str(B) ,"},");      
      Files = Files - 1;
    endwhile
    
    Columnes = Columnes - 1;
    #Files senars
    Files = 1;
    while Files <= 60
      pixelRGB = impixel(ImageRGB, Columnes, Files);
      R = pixelRGB(1); 
      G = pixelRGB(2);
      B = pixelRGB(3);          
      vectorRGB = strcat(vectorRGB, "{", num2str(R) , "," , num2str(G) , "," , num2str(B) ,"},");      
      Files = Files + 1;    
    endwhile
    
    Columnes = Columnes -1;
  endwhile
    
  #save EscutTorroella.txt vectorRGB;
  #save Montgri.txt vectorRGB;
  save Estel.txt vectorRGB;

  
  imshow(ImageRGB);