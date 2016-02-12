#ifndef _DSETS_H_
#define _DSETS_H_
#include <vector>
class DisjointSets{
	public:
		void addelements(int num);	
		int find(int elem);
		void setunion(int a,int b);
		void clear();
		
	private:
		std::vector<int> upTree;
		bool smaller(int a,int b);
};
#endif