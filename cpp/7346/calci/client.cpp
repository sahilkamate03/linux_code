#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
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
    std::cout << endl << "Enter character: ";
    std::cin >> inputChar;
    vector<int> data =convertASCII_Binary(inputChar);
    reverse(data.begin(), data.end());
    vector<int> hc =encodeHamming(data);

    if (e && hc[1]==0)
        hc[1] =1;
    else if(e && hc[1]==1)
        hc[1] =0;

    cout << "Hamming Code Sent: ";
    string final;
    
    for (int i=1; i<hc.size(); i++)
        cout << hc[i];
    cout << endl;
    for (int i=0; i<hc.size(); i++)
    {
        final +=to_string(hc[i]);
    }

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

    cout << "Hamming Code Recieved: ";
    for (int i=1; i<hc.size(); i++)
        cout << hc[i];
    cout<<endl;
    // cout << "Hamming Code: ";
    // for (int i=1; i<hc.size(); i++)
    //     cout << hc[i];
    // cout << endl;

    hc = decodeHamming(hc);
    
    cout << endl;
    cout << "Binary representation Server: ";
    for (auto &h : hc)
        cout << h;
    cout << endl;
    cout << "Server: ";
    vector<int> binaryVector =hc;
    reverse(hc.begin(), hc.end());
    binaryToChar(hc);
}



//Client side
int main(int argc, char *argv[])
{
    //we need 2 things: ip address and port number, in that order
    if(argc != 3)
    {
        cerr << "Usage: ip_address port" << endl; exit(0); 
    } //grab the IP address and port number 
    char *serverIp = argv[1]; int port = atoi(argv[2]); 
    //create a message buffer 
    char msg[1500]; 
    //setup a socket and connection tools 
    struct hostent* host = gethostbyname(serverIp); 
    sockaddr_in sendSockAddr;   
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr)); 
    sendSockAddr.sin_family = AF_INET; 
    sendSockAddr.sin_addr.s_addr = 
        inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);
    //try to connect...
    int status = connect(clientSd,
                         (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
    if(status < 0)
    {
        cout<<"Error connecting to socket!"<<endl; 
    }
    cout << "Connected to the server!" << endl;
    int bytesRead, bytesWritten = 0;
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    while(1)
    {
        cout << "Menu:\n1. With Error\n2. Without Error\n3. Exit\n> ";
        int t; cin >>t;
        string data;
        if (t==1)
            data =hammingClient(true);
        else if (t==2)
            data =hammingClient(false);
        else
            exit(0);
        memset(&msg, 0, sizeof(msg));//clear the buffer
        strcpy(msg, data.c_str());

        if(data == "exit")
        {
            send(clientSd, (char*)&msg, strlen(msg), 0);
            break;
        }
        bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
        
    }
    gettimeofday(&end1, NULL);
    close(clientSd);
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten << 
    " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec- start1.tv_sec) 
      << " secs" << endl;
    cout << "Connection closed" << endl;
    return 0;    
}