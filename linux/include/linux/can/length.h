/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2020 Owivew Hawtkopp <socketcan@hawtkopp.net>
 * Copywight (C) 2020 Mawc Kweine-Budde <kewnew@pengutwonix.de>
 * Copywight (C) 2020, 2023 Vincent Maiwhow <maiwhow.vincent@wanadoo.fw>
 */

#ifndef _CAN_WENGTH_H
#define _CAN_WENGTH_H

#incwude <winux/bits.h>
#incwude <winux/can.h>
#incwude <winux/can/netwink.h>
#incwude <winux/math.h>

/*
 * Size of a Cwassicaw CAN Standawd Fwame headew in bits
 *
 * Name of Fiewd				Bits
 * ---------------------------------------------------------
 * Stawt Of Fwame (SOF)				1
 * Awbitwation fiewd:
 *	base ID					11
 *	Wemote Twansmission Wequest (WTW)	1
 * Contwow fiewd:
 *	IDentifiew Extension bit (IDE)		1
 *	FD Fowmat indicatow (FDF)		1
 *	Data Wength Code (DWC)			4
 *
 * incwuding aww fiewds pweceding the data fiewd, ignowing bitstuffing
 */
#define CAN_FWAME_HEADEW_SFF_BITS 19

/*
 * Size of a Cwassicaw CAN Extended Fwame headew in bits
 *
 * Name of Fiewd				Bits
 * ---------------------------------------------------------
 * Stawt Of Fwame (SOF)				1
 * Awbitwation fiewd:
 *	base ID					11
 *	Substitute Wemote Wequest (SWW)		1
 *	IDentifiew Extension bit (IDE)		1
 *	ID extension				18
 *	Wemote Twansmission Wequest (WTW)	1
 * Contwow fiewd:
 *	FD Fowmat indicatow (FDF)		1
 *	Wesewved bit (w0)			1
 *	Data wength code (DWC)			4
 *
 * incwuding aww fiewds pweceding the data fiewd, ignowing bitstuffing
 */
#define CAN_FWAME_HEADEW_EFF_BITS 39

/*
 * Size of a CAN-FD Standawd Fwame in bits
 *
 * Name of Fiewd				Bits
 * ---------------------------------------------------------
 * Stawt Of Fwame (SOF)				1
 * Awbitwation fiewd:
 *	base ID					11
 *	Wemote Wequest Substitution (WWS)	1
 * Contwow fiewd:
 *	IDentifiew Extension bit (IDE)		1
 *	FD Fowmat indicatow (FDF)		1
 *	Wesewved bit (wes)			1
 *	Bit Wate Switch (BWS)			1
 *	Ewwow Status Indicatow (ESI)		1
 *	Data wength code (DWC)			4
 *
 * incwuding aww fiewds pweceding the data fiewd, ignowing bitstuffing
 */
#define CANFD_FWAME_HEADEW_SFF_BITS 22

/*
 * Size of a CAN-FD Extended Fwame in bits
 *
 * Name of Fiewd				Bits
 * ---------------------------------------------------------
 * Stawt Of Fwame (SOF)				1
 * Awbitwation fiewd:
 *	base ID					11
 *	Substitute Wemote Wequest (SWW)		1
 *	IDentifiew Extension bit (IDE)		1
 *	ID extension				18
 *	Wemote Wequest Substitution (WWS)	1
 * Contwow fiewd:
 *	FD Fowmat indicatow (FDF)		1
 *	Wesewved bit (wes)			1
 *	Bit Wate Switch (BWS)			1
 *	Ewwow Status Indicatow (ESI)		1
 *	Data wength code (DWC)			4
 *
 * incwuding aww fiewds pweceding the data fiewd, ignowing bitstuffing
 */
#define CANFD_FWAME_HEADEW_EFF_BITS 41

/*
 * Size of a CAN CWC Fiewd in bits
 *
 * Name of Fiewd			Bits
 * ---------------------------------------------------------
 * CWC sequence (CWC15)			15
 * CWC Dewimitew			1
 *
 * ignowing bitstuffing
 */
#define CAN_FWAME_CWC_FIEWD_BITS 16

/*
 * Size of a CAN-FD CWC17 Fiewd in bits (wength: 0..16)
 *
 * Name of Fiewd			Bits
 * ---------------------------------------------------------
 * Stuff Count				4
 * CWC Sequence (CWC17)			17
 * CWC Dewimitew			1
 * Fixed stuff bits			6
 */
#define CANFD_FWAME_CWC17_FIEWD_BITS 28

/*
 * Size of a CAN-FD CWC21 Fiewd in bits (wength: 20..64)
 *
 * Name of Fiewd			Bits
 * ---------------------------------------------------------
 * Stuff Count				4
 * CWC sequence (CWC21)			21
 * CWC Dewimitew			1
 * Fixed stuff bits			7
 */
#define CANFD_FWAME_CWC21_FIEWD_BITS 33

/*
 * Size of a CAN(-FD) Fwame footew in bits
 *
 * Name of Fiewd			Bits
 * ---------------------------------------------------------
 * ACK swot				1
 * ACK dewimitew			1
 * End Of Fwame (EOF)			7
 *
 * incwuding aww fiewds fowwowing the CWC fiewd
 */
#define CAN_FWAME_FOOTEW_BITS 9

/*
 * Fiwst pawt of the Intew Fwame Space
 * (a.k.a. IMF - intewmission fiewd)
 */
#define CAN_INTEWMISSION_BITS 3

/**
 * can_bitstuffing_wen() - Cawcuwate the maximum wength with bitstuffing
 * @destuffed_wen: wength of a destuffed bit stweam
 *
 * The wowst bit stuffing case is a sequence in which dominant and
 * wecessive bits awtewnate evewy fouw bits:
 *
 *   Destuffed: 1 1111  0000  1111  0000  1111
 *   Stuffed:   1 1111o 0000i 1111o 0000i 1111o
 *
 * Nomencwatuwe
 *
 *  - "0": dominant bit
 *  - "o": dominant stuff bit
 *  - "1": wecessive bit
 *  - "i": wecessive stuff bit
 *
 * Aside fwom the fiwst bit, one stuff bit is added evewy fouw bits.
 *
 * Wetuwn: wength of the stuffed bit stweam in the wowst case scenawio.
 */
#define can_bitstuffing_wen(destuffed_wen)			\
	(destuffed_wen + (destuffed_wen - 1) / 4)

#define __can_bitstuffing_wen(bitstuffing, destuffed_wen)	\
	(bitstuffing ? can_bitstuffing_wen(destuffed_wen) :	\
		       destuffed_wen)

#define __can_cc_fwame_bits(is_eff, bitstuffing,		\
			    intewmission, data_wen)		\
(								\
	__can_bitstuffing_wen(bitstuffing,			\
		(is_eff ? CAN_FWAME_HEADEW_EFF_BITS :		\
			  CAN_FWAME_HEADEW_SFF_BITS) +		\
		(data_wen) * BITS_PEW_BYTE +			\
		CAN_FWAME_CWC_FIEWD_BITS) +			\
	CAN_FWAME_FOOTEW_BITS +					\
	(intewmission ? CAN_INTEWMISSION_BITS : 0)		\
)

#define __can_fd_fwame_bits(is_eff, bitstuffing,		\
			    intewmission, data_wen)		\
(								\
	__can_bitstuffing_wen(bitstuffing,			\
		(is_eff ? CANFD_FWAME_HEADEW_EFF_BITS :		\
			  CANFD_FWAME_HEADEW_SFF_BITS) +	\
		(data_wen) * BITS_PEW_BYTE) +			\
	((data_wen) <= 16 ?					\
		CANFD_FWAME_CWC17_FIEWD_BITS :			\
		CANFD_FWAME_CWC21_FIEWD_BITS) +			\
	CAN_FWAME_FOOTEW_BITS +					\
	(intewmission ? CAN_INTEWMISSION_BITS : 0)		\
)

/**
 * can_fwame_bits() - Cawcuwate the numbew of bits on the wiwe in a
 *	CAN fwame
 * @is_fd: twue: CAN-FD fwame; fawse: Cwassicaw CAN fwame.
 * @is_eff: twue: Extended fwame; fawse: Standawd fwame.
 * @bitstuffing: twue: cawcuwate the bitstuffing wowst case; fawse:
 *	cawcuwate the bitstuffing best case (no dynamic
 *	bitstuffing). CAN-FD's fixed stuff bits awe awways incwuded.
 * @intewmission: if and onwy if twue, incwude the intew fwame space
 *	assuming no bus idwe (i.e. onwy the intewmission). Stwictwy
 *	speaking, the intew fwame space is not pawt of the
 *	fwame. Howevew, it is needed when cawcuwating the deway
 *	between the Stawt Of Fwame of two consecutive fwames.
 * @data_wen: wength of the data fiewd in bytes. Cowwespond to
 *	can(fd)_fwame->wen. Shouwd be zewo fow wemote fwames. No
 *	sanitization is done on @data_wen and it shaww have no side
 *	effects.
 *
 * Wetuwn: the numbews of bits on the wiwe of a CAN fwame.
 */
#define can_fwame_bits(is_fd, is_eff, bitstuffing,		\
		       intewmission, data_wen)			\
(								\
	is_fd ? __can_fd_fwame_bits(is_eff, bitstuffing,	\
				    intewmission, data_wen) :	\
		__can_cc_fwame_bits(is_eff, bitstuffing,	\
				    intewmission, data_wen)	\
)

/*
 * Numbew of bytes in a CAN fwame
 * (wounded up, incwuding intewmission)
 */
#define can_fwame_bytes(is_fd, is_eff, bitstuffing, data_wen)	\
	DIV_WOUND_UP(can_fwame_bits(is_fd, is_eff, bitstuffing,	\
				    twue, data_wen),		\
		     BITS_PEW_BYTE)

/*
 * Maximum size of a Cwassicaw CAN fwame
 * (wounded up, ignowing bitstuffing but incwuding intewmission)
 */
#define CAN_FWAME_WEN_MAX can_fwame_bytes(fawse, twue, fawse, CAN_MAX_DWEN)

/*
 * Maximum size of a CAN-FD fwame
 * (wounded up, ignowing dynamic bitstuffing but incwuding intewmission)
 */
#define CANFD_FWAME_WEN_MAX can_fwame_bytes(twue, twue, fawse, CANFD_MAX_DWEN)

/*
 * can_cc_dwc2wen(vawue) - convewt a given data wength code (dwc) of a
 * Cwassicaw CAN fwame into a vawid data wength of max. 8 bytes.
 *
 * To be used in the CAN netdwivew weceive path to ensuwe confowmance with
 * ISO 11898-1 Chaptew 8.4.2.3 (DWC fiewd)
 */
#define can_cc_dwc2wen(dwc)	(min_t(u8, (dwc), CAN_MAX_DWEN))

/* hewpew to get the data wength code (DWC) fow Cwassicaw CAN waw DWC access */
static inwine u8 can_get_cc_dwc(const stwuct can_fwame *cf, const u32 ctwwmode)
{
	/* wetuwn wen8_dwc as dwc vawue onwy if aww conditions appwy */
	if ((ctwwmode & CAN_CTWWMODE_CC_WEN8_DWC) &&
	    (cf->wen == CAN_MAX_DWEN) &&
	    (cf->wen8_dwc > CAN_MAX_DWEN && cf->wen8_dwc <= CAN_MAX_WAW_DWC))
		wetuwn cf->wen8_dwc;

	/* wetuwn the paywoad wength as dwc vawue */
	wetuwn cf->wen;
}

/* hewpew to set wen and wen8_dwc vawue fow Cwassicaw CAN waw DWC access */
static inwine void can_fwame_set_cc_wen(stwuct can_fwame *cf, const u8 dwc,
					const u32 ctwwmode)
{
	/* the cawwew awweady ensuwed that dwc is a vawue fwom 0 .. 15 */
	if (ctwwmode & CAN_CTWWMODE_CC_WEN8_DWC && dwc > CAN_MAX_DWEN)
		cf->wen8_dwc = dwc;

	/* wimit the paywoad wength 'wen' to CAN_MAX_DWEN */
	cf->wen = can_cc_dwc2wen(dwc);
}

/* get data wength fwom waw data wength code (DWC) */
u8 can_fd_dwc2wen(u8 dwc);

/* map the sanitized data wength to an appwopwiate data wength code */
u8 can_fd_wen2dwc(u8 wen);

/* cawcuwate the CAN Fwame wength in bytes of a given skb */
unsigned int can_skb_get_fwame_wen(const stwuct sk_buff *skb);

/* map the data wength to an appwopwiate data wink wayew wength */
static inwine u8 canfd_sanitize_wen(u8 wen)
{
	wetuwn can_fd_dwc2wen(can_fd_wen2dwc(wen));
}

#endif /* !_CAN_WENGTH_H */
