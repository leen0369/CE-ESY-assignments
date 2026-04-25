#include <stdio.h>
#include <string.h>

#define SIZE 10  // حجم المخزن

typedef struct {
    char buffer[SIZE];
    int head;   // موقع القراءة
    int tail;   // موقع الكتابة
    int count;  // عدد العناصر
} CircularBuffer;

// تهيئة القيم
void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// التحقق من الامتلاء
int isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
}

// التحقق من الفراغ
int isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

// إضافة عنصر
void write(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("Buffer Overflow\n");
        return;
    }

    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE;  // رجوع للبداية إذا وصل للنهاية
    cb->count++;
}

// قراءة عنصر
char read(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("Buffer Underflow\n");
        return '\0';
    }

    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE;  // حركة دائرية
    cb->count--;

    return data;
}

int main() {
    CircularBuffer cb;
    init(&cb);

    char name[100];

    printf("Enter your name: ");
    scanf("%s", name);

    strcat(name, "CE-ESY");  // إضافة النص المطلوب

    // تخزين الأحرف
    for (int i = 0; i < strlen(name); i++) {
        write(&cb, name[i]);
    }

    // قراءة وطباعة
    while (!isEmpty(&cb)) {
        printf("%c", read(&cb));
    }

    printf("\n");

    return 0;
}
