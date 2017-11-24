
filetoread =('/Users/Abraham/Documents/Matlab/ITESO/Lena.bmp');
A = imread(filetoread,'bmp');
[rows,cols] = size(A)


map = colormap(gray(256));
image(A)
axis square

fileID = fopen('Lena.c','w+');
fprintf(fileID, 'const uint8_t Lena[] = {\r\n');
for index = 1:(rows*cols)-1
    fprintf(fileID,'%4d, \r\n',A(index));
end
fprintf(fileID,'%4d \r\n',A(rows*cols));
fprintf(fileID, '};\r\n');
fclose(fileID);