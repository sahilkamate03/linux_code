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

   cout << "Correct Hamming Code: ";
   for(int i=1; i<hc.size(); i++)
        cout << hc[i];
    

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
    cout << "\n\n";

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
    cout << endl;

    hc = decodeHamming(hc);
    
    cout << endl;
    cout << "Binary representation Server: ";
    for (auto &h : hc)
        cout << h;
    cout << endl;
    cout << "Client: ";
    vector<int> binaryVector =hc;
    reverse(hc.begin(), hc.end());
    binaryToChar(hc);
}

//Server side
int main(int argc, char *argv[])
{
    //for the server, we only need to specify a port number
    if(argc != 2)
    {
        cerr << "Usage: port" << endl;
        exit(0);
    }
    //grab the port number
    int port = atoi(argv[1]);
    //buffer to send and receive messages with
    char msg[1500];
     
    //setup a socket and connection tools
    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);
 
    //open stream oriented socket with internet address
    //also keep track of the socket descriptor
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }
    //bind the socket to its local address
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, 
        sizeof(servAddr));
    if(bindStatus < 0)
    {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }
    cout << "Waiting for a client to connect..." << endl;
    //listen for up to 5 requests at a time
    listen(serverSd, 5);
    //receive a request from client using accept
    //we need a new address to connect with the client
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);
    //accept, create a new socket descriptor to 
    //handle the new connection with client
    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(newSd < 0)
    {
        cerr << "Error accepting request from client!" << endl;
        exit(1);
    }
    cout << "Connected with client!" << endl;
    //lets keep track of the session time
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    //also keep track of the amount of data sent as well
    int bytesRead, bytesWritten = 0;
    while(1)
    {
        //receive a message from the client (listen)
        cout << "Awaiting client response..." << endl;
        memset(&msg, 0, sizeof(msg));//clear the buffer
        bytesRead += recv(newSd, (char*)&msg, sizeof(msg), 0);
        if(!strcmp(msg, "exit"))
        {
            cout << "Client has quit the session" << endl;
            break;
        }
        string clientData(msg);
        hammingServer(clientData);
        cout << endl;
    }
    //we need to close the socket descriptors after we're all done
    gettimeofday(&end1, NULL);
    close(newSd);
    close(serverSd);
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) 
        << " secs" << endl;
    cout << "Connection closed..." << endl;
    return 0;   
}