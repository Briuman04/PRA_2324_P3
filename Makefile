bin/testTableEntry: testTableEntry.cpp TableEntry.h
		mkdir -p bin
		g++ -o bin/testTableEntry testTableEntry.cpp
clean:
		rm -rf *.o *.gch bin

bin/testHashTable: testHashTable.cpp HashTable.h TableEntry.h
		mkdir -p bin
		g++ -o bin/testHashTable testHashTable.cpp

bin/testBSTree: testBSTree.cpp BSTree.h TableEntry.h
		mkdir -p bin
		g++ -o bin/testBSTree testBSTree.cpp

bin/testBSTreeDict: testBSTreeDict.cpp BSTreeDict.h TableEntry.h
		mkdir -p bin
		g++ -o bin/testBSTreeDict testBSTreeDict.cpp