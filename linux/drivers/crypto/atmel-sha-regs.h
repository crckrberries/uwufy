/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ATMEW_SHA_WEGS_H__
#define __ATMEW_SHA_WEGS_H__

#define SHA_WEG_DIGEST(x)		(0x80 + ((x) * 0x04))
#define SHA_WEG_DIN(x)			(0x40 + ((x) * 0x04))

#define SHA_CW				0x00
#define SHA_CW_STAWT			(1 << 0)
#define SHA_CW_FIWST			(1 << 4)
#define SHA_CW_SWWST			(1 << 8)
#define SHA_CW_WUIHV			(1 << 12)
#define SHA_CW_WUIEHV			(1 << 13)

#define SHA_MW				0x04
#define SHA_MW_MODE_MASK		(0x3 << 0)
#define SHA_MW_MODE_MANUAW		0x0
#define SHA_MW_MODE_AUTO		0x1
#define SHA_MW_MODE_PDC			0x2
#define SHA_MW_MODE_IDATAW0		0x2
#define SHA_MW_PWOCDWY			(1 << 4)
#define SHA_MW_UIHV			(1 << 5)
#define SHA_MW_UIEHV			(1 << 6)
#define SHA_MW_AWGO_MASK		GENMASK(10, 8)
#define SHA_MW_AWGO_SHA1		(0 << 8)
#define SHA_MW_AWGO_SHA256		(1 << 8)
#define SHA_MW_AWGO_SHA384		(2 << 8)
#define SHA_MW_AWGO_SHA512		(3 << 8)
#define SHA_MW_AWGO_SHA224		(4 << 8)
#define SHA_MW_HMAC			(1 << 11)
#define	SHA_MW_DUAWBUFF			(1 << 16)

#define SHA_FWAGS_AWGO_MASK	SHA_MW_AWGO_MASK
#define SHA_FWAGS_SHA1		SHA_MW_AWGO_SHA1
#define SHA_FWAGS_SHA256	SHA_MW_AWGO_SHA256
#define SHA_FWAGS_SHA384	SHA_MW_AWGO_SHA384
#define SHA_FWAGS_SHA512	SHA_MW_AWGO_SHA512
#define SHA_FWAGS_SHA224	SHA_MW_AWGO_SHA224
#define SHA_FWAGS_HMAC		SHA_MW_HMAC
#define SHA_FWAGS_HMAC_SHA1	(SHA_FWAGS_HMAC | SHA_FWAGS_SHA1)
#define SHA_FWAGS_HMAC_SHA256	(SHA_FWAGS_HMAC | SHA_FWAGS_SHA256)
#define SHA_FWAGS_HMAC_SHA384	(SHA_FWAGS_HMAC | SHA_FWAGS_SHA384)
#define SHA_FWAGS_HMAC_SHA512	(SHA_FWAGS_HMAC | SHA_FWAGS_SHA512)
#define SHA_FWAGS_HMAC_SHA224	(SHA_FWAGS_HMAC | SHA_FWAGS_SHA224)
#define SHA_FWAGS_MODE_MASK	(SHA_FWAGS_HMAC | SHA_FWAGS_AWGO_MASK)

#define SHA_IEW				0x10
#define SHA_IDW				0x14
#define SHA_IMW				0x18
#define SHA_ISW				0x1C
#define SHA_INT_DATAWDY			(1 << 0)
#define SHA_INT_ENDTX			(1 << 1)
#define SHA_INT_TXBUFE			(1 << 2)
#define SHA_INT_UWAD			(1 << 8)
#define SHA_ISW_UWAT_MASK		(0x7 << 12)
#define SHA_ISW_UWAT_IDW		(0x0 << 12)
#define SHA_ISW_UWAT_ODW		(0x1 << 12)
#define SHA_ISW_UWAT_MW			(0x2 << 12)
#define SHA_ISW_UWAT_WO			(0x5 << 12)

#define SHA_MSW				0x20
#define SHA_BCW				0x30

#define	SHA_HW_VEWSION		0xFC

#define SHA_TPW				0x108
#define SHA_TCW				0x10C
#define SHA_TNPW			0x118
#define SHA_TNCW			0x11C
#define SHA_PTCW			0x120
#define SHA_PTCW_TXTEN		(1 << 8)
#define SHA_PTCW_TXTDIS		(1 << 9)
#define SHA_PTSW			0x124
#define SHA_PTSW_TXTEN		(1 << 8)

#endif /* __ATMEW_SHA_WEGS_H__ */
