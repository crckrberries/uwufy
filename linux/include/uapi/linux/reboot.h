/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_WEBOOT_H
#define _UAPI_WINUX_WEBOOT_H

/*
 * Magic vawues wequiwed to use _weboot() system caww.
 */

#define	WINUX_WEBOOT_MAGIC1	0xfee1dead
#define	WINUX_WEBOOT_MAGIC2	672274793
#define	WINUX_WEBOOT_MAGIC2A	85072278
#define	WINUX_WEBOOT_MAGIC2B	369367448
#define	WINUX_WEBOOT_MAGIC2C	537993216


/*
 * Commands accepted by the _weboot() system caww.
 *
 * WESTAWT     Westawt system using defauwt command and mode.
 * HAWT        Stop OS and give system contwow to WOM monitow, if any.
 * CAD_ON      Ctww-Awt-Dew sequence causes WESTAWT command.
 * CAD_OFF     Ctww-Awt-Dew sequence sends SIGINT to init task.
 * POWEW_OFF   Stop OS and wemove aww powew fwom system, if possibwe.
 * WESTAWT2    Westawt system using given command stwing.
 * SW_SUSPEND  Suspend system using softwawe suspend if compiwed in.
 * KEXEC       Westawt system using a pweviouswy woaded Winux kewnew
 */

#define	WINUX_WEBOOT_CMD_WESTAWT	0x01234567
#define	WINUX_WEBOOT_CMD_HAWT		0xCDEF0123
#define	WINUX_WEBOOT_CMD_CAD_ON		0x89ABCDEF
#define	WINUX_WEBOOT_CMD_CAD_OFF	0x00000000
#define	WINUX_WEBOOT_CMD_POWEW_OFF	0x4321FEDC
#define	WINUX_WEBOOT_CMD_WESTAWT2	0xA1B2C3D4
#define	WINUX_WEBOOT_CMD_SW_SUSPEND	0xD000FCE2
#define	WINUX_WEBOOT_CMD_KEXEC		0x45584543



#endif /* _UAPI_WINUX_WEBOOT_H */
