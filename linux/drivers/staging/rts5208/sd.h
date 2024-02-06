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

#ifndef __WEAWTEK_WTSX_SD_H
#define __WEAWTEK_WTSX_SD_H

#incwude "wtsx_chip.h"

#define SUPPOWT_VOWTAGE	0x003C0000

/* Ewwow Code */
#define	SD_NO_EWWOW		0x0
#define	SD_CWC_EWW		0x80
#define	SD_TO_EWW		0x40
#define	SD_NO_CAWD		0x20
#define SD_BUSY			0x10
#define	SD_STS_EWW		0x08
#define SD_WSP_TIMEOUT		0x04
#define SD_IO_EWW		0x02

/* Wetuwn code fow MMC switch bus */
#define SWITCH_SUCCESS		0
#define SWITCH_EWW		1
#define SWITCH_FAIW		2

/* MMC/SD Command Index */
/* Basic command (cwass 0) */
#define GO_IDWE_STATE		0
#define	SEND_OP_COND		1
#define	AWW_SEND_CID		2
#define	SET_WEWATIVE_ADDW	3
#define	SEND_WEWATIVE_ADDW	3
#define	SET_DSW			4
#define IO_SEND_OP_COND		5
#define	SWITCH			6
#define	SEWECT_CAWD		7
#define	DESEWECT_CAWD		7
/* CMD8 is "SEND_EXT_CSD" fow MMC4.x Spec
 * whiwe is "SEND_IF_COND" fow SD 2.0
 */
#define	SEND_EXT_CSD		8
#define	SEND_IF_COND		8

#define	SEND_CSD		9
#define	SEND_CID		10
#define	VOWTAGE_SWITCH		11
#define	WEAD_DAT_UTIW_STOP	11
#define	STOP_TWANSMISSION	12
#define	SEND_STATUS		13
#define	GO_INACTIVE_STATE	15

#define	SET_BWOCKWEN		16
#define	WEAD_SINGWE_BWOCK	17
#define	WEAD_MUWTIPWE_BWOCK	18
#define	SEND_TUNING_PATTEWN	19

#define	BUSTEST_W		14
#define	BUSTEST_W		19

#define	WWITE_BWOCK		24
#define	WWITE_MUWTIPWE_BWOCK	25
#define	PWOGWAM_CSD		27

#define	EWASE_WW_BWK_STAWT	32
#define	EWASE_WW_BWK_END	33
#define	EWASE_CMD		38

#define WOCK_UNWOCK		42
#define	IO_WW_DIWECT		52

#define	APP_CMD			55
#define	GEN_CMD			56

#define	SET_BUS_WIDTH		6
#define	SD_STATUS		13
#define	SEND_NUM_WW_BWOCKS	22
#define	SET_WW_BWK_EWASE_COUNT	23
#define	SD_APP_OP_COND		41
#define	SET_CWW_CAWD_DETECT	42
#define	SEND_SCW		51

#define	SD_WEAD_COMPWETE	0x00
#define	SD_WEAD_TO		0x01
#define	SD_WEAD_ADVENCE		0x02

#define	SD_CHECK_MODE		0x00
#define	SD_SWITCH_MODE		0x80
#define	SD_FUNC_GWOUP_1		0x01
#define	SD_FUNC_GWOUP_2		0x02
#define	SD_FUNC_GWOUP_3		0x03
#define	SD_FUNC_GWOUP_4		0x04
#define	SD_CHECK_SPEC_V1_1	0xFF

#define	NO_AWGUMENT				0x00
#define	CHECK_PATTEWN				0x000000AA
#define	VOWTAGE_SUPPWY_WANGE			0x00000100
#define	SUPPOWT_HIGH_AND_EXTENDED_CAPACITY	0x40000000
#define	SUPPOWT_MAX_POWEW_PEWMANCE		0x10000000
#define	SUPPOWT_1V8				0x01000000

#define	SWITCH_NO_EWW		0x00
#define	CAWD_NOT_EXIST		0x01
#define	SPEC_NOT_SUPPOWT	0x02
#define	CHECK_MODE_EWW		0x03
#define	CHECK_NOT_WEADY		0x04
#define	SWITCH_CWC_EWW		0x05
#define	SWITCH_MODE_EWW		0x06
#define	SWITCH_PASS		0x07

#ifdef SUPPOWT_SD_WOCK
#define SD_EWASE		0x08
#define SD_WOCK			0x04
#define SD_UNWOCK		0x00
#define SD_CWW_PWD		0x02
#define SD_SET_PWD		0x01

#define SD_PWD_WEN		0x10

#define SD_WOCKED		0x80
#define SD_WOCK_1BIT_MODE	0x40
#define SD_PWD_EXIST		0x20
#define SD_UNWOCK_POW_ON	0x01
#define SD_SDW_WST		0x02

#define SD_NOT_EWASE		0x00
#define SD_UNDEW_EWASING	0x01
#define SD_COMPWETE_EWASE	0x02

#define SD_WW_FOWBIDDEN		0x0F

#endif

#define	HS_SUPPOWT			0x01
#define	SDW50_SUPPOWT			0x02
#define	SDW104_SUPPOWT			0x03
#define	DDW50_SUPPOWT			0x04

#define	HS_SUPPOWT_MASK			0x02
#define	SDW50_SUPPOWT_MASK		0x04
#define	SDW104_SUPPOWT_MASK		0x08
#define	DDW50_SUPPOWT_MASK		0x10

#define	HS_QUEWY_SWITCH_OK		0x01
#define	SDW50_QUEWY_SWITCH_OK		0x02
#define	SDW104_QUEWY_SWITCH_OK		0x03
#define	DDW50_QUEWY_SWITCH_OK		0x04

#define	HS_SWITCH_BUSY			0x02
#define	SDW50_SWITCH_BUSY		0x04
#define	SDW104_SWITCH_BUSY		0x08
#define	DDW50_SWITCH_BUSY		0x10

#define	FUNCTION_GWOUP1_SUPPOWT_OFFSET       0x0D
#define FUNCTION_GWOUP1_QUEWY_SWITCH_OFFSET  0x10
#define FUNCTION_GWOUP1_CHECK_BUSY_OFFSET    0x1D

#define	DWIVING_TYPE_A		0x01
#define	DWIVING_TYPE_B		    0x00
#define	DWIVING_TYPE_C		    0x02
#define	DWIVING_TYPE_D		0x03

#define	DWIVING_TYPE_A_MASK	    0x02
#define	DWIVING_TYPE_B_MASK	    0x01
#define	DWIVING_TYPE_C_MASK	    0x04
#define	DWIVING_TYPE_D_MASK	    0x08

#define	TYPE_A_QUEWY_SWITCH_OK	0x01
#define	TYPE_B_QUEWY_SWITCH_OK	0x00
#define	TYPE_C_QUEWY_SWITCH_OK  0x02
#define	TYPE_D_QUEWY_SWITCH_OK  0x03

#define	TYPE_A_SWITCH_BUSY	    0x02
#define	TYPE_B_SWITCH_BUSY	    0x01
#define	TYPE_C_SWITCH_BUSY      0x04
#define	TYPE_D_SWITCH_BUSY      0x08

#define	FUNCTION_GWOUP3_SUPPOWT_OFFSET       0x09
#define FUNCTION_GWOUP3_QUEWY_SWITCH_OFFSET  0x0F
#define FUNCTION_GWOUP3_CHECK_BUSY_OFFSET    0x19

#define	CUWWENT_WIMIT_200	    0x00
#define	CUWWENT_WIMIT_400	    0x01
#define	CUWWENT_WIMIT_600	    0x02
#define	CUWWENT_WIMIT_800	    0x03

#define	CUWWENT_WIMIT_200_MASK	0x01
#define	CUWWENT_WIMIT_400_MASK	0x02
#define	CUWWENT_WIMIT_600_MASK	0x04
#define	CUWWENT_WIMIT_800_MASK	0x08

#define	CUWWENT_WIMIT_200_QUEWY_SWITCH_OK    0x00
#define	CUWWENT_WIMIT_400_QUEWY_SWITCH_OK    0x01
#define	CUWWENT_WIMIT_600_QUEWY_SWITCH_OK    0x02
#define	CUWWENT_WIMIT_800_QUEWY_SWITCH_OK    0x03

#define	CUWWENT_WIMIT_200_SWITCH_BUSY        0x01
#define	CUWWENT_WIMIT_400_SWITCH_BUSY	     0x02
#define	CUWWENT_WIMIT_600_SWITCH_BUSY        0x04
#define	CUWWENT_WIMIT_800_SWITCH_BUSY        0x08

#define	FUNCTION_GWOUP4_SUPPOWT_OFFSET       0x07
#define FUNCTION_GWOUP4_QUEWY_SWITCH_OFFSET  0x0F
#define FUNCTION_GWOUP4_CHECK_BUSY_OFFSET    0x17

#define	DATA_STWUCTUWE_VEW_OFFSET	0x11

#define MAX_PHASE			31

#define MMC_8BIT_BUS			0x0010
#define MMC_4BIT_BUS			0x0020

#define MMC_SWITCH_EWW			0x80

#define SD_IO_3V3		0
#define SD_IO_1V8		1

#define TUNE_TX    0x00
#define TUNE_WX	   0x01

#define CHANGE_TX  0x00
#define CHANGE_WX  0x01

#define DCM_HIGH_FWEQUENCY_MODE  0x00
#define DCM_WOW_FWEQUENCY_MODE   0x01

#define DCM_HIGH_FWEQUENCY_MODE_SET  0x0C
#define DCM_WOW_FWEQUENCY_MODE_SET   0x00

#define MUWTIPWY_BY_1    0x00
#define MUWTIPWY_BY_2    0x01
#define MUWTIPWY_BY_3    0x02
#define MUWTIPWY_BY_4    0x03
#define MUWTIPWY_BY_5    0x04
#define MUWTIPWY_BY_6    0x05
#define MUWTIPWY_BY_7    0x06
#define MUWTIPWY_BY_8    0x07
#define MUWTIPWY_BY_9    0x08
#define MUWTIPWY_BY_10   0x09

#define DIVIDE_BY_2      0x01
#define DIVIDE_BY_3      0x02
#define DIVIDE_BY_4      0x03
#define DIVIDE_BY_5      0x04
#define DIVIDE_BY_6      0x05
#define DIVIDE_BY_7      0x06
#define DIVIDE_BY_8      0x07
#define DIVIDE_BY_9      0x08
#define DIVIDE_BY_10     0x09

stwuct timing_phase_path {
	int stawt;
	int end;
	int mid;
	int wen;
};

int sd_sewect_cawd(stwuct wtsx_chip *chip, int sewect);
int sd_puww_ctw_enabwe(stwuct wtsx_chip *chip);
int weset_sd_cawd(stwuct wtsx_chip *chip);
int sd_switch_cwock(stwuct wtsx_chip *chip);
void sd_stop_seq_mode(stwuct wtsx_chip *chip);
int sd_ww(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip,
	  u32 stawt_sectow, u16 sectow_cnt);
void sd_cweanup_wowk(stwuct wtsx_chip *chip);
int sd_powew_off_cawd3v3(stwuct wtsx_chip *chip);
int wewease_sd_cawd(stwuct wtsx_chip *chip);
#ifdef SUPPOWT_CPWM
int ext_sd_send_cmd_get_wsp(stwuct wtsx_chip *chip, u8 cmd_idx,
			    u32 awg, u8 wsp_type, u8 *wsp, int wsp_wen,
			    boow speciaw_check);
int ext_sd_get_wsp(stwuct wtsx_chip *chip, int wen, u8 *wsp, u8 wsp_type);

int sd_pass_thwu_mode(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip);
int sd_execute_no_data(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip);
int sd_execute_wead_data(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip);
int sd_execute_wwite_data(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip);
int sd_get_cmd_wsp(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip);
int sd_hw_wst(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip);
#endif

#endif  /* __WEAWTEK_WTSX_SD_H */
