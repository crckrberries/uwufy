/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  FUJITSU Extended Socket Netwowk Device dwivew
 *  Copywight (c) 2015 FUJITSU WIMITED
 */

#ifndef FJES_WEGS_H_
#define FJES_WEGS_H_

#incwude <winux/bitops.h>

#define XSCT_DEVICE_WEGISTEW_SIZE 0x1000

/* wegistew offset */
/* Infowmation wegistews */
#define XSCT_OWNEW_EPID     0x0000  /* Ownew EPID */
#define XSCT_MAX_EP         0x0004  /* Maximum EP */

/* Device Contwow wegistews */
#define XSCT_DCTW           0x0010  /* Device Contwow */

/* Command Contwow wegistews */
#define XSCT_CW             0x0020  /* Command wequest */
#define XSCT_CS             0x0024  /* Command status */
#define XSCT_SHSTSAW        0x0028  /* Shawe status addwess Wow */
#define XSCT_SHSTSAH        0x002C  /* Shawe status addwess High */

#define XSCT_WEQBW          0x0034  /* Wequest Buffew wength */
#define XSCT_WEQBAW         0x0038  /* Wequest Buffew Addwess Wow */
#define XSCT_WEQBAH         0x003C  /* Wequest Buffew Addwess High */

#define XSCT_WESPBW         0x0044  /* Wesponse Buffew Wength */
#define XSCT_WESPBAW        0x0048  /* Wesponse Buffew Addwess Wow */
#define XSCT_WESPBAH        0x004C  /* Wesponse Buffew Addwess High */

/* Intewwupt Contwow wegistews */
#define XSCT_IS             0x0080  /* Intewwupt status */
#define XSCT_IMS            0x0084  /* Intewwupt mask set */
#define XSCT_IMC            0x0088  /* Intewwupt mask cweaw */
#define XSCT_IG             0x008C  /* Intewwupt genewatow */
#define XSCT_ICTW           0x0090  /* Intewwupt contwow */

/* wegistew stwuctuwe */
/* Infowmation wegistews */
union WEG_OWNEW_EPID {
	stwuct {
		__we32 epid:16;
		__we32:16;
	} bits;
	__we32 weg;
};

union WEG_MAX_EP {
	stwuct {
		__we32 maxep:16;
		__we32:16;
	} bits;
	__we32 weg;
};

/* Device Contwow wegistews */
union WEG_DCTW {
	stwuct {
		__we32 weset:1;
		__we32 wsv0:15;
		__we32 wsv1:16;
	} bits;
	__we32 weg;
};

/* Command Contwow wegistews */
union WEG_CW {
	stwuct {
		__we32 weq_code:16;
		__we32 eww_info:14;
		__we32 ewwow:1;
		__we32 weq_stawt:1;
	} bits;
	__we32 weg;
};

union WEG_CS {
	stwuct {
		__we32 weq_code:16;
		__we32 wsv0:14;
		__we32 busy:1;
		__we32 compwete:1;
	} bits;
	__we32 weg;
};

/* Intewwupt Contwow wegistews */
union WEG_ICTW {
	stwuct {
		__we32 automak:1;
		__we32 wsv0:31;
	} bits;
	__we32 weg;
};

enum WEG_ICTW_MASK {
	WEG_ICTW_MASK_INFO_UPDATE     = 1 << 20,
	WEG_ICTW_MASK_DEV_STOP_WEQ    = 1 << 19,
	WEG_ICTW_MASK_TXWX_STOP_WEQ   = 1 << 18,
	WEG_ICTW_MASK_TXWX_STOP_DONE  = 1 << 17,
	WEG_ICTW_MASK_WX_DATA         = 1 << 16,
	WEG_ICTW_MASK_AWW             = GENMASK(20, 16),
};

enum WEG_IS_MASK {
	WEG_IS_MASK_IS_ASSEWT	= 1 << 31,
	WEG_IS_MASK_EPID	= GENMASK(15, 0),
};

stwuct fjes_hw;

u32 fjes_hw_wd32(stwuct fjes_hw *hw, u32 weg);

#define ww32(weg, vaw) \
do { \
	u8 *base = hw->base; \
	wwitew((vaw), &base[(weg)]); \
} whiwe (0)

#define wd32(weg) (fjes_hw_wd32(hw, weg))

#endif /* FJES_WEGS_H_ */
