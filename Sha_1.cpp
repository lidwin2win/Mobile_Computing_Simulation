#include<iostream>
#include<bitset>
#include<string>
#include<string>
#include<bitset>
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

string H[5]={"67452301","EFCDAB89","98BADCFE","10325476","C3D2E1F0"};

string K[4]={"5A827999","6ED9EBA1","8F1BBCDC","CA62C1D6"};

/*
H[0] = "67452301";
H[1] = "EFCDAB89";
H[2] = "98BADCFE";
H[3] = "10325476";
H[4] = "C3D2E1F0";
*/

string change_hex_to_bin(string hex){
	
	string binary = "";
	
	string hex_to_bin[16] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
	
	for(int i=0;i<hex.length();i++){
		
		char c = hex[i];
		int index = c - '0';
		if(index > 9 ){
			index = c-'A' + 10;
		}
		
		binary.append(hex_to_bin[index]);
		
	}
	
	return binary;
}




string and_data(string lhs, string rhs){
       
       string ans="";
       
       for(int i=0 ;i< lhs.length();i++){
       
               if(lhs[i] == '1' && rhs[i] == '1'){
               
                         ans += '1';
                         
               }
               else{
               
                    ans += '0';
                    
               }
               
       }       
       
       return ans;
       
}

string or_data(string lhs, string rhs){
       
       string ans="";
       
       for(int i=0 ;i< lhs.length();i++){
       
               if(lhs[i] == '1' || rhs[i] == '1'){
               
                         ans += '1';
                         
               }
               else{
               
                    ans += '0';
                    
               }
               
       }       
       
       return ans;
       
}  

string not_data(string datum){
       
       string ans="";
       
       for(int i=0 ;i< datum.length();i++){
       
               if( datum[i] == '1' ){
               
                         ans += '0';
                         
               }
               else{
               
                    ans += '1';
                    
               }
               
       }       
       
       return ans;
       
}

string exor_data(string lhs, string rhs){
       
       string ans="";
       
       for(int i=0 ;i< lhs.length();i++){
       
               if(lhs[i] !=  rhs[i]){
               
                         ans += '1';
                         
               }
               else{
               
                    ans += '0';
                    
               }
               
       }       
       
       return ans;
       
}

string pad_msg(string msg){

       string pad ="";

       bitset<8> mybits;
 
       bitset<64> mybits2;
              
       for(int i=0;i<msg.size();i++){
       
               mybits = bitset<8>( msg[i] ) ;
       
               string temp = mybits.to_string<char,std::string::traits_type,std::string::allocator_type>();

               pad += temp;       
               
       }       
       
       pad = pad + '1';
       
       for(int j = pad.size(); j<512 - 64;j++){
       
               pad = pad + '0';
               
       }
       
       int length = msg.size() * 8;
       
       mybits2 = bitset<64>(length);
       
       string temp = mybits2.to_string<char,std::string::traits_type,std::string::allocator_type>();       
       
       //cout<<temp<<endl;
       
       //cout<<pad<<endl;
       
       
       pad += temp;
       
       //cout<<"padded msg is:"<<pad<<"\n\n";
       
       //cout<<"length of padded msg is: "<<pad.size()<<endl;
       
       
       return pad;
       
}


string lshift_data(string datum,int shifts){
       
       string ans=datum;
       
       for(int i=0;i<datum.size();i++){
               
               char rot = datum[i];
               
               int index = i-shifts;
               
               if(index < 0){ index += datum.size();} 
               
               ans[index] =datum[i];       
               
       }
       
       return ans;

}


string Words[80]={};

void fill_words(string padded){
     
     string temp="";
     
     for(int i=0;i<16;i++){
             temp = padded.substr(i*16*2,32);
             Words[i] = temp;
     }
     
     //for(int j=0;j<16;j++)cout<<"\n\nj-"<<j<<": "<<Words[j]<<endl;
     
     for(int t=16;t<80;t++){
             
                    Words[t] = lshift_data( exor_data( Words[t-3] , exor_data( Words[t-8] , exor_data( Words[t-14] , Words[t-16] )  ) ) , 1) ;
             
     }
     
     //for(int j=0;j<80;j++)cout<<"\n\nj-"<<j<<": "<<Words[j]<<endl;
     
}

long long int str_to_int(string binary){

    int length = binary.size();
	
	int power=0;
	
	long long int dec=0;
	
	for(int i=length-1 ; i>=0 ;i--){
		
		dec = dec + (  (binary[i] - '0') * (long long int)pow((double)2,power)  ) ;
		
		power++;
		
	}
	
	return dec;     
     
     
     
}

string add_data(string lhs,string rhs){

       long long int x = str_to_int(lhs);     
       
       long long int y = str_to_int(rhs);
       
       long long int z = (x+y)%((long long int)pow((double)2,32)) ;
       
       int l = lhs.size();
       
       bitset<32> mybits = bitset<32>(z);
       
       return mybits.to_string<char,std::string::traits_type,std::string::allocator_type>();
       
       
}

string func(string b , string c , string d, int t){

       if(t>=0&&t<=19)
                      return   or_data ( and_data(b,c), and_data(not_data(b),d) );
       
       else if(t>=20&&t<=39)
                      return  exor_data(b,exor_data(c,d));
       
       else if(t>=40 && t<=59)
                     return   or_data( and_data(b,c) , or_data( and_data(b,d) , and_data(c,d) ) );
       
       else       
                      return  exor_data(b,exor_data(c,d));       
}


string bin_to_hex(string);

int main(){
	
	///cout<<func("101","111","000",60);
	
	
	
    
    for(int i=0;i<5;i++){
        H[i] = change_hex_to_bin(H[i]);
    //    cout<<H[i]<<endl;    
        }
        
    for(int i=0;i<4;i++){
      
        K[i] = change_hex_to_bin(K[i]);
        //cout<<K[i]<<endl;
            
    }
    
//    cout<<lshift_data("0111010101",5)<<endl;

    string msg = "thankyougod";//godisgood";//"abc";
    
	
    
    string padded = pad_msg(msg);
    
    //cout<<padded<<endl;
    
    fill_words(padded);
    
    for(int i=0;i<16;i++){
    	
    	//cout<<Words[i]<<endl;
    	cout<<"W["<<i<<"]= "<<bin_to_hex( Words[i] )<<endl;
    	
    	//break;
	}
    
    string abcde[5];
    
    for(int i=0;i<5;i++){
    
            abcde[i] = H[i];
            
    }
    
    string temp="";
    
    for(int t=0;t<80;t++){
    	
			/*    	
    	     cout<<K[0]<<"   "<<str_to_int(K[0] )<<endl;
             
             cout<<Words[t]<<"   "<<str_to_int( Words[t] )<<endl;
             
             cout<<abcde[4]<<"   "<<str_to_int( abcde[4] )<<endl;
             
             //cout<<(  func(abcde[1],abcde[2],abcde[3] , t) )<<endl;
             
             cout<<func(abcde[1],abcde[2],abcde[3] , t)<<"   "<<str_to_int(  func(abcde[1],abcde[2],abcde[3] , t) )<<endl;
             
             cout<<lshift_data(abcde[0],5)<<"   "<<str_to_int( lshift_data(abcde[0],5) )<<endl;
             
             long long int y = str_to_int(K[0]) + str_to_int( Words[t] )+ str_to_int( abcde[4] )+ str_to_int(  func(abcde[1],abcde[2],abcde[3] , t) ) + str_to_int( lshift_data(abcde[0],5) );
             
             long long int z = y % (long long int)pow(2,32);
             
             cout<<"Modulo ans is:"<<z<<endl;*/
            
            
            if(t>=0&&t<=19)
            temp =  add_data(  lshift_data(abcde[0],5) , add_data( func(abcde[1],abcde[2],abcde[3] , t), add_data( abcde[4] , add_data(Words[t],K[0]) ) )  );
            
            else if(t>=20 && t<=39)
            temp =  add_data(  lshift_data(abcde[0],5) , add_data( func(abcde[1],abcde[2],abcde[3] , t), add_data( abcde[4] , add_data(Words[t],K[1]) ) )  );
            
            else if(t>=40 && t<=59)
            temp =  add_data(  lshift_data(abcde[0],5) , add_data( func(abcde[1],abcde[2],abcde[3] , t), add_data( abcde[4] , add_data(Words[t],K[2]) ) )  );
            
            else
            temp =  add_data(  lshift_data(abcde[0],5) , add_data( func(abcde[1],abcde[2],abcde[3] , t), add_data( abcde[4] , add_data(Words[t],K[3]) ) )  );
            //cout<<temp;
            
            abcde[4] = abcde[3]; //TEMP = S^5(A) + f(t;B,C,D) + E + W(t) + K(t);//
//E = D; D = C; C = S^30(B); B = A; A = TEMP;
  
             abcde[3] = abcde[2];
             
             abcde[2] = lshift_data(abcde[1],30);
             
             
             abcde[1] = abcde[0];
             
             abcde[0] = temp;
             
             
             cout<<"t= "<<t<<": "<<bin_to_hex(abcde[0])<<"  "<<bin_to_hex(abcde[1])<<"  "<<bin_to_hex(abcde[2])<<"  "<<bin_to_hex(abcde[3])<<"  "<<bin_to_hex(abcde[4])<<"\n\n";
             
             //cout<<"\n#####################################################\n";

             
             
             //if(t==1)
             //break;
            
    }
    
    
    for(int i=0;i<5;i++){
    
            H[i] = add_data(H[i] , abcde[i] );
            
    }
    
    cout<<"\n\n\n";
    cout<<H[0]<<H[1]<<H[2]<<H[3]<<H[4]<<endl;
    
    cout<<"\n\nThe Sum for the msg is: \n\n";
    
    cout<<bin_to_hex(H[0]+H[1]+H[2]+H[3]+H[4])<<"\n\n";
    
    
    //system("pause");
    
    return 0;
    
}


string bin_to_hex(string bin){
	
	//cout<<bin.size()<<endl;
	
	char hexa[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	
	string ans="";
	
	for(int i=0;i<bin.size(); i = i+4){
		
		string temp = bin.substr(i,4);
	
		int index = (int)str_to_int(temp);
		
		ans += hexa[index];
		
		
	}
	
	return ans;
	
}

/*

070F641AEEE23C12BC6B1A41E8186F79F6182B8F
 70F641AEEE23C12BC6B1A41E8186F79F6182B8F

01100010011000111000000001100001
01100010011000111000000001100001
01100010011000111000000001100001

01100001011000100110001110000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000011

01100001011000100110001110000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000011



*/
