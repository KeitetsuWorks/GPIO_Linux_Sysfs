/**
 * @file        GPIO.c
 * @brief       GPIO Control Functions
 * @author      Keitetsu
 * @date        2016/09/29
 * @copyright   Copyright (c) 2016 Keitetsu
 * @license     This software is released under the MIT License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "GPIO.h"


int gpio_export(GPIO_T *target)
{
    int fd_export;
    char buf_port_str[BUF_PORT_STR_MAX];
    int buf_port_str_used;
    char buf_path_str[BUF_PATH_STR_MAX];
    int buf_path_str_used;
    struct stat stat_port;
    int retval;

    buf_port_str_used = snprintf(buf_port_str, BUF_PORT_STR_MAX, "%d", target->port);
    if(buf_port_str_used < 0 || buf_port_str_used >= BUF_PORT_STR_MAX) {
        printf("Error: invalid gpio port \"gpio%d\"\n", target->port);

        return 1;
    }

    buf_path_str_used = snprintf(
            buf_path_str,
            BUF_PATH_STR_MAX,
            "/sys/class/gpio/gpio%d",
            target->port);
    if(buf_path_str_used < 0 || buf_path_str_used >= BUF_PATH_STR_MAX) {
        printf("Error: invalid gpio port \"gpio%d\"\n", target->port);

        return 1;
    }
    if(stat(buf_path_str, &stat_port) == 0) {
        printf("Warning: gpio%d is already exported\n", target->port);

        return 0;
    }

    fd_export = open("/sys/class/gpio/export", O_WRONLY);
    if(fd_export == -1) {
        printf("Error: failed to open gpio export file\n");

        return 1;
    }

    retval = write(fd_export, buf_port_str, buf_port_str_used);
    if(retval != buf_port_str_used) {
        printf("Error: faild to export gpio%d\n", target->port);

        return 1;
    }

    close(fd_export);

    return 0;
}


int gpio_unexport(GPIO_T *target)
{
    int fd_unexport;
    char buf_port_str[BUF_PORT_STR_MAX];
    int buf_port_str_used;
    char buf_path_str[BUF_PATH_STR_MAX];
    int buf_path_str_used;
    struct stat stat_port;
    int retval;

    buf_port_str_used = snprintf(buf_port_str, BUF_PORT_STR_MAX, "%d", target->port);
    if(buf_port_str_used < 0 || buf_port_str_used >= BUF_PORT_STR_MAX) {
        printf("Error: invalid gpio port \"gpio%d\"\n", target->port);

        return 1;
    }

    buf_path_str_used = snprintf(
            buf_path_str,
            BUF_PATH_STR_MAX,
            "/sys/class/gpio/gpio%d",
            target->port);
    if(buf_path_str_used < 0 || buf_path_str_used >= BUF_PATH_STR_MAX) {
        printf("Error: invalid gpio port \"gpio%d\"\n", target->port);

        return 1;
    }
    if(stat(buf_path_str, &stat_port) == -1) {
        printf("Warning: gpio%d is already unexported\n", target->port);

        return 0;
    }

    fd_unexport = open("/sys/class/gpio/unexport", O_WRONLY);
    if(fd_unexport == -1) {
        printf("Error: failed to open gpio unexport file\n");

        return 1;
    }

    retval = write(fd_unexport, buf_port_str, buf_port_str_used);
    if(retval != buf_port_str_used) {
        printf("Error: faild to unexport gpio%d\n", target->port);

        return 1;
    }

    close(fd_unexport);

    return 0;
}


int gpio_set_direction(GPIO_T *target)
{
    char buf_path_str[BUF_PATH_STR_MAX];
    int buf_path_str_used;
    int fd_direction;
    const char *direction_in = "in";
    const char *direction_out = "out";
    int retval;

    buf_path_str_used = snprintf(
            buf_path_str,
            BUF_PATH_STR_MAX,
            "/sys/class/gpio/gpio%d/direction",
            target->port);
    if(buf_path_str_used < 0 || buf_path_str_used >= BUF_PATH_STR_MAX) {
        printf("Error: invalid gpio port \"gpio%d\"\n", target->port);

        return 1;
    }

    fd_direction = open(buf_path_str, O_WRONLY);
    if(fd_direction == -1) {
        printf("Error: failed to open gpio direction file\n");

        return 1;
    }

    if(target->direction == GPIO_INPUT) {
        retval = write(fd_direction, direction_in, strlen(direction_in));
        if(retval != (int)strlen(direction_in)) {
            printf("Error: faild to set gpio%d direction\n", target->port);
            
            return 1;
        }
    }
    else if(target->direction == GPIO_OUTPUT) {
        retval = write(fd_direction, direction_out, strlen(direction_out));
        if(retval != (int)strlen(direction_out)) {
            printf("Error: faild to set gpio%d direction\n", target->port);
            
            return 1;
        }
    }
    else{
        printf("Error: invalid gpio direction\n");

        return 1;
    }

    close(fd_direction);

    return 0;
}


int gpio_open(GPIO_T *target)
{
    int retval;

    retval = gpio_export(target);
    if(retval != 0) {
        return retval;
    }

    retval = gpio_set_direction(target);
    if(retval != 0) {
        return retval;
    }

    return 0;
}


int gpio_close(GPIO_T *target)
{
    return gpio_unexport(target);
}


int gpio_read(GPIO_T *target)
{
    char buf_path_str[BUF_PATH_STR_MAX];
    int buf_path_str_used;
    int fd_value;
    char buf_value_str[BUF_VALUE_STR_MAX];
    int retval;
    int value;

    buf_path_str_used = snprintf(
            buf_path_str,
            BUF_PATH_STR_MAX,
            "/sys/class/gpio/gpio%d/value",
            target->port);
    if(buf_path_str_used < 0 || buf_path_str_used >= BUF_PATH_STR_MAX) {
        printf("Error: invalid gpio port \"gpio%d\"\n", target->port);

        return 1;
    }

    fd_value = open(buf_path_str, O_RDONLY);
    if(fd_value == -1) {
        printf("Error: failed to open gpio value file\n");

        return 1;
    }

    retval = read(fd_value, buf_value_str, BUF_VALUE_STR_MAX);
    if(retval == -1) {
        printf("Error: failed to read gpio%d value\n", target->port);

        return 1;
    }

    close(fd_value);

    value = atoi(buf_value_str);

    return value;
}


int gpio_write(GPIO_T *target, int value)
{
    char buf_path_str[BUF_PATH_STR_MAX];
    int buf_path_str_used;
    int fd_value;
    const char *value_low = "0";
    const char *value_high = "1";
    int retval;

    buf_path_str_used = snprintf(
            buf_path_str,
            BUF_PATH_STR_MAX,
            "/sys/class/gpio/gpio%d/value",
            target->port);
    if(buf_path_str_used < 0 || buf_path_str_used >= BUF_PATH_STR_MAX) {
        printf("Error: invalid gpio port \"gpio%d\"\n", target->port);

        return 1;
    }

    fd_value = open(buf_path_str, O_WRONLY);
    if(fd_value == -1) {
        printf("Error: failed to open gpio value file\n");

        return 1;
    }

    if(value == GPIO_LOW) {
        retval = write(fd_value, value_low, strlen(value_low));
        if(retval != (int)strlen(value_low)) {
            printf("Error: failed to write gpio%d value\n", target->port);
            
            return 1;
        }
    }
    else if(value == GPIO_HIGH) {
        retval = write(fd_value, value_high, strlen(value_high));
        if(retval != (int)strlen(value_high)) {
            printf("Error: faild to write gpio%d value\n", target->port);
            
            return 1;
        }
    }
    else{
        printf("Error: invalid gpio output value \"%d\"\n", value);

        return 1;
    }

    close(fd_value);

    return 0;
}

