#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <regex>
#include<string>
#include<bits/stdc++.h>
using namespace std;

class Token{

	public :
		string name;
		unordered_map<string, string>* mapValue;
		unordered_map<string, Token*>* mapToken;
		
		Token(){}
		Token(string name){
			this->name = name;
			mapToken = new unordered_map<string, Token*>();
		}
		
		void print(){
			cout<<"--------------Token----------------------"<<endl;
			cout<<" name : "<<name<<endl;

			for (auto itr = mapToken->begin(); itr != mapToken->end(); ++itr)
   	 		{
       		 		cout << "\n\t" << itr->first         	   << '\t' << &itr->second << '\n';
   			}
			
			for (auto itr = mapValue->begin(); itr != mapValue->end(); ++itr)
   	 		{
       		 		cout << "\n\t" << itr->first         	   << '\t' << itr->second << '\n';
   			}
    			cout<<"-------------------------------------" << endl;
		}

};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
        int hrml;
        int qno;
	stack<Token*> s1;
	unordered_map<string, Token *> treemapToken;
    	vector<string> query;

	cin>>hrml>>qno;

	string result;
	string ip="";
	string rootelement = "";

	getline(cin,result) ;
	// cout << result << endl;
	for(int i=1;i<=hrml;i++){
		getline(cin,result) ;
		ip += result;
	}

	for(int i=1;i<=qno;i++){
		getline(cin,result) ;
		query.push_back(result);
	}
        
	regex r1("(<[a-zA-Z0-9]+(( )[a-zA-Z0-9_]+( )*(=)( )*\"(([a-zA-Z0-9_!@#%&$]+)|([0-9]+\\.[0-9]+))\")*( )*>)|(<[a-zA-Z0-9]+( )*>)|(</[A-Za-z0-9]+>)"); //[a-zA-Z0-9]*
         
		regex tagname("<[a-zA-Z0-9]+");
		regex tagvalue("([a-zA-Z0-9_]+( )*(=)( )*\"(([a-zA-Z0-9_!@#%&$]+)|([0-9]+\\.[0-9]+))\")");
          	regex identifier("([+-]?([0-9]*[.])?[0-9]+)[$%]?|([A-Za-z0-9_!@#%&$]+)");
	

		auto word_Begin = sregex_iterator(ip.begin(), ip.end(), r1);
		auto word_End = sregex_iterator();
        
		for (auto token_iterator = word_Begin; token_iterator != word_End; token_iterator++ )
		{
		
		        string str1 = token_iterator->str();
			string tagname1 = "";
			Token* token1;

			//cout<<str1<<endl;
			//cout<<"before pop : "<<str1<<"  "<<str1.length()<<endl;	
			if(str1[1] == '/' && s1.size() > 0){

				string tagclose = str1.substr(2,str1.length() - 3);
				token1 = s1.top();
				//cout<<tagclose<<" compare pop "<<token1->name<<"  "<<str1<<" stack size "<<s1.size()<<endl;

				if(tagclose.compare(token1->name) == 0){
					s1.pop();
					if(s1.size() > 0){
						
						Token*  parent = s1.top();
						parent->mapToken->insert({token1->name,token1});
						//parent->print();
					}
					continue;
				}
				else{
					cout<<"Tag : "<<tagclose<<" not closed Syntax error"<<endl;
					exit(0);
				}
			}
		
			string str11 = "";
			auto word_Begin1 = sregex_iterator(str1.begin(), str1.end(), tagname);
			auto word_End1 = sregex_iterator();
			for (auto token_iterator1 = word_Begin1; token_iterator1 != word_End1; token_iterator1++ ){

			
				str11 = token_iterator1->str();  // "<tag1	
			
				tagname1 = str11.substr(1,str11.length() - 1);
				
				//cout<<"push :"<<str11<<"  tagname : "<<tagname1<<endl;

				token1 = new Token(tagname1);
				if(s1.empty()){
					treemapToken.insert({tagname1,token1});
				}
				s1.push(token1);
			}
		
			/*if(str11.length() == 0){
				outerloopflag = false;
				continue;
			}*/

			unordered_map <string,string> *valmap = new unordered_map<string,string>();

			auto word_Begin2 = sregex_iterator(str1.begin(), str1.end(), tagvalue);
			auto word_End2 = sregex_iterator();
			for (auto token_iterator2 = word_Begin2; token_iterator2 != word_End2; token_iterator2++ ){
				string str12 = token_iterator2->str();		
			
				//cout<<str12<<endl;
			
				auto word_Begin3 = sregex_iterator(str12.begin(), str12.end(), identifier);
				auto word_End3 = sregex_iterator();

				bool flag = true;
				string str123="";

				for (auto token_iterator3 = word_Begin3; token_iterator3 != word_End3; token_iterator3++ ){
				
					if(flag){
						str123 = token_iterator3->str();
						flag = false;
					}
					else{
						string str124 = token_iterator3->str();	
						//cout<<str123<<"  "<<str124<<endl;
						valmap->insert({str123,str124});
					}
				}
			
			}
			token1->mapValue = valmap;
			//token1->print();
        	}
    
	regex que1("([A-Za-z_]+[0-9A-Za-z_]*)|\\.|~");

	for(auto &it : query){
		string stq = it;
		//cout<<stq<<endl;
		
		bool foundflag = false;
		
		bool tagflag = false;
		bool valueflag = false;
		bool firstflag = true;
		string prev = "";
		Token* token2, *prevToken;

		auto word_Beginq1 = sregex_iterator(stq.begin(), stq.end(), que1);
        	auto word_Endq1 = sregex_iterator();
        	 for (auto token_iteratorq1 = word_Beginq1; token_iteratorq1 != word_Endq1; token_iteratorq1++ )
       		 {
			string strq12 = token_iteratorq1->str();
			//cout<<strq12<<endl;
			
			if(strq12.compare(".") == 0){
				tagflag = true;
				continue;
			}
			else if(strq12.compare("~") == 0){
				valueflag = true;
				continue;
			}			
			else if(tagflag){

					tagflag = false;				
					//prevToken->print();
					auto range = prevToken->mapToken->find(strq12);
					if(range != prevToken->mapToken->end()){
						prevToken = range->second;
						prev = strq12;
						continue;	
					}
					else{
						break;		
					}
				
			}
			else if(valueflag){
				valueflag = false;

				auto itvalue = prevToken->mapValue->find(strq12);
				//prevToken->print();
				if( itvalue != prevToken->mapValue->end() ){
						string ans = itvalue->second;
						prev = ans;
						foundflag = true;
					
				}
				break;					
			}
			else if(firstflag){
			
				firstflag = false;
				auto itrtreemapToken = treemapToken.find(strq12);
				if(itrtreemapToken == treemapToken.end()){
					break;
				}
				else{
					prevToken = itrtreemapToken->second;
					prev = strq12;
					continue;	
				}
			}
			
		}

		if(!foundflag){
			cout<<"Not Found!"<<endl;
		}
		else{
			cout<<prev<<endl;
		}
	}
	

    return 0;
}


/*

4 3
<tag1 value = "HelloWorld" name="hi">
<tag2 name = "Name1"></tag2>
<tag3></tag3>
</tag1>
tag1.tag2~name
tag1~name
tag1~value

*/


/*

test case 2


10 10
<a value = "GoodVal">
<b value = "BadVal" size = "10">
</b>
<c height = "auto">
<d size = "3">
<e strength = "2">
</e>
</d>
</c>
</a>
a~value
b~value
a.b~size
a.b~value
a.b.c~height
a.c~height
a.d.e~strength
a.c.d.e~strength
d~sze
a.c.d~size


o/p

GoodVal
Not Found!
10
BadVal
Not Found!
auto
Not Found!
2
Not Found!
3

*/



/*

case 4



o/p


123
43.4
hello
Not Found!
Hello
Universe!
World!
New
Not Found!
Not Found!
34
9.845
Not Found!
Not Found!


*/
