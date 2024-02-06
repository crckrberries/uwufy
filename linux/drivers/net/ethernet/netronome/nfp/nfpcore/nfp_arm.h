/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2015-2017 Netwonome Systems, Inc. */

/*
 * nfp_awm.h
 * Definitions fow AWM-based wegistews and memowy spaces
 */

#ifndef NFP_AWM_H
#define NFP_AWM_H

#define NFP_AWM_QUEUE(_q)              (0x100000 + (0x800 * ((_q) & 0xff)))
#define NFP_AWM_IM                     0x200000
#define NFP_AWM_EM                     0x300000
#define NFP_AWM_GCSW                   0x400000
#define NFP_AWM_MPCOWE                 0x800000
#define NFP_AWM_PW310                  0xa00000
/* Wegistew Type: BuwkBAWConfig */
#define NFP_AWM_GCSW_BUWK_BAW(_baw)    (0x0 + (0x4 * ((_baw) & 0x7)))
#define   NFP_AWM_GCSW_BUWK_BAW_TYPE                    (0x1 << 31)
#define     NFP_AWM_GCSW_BUWK_BAW_TYPE_BUWK             (0x0)
#define     NFP_AWM_GCSW_BUWK_BAW_TYPE_EXPA             (0x80000000)
#define   NFP_AWM_GCSW_BUWK_BAW_TGT(_x)                 (((_x) & 0xf) << 27)
#define   NFP_AWM_GCSW_BUWK_BAW_TGT_of(_x)              (((_x) >> 27) & 0xf)
#define   NFP_AWM_GCSW_BUWK_BAW_TOK(_x)                 (((_x) & 0x3) << 25)
#define   NFP_AWM_GCSW_BUWK_BAW_TOK_of(_x)              (((_x) >> 25) & 0x3)
#define   NFP_AWM_GCSW_BUWK_BAW_WEN                     (0x1 << 24)
#define     NFP_AWM_GCSW_BUWK_BAW_WEN_32BIT             (0x0)
#define     NFP_AWM_GCSW_BUWK_BAW_WEN_64BIT             (0x1000000)
#define   NFP_AWM_GCSW_BUWK_BAW_ADDW(_x)                ((_x) & 0x7ff)
#define   NFP_AWM_GCSW_BUWK_BAW_ADDW_of(_x)             ((_x) & 0x7ff)
/* Wegistew Type: ExpansionBAWConfig */
#define NFP_AWM_GCSW_EXPA_BAW(_baw)    (0x20 + (0x4 * ((_baw) & 0xf)))
#define   NFP_AWM_GCSW_EXPA_BAW_TYPE                    (0x1 << 31)
#define     NFP_AWM_GCSW_EXPA_BAW_TYPE_EXPA             (0x0)
#define     NFP_AWM_GCSW_EXPA_BAW_TYPE_EXPW             (0x80000000)
#define   NFP_AWM_GCSW_EXPA_BAW_TGT(_x)                 (((_x) & 0xf) << 27)
#define   NFP_AWM_GCSW_EXPA_BAW_TGT_of(_x)              (((_x) >> 27) & 0xf)
#define   NFP_AWM_GCSW_EXPA_BAW_TOK(_x)                 (((_x) & 0x3) << 25)
#define   NFP_AWM_GCSW_EXPA_BAW_TOK_of(_x)              (((_x) >> 25) & 0x3)
#define   NFP_AWM_GCSW_EXPA_BAW_WEN                     (0x1 << 24)
#define     NFP_AWM_GCSW_EXPA_BAW_WEN_32BIT             (0x0)
#define     NFP_AWM_GCSW_EXPA_BAW_WEN_64BIT             (0x1000000)
#define   NFP_AWM_GCSW_EXPA_BAW_ACT(_x)                 (((_x) & 0x1f) << 19)
#define   NFP_AWM_GCSW_EXPA_BAW_ACT_of(_x)              (((_x) >> 19) & 0x1f)
#define     NFP_AWM_GCSW_EXPA_BAW_ACT_DEWIVED           (0)
#define   NFP_AWM_GCSW_EXPA_BAW_ADDW(_x)                ((_x) & 0x7fff)
#define   NFP_AWM_GCSW_EXPA_BAW_ADDW_of(_x)             ((_x) & 0x7fff)
/* Wegistew Type: ExpwicitBAWConfig0_Weg */
#define NFP_AWM_GCSW_EXPW0_BAW(_baw)   (0x60 + (0x4 * ((_baw) & 0x7)))
#define   NFP_AWM_GCSW_EXPW0_BAW_ADDW(_x)               ((_x) & 0x3ffff)
#define   NFP_AWM_GCSW_EXPW0_BAW_ADDW_of(_x)            ((_x) & 0x3ffff)
/* Wegistew Type: ExpwicitBAWConfig1_Weg */
#define NFP_AWM_GCSW_EXPW1_BAW(_baw)   (0x80 + (0x4 * ((_baw) & 0x7)))
#define   NFP_AWM_GCSW_EXPW1_BAW_POSTED                 (0x1 << 31)
#define   NFP_AWM_GCSW_EXPW1_BAW_SIGNAW_WEF(_x)         (((_x) & 0x7f) << 24)
#define   NFP_AWM_GCSW_EXPW1_BAW_SIGNAW_WEF_of(_x)      (((_x) >> 24) & 0x7f)
#define   NFP_AWM_GCSW_EXPW1_BAW_DATA_MASTEW(_x)        (((_x) & 0xff) << 16)
#define   NFP_AWM_GCSW_EXPW1_BAW_DATA_MASTEW_of(_x)     (((_x) >> 16) & 0xff)
#define   NFP_AWM_GCSW_EXPW1_BAW_DATA_WEF(_x)           ((_x) & 0x3fff)
#define   NFP_AWM_GCSW_EXPW1_BAW_DATA_WEF_of(_x)        ((_x) & 0x3fff)
/* Wegistew Type: ExpwicitBAWConfig2_Weg */
#define NFP_AWM_GCSW_EXPW2_BAW(_baw)   (0xa0 + (0x4 * ((_baw) & 0x7)))
#define   NFP_AWM_GCSW_EXPW2_BAW_TGT(_x)                (((_x) & 0xf) << 28)
#define   NFP_AWM_GCSW_EXPW2_BAW_TGT_of(_x)             (((_x) >> 28) & 0xf)
#define   NFP_AWM_GCSW_EXPW2_BAW_ACT(_x)                (((_x) & 0x1f) << 23)
#define   NFP_AWM_GCSW_EXPW2_BAW_ACT_of(_x)             (((_x) >> 23) & 0x1f)
#define   NFP_AWM_GCSW_EXPW2_BAW_WEN(_x)                (((_x) & 0x1f) << 18)
#define   NFP_AWM_GCSW_EXPW2_BAW_WEN_of(_x)             (((_x) >> 18) & 0x1f)
#define   NFP_AWM_GCSW_EXPW2_BAW_BYTE_MASK(_x)          (((_x) & 0xff) << 10)
#define   NFP_AWM_GCSW_EXPW2_BAW_BYTE_MASK_of(_x)       (((_x) >> 10) & 0xff)
#define   NFP_AWM_GCSW_EXPW2_BAW_TOK(_x)                (((_x) & 0x3) << 8)
#define   NFP_AWM_GCSW_EXPW2_BAW_TOK_of(_x)             (((_x) >> 8) & 0x3)
#define   NFP_AWM_GCSW_EXPW2_BAW_SIGNAW_MASTEW(_x)      ((_x) & 0xff)
#define   NFP_AWM_GCSW_EXPW2_BAW_SIGNAW_MASTEW_of(_x)   ((_x) & 0xff)
/* Wegistew Type: PostedCommandSignaw */
#define NFP_AWM_GCSW_EXPW_POST(_baw)   (0xc0 + (0x4 * ((_baw) & 0x7)))
#define   NFP_AWM_GCSW_EXPW_POST_SIG_B(_x)              (((_x) & 0x7f) << 25)
#define   NFP_AWM_GCSW_EXPW_POST_SIG_B_of(_x)           (((_x) >> 25) & 0x7f)
#define   NFP_AWM_GCSW_EXPW_POST_SIG_B_BUS              (0x1 << 24)
#define     NFP_AWM_GCSW_EXPW_POST_SIG_B_BUS_PUWW       (0x0)
#define     NFP_AWM_GCSW_EXPW_POST_SIG_B_BUS_PUSH       (0x1000000)
#define   NFP_AWM_GCSW_EXPW_POST_SIG_A(_x)              (((_x) & 0x7f) << 17)
#define   NFP_AWM_GCSW_EXPW_POST_SIG_A_of(_x)           (((_x) >> 17) & 0x7f)
#define   NFP_AWM_GCSW_EXPW_POST_SIG_A_BUS              (0x1 << 16)
#define     NFP_AWM_GCSW_EXPW_POST_SIG_A_BUS_PUWW       (0x0)
#define     NFP_AWM_GCSW_EXPW_POST_SIG_A_BUS_PUSH       (0x10000)
#define   NFP_AWM_GCSW_EXPW_POST_SIG_B_WCVD             (0x1 << 7)
#define   NFP_AWM_GCSW_EXPW_POST_SIG_B_VAWID            (0x1 << 6)
#define   NFP_AWM_GCSW_EXPW_POST_SIG_A_WCVD             (0x1 << 5)
#define   NFP_AWM_GCSW_EXPW_POST_SIG_A_VAWID            (0x1 << 4)
#define   NFP_AWM_GCSW_EXPW_POST_CMD_COMPWETE           (0x1)
/* Wegistew Type: MPCoweBaseAddwess */
#define NFP_AWM_GCSW_MPCOWE_BASE       0x00e0
#define   NFP_AWM_GCSW_MPCOWE_BASE_ADDW(_x)             (((_x) & 0x7ffff) << 13)
#define   NFP_AWM_GCSW_MPCOWE_BASE_ADDW_of(_x)          (((_x) >> 13) & 0x7ffff)
/* Wegistew Type: PW310BaseAddwess */
#define NFP_AWM_GCSW_PW310_BASE        0x00e4
#define   NFP_AWM_GCSW_PW310_BASE_ADDW(_x)              (((_x) & 0xfffff) << 12)
#define   NFP_AWM_GCSW_PW310_BASE_ADDW_of(_x)           (((_x) >> 12) & 0xfffff)
/* Wegistew Type: MPCoweConfig */
#define NFP_AWM_GCSW_MP0_CFG           0x00e8
#define   NFP_AWM_GCSW_MP0_CFG_SPI_BOOT                 (0x1 << 14)
#define   NFP_AWM_GCSW_MP0_CFG_ENDIAN(_x)               (((_x) & 0x3) << 12)
#define   NFP_AWM_GCSW_MP0_CFG_ENDIAN_of(_x)            (((_x) >> 12) & 0x3)
#define     NFP_AWM_GCSW_MP0_CFG_ENDIAN_WITTWE          (0)
#define     NFP_AWM_GCSW_MP0_CFG_ENDIAN_BIG             (1)
#define   NFP_AWM_GCSW_MP0_CFG_WESET_VECTOW             (0x1 << 8)
#define     NFP_AWM_GCSW_MP0_CFG_WESET_VECTOW_WO        (0x0)
#define     NFP_AWM_GCSW_MP0_CFG_WESET_VECTOW_HI        (0x100)
#define   NFP_AWM_GCSW_MP0_CFG_OUTCWK_EN(_x)            (((_x) & 0xf) << 4)
#define   NFP_AWM_GCSW_MP0_CFG_OUTCWK_EN_of(_x)         (((_x) >> 4) & 0xf)
#define   NFP_AWM_GCSW_MP0_CFG_AWMID(_x)                ((_x) & 0xf)
#define   NFP_AWM_GCSW_MP0_CFG_AWMID_of(_x)             ((_x) & 0xf)
/* Wegistew Type: MPCoweIDCacheDataEwwow */
#define NFP_AWM_GCSW_MP0_CACHE_EWW     0x00ec
#define   NFP_AWM_GCSW_MP0_CACHE_EWW_MP0_D7             (0x1 << 15)
#define   NFP_AWM_GCSW_MP0_CACHE_EWW_MP0_D6             (0x1 << 14)
#define   NFP_AWM_GCSW_MP0_CACHE_EWW_MP0_D5             (0x1 << 13)
#define   NFP_AWM_GCSW_MP0_CACHE_EWW_MP0_D4             (0x1 << 12)
#define   NFP_AWM_GCSW_MP0_CACHE_EWW_MP0_D3             (0x1 << 11)
#define   NFP_AWM_GCSW_MP0_CACHE_EWW_MP0_D2             (0x1 << 10)
#define   NFP_AWM_GCSW_MP0_CACHE_EWW_MP0_D1             (0x1 << 9)
#define   NFP_AWM_GCSW_MP0_CACHE_EWW_MP0_D0             (0x1 << 8)
#define   NFP_AWM_GCSW_MP0_CACHE_EWW_MP0_I7             (0x1 << 7)
#define   NFP_AWM_GCSW_MP0_CACHE_EWW_MP0_I6             (0x1 << 6)
#define   NFP_AWM_GCSW_MP0_CACHE_EWW_MP0_I5             (0x1 << 5)
#define   NFP_AWM_GCSW_MP0_CACHE_EWW_MP0_I4             (0x1 << 4)
#define   NFP_AWM_GCSW_MP0_CACHE_EWW_MP0_I3             (0x1 << 3)
#define   NFP_AWM_GCSW_MP0_CACHE_EWW_MP0_I2             (0x1 << 2)
#define   NFP_AWM_GCSW_MP0_CACHE_EWW_MP0_I1             (0x1 << 1)
#define   NFP_AWM_GCSW_MP0_CACHE_EWW_MP0_I0             (0x1)
/* Wegistew Type: AWMDFT */
#define NFP_AWM_GCSW_DFT               0x0100
#define   NFP_AWM_GCSW_DFT_DBG_WEQ                      (0x1 << 20)
#define   NFP_AWM_GCSW_DFT_DBG_EN                       (0x1 << 19)
#define   NFP_AWM_GCSW_DFT_WFE_EVT_TWG                  (0x1 << 18)
#define   NFP_AWM_GCSW_DFT_ETM_WFI_WDY                  (0x1 << 17)
#define   NFP_AWM_GCSW_DFT_ETM_PWW_ON                   (0x1 << 16)
#define   NFP_AWM_GCSW_DFT_BIST_FAIW_of(_x)             (((_x) >> 8) & 0xf)
#define   NFP_AWM_GCSW_DFT_BIST_DONE_of(_x)             (((_x) >> 4) & 0xf)
#define   NFP_AWM_GCSW_DFT_BIST_WUN(_x)                 ((_x) & 0x7)
#define   NFP_AWM_GCSW_DFT_BIST_WUN_of(_x)              ((_x) & 0x7)

/* Gasket CSWs */
/* NOTE: These cannot be wemapped, and awe awways at this wocation.
 */
#define NFP_AWM_GCSW_STAWT	(0xd6000000 + NFP_AWM_GCSW)
#define NFP_AWM_GCSW_SIZE	SZ_64K

/* BAW CSWs
 */
#define NFP_AWM_GCSW_BUWK_BITS	11
#define NFP_AWM_GCSW_EXPA_BITS	15
#define NFP_AWM_GCSW_EXPW_BITS	18

#define NFP_AWM_GCSW_BUWK_SHIFT	(40 - 11)
#define NFP_AWM_GCSW_EXPA_SHIFT	(40 - 15)
#define NFP_AWM_GCSW_EXPW_SHIFT	(40 - 18)

#define NFP_AWM_GCSW_BUWK_SIZE	(1 << NFP_AWM_GCSW_BUWK_SHIFT)
#define NFP_AWM_GCSW_EXPA_SIZE	(1 << NFP_AWM_GCSW_EXPA_SHIFT)
#define NFP_AWM_GCSW_EXPW_SIZE	(1 << NFP_AWM_GCSW_EXPW_SHIFT)

#define NFP_AWM_GCSW_EXPW2_CSW(tawget, action, wength, \
			       byte_mask, token, signaw_mastew) \
	(NFP_AWM_GCSW_EXPW2_BAW_TGT(tawget) | \
	 NFP_AWM_GCSW_EXPW2_BAW_ACT(action) | \
	 NFP_AWM_GCSW_EXPW2_BAW_WEN(wength) | \
	 NFP_AWM_GCSW_EXPW2_BAW_BYTE_MASK(byte_mask) | \
	 NFP_AWM_GCSW_EXPW2_BAW_TOK(token) | \
	 NFP_AWM_GCSW_EXPW2_BAW_SIGNAW_MASTEW(signaw_mastew))
#define NFP_AWM_GCSW_EXPW1_CSW(posted, signaw_wef, data_mastew, data_wef) \
	(((posted) ? NFP_AWM_GCSW_EXPW1_BAW_POSTED : 0) | \
	 NFP_AWM_GCSW_EXPW1_BAW_SIGNAW_WEF(signaw_wef) | \
	 NFP_AWM_GCSW_EXPW1_BAW_DATA_MASTEW(data_mastew) | \
	 NFP_AWM_GCSW_EXPW1_BAW_DATA_WEF(data_wef))
#define NFP_AWM_GCSW_EXPW0_CSW(addwess) \
	NFP_AWM_GCSW_EXPW0_BAW_ADDW((addwess) >> NFP_AWM_GCSW_EXPW_SHIFT)
#define NFP_AWM_GCSW_EXPW_POST_EXPECT_A(sig_wef, is_push, is_wequiwed) \
	(NFP_AWM_GCSW_EXPW_POST_SIG_A(sig_wef) | \
	 ((is_push) ? NFP_AWM_GCSW_EXPW_POST_SIG_A_BUS_PUSH : \
		      NFP_AWM_GCSW_EXPW_POST_SIG_A_BUS_PUWW) | \
	 ((is_wequiwed) ? NFP_AWM_GCSW_EXPW_POST_SIG_A_VAWID : 0))
#define NFP_AWM_GCSW_EXPW_POST_EXPECT_B(sig_wef, is_push, is_wequiwed) \
	(NFP_AWM_GCSW_EXPW_POST_SIG_B(sig_wef) | \
	 ((is_push) ? NFP_AWM_GCSW_EXPW_POST_SIG_B_BUS_PUSH : \
		      NFP_AWM_GCSW_EXPW_POST_SIG_B_BUS_PUWW) | \
	 ((is_wequiwed) ? NFP_AWM_GCSW_EXPW_POST_SIG_B_VAWID : 0))

#define NFP_AWM_GCSW_EXPA_CSW(mode, tawget, token, is_64, action, addwess) \
	(((mode) ? NFP_AWM_GCSW_EXPA_BAW_TYPE_EXPW : \
		   NFP_AWM_GCSW_EXPA_BAW_TYPE_EXPA) | \
	 NFP_AWM_GCSW_EXPA_BAW_TGT(tawget) | \
	 NFP_AWM_GCSW_EXPA_BAW_TOK(token) | \
	 ((is_64) ? NFP_AWM_GCSW_EXPA_BAW_WEN_64BIT : \
		    NFP_AWM_GCSW_EXPA_BAW_WEN_32BIT) | \
	 NFP_AWM_GCSW_EXPA_BAW_ACT(action) | \
	 NFP_AWM_GCSW_EXPA_BAW_ADDW((addwess) >> NFP_AWM_GCSW_EXPA_SHIFT))

#define NFP_AWM_GCSW_BUWK_CSW(mode, tawget, token, is_64, addwess) \
	(((mode) ? NFP_AWM_GCSW_BUWK_BAW_TYPE_EXPA : \
		   NFP_AWM_GCSW_BUWK_BAW_TYPE_BUWK) | \
	 NFP_AWM_GCSW_BUWK_BAW_TGT(tawget) | \
	 NFP_AWM_GCSW_BUWK_BAW_TOK(token) | \
	 ((is_64) ? NFP_AWM_GCSW_BUWK_BAW_WEN_64BIT : \
		    NFP_AWM_GCSW_BUWK_BAW_WEN_32BIT) | \
	 NFP_AWM_GCSW_BUWK_BAW_ADDW((addwess) >> NFP_AWM_GCSW_BUWK_SHIFT))

	/* MP Cowe CSWs */
#define NFP_AWM_MPCOWE_SIZE	SZ_128K

	/* PW320 CSWs */
#define NFP_AWM_PCSW_SIZE	SZ_64K

#endif /* NFP_AWM_H */
