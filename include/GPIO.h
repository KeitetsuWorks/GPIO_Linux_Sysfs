/**
 * @file    GPIO.h
 * @brief   GPIO Control Functions
 * @author  Keitetsu
 * @date    2016/09/29
 */

#pragma once    // __GPIO_H__

#define BUF_PORT_STR_MAX    4               /*!< GPIOポート番号文字列の最大サイズ */
#define BUF_PATH_STR_MAX    40              /*!< ファイルパス文字列の最大サイズ */
#define BUF_VALUE_STR_MAX   2               /*!< GPIO値文字列の最大サイズ */


/**
 * @enum    gpio_dir_e
 * @brief   GPIOポートの入出力方向
 *
 * @typedef GPIO_DIR_E
 * @brief   GPIOポートの入出力方向
 */
typedef enum gpio_dir_e {
    GPIO_INPUT = 0,     /*!< GPIO入力ポート */
    GPIO_OUTPUT         /*!< GPIO出力ポート */
} GPIO_DIR_E;


/**
 * @enum    gpio_value_e
 * @brief   GPIOポートの論理
 *
 * @typedef GPIO_VALUE_E
 * @brief   GPIOポートの論理
 */
typedef enum gpio_value_e {
    GPIO_LOW = 0,       /*!< Low */
    GPIO_HIGH           /*!< High */
} GPIO_VALUE_E;


/**
 * @struct  gpio_t
 * @brief   GPIOポートの情報
 *
 * @typedef GPIO_T
 * @brief   GPIOポートの情報
 */
typedef struct gpio_t {
    int port;           /*!< GPIOポート番号 */
    int direction;      /*!< GPIOポートの入出力方向 */
} GPIO_T;


// プロトタイプ宣言
/**
 * @brief   Export GPIO Port
 * @param[in]       target      GPIO Port Information
 * @retval          0           Success
 * @retval          1           Failure
 */
int gpio_export(GPIO_T *target);


/**
 * @brief   Unexport GPIO Port
 * @param[in]       target      GPIO Port Information
 * @retval          0           Success
 * @retval          1           Failure
 */
int gpio_unexport(GPIO_T *target);


/**
 * @brief   Set GPIO Direction
 * @param[in]       target      GPIO Port Information
 * @retval          0           Success
 * @retval          1           Failure
 */
int gpio_set_direction(GPIO_T *target);


/**
 * @brief   Open GPIO Port (Export GPIO Port, and Set GPIO Direction)
 * @param[in]       target      GPIO Port Information
 * @retval          0           Success
 * @retval          1           Failure
 */
int gpio_open(GPIO_T *target);


/**
 * @brief   Close GPIO (Unexport GPIO)
 * @param[in]       target      GPIO Port Information
 * @retval          0           Success
 * @retval          1           Failure
 */
int gpio_close(GPIO_T *target);


/**
 * @brief   Read Value from GPIO Port
 * @param[in]       target      GPIO Port Information
 * @return          Read Value from GPIO Port
 */
int gpio_read(GPIO_T *target);


/**
 * @brief   Write Value to GPIO Port
 * @param[in]       target      GPIO Port Information
 * @param[in]       value       Write Value for GPIO Port
 * @retval          0           Success
 * @retval          1           Failure
 */
int gpio_write(GPIO_T *target, int value);

