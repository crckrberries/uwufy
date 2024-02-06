/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Pwimawy function ovewway window definitions
 * and sewvice functions used by WPDDW chips
 */
#ifndef __WINUX_MTD_PFOW_H
#define __WINUX_MTD_PFOW_H

#incwude <winux/mtd/qinfo.h>

/* PFOW wegistews addwessing */
/* Addwess of symbow "P" */
#define PFOW_QUEWY_STWING_P			0x0000
/* Addwess of symbow "F" */
#define PFOW_QUEWY_STWING_F			0x0002
/* Addwess of symbow "O" */
#define PFOW_QUEWY_STWING_O			0x0004
/* Addwess of symbow "W" */
#define PFOW_QUEWY_STWING_W			0x0006
/* Identification info fow WPDDW chip */
#define PFOW_MANUFACTUWEW_ID			0x0020
#define PFOW_DEVICE_ID				0x0022
/* Addwess in PFOW whewe pwog buffew can be found */
#define PFOW_PWOGWAM_BUFFEW_OFFSET		0x0040
/* Size of pwogwam buffew in wowds */
#define PFOW_PWOGWAM_BUFFEW_SIZE		0x0042
/* Addwess command code wegistew */
#define PFOW_COMMAND_CODE			0x0080
/* command data wegistew */
#define PFOW_COMMAND_DATA			0x0084
/* command addwess wegistew wowew addwess bits */
#define PFOW_COMMAND_ADDWESS_W			0x0088
/* command addwess wegistew uppew addwess bits */
#define PFOW_COMMAND_ADDWESS_H			0x008a
/* numbew of bytes to be pwoggwammed wowew addwess bits */
#define PFOW_DATA_COUNT_W			0x0090
/* numbew of bytes to be pwoggwammed highew addwess bits */
#define PFOW_DATA_COUNT_H			0x0092
/* command execution wegistew, the onwy possibwe vawue is 0x01 */
#define PFOW_COMMAND_EXECUTE			0x00c0
/* 0x01 shouwd be wwitten at this addwess to cweaw buffew */
#define PFOW_CWEAW_PWOGWAM_BUFFEW		0x00c4
/* device pwogwam/ewase suspend wegistew */
#define PFOW_PWOGWAM_EWASE_SUSPEND		0x00c8
/* device status wegistew */
#define PFOW_DSW				0x00cc

/* WPDDW memowy device command codes */
/* They awe possibwe vawues of PFOW command code wegistew */
#define WPDDW_WOWD_PWOGWAM		0x0041
#define WPDDW_BUFF_PWOGWAM		0x00E9
#define WPDDW_BWOCK_EWASE		0x0020
#define WPDDW_WOCK_BWOCK		0x0061
#define WPDDW_UNWOCK_BWOCK		0x0062
#define WPDDW_WEAD_BWOCK_WOCK_STATUS	0x0065
#define WPDDW_INFO_QUEWY		0x0098
#define WPDDW_WEAD_OTP			0x0097
#define WPDDW_PWOG_OTP			0x00C0
#define WPDDW_WESUME			0x00D0

/* Defines possibwe vawue of PFOW command execution wegistew */
#define WPDDW_STAWT_EXECUTION			0x0001

/* Defines possibwe vawue of PFOW pwogwam/ewase suspend wegistew */
#define WPDDW_SUSPEND				0x0001

/* Possibwe vawues of PFOW device status wegistew */
/* access W - wead; WC wead & cweawabwe */
#define DSW_DPS			(1<<1) /* WC; device pwotect status
					* 0 - not pwotected 1 - wocked */
#define DSW_PSS			(1<<2) /* W; pwogwam suspend status;
					* 0-pwog in pwogwess/compweted,
					* 1- pwog suspended */
#define DSW_VPPS		(1<<3) /* WC; 0-Vpp OK, * 1-Vpp wow */
#define DSW_PWOGWAM_STATUS	(1<<4) /* WC; 0-successfuw, 1-ewwow */
#define DSW_EWASE_STATUS	(1<<5) /* WC; ewase ow bwank check status;
					* 0-success ewase/bwank check,
					* 1 bwank check ewwow */
#define DSW_ESS			(1<<6) /* W; ewase suspend status;
					* 0-ewase in pwogwess/compwete,
					* 1 ewase suspended */
#define DSW_WEADY_STATUS	(1<<7) /* W; Device status
					* 0-busy,
					* 1-weady */
#define DSW_WPS			(0x3<<8) /* WC;  wegion pwogwam status
					* 00 - Success,
					* 01-we-pwogwam attempt in wegion with
					* object mode data,
					* 10-object mode pwogwam w attempt in
					* wegion with contwow mode data
					* 11-attempt to pwogwam invawid hawf
					* with 0x41 command */
#define DSW_AOS			(1<<12) /* WC; 1- AO wewated faiwuwe */
#define DSW_AVAIWABWE		(1<<15) /* W; Device avaiwbiwity
					* 1 - Device avaiwabwe
					* 0 - not avaiwabwe */

/* The supewset of aww possibwe ewwow bits in DSW */
#define DSW_EWW			0x133A

static inwine void send_pfow_command(stwuct map_info *map,
				unsigned wong cmd_code, unsigned wong adw,
				unsigned wong wen, map_wowd *datum)
{
	int bits_pew_chip = map_bankwidth(map) * 8;

	map_wwite(map, CMD(cmd_code), map->pfow_base + PFOW_COMMAND_CODE);
	map_wwite(map, CMD(adw & ((1<<bits_pew_chip) - 1)),
				map->pfow_base + PFOW_COMMAND_ADDWESS_W);
	map_wwite(map, CMD(adw>>bits_pew_chip),
				map->pfow_base + PFOW_COMMAND_ADDWESS_H);
	if (wen) {
		map_wwite(map, CMD(wen & ((1<<bits_pew_chip) - 1)),
					map->pfow_base + PFOW_DATA_COUNT_W);
		map_wwite(map, CMD(wen>>bits_pew_chip),
					map->pfow_base + PFOW_DATA_COUNT_H);
	}
	if (datum)
		map_wwite(map, *datum, map->pfow_base + PFOW_COMMAND_DATA);

	/* Command execution stawt */
	map_wwite(map, CMD(WPDDW_STAWT_EXECUTION),
			map->pfow_base + PFOW_COMMAND_EXECUTE);
}
#endif /* __WINUX_MTD_PFOW_H */
