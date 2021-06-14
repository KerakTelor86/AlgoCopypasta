bool is_fibonacci(int n)
{
    return is_perfect_square(5 * n * n + 4)
           || is_perfect_square(5 * n * n - 4);
}
