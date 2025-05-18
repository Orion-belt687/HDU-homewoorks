#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <math.h> 
//ð��ok����ѡ��ok���򵥲���ok������ok���鲢����ok����������ok��Ͱ����ok?����������ok
//���ﶼ�Ǵ�С�����ŵģ�����������������������
//�����������ok��������ok����ʱ����
void bubble(int A[],int len){//ð������
    int i,j;
    for(i=0;i<len;i++){
        for(j=0;j<len-i-1;j++){
            if(A[j]>A[j+1]){
                int temp=A[j];
                A[j]=A[j+1];
                A[j+1]=temp;
            }
        }
    }

}
void simple(int A[],int len){//������
    for(int i=0;i<len;i++){
        int mininow=i;
        for(int j=i+1;j<len;j++){
            if(A[j]<A[mininow]){
                mininow=j;
            }
        }
        if(mininow!=i){
            int temp=A[i];
            A[i]=A[mininow];
            A[mininow]=temp;
        }
    }
}
void insert(int A[],int len){//����
    for(int i=1;i<len;i++){
        int temp=A[i];
        int j=i-1;
        while(j>=0&&A[j]>temp){
            A[j+1]=A[j];
            j--;
        }
        A[j+1]=temp;
    }
}
void quick(int A[],int low,int high){//��������
    if(low<high){
        int i=low,j=high;
        int key=A[low];
        while(i<j){
            while(i<j&&A[j]>=key) j--;
            if(i<j) A[i++]=A[j];
            while(i<j&&A[i]<=key) i++;
            if(i<j) A[j--]=A[i];
        }
        A[i]=key;
        quick(A,low,i-1);
        quick(A,i+1,high);
    }
}
void merge(int A[],int low,int high){//�鲢
    int mid=(low+high)/2;
     if (low < high) {
        merge(A, low, mid);
        merge(A, mid + 1, high);
        int* temp = (int*)malloc((high - low + 1) * sizeof(int));
        int i = low, j = mid + 1, k = 0;
        while (i <= mid && j <= high) {
            if (A[i] <= A[j]) temp[k++] = A[i++];
            else temp[k++] = A[j++];
        }
        while (i <= mid) temp[k++] = A[i++];
        while (j <= high) temp[k++] = A[j++];
        for (int t = 0; t < k; t++) {
            A[low + t] = temp[t];
        }
        free(temp);
    }
}
void count(int A[],int len){//��������
    // 1. �ҵ����ֵ
    int max = A[0];
    for (int i = 1; i < len; i++) {
        if (A[i] > max) max = A[i];
    }
    // 2. �����������
    int* temp = (int*)calloc(max + 1, sizeof(int));
    // 3. ����
    for (int i = 0; i < len; i++) {
        temp[A[i]]++;
    }
    // 4. ��д
    int pos = 0;
    for (int i = 0; i <= max; i++) {
        while (temp[i] > 0) {
            A[pos++] = i;
            temp[i]--;
        }
    }
    free(temp);
}
void bucket(int A[],int len){//Ͱ����Ͱ�Ĵ�СΪ1
    int max = A[0];
    for (int i = 1; i < len; i++) {
        if (A[i] > max) max = A[i];
    }
    int* temp = (int*)calloc(max + 1, sizeof(int));
    for (int i = 0; i < len; i++) {
        temp[A[i]]++;
    }
    int pos = 0;
    for (int i = 0; i <= max; i++) {
        while (temp[i] > 0) {
            A[pos++] = i;
            temp[i]--;
        }
    }
    free(temp);
}
void radix(int A[],int len){//��������
    int max = A[0];
    for (int i = 1; i < len; i++) {
        if (A[i] > max) max = A[i];
    }
    // �����������λ��
    int exp = 1;
    int* output = (int*)malloc(len * sizeof(int));
    while (max / exp > 0) {
        int bucket[10] = {0};
        // ͳ��ÿ��Ͱ�е�Ԫ�ظ���
        for (int i = 0; i < len; i++) {
            bucket[(A[i] / exp) % 10]++;
        }
        // ����ǰ׺�ͣ�ȷ��ÿ��Ԫ����output�е�λ��
        for (int i = 1; i < 10; i++) {
            bucket[i] += bucket[i - 1];
        }
        // �Ӻ���ǰ��������֤�ȶ���
        for (int i = len - 1; i >= 0; i--) {
            int idx = (A[i] / exp) % 10;
            output[--bucket[idx]] = A[i];
        }
        // ������ԭ����
        for (int i = 0; i < len; i++) {
            A[i] = output[i];
        }
        exp *= 10;
    }
    free(output);
}
int check(int A[],int len){//��������Ƿ���ȷ
    for(int i=0;i<len-1;i++){
        if(A[i]>A[i+1]){
            printf("error!\n");
            return 1;
        }
    }
    //printf("ok\n");
    return 0;
}
void createrandom(int A[],int len){//��ȫ�������
    for(int i=0;i<len;i++){
        A[i]=rand()%len;
    }
}
void createswap(int A[],int len){//�������黻λ��
    for(int i=0;i<len;i++){//�ȳ���������
        A[i]=i;
    }
    int swap=len/5;
    for(int i=0;i<swap;i++){//�������֮��������λ��
        int first=rand()%len;
        int second=rand()%len;
        int t=0;
        t=A[first];
        A[first]=A[second];
        A[second]=t;
    }
}
void Try(int A[],int len){
    int* B = (int*)malloc(len * sizeof(int));
    clock_t start, end;

    // ð������
    memcpy(B, A, len * sizeof(int));
    start = clock();
    bubble(B, len);
    end = clock();
    printf("bubble: %ld ms in Windows/ns in LUNIX\n", end - start);
    check(B, len);

    // ��ѡ������
    memcpy(B, A, len * sizeof(int));
    start = clock();
    simple(B, len);
    end = clock();
    printf("simple: %ld ms in Windows/ns in LUNIX\n", end - start);
    check(B, len);

    // ��������
    memcpy(B, A, len * sizeof(int));
    start = clock();
    insert(B, len);
    end = clock();
    printf("insert: %ld ms in Windows/ns in LUNIX\n", end - start);
    check(B, len);

    // ��������
    memcpy(B, A, len * sizeof(int));
    start = clock();
    quick(B, 0, len - 1);
    end = clock();
    printf("quick: %ld ms in Windows/ns in LUNIX\n", end - start);
    check(B, len);

    // �鲢����
    memcpy(B, A, len * sizeof(int));
    start = clock();
    merge(B, 0, len - 1);
    end = clock();
    printf("merge: %ld ms in Windows/ns in LUNIX\n", end - start);
    check(B, len);

    // ��������
    memcpy(B, A, len * sizeof(int));
    start = clock();
    count(B, len);
    end = clock();
    printf("count: %ld ms in Windows/ns in LUNIX\n", end - start);
    check(B, len);

    // Ͱ����
    memcpy(B, A, len * sizeof(int));
    start = clock();
    bucket(B, len);
    end = clock();
    printf("bucket: %ld ms in Windows/ns in LUNIX\n", end - start);
    check(B, len);

    // ��������
    memcpy(B, A, len * sizeof(int));
    start = clock();
    radix(B, len);
    end = clock();
    printf("radix: %ld ms in Windows/ns in LUNIX\n", end - start);
    check(B, len);

    printf("\n");
    free(B);
}
int main(){
    int A[100];
    printf("100��������:\n");
    createswap(A,100);
    Try(A,100);
    printf("100�������:\n");
    createrandom(A,100);
    Try(A,100);

    int B[1000];
    printf("1000��������:\n");
    createswap(B,1000);
    Try(B,1000);
    printf("1000�������:\n");
    createrandom(B,1000);
    Try(B,1000);

    int C[10000];
    printf("10000��������:\n");
    createswap(C,10000);
    Try(C,10000);
    printf("10000�������:\n");
    createrandom(C,10000);
    Try(C,10000);

    int D[100000];
    printf("100000��������:\n");
    createswap(D,100000);
    Try(D,100000);
    printf("100000�������:\n");
    createrandom(D,100000);
    Try(D,100000);

    int E[1000000];
    printf("1000000��������:\n");
    createswap(E,1000000);
    Try(E,1000000);
    printf("1000000�������:\n");
    createrandom(E,1000000);
    Try(E,1000000);
    return 0;
}