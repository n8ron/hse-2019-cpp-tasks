#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "str.h"
#include "test_str.h"

void test_my_strcpy() {
    char temp[200] = "";
    assert(strcmp(my_strcpy(temp, "abd213"), "abd213") == 0);
    assert(strcmp(my_strcpy(temp, ""), "") == 0);
       
}

void test_my_strcat() {
    char temp[200] = "abcd";
    assert(strcmp(my_strcat(temp, "efgh"), "abcdefgh") == 0);
    assert(strcmp(my_strcat(temp, ""), "abcdefgh") == 0);
}

void test_my_strcmp() {
	assert(my_strcmp("abcd", "abcd") == 0);
	assert(my_strcmp("abcd", "abce") < 0);
	assert(my_strcmp("123", "12") > 0);
	assert(my_strcmp("123", "") > 0);
}

void test_my_strlen() {
	assert(my_strlen("123") == 3);
	assert(my_strlen("adsdd") == 5);
	assert(my_strlen("") == 0);	
}
