int fib(int n) __attribute__((noinline));

int _start()
{
    int x = 0;

    x = fib(5);
}

int fib(int n)
{
    if(n==0 || n==1) return n;

    return fib(n-1) + fib(n-2);
}