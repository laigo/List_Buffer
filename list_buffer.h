#ifndef __LIST_BUFFER_H_
#define __LIST_BUFFER_H_

#include "stdint.h"
/**
 * @brief List buffer structure
 */
typedef struct {
	void *data;
	int count;
	int itemSz;
	uint32_t itemIndex;
} LISTBUFF_T;

int ListBuffer_Init(LISTBUFF_T *ListBuff, void *buffer, int itemSize, int count);
char* ListBuffer_FindStr(LISTBUFF_T *ListBuff, char *match);
int ListBuffer_AddRange(LISTBUFF_T *ListBuff, const void *data,int num);

void ListBuffer_Clr(LISTBUFF_T *ListBuff);

char* ListBuffer_FindMsg(LISTBUFF_T *ListBuff, int *pIndex);
char* ListBuffer_MatchPrefix(LISTBUFF_T *ListBuff, char *pPrefix, int *pIndex);

int  ListBuffer_RemoveRange(LISTBUFF_T *ListBuff, int index, int count);

#endif