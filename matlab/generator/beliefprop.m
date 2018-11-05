% Belief propegation
% Iteration based, each iteration has 2 steps
% n = columns = var vectors
% m = rows = check vectors

H = [ ...
1 1 0 1 0 0 0; ...
0 1 1 0 1 0 0; ...
0 0 1 1 0 1 0; ...
0 0 0 1 1 0 1; ...
1 0 0 0 1 1 0; ...
0 1 0 0 0 1 1; ...
1 0 1 0 0 0 1; ...
];

[m,n] = size(H);

L = [+0.9 +0.1 +0.3 +0.8 +1.0 -0.2 -0.3];

svMat = zeros(size(H));

svSum = L;
for it = 1:2

    % It 1, step 1: Var -> Check
    % Sum - column elements
    for vv = 1:n
        for r = 1:m
            if H(r,vv) > 0
                svMat(r,vv) = svSum(vv) - svMat(r,vv);
            end
        end
    end

    %fprintf("It1, step1\n");
    %svMat

    % It 1, step 2: Check -> Var
    for row = 1:m
        % Look at all connections and only look at 1's
        combine_vec = [];
        idx_vec = [];
        lnew_vec = [];

        % Get the correct indexes
        for idx = 1:n
            if (H(row,idx) > 0)
               combine_vec = [combine_vec svMat(row,idx)];
               idx_vec = [idx_vec idx];
            end
        end

        % Compute the new likelehood
        for elm = 1:length(combine_vec)

            minv = 999999;
            signv = 1;
            for x = 1:length(combine_vec)

                if x ~= elm
                    val = abs(combine_vec(x));
                    if  val < minv
                       minv = val;
                    end
                    signv = signv * sign(combine_vec(x));
                end
            end
            %%signv
            lnew_vec = [lnew_vec (signv * minv)];
        end

        %%combine_vec
        %%idx_vec
        %%lnew_vec

        % Assign the new likelehoods
        for elm = 1:length(idx_vec)
            svMat(row,idx_vec(elm)) = lnew_vec(elm);
        end
    end

    % Sum and est
    % svSum is sum of column and L
    svSum = zeros(size(L));
    for l = 1:length(L)
        svSum(l) = sum(svMat(:,l)) + L(l);
    end

end




