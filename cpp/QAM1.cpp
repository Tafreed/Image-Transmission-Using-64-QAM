#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#include <cmath>
#include <fstream>
#include"tmwtypes.h"
#include"stdlib.h"
#include <algorithm>
using namespace std;

void modulate(vector<int> x){
	ofstream fp1;
	fp1.open("QAMDATA.txt");

	int n = x.size();
	cout << "X size: " << n << endl;
	
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
		
		/************* For Imaginary *************/
		
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

		// Writes QAMDATA.txt with zero noise assumption.
		fp1 << mod[k].re << " " << mod[k].im << endl;
 		k++;
	}

	cout << "Num:" << k << endl;
	fp1.close();
}
void create_noise_data(int noise_size){
	// random seed.
	srand(2);
	
	// length of sequence.
	int n = noise_size;

	float x1[n], x2[n], x3[n], x4[n], x5[n];
	float y[n];
	
	for (int i = 0; i < n; i++) {
		x1[i] = (float)rand() / (float)RAND_MAX;
		x2[i] = (float)rand() / (float)RAND_MAX;
		x3[i] = (float)rand() / (float)RAND_MAX;
		x4[i] = (float)rand() / (float)RAND_MAX;
		x5[i] = (float)rand() / (float)RAND_MAX;
	
		y[i] = (x1[i] + x2[i] + x3[i] + x4[i] + x5[i]) / n;
	}
	
	// write file.
	ofstream outfile("gnoise.txt");
	
	for (int i = 0; i < n; i++) {
		outfile << y[i] << "\n";
	}
	
	outfile.close();
}

void add_noise_data(int noise_size) {
	ifstream fp1;
	fp1.open("QAMDATA.txt");

	create_noise_data(noise_size);

	ifstream fp2;
	fp2.open("gnoise.txt");

	ofstream fp3;
	fp3.open("QAMDATA_WITH_NOISE.txt");

	vector<double> noise;
	double num;

	vector<int> qam;
	int temp;

	while (fp1 >> temp) {
    	
    	qam.push_back(temp);
	}

	while (fp2 >> num) {
		
		noise.push_back(num);
	}

	cout << "Noise size: " << noise.size() << endl;
	cout << "QAM Data size: " << qam.size() << endl;
	int i=0;
	for (i = 0; i < noise.size(); i += 2) {
    	fp3 << qam[i]+noise[i] << " " << qam[i+1]+noise[i+1] << "\n";
    	
	}
	cout<<"Loop:" <<i<<endl;
	fp3.close();
}

vector<int> demodulate(){
	ifstream fp2;
	fp2.open("QAMDATA_WITH_NOISE.txt");

	vector<int> dem;
	float temp;

	while(fp2 >> temp) {
		dem.push_back(round(temp));
		//cout << round(temp) << " ";
		fp2 >> temp;
		dem.push_back(round(temp));
		//cout << round(temp) << endl;
	}
	cout << "Dem size:" << dem.size() << endl;
	
	fp2.close();
	vector<int> a;
	cout << "Init a size: " << a.size() << endl;
	int n = dem.size();
	int kk=0;
	for(int i=0;i<n;i=i+2){
		kk++;
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
            	cout << "Error!" <<endl;
		}

		switch (dem[i+1]) {
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
            	cout << "Error in 2nd loop!"<< endl;
		}
	}

	// cout << "Size of a: " << a.size() << " " << kk << endl;
	cout << "Size of a: " << a.size() << endl;
	return a;
}

int main() {
	
	FILE *fp1;
	fp1 = fopen("new.bmp","rb");
	
	char code[1024];
	int n=0;

   	do {
		code[n] = (char)fgetc(fp1);
		//cout<<code[n]<<endl;
		n++;
    } while(!feof(fp1));

	int h[n];

    for (int i=0;i<n;i++) {
    	h[i] = (code[i] + 128);
	}
	cout << endl << "Count: " << n << endl;		
    
	vector<int> x;
	
	for (int i=0;i<n;i++) {
		int a = h[i];
		int reva = x.size();
		int t = 0;
		while (a || t < 8) {
			x.push_back(a%2);
			a=a/2;
			t++;	
		}
		reverse(x.begin()+reva,x.end());			
	}
	cout << "Size of Binary: " << x.size() << endl;
	
	// creal_T mod[x.size()/6] = modulate(x);
	// creal_T mod[2] = modulate(x);
	// cout << mod[1] << endl << mod[2] << endl;

	// Modulate creates QAMDATA.txt with zero noise.
	modulate(x);

	// To create QAMDATA_WITH_NOISE.txt
	add_noise_data(x.size()/3);
	
	vector<int> xd;
	xd = demodulate();
	cout << "XD Size: " << xd.size() << endl;

	vector<int> v;
	for (int i=0;i < n*8; i+=8) {	
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
	for (int i=0; i<n; i++) {
		q[i] = (char)(v[i] - 128);	
	}
	cout << "Re-constructing the image....." << endl;

	//this_thread::sleep_for(chrono::milliseconds(3000));
	cout << "Done!" << endl;
	
	FILE *fp5;
	fp5 = fopen("finalcameraman.bmp","wb");
	
	for (int i=0; i<n; i++){
		fputc(q[i],fp5);
	}

	fclose(fp5);
	fclose(fp1);

	return 0;
}
