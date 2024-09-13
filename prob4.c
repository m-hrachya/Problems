#include <stdio.h>
#include <math.h>

typedef struct Point {
    float x;
    float y;
} Point;

double initialize(Point * point) {
    printf("Enter x: ");
    scanf("%f", &point->x);
    printf("Enter y: ");
    scanf("%f", &point->y);
    return sqrt((point->y * point->y) + (point->x * point->x));
}

double getLen(const Point * ptr1, const Point * ptr2) {
    float max_x = ptr1->x > ptr2->x ? ptr1->x : ptr2->x;
    float min_x = ptr1->x < ptr2->x ? ptr1->x : ptr2->x;
    float max_y = ptr1->y > ptr2->y ? ptr1->y : ptr2->y;
    float min_y = ptr1->y < ptr2->y ? ptr1->y : ptr2->y;
    float mid_x = max_x - min_x;
    float mid_y = max_y - min_y;
    return sqrt((mid_x * mid_x) + (mid_y * mid_y));
}

Point returnMiddlePoint(const Point * ptr1, const Point * ptr2) {
    Point middlePoint;
    float max_x = ptr1->x > ptr2->x ? ptr1->x : ptr2->x;
    float min_x = ptr1->x < ptr2->x ? ptr1->x : ptr2->x;
    float max_y = ptr1->y > ptr2->y ? ptr1->y : ptr2->y;
    float min_y = ptr1->y < ptr2->y ? ptr1->y : ptr2->y;
    middlePoint.x = ((max_x - min_x) / 2) + min_x;
    middlePoint.y = ((max_y - min_y) / 2) + min_y;
    return middlePoint;
}

int main() {
    Point points[3];
    double lens[3];
    for(int i = 0; i < 3; ++i) {
        lens[i] = initialize(&points[i]);
        printf("Len: %lf\n", lens[i]);
    }
    printf("1 && 2: %lf\n", getLen(&points[0], &points[1]));
    Point middlePoint = returnMiddlePoint(&points[0], &points[1]);
    printf("Middle Point of 1 && 2\nx: %f, y: %f\n", middlePoint.x, middlePoint.y);
    return 0;
}