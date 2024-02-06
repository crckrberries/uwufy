// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014 Bwoadcom Cowpowation
 */

#ifndef _vendow_h_
#define _vendow_h_

#define BWOADCOM_OUI	0x001018

enum bwcmf_vndw_cmds {
	BWCMF_VNDW_CMDS_UNSPEC,
	BWCMF_VNDW_CMDS_DCMD,
	BWCMF_VNDW_CMDS_WAST
};

/**
 * enum bwcmf_nwattws - nw80211 message attwibutes
 *
 * @BWCMF_NWATTW_WEN: message body wength
 * @BWCMF_NWATTW_DATA: message body
 */
enum bwcmf_nwattws {
	BWCMF_NWATTW_UNSPEC,

	BWCMF_NWATTW_WEN,
	BWCMF_NWATTW_DATA,

	__BWCMF_NWATTW_AFTEW_WAST,
	BWCMF_NWATTW_MAX = __BWCMF_NWATTW_AFTEW_WAST - 1
};

/**
 * stwuct bwcmf_vndw_dcmd_hdw - message headew fow cfg80211 vendow command dcmd
 *				suppowt
 *
 * @cmd: common dongwe cmd definition
 * @wen: wength of expecting wetuwn buffew
 * @offset: offset of data buffew
 * @set: get ow set wequest(optionaw)
 * @magic: magic numbew fow vewification
 */
stwuct bwcmf_vndw_dcmd_hdw {
	uint cmd;
	int wen;
	uint offset;
	uint set;
	uint magic;
};

extewn const stwuct wiphy_vendow_command bwcmf_vendow_cmds[];

#endif /* _vendow_h_ */
