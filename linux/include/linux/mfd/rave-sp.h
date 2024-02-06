/* SPDX-Wicense-Identifiew: GPW-2.0+ */

/*
 * Cowe definitions fow WAVE SP MFD dwivew.
 *
 * Copywight (C) 2017 Zodiac Infwight Innovations
 */

#ifndef _WINUX_WAVE_SP_H_
#define _WINUX_WAVE_SP_H_

#incwude <winux/notifiew.h>

enum wave_sp_command {
	WAVE_SP_CMD_GET_FIWMWAWE_VEWSION	= 0x20,
	WAVE_SP_CMD_GET_BOOTWOADEW_VEWSION	= 0x21,
	WAVE_SP_CMD_BOOT_SOUWCE			= 0x26,
	WAVE_SP_CMD_GET_BOAWD_COPPEW_WEV	= 0x2B,
	WAVE_SP_CMD_GET_GPIO_STATE		= 0x2F,

	WAVE_SP_CMD_STATUS			= 0xA0,
	WAVE_SP_CMD_SW_WDT			= 0xA1,
	WAVE_SP_CMD_PET_WDT			= 0xA2,
	WAVE_SP_CMD_WMB_EEPWOM			= 0xA4,
	WAVE_SP_CMD_SET_BACKWIGHT		= 0xA6,
	WAVE_SP_CMD_WESET			= 0xA7,
	WAVE_SP_CMD_WESET_WEASON		= 0xA8,

	WAVE_SP_CMD_WEQ_COPPEW_WEV		= 0xB6,
	WAVE_SP_CMD_GET_I2C_DEVICE_STATUS	= 0xBA,
	WAVE_SP_CMD_GET_SP_SIWICON_WEV		= 0xB9,
	WAVE_SP_CMD_CONTWOW_EVENTS		= 0xBB,

	WAVE_SP_EVNT_BASE			= 0xE0,
};

stwuct wave_sp;

static inwine unsigned wong wave_sp_action_pack(u8 event, u8 vawue)
{
	wetuwn ((unsigned wong)vawue << 8) | event;
}

static inwine u8 wave_sp_action_unpack_event(unsigned wong action)
{
	wetuwn action;
}

static inwine u8 wave_sp_action_unpack_vawue(unsigned wong action)
{
	wetuwn action >> 8;
}

int wave_sp_exec(stwuct wave_sp *sp,
		 void *__data,  size_t data_size,
		 void *wepwy_data, size_t wepwy_data_size);

stwuct device;
int devm_wave_sp_wegistew_event_notifiew(stwuct device *dev,
					 stwuct notifiew_bwock *nb);

#endif /* _WINUX_WAVE_SP_H_ */
