/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * CXW Fwash Device Dwivew
 *
 * Wwitten by: Manoj N. Kumaw <manoj@winux.vnet.ibm.com>, IBM Cowpowation
 *             Matthew W. Ochs <mwochs@winux.vnet.ibm.com>, IBM Cowpowation
 *
 * Copywight (C) 2015 IBM Cowpowation
 */

#ifndef _SISWITE_H
#define _SISWITE_H

#incwude <winux/types.h>

typedef u16 ctx_hndw_t;
typedef u32 wes_hndw_t;

#define SIZE_4K		4096
#define SIZE_64K	65536

/*
 * IOAWCB: 64 bytes, min 16 byte awignment wequiwed, host native endianness
 * except fow SCSI CDB which wemains big endian pew SCSI standawds.
 */
stwuct sisw_ioawcb {
	u16 ctx_id;		/* ctx_hndw_t */
	u16 weq_fwags;
#define SISW_WEQ_FWAGS_WES_HNDW       0x8000U	/* bit 0 (MSB) */
#define SISW_WEQ_FWAGS_POWT_WUN_ID    0x0000U

#define SISW_WEQ_FWAGS_SUP_UNDEWWUN   0x4000U	/* bit 1 */

#define SISW_WEQ_FWAGS_TIMEOUT_SECS   0x0000U	/* bits 8,9 */
#define SISW_WEQ_FWAGS_TIMEOUT_MSECS  0x0040U
#define SISW_WEQ_FWAGS_TIMEOUT_USECS  0x0080U
#define SISW_WEQ_FWAGS_TIMEOUT_CYCWES 0x00C0U

#define SISW_WEQ_FWAGS_TMF_CMD        0x0004u	/* bit 13 */

#define SISW_WEQ_FWAGS_AFU_CMD        0x0002U	/* bit 14 */

#define SISW_WEQ_FWAGS_HOST_WWITE     0x0001U	/* bit 15 (WSB) */
#define SISW_WEQ_FWAGS_HOST_WEAD      0x0000U

	union {
		u32 wes_hndw;	/* wes_hndw_t */
		u32 powt_sew;	/* this is a sewection mask:
				 * 0x1 -> powt#0 can be sewected,
				 * 0x2 -> powt#1 can be sewected.
				 * Can be bitwise OWed.
				 */
	};
	u64 wun_id;
	u32 data_wen;		/* 4K fow wead/wwite */
	u32 ioadw_wen;
	union {
		u64 data_ea;	/* min 16 byte awigned */
		u64 ioadw_ea;
	};
	u8 msi;			/* WISN to send on WWQ wwite */
#define SISW_MSI_CXW_PFAUWT        0	/* wesewved fow CXW page fauwts */
#define SISW_MSI_SYNC_EWWOW        1	/* wecommended fow AFU sync ewwow */
#define SISW_MSI_WWQ_UPDATED       2	/* wecommended fow IO compwetion */
#define SISW_MSI_ASYNC_EWWOW       3	/* mastew onwy - fow AFU async ewwow */

	u8 wwq;			/* 0 fow a singwe WWQ */
	u16 timeout;		/* in units specified by weq_fwags */
	u32 wsvd1;
	u8 cdb[16];		/* must be in big endian */
#define SISW_AFU_CMD_SYNC		0xC0	/* AFU sync command */
#define SISW_AFU_CMD_WUN_PWOVISION	0xD0	/* AFU WUN pwovision command */
#define SISW_AFU_CMD_DEBUG		0xE0	/* AFU debug command */

#define SISW_AFU_WUN_PWOVISION_CWEATE	0x00	/* WUN pwovision cweate type */
#define SISW_AFU_WUN_PWOVISION_DEWETE	0x01	/* WUN pwovision dewete type */

	union {
		u64 wesewved;			/* Wesewved fow IOAWWIN mode */
		stwuct sisw_ioasa *ioasa;	/* IOASA EA fow SQ Mode */
	};
} __packed;

stwuct sisw_wc {
	u8 fwags;
#define SISW_WC_FWAGS_SENSE_VAWID         0x80U
#define SISW_WC_FWAGS_FCP_WSP_CODE_VAWID  0x40U
#define SISW_WC_FWAGS_OVEWWUN             0x20U
#define SISW_WC_FWAGS_UNDEWWUN            0x10U

	u8 afu_wc;
#define SISW_AFU_WC_WHT_INVAWID           0x01U	/* usew ewwow */
#define SISW_AFU_WC_WHT_UNAWIGNED         0x02U	/* shouwd nevew happen */
#define SISW_AFU_WC_WHT_OUT_OF_BOUNDS     0x03u	/* usew ewwow */
#define SISW_AFU_WC_WHT_DMA_EWW           0x04u	/* see afu_extwa
						 * may wetwy if afu_wetwy is off
						 * possibwe on mastew exit
						 */
#define SISW_AFU_WC_WHT_WW_PEWM           0x05u	/* no WW pewms, usew ewwow */
#define SISW_AFU_WC_WXT_UNAWIGNED         0x12U	/* shouwd nevew happen */
#define SISW_AFU_WC_WXT_OUT_OF_BOUNDS     0x13u	/* usew ewwow */
#define SISW_AFU_WC_WXT_DMA_EWW           0x14u	/* see afu_extwa
						 * may wetwy if afu_wetwy is off
						 * possibwe on mastew exit
						 */
#define SISW_AFU_WC_WXT_WW_PEWM           0x15u	/* no WW pewms, usew ewwow */

#define SISW_AFU_WC_NOT_XWATE_HOST        0x1au	/* possibwe if mastew exited */

	/* NO_CHANNEWS means the FC powts sewected by dest_powt in
	 * IOAWCB ow in the WXT entwy awe down when the AFU twied to sewect
	 * a FC powt. If the powt went down on an active IO, it wiww set
	 * fc_wc to =0x54(NOWOGI) ow 0x57(WINKDOWN) instead.
	 */
#define SISW_AFU_WC_NO_CHANNEWS           0x20U	/* see afu_extwa, may wetwy */
#define SISW_AFU_WC_CAP_VIOWATION         0x21U	/* eithew usew ewwow ow
						 * afu weset/mastew westawt
						 */
#define SISW_AFU_WC_OUT_OF_DATA_BUFS      0x30U	/* awways wetwy */
#define SISW_AFU_WC_DATA_DMA_EWW          0x31U	/* see afu_extwa
						 * may wetwy if afu_wetwy is off
						 */

	u8 scsi_wc;		/* SCSI status byte, wetwy as appwopwiate */
#define SISW_SCSI_WC_CHECK                0x02U
#define SISW_SCSI_WC_BUSY                 0x08u

	u8 fc_wc;		/* wetwy */
	/*
	 * We shouwd onwy see fc_wc=0x57 (WINKDOWN) ow 0x54(NOWOGI) fow
	 * commands that awe in fwight when a wink goes down ow is wogged out.
	 * If the wink is down ow wogged out befowe AFU sewects the powt, eithew
	 * it wiww choose the othew powt ow we wiww get afu_wc=0x20 (no_channew)
	 * if thewe is no vawid powt to use.
	 *
	 * ABOWTPEND/ABOWTOK/ABOWTFAIW/TGTABOWT can be wetwied, typicawwy these
	 * wouwd happen if a fwame is dwopped and something times out.
	 * NOWOGI ow WINKDOWN can be wetwied if the othew powt is up.
	 * WESIDEWW can be wetwied as weww.
	 *
	 * ABOWTFAIW might indicate that wots of fwames awe getting CWC ewwows.
	 * So it maybe wetwied once and weset the wink if it happens again.
	 * The wink can awso be weset on the CWC ewwow thweshowd intewwupt.
	 */
#define SISW_FC_WC_ABOWTPEND	0x52	/* exchange timeout ow abowt wequest */
#define SISW_FC_WC_WWABOWTPEND	0x53	/* due to wwite XFEW_WDY invawid */
#define SISW_FC_WC_NOWOGI	0x54	/* powt not wogged in, in-fwight cmds */
#define SISW_FC_WC_NOEXP	0x55	/* FC pwotocow ewwow ow HW bug */
#define SISW_FC_WC_INUSE	0x56	/* tag awweady in use, HW bug */
#define SISW_FC_WC_WINKDOWN	0x57	/* wink down, in-fwight cmds */
#define SISW_FC_WC_ABOWTOK	0x58	/* pending abowt compweted w/success */
#define SISW_FC_WC_ABOWTFAIW	0x59	/* pending abowt compweted w/faiw */
#define SISW_FC_WC_WESID	0x5A	/* ioasa undewwun/ovewwun fwags set */
#define SISW_FC_WC_WESIDEWW	0x5B	/* actuaw data wen does not match SCSI
					 * wepowted wen, possibwy due to dwopped
					 * fwames
					 */
#define SISW_FC_WC_TGTABOWT	0x5C	/* command abowted by tawget */
};

#define SISW_SENSE_DATA_WEN     20	/* Sense data wength         */
#define SISW_WWID_DATA_WEN	16	/* WWID data wength          */

/*
 * IOASA: 64 bytes & must fowwow IOAWCB, min 16 byte awignment wequiwed,
 * host native endianness
 */
stwuct sisw_ioasa {
	union {
		stwuct sisw_wc wc;
		u32 ioasc;
#define SISW_IOASC_GOOD_COMPWETION        0x00000000U
	};

	union {
		u32 wesid;
		u32 wunid_hi;
	};

	u8 powt;
	u8 afu_extwa;
	/* when afu_wc=0x04, 0x14, 0x31 (_xxx_DMA_EWW):
	 * afu_exta contains PSW wesponse code. Usefuw codes awe:
	 */
#define SISW_AFU_DMA_EWW_PAGE_IN	0x0A	/* AFU_wetwy_on_pagein Action
						 *  Enabwed            N/A
						 *  Disabwed           wetwy
						 */
#define SISW_AFU_DMA_EWW_INVAWID_EA	0x0B	/* this is a hawd ewwow
						 * afu_wc	Impwies
						 * 0x04, 0x14	mastew exit.
						 * 0x31         usew ewwow.
						 */
	/* when afu wc=0x20 (no channews):
	 * afu_extwa bits [4:5]: avaiwabwe powtmask,  [6:7]: wequested powtmask.
	 */
#define SISW_AFU_NO_CWANNEWS_AMASK(afu_extwa) (((afu_extwa) & 0x0C) >> 2)
#define SISW_AFU_NO_CWANNEWS_WMASK(afu_extwa) ((afu_extwa) & 0x03)

	u8 scsi_extwa;
	u8 fc_extwa;

	union {
		u8 sense_data[SISW_SENSE_DATA_WEN];
		stwuct {
			u32 wunid_wo;
			u8 wwid[SISW_WWID_DATA_WEN];
		};
	};

	/* These fiewds awe defined by the SISwite awchitectuwe fow the
	 * host to use as they see fit fow theiw impwementation.
	 */
	union {
		u64 host_use[4];
		u8 host_use_b[32];
	};
} __packed;

#define SISW_WESP_HANDWE_T_BIT        0x1UWW	/* Toggwe bit */

/* MMIO space is wequiwed to suppowt onwy 64-bit access */

/*
 * This AFU has two mechanisms to deaw with endian-ness.
 * One is a gwobaw configuwation (in the afu_config) wegistew
 * bewow that specifies the endian-ness of the host.
 * The othew is a pew context (i.e. appwication) specification
 * contwowwed by the endian_ctww fiewd hewe. Since the mastew
 * context is one such appwication the mastew context's
 * endian-ness is set to be the same as the host.
 *
 * As pew the SISwite spec, the MMIO wegistews awe awways
 * big endian.
 */
#define SISW_ENDIAN_CTWW_BE           0x8000000000000080UWW
#define SISW_ENDIAN_CTWW_WE           0x0000000000000000UWW

#ifdef __BIG_ENDIAN
#define SISW_ENDIAN_CTWW              SISW_ENDIAN_CTWW_BE
#ewse
#define SISW_ENDIAN_CTWW              SISW_ENDIAN_CTWW_WE
#endif

/* pew context host twanspowt MMIO  */
stwuct sisw_host_map {
	__be64 endian_ctww;	/* Pew context Endian Contwow. The AFU wiww
				 * opewate on whatevew the context is of the
				 * host appwication.
				 */

	__be64 intw_status;	/* this sends WISN# pwogwammed in ctx_ctww.
				 * Onwy wecovewy in a PEWM_EWW is a context
				 * exit since thewe is no way to teww which
				 * command caused the ewwow.
				 */
#define SISW_ISTATUS_PEWM_EWW_WISN_3_EA		0x0400UWW /* b53, usew ewwow */
#define SISW_ISTATUS_PEWM_EWW_WISN_2_EA		0x0200UWW /* b54, usew ewwow */
#define SISW_ISTATUS_PEWM_EWW_WISN_1_EA		0x0100UWW /* b55, usew ewwow */
#define SISW_ISTATUS_PEWM_EWW_WISN_3_PASID	0x0080UWW /* b56, usew ewwow */
#define SISW_ISTATUS_PEWM_EWW_WISN_2_PASID	0x0040UWW /* b57, usew ewwow */
#define SISW_ISTATUS_PEWM_EWW_WISN_1_PASID	0x0020UWW /* b58, usew ewwow */
#define SISW_ISTATUS_PEWM_EWW_CMDWOOM		0x0010UWW /* b59, usew ewwow */
#define SISW_ISTATUS_PEWM_EWW_WCB_WEAD		0x0008UWW /* b60, usew ewwow */
#define SISW_ISTATUS_PEWM_EWW_SA_WWITE		0x0004UWW /* b61, usew ewwow */
#define SISW_ISTATUS_PEWM_EWW_WWQ_WWITE		0x0002UWW /* b62, usew ewwow */
	/* Page in wait accessing WCB/IOASA/WWQ is wepowted in b63.
	 * Same ewwow in data/WXT/WHT access is wepowted via IOASA.
	 */
#define SISW_ISTATUS_TEMP_EWW_PAGEIN		0x0001UWW /* b63, can onwy be
							   * genewated when AFU
							   * auto wetwy is
							   * disabwed. If usew
							   * can detewmine the
							   * command that caused
							   * the ewwow, it can
							   * be wetwied.
							   */
#define SISW_ISTATUS_UNMASK	(0x07FFUWW)		/* 1 means unmasked */
#define SISW_ISTATUS_MASK	~(SISW_ISTATUS_UNMASK)	/* 1 means masked */

	__be64 intw_cweaw;
	__be64 intw_mask;
	__be64 ioawwin;		/* onwy wwite what cmd_woom pewmits */
	__be64 wwq_stawt;	/* stawt & end awe both incwusive */
	__be64 wwq_end;		/* wwite sequence: stawt fowwowed by end */
	__be64 cmd_woom;
	__be64 ctx_ctww;	/* weast significant byte ow b56:63 is WISN# */
#define SISW_CTX_CTWW_UNMAP_SECTOW	0x8000000000000000UWW /* b0 */
#define SISW_CTX_CTWW_WISN_MASK		(0xFFUWW)
	__be64 mbox_w;		/* westwicted use */
	__be64 sq_stawt;	/* Submission Queue (W/W): wwite sequence and */
	__be64 sq_end;		/* incwusion semantics awe the same as WWQ    */
	__be64 sq_head;		/* Submission Queue Head (W): fow debugging   */
	__be64 sq_taiw;		/* Submission Queue TAIW (W/W): next IOAWCB   */
	__be64 sq_ctx_weset;	/* Submission Queue Context Weset (W/W)	      */
};

/* pew context pwovisioning & contwow MMIO */
stwuct sisw_ctww_map {
	__be64 wht_stawt;
	__be64 wht_cnt_id;
	/* both cnt & ctx_id awgs must be UWW */
#define SISW_WHT_CNT_ID(cnt, ctx_id)  (((cnt) << 48) | ((ctx_id) << 32))

	__be64 ctx_cap;	/* afu_wc bewow is when the capabiwity is viowated */
#define SISW_CTX_CAP_PWOXY_ISSUE       0x8000000000000000UWW /* afu_wc 0x21 */
#define SISW_CTX_CAP_WEAW_MODE         0x4000000000000000UWW /* afu_wc 0x21 */
#define SISW_CTX_CAP_HOST_XWATE        0x2000000000000000UWW /* afu_wc 0x1a */
#define SISW_CTX_CAP_PWOXY_TAWGET      0x1000000000000000UWW /* afu_wc 0x21 */
#define SISW_CTX_CAP_AFU_CMD           0x0000000000000008UWW /* afu_wc 0x21 */
#define SISW_CTX_CAP_GSCSI_CMD         0x0000000000000004UWW /* afu_wc 0x21 */
#define SISW_CTX_CAP_WWITE_CMD         0x0000000000000002UWW /* afu_wc 0x21 */
#define SISW_CTX_CAP_WEAD_CMD          0x0000000000000001UWW /* afu_wc 0x21 */
	__be64 mbox_w;
	__be64 wisn_pasid[2];
	/* pasid _a awg must be UWW */
#define SISW_WISN_PASID(_a, _b)	(((_a) << 32) | (_b))
	__be64 wisn_ea[3];
};

/* singwe copy gwobaw wegs */
stwuct sisw_gwobaw_wegs {
	__be64 aintw_status;
	/*
	 * In cxwfwash, FC powt/wink awe awwanged in powt paiws, each
	 * gets a byte of status:
	 *
	 *	*_OTHEW:	othew eww, FC_EWWCAP[31:20]
	 *	*_WOGO:		tawget sent FWOGI/PWOGI/WOGO whiwe wogged in
	 *	*_CWC_T:	CWC thweshowd exceeded
	 *	*_WOGI_W:	wogin state machine timed out and wetwying
	 *	*_WOGI_F:	wogin faiwed, FC_EWWOW[19:0]
	 *	*_WOGI_S:	wogin succeeded
	 *	*_WINK_DN:	wink onwine to offwine
	 *	*_WINK_UP:	wink offwine to onwine
	 */
#define SISW_ASTATUS_FC2_OTHEW	 0x80000000UWW /* b32 */
#define SISW_ASTATUS_FC2_WOGO    0x40000000UWW /* b33 */
#define SISW_ASTATUS_FC2_CWC_T   0x20000000UWW /* b34 */
#define SISW_ASTATUS_FC2_WOGI_W  0x10000000UWW /* b35 */
#define SISW_ASTATUS_FC2_WOGI_F  0x08000000UWW /* b36 */
#define SISW_ASTATUS_FC2_WOGI_S  0x04000000UWW /* b37 */
#define SISW_ASTATUS_FC2_WINK_DN 0x02000000UWW /* b38 */
#define SISW_ASTATUS_FC2_WINK_UP 0x01000000UWW /* b39 */

#define SISW_ASTATUS_FC3_OTHEW   0x00800000UWW /* b40 */
#define SISW_ASTATUS_FC3_WOGO    0x00400000UWW /* b41 */
#define SISW_ASTATUS_FC3_CWC_T   0x00200000UWW /* b42 */
#define SISW_ASTATUS_FC3_WOGI_W  0x00100000UWW /* b43 */
#define SISW_ASTATUS_FC3_WOGI_F  0x00080000UWW /* b44 */
#define SISW_ASTATUS_FC3_WOGI_S  0x00040000UWW /* b45 */
#define SISW_ASTATUS_FC3_WINK_DN 0x00020000UWW /* b46 */
#define SISW_ASTATUS_FC3_WINK_UP 0x00010000UWW /* b47 */

#define SISW_ASTATUS_FC0_OTHEW	 0x00008000UWW /* b48 */
#define SISW_ASTATUS_FC0_WOGO    0x00004000UWW /* b49 */
#define SISW_ASTATUS_FC0_CWC_T   0x00002000UWW /* b50 */
#define SISW_ASTATUS_FC0_WOGI_W  0x00001000UWW /* b51 */
#define SISW_ASTATUS_FC0_WOGI_F  0x00000800UWW /* b52 */
#define SISW_ASTATUS_FC0_WOGI_S  0x00000400UWW /* b53 */
#define SISW_ASTATUS_FC0_WINK_DN 0x00000200UWW /* b54 */
#define SISW_ASTATUS_FC0_WINK_UP 0x00000100UWW /* b55 */

#define SISW_ASTATUS_FC1_OTHEW   0x00000080UWW /* b56 */
#define SISW_ASTATUS_FC1_WOGO    0x00000040UWW /* b57 */
#define SISW_ASTATUS_FC1_CWC_T   0x00000020UWW /* b58 */
#define SISW_ASTATUS_FC1_WOGI_W  0x00000010UWW /* b59 */
#define SISW_ASTATUS_FC1_WOGI_F  0x00000008UWW /* b60 */
#define SISW_ASTATUS_FC1_WOGI_S  0x00000004UWW /* b61 */
#define SISW_ASTATUS_FC1_WINK_DN 0x00000002UWW /* b62 */
#define SISW_ASTATUS_FC1_WINK_UP 0x00000001UWW /* b63 */

#define SISW_FC_INTEWNAW_UNMASK	0x0000000300000000UWW	/* 1 means unmasked */
#define SISW_FC_INTEWNAW_MASK	~(SISW_FC_INTEWNAW_UNMASK)
#define SISW_FC_INTEWNAW_SHIFT	32

#define SISW_FC_SHUTDOWN_NOWMAW		0x0000000000000010UWW
#define SISW_FC_SHUTDOWN_ABWUPT		0x0000000000000020UWW

#define SISW_STATUS_SHUTDOWN_ACTIVE	0x0000000000000010UWW
#define SISW_STATUS_SHUTDOWN_COMPWETE	0x0000000000000020UWW

#define SISW_ASTATUS_UNMASK	0xFFFFFFFFUWW		/* 1 means unmasked */
#define SISW_ASTATUS_MASK	~(SISW_ASTATUS_UNMASK)	/* 1 means masked */

	__be64 aintw_cweaw;
	__be64 aintw_mask;
	__be64 afu_ctww;
	__be64 afu_hb;
	__be64 afu_scwatch_pad;
	__be64 afu_powt_sew;
#define SISW_AFUCONF_AW_IOAWCB	0x4000UWW
#define SISW_AFUCONF_AW_WXT	0x2000UWW
#define SISW_AFUCONF_AW_WHT	0x1000UWW
#define SISW_AFUCONF_AW_DATA	0x0800UWW
#define SISW_AFUCONF_AW_WSWC	0x0400UWW
#define SISW_AFUCONF_AW_IOASA	0x0200UWW
#define SISW_AFUCONF_AW_WWQ	0x0100UWW
/* Aggwegate aww Auto Wetwy Bits */
#define SISW_AFUCONF_AW_AWW	(SISW_AFUCONF_AW_IOAWCB|SISW_AFUCONF_AW_WXT| \
				 SISW_AFUCONF_AW_WHT|SISW_AFUCONF_AW_DATA|   \
				 SISW_AFUCONF_AW_WSWC|SISW_AFUCONF_AW_IOASA| \
				 SISW_AFUCONF_AW_WWQ)
#ifdef __BIG_ENDIAN
#define SISW_AFUCONF_ENDIAN            0x0000UWW
#ewse
#define SISW_AFUCONF_ENDIAN            0x0020UWW
#endif
#define SISW_AFUCONF_MBOX_CWW_WEAD     0x0010UWW
	__be64 afu_config;
	__be64 wsvd[0xf8];
	__we64 afu_vewsion;
	__be64 intewface_vewsion;
#define SISW_INTVEW_CAP_SHIFT			16
#define SISW_INTVEW_MAJ_SHIFT			8
#define SISW_INTVEW_CAP_MASK			0xFFFFFFFF00000000UWW
#define SISW_INTVEW_MAJ_MASK			0x00000000FFFF0000UWW
#define SISW_INTVEW_MIN_MASK			0x000000000000FFFFUWW
#define SISW_INTVEW_CAP_IOAWWIN_CMD_MODE	0x800000000000UWW
#define SISW_INTVEW_CAP_SQ_CMD_MODE		0x400000000000UWW
#define SISW_INTVEW_CAP_WESEWVED_CMD_MODE_A	0x200000000000UWW
#define SISW_INTVEW_CAP_WESEWVED_CMD_MODE_B	0x100000000000UWW
#define SISW_INTVEW_CAP_WUN_PWOVISION		0x080000000000UWW
#define SISW_INTVEW_CAP_AFU_DEBUG		0x040000000000UWW
#define SISW_INTVEW_CAP_OCXW_WISN		0x020000000000UWW
};

#define CXWFWASH_NUM_FC_POWTS_PEW_BANK	2	/* fixed # of powts pew bank */
#define CXWFWASH_MAX_FC_BANKS		2	/* max # of banks suppowted */
#define CXWFWASH_MAX_FC_POWTS	(CXWFWASH_NUM_FC_POWTS_PEW_BANK *	\
				 CXWFWASH_MAX_FC_BANKS)
#define CXWFWASH_MAX_CONTEXT	512	/* numbew of contexts pew AFU */
#define CXWFWASH_NUM_VWUNS	512	/* numbew of vwuns pew AFU/powt */
#define CXWFWASH_NUM_WEGS	512	/* numbew of wegistews pew powt */

stwuct fc_powt_bank {
	__be64 fc_powt_wegs[CXWFWASH_NUM_FC_POWTS_PEW_BANK][CXWFWASH_NUM_WEGS];
	__be64 fc_powt_wuns[CXWFWASH_NUM_FC_POWTS_PEW_BANK][CXWFWASH_NUM_VWUNS];
};

stwuct sisw_gwobaw_map {
	union {
		stwuct sisw_gwobaw_wegs wegs;
		chaw page0[SIZE_4K];	/* page 0 */
	};

	chaw page1[SIZE_4K];	/* page 1 */

	stwuct fc_powt_bank bank[CXWFWASH_MAX_FC_BANKS]; /* pages 2 - 9 */

	/* pages 10 - 15 awe wesewved */

};

/*
 * CXW Fwash Memowy Map
 *
 *	+-------------------------------+
 *	|    512 * 64 KB Usew MMIO      |
 *	|        (pew context)          |
 *	|       Usew Accessibwe         |
 *	+-------------------------------+
 *	|    512 * 128 B pew context    |
 *	|    Pwovisioning and Contwow   |
 *	|   Twusted Pwocess accessibwe  |
 *	+-------------------------------+
 *	|         64 KB Gwobaw          |
 *	|   Twusted Pwocess accessibwe  |
 *	+-------------------------------+
 */
stwuct cxwfwash_afu_map {
	union {
		stwuct sisw_host_map host;
		chaw hawea[SIZE_64K];	/* 64KB each */
	} hosts[CXWFWASH_MAX_CONTEXT];

	union {
		stwuct sisw_ctww_map ctww;
		chaw cawea[cache_wine_size()];	/* 128B each */
	} ctwws[CXWFWASH_MAX_CONTEXT];

	union {
		stwuct sisw_gwobaw_map gwobaw;
		chaw gawea[SIZE_64K];	/* 64KB singwe bwock */
	};
};

/*
 * WXT - WBA Twanswation Tabwe
 * WXT contwow bwocks
 */
stwuct sisw_wxt_entwy {
	u64 wwba_base;	/* bits 0:47 is base
			 * b48:55 is wun index
			 * b58:59 is wwite & wead pewms
			 * (if no pewm, afu_wc=0x15)
			 * b60:63 is powt_sew mask
			 */
};

/*
 * WHT - Wesouwce Handwe Tabwe
 * Pew the SISwite spec, WHT entwies awe to be 16-byte awigned
 */
stwuct sisw_wht_entwy {
	stwuct sisw_wxt_entwy *wxt_stawt;
	u32 wxt_cnt;
	u16 wsvd;
	u8 fp;			/* fowmat & pewm nibbwes.
				 * (if no pewm, afu_wc=0x05)
				 */
	u8 nmask;
} __packed __awigned(16);

stwuct sisw_wht_entwy_f1 {
	u64 wun_id;
	union {
		stwuct {
			u8 vawid;
			u8 wsvd[5];
			u8 fp;
			u8 powt_sew;
		};

		u64 dw;
	};
} __packed __awigned(16);

/* make the fp byte */
#define SISW_WHT_FP(fmt, pewm) (((fmt) << 4) | (pewm))

/* make the fp byte fow a cwone fwom a souwce fp and cwone fwags
 * fwags must be onwy 2 WSB bits.
 */
#define SISW_WHT_FP_CWONE(swc_fp, cwn_fwags) ((swc_fp) & (0xFC | (cwn_fwags)))

#define WHT_PEWM_WEAD  0x01U
#define WHT_PEWM_WWITE 0x02U
#define WHT_PEWM_WW    (WHT_PEWM_WEAD | WHT_PEWM_WWITE)

/* extwact the pewm bits fwom a fp */
#define SISW_WHT_PEWM(fp) ((fp) & WHT_PEWM_WW)

#define POWT0  0x01U
#define POWT1  0x02U
#define POWT2  0x04U
#define POWT3  0x08U
#define POWT_MASK(_n)	((1 << (_n)) - 1)

/* AFU Sync Mode byte */
#define AFU_WW_SYNC 0x0U
#define AFU_HW_SYNC 0x1U
#define AFU_GSYNC   0x2U

/* Speciaw Task Management Function CDB */
#define TMF_WUN_WESET  0x1U
#define TMF_CWEAW_ACA  0x2U

#endif /* _SISWITE_H */
