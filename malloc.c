// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>


void *malloc(size_t size) {
	if (size == 0)
		return NULL;
	void *p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (p == MAP_FAILED)
		return NULL;
	if (mem_list_add(p, size) < 0) {
		munmap(p, size);
		return NULL;
	}
	return p;
}

void *calloc(size_t nmemb, size_t size)
{
	size_t max = nmemb * size;
	void *p = malloc(max);
	if (p == NULL)
		return NULL;
	memset(p, 0, max);
	return p;
}

void free(void *ptr)
{
	if (ptr == NULL) return;
	struct mem_list *a = mem_list_find(ptr);
	if (a == NULL) return;
	munmap(ptr, a->len);
	mem_list_del(ptr);
}

void *realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return malloc(size);
	if (size == 0) {
		free(ptr);
		return NULL;
	}
	struct mem_list *a = mem_list_find(ptr);
	if (a == NULL) return NULL;
	void *n = malloc(size);
	if (n == NULL) return NULL;
	size_t l;
	if(a->len < size)
		l = a->len;
	else l = size;
	memcpy(n, ptr, l);
	free(ptr);
	return n;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	size_t a = nmemb * size;
	if (nmemb != 0 && a / nmemb != size)
		return NULL;
	return realloc(ptr, a);
}