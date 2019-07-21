#include <stdio.h>

/* https://en.wikipedia.org/wiki/Difference_engine#Method_of_differences
 * Sequence of length S must be extrapolated C steps
 * 1: Derive sequence until D != 0
 * P(n)    -> 1 2 4 7 11 16 22 29 -> D > 0
 * P'(n)   -> 1 2 3 4  5  6  7    -> D > 0
 * P''(n)  -> 1 1 1 1  1  1       -> D = 0 ()
 * P'''(n) -> 0 0 0 0  0          -> D = -1 (can be ignored)
 *
 * 2: Take values last in orders
 * 29 7 1
 *
 * 3: Append all values from back to front. Repeat C times
 * 37 8 1
 * 46 9 1
 */

#define MAX_ORDER 100
#define MAX_SEQ 100

int derive_val( const int * sequence, int len )
{
    // Return P(n) - P(n-1). In case of 0, D = -1
    // Must check all values! Special case "1 1 1 1 1 1 1 1 1 2" is derived all the way until "1"
    int derived = 0;
    for( int i = 0; i < len; i++ )
    {
        derived = sequence[i+1] - sequence[i];
        if( derived != 0 )
            break;
    }
    return derived;
}


void derive_order( int * sequence, int len )
{
    for( int i = 0; i < len; i++ )
    {
        sequence[i] = sequence[i+1] - sequence[i];
    }
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
    while( len > 1 && derive_val( sequence, len ) != 0 && orders < MAX_ORDER )
    {
        len--;
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
