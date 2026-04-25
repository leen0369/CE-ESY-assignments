#include <stdio.h>
#include <string.h>

#define SIZE 10  // حجم المخزن (يمكن تغييره لاختبار overflow)

// تعريف بنية المخزن الدائري
// يعتمد على مصفوفة ثابتة الحجم + مؤشرين
// head: يشير إلى موقع القراءة
// tail: يشير إلى موقع الكتابة
// count: عدد العناصر الحالية داخل المخزن
// يتم استخدام modulo لتحقيق خاصية الدوران (wrap-around)
typedef struct {
    char buffer[SIZE];
    int head;
    int tail;
    int count;
} CircularBuffer;

// تهيئة المخزن: تصفير المؤشرات وعدد العناصر
void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// التحقق إذا كان المخزن ممتلئ
// يصبح ممتلئ عندما يصل عدد العناصر إلى الحجم الأقصى
int isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
}

// التحقق إذا كان المخزن فارغ
// يكون فارغ عندما لا يحتوي على أي عناصر
int isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

// دالة الكتابة (إدخال عنصر)
// تضيف عنصر عند موقع tail ثم تحرك المؤشر للأمام
// في حال الامتلاء يتم منع الإدخال لتجنب overflow
void write(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("⚠️ Buffer Overflow\n");
        return;
    }

    cb->buffer[cb->tail] = data;

    // تحريك المؤشر مع الحفاظ على الطبيعة الدائرية
    cb->tail = (cb->tail + 1) % SIZE;

    cb->count++;
}

// دالة القراءة (إزالة عنصر)
// تقرأ من موقع head ثم تحرك المؤشر
// في حال الفراغ يتم تنبيه المستخدم (underflow)
char read(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("⚠️ Buffer Underflow\n");
        return '\0';
    }

    char data = cb->buffer[cb->head];

    // تحريك المؤشر مع wrap-around
    cb->head = (cb->head + 1) % SIZE;

    cb->count--;

    return data;
}

int main() {
    CircularBuffer cb;
    init(&cb);

    char name[100];

    // قراءة الاسم من المستخدم باستخدام الإدخال القياسي
    printf("Enter your name: ");
    scanf("%s", name);

    // إضافة النص المطلوب إلى الاسم
    strcat(name, "CE-ESY");

    printf("\nWriting to circular buffer...\n");

    // إدخال كل حرف من النص إلى المخزن
    for (int i = 0; i < strlen(name); i++) {
        write(&cb, name[i]);
    }

    printf("\nReading from circular buffer:\n");

    // قراءة البيانات من المخزن حتى يصبح فارغ
    while (!isEmpty(&cb)) {
        char c = read(&cb);
        printf("%c", c);
    }

    // التأكد من أن المخزن أصبح فارغ
    if (isEmpty(&cb)) {
        printf("\n\nBuffer is now empty ✅\n");
    }

    return 0;
}