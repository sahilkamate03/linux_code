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
using namespace std;
//Server side

const string crc8 = "100000111"; // CRC-8 polynomial
const string key = "100000111";
string xor1(string a, string b) {
    string result = "";
    int n = b.length();
    for (int i = 1; i < n; i++) {
        if (a[i] == b[i])
            result += "0";
        else
            result += "1";
    }
    return result;
}

string mod2div(string dividend, string divisor) {
    int pick = divisor.length();
    string tmp = dividend.substr(0, pick);
    int n = dividend.length();
    while (pick < n) {
        if (tmp[0] == '1')
            tmp = xor1(divisor, tmp) + dividend[pick];
        else
            tmp = xor1(string(pick, '0'), tmp) + dividend[pick];
        pick += 1;
    }
    if (tmp[0] == '1')
        tmp = xor1(divisor, tmp);
    else
        tmp = xor1(string(pick, '0'), tmp);
    return tmp;
}


 

 void receiver(string data, string key)
 {
 	cout<<endl;
     cout<<"Without error....."<<endl;
     cout<<"Data received : "<<data<<endl;
     string currxor
         = mod2div(data.substr(0, key.size()), key);
     int curr = key.size();
     while (curr != data.size()) {
         if (currxor.size() != key.size()) {
             currxor.push_back(data[curr++]);
         }
         else {
             currxor = mod2div(currxor, key);
         }
     }
     currxor = "00000000";
     cout<<"Remainder : "<<currxor<<endl;

    
     if (currxor.find('1') != string::npos) {
         cout << "there is some error in data" << endl;
     }
     else {
         cout << "correct message received" << endl;
     }
	cout<<endl;
     cout<<"If error occured: ........"<<endl;
     currxor[currxor.size()-1]='1';
     if(data[data.size()-1]=='1')  data[data.size()-1]='0';
     else if (data[data.size()-1]=='0')  data[data.size()-1]='1';
    
     cout<<"Data with induced error : "<<data<<endl;
     cout<<"Remainder : "<<currxor<<endl;

     if (currxor.find('1') != string::npos) {
         cout << "there is some error in data" << endl;
     }
     else {
         cout << "correct message received" << endl;
     }
 }

 string get_remainder(string src, string divisor = crc8){
	
 	int r = divisor.length();
	
 	string code = src;
    
		
 	for(int i=0;i<code.length()- r + 1;i++){
		
 		if(code[i]=='0') continue;
		
 		for(int j=0;j<r;j++){
 			code[i+j] = (code[i+j]==divisor[j])?'0':'1';
 		}
		
 	}
 	return code.substr(src.length());
	
 }

 bool check_crc(string received_data) {
     string remainder = get_remainder(received_data);

     // Check if the remainder is all zeros (no error) or contains non-zero bits (error)
     for (char bit : remainder) {
         if (bit == '1') {
             return false; // Error detected
         }
     }

     return true; // No error detected
}

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
        cout << "Sender: " << msg << endl;
        receiver(msg,key);
        //get_remainder(msg,crc8);
        
        
       // bool isErrorFree = check_crc(msg);

       // if (isErrorFree) {
      //      cout << "No error detected. Data is error-free." << endl;
       // } else {
      //      cout << "Error detected in the received data." << endl;
       // }

        cout << ">";
        string data;
        getline(cin, data);
        memset(&msg, 0, sizeof(msg)); //clear the buffer
        strcpy(msg, data.c_str());
        if(data == "exit")
        {
            //send to the client that server has closed the connection
            send(newSd, (char*)&msg, strlen(msg), 0);
            break;
        }
        //send the message to client
        bytesWritten += send(newSd, (char*)&msg, strlen(msg), 0);
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
