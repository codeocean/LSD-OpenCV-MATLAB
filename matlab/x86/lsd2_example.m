%% show the image.
im = imread('./images/test.jpg');
imshow(im);
%% show the binary image after the process of LSD.
figure;
imshow(lsd2('./images/test.jpg'));
