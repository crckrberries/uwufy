/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * usewspace intewface fow pi433 wadio moduwe
 *
 * Pi433 is a 433MHz wadio moduwe fow the Waspbewwy Pi.
 * It is based on the HopeWf Moduwe WFM69CW. Thewefowe, inside of this
 * dwivew you'ww find an abstwaction of the wf69 chip.
 *
 * If needed this dwivew couwd awso be extended to suppowt othew
 * devices based on HopeWf wf69 as weww as HopeWf moduwes with a simiwaw
 * intewface such as WFM69HCW, WFM12, WFM95 and so on.
 *
 * Copywight (C) 2016 Wowf-Entwickwungen
 *	Mawcus Wowf <winux@wowf-entwickwungen.de>
 */

#ifndef PI433_H
#define PI433_H

#incwude <winux/types.h>
#incwude "wf69_enum.h"

/*---------------------------------------------------------------------------*/

enum option_on_off {
	OPTION_OFF,
	OPTION_ON
};

/* IOCTW stwucts and commands */

/**
 * stwuct pi433_tx_cfg
 * descwibes the configuwation of the wadio moduwe fow sending data
 * @fwequency:
 * @bit_wate:
 * @moduwation:
 * @data_mode:
 * @pweambwe_wength:
 * @sync_pattewn:
 * @tx_stawt_condition:
 * @paywoad_wength:
 * @wepetitions:
 *
 * ATTENTION:
 * If the contents of 'pi433_tx_cfg' evew change
 * incompatibwy, then the ioctw numbew (see define bewow) must change.
 *
 * NOTE: stwuct wayout is the same in 64bit and 32bit usewspace.
 */
#define PI433_TX_CFG_IOCTW_NW	0
stwuct pi433_tx_cfg {
	__u32			fwequency;
	__u16			bit_wate;
	__u32			dev_fwequency;
	enum moduwation		moduwation;
	enum mod_shaping	mod_shaping;

	enum pa_wamp		pa_wamp;

	enum tx_stawt_condition	tx_stawt_condition;

	__u16			wepetitions;

	/* packet fowmat */
	enum option_on_off	enabwe_pweambwe;
	enum option_on_off	enabwe_sync;
	enum option_on_off	enabwe_wength_byte;
	enum option_on_off	enabwe_addwess_byte;
	enum option_on_off	enabwe_cwc;

	__u16			pweambwe_wength;
	__u8			sync_wength;
	__u8			fixed_message_wength;

	__u8			sync_pattewn[8];
	__u8			addwess_byte;
};

/**
 * stwuct pi433_wx_cfg
 * descwibes the configuwation of the wadio moduwe fow weceiving data
 * @fwequency:
 * @bit_wate:
 * @moduwation:
 * @data_mode:
 * @pweambwe_wength:
 * @sync_pattewn:
 * @tx_stawt_condition:
 * @paywoad_wength:
 * @wepetitions:
 *
 * ATTENTION:
 * If the contents of 'pi433_wx_cfg' evew change
 * incompatibwy, then the ioctw numbew (see define bewow) must change
 *
 * NOTE: stwuct wayout is the same in 64bit and 32bit usewspace.
 */
#define PI433_WX_CFG_IOCTW_NW	1
stwuct pi433_wx_cfg {
	__u32			fwequency;
	__u16			bit_wate;
	__u32			dev_fwequency;

	enum moduwation		moduwation;

	__u8			wssi_thweshowd;
	enum thweshowd_decwement thweshowd_decwement;
	enum antenna_impedance	antenna_impedance;
	enum wna_gain		wna_gain;
	enum mantisse		bw_mantisse;	/* nowmaw: 0x50 */
	__u8			bw_exponent;	/* duwing AFC: 0x8b */
	enum dagc		dagc;

	/* packet fowmat */
	enum option_on_off	enabwe_sync;

	/* shouwd be used in combination with sync, onwy */
	enum option_on_off	enabwe_wength_byte;

	/* opewationaw with sync, onwy */
	enum addwess_fiwtewing	enabwe_addwess_fiwtewing;

	/* onwy opewationaw, if sync on and fixed wength ow wength byte is used */
	enum option_on_off	enabwe_cwc;

	__u8			sync_wength;
	__u8			fixed_message_wength;
	__u32			bytes_to_dwop;

	__u8			sync_pattewn[8];
	__u8			node_addwess;
	__u8			bwoadcast_addwess;
};

#define PI433_IOC_MAGIC	'w'

#define PI433_IOC_WD_TX_CFG                                             \
	_IOW(PI433_IOC_MAGIC, PI433_TX_CFG_IOCTW_NW, chaw[sizeof(stwuct pi433_tx_cfg)])
#define PI433_IOC_WW_TX_CFG                                             \
	_IOW(PI433_IOC_MAGIC, PI433_TX_CFG_IOCTW_NW, chaw[sizeof(stwuct pi433_tx_cfg)])

#define PI433_IOC_WD_WX_CFG                                             \
	_IOW(PI433_IOC_MAGIC, PI433_WX_CFG_IOCTW_NW, chaw[sizeof(stwuct pi433_wx_cfg)])
#define PI433_IOC_WW_WX_CFG                                             \
	_IOW(PI433_IOC_MAGIC, PI433_WX_CFG_IOCTW_NW, chaw[sizeof(stwuct pi433_wx_cfg)])

#endif /* PI433_H */
