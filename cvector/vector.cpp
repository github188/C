#include <iostream>
#include <vector>
#include <allocator>

template<class _Ty, class _A = allocator<_Ty> >
class m207_vector {

};

int main(int argc, char* argv[])
{
	std::vector<int> vt;
	vt.push_back(5);
	vt.push_back(1);
	vt.push_back(9);
	std::cout<<"Hello vector"<<std::endl;
	std::cout<<"size is "<<vt.size()<<std::endl;
	std::cout<<"element is:"<<std::endl;
	int count = vt.size();
	for (int i=0; i<count; i++)
		std::cout<<vt.at(i)<<std::endl;
	return 0;
}
