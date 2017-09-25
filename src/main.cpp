#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <valarray>
#include <iomanip>
#include <ctime>

#include "binarybuffer.h"
#include "mistake.h"

using std::cout;
using std::cerr;
using std::endl;

template<typename T>
void checker(const T& v1, const T& v2){
	if ( v1 == v2 )
		std::cout << "equal" << std::endl;
	else{
		std::cout << "NOT EQUAL: v1 = " << v1 << ", v2 = " << v2 << std::endl;
	}
}

template<typename T>
void checker(const std::vector<T>& vec1, const std::vector<T>& vec2){
	if ( vec1 == vec2 ){
		std::cout << "equal vectors" << std::endl;
	}
	else{
		std::cout << "NOT EQUAL:" << std::endl;
		std::cout << "  vec1 = [";
		for(size_t i=0; i < vec1.size(); ++i){
			std::cout << " " << vec1[i];
		}
		std::cout << "]" << std::endl;

		std::cout << "  vec2 = [";
		for(size_t i=0; i < vec2.size(); ++i){
			std::cout << " " << vec2[i];
		}
		std::cout << "]" << std::endl;
	}
}

template<typename T>
void checker(const std::valarray<T>& vec1, const std::valarray<T>& vec2){
	bool equal = true;
	if ( vec1.size() == vec2.size() ){
		for(size_t i=0; i < vec1.size(); ++i){
			if ( vec1[i] != vec2[i] ){
				equal = false;
				break;
			}
		}
	}
	else
		equal = false;

	if ( equal ){
		std::cout << "equal valarrays" << std::endl;
	}
	else{
		std::cout << "NOT EQUAL:" << std::endl;
		std::cout << "  val1 = [";
		for(size_t i=0; i < vec1.size(); ++i){
			std::cout << " " << vec1[i];
		}
		std::cout << "]" << std::endl;

		std::cout << "  val2 = [";
		for(size_t i=0; i < vec2.size(); ++i){
			std::cout << " " << vec2[i];
		}
		std::cout << "]" << std::endl;
	}
}

void checker(const char* s1, const char* s2){
	if (! std::strcmp(s1, s2) )
		std::cout << "equal" << std::endl;
	else{
		std::cout << "NOT EQUAL: s1 = " << s1 << ", s2 = " << s2 << std::endl;
	}
}


void errors_test(const std::string& filenameBin){
	std::cout << "ERROR TEST starts" << endl;

	std::ofstream foutBin;

	foutBin.open(filenameBin, std::ios::out | std::ios::binary);
	if  (!foutBin.is_open())
		print_mistake(__FUNCTION__, __LINE__, __FILE__, "can\'t open file with name\n" + filenameBin);

	BinaryBufferOutS binbuf(foutBin);

	int vi = 3434;
	float vf = 34.3353;
	double vd = 555444.34234234;
	const char* cs = "Hello, world!";
	std::string cpps = "I\'m prohibited person";
	size_t N = 20;
	std::vector<float> vecf(N);
	std::valarray<double> vald(N);

	for(size_t i=0; i < N; ++i){
		vecf[i] = i * 3.434;
		vald[i] = i * 99.232333;
	}

	std::cout << std::setprecision(15);

	binbuf << vi << vf << vd << cs << cpps << vecf << vald;
	binbuf.flushIt();

	foutBin.close();

	// -------------------------------------------------
	std::cout << std::endl << "EQUAL OR NOT:" << std::endl << std::endl;

	std::ifstream fin;
	fin.open(filenameBin, std::ios::in | std::ios::binary );

	int viR = 0;
	float vfR = 0;
	double vdR = 0;
	char* csR = nullptr;
	csR = new char[std::strlen(cs) + 1];
	for(size_t i=0; i <= std::strlen(cs); ++i){
		csR[i] = '\0';
	}

	std::string cppsR;
	cppsR.resize(cpps.size());
	std::vector<float> vecfR(N);
	std::valarray<double> valdR(N);

	fin.read(reinterpret_cast<char*>(&viR), sizeof(int));
	fin.read(reinterpret_cast<char*>(&vfR), sizeof(float));
	fin.read(reinterpret_cast<char*>(&vdR), sizeof(double));
	fin.read(reinterpret_cast<char*>(csR), std::strlen(cs));
	fin.read(reinterpret_cast<char*>(&cppsR[0]), cppsR.size());
	fin.read(reinterpret_cast<char*>(vecfR.data()), vecfR.size()*sizeof(float));
	fin.read(reinterpret_cast<char*>(&valdR[0]), valdR.size()*sizeof(double));

	checker(vi, viR);
	checker(vf, vfR);
	checker(vd, vdR);
	checker(cs, csR);
	checker(cpps, cppsR);
	checker(vecf, vecfR);
	checker(vald, valdR);

	fin.close();

	// ------------------------------- TEST INbuffer
	std::cout << std::endl << "TEST in buffer:\n";

	viR = 0;
	vfR = 0;
	vdR = 0;
	for(size_t i=0; i <= std::strlen(cs); ++i){
		csR[i] = '\0';
	}
	cppsR.clear();
	cppsR = "";
	cppsR.resize( cpps.size() );
	for(size_t i=0; i < vecfR.size(); ++i){
		vecfR[i] = 0;
	}
	for(size_t i=0; i < valdR.size(); ++i){
		valdR[i] = 0;
	}

	fin.open(filenameBin, std::ios::in | std::ios::binary);

	fin.read(reinterpret_cast<char*>(&viR), sizeof(int));
	fin.read(reinterpret_cast<char*>(&vfR), sizeof(float));
	fin.read(reinterpret_cast<char*>(&vdR), sizeof(double));
	fin.read(reinterpret_cast<char*>(csR), std::strlen(cs));
	fin.read(reinterpret_cast<char*>(&cppsR[0]), cppsR.size());
	fin.read(reinterpret_cast<char*>(vecfR.data()), vecfR.size()*sizeof(float));
	fin.read(reinterpret_cast<char*>(&valdR[0]), valdR.size()*sizeof(double));

	BinaryBufferInS binbufin(fin);

	binbufin >> viR >> vfR >> vdR >> csR >> cppsR >> vecfR >> valdR;

	checker(vi, viR);
	checker(vf, vfR);
	checker(vd, vdR);
	checker(cs, csR);
	checker(cpps, cppsR);
	checker(vecf, vecfR);
	checker(vald, valdR);

	fin.close();

	delete[] csR;
	std::cout << "ERROR TEST FINISHED" << endl;
}

void time_test(const std::string& filename, const std::string& filenameBin){
	std::cout << "TIME TEST STARTS" << endl;

	using VecType = float;

	std::ofstream fout;
	fout.open(filename, std::ios::out);
	if  (!fout.is_open())
		print_mistake(__FUNCTION__, __LINE__, __FILE__, "can\'t open file with name\n" + filenameBin);

	std::ofstream foutBin;
	foutBin.open(filenameBin, std::ios::out | std::ios::binary);
	if  (!foutBin.is_open())
		print_mistake(__FUNCTION__, __LINE__, __FILE__, "can\'t open file with name\n" + filenameBin);

	size_t N = 10000;
	std::vector<VecType> vecf(N);
	std::valarray<VecType> valf(N);
	VecType sqrtFirst = std::sqrt(2.0);
	VecType sqrtSecond = std::sqrt(3.0);
	for(size_t i=0; i < vecf.size(); ++i){
		vecf[i] = i * sqrtFirst;
		valf[i] = i * sqrtSecond;
	}

	long long int t1,t2,dt,dtBin;
	size_t Nloops = 4;

	std::cout << "VECTOR TEST:" << endl;

	cout << "usual vector writing:" << endl;
	dt = 0;
	for(size_t il = 0; il < Nloops; ++il){
		t1 = clock();
		for(size_t i=0; i < vecf.size(); ++i){
			fout << vecf[i];
		}
		fout << std::flush;
		t2 = clock();
		dt += t2 - t1;

		sqrtFirst = std::sqrt( (il+1) * sqrtFirst );
		std::cout << "\t\tsqrtFirst = " << sqrtFirst << ", loop finished" << std::endl;
		for(size_t i=0; i < vecf.size(); ++i){
			vecf[i] *= sqrtFirst;
		}
	}

	cout << "binary vector writing:" << endl;
	dtBin = 0;
	sqrtFirst = std::sqrt(2.0);
	BinaryBufferOutS binBufOut(foutBin);
	for(size_t i=0; i < vecf.size(); ++i){
		vecf[i] = i * sqrtFirst;
	}
	for(size_t il = 0; il < Nloops; ++il){
		t1 = clock();
		binBufOut << vecf;
		binBufOut.flushIt();
		t2 = clock();
		dtBin += t2 - t1;

		sqrtFirst = std::sqrt( (il+1) * sqrtFirst );
		std::cout << "\t\tsqrtFirst = " << sqrtFirst << ", loop finished" << std::endl;
		for(size_t i=0; i < vecf.size(); ++i){
			vecf[i] *= sqrtFirst;
		}
	}

	fout.close();
	foutBin.close();

	std::cout << "time of usual writing  = " << static_cast<double>(dt) / CLOCKS_PER_SEC << " sec" << endl;
	std::cout << "time of binary writing = " << static_cast<double>(dtBin) / CLOCKS_PER_SEC << " sec" << endl;

	std::cout << "VECTOR TEST FINISHED" << endl;

	std::cout << "TIME TEST FINISHED" << std::endl;
}

int main() {

	errors_test("testBin.txt");
	std::cout << "------------------------------------------------------------" << endl;
	time_test("timeTest.txt", "timeTestBin.txt");

	return 0;
}
