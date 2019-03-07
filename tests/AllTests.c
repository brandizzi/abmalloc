#include <stdio.h>

#include "CuTest.h"

#include "linked_list_test.h"
#include "abmalloc_test.h"

CuSuite* CuGetSuite();
CuSuite* CuStringGetSuite();

void RunAllTests(void)
{
	CuSuite suite;
	CuSuiteInit(&suite);
	CuString output;
	CuStringInit(&output);

	CuSuiteAddSuite(&suite, LinkedListGetSuite());
	CuSuiteAddSuite(&suite, ABMallocGetSuite());

	CuSuiteRun(&suite);
	CuSuiteSummary(&suite, &output);
	CuSuiteDetails(&suite, &output);
	printf("%s\n", output.buffer);
}

int main(void)
{
	RunAllTests();
}
