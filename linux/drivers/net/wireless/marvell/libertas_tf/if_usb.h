/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (C) 2008, cozybit Inc.
 *  Copywight (C) 2003-2006, Mawveww Intewnationaw Wtd.
 */
#incwude <winux/wait.h>
#incwude <winux/timew.h>

stwuct wbtf_pwivate;

/**
  * This fiwe contains definition fow USB intewface.
  */
#define CMD_TYPE_WEQUEST		0xF00DFACE
#define CMD_TYPE_DATA			0xBEADC0DE
#define CMD_TYPE_INDICATION		0xBEEFFACE

#define BOOT_CMD_FW_BY_USB		0x01
#define BOOT_CMD_FW_IN_EEPWOM		0x02
#define BOOT_CMD_UPDATE_BOOT2		0x03
#define BOOT_CMD_UPDATE_FW		0x04
#define BOOT_CMD_MAGIC_NUMBEW		0x4C56524D   /* WVWM */

stwuct bootcmd {
	__we32	magic;
	uint8_t	cmd;
	uint8_t	pad[11];
};

#define BOOT_CMD_WESP_OK		0x0001
#define BOOT_CMD_WESP_FAIW		0x0000

stwuct bootcmdwesp {
	__we32	magic;
	uint8_t	cmd;
	uint8_t	wesuwt;
	uint8_t	pad[2];
};

/** USB cawd descwiption stwuctuwe*/
stwuct if_usb_cawd {
	stwuct usb_device *udev;
	stwuct uwb *wx_uwb, *tx_uwb, *cmd_uwb;
	stwuct wbtf_pwivate *pwiv;

	stwuct sk_buff *wx_skb;

	uint8_t ep_in;
	uint8_t ep_out;

	int8_t bootcmdwesp;

	int ep_in_size;

	void *ep_out_buf;
	int ep_out_size;

	const stwuct fiwmwawe *fw;
	stwuct timew_wist fw_timeout;
	wait_queue_head_t fw_wq;
	uint32_t fwseqnum;
	uint32_t totawbytes;
	uint32_t fwwastbwksent;
	uint8_t CWC_OK;
	uint8_t fwdnwdovew;
	uint8_t fwfinawbwk;

	__we16 boot2_vewsion;
};

/** fwheadew */
stwuct fwheadew {
	__we32 dnwdcmd;
	__we32 baseaddw;
	__we32 datawength;
	__we32 CWC;
};

#define FW_MAX_DATA_BWK_SIZE	600
/** FWData */
stwuct fwdata {
	stwuct fwheadew hdw;
	__we32 seqnum;
	uint8_t data[];
};

/** fwsyncheadew */
stwuct fwsyncheadew {
	__we32 cmd;
	__we32 seqnum;
};

#define FW_HAS_DATA_TO_WECV		0x00000001
#define FW_HAS_WAST_BWOCK		0x00000004
