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

/** \brief This file implements the Flash Update Services functionality
 **
 ** This file implements the functionality of the Flash Update Services
 **
 ** \todo Improve flash writing functionality: Delete the block to be written
 ** and implement a dirty block marking feature.
 ** \todo Implement a write optimization method which buffers the data sent
 ** by the protocol until there is a full block to write or the current
 ** data segment finishes.
 ** \todo Improve the performance by adding an additional thread to store the
 ** data.
 ** \todo Update credits
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
#include "ciaaPOSIX_assert.h"
#include "ciaaPOSIX_stdio.h"
#include "ciaaUpdate_protocol.h"
#include "ciaaUpdate_services.h"
#include "ciaaUpdate_transport.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/** \brief flash file descriptor */
static int32_t ciaaUpdate_services_flash_fd = -1;

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static ssize_t ciaaUpdate_servicesStore(const void *data, size_t size, uint32_t address)
{
   int32_t ret;
   ciaaPOSIX_assert(-1 != ciaaUpdate_services_flash_fd);

   ret = ciaaPOSIX_lseek(ciaaUpdate_services_flash_fd, address, SEEK_SET);
   ciaaPOSIX_assert(address == ret);

   ret = ciaaPOSIX_write(ciaaUpdate_services_flash_fd, data, size);
   ciaaPOSIX_assert(size == ret);

   return ret;
}
/*==================[external functions definition]==========================*/
int32_t ciaaUpdate_servicesStart(
   ciaaUpdate_transportType *transport,
   int32_t flash_fd
)
{
   int32_t error;

   ciaaUpdate_services_flash_fd = flash_fd;
   ciaaPOSIX_assert(-1 != ciaaUpdate_services_flash_fd);

   error = ciaaUpdate_protocolRecv(transport, ciaaUpdate_servicesStore);

   ciaaUpdate_services_flash_fd = -1;
   return error;
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/