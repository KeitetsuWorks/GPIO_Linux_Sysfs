/**
 * @file        GPIO.h
 * @brief       GPIO Control Functions
 * @author      Keitetsu
 * @date        2016/09/29
 * @copyright   Copyright (c) 2016 Keitetsu
 * @license     This software is released under the MIT License.
 */

#pragma once    // __GPIO_H__


/**
 * @name    バッファサイズ
 */
/*! @{ */
#define BUF_PORT_STR_MAX    4   /*!< GPIOポート番号文字列の最大サイズ */
#define BUF_PATH_STR_MAX    40  /*!< ファイルパス文字列の最大サイズ */
#define BUF_VALUE_STR_MAX   2   /*!< GPIO値文字列の最大サイズ */
/*! @} */


/**
 * @name    GPIOポートの論理
 */
/*! @{ */
#define GPIO_LOW            0   /*!< Low */
#define GPIO_HIGH           1   /*!< High */
/*! @} */


/**
 * @enum    gpio_dir_e
 * @brief   GPIOポートの入出力方向
 *
 * @typedef GPIO_DIR_E
 * @brief   GPIOポートの入出力方向
 */
typedef enum gpio_dir_e {
    GPIO_INPUT = 0,             /*!< GPIO入力ポート */
    GPIO_OUTPUT,                /*!< GPIO出力ポート */
    GPIO_DIR_E_NUM              /*!< GPIO_DIR_Eの列挙数 */
} GPIO_DIR_E;


/**
 * @struct  gpio_t
 * @brief   GPIOポートの情報
 *
 * @typedef GPIO_T
 * @brief   GPIOポートの情報
 */
typedef struct gpio_t {
    int port;                   /*!< GPIOポート番号 */
    GPIO_DIR_E direction;       /*!< GPIOポートの入出力方向 */
} GPIO_T;


/**
 * @brief   Export GPIO Port
 * @param[in]       target      GPIO Port Information
 * @retval          0           Success
 * @retval          -1          Failure
 */
int gpio_export(GPIO_T *target);


/**
 * @brief   Unexport GPIO Port
 * @param[in]       target      GPIO Port Information
 * @retval          0           Success
 * @retval          -1          Failure
 */
int gpio_unexport(GPIO_T *target);


/**
 * @brief   Set GPIO Direction
 * @param[in]       target      GPIO Port Information
 * @retval          0           Success
 * @retval          -1          Failure
 */
int gpio_set_direction(GPIO_T *target);


/**
 * @brief   Open GPIO Port (Export GPIO Port, and Set GPIO Direction)
 * @param[in]       target      GPIO Port Information
 * @retval          0           Success
 * @retval          -1          Failure
 */
int gpio_open(GPIO_T *target);


/**
 * @brief   Close GPIO (Unexport GPIO)
 * @param[in]       target      GPIO Port Information
 * @retval          0           Success
 * @retval          -1          Failure
 */
int gpio_close(GPIO_T *target);


/**
 * @brief   Read Value from GPIO Port
 * @param[in]       target      GPIO Port Information
 * @retval          -1          Failure
 * @retval          Others      Read Value from GPIO Port
 */
int gpio_read(GPIO_T *target);


/**
 * @brief   Write Value to GPIO Port
 * @param[in]       target      GPIO Port Information
 * @param[in]       value       Write Value for GPIO Port
 * @retval          0           Success
 * @retval          -1          Failure
 */
int gpio_write(GPIO_T *target, int value);

