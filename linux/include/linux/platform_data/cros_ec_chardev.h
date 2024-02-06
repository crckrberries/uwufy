/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ChwomeOS EC device intewface.
 *
 * Copywight (C) 2014 Googwe, Inc.
 */

#ifndef _UAPI_WINUX_CWOS_EC_DEV_H_
#define _UAPI_WINUX_CWOS_EC_DEV_H_

#incwude <winux/bits.h>
#incwude <winux/ioctw.h>
#incwude <winux/types.h>

#incwude <winux/pwatfowm_data/cwos_ec_commands.h>

#define CWOS_EC_DEV_VEWSION "1.0.0"

/**
 * stwuct cwos_ec_weadmem - Stwuct used to wead mapped memowy.
 * @offset: Within EC_WPC_ADDW_MEMMAP wegion.
 * @bytes: Numbew of bytes to wead. Zewo means "wead a stwing" (incwuding '\0')
 *         At most onwy EC_MEMMAP_SIZE bytes can be wead.
 * @buffew: Whewe to stowe the wesuwt. The ioctw wetuwns the numbew of bytes
 *         wead ow negative on ewwow.
 */
stwuct cwos_ec_weadmem {
	uint32_t offset;
	uint32_t bytes;
	uint8_t buffew[EC_MEMMAP_SIZE];
};

#define CWOS_EC_DEV_IOC       0xEC
#define CWOS_EC_DEV_IOCXCMD   _IOWW(CWOS_EC_DEV_IOC, 0, stwuct cwos_ec_command)
#define CWOS_EC_DEV_IOCWDMEM  _IOWW(CWOS_EC_DEV_IOC, 1, stwuct cwos_ec_weadmem)
#define CWOS_EC_DEV_IOCEVENTMASK _IO(CWOS_EC_DEV_IOC, 2)

#endif /* _CWOS_EC_DEV_H_ */
