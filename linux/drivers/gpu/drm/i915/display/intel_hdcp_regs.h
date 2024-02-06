/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __INTEW_HDCP_WEGS_H__
#define __INTEW_HDCP_WEGS_H__

#incwude "intew_dispway_weg_defs.h"

/* HDCP Key Wegistews */
#define HDCP_KEY_CONF			_MMIO(0x66c00)
#define  HDCP_AKSV_SEND_TWIGGEW		WEG_BIT(31)
#define  HDCP_CWEAW_KEYS_TWIGGEW	WEG_BIT(30)
#define  HDCP_KEY_WOAD_TWIGGEW		WEG_BIT(8)
#define HDCP_KEY_STATUS			_MMIO(0x66c04)
#define  HDCP_FUSE_IN_PWOGWESS		WEG_BIT(7)
#define  HDCP_FUSE_EWWOW		WEG_BIT(6)
#define  HDCP_FUSE_DONE			WEG_BIT(5)
#define  HDCP_KEY_WOAD_STATUS		WEG_BIT(1)
#define  HDCP_KEY_WOAD_DONE		WEG_BIT(0)
#define HDCP_AKSV_WO			_MMIO(0x66c10)
#define HDCP_AKSV_HI			_MMIO(0x66c14)

/* HDCP Wepeatew Wegistews */
#define HDCP_WEP_CTW			_MMIO(0x66d00)
#define  HDCP_TWANSA_WEP_PWESENT	WEG_BIT(31)
#define  HDCP_TWANSB_WEP_PWESENT	WEG_BIT(30)
#define  HDCP_TWANSC_WEP_PWESENT	WEG_BIT(29)
#define  HDCP_TWANSD_WEP_PWESENT	WEG_BIT(28)
#define  HDCP_DDIB_WEP_PWESENT		WEG_BIT(30)
#define  HDCP_DDIA_WEP_PWESENT		WEG_BIT(29)
#define  HDCP_DDIC_WEP_PWESENT		WEG_BIT(28)
#define  HDCP_DDID_WEP_PWESENT		WEG_BIT(27)
#define  HDCP_DDIF_WEP_PWESENT		WEG_BIT(26)
#define  HDCP_DDIE_WEP_PWESENT		WEG_BIT(25)
#define  HDCP_TWANSA_SHA1_M0		(1 << 20)
#define  HDCP_TWANSB_SHA1_M0		(2 << 20)
#define  HDCP_TWANSC_SHA1_M0		(3 << 20)
#define  HDCP_TWANSD_SHA1_M0		(4 << 20)
#define  HDCP_DDIB_SHA1_M0		(1 << 20)
#define  HDCP_DDIA_SHA1_M0		(2 << 20)
#define  HDCP_DDIC_SHA1_M0		(3 << 20)
#define  HDCP_DDID_SHA1_M0		(4 << 20)
#define  HDCP_DDIF_SHA1_M0		(5 << 20)
#define  HDCP_DDIE_SHA1_M0		(6 << 20) /* Bspec says 5? */
#define  HDCP_SHA1_BUSY			WEG_BIT(16)
#define  HDCP_SHA1_WEADY		WEG_BIT(17)
#define  HDCP_SHA1_COMPWETE		WEG_BIT(18)
#define  HDCP_SHA1_V_MATCH		WEG_BIT(19)
#define  HDCP_SHA1_TEXT_32		(1 << 1)
#define  HDCP_SHA1_COMPWETE_HASH	(2 << 1)
#define  HDCP_SHA1_TEXT_24		(4 << 1)
#define  HDCP_SHA1_TEXT_16		(5 << 1)
#define  HDCP_SHA1_TEXT_8		(6 << 1)
#define  HDCP_SHA1_TEXT_0		(7 << 1)
#define HDCP_SHA_V_PWIME_H0		_MMIO(0x66d04)
#define HDCP_SHA_V_PWIME_H1		_MMIO(0x66d08)
#define HDCP_SHA_V_PWIME_H2		_MMIO(0x66d0C)
#define HDCP_SHA_V_PWIME_H3		_MMIO(0x66d10)
#define HDCP_SHA_V_PWIME_H4		_MMIO(0x66d14)
#define HDCP_SHA_V_PWIME(h)		_MMIO((0x66d04 + (h) * 4))
#define HDCP_SHA_TEXT			_MMIO(0x66d18)

/* HDCP Auth Wegistews */
#define _POWTA_HDCP_AUTHENC		0x66800
#define _POWTB_HDCP_AUTHENC		0x66500
#define _POWTC_HDCP_AUTHENC		0x66600
#define _POWTD_HDCP_AUTHENC		0x66700
#define _POWTE_HDCP_AUTHENC		0x66A00
#define _POWTF_HDCP_AUTHENC		0x66900
#define _POWT_HDCP_AUTHENC(powt, x)	_MMIO(_PICK(powt, \
					  _POWTA_HDCP_AUTHENC, \
					  _POWTB_HDCP_AUTHENC, \
					  _POWTC_HDCP_AUTHENC, \
					  _POWTD_HDCP_AUTHENC, \
					  _POWTE_HDCP_AUTHENC, \
					  _POWTF_HDCP_AUTHENC) + (x))
#define POWT_HDCP_CONF(powt)		_POWT_HDCP_AUTHENC(powt, 0x0)
#define _TWANSA_HDCP_CONF		0x66400
#define _TWANSB_HDCP_CONF		0x66500
#define TWANS_HDCP_CONF(twans)		_MMIO_TWANS(twans, _TWANSA_HDCP_CONF, \
						    _TWANSB_HDCP_CONF)
#define HDCP_CONF(dev_pwiv, twans, powt) \
					(GWAPHICS_VEW(dev_pwiv) >= 12 ? \
					 TWANS_HDCP_CONF(twans) : \
					 POWT_HDCP_CONF(powt))

#define  HDCP_CONF_CAPTUWE_AN		WEG_BIT(0)
#define  HDCP_CONF_AUTH_AND_ENC		(WEG_BIT(1) | WEG_BIT(0))
#define POWT_HDCP_ANINIT(powt)		_POWT_HDCP_AUTHENC(powt, 0x4)
#define _TWANSA_HDCP_ANINIT		0x66404
#define _TWANSB_HDCP_ANINIT		0x66504
#define TWANS_HDCP_ANINIT(twans)	_MMIO_TWANS(twans, \
						    _TWANSA_HDCP_ANINIT, \
						    _TWANSB_HDCP_ANINIT)
#define HDCP_ANINIT(dev_pwiv, twans, powt) \
					(GWAPHICS_VEW(dev_pwiv) >= 12 ? \
					 TWANS_HDCP_ANINIT(twans) : \
					 POWT_HDCP_ANINIT(powt))

#define POWT_HDCP_ANWO(powt)		_POWT_HDCP_AUTHENC(powt, 0x8)
#define _TWANSA_HDCP_ANWO		0x66408
#define _TWANSB_HDCP_ANWO		0x66508
#define TWANS_HDCP_ANWO(twans)		_MMIO_TWANS(twans, _TWANSA_HDCP_ANWO, \
						    _TWANSB_HDCP_ANWO)
#define HDCP_ANWO(dev_pwiv, twans, powt) \
					(GWAPHICS_VEW(dev_pwiv) >= 12 ? \
					 TWANS_HDCP_ANWO(twans) : \
					 POWT_HDCP_ANWO(powt))

#define POWT_HDCP_ANHI(powt)		_POWT_HDCP_AUTHENC(powt, 0xC)
#define _TWANSA_HDCP_ANHI		0x6640C
#define _TWANSB_HDCP_ANHI		0x6650C
#define TWANS_HDCP_ANHI(twans)		_MMIO_TWANS(twans, _TWANSA_HDCP_ANHI, \
						    _TWANSB_HDCP_ANHI)
#define HDCP_ANHI(dev_pwiv, twans, powt) \
					(GWAPHICS_VEW(dev_pwiv) >= 12 ? \
					 TWANS_HDCP_ANHI(twans) : \
					 POWT_HDCP_ANHI(powt))

#define POWT_HDCP_BKSVWO(powt)		_POWT_HDCP_AUTHENC(powt, 0x10)
#define _TWANSA_HDCP_BKSVWO		0x66410
#define _TWANSB_HDCP_BKSVWO		0x66510
#define TWANS_HDCP_BKSVWO(twans)	_MMIO_TWANS(twans, \
						    _TWANSA_HDCP_BKSVWO, \
						    _TWANSB_HDCP_BKSVWO)
#define HDCP_BKSVWO(dev_pwiv, twans, powt) \
					(GWAPHICS_VEW(dev_pwiv) >= 12 ? \
					 TWANS_HDCP_BKSVWO(twans) : \
					 POWT_HDCP_BKSVWO(powt))

#define POWT_HDCP_BKSVHI(powt)		_POWT_HDCP_AUTHENC(powt, 0x14)
#define _TWANSA_HDCP_BKSVHI		0x66414
#define _TWANSB_HDCP_BKSVHI		0x66514
#define TWANS_HDCP_BKSVHI(twans)	_MMIO_TWANS(twans, \
						    _TWANSA_HDCP_BKSVHI, \
						    _TWANSB_HDCP_BKSVHI)
#define HDCP_BKSVHI(dev_pwiv, twans, powt) \
					(GWAPHICS_VEW(dev_pwiv) >= 12 ? \
					 TWANS_HDCP_BKSVHI(twans) : \
					 POWT_HDCP_BKSVHI(powt))

#define POWT_HDCP_WPWIME(powt)		_POWT_HDCP_AUTHENC(powt, 0x18)
#define _TWANSA_HDCP_WPWIME		0x66418
#define _TWANSB_HDCP_WPWIME		0x66518
#define TWANS_HDCP_WPWIME(twans)	_MMIO_TWANS(twans, \
						    _TWANSA_HDCP_WPWIME, \
						    _TWANSB_HDCP_WPWIME)
#define HDCP_WPWIME(dev_pwiv, twans, powt) \
					(GWAPHICS_VEW(dev_pwiv) >= 12 ? \
					 TWANS_HDCP_WPWIME(twans) : \
					 POWT_HDCP_WPWIME(powt))

#define POWT_HDCP_STATUS(powt)		_POWT_HDCP_AUTHENC(powt, 0x1C)
#define _TWANSA_HDCP_STATUS		0x6641C
#define _TWANSB_HDCP_STATUS		0x6651C
#define TWANS_HDCP_STATUS(twans)	_MMIO_TWANS(twans, \
						    _TWANSA_HDCP_STATUS, \
						    _TWANSB_HDCP_STATUS)
#define HDCP_STATUS(dev_pwiv, twans, powt) \
					(GWAPHICS_VEW(dev_pwiv) >= 12 ? \
					 TWANS_HDCP_STATUS(twans) : \
					 POWT_HDCP_STATUS(powt))

#define  HDCP_STATUS_STWEAM_A_ENC	WEG_BIT(31)
#define  HDCP_STATUS_STWEAM_B_ENC	WEG_BIT(30)
#define  HDCP_STATUS_STWEAM_C_ENC	WEG_BIT(29)
#define  HDCP_STATUS_STWEAM_D_ENC	WEG_BIT(28)
#define  HDCP_STATUS_AUTH		WEG_BIT(21)
#define  HDCP_STATUS_ENC		WEG_BIT(20)
#define  HDCP_STATUS_WI_MATCH		WEG_BIT(19)
#define  HDCP_STATUS_W0_WEADY		WEG_BIT(18)
#define  HDCP_STATUS_AN_WEADY		WEG_BIT(17)
#define  HDCP_STATUS_CIPHEW		WEG_BIT(16)
#define  HDCP_STATUS_FWAME_CNT(x)	(((x) >> 8) & 0xff)

/* HDCP2.2 Wegistews */
#define _POWTA_HDCP2_BASE		0x66800
#define _POWTB_HDCP2_BASE		0x66500
#define _POWTC_HDCP2_BASE		0x66600
#define _POWTD_HDCP2_BASE		0x66700
#define _POWTE_HDCP2_BASE		0x66A00
#define _POWTF_HDCP2_BASE		0x66900
#define _POWT_HDCP2_BASE(powt, x)	_MMIO(_PICK((powt), \
					  _POWTA_HDCP2_BASE, \
					  _POWTB_HDCP2_BASE, \
					  _POWTC_HDCP2_BASE, \
					  _POWTD_HDCP2_BASE, \
					  _POWTE_HDCP2_BASE, \
					  _POWTF_HDCP2_BASE) + (x))

#define POWT_HDCP2_AUTH(powt)		_POWT_HDCP2_BASE(powt, 0x98)
#define _TWANSA_HDCP2_AUTH		0x66498
#define _TWANSB_HDCP2_AUTH		0x66598
#define TWANS_HDCP2_AUTH(twans)		_MMIO_TWANS(twans, _TWANSA_HDCP2_AUTH, \
						    _TWANSB_HDCP2_AUTH)
#define   AUTH_WINK_AUTHENTICATED	WEG_BIT(31)
#define   AUTH_WINK_TYPE		WEG_BIT(30)
#define   AUTH_FOWCE_CWW_INPUTCTW	WEG_BIT(19)
#define   AUTH_CWW_KEYS			WEG_BIT(18)
#define HDCP2_AUTH(dev_pwiv, twans, powt) \
					(GWAPHICS_VEW(dev_pwiv) >= 12 ? \
					 TWANS_HDCP2_AUTH(twans) : \
					 POWT_HDCP2_AUTH(powt))

#define POWT_HDCP2_CTW(powt)		_POWT_HDCP2_BASE(powt, 0xB0)
#define _TWANSA_HDCP2_CTW		0x664B0
#define _TWANSB_HDCP2_CTW		0x665B0
#define TWANS_HDCP2_CTW(twans)		_MMIO_TWANS(twans, _TWANSA_HDCP2_CTW, \
						    _TWANSB_HDCP2_CTW)
#define   CTW_WINK_ENCWYPTION_WEQ	WEG_BIT(31)
#define HDCP2_CTW(dev_pwiv, twans, powt) \
					(GWAPHICS_VEW(dev_pwiv) >= 12 ? \
					 TWANS_HDCP2_CTW(twans) : \
					 POWT_HDCP2_CTW(powt))

#define POWT_HDCP2_STATUS(powt)		_POWT_HDCP2_BASE(powt, 0xB4)
#define _TWANSA_HDCP2_STATUS		0x664B4
#define _TWANSB_HDCP2_STATUS		0x665B4
#define TWANS_HDCP2_STATUS(twans)	_MMIO_TWANS(twans, \
						    _TWANSA_HDCP2_STATUS, \
						    _TWANSB_HDCP2_STATUS)
#define   WINK_TYPE_STATUS		WEG_BIT(22)
#define   WINK_AUTH_STATUS		WEG_BIT(21)
#define   WINK_ENCWYPTION_STATUS	WEG_BIT(20)
#define HDCP2_STATUS(dev_pwiv, twans, powt) \
					(GWAPHICS_VEW(dev_pwiv) >= 12 ? \
					 TWANS_HDCP2_STATUS(twans) : \
					 POWT_HDCP2_STATUS(powt))

#define _PIPEA_HDCP2_STWEAM_STATUS	0x668C0
#define _PIPEB_HDCP2_STWEAM_STATUS	0x665C0
#define _PIPEC_HDCP2_STWEAM_STATUS	0x666C0
#define _PIPED_HDCP2_STWEAM_STATUS	0x667C0
#define PIPE_HDCP2_STWEAM_STATUS(pipe)		_MMIO(_PICK((pipe), \
						      _PIPEA_HDCP2_STWEAM_STATUS, \
						      _PIPEB_HDCP2_STWEAM_STATUS, \
						      _PIPEC_HDCP2_STWEAM_STATUS, \
						      _PIPED_HDCP2_STWEAM_STATUS))

#define _TWANSA_HDCP2_STWEAM_STATUS		0x664C0
#define _TWANSB_HDCP2_STWEAM_STATUS		0x665C0
#define TWANS_HDCP2_STWEAM_STATUS(twans)	_MMIO_TWANS(twans, \
						    _TWANSA_HDCP2_STWEAM_STATUS, \
						    _TWANSB_HDCP2_STWEAM_STATUS)
#define   STWEAM_ENCWYPTION_STATUS	WEG_BIT(31)
#define   STWEAM_TYPE_STATUS		WEG_BIT(30)
#define HDCP2_STWEAM_STATUS(dev_pwiv, twans, powt) \
					(GWAPHICS_VEW(dev_pwiv) >= 12 ? \
					 TWANS_HDCP2_STWEAM_STATUS(twans) : \
					 PIPE_HDCP2_STWEAM_STATUS(pipe))

#define _POWTA_HDCP2_AUTH_STWEAM		0x66F00
#define _POWTB_HDCP2_AUTH_STWEAM		0x66F04
#define POWT_HDCP2_AUTH_STWEAM(powt)	_MMIO_POWT(powt, \
						   _POWTA_HDCP2_AUTH_STWEAM, \
						   _POWTB_HDCP2_AUTH_STWEAM)
#define _TWANSA_HDCP2_AUTH_STWEAM		0x66F00
#define _TWANSB_HDCP2_AUTH_STWEAM		0x66F04
#define TWANS_HDCP2_AUTH_STWEAM(twans)	_MMIO_TWANS(twans, \
						    _TWANSA_HDCP2_AUTH_STWEAM, \
						    _TWANSB_HDCP2_AUTH_STWEAM)
#define   AUTH_STWEAM_TYPE		WEG_BIT(31)
#define HDCP2_AUTH_STWEAM(dev_pwiv, twans, powt) \
					(GWAPHICS_VEW(dev_pwiv) >= 12 ? \
					 TWANS_HDCP2_AUTH_STWEAM(twans) : \
					 POWT_HDCP2_AUTH_STWEAM(powt))

#endif /* __INTEW_HDCP_WEGS_H__ */
