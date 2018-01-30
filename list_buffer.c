#include "list_buffer.h"
#include "stdint.h"
#include "string.h"

#if !defined(MAX)
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif
#if !defined(MIN)
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

/* Initialize list buffer */
int ListBuffer_Init(LISTBUFF_T *ListBuff, void *buffer, int itemSize, int count)
{
	//参数检测
        
  
  
        ListBuff->data = buffer;
	ListBuff->count = count - 1; 
	ListBuff->itemSz = itemSize;
	ListBuff->itemIndex = 0;
	
	memset(buffer, '\0' , count * itemSize);		
	return 1;
}


/**
 * @brief	Return number of free items in the list buffer
 * @param	RingBuff	: Pointer to list buffer
 * @return	Number of free items in the list buffer
 */
static  int ListBuffer_GetFree(LISTBUFF_T *ListBuff)
{
	return (ListBuff->count  - ListBuff->itemIndex);	
}


int ListBuffer_AddRange(LISTBUFF_T *ListBuff, const void *data,int num)
{
	uint8_t *ptr = ListBuff->data;
	
	int cnt = ListBuffer_GetFree(ListBuff);
	//
	cnt = MIN(cnt,num);
			
	ptr += ListBuff->itemIndex * ListBuff->itemSz;	
	memcpy(ptr, data, cnt * ListBuff->itemSz);
	ListBuff->itemIndex += cnt;	
	
	return cnt;
}


char* ListBuffer_FindStr(LISTBUFF_T *ListBuff, char *match)
{
	char *ptr = ListBuff->data;
	
	if(match==NULL)
	{
		return NULL;
	}
	
	//返回值：若match是ptr的子串，则返回match在ptr的首次出现的地址；如果match不是ptr的子串，则返回NULL。
	return strstr(ptr, match);			
}




char* ListBuffer_FindMsg(LISTBUFF_T *ListBuff, int *pIndex)
{
        
	char *ptr = ListBuff->data;
	char *pEnd = strstr(ptr, "\r\n"); //结束码 \r\n
	if(pEnd!=NULL)
	{//找到结束码
	
		(*pIndex)  = (pEnd - ptr);
	}
	return pEnd;
}

char* ListBuffer_MatchPrefix(LISTBUFF_T *ListBuff, char *pPrefix, int *pIndex)
{
	char *ptr = ListBuff->data;
		   
	char *pStart = strstr(ptr, pPrefix); 
	if(pStart!=NULL)
	{
		  *pIndex  = (pStart - ptr);
	}    
	return pStart;
}
	

int ListBuffer_FindIndex(LISTBUFF_T *ListBuff, int startIndex,  int count, char *match)
{
	
	return -1;
}

int  ListBuffer_RemoveRange(LISTBUFF_T *ListBuff, int index, int count)
{
	char *ptr = ListBuff->data;
	char *pHead = ptr, *pTail = ptr;


	if(ListBuff->itemIndex > (index+ count))
	{
		//
		ListBuff->itemIndex -= count;
	}
	else if(ListBuff->itemIndex < index)  
	{
		//
		//todo? donothing
		return -1;
	}
	else
	{
		//
		count =  ListBuff->itemIndex - index;
		ListBuff->itemIndex -= count;     
	}

	pHead = ptr+ index;
	pTail = pHead + count;     


	int moveCnt =  ListBuff->count * ListBuff->itemSz - (pTail - ptr);
	 
	memcpy(pHead ,pTail ,moveCnt);
	memset(pHead+ moveCnt,'\0', count);

	return 1;      	
}



void ListBuffer_Clr(LISTBUFF_T *ListBuff)
{	
	ListBuff->itemIndex = 0;     
	memset(ListBuff->data ,'\0' , ListBuff->count * ListBuff->itemSz);            
}

