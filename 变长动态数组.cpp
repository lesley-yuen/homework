#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#define ERROR 0
//#define RIGHT 1
typedef int Elem;
typedef struct DynamicArray
{
    size_t capacity;   // �������������ʼֵ����Сֵ��Ϊ16u
    size_t size;       // ������Ԫ�صĸ���
    Elem* data;     // ���ڱ���������Ԫ�ص��ڴ�ռ�
} DynamicArray;
// �������飬��ʼ����Ϊ16��
DynamicArray* DynamicArray_new();

// �����У���λ��posǰ����Ԫ��*v��Ҳ����*v��������������еĵ�pos��Ԫ�أ��±��0��ʼ��
// ע�⣬������������ܷ��������ı����������ڴ�������ǺϷ��ģ�����Ҫ����ڴ治���׳��쳣��
// ���磺
//      1. pos = 10  ����ʾ�ڵ�10��Ԫ��ǰ����Ԫ��*v���������ǰ����10��Ԫ�أ�ԭ���ĵ�10��Ԫ����������
//      2. pos = 0   ����ʾ���������ʼλ�ò���Ԫ��*v
//      3. pos = size����ʾ�������ĩβ����Ԫ��*v
void DynamicArray_insert(DynamicArray* thi, size_t pos, const Elem* v);

// ɾ��λ��pos��Ԫ�أ����Լٶ�pos���ǺϷ��ģ���pos=0,1,...,size - 1��ɾ��������鲻Ӧ���пյ���
// ע�⣬ɾ������Ԫ�ؿ��ܻᵼ�����������
// ���磺
//     size = 6, �����е�Ԫ��Ϊ0,1,2,3,4,5��ɾ����pos=3��Ԫ��3֮�������Ԫ�ر�Ϊ0,1,2,4,5��size=5�������3��Ԫ��Ϊ4
Elem DynamicArray_erase(DynamicArray* thi, size_t pos);

// ��ȡλ��Ϊpos��Ԫ�أ�����pos���ǺϷ��ġ�
Elem DynamicArray_get(const DynamicArray* thi, size_t pos);

// ��λ��Ϊpos��Ԫ������Ϊ*v������pos���ǺϷ��ġ�
void DynamicArray_set(DynamicArray* thi, size_t pos, const Elem* v);

// ���������������
size_t DynamicArray_capacity(const DynamicArray* thi);

// ���������Ԫ�ظ�����
size_t DynamicArray_size(const DynamicArray* thi);

// ��������Ԫ���Ƿ�Ϊ�գ�Ϊ���򷵻�true�����򷵻�false��
bool DynamicArray_empty(const DynamicArray* thi);

// ��������Ԫ�ظ���Ϊnew_size��ע�⣬����������˷��������
// �µ�����Ԫ�ظ��������ԭ����������࣬��ԭ�������Ԫ�ظ��Ƶ��������Ӧλ�ü��ɡ�
// �µ�����Ԫ�ظ��������ԭ����������٣������Ĳ��ֽضϼ��ɡ�
// ���磺
//    1. ԭ����Ϊ0,1,2,3,4,5���������СΪ4����ô�������Ϊ0,1,2,3��size=4
//    2. ԭ����Ϊ0,1,2,3���������СΪ6����ô�����Ϊ0,1,2,3,?,?��size=6������?��ʾ����ֵ������Щ�����Ԫ��
//       ����Ҫ��ʼ��
void DynamicArray_resize(DynamicArray* thi, size_t new_size);

// ɾ�����顣��Ҫ�����ͷ�ԭ������Ŀռ䣬���������ڴ�й©��
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
        case 'C': // ��������
            arr = DynamicArray_new();
            break;
        case 'D': // ɾ������
            DynamicArray_delete(arr);
            arr = NULL;
            break;
        case 'R': // resize
            sscanf(line + 2, "%lu", &size);
            DynamicArray_resize(arr, size);
            break;
        case 'c': // ���capacity
            printf("%lu\n", DynamicArray_capacity(arr));
            break;
        case 's': // ���size
            printf("%lu\n", DynamicArray_size(arr));
            break;
        case 'i': // ����Ԫ��
            sscanf(line + 2, "%lu %d", &pos, &v);
            DynamicArray_insert(arr, pos, &v);
            break;
        case 'd': // ɾ��Ԫ�ز����
            sscanf(line + 2, "%lu", &pos);
            printf("%d\n", DynamicArray_erase(arr, pos));
            break;
        case 'G': // getԪ�ز����
            sscanf(line + 2, "%lu", &pos);
            printf("%d\n", DynamicArray_get(arr, pos));
            break;
        case 'S': // setԪ��
            sscanf(line + 2, "%lu %d", &pos, &v);
            DynamicArray_set(arr, pos, &v);
            break;
        case 'e': // ��������Ƿ�Ϊempty
            printf("%s\n", DynamicArray_empty(arr) == true ? "true" : "false");
            break;
        default:
            break;
        }
    }

    return 0;
}
// �������飬��ʼ����Ϊ16��
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
		printf("��������ʧ��");
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
		printf("��������ʧ��");
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
		printf("ɾ������ʧ��");
		exit(1);
	}
	if (thi->data)
		free(thi->data);
	free(thi);
}

