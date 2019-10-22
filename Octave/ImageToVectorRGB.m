  file = 'Montgri.jpg';
  ImageOrig = imread(file);
  
  ImageRGB = imresize(ImageOrig,[60,60]);

  #[Files, Columnes] = size(ImageOrig);
  [Files, Columnes] = size(ImageRGB);
  Columnes = Columnes / 3;
  
  c = 0;
  vectorRGB = "";
  
  vectorImage = zeros(3600,3);

  for i = 1:Columnes
    for j = 1:Files

      c = c+1;
      
      pixelRGB = impixel(ImageRGB,i,j);
      R = pixelRGB(1); 
      G = pixelRGB(2);
      B = pixelRGB(3);
      
      vectorImage(c,1) = R;
      vectorImage(c,2) = G;
      vectorImage(c,3) = B;
      
      vectorRGB = strcat(vectorRGB, "{", num2str(R) , "," , num2str(G) , "," , num2str(B) ,"},");      
    endfor
  endfor

  #NewFile = strcat(file, ".txt");
  save Montgri.txt vectorRGB;

  imshow(ImageRGB);
  #imshow(ImageOrig);