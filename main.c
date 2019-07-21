#include <stdio.h>

// https://en.wikipedia.org/wiki/Difference_engine#Method_of_differences
#define MAX_ORDER 10
#define MAX_SEQ 100

void derive_order( int * sequence, int len )
{
    while( len > 1 )
    {
        sequence[len-1] = sequence[len-1] - sequence[len-2];
        len--;
    }
    sequence[0] = 0;
}

int append_sequence( int * last_in_order_arr, int orders )
{
    // update all orders and return last element
    // each order P(n+1)=P(n)+P'(n)+...P'D(d)
    while( orders > 1 )
    {
        last_in_order_arr[orders-2] += last_in_order_arr[orders-1];
        orders--;
    }
    return last_in_order_arr[0];
}

void method_of_differences( int * sequence, int len, int to_compute )
{
    if( !len )
        return;

    int orders = 1;
    int last_in_order_arr[MAX_ORDER] = {0};
    last_in_order_arr[0] = sequence[len-1];

    // Find Degree 0
    // D-1 for P'(n) is P(n)-P(n-1)
    // Constant function P(n) = C can be considered D = 0, Zero function P(n) = 0 is D = -1.
    while( len > 1 && sequence[len-1] - sequence[len-2] != 0 && orders < MAX_ORDER )
    {
        derive_order( sequence, len );
        last_in_order_arr[orders] = sequence[len-1];
        orders++;
    }

    if( orders == MAX_ORDER )
    {
        // very high order to compute
        return;
    }

    while( to_compute )
    {
        printf( "%d", append_sequence( last_in_order_arr, orders ) );
        if( to_compute > 1 ) printf(" ");
        to_compute--;
    }
    printf("\n");
}

int main()
{
    int num_of_tests = 0;
    scanf("%d", &num_of_tests);

    int sequence[MAX_SEQ];
    while( num_of_tests-- )
    {
        int sequence_len = 0;
        int compute_len = 0;
        scanf("%d %d", &sequence_len, &compute_len);
        if( sequence_len + compute_len > MAX_SEQ )
            continue;

        for( int i = 0; i < sequence_len; i++ )
        {
            scanf( "%d", &sequence[i] );
        }
        method_of_differences( sequence, sequence_len, compute_len );
    }

    return 0;
}
