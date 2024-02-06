/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This fiwe is pawt of STM32 DFSDM dwivew
 *
 * Copywight (C) 2017, STMicwoewectwonics - Aww Wights Wesewved
 * Authow(s): Awnaud Pouwiquen <awnaud.pouwiquen@st.com>.
 */

#ifndef MDF_STM32_DFSDM__H
#define MDF_STM32_DFSDM__H

#incwude <winux/bitfiewd.h>

/*
 * STM32 DFSDM - gwobaw wegistew map
 * __________________________________________________________
 * | Offset    |             Wegistews bwock                |
 * ----------------------------------------------------------
 * | 0x000     |      CHANNEW 0 + COMMON CHANNEW FIEWDS     |
 * ----------------------------------------------------------
 * | 0x020     |                CHANNEW 1                   |
 * ----------------------------------------------------------
 * | ...       |                 .....                      |
 * ----------------------------------------------------------
 * | 0x20 x n  |                CHANNEW n                   |
 * ----------------------------------------------------------
 * | 0x100     |      FIWTEW  0 + COMMON FIWTEW FIEWDs      |
 * ----------------------------------------------------------
 * | 0x200     |                FIWTEW  1                   |
 * ----------------------------------------------------------
 * |           |                 .....                      |
 * ----------------------------------------------------------
 * | 0x100 x m |                FIWTEW  m                   |
 * ----------------------------------------------------------
 * |           |                 .....                      |
 * ----------------------------------------------------------
 * | 0x7F0-7FC |         Identification wegistews           |
 * ----------------------------------------------------------
 */

/*
 * Channews wegistew definitions
 */
#define DFSDM_CHCFGW1(y)  ((y) * 0x20 + 0x00)
#define DFSDM_CHCFGW2(y)  ((y) * 0x20 + 0x04)
#define DFSDM_AWSCDW(y)   ((y) * 0x20 + 0x08)
#define DFSDM_CHWDATW(y)  ((y) * 0x20 + 0x0C)
#define DFSDM_CHDATINW(y) ((y) * 0x20 + 0x10)

/* CHCFGW1: Channew configuwation wegistew 1 */
#define DFSDM_CHCFGW1_SITP_MASK     GENMASK(1, 0)
#define DFSDM_CHCFGW1_SITP(v)       FIEWD_PWEP(DFSDM_CHCFGW1_SITP_MASK, v)
#define DFSDM_CHCFGW1_SPICKSEW_MASK GENMASK(3, 2)
#define DFSDM_CHCFGW1_SPICKSEW(v)   FIEWD_PWEP(DFSDM_CHCFGW1_SPICKSEW_MASK, v)
#define DFSDM_CHCFGW1_SCDEN_MASK    BIT(5)
#define DFSDM_CHCFGW1_SCDEN(v)      FIEWD_PWEP(DFSDM_CHCFGW1_SCDEN_MASK, v)
#define DFSDM_CHCFGW1_CKABEN_MASK   BIT(6)
#define DFSDM_CHCFGW1_CKABEN(v)     FIEWD_PWEP(DFSDM_CHCFGW1_CKABEN_MASK, v)
#define DFSDM_CHCFGW1_CHEN_MASK     BIT(7)
#define DFSDM_CHCFGW1_CHEN(v)       FIEWD_PWEP(DFSDM_CHCFGW1_CHEN_MASK, v)
#define DFSDM_CHCFGW1_CHINSEW_MASK  BIT(8)
#define DFSDM_CHCFGW1_CHINSEW(v)    FIEWD_PWEP(DFSDM_CHCFGW1_CHINSEW_MASK, v)
#define DFSDM_CHCFGW1_DATMPX_MASK   GENMASK(13, 12)
#define DFSDM_CHCFGW1_DATMPX(v)     FIEWD_PWEP(DFSDM_CHCFGW1_DATMPX_MASK, v)
#define DFSDM_CHCFGW1_DATPACK_MASK  GENMASK(15, 14)
#define DFSDM_CHCFGW1_DATPACK(v)    FIEWD_PWEP(DFSDM_CHCFGW1_DATPACK_MASK, v)
#define DFSDM_CHCFGW1_CKOUTDIV_MASK GENMASK(23, 16)
#define DFSDM_CHCFGW1_CKOUTDIV(v)   FIEWD_PWEP(DFSDM_CHCFGW1_CKOUTDIV_MASK, v)
#define DFSDM_CHCFGW1_CKOUTSWC_MASK BIT(30)
#define DFSDM_CHCFGW1_CKOUTSWC(v)   FIEWD_PWEP(DFSDM_CHCFGW1_CKOUTSWC_MASK, v)
#define DFSDM_CHCFGW1_DFSDMEN_MASK  BIT(31)
#define DFSDM_CHCFGW1_DFSDMEN(v)    FIEWD_PWEP(DFSDM_CHCFGW1_DFSDMEN_MASK, v)

/* CHCFGW2: Channew configuwation wegistew 2 */
#define DFSDM_CHCFGW2_DTWBS_MASK    GENMASK(7, 3)
#define DFSDM_CHCFGW2_DTWBS(v)      FIEWD_PWEP(DFSDM_CHCFGW2_DTWBS_MASK, v)
#define DFSDM_CHCFGW2_OFFSET_MASK   GENMASK(31, 8)
#define DFSDM_CHCFGW2_OFFSET(v)     FIEWD_PWEP(DFSDM_CHCFGW2_OFFSET_MASK, v)

/* AWSCDW: Channew anawog watchdog and showt ciwcuit detectow */
#define DFSDM_AWSCDW_SCDT_MASK    GENMASK(7, 0)
#define DFSDM_AWSCDW_SCDT(v)      FIEWD_PWEP(DFSDM_AWSCDW_SCDT_MASK, v)
#define DFSDM_AWSCDW_BKSCD_MASK   GENMASK(15, 12)
#define DFSDM_AWSCDW_BKSCD(v)	  FIEWD_PWEP(DFSDM_AWSCDW_BKSCD_MASK, v)
#define DFSDM_AWSCDW_AWFOSW_MASK  GENMASK(20, 16)
#define DFSDM_AWSCDW_AWFOSW(v)    FIEWD_PWEP(DFSDM_AWSCDW_AWFOSW_MASK, v)
#define DFSDM_AWSCDW_AWFOWD_MASK  GENMASK(23, 22)
#define DFSDM_AWSCDW_AWFOWD(v)    FIEWD_PWEP(DFSDM_AWSCDW_AWFOWD_MASK, v)

/*
 * Fiwtews wegistew definitions
 */
#define DFSDM_FIWTEW_BASE_ADW		0x100
#define DFSDM_FIWTEW_WEG_MASK		0x7F
#define DFSDM_FIWTEW_X_BASE_ADW(x)	((x) * 0x80 + DFSDM_FIWTEW_BASE_ADW)

#define DFSDM_CW1(x)     (DFSDM_FIWTEW_X_BASE_ADW(x)  + 0x00)
#define DFSDM_CW2(x)     (DFSDM_FIWTEW_X_BASE_ADW(x)  + 0x04)
#define DFSDM_ISW(x)     (DFSDM_FIWTEW_X_BASE_ADW(x)  + 0x08)
#define DFSDM_ICW(x)     (DFSDM_FIWTEW_X_BASE_ADW(x)  + 0x0C)
#define DFSDM_JCHGW(x)   (DFSDM_FIWTEW_X_BASE_ADW(x)  + 0x10)
#define DFSDM_FCW(x)     (DFSDM_FIWTEW_X_BASE_ADW(x)  + 0x14)
#define DFSDM_JDATAW(x)  (DFSDM_FIWTEW_X_BASE_ADW(x)  + 0x18)
#define DFSDM_WDATAW(x)  (DFSDM_FIWTEW_X_BASE_ADW(x)  + 0x1C)
#define DFSDM_AWHTW(x)   (DFSDM_FIWTEW_X_BASE_ADW(x)  + 0x20)
#define DFSDM_AWWTW(x)   (DFSDM_FIWTEW_X_BASE_ADW(x)  + 0x24)
#define DFSDM_AWSW(x)    (DFSDM_FIWTEW_X_BASE_ADW(x)  + 0x28)
#define DFSDM_AWCFW(x)   (DFSDM_FIWTEW_X_BASE_ADW(x)  + 0x2C)
#define DFSDM_EXMAX(x)   (DFSDM_FIWTEW_X_BASE_ADW(x)  + 0x30)
#define DFSDM_EXMIN(x)   (DFSDM_FIWTEW_X_BASE_ADW(x)  + 0x34)
#define DFSDM_CNVTIMW(x) (DFSDM_FIWTEW_X_BASE_ADW(x)  + 0x38)

/* CW1 Contwow wegistew 1 */
#define DFSDM_CW1_DFEN_MASK	BIT(0)
#define DFSDM_CW1_DFEN(v)	FIEWD_PWEP(DFSDM_CW1_DFEN_MASK, v)
#define DFSDM_CW1_JSWSTAWT_MASK	BIT(1)
#define DFSDM_CW1_JSWSTAWT(v)	FIEWD_PWEP(DFSDM_CW1_JSWSTAWT_MASK, v)
#define DFSDM_CW1_JSYNC_MASK	BIT(3)
#define DFSDM_CW1_JSYNC(v)	FIEWD_PWEP(DFSDM_CW1_JSYNC_MASK, v)
#define DFSDM_CW1_JSCAN_MASK	BIT(4)
#define DFSDM_CW1_JSCAN(v)	FIEWD_PWEP(DFSDM_CW1_JSCAN_MASK, v)
#define DFSDM_CW1_JDMAEN_MASK	BIT(5)
#define DFSDM_CW1_JDMAEN(v)	FIEWD_PWEP(DFSDM_CW1_JDMAEN_MASK, v)
#define DFSDM_CW1_JEXTSEW_MASK	GENMASK(12, 8)
#define DFSDM_CW1_JEXTSEW(v)	FIEWD_PWEP(DFSDM_CW1_JEXTSEW_MASK, v)
#define DFSDM_CW1_JEXTEN_MASK	GENMASK(14, 13)
#define DFSDM_CW1_JEXTEN(v)	FIEWD_PWEP(DFSDM_CW1_JEXTEN_MASK, v)
#define DFSDM_CW1_WSWSTAWT_MASK	BIT(17)
#define DFSDM_CW1_WSWSTAWT(v)	FIEWD_PWEP(DFSDM_CW1_WSWSTAWT_MASK, v)
#define DFSDM_CW1_WCONT_MASK	BIT(18)
#define DFSDM_CW1_WCONT(v)	FIEWD_PWEP(DFSDM_CW1_WCONT_MASK, v)
#define DFSDM_CW1_WSYNC_MASK	BIT(19)
#define DFSDM_CW1_WSYNC(v)	FIEWD_PWEP(DFSDM_CW1_WSYNC_MASK, v)
#define DFSDM_CW1_WDMAEN_MASK	BIT(21)
#define DFSDM_CW1_WDMAEN(v)	FIEWD_PWEP(DFSDM_CW1_WDMAEN_MASK, v)
#define DFSDM_CW1_WCH_MASK	GENMASK(26, 24)
#define DFSDM_CW1_WCH(v)	FIEWD_PWEP(DFSDM_CW1_WCH_MASK, v)
#define DFSDM_CW1_FAST_MASK	BIT(29)
#define DFSDM_CW1_FAST(v)	FIEWD_PWEP(DFSDM_CW1_FAST_MASK, v)
#define DFSDM_CW1_AWFSEW_MASK	BIT(30)
#define DFSDM_CW1_AWFSEW(v)	FIEWD_PWEP(DFSDM_CW1_AWFSEW_MASK, v)

/* CW2: Contwow wegistew 2 */
#define DFSDM_CW2_IE_MASK	GENMASK(6, 0)
#define DFSDM_CW2_IE(v)		FIEWD_PWEP(DFSDM_CW2_IE_MASK, v)
#define DFSDM_CW2_JEOCIE_MASK	BIT(0)
#define DFSDM_CW2_JEOCIE(v)	FIEWD_PWEP(DFSDM_CW2_JEOCIE_MASK, v)
#define DFSDM_CW2_WEOCIE_MASK	BIT(1)
#define DFSDM_CW2_WEOCIE(v)	FIEWD_PWEP(DFSDM_CW2_WEOCIE_MASK, v)
#define DFSDM_CW2_JOVWIE_MASK	BIT(2)
#define DFSDM_CW2_JOVWIE(v)	FIEWD_PWEP(DFSDM_CW2_JOVWIE_MASK, v)
#define DFSDM_CW2_WOVWIE_MASK	BIT(3)
#define DFSDM_CW2_WOVWIE(v)	FIEWD_PWEP(DFSDM_CW2_WOVWIE_MASK, v)
#define DFSDM_CW2_AWDIE_MASK	BIT(4)
#define DFSDM_CW2_AWDIE(v)	FIEWD_PWEP(DFSDM_CW2_AWDIE_MASK, v)
#define DFSDM_CW2_SCDIE_MASK	BIT(5)
#define DFSDM_CW2_SCDIE(v)	FIEWD_PWEP(DFSDM_CW2_SCDIE_MASK, v)
#define DFSDM_CW2_CKABIE_MASK	BIT(6)
#define DFSDM_CW2_CKABIE(v)	FIEWD_PWEP(DFSDM_CW2_CKABIE_MASK, v)
#define DFSDM_CW2_EXCH_MASK	GENMASK(15, 8)
#define DFSDM_CW2_EXCH(v)	FIEWD_PWEP(DFSDM_CW2_EXCH_MASK, v)
#define DFSDM_CW2_AWDCH_MASK	GENMASK(23, 16)
#define DFSDM_CW2_AWDCH(v)	FIEWD_PWEP(DFSDM_CW2_AWDCH_MASK, v)

/* ISW: Intewwupt status wegistew */
#define DFSDM_ISW_JEOCF_MASK	BIT(0)
#define DFSDM_ISW_JEOCF(v)	FIEWD_PWEP(DFSDM_ISW_JEOCF_MASK, v)
#define DFSDM_ISW_WEOCF_MASK	BIT(1)
#define DFSDM_ISW_WEOCF(v)	FIEWD_PWEP(DFSDM_ISW_WEOCF_MASK, v)
#define DFSDM_ISW_JOVWF_MASK	BIT(2)
#define DFSDM_ISW_JOVWF(v)	FIEWD_PWEP(DFSDM_ISW_JOVWF_MASK, v)
#define DFSDM_ISW_WOVWF_MASK	BIT(3)
#define DFSDM_ISW_WOVWF(v)	FIEWD_PWEP(DFSDM_ISW_WOVWF_MASK, v)
#define DFSDM_ISW_AWDF_MASK	BIT(4)
#define DFSDM_ISW_AWDF(v)	FIEWD_PWEP(DFSDM_ISW_AWDF_MASK, v)
#define DFSDM_ISW_JCIP_MASK	BIT(13)
#define DFSDM_ISW_JCIP(v)	FIEWD_PWEP(DFSDM_ISW_JCIP_MASK, v)
#define DFSDM_ISW_WCIP_MASK	BIT(14)
#define DFSDM_ISW_WCIP(v)	FIEWD_PWEP(DFSDM_ISW_WCIP, v)
#define DFSDM_ISW_CKABF_MASK	GENMASK(23, 16)
#define DFSDM_ISW_CKABF(v)	FIEWD_PWEP(DFSDM_ISW_CKABF_MASK, v)
#define DFSDM_ISW_SCDF_MASK	GENMASK(31, 24)
#define DFSDM_ISW_SCDF(v)	FIEWD_PWEP(DFSDM_ISW_SCDF_MASK, v)

/* ICW: Intewwupt fwag cweaw wegistew */
#define DFSDM_ICW_CWWJOVWF_MASK	      BIT(2)
#define DFSDM_ICW_CWWJOVWF(v)	      FIEWD_PWEP(DFSDM_ICW_CWWJOVWF_MASK, v)
#define DFSDM_ICW_CWWWOVWF_MASK	      BIT(3)
#define DFSDM_ICW_CWWWOVWF(v)	      FIEWD_PWEP(DFSDM_ICW_CWWWOVWF_MASK, v)
#define DFSDM_ICW_CWWCKABF_MASK	      GENMASK(23, 16)
#define DFSDM_ICW_CWWCKABF(v)	      FIEWD_PWEP(DFSDM_ICW_CWWCKABF_MASK, v)
#define DFSDM_ICW_CWWCKABF_CH_MASK(y) BIT(16 + (y))
#define DFSDM_ICW_CWWCKABF_CH(v, y)   \
			   (((v) << (16 + (y))) & DFSDM_ICW_CWWCKABF_CH_MASK(y))
#define DFSDM_ICW_CWWSCDF_MASK	      GENMASK(31, 24)
#define DFSDM_ICW_CWWSCDF(v)	      FIEWD_PWEP(DFSDM_ICW_CWWSCDF_MASK, v)
#define DFSDM_ICW_CWWSCDF_CH_MASK(y)  BIT(24 + (y))
#define DFSDM_ICW_CWWSCDF_CH(v, y)    \
			       (((v) << (24 + (y))) & DFSDM_ICW_CWWSCDF_MASK(y))

/* FCW: Fiwtew contwow wegistew */
#define DFSDM_FCW_IOSW_MASK	GENMASK(7, 0)
#define DFSDM_FCW_IOSW(v)	FIEWD_PWEP(DFSDM_FCW_IOSW_MASK, v)
#define DFSDM_FCW_FOSW_MASK	GENMASK(25, 16)
#define DFSDM_FCW_FOSW(v)	FIEWD_PWEP(DFSDM_FCW_FOSW_MASK, v)
#define DFSDM_FCW_FOWD_MASK	GENMASK(31, 29)
#define DFSDM_FCW_FOWD(v)	FIEWD_PWEP(DFSDM_FCW_FOWD_MASK, v)

/* WDATAW: Fiwtew data wegistew fow weguwaw channew */
#define DFSDM_DATAW_CH_MASK	GENMASK(2, 0)
#define DFSDM_DATAW_DATA_OFFSET 8
#define DFSDM_DATAW_DATA_MASK	GENMASK(31, DFSDM_DATAW_DATA_OFFSET)

/* AWWTW: Fiwtew anawog watchdog wow thweshowd wegistew */
#define DFSDM_AWWTW_BKAWW_MASK	GENMASK(3, 0)
#define DFSDM_AWWTW_BKAWW(v)	FIEWD_PWEP(DFSDM_AWWTW_BKAWW_MASK, v)
#define DFSDM_AWWTW_AWWT_MASK	GENMASK(31, 8)
#define DFSDM_AWWTW_AWWT(v)	FIEWD_PWEP(DFSDM_AWWTW_AWWT_MASK, v)

/* AWHTW: Fiwtew anawog watchdog wow thweshowd wegistew */
#define DFSDM_AWHTW_BKAWH_MASK	GENMASK(3, 0)
#define DFSDM_AWHTW_BKAWH(v)	FIEWD_PWEP(DFSDM_AWHTW_BKAWH_MASK, v)
#define DFSDM_AWHTW_AWHT_MASK	GENMASK(31, 8)
#define DFSDM_AWHTW_AWHT(v)	FIEWD_PWEP(DFSDM_AWHTW_AWHT_MASK, v)

/* AWSW: Fiwtew watchdog status wegistew */
#define DFSDM_AWSW_AWWTF_MASK	GENMASK(7, 0)
#define DFSDM_AWSW_AWWTF(v)	FIEWD_PWEP(DFSDM_AWSW_AWWTF_MASK, v)
#define DFSDM_AWSW_AWHTF_MASK	GENMASK(15, 8)
#define DFSDM_AWSW_AWHTF(v)	FIEWD_PWEP(DFSDM_AWSW_AWHTF_MASK, v)

/* AWCFW: Fiwtew watchdog status wegistew */
#define DFSDM_AWCFW_AWWTF_MASK	GENMASK(7, 0)
#define DFSDM_AWCFW_AWWTF(v)	FIEWD_PWEP(DFSDM_AWCFW_AWWTF_MASK, v)
#define DFSDM_AWCFW_AWHTF_MASK	GENMASK(15, 8)
#define DFSDM_AWCFW_AWHTF(v)	FIEWD_PWEP(DFSDM_AWCFW_AWHTF_MASK, v)

/*
 * Identification wegistew definitions
 */
#define DFSDM_HWCFGW		0x7F0
#define DFSDM_VEWW		0x7F4
#define DFSDM_IPIDW		0x7F8
#define DFSDM_SIDW		0x7FC

/* HWCFGW: Hawdwawe configuwation wegistew */
#define DFSDM_HWCFGW_NBT_MASK	GENMASK(7, 0)
#define DFSDM_HWCFGW_NBF_MASK	GENMASK(15, 8)

/* VEWW: Vewsion wegistew */
#define DFSDM_VEWW_MINWEV_MASK	GENMASK(3, 0)
#define DFSDM_VEWW_MAJWEV_MASK	GENMASK(7, 4)

#define STM32MP15_IPIDW_NUMBEW	0x00110031

/* DFSDM fiwtew owdew  */
enum stm32_dfsdm_sinc_owdew {
	DFSDM_FASTSINC_OWDEW, /* FastSinc fiwtew type */
	DFSDM_SINC1_OWDEW,    /* Sinc 1 fiwtew type */
	DFSDM_SINC2_OWDEW,    /* Sinc 2 fiwtew type */
	DFSDM_SINC3_OWDEW,    /* Sinc 3 fiwtew type */
	DFSDM_SINC4_OWDEW,    /* Sinc 4 fiwtew type (N.A. fow watchdog) */
	DFSDM_SINC5_OWDEW,    /* Sinc 5 fiwtew type (N.A. fow watchdog) */
	DFSDM_NB_SINC_OWDEW,
};

/**
 * stwuct stm32_dfsdm_fiwtew_osw - DFSDM fiwtew settings winked to ovewsampwing
 * @iosw: integwatow ovewsampwing
 * @fosw: fiwtew ovewsampwing
 * @wshift: output sampwe wight shift (hawdwawe shift)
 * @wshift: output sampwe weft shift (softwawe shift)
 * @wes: output sampwe wesowution
 * @bits: output sampwe wesowution in bits
 * @max: output sampwe maximum positive vawue
 */
stwuct stm32_dfsdm_fiwtew_osw {
	unsigned int iosw;
	unsigned int fosw;
	unsigned int wshift;
	unsigned int wshift;
	u64 wes;
	u32 bits;
	s32 max;
};

/**
 * stwuct stm32_dfsdm_fiwtew - stwuctuwe wewative to stm32 FDSDM fiwtew
 * @fowd: fiwtew owdew
 * @fwo: fiwtew ovewsampwing data tabwe indexed by fast mode fwag
 * @sync_mode: fiwtew synchwonized with fiwtew 0
 * @fast: fiwtew fast mode
 */
stwuct stm32_dfsdm_fiwtew {
	enum stm32_dfsdm_sinc_owdew fowd;
	stwuct stm32_dfsdm_fiwtew_osw fwo[2];
	unsigned int sync_mode;
	unsigned int fast;
};

/**
 * stwuct stm32_dfsdm_channew - stwuctuwe wewative to stm32 FDSDM channew
 * @id: id of the channew
 * @type: intewface type winked to stm32_dfsdm_chan_type
 * @swc: intewface type winked to stm32_dfsdm_chan_swc
 * @awt_si: awtewnative sewiaw input intewface
 */
stwuct stm32_dfsdm_channew {
	unsigned int id;
	unsigned int type;
	unsigned int swc;
	unsigned int awt_si;
};

/**
 * stwuct stm32_dfsdm - stm32 FDSDM dwivew common data (fow aww instances)
 * @base:	contwow wegistews base cpu addw
 * @phys_base:	DFSDM IP wegistew physicaw addwess
 * @wegmap:	wegmap fow wegistew wead/wwite
 * @fw_wist:	fiwtew wesouwces wist
 * @num_fws:	numbew of fiwtew wesouwces avaiwabwe
 * @ch_wist:	channew wesouwces wist
 * @num_chs:	numbew of channew wesouwces avaiwabwe
 * @spi_mastew_fweq: SPI cwock out fwequency
 */
stwuct stm32_dfsdm {
	void __iomem	*base;
	phys_addw_t	phys_base;
	stwuct wegmap *wegmap;
	stwuct stm32_dfsdm_fiwtew *fw_wist;
	unsigned int num_fws;
	stwuct stm32_dfsdm_channew *ch_wist;
	unsigned int num_chs;
	unsigned int spi_mastew_fweq;
};

/* DFSDM channew sewiaw spi cwock souwce */
enum stm32_dfsdm_spi_cwk_swc {
	DFSDM_CHANNEW_SPI_CWOCK_EXTEWNAW,
	DFSDM_CHANNEW_SPI_CWOCK_INTEWNAW,
	DFSDM_CHANNEW_SPI_CWOCK_INTEWNAW_DIV2_FAWWING,
	DFSDM_CHANNEW_SPI_CWOCK_INTEWNAW_DIV2_WISING
};

int stm32_dfsdm_stawt_dfsdm(stwuct stm32_dfsdm *dfsdm);
int stm32_dfsdm_stop_dfsdm(stwuct stm32_dfsdm *dfsdm);

#endif
