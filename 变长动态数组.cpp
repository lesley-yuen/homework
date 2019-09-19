#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#define ERROR 0
//#define RIGHT 1
typedef int Elem;
typedef struct DynamicArray
{
    size_t capacity;   // 数组的容量，初始值和最小值均为16u
    size_t size;       // 数组中元素的个数
    Elem* data;     // 用于保存数组中元素的内存空间
} DynamicArray;
// 创建数组，初始容量为16。
DynamicArray* DynamicArray_new();

// 本题中，在位置pos前插入元素*v，也就是*v插入后，它是数组中的第pos个元素，下标从0开始。
// 注意，插入后的数组可能发生容量的倍增，假设内存分配总是合法的，不需要针对内存不足抛出异常。
// 例如：
//      1. pos = 10  ，表示在第10个元素前插入元素*v，插入后它前面有10个元素，原来的第10个元素在它后面
//      2. pos = 0   ，表示在数组的起始位置插入元素*v
//      3. pos = size，表示在数组的末尾插入元素*v
void DynamicArray_insert(DynamicArray* thi, size_t pos, const Elem* v);

// 删除位置pos的元素，可以假定pos总是合法的，即pos=0,1,...,size - 1，删除后的数组不应该有空档。
// 注意，删除数组元素可能会导致容量变更。
// 例如：
//     size = 6, 数组中的元素为0,1,2,3,4,5。删除了pos=3的元素3之后，数组的元素变为0,1,2,4,5，size=5，数组第3个元素为4
Elem DynamicArray_erase(DynamicArray* thi, size_t pos);

// 获取位置为pos的元素，假设pos总是合法的。
Elem DynamicArray_get(const DynamicArray* thi, size_t pos);

// 将位置为pos的元素设置为*v，假设pos总是合法的。
void DynamicArray_set(DynamicArray* thi, size_t pos, const Elem* v);

// 返回数组的容量。
size_t DynamicArray_capacity(const DynamicArray* thi);

// 返回数组的元素个数。
size_t DynamicArray_size(const DynamicArray* thi);

// 返回数组元素是否为空，为空则返回true，否则返回false。
bool DynamicArray_empty(const DynamicArray* thi);

// 重设数组元素个数为new_size，注意，容量可能因此发生变更。
// 新的数组元素个数如果比原来的数组更多，将原有数组的元素复制到新数组对应位置即可。
// 新的数组元素个数如果比原来的数组更少，超出的部分截断即可。
// 例如：
//    1. 原数组为0,1,2,3,4,5，新数组大小为4，那么新数组变为0,1,2,3，size=4
//    2. 原数组为0,1,2,3，新数组大小为6，那么数组变为0,1,2,3,?,?，size=6，其中?表示任意值，即这些多出的元素
//       不需要初始化
void DynamicArray_resize(DynamicArray* thi, size_t new_size);

// 删除数组。不要忘记释放原有数组的空间，否则会造成内存泄漏。
void DynamicArray_delete(DynamicArray* thi);
int main()
{
    char line[100];
    DynamicArray* arr = NULL;
    size_t size;
    size_t pos;
    Elem v;

    while (gets(line))
    {
        switch (line[0])
        {
        case 'C': // 创建数组
            arr = DynamicArray_new();
            break;
        case 'D': // 删除数组
            DynamicArray_delete(arr);
            arr = NULL;
            break;
        case 'R': // resize
            sscanf(line + 2, "%lu", &size);
            DynamicArray_resize(arr, size);
            break;
        case 'c': // 输出capacity
            printf("%lu\n", DynamicArray_capacity(arr));
            break;
        case 's': // 输出size
            printf("%lu\n", DynamicArray_size(arr));
            break;
        case 'i': // 插入元素
            sscanf(line + 2, "%lu %d", &pos, &v);
            DynamicArray_insert(arr, pos, &v);
            break;
        case 'd': // 删除元素并输出
            sscanf(line + 2, "%lu", &pos);
            printf("%d\n", DynamicArray_erase(arr, pos));
            break;
        case 'G': // get元素并输出
            sscanf(line + 2, "%lu", &pos);
            printf("%d\n", DynamicArray_get(arr, pos));
            break;
        case 'S': // set元素
            sscanf(line + 2, "%lu %d", &pos, &v);
            DynamicArray_set(arr, pos, &v);
            break;
        case 'e': // 输出数组是否为empty
            printf("%s\n", DynamicArray_empty(arr) == true ? "true" : "false");
            break;
        default:
            break;
        }
    }

    return 0;
}
// 创建数组，初始容量为16。
DynamicArray* DynamicArray_new()
{
	DynamicArray *arr = (DynamicArray*)malloc(sizeof(DynamicArray));
	arr->capacity = 16;
	arr->size = 0;
	arr->data = (int*)malloc(sizeof(int)*16);
	return arr;
}

void DynamicArray_insert(DynamicArray *arr, size_t pos, const Elem *v)
{
	if (!arr){
		printf("创建数组失败");
		exit(1);
	}
	if((arr->size)==(arr->capacity))
	{
		int b;
		b=2*arr->capacity;
		int *a=arr->data;
		int *p=(int*)malloc(b*sizeof(int));
		for(int i=0;i<pos;i++)
		{
			*(p+i)=*(a+i);
		}
		*(p+pos)=*v;
		for(int i=pos+1;i<arr->size+1;i++)
		{
			*(p+i)=*(a+i-1);
		}
		free(arr->data);
		arr->data=p;
		arr->capacity=b;
		arr->size=arr->size+1;
	}
	else
	{
		int*a=arr->data;
		for(int i=arr->size;i>pos;i--)
		{
			*(a+i)=*(a+i-1);
		}
		*(a+pos)=*v;
		arr->size=arr->size+1;
	}
}
Elem DynamicArray_erase(DynamicArray* arr, size_t pos)
{

 if(arr->size-1<arr->capacity/4&&arr->capacity>16)
	{
		int n=arr->capacity/2;
		int *a=arr->data;
		int *p=(int*)malloc(n*sizeof(int));
		int flag=*(a+pos);
		for(int i=0;i<pos;i++)
		{
			*(p+i)=*(a+i);
		}
		for(int i=pos;i<(arr->size)-1;i++)
		{
			*(p+i)=*(a+i+1);
		}
		free(arr->data);
		arr->capacity=n;
		arr->size=arr->size-1;
		arr->data=p;
		return(flag);
	}
	else
	{
		int*a=arr->data;
		int q=*(a+pos);
		for(int i=pos;i<arr->size-1;i++)
		{
			*(a+i)=*(a+i+1);
		}
		arr->data=a;
		if(arr->size==1)
		*a=*(a+1);
		arr->size=arr->size-1;
		return q;
	}
}

Elem DynamicArray_get(const DynamicArray* arr, size_t pos)
{

	int*a=arr->data;
	return(*(a+pos));
}

void DynamicArray_set(DynamicArray* arr, size_t pos, const Elem* v)
{
	if (!arr){
		printf("创建数组失败");
		exit(1);
	}
	int*a=arr->data;
	*(a+pos)=*v;
}

size_t DynamicArray_capacity(const DynamicArray* arr)
{

	return(arr->capacity);
}

size_t DynamicArray_size(const DynamicArray* arr)
{

	return(arr->size);
 }

bool DynamicArray_empty(const DynamicArray* arr)
{
	if(arr->size==0)
	return(true);
	else
	return(false);
}

void DynamicArray_resize(DynamicArray* arr, size_t new_size)
{
	if(new_size>arr->capacity)
	{
		while(new_size>arr->capacity)
		arr->capacity*=2;
		int *p=(int*)malloc(arr->capacity*sizeof(int));
		for(int i=0;i<arr->size;i++)
		{
			*(p+i)=arr->data[i];
		}
		free(arr->data);
		arr->data=p;
		arr->size=new_size;
	}
	else if(new_size==arr->size)
	;
	else if(new_size<arr->size)
	{
		while(new_size<arr->capacity/4&&arr->capacity>16)
		{
			arr->capacity/=2;
		}
		int*p=(int*)malloc(arr->capacity*sizeof(int));
		for(int i=0;i<new_size;i++)
		{
			*(p+i)=arr->data[i];
		}
		free(arr->data);
		arr->data=p;
		arr->size=new_size;

	}
	else if(new_size>arr->size)
	{
		int *p=(int*)malloc(arr->capacity*sizeof(int));
		for (int i=0;i<arr->size;i++)
		{
			*(p+i)=arr->data[i];
		}
		free(arr->data);
		arr->data=p;
		arr->size=new_size;
	}
}

void DynamicArray_delete(DynamicArray* thi)
 {
	if (!thi){
		printf("删除数组失败");
		exit(1);
	}
	if (thi->data)
		free(thi->data);
	free(thi);
}

