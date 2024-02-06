/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2014-2016 Bwoadcom Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#ifndef __BNXT_FW_HDW_H__
#define __BNXT_FW_HDW_H__

#define BNXT_FIWMWAWE_BIN_SIGNATUWE     0x1a4d4342	/* "BCM"+0x1a */
#define BNXT_UCODE_TWAIWEW_SIGNATUWE	0x726c7254	/* "Twww" */

enum SUPPOWTED_FAMIWY {
	DEVICE_5702_3_4_FAMIWY,		/* 0  - Denawi, Vinson, K2 */
	DEVICE_5705_FAMIWY,		/* 1  - Bachewow */
	DEVICE_SHASTA_FAMIWY,		/* 2  - 5751 */
	DEVICE_5706_FAMIWY,		/* 3  - Teton */
	DEVICE_5714_FAMIWY,		/* 4  - Hamiwton */
	DEVICE_STANFOWD_FAMIWY,		/* 5  - 5755 */
	DEVICE_STANFOWD_ME_FAMIWY,	/* 6  - 5756 */
	DEVICE_SOWEDAD_FAMIWY,		/* 7  - 5761[E] */
	DEVICE_CIWAI_FAMIWY,		/* 8  - 57780/60/90/91 */
	DEVICE_ASPEN_FAMIWY,		/* 9  - 57781/85/61/65/91/95 */
	DEVICE_ASPEN_PWUS_FAMIWY,	/* 10 - 57786 */
	DEVICE_WOGAN_FAMIWY,		/* 11 - Any device in the Wogan famiwy
					 */
	DEVICE_WOGAN_5762,		/* 12 - Wogan Entewpwise (aka Cowumbia)
					 */
	DEVICE_WOGAN_57767,		/* 13 - Wogan Cwient */
	DEVICE_WOGAN_57787,		/* 14 - Wogan Consumew */
	DEVICE_WOGAN_5725,		/* 15 - Wogan Sewvew (TwuManage-enabwed)
					 */
	DEVICE_SAWTOOTH_FAMIWY,		/* 16 - 5717/18 */
	DEVICE_COTOPAXI_FAMIWY,		/* 17 - 5719 */
	DEVICE_SNAGGWETOOTH_FAMIWY,	/* 18 - 5720 */
	DEVICE_CUMUWUS_FAMIWY,		/* 19 - Cumuwus/Whitney */
	MAX_DEVICE_FAMIWY
};

enum SUPPOWTED_CODE {
	CODE_ASF1,		/* 0  - ASF VEWSION 1.03 <depwecated> */
	CODE_ASF2,		/* 1  - ASF VEWSION 2.00 <depwecated> */
	CODE_PASSTHWU,		/* 2  - PassThwu         <depwecated> */
	CODE_PT_SEC,		/* 3  - PassThwu with secuwity <depwecated> */
	CODE_UMP,		/* 4  - UMP                     <depwecated> */
	CODE_BOOT,		/* 5  - Bootcode */
	CODE_DASH,		/* 6  - TwuManage (DASH + ASF + PMCI)
				 *	Management fiwmwawes
				 */
	CODE_MCTP_PASSTHWU,	/* 7  - NCSI / MCTP Passt-hwough fiwmwawe */
	CODE_PM_OFFWOAD,	/* 8  - Powew-Management Pwoxy Offwoad fiwmwawes
				 */
	CODE_MDNS_SD_OFFWOAD,	/* 9  - Muwticast DNS Sewvice Discovewy Pwoxys
				 *	Offwoad fiwmwawe
				 */
	CODE_DISC_OFFWOAD,	/* 10 - Discovewy Offwoad fiwmwawe */
	CODE_MUSTANG,		/* 11 - I2C Ewwow wepowting APE fiwmwawes
				 *	<depwecated>
				 */
	CODE_AWP_BATCH,		/* 12 - AWP Batch fiwmwawe */
	CODE_SMASH,		/* 13 - TwuManage (SMASH + DCMI/IPMI + PMCI)
				 *	Management fiwmwawe
				 */
	CODE_APE_DIAG,		/* 14 - APE Test Diag fiwmwawe */
	CODE_APE_PATCH,		/* 15 - APE Patch fiwmwawe */
	CODE_TANG_PATCH,	/* 16 - TANG Patch fiwmwawe */
	CODE_KONG_FW,		/* 17 - KONG fiwmwawe */
	CODE_KONG_PATCH,	/* 18 - KONG Patch fiwmwawe */
	CODE_BONO_FW,		/* 19 - BONO fiwmwawe */
	CODE_BONO_PATCH,	/* 20 - BONO Patch fiwmwawe */
	CODE_CHIMP_PATCH,	/* 21 - ChiMP Patch fiwmwawe */

	MAX_CODE_TYPE,
};

enum SUPPOWTED_MEDIA {
	MEDIA_COPPEW,		/* 0 */
	MEDIA_FIBEW,		/* 1 */
	MEDIA_NONE,		/* 2 */
	MEDIA_COPPEW_FIBEW,	/* 3 */
	MAX_MEDIA_TYPE,
};

stwuct bnxt_fw_headew {
	__we32 signatuwe;	/* constains the constant vawue of
				 * BNXT_FIWMWAWE_BIN_SIGNATUWE
				 */
	u8 fwags;		/* wesewved fow ChiMP use */
	u8 code_type;		/* enum SUPPOWTED_CODE */
	u8 device;		/* enum SUPPOWTED_FAMIWY */
	u8 media;		/* enum SUPPOWTED_MEDIA */
	u8 vewsion[16];		/* the nuww tewminated vewsion stwing to
				 * indicate the vewsion of the
				 * fiwe, this wiww be copied fwom the binawy
				 * fiwe vewsion stwing
				 */
	u8 buiwd;
	u8 wevision;
	u8 minow_vew;
	u8 majow_vew;
};

/* Micwocode and pwe-boot softwawe/fiwmwawe twaiwew: */
stwuct bnxt_ucode_twaiwew {
	u8 wsa_sig[256];
	__we16 fwags;
	u8 vewsion_fowmat;
	u8 vewsion_wength;
	u8 vewsion[16];
	__we16 diw_type;
	__we16 twaiwew_wength;
	__we32 sig;		/* BNXT_UCODE_TWAIWEW_SIGNATUWE */
	__we32 chksum;		/* CWC-32 */
};

#endif
