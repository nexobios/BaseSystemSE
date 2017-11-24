cols = 308;
rows = 308;


%Files to read (Microcontroller information)
filetoopen_2=('/Users/Abraham/Documents/Matlab/ITESO/Lena_filtered.bin');
file_id_2 = fopen(filetoopen_2,'r');
P2 = fread(file_id_2);
Micro_filtered2x2 = reshape(P2,cols,rows);
%Micro_filtered2x2=Micro_filtered2x2';
Micro_filtered2x2=uint8(Micro_filtered2x2);

map = colormap(gray(256));
image(Micro_filtered2x2)
axis square