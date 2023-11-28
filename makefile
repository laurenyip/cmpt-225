all: td

td: hashFunctionTestDriver.o Profile.o EmptyDataCollectionException.o UnableToInsertException.o ElementAlreadyExistsException.o Dictionary.o
	g++ -Wall -o td hashFunctionTestDriver.o Profile.o EmptyDataCollectionException.o UnableToInsertException.o ElementAlreadyExistsException.o Dictionary.o
	
hashFunctionTestDriver.o: hashFunctionTestDriver.cpp
	g++ -Wall -c hashFunctionTestDriver.cpp 
			
Dictionary.o: Dictionary.h Dictionary.cpp
	g++ -Wall -c Dictionary.cpp

Profile.o: Profile.h Profile.cpp
	g++ -Wall -c Profile.cpp

ElementAlreadyExistsException.o: ElementAlreadyExistsException.h ElementAlreadyExistsException.cpp
	g++ -Wall -c ElementAlreadyExistsException.cpp
		
EmptyDataCollectionException.o: EmptyDataCollectionException.h EmptyDataCollectionException.cpp
	g++ -Wall -c EmptyDataCollectionException.cpp
	
UnableToInsertException.o: UnableToInsertException.h UnableToInsertException.cpp
	g++ -Wall -c UnableToInsertException.cpp

clean:
	rm -f td *.o
