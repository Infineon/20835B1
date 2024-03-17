/*
 * Copyright 2016-2024, Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
 *
 * This software, including source code, documentation and related
 * materials ("Software") is owned by Cypress Semiconductor Corporation
 * or one of its affiliates ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products.  Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
 */

/** @file
 *
 * List of parameters and defined functions needed to access the
 * Inter-Integrated Circuit (I2C, IIC) driver.
 *
 */

#ifndef __WICED_I2C_DRIVER_H__
#define __WICED_I2C_DRIVER_H__

#include "brcm_fw_types.h"

/**  \addtogroup I2CDriver I2C
 * \ingroup HardwareDrivers
 * @{
 *
 * Defines an I2C driver to facilitate communication with other devices on an
 * I2C bus (such as a temperature sensor, etc). The driver is only capable of
 * assuming a master role. Applications use this driver to obtain the status
 * from and control the behavior of the I2C hardware. This driver only offers
 * services for speed control and data transfer operations.
 *
 * Please note that even though this driver can access off-chip memory
 * (if installed; EEPROM, etc), please use the drivers found in
 * wiced_hal_ieeprom.h to access those modules, as those drivers include
 * checks to ensure safe data handling operations. This driver is intended
 * only to interface with other devices on the I2C bus, such as a motion
 * sensor.
 *
 */

/******************************************************************************
 *** Parameters.
 ***
 *** The following parameters are used to configure the driver or define
 *** return status. They are not modifiable.
 ******************************************************************************/

/// Speed Options
enum
{
    /// I2C speed is 100 KHz
    I2CM_SPEED_100KHZ = 240,

    /// I2C speed is 400 KHz
    I2CM_SPEED_400KHZ = 60,

    /// I2C speed is 800 KHz
    I2CM_SPEED_800KHZ = 30,

    /// I2C speed is 1 MHz
    I2CM_SPEED_1000KHZ = 24,
};

/// Transaction Status Return Values
enum
{
    /// The transaction was sucessful
    I2CM_SUCCESS,

    /// The attempted operation failed, possibly because
    /// of no ack from slave.
    I2CM_OP_FAILED,
};

/******************************************************************************
 *** Function prototypes.
 ******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
/// Initializes the I2C driver and its private values. This initialization
/// sets the bus speed to 100KHz by default (I2CM_SPEED_100KHZ). To make
/// the bus run at another speed, call wiced_hal_i2c_setSpeed(<speed>)
/// right after this call.
///
/// I2C pins are configured through platform_gpio_pins[] in wiced_platform_pin_config.c
/// In case of change in I2C pins from default platform initialization,
/// the user needs to use external pull-ups or internal GPIO pull-ups.
/// It is recommended to use external pull-ups for a reliable design
///
/// \param none
///
/// \return none
///////////////////////////////////////////////////////////////////////////////
void wiced_hal_i2c_init(void);

///////////////////////////////////////////////////////////////////////////////
/// Sets the I2C bus speed. Note that the default after initialization is
/// set to 100KHz by default (I2CM_SPEED_100KHZ). To make the bus run at
/// another speed, use one of the following parameters (also see Parameters
/// section):
///
///
///     // I2C speed is 100 KHz
///     I2CM_SPEED_100KHZ
///
///     // I2C speed is 400 KHz
///     I2CM_SPEED_400KHZ
///
///     // I2C speed is 800 KHz
///     I2CM_SPEED_800KHZ
///
///     // I2C speed is 1 MHz
///     I2CM_SPEED_1000KHZ
///
/// \param speed - The new speed to be used. This is the transport clock counter
/// that counts the number of reference clock cycles.
///
/// \return none
///////////////////////////////////////////////////////////////////////////////
void wiced_hal_i2c_set_speed(UINT8 speed);


///////////////////////////////////////////////////////////////////////////////
/// Gets the current I2C bus speed. Smaller numbers indicate higher speeds.
/// See the Parameters section for more information.
///
/// \param none
///
/// \return The SCL ref clock cycle counter value that corresponding to
/// the SCL speed.
///////////////////////////////////////////////////////////////////////////////
UINT8 wiced_hal_i2c_get_speed(void);


///////////////////////////////////////////////////////////////////////////////
/// Reads data into given buffer from the I2C HW addressing a particualr
/// slave address. The data bytes are transparent. Though any arbitrary
/// length of data may be read from the slave, atomic transactions greater
/// than HW's capability are not possible - they will be split into multiple
/// transactions. This is a blocking call. Interrupts will not affect timing
/// within a transaction.
/// Note: Please see the Kit Guide or HW User Manual for your device for the
/// actual limitation of the part on your platform.
///
/// \param data   - Pointer to a buffer that will hold the incoming data.
/// \param length - The length of the data to read.
/// \param slave  - The source slave address.
///
/// \return The status of the transaction (success[0], failure[1]).
///////////////////////////////////////////////////////////////////////////////
UINT8 wiced_hal_i2c_read(UINT8 *data, UINT16 length, UINT8 slave);


///////////////////////////////////////////////////////////////////////////////
/// Writes the given data to the I2C HW addressing a particualr slave address.
/// The data bytes are transparent. Though any arbitrary length of data may be
/// written to the slave, atomic transactions greater than HW's capability
/// are not possible - they will be split into multiple transactions. This is
/// a blocking call. Interrupts will not affect timing within a transaction.
/// Note: Please see the Kit Guide or HW User Manual for your device for the
/// actual limitation of the part on your platform.
///
/// \param data   - Pointer to a buffer holding the data to write.
/// \param length - The length of the data to write.
/// \param slave  - The destination slave address.
///
/// \return The status of the transaction (success[0], failure[1]).
///////////////////////////////////////////////////////////////////////////////
UINT8 wiced_hal_i2c_write(UINT8 *data, UINT16 length, UINT8 slave);

///////////////////////////////////////////////////////////////////////////////
/// Configures I2C pins
///
/// \param scl_pin LHL GPIO to be used for SCL
/// \param sda_pin LHL GPIO to be used for SDA
///
///////////////////////////////////////////////////////////////////////////////
void wiced_hal_i2c_select_pads(UINT8 scl_pin, UINT8 sda_pin);

////////////////////////////////////////////////////////////////////////////////
/// Executes two transactions back-to-back with a repeated start condition between
/// the first and the second. tx_data is written to the slave in the first transaction
/// while data is read back from the slave into rx_data after the repeated start.
/// \param rx_data Pointer to the buffer where data is to be read after the repeated start
/// \param rx_data_len Number of bytes to read from slaveAdr - rx_data should be at least this big
/// \param tx_data Pointer to the buffer that is to be written to the slave
/// \param tx_data_len Number of bytes to write to the slave starting from tx_data
/// \param slave   slave addr
/// \return The status of the transaction (success[0], failure[1])
///////////////////////////////////////////////////////////////////////////////
UINT8 wiced_hal_i2c_combined_read(UINT8 *rx_data, UINT8 rx_data_len, UINT8 *tx_data, UINT16 tx_data_len, UINT8 slave);

/*******************************************************************************
 *
 * For I2C slave, please add
 * CY_20819A1_APP_PATCH_LIBS += wiced_hal_i2c_slave_lib.a
 * in the app's makefile.
 *
 * Usage example:
 *  1. setup your slave device address by calling wiced_hal_i2c_slave_set_device_address.
 *  2. setup your gpio pins by calling wiced_hal_i2c_slave_select_pads.
 *  3. Register app's call back function by calling wiced_hal_i2c_slave_register_cb.
 *  4. Initialize I2C slave by calling wiced_hal_i2c_slave_init.
 *  5. Please make sure I2C master has the time interval at least 10ms between each I2C read/write.
 *******************************************************************************/
enum
{
    I2C_TRAN_EVENT_MASK_RX_DONE = 1,
    I2C_TRAN_EVENT_MASK_TX_DONE = 2,
    I2C_TRAN_EVENT_MASK_RX_STOP = 4,
};

/*
 * I2C_SLAVE_CALLBACK_HANDLER
 *
 * Description:
 *      This is a call back function while the firmware has RX or TX event.
 * Input:
 *      evtFlag       - The event Flag as following:
 *                      enum
 *                      {
 *                          I2C_TRAN_EVENT_MASK_RX_DONE = 1,
 *                          I2C_TRAN_EVENT_MASK_TX_DONE = 2,
 *                          I2C_TRAN_EVENT_MASK_RX_STOP = 4,
 *                      };
 *      rx_PktPointer - Point to a caller's buffer which will have received data.
 *      rx_PktLength  - The received data length (in bytes).
 * Output:
 *      None
 * Return:
 *      None
 */
typedef void I2C_SLAVE_CALLBACK_HANDLER(uint32_t evtFlag, uint8_t *rx_PktPointer, uint16_t rx_PktLength);

/*
 * wiced_hal_i2c_slave_set_device_address
 *
 * Description:
 *      Set the 7-bit I2C slave device address.
 *      By default, the device addresses are 0x77, 0x76, and 0x66
 * Input:
 *      address - 7-bit I2C slave device address.
 * Output:
 *      None
 * Return:
 *      None
 */
void wiced_hal_i2c_slave_set_device_address(UINT8 address);

/*
 * wiced_hal_i2c_slave_select_pads
 *
 * Description:
 *      Select the SCL and SDA for the I2C slave hardware to use.
 * Input:
 *      scl_pin - SCL pin for I2C slave (input)
 *      sda_pin - SDA pin ofr I2C slave (input/output)
 * Output:
 *      None
 * Return:
 *      None
 */
void wiced_hal_i2c_slave_select_pads(UINT32 scl_pin, UINT32 sda_pin);

/*
 * wiced_hal_i2c_slave_init
 *
 * Description:
 *      Initializes the I2C slave driver
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      None
 */
void wiced_hal_i2c_slave_init(void);

/*
 * wiced_hal_i2c_slave_register_cb
 *
 * Description:
 *      The WICED Application call this function to register a call back function.
 *      The call back function will be called after received data from I2C master.
 * Input:
 *      cb - Call back function of caller
 * Output:
 *      None
 * Return:
 *      None
 */
void wiced_hal_i2c_slave_register_cb(I2C_SLAVE_CALLBACK_HANDLER *cb);

/*
 * wiced_hal_i2c_slave_synchronous_write
 *
 * Description:
 *      This function processes write request
 * Input:
 *      buffer - Point to the data buffer
 *      length - Bytes will be transmited
 * Output:
 *      None
 * Return:
 *      None
 */
void wiced_hal_i2c_slave_synchronous_write(UINT8 *buffer, UINT32 length);


/** @} */

#endif // __WICED_I2C_DRIVER_H__
