#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

struct User_t {
    double latitude;
    double longitude;
    double altitude;
    double time;
    double distance;
    char username[100];
};

void scan_user(struct User_t *our_user_ptr, double lat, double longi, double alt, double time, char *name);
void scan_all_users(char *file, struct User_t *our_user_ptr, struct User_t *other_users, int num);
void cal_distance(struct User_t *userA, struct User_t *userB);
void cal_all_distance(int num, struct User_t *other_users, struct User_t *our_user_ptr);
struct User_t* find_nearest_user(struct User_t *other_users, int num);

int main() {
    int num;
    struct User_t *our_user_ptr, *nearest_user_ptr, our_user;
    our_user_ptr = &our_user;
    char filename[100];
    printf("Please enter the path for the file: \n");
    scanf("%s", filename);
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("Error: file does not exist.\n");
        exit(1);
    }
    fscanf(fp, "%d", &num);
    struct User_t *other_users = (struct User_t*) malloc((num+1) * sizeof(struct User_t));
    scan_all_users(filename, our_user_ptr, other_users, num);
    cal_all_distance(num, other_users, our_user_ptr);
    nearest_user_ptr = find_nearest_user(other_users, num);
    printf("The nearest user is: %s\n", nearest_user_ptr->username);
    printf("The position is: \nlatitude: %.2f\nlongitude: %.2f\naltitude: %.2f\n", nearest_user_ptr->latitude, nearest_user_ptr->longitude, nearest_user_ptr->altitude);
    return 0;
}

void scan_user(struct User_t *our_user_ptr, double lat, double longi, double alt, double time, char *name) {
    our_user_ptr->latitude = lat;
    our_user_ptr->longitude = longi;
    our_user_ptr->altitude = alt;
    our_user_ptr->time = time;
    our_user_ptr->distance = 0;
    strcpy(our_user_ptr->username, name);
}

void scan_all_users(char *file, struct User_t *our_user_ptr, struct User_t *other_users, int num) {
    char username[100];
    double lat, longi, alt, time;
    FILE *f = fopen(file, "r");
    fscanf(f, "%d", &num);
    fscanf(f, "%s", username);
    fscanf(f, "%lf", &time);
    fscanf(f, "%lf", &lat);
    fscanf(f, "%lf", &longi);
    fscanf(f, "%lf", &alt);
    scan_user(our_user_ptr, lat, longi, alt, time, username);
    for(int i = 0; i < num; ++i) {
        fscanf(f, "%s", username);
        fscanf(f, "%lf", &time);
        fscanf(f, "%lf", &lat);
        fscanf(f, "%lf", &longi);
        fscanf(f, "%lf", &alt);
        scan_user((other_users+i), lat, longi, alt, time, username);
    }
}

void cal_distance(struct User_t *userA, struct User_t *userB) {
    double dis;
    dis = sqrt(pow((userA->latitude - userB->latitude), 2) + pow((userA->longitude - userB->longitude), 2) + pow((userA->altitude - userB->altitude), 2));
    userB->distance = dis;
}

void cal_all_distance(int num, struct User_t *other_users, struct User_t *our_user_ptr) {
    for(int i = 0; i < num; ++i) {
        cal_distance(our_user_ptr, (other_users+i));
    }
}

struct User_t* find_nearest_user(struct User_t *other_users, int num) {
    double distance = INT_MAX;
    struct User_t *nearest_user;
    for(int i = 0; i < num; ++i) {
        if((other_users+i)->distance < distance) {
            distance = (other_users+i)->distance;
            nearest_user = (other_users + i);
        }
    }
    return nearest_user;
}



