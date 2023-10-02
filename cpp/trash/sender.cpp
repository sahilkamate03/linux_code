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


#include <bits/stdc++.h>
using namespace std;

const string crc8 = "100000111";

bool is_binary(string& str){
	for(char& c:str){
		if(!(c=='0'||c=='1')) return false;
	}
	return true;
}

string convert_to_binary(string& str){
	string ans = "";
	for(char& ch: str){
		int x = (int)ch;
		string curr_byte = "";
		while(x>0){
			curr_byte+=(x%2?'1':'0');
			x/=2;
		}
		while(curr_byte.length()<8) curr_byte.push_back('0');
		reverse(curr_byte.begin(), curr_byte.end());
		ans+=curr_byte;
	}
	
	return ans;
}

string get_remainder(string src, string divisor = crc8){
	
	int r = divisor.length();
	
	string code = src;
	for(int i=0;i<r-1;i++){
		code.push_back('0');
	}
	
	for(int i=0;i+r-1<code.length();i++){
		
		if(code[i]=='0') continue;
		
		for(int j=0;j<r;j++){
			code[i+j] = (code[i+j]==divisor[j])?'0':'1';
		}
	}
	return code.substr(src.length());
}

string generate_crc_code(string src, string divisor = crc8){

    cout<<"Data : "<<convert_to_binary(src)<<endl;
    string r = get_remainder(src,divisor);  
    cout<<"Remainder : "<<r<<endl;
	if(!is_binary(src)) src = convert_to_binary(src);
    
	cout<<"code : "<<src+r<<endl;
	return src+r;
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
        cout << ">";
        string data;
        cout<<"Enter message to send : ";
        getline(cin, data);
        data = generate_crc_code(data,crc8);

        memset(&msg, 0, sizeof(msg));//clear the buffer
        strcpy(msg, data.c_str());
        if(data == "exit")
        {
            send(clientSd, (char*)&msg, strlen(msg), 0);
            break;
        }
        bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
        cout << "Awaiting server response..." << endl;
        memset(&msg, 0, sizeof(msg));//clear the buffer
        bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);
        if(!strcmp(msg, "exit"))
        {
            cout << "Server has quit the session" << endl;
            break;
        }
        cout << "Server: " << msg << endl;
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
