H = [ ...
1 1 0 1 0 0 0; ...
0 1 1 0 1 0 0; ...
0 0 1 1 0 1 0; ...
0 0 0 1 1 0 1; ...
%1 0 0 0 1 1 0; ...
%0 1 0 0 0 1 1; ...
%1 0 1 0 0 0 1; ...
];

u = gf([1 0 0]);

H = gf(H);

%% Make gen
m = size(H, 1);
n = size(H, 2);
k = n - m;

% Make F
A = H(1:m, 1:k);
B = H(1:m, k+1:n);
F = transpose(A) * inv(transpose(B));

G = [gf(eye(k)), F];

% Generate Code word
c = u * G;

%% Transmission
y = c; % No errors

%% Decoder (HARD bit flip)
% 1. Compute parity-check sums for received bits
% 2. Compute number of failed parity-check equations for each bit
% 3. Flip the bits fot which number of failed equations is largest
% Repeat untill all parity-check sums are zero or preset number is reached

