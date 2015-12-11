#ifndef __WB_PTHREAD_POOL_H_
#define __WB_PTHREAD_POOL_H_

#include <stdint.h>
#include <pthread.h>
#include "wb_gcc.h"

/*�����ʼ������ָ��*/
typedef int32_t(*mutex_constructor_t)(void* ob);
/*����������ָ��*/
typedef void(*mutex_destructor_t)(void* ob);
/*�Ϸ���У�麯��ָ��*/
typedef int32_t(*mutex_check_t)(void* ob);
/*����λ����ָ��*/
typedef void(*mutex_reset_t)(void* ob, int32_t flag);

typedef struct CACHE_ALIGN mutex_pool_s
{
	void**				ptr;		/*object array*/
	size_t				ob_size;	/*����ռ�õĿռ��ֽ���*/

	pthread_mutex_t		mutex;		/*latch*/
	int32_t				array_size;	/*ptr����ĳ���*/
	int32_t				curr;		/*��ǰ���е�ptrλ��*/

	mutex_constructor_t	constructor; /*�����ʼ������ָ��*/
	mutex_destructor_t	destructor;	/*���������պ���ָ��*/
	mutex_check_t		check;
	mutex_reset_t		reset;

	char*				name;		/*pool name*/
}mutex_pool_t;

mutex_pool_t*			mutex_pool_create(const char* name, size_t ob_size, size_t array_size, mutex_constructor_t constructor, mutex_destructor_t destructor,
	mutex_check_t check, mutex_reset_t reset);

void					mutex_pool_destroy(mutex_pool_t* pool);

void*					mutex_pool_alloc(mutex_pool_t* pool);

void					mutex_pool_free(mutex_pool_t* pool, void* ob);

void					mutex_pool_print(mutex_pool_t* pool);

int32_t					mutex_get_pool_info(mutex_pool_t* pool, char* buf);

#endif
