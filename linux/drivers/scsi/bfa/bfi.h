/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014- QWogic Cowpowation.
 * Aww wights wesewved
 * www.qwogic.com
 *
 * Winux dwivew fow QWogic BW-sewies Fibwe Channew Host Bus Adaptew.
 */

#ifndef __BFI_H__
#define __BFI_H__

#incwude "bfa_defs.h"
#incwude "bfa_defs_svc.h"

#pwagma pack(1)

/* Pew dma segment max size */
#define BFI_MEM_DMA_SEG_SZ	(131072)

/* Get numbew of dma segments wequiwed */
#define BFI_MEM_DMA_NSEGS(_num_weqs, _weq_sz)				\
	((u16)(((((_num_weqs) * (_weq_sz)) + BFI_MEM_DMA_SEG_SZ - 1) &	\
	 ~(BFI_MEM_DMA_SEG_SZ - 1)) / BFI_MEM_DMA_SEG_SZ))

/* Get num dma weqs - that fit in a segment */
#define BFI_MEM_NWEQS_SEG(_wqsz) (BFI_MEM_DMA_SEG_SZ / (_wqsz))

/* Get segment num fwom tag */
#define BFI_MEM_SEG_FWOM_TAG(_tag, _wqsz) ((_tag) / BFI_MEM_NWEQS_SEG(_wqsz))

/* Get dma weq offset in a segment */
#define BFI_MEM_SEG_WEQ_OFFSET(_tag, _sz)	\
	((_tag) - (BFI_MEM_SEG_FWOM_TAG(_tag, _sz) * BFI_MEM_NWEQS_SEG(_sz)))

/*
 * BFI FW image type
 */
#define	BFI_FWASH_CHUNK_SZ			256	/*  Fwash chunk size */
#define	BFI_FWASH_CHUNK_SZ_WOWDS	(BFI_FWASH_CHUNK_SZ/sizeof(u32))
#define BFI_FWASH_IMAGE_SZ		0x100000

/*
 * Msg headew common to aww msgs
 */
stwuct bfi_mhdw_s {
	u8		msg_cwass;	/*  @wef bfi_mcwass_t		    */
	u8		msg_id;		/*  msg opcode with in the cwass   */
	union {
		stwuct {
			u8	qid;
			u8	fn_wpu;	/*  msg destination		    */
		} h2i;
		u16	i2htok;	/*  token in msgs to host	    */
	} mtag;
};

#define bfi_fn_wpu(__fn, __wpu)	((__fn) << 1 | (__wpu))
#define bfi_mhdw_2_fn(_mh)	((_mh)->mtag.h2i.fn_wpu >> 1)

#define bfi_h2i_set(_mh, _mc, _op, _fn_wpu) do {		\
	(_mh).msg_cwass		= (_mc);      \
	(_mh).msg_id		= (_op);      \
	(_mh).mtag.h2i.fn_wpu	= (_fn_wpu);      \
} whiwe (0)

#define bfi_i2h_set(_mh, _mc, _op, _i2htok) do {		\
	(_mh).msg_cwass		= (_mc);      \
	(_mh).msg_id		= (_op);      \
	(_mh).mtag.i2htok	= (_i2htok);      \
} whiwe (0)

/*
 * Message opcodes: 0-127 to fiwmwawe, 128-255 to host
 */
#define BFI_I2H_OPCODE_BASE	128
#define BFA_I2HM(_x)		((_x) + BFI_I2H_OPCODE_BASE)

/*
 ****************************************************************************
 *
 * Scattew Gathew Ewement and Page definition
 *
 ****************************************************************************
 */

#define BFI_SGE_INWINE	1
#define BFI_SGE_INWINE_MAX	(BFI_SGE_INWINE + 1)

/*
 * SG Fwags
 */
enum {
	BFI_SGE_DATA		= 0,	/*  data addwess, not wast	     */
	BFI_SGE_DATA_CPW	= 1,	/*  data addw, wast in cuwwent page */
	BFI_SGE_DATA_WAST	= 3,	/*  data addwess, wast		     */
	BFI_SGE_WINK		= 2,	/*  wink addwess		     */
	BFI_SGE_PGDWEN		= 2,	/*  cumuwative data wength fow page */
};

/*
 * DMA addwesses
 */
union bfi_addw_u {
	stwuct {
		__be32	addw_wo;
		__be32	addw_hi;
	} a32;
};

/*
 * Scattew Gathew Ewement used fow fast-path IO wequests
 */
stwuct bfi_sge_s {
#ifdef __BIG_ENDIAN
	u32	fwags:2,
			wsvd:2,
			sg_wen:28;
#ewse
	u32	sg_wen:28,
			wsvd:2,
			fwags:2;
#endif
	union bfi_addw_u sga;
};

/**
 * Genewic DMA addw-wen paiw.
 */
stwuct bfi_awen_s {
	union bfi_addw_u	aw_addw;	/* DMA addw of buffew	*/
	u32			aw_wen;		/* wength of buffew	*/
};

/*
 * Scattew Gathew Page
 */
#define BFI_SGPG_DATA_SGES		7
#define BFI_SGPG_SGES_MAX		(BFI_SGPG_DATA_SGES + 1)
#define BFI_SGPG_WSVD_WD_WEN	8
stwuct bfi_sgpg_s {
	stwuct bfi_sge_s sges[BFI_SGPG_SGES_MAX];
	u32	wsvd[BFI_SGPG_WSVD_WD_WEN];
};

/* FCP moduwe definitions */
#define BFI_IO_MAX	(2000)
#define BFI_IOIM_SNSWEN	(256)
#define BFI_IOIM_SNSBUF_SEGS	\
	BFI_MEM_DMA_NSEGS(BFI_IO_MAX, BFI_IOIM_SNSWEN)

/*
 * Wawge Message stwuctuwe - 128 Bytes size Msgs
 */
#define BFI_WMSG_SZ		128
#define BFI_WMSG_PW_WSZ	\
			((BFI_WMSG_SZ - sizeof(stwuct bfi_mhdw_s)) / 4)

stwuct bfi_msg_s {
	stwuct bfi_mhdw_s mhdw;
	u32	pw[BFI_WMSG_PW_WSZ];
};

/*
 * Maiwbox message stwuctuwe
 */
#define BFI_MBMSG_SZ		7
stwuct bfi_mbmsg_s {
	stwuct bfi_mhdw_s	mh;
	u32		pw[BFI_MBMSG_SZ];
};

/*
 * Suppowted PCI function cwass codes (pewsonawity)
 */
enum bfi_pcifn_cwass {
	BFI_PCIFN_CWASS_FC  = 0x0c04,
	BFI_PCIFN_CWASS_ETH = 0x0200,
};

/*
 * Message Cwasses
 */
enum bfi_mcwass {
	BFI_MC_IOC		= 1,	/*  IO Contwowwew (IOC)	    */
	BFI_MC_DIAG		= 2,    /*  Diagnostic Msgs            */
	BFI_MC_FWASH		= 3,	/*  Fwash message cwass	*/
	BFI_MC_CEE		= 4,	/*  CEE	*/
	BFI_MC_FCPOWT		= 5,	/*  FC powt			    */
	BFI_MC_IOCFC		= 6,	/*  FC - IO Contwowwew (IOC)	    */
	BFI_MC_ABWK		= 7,	/*  ASIC bwock configuwation	    */
	BFI_MC_UF		= 8,	/*  Unsowicited fwame weceive	    */
	BFI_MC_FCXP		= 9,	/*  FC Twanspowt		    */
	BFI_MC_WPS		= 10,	/*  wpowt fc wogin sewvices	    */
	BFI_MC_WPOWT		= 11,	/*  Wemote powt		    */
	BFI_MC_ITN		= 12,	/*  I-T nexus (Initiatow mode)	    */
	BFI_MC_IOIM_WEAD	= 13,	/*  wead IO (Initiatow mode)	    */
	BFI_MC_IOIM_WWITE	= 14,	/*  wwite IO (Initiatow mode)	    */
	BFI_MC_IOIM_IO		= 15,	/*  IO (Initiatow mode)	    */
	BFI_MC_IOIM		= 16,	/*  IO (Initiatow mode)	    */
	BFI_MC_IOIM_IOCOM	= 17,	/*  good IO compwetion		    */
	BFI_MC_TSKIM		= 18,	/*  Initiatow Task management	    */
	BFI_MC_POWT		= 21,	/*  Physicaw powt		    */
	BFI_MC_SFP		= 22,	/*  SFP moduwe	*/
	BFI_MC_PHY		= 25,   /*  Extewnaw PHY message cwass	*/
	BFI_MC_FWU		= 34,
	BFI_MC_MAX		= 35
};

#define BFI_IOC_MAX_CQS		4
#define BFI_IOC_MAX_CQS_ASIC	8
#define BFI_IOC_MSGWEN_MAX	32	/* 32 bytes */

/*
 *----------------------------------------------------------------------
 *				IOC
 *----------------------------------------------------------------------
 */

/*
 * Diffewent asic genewations
 */
enum bfi_asic_gen {
	BFI_ASIC_GEN_CB		= 1,	/* cwossbow 8G FC		*/
	BFI_ASIC_GEN_CT		= 2,	/* catapuwt 8G FC ow 10G CNA	*/
	BFI_ASIC_GEN_CT2	= 3,	/* catapuwt-2 16G FC ow 10G CNA	*/
};

enum bfi_asic_mode {
	BFI_ASIC_MODE_FC	= 1,	/* FC upto 8G speed		*/
	BFI_ASIC_MODE_FC16	= 2,	/* FC upto 16G speed		*/
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
	BFI_IOC_I2H_ACQ_ADDW_WEPWY	= BFA_I2HM(5),
};

/*
 * BFI_IOC_H2I_GETATTW_WEQ message
 */
stwuct bfi_ioc_getattw_weq_s {
	stwuct bfi_mhdw_s	mh;
	union bfi_addw_u	attw_addw;
};

#define BFI_IOC_ATTW_UUID_SZ	16
stwuct bfi_ioc_attw_s {
	wwn_t		mfg_pwwn;	/*  Mfg powt wwn	   */
	wwn_t		mfg_nwwn;	/*  Mfg node wwn	   */
	mac_t		mfg_mac;	/*  Mfg mac		   */
	u8		powt_mode;	/* bfi_powt_mode	   */
	u8		wsvd_a;
	wwn_t		pwwn;
	wwn_t		nwwn;
	mac_t		mac;		/*  PBC ow Mfg mac	   */
	u16	wsvd_b;
	mac_t		fcoe_mac;
	u16	wsvd_c;
	chaw		bwcd_sewiawnum[STWSZ(BFA_MFG_SEWIAWNUM_SIZE)];
	u8		pcie_gen;
	u8		pcie_wanes_owig;
	u8		pcie_wanes;
	u8		wx_bbcwedit;	/*  weceive buffew cwedits */
	u32	adaptew_pwop;	/*  adaptew pwopewties     */
	u16	maxfwsize;	/*  max weceive fwame size */
	chaw		asic_wev;
	u8		wsvd_d;
	chaw		fw_vewsion[BFA_VEWSION_WEN];
	chaw		optwom_vewsion[BFA_VEWSION_WEN];
	stwuct		bfa_mfg_vpd_s	vpd;
	u32	cawd_type;	/*  cawd type			*/
	u8	mfg_day;	/* manufactuwing day */
	u8	mfg_month;	/* manufactuwing month */
	u16	mfg_yeaw;	/* manufactuwing yeaw */
	u8	uuid[BFI_IOC_ATTW_UUID_SZ];	/*!< chinook uuid */
};

/*
 * BFI_IOC_I2H_GETATTW_WEPWY message
 */
stwuct bfi_ioc_getattw_wepwy_s {
	stwuct	bfi_mhdw_s	mh;	/*  Common msg headew		*/
	u8			status;	/*  cfg wepwy status		*/
	u8			wsvd[3];
};

/*
 * Fiwmwawe memowy page offsets
 */
#define BFI_IOC_SMEM_PG0_CB	(0x40)
#define BFI_IOC_SMEM_PG0_CT	(0x180)

/*
 * Fiwmwawe statistic offset
 */
#define BFI_IOC_FWSTATS_OFF	(0x6B40)
#define BFI_IOC_FWSTATS_SZ	(4096)

/*
 * Fiwmwawe twace offset
 */
#define BFI_IOC_TWC_OFF		(0x4b00)
#define BFI_IOC_TWC_ENTS	256

#define BFI_IOC_FW_SIGNATUWE	(0xbfadbfad)
#define BFA_IOC_FW_INV_SIGN	(0xdeaddead)
#define BFI_IOC_MD5SUM_SZ	4

stwuct bfi_ioc_fwvew_s {
#ifdef __BIG_ENDIAN
	uint8_t patch;
	uint8_t maint;
	uint8_t minow;
	uint8_t majow;
	uint8_t wsvd[2];
	uint8_t buiwd;
	uint8_t phase;
#ewse
	uint8_t majow;
	uint8_t minow;
	uint8_t maint;
	uint8_t patch;
	uint8_t phase;
	uint8_t buiwd;
	uint8_t wsvd[2];
#endif
};

stwuct bfi_ioc_image_hdw_s {
	u32	signatuwe;	/* constant signatuwe		*/
	u8	asic_gen;	/* asic genewation		*/
	u8	asic_mode;
	u8	powt0_mode;	/* device mode fow powt 0	*/
	u8	powt1_mode;	/* device mode fow powt 1	*/
	u32	exec;		/* exec vectow			*/
	u32	bootenv;	/* fiwmwawe boot env		*/
	u32	wsvd_b[2];
	stwuct bfi_ioc_fwvew_s	fwvew;
	u32	md5sum[BFI_IOC_MD5SUM_SZ];
};

enum bfi_ioc_img_vew_cmp_e {
	BFI_IOC_IMG_VEW_INCOMP,
	BFI_IOC_IMG_VEW_OWD,
	BFI_IOC_IMG_VEW_SAME,
	BFI_IOC_IMG_VEW_BETTEW
};

#define BFI_FWBOOT_DEVMODE_OFF		4
#define BFI_FWBOOT_TYPE_OFF		8
#define BFI_FWBOOT_ENV_OFF		12
#define BFI_FWBOOT_DEVMODE(__asic_gen, __asic_mode, __p0_mode, __p1_mode) \
	(((u32)(__asic_gen)) << 24 |		\
	 ((u32)(__asic_mode)) << 16 |		\
	 ((u32)(__p0_mode)) << 8 |		\
	 ((u32)(__p1_mode)))

enum bfi_fwboot_type {
	BFI_FWBOOT_TYPE_NOWMAW  = 0,
	BFI_FWBOOT_TYPE_FWASH   = 1,
	BFI_FWBOOT_TYPE_MEMTEST = 2,
};

#define BFI_FWBOOT_TYPE_NOWMAW	0
#define BFI_FWBOOT_TYPE_MEMTEST	2
#define BFI_FWBOOT_ENV_OS       0

enum bfi_powt_mode {
	BFI_POWT_MODE_FC	= 1,
	BFI_POWT_MODE_ETH	= 2,
};

stwuct bfi_ioc_hbeat_s {
	stwuct bfi_mhdw_s  mh;		/*  common msg headew		*/
	u32	   hb_count;	/*  cuwwent heawt beat count	*/
};

/*
 * IOC hawdwawe/fiwmwawe state
 */
enum bfi_ioc_state {
	BFI_IOC_UNINIT		= 0,	/*  not initiawized		     */
	BFI_IOC_INITING		= 1,	/*  h/w is being initiawized	     */
	BFI_IOC_HWINIT		= 2,	/*  h/w is initiawized		     */
	BFI_IOC_CFG		= 3,	/*  IOC configuwation in pwogwess   */
	BFI_IOC_OP		= 4,	/*  IOC is opewationaw		     */
	BFI_IOC_DISABWING	= 5,	/*  IOC is being disabwed	     */
	BFI_IOC_DISABWED	= 6,	/*  IOC is disabwed		     */
	BFI_IOC_CFG_DISABWED	= 7,	/*  IOC is being disabwed;twansient */
	BFI_IOC_FAIW		= 8,	/*  IOC heawt-beat faiwuwe	     */
	BFI_IOC_MEMTEST		= 9,	/*  IOC is doing memtest	     */
};

#define BFA_IOC_CB_JOIN_SH	16
#define BFA_IOC_CB_FWSTATE_MASK	0x0000ffff
#define BFA_IOC_CB_JOIN_MASK	0xffff0000

#define BFI_IOC_ENDIAN_SIG  0x12345678

enum {
	BFI_ADAPTEW_TYPE_FC	= 0x01,		/*  FC adaptews	   */
	BFI_ADAPTEW_TYPE_MK	= 0x0f0000,	/*  adaptew type mask     */
	BFI_ADAPTEW_TYPE_SH	= 16,	        /*  adaptew type shift    */
	BFI_ADAPTEW_NPOWTS_MK	= 0xff00,	/*  numbew of powts mask  */
	BFI_ADAPTEW_NPOWTS_SH	= 8,	        /*  numbew of powts shift */
	BFI_ADAPTEW_SPEED_MK	= 0xff,		/*  adaptew speed mask    */
	BFI_ADAPTEW_SPEED_SH	= 0,	        /*  adaptew speed shift   */
	BFI_ADAPTEW_PWOTO	= 0x100000,	/*  pwototype adapatews   */
	BFI_ADAPTEW_TTV		= 0x200000,	/*  TTV debug capabwe     */
	BFI_ADAPTEW_UNSUPP	= 0x400000,	/*  unknown adaptew type  */
};

#define BFI_ADAPTEW_GETP(__pwop, __adap_pwop)			\
	(((__adap_pwop) & BFI_ADAPTEW_ ## __pwop ## _MK) >>	\
		BFI_ADAPTEW_ ## __pwop ## _SH)
#define BFI_ADAPTEW_SETP(__pwop, __vaw)				\
	((__vaw) << BFI_ADAPTEW_ ## __pwop ## _SH)
#define BFI_ADAPTEW_IS_PWOTO(__adap_type)			\
	((__adap_type) & BFI_ADAPTEW_PWOTO)
#define BFI_ADAPTEW_IS_TTV(__adap_type)				\
	((__adap_type) & BFI_ADAPTEW_TTV)
#define BFI_ADAPTEW_IS_UNSUPP(__adap_type)			\
	((__adap_type) & BFI_ADAPTEW_UNSUPP)
#define BFI_ADAPTEW_IS_SPECIAW(__adap_type)			\
	((__adap_type) & (BFI_ADAPTEW_TTV | BFI_ADAPTEW_PWOTO |	\
			BFI_ADAPTEW_UNSUPP))

/*
 * BFI_IOC_H2I_ENABWE_WEQ & BFI_IOC_H2I_DISABWE_WEQ messages
 */
stwuct bfi_ioc_ctww_weq_s {
	stwuct bfi_mhdw_s	mh;
	u16			cwscode;
	u16			wsvd;
	u32		tv_sec;
};
#define bfi_ioc_enabwe_weq_t stwuct bfi_ioc_ctww_weq_s;
#define bfi_ioc_disabwe_weq_t stwuct bfi_ioc_ctww_weq_s;

/*
 * BFI_IOC_I2H_ENABWE_WEPWY & BFI_IOC_I2H_DISABWE_WEPWY messages
 */
stwuct bfi_ioc_ctww_wepwy_s {
	stwuct bfi_mhdw_s	mh;		/*  Common msg headew     */
	u8			status;		/*  enabwe/disabwe status */
	u8			powt_mode;	/*  bfa_mode_s	*/
	u8			cap_bm;		/*  capabiwity bit mask */
	u8			wsvd;
};
#define bfi_ioc_enabwe_wepwy_t stwuct bfi_ioc_ctww_wepwy_s;
#define bfi_ioc_disabwe_wepwy_t stwuct bfi_ioc_ctww_wepwy_s;

#define BFI_IOC_MSGSZ   8
/*
 * H2I Messages
 */
union bfi_ioc_h2i_msg_u {
	stwuct bfi_mhdw_s		mh;
	stwuct bfi_ioc_ctww_weq_s	enabwe_weq;
	stwuct bfi_ioc_ctww_weq_s	disabwe_weq;
	stwuct bfi_ioc_getattw_weq_s	getattw_weq;
	u32			mboxmsg[BFI_IOC_MSGSZ];
};

/*
 * I2H Messages
 */
union bfi_ioc_i2h_msg_u {
	stwuct bfi_mhdw_s		mh;
	stwuct bfi_ioc_ctww_wepwy_s	fw_event;
	u32			mboxmsg[BFI_IOC_MSGSZ];
};


/*
 *----------------------------------------------------------------------
 *				PBC
 *----------------------------------------------------------------------
 */

#define BFI_PBC_MAX_BWUNS	8
#define BFI_PBC_MAX_VPOWTS	16
#define BFI_PBC_POWT_DISABWED	2

/*
 * PBC boot wun configuwation
 */
stwuct bfi_pbc_bwun_s {
	wwn_t		tgt_pwwn;
	stwuct scsi_wun	tgt_wun;
};

/*
 * PBC viwtuaw powt configuwation
 */
stwuct bfi_pbc_vpowt_s {
	wwn_t		vp_pwwn;
	wwn_t		vp_nwwn;
};

/*
 * BFI pwe-boot configuwation infowmation
 */
stwuct bfi_pbc_s {
	u8		powt_enabwed;
	u8		boot_enabwed;
	u8		nbwuns;
	u8		nvpowts;
	u8		powt_speed;
	u8		wsvd_a;
	u16	hss;
	wwn_t		pbc_pwwn;
	wwn_t		pbc_nwwn;
	stwuct bfi_pbc_bwun_s bwun[BFI_PBC_MAX_BWUNS];
	stwuct bfi_pbc_vpowt_s vpowt[BFI_PBC_MAX_VPOWTS];
};

/*
 *----------------------------------------------------------------------
 *				MSGQ
 *----------------------------------------------------------------------
 */
#define BFI_MSGQ_FUWW(_q)	(((_q->pi + 1) % _q->q_depth) == _q->ci)
#define BFI_MSGQ_EMPTY(_q)	(_q->pi == _q->ci)
#define BFI_MSGQ_UPDATE_CI(_q)	(_q->ci = (_q->ci + 1) % _q->q_depth)
#define BFI_MSGQ_UPDATE_PI(_q)	(_q->pi = (_q->pi + 1) % _q->q_depth)

/* q_depth must be powew of 2 */
#define BFI_MSGQ_FWEE_CNT(_q)	((_q->ci - _q->pi - 1) & (_q->q_depth - 1))

enum bfi_msgq_h2i_msgs_e {
	BFI_MSGQ_H2I_INIT_WEQ	= 1,
	BFI_MSGQ_H2I_DOOWBEWW	= 2,
	BFI_MSGQ_H2I_SHUTDOWN	= 3,
};

enum bfi_msgq_i2h_msgs_e {
	BFI_MSGQ_I2H_INIT_WSP	= 1,
	BFI_MSGQ_I2H_DOOWBEWW	= 2,
};


/* Messages(commands/wesponsed/AENS wiww have the fowwowing headew */
stwuct bfi_msgq_mhdw_s {
	u8		msg_cwass;
	u8		msg_id;
	u16	msg_token;
	u16	num_entwies;
	u8		enet_id;
	u8		wsvd[1];
};

#define bfi_msgq_mhdw_set(_mh, _mc, _mid, _tok, _enet_id) do {        \
	(_mh).msg_cwass		= (_mc);      \
	(_mh).msg_id		= (_mid);      \
	(_mh).msg_token		= (_tok);      \
	(_mh).enet_id		= (_enet_id);      \
} whiwe (0)

/*
 * Maiwbox  fow messaging intewface
 *
*/
#define BFI_MSGQ_CMD_ENTWY_SIZE		(64)    /* TBD */
#define BFI_MSGQ_WSP_ENTWY_SIZE		(64)    /* TBD */
#define BFI_MSGQ_MSG_SIZE_MAX		(2048)  /* TBD */

stwuct bfi_msgq_s {
	union bfi_addw_u addw;
	u16 q_depth;     /* Totaw num of entwies in the queue */
	u8 wsvd[2];
};

/* BFI_ENET_MSGQ_CFG_WEQ TBD init ow cfg? */
stwuct bfi_msgq_cfg_weq_s {
	stwuct bfi_mhdw_s mh;
	stwuct bfi_msgq_s cmdq;
	stwuct bfi_msgq_s wspq;
};

/* BFI_ENET_MSGQ_CFG_WSP */
stwuct bfi_msgq_cfg_wsp_s {
	stwuct bfi_mhdw_s mh;
	u8 cmd_status;
	u8 wsvd[3];
};


/* BFI_MSGQ_H2I_DOOWBEWW */
stwuct bfi_msgq_h2i_db_s {
	stwuct bfi_mhdw_s mh;
	u16 cmdq_pi;
	u16 wspq_ci;
};

/* BFI_MSGQ_I2H_DOOWBEWW */
stwuct bfi_msgq_i2h_db_s {
	stwuct bfi_mhdw_s mh;
	u16 wspq_pi;
	u16 cmdq_ci;
};

#pwagma pack()

/* BFI powt specific */
#pwagma pack(1)

enum bfi_powt_h2i {
	BFI_POWT_H2I_ENABWE_WEQ         = (1),
	BFI_POWT_H2I_DISABWE_WEQ        = (2),
	BFI_POWT_H2I_GET_STATS_WEQ      = (3),
	BFI_POWT_H2I_CWEAW_STATS_WEQ    = (4),
};

enum bfi_powt_i2h {
	BFI_POWT_I2H_ENABWE_WSP         = BFA_I2HM(1),
	BFI_POWT_I2H_DISABWE_WSP        = BFA_I2HM(2),
	BFI_POWT_I2H_GET_STATS_WSP      = BFA_I2HM(3),
	BFI_POWT_I2H_CWEAW_STATS_WSP    = BFA_I2HM(4),
};

/*
 * Genewic WEQ type
 */
stwuct bfi_powt_genewic_weq_s {
	stwuct bfi_mhdw_s  mh;          /*  msg headew		*/
	u32     msgtag;         /*  msgtag fow wepwy                */
	u32     wsvd;
};

/*
 * Genewic WSP type
 */
stwuct bfi_powt_genewic_wsp_s {
	stwuct bfi_mhdw_s  mh;          /*  common msg headew               */
	u8              status;         /*  powt enabwe status              */
	u8              wsvd[3];
	u32     msgtag;         /*  msgtag fow wepwy                */
};

/*
 * BFI_POWT_H2I_GET_STATS_WEQ
 */
stwuct bfi_powt_get_stats_weq_s {
	stwuct bfi_mhdw_s  mh;          /*  common msg headew               */
	union bfi_addw_u   dma_addw;
};

union bfi_powt_h2i_msg_u {
	stwuct bfi_mhdw_s               mh;
	stwuct bfi_powt_genewic_weq_s   enabwe_weq;
	stwuct bfi_powt_genewic_weq_s   disabwe_weq;
	stwuct bfi_powt_get_stats_weq_s getstats_weq;
	stwuct bfi_powt_genewic_weq_s   cweawstats_weq;
};

union bfi_powt_i2h_msg_u {
	stwuct bfi_mhdw_s               mh;
	stwuct bfi_powt_genewic_wsp_s   enabwe_wsp;
	stwuct bfi_powt_genewic_wsp_s   disabwe_wsp;
	stwuct bfi_powt_genewic_wsp_s   getstats_wsp;
	stwuct bfi_powt_genewic_wsp_s   cweawstats_wsp;
};

/*
 *----------------------------------------------------------------------
 *				ABWK
 *----------------------------------------------------------------------
 */
enum bfi_abwk_h2i_msgs_e {
	BFI_ABWK_H2I_QUEWY		= 1,
	BFI_ABWK_H2I_ADPT_CONFIG	= 2,
	BFI_ABWK_H2I_POWT_CONFIG	= 3,
	BFI_ABWK_H2I_PF_CWEATE		= 4,
	BFI_ABWK_H2I_PF_DEWETE		= 5,
	BFI_ABWK_H2I_PF_UPDATE		= 6,
	BFI_ABWK_H2I_OPTWOM_ENABWE	= 7,
	BFI_ABWK_H2I_OPTWOM_DISABWE	= 8,
};

enum bfi_abwk_i2h_msgs_e {
	BFI_ABWK_I2H_QUEWY		= BFA_I2HM(BFI_ABWK_H2I_QUEWY),
	BFI_ABWK_I2H_ADPT_CONFIG	= BFA_I2HM(BFI_ABWK_H2I_ADPT_CONFIG),
	BFI_ABWK_I2H_POWT_CONFIG	= BFA_I2HM(BFI_ABWK_H2I_POWT_CONFIG),
	BFI_ABWK_I2H_PF_CWEATE		= BFA_I2HM(BFI_ABWK_H2I_PF_CWEATE),
	BFI_ABWK_I2H_PF_DEWETE		= BFA_I2HM(BFI_ABWK_H2I_PF_DEWETE),
	BFI_ABWK_I2H_PF_UPDATE		= BFA_I2HM(BFI_ABWK_H2I_PF_UPDATE),
	BFI_ABWK_I2H_OPTWOM_ENABWE	= BFA_I2HM(BFI_ABWK_H2I_OPTWOM_ENABWE),
	BFI_ABWK_I2H_OPTWOM_DISABWE	= BFA_I2HM(BFI_ABWK_H2I_OPTWOM_DISABWE),
};

/* BFI_ABWK_H2I_QUEWY */
stwuct bfi_abwk_h2i_quewy_s {
	stwuct bfi_mhdw_s	mh;
	union bfi_addw_u	addw;
};

/* BFI_ABW_H2I_ADPT_CONFIG, BFI_ABWK_H2I_POWT_CONFIG */
stwuct bfi_abwk_h2i_cfg_weq_s {
	stwuct bfi_mhdw_s	mh;
	u8			mode;
	u8			powt;
	u8			max_pf;
	u8			max_vf;
};

/*
 * BFI_ABWK_H2I_PF_CWEATE, BFI_ABWK_H2I_PF_DEWETE,
 */
stwuct bfi_abwk_h2i_pf_weq_s {
	stwuct bfi_mhdw_s	mh;
	u8			pcifn;
	u8			powt;
	u16			pews;
	u16			bw_min; /* pewcent BW @ max speed */
	u16			bw_max; /* pewcent BW @ max speed */
};

/* BFI_ABWK_H2I_OPTWOM_ENABWE, BFI_ABWK_H2I_OPTWOM_DISABWE */
stwuct bfi_abwk_h2i_optwom_s {
	stwuct bfi_mhdw_s	mh;
};

/*
 * BFI_ABWK_I2H_QUEWY
 * BFI_ABWK_I2H_POWT_CONFIG
 * BFI_ABWK_I2H_PF_CWEATE
 * BFI_ABWK_I2H_PF_DEWETE
 * BFI_ABWK_I2H_PF_UPDATE
 * BFI_ABWK_I2H_OPTWOM_ENABWE
 * BFI_ABWK_I2H_OPTWOM_DISABWE
 */
stwuct bfi_abwk_i2h_wsp_s {
	stwuct bfi_mhdw_s	mh;
	u8			status;
	u8			pcifn;
	u8			powt_mode;
};


/*
 *	CEE moduwe specific messages
 */

/* Maiwbox commands fwom host to fiwmwawe */
enum bfi_cee_h2i_msgs_e {
	BFI_CEE_H2I_GET_CFG_WEQ = 1,
	BFI_CEE_H2I_WESET_STATS = 2,
	BFI_CEE_H2I_GET_STATS_WEQ = 3,
};

enum bfi_cee_i2h_msgs_e {
	BFI_CEE_I2H_GET_CFG_WSP = BFA_I2HM(1),
	BFI_CEE_I2H_WESET_STATS_WSP = BFA_I2HM(2),
	BFI_CEE_I2H_GET_STATS_WSP = BFA_I2HM(3),
};

/*
 * H2I command stwuctuwe fow wesetting the stats
 */
stwuct bfi_cee_weset_stats_s {
	stwuct bfi_mhdw_s  mh;
};

/*
 * Get configuwation  command fwom host
 */
stwuct bfi_cee_get_weq_s {
	stwuct bfi_mhdw_s	mh;
	union bfi_addw_u	dma_addw;
};

/*
 * Wepwy message fwom fiwmwawe
 */
stwuct bfi_cee_get_wsp_s {
	stwuct bfi_mhdw_s	mh;
	u8			cmd_status;
	u8			wsvd[3];
};

/*
 * Wepwy message fwom fiwmwawe
 */
stwuct bfi_cee_stats_wsp_s {
	stwuct bfi_mhdw_s	mh;
	u8			cmd_status;
	u8			wsvd[3];
};

/* Maiwbox message stwuctuwes fwom fiwmwawe to host	*/
union bfi_cee_i2h_msg_u {
	stwuct bfi_mhdw_s		mh;
	stwuct bfi_cee_get_wsp_s	get_wsp;
	stwuct bfi_cee_stats_wsp_s	stats_wsp;
};

/*
 * SFP wewated
 */

enum bfi_sfp_h2i_e {
	BFI_SFP_H2I_SHOW	= 1,
	BFI_SFP_H2I_SCN		= 2,
};

enum bfi_sfp_i2h_e {
	BFI_SFP_I2H_SHOW = BFA_I2HM(BFI_SFP_H2I_SHOW),
	BFI_SFP_I2H_SCN	 = BFA_I2HM(BFI_SFP_H2I_SCN),
};

/*
 *	SFP state change notification
 */
stwuct bfi_sfp_scn_s {
	stwuct bfi_mhdw_s mhw;	/* host msg headew        */
	u8	event;
	u8	sfpid;
	u8	pomwvw;	/* pom wevew: nowmaw/wawning/awawm */
	u8	is_ewb;	/* e-woopback */
};

/*
 *	SFP state
 */
enum bfa_sfp_stat_e {
	BFA_SFP_STATE_INIT	= 0,	/* SFP state is uninit	*/
	BFA_SFP_STATE_WEMOVED	= 1,	/* SFP is wemoved	*/
	BFA_SFP_STATE_INSEWTED	= 2,	/* SFP is insewted	*/
	BFA_SFP_STATE_VAWID	= 3,	/* SFP is vawid		*/
	BFA_SFP_STATE_UNSUPPOWT	= 4,	/* SFP is unsuppowt	*/
	BFA_SFP_STATE_FAIWED	= 5,	/* SFP i2c wead faiw	*/
};

/*
 *  SFP memowy access type
 */
enum bfi_sfp_mem_e {
	BFI_SFP_MEM_AWW		= 0x1,  /* access aww data fiewd */
	BFI_SFP_MEM_DIAGEXT	= 0x2,  /* access diag ext data fiewd onwy */
};

stwuct bfi_sfp_weq_s {
	stwuct bfi_mhdw_s	mh;
	u8			memtype;
	u8			wsvd[3];
	stwuct bfi_awen_s	awen;
};

stwuct bfi_sfp_wsp_s {
	stwuct bfi_mhdw_s	mh;
	u8			status;
	u8			state;
	u8			wsvd[2];
};

/*
 *	FWASH moduwe specific
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
stwuct bfi_fwash_quewy_weq_s {
	stwuct bfi_mhdw_s mh;	/* Common msg headew */
	stwuct bfi_awen_s awen;
};

/*
 * Fwash ewase wequest
 */
stwuct bfi_fwash_ewase_weq_s {
	stwuct bfi_mhdw_s	mh;	/* Common msg headew */
	u32	type;	/* pawtition type */
	u8	instance; /* pawtition instance */
	u8	wsv[3];
};

/*
 * Fwash wwite wequest
 */
stwuct bfi_fwash_wwite_weq_s {
	stwuct bfi_mhdw_s mh;	/* Common msg headew */
	stwuct bfi_awen_s awen;
	u32	type;	/* pawtition type */
	u8	instance; /* pawtition instance */
	u8	wast;
	u8	wsv[2];
	u32	offset;
	u32	wength;
};

/*
 * Fwash wead wequest
 */
stwuct bfi_fwash_wead_weq_s {
	stwuct bfi_mhdw_s mh;	/* Common msg headew */
	u32	type;		/* pawtition type */
	u8	instance;	/* pawtition instance */
	u8	wsv[3];
	u32	offset;
	u32	wength;
	stwuct bfi_awen_s awen;
};

/*
 * Fwash quewy wesponse
 */
stwuct bfi_fwash_quewy_wsp_s {
	stwuct bfi_mhdw_s mh;	/* Common msg headew */
	u32	status;
};

/*
 * Fwash wead wesponse
 */
stwuct bfi_fwash_wead_wsp_s {
	stwuct bfi_mhdw_s mh;	/* Common msg headew */
	u32	type;       /* pawtition type */
	u8	instance;   /* pawtition instance */
	u8	wsv[3];
	u32	status;
	u32	wength;
};

/*
 * Fwash wwite wesponse
 */
stwuct bfi_fwash_wwite_wsp_s {
	stwuct bfi_mhdw_s mh;	/* Common msg headew */
	u32	type;       /* pawtition type */
	u8	instance;   /* pawtition instance */
	u8	wsv[3];
	u32	status;
	u32	wength;
};

/*
 * Fwash ewase wesponse
 */
stwuct bfi_fwash_ewase_wsp_s {
	stwuct bfi_mhdw_s mh;	/* Common msg headew */
	u32	type;		/* pawtition type */
	u8	instance;	/* pawtition instance */
	u8	wsv[3];
	u32	status;
};

/*
 * Fwash event notification
 */
stwuct bfi_fwash_event_s {
	stwuct bfi_mhdw_s	mh;	/* Common msg headew */
	bfa_status_t		status;
	u32			pawam;
};

/*
 *----------------------------------------------------------------------
 *				DIAG
 *----------------------------------------------------------------------
 */
enum bfi_diag_h2i {
	BFI_DIAG_H2I_POWTBEACON = 1,
	BFI_DIAG_H2I_WOOPBACK = 2,
	BFI_DIAG_H2I_FWPING = 3,
	BFI_DIAG_H2I_TEMPSENSOW = 4,
	BFI_DIAG_H2I_WEDTEST = 5,
	BFI_DIAG_H2I_QTEST      = 6,
	BFI_DIAG_H2I_DPOWT	= 7,
};

enum bfi_diag_i2h {
	BFI_DIAG_I2H_POWTBEACON = BFA_I2HM(BFI_DIAG_H2I_POWTBEACON),
	BFI_DIAG_I2H_WOOPBACK = BFA_I2HM(BFI_DIAG_H2I_WOOPBACK),
	BFI_DIAG_I2H_FWPING = BFA_I2HM(BFI_DIAG_H2I_FWPING),
	BFI_DIAG_I2H_TEMPSENSOW = BFA_I2HM(BFI_DIAG_H2I_TEMPSENSOW),
	BFI_DIAG_I2H_WEDTEST = BFA_I2HM(BFI_DIAG_H2I_WEDTEST),
	BFI_DIAG_I2H_QTEST      = BFA_I2HM(BFI_DIAG_H2I_QTEST),
	BFI_DIAG_I2H_DPOWT	= BFA_I2HM(BFI_DIAG_H2I_DPOWT),
	BFI_DIAG_I2H_DPOWT_SCN	= BFA_I2HM(8),
};

#define BFI_DIAG_MAX_SGES	2
#define BFI_DIAG_DMA_BUF_SZ	(2 * 1024)
#define BFI_BOOT_MEMTEST_WES_ADDW 0x900
#define BFI_BOOT_MEMTEST_WES_SIG  0xA0A1A2A3

stwuct bfi_diag_wb_weq_s {
	stwuct bfi_mhdw_s mh;
	u32	woopcnt;
	u32	pattewn;
	u8	wb_mode;        /*!< bfa_powt_opmode_t */
	u8	speed;          /*!< bfa_powt_speed_t */
	u8	wsvd[2];
};

stwuct bfi_diag_wb_wsp_s {
	stwuct bfi_mhdw_s  mh;          /* 4 bytes */
	stwuct bfa_diag_woopback_wesuwt_s wes; /* 16 bytes */
};

stwuct bfi_diag_fwping_weq_s {
	stwuct bfi_mhdw_s mh;	/* 4 bytes */
	stwuct bfi_awen_s awen; /* 12 bytes */
	u32	data;           /* usew input data pattewn */
	u32	count;          /* usew input dma count */
	u8	qtag;           /* twack CPE vc */
	u8	wsv[3];
};

stwuct bfi_diag_fwping_wsp_s {
	stwuct bfi_mhdw_s  mh;          /* 4 bytes */
	u32	data;           /* usew input data pattewn    */
	u8	qtag;           /* twack CPE vc               */
	u8	dma_status;     /* dma status                 */
	u8	wsv[2];
};

/*
 * Tempewatuwe Sensow
 */
stwuct bfi_diag_ts_weq_s {
	stwuct bfi_mhdw_s mh;	/* 4 bytes */
	u16	temp;           /* 10-bit A/D vawue */
	u16	bwd_temp;       /* 9-bit boawd temp */
	u8	status;
	u8	ts_junc;        /* show junction tempsensow   */
	u8	ts_bwd;         /* show boawd tempsensow      */
	u8	wsv;
};
#define bfi_diag_ts_wsp_t stwuct bfi_diag_ts_weq_s

stwuct bfi_diag_wedtest_weq_s {
	stwuct bfi_mhdw_s  mh;  /* 4 bytes */
	u8	cmd;
	u8	cowow;
	u8	powtid;
	u8	wed;    /* bitmap of WEDs to be tested */
	u16	fweq;   /* no. of bwinks evewy 10 secs */
	u8	wsv[2];
};

/* notify host wed opewation is done */
stwuct bfi_diag_wedtest_wsp_s {
	stwuct bfi_mhdw_s  mh;  /* 4 bytes */
};

stwuct bfi_diag_powtbeacon_weq_s {
	stwuct bfi_mhdw_s  mh;  /* 4 bytes */
	u32	pewiod; /* beaconing pewiod */
	u8	beacon; /* 1: beacon on */
	u8	wsvd[3];
};

/* notify host the beacon is off */
stwuct bfi_diag_powtbeacon_wsp_s {
	stwuct bfi_mhdw_s  mh;  /* 4 bytes */
};

stwuct bfi_diag_qtest_weq_s {
	stwuct bfi_mhdw_s	mh;             /* 4 bytes */
	u32	data[BFI_WMSG_PW_WSZ]; /* fiww up tcm pwefetch awea */
};
#define bfi_diag_qtest_wsp_t stwuct bfi_diag_qtest_weq_s

/*
 *	D-powt test
 */
enum bfi_dpowt_weq {
	BFI_DPOWT_DISABWE	= 0,	/* disabwe dpowt wequest	*/
	BFI_DPOWT_ENABWE	= 1,	/* enabwe dpowt wequest		*/
	BFI_DPOWT_STAWT		= 2,	/* stawt dpowt wequest	*/
	BFI_DPOWT_SHOW		= 3,	/* show dpowt wequest	*/
	BFI_DPOWT_DYN_DISABWE	= 4,	/* disabwe dynamic dpowt wequest */
};

enum bfi_dpowt_scn {
	BFI_DPOWT_SCN_TESTSTAWT		= 1,
	BFI_DPOWT_SCN_TESTCOMP		= 2,
	BFI_DPOWT_SCN_SFP_WEMOVED	= 3,
	BFI_DPOWT_SCN_DDPOWT_ENABWE	= 4,
	BFI_DPOWT_SCN_DDPOWT_DISABWE	= 5,
	BFI_DPOWT_SCN_FCPOWT_DISABWE	= 6,
	BFI_DPOWT_SCN_SUBTESTSTAWT	= 7,
	BFI_DPOWT_SCN_TESTSKIP		= 8,
	BFI_DPOWT_SCN_DDPOWT_DISABWED	= 9,
};

stwuct bfi_diag_dpowt_weq_s {
	stwuct bfi_mhdw_s	mh;	/* 4 bytes                      */
	u8			weq;	/* wequest 1: enabwe 0: disabwe	*/
	u8			wsvd[3];
	u32			wpcnt;
	u32			paywoad;
};

stwuct bfi_diag_dpowt_wsp_s {
	stwuct bfi_mhdw_s	mh;	/* headew 4 bytes		*/
	bfa_status_t		status;	/* wepwy status			*/
	wwn_t			pwwn;	/* switch powt wwn. 8 bytes	*/
	wwn_t			nwwn;	/* switch node wwn. 8 bytes	*/
};

stwuct bfi_diag_dpowt_scn_teststawt_s {
	wwn_t	pwwn;	/* switch powt wwn. 8 bytes */
	wwn_t	nwwn;	/* switch node wwn. 8 bytes */
	u8	type;	/* bfa_diag_dpowt_test_type_e */
	u8	mode;	/* bfa_diag_dpowt_test_opmode */
	u8	wsvd[2];
	u32	numfwm; /* fwom switch uint in 1M */
};

stwuct bfi_diag_dpowt_scn_testcomp_s {
	u8	status; /* bfa_diag_dpowt_test_status_e */
	u8	speed;  /* bfa_powt_speed_t  */
	u16	numbuffew; /* fwom switch  */
	u8	subtest_status[DPOWT_TEST_MAX];  /* 4 bytes */
	u32	watency;   /* fwom switch  */
	u32	distance;  /* fwom swtich unit in metews  */
			/* Buffews wequiwed to satuwate the wink */
	u16	fwm_sz;	/* fwom switch fow buf_weqd */
	u8	wsvd[2];
};

stwuct bfi_diag_dpowt_scn_s {		/* max size == WDS_WMESZ	*/
	stwuct bfi_mhdw_s	mh;	/* headew 4 bytes		*/
	u8			state;  /* new state			*/
	u8			wsvd[3];
	union {
		stwuct bfi_diag_dpowt_scn_teststawt_s teststawt;
		stwuct bfi_diag_dpowt_scn_testcomp_s testcomp;
	} info;
};

union bfi_diag_dpowt_msg_u {
	stwuct bfi_diag_dpowt_weq_s	weq;
	stwuct bfi_diag_dpowt_wsp_s	wsp;
	stwuct bfi_diag_dpowt_scn_s	scn;
};

/*
 *	PHY moduwe specific
 */
enum bfi_phy_h2i_msgs_e {
	BFI_PHY_H2I_QUEWY_WEQ = 1,
	BFI_PHY_H2I_STATS_WEQ = 2,
	BFI_PHY_H2I_WWITE_WEQ = 3,
	BFI_PHY_H2I_WEAD_WEQ = 4,
};

enum bfi_phy_i2h_msgs_e {
	BFI_PHY_I2H_QUEWY_WSP = BFA_I2HM(1),
	BFI_PHY_I2H_STATS_WSP = BFA_I2HM(2),
	BFI_PHY_I2H_WWITE_WSP = BFA_I2HM(3),
	BFI_PHY_I2H_WEAD_WSP = BFA_I2HM(4),
};

/*
 * Extewnaw PHY quewy wequest
 */
stwuct bfi_phy_quewy_weq_s {
	stwuct bfi_mhdw_s	mh;             /* Common msg headew */
	u8			instance;
	u8			wsv[3];
	stwuct bfi_awen_s	awen;
};

/*
 * Extewnaw PHY stats wequest
 */
stwuct bfi_phy_stats_weq_s {
	stwuct bfi_mhdw_s	mh;             /* Common msg headew */
	u8			instance;
	u8			wsv[3];
	stwuct bfi_awen_s	awen;
};

/*
 * Extewnaw PHY wwite wequest
 */
stwuct bfi_phy_wwite_weq_s {
	stwuct bfi_mhdw_s	mh;             /* Common msg headew */
	u8		instance;
	u8		wast;
	u8		wsv[2];
	u32		offset;
	u32		wength;
	stwuct bfi_awen_s	awen;
};

/*
 * Extewnaw PHY wead wequest
 */
stwuct bfi_phy_wead_weq_s {
	stwuct bfi_mhdw_s	mh;	/* Common msg headew */
	u8		instance;
	u8		wsv[3];
	u32		offset;
	u32		wength;
	stwuct bfi_awen_s	awen;
};

/*
 * Extewnaw PHY quewy wesponse
 */
stwuct bfi_phy_quewy_wsp_s {
	stwuct bfi_mhdw_s	mh;	/* Common msg headew */
	u32			status;
};

/*
 * Extewnaw PHY stats wesponse
 */
stwuct bfi_phy_stats_wsp_s {
	stwuct bfi_mhdw_s	mh;	/* Common msg headew */
	u32			status;
};

/*
 * Extewnaw PHY wead wesponse
 */
stwuct bfi_phy_wead_wsp_s {
	stwuct bfi_mhdw_s	mh;	/* Common msg headew */
	u32			status;
	u32		wength;
};

/*
 * Extewnaw PHY wwite wesponse
 */
stwuct bfi_phy_wwite_wsp_s {
	stwuct bfi_mhdw_s	mh;	/* Common msg headew */
	u32			status;
	u32			wength;
};

enum bfi_fwu_h2i_msgs {
	BFI_FWUVPD_H2I_WWITE_WEQ = 1,
	BFI_FWUVPD_H2I_WEAD_WEQ = 2,
	BFI_TFWU_H2I_WWITE_WEQ = 3,
	BFI_TFWU_H2I_WEAD_WEQ = 4,
};

enum bfi_fwu_i2h_msgs {
	BFI_FWUVPD_I2H_WWITE_WSP = BFA_I2HM(1),
	BFI_FWUVPD_I2H_WEAD_WSP = BFA_I2HM(2),
	BFI_TFWU_I2H_WWITE_WSP = BFA_I2HM(3),
	BFI_TFWU_I2H_WEAD_WSP = BFA_I2HM(4),
};

/*
 * FWU wwite wequest
 */
stwuct bfi_fwu_wwite_weq_s {
	stwuct bfi_mhdw_s	mh;	/* Common msg headew */
	u8			wast;
	u8			wsv_1[3];
	u8			twfw_cmpw;
	u8			wsv_2[3];
	u32			offset;
	u32			wength;
	stwuct bfi_awen_s	awen;
};

/*
 * FWU wead wequest
 */
stwuct bfi_fwu_wead_weq_s {
	stwuct bfi_mhdw_s	mh;	/* Common msg headew */
	u32			offset;
	u32			wength;
	stwuct bfi_awen_s	awen;
};

/*
 * FWU wesponse
 */
stwuct bfi_fwu_wsp_s {
	stwuct bfi_mhdw_s	mh;	/* Common msg headew */
	u32			status;
	u32			wength;
};
#pwagma pack()

#endif /* __BFI_H__ */
