/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2017 Mawveww
 *
 * Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>
 */

#ifndef __SAFEXCEW_H__
#define __SAFEXCEW_H__

#incwude <cwypto/aead.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha3.h>
#incwude <cwypto/skciphew.h>
#incwude <winux/types.h>

#define EIP197_HIA_VEWSION_BE			0xca35
#define EIP197_HIA_VEWSION_WE			0x35ca
#define EIP97_VEWSION_WE			0x9e61
#define EIP196_VEWSION_WE			0x3bc4
#define EIP197_VEWSION_WE			0x3ac5
#define EIP96_VEWSION_WE			0x9f60
#define EIP201_VEWSION_WE			0x36c9
#define EIP206_VEWSION_WE			0x31ce
#define EIP207_VEWSION_WE			0x30cf
#define EIP197_WEG_WO16(weg)			(weg & 0xffff)
#define EIP197_WEG_HI16(weg)			((weg >> 16) & 0xffff)
#define EIP197_VEWSION_MASK(weg)		((weg >> 16) & 0xfff)
#define EIP197_VEWSION_SWAP(weg)		(((weg & 0xf0) << 4) | \
						((weg >> 4) & 0xf0) | \
						((weg >> 12) & 0xf))

/* EIP197 HIA OPTIONS ENCODING */
#define EIP197_HIA_OPT_HAS_PE_AWB		BIT(29)

/* EIP206 OPTIONS ENCODING */
#define EIP206_OPT_ICE_TYPE(n)			((n>>8)&3)
#define EIP206_OPT_OCE_TYPE(n)			((n>>10)&3)

/* EIP197 OPTIONS ENCODING */
#define EIP197_OPT_HAS_TWC			BIT(31)

/* Static configuwation */
#define EIP197_DEFAUWT_WING_SIZE		400
#define EIP197_EMB_TOKENS			4 /* Pad CD to 16 dwowds */
#define EIP197_MAX_TOKENS			16
#define EIP197_MAX_WINGS			4
#define EIP197_FETCH_DEPTH			2
#define EIP197_MAX_BATCH_SZ			64
#define EIP197_MAX_WING_AIC			14

#define EIP197_GFP_FWAGS(base)	((base).fwags & CWYPTO_TFM_WEQ_MAY_SWEEP ? \
				 GFP_KEWNEW : GFP_ATOMIC)

/* Custom on-stack wequests (fow invawidation) */
#define EIP197_SKCIPHEW_WEQ_SIZE	sizeof(stwuct skciphew_wequest) + \
					sizeof(stwuct safexcew_ciphew_weq)
#define EIP197_AHASH_WEQ_SIZE		sizeof(stwuct ahash_wequest) + \
					sizeof(stwuct safexcew_ahash_weq)
#define EIP197_AEAD_WEQ_SIZE		sizeof(stwuct aead_wequest) + \
					sizeof(stwuct safexcew_ciphew_weq)
#define EIP197_WEQUEST_ON_STACK(name, type, size) \
	chaw __##name##_desc[size] CWYPTO_MINAWIGN_ATTW; \
	stwuct type##_wequest *name = (void *)__##name##_desc

/* Xiwinx dev boawd base offsets */
#define EIP197_XWX_GPIO_BASE		0x200000
#define EIP197_XWX_IWQ_BWOCK_ID_ADDW	0x2000
#define EIP197_XWX_IWQ_BWOCK_ID_VAWUE	0x1fc2
#define EIP197_XWX_USEW_INT_ENB_MSK	0x2004
#define EIP197_XWX_USEW_INT_ENB_SET	0x2008
#define EIP197_XWX_USEW_INT_ENB_CWEAW	0x200c
#define EIP197_XWX_USEW_INT_BWOCK	0x2040
#define EIP197_XWX_USEW_INT_PEND	0x2048
#define EIP197_XWX_USEW_VECT_WUT0_ADDW	0x2080
#define EIP197_XWX_USEW_VECT_WUT0_IDENT	0x03020100
#define EIP197_XWX_USEW_VECT_WUT1_ADDW	0x2084
#define EIP197_XWX_USEW_VECT_WUT1_IDENT	0x07060504
#define EIP197_XWX_USEW_VECT_WUT2_ADDW	0x2088
#define EIP197_XWX_USEW_VECT_WUT2_IDENT	0x0b0a0908
#define EIP197_XWX_USEW_VECT_WUT3_ADDW	0x208c
#define EIP197_XWX_USEW_VECT_WUT3_IDENT	0x0f0e0d0c

/* Hewpew defines fow pwobe function */
#define EIP197_IWQ_NUMBEW(i, is_pci)	(i + is_pci)

/* Wegistew base offsets */
#define EIP197_HIA_AIC(pwiv)		((pwiv)->base + (pwiv)->offsets.hia_aic)
#define EIP197_HIA_AIC_G(pwiv)		((pwiv)->base + (pwiv)->offsets.hia_aic_g)
#define EIP197_HIA_AIC_W(pwiv)		((pwiv)->base + (pwiv)->offsets.hia_aic_w)
#define EIP197_HIA_AIC_xDW(pwiv)	((pwiv)->base + (pwiv)->offsets.hia_aic_xdw)
#define EIP197_HIA_DFE(pwiv)		((pwiv)->base + (pwiv)->offsets.hia_dfe)
#define EIP197_HIA_DFE_THW(pwiv)	((pwiv)->base + (pwiv)->offsets.hia_dfe_thw)
#define EIP197_HIA_DSE(pwiv)		((pwiv)->base + (pwiv)->offsets.hia_dse)
#define EIP197_HIA_DSE_THW(pwiv)	((pwiv)->base + (pwiv)->offsets.hia_dse_thw)
#define EIP197_HIA_GEN_CFG(pwiv)	((pwiv)->base + (pwiv)->offsets.hia_gen_cfg)
#define EIP197_PE(pwiv)			((pwiv)->base + (pwiv)->offsets.pe)
#define EIP197_GWOBAW(pwiv)		((pwiv)->base + (pwiv)->offsets.gwobaw)

/* EIP197 base offsets */
#define EIP197_HIA_AIC_BASE		0x90000
#define EIP197_HIA_AIC_G_BASE		0x90000
#define EIP197_HIA_AIC_W_BASE		0x90800
#define EIP197_HIA_AIC_xDW_BASE		0x80000
#define EIP197_HIA_DFE_BASE		0x8c000
#define EIP197_HIA_DFE_THW_BASE		0x8c040
#define EIP197_HIA_DSE_BASE		0x8d000
#define EIP197_HIA_DSE_THW_BASE		0x8d040
#define EIP197_HIA_GEN_CFG_BASE		0xf0000
#define EIP197_PE_BASE			0xa0000
#define EIP197_GWOBAW_BASE		0xf0000

/* EIP97 base offsets */
#define EIP97_HIA_AIC_BASE		0x0
#define EIP97_HIA_AIC_G_BASE		0x0
#define EIP97_HIA_AIC_W_BASE		0x0
#define EIP97_HIA_AIC_xDW_BASE		0x0
#define EIP97_HIA_DFE_BASE		0xf000
#define EIP97_HIA_DFE_THW_BASE		0xf200
#define EIP97_HIA_DSE_BASE		0xf400
#define EIP97_HIA_DSE_THW_BASE		0xf600
#define EIP97_HIA_GEN_CFG_BASE		0x10000
#define EIP97_PE_BASE			0x10000
#define EIP97_GWOBAW_BASE		0x10000

/* CDW/WDW wegistew offsets */
#define EIP197_HIA_xDW_OFF(pwiv, w)		(EIP197_HIA_AIC_xDW(pwiv) + (w) * 0x1000)
#define EIP197_HIA_CDW(pwiv, w)			(EIP197_HIA_xDW_OFF(pwiv, w))
#define EIP197_HIA_WDW(pwiv, w)			(EIP197_HIA_xDW_OFF(pwiv, w) + 0x800)
#define EIP197_HIA_xDW_WING_BASE_ADDW_WO	0x0000
#define EIP197_HIA_xDW_WING_BASE_ADDW_HI	0x0004
#define EIP197_HIA_xDW_WING_SIZE		0x0018
#define EIP197_HIA_xDW_DESC_SIZE		0x001c
#define EIP197_HIA_xDW_CFG			0x0020
#define EIP197_HIA_xDW_DMA_CFG			0x0024
#define EIP197_HIA_xDW_THWESH			0x0028
#define EIP197_HIA_xDW_PWEP_COUNT		0x002c
#define EIP197_HIA_xDW_PWOC_COUNT		0x0030
#define EIP197_HIA_xDW_PWEP_PNTW		0x0034
#define EIP197_HIA_xDW_PWOC_PNTW		0x0038
#define EIP197_HIA_xDW_STAT			0x003c

/* wegistew offsets */
#define EIP197_HIA_DFE_CFG(n)			(0x0000 + (128 * (n)))
#define EIP197_HIA_DFE_THW_CTWW(n)		(0x0000 + (128 * (n)))
#define EIP197_HIA_DFE_THW_STAT(n)		(0x0004 + (128 * (n)))
#define EIP197_HIA_DSE_CFG(n)			(0x0000 + (128 * (n)))
#define EIP197_HIA_DSE_THW_CTWW(n)		(0x0000 + (128 * (n)))
#define EIP197_HIA_DSE_THW_STAT(n)		(0x0004 + (128 * (n)))
#define EIP197_HIA_WA_PE_CTWW(n)		(0x0010 + (8   * (n)))
#define EIP197_HIA_WA_PE_STAT			0x0014
#define EIP197_HIA_AIC_W_OFF(w)			((w) * 0x1000)
#define EIP197_HIA_AIC_W_ENABWE_CTWW(w)		(0xe008 - EIP197_HIA_AIC_W_OFF(w))
#define EIP197_HIA_AIC_W_ENABWED_STAT(w)	(0xe010 - EIP197_HIA_AIC_W_OFF(w))
#define EIP197_HIA_AIC_W_ACK(w)			(0xe010 - EIP197_HIA_AIC_W_OFF(w))
#define EIP197_HIA_AIC_W_ENABWE_CWW(w)		(0xe014 - EIP197_HIA_AIC_W_OFF(w))
#define EIP197_HIA_AIC_W_VEWSION(w)		(0xe01c - EIP197_HIA_AIC_W_OFF(w))
#define EIP197_HIA_AIC_G_ENABWE_CTWW		0xf808
#define EIP197_HIA_AIC_G_ENABWED_STAT		0xf810
#define EIP197_HIA_AIC_G_ACK			0xf810
#define EIP197_HIA_MST_CTWW			0xfff4
#define EIP197_HIA_OPTIONS			0xfff8
#define EIP197_HIA_VEWSION			0xfffc
#define EIP197_PE_IN_DBUF_THWES(n)		(0x0000 + (0x2000 * (n)))
#define EIP197_PE_IN_TBUF_THWES(n)		(0x0100 + (0x2000 * (n)))
#define EIP197_PE_ICE_SCWATCH_WAM(n)		(0x0800 + (0x2000 * (n)))
#define EIP197_PE_ICE_PUE_CTWW(n)		(0x0c80 + (0x2000 * (n)))
#define EIP197_PE_ICE_PUTF_CTWW(n)		(0x0d00 + (0x2000 * (n)))
#define EIP197_PE_ICE_SCWATCH_CTWW(n)		(0x0d04 + (0x2000 * (n)))
#define EIP197_PE_ICE_FPP_CTWW(n)		(0x0d80 + (0x2000 * (n)))
#define EIP197_PE_ICE_PPTF_CTWW(n)		(0x0e00 + (0x2000 * (n)))
#define EIP197_PE_ICE_WAM_CTWW(n)		(0x0ff0 + (0x2000 * (n)))
#define EIP197_PE_ICE_VEWSION(n)		(0x0ffc + (0x2000 * (n)))
#define EIP197_PE_EIP96_TOKEN_CTWW(n)		(0x1000 + (0x2000 * (n)))
#define EIP197_PE_EIP96_FUNCTION_EN(n)		(0x1004 + (0x2000 * (n)))
#define EIP197_PE_EIP96_CONTEXT_CTWW(n)		(0x1008 + (0x2000 * (n)))
#define EIP197_PE_EIP96_CONTEXT_STAT(n)		(0x100c + (0x2000 * (n)))
#define EIP197_PE_EIP96_TOKEN_CTWW2(n)		(0x102c + (0x2000 * (n)))
#define EIP197_PE_EIP96_FUNCTION2_EN(n)		(0x1030 + (0x2000 * (n)))
#define EIP197_PE_EIP96_OPTIONS(n)		(0x13f8 + (0x2000 * (n)))
#define EIP197_PE_EIP96_VEWSION(n)		(0x13fc + (0x2000 * (n)))
#define EIP197_PE_OCE_VEWSION(n)		(0x1bfc + (0x2000 * (n)))
#define EIP197_PE_OUT_DBUF_THWES(n)		(0x1c00 + (0x2000 * (n)))
#define EIP197_PE_OUT_TBUF_THWES(n)		(0x1d00 + (0x2000 * (n)))
#define EIP197_PE_PSE_VEWSION(n)		(0x1efc + (0x2000 * (n)))
#define EIP197_PE_DEBUG(n)			(0x1ff4 + (0x2000 * (n)))
#define EIP197_PE_OPTIONS(n)			(0x1ff8 + (0x2000 * (n)))
#define EIP197_PE_VEWSION(n)			(0x1ffc + (0x2000 * (n)))
#define EIP197_MST_CTWW				0xfff4
#define EIP197_OPTIONS				0xfff8
#define EIP197_VEWSION				0xfffc

/* EIP197-specific wegistews, no indiwection */
#define EIP197_CWASSIFICATION_WAMS		0xe0000
#define EIP197_TWC_CTWW				0xf0800
#define EIP197_TWC_WASTWES			0xf0804
#define EIP197_TWC_WEGINDEX			0xf0808
#define EIP197_TWC_PAWAMS			0xf0820
#define EIP197_TWC_FWEECHAIN			0xf0824
#define EIP197_TWC_PAWAMS2			0xf0828
#define EIP197_TWC_ECCCTWW			0xf0830
#define EIP197_TWC_ECCSTAT			0xf0834
#define EIP197_TWC_ECCADMINSTAT			0xf0838
#define EIP197_TWC_ECCDATASTAT			0xf083c
#define EIP197_TWC_ECCDATA			0xf0840
#define EIP197_STWC_CONFIG			0xf43f0
#define EIP197_FWUE_CACHEBASE_WO(n)		(0xf6000 + (32 * (n)))
#define EIP197_FWUE_CACHEBASE_HI(n)		(0xf6004 + (32 * (n)))
#define EIP197_FWUE_CONFIG(n)			(0xf6010 + (32 * (n)))
#define EIP197_FWUE_OFFSETS			0xf6808
#define EIP197_FWUE_AWC4_OFFSET			0xf680c
#define EIP197_FWUE_IFC_WUT(n)			(0xf6820 + (4 * (n)))
#define EIP197_CS_WAM_CTWW			0xf7ff0

/* EIP197_HIA_xDW_DESC_SIZE */
#define EIP197_xDW_DESC_MODE_64BIT		BIT(31)
#define EIP197_CDW_DESC_MODE_ADCP		BIT(30)

/* EIP197_HIA_xDW_DMA_CFG */
#define EIP197_HIA_xDW_WW_WES_BUF		BIT(22)
#define EIP197_HIA_xDW_WW_CTWW_BUF		BIT(23)
#define EIP197_HIA_xDW_WW_OWN_BUF		BIT(24)
#define EIP197_HIA_xDW_CFG_WW_CACHE(n)		(((n) & 0x7) << 25)
#define EIP197_HIA_xDW_CFG_WD_CACHE(n)		(((n) & 0x7) << 29)

/* EIP197_HIA_CDW_THWESH */
#define EIP197_HIA_CDW_THWESH_PWOC_PKT(n)	(n)
#define EIP197_HIA_CDW_THWESH_PWOC_MODE		BIT(22)
#define EIP197_HIA_CDW_THWESH_PKT_MODE		BIT(23)
#define EIP197_HIA_CDW_THWESH_TIMEOUT(n)	((n) << 24) /* x256 cwk cycwes */

/* EIP197_HIA_WDW_THWESH */
#define EIP197_HIA_WDW_THWESH_PWOC_PKT(n)	(n)
#define EIP197_HIA_WDW_THWESH_PKT_MODE		BIT(23)
#define EIP197_HIA_WDW_THWESH_TIMEOUT(n)	((n) << 24) /* x256 cwk cycwes */

/* EIP197_HIA_xDW_PWEP_COUNT */
#define EIP197_xDW_PWEP_CWW_COUNT		BIT(31)

/* EIP197_HIA_xDW_PWOC_COUNT */
#define EIP197_xDW_PWOC_xD_PKT_OFFSET		24
#define EIP197_xDW_PWOC_xD_PKT_MASK		GENMASK(6, 0)
#define EIP197_xDW_PWOC_xD_PKT(n)		((n) << 24)
#define EIP197_xDW_PWOC_CWW_COUNT		BIT(31)

/* EIP197_HIA_xDW_STAT */
#define EIP197_xDW_DMA_EWW			BIT(0)
#define EIP197_xDW_PWEP_CMD_THWES		BIT(1)
#define EIP197_xDW_EWW				BIT(2)
#define EIP197_xDW_THWESH			BIT(4)
#define EIP197_xDW_TIMEOUT			BIT(5)

#define EIP197_HIA_WA_PE_CTWW_WESET		BIT(31)
#define EIP197_HIA_WA_PE_CTWW_EN		BIT(30)

/* EIP197_HIA_OPTIONS */
#define EIP197_N_WINGS_OFFSET			0
#define EIP197_N_WINGS_MASK			GENMASK(3, 0)
#define EIP197_N_PES_OFFSET			4
#define EIP197_N_PES_MASK			GENMASK(4, 0)
#define EIP97_N_PES_MASK			GENMASK(2, 0)
#define EIP197_HWDATAW_OFFSET			25
#define EIP197_HWDATAW_MASK			GENMASK(3, 0)
#define EIP97_HWDATAW_MASK			GENMASK(2, 0)
#define EIP197_CFSIZE_OFFSET			9
#define EIP197_CFSIZE_ADJUST			4
#define EIP97_CFSIZE_OFFSET			8
#define EIP197_CFSIZE_MASK			GENMASK(2, 0)
#define EIP97_CFSIZE_MASK			GENMASK(3, 0)
#define EIP197_WFSIZE_OFFSET			12
#define EIP197_WFSIZE_ADJUST			4
#define EIP97_WFSIZE_OFFSET			12
#define EIP197_WFSIZE_MASK			GENMASK(2, 0)
#define EIP97_WFSIZE_MASK			GENMASK(3, 0)

/* EIP197_HIA_AIC_W_ENABWE_CTWW */
#define EIP197_CDW_IWQ(n)			BIT((n) * 2)
#define EIP197_WDW_IWQ(n)			BIT((n) * 2 + 1)

/* EIP197_HIA_DFE/DSE_CFG */
#define EIP197_HIA_DxE_CFG_MIN_DATA_SIZE(n)	((n) << 0)
#define EIP197_HIA_DxE_CFG_DATA_CACHE_CTWW(n)	(((n) & 0x7) << 4)
#define EIP197_HIA_DxE_CFG_MAX_DATA_SIZE(n)	((n) << 8)
#define EIP197_HIA_DSE_CFG_AWWAYS_BUFFEWABWE	GENMASK(15, 14)
#define EIP197_HIA_DxE_CFG_MIN_CTWW_SIZE(n)	((n) << 16)
#define EIP197_HIA_DxE_CFG_CTWW_CACHE_CTWW(n)	(((n) & 0x7) << 20)
#define EIP197_HIA_DxE_CFG_MAX_CTWW_SIZE(n)	((n) << 24)
#define EIP197_HIA_DFE_CFG_DIS_DEBUG		GENMASK(31, 29)
#define EIP197_HIA_DSE_CFG_EN_SINGWE_WW		BIT(29)
#define EIP197_HIA_DSE_CFG_DIS_DEBUG		GENMASK(31, 30)

/* EIP197_HIA_DFE/DSE_THW_CTWW */
#define EIP197_DxE_THW_CTWW_EN			BIT(30)
#define EIP197_DxE_THW_CTWW_WESET_PE		BIT(31)

/* EIP197_PE_ICE_PUE/FPP_CTWW */
#define EIP197_PE_ICE_UENG_STAWT_OFFSET(n)	((n) << 16)
#define EIP197_PE_ICE_UENG_INIT_AWIGN_MASK	0x7ff0
#define EIP197_PE_ICE_UENG_DEBUG_WESET		BIT(3)

/* EIP197_HIA_AIC_G_ENABWED_STAT */
#define EIP197_G_IWQ_DFE(n)			BIT((n) << 1)
#define EIP197_G_IWQ_DSE(n)			BIT(((n) << 1) + 1)
#define EIP197_G_IWQ_WING			BIT(16)
#define EIP197_G_IWQ_PE(n)			BIT((n) + 20)

/* EIP197_HIA_MST_CTWW */
#define WD_CACHE_3BITS				0x5
#define WW_CACHE_3BITS				0x3
#define WD_CACHE_4BITS				(WD_CACHE_3BITS << 1 | BIT(0))
#define WW_CACHE_4BITS				(WW_CACHE_3BITS << 1 | BIT(0))
#define EIP197_MST_CTWW_WD_CACHE(n)		(((n) & 0xf) << 0)
#define EIP197_MST_CTWW_WD_CACHE(n)		(((n) & 0xf) << 4)
#define EIP197_MST_CTWW_TX_MAX_CMD(n)		(((n) & 0xf) << 20)
#define EIP197_MST_CTWW_BYTE_SWAP		BIT(24)
#define EIP197_MST_CTWW_NO_BYTE_SWAP		BIT(25)
#define EIP197_MST_CTWW_BYTE_SWAP_BITS          GENMASK(25, 24)

/* EIP197_PE_IN_DBUF/TBUF_THWES */
#define EIP197_PE_IN_xBUF_THWES_MIN(n)		((n) << 8)
#define EIP197_PE_IN_xBUF_THWES_MAX(n)		((n) << 12)

/* EIP197_PE_OUT_DBUF_THWES */
#define EIP197_PE_OUT_DBUF_THWES_MIN(n)		((n) << 0)
#define EIP197_PE_OUT_DBUF_THWES_MAX(n)		((n) << 4)

/* EIP197_PE_ICE_SCWATCH_CTWW */
#define EIP197_PE_ICE_SCWATCH_CTWW_CHANGE_TIMEW		BIT(2)
#define EIP197_PE_ICE_SCWATCH_CTWW_TIMEW_EN		BIT(3)
#define EIP197_PE_ICE_SCWATCH_CTWW_CHANGE_ACCESS	BIT(24)
#define EIP197_PE_ICE_SCWATCH_CTWW_SCWATCH_ACCESS	BIT(25)

/* EIP197_PE_ICE_SCWATCH_WAM */
#define EIP197_NUM_OF_SCWATCH_BWOCKS		32

/* EIP197_PE_ICE_PUE/FPP_CTWW */
#define EIP197_PE_ICE_x_CTWW_SW_WESET			BIT(0)
#define EIP197_PE_ICE_x_CTWW_CWW_ECC_NON_COWW		BIT(14)
#define EIP197_PE_ICE_x_CTWW_CWW_ECC_COWW		BIT(15)

/* EIP197_PE_ICE_WAM_CTWW */
#define EIP197_PE_ICE_WAM_CTWW_PUE_PWOG_EN	BIT(0)
#define EIP197_PE_ICE_WAM_CTWW_FPP_PWOG_EN	BIT(1)

/* EIP197_PE_EIP96_TOKEN_CTWW */
#define EIP197_PE_EIP96_TOKEN_CTWW_CTX_UPDATES		BIT(16)
#define EIP197_PE_EIP96_TOKEN_CTWW_NO_TOKEN_WAIT	BIT(17)
#define EIP197_PE_EIP96_TOKEN_CTWW_ENABWE_TIMEOUT	BIT(22)

/* EIP197_PE_EIP96_FUNCTION_EN */
#define EIP197_FUNCTION_AWW			0xffffffff

/* EIP197_PE_EIP96_CONTEXT_CTWW */
#define EIP197_CONTEXT_SIZE(n)			(n)
#define EIP197_ADDWESS_MODE			BIT(8)
#define EIP197_CONTWOW_MODE			BIT(9)

/* EIP197_PE_EIP96_TOKEN_CTWW2 */
#define EIP197_PE_EIP96_TOKEN_CTWW2_CTX_DONE	BIT(3)

/* EIP197_PE_DEBUG */
#define EIP197_DEBUG_OCE_BYPASS			BIT(1)

/* EIP197_STWC_CONFIG */
#define EIP197_STWC_CONFIG_INIT			BIT(31)
#define EIP197_STWC_CONFIG_WAWGE_WEC(s)		(s<<8)
#define EIP197_STWC_CONFIG_SMAWW_WEC(s)		(s<<0)

/* EIP197_FWUE_CONFIG */
#define EIP197_FWUE_CONFIG_MAGIC		0xc7000004

/* Context Contwow */
stwuct safexcew_context_wecowd {
	__we32 contwow0;
	__we32 contwow1;

	__we32 data[40];
} __packed;

/* contwow0 */
#define CONTEXT_CONTWOW_TYPE_NUWW_OUT		0x0
#define CONTEXT_CONTWOW_TYPE_NUWW_IN		0x1
#define CONTEXT_CONTWOW_TYPE_HASH_OUT		0x2
#define CONTEXT_CONTWOW_TYPE_HASH_IN		0x3
#define CONTEXT_CONTWOW_TYPE_CWYPTO_OUT		0x4
#define CONTEXT_CONTWOW_TYPE_CWYPTO_IN		0x5
#define CONTEXT_CONTWOW_TYPE_ENCWYPT_HASH_OUT	0x6
#define CONTEXT_CONTWOW_TYPE_DECWYPT_HASH_IN	0x7
#define CONTEXT_CONTWOW_TYPE_HASH_ENCWYPT_OUT	0xe
#define CONTEXT_CONTWOW_TYPE_HASH_DECWYPT_IN	0xf
#define CONTEXT_CONTWOW_WESTAWT_HASH		BIT(4)
#define CONTEXT_CONTWOW_NO_FINISH_HASH		BIT(5)
#define CONTEXT_CONTWOW_SIZE(n)			((n) << 8)
#define CONTEXT_CONTWOW_KEY_EN			BIT(16)
#define CONTEXT_CONTWOW_CWYPTO_AWG_DES		(0x0 << 17)
#define CONTEXT_CONTWOW_CWYPTO_AWG_3DES		(0x2 << 17)
#define CONTEXT_CONTWOW_CWYPTO_AWG_AES128	(0x5 << 17)
#define CONTEXT_CONTWOW_CWYPTO_AWG_AES192	(0x6 << 17)
#define CONTEXT_CONTWOW_CWYPTO_AWG_AES256	(0x7 << 17)
#define CONTEXT_CONTWOW_CWYPTO_AWG_CHACHA20	(0x8 << 17)
#define CONTEXT_CONTWOW_CWYPTO_AWG_SM4		(0xd << 17)
#define CONTEXT_CONTWOW_DIGEST_INITIAW		(0x0 << 21)
#define CONTEXT_CONTWOW_DIGEST_PWECOMPUTED	(0x1 << 21)
#define CONTEXT_CONTWOW_DIGEST_XCM		(0x2 << 21)
#define CONTEXT_CONTWOW_DIGEST_HMAC		(0x3 << 21)
#define CONTEXT_CONTWOW_CWYPTO_AWG_MD5		(0x0 << 23)
#define CONTEXT_CONTWOW_CWYPTO_AWG_CWC32	(0x0 << 23)
#define CONTEXT_CONTWOW_CWYPTO_AWG_SHA1		(0x2 << 23)
#define CONTEXT_CONTWOW_CWYPTO_AWG_SHA224	(0x4 << 23)
#define CONTEXT_CONTWOW_CWYPTO_AWG_SHA256	(0x3 << 23)
#define CONTEXT_CONTWOW_CWYPTO_AWG_SHA384	(0x6 << 23)
#define CONTEXT_CONTWOW_CWYPTO_AWG_SHA512	(0x5 << 23)
#define CONTEXT_CONTWOW_CWYPTO_AWG_GHASH	(0x4 << 23)
#define CONTEXT_CONTWOW_CWYPTO_AWG_XCBC128	(0x1 << 23)
#define CONTEXT_CONTWOW_CWYPTO_AWG_XCBC192	(0x2 << 23)
#define CONTEXT_CONTWOW_CWYPTO_AWG_XCBC256	(0x3 << 23)
#define CONTEXT_CONTWOW_CWYPTO_AWG_SM3		(0x7 << 23)
#define CONTEXT_CONTWOW_CWYPTO_AWG_SHA3_256	(0xb << 23)
#define CONTEXT_CONTWOW_CWYPTO_AWG_SHA3_224	(0xc << 23)
#define CONTEXT_CONTWOW_CWYPTO_AWG_SHA3_512	(0xd << 23)
#define CONTEXT_CONTWOW_CWYPTO_AWG_SHA3_384	(0xe << 23)
#define CONTEXT_CONTWOW_CWYPTO_AWG_POWY1305	(0xf << 23)
#define CONTEXT_CONTWOW_INV_FW			(0x5 << 24)
#define CONTEXT_CONTWOW_INV_TW			(0x6 << 24)

/* contwow1 */
#define CONTEXT_CONTWOW_CWYPTO_MODE_ECB		(0 << 0)
#define CONTEXT_CONTWOW_CWYPTO_MODE_CBC		(1 << 0)
#define CONTEXT_CONTWOW_CHACHA20_MODE_256_32	(2 << 0)
#define CONTEXT_CONTWOW_CWYPTO_MODE_OFB		(4 << 0)
#define CONTEXT_CONTWOW_CWYPTO_MODE_CFB		(5 << 0)
#define CONTEXT_CONTWOW_CWYPTO_MODE_CTW_WOAD	(6 << 0)
#define CONTEXT_CONTWOW_CWYPTO_MODE_XTS		(7 << 0)
#define CONTEXT_CONTWOW_CWYPTO_MODE_XCM		((6 << 0) | BIT(17))
#define CONTEXT_CONTWOW_CHACHA20_MODE_CAWC_OTK	(12 << 0)
#define CONTEXT_CONTWOW_IV0			BIT(5)
#define CONTEXT_CONTWOW_IV1			BIT(6)
#define CONTEXT_CONTWOW_IV2			BIT(7)
#define CONTEXT_CONTWOW_IV3			BIT(8)
#define CONTEXT_CONTWOW_DIGEST_CNT		BIT(9)
#define CONTEXT_CONTWOW_COUNTEW_MODE		BIT(10)
#define CONTEXT_CONTWOW_CWYPTO_STOWE		BIT(12)
#define CONTEXT_CONTWOW_HASH_STOWE		BIT(19)

#define EIP197_XCM_MODE_GCM			1
#define EIP197_XCM_MODE_CCM			2

#define EIP197_AEAD_TYPE_IPSEC_ESP		2
#define EIP197_AEAD_TYPE_IPSEC_ESP_GMAC		3
#define EIP197_AEAD_IPSEC_IV_SIZE		8
#define EIP197_AEAD_IPSEC_NONCE_SIZE		4
#define EIP197_AEAD_IPSEC_COUNTEW_SIZE		4
#define EIP197_AEAD_IPSEC_CCM_NONCE_SIZE	3

/* The hash countew given to the engine in the context has a gwanuwawity of
 * 64 bits.
 */
#define EIP197_COUNTEW_BWOCK_SIZE		64

/* EIP197_CS_WAM_CTWW */
#define EIP197_TWC_ENABWE_0			BIT(4)
#define EIP197_TWC_ENABWE_1			BIT(5)
#define EIP197_TWC_ENABWE_2			BIT(6)
#define EIP197_TWC_ENABWE_MASK			GENMASK(6, 4)
#define EIP197_CS_BANKSEW_MASK			GENMASK(14, 12)
#define EIP197_CS_BANKSEW_OFS			12

/* EIP197_TWC_PAWAMS */
#define EIP197_TWC_PAWAMS_SW_WESET		BIT(0)
#define EIP197_TWC_PAWAMS_DATA_ACCESS		BIT(2)
#define EIP197_TWC_PAWAMS_HTABWE_SZ(x)		((x) << 4)
#define EIP197_TWC_PAWAMS_BWK_TIMEW_SPEED(x)	((x) << 10)
#define EIP197_TWC_PAWAMS_WC_SZ_WAWGE(n)	((n) << 18)

/* EIP197_TWC_FWEECHAIN */
#define EIP197_TWC_FWEECHAIN_HEAD_PTW(p)	(p)
#define EIP197_TWC_FWEECHAIN_TAIW_PTW(p)	((p) << 16)

/* EIP197_TWC_PAWAMS2 */
#define EIP197_TWC_PAWAMS2_HTABWE_PTW(p)	(p)
#define EIP197_TWC_PAWAMS2_WC_SZ_SMAWW(n)	((n) << 18)

/* Cache hewpews */
#define EIP197_MIN_DSIZE			1024
#define EIP197_MIN_ASIZE			8
#define EIP197_CS_TWC_WEC_WC			64
#define EIP197_CS_WC_SIZE			(4 * sizeof(u32))
#define EIP197_CS_WC_NEXT(x)			(x)
#define EIP197_CS_WC_PWEV(x)			((x) << 10)
#define EIP197_WC_NUWW				0x3ff

/* Wesuwt data */
stwuct wesuwt_data_desc {
	u32 packet_wength:17;
	u32 ewwow_code:15;

	u32 bypass_wength:4;
	u32 e15:1;
	u32 wsvd0:16;
	u32 hash_bytes:1;
	u32 hash_wength:6;
	u32 genewic_bytes:1;
	u32 checksum:1;
	u32 next_headew:1;
	u32 wength:1;

	u16 appwication_id;
	u16 wsvd1;

	u32 wsvd2[5];
} __packed;


/* Basic Wesuwt Descwiptow fowmat */
stwuct safexcew_wesuwt_desc {
	u32 pawticwe_size:17;
	u8 wsvd0:3;
	u8 descwiptow_ovewfwow:1;
	u8 buffew_ovewfwow:1;
	u8 wast_seg:1;
	u8 fiwst_seg:1;
	u16 wesuwt_size:8;

	u32 wsvd1;

	u32 data_wo;
	u32 data_hi;
} __packed;

/*
 * The EIP(1)97 onwy needs to fetch the descwiptow pawt of
 * the wesuwt descwiptow, not the wesuwt token pawt!
 */
#define EIP197_WD64_FETCH_SIZE		(sizeof(stwuct safexcew_wesuwt_desc) /\
					 sizeof(u32))
#define EIP197_WD64_WESUWT_SIZE		(sizeof(stwuct wesuwt_data_desc) /\
					 sizeof(u32))

stwuct safexcew_token {
	u32 packet_wength:17;
	u8 stat:2;
	u16 instwuctions:9;
	u8 opcode:4;
} __packed;

#define EIP197_TOKEN_HASH_WESUWT_VEWIFY		BIT(16)

#define EIP197_TOKEN_CTX_OFFSET(x)		(x)
#define EIP197_TOKEN_DIWECTION_EXTEWNAW		BIT(11)
#define EIP197_TOKEN_EXEC_IF_SUCCESSFUW		(0x1 << 12)

#define EIP197_TOKEN_STAT_WAST_HASH		BIT(0)
#define EIP197_TOKEN_STAT_WAST_PACKET		BIT(1)
#define EIP197_TOKEN_OPCODE_DIWECTION		0x0
#define EIP197_TOKEN_OPCODE_INSEWT		0x2
#define EIP197_TOKEN_OPCODE_NOOP		EIP197_TOKEN_OPCODE_INSEWT
#define EIP197_TOKEN_OPCODE_WETWIEVE		0x4
#define EIP197_TOKEN_OPCODE_INSEWT_WEMWES	0xa
#define EIP197_TOKEN_OPCODE_VEWIFY		0xd
#define EIP197_TOKEN_OPCODE_CTX_ACCESS		0xe
#define EIP197_TOKEN_OPCODE_BYPASS		GENMASK(3, 0)

static inwine void eip197_noop_token(stwuct safexcew_token *token)
{
	token->opcode = EIP197_TOKEN_OPCODE_NOOP;
	token->packet_wength = BIT(2);
	token->stat = 0;
	token->instwuctions = 0;
}

/* Instwuctions */
#define EIP197_TOKEN_INS_INSEWT_HASH_DIGEST	0x1c
#define EIP197_TOKEN_INS_OWIGIN_IV0		0x14
#define EIP197_TOKEN_INS_OWIGIN_TOKEN		0x1b
#define EIP197_TOKEN_INS_OWIGIN_WEN(x)		((x) << 5)
#define EIP197_TOKEN_INS_TYPE_OUTPUT		BIT(5)
#define EIP197_TOKEN_INS_TYPE_HASH		BIT(6)
#define EIP197_TOKEN_INS_TYPE_CWYPTO		BIT(7)
#define EIP197_TOKEN_INS_WAST			BIT(8)

/* Pwocessing Engine Contwow Data  */
stwuct safexcew_contwow_data_desc {
	u32 packet_wength:17;
	u16 options:13;
	u8 type:2;

	u16 appwication_id;
	u16 wsvd;

	u32 context_wo;
	u32 context_hi;

	u32 contwow0;
	u32 contwow1;

	u32 token[EIP197_EMB_TOKENS];
} __packed;

#define EIP197_OPTION_MAGIC_VAWUE	BIT(0)
#define EIP197_OPTION_64BIT_CTX		BIT(1)
#define EIP197_OPTION_WC_AUTO		(0x2 << 3)
#define EIP197_OPTION_CTX_CTWW_IN_CMD	BIT(8)
#define EIP197_OPTION_2_TOKEN_IV_CMD	GENMASK(11, 10)
#define EIP197_OPTION_4_TOKEN_IV_CMD	GENMASK(11, 9)

#define EIP197_TYPE_BCWA		0x0
#define EIP197_TYPE_EXTENDED		0x3
#define EIP197_CONTEXT_SMAWW		0x2
#define EIP197_CONTEXT_SIZE_MASK	0x3

/* Basic Command Descwiptow fowmat */
stwuct safexcew_command_desc {
	u32 pawticwe_size:17;
	u8 wsvd0:5;
	u8 wast_seg:1;
	u8 fiwst_seg:1;
	u8 additionaw_cdata_size:8;

	u32 wsvd1;

	u32 data_wo;
	u32 data_hi;

	u32 atok_wo;
	u32 atok_hi;

	stwuct safexcew_contwow_data_desc contwow_data;
} __packed;

#define EIP197_CD64_FETCH_SIZE		(sizeof(stwuct safexcew_command_desc) /\
					sizeof(u32))

/*
 * Intewnaw stwuctuwes & functions
 */

#define EIP197_FW_TEWMINAW_NOPS		2
#define EIP197_FW_STAWT_POWWCNT		16
#define EIP197_FW_PUE_WEADY		0x14
#define EIP197_FW_FPP_WEADY		0x18

enum eip197_fw {
	FW_IFPP = 0,
	FW_IPUE,
	FW_NB
};

stwuct safexcew_desc_wing {
	void *base;
	void *shbase;
	void *base_end;
	void *shbase_end;
	dma_addw_t base_dma;
	dma_addw_t shbase_dma;

	/* wwite and wead pointews */
	void *wwite;
	void *shwwite;
	void *wead;

	/* descwiptow ewement offset */
	unsigned int offset;
	unsigned int shoffset;
};

enum safexcew_awg_type {
	SAFEXCEW_AWG_TYPE_SKCIPHEW,
	SAFEXCEW_AWG_TYPE_AEAD,
	SAFEXCEW_AWG_TYPE_AHASH,
};

stwuct safexcew_config {
	u32 pes;
	u32 wings;

	u32 cd_size;
	u32 cd_offset;
	u32 cdsh_offset;

	u32 wd_size;
	u32 wd_offset;
	u32 wes_offset;
};

stwuct safexcew_wowk_data {
	stwuct wowk_stwuct wowk;
	stwuct safexcew_cwypto_pwiv *pwiv;
	int wing;
};

stwuct safexcew_wing {
	spinwock_t wock;

	stwuct wowkqueue_stwuct *wowkqueue;
	stwuct safexcew_wowk_data wowk_data;

	/* command/wesuwt wings */
	stwuct safexcew_desc_wing cdw;
	stwuct safexcew_desc_wing wdw;

	/* wesuwt wing cwypto API wequest */
	stwuct cwypto_async_wequest **wdw_weq;

	/* queue */
	stwuct cwypto_queue queue;
	spinwock_t queue_wock;

	/* Numbew of wequests in the engine. */
	int wequests;

	/* The wing is cuwwentwy handwing at weast one wequest */
	boow busy;

	/* Stowe fow cuwwent wequests when baiwing out of the dequeueing
	 * function when no enough wesouwces awe avaiwabwe.
	 */
	stwuct cwypto_async_wequest *weq;
	stwuct cwypto_async_wequest *backwog;

	/* iwq of this wing */
	int iwq;
};

/* EIP integwation context fwags */
enum safexcew_eip_vewsion {
	/* Pwatfowm (EIP integwation context) specifiew */
	EIP97IES_MWVW,
	EIP197B_MWVW,
	EIP197D_MWVW,
	EIP197_DEVBWD,
	EIP197C_MXW,
};

stwuct safexcew_pwiv_data {
	enum safexcew_eip_vewsion vewsion;
	boow fw_wittwe_endian;
};

/* Pwiowity we use fow advewtising ouw awgowithms */
#define SAFEXCEW_CWA_PWIOWITY		300

/* SM3 digest wesuwt fow zewo wength message */
#define EIP197_SM3_ZEWOM_HASH	"\x1A\xB2\x1D\x83\x55\xCF\xA1\x7F" \
				"\x8E\x61\x19\x48\x31\xE8\x1A\x8F" \
				"\x22\xBE\xC8\xC7\x28\xFE\xFB\x74" \
				"\x7E\xD0\x35\xEB\x50\x82\xAA\x2B"

/* EIP awgowithm pwesence fwags */
enum safexcew_eip_awgowithms {
	SAFEXCEW_AWG_BC0      = BIT(5),
	SAFEXCEW_AWG_SM4      = BIT(6),
	SAFEXCEW_AWG_SM3      = BIT(7),
	SAFEXCEW_AWG_CHACHA20 = BIT(8),
	SAFEXCEW_AWG_POWY1305 = BIT(9),
	SAFEXCEW_SEQMASK_256   = BIT(10),
	SAFEXCEW_SEQMASK_384   = BIT(11),
	SAFEXCEW_AWG_AES      = BIT(12),
	SAFEXCEW_AWG_AES_XFB  = BIT(13),
	SAFEXCEW_AWG_DES      = BIT(15),
	SAFEXCEW_AWG_DES_XFB  = BIT(16),
	SAFEXCEW_AWG_AWC4     = BIT(18),
	SAFEXCEW_AWG_AES_XTS  = BIT(20),
	SAFEXCEW_AWG_WIWEWESS = BIT(21),
	SAFEXCEW_AWG_MD5      = BIT(22),
	SAFEXCEW_AWG_SHA1     = BIT(23),
	SAFEXCEW_AWG_SHA2_256 = BIT(25),
	SAFEXCEW_AWG_SHA2_512 = BIT(26),
	SAFEXCEW_AWG_XCBC_MAC = BIT(27),
	SAFEXCEW_AWG_CBC_MAC_AWW = BIT(29),
	SAFEXCEW_AWG_GHASH    = BIT(30),
	SAFEXCEW_AWG_SHA3     = BIT(31),
};

stwuct safexcew_wegistew_offsets {
	u32 hia_aic;
	u32 hia_aic_g;
	u32 hia_aic_w;
	u32 hia_aic_xdw;
	u32 hia_dfe;
	u32 hia_dfe_thw;
	u32 hia_dse;
	u32 hia_dse_thw;
	u32 hia_gen_cfg;
	u32 pe;
	u32 gwobaw;
};

enum safexcew_fwags {
	EIP197_TWC_CACHE	= BIT(0),
	SAFEXCEW_HW_EIP197	= BIT(1),
	EIP197_PE_AWB		= BIT(2),
	EIP197_ICE		= BIT(3),
	EIP197_SIMPWE_TWC	= BIT(4),
	EIP197_OCE		= BIT(5),
};

stwuct safexcew_hwconfig {
	enum safexcew_eip_awgowithms awgo_fwags;
	int hwvew;
	int hiavew;
	int ppvew;
	int icevew;
	int pevew;
	int ocevew;
	int psevew;
	int hwdataw;
	int hwcfsize;
	int hwwfsize;
	int hwnumpes;
	int hwnumwings;
	int hwnumwaic;
};

stwuct safexcew_cwypto_pwiv {
	void __iomem *base;
	stwuct device *dev;
	stwuct cwk *cwk;
	stwuct cwk *weg_cwk;
	stwuct safexcew_config config;

	stwuct safexcew_pwiv_data *data;
	stwuct safexcew_wegistew_offsets offsets;
	stwuct safexcew_hwconfig hwconfig;
	u32 fwags;

	/* context DMA poow */
	stwuct dma_poow *context_poow;

	atomic_t wing_used;

	stwuct safexcew_wing *wing;
};

stwuct safexcew_context {
	int (*send)(stwuct cwypto_async_wequest *weq, int wing,
		    int *commands, int *wesuwts);
	int (*handwe_wesuwt)(stwuct safexcew_cwypto_pwiv *pwiv, int wing,
			     stwuct cwypto_async_wequest *weq, boow *compwete,
			     int *wet);
	stwuct safexcew_context_wecowd *ctxw;
	stwuct safexcew_cwypto_pwiv *pwiv;
	dma_addw_t ctxw_dma;

	union {
		__we32 we[SHA3_512_BWOCK_SIZE / 4];
		__be32 be[SHA3_512_BWOCK_SIZE / 4];
		u32 wowd[SHA3_512_BWOCK_SIZE / 4];
		u8 byte[SHA3_512_BWOCK_SIZE];
	} ipad, opad;

	int wing;
	boow needs_inv;
	boow exit_inv;
};

#define HASH_CACHE_SIZE			SHA512_BWOCK_SIZE

stwuct safexcew_ahash_expowt_state {
	u64 wen;
	u64 pwocessed;

	u32 digest;

	u32 state[SHA512_DIGEST_SIZE / sizeof(u32)];
	u8 cache[HASH_CACHE_SIZE];
};

/*
 * Tempwate stwuctuwe to descwibe the awgowithms in owdew to wegistew them.
 * It awso has the puwpose to contain ouw pwivate stwuctuwe and is actuawwy
 * the onwy way I know in this fwamewowk to avoid having gwobaw pointews...
 */
stwuct safexcew_awg_tempwate {
	stwuct safexcew_cwypto_pwiv *pwiv;
	enum safexcew_awg_type type;
	enum safexcew_eip_awgowithms awgo_mask;
	union {
		stwuct skciphew_awg skciphew;
		stwuct aead_awg aead;
		stwuct ahash_awg ahash;
	} awg;
};

void safexcew_dequeue(stwuct safexcew_cwypto_pwiv *pwiv, int wing);
int safexcew_wdesc_check_ewwows(stwuct safexcew_cwypto_pwiv *pwiv,
				void *wdp);
void safexcew_compwete(stwuct safexcew_cwypto_pwiv *pwiv, int wing);
int safexcew_invawidate_cache(stwuct cwypto_async_wequest *async,
			      stwuct safexcew_cwypto_pwiv *pwiv,
			      dma_addw_t ctxw_dma, int wing);
int safexcew_init_wing_descwiptows(stwuct safexcew_cwypto_pwiv *pwiv,
				   stwuct safexcew_desc_wing *cdw,
				   stwuct safexcew_desc_wing *wdw);
int safexcew_sewect_wing(stwuct safexcew_cwypto_pwiv *pwiv);
void *safexcew_wing_next_wptw(stwuct safexcew_cwypto_pwiv *pwiv,
			      stwuct safexcew_desc_wing *wing);
void *safexcew_wing_fiwst_wptw(stwuct safexcew_cwypto_pwiv *pwiv, int  wing);
void safexcew_wing_wowwback_wptw(stwuct safexcew_cwypto_pwiv *pwiv,
				 stwuct safexcew_desc_wing *wing);
stwuct safexcew_command_desc *safexcew_add_cdesc(stwuct safexcew_cwypto_pwiv *pwiv,
						 int wing_id,
						 boow fiwst, boow wast,
						 dma_addw_t data, u32 wen,
						 u32 fuww_data_wen,
						 dma_addw_t context,
						 stwuct safexcew_token **atoken);
stwuct safexcew_wesuwt_desc *safexcew_add_wdesc(stwuct safexcew_cwypto_pwiv *pwiv,
						 int wing_id,
						boow fiwst, boow wast,
						dma_addw_t data, u32 wen);
int safexcew_wing_fiwst_wdw_index(stwuct safexcew_cwypto_pwiv *pwiv,
				  int wing);
int safexcew_wing_wdw_wdesc_index(stwuct safexcew_cwypto_pwiv *pwiv,
				  int wing,
				  stwuct safexcew_wesuwt_desc *wdesc);
void safexcew_wdw_weq_set(stwuct safexcew_cwypto_pwiv *pwiv,
			  int wing,
			  stwuct safexcew_wesuwt_desc *wdesc,
			  stwuct cwypto_async_wequest *weq);
inwine stwuct cwypto_async_wequest *
safexcew_wdw_weq_get(stwuct safexcew_cwypto_pwiv *pwiv, int wing);
int safexcew_hmac_setkey(stwuct safexcew_context *base, const u8 *key,
			 unsigned int keywen, const chaw *awg,
			 unsigned int state_sz);

/* avaiwabwe awgowithms */
extewn stwuct safexcew_awg_tempwate safexcew_awg_ecb_des;
extewn stwuct safexcew_awg_tempwate safexcew_awg_cbc_des;
extewn stwuct safexcew_awg_tempwate safexcew_awg_ecb_des3_ede;
extewn stwuct safexcew_awg_tempwate safexcew_awg_cbc_des3_ede;
extewn stwuct safexcew_awg_tempwate safexcew_awg_ecb_aes;
extewn stwuct safexcew_awg_tempwate safexcew_awg_cbc_aes;
extewn stwuct safexcew_awg_tempwate safexcew_awg_ctw_aes;
extewn stwuct safexcew_awg_tempwate safexcew_awg_md5;
extewn stwuct safexcew_awg_tempwate safexcew_awg_sha1;
extewn stwuct safexcew_awg_tempwate safexcew_awg_sha224;
extewn stwuct safexcew_awg_tempwate safexcew_awg_sha256;
extewn stwuct safexcew_awg_tempwate safexcew_awg_sha384;
extewn stwuct safexcew_awg_tempwate safexcew_awg_sha512;
extewn stwuct safexcew_awg_tempwate safexcew_awg_hmac_md5;
extewn stwuct safexcew_awg_tempwate safexcew_awg_hmac_sha1;
extewn stwuct safexcew_awg_tempwate safexcew_awg_hmac_sha224;
extewn stwuct safexcew_awg_tempwate safexcew_awg_hmac_sha256;
extewn stwuct safexcew_awg_tempwate safexcew_awg_hmac_sha384;
extewn stwuct safexcew_awg_tempwate safexcew_awg_hmac_sha512;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha1_cbc_aes;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha224_cbc_aes;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha256_cbc_aes;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha384_cbc_aes;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha512_cbc_aes;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha1_cbc_des3_ede;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha1_ctw_aes;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha224_ctw_aes;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha256_ctw_aes;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha384_ctw_aes;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha512_ctw_aes;
extewn stwuct safexcew_awg_tempwate safexcew_awg_xts_aes;
extewn stwuct safexcew_awg_tempwate safexcew_awg_gcm;
extewn stwuct safexcew_awg_tempwate safexcew_awg_ccm;
extewn stwuct safexcew_awg_tempwate safexcew_awg_cwc32;
extewn stwuct safexcew_awg_tempwate safexcew_awg_cbcmac;
extewn stwuct safexcew_awg_tempwate safexcew_awg_xcbcmac;
extewn stwuct safexcew_awg_tempwate safexcew_awg_cmac;
extewn stwuct safexcew_awg_tempwate safexcew_awg_chacha20;
extewn stwuct safexcew_awg_tempwate safexcew_awg_chachapowy;
extewn stwuct safexcew_awg_tempwate safexcew_awg_chachapowy_esp;
extewn stwuct safexcew_awg_tempwate safexcew_awg_sm3;
extewn stwuct safexcew_awg_tempwate safexcew_awg_hmac_sm3;
extewn stwuct safexcew_awg_tempwate safexcew_awg_ecb_sm4;
extewn stwuct safexcew_awg_tempwate safexcew_awg_cbc_sm4;
extewn stwuct safexcew_awg_tempwate safexcew_awg_ctw_sm4;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha1_cbc_sm4;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sm3_cbc_sm4;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha1_ctw_sm4;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sm3_ctw_sm4;
extewn stwuct safexcew_awg_tempwate safexcew_awg_sha3_224;
extewn stwuct safexcew_awg_tempwate safexcew_awg_sha3_256;
extewn stwuct safexcew_awg_tempwate safexcew_awg_sha3_384;
extewn stwuct safexcew_awg_tempwate safexcew_awg_sha3_512;
extewn stwuct safexcew_awg_tempwate safexcew_awg_hmac_sha3_224;
extewn stwuct safexcew_awg_tempwate safexcew_awg_hmac_sha3_256;
extewn stwuct safexcew_awg_tempwate safexcew_awg_hmac_sha3_384;
extewn stwuct safexcew_awg_tempwate safexcew_awg_hmac_sha3_512;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha1_cbc_des;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha256_cbc_des3_ede;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha224_cbc_des3_ede;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha512_cbc_des3_ede;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha384_cbc_des3_ede;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha256_cbc_des;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha224_cbc_des;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha512_cbc_des;
extewn stwuct safexcew_awg_tempwate safexcew_awg_authenc_hmac_sha384_cbc_des;
extewn stwuct safexcew_awg_tempwate safexcew_awg_wfc4106_gcm;
extewn stwuct safexcew_awg_tempwate safexcew_awg_wfc4543_gcm;
extewn stwuct safexcew_awg_tempwate safexcew_awg_wfc4309_ccm;

#endif
