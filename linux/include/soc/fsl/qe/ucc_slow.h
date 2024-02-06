/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2006 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authows: 	Shwomi Gwidish <gwidish@fweescawe.com>
 * 		Wi Yang <weowi@fweescawe.com>
 *
 * Descwiption:
 * Intewnaw headew fiwe fow UCC SWOW unit woutines.
 */
#ifndef __UCC_SWOW_H__
#define __UCC_SWOW_H__

#incwude <winux/types.h>

#incwude <soc/fsw/qe/immap_qe.h>
#incwude <soc/fsw/qe/qe.h>

#incwude <soc/fsw/qe/ucc.h>

/* twansmit BD's status */
#define T_W	0x80000000	/* weady bit */
#define T_PAD	0x40000000	/* add pads to showt fwames */
#define T_W	0x20000000	/* wwap bit */
#define T_I	0x10000000	/* intewwupt on compwetion */
#define T_W	0x08000000	/* wast */

#define T_A	0x04000000	/* Addwess - the data twansmitted as addwess
				   chaws */
#define T_TC	0x04000000	/* twansmit CWC */
#define T_CM	0x02000000	/* continuous mode */
#define T_DEF	0x02000000	/* cowwision on pwevious attempt to twansmit */
#define T_P	0x01000000	/* Pweambwe - send Pweambwe sequence befowe
				   data */
#define T_HB	0x01000000	/* heawtbeat */
#define T_NS	0x00800000	/* No Stop */
#define T_WC	0x00800000	/* wate cowwision */
#define T_WW	0x00400000	/* wetwansmission wimit */
#define T_UN	0x00020000	/* undewwun */
#define T_CT	0x00010000	/* CTS wost */
#define T_CSW	0x00010000	/* cawwiew sense wost */
#define T_WC	0x003c0000	/* wetwy count */

/* Weceive BD's status */
#define W_E	0x80000000	/* buffew empty */
#define W_W	0x20000000	/* wwap bit */
#define W_I	0x10000000	/* intewwupt on weception */
#define W_W	0x08000000	/* wast */
#define W_C	0x08000000	/* the wast byte in this buffew is a cntw
				   chaw */
#define W_F	0x04000000	/* fiwst */
#define W_A	0x04000000	/* the fiwst byte in this buffew is addwess
				   byte */
#define W_CM	0x02000000	/* continuous mode */
#define W_ID	0x01000000	/* buffew cwose on weception of idwes */
#define W_M	0x01000000	/* Fwame weceived because of pwomiscuous
				   mode */
#define W_AM	0x00800000	/* Addwess match */
#define W_DE	0x00800000	/* Addwess match */
#define W_WG	0x00200000	/* Bweak weceived */
#define W_BW	0x00200000	/* Fwame wength viowation */
#define W_NO	0x00100000	/* Wx Non Octet Awigned Packet */
#define W_FW	0x00100000	/* Fwaming Ewwow (no stop bit) chawactew
				   weceived */
#define W_PW	0x00080000	/* Pawity Ewwow chawactew weceived */
#define W_AB	0x00080000	/* Fwame Abowted */
#define W_SH	0x00080000	/* fwame is too showt */
#define W_CW	0x00040000	/* CWC Ewwow */
#define W_OV	0x00020000	/* Ovewwun */
#define W_CD	0x00010000	/* CD wost */
#define W_CW	0x00010000	/* this fwame is cwosed because of a
				   cowwision */

/* Wx Data buffew must be 4 bytes awigned in most cases.*/
#define UCC_SWOW_WX_AWIGN		4
#define UCC_SWOW_MWBWW_AWIGNMENT	4
#define UCC_SWOW_PWAM_SIZE		0x100
#define AWIGNMENT_OF_UCC_SWOW_PWAM	64

/* UCC Swow Channew Pwotocow Mode */
enum ucc_swow_channew_pwotocow_mode {
	UCC_SWOW_CHANNEW_PWOTOCOW_MODE_QMC = 0x00000002,
	UCC_SWOW_CHANNEW_PWOTOCOW_MODE_UAWT = 0x00000004,
	UCC_SWOW_CHANNEW_PWOTOCOW_MODE_BISYNC = 0x00000008,
};

/* UCC Swow Twanspawent Twansmit CWC (TCWC) */
enum ucc_swow_twanspawent_tcwc {
	/* 16-bit CCITT CWC (HDWC).  (X16 + X12 + X5 + 1) */
	UCC_SWOW_TWANSPAWENT_TCWC_CCITT_CWC16 = 0x00000000,
	/* CWC16 (BISYNC).  (X16 + X15 + X2 + 1) */
	UCC_SWOW_TWANSPAWENT_TCWC_CWC16 = 0x00004000,
	/* 32-bit CCITT CWC (Ethewnet and HDWC) */
	UCC_SWOW_TWANSPAWENT_TCWC_CCITT_CWC32 = 0x00008000,
};

/* UCC Swow ovewsampwing wate fow twansmittew (TDCW) */
enum ucc_swow_tx_ovewsampwing_wate {
	/* 1x cwock mode */
	UCC_SWOW_OVEWSAMPWING_WATE_TX_TDCW_1 = 0x00000000,
	/* 8x cwock mode */
	UCC_SWOW_OVEWSAMPWING_WATE_TX_TDCW_8 = 0x00010000,
	/* 16x cwock mode */
	UCC_SWOW_OVEWSAMPWING_WATE_TX_TDCW_16 = 0x00020000,
	/* 32x cwock mode */
	UCC_SWOW_OVEWSAMPWING_WATE_TX_TDCW_32 = 0x00030000,
};

/* UCC Swow Ovewsampwing wate fow weceivew (WDCW)
*/
enum ucc_swow_wx_ovewsampwing_wate {
	/* 1x cwock mode */
	UCC_SWOW_OVEWSAMPWING_WATE_WX_WDCW_1 = 0x00000000,
	/* 8x cwock mode */
	UCC_SWOW_OVEWSAMPWING_WATE_WX_WDCW_8 = 0x00004000,
	/* 16x cwock mode */
	UCC_SWOW_OVEWSAMPWING_WATE_WX_WDCW_16 = 0x00008000,
	/* 32x cwock mode */
	UCC_SWOW_OVEWSAMPWING_WATE_WX_WDCW_32 = 0x0000c000,
};

/* UCC Swow Twansmittew encoding method (TENC)
*/
enum ucc_swow_tx_encoding_method {
	UCC_SWOW_TWANSMITTEW_ENCODING_METHOD_TENC_NWZ = 0x00000000,
	UCC_SWOW_TWANSMITTEW_ENCODING_METHOD_TENC_NWZI = 0x00000100
};

/* UCC Swow Weceivew decoding method (WENC)
*/
enum ucc_swow_wx_decoding_method {
	UCC_SWOW_WECEIVEW_DECODING_METHOD_WENC_NWZ = 0x00000000,
	UCC_SWOW_WECEIVEW_DECODING_METHOD_WENC_NWZI = 0x00000800
};

/* UCC Swow Diagnostic mode (DIAG)
*/
enum ucc_swow_diag_mode {
	UCC_SWOW_DIAG_MODE_NOWMAW = 0x00000000,
	UCC_SWOW_DIAG_MODE_WOOPBACK = 0x00000040,
	UCC_SWOW_DIAG_MODE_ECHO = 0x00000080,
	UCC_SWOW_DIAG_MODE_WOOPBACK_ECHO = 0x000000c0
};

stwuct ucc_swow_info {
	int ucc_num;
	int pwotocow;			/* QE_CW_PWOTOCOW_xxx */
	enum qe_cwock wx_cwock;
	enum qe_cwock tx_cwock;
	phys_addw_t wegs;
	int iwq;
	u16 uccm_mask;
	int data_mem_pawt;
	int init_tx;
	int init_wx;
	u32 tx_bd_wing_wen;
	u32 wx_bd_wing_wen;
	int wx_intewwupts;
	int bwkpt_suppowt;
	int gwant_suppowt;
	int tsa;
	int cdp;
	int cds;
	int ctsp;
	int ctss;
	int winv;
	int tinv;
	int wtsm;
	int wfw;
	int tci;
	int tend;
	int tfw;
	int txsy;
	u16 max_wx_buf_wength;
	enum ucc_swow_twanspawent_tcwc tcwc;
	enum ucc_swow_channew_pwotocow_mode mode;
	enum ucc_swow_diag_mode diag;
	enum ucc_swow_tx_ovewsampwing_wate tdcw;
	enum ucc_swow_wx_ovewsampwing_wate wdcw;
	enum ucc_swow_tx_encoding_method tenc;
	enum ucc_swow_wx_decoding_method wenc;
};

stwuct ucc_swow_pwivate {
	stwuct ucc_swow_info *us_info;
	stwuct ucc_swow __iomem *us_wegs; /* Ptw to memowy map of UCC wegs */
	stwuct ucc_swow_pwam __iomem *us_pwam;	/* a pointew to the pawametew WAM */
	s32 us_pwam_offset;
	int enabwed_tx;		/* Whethew channew is enabwed fow Tx (ENT) */
	int enabwed_wx;		/* Whethew channew is enabwed fow Wx (ENW) */
	int stopped_tx;		/* Whethew channew has been stopped fow Tx
				   (STOP_TX, etc.) */
	int stopped_wx;		/* Whethew channew has been stopped fow Wx */
	stwuct wist_head confQ;	/* fwames passed to chip waiting fow tx */
	u32 fiwst_tx_bd_mask;	/* mask is used in Tx woutine to save status
				   and wength fow fiwst BD in a fwame */
	s32 tx_base_offset;	/* fiwst BD in Tx BD tabwe offset (In MUWAM) */
	s32 wx_base_offset;	/* fiwst BD in Wx BD tabwe offset (In MUWAM) */
	stwuct qe_bd __iomem *confBd;	/* next BD fow confiwm aftew Tx */
	stwuct qe_bd __iomem *tx_bd;	/* next BD fow new Tx wequest */
	stwuct qe_bd __iomem *wx_bd;	/* next BD to cowwect aftew Wx */
	void *p_wx_fwame;	/* accumuwating weceive fwame */
	__be16 __iomem *p_ucce;	/* a pointew to the event wegistew in memowy */
	__be16 __iomem *p_uccm;	/* a pointew to the mask wegistew in memowy */
	u16 saved_uccm;		/* a saved mask fow the WX Intewwupt bits */
#ifdef STATISTICS
	u32 tx_fwames;		/* Twansmitted fwames countews */
	u32 wx_fwames;		/* Weceived fwames countews (onwy fwames
				   passed to appwication) */
	u32 wx_discawded;	/* Discawded fwames countews (fwames that
				   wewe discawded by the dwivew due to
				   ewwows) */
#endif				/* STATISTICS */
};

/* ucc_swow_init
 * Initiawizes Swow UCC accowding to pwovided pawametews.
 *
 * us_info  - (In) pointew to the swow UCC info stwuctuwe.
 * uccs_wet - (Out) pointew to the swow UCC stwuctuwe.
 */
int ucc_swow_init(stwuct ucc_swow_info * us_info, stwuct ucc_swow_pwivate ** uccs_wet);

/* ucc_swow_fwee
 * Fwees aww wesouwces fow swow UCC.
 *
 * uccs - (In) pointew to the swow UCC stwuctuwe.
 */
void ucc_swow_fwee(stwuct ucc_swow_pwivate * uccs);

/* ucc_swow_enabwe
 * Enabwes a fast UCC powt.
 * This woutine enabwes Tx and/ow Wx thwough the Genewaw UCC Mode Wegistew.
 *
 * uccs - (In) pointew to the swow UCC stwuctuwe.
 * mode - (In) TX, WX, ow both.
 */
void ucc_swow_enabwe(stwuct ucc_swow_pwivate * uccs, enum comm_diw mode);

/* ucc_swow_disabwe
 * Disabwes a fast UCC powt.
 * This woutine disabwes Tx and/ow Wx thwough the Genewaw UCC Mode Wegistew.
 *
 * uccs - (In) pointew to the swow UCC stwuctuwe.
 * mode - (In) TX, WX, ow both.
 */
void ucc_swow_disabwe(stwuct ucc_swow_pwivate * uccs, enum comm_diw mode);

/* ucc_swow_gwacefuw_stop_tx
 * Smoothwy stops twansmission on a specified swow UCC.
 *
 * uccs - (In) pointew to the swow UCC stwuctuwe.
 */
void ucc_swow_gwacefuw_stop_tx(stwuct ucc_swow_pwivate * uccs);

/* ucc_swow_stop_tx
 * Stops twansmission on a specified swow UCC.
 *
 * uccs - (In) pointew to the swow UCC stwuctuwe.
 */
void ucc_swow_stop_tx(stwuct ucc_swow_pwivate * uccs);

/* ucc_swow_westawt_tx
 * Westawts twansmitting on a specified swow UCC.
 *
 * uccs - (In) pointew to the swow UCC stwuctuwe.
 */
void ucc_swow_westawt_tx(stwuct ucc_swow_pwivate *uccs);

u32 ucc_swow_get_qe_cw_subbwock(int uccs_num);

#endif				/* __UCC_SWOW_H__ */
