#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#include <cmath>
#include <fstream>
#include"tmwtypes.h"
#include"stdlib.h"

void modulate(vector<int> x){
	ofstream fp1;
	fp1.open("QAMDATA.txt");
	int n = x.size();
	cout<<"X size:"<<n<<endl;
	creal_T mod[n/6];
	int k=0;
	for(int i=0;i<n;i=i+6){
		if(x[i]==0 && x[i+1]==0 && x[i+2]==0){
			
			mod[k].re = -7;
		}
		else if(x[i]==0 && x[i+1]==0 && x[i+2]==1){
			mod[k].re = -5;
			
		}
		else if(x[i]==0 && x[i+1]==1 && x[i+2]==1){
			mod[k].re = -3;
			
		}
		else if(x[i]==0 && x[i+1]==1 && x[i+2]==0){
			mod[k].re = -1;
			
		}
		else if(x[i]==1 && x[i+1]==1 && x[i+2]==0){
			mod[k].re = 1;
			
		}
		else if(x[i]==1 && x[i+1]==0 && x[i+2]==0){
			mod[k].re = 3;
			
		}
		else if(x[i]==1 && x[i+1]==0 && x[i+2]==1){
			mod[k].re = 5;
			
		}
		else if(x[i]==1 && x[i+1]==1 && x[i+2]==1){
			mod[k].re = 7;
			
		}
		
		//*************For Imaginary************************
		
		
		if(x[i+3]==0 && x[i+4]==0 && x[i+5]==0){
			
			mod[k].im = -7;
		}
		else if(x[i+3]==0 && x[i+4]==0 && x[i+5]==1){
			mod[k].im = -5;
			
		}
		else if(x[i+3]==0 && x[i+4]==1 && x[i+5]==1){
			mod[k].im = -3;
			
		}
		else if(x[i+3]==0 && x[i+4]==1 && x[i+5]==0){
			mod[k].im = -1;
			
		}
		else if(x[i+3]==1 && x[i+4]==1 && x[i+5]==0){
			mod[k].im = 1;
			
		}
		else if(x[i+3]==1 && x[i+4]==0 && x[i+5]==0){
			mod[k].im = 3;
			
		}
		else if(x[i+3]==1 && x[i+4]==0 && x[i+5]==1){
			mod[k].im = 5;
			
		}
		else if(x[i+3]==1 && x[i+4]==1 && x[i+5]==1){
			mod[k].im = 7;
			
		}
		fp1<<mod[k].re<<" "<<mod[k].im<<endl;	
		k++;
		
	}
	cout<<"Num:"<<k<<endl;
	fp1.close();
}

vector<int> demodulate(){
	ifstream fp2;
	fp2.open("QAMDATA.txt");
	vector<int> dem;
	int temp;
	while(fp2>>temp){
		dem.push_back(temp);
		//cout<<temp<<" ";
		fp2>>temp;
		dem.push_back(temp);
		//cout<<temp<<endl;
	}
	cout<<"Dem size:"<<dem.size()<<endl;
	
	fp2.close();
	vector<int> a;
	cout<<"Init a size:"<<a.size()<<endl;
	int n = dem.size();
	int kk=0;
	for(int i=0;i<n;i=i+2){
		kk++;
		//cout<<"Init a size:"<<a.size()<<endl;
		switch (dem[i]){
			case -7:
            	
				a.push_back(0);
            	a.push_back(0);
            	a.push_back(0);
            	break;
	        case -5:
	            a.push_back(0);
            	a.push_back(0);
            	a.push_back(1);
            	break;
	        case -3:
	            a.push_back(0);
            	a.push_back(1);
            	a.push_back(1);
            	break;
	        case -1:
	            a.push_back(0);
            	a.push_back(1);
            	a.push_back(0);
            	break;
	        case 1:
	            a.push_back(1);
            	a.push_back(1);
            	a.push_back(0);
            	break;
	        case 3:
	            a.push_back(1);
            	a.push_back(0);
            	a.push_back(0);
            	break;
	        case 5:
	            a.push_back(1);
            	a.push_back(0);
            	a.push_back(1);
            	break;
	        case 7:
	            a.push_back(1);
            	a.push_back(1);
            	a.push_back(1);
            	break;
            default:
            	cout<<"Somewthing is wrong!!"<<endl;
			
		}
		
		
		switch (dem[i+1]){
			case -7:
            	a.push_back(0);
            	a.push_back(0);
            	a.push_back(0);
            	break;
	        case -5:
	            a.push_back(0);
            	a.push_back(0);
            	a.push_back(1);
            	break;
	        case -3:
	            a.push_back(0);
            	a.push_back(1);
            	a.push_back(1);
            	break;
	        case -1:
	            a.push_back(0);
            	a.push_back(1);
            	a.push_back(0);
            	break;
	        case 1:
	            a.push_back(1);
            	a.push_back(1);
            	a.push_back(0);
            	break;
	        case 3:
	            a.push_back(1);
            	a.push_back(0);
            	a.push_back(0);
            	break;
	        case 5:
	            a.push_back(1);
            	a.push_back(0);
            	a.push_back(1);
            	break;
	        case 7:
	            a.push_back(1);
            	a.push_back(1);
            	a.push_back(1);
            	break;
            default:
            	cout<<"Somewthing is wrong!! in 2nd loop"<<endl;
			
		}
	}
	cout<<"Size Of a:"<<a.size()<<" "<<kk<<endl;
	return a;
}


int main(){
	FILE *fp1;
	fp1 = fopen("new.bmp","rb");
	char code[1024];
	int n=0;
   	do{
		code[n]=(char)fgetc(fp1);
		
		n++;
    }while(!feof(fp1));

	int h[n];
    for(int i=0;i<n;i++){
    	h[i]=(code[i]+128);
    	
    	
	}
    cout<<endl<<"Count:"<<n<<endl;		
    vector<int> x;
	for(int i=0;i<n;i++){
		int a=h[i];
		int reva=x.size();
		int t=0;
		while(a||t<8){

			x.push_back(a%2);
			a=a/2;
			t++;	
		}

		reverse(x.begin()+reva,x.end());			
	}
	cout<<"Size of Binary:"<<x.size()<<endl;
	
	modulate(x);
	
	vector<int> xd;
	xd = demodulate();
	cout<<"XD Size:"<<xd.size()<<endl;
	vector<int>v;
	for(int i=0;i<n*8;i+=8){	
		int u=0;
		u+=xd[i]*pow(2,7);
		u+=xd[i+1]*pow(2,6);
		u+=xd[i+2]*pow(2,5);
		u+=xd[i+3]*pow(2,4);
		u+=xd[i+4]*pow(2,3);
		u+=xd[i+5]*pow(2,2);
		u+=xd[i+6]*pow(2,1);
		u+=xd[i+7]*pow(2,0);
		v.push_back(u);	
	}
	char q[n];
	for(int i=0;i<n;i++){
		q[i]=(char)(v[i]-128);	
	}
	cout<<"Done3"<<endl;
	FILE *fp5;
	fp5=fopen("finalcameraman.bmp","wb");
	for(int i=0;i<n;i++){
		fputc(q[i],fp5);
	}
	fclose(fp5);
	
	
	

	fclose(fp1);
	
	return 0;
}
