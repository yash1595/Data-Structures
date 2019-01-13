/*
 * Principles of Embedded Software : Project-2
 * Team Members: 1. Lekshmi Prathap 2.Yash Gupte
 *
 *
*/

/*CUnit library headers */
#include <CUnit/Automated.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include "../inc/Allocate_2.h"

/* Own headers */
       

int init_test (void)
{
	return 0;
}


int deinit_test (void)
{
	return 0;
}


/*-----------------------------------Allocate Function Test---------------------------------*/

/*void test_allocate_function(void)
{
	CU_ASSERT_PTR_NOT_EQUAL(NULL, g_blockptr);
	CU_ASSERT_EQUAL(10, g_nblock);
}*/

/*-------------------------------------Write Function Test---------------------------------*/

void test_alloc_function(void)
{
	CU_ASSERT_EQUAL(Allocate(0,0,10),1);			//Valid index.
	CU_ASSERT_EQUAL(Allocate(0,-1,5),0);			//Invalid index.
	CU_ASSERT_EQUAL(Allocate(0,0,257),0);			//Length>255.
	FreeMem(0,0,0);
}
void test_write_function(void)
{
	Allocate(0,0,8);
	CU_ASSERT_EQUAL(AddDataCycBuff("134\n",0,0), 1);	//Valid output.
	CU_ASSERT_EQUAL(AddDataCycBuff("abc\n",0,0),1);		//Valid output.
	CU_ASSERT_EQUAL(AddDataCycBuff("abceert\n",0,0),0);	//String longer than buffer size.
	CU_ASSERT_EQUAL(AddDataCycBuff("13\n",0,0), 1);		//Valid output.
	CU_ASSERT_EQUAL(AddDataCycBuff("abcd\n",0,0),1);	//Valid output.
	CU_ASSERT_EQUAL(AddDataCycBuff("abceecet\n",0,0),0);	//String longer than buffer size.
	CU_ASSERT_EQUAL(AddDataCycBuff("\n",0,0), 1);		//Valid input.
	
}
void test_del_function(void)
{
	CU_ASSERT_EQUAL(DelDataCycBuff(0,0,5),1);		//Valid
	CU_ASSERT_EQUAL(DelDataCycBuff(0,0,2),1);		//Valid
	CU_ASSERT_EQUAL(DelDataCycBuff(0,0,8),0);		//Length>buffer size.
	
}
void test_disp_function(void)
{
	CU_ASSERT_EQUAL(DisplayCycBuff(0,1,0),0);		//Display buffer not allocated but within BUFFSIZE.
	CU_ASSERT_EQUAL(DisplayCycBuff(0,5,0),0);		//Display buffer not allocated outside BUFFSIZE.
	CU_ASSERT_EQUAL(DisplayCycBuff(0,0,0),1);		//Valid buffer.
	
	
}
void test_free_function(void)
{
	CU_ASSERT_EQUAL(FreeMem(0,4,0), 0);			//Tries to free index not allocated.
	CU_ASSERT_EQUAL(FreeMem(0,0,0), 1);			//Valid.
	CU_ASSERT_EQUAL(FreeMem(0,1,0), 0);			//Tries to free index not allocated.
	
	
}
void test_realloc_function(void)
{
	CU_ASSERT_EQUAL(ReallocBuff(0,0,10),1);			//Valid.
	CU_ASSERT_EQUAL(ReallocBuff(0,0,12),1);			//Valid.
	CU_ASSERT_EQUAL(ReallocBuff(0,4,0),0);			//Realloc out of bound index.
	CU_ASSERT_EQUAL(ReallocBuff(0,0,4),0);			//Realloc out of bound length.
}
int register_test_suite(void) {

    CU_pSuite pSuite = NULL;

    pSuite = CU_add_suite("Functionality Test", init_test,deinit_test);
    if (NULL == pSuite) {
        return -1;
    }
    /*Adding tests to the suite */
    if ((NULL == CU_add_test(pSuite, "Alloc functionality test", test_alloc_function))||
	(NULL == CU_add_test(pSuite, "Write functionality test", test_write_function))||
	(NULL == CU_add_test(pSuite, "Disp functionality test", test_disp_function))||
	(NULL == CU_add_test(pSuite, "Del functionality test", test_del_function))||
	(NULL == CU_add_test(pSuite, "Realloc functionality test", test_realloc_function))||
	(NULL == CU_add_test(pSuite, "Free functionality test", test_free_function)))
    {    
	return -1;
    }
    return 0;
}
int main()
{
    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

 	//register_test_suite will add a test suite to the CUnit test registry
    if (register_test_suite() == -1) {
        CU_cleanup_registry();
        return CU_get_error();
    }

	/* Run all tests using CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();


    CU_cleanup_registry();
    return CU_get_error();
}

