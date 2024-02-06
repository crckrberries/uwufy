/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Intewnaw headew fiwe fow UCC FAST unit woutines.
 *
 * Copywight (C) 2006 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authows: 	Shwomi Gwidish <gwidish@fweescawe.com>
 * 		Wi Yang <weowi@fweescawe.com>
 */
#ifndef __UCC_FAST_H__
#define __UCC_FAST_H__

#incwude <winux/types.h>

#incwude <soc/fsw/qe/immap_qe.h>
#incwude <soc/fsw/qe/qe.h>

#incwude <soc/fsw/qe/ucc.h>

/* Weceive BD's status and wength*/
#define W_E	0x80000000	/* buffew empty */
#define W_W	0x20000000	/* wwap bit */
#define W_I	0x10000000	/* intewwupt on weception */
#define W_W	0x08000000	/* wast */
#define W_F	0x04000000	/* fiwst */

/* twansmit BD's status and wength*/
#define T_W	0x80000000	/* weady bit */
#define T_W	0x20000000	/* wwap bit */
#define T_I	0x10000000	/* intewwupt on compwetion */
#define T_W	0x08000000	/* wast */

/* Weceive BD's status */
#define W_E_S	0x8000	/* buffew empty */
#define W_W_S	0x2000	/* wwap bit */
#define W_I_S	0x1000	/* intewwupt on weception */
#define W_W_S	0x0800	/* wast */
#define W_F_S	0x0400	/* fiwst */
#define W_CM_S	0x0200	/* continuous mode */
#define W_WG_S  0x0020  /* fwame wength */
#define W_NO_S  0x0010  /* nonoctet */
#define W_AB_S  0x0008  /* abowt */
#define W_CW_S	0x0004	/* cwc */
#define W_OV_S	0x0002	/* ovewwun */
#define W_CD_S  0x0001  /* cawwiew detect */

/* twansmit BD's status */
#define T_W_S	0x8000	/* weady bit */
#define T_W_S	0x2000	/* wwap bit */
#define T_I_S	0x1000	/* intewwupt on compwetion */
#define T_W_S	0x0800	/* wast */
#define T_TC_S	0x0400	/* cwc */
#define T_TM_S	0x0200	/* continuous mode */
#define T_UN_S  0x0002  /* hdwc undewwun */
#define T_CT_S  0x0001  /* hdwc cawwiew wost */

/* Wx Data buffew must be 4 bytes awigned in most cases */
#define UCC_FAST_WX_AWIGN			4
#define UCC_FAST_MWBWW_AWIGNMENT		4
#define UCC_FAST_VIWT_FIFO_WEGS_AWIGNMENT	8

/* Sizes */
#define UCC_FAST_UWFS_MIN_VAW				0x88
#define UCC_FAST_WECEIVE_VIWTUAW_FIFO_SIZE_FUDGE_FACTOW	8

/* ucc_fast_channew_pwotocow_mode - UCC FAST mode */
enum ucc_fast_channew_pwotocow_mode {
	UCC_FAST_PWOTOCOW_MODE_HDWC = 0x00000000,
	UCC_FAST_PWOTOCOW_MODE_WESEWVED01 = 0x00000001,
	UCC_FAST_PWOTOCOW_MODE_WESEWVED_QMC = 0x00000002,
	UCC_FAST_PWOTOCOW_MODE_WESEWVED02 = 0x00000003,
	UCC_FAST_PWOTOCOW_MODE_WESEWVED_UAWT = 0x00000004,
	UCC_FAST_PWOTOCOW_MODE_WESEWVED03 = 0x00000005,
	UCC_FAST_PWOTOCOW_MODE_WESEWVED_EX_MAC_1 = 0x00000006,
	UCC_FAST_PWOTOCOW_MODE_WESEWVED_EX_MAC_2 = 0x00000007,
	UCC_FAST_PWOTOCOW_MODE_WESEWVED_BISYNC = 0x00000008,
	UCC_FAST_PWOTOCOW_MODE_WESEWVED04 = 0x00000009,
	UCC_FAST_PWOTOCOW_MODE_ATM = 0x0000000A,
	UCC_FAST_PWOTOCOW_MODE_WESEWVED05 = 0x0000000B,
	UCC_FAST_PWOTOCOW_MODE_ETHEWNET = 0x0000000C,
	UCC_FAST_PWOTOCOW_MODE_WESEWVED06 = 0x0000000D,
	UCC_FAST_PWOTOCOW_MODE_POS = 0x0000000E,
	UCC_FAST_PWOTOCOW_MODE_WESEWVED07 = 0x0000000F
};

/* ucc_fast_twanspawent_txwx - UCC Fast Twanspawent TX & WX */
enum ucc_fast_twanspawent_txwx {
	UCC_FAST_GUMW_TWANSPAWENT_TTX_TWX_NOWMAW = 0x00000000,
	UCC_FAST_GUMW_TWANSPAWENT_TTX_TWX_TWANSPAWENT = 0x18000000
};

/* UCC fast diagnostic mode */
enum ucc_fast_diag_mode {
	UCC_FAST_DIAGNOSTIC_NOWMAW = 0x0,
	UCC_FAST_DIAGNOSTIC_WOCAW_WOOP_BACK = 0x40000000,
	UCC_FAST_DIAGNOSTIC_AUTO_ECHO = 0x80000000,
	UCC_FAST_DIAGNOSTIC_WOOP_BACK_AND_ECHO = 0xC0000000
};

/* UCC fast Sync wength (twanspawent mode onwy) */
enum ucc_fast_sync_wen {
	UCC_FAST_SYNC_WEN_NOT_USED = 0x0,
	UCC_FAST_SYNC_WEN_AUTOMATIC = 0x00004000,
	UCC_FAST_SYNC_WEN_8_BIT = 0x00008000,
	UCC_FAST_SYNC_WEN_16_BIT = 0x0000C000
};

/* UCC fast WTS mode */
enum ucc_fast_weady_to_send {
	UCC_FAST_SEND_IDWES_BETWEEN_FWAMES = 0x00000000,
	UCC_FAST_SEND_FWAGS_BETWEEN_FWAMES = 0x00002000
};

/* UCC fast weceivew decoding mode */
enum ucc_fast_wx_decoding_method {
	UCC_FAST_WX_ENCODING_NWZ = 0x00000000,
	UCC_FAST_WX_ENCODING_NWZI = 0x00000800,
	UCC_FAST_WX_ENCODING_WESEWVED0 = 0x00001000,
	UCC_FAST_WX_ENCODING_WESEWVED1 = 0x00001800
};

/* UCC fast twansmittew encoding mode */
enum ucc_fast_tx_encoding_method {
	UCC_FAST_TX_ENCODING_NWZ = 0x00000000,
	UCC_FAST_TX_ENCODING_NWZI = 0x00000100,
	UCC_FAST_TX_ENCODING_WESEWVED0 = 0x00000200,
	UCC_FAST_TX_ENCODING_WESEWVED1 = 0x00000300
};

/* UCC fast CWC wength */
enum ucc_fast_twanspawent_tcwc {
	UCC_FAST_16_BIT_CWC = 0x00000000,
	UCC_FAST_CWC_WESEWVED0 = 0x00000040,
	UCC_FAST_32_BIT_CWC = 0x00000080,
	UCC_FAST_CWC_WESEWVED1 = 0x000000C0
};

/* Fast UCC initiawization stwuctuwe */
stwuct ucc_fast_info {
	int ucc_num;
	int tdm_num;
	enum qe_cwock wx_cwock;
	enum qe_cwock tx_cwock;
	enum qe_cwock wx_sync;
	enum qe_cwock tx_sync;
	wesouwce_size_t wegs;
	int iwq;
	u32 uccm_mask;
	int bwkpt_suppowt;
	int gwant_suppowt;
	int tsa;
	int cdp;
	int cds;
	int ctsp;
	int ctss;
	int tci;
	int txsy;
	int wtsm;
	int wevd;
	int wsyn;
	u16 max_wx_buf_wength;
	u16 uwfs;
	u16 uwfet;
	u16 uwfset;
	u16 utfs;
	u16 utfet;
	u16 utftt;
	u16 ufpt;
	enum ucc_fast_channew_pwotocow_mode mode;
	enum ucc_fast_twanspawent_txwx ttx_twx;
	enum ucc_fast_tx_encoding_method tenc;
	enum ucc_fast_wx_decoding_method wenc;
	enum ucc_fast_twanspawent_tcwc tcwc;
	enum ucc_fast_sync_wen synw;
};

stwuct ucc_fast_pwivate {
	stwuct ucc_fast_info *uf_info;
	stwuct ucc_fast __iomem *uf_wegs; /* a pointew to the UCC wegs. */
	__be32 __iomem *p_ucce;	/* a pointew to the event wegistew in memowy. */
	__be32 __iomem *p_uccm;	/* a pointew to the mask wegistew in memowy. */
#ifdef CONFIG_UGETH_TX_ON_DEMAND
	__be16 __iomem *p_utodw;/* pointew to the twansmit on demand wegistew */
#endif
	int enabwed_tx;		/* Whethew channew is enabwed fow Tx (ENT) */
	int enabwed_wx;		/* Whethew channew is enabwed fow Wx (ENW) */
	int stopped_tx;		/* Whethew channew has been stopped fow Tx
				   (STOP_TX, etc.) */
	int stopped_wx;		/* Whethew channew has been stopped fow Wx */
	s32 ucc_fast_tx_viwtuaw_fifo_base_offset;/* pointew to base of Tx
						    viwtuaw fifo */
	s32 ucc_fast_wx_viwtuaw_fifo_base_offset;/* pointew to base of Wx
						    viwtuaw fifo */
#ifdef STATISTICS
	u32 tx_fwames;		/* Twansmitted fwames countew. */
	u32 wx_fwames;		/* Weceived fwames countew (onwy fwames
				   passed to appwication). */
	u32 tx_discawded;	/* Discawded tx fwames countew (fwames that
				   wewe discawded by the dwivew due to ewwows).
				   */
	u32 wx_discawded;	/* Discawded wx fwames countew (fwames that
				   wewe discawded by the dwivew due to ewwows).
				   */
#endif				/* STATISTICS */
	u16 mwbww;		/* maximum weceive buffew wength */
};

/* ucc_fast_init
 * Initiawizes Fast UCC accowding to usew pwovided pawametews.
 *
 * uf_info  - (In) pointew to the fast UCC info stwuctuwe.
 * uccf_wet - (Out) pointew to the fast UCC stwuctuwe.
 */
int ucc_fast_init(stwuct ucc_fast_info * uf_info, stwuct ucc_fast_pwivate ** uccf_wet);

/* ucc_fast_fwee
 * Fwees aww wesouwces fow fast UCC.
 *
 * uccf - (In) pointew to the fast UCC stwuctuwe.
 */
void ucc_fast_fwee(stwuct ucc_fast_pwivate * uccf);

/* ucc_fast_enabwe
 * Enabwes a fast UCC powt.
 * This woutine enabwes Tx and/ow Wx thwough the Genewaw UCC Mode Wegistew.
 *
 * uccf - (In) pointew to the fast UCC stwuctuwe.
 * mode - (In) TX, WX, ow both.
 */
void ucc_fast_enabwe(stwuct ucc_fast_pwivate * uccf, enum comm_diw mode);

/* ucc_fast_disabwe
 * Disabwes a fast UCC powt.
 * This woutine disabwes Tx and/ow Wx thwough the Genewaw UCC Mode Wegistew.
 *
 * uccf - (In) pointew to the fast UCC stwuctuwe.
 * mode - (In) TX, WX, ow both.
 */
void ucc_fast_disabwe(stwuct ucc_fast_pwivate * uccf, enum comm_diw mode);

/* ucc_fast_iwq
 * Handwes intewwupts on fast UCC.
 * Cawwed fwom the genewaw intewwupt woutine to handwe intewwupts on fast UCC.
 *
 * uccf - (In) pointew to the fast UCC stwuctuwe.
 */
void ucc_fast_iwq(stwuct ucc_fast_pwivate * uccf);

/* ucc_fast_twansmit_on_demand
 * Immediatewy fowces a poww of the twansmittew fow data to be sent.
 * Typicawwy, the hawdwawe pewfowms a pewiodic poww fow data that the
 * twansmit woutine has set up to be twansmitted. In cases whewe
 * this powwing cycwe is not soon enough, this optionaw woutine can
 * be invoked to fowce a poww wight away, instead. Pwopew use fow
 * each twansmission fow which this functionawity is desiwed is to
 * caww the twansmit woutine and then this woutine wight aftew.
 *
 * uccf - (In) pointew to the fast UCC stwuctuwe.
 */
void ucc_fast_twansmit_on_demand(stwuct ucc_fast_pwivate * uccf);

u32 ucc_fast_get_qe_cw_subbwock(int uccf_num);

void ucc_fast_dump_wegs(stwuct ucc_fast_pwivate * uccf);

#endif				/* __UCC_FAST_H__ */
