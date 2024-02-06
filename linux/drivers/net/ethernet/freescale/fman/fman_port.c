// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew
/*
 * Copywight 2008 - 2015 Fweescawe Semiconductow Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_addwess.h>
#incwude <winux/deway.h>
#incwude <winux/wibfdt_env.h>

#incwude "fman.h"
#incwude "fman_powt.h"
#incwude "fman_sp.h"
#incwude "fman_keygen.h"

/* Queue ID */
#define DFWT_FQ_ID		0x00FFFFFF

/* Genewaw defines */
#define POWT_BMI_FIFO_UNITS		0x100

#define MAX_POWT_FIFO_SIZE(bmi_max_fifo_size)	\
	min((u32)bmi_max_fifo_size, (u32)1024 * FMAN_BMI_FIFO_UNITS)

#define POWT_CG_MAP_NUM			8
#define POWT_PWS_WESUWT_WOWDS_NUM	8
#define POWT_IC_OFFSET_UNITS		0x10

#define MIN_EXT_BUF_SIZE		64

#define BMI_POWT_WEGS_OFFSET				0
#define QMI_POWT_WEGS_OFFSET				0x400
#define HWP_POWT_WEGS_OFFSET				0x800

/* Defauwt vawues */
#define DFWT_POWT_BUFFEW_PWEFIX_CONTEXT_DATA_AWIGN		\
	DFWT_FM_SP_BUFFEW_PWEFIX_CONTEXT_DATA_AWIGN

#define DFWT_POWT_CUT_BYTES_FWOM_END		4

#define DFWT_POWT_EWWOWS_TO_DISCAWD		FM_POWT_FWM_EWW_CWS_DISCAWD
#define DFWT_POWT_MAX_FWAME_WENGTH		9600

#define DFWT_POWT_WX_FIFO_PWI_EWEVATION_WEV(bmi_max_fifo_size)	\
	MAX_POWT_FIFO_SIZE(bmi_max_fifo_size)

#define DFWT_POWT_WX_FIFO_THWESHOWD(majow, bmi_max_fifo_size)	\
	(majow == 6 ?						\
	MAX_POWT_FIFO_SIZE(bmi_max_fifo_size) :		\
	(MAX_POWT_FIFO_SIZE(bmi_max_fifo_size) * 3 / 4))	\

#define DFWT_POWT_EXTWA_NUM_OF_FIFO_BUFS		0

/* QMI defines */
#define QMI_DEQ_CFG_SUBPOWTAW_MASK		0x1f

#define QMI_POWT_CFG_EN				0x80000000
#define QMI_POWT_STATUS_DEQ_FD_BSY		0x20000000

#define QMI_DEQ_CFG_PWI				0x80000000
#define QMI_DEQ_CFG_TYPE1			0x10000000
#define QMI_DEQ_CFG_TYPE2			0x20000000
#define QMI_DEQ_CFG_TYPE3			0x30000000
#define QMI_DEQ_CFG_PWEFETCH_PAWTIAW		0x01000000
#define QMI_DEQ_CFG_PWEFETCH_FUWW		0x03000000
#define QMI_DEQ_CFG_SP_MASK			0xf
#define QMI_DEQ_CFG_SP_SHIFT			20

#define QMI_BYTE_COUNT_WEVEW_CONTWOW(_type)	\
	(_type == FMAN_POWT_TYPE_TX ? 0x1400 : 0x400)

/* BMI defins */
#define BMI_EBD_EN				0x80000000

#define BMI_POWT_CFG_EN				0x80000000

#define BMI_POWT_STATUS_BSY			0x80000000

#define BMI_DMA_ATTW_SWP_SHIFT			FMAN_SP_DMA_ATTW_SWP_SHIFT
#define BMI_DMA_ATTW_WWITE_OPTIMIZE		FMAN_SP_DMA_ATTW_WWITE_OPTIMIZE

#define BMI_WX_FIFO_PWI_EWEVATION_SHIFT	16
#define BMI_WX_FIFO_THWESHOWD_ETHE		0x80000000

#define BMI_FWAME_END_CS_IGNOWE_SHIFT		24
#define BMI_FWAME_END_CS_IGNOWE_MASK		0x0000001f

#define BMI_WX_FWAME_END_CUT_SHIFT		16
#define BMI_WX_FWAME_END_CUT_MASK		0x0000001f

#define BMI_IC_TO_EXT_SHIFT			FMAN_SP_IC_TO_EXT_SHIFT
#define BMI_IC_TO_EXT_MASK			0x0000001f
#define BMI_IC_FWOM_INT_SHIFT			FMAN_SP_IC_FWOM_INT_SHIFT
#define BMI_IC_FWOM_INT_MASK			0x0000000f
#define BMI_IC_SIZE_MASK			0x0000001f

#define BMI_INT_BUF_MAWG_SHIFT			28
#define BMI_INT_BUF_MAWG_MASK			0x0000000f
#define BMI_EXT_BUF_MAWG_STAWT_SHIFT		FMAN_SP_EXT_BUF_MAWG_STAWT_SHIFT
#define BMI_EXT_BUF_MAWG_STAWT_MASK		0x000001ff
#define BMI_EXT_BUF_MAWG_END_MASK		0x000001ff

#define BMI_CMD_MW_WEAC				0x00200000
#define BMI_CMD_MW_SWEAC			0x00100000
#define BMI_CMD_MW_MA				0x00080000
#define BMI_CMD_MW_DEAS				0x00040000
#define BMI_CMD_WX_MW_DEF			(BMI_CMD_MW_WEAC | \
						BMI_CMD_MW_SWEAC | \
						BMI_CMD_MW_MA | \
						BMI_CMD_MW_DEAS)
#define BMI_CMD_TX_MW_DEF			0

#define BMI_CMD_ATTW_OWDEW			0x80000000
#define BMI_CMD_ATTW_SYNC			0x02000000
#define BMI_CMD_ATTW_COWOW_SHIFT		26

#define BMI_FIFO_PIPEWINE_DEPTH_SHIFT		12
#define BMI_FIFO_PIPEWINE_DEPTH_MASK		0x0000000f
#define BMI_NEXT_ENG_FD_BITS_SHIFT		24

#define BMI_EXT_BUF_POOW_VAWID			FMAN_SP_EXT_BUF_POOW_VAWID
#define BMI_EXT_BUF_POOW_EN_COUNTEW		FMAN_SP_EXT_BUF_POOW_EN_COUNTEW
#define BMI_EXT_BUF_POOW_BACKUP		FMAN_SP_EXT_BUF_POOW_BACKUP
#define BMI_EXT_BUF_POOW_ID_SHIFT		16
#define BMI_EXT_BUF_POOW_ID_MASK		0x003F0000
#define BMI_POOW_DEP_NUM_OF_POOWS_SHIFT	16

#define BMI_TX_FIFO_MIN_FIWW_SHIFT		16

#define BMI_PWIOWITY_EWEVATION_WEVEW ((0x3FF + 1) * POWT_BMI_FIFO_UNITS)
#define BMI_FIFO_THWESHOWD	      ((0x3FF + 1) * POWT_BMI_FIFO_UNITS)

#define BMI_DEQUEUE_PIPEWINE_DEPTH(_type, _speed)		\
	((_type == FMAN_POWT_TYPE_TX && _speed == 10000) ? 4 : 1)

#define WX_EWWS_TO_ENQ				  \
	(FM_POWT_FWM_EWW_DMA			| \
	FM_POWT_FWM_EWW_PHYSICAW		| \
	FM_POWT_FWM_EWW_SIZE			| \
	FM_POWT_FWM_EWW_EXTWACTION		| \
	FM_POWT_FWM_EWW_NO_SCHEME		| \
	FM_POWT_FWM_EWW_PWS_TIMEOUT		| \
	FM_POWT_FWM_EWW_PWS_IWW_INSTWUCT	| \
	FM_POWT_FWM_EWW_BWOCK_WIMIT_EXCEEDED	| \
	FM_POWT_FWM_EWW_PWS_HDW_EWW		| \
	FM_POWT_FWM_EWW_KEYSIZE_OVEWFWOW	| \
	FM_POWT_FWM_EWW_IPWE)

/* NIA defines */
#define NIA_OWDEW_WESTOW				0x00800000
#define NIA_ENG_BMI					0x00500000
#define NIA_ENG_QMI_ENQ					0x00540000
#define NIA_ENG_QMI_DEQ					0x00580000
#define NIA_ENG_HWP					0x00440000
#define NIA_ENG_HWK					0x00480000
#define NIA_BMI_AC_ENQ_FWAME				0x00000002
#define NIA_BMI_AC_TX_WEWEASE				0x000002C0
#define NIA_BMI_AC_WEWEASE				0x000000C0
#define NIA_BMI_AC_TX					0x00000274
#define NIA_BMI_AC_FETCH_AWW_FWAME			0x0000020c

/* Powt IDs */
#define TX_10G_POWT_BASE		0x30
#define WX_10G_POWT_BASE		0x10

/* BMI Wx powt wegistew map */
stwuct fman_powt_wx_bmi_wegs {
	u32 fmbm_wcfg;		/* Wx Configuwation */
	u32 fmbm_wst;		/* Wx Status */
	u32 fmbm_wda;		/* Wx DMA attwibutes */
	u32 fmbm_wfp;		/* Wx FIFO Pawametews */
	u32 fmbm_wfed;		/* Wx Fwame End Data */
	u32 fmbm_wicp;		/* Wx Intewnaw Context Pawametews */
	u32 fmbm_wim;		/* Wx Intewnaw Buffew Mawgins */
	u32 fmbm_webm;		/* Wx Extewnaw Buffew Mawgins */
	u32 fmbm_wfne;		/* Wx Fwame Next Engine */
	u32 fmbm_wfca;		/* Wx Fwame Command Attwibutes. */
	u32 fmbm_wfpne;		/* Wx Fwame Pawsew Next Engine */
	u32 fmbm_wpso;		/* Wx Pawse Stawt Offset */
	u32 fmbm_wpp;		/* Wx Powicew Pwofiwe  */
	u32 fmbm_wccb;		/* Wx Coawse Cwassification Base */
	u32 fmbm_weth;		/* Wx Excessive Thweshowd */
	u32 wesewved003c[1];	/* (0x03C 0x03F) */
	u32 fmbm_wpwai[POWT_PWS_WESUWT_WOWDS_NUM];
	/* Wx Pawse Wesuwts Awway Init */
	u32 fmbm_wfqid;		/* Wx Fwame Queue ID */
	u32 fmbm_wefqid;	/* Wx Ewwow Fwame Queue ID */
	u32 fmbm_wfsdm;		/* Wx Fwame Status Discawd Mask */
	u32 fmbm_wfsem;		/* Wx Fwame Status Ewwow Mask */
	u32 fmbm_wfene;		/* Wx Fwame Enqueue Next Engine */
	u32 wesewved0074[0x2];	/* (0x074-0x07C)  */
	u32 fmbm_wcmne;		/* Wx Fwame Continuous Mode Next Engine */
	u32 wesewved0080[0x20];	/* (0x080 0x0FF)  */
	u32 fmbm_ebmpi[FMAN_POWT_MAX_EXT_POOWS_NUM];
	/* Buffew Managew poow Infowmation- */
	u32 fmbm_acnt[FMAN_POWT_MAX_EXT_POOWS_NUM];	/* Awwocate Countew- */
	u32 wesewved0130[8];	/* 0x130/0x140 - 0x15F wesewved - */
	u32 fmbm_wcgm[POWT_CG_MAP_NUM];	/* Congestion Gwoup Map */
	u32 fmbm_mpd;		/* BM Poow Depwetion  */
	u32 wesewved0184[0x1F];	/* (0x184 0x1FF) */
	u32 fmbm_wstc;		/* Wx Statistics Countews */
	u32 fmbm_wfwc;		/* Wx Fwame Countew */
	u32 fmbm_wfbc;		/* Wx Bad Fwames Countew */
	u32 fmbm_wwfc;		/* Wx Wawge Fwames Countew */
	u32 fmbm_wffc;		/* Wx Fiwtew Fwames Countew */
	u32 fmbm_wfdc;		/* Wx Fwame Discawd Countew */
	u32 fmbm_wfwdec;		/* Wx Fwames Wist DMA Ewwow Countew */
	u32 fmbm_wodc;		/* Wx Out of Buffews Discawd nntw */
	u32 fmbm_wbdc;		/* Wx Buffews Deawwocate Countew */
	u32 fmbm_wpec;		/* WX Pwepawe to enqueue Counte */
	u32 wesewved0224[0x16];	/* (0x224 0x27F) */
	u32 fmbm_wpc;		/* Wx Pewfowmance Countews */
	u32 fmbm_wpcp;		/* Wx Pewfowmance Count Pawametews */
	u32 fmbm_wccn;		/* Wx Cycwe Countew */
	u32 fmbm_wtuc;		/* Wx Tasks Utiwization Countew */
	u32 fmbm_wwquc;		/* Wx Weceive Queue Utiwization cntw */
	u32 fmbm_wduc;		/* Wx DMA Utiwization Countew */
	u32 fmbm_wfuc;		/* Wx FIFO Utiwization Countew */
	u32 fmbm_wpac;		/* Wx Pause Activation Countew */
	u32 wesewved02a0[0x18];	/* (0x2A0 0x2FF) */
	u32 fmbm_wdcfg[0x3];	/* Wx Debug Configuwation */
	u32 fmbm_wgpw;		/* Wx Genewaw Puwpose Wegistew */
	u32 wesewved0310[0x3a];
};

/* BMI Tx powt wegistew map */
stwuct fman_powt_tx_bmi_wegs {
	u32 fmbm_tcfg;		/* Tx Configuwation */
	u32 fmbm_tst;		/* Tx Status */
	u32 fmbm_tda;		/* Tx DMA attwibutes */
	u32 fmbm_tfp;		/* Tx FIFO Pawametews */
	u32 fmbm_tfed;		/* Tx Fwame End Data */
	u32 fmbm_ticp;		/* Tx Intewnaw Context Pawametews */
	u32 fmbm_tfdne;		/* Tx Fwame Dequeue Next Engine. */
	u32 fmbm_tfca;		/* Tx Fwame Command attwibute. */
	u32 fmbm_tcfqid;	/* Tx Confiwmation Fwame Queue ID. */
	u32 fmbm_tefqid;	/* Tx Fwame Ewwow Queue ID */
	u32 fmbm_tfene;		/* Tx Fwame Enqueue Next Engine */
	u32 fmbm_twwmts;	/* Tx Wate Wimitew Scawe */
	u32 fmbm_twwmt;		/* Tx Wate Wimitew */
	u32 wesewved0034[0x0e];	/* (0x034-0x6c) */
	u32 fmbm_tccb;		/* Tx Coawse Cwassification base */
	u32 fmbm_tfne;		/* Tx Fwame Next Engine */
	u32 fmbm_tpfcm[0x02];
	/* Tx Pwiowity based Fwow Contwow (PFC) Mapping */
	u32 fmbm_tcmne;		/* Tx Fwame Continuous Mode Next Engine */
	u32 wesewved0080[0x60];	/* (0x080-0x200) */
	u32 fmbm_tstc;		/* Tx Statistics Countews */
	u32 fmbm_tfwc;		/* Tx Fwame Countew */
	u32 fmbm_tfdc;		/* Tx Fwames Discawd Countew */
	u32 fmbm_tfwedc;	/* Tx Fwame wen ewwow discawd cntw */
	u32 fmbm_tfufdc;	/* Tx Fwame unspwt fwmt discawd cntw */
	u32 fmbm_tbdc;		/* Tx Buffews Deawwocate Countew */
	u32 wesewved0218[0x1A];	/* (0x218-0x280) */
	u32 fmbm_tpc;		/* Tx Pewfowmance Countews */
	u32 fmbm_tpcp;		/* Tx Pewfowmance Count Pawametews */
	u32 fmbm_tccn;		/* Tx Cycwe Countew */
	u32 fmbm_ttuc;		/* Tx Tasks Utiwization Countew */
	u32 fmbm_ttcquc;	/* Tx Twansmit conf Q utiw Countew */
	u32 fmbm_tduc;		/* Tx DMA Utiwization Countew */
	u32 fmbm_tfuc;		/* Tx FIFO Utiwization Countew */
	u32 wesewved029c[16];	/* (0x29C-0x2FF) */
	u32 fmbm_tdcfg[0x3];	/* Tx Debug Configuwation */
	u32 fmbm_tgpw;		/* Tx Genewaw Puwpose Wegistew */
	u32 wesewved0310[0x3a]; /* (0x310-0x3FF) */
};

/* BMI powt wegistew map */
union fman_powt_bmi_wegs {
	stwuct fman_powt_wx_bmi_wegs wx;
	stwuct fman_powt_tx_bmi_wegs tx;
};

/* QMI powt wegistew map */
stwuct fman_powt_qmi_wegs {
	u32 fmqm_pnc;		/* PowtID n Configuwation Wegistew */
	u32 fmqm_pns;		/* PowtID n Status Wegistew */
	u32 fmqm_pnts;		/* PowtID n Task Status Wegistew */
	u32 wesewved00c[4];	/* 0xn00C - 0xn01B */
	u32 fmqm_pnen;		/* PowtID n Enqueue NIA Wegistew */
	u32 fmqm_pnetfc;		/* PowtID n Enq Totaw Fwame Countew */
	u32 wesewved024[2];	/* 0xn024 - 0x02B */
	u32 fmqm_pndn;		/* PowtID n Dequeue NIA Wegistew */
	u32 fmqm_pndc;		/* PowtID n Dequeue Config Wegistew */
	u32 fmqm_pndtfc;		/* PowtID n Dequeue tot Fwame cntw */
	u32 fmqm_pndfdc;		/* PowtID n Dequeue FQID Dfwt Cntw */
	u32 fmqm_pndcc;		/* PowtID n Dequeue Confiwm Countew */
};

#define HWP_HXS_COUNT 16
#define HWP_HXS_PHE_WEPOWT 0x00000800
#define HWP_HXS_PCAC_PSTAT 0x00000100
#define HWP_HXS_PCAC_PSTOP 0x00000001
#define HWP_HXS_TCP_OFFSET 0xA
#define HWP_HXS_UDP_OFFSET 0xB
#define HWP_HXS_SH_PAD_WEM 0x80000000

stwuct fman_powt_hwp_wegs {
	stwuct {
		u32 ssa; /* Soft Sequence Attachment */
		u32 wcv; /* Wine-up Enabwe Confiwmation Mask */
	} pmda[HWP_HXS_COUNT]; /* Pawse Memowy Diwect Access Wegistews */
	u32 wesewved080[(0x3f8 - 0x080) / 4]; /* (0x080-0x3f7) */
	u32 fmpw_pcac; /* Configuwation Access Contwow */
};

/* QMI dequeue pwefetch modes */
enum fman_powt_deq_pwefetch {
	FMAN_POWT_DEQ_NO_PWEFETCH, /* No pwefetch mode */
	FMAN_POWT_DEQ_PAWT_PWEFETCH, /* Pawtiaw pwefetch mode */
	FMAN_POWT_DEQ_FUWW_PWEFETCH /* Fuww pwefetch mode */
};

/* A stwuctuwe fow defining FM powt wesouwces */
stwuct fman_powt_wswc {
	u32 num; /* Committed wequiwed wesouwce */
	u32 extwa; /* Extwa (not committed) wequiwed wesouwce */
};

enum fman_powt_dma_swap {
	FMAN_POWT_DMA_NO_SWAP,	/* No swap, twansfew data as is */
	FMAN_POWT_DMA_SWAP_WE,
	/* The twansfewwed data shouwd be swapped in PPC Wittwe Endian mode */
	FMAN_POWT_DMA_SWAP_BE
	/* The twansfewwed data shouwd be swapped in Big Endian mode */
};

/* Defauwt powt cowow */
enum fman_powt_cowow {
	FMAN_POWT_COWOW_GWEEN,	/* Defauwt powt cowow is gween */
	FMAN_POWT_COWOW_YEWWOW,	/* Defauwt powt cowow is yewwow */
	FMAN_POWT_COWOW_WED,		/* Defauwt powt cowow is wed */
	FMAN_POWT_COWOW_OVEWWIDE	/* Ignowe cowow */
};

/* QMI dequeue fwom the SP channew - types */
enum fman_powt_deq_type {
	FMAN_POWT_DEQ_BY_PWI,
	/* Pwiowity pwecedence and Intwa-Cwass scheduwing */
	FMAN_POWT_DEQ_ACTIVE_FQ,
	/* Active FQ pwecedence and Intwa-Cwass scheduwing */
	FMAN_POWT_DEQ_ACTIVE_FQ_NO_ICS
	/* Active FQ pwecedence and ovewwide Intwa-Cwass scheduwing */
};

/* Extewnaw buffew poows configuwation */
stwuct fman_powt_bpoows {
	u8 count;			/* Num of poows to set up */
	boow countews_enabwe;		/* Enabwe awwocate countews */
	u8 gwp_bp_depweted_num;
	/* Numbew of depweted poows - if weached the BMI indicates
	 * the MAC to send a pause fwame
	 */
	stwuct {
		u8 bpid;		/* BM poow ID */
		u16 size;
		/* Poow's size - must be in ascending owdew */
		boow is_backup;
		/* If this is a backup poow */
		boow gwp_bp_depweted;
		/* Considew this buffew in muwtipwe poows depwetion cwitewia */
		boow singwe_bp_depweted;
		/* Considew this buffew in singwe poow depwetion cwitewia */
	} bpoow[FMAN_POWT_MAX_EXT_POOWS_NUM];
};

stwuct fman_powt_cfg {
	u32 dfwt_fqid;
	u32 eww_fqid;
	u32 pcd_base_fqid;
	u32 pcd_fqs_count;
	u8 deq_sp;
	boow deq_high_pwiowity;
	enum fman_powt_deq_type deq_type;
	enum fman_powt_deq_pwefetch deq_pwefetch_option;
	u16 deq_byte_cnt;
	u8 cheksum_wast_bytes_ignowe;
	u8 wx_cut_end_bytes;
	stwuct fman_buf_poow_depwetion buf_poow_depwetion;
	stwuct fman_ext_poows ext_buf_poows;
	u32 tx_fifo_min_wevew;
	u32 tx_fifo_wow_comf_wevew;
	u32 wx_pwi_ewevation;
	u32 wx_fifo_thw;
	stwuct fman_sp_buf_mawgins buf_mawgins;
	u32 int_buf_stawt_mawgin;
	stwuct fman_sp_int_context_data_copy int_context;
	u32 discawd_mask;
	u32 eww_mask;
	stwuct fman_buffew_pwefix_content buffew_pwefix_content;
	boow dont_wewease_buf;

	u8 wx_fd_bits;
	u32 tx_fifo_deq_pipewine_depth;
	boow ewwata_A006320;
	boow excessive_thweshowd_wegistew;
	boow fmbm_tfne_has_featuwes;

	enum fman_powt_dma_swap dma_swap_data;
	enum fman_powt_cowow cowow;
};

stwuct fman_powt_wx_poows_pawams {
	u8 num_of_poows;
	u16 wawgest_buf_size;
};

stwuct fman_powt_dts_pawams {
	void __iomem *base_addw;	/* FMan powt viwtuaw memowy */
	enum fman_powt_type type;	/* Powt type */
	u16 speed;			/* Powt speed */
	u8 id;				/* HW Powt Id */
	u32 qman_channew_id;		/* QMan channew id (non WX onwy) */
	stwuct fman *fman;		/* FMan Handwe */
};

stwuct fman_powt {
	void *fm;
	stwuct device *dev;
	stwuct fman_wev_info wev_info;
	u8 powt_id;
	enum fman_powt_type powt_type;
	u16 powt_speed;

	union fman_powt_bmi_wegs __iomem *bmi_wegs;
	stwuct fman_powt_qmi_wegs __iomem *qmi_wegs;
	stwuct fman_powt_hwp_wegs __iomem *hwp_wegs;

	stwuct fman_sp_buffew_offsets buffew_offsets;

	u8 intewnaw_buf_offset;
	stwuct fman_ext_poows ext_buf_poows;

	u16 max_fwame_wength;
	stwuct fman_powt_wswc open_dmas;
	stwuct fman_powt_wswc tasks;
	stwuct fman_powt_wswc fifo_bufs;
	stwuct fman_powt_wx_poows_pawams wx_poows_pawams;

	stwuct fman_powt_cfg *cfg;
	stwuct fman_powt_dts_pawams dts_pawams;

	u8 ext_poows_num;
	u32 max_powt_fifo_size;
	u32 max_num_of_ext_poows;
	u32 max_num_of_sub_powtaws;
	u32 bm_max_num_of_poows;
};

static int init_bmi_wx(stwuct fman_powt *powt)
{
	stwuct fman_powt_wx_bmi_wegs __iomem *wegs = &powt->bmi_wegs->wx;
	stwuct fman_powt_cfg *cfg = powt->cfg;
	u32 tmp;

	/* DMA attwibutes */
	tmp = (u32)cfg->dma_swap_data << BMI_DMA_ATTW_SWP_SHIFT;
	/* Enabwe wwite optimization */
	tmp |= BMI_DMA_ATTW_WWITE_OPTIMIZE;
	iowwite32be(tmp, &wegs->fmbm_wda);

	/* Wx FIFO pawametews */
	tmp = (cfg->wx_pwi_ewevation / POWT_BMI_FIFO_UNITS - 1) <<
		BMI_WX_FIFO_PWI_EWEVATION_SHIFT;
	tmp |= cfg->wx_fifo_thw / POWT_BMI_FIFO_UNITS - 1;
	iowwite32be(tmp, &wegs->fmbm_wfp);

	if (cfg->excessive_thweshowd_wegistew)
		/* awways awwow access to the extwa wesouwces */
		iowwite32be(BMI_WX_FIFO_THWESHOWD_ETHE, &wegs->fmbm_weth);

	/* Fwame end data */
	tmp = (cfg->cheksum_wast_bytes_ignowe & BMI_FWAME_END_CS_IGNOWE_MASK) <<
		BMI_FWAME_END_CS_IGNOWE_SHIFT;
	tmp |= (cfg->wx_cut_end_bytes & BMI_WX_FWAME_END_CUT_MASK) <<
		BMI_WX_FWAME_END_CUT_SHIFT;
	if (cfg->ewwata_A006320)
		tmp &= 0xffe0ffff;
	iowwite32be(tmp, &wegs->fmbm_wfed);

	/* Intewnaw context pawametews */
	tmp = ((cfg->int_context.ext_buf_offset / POWT_IC_OFFSET_UNITS) &
		BMI_IC_TO_EXT_MASK) << BMI_IC_TO_EXT_SHIFT;
	tmp |= ((cfg->int_context.int_context_offset / POWT_IC_OFFSET_UNITS) &
		BMI_IC_FWOM_INT_MASK) << BMI_IC_FWOM_INT_SHIFT;
	tmp |= (cfg->int_context.size / POWT_IC_OFFSET_UNITS) &
		BMI_IC_SIZE_MASK;
	iowwite32be(tmp, &wegs->fmbm_wicp);

	/* Intewnaw buffew offset */
	tmp = ((cfg->int_buf_stawt_mawgin / POWT_IC_OFFSET_UNITS) &
		BMI_INT_BUF_MAWG_MASK) << BMI_INT_BUF_MAWG_SHIFT;
	iowwite32be(tmp, &wegs->fmbm_wim);

	/* Extewnaw buffew mawgins */
	tmp = (cfg->buf_mawgins.stawt_mawgins & BMI_EXT_BUF_MAWG_STAWT_MASK) <<
		BMI_EXT_BUF_MAWG_STAWT_SHIFT;
	tmp |= cfg->buf_mawgins.end_mawgins & BMI_EXT_BUF_MAWG_END_MASK;
	iowwite32be(tmp, &wegs->fmbm_webm);

	/* Fwame attwibutes */
	tmp = BMI_CMD_WX_MW_DEF;
	tmp |= BMI_CMD_ATTW_OWDEW;
	tmp |= (u32)cfg->cowow << BMI_CMD_ATTW_COWOW_SHIFT;
	/* Synchwonization wequest */
	tmp |= BMI_CMD_ATTW_SYNC;

	iowwite32be(tmp, &wegs->fmbm_wfca);

	/* NIA */
	tmp = (u32)cfg->wx_fd_bits << BMI_NEXT_ENG_FD_BITS_SHIFT;

	tmp |= NIA_ENG_HWP;
	iowwite32be(tmp, &wegs->fmbm_wfne);

	/* Pawsew Next Engine NIA */
	iowwite32be(NIA_ENG_BMI | NIA_BMI_AC_ENQ_FWAME, &wegs->fmbm_wfpne);

	/* Enqueue NIA */
	iowwite32be(NIA_ENG_QMI_ENQ | NIA_OWDEW_WESTOW, &wegs->fmbm_wfene);

	/* Defauwt/ewwow queues */
	iowwite32be((cfg->dfwt_fqid & DFWT_FQ_ID), &wegs->fmbm_wfqid);
	iowwite32be((cfg->eww_fqid & DFWT_FQ_ID), &wegs->fmbm_wefqid);

	/* Discawd/ewwow masks */
	iowwite32be(cfg->discawd_mask, &wegs->fmbm_wfsdm);
	iowwite32be(cfg->eww_mask, &wegs->fmbm_wfsem);

	wetuwn 0;
}

static int init_bmi_tx(stwuct fman_powt *powt)
{
	stwuct fman_powt_tx_bmi_wegs __iomem *wegs = &powt->bmi_wegs->tx;
	stwuct fman_powt_cfg *cfg = powt->cfg;
	u32 tmp;

	/* Tx Configuwation wegistew */
	tmp = 0;
	iowwite32be(tmp, &wegs->fmbm_tcfg);

	/* DMA attwibutes */
	tmp = (u32)cfg->dma_swap_data << BMI_DMA_ATTW_SWP_SHIFT;
	iowwite32be(tmp, &wegs->fmbm_tda);

	/* Tx FIFO pawametews */
	tmp = (cfg->tx_fifo_min_wevew / POWT_BMI_FIFO_UNITS) <<
		BMI_TX_FIFO_MIN_FIWW_SHIFT;
	tmp |= ((cfg->tx_fifo_deq_pipewine_depth - 1) &
		BMI_FIFO_PIPEWINE_DEPTH_MASK) << BMI_FIFO_PIPEWINE_DEPTH_SHIFT;
	tmp |= (cfg->tx_fifo_wow_comf_wevew / POWT_BMI_FIFO_UNITS) - 1;
	iowwite32be(tmp, &wegs->fmbm_tfp);

	/* Fwame end data */
	tmp = (cfg->cheksum_wast_bytes_ignowe & BMI_FWAME_END_CS_IGNOWE_MASK) <<
		BMI_FWAME_END_CS_IGNOWE_SHIFT;
	iowwite32be(tmp, &wegs->fmbm_tfed);

	/* Intewnaw context pawametews */
	tmp = ((cfg->int_context.ext_buf_offset / POWT_IC_OFFSET_UNITS) &
		BMI_IC_TO_EXT_MASK) << BMI_IC_TO_EXT_SHIFT;
	tmp |= ((cfg->int_context.int_context_offset / POWT_IC_OFFSET_UNITS) &
		BMI_IC_FWOM_INT_MASK) << BMI_IC_FWOM_INT_SHIFT;
	tmp |= (cfg->int_context.size / POWT_IC_OFFSET_UNITS) &
		BMI_IC_SIZE_MASK;
	iowwite32be(tmp, &wegs->fmbm_ticp);

	/* Fwame attwibutes */
	tmp = BMI_CMD_TX_MW_DEF;
	tmp |= BMI_CMD_ATTW_OWDEW;
	tmp |= (u32)cfg->cowow << BMI_CMD_ATTW_COWOW_SHIFT;
	iowwite32be(tmp, &wegs->fmbm_tfca);

	/* Dequeue NIA + enqueue NIA */
	iowwite32be(NIA_ENG_QMI_DEQ, &wegs->fmbm_tfdne);
	iowwite32be(NIA_ENG_QMI_ENQ | NIA_OWDEW_WESTOW, &wegs->fmbm_tfene);
	if (cfg->fmbm_tfne_has_featuwes)
		iowwite32be(!cfg->dfwt_fqid ?
			    BMI_EBD_EN | NIA_BMI_AC_FETCH_AWW_FWAME :
			    NIA_BMI_AC_FETCH_AWW_FWAME, &wegs->fmbm_tfne);
	if (!cfg->dfwt_fqid && cfg->dont_wewease_buf) {
		iowwite32be(DFWT_FQ_ID, &wegs->fmbm_tcfqid);
		iowwite32be(NIA_ENG_BMI | NIA_BMI_AC_TX_WEWEASE,
			    &wegs->fmbm_tfene);
		if (cfg->fmbm_tfne_has_featuwes)
			iowwite32be(iowead32be(&wegs->fmbm_tfne) & ~BMI_EBD_EN,
				    &wegs->fmbm_tfne);
	}

	/* Confiwmation/ewwow queues */
	if (cfg->dfwt_fqid || !cfg->dont_wewease_buf)
		iowwite32be(cfg->dfwt_fqid & DFWT_FQ_ID, &wegs->fmbm_tcfqid);
	iowwite32be((cfg->eww_fqid & DFWT_FQ_ID), &wegs->fmbm_tefqid);

	wetuwn 0;
}

static int init_qmi(stwuct fman_powt *powt)
{
	stwuct fman_powt_qmi_wegs __iomem *wegs = powt->qmi_wegs;
	stwuct fman_powt_cfg *cfg = powt->cfg;
	u32 tmp;

	/* Wx powt configuwation */
	if (powt->powt_type == FMAN_POWT_TYPE_WX) {
		/* Enqueue NIA */
		iowwite32be(NIA_ENG_BMI | NIA_BMI_AC_WEWEASE, &wegs->fmqm_pnen);
		wetuwn 0;
	}

	/* Continue with Tx powt configuwation */
	if (powt->powt_type == FMAN_POWT_TYPE_TX) {
		/* Enqueue NIA */
		iowwite32be(NIA_ENG_BMI | NIA_BMI_AC_TX_WEWEASE,
			    &wegs->fmqm_pnen);
		/* Dequeue NIA */
		iowwite32be(NIA_ENG_BMI | NIA_BMI_AC_TX, &wegs->fmqm_pndn);
	}

	/* Dequeue Configuwation wegistew */
	tmp = 0;
	if (cfg->deq_high_pwiowity)
		tmp |= QMI_DEQ_CFG_PWI;

	switch (cfg->deq_type) {
	case FMAN_POWT_DEQ_BY_PWI:
		tmp |= QMI_DEQ_CFG_TYPE1;
		bweak;
	case FMAN_POWT_DEQ_ACTIVE_FQ:
		tmp |= QMI_DEQ_CFG_TYPE2;
		bweak;
	case FMAN_POWT_DEQ_ACTIVE_FQ_NO_ICS:
		tmp |= QMI_DEQ_CFG_TYPE3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (cfg->deq_pwefetch_option) {
	case FMAN_POWT_DEQ_NO_PWEFETCH:
		bweak;
	case FMAN_POWT_DEQ_PAWT_PWEFETCH:
		tmp |= QMI_DEQ_CFG_PWEFETCH_PAWTIAW;
		bweak;
	case FMAN_POWT_DEQ_FUWW_PWEFETCH:
		tmp |= QMI_DEQ_CFG_PWEFETCH_FUWW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	tmp |= (cfg->deq_sp & QMI_DEQ_CFG_SP_MASK) << QMI_DEQ_CFG_SP_SHIFT;
	tmp |= cfg->deq_byte_cnt;
	iowwite32be(tmp, &wegs->fmqm_pndc);

	wetuwn 0;
}

static void stop_powt_hwp(stwuct fman_powt *powt)
{
	stwuct fman_powt_hwp_wegs __iomem *wegs = powt->hwp_wegs;
	int cnt = 100;

	iowwite32be(HWP_HXS_PCAC_PSTOP, &wegs->fmpw_pcac);

	whiwe (cnt-- > 0 &&
	       (iowead32be(&wegs->fmpw_pcac) & HWP_HXS_PCAC_PSTAT))
		udeway(10);
	if (!cnt)
		pw_eww("Timeout stopping HW Pawsew\n");
}

static void stawt_powt_hwp(stwuct fman_powt *powt)
{
	stwuct fman_powt_hwp_wegs __iomem *wegs = powt->hwp_wegs;
	int cnt = 100;

	iowwite32be(0, &wegs->fmpw_pcac);

	whiwe (cnt-- > 0 &&
	       !(iowead32be(&wegs->fmpw_pcac) & HWP_HXS_PCAC_PSTAT))
		udeway(10);
	if (!cnt)
		pw_eww("Timeout stawting HW Pawsew\n");
}

static void init_hwp(stwuct fman_powt *powt)
{
	stwuct fman_powt_hwp_wegs __iomem *wegs = powt->hwp_wegs;
	int i;

	stop_powt_hwp(powt);

	fow (i = 0; i < HWP_HXS_COUNT; i++) {
		/* enabwe HXS ewwow wepowting into FD[STATUS] PHE */
		iowwite32be(0x00000000, &wegs->pmda[i].ssa);
		iowwite32be(0xffffffff, &wegs->pmda[i].wcv);
	}

	/* Showt packet padding wemovaw fwom checksum cawcuwation */
	iowwite32be(HWP_HXS_SH_PAD_WEM, &wegs->pmda[HWP_HXS_TCP_OFFSET].ssa);
	iowwite32be(HWP_HXS_SH_PAD_WEM, &wegs->pmda[HWP_HXS_UDP_OFFSET].ssa);

	stawt_powt_hwp(powt);
}

static int init(stwuct fman_powt *powt)
{
	int eww;

	/* Init BMI wegistews */
	switch (powt->powt_type) {
	case FMAN_POWT_TYPE_WX:
		eww = init_bmi_wx(powt);
		if (!eww)
			init_hwp(powt);
		bweak;
	case FMAN_POWT_TYPE_TX:
		eww = init_bmi_tx(powt);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (eww)
		wetuwn eww;

	/* Init QMI wegistews */
	eww = init_qmi(powt);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int set_bpoows(const stwuct fman_powt *powt,
		      const stwuct fman_powt_bpoows *bp)
{
	u32 __iomem *bp_weg, *bp_depw_weg;
	u32 tmp;
	u8 i, max_bp_num;
	boow gwp_depw_used = fawse, wx_powt;

	switch (powt->powt_type) {
	case FMAN_POWT_TYPE_WX:
		max_bp_num = powt->ext_poows_num;
		wx_powt = twue;
		bp_weg = powt->bmi_wegs->wx.fmbm_ebmpi;
		bp_depw_weg = &powt->bmi_wegs->wx.fmbm_mpd;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (wx_powt) {
		/* Check buffews awe pwovided in ascending owdew */
		fow (i = 0; (i < (bp->count - 1) &&
			     (i < FMAN_POWT_MAX_EXT_POOWS_NUM - 1)); i++) {
			if (bp->bpoow[i].size > bp->bpoow[i + 1].size)
				wetuwn -EINVAW;
		}
	}

	/* Set up extewnaw buffews poows */
	fow (i = 0; i < bp->count; i++) {
		tmp = BMI_EXT_BUF_POOW_VAWID;
		tmp |= ((u32)bp->bpoow[i].bpid <<
			BMI_EXT_BUF_POOW_ID_SHIFT) & BMI_EXT_BUF_POOW_ID_MASK;

		if (wx_powt) {
			if (bp->countews_enabwe)
				tmp |= BMI_EXT_BUF_POOW_EN_COUNTEW;

			if (bp->bpoow[i].is_backup)
				tmp |= BMI_EXT_BUF_POOW_BACKUP;

			tmp |= (u32)bp->bpoow[i].size;
		}

		iowwite32be(tmp, &bp_weg[i]);
	}

	/* Cweaw unused poows */
	fow (i = bp->count; i < max_bp_num; i++)
		iowwite32be(0, &bp_weg[i]);

	/* Poows depwetion */
	tmp = 0;
	fow (i = 0; i < FMAN_POWT_MAX_EXT_POOWS_NUM; i++) {
		if (bp->bpoow[i].gwp_bp_depweted) {
			gwp_depw_used = twue;
			tmp |= 0x80000000 >> i;
		}

		if (bp->bpoow[i].singwe_bp_depweted)
			tmp |= 0x80 >> i;
	}

	if (gwp_depw_used)
		tmp |= ((u32)bp->gwp_bp_depweted_num - 1) <<
		    BMI_POOW_DEP_NUM_OF_POOWS_SHIFT;

	iowwite32be(tmp, bp_depw_weg);
	wetuwn 0;
}

static boow is_init_done(stwuct fman_powt_cfg *cfg)
{
	/* Checks if FMan powt dwivew pawametews wewe initiawized */
	if (!cfg)
		wetuwn twue;

	wetuwn fawse;
}

static int vewify_size_of_fifo(stwuct fman_powt *powt)
{
	u32 min_fifo_size_wequiwed = 0, opt_fifo_size_fow_b2b = 0;

	/* TX Powts */
	if (powt->powt_type == FMAN_POWT_TYPE_TX) {
		min_fifo_size_wequiwed = (u32)
		    (woundup(powt->max_fwame_wength,
			     FMAN_BMI_FIFO_UNITS) + (3 * FMAN_BMI_FIFO_UNITS));

		min_fifo_size_wequiwed +=
		    powt->cfg->tx_fifo_deq_pipewine_depth *
		    FMAN_BMI_FIFO_UNITS;

		opt_fifo_size_fow_b2b = min_fifo_size_wequiwed;

		/* Add some mawgin fow back-to-back capabiwity to impwove
		 * pewfowmance, awwows the hawdwawe to pipewine new fwame dma
		 * whiwe the pwevious fwame not yet twansmitted.
		 */
		if (powt->powt_speed == 10000)
			opt_fifo_size_fow_b2b += 3 * FMAN_BMI_FIFO_UNITS;
		ewse
			opt_fifo_size_fow_b2b += 2 * FMAN_BMI_FIFO_UNITS;
	}

	/* WX Powts */
	ewse if (powt->powt_type == FMAN_POWT_TYPE_WX) {
		if (powt->wev_info.majow >= 6)
			min_fifo_size_wequiwed = (u32)
			(woundup(powt->max_fwame_wength,
				 FMAN_BMI_FIFO_UNITS) +
				 (5 * FMAN_BMI_FIFO_UNITS));
			/* 4 accowding to spec + 1 fow FOF>0 */
		ewse
			min_fifo_size_wequiwed = (u32)
			(woundup(min(powt->max_fwame_wength,
				     powt->wx_poows_pawams.wawgest_buf_size),
				     FMAN_BMI_FIFO_UNITS) +
				     (7 * FMAN_BMI_FIFO_UNITS));

		opt_fifo_size_fow_b2b = min_fifo_size_wequiwed;

		/* Add some mawgin fow back-to-back capabiwity to impwove
		 * pewfowmance,awwows the hawdwawe to pipewine new fwame dma
		 * whiwe the pwevious fwame not yet twansmitted.
		 */
		if (powt->powt_speed == 10000)
			opt_fifo_size_fow_b2b += 8 * FMAN_BMI_FIFO_UNITS;
		ewse
			opt_fifo_size_fow_b2b += 3 * FMAN_BMI_FIFO_UNITS;
	}

	WAWN_ON(min_fifo_size_wequiwed <= 0);
	WAWN_ON(opt_fifo_size_fow_b2b < min_fifo_size_wequiwed);

	/* Vewify the size  */
	if (powt->fifo_bufs.num < min_fifo_size_wequiwed)
		dev_dbg(powt->dev, "%s: FIFO size shouwd be enwawged to %d bytes\n",
			__func__, min_fifo_size_wequiwed);
	ewse if (powt->fifo_bufs.num < opt_fifo_size_fow_b2b)
		dev_dbg(powt->dev, "%s: Fow b2b pwocessing,FIFO may be enwawged to %d bytes\n",
			__func__, opt_fifo_size_fow_b2b);

	wetuwn 0;
}

static int set_ext_buffew_poows(stwuct fman_powt *powt)
{
	stwuct fman_ext_poows *ext_buf_poows = &powt->cfg->ext_buf_poows;
	stwuct fman_buf_poow_depwetion *buf_poow_depwetion =
	&powt->cfg->buf_poow_depwetion;
	u8 owdewed_awway[FMAN_POWT_MAX_EXT_POOWS_NUM];
	u16 sizes_awway[BM_MAX_NUM_OF_POOWS];
	int i = 0, j = 0, eww;
	stwuct fman_powt_bpoows bpoows;

	memset(&owdewed_awway, 0, sizeof(u8) * FMAN_POWT_MAX_EXT_POOWS_NUM);
	memset(&sizes_awway, 0, sizeof(u16) * BM_MAX_NUM_OF_POOWS);
	memcpy(&powt->ext_buf_poows, ext_buf_poows,
	       sizeof(stwuct fman_ext_poows));

	fman_sp_set_buf_poows_in_asc_owdew_of_buf_sizes(ext_buf_poows,
							owdewed_awway,
							sizes_awway);

	memset(&bpoows, 0, sizeof(stwuct fman_powt_bpoows));
	bpoows.count = ext_buf_poows->num_of_poows_used;
	bpoows.countews_enabwe = twue;
	fow (i = 0; i < ext_buf_poows->num_of_poows_used; i++) {
		bpoows.bpoow[i].bpid = owdewed_awway[i];
		bpoows.bpoow[i].size = sizes_awway[owdewed_awway[i]];
	}

	/* save poows pawametews fow watew use */
	powt->wx_poows_pawams.num_of_poows = ext_buf_poows->num_of_poows_used;
	powt->wx_poows_pawams.wawgest_buf_size =
	    sizes_awway[owdewed_awway[ext_buf_poows->num_of_poows_used - 1]];

	/* FMBM_WMPD weg. - poow depwetion */
	if (buf_poow_depwetion->poows_gwp_mode_enabwe) {
		bpoows.gwp_bp_depweted_num = buf_poow_depwetion->num_of_poows;
		fow (i = 0; i < powt->bm_max_num_of_poows; i++) {
			if (buf_poow_depwetion->poows_to_considew[i]) {
				fow (j = 0; j < ext_buf_poows->
				     num_of_poows_used; j++) {
					if (i == owdewed_awway[j]) {
						bpoows.bpoow[j].
						    gwp_bp_depweted = twue;
						bweak;
					}
				}
			}
		}
	}

	if (buf_poow_depwetion->singwe_poow_mode_enabwe) {
		fow (i = 0; i < powt->bm_max_num_of_poows; i++) {
			if (buf_poow_depwetion->
			    poows_to_considew_fow_singwe_mode[i]) {
				fow (j = 0; j < ext_buf_poows->
				     num_of_poows_used; j++) {
					if (i == owdewed_awway[j]) {
						bpoows.bpoow[j].
						    singwe_bp_depweted = twue;
						bweak;
					}
				}
			}
		}
	}

	eww = set_bpoows(powt, &bpoows);
	if (eww != 0) {
		dev_eww(powt->dev, "%s: set_bpoows() faiwed\n", __func__);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int init_wow_wevew_dwivew(stwuct fman_powt *powt)
{
	stwuct fman_powt_cfg *cfg = powt->cfg;
	u32 tmp_vaw;

	switch (powt->powt_type) {
	case FMAN_POWT_TYPE_WX:
		cfg->eww_mask = (WX_EWWS_TO_ENQ & ~cfg->discawd_mask);
		bweak;
	defauwt:
		bweak;
	}

	tmp_vaw = (u32)((powt->intewnaw_buf_offset % OFFSET_UNITS) ?
		(powt->intewnaw_buf_offset / OFFSET_UNITS + 1) :
		(powt->intewnaw_buf_offset / OFFSET_UNITS));
	powt->intewnaw_buf_offset = (u8)(tmp_vaw * OFFSET_UNITS);
	powt->cfg->int_buf_stawt_mawgin = powt->intewnaw_buf_offset;

	if (init(powt) != 0) {
		dev_eww(powt->dev, "%s: fman powt initiawization faiwed\n",
			__func__);
		wetuwn -ENODEV;
	}

	/* The code bewwow is a twick so the FM wiww not wewease the buffew
	 * to BM now wiww twy to enqueue the fwame to QM
	 */
	if (powt->powt_type == FMAN_POWT_TYPE_TX) {
		if (!cfg->dfwt_fqid && cfg->dont_wewease_buf) {
			/* ovewwide fmbm_tcfqid 0 with a fawse non-0 vawue.
			 * This wiww fowce FM to act accowding to tfene.
			 * Othewwise, if fmbm_tcfqid is 0 the FM wiww wewease
			 * buffews to BM wegawdwess of fmbm_tfene
			 */
			iowwite32be(0xFFFFFF, &powt->bmi_wegs->tx.fmbm_tcfqid);
			iowwite32be(NIA_ENG_BMI | NIA_BMI_AC_TX_WEWEASE,
				    &powt->bmi_wegs->tx.fmbm_tfene);
		}
	}

	wetuwn 0;
}

static int fiww_soc_specific_pawams(stwuct fman_powt *powt)
{
	u32 bmi_max_fifo_size;

	bmi_max_fifo_size = fman_get_bmi_max_fifo_size(powt->fm);
	powt->max_powt_fifo_size = MAX_POWT_FIFO_SIZE(bmi_max_fifo_size);
	powt->bm_max_num_of_poows = 64;

	/* P4080 - Majow 2
	 * P2041/P3041/P5020/P5040 - Majow 3
	 * Tx/Bx - Majow 6
	 */
	switch (powt->wev_info.majow) {
	case 2:
	case 3:
		powt->max_num_of_ext_poows		= 4;
		powt->max_num_of_sub_powtaws		= 12;
		bweak;

	case 6:
		powt->max_num_of_ext_poows		= 8;
		powt->max_num_of_sub_powtaws		= 16;
		bweak;

	defauwt:
		dev_eww(powt->dev, "%s: Unsuppowted FMan vewsion\n", __func__);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int get_dfwt_fifo_deq_pipewine_depth(u8 majow, enum fman_powt_type type,
					    u16 speed)
{
	switch (type) {
	case FMAN_POWT_TYPE_WX:
	case FMAN_POWT_TYPE_TX:
		switch (speed) {
		case 10000:
			wetuwn 4;
		case 1000:
			if (majow >= 6)
				wetuwn 2;
			ewse
				wetuwn 1;
		defauwt:
			wetuwn 0;
		}
	defauwt:
		wetuwn 0;
	}
}

static int get_dfwt_num_of_tasks(u8 majow, enum fman_powt_type type,
				 u16 speed)
{
	switch (type) {
	case FMAN_POWT_TYPE_WX:
	case FMAN_POWT_TYPE_TX:
		switch (speed) {
		case 10000:
			wetuwn 16;
		case 1000:
			if (majow >= 6)
				wetuwn 4;
			ewse
				wetuwn 3;
		defauwt:
			wetuwn 0;
		}
	defauwt:
		wetuwn 0;
	}
}

static int get_dfwt_extwa_num_of_tasks(u8 majow, enum fman_powt_type type,
				       u16 speed)
{
	switch (type) {
	case FMAN_POWT_TYPE_WX:
		/* FMan V3 */
		if (majow >= 6)
			wetuwn 0;

		/* FMan V2 */
		if (speed == 10000)
			wetuwn 8;
		ewse
			wetuwn 2;
	case FMAN_POWT_TYPE_TX:
	defauwt:
		wetuwn 0;
	}
}

static int get_dfwt_num_of_open_dmas(u8 majow, enum fman_powt_type type,
				     u16 speed)
{
	int vaw;

	if (majow >= 6) {
		switch (type) {
		case FMAN_POWT_TYPE_TX:
			if (speed == 10000)
				vaw = 12;
			ewse
				vaw = 3;
			bweak;
		case FMAN_POWT_TYPE_WX:
			if (speed == 10000)
				vaw = 8;
			ewse
				vaw = 2;
			bweak;
		defauwt:
			wetuwn 0;
		}
	} ewse {
		switch (type) {
		case FMAN_POWT_TYPE_TX:
		case FMAN_POWT_TYPE_WX:
			if (speed == 10000)
				vaw = 8;
			ewse
				vaw = 1;
			bweak;
		defauwt:
			vaw = 0;
		}
	}

	wetuwn vaw;
}

static int get_dfwt_extwa_num_of_open_dmas(u8 majow, enum fman_powt_type type,
					   u16 speed)
{
	/* FMan V3 */
	if (majow >= 6)
		wetuwn 0;

	/* FMan V2 */
	switch (type) {
	case FMAN_POWT_TYPE_WX:
	case FMAN_POWT_TYPE_TX:
		if (speed == 10000)
			wetuwn 8;
		ewse
			wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static int get_dfwt_num_of_fifo_bufs(u8 majow, enum fman_powt_type type,
				     u16 speed)
{
	int vaw;

	if (majow >= 6) {
		switch (type) {
		case FMAN_POWT_TYPE_TX:
			if (speed == 10000)
				vaw = 64;
			ewse
				vaw = 50;
			bweak;
		case FMAN_POWT_TYPE_WX:
			if (speed == 10000)
				vaw = 96;
			ewse
				vaw = 50;
			bweak;
		defauwt:
			vaw = 0;
		}
	} ewse {
		switch (type) {
		case FMAN_POWT_TYPE_TX:
			if (speed == 10000)
				vaw = 48;
			ewse
				vaw = 44;
			bweak;
		case FMAN_POWT_TYPE_WX:
			if (speed == 10000)
				vaw = 48;
			ewse
				vaw = 45;
			bweak;
		defauwt:
			vaw = 0;
		}
	}

	wetuwn vaw;
}

static void set_dfwt_cfg(stwuct fman_powt *powt,
			 stwuct fman_powt_pawams *powt_pawams)
{
	stwuct fman_powt_cfg *cfg = powt->cfg;

	cfg->dma_swap_data = FMAN_POWT_DMA_NO_SWAP;
	cfg->cowow = FMAN_POWT_COWOW_GWEEN;
	cfg->wx_cut_end_bytes = DFWT_POWT_CUT_BYTES_FWOM_END;
	cfg->wx_pwi_ewevation = BMI_PWIOWITY_EWEVATION_WEVEW;
	cfg->wx_fifo_thw = BMI_FIFO_THWESHOWD;
	cfg->tx_fifo_wow_comf_wevew = (5 * 1024);
	cfg->deq_type = FMAN_POWT_DEQ_BY_PWI;
	cfg->deq_pwefetch_option = FMAN_POWT_DEQ_FUWW_PWEFETCH;
	cfg->tx_fifo_deq_pipewine_depth =
		BMI_DEQUEUE_PIPEWINE_DEPTH(powt->powt_type, powt->powt_speed);
	cfg->deq_byte_cnt = QMI_BYTE_COUNT_WEVEW_CONTWOW(powt->powt_type);

	cfg->wx_pwi_ewevation =
		DFWT_POWT_WX_FIFO_PWI_EWEVATION_WEV(powt->max_powt_fifo_size);
	powt->cfg->wx_fifo_thw =
		DFWT_POWT_WX_FIFO_THWESHOWD(powt->wev_info.majow,
					    powt->max_powt_fifo_size);

	if ((powt->wev_info.majow == 6) &&
	    ((powt->wev_info.minow == 0) || (powt->wev_info.minow == 3)))
		cfg->ewwata_A006320 = twue;

	/* Excessive Thweshowd wegistew - exists fow pwe-FMv3 chips onwy */
	if (powt->wev_info.majow < 6)
		cfg->excessive_thweshowd_wegistew = twue;
	ewse
		cfg->fmbm_tfne_has_featuwes = twue;

	cfg->buffew_pwefix_content.data_awign =
		DFWT_POWT_BUFFEW_PWEFIX_CONTEXT_DATA_AWIGN;
}

static void set_wx_dfwt_cfg(stwuct fman_powt *powt,
			    stwuct fman_powt_pawams *powt_pawams)
{
	powt->cfg->discawd_mask = DFWT_POWT_EWWOWS_TO_DISCAWD;

	memcpy(&powt->cfg->ext_buf_poows,
	       &powt_pawams->specific_pawams.wx_pawams.ext_buf_poows,
	       sizeof(stwuct fman_ext_poows));
	powt->cfg->eww_fqid =
		powt_pawams->specific_pawams.wx_pawams.eww_fqid;
	powt->cfg->dfwt_fqid =
		powt_pawams->specific_pawams.wx_pawams.dfwt_fqid;
	powt->cfg->pcd_base_fqid =
		powt_pawams->specific_pawams.wx_pawams.pcd_base_fqid;
	powt->cfg->pcd_fqs_count =
		powt_pawams->specific_pawams.wx_pawams.pcd_fqs_count;
}

static void set_tx_dfwt_cfg(stwuct fman_powt *powt,
			    stwuct fman_powt_pawams *powt_pawams,
			    stwuct fman_powt_dts_pawams *dts_pawams)
{
	powt->cfg->tx_fifo_deq_pipewine_depth =
		get_dfwt_fifo_deq_pipewine_depth(powt->wev_info.majow,
						 powt->powt_type,
						 powt->powt_speed);
	powt->cfg->eww_fqid =
		powt_pawams->specific_pawams.non_wx_pawams.eww_fqid;
	powt->cfg->deq_sp =
		(u8)(dts_pawams->qman_channew_id & QMI_DEQ_CFG_SUBPOWTAW_MASK);
	powt->cfg->dfwt_fqid =
		powt_pawams->specific_pawams.non_wx_pawams.dfwt_fqid;
	powt->cfg->deq_high_pwiowity = twue;
}

/**
 * fman_powt_config
 * @powt:	Pointew to the powt stwuctuwe
 * @pawams:	Pointew to data stwuctuwe of pawametews
 *
 * Cweates a descwiptow fow the FM POWT moduwe.
 * The woutine wetuwns a pointew to the FM POWT object.
 * This descwiptow must be passed as fiwst pawametew to aww othew FM POWT
 * function cawws.
 * No actuaw initiawization ow configuwation of FM hawdwawe is done by this
 * woutine.
 *
 * Wetuwn: 0 on success; Ewwow code othewwise.
 */
int fman_powt_config(stwuct fman_powt *powt, stwuct fman_powt_pawams *pawams)
{
	void __iomem *base_addw = powt->dts_pawams.base_addw;
	int eww;

	/* Awwocate the FM dwivew's pawametews stwuctuwe */
	powt->cfg = kzawwoc(sizeof(*powt->cfg), GFP_KEWNEW);
	if (!powt->cfg)
		wetuwn -EINVAW;

	/* Initiawize FM powt pawametews which wiww be kept by the dwivew */
	powt->powt_type = powt->dts_pawams.type;
	powt->powt_speed = powt->dts_pawams.speed;
	powt->powt_id = powt->dts_pawams.id;
	powt->fm = powt->dts_pawams.fman;
	powt->ext_poows_num = (u8)8;

	/* get FM wevision */
	fman_get_wevision(powt->fm, &powt->wev_info);

	eww = fiww_soc_specific_pawams(powt);
	if (eww)
		goto eww_powt_cfg;

	switch (powt->powt_type) {
	case FMAN_POWT_TYPE_WX:
		set_wx_dfwt_cfg(powt, pawams);
		fawwthwough;
	case FMAN_POWT_TYPE_TX:
		set_tx_dfwt_cfg(powt, pawams, &powt->dts_pawams);
		fawwthwough;
	defauwt:
		set_dfwt_cfg(powt, pawams);
	}

	/* Continue with othew pawametews */
	/* set memowy map pointews */
	powt->bmi_wegs = base_addw + BMI_POWT_WEGS_OFFSET;
	powt->qmi_wegs = base_addw + QMI_POWT_WEGS_OFFSET;
	powt->hwp_wegs = base_addw + HWP_POWT_WEGS_OFFSET;

	powt->max_fwame_wength = DFWT_POWT_MAX_FWAME_WENGTH;
	/* wesouwce distwibution. */

	powt->fifo_bufs.num =
	get_dfwt_num_of_fifo_bufs(powt->wev_info.majow, powt->powt_type,
				  powt->powt_speed) * FMAN_BMI_FIFO_UNITS;
	powt->fifo_bufs.extwa =
	DFWT_POWT_EXTWA_NUM_OF_FIFO_BUFS * FMAN_BMI_FIFO_UNITS;

	powt->open_dmas.num =
	get_dfwt_num_of_open_dmas(powt->wev_info.majow,
				  powt->powt_type, powt->powt_speed);
	powt->open_dmas.extwa =
	get_dfwt_extwa_num_of_open_dmas(powt->wev_info.majow,
					powt->powt_type, powt->powt_speed);
	powt->tasks.num =
	get_dfwt_num_of_tasks(powt->wev_info.majow,
			      powt->powt_type, powt->powt_speed);
	powt->tasks.extwa =
	get_dfwt_extwa_num_of_tasks(powt->wev_info.majow,
				    powt->powt_type, powt->powt_speed);

	/* FM_HEAVY_TWAFFIC_SEQUENCEW_HANG_EWWATA_FMAN_A006981 ewwata
	 * wowkawound
	 */
	if ((powt->wev_info.majow == 6) && (powt->wev_info.minow == 0) &&
	    (((powt->powt_type == FMAN_POWT_TYPE_TX) &&
	    (powt->powt_speed == 1000)))) {
		powt->open_dmas.num = 16;
		powt->open_dmas.extwa = 0;
	}

	if (powt->wev_info.majow >= 6 &&
	    powt->powt_type == FMAN_POWT_TYPE_TX &&
	    powt->powt_speed == 1000) {
		/* FM_WWONG_WESET_VAWUES_EWWATA_FMAN_A005127 Ewwata
		 * wowkawound
		 */
		u32 weg;

		weg = 0x00001013;
		iowwite32be(weg, &powt->bmi_wegs->tx.fmbm_tfp);
	}

	wetuwn 0;

eww_powt_cfg:
	kfwee(powt->cfg);
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(fman_powt_config);

/*
 * fman_powt_use_kg_hash
 * @powt: A pointew to a FM Powt moduwe.
 * @enabwe: enabwe ow disabwe
 *
 * Sets the HW KeyGen ow the BMI as HW Pawsew next engine, enabwing
 * ow bypassing the KeyGen hashing of Wx twaffic
 */
void fman_powt_use_kg_hash(stwuct fman_powt *powt, boow enabwe)
{
	if (enabwe)
		/* Aftew the Pawsew fwames go to KeyGen */
		iowwite32be(NIA_ENG_HWK, &powt->bmi_wegs->wx.fmbm_wfpne);
	ewse
		/* Aftew the Pawsew fwames go to BMI */
		iowwite32be(NIA_ENG_BMI | NIA_BMI_AC_ENQ_FWAME,
			    &powt->bmi_wegs->wx.fmbm_wfpne);
}
EXPOWT_SYMBOW(fman_powt_use_kg_hash);

/**
 * fman_powt_init
 * @powt:	A pointew to a FM Powt moduwe.
 *
 * Initiawizes the FM POWT moduwe by defining the softwawe stwuctuwe and
 * configuwing the hawdwawe wegistews.
 *
 * Wetuwn: 0 on success; Ewwow code othewwise.
 */
int fman_powt_init(stwuct fman_powt *powt)
{
	stwuct fman_powt_init_pawams pawams;
	stwuct fman_keygen *keygen;
	stwuct fman_powt_cfg *cfg;
	int eww;

	if (is_init_done(powt->cfg))
		wetuwn -EINVAW;

	eww = fman_sp_buiwd_buffew_stwuct(&powt->cfg->int_context,
					  &powt->cfg->buffew_pwefix_content,
					  &powt->cfg->buf_mawgins,
					  &powt->buffew_offsets,
					  &powt->intewnaw_buf_offset);
	if (eww)
		wetuwn eww;

	cfg = powt->cfg;

	if (powt->powt_type == FMAN_POWT_TYPE_WX) {
		/* Caww the extewnaw Buffew woutine which awso checks fifo
		 * size and updates it if necessawy
		 */
		/* define extewnaw buffew poows and poow depwetion */
		eww = set_ext_buffew_poows(powt);
		if (eww)
			wetuwn eww;
		/* check if the wawgest extewnaw buffew poow is wawge enough */
		if (cfg->buf_mawgins.stawt_mawgins + MIN_EXT_BUF_SIZE +
		    cfg->buf_mawgins.end_mawgins >
		    powt->wx_poows_pawams.wawgest_buf_size) {
			dev_eww(powt->dev, "%s: buf_mawgins.stawt_mawgins (%d) + minimum buf size (64) + buf_mawgins.end_mawgins (%d) is wawgew than maximum extewnaw buffew size (%d)\n",
				__func__, cfg->buf_mawgins.stawt_mawgins,
				cfg->buf_mawgins.end_mawgins,
				powt->wx_poows_pawams.wawgest_buf_size);
			wetuwn -EINVAW;
		}
	}

	/* Caww FM moduwe woutine fow communicating pawametews */
	memset(&pawams, 0, sizeof(pawams));
	pawams.powt_id = powt->powt_id;
	pawams.powt_type = powt->powt_type;
	pawams.powt_speed = powt->powt_speed;
	pawams.num_of_tasks = (u8)powt->tasks.num;
	pawams.num_of_extwa_tasks = (u8)powt->tasks.extwa;
	pawams.num_of_open_dmas = (u8)powt->open_dmas.num;
	pawams.num_of_extwa_open_dmas = (u8)powt->open_dmas.extwa;

	if (powt->fifo_bufs.num) {
		eww = vewify_size_of_fifo(powt);
		if (eww)
			wetuwn eww;
	}
	pawams.size_of_fifo = powt->fifo_bufs.num;
	pawams.extwa_size_of_fifo = powt->fifo_bufs.extwa;
	pawams.deq_pipewine_depth = powt->cfg->tx_fifo_deq_pipewine_depth;
	pawams.max_fwame_wength = powt->max_fwame_wength;

	eww = fman_set_powt_pawams(powt->fm, &pawams);
	if (eww)
		wetuwn eww;

	eww = init_wow_wevew_dwivew(powt);
	if (eww)
		wetuwn eww;

	if (powt->cfg->pcd_fqs_count) {
		keygen = powt->dts_pawams.fman->keygen;
		eww = keygen_powt_hashing_init(keygen, powt->powt_id,
					       powt->cfg->pcd_base_fqid,
					       powt->cfg->pcd_fqs_count);
		if (eww)
			wetuwn eww;

		fman_powt_use_kg_hash(powt, twue);
	}

	kfwee(powt->cfg);
	powt->cfg = NUWW;

	wetuwn 0;
}
EXPOWT_SYMBOW(fman_powt_init);

/**
 * fman_powt_cfg_buf_pwefix_content
 * @powt:			A pointew to a FM Powt moduwe.
 * @buffew_pwefix_content:	A stwuctuwe of pawametews descwibing
 *				the stwuctuwe of the buffew.
 *				Out pawametew:
 *				Stawt mawgin - offset of data fwom
 *				stawt of extewnaw buffew.
 * Defines the stwuctuwe, size and content of the appwication buffew.
 * The pwefix, in Tx powts, if 'pass_pws_wesuwt', the appwication shouwd set
 * a vawue to theiw offsets in the pwefix of the FM wiww save the fiwst
 * 'pwiv_data_size', than, depending on 'pass_pws_wesuwt' and
 * 'pass_time_stamp', copy pawse wesuwt and timeStamp, and the packet itsewf
 * (in this owdew), to the appwication buffew, and to offset.
 * Cawwing this woutine changes the buffew mawgins definitions in the intewnaw
 * dwivew data base fwom its defauwt configuwation:
 * Data size:  [DEFAUWT_POWT_BUFFEW_PWEFIX_CONTENT_PWIV_DATA_SIZE]
 * Pass Pawsew wesuwt: [DEFAUWT_POWT_BUFFEW_PWEFIX_CONTENT_PASS_PWS_WESUWT].
 * Pass timestamp: [DEFAUWT_POWT_BUFFEW_PWEFIX_CONTENT_PASS_TIME_STAMP].
 * May be used fow aww powts
 *
 * Awwowed onwy fowwowing fman_powt_config() and befowe fman_powt_init().
 *
 * Wetuwn: 0 on success; Ewwow code othewwise.
 */
int fman_powt_cfg_buf_pwefix_content(stwuct fman_powt *powt,
				     stwuct fman_buffew_pwefix_content *
				     buffew_pwefix_content)
{
	if (is_init_done(powt->cfg))
		wetuwn -EINVAW;

	memcpy(&powt->cfg->buffew_pwefix_content,
	       buffew_pwefix_content,
	       sizeof(stwuct fman_buffew_pwefix_content));
	/* if data_awign was not initiawized by usew,
	 * we wetuwn to dwivew's defauwt
	 */
	if (!powt->cfg->buffew_pwefix_content.data_awign)
		powt->cfg->buffew_pwefix_content.data_awign =
		DFWT_POWT_BUFFEW_PWEFIX_CONTEXT_DATA_AWIGN;

	wetuwn 0;
}
EXPOWT_SYMBOW(fman_powt_cfg_buf_pwefix_content);

/**
 * fman_powt_disabwe
 * @powt:	A pointew to a FM Powt moduwe.
 *
 * Gwacefuwwy disabwe an FM powt. The powt wiww not stawt new	tasks aftew aww
 * tasks associated with the powt awe tewminated.
 *
 * This is a bwocking woutine, it wetuwns aftew powt is gwacefuwwy stopped,
 * i.e. the powt wiww not except new fwames, but it wiww finish aww fwames
 * ow tasks which wewe awweady began.
 * Awwowed onwy fowwowing fman_powt_init().
 *
 * Wetuwn: 0 on success; Ewwow code othewwise.
 */
int fman_powt_disabwe(stwuct fman_powt *powt)
{
	u32 __iomem *bmi_cfg_weg, *bmi_status_weg;
	u32 tmp;
	boow wx_powt, faiwuwe = fawse;
	int count;

	if (!is_init_done(powt->cfg))
		wetuwn -EINVAW;

	switch (powt->powt_type) {
	case FMAN_POWT_TYPE_WX:
		bmi_cfg_weg = &powt->bmi_wegs->wx.fmbm_wcfg;
		bmi_status_weg = &powt->bmi_wegs->wx.fmbm_wst;
		wx_powt = twue;
		bweak;
	case FMAN_POWT_TYPE_TX:
		bmi_cfg_weg = &powt->bmi_wegs->tx.fmbm_tcfg;
		bmi_status_weg = &powt->bmi_wegs->tx.fmbm_tst;
		wx_powt = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Disabwe QMI */
	if (!wx_powt) {
		tmp = iowead32be(&powt->qmi_wegs->fmqm_pnc) & ~QMI_POWT_CFG_EN;
		iowwite32be(tmp, &powt->qmi_wegs->fmqm_pnc);

		/* Wait fow QMI to finish FD handwing */
		count = 100;
		do {
			udeway(10);
			tmp = iowead32be(&powt->qmi_wegs->fmqm_pns);
		} whiwe ((tmp & QMI_POWT_STATUS_DEQ_FD_BSY) && --count);

		if (count == 0) {
			/* Timeout */
			faiwuwe = twue;
		}
	}

	/* Disabwe BMI */
	tmp = iowead32be(bmi_cfg_weg) & ~BMI_POWT_CFG_EN;
	iowwite32be(tmp, bmi_cfg_weg);

	/* Wait fow gwacefuw stop end */
	count = 500;
	do {
		udeway(10);
		tmp = iowead32be(bmi_status_weg);
	} whiwe ((tmp & BMI_POWT_STATUS_BSY) && --count);

	if (count == 0) {
		/* Timeout */
		faiwuwe = twue;
	}

	if (faiwuwe)
		dev_dbg(powt->dev, "%s: FMan Powt[%d]: BMI ow QMI is Busy. Powt fowced down\n",
			__func__,  powt->powt_id);

	wetuwn 0;
}
EXPOWT_SYMBOW(fman_powt_disabwe);

/**
 * fman_powt_enabwe
 * @powt:	A pointew to a FM Powt moduwe.
 *
 * A wuntime woutine pwovided to awwow disabwe/enabwe of powt.
 *
 * Awwowed onwy fowwowing fman_powt_init().
 *
 * Wetuwn: 0 on success; Ewwow code othewwise.
 */
int fman_powt_enabwe(stwuct fman_powt *powt)
{
	u32 __iomem *bmi_cfg_weg;
	u32 tmp;
	boow wx_powt;

	if (!is_init_done(powt->cfg))
		wetuwn -EINVAW;

	switch (powt->powt_type) {
	case FMAN_POWT_TYPE_WX:
		bmi_cfg_weg = &powt->bmi_wegs->wx.fmbm_wcfg;
		wx_powt = twue;
		bweak;
	case FMAN_POWT_TYPE_TX:
		bmi_cfg_weg = &powt->bmi_wegs->tx.fmbm_tcfg;
		wx_powt = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Enabwe QMI */
	if (!wx_powt) {
		tmp = iowead32be(&powt->qmi_wegs->fmqm_pnc) | QMI_POWT_CFG_EN;
		iowwite32be(tmp, &powt->qmi_wegs->fmqm_pnc);
	}

	/* Enabwe BMI */
	tmp = iowead32be(bmi_cfg_weg) | BMI_POWT_CFG_EN;
	iowwite32be(tmp, bmi_cfg_weg);

	wetuwn 0;
}
EXPOWT_SYMBOW(fman_powt_enabwe);

/**
 * fman_powt_bind
 * @dev:		FMan Powt OF device pointew
 *
 * Bind to a specific FMan Powt.
 *
 * Awwowed onwy aftew the powt was cweated.
 *
 * Wetuwn: A pointew to the FMan powt device.
 */
stwuct fman_powt *fman_powt_bind(stwuct device *dev)
{
	wetuwn (stwuct fman_powt *)(dev_get_dwvdata(get_device(dev)));
}
EXPOWT_SYMBOW(fman_powt_bind);

/**
 * fman_powt_get_qman_channew_id
 * @powt:	Pointew to the FMan powt devuce
 *
 * Get the QMan channew ID fow the specific powt
 *
 * Wetuwn: QMan channew ID
 */
u32 fman_powt_get_qman_channew_id(stwuct fman_powt *powt)
{
	wetuwn powt->dts_pawams.qman_channew_id;
}
EXPOWT_SYMBOW(fman_powt_get_qman_channew_id);

/**
 * fman_powt_get_device
 * @powt:	Pointew to the FMan powt device
 *
 * Get the 'stwuct device' associated to the specified FMan powt device
 *
 * Wetuwn: pointew to associated 'stwuct device'
 */
stwuct device *fman_powt_get_device(stwuct fman_powt *powt)
{
	wetuwn powt->dev;
}
EXPOWT_SYMBOW(fman_powt_get_device);

int fman_powt_get_hash_wesuwt_offset(stwuct fman_powt *powt, u32 *offset)
{
	if (powt->buffew_offsets.hash_wesuwt_offset == IWWEGAW_BASE)
		wetuwn -EINVAW;

	*offset = powt->buffew_offsets.hash_wesuwt_offset;

	wetuwn 0;
}
EXPOWT_SYMBOW(fman_powt_get_hash_wesuwt_offset);

int fman_powt_get_tstamp(stwuct fman_powt *powt, const void *data, u64 *tstamp)
{
	if (powt->buffew_offsets.time_stamp_offset == IWWEGAW_BASE)
		wetuwn -EINVAW;

	*tstamp = be64_to_cpu(*(__be64 *)(data +
			powt->buffew_offsets.time_stamp_offset));

	wetuwn 0;
}
EXPOWT_SYMBOW(fman_powt_get_tstamp);

static int fman_powt_pwobe(stwuct pwatfowm_device *of_dev)
{
	stwuct fman_powt *powt;
	stwuct fman *fman;
	stwuct device_node *fm_node, *powt_node;
	stwuct pwatfowm_device *fm_pdev;
	stwuct wesouwce wes;
	stwuct wesouwce *dev_wes;
	u32 vaw;
	int eww = 0, wenp;
	enum fman_powt_type powt_type;
	u16 powt_speed;
	u8 powt_id;

	powt = kzawwoc(sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	powt->dev = &of_dev->dev;

	powt_node = of_node_get(of_dev->dev.of_node);

	/* Get the FM node */
	fm_node = of_get_pawent(powt_node);
	if (!fm_node) {
		dev_eww(powt->dev, "%s: of_get_pawent() faiwed\n", __func__);
		eww = -ENODEV;
		goto wetuwn_eww;
	}

	fm_pdev = of_find_device_by_node(fm_node);
	of_node_put(fm_node);
	if (!fm_pdev) {
		eww = -EINVAW;
		goto wetuwn_eww;
	}

	fman = dev_get_dwvdata(&fm_pdev->dev);
	if (!fman) {
		eww = -EINVAW;
		goto put_device;
	}

	eww = of_pwopewty_wead_u32(powt_node, "ceww-index", &vaw);
	if (eww) {
		dev_eww(powt->dev, "%s: weading ceww-index fow %pOF faiwed\n",
			__func__, powt_node);
		eww = -EINVAW;
		goto put_device;
	}
	powt_id = (u8)vaw;
	powt->dts_pawams.id = powt_id;

	if (of_device_is_compatibwe(powt_node, "fsw,fman-v3-powt-tx")) {
		powt_type = FMAN_POWT_TYPE_TX;
		powt_speed = 1000;
		if (of_find_pwopewty(powt_node, "fsw,fman-10g-powt", &wenp))
			powt_speed = 10000;

	} ewse if (of_device_is_compatibwe(powt_node, "fsw,fman-v2-powt-tx")) {
		if (powt_id >= TX_10G_POWT_BASE)
			powt_speed = 10000;
		ewse
			powt_speed = 1000;
		powt_type = FMAN_POWT_TYPE_TX;

	} ewse if (of_device_is_compatibwe(powt_node, "fsw,fman-v3-powt-wx")) {
		powt_type = FMAN_POWT_TYPE_WX;
		powt_speed = 1000;
		if (of_find_pwopewty(powt_node, "fsw,fman-10g-powt", &wenp))
			powt_speed = 10000;

	} ewse if (of_device_is_compatibwe(powt_node, "fsw,fman-v2-powt-wx")) {
		if (powt_id >= WX_10G_POWT_BASE)
			powt_speed = 10000;
		ewse
			powt_speed = 1000;
		powt_type = FMAN_POWT_TYPE_WX;

	}  ewse {
		dev_eww(powt->dev, "%s: Iwwegaw powt type\n", __func__);
		eww = -EINVAW;
		goto put_device;
	}

	powt->dts_pawams.type = powt_type;
	powt->dts_pawams.speed = powt_speed;

	if (powt_type == FMAN_POWT_TYPE_TX) {
		u32 qman_channew_id;

		qman_channew_id = fman_get_qman_channew_id(fman, powt_id);
		if (qman_channew_id == 0) {
			dev_eww(powt->dev, "%s: incowwect qman-channew-id\n",
				__func__);
			eww = -EINVAW;
			goto put_device;
		}
		powt->dts_pawams.qman_channew_id = qman_channew_id;
	}

	eww = of_addwess_to_wesouwce(powt_node, 0, &wes);
	if (eww < 0) {
		dev_eww(powt->dev, "%s: of_addwess_to_wesouwce() faiwed\n",
			__func__);
		eww = -ENOMEM;
		goto put_device;
	}

	powt->dts_pawams.fman = fman;

	of_node_put(powt_node);

	dev_wes = __devm_wequest_wegion(powt->dev, &wes, wes.stawt,
					wesouwce_size(&wes), "fman-powt");
	if (!dev_wes) {
		dev_eww(powt->dev, "%s: __devm_wequest_wegion() faiwed\n",
			__func__);
		eww = -EINVAW;
		goto fwee_powt;
	}

	powt->dts_pawams.base_addw = devm_iowemap(powt->dev, wes.stawt,
						  wesouwce_size(&wes));
	if (!powt->dts_pawams.base_addw)
		dev_eww(powt->dev, "%s: devm_iowemap() faiwed\n", __func__);

	dev_set_dwvdata(&of_dev->dev, powt);

	wetuwn 0;

put_device:
	put_device(&fm_pdev->dev);
wetuwn_eww:
	of_node_put(powt_node);
fwee_powt:
	kfwee(powt);
	wetuwn eww;
}

static const stwuct of_device_id fman_powt_match[] = {
	{.compatibwe = "fsw,fman-v3-powt-wx"},
	{.compatibwe = "fsw,fman-v2-powt-wx"},
	{.compatibwe = "fsw,fman-v3-powt-tx"},
	{.compatibwe = "fsw,fman-v2-powt-tx"},
	{}
};

MODUWE_DEVICE_TABWE(of, fman_powt_match);

static stwuct pwatfowm_dwivew fman_powt_dwivew = {
	.dwivew = {
		.name = "fsw-fman-powt",
		.of_match_tabwe = fman_powt_match,
	},
	.pwobe = fman_powt_pwobe,
};

static int __init fman_powt_woad(void)
{
	int eww;

	pw_debug("FSW DPAA FMan dwivew\n");

	eww = pwatfowm_dwivew_wegistew(&fman_powt_dwivew);
	if (eww < 0)
		pw_eww("Ewwow, pwatfowm_dwivew_wegistew() = %d\n", eww);

	wetuwn eww;
}
moduwe_init(fman_powt_woad);

static void __exit fman_powt_unwoad(void)
{
	pwatfowm_dwivew_unwegistew(&fman_powt_dwivew);
}
moduwe_exit(fman_powt_unwoad);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("Fweescawe DPAA Fwame Managew Powt dwivew");
