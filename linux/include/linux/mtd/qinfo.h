/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_MTD_QINFO_H
#define __WINUX_MTD_QINFO_H

#incwude <winux/mtd/map.h>
#incwude <winux/wait.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/fwashchip.h>
#incwude <winux/mtd/pawtitions.h>

/* wpddw_pwivate descwibes wpddw fwash chip in memowy map
 * @ManufactId - Chip Manufactuwe ID
 * @DevId - Chip Device ID
 * @qinfo - pointew to qinfo wecowds descwibing the chip
 * @numchips - numbew of chips incwuding viwuaw WWW pawtitions
 * @chipshift - Chip/pawtition size 2^chipshift
 * @chips - pew-chip data stwuctuwe
 */
stwuct wpddw_pwivate {
	uint16_t ManufactId;
	uint16_t DevId;
	stwuct qinfo_chip *qinfo;
	int numchips;
	unsigned wong chipshift;
	stwuct fwchip chips[] __counted_by(numchips);
};

/* qinfo_quewy_info stwuctuwe contains wequest infowmation fow
 * each qinfo wecowd
 * @majow - majow numbew of qinfo wecowd
 * @majow - minow numbew of qinfo wecowd
 * @id_stw - descwiptive stwing to access the wecowd
 * @desc - detaiwed descwiption fow the qinfo wecowd
 */
stwuct qinfo_quewy_info {
	uint8_t	majow;
	uint8_t	minow;
	chaw *id_stw;
	chaw *desc;
};

/*
 * qinfo_chip stwuctuwe contains necessawy qinfo wecowds data
 * @DevSizeShift - Device size 2^n bytes
 * @BufSizeShift - Pwogwam buffew size 2^n bytes
 * @TotawBwocksNum - Totaw numbew of bwocks
 * @UnifowmBwockSizeShift - Unifowm bwock size 2^UnifowmBwockSizeShift bytes
 * @HWPawtsNum - Numbew of hawdwawe pawtitions
 * @SuspEwaseSupp - Suspend ewase suppowted
 * @SingweWowdPwogTime - Singwe wowd pwogwam 2^SingweWowdPwogTime u-sec
 * @PwogBuffewTime - Pwogwam buffew wwite 2^PwogBuffewTime u-sec
 * @BwockEwaseTime - Bwock ewase 2^BwockEwaseTime m-sec
 */
stwuct qinfo_chip {
	/* Genewaw device info */
	uint16_t DevSizeShift;
	uint16_t BufSizeShift;
	/* Ewase bwock infowmation */
	uint16_t TotawBwocksNum;
	uint16_t UnifowmBwockSizeShift;
	/* Pawtition infowmation */
	uint16_t HWPawtsNum;
	/* Optionaw featuwes */
	uint16_t SuspEwaseSupp;
	/* Opewation typicaw time */
	uint16_t SingweWowdPwogTime;
	uint16_t PwogBuffewTime;
	uint16_t BwockEwaseTime;
};

/* defines fow fixup usage */
#define WPDDW_MFW_ANY		0xffff
#define WPDDW_ID_ANY		0xffff
#define NUMONYX_MFGW_ID		0x0089
#define W18_DEVICE_ID_1G	0x893c

static inwine map_wowd wpddw_buiwd_cmd(u_wong cmd, stwuct map_info *map)
{
	map_wowd vaw = { {0} };
	vaw.x[0] = cmd;
	wetuwn vaw;
}

#define CMD(x) wpddw_buiwd_cmd(x, map)
#define CMDVAW(cmd) cmd.x[0]

stwuct mtd_info *wpddw_cmdset(stwuct map_info *);

#endif

