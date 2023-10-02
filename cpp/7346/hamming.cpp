#include <bits/stdc++.h>
#include <string>
using namespace std;

int getR(int x)
{
    int l =0, r =32;
    int ans =0;
	while (l <= r) {
		int m = l + (r - l) / 2;

		if (pow(2,m) >= x+m+1)
			 ans =m;

		if (pow(2,m) < x+m+1)
			l = m + 1;

		else
			r = m - 1;
	}

	return ans;
}

int getRD(int x)
{
    int l =0, r =32;
    int ans =0;
    while (l <= r) {
        int m = l + (r - l) / 2;

        if (pow(2,m) >= x)
             ans =m;

        if (pow(2,m) < x)
            l = m + 1;

        else
            r = m - 1;
    }

    return ans;
}

vector<int> encodeHamming(vector<int> data)
{
    vector<int> hC;
    int n =data.size();
    int r =getR(n);

    int counter =r-1;
    int k= 0;
    for (int i=data.size()+r-1; i>=0; i--)
    {
        if (counter >= 0 && i == pow(2,counter) -1)
        {
            hC.push_back(-1);
            counter--;
        } else{
            hC.push_back(data[k]);
            k++;
        }
    } 
    hC.push_back(-1);
    reverse(hC.begin(), hC.end());

    for (int i=0; i<r; i++)
    {
        int ans =0;
        for (int j=1; j<=n+r; j++)
        {
            int x =j>>i;
            if (x&1 && hC[j]!=-1)
                ans ^=hC[j];
        }       
        hC[pow(2,i)] =ans;
    }       
    return hC;
}

vector<int> decodeHamming(vector<int> &hc)
{
   vector<int> R;
   bool correct =true;
   int n =hc.size();
   int r =getRD(n); 
   vector<int> data;
   for (int i=0; i<r; i++)
   {
    int ans =0;
    for (int j=1; j<=hc.size(); j++)
    {
        int x =j>>i;
        if (x&1)
            ans ^=hc[j];
    }

    if (ans != 0)
        correct =false;
    R.push_back(ans);
   }

   if (!correct)
   {
        cout << "Error detected in Hamming Code. Correcting...\n"; 
        int t =0;
        for (int i=0; i<r; i++)
            if(R[i])
                t+=pow(2,int(i));
        
        if (hc[t]==0)
            hc[t]=1;
        else 
            hc[t]=0;
   }

   int k =0;
    for (int i=1; i<=hc.size()-1; i++)
    {
        if (i!=pow(2,k))
        {
            data.push_back(hc[i]); 
        } else
            k++;
    }

    reverse(data.begin(), data.end());
   return data;
}

vector<int> convertASCII_Binary(char inputChar)
{
    std::bitset<8> binaryRepresentation(inputChar);
    std::vector<int> binaryVector;
    
    for (int i = 0; i < 8; ++i) {
        binaryVector.push_back(binaryRepresentation[i]);
    }
    reverse(binaryVector.begin(), binaryVector.end());
    std::cout << "Binary representation of '" << inputChar << "': ";
    for (int i=binaryVector.size()-1; i>=0; i--) {
        std::cout << binaryVector[i];
    }
    cout << endl;
    return binaryVector;
}

char binaryToChar(vector<int> binaryVector)
{
    string binaryString;
    for (int bit : binaryVector) {
        binaryString += std::to_string(bit);
    }

    char convertedChar = static_cast<char>(std::bitset<8>(binaryString).to_ulong());
    cout << convertedChar << endl;
    return convertedChar;
}

string hammingClient(bool e)
{
    char inputChar;
    std::cout << "Enter a character: ";
    std::cin >> inputChar;
    vector<int> data =convertASCII_Binary(inputChar);
    reverse(data.begin(), data.end());
    vector<int> hc =encodeHamming(data);

    if (e && hc[1]==0)
        hc[1] =1;
    else if(e && hc[1]==1)
        hc[1] =0;

    cout << "Hamming Code: ";
    string final;
    
    for (int i=1; i<hc.size(); i++)
        cout << hc[i];
    cout << endl;

    for (int i=0; i<hc.size(); i++)
    {
        final +=to_string(hc[i]);
    }

    cout << "final: " << final << endl;
    return final;
}

void hammingServer(string d)
{
    vector<int> hc;
    for (char c : d) {
        // Check if the character is a digit (0-9)
        if (std::isdigit(c)) {
            // Convert the character to an integer and push it into the vector
            int digit = c - '0'; // Convert character to integer
            hc.push_back(digit);
        }
    }
    hc = decodeHamming(hc);
    
    cout << endl;
    cout << "Binary representation Server: ";
    for (auto &h : hc)
        cout << h;
    cout << endl;
    cout << "Data: ";
    vector<int> binaryVector =hc;
    reverse(hc.begin(), hc.end());
    binaryToChar(hc);
}

int main()
{
    string data =hammingClient(false);
    hammingServer(data);
    return 0;
}
