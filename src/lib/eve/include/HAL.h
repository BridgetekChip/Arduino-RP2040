/**
* @file HAL.h
* @brief This header file will contain all required EVE's HAL functions
*
* @author BridgeTek
*
* @date 2019
*/

#ifndef HAL_HEADER_H
#define	HAL_HEADER_H

#include <stdint.h> // for Uint8/16/32 and Int8/16/32 data types

/**
 @brief Initialise EVE HAL Layer.
 @details Power cycle and start the EVE display in a controlled manner.
 	 This will call the MCU-specific initialisation routine and check for
 	 the presence of a supported FT8xx device on the SPI bus.
 */
void HAL_EVE_Init(void);

/**
 @brief Chip Select Control
 @details Abstract the low-level MCU chip select control to either
 	 enable or disable. A call to this function to enable chip select
 	 will result in a logic low on the SPI CS line.
 @param enable - Non-zero to enable chip select
 	 	 	 	  Zero to deselect.
 */
void HAL_ChipSelect(int8_t enable);

/**
 @brief Power Down Control
 @details Abstract the low-level MCU power down control line to
 	 control the EVE display. A call to this function to enable
 	 power down will result in a logig low on the PD line.
 @param enable - Non-zero to enable power down
 	 	 	 	  Zero to disable (normal operating state of EVE).
 */
void HAL_PowerDown(int8_t enable);

/**
 @brief Increment command memory write pointer
 @details The command memory write pointer stores the current
 	 location where coprocessor commands are written. This is
 	 kept internally in the HAL and is NOT written to the
 	 REG_CMD_WRITE register on EVE until the HAL_WriteCmdPointer
 	 function is called. This allows multiple commands (up-to
 	 the size of the command memory) to be stored and executed
 	 when required.
 @param commandSize - The number of bytes to advance the command
  	 memory write pointer. This will wrap at the end of the
  	 command memory.
 */
void HAL_IncCmdPointer(uint16_t commandSize);

/**
 @brief Get the current command memory write pointer
 @details Obtains the current command memory write pointer from
 	 the value stored internally in the HAL. It is not the value
 	 read from the REG_CMD_WRITE register.
 @returns Command memory write pointer
 */
uint16_t HAL_GetCmdPointer(void);

/**
 @brief Commits the current command memory write pointer
 @details Stores the internal HAL command memory write pointer to
 	 the REG_CMD_WRITE register. This will start the coprocessor
 	 working through items in the display list.
 */
void HAL_WriteCmdPointer(void);

/**
 @brief Wait for display list to complete
 @details Polls the REG_CMD_READ register until it matches the
 	 current command memory write pointer. This will indicate that
 	 the coprocessor has completed working through the items in the
 	 display list.
 @returns Zero for normal completion or 0xff for an error condition.
 */
uint8_t HAL_WaitCmdFifoEmpty(void);

/**
 @brief Calculate free space in the command memory.
 @details Works out how many bytes of command memory is available
 	 to receive display list instructions. There will always be
 	 4 bytes (one display list entry) reserved in the command memory
 	 to ensure that the display list can never create a loop.
 @returns Number of free bytes.
 */
uint16_t HAL_CheckCmdFreeSpace(void);

/**
 @brief Write a 32 bit value to an EVE memory location
 @details Formats a memory space write to EVE. This can be any register
   	   or mapped memory on the device (display list or command list).
   	   This function will control chip select.
 @param address - 24 bit address on EVE
 @param val32 - value to write
 */
void HAL_MemWrite32(uint32_t address, uint32_t val32);

/**
 @brief Write a 16 bit value to an EVE memory location
 @details Formats a memory space write to EVE. This can be any register
   	   or mapped memory on the device (display list or command list).
   	   This function will control chip select.
 @param address - 24 bit address on EVE
 @param val16 - value to write
 */
void HAL_MemWrite16(uint32_t address, uint16_t val16);

/**
 @brief Write an 8 bit value to an EVE memory location
 @details Formats a memory space write to EVE. This can be any register
   	   or mapped memory on the device (display list or command list).
   	   This function will control chip select.
 @param address - 24 bit address on EVE
 @param val8 - value to write
 */
void HAL_MemWrite8(uint32_t address, uint8_t val8);

/**
 @brief Read a 32 bit value from an EVE memory location
 @details Formats a memory space read to EVE. This can be any register
   	   or mapped memory on the device (display list or command list).
   	   This function will control chip select.
 @param address - 24 bit address on EVE
 @returns value read from EVE
 */
uint32_t HAL_MemRead32(uint32_t address);

/**
 @brief Read a 16 bit value from an EVE memory location
 @details Formats a memory space read to EVE. This can be any register
   	   or mapped memory on the device (display list or command list).
   	   This function will control chip select.
 @param address - 24 bit address on EVE
 @returns value read from EVE
 */
uint16_t HAL_MemRead16(uint32_t address);

/**
 @brief Read an 8 bit value from an EVE memory location
 @details Formats a memory space read to EVE. This can be any register
   	   or mapped memory on the device (display list or command list).
   	   This function will control chip select.
 @param address - 24 bit address on EVE
 @returns value read from EVE
 */
uint8_t HAL_MemRead8(uint32_t address);

/**
 @brief Sends an address for writing to EVE
 @details Formats a memory address for writing to the EVE.
   	   This function will not control chip select.
 @param address - 24 bit address on EVE
 */
void HAL_SetWriteAddress(uint32_t address);

/**
 @brief Sends an address for reading to EVE
 @details Formats a memory address for read from the EVE.
   	   This function will not control chip select.
 @param address - 24 bit address on EVE
 */
void HAL_SetReadAddress(uint32_t address);

/**
 @brief Sends an 8 bit command to EVE
 @details Sends a 8 bit command and paramter using SPI to the EVE.
   	   This function will control chip select.
 @returns 8 bit value read
 */
void HAL_HostCmdWrite(uint8_t cmd, uint8_t param);

/**
 @brief Sends a block of data to EVE
 @details Sends a block of data using SPI to the EVE.
   	   This function will not control chip select.
 @param val32 - 32 bit value
 */
void HAL_Write(const uint8_t *buffer, uint32_t length);

/**
 @brief Sends a 32 bit value to EVE
 @details Sends a 32 bit value using SPI to the EVE.
   	   This function will not control chip select.
 @param val32 - 32 bit value
 */
void HAL_Write32(uint32_t val32);

/**
 @brief Sends a 16 bit value to EVE
 @details Sends a 16 bit value using SPI to the EVE.
   	   This function will not control chip select.
 @param val16 - 16 bit value
 */
void HAL_Write16(uint16_t val16);

/**
 @brief Sends a 8 bit value to EVE
 @details Sends a 8 bit value using SPI to the EVE.
   	   This function will not control chip select.
 @param val8 - 8 bit value
 */
void HAL_Write8(uint8_t val8);

/**
 @brief Reads a 32 bit value from EVE
 @details Sends a 32 bit dummy value using SPI to the EVE
 	 and receives the result.
   	   This function will not control chip select.
 @returns 32 bit value read
 */
uint32_t HAL_Read32(void);

/**
 @brief Reads a 16 bit value from EVE
 @details Sends a 16 bit dummy value using SPI to the EVE
 	 and receives the result.
   	   This function will not control chip select.
 @returns 16 bit value read
 */
uint16_t HAL_Read16(void);

/**
 @brief Reads a 8 bit value from EVE
 @details Sends a 8 bit dummy value using SPI to the EVE
 	 and receives the result.
   	   This function will not control chip select.
 @returns 8 bit value read
 */
uint8_t HAL_Read8(void);

#endif	/* HAL_HEADER_H */
