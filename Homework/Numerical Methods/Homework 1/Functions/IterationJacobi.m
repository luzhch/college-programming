function [x, step, err, ok] = IterationJacobi(A, b, n, k)
D = zeros(n);
LU = zeros(n);
for i = 1 : n
    for j = 1 : n
        if i == j
            D(i, j) = A(i, j);
        else
            LU(i, j) = -A(i, j);
        end
    end
end
J = D^-1 * LU;
f = D^-1 * b;
x = zeros(n, 1);
prev = x;
count = 0;
step = zeros(1, k);
err = zeros(1, k);
while count == 0 || max(abs(x - prev)) >= 10e-5
    prev = x;
    x = J * x + f;
    count = count + 1;
    step(count) = count;
    err(count) = norm(x - prev);
    if count == k
        ok = 0;
        return
    end
end
step = step(1:count);
err = err(1:count);
ok = 1;
end