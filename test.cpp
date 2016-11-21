#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <bits/stdc++.h>

using namespace std;

#define MAX 10000
#define pb push_back

#define header "header"
#define macro "macro"
#define statement "statement"
#define start_brace "start_brace"
#define close_brace "close_brace"
#define loop "loop"
#define condition "condition"
#define function "function"





struct node{
	string type;
	string code_segment;
	int pos;
	int parent;
	vector<int>child;
}root;



vector<string> codes;
fstream myFile;
int node_idx;
vector<node> noded_code;
vector<int> tree[MAX];


string supported_char ="();{}''\"+=-*&|#%^?/<>,";
bool isChar(char x){
	if((x>='A' && x<='Z') || (x>='a' && x<='z')) return true;
	for(int i=0;i<supported_char.size();i++){
		if(x == supported_char[i]) return true;
	}
	return false;
}

bool starts_with(string x,string with){
	if(x.size()>with.size()) return false;

	for(int i=0;i<x.size();i++){
		if(x[i]!=with[i]) return false;
	}
	return true;

}



void store()
{
	string line;

    if (myFile.is_open())
    {
   	    while ( getline (myFile,line) )
    	{
      		// cout << line << '\n';
    		if(line.size()<1) continue;
      		codes.push_back(line + "\n");
    	}

    }

}

void printVector()
{
	for(int i=0; i<codes.size(); i++)
    {

    	cout << codes.at(i)<<endl;;
    }
}




node create_node(string line){

	node temp;
	temp.pos = node_idx++;
	temp.code_segment=line;

	if(starts_with("#include",line)==true){
		temp.type="header";
	}
	else if(starts_with("#define",line)==true){
		temp.type="macro";
	}
	else if(line[line.length()-1]==';'){
		temp.type = "statement";
	}
	else if(line.length()==1){
		if(line[0]=='{'){
			temp.type = "start_brace";
		}
		else temp.type="close_brace";
	}
	else if(line[line.length()-1]==')' || line[line.length()-1]=='{' || line[line.length()-1]=='e'){
		if(starts_with("for",line)==true || starts_with("while",line)==true || starts_with("do",line)==true){
			temp.type = "loop";
		}
		else if(starts_with("if",line)==true || starts_with("else",line)==true){
			temp.type= "condition";
		}
		else{
			temp.type = "function";
		}
	}
	return temp;

}


void dfs(int cur){
	if(tree[cur].size()>0)
		cout<<cur<<" -> ";
	for(int i=0;i<tree[cur].size();i++){
		cout<<tree[cur][i]<<' ';
	}
	if(tree[cur].size()>0)
		cout<<endl;
	for(int i=0;i<tree[cur].size();i++){
		if(tree[cur][i]!=cur) dfs(tree[cur][i]);
	}

}



void generate_tree(){


	int cur = 0;

	for(int i=0;i<codes.size();i++){
		string line = codes[i];
		node temp = create_node(line);
		noded_code.pb(temp);
//		cout<<line<<" -> "<<noded_code[i].pos<<' '<<noded_code[i].type<<endl;

		if(temp.type == "loop" || temp.type == "condition" || temp.type =="function"){
			noded_code[i].parent = cur;
			tree[cur].pb(temp.pos);
			cur = temp.pos;
		}
		else if(temp.type == "close_brace"){
			cur = noded_code[cur].parent;
		}
		else{
			tree[cur].pb(temp.pos);
			noded_code[i].parent=cur;
		}



	}
	cout<<endl;
	cout<<"Generated tree: "<<endl;
	dfs(0);



}



void trim()
{
	for(int j=0; j<codes.size(); j++)
    {

    	string line;
    	line = codes[j];

    	for(int i=0; i<line.size(); i++)
    	{
    		if(isChar(line[i])==true && i!=0){
    			line.erase(0,i);
    			break;
    		}
    		else if(isChar(line[i])==true) {
				break;
			}
    	}
    	for(int i=line.length()-1;i>=0;i--){
    		if(isChar(line[i])==false){
    			line.erase(i,1);
    		}
    		if(isChar(line[i])==true) break;
    	}
    	codes[j]=line;
    }
    // printVector();
}


vector<string> functions;
map<string,bool> functions_map;
map<string,string> functions_name;

void extract_functions(){
    for(int i=0;i<tree[0].size();i++){
        node temp = noded_code[tree[0][i]];
        string st="";
        if(temp.type==function){
            cout<<temp.code_segment<<endl;
            if(temp.code_segment[temp.code_segment.length()-1]!=')'){
                temp.code_segment.erase(temp.code_segment.length()-1,1);
            }
            bool flag = false;
            for(int j=0;temp.code_segment[j]!='(';j++){
                if(temp.code_segment[j]==' ') {
                    flag=true;
                    continue;
                }
                if(flag) st+=temp.code_segment[j];
            }
            functions.pb(st);
            functions_map[st]=true;
            functions_name[temp.code_segment]=st;
        }
    }
    cout<<endl;
    cout<<"Functions:"<<endl;
    for(int i=0;i<functions.size();i++){
        cout<<functions[i]<<endl;
    }
}




vector<string> global_variable;

void clean_global_variable(){
    for(int i=0;i<global_variable.size();i++){
        string temp = global_variable[i];

        if(temp[0]=='*') global_variable[i].erase(0,1);
        temp = global_variable[i];

        if(temp[temp.length()-1]==']'){
            for(int j=temp.length()-1;;j--){
                if(temp[j]=='['){
                    global_variable[i].erase(j,temp.length()-j);
                    break;
                }
            }
        }
    }
}



void parse_global_variable(string line){
    for(int i=0;i<line.length();i++){
        if(line[i]==' '){
            line.erase(0,i+1);

            break;
        }
    }
    for(int i=0;i<line.length();i++){
        if(line[i]==' ' || line[i]==';'){
            line.erase(line.begin()+i);
        }
    }

    string temp="";
    for(int i=0;i<line.length();i++){
        if(line[i]==','){
            global_variable.pb(temp);
            temp="";
            continue;
        }
        temp+=line[i];
    }
    if(temp!="") global_variable.pb(temp);

    clean_global_variable();
}


void extract_global_variable(){
    cout<<"started extraction"<<endl;
	for(int i=0;i<tree[0].size();i++){
		int pos = tree[0][i];
		node temp = noded_code[pos];
//        cout<<temp.type<< ' '<<temp.code_segment<<endl;
		if(temp.type == statement && temp.code_segment[temp.code_segment.length()-2]!=')'){
			parse_global_variable(temp.code_segment);
		}
	}

	cout<<endl;
	cout<<"Global variable"<<endl;
	for(int i=0;i<global_variable.size();i++){
		cout<<global_variable[i]<<endl;
	}
}

vector<int> fun_mat[MAX];

void function_matrix()
{
    cout<<"Function matrix started"<<endl;

    for(int i=0;i<tree[0].size();i++){
        node temp = noded_code[tree[0][i]];
        if(temp.type==function){
            queue<node> q;
            q.push(temp);
            while(!q.empty()){
                node top=q.front();
                q.pop();
//                cout<<top.code_segment<<"-> ";
                for(int j=0;j<tree[top.pos].size();j++){
                    node child = noded_code[tree[top.pos][j]];
//                    cout<<child.code_segment<<' '<<child.type<<',';
                    if(child.type==statement && child.code_segment[child.code_segment.length()-2]==')'){

                        string x="";
                        for(int k=0;k<child.code_segment.length();k++){
                            if(child.code_segment[k]=='('){
                                if(functions_map.find(x)!=functions_map.end()){
                                    fun_mat[top.pos].pb(child.pos);
                                    break;
                               }
                            }
                            x+=child.code_segment[k];
                        }


                    }
                    q.push(child);
                }
//                cout<<endl;
            }
        }
    }
    cout<<endl;
    for(int i = 0 ;i<tree[0].size();i++){
        node temp = noded_code[tree[0][i]];

        if(temp.type==function){
            cout<<temp.code_segment<<" -> ";
            for(int j=0;j<fun_mat[temp.pos].size();j++){
                cout<<noded_code[fun_mat[temp.pos][j]].code_segment <<' ';
            }
            cout<<endl;
        }
    }
}





int main()
{

	myFile.open("ForTestCode.c");

	store();
    // printVector();
    trim();
    generate_tree();
    extract_global_variable();

    extract_functions();
    function_matrix();

    myFile.close();

    return 0;

}
