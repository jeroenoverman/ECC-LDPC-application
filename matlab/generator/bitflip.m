%% Decoder (HARD bit flip)
% 1. Compute parity-check sums for received bits
% 2. Compute number of failed parity-check equations for each bit
% 3. Flip the bits fot which number of failed equations is largest
% Repeat untill all parity-check sums are zero or preset number is reached

H = [...
1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0; ...
0 0 0 0 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0; ...
0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0 0 0 0 0; ...
0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0; ...
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1; ...
1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 0 0 0 0; ...
0 1 0 0 0 1 0 0 0 1 0 0 0 0 0 0 1 0 0 0; ...
0 0 1 0 0 0 1 0 0 0 0 0 0 1 0 0 0 1 0 0; ...
0 0 0 1 0 0 0 0 0 0 1 0 0 0 1 0 0 0 1 0; ...
0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1; ...
1 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 1 0 0; ...
0 1 0 0 0 0 1 0 0 0 1 0 0 0 0 1 0 0 0 0; ...
0 0 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 1 0; ...
0 0 0 1 0 0 0 0 1 0 0 0 0 1 0 0 1 0 0 0; ...
0 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1];

y = [1 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0];
y_orig = y;

% Sj = y1 * hj,1 + y2 * hj,2 + ... + yn * hj,n
s = [];
for n = 1:10 % Max iterations
    s_n = [];
    for j = 1:size(H,1)
        tmp = mod(sum(y .* H(j,:)), 2);
        s_n = [s_n tmp];
    end
    
    % If s_n == all zero, we are done
    if sum(s_n) == 0
        break;
    end
    
    f_n = [];
    for i = 1:size(H,2)
        tmp = sum(transpose(s_n) .* H(:,i));
        f_n = [f_n tmp];
    end
    
    % Find index of largest sums
    m = max(f_n);
    idx = find(f_n == m);
    for mm = idx
        y(mm) = mod(y(mm)+1,2);
    end
end

fprintf('Done after %d iterations\n', n);
fprintf('Starting y: ');
y_orig
fprintf('Final y: ');
y