int NthRoot(int n, int b) {
  // Write your code here.
  int l=1, r=30;
  while (l <= r) {
        int m = l + (r - l) / 2;
        float s = pow(n, m);

        // Check if x is present at mid
        if (s == (float)b)
            return m;
 
        // If x greater, ignore left half
        if (s < (float)b)
            l = m + 1;
 
        // If x is smaller, ignore right half
        else
            r = m - 1;
    }

    return -1;
}

