/*
Main implementation of Shared Library Test board
*/

#include <sharetest/sharetest.h>

#include <shared/io_sd.h>

int main()
{

	/*
	* SD File Logging Tests
	*/
	tsprintf("Start SD logging tests...");
	sdWriteString("foo bar par");
	double output[] = {0, 2, 5.04, 7.66};
	sdWriteDouble(output, 4);
	tsprintf("Finished SD logging tests.");
	return 0;
}
