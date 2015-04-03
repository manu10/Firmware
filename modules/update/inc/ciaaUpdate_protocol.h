/* Copyright 2014, Daniel Cohen
 * Copyright 2014, Esteban Volentini
 * Copyright 2014, Matias Giori
 * Copyright 2014, Franco Salinas
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _CIAAUPDATE_PROTOCOL_H_
#define _CIAAUPDATE_PROTOCOL_H_
/** \brief Flash Update Protocol Header File
 **
 ** This files shall be included by moodules using the interfaces provided by
 ** the Flash Update Protocol
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Updater CIAA Updater Service
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * DC           Daniel Cohen
 * EV           Esteban Volentini
 * MG           Matias Giori
 * FS           Franco Salinas
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20141010 v0.0.1  EV  first initial version
 */

/*==================[inclusions]=============================================*/
#include "ciaaUpdate_transport.h"
#include "ciaaUpdate_utils.h"

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

#define CIAAUPDATE_PROTOCOL_ERROR_NONE                0
#define CIAAUPDATE_PROTOCOL_ERROR_UNKNOWN_VERSION     1
/*==================[typedef]================================================*/
/** \brief Stores the data received at the specified address.
 ** \param data Data to be written.
 ** \param size Number of bytes to write.
 ** \param address Address to write at.
 ** \return On success the number of bytes written. If this number differs
 ** from the size parameter an error occurred.
 **/
typedef ssize_t (*ciaaUpdate_protocolStoreCallback) (const void *data, size_t size, uint32_t address);
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** \brief Performs all protocol operations to receive a binary image through
 ** the specified transport type and stores it using the provided function **
 ** \param transport Transport layer descriptor.
 ** \param store_cb Callback function to store data at a specific address.
 **/
int32_t ciaaUpdate_protocolRecv(
   ciaaUpdate_transportType* transport,
   ciaaUpdate_protocolStoreCallback store_cb);
/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
}
#endif
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _CIAAUPDATE_PROTOCOL_H_ */
