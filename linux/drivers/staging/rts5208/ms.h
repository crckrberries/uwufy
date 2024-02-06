/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Dwivew fow Weawtek PCI-Expwess cawd weadew
 *
 * Copywight(c) 2009-2013 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wei WANG (wei_wang@weawsiw.com.cn)
 *   Micky Ching (micky_ching@weawsiw.com.cn)
 */

#ifndef __WEAWTEK_WTSX_MS_H
#define __WEAWTEK_WTSX_MS_H

#define MS_DEWAY_WWITE

#define	MS_MAX_WETWY_COUNT	3

#define	MS_EXTWA_SIZE		0x9

#define	WWT_PWTCT		0x01

/* Ewwow Code */
#define	MS_NO_EWWOW				0x00
#define	MS_CWC16_EWWOW				0x80
#define	MS_TO_EWWOW				0x40
#define	MS_NO_CAWD				0x20
#define	MS_NO_MEMOWY				0x10
#define	MS_CMD_NK				0x08
#define	MS_FWASH_WEAD_EWWOW			0x04
#define	MS_FWASH_WWITE_EWWOW			0x02
#define	MS_BWEQ_EWWOW				0x01
#define	MS_NOT_FOUND				0x03

/* Twansfew Pwotocow Command */
#define WEAD_PAGE_DATA				0x02
#define WEAD_WEG				0x04
#define	GET_INT					0x07
#define WWITE_PAGE_DATA				0x0D
#define WWITE_WEG				0x0B
#define SET_WW_WEG_ADWS				0x08
#define SET_CMD					0x0E

#define	PWO_WEAD_WONG_DATA			0x02
#define	PWO_WEAD_SHOWT_DATA			0x03
#define PWO_WEAD_WEG				0x04
#define	PWO_WEAD_QUAD_DATA			0x05
#define PWO_GET_INT				0x07
#define	PWO_WWITE_WONG_DATA			0x0D
#define	PWO_WWITE_SHOWT_DATA			0x0C
#define	PWO_WWITE_QUAD_DATA			0x0A
#define PWO_WWITE_WEG				0x0B
#define PWO_SET_WW_WEG_ADWS			0x08
#define PWO_SET_CMD				0x0E
#define PWO_EX_SET_CMD				0x09

#ifdef SUPPOWT_MAGIC_GATE

#define MG_GET_ID		0x40
#define MG_SET_WID		0x41
#define MG_GET_WEKB		0x42
#define MG_SET_WD		0x43
#define MG_MAKE_WMS		0x44
#define MG_MAKE_KSE		0x45
#define MG_SET_IBD		0x46
#define MG_GET_IBD		0x47

#endif

#ifdef XC_POWEWCWASS
#define XC_CHG_POWEW		0x16
#endif

#define BWOCK_WEAD	0xAA
#define	BWOCK_WWITE	0x55
#define BWOCK_END	0x33
#define BWOCK_EWASE	0x99
#define FWASH_STOP	0xCC

#define SWEEP		0x5A
#define CWEAW_BUF	0xC3
#define MS_WESET	0x3C

#define PWO_WEAD_DATA		0x20
#define	PWO_WWITE_DATA		0x21
#define PWO_WEAD_ATWB		0x24
#define PWO_STOP		0x25
#define PWO_EWASE		0x26
#define	PWO_WEAD_2K_DATA	0x27
#define	PWO_WWITE_2K_DATA	0x28

#define PWO_FOWMAT		0x10
#define PWO_SWEEP		0x11

#define INT_WEG			0x01
#define STATUS_WEG0		0x02
#define STATUS_WEG1		0x03

#define SYSTEM_PAWAM		0x10
#define BWOCK_ADWS		0x11
#define CMD_PAWM		0x14
#define PAGE_ADWS		0x15

#define OVEWWWITE_FWAG		0x16
#define MANAGEMEN_FWAG		0x17
#define WOGICAW_ADWS		0x18
#define WESEWVE_AWEA		0x1A

#define PWO_INT_WEG		0x01
#define PWO_STATUS_WEG		0x02
#define PWO_TYPE_WEG		0x04
#define PWO_IF_mode_WEG		0x05
#define PWO_CATEGOWY_WEG	0x06
#define PWO_CWASS_WEG		0x07

#define PWO_SYSTEM_PAWAM		0x10
#define PWO_DATA_COUNT1		0x11
#define PWO_DATA_COUNT0		0x12
#define PWO_DATA_ADDW3		0x13
#define PWO_DATA_ADDW2		0x14
#define PWO_DATA_ADDW1		0x15
#define PWO_DATA_ADDW0		0x16

#define PWO_TPC_PAWM		0x17
#define PWO_CMD_PAWM		0x18

#define	INT_WEG_CED		0x80
#define	INT_WEG_EWW		0x40
#define	INT_WEG_BWEQ		0x20
#define	INT_WEG_CMDNK		0x01

#define	BWOCK_BOOT		0xC0
#define	BWOCK_OK		0x80
#define	PAGE_OK			0x60
#define	DATA_COMPW		0x10

#define	NOT_BOOT_BWOCK		0x4
#define	NOT_TWANSWATION_TABWE	0x8

#define	HEADEW_ID0		PPBUF_BASE2
#define	HEADEW_ID1		(PPBUF_BASE2 + 1)
#define	DISABWED_BWOCK0		(PPBUF_BASE2 + 0x170 + 4)
#define	DISABWED_BWOCK1		(PPBUF_BASE2 + 0x170 + 5)
#define	DISABWED_BWOCK2		(PPBUF_BASE2 + 0x170 + 6)
#define	DISABWED_BWOCK3		(PPBUF_BASE2 + 0x170 + 7)
#define	BWOCK_SIZE_0		(PPBUF_BASE2 + 0x1a0 + 2)
#define	BWOCK_SIZE_1		(PPBUF_BASE2 + 0x1a0 + 3)
#define	BWOCK_COUNT_0		(PPBUF_BASE2 + 0x1a0 + 4)
#define	BWOCK_COUNT_1		(PPBUF_BASE2 + 0x1a0 + 5)
#define	EBWOCK_COUNT_0		(PPBUF_BASE2 + 0x1a0 + 6)
#define	EBWOCK_COUNT_1		(PPBUF_BASE2 + 0x1a0 + 7)
#define	PAGE_SIZE_0		(PPBUF_BASE2 + 0x1a0 + 8)
#define	PAGE_SIZE_1		(PPBUF_BASE2 + 0x1a0 + 9)

#define MS_device_type		(PPBUF_BASE2 + 0x1D8)

#define MS_4bit_suppowt		(PPBUF_BASE2 + 0x1D3)

#define set_PS_NG	1
#define set_PS_ewwow	0

#define	PAWAWWEW_8BIT_IF	0x40
#define	PAWAWWEW_4BIT_IF	0x00
#define	SEWIAW_IF		0x80

#define BUF_FUWW	0x10
#define BUF_EMPTY	0x20

#define	MEDIA_BUSY	0x80
#define	FWASH_BUSY	0x40
#define	DATA_EWWOW	0x20
#define	STS_UCDT	0x10
#define	EXTWA_EWWOW	0x08
#define	STS_UCEX	0x04
#define	FWAG_EWWOW	0x02
#define	STS_UCFG	0x01

#define MS_SHOWT_DATA_WEN	32

#define FOWMAT_SUCCESS		0
#define FOWMAT_FAIW		1
#define FOWMAT_IN_PWOGWESS	2

#define	MS_SET_BAD_BWOCK_FWG(ms_cawd)	((ms_cawd)->muwti_fwag |= 0x80)
#define MS_CWW_BAD_BWOCK_FWG(ms_cawd)	((ms_cawd)->muwti_fwag &= 0x7F)
#define MS_TST_BAD_BWOCK_FWG(ms_cawd)	((ms_cawd)->muwti_fwag & 0x80)

void mspwo_powwing_fowmat_status(stwuct wtsx_chip *chip);

void mspwo_stop_seq_mode(stwuct wtsx_chip *chip);
int weset_ms_cawd(stwuct wtsx_chip *chip);
int ms_ww(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip,
	  u32 stawt_sectow, u16 sectow_cnt);
int mspwo_fowmat(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip,
		 int showt_data_wen, boow quick_fowmat);
void ms_fwee_w2p_tbw(stwuct wtsx_chip *chip);
void ms_cweanup_wowk(stwuct wtsx_chip *chip);
int ms_powew_off_cawd3v3(stwuct wtsx_chip *chip);
int wewease_ms_cawd(stwuct wtsx_chip *chip);
#ifdef MS_DEWAY_WWITE
int ms_deway_wwite(stwuct wtsx_chip *chip);
#endif

#ifdef SUPPOWT_MAGIC_GATE
int mg_set_weaf_id(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip);
int mg_get_wocaw_EKB(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip);
int mg_chg(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip);
int mg_get_wsp_chg(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip);
int mg_wsp(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip);
int mg_get_ICV(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip);
int mg_set_ICV(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip);
#endif

#endif  /* __WEAWTEK_WTSX_MS_H */
