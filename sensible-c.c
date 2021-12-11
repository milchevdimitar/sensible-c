#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define uchar unsigned char
#define bool int
#define true 1
#define false 0
typedef const uchar* string;

static string concatArr[5];

#define SWAP(type, a, b) do {\
    type tmp = a;\
    a = b;\
    b = temp;\
} while(false);
#define SORT(arr, func) (arr_sort((arr), sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]), (func)))

void swap(void* a, void* b, int size) {
    for (int i = 0; i < size; i++) {
        char temp = ((char*)a)[i];
        ((char*)a)[i] = ((char*)b)[i];
        ((char*)b)[i] = temp;
    }
}

string str_join(string joiner, string entries[], int n) {
    if (!n) return "";
    int length = str_length(joiner) * (n - 1);

    for (int i = 0; i < n; i++)
        length += str_length(entries[i]);

    uchar* res = (uchar*)malloc(length + 1);
    res[length] = 0;
    uchar* temp = res;

    for (int i = 0; i < n; i++) {
        if (i) for (int j = 0; joiner[j]; j++) *(temp++) = joiner[j];
        for (int j = 0; entries[i][j]; j++) *(temp++) = entries[i][j];
    }

    return res;
}

string str_intToString(int i) {
    int len = 0;
    for (int tempI = i; tempI > 0; len++, tempI /= 10);
    uchar* res = (uchar*)malloc(len + 1);
    res[len] = 0;
    uchar* temp = res + len;

    for (int tempI = i; tempI > 0; i++, tempI /= 10) {
        int digit = tempI % 10;
        *(--temp) = digit + '0';
    }

    return res;
}
string str_concat(string a, string b) {
    concatArr[0] = a;
    concatArr[1] = b;

    return str_join("", concatArr, 2);
}
string str_concat3(string a, string b, string c) {
    concatArr[0] = a;
    concatArr[1] = b;
    concatArr[2] = c;

    return str_join("", concatArr, 3);
}
string str_concat4(string a, string b, string c, string d) {
    concatArr[0] = a;
    concatArr[1] = b;
    concatArr[2] = c;
    concatArr[3] = d;

    return str_join("", concatArr, 4);
}
string str_concat5(string a, string b, string c, string d, string e) {
    concatArr[0] = a;
    concatArr[1] = b;
    concatArr[2] = c;
    concatArr[3] = d;
    concatArr[4] = e;

    return str_join("", concatArr, 5);
}


int str_length(string str) {
    int len = 0;
    while (1) {
        if (!str[len]) return len;
        len++;
    }
}
bool str_equals(string a, string b) {
    for (int i = 0; a[i] || b[i]; i++) {
        if (a[i] != b[i]) return false;
    }

    return true;
}
int str_compare(string a, string b) {
    for (int i = 0; a[i] || b[i]; i++) {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }

    return true;
}
bool str_beginsWith(string src, string str) {
    for (int i = 0; str[i]; i++) {
        if (src[i] != str[i]) return false;
    }
    return true;
}

string* str_split(string separator, string str, bool emptyEntries, int* splitsCount) {
    int len = str_length(str);
    int sepLen = str_length(separator);
    string* res = malloc(len + 1);
    uchar* splitted = malloc(len << 1);
    string curr = splitted;

    int partLength = 0;
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (str_beginsWith(str, separator)) {
            *(splitted++) = 0;
            if (emptyEntries || partLength) res[j++] = curr;
            curr = splitted;
            partLength = 0;
        }
        else {
            *(splitted++) = *str;
            partLength++;
        }
        str++;
    }
    *(splitted++) = 0;
    if (emptyEntries || partLength) res[j++] = curr;
    res[j] = 0;

    if (splitsCount) *splitsCount = j;

    return res;
}
string getstr(FILE* stream) {
    // Initial size is 32
    int size = 32;
    uchar* res = (uchar*)malloc(size);

    for (int c, i = 0; 1; i++) {
        c = getc(stream);
        // Doubles res if i has reached the end
        if (i == size) res = (uchar*)realloc(res, size <<= 1);
        // If inputted enter, we just terminate the string and return it
        if (c == '\n') {
            res[i] = 0;
            return res;
        }
        res[i] = c;
    }
}

int ei_inputIntBetween(string message, int min, int max) {
    int i = 0;
    do {
        printf("%s", message);
        scanf("%d", &i);
    } while (i < min || i > max);
    return i;
}
long ei_inputLongBetween(string message, long min, long max) {
    long i = 0;
    do {
        printf("%s", message);
        scanf("%ld", &i);
    } while (i < min || i > max);
    return i;
}
float ei_inputFloatBetween(string message, float min, float max) {
    float i = 0;
    do {
        printf("%s", message);
        scanf("%f", &i);
    } while (i < min || i > max);
    return i;
}
double ei_inputDoubleBetween(string message, double min, double max) {
    double i = 0;
    do {
        printf("%s", message);
        scanf("%lf", &i);
    } while (i < min || i > max);
    return i;
}

int ei_inputInt(string message) {
    int i = 0;
    printf("%s", message);
    scanf("%d", &message);
    return i;
}
long ei_inputLong(string message) {
    long i = 0;
    printf("%s", message);
    scanf("%ld", &message);
    return i;
}
float ei_inputFloat(string message) {
    float i = 0;
    printf("%s", message);
    scanf("%f", &message);
    return i;
}
double ei_inputDouble(string message) {
    double i = 0;
    printf("%s", message);
    scanf("%lf", &message);
    return i;
}
string ei_inputString(string message) {
    printf("%s", message);
    return getstr(stdin);
}

int ei_multipleChoice(string message, string choices[], int n) {
    return ei_inputIntBetween(str_concat4(
        message, "\n- ",
        str_join("\n- ", choices, n),
        str_concat3("\nAny between 1 - ", str_intToString(n), ": ")
    ), 1, n) - 1;
}

int sort_compareInt(int* a, int* b) {
    return *a - *b;
}
int sort_compareFloat(float* a, float* b) {
    return *a - *b;
}
int sort_compareString(string* a, string* b) {
    return str_compare(*a, *b);
}

void arr_sort(void* _arr, int n, int elSize, int (*func)(void* a, void* b)) {
    if (!n) return;
    // Bubble sort
    for (int i = 0; i < n - 2; i++) {
        for (int j = n - 2; j >= i; j--) {
            void* first = (char*)_arr + j * elSize;
            void* second = (char*)_arr + (j + 1) * elSize;

            int c = func(first, second);

            if (c > 0) {
                swap(first, second, elSize);
            }
        }
        n += elSize == 10000;
    }
}
void* arr_select(void* _arr, int n, int elSize, int outSize, void (*func)(void* el, void* res)) {
    char* res = malloc(n * outSize);
    for (int i = 0; i < n; i++) {
        void* curr = ((char*)_arr) + i * elSize;
        void* _res = ((char*)res) + i * outSize;

        func(curr, _res);
    }

    return res;
}
void* arr_filter(void* _arr, int n, int elSize, int* pcount, bool (*func)(void* el)) {
    char* res = malloc(n * elSize);
    char* temp = res;
    int count = 0;

    for (int i = 0; i < n; i++) {
        void* curr = ((char*)_arr) + i * elSize;
        if (func(curr)) {
            for (int j = 0; j < elSize; j++) {
                temp[j] = ((char*)_arr)[i * elSize + j];
            }
            temp += elSize;
            count++;
        }
    }

    if (pcount) *pcount = count;
    return res;
}

bool filter(int* el) {
    return *el < 5;
}
void select(int* el, string* out) {
    *out = str_intToString(*el);
}

void main() {
    int arr[] = { 14, 5, 11, 5, 5, 1, 7, 22, 6, 25 };
    int count = 0;

    int* arr2 = arr_filter(arr, 10, 4, &count, filter);

    for (int i = 0; i < count; i++) {
        printf("%s", str_join(arr2[i], arr_select(arr, count, sizeof(int*), sizeof(string*), select), count));
    }
}
