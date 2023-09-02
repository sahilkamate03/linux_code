/**
 * @input A : Integer array
 * @input n1 : Integer array's ( A ) length
 * @input B : Integer
 * 
 * @Output Integer
 */
bool solve(int *A, int n1, int B, int mW)
{
    int count =1;
    int b=B;
    int w =0;
    int i=0;
    while (i<n1)
    {
        if (w+A[i]<=mW && B>=n1-i)
        {
            w +=A[i];
            i++;
        }
        else{
            w =A[i];
            count++;
            B--; i++;
        }
    }

    if (count == b) return true;
    else return false;
}

int books(int* A, int n1, int B) {
    int start =*max_element(A, A+n1);
    int end =0;
    end =accumulate(A, A+n1, end);

    for (start; start<=end; start++)
    {
        if (!solve(A, n1, B, mW))
            continue;
        return start;
    }

    return -1;
}

