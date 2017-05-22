/*
  Copyright (c) 2009-2017 Dave Gamble and cJSON contributors

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "unity/examples/unity_config.h"
//#include "unity.h"
//#include "common.h"
#include "cjson/cJSON.h"
//#include "sensor-meta.h"

//TypeSensor sensors[20];
int activeSensorNumber=0;

static cJSON item[1];

//CJSON_PUBLIC(char*) read_file(const char *filename)
char* read_file(const char *filename)
{
    FILE *file = NULL;
    long length = 0;
    char *content = NULL;
    size_t read_chars = 0;

    /* open in read binary mode */
    file = fopen(filename, "rb");
    if (file == NULL)
    {
        goto cleanup;
    }

    /* get the length */
    if (fseek(file, 0, SEEK_END) != 0)
    {
        goto cleanup;
    }
    length = ftell(file);
    if (length < 0)
    {
        goto cleanup;
    }
    if (fseek(file, 0, SEEK_SET) != 0)
    {
        goto cleanup;
    }

    /* allocate content buffer */
    content = (char*)malloc((size_t)length + sizeof(""));
    if (content == NULL)
    {
        goto cleanup;
    }

    /* read the file into memory */
    read_chars = fread(content, sizeof(char), (size_t)length, file);
    if ((long)read_chars != length)
    {
        free(content);
        content = NULL;
        goto cleanup;
    }
    content[read_chars] = '\0';


cleanup:
    if (file != NULL)
    {
        fclose(file);
    }

    return content;
}



static cJSON *parse_file(const char *filename)
{
    cJSON *parsed = NULL;
    char *content = read_file(filename);

    parsed = cJSON_Parse(content);

    if (content != NULL)
    {
        free(content);
    }

    return parsed;
}

char* getConnParameters(){
    char *expected = NULL;
    char *expected_path = "config/conn-param.cfg";
	cJSON* tree = NULL;
	char result[20];

   /* initialize cJSON item */
    memset(item, 0, sizeof(cJSON));
 	expected = read_file(expected_path);
	//printf("%s", expected);
	tree =cJSON_Parse(expected);
	//actual = cJSON_Print(tree);
	//printf("===\n%s", actual);


	cJSON *destination = cJSON_GetObjectItemCaseSensitive(tree, "destination");
	cJSON *weight_item = cJSON_GetObjectItemCaseSensitive(tree, "weight");
	if (!cJSON_IsNull(destination)){
		return destination->valuestring;
	}else{
		return NULL;
	}
}


#define funcmain 0
#if funcmain
int main(void)
{
    char *expected = NULL;
//    char *expected_path = "json-data.txt";
    char *expected_path = "../config/conn-param.cfg";
	cJSON* tree = NULL;
	char * actual = NULL;

   /* initialize cJSON item */
    memset(item, 0, sizeof(cJSON));
 	expected = read_file(expected_path);
	printf("%s", expected);
	tree =cJSON_Parse(expected);
	actual = cJSON_Print(tree);
	printf("===\n%s", actual);
/*
    if (tree != NULL)
    {
        cJSON_Delete(tree);
    }
*/
	cJSON *selfip = cJSON_GetObjectItemCaseSensitive(tree, "selfip");
if (cJSON_IsNull(selfip)){
	printf("Null\n");
}else{
	printf("not Null\n");
	printf("selfip=%s\n", selfip->valuestring);
}
	cJSON *weight_item = cJSON_GetObjectItemCaseSensitive(tree, "weight");
	double framerate = 0;
	if (cJSON_IsNumber(weight_item))
	{
	  framerate = weight_item->valuedouble;
	}
	printf("dest=%s\n", getConnParameters());
}

#endif
