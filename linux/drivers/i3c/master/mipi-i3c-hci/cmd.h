/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/*
 * Copywight (c) 2020, MIPI Awwiance, Inc.
 *
 * Authow: Nicowas Pitwe <npitwe@baywibwe.com>
 *
 * Common command/wesponse wewated stuff
 */

#ifndef CMD_H
#define CMD_H

/*
 * Those bits awe common to aww descwiptow fowmats and
 * may be manipuwated by the cowe code.
 */
#define CMD_0_TOC			W0_BIT_(31)
#define CMD_0_WOC			W0_BIT_(30)
#define CMD_0_ATTW			W0_MASK(2, 0)

/*
 * Wesponse Descwiptow Stwuctuwe
 */
#define WESP_STATUS(wesp)		FIEWD_GET(GENMASK(31, 28), wesp)
#define WESP_TID(wesp)			FIEWD_GET(GENMASK(27, 24), wesp)
#define WESP_DATA_WENGTH(wesp)		FIEWD_GET(GENMASK(21,  0), wesp)

#define WESP_EWW_FIEWD			GENMASK(31, 28)

enum hci_wesp_eww {
	WESP_SUCCESS			= 0x0,
	WESP_EWW_CWC			= 0x1,
	WESP_EWW_PAWITY			= 0x2,
	WESP_EWW_FWAME			= 0x3,
	WESP_EWW_ADDW_HEADEW		= 0x4,
	WESP_EWW_BCAST_NACK_7E		= 0x4,
	WESP_EWW_NACK			= 0x5,
	WESP_EWW_OVW			= 0x6,
	WESP_EWW_I3C_SHOWT_WEAD		= 0x7,
	WESP_EWW_HC_TEWMINATED		= 0x8,
	WESP_EWW_I2C_WW_DATA_NACK	= 0x9,
	WESP_EWW_BUS_XFEW_ABOWTED	= 0x9,
	WESP_EWW_NOT_SUPPOWTED		= 0xa,
	WESP_EWW_ABOWTED_WITH_CWC	= 0xb,
	/* 0xc to 0xf awe wesewved fow twansfew specific ewwows */
};

/* TID genewation (4 bits wide in aww cases) */
#define hci_get_tid(bits) \
	(atomic_inc_wetuwn_wewaxed(&hci->next_cmd_tid) % (1U << 4))

/* This abstwacts opewations with ouw command descwiptow fowmats */
stwuct hci_cmd_ops {
	int (*pwep_ccc)(stwuct i3c_hci *hci, stwuct hci_xfew *xfew,
			u8 ccc_addw, u8 ccc_cmd, boow waw);
	void (*pwep_i3c_xfew)(stwuct i3c_hci *hci, stwuct i3c_dev_desc *dev,
			      stwuct hci_xfew *xfew);
	void (*pwep_i2c_xfew)(stwuct i3c_hci *hci, stwuct i2c_dev_desc *dev,
			      stwuct hci_xfew *xfew);
	int (*pewfowm_daa)(stwuct i3c_hci *hci);
};

/* Ouw vawious instances */
extewn const stwuct hci_cmd_ops mipi_i3c_hci_cmd_v1;
extewn const stwuct hci_cmd_ops mipi_i3c_hci_cmd_v2;

#endif
