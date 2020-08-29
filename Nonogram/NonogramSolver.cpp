#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <set>
#include <string>
using namespace std;
#define pb push_back
vector <int> row[107];
vector <int> column[107];
vector <string> perms[107];
int T[107][107],n,m;
void copyArray(int t[107][107],int tab[107][107]){
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      tab[i][j] = t[i][j];
    }
  }
}
bool checkIfCorrect(string name,vector <int> needed,int limit){
  int akt = 0,pos = 0;
  bool doIHave = 0;
  for(int i=0;i<name.size();i++){
    if(name[i]=='1'){
      akt++;
      if(pos >= needed.size() || akt>needed[pos]){return false;}
      doIHave = 1;
    } else {
      if(doIHave==1){
        if(pos < needed.size() && akt != needed[pos]){
          return false;
        } else if(pos < needed.size() && akt == needed[pos]) {
          pos++;
        } else {
          return false;
        }
      }
      akt = 0;
      doIHave = 0;
    }
  }
  int sum = 0;
  for(int i=pos;i<needed.size();i++){sum+=needed[i];}
  if((limit-name.size()+1)<(needed.size()-pos+sum-akt)){
    //cout << limit-name.size() << " " << (needed.size()-pos+sum-akt) << "\n";
    //cout << limit << " " << name.size() << " " << name << " " << needed.size() << " " << pos << " " << sum << " " << akt << "\n";
    // for(int i=0;i<needed.size();i++){
    //   cout << needed[i] << " ";
    // }
    // cout << "\n\n";
    return false;
  }
  return true;
}
bool checkIfReallyIsCorrect(string name,vector <int> needed){
  int akt = 0,pos = 0;
  bool doIHave = 0;
  for(int i=0;i<name.size();i++){
    if(name[i]=='1'){
      akt++;
      if(pos>= needed.size() || akt>needed[pos]){return false;}
      doIHave = 1;
    } else {
      if(doIHave==1){
        if(pos < needed.size() && akt != needed[pos]){
          return false;
        } else if(pos < needed.size() && akt == needed[pos]) {
          pos++;
        } else {
          return false;
        }
      }
      akt = 0;
      doIHave = 0;
    }
  }
  if(doIHave==0){
    if(pos==needed.size()){
      return true;
    } else {
      return false;
    }
  } else {
    if(pos == needed.size()-1 && akt==needed[pos]){
      return true;
    } else {
      return false;
    }
  }
}
bool alreadySolved(){
  for(int i=0;i<n;i++){
    string a = "";
    for(int j=0;j<m;j++){
      if(T[i][j]==1){a+="1";}
      else if(T[i][j]==0){return false;}
      else{a+="0";}
    }
    if(!checkIfReallyIsCorrect(a,row[i])){return false;}
  }
  for(int i=0;i<m;i++){
    string a = "";
    for(int j=0;j<n;j++){
      if(T[j][i]==1){a+="1";}
      else if(T[j][i]==0){return false;}
      else{a+="0";}
    }
    if(!checkIfReallyIsCorrect(a,column[i])){return false;}
  }
  return true;
}
void reccurGenPermsRow(vector <string> permut[107],int idx,int pos,string permutation){//CONDI SHOULD BE FINE
  if(pos==m){
    if(!checkIfReallyIsCorrect(permutation,row[idx])){return;}
    permut[idx].pb(permutation);
    return;
  }
  if(T[idx][pos]==1){
    permutation+="1";
    if(checkIfCorrect(permutation,row[idx],m)){
      reccurGenPermsRow(permut,idx,pos+1,permutation);
    } else {
      return;
    }
    permutation.pop_back();
  } else if(T[idx][pos]==-1){
    permutation+="0";
    if(checkIfCorrect(permutation,row[idx],m)){
      reccurGenPermsRow(permut,idx,pos+1,permutation);
    } else {
      return;
    }
    permutation.pop_back();
  } else {
    permutation+="1";
    if(checkIfCorrect(permutation,row[idx],m)){
      reccurGenPermsRow(permut,idx,pos+1,permutation);
    }
    permutation.pop_back();
    permutation+="0";
    if(checkIfCorrect(permutation,row[idx],m)){
      reccurGenPermsRow(permut,idx,pos+1,permutation);
    }
    permutation.pop_back();
  }
}
void genPermsRow(vector <string> permut[107]){
  for(int i=0;i<n;i++){
    reccurGenPermsRow(permut,i,0,"");
  }
}
void reccurGenPermsColumn(vector <string> permut[107],int idx,int pos,string permutation){//CONDI SHOULD BE FINE
  if(pos==n){
    if(!checkIfReallyIsCorrect(permutation,column[idx])){return;}
    permut[idx].pb(permutation);
    return;
  }
  if(T[pos][idx]==1){
    permutation+="1";
    if(checkIfCorrect(permutation,column[idx],n)){
      reccurGenPermsColumn(permut,idx,pos+1,permutation);
    } else {
      return;
    }
    permutation.pop_back();
  } else if(T[pos][idx]==-1){
    permutation+="0";
    if(checkIfCorrect(permutation,column[idx],n)){
      reccurGenPermsColumn(permut,idx,pos+1,permutation);
    } else {
      return;
    }
    permutation.pop_back();
  } else {
    permutation+="1";
    if(checkIfCorrect(permutation,column[idx],n)){
      reccurGenPermsColumn(permut,idx,pos+1,permutation);
    }
    permutation.pop_back();
    permutation+="0";
    if(checkIfCorrect(permutation,column[idx],n)){
      reccurGenPermsColumn(permut,idx,pos+1,permutation);
    }
    permutation.pop_back();
  }
}
void genPermsColumn(vector <string> permut[107]){
  for(int i=0;i<m;i++){
    reccurGenPermsColumn(permut,i,0,"");
  }
}
int makeDeductionRow(vector <string> permut[107]){
  int deducedRow = 0;
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      char base = permut[i][0][j];
      bool canBeDeduced = 1;
      for(int k=1;k<permut[i].size();k++){
        if(permut[i][k][j] != base){
          canBeDeduced = 0;
          break;
        }
      }
      if(canBeDeduced==1){
        if(T[i][j]==0){
          deducedRow++;
        }
        if(permut[i][0][j] == '1'){ T[i][j] = 1; }
        else { T[i][j] = -1; }
      }
    }
  }
  return deducedRow;
}
int makeDeductionColumn(vector <string> permut[107]){
  int deducedColumns = 0;
  for(int i=0;i<m;i++){
    for(int j=0;j<n;j++){
      char base = permut[i][0][j];
      bool canBeDeduced = 1;
      for(int k=1;k<permut[i].size();k++){
        if(permut[i][k][j] != base){
          canBeDeduced = 0;
          break;
        }
      }
      if(canBeDeduced==1){
        if(T[j][i]==0){
          deducedColumns++;
        }
        if(permut[i][0][j]=='1'){ T[j][i] = 1; }
        else { T[j][i] = -1; }
      }
    }
  }
  return deducedColumns;
}
void printState(){
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      if(T[i][j]==-1){cout << "." << " ";}
      else if(T[i][j]==1){cout << "#" << " ";}
      else {cout << "?" << " ";}
    }
    cout << "\n";
  }
  cout << "\n";
}
pair <int,bool> solveIter(){
  int ammountOfDeduced = 0;
  for(int i=0;i<m;i++){
    perms[i].clear();
  }
  genPermsRow(perms);
  for(int i=0;i<n;i++){
    if(perms[i].size()==0){
      return make_pair(ammountOfDeduced,false);
    }
  }
  ammountOfDeduced+=makeDeductionRow(perms);
  for(int i=0;i<n;i++){
    perms[i].clear();
  }
  genPermsColumn(perms);
  for(int i=0;i<m;i++){
    if(perms[i].size()==0){
      return make_pair(ammountOfDeduced,false);
    }
  }
  ammountOfDeduced+=makeDeductionColumn(perms);
  return make_pair(ammountOfDeduced,true);
}
int counter = 0;
bool solve(){
  while(!alreadySolved()){
    pair <int,bool> maybeBackTrack = solveIter();
    if(maybeBackTrack.second == false){
      return false;
    }
    //printState();
    if(maybeBackTrack.first==0){
      bool found = false;
      for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
          if(T[i][j]==0){
            int TAB[107][107];
            copyArray(T,TAB);
            T[i][j] = 1;
            if(solve()==1){return true;}
            else{
              copyArray(TAB,T);
              T[i][j]=-1;
            }
            found = 1;
            break;
          }
        }
        if(found == true){
          break;
        }
      }
    }
  }
  return true;
}
int main(){
  ios_base::sync_with_stdio(0);
  cout.tie(0);
  fstream file;
  file.open("zad_input.txt");
  file >> n >> m;
  char c;
  file.get(c);
  for(int i=0;i<n;i++){
    file.get(c);
    while(c!='\n'){
      int a = c - '0';
      file.get(c);
      if(c != ' ' && c != '\n'){
        int b = c - '0';
        row[i].pb(a*10+b);
        file.get(c);
        if(c == ' '){
          file.get(c);
        }
      } else {
        if(c == ' '){
          file.get(c);
        }
        row[i].pb(a);
      }
    }
  }
  for(int i=0;i<m;i++){
    file.get(c);
    while(c!='\n'){
      int a = c - '0';
      file.get(c);
      if(c != ' ' && c != '\n'){
        int b = c - '0';
        column[i].pb(a*10+b);
        file.get(c);
        if(c == ' '){
          file.get(c);
        }
      } else {
        if(c == ' '){
          file.get(c);
        }
        column[i].pb(a);
      }
    }
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      T[i][j] = 0;
    }
  }
  solve();
  ofstream out;
  out.open("zad_output.txt");
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      if(T[i][j]==-1){out << ".";}
      else if(T[i][j]==1){out << "#";}
    }
    out << "\n";
  }
  out.close();
  file.close();
}
