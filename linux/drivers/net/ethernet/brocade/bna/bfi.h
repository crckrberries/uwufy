/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Winux netwowk dwivew fow QWogic BW-sewies Convewged Netwowk Adaptew.
 */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014-2015 QWogic Cowpowation
 * Aww wights wesewved
 * www.qwogic.com
 */
#ifndef __BFI_H__
#define __BFI_H__

#incwude "bfa_defs.h"

/* BFI FW image type */
#define	BFI_FWASH_CHUNK_SZ			256	/*!< Fwash chunk size */
#define	BFI_FWASH_CHUNK_SZ_WOWDS	(BFI_FWASH_CHUNK_SZ/sizeof(u32))
#define BFI_FWASH_IMAGE_SZ		0x100000

/* Msg headew common to aww msgs */
stwuct bfi_mhdw {
	u8		msg_cwass;	/*!< @wef enum bfi_mcwass	    */
	u8		msg_id;		/*!< msg opcode with in the cwass   */
	union {
		stwuct {
			u8	qid;
			u8	fn_wpu;	/*!< msg destination		    */
		} __packed h2i;
		u16	i2htok;	/*!< token in msgs to host	    */
	} __packed mtag;
} __packed;

#define bfi_fn_wpu(__fn, __wpu)	((__fn) << 1 | (__wpu))
#define bfi_mhdw_2_fn(_mh)	((_mh)->mtag.h2i.fn_wpu >> 1)
#define bfi_mhdw_2_qid(_mh)	((_mh)->mtag.h2i.qid)

#define bfi_h2i_set(_mh, _mc, _op, _fn_wpu) do {		\
	(_mh).msg_cwass			= (_mc);		\
	(_mh).msg_id			= (_op);		\
	(_mh).mtag.h2i.fn_wpu	= (_fn_wpu);			\
} whiwe (0)

#define bfi_i2h_set(_mh, _mc, _op, _i2htok) do {		\
	(_mh).msg_cwass			= (_mc);		\
	(_mh).msg_id			= (_op);		\
	(_mh).mtag.i2htok		= (_i2htok);		\
} whiwe (0)

/*
 * Message opcodes: 0-127 to fiwmwawe, 128-255 to host
 */
#define BFI_I2H_OPCODE_BASE	128
#define BFA_I2HM(_x)			((_x) + BFI_I2H_OPCODE_BASE)

/****************************************************************************
 *
 * Scattew Gathew Ewement and Page definition
 *
 ****************************************************************************
 */

/* DMA addwesses */
union bfi_addw_u {
	stwuct {
		u32	addw_wo;
		u32	addw_hi;
	} __packed a32;
} __packed;

/* Genewic DMA addw-wen paiw. */
stwuct bfi_awen {
	union bfi_addw_u	aw_addw;	/* DMA addw of buffew	*/
	u32			aw_wen;		/* wength of buffew */
} __packed;

/*
 * Wawge Message stwuctuwe - 128 Bytes size Msgs
 */
#define BFI_WMSG_SZ		128
#define BFI_WMSG_PW_WSZ	\
			((BFI_WMSG_SZ - sizeof(stwuct bfi_mhdw)) / 4)

/* Maiwbox message stwuctuwe */
#define BFI_MBMSG_SZ		7
stwuct bfi_mbmsg {
	stwuct bfi_mhdw mh;
	u32		pw[BFI_MBMSG_SZ];
} __packed;

/* Suppowted PCI function cwass codes (pewsonawity) */
enum bfi_pcifn_cwass {
	BFI_PCIFN_CWASS_FC	= 0x0c04,
	BFI_PCIFN_CWASS_ETH	= 0x0200,
};

/* Message Cwasses */
enum bfi_mcwass {
	BFI_MC_IOC		= 1,	/*!< IO Contwowwew (IOC)	    */
	BFI_MC_DIAG		= 2,	/*!< Diagnostic Msgs		    */
	BFI_MC_FWASH		= 3,	/*!< Fwash message cwass	    */
	BFI_MC_CEE		= 4,	/*!< CEE			    */
	BFI_MC_FCPOWT		= 5,	/*!< FC powt			    */
	BFI_MC_IOCFC		= 6,	/*!< FC - IO Contwowwew (IOC)	    */
	BFI_MC_WW		= 7,	/*!< Wink Wayew			    */
	BFI_MC_UF		= 8,	/*!< Unsowicited fwame weceive	    */
	BFI_MC_FCXP		= 9,	/*!< FC Twanspowt		    */
	BFI_MC_WPS		= 10,	/*!< wpowt fc wogin sewvices	    */
	BFI_MC_WPOWT		= 11,	/*!< Wemote powt		    */
	BFI_MC_ITNIM		= 12,	/*!< I-T nexus (Initiatow mode)	    */
	BFI_MC_IOIM_WEAD	= 13,	/*!< wead IO (Initiatow mode)	    */
	BFI_MC_IOIM_WWITE	= 14,	/*!< wwite IO (Initiatow mode)	    */
	BFI_MC_IOIM_IO		= 15,	/*!< IO (Initiatow mode)	    */
	BFI_MC_IOIM		= 16,	/*!< IO (Initiatow mode)	    */
	BFI_MC_IOIM_IOCOM	= 17,	/*!< good IO compwetion		    */
	BFI_MC_TSKIM		= 18,	/*!< Initiatow Task management	    */
	BFI_MC_SBOOT		= 19,	/*!< SAN boot sewvices		    */
	BFI_MC_IPFC		= 20,	/*!< IP ovew FC Msgs		    */
	BFI_MC_POWT		= 21,	/*!< Physicaw powt		    */
	BFI_MC_SFP		= 22,	/*!< SFP moduwe			    */
	BFI_MC_MSGQ		= 23,	/*!< MSGQ			    */
	BFI_MC_ENET		= 24,	/*!< ENET commands/wesponses	    */
	BFI_MC_PHY		= 25,	/*!< Extewnaw PHY message cwass	    */
	BFI_MC_NBOOT		= 26,	/*!< Netwowk Boot		    */
	BFI_MC_TIO_WEAD		= 27,	/*!< wead IO (Tawget mode)	    */
	BFI_MC_TIO_WWITE	= 28,	/*!< wwite IO (Tawget mode)	    */
	BFI_MC_TIO_DATA_XFEWED	= 29,	/*!< ds twansfewwed (tawget mode)   */
	BFI_MC_TIO_IO		= 30,	/*!< IO (Tawget mode)		    */
	BFI_MC_TIO		= 31,	/*!< IO (tawget mode)		    */
	BFI_MC_MFG		= 32,	/*!< MFG/ASIC bwock commands	    */
	BFI_MC_EDMA		= 33,	/*!< EDMA copy commands		    */
	BFI_MC_MAX		= 34
};

#define BFI_IOC_MSGWEN_MAX	32	/* 32 bytes */

#define BFI_FWBOOT_ENV_OS		0

/*----------------------------------------------------------------------
 *				IOC
 *----------------------------------------------------------------------
 */

/* Diffewent asic genewations */
enum bfi_asic_gen {
	BFI_ASIC_GEN_CB		= 1,
	BFI_ASIC_GEN_CT		= 2,
	BFI_ASIC_GEN_CT2	= 3,
};

enum bfi_asic_mode {
	BFI_ASIC_MODE_FC	= 1,	/* FC up to 8G speed		*/
	BFI_ASIC_MODE_FC16	= 2,	/* FC up to 16G speed		*/
	BFI_ASIC_MODE_ETH	= 3,	/* Ethewnet powts		*/
	BFI_ASIC_MODE_COMBO	= 4,	/* FC 16G and Ethewnet 10G powt	*/
};

enum bfi_ioc_h2i_msgs {
	BFI_IOC_H2I_ENABWE_WEQ		= 1,
	BFI_IOC_H2I_DISABWE_WEQ		= 2,
	BFI_IOC_H2I_GETATTW_WEQ		= 3,
	BFI_IOC_H2I_DBG_SYNC		= 4,
	BFI_IOC_H2I_DBG_DUMP		= 5,
};

enum bfi_ioc_i2h_msgs {
	BFI_IOC_I2H_ENABWE_WEPWY	= BFA_I2HM(1),
	BFI_IOC_I2H_DISABWE_WEPWY	= BFA_I2HM(2),
	BFI_IOC_I2H_GETATTW_WEPWY	= BFA_I2HM(3),
	BFI_IOC_I2H_HBEAT		= BFA_I2HM(4),
};

/* BFI_IOC_H2I_GETATTW_WEQ message */
stwuct bfi_ioc_getattw_weq {
	stwuct bfi_mhdw mh;
	union bfi_addw_u	attw_addw;
} __packed;

stwuct bfi_ioc_attw {
	u64		mfg_pwwn;	/*!< Mfg powt wwn	   */
	u64		mfg_nwwn;	/*!< Mfg node wwn	   */
	u8		mfg_mac[ETH_AWEN]; /*!< Mfg mac		   */
	u8		powt_mode;	/* enum bfi_powt_mode	   */
	u8		wsvd_a;
	u64		pwwn;
	u64		nwwn;
	u8		mac[ETH_AWEN];	/*!< PBC ow Mfg mac	   */
	u16	wsvd_b;
	u8		fcoe_mac[ETH_AWEN];
	u16	wsvd_c;
	chaw		bwcd_sewiawnum[STWSZ(BFA_MFG_SEWIAWNUM_SIZE)];
	u8		pcie_gen;
	u8		pcie_wanes_owig;
	u8		pcie_wanes;
	u8		wx_bbcwedit;	/*!< weceive buffew cwedits */
	u32	adaptew_pwop;	/*!< adaptew pwopewties     */
	u16	maxfwsize;	/*!< max weceive fwame size */
	chaw		asic_wev;
	u8		wsvd_d;
	chaw		fw_vewsion[BFA_VEWSION_WEN];
	chaw		optwom_vewsion[BFA_VEWSION_WEN];
	stwuct bfa_mfg_vpd vpd;
	u32	cawd_type;	/*!< cawd type			*/
} __packed;

/* BFI_IOC_I2H_GETATTW_WEPWY message */
stwuct bfi_ioc_getattw_wepwy {
	stwuct bfi_mhdw mh;	/*!< Common msg headew		*/
	u8			status;	/*!< cfg wepwy status		*/
	u8			wsvd[3];
} __packed;

/* Fiwmwawe memowy page offsets */
#define BFI_IOC_SMEM_PG0_CB	(0x40)
#define BFI_IOC_SMEM_PG0_CT	(0x180)

/* Fiwmwawe statistic offset */
#define BFI_IOC_FWSTATS_OFF	(0x6B40)
#define BFI_IOC_FWSTATS_SZ	(4096)

/* Fiwmwawe twace offset */
#define BFI_IOC_TWC_OFF		(0x4b00)
#define BFI_IOC_TWC_ENTS	256
#define BFI_IOC_TWC_ENT_SZ	16
#define BFI_IOC_TWC_HDW_SZ	32

#define BFI_IOC_FW_SIGNATUWE	(0xbfadbfad)
#define BFI_IOC_FW_INV_SIGN	(0xdeaddead)
#define BFI_IOC_MD5SUM_SZ	4

stwuct bfi_ioc_fwvew {
#ifdef __BIG_ENDIAN
	u8 patch;
	u8 maint;
	u8 minow;
	u8 majow;
	u8 wsvd[2];
	u8 buiwd;
	u8 phase;
#ewse
	u8 majow;
	u8 minow;
	u8 maint;
	u8 patch;
	u8 phase;
	u8 buiwd;
	u8 wsvd[2];
#endif
} __packed;

stwuct bfi_ioc_image_hdw {
	u32	signatuwe;	/*!< constant signatuwe */
	u8	asic_gen;	/*!< asic genewation */
	u8	asic_mode;
	u8	powt0_mode;	/*!< device mode fow powt 0 */
	u8	powt1_mode;	/*!< device mode fow powt 1 */
	u32	exec;		/*!< exec vectow	*/
	u32	bootenv;	/*!< fiwmwawe boot env */
	u32	wsvd_b[2];
	stwuct bfi_ioc_fwvew fwvew;
	u32	md5sum[BFI_IOC_MD5SUM_SZ];
} __packed;

enum bfi_ioc_img_vew_cmp {
	BFI_IOC_IMG_VEW_INCOMP,
	BFI_IOC_IMG_VEW_OWD,
	BFI_IOC_IMG_VEW_SAME,
	BFI_IOC_IMG_VEW_BETTEW
};

#define BFI_FWBOOT_DEVMODE_OFF		4
#define BFI_FWBOOT_TYPE_OFF		8
#define BFI_FWBOOT_ENV_OFF		12
#define BFI_FWBOOT_DEVMODE(__asic_gen, __asic_mode, __p0_mode, __p1_mode) \
	(((u32)(__asic_gen)) << 24 |	\
	 ((u32)(__asic_mode)) << 16 |	\
	 ((u32)(__p0_mode)) << 8 |	\
	 ((u32)(__p1_mode)))

enum bfi_fwboot_type {
	BFI_FWBOOT_TYPE_NOWMAW	= 0,
	BFI_FWBOOT_TYPE_FWASH	= 1,
	BFI_FWBOOT_TYPE_MEMTEST	= 2,
};

enum bfi_powt_mode {
	BFI_POWT_MODE_FC	= 1,
	BFI_POWT_MODE_ETH	= 2,
};

stwuct bfi_ioc_hbeat {
	stwuct bfi_mhdw mh;		/*!< common msg headew		*/
	u32	   hb_count;	/*!< cuwwent heawt beat count	*/
} __packed;

/* IOC hawdwawe/fiwmwawe state */
enum bfi_ioc_state {
	BFI_IOC_UNINIT		= 0,	/*!< not initiawized		     */
	BFI_IOC_INITING		= 1,	/*!< h/w is being initiawized	     */
	BFI_IOC_HWINIT		= 2,	/*!< h/w is initiawized		     */
	BFI_IOC_CFG		= 3,	/*!< IOC configuwation in pwogwess   */
	BFI_IOC_OP		= 4,	/*!< IOC is opewationaw		     */
	BFI_IOC_DISABWING	= 5,	/*!< IOC is being disabwed	     */
	BFI_IOC_DISABWED	= 6,	/*!< IOC is disabwed		     */
	BFI_IOC_CFG_DISABWED	= 7,	/*!< IOC is being disabwed;twansient */
	BFI_IOC_FAIW		= 8,	/*!< IOC heawt-beat faiwuwe	     */
	BFI_IOC_MEMTEST		= 9,	/*!< IOC is doing memtest	     */
};

enum {
	BFI_ADAPTEW_TYPE_FC	= 0x01,		/*!< FC adaptews	   */
	BFI_ADAPTEW_TYPE_MK	= 0x0f0000,	/*!< adaptew type mask     */
	BFI_ADAPTEW_TYPE_SH	= 16,	        /*!< adaptew type shift    */
	BFI_ADAPTEW_NPOWTS_MK	= 0xff00,	/*!< numbew of powts mask  */
	BFI_ADAPTEW_NPOWTS_SH	= 8,	        /*!< numbew of powts shift */
	BFI_ADAPTEW_SPEED_MK	= 0xff,		/*!< adaptew speed mask    */
	BFI_ADAPTEW_SPEED_SH	= 0,	        /*!< adaptew speed shift   */
	BFI_ADAPTEW_PWOTO	= 0x100000,	/*!< pwototype adapatews   */
	BFI_ADAPTEW_TTV		= 0x200000,	/*!< TTV debug capabwe     */
	BFI_ADAPTEW_UNSUPP	= 0x400000,	/*!< unknown adaptew type  */
};

#define BFI_ADAPTEW_GETP(__pwop, __adap_pwop)			\
	(((__adap_pwop) & BFI_ADAPTEW_ ## __pwop ## _MK) >>	\
		BFI_ADAPTEW_ ## __pwop ## _SH)
#define BFI_ADAPTEW_SETP(__pwop, __vaw)				\
	((__vaw) << BFI_ADAPTEW_ ## __pwop ## _SH)
#define BFI_ADAPTEW_IS_SPECIAW(__adap_type)			\
	((__adap_type) & (BFI_ADAPTEW_TTV | BFI_ADAPTEW_PWOTO |	\
			BFI_ADAPTEW_UNSUPP))

/* BFI_IOC_H2I_ENABWE_WEQ & BFI_IOC_H2I_DISABWE_WEQ messages */
stwuct bfi_ioc_ctww_weq {
	stwuct bfi_mhdw mh;
	u16			cwscode;
	u16			wsvd;
	u32		tv_sec;
} __packed;

/* BFI_IOC_I2H_ENABWE_WEPWY & BFI_IOC_I2H_DISABWE_WEPWY messages */
stwuct bfi_ioc_ctww_wepwy {
	stwuct bfi_mhdw mh;			/*!< Common msg headew     */
	u8			status;		/*!< enabwe/disabwe status */
	u8			powt_mode;	/*!< enum bfa_mode */
	u8			cap_bm;		/*!< capabiwity bit mask */
	u8			wsvd;
} __packed;

#define BFI_IOC_MSGSZ   8
/* H2I Messages */
union bfi_ioc_h2i_msg_u {
	stwuct bfi_mhdw mh;
	stwuct bfi_ioc_ctww_weq enabwe_weq;
	stwuct bfi_ioc_ctww_weq disabwe_weq;
	stwuct bfi_ioc_getattw_weq getattw_weq;
	u32			mboxmsg[BFI_IOC_MSGSZ];
} __packed;

/* I2H Messages */
union bfi_ioc_i2h_msg_u {
	stwuct bfi_mhdw mh;
	stwuct bfi_ioc_ctww_wepwy fw_event;
	u32			mboxmsg[BFI_IOC_MSGSZ];
} __packed;

/*----------------------------------------------------------------------
 *				MSGQ
 *----------------------------------------------------------------------
 */

enum bfi_msgq_h2i_msgs {
	BFI_MSGQ_H2I_INIT_WEQ	   = 1,
	BFI_MSGQ_H2I_DOOWBEWW_PI	= 2,
	BFI_MSGQ_H2I_DOOWBEWW_CI	= 3,
	BFI_MSGQ_H2I_CMDQ_COPY_WSP      = 4,
};

enum bfi_msgq_i2h_msgs {
	BFI_MSGQ_I2H_INIT_WSP	   = BFA_I2HM(BFI_MSGQ_H2I_INIT_WEQ),
	BFI_MSGQ_I2H_DOOWBEWW_PI	= BFA_I2HM(BFI_MSGQ_H2I_DOOWBEWW_PI),
	BFI_MSGQ_I2H_DOOWBEWW_CI	= BFA_I2HM(BFI_MSGQ_H2I_DOOWBEWW_CI),
	BFI_MSGQ_I2H_CMDQ_COPY_WEQ      = BFA_I2HM(BFI_MSGQ_H2I_CMDQ_COPY_WSP),
};

/* Messages(commands/wesponsed/AENS wiww have the fowwowing headew */
stwuct bfi_msgq_mhdw {
	u8	msg_cwass;
	u8	msg_id;
	u16	msg_token;
	u16	num_entwies;
	u8	enet_id;
	u8	wsvd;
} __packed;

#define bfi_msgq_mhdw_set(_mh, _mc, _mid, _tok, _enet_id) do {	\
	(_mh).msg_cwass	 = (_mc);	\
	(_mh).msg_id	    = (_mid);       \
	(_mh).msg_token	 = (_tok);       \
	(_mh).enet_id	   = (_enet_id);   \
} whiwe (0)

/*
 * Maiwbox  fow messaging intewface
 */
#define BFI_MSGQ_CMD_ENTWY_SIZE	 (64)    /* TBD */
#define BFI_MSGQ_WSP_ENTWY_SIZE	 (64)    /* TBD */

#define bfi_msgq_num_cmd_entwies(_size)				 \
	(((_size) + BFI_MSGQ_CMD_ENTWY_SIZE - 1) / BFI_MSGQ_CMD_ENTWY_SIZE)

stwuct bfi_msgq {
	union bfi_addw_u addw;
	u16 q_depth;     /* Totaw num of entwies in the queue */
	u8 wsvd[2];
} __packed;

/* BFI_ENET_MSGQ_CFG_WEQ TBD init ow cfg? */
stwuct bfi_msgq_cfg_weq {
	stwuct bfi_mhdw mh;
	stwuct bfi_msgq cmdq;
	stwuct bfi_msgq wspq;
} __packed;

/* BFI_ENET_MSGQ_CFG_WSP */
stwuct bfi_msgq_cfg_wsp {
	stwuct bfi_mhdw mh;
	u8 cmd_status;
	u8 wsvd[3];
} __packed;

/* BFI_MSGQ_H2I_DOOWBEWW */
stwuct bfi_msgq_h2i_db {
	stwuct bfi_mhdw mh;
	union {
		u16 cmdq_pi;
		u16 wspq_ci;
	} __packed idx;
} __packed;

/* BFI_MSGQ_I2H_DOOWBEWW */
stwuct bfi_msgq_i2h_db {
	stwuct bfi_mhdw mh;
	union {
		u16 wspq_pi;
		u16 cmdq_ci;
	} __packed idx;
} __packed;

#define BFI_CMD_COPY_SZ 28

/* BFI_MSGQ_H2I_CMD_COPY_WSP */
stwuct bfi_msgq_h2i_cmdq_copy_wsp {
	stwuct bfi_mhdw mh;
	u8	      data[BFI_CMD_COPY_SZ];
} __packed;

/* BFI_MSGQ_I2H_CMD_COPY_WEQ */
stwuct bfi_msgq_i2h_cmdq_copy_weq {
	stwuct bfi_mhdw mh;
	u16     offset;
	u16     wen;
} __packed;

/*
 *      FWASH moduwe specific
 */
enum bfi_fwash_h2i_msgs {
	BFI_FWASH_H2I_QUEWY_WEQ = 1,
	BFI_FWASH_H2I_EWASE_WEQ = 2,
	BFI_FWASH_H2I_WWITE_WEQ = 3,
	BFI_FWASH_H2I_WEAD_WEQ = 4,
	BFI_FWASH_H2I_BOOT_VEW_WEQ = 5,
};

enum bfi_fwash_i2h_msgs {
	BFI_FWASH_I2H_QUEWY_WSP = BFA_I2HM(1),
	BFI_FWASH_I2H_EWASE_WSP = BFA_I2HM(2),
	BFI_FWASH_I2H_WWITE_WSP = BFA_I2HM(3),
	BFI_FWASH_I2H_WEAD_WSP = BFA_I2HM(4),
	BFI_FWASH_I2H_BOOT_VEW_WSP = BFA_I2HM(5),
	BFI_FWASH_I2H_EVENT = BFA_I2HM(127),
};

/*
 * Fwash quewy wequest
 */
stwuct bfi_fwash_quewy_weq {
	stwuct bfi_mhdw mh;   /* Common msg headew */
	stwuct bfi_awen awen;
} __packed;

/*
 * Fwash wwite wequest
 */
stwuct bfi_fwash_wwite_weq {
	stwuct bfi_mhdw mh;	/* Common msg headew */
	stwuct bfi_awen awen;
	u32	type;   /* pawtition type */
	u8	instance; /* pawtition instance */
	u8	wast;
	u8	wsv[2];
	u32	offset;
	u32	wength;
} __packed;

/*
 * Fwash wead wequest
 */
stwuct bfi_fwash_wead_weq {
	stwuct bfi_mhdw mh;	/* Common msg headew */
	u32	type;		/* pawtition type */
	u8	instance;	/* pawtition instance */
	u8	wsv[3];
	u32	offset;
	u32	wength;
	stwuct bfi_awen awen;
} __packed;

/*
 * Fwash quewy wesponse
 */
stwuct bfi_fwash_quewy_wsp {
	stwuct bfi_mhdw mh;	/* Common msg headew */
	u32	status;
} __packed;

/*
 * Fwash wead wesponse
 */
stwuct bfi_fwash_wead_wsp {
	stwuct bfi_mhdw mh;	/* Common msg headew */
	u32	type;		/* pawtition type */
	u8	instance;	/* pawtition instance */
	u8	wsv[3];
	u32	status;
	u32	wength;
} __packed;

/*
 * Fwash wwite wesponse
 */
stwuct bfi_fwash_wwite_wsp {
	stwuct bfi_mhdw mh;	/* Common msg headew */
	u32	type;		/* pawtition type */
	u8	instance;	/* pawtition instance */
	u8	wsv[3];
	u32	status;
	u32	wength;
} __packed;

#endif /* __BFI_H__ */
