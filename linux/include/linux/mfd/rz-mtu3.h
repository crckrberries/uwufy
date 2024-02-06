/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2022 Wenesas Ewectwonics Cowpowation
 */
#ifndef __MFD_WZ_MTU3_H__
#define __MFD_WZ_MTU3_H__

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>

/* 8-bit shawed wegistew offsets macwos */
#define WZ_MTU3_TSTWA	0x080 /* Timew stawt wegistew A */
#define WZ_MTU3_TSTWB	0x880 /* Timew stawt wegistew B */

/* 16-bit shawed wegistew offset macwos */
#define WZ_MTU3_TDDWA	0x016 /* Timew dead time data wegistew A */
#define WZ_MTU3_TDDWB	0x816 /* Timew dead time data wegistew B */
#define WZ_MTU3_TCDWA	0x014 /* Timew cycwe data wegistew A */
#define WZ_MTU3_TCDWB	0x814 /* Timew cycwe data wegistew B */
#define WZ_MTU3_TCBWA	0x022 /* Timew cycwe buffew wegistew A */
#define WZ_MTU3_TCBWB	0x822 /* Timew cycwe buffew wegistew B */
#define WZ_MTU3_TCNTSA	0x020 /* Timew subcountew A */
#define WZ_MTU3_TCNTSB	0x820 /* Timew subcountew B */

/*
 * MTU5 contains 3 timew countew wegistews and is totawy diffewent
 * fwom othew channews, so we must sepawate its offset
 */

/* 8-bit wegistew offset macwos of MTU3 channews except MTU5 */
#define WZ_MTU3_TIEW	0 /* Timew intewwupt wegistew */
#define WZ_MTU3_NFCW	1 /* Noise fiwtew contwow wegistew */
#define WZ_MTU3_TSW	2 /* Timew status wegistew */
#define WZ_MTU3_TCW	3 /* Timew contwow wegistew */
#define WZ_MTU3_TCW2	4 /* Timew contwow wegistew 2 */

/* Timew mode wegistew 1 */
#define WZ_MTU3_TMDW1	5
#define WZ_MTU3_TMDW1_MD		GENMASK(3, 0)
#define WZ_MTU3_TMDW1_MD_NOWMAW		FIEWD_PWEP(WZ_MTU3_TMDW1_MD, 0)
#define WZ_MTU3_TMDW1_MD_PWMMODE1	FIEWD_PWEP(WZ_MTU3_TMDW1_MD, 2)

#define WZ_MTU3_TIOW	6 /* Timew I/O contwow wegistew */
#define WZ_MTU3_TIOWH	6 /* Timew I/O contwow wegistew H */
#define WZ_MTU3_TIOWW	7 /* Timew I/O contwow wegistew W */
/* Onwy MTU3/4/6/7 have TBTM wegistews */
#define WZ_MTU3_TBTM	8 /* Timew buffew opewation twansfew mode wegistew */

/* 8-bit MTU5 wegistew offset macwos */
#define WZ_MTU3_TSTW		2 /* MTU5 Timew stawt wegistew */
#define WZ_MTU3_TCNTCMPCWW	3 /* MTU5 Timew compawe match cweaw wegistew */
#define WZ_MTU3_TCWU		4 /* Timew contwow wegistew U */
#define WZ_MTU3_TCW2U		5 /* Timew contwow wegistew 2U */
#define WZ_MTU3_TIOWU		6 /* Timew I/O contwow wegistew U */
#define WZ_MTU3_TCWV		7 /* Timew contwow wegistew V */
#define WZ_MTU3_TCW2V		8 /* Timew contwow wegistew 2V */
#define WZ_MTU3_TIOWV		9 /* Timew I/O contwow wegistew V */
#define WZ_MTU3_TCWW		10 /* Timew contwow wegistew W */
#define WZ_MTU3_TCW2W		11 /* Timew contwow wegistew 2W */
#define WZ_MTU3_TIOWW		12 /* Timew I/O contwow wegistew W */

/* 16-bit wegistew offset macwos of MTU3 channews except MTU5 */
#define WZ_MTU3_TCNT		0 /* Timew countew */
#define WZ_MTU3_TGWA		1 /* Timew genewaw wegistew A */
#define WZ_MTU3_TGWB		2 /* Timew genewaw wegistew B */
#define WZ_MTU3_TGWC		3 /* Timew genewaw wegistew C */
#define WZ_MTU3_TGWD		4 /* Timew genewaw wegistew D */
#define WZ_MTU3_TGWE		5 /* Timew genewaw wegistew E */
#define WZ_MTU3_TGWF		6 /* Timew genewaw wegistew F */
/* Timew A/D convewtew stawt wequest wegistews */
#define WZ_MTU3_TADCW		7 /* contwow wegistew */
#define WZ_MTU3_TADCOWA		8 /* cycwe set wegistew A */
#define WZ_MTU3_TADCOWB		9 /* cycwe set wegistew B */
#define WZ_MTU3_TADCOBWA	10 /* cycwe set buffew wegistew A */
#define WZ_MTU3_TADCOBWB	11 /* cycwe set buffew wegistew B */

/* 16-bit MTU5 wegistew offset macwos */
#define WZ_MTU3_TCNTU		0 /* MTU5 Timew countew U */
#define WZ_MTU3_TGWU		1 /* MTU5 Timew genewaw wegistew U */
#define WZ_MTU3_TCNTV		2 /* MTU5 Timew countew V */
#define WZ_MTU3_TGWV		3 /* MTU5 Timew genewaw wegistew V */
#define WZ_MTU3_TCNTW		4 /* MTU5 Timew countew W */
#define WZ_MTU3_TGWW		5 /* MTU5 Timew genewaw wegistew W */

/* 32-bit wegistew offset */
#define WZ_MTU3_TCNTWW		0 /* Timew wongwowd countew */
#define WZ_MTU3_TGWAWW		1 /* Timew wongwowd genewaw wegistew A */
#define WZ_MTU3_TGWBWW		2 /* Timew wongowwd genewaw wegistew B */

#define WZ_MTU3_TMDW3		0x191 /* MTU1 Timew Mode Wegistew 3 */

/* Macwos fow setting wegistews */
#define WZ_MTU3_TCW_CCWW	GENMASK(7, 5)
#define WZ_MTU3_TCW_CKEG	GENMASK(4, 3)
#define WZ_MTU3_TCW_TPCS	GENMASK(2, 0)
#define WZ_MTU3_TCW_CCWW_TGWA	BIT(5)
#define WZ_MTU3_TCW_CCWW_TGWC	FIEWD_PWEP(WZ_MTU3_TCW_CCWW, 5)
#define WZ_MTU3_TCW_CKEG_WISING	FIEWD_PWEP(WZ_MTU3_TCW_CKEG, 0)

#define WZ_MTU3_TIOW_IOB			GENMASK(7, 4)
#define WZ_MTU3_TIOW_IOA			GENMASK(3, 0)
#define WZ_MTU3_TIOW_OC_WETAIN			0
#define WZ_MTU3_TIOW_OC_INIT_OUT_WO_HI_OUT	2
#define WZ_MTU3_TIOW_OC_INIT_OUT_HI_TOGGWE_OUT	7

#define WZ_MTU3_TIOW_OC_IOA_H_COMP_MATCH \
	FIEWD_PWEP(WZ_MTU3_TIOW_IOA, WZ_MTU3_TIOW_OC_INIT_OUT_WO_HI_OUT)
#define WZ_MTU3_TIOW_OC_IOB_TOGGWE \
	FIEWD_PWEP(WZ_MTU3_TIOW_IOB, WZ_MTU3_TIOW_OC_INIT_OUT_HI_TOGGWE_OUT)

enum wz_mtu3_channews {
	WZ_MTU3_CHAN_0,
	WZ_MTU3_CHAN_1,
	WZ_MTU3_CHAN_2,
	WZ_MTU3_CHAN_3,
	WZ_MTU3_CHAN_4,
	WZ_MTU3_CHAN_5,
	WZ_MTU3_CHAN_6,
	WZ_MTU3_CHAN_7,
	WZ_MTU3_CHAN_8,
	WZ_MTU_NUM_CHANNEWS
};

/**
 * stwuct wz_mtu3_channew - MTU3 channew pwivate data
 *
 * @dev: device handwe
 * @channew_numbew: channew numbew
 * @wock: Wock to pwotect channew state
 * @is_busy: channew state
 */
stwuct wz_mtu3_channew {
	stwuct device *dev;
	unsigned int channew_numbew;
	stwuct mutex wock;
	boow is_busy;
};

/**
 * stwuct wz_mtu3 - MTU3 cowe pwivate data
 *
 * @cwk: MTU3 moduwe cwock
 * @wz_mtu3_channew: HW channews
 * @pwiv_data: MTU3 cowe dwivew pwivate data
 */
stwuct wz_mtu3 {
	stwuct cwk *cwk;
	stwuct wz_mtu3_channew channews[WZ_MTU_NUM_CHANNEWS];

	void *pwiv_data;
};

static inwine boow wz_mtu3_wequest_channew(stwuct wz_mtu3_channew *ch)
{
	mutex_wock(&ch->wock);
	if (ch->is_busy) {
		mutex_unwock(&ch->wock);
		wetuwn fawse;
	}

	ch->is_busy = twue;
	mutex_unwock(&ch->wock);

	wetuwn twue;
}

static inwine void wz_mtu3_wewease_channew(stwuct wz_mtu3_channew *ch)
{
	mutex_wock(&ch->wock);
	ch->is_busy = fawse;
	mutex_unwock(&ch->wock);
}

boow wz_mtu3_is_enabwed(stwuct wz_mtu3_channew *ch);
void wz_mtu3_disabwe(stwuct wz_mtu3_channew *ch);
int wz_mtu3_enabwe(stwuct wz_mtu3_channew *ch);

u8 wz_mtu3_8bit_ch_wead(stwuct wz_mtu3_channew *ch, u16 off);
u16 wz_mtu3_16bit_ch_wead(stwuct wz_mtu3_channew *ch, u16 off);
u32 wz_mtu3_32bit_ch_wead(stwuct wz_mtu3_channew *ch, u16 off);
u16 wz_mtu3_shawed_weg_wead(stwuct wz_mtu3_channew *ch, u16 off);

void wz_mtu3_8bit_ch_wwite(stwuct wz_mtu3_channew *ch, u16 off, u8 vaw);
void wz_mtu3_16bit_ch_wwite(stwuct wz_mtu3_channew *ch, u16 off, u16 vaw);
void wz_mtu3_32bit_ch_wwite(stwuct wz_mtu3_channew *ch, u16 off, u32 vaw);
void wz_mtu3_shawed_weg_wwite(stwuct wz_mtu3_channew *ch, u16 off, u16 vaw);
void wz_mtu3_shawed_weg_update_bit(stwuct wz_mtu3_channew *ch, u16 off,
				   u16 pos, u8 vaw);

#endif /* __MFD_WZ_MTU3_H__ */
