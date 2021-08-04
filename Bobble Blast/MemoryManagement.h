#pragma once

static int tot = 0;
static bool loaded = false;
std::ofstream file;


inline void* operator new(size_t size, const char* filename, int line)
{
	if (!loaded)
	{
		file.open("Assets/MemoryLog.txt");
		loaded = true;
	}

	tot += size;
	void* ptr = new char[size];
	file << "size = " << size << " bytes " << "filename = " << filename << "line = " << line << std::endl;
	file << "total heap allocation = " << tot << " bytes " << std::endl;

	return ptr;
}

inline void* operator new[](size_t size, const char* filename, int line)
{
	if (!loaded)
	{
		UsefullFunctions::OpenFile(file, "Assets/MemoryLog.txt");
		loaded = true;
	}

	tot += size;
	void* ptr = new char[size];
	
	file << "size = " << size << " bytes " << "filename = " << filename << "line = " << line << std::endl;
	file << "total heap allocation = " << tot << " bytes " << std::endl;

	return ptr;
}

//Exception delete: parameters match the overloaded new and will be used
//if the object creation throws an exception
//inline void operator delete(void* ptr, const char* filename, int line)
//{
//	//if (!loaded)
//	//{
//	//	file.open("Assets/MemoryLog.txt");
//	//	loaded = true;
//	//}
//	//
//	//tot -= _msize(ptr);
//	//file << _msize(ptr) << " bytes released" << std::endl;
//	//file << "Total heap allocation = " << tot << " bytes " << std::endl;
//
//	free(ptr);
//}
//
////if successfull object creation, the following deletes will be used 
//inline void operator delete(void* ptr)
//{
//	//if (!loaded)
//	//{
//	//	file.open("Assets/MemoryLog.txt");
//	//	loaded = true;
//	//}
//	//
//	//tot -= _msize(ptr);
//	//file << _msize(ptr) << " bytes released" << std::endl;
//	//file << "Total heap allocation = " << tot << " bytes " << std::endl;
//
//	free(ptr);
//}
//
//inline void operator delete[](void* ptr)
//{
//	//if (!loaded)
//	//{
//	//	file.open("Assets/MemoryLog.txt");
//	//	loaded = true;
//	//}
//	//
//	//tot -= _msize(ptr);
//	//file << _msize(ptr) << " bytes released" << std::endl;
//	//file << "Total heap allocation = " << tot << " bytes " << std::endl;
//
//	free(ptr);
//}


//exploit the preprocessor
#define new new(__FILE__, __LINE__)