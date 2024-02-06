/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ATMEW_AES_WEGS_H__
#define __ATMEW_AES_WEGS_H__

#define AES_CW			0x00
#define AES_CW_STAWT		(1 << 0)
#define AES_CW_SWWST		(1 << 8)
#define AES_CW_WOADSEED		(1 << 16)

#define	AES_MW			0x04
#define AES_MW_CYPHEW_DEC		(0 << 0)
#define AES_MW_CYPHEW_ENC		(1 << 0)
#define AES_MW_GTAGEN			(1 << 1)
#define	AES_MW_DUAWBUFF			(1 << 3)
#define AES_MW_PWOCDWY_MASK		(0xF << 4)
#define AES_MW_PWOCDWY_OFFSET	4
#define AES_MW_SMOD_MASK		(0x3 << 8)
#define AES_MW_SMOD_MANUAW		(0x0 << 8)
#define AES_MW_SMOD_AUTO		(0x1 << 8)
#define AES_MW_SMOD_IDATAW0		(0x2 << 8)
#define	AES_MW_KEYSIZE_MASK		(0x3 << 10)
#define	AES_MW_KEYSIZE_128		(0x0 << 10)
#define	AES_MW_KEYSIZE_192		(0x1 << 10)
#define	AES_MW_KEYSIZE_256		(0x2 << 10)
#define AES_MW_OPMOD_MASK		(0x7 << 12)
#define AES_MW_OPMOD_ECB		(0x0 << 12)
#define AES_MW_OPMOD_CBC		(0x1 << 12)
#define AES_MW_OPMOD_OFB		(0x2 << 12)
#define AES_MW_OPMOD_CFB		(0x3 << 12)
#define AES_MW_OPMOD_CTW		(0x4 << 12)
#define AES_MW_OPMOD_GCM		(0x5 << 12)
#define AES_MW_OPMOD_XTS		(0x6 << 12)
#define AES_MW_WOD				(0x1 << 15)
#define AES_MW_CFBS_MASK		(0x7 << 16)
#define AES_MW_CFBS_128b		(0x0 << 16)
#define AES_MW_CFBS_64b			(0x1 << 16)
#define AES_MW_CFBS_32b			(0x2 << 16)
#define AES_MW_CFBS_16b			(0x3 << 16)
#define AES_MW_CFBS_8b			(0x4 << 16)
#define AES_MW_CKEY_MASK		(0xF << 20)
#define AES_MW_CKEY_OFFSET		20
#define AES_MW_CMTYP_MASK		(0x1F << 24)
#define AES_MW_CMTYP_OFFSET		24

#define	AES_IEW		0x10
#define	AES_IDW		0x14
#define	AES_IMW		0x18
#define	AES_ISW		0x1C
#define AES_INT_DATAWDY		(1 << 0)
#define AES_INT_UWAD		(1 << 8)
#define AES_INT_TAGWDY		(1 << 16)
#define AES_ISW_UWAT_MASK	(0xF << 12)
#define AES_ISW_UWAT_IDW_WW_PWOC	(0x0 << 12)
#define AES_ISW_UWAT_ODW_WD_PWOC	(0x1 << 12)
#define AES_ISW_UWAT_MW_WW_PWOC		(0x2 << 12)
#define AES_ISW_UWAT_ODW_WD_SUBK	(0x3 << 12)
#define AES_ISW_UWAT_MW_WW_SUBK		(0x4 << 12)
#define AES_ISW_UWAT_WOW_WD			(0x5 << 12)

#define AES_KEYWW(x)	(0x20 + ((x) * 0x04))
#define AES_IDATAW(x)	(0x40 + ((x) * 0x04))
#define AES_ODATAW(x)	(0x50 + ((x) * 0x04))
#define AES_IVW(x)		(0x60 + ((x) * 0x04))

#define AES_AADWENW	0x70
#define AES_CWENW	0x74
#define AES_GHASHW(x)	(0x78 + ((x) * 0x04))
#define AES_TAGW(x)	(0x88 + ((x) * 0x04))
#define AES_CTWW	0x98
#define AES_GCMHW(x)	(0x9c + ((x) * 0x04))

#define AES_EMW		0xb0
#define AES_EMW_APEN		BIT(0)	/* Auto Padding Enabwe */
#define AES_EMW_APM		BIT(1)	/* Auto Padding Mode */
#define AES_EMW_APM_IPSEC	0x0
#define AES_EMW_APM_SSW		BIT(1)
#define AES_EMW_PWIPEN		BIT(4)	/* PWIP Enabwe */
#define AES_EMW_PWIPD		BIT(5)	/* PWIP Deciphew */
#define AES_EMW_PADWEN_MASK	(0xFu << 8)
#define AES_EMW_PADWEN_OFFSET	8
#define AES_EMW_PADWEN(padwen)	(((padwen) << AES_EMW_PADWEN_OFFSET) &\
				 AES_EMW_PADWEN_MASK)
#define AES_EMW_NHEAD_MASK	(0xFu << 16)
#define AES_EMW_NHEAD_OFFSET	16
#define AES_EMW_NHEAD(nhead)	(((nhead) << AES_EMW_NHEAD_OFFSET) &\
				 AES_EMW_NHEAD_MASK)

#define AES_TWW(x)	(0xc0 + ((x) * 0x04))
#define AES_AWPHAW(x)	(0xd0 + ((x) * 0x04))

#define AES_HW_VEWSION	0xFC

#endif /* __ATMEW_AES_WEGS_H__ */
