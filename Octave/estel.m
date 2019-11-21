##clf;
##[I,M] = imread("Paisaje60x60.jpg");
##imshow(I,M);
##[R, G, B] = ind2rgb (I, M);
##imshow (cat (3, R, G*0.5, B*0.8));*/

RGB = imread('Paisaje60x60.jpg');
#RGB(1,1,:)
#RGB(1:45,1:60,:)
#imshow(RGB)
#vals = impixel
#imfinfo('Paisaje60x60.jpg');


for i = 1:45
  for j = 1:60    
    pixel = impixel(RGB,i,j);
    disp(strcat('R: ', disp(pixel(1,1,1))))
    disp(strcat('G: ', disp(pixel(2,2,2))))
    disp(strcat('B: ', disp(pixel(3,3,3))))
    #, disp(pixel(1,1,1))
  endfor
endfor
