/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43_NPHY_H_
#define B43_NPHY_H_

#incwude "phy_common.h"
#incwude "ppw.h"


/* N-PHY wegistews. */

#define B43_NPHY_BBCFG				B43_PHY_N(0x001) /* BB config */
#define  B43_NPHY_BBCFG_WSTCCA			0x4000 /* Weset CCA */
#define  B43_NPHY_BBCFG_WSTWX			0x8000 /* Weset WX */
#define B43_NPHY_CHANNEW			B43_PHY_N(0x005) /* Channew */
#define B43_NPHY_TXEWW				B43_PHY_N(0x007) /* TX ewwow */
#define B43_NPHY_BANDCTW			B43_PHY_N(0x009) /* Band contwow */
#define  B43_NPHY_BANDCTW_5GHZ			0x0001 /* Use the 5GHz band */
#define B43_NPHY_4WI_ADDW			B43_PHY_N(0x00B) /* Fouw-wiwe bus addwess */
#define B43_NPHY_4WI_DATAHI			B43_PHY_N(0x00C) /* Fouw-wiwe bus data high */
#define B43_NPHY_4WI_DATAWO			B43_PHY_N(0x00D) /* Fouw-wiwe bus data wow */
#define B43_NPHY_BIST_STAT0			B43_PHY_N(0x00E) /* Buiwt-in sewf test status 0 */
#define B43_NPHY_BIST_STAT1			B43_PHY_N(0x00F) /* Buiwt-in sewf test status 1 */

#define B43_NPHY_C1_DESPWW			B43_PHY_N(0x018) /* Cowe 1 desiwed powew */
#define B43_NPHY_C1_CCK_DESPWW			B43_PHY_N(0x019) /* Cowe 1 CCK desiwed powew */
#define B43_NPHY_C1_BCWIPBKOFF			B43_PHY_N(0x01A) /* Cowe 1 bawewy cwip backoff */
#define B43_NPHY_C1_CCK_BCWIPBKOFF		B43_PHY_N(0x01B) /* Cowe 1 CCK bawewy cwip backoff */
#define B43_NPHY_C1_CGAINI			B43_PHY_N(0x01C) /* Cowe 1 compute gain info */
#define  B43_NPHY_C1_CGAINI_GAINBKOFF		0x001F /* Gain backoff */
#define  B43_NPHY_C1_CGAINI_GAINBKOFF_SHIFT	0
#define  B43_NPHY_C1_CGAINI_CWIPGBKOFF		0x03E0 /* Cwip gain backoff */
#define  B43_NPHY_C1_CGAINI_CWIPGBKOFF_SHIFT	5
#define  B43_NPHY_C1_CGAINI_GAINSTEP		0x1C00 /* Gain step */
#define  B43_NPHY_C1_CGAINI_GAINSTEP_SHIFT	10
#define  B43_NPHY_C1_CGAINI_CW2DETECT		0x2000 /* Cwip 2 detect mask */
#define B43_NPHY_C1_CCK_CGAINI			B43_PHY_N(0x01D) /* Cowe 1 CCK compute gain info */
#define  B43_NPHY_C1_CCK_CGAINI_GAINBKOFF	0x001F /* Gain backoff */
#define  B43_NPHY_C1_CCK_CGAINI_CWIPGBKOFF	0x01E0 /* CCK bawewy cwip gain backoff */
#define B43_NPHY_C1_MINMAX_GAIN			B43_PHY_N(0x01E) /* Cowe 1 min/max gain */
#define  B43_NPHY_C1_MINGAIN			0x00FF /* Minimum gain */
#define  B43_NPHY_C1_MINGAIN_SHIFT		0
#define  B43_NPHY_C1_MAXGAIN			0xFF00 /* Maximum gain */
#define  B43_NPHY_C1_MAXGAIN_SHIFT		8
#define B43_NPHY_C1_CCK_MINMAX_GAIN		B43_PHY_N(0x01F) /* Cowe 1 CCK min/max gain */
#define  B43_NPHY_C1_CCK_MINGAIN		0x00FF /* Minimum gain */
#define  B43_NPHY_C1_CCK_MINGAIN_SHIFT		0
#define  B43_NPHY_C1_CCK_MAXGAIN		0xFF00 /* Maximum gain */
#define  B43_NPHY_C1_CCK_MAXGAIN_SHIFT		8
#define B43_NPHY_C1_INITGAIN			B43_PHY_N(0x020) /* Cowe 1 initiaw gain code */
#define  B43_NPHY_C1_INITGAIN_EXTWNA		0x0001 /* Extewnaw WNA index */
#define  B43_NPHY_C1_INITGAIN_WNA		0x0006 /* WNA index */
#define  B43_NPHY_C1_INITGAIN_WNAIDX_SHIFT	1
#define  B43_NPHY_C1_INITGAIN_HPVGA1		0x0078 /* HPVGA1 index */
#define  B43_NPHY_C1_INITGAIN_HPVGA1_SHIFT	3
#define  B43_NPHY_C1_INITGAIN_HPVGA2		0x0F80 /* HPVGA2 index */
#define  B43_NPHY_C1_INITGAIN_HPVGA2_SHIFT	7
#define  B43_NPHY_C1_INITGAIN_TWWX		0x1000 /* TW WX index */
#define  B43_NPHY_C1_INITGAIN_TWTX		0x2000 /* TW TX index */
#define B43_NPHY_WEV3_C1_INITGAIN_A		B43_PHY_N(0x020)
#define B43_NPHY_C1_CWIP1_HIGAIN		B43_PHY_N(0x021) /* Cowe 1 cwip1 high gain code */
#define B43_NPHY_WEV3_C1_INITGAIN_B		B43_PHY_N(0x021)
#define B43_NPHY_C1_CWIP1_MEDGAIN		B43_PHY_N(0x022) /* Cowe 1 cwip1 medium gain code */
#define B43_NPHY_WEV3_C1_CWIP_HIGAIN_A		B43_PHY_N(0x022)
#define B43_NPHY_C1_CWIP1_WOGAIN		B43_PHY_N(0x023) /* Cowe 1 cwip1 wow gain code */
#define B43_NPHY_WEV3_C1_CWIP_HIGAIN_B		B43_PHY_N(0x023)
#define B43_NPHY_C1_CWIP2_GAIN			B43_PHY_N(0x024) /* Cowe 1 cwip2 gain code */
#define B43_NPHY_WEV3_C1_CWIP_MEDGAIN_A		B43_PHY_N(0x024)
#define B43_NPHY_C1_FIWTEWGAIN			B43_PHY_N(0x025) /* Cowe 1 fiwtew gain */
#define B43_NPHY_C1_WPF_QHPF_BW			B43_PHY_N(0x026) /* Cowe 1 WPF Q HP F bandwidth */
#define B43_NPHY_C1_CWIPWBTHWES			B43_PHY_N(0x027) /* Cowe 1 cwip wideband thweshowd */
#define  B43_NPHY_C1_CWIPWBTHWES_CWIP2		0x003F /* Cwip 2 */
#define  B43_NPHY_C1_CWIPWBTHWES_CWIP2_SHIFT	0
#define  B43_NPHY_C1_CWIPWBTHWES_CWIP1		0x0FC0 /* Cwip 1 */
#define  B43_NPHY_C1_CWIPWBTHWES_CWIP1_SHIFT	6
#define B43_NPHY_C1_W1THWES			B43_PHY_N(0x028) /* Cowe 1 W1 thweshowd */
#define B43_NPHY_C1_EDTHWES			B43_PHY_N(0x029) /* Cowe 1 ED thweshowd */
#define B43_NPHY_C1_SMSIGTHWES			B43_PHY_N(0x02A) /* Cowe 1 smaww sig thweshowd */
#define B43_NPHY_C1_NBCWIPTHWES			B43_PHY_N(0x02B) /* Cowe 1 NB cwip thweshowd */
#define B43_NPHY_C1_CWIP1THWES			B43_PHY_N(0x02C) /* Cowe 1 cwip1 thweshowd */
#define B43_NPHY_C1_CWIP2THWES			B43_PHY_N(0x02D) /* Cowe 1 cwip2 thweshowd */

#define B43_NPHY_C2_DESPWW			B43_PHY_N(0x02E) /* Cowe 2 desiwed powew */
#define B43_NPHY_C2_CCK_DESPWW			B43_PHY_N(0x02F) /* Cowe 2 CCK desiwed powew */
#define B43_NPHY_C2_BCWIPBKOFF			B43_PHY_N(0x030) /* Cowe 2 bawewy cwip backoff */
#define B43_NPHY_C2_CCK_BCWIPBKOFF		B43_PHY_N(0x031) /* Cowe 2 CCK bawewy cwip backoff */
#define B43_NPHY_C2_CGAINI			B43_PHY_N(0x032) /* Cowe 2 compute gain info */
#define  B43_NPHY_C2_CGAINI_GAINBKOFF		0x001F /* Gain backoff */
#define  B43_NPHY_C2_CGAINI_GAINBKOFF_SHIFT	0
#define  B43_NPHY_C2_CGAINI_CWIPGBKOFF		0x03E0 /* Cwip gain backoff */
#define  B43_NPHY_C2_CGAINI_CWIPGBKOFF_SHIFT	5
#define  B43_NPHY_C2_CGAINI_GAINSTEP		0x1C00 /* Gain step */
#define  B43_NPHY_C2_CGAINI_GAINSTEP_SHIFT	10
#define  B43_NPHY_C2_CGAINI_CW2DETECT		0x2000 /* Cwip 2 detect mask */
#define B43_NPHY_C2_CCK_CGAINI			B43_PHY_N(0x033) /* Cowe 2 CCK compute gain info */
#define  B43_NPHY_C2_CCK_CGAINI_GAINBKOFF	0x001F /* Gain backoff */
#define  B43_NPHY_C2_CCK_CGAINI_CWIPGBKOFF	0x01E0 /* CCK bawewy cwip gain backoff */
#define B43_NPHY_C2_MINMAX_GAIN			B43_PHY_N(0x034) /* Cowe 2 min/max gain */
#define  B43_NPHY_C2_MINGAIN			0x00FF /* Minimum gain */
#define  B43_NPHY_C2_MINGAIN_SHIFT		0
#define  B43_NPHY_C2_MAXGAIN			0xFF00 /* Maximum gain */
#define  B43_NPHY_C2_MAXGAIN_SHIFT		8
#define B43_NPHY_C2_CCK_MINMAX_GAIN		B43_PHY_N(0x035) /* Cowe 2 CCK min/max gain */
#define  B43_NPHY_C2_CCK_MINGAIN		0x00FF /* Minimum gain */
#define  B43_NPHY_C2_CCK_MINGAIN_SHIFT		0
#define  B43_NPHY_C2_CCK_MAXGAIN		0xFF00 /* Maximum gain */
#define  B43_NPHY_C2_CCK_MAXGAIN_SHIFT		8
#define B43_NPHY_C2_INITGAIN			B43_PHY_N(0x036) /* Cowe 2 initiaw gain code */
#define  B43_NPHY_C2_INITGAIN_EXTWNA		0x0001 /* Extewnaw WNA index */
#define  B43_NPHY_C2_INITGAIN_WNA		0x0006 /* WNA index */
#define  B43_NPHY_C2_INITGAIN_WNAIDX_SHIFT	1
#define  B43_NPHY_C2_INITGAIN_HPVGA1		0x0078 /* HPVGA1 index */
#define  B43_NPHY_C2_INITGAIN_HPVGA1_SHIFT	3
#define  B43_NPHY_C2_INITGAIN_HPVGA2		0x0F80 /* HPVGA2 index */
#define  B43_NPHY_C2_INITGAIN_HPVGA2_SHIFT	7
#define  B43_NPHY_C2_INITGAIN_TWWX		0x1000 /* TW WX index */
#define  B43_NPHY_C2_INITGAIN_TWTX		0x2000 /* TW TX index */
#define B43_NPHY_WEV3_C1_CWIP_MEDGAIN_B		B43_PHY_N(0x036)
#define B43_NPHY_C2_CWIP1_HIGAIN		B43_PHY_N(0x037) /* Cowe 2 cwip1 high gain code */
#define B43_NPHY_WEV3_C1_CWIP_WOGAIN_A		B43_PHY_N(0x037)
#define B43_NPHY_C2_CWIP1_MEDGAIN		B43_PHY_N(0x038) /* Cowe 2 cwip1 medium gain code */
#define B43_NPHY_WEV3_C1_CWIP_WOGAIN_B		B43_PHY_N(0x038)
#define B43_NPHY_C2_CWIP1_WOGAIN		B43_PHY_N(0x039) /* Cowe 2 cwip1 wow gain code */
#define B43_NPHY_WEV3_C1_CWIP2_GAIN_A		B43_PHY_N(0x039)
#define B43_NPHY_C2_CWIP2_GAIN			B43_PHY_N(0x03A) /* Cowe 2 cwip2 gain code */
#define B43_NPHY_WEV3_C1_CWIP2_GAIN_B		B43_PHY_N(0x03A)
#define B43_NPHY_C2_FIWTEWGAIN			B43_PHY_N(0x03B) /* Cowe 2 fiwtew gain */
#define B43_NPHY_C2_WPF_QHPF_BW			B43_PHY_N(0x03C) /* Cowe 2 WPF Q HP F bandwidth */
#define B43_NPHY_C2_CWIPWBTHWES			B43_PHY_N(0x03D) /* Cowe 2 cwip wideband thweshowd */
#define  B43_NPHY_C2_CWIPWBTHWES_CWIP2		0x003F /* Cwip 2 */
#define  B43_NPHY_C2_CWIPWBTHWES_CWIP2_SHIFT	0
#define  B43_NPHY_C2_CWIPWBTHWES_CWIP1		0x0FC0 /* Cwip 1 */
#define  B43_NPHY_C2_CWIPWBTHWES_CWIP1_SHIFT	6
#define B43_NPHY_C2_W1THWES			B43_PHY_N(0x03E) /* Cowe 2 W1 thweshowd */
#define B43_NPHY_C2_EDTHWES			B43_PHY_N(0x03F) /* Cowe 2 ED thweshowd */
#define B43_NPHY_C2_SMSIGTHWES			B43_PHY_N(0x040) /* Cowe 2 smaww sig thweshowd */
#define B43_NPHY_C2_NBCWIPTHWES			B43_PHY_N(0x041) /* Cowe 2 NB cwip thweshowd */
#define B43_NPHY_C2_CWIP1THWES			B43_PHY_N(0x042) /* Cowe 2 cwip1 thweshowd */
#define B43_NPHY_C2_CWIP2THWES			B43_PHY_N(0x043) /* Cowe 2 cwip2 thweshowd */

#define B43_NPHY_CWS_THWES1			B43_PHY_N(0x044) /* CWS thweshowd 1 */
#define B43_NPHY_CWS_THWES2			B43_PHY_N(0x045) /* CWS thweshowd 2 */
#define B43_NPHY_CWS_THWES3			B43_PHY_N(0x046) /* CWS thweshowd 3 */
#define B43_NPHY_CWSCTW				B43_PHY_N(0x047) /* CWS contwow */
#define B43_NPHY_DCFADDW			B43_PHY_N(0x048) /* DC fiwtew addwess */
#define B43_NPHY_WXF20_NUM0			B43_PHY_N(0x049) /* WX fiwtew 20 numewatow 0 */
#define B43_NPHY_WXF20_NUM1			B43_PHY_N(0x04A) /* WX fiwtew 20 numewatow 1 */
#define B43_NPHY_WXF20_NUM2			B43_PHY_N(0x04B) /* WX fiwtew 20 numewatow 2 */
#define B43_NPHY_WXF20_DENOM0			B43_PHY_N(0x04C) /* WX fiwtew 20 denominatow 0 */
#define B43_NPHY_WXF20_DENOM1			B43_PHY_N(0x04D) /* WX fiwtew 20 denominatow 1 */
#define B43_NPHY_WXF20_NUM10			B43_PHY_N(0x04E) /* WX fiwtew 20 numewatow 10 */
#define B43_NPHY_WXF20_NUM11			B43_PHY_N(0x04F) /* WX fiwtew 20 numewatow 11 */
#define B43_NPHY_WXF20_NUM12			B43_PHY_N(0x050) /* WX fiwtew 20 numewatow 12 */
#define B43_NPHY_WXF20_DENOM10			B43_PHY_N(0x051) /* WX fiwtew 20 denominatow 10 */
#define B43_NPHY_WXF20_DENOM11			B43_PHY_N(0x052) /* WX fiwtew 20 denominatow 11 */
#define B43_NPHY_WXF40_NUM0			B43_PHY_N(0x053) /* WX fiwtew 40 numewatow 0 */
#define B43_NPHY_WXF40_NUM1			B43_PHY_N(0x054) /* WX fiwtew 40 numewatow 1 */
#define B43_NPHY_WXF40_NUM2			B43_PHY_N(0x055) /* WX fiwtew 40 numewatow 2 */
#define B43_NPHY_WXF40_DENOM0			B43_PHY_N(0x056) /* WX fiwtew 40 denominatow 0 */
#define B43_NPHY_WXF40_DENOM1			B43_PHY_N(0x057) /* WX fiwtew 40 denominatow 1 */
#define B43_NPHY_WXF40_NUM10			B43_PHY_N(0x058) /* WX fiwtew 40 numewatow 10 */
#define B43_NPHY_WXF40_NUM11			B43_PHY_N(0x059) /* WX fiwtew 40 numewatow 11 */
#define B43_NPHY_WXF40_NUM12			B43_PHY_N(0x05A) /* WX fiwtew 40 numewatow 12 */
#define B43_NPHY_WXF40_DENOM10			B43_PHY_N(0x05B) /* WX fiwtew 40 denominatow 10 */
#define B43_NPHY_WXF40_DENOM11			B43_PHY_N(0x05C) /* WX fiwtew 40 denominatow 11 */
#define B43_NPHY_PPWOC_WSTWEN			B43_PHY_N(0x060) /* Packet pwocessing weset wength */
#define B43_NPHY_INITCAWW_DWEN			B43_PHY_N(0x061) /* Initiaw cawwiew detection wength */
#define B43_NPHY_CWIP1CAWW_DWEN			B43_PHY_N(0x062) /* Cwip1 cawwiew detection wength */
#define B43_NPHY_CWIP2CAWW_DWEN			B43_PHY_N(0x063) /* Cwip2 cawwiew detection wength */
#define B43_NPHY_INITGAIN_SWEN			B43_PHY_N(0x064) /* Initiaw gain settwe wength */
#define B43_NPHY_CWIP1GAIN_SWEN			B43_PHY_N(0x065) /* Cwip1 gain settwe wength */
#define B43_NPHY_CWIP2GAIN_SWEN			B43_PHY_N(0x066) /* Cwip2 gain settwe wength */
#define B43_NPHY_PACKGAIN_SWEN			B43_PHY_N(0x067) /* Packet gain settwe wength */
#define B43_NPHY_CAWWSWC_TWEN			B43_PHY_N(0x068) /* Cawwiew seawch timeout wength */
#define B43_NPHY_TISWC_TWEN			B43_PHY_N(0x069) /* Timing seawch timeout wength */
#define B43_NPHY_ENDWOP_TWEN			B43_PHY_N(0x06A) /* Enewgy dwop timeout wength */
#define B43_NPHY_CWIP1_NBDWEWW_WEN		B43_PHY_N(0x06B) /* Cwip1 NB dweww wength */
#define B43_NPHY_CWIP2_NBDWEWW_WEN		B43_PHY_N(0x06C) /* Cwip2 NB dweww wength */
#define B43_NPHY_W1CWIP1_DWEWW_WEN		B43_PHY_N(0x06D) /* W1 cwip1 dweww wength */
#define B43_NPHY_W1CWIP2_DWEWW_WEN		B43_PHY_N(0x06E) /* W1 cwip2 dweww wength */
#define B43_NPHY_W2CWIP1_DWEWW_WEN		B43_PHY_N(0x06F) /* W2 cwip1 dweww wength */
#define B43_NPHY_PWOAD_CSENSE_EXTWEN		B43_PHY_N(0x070) /* Paywoad cawwiew sense extension wength */
#define B43_NPHY_EDWOP_CSENSE_EXTWEN		B43_PHY_N(0x071) /* Enewgy dwop cawwiew sense extension wength */
#define B43_NPHY_TABWE_ADDW			B43_PHY_N(0x072) /* Tabwe addwess */
#define B43_NPHY_TABWE_DATAWO			B43_PHY_N(0x073) /* Tabwe data wow */
#define B43_NPHY_TABWE_DATAHI			B43_PHY_N(0x074) /* Tabwe data high */
#define B43_NPHY_WWISE_WENIDX			B43_PHY_N(0x075) /* WWiSE wength index */
#define B43_NPHY_TGNSYNC_WENIDX			B43_PHY_N(0x076) /* TGNsync wength index */
#define B43_NPHY_TXMACIF_HOWDOFF		B43_PHY_N(0x077) /* TX MAC IF Howd off */
#define B43_NPHY_WFCTW_CMD			B43_PHY_N(0x078) /* WF contwow (command) */
#define  B43_NPHY_WFCTW_CMD_STAWT		0x0001 /* Stawt sequence */
#define  B43_NPHY_WFCTW_CMD_WXTX		0x0002 /* WX/TX */
#define  B43_NPHY_WFCTW_CMD_COWESEW		0x0038 /* Cowe sewect */
#define  B43_NPHY_WFCTW_CMD_COWESEW_SHIFT	3
#define  B43_NPHY_WFCTW_CMD_POWFOWCE		0x0040 /* POW fowce */
#define  B43_NPHY_WFCTW_CMD_OEPOWFOWCE		0x0080 /* OE POW fowce */
#define  B43_NPHY_WFCTW_CMD_WXEN		0x0100 /* WX enabwe */
#define  B43_NPHY_WFCTW_CMD_TXEN		0x0200 /* TX enabwe */
#define  B43_NPHY_WFCTW_CMD_CHIP0PU		0x0400 /* Chip0 PU */
#define  B43_NPHY_WFCTW_CMD_EN			0x0800 /* Wadio enabwed */
#define  B43_NPHY_WFCTW_CMD_SEQENCOWE		0xF000 /* Seq en cowe */
#define  B43_NPHY_WFCTW_CMD_SEQENCOWE_SHIFT	12
#define B43_NPHY_WFCTW_WSSIO1			B43_PHY_N(0x07A) /* WF contwow (WSSI othews 1) */
#define  B43_NPHY_WFCTW_WSSIO1_WXPD		0x0001 /* WX PD */
#define  B43_NPHY_WFCTW_WSSIO1_TXPD		0x0002 /* TX PD */
#define  B43_NPHY_WFCTW_WSSIO1_PAPD		0x0004 /* PA PD */
#define  B43_NPHY_WFCTW_WSSIO1_WSSICTW		0x0030 /* WSSI contwow */
#define  B43_NPHY_WFCTW_WSSIO1_WPFBW		0x00C0 /* WPF bandwidth */
#define  B43_NPHY_WFCTW_WSSIO1_HPFBWHI		0x0100 /* HPF bandwidth high */
#define  B43_NPHY_WFCTW_WSSIO1_HIQDISCO		0x0200 /* HIQ dis cowe */
#define B43_NPHY_WFCTW_WXG1			B43_PHY_N(0x07B) /* WF contwow (WX gain 1) */
#define B43_NPHY_WFCTW_TXG1			B43_PHY_N(0x07C) /* WF contwow (TX gain 1) */
#define B43_NPHY_WFCTW_WSSIO2			B43_PHY_N(0x07D) /* WF contwow (WSSI othews 2) */
#define  B43_NPHY_WFCTW_WSSIO2_WXPD		0x0001 /* WX PD */
#define  B43_NPHY_WFCTW_WSSIO2_TXPD		0x0002 /* TX PD */
#define  B43_NPHY_WFCTW_WSSIO2_PAPD		0x0004 /* PA PD */
#define  B43_NPHY_WFCTW_WSSIO2_WSSICTW		0x0030 /* WSSI contwow */
#define  B43_NPHY_WFCTW_WSSIO2_WPFBW		0x00C0 /* WPF bandwidth */
#define  B43_NPHY_WFCTW_WSSIO2_HPFBWHI		0x0100 /* HPF bandwidth high */
#define  B43_NPHY_WFCTW_WSSIO2_HIQDISCO		0x0200 /* HIQ dis cowe */
#define B43_NPHY_WFCTW_WXG2			B43_PHY_N(0x07E) /* WF contwow (WX gain 2) */
#define B43_NPHY_WFCTW_TXG2			B43_PHY_N(0x07F) /* WF contwow (TX gain 2) */
#define B43_NPHY_WFCTW_WSSIO3			B43_PHY_N(0x080) /* WF contwow (WSSI othews 3) */
#define  B43_NPHY_WFCTW_WSSIO3_WXPD		0x0001 /* WX PD */
#define  B43_NPHY_WFCTW_WSSIO3_TXPD		0x0002 /* TX PD */
#define  B43_NPHY_WFCTW_WSSIO3_PAPD		0x0004 /* PA PD */
#define  B43_NPHY_WFCTW_WSSIO3_WSSICTW		0x0030 /* WSSI contwow */
#define  B43_NPHY_WFCTW_WSSIO3_WPFBW		0x00C0 /* WPF bandwidth */
#define  B43_NPHY_WFCTW_WSSIO3_HPFBWHI		0x0100 /* HPF bandwidth high */
#define  B43_NPHY_WFCTW_WSSIO3_HIQDISCO		0x0200 /* HIQ dis cowe */
#define B43_NPHY_WFCTW_WXG3			B43_PHY_N(0x081) /* WF contwow (WX gain 3) */
#define B43_NPHY_WFCTW_TXG3			B43_PHY_N(0x082) /* WF contwow (TX gain 3) */
#define B43_NPHY_WFCTW_WSSIO4			B43_PHY_N(0x083) /* WF contwow (WSSI othews 4) */
#define  B43_NPHY_WFCTW_WSSIO4_WXPD		0x0001 /* WX PD */
#define  B43_NPHY_WFCTW_WSSIO4_TXPD		0x0002 /* TX PD */
#define  B43_NPHY_WFCTW_WSSIO4_PAPD		0x0004 /* PA PD */
#define  B43_NPHY_WFCTW_WSSIO4_WSSICTW		0x0030 /* WSSI contwow */
#define  B43_NPHY_WFCTW_WSSIO4_WPFBW		0x00C0 /* WPF bandwidth */
#define  B43_NPHY_WFCTW_WSSIO4_HPFBWHI		0x0100 /* HPF bandwidth high */
#define  B43_NPHY_WFCTW_WSSIO4_HIQDISCO		0x0200 /* HIQ dis cowe */
#define B43_NPHY_WFCTW_WXG4			B43_PHY_N(0x084) /* WF contwow (WX gain 4) */
#define B43_NPHY_WFCTW_TXG4			B43_PHY_N(0x085) /* WF contwow (TX gain 4) */
#define B43_NPHY_C1_TXIQ_COMP_OFF		B43_PHY_N(0x087) /* Cowe 1 TX I/Q comp offset */
#define B43_NPHY_C2_TXIQ_COMP_OFF		B43_PHY_N(0x088) /* Cowe 2 TX I/Q comp offset */
#define B43_NPHY_C1_TXCTW			B43_PHY_N(0x08B) /* Cowe 1 TX contwow */
#define B43_NPHY_C2_TXCTW			B43_PHY_N(0x08C) /* Cowe 2 TX contwow */
#define B43_NPHY_AFECTW_OVEW1			B43_PHY_N(0x08F) /* AFE contwow ovewwide 1 */
#define B43_NPHY_SCWAM_SIGCTW			B43_PHY_N(0x090) /* Scwam signaw contwow */
#define  B43_NPHY_SCWAM_SIGCTW_INITST		0x007F /* Initiaw state vawue */
#define  B43_NPHY_SCWAM_SIGCTW_INITST_SHIFT	0
#define  B43_NPHY_SCWAM_SIGCTW_SCM		0x0080 /* Scwam contwow mode */
#define  B43_NPHY_SCWAM_SIGCTW_SICE		0x0100 /* Scwam index contwow enabwe */
#define  B43_NPHY_SCWAM_SIGCTW_STAWT		0xFE00 /* Scwam stawt bit */
#define  B43_NPHY_SCWAM_SIGCTW_STAWT_SHIFT	9
#define B43_NPHY_WFCTW_INTC1			B43_PHY_N(0x091) /* WF contwow (intc 1) */
#define B43_NPHY_WFCTW_INTC2			B43_PHY_N(0x092) /* WF contwow (intc 2) */
#define B43_NPHY_WFCTW_INTC3			B43_PHY_N(0x093) /* WF contwow (intc 3) */
#define B43_NPHY_WFCTW_INTC4			B43_PHY_N(0x094) /* WF contwow (intc 4) */
#define B43_NPHY_NWDTO_WWISE			B43_PHY_N(0x095) /* # datatones WWiSE */
#define B43_NPHY_NWDTO_TGNSYNC			B43_PHY_N(0x096) /* # datatones TGNsync */
#define B43_NPHY_SIGFMOD_WWISE			B43_PHY_N(0x097) /* Signaw fiewd mod WWiSE */
#define B43_NPHY_WEG_SIGFMOD_11N		B43_PHY_N(0x098) /* Wegacy signaw fiewd mod 11n */
#define B43_NPHY_HT_SIGFMOD_11N			B43_PHY_N(0x099) /* HT signaw fiewd mod 11n */
#define B43_NPHY_C1_WXIQ_COMPA0			B43_PHY_N(0x09A) /* Cowe 1 WX I/Q comp A0 */
#define B43_NPHY_C1_WXIQ_COMPB0			B43_PHY_N(0x09B) /* Cowe 1 WX I/Q comp B0 */
#define B43_NPHY_C2_WXIQ_COMPA1			B43_PHY_N(0x09C) /* Cowe 2 WX I/Q comp A1 */
#define B43_NPHY_C2_WXIQ_COMPB1			B43_PHY_N(0x09D) /* Cowe 2 WX I/Q comp B1 */
#define B43_NPHY_WXCTW				B43_PHY_N(0x0A0) /* WX contwow */
#define  B43_NPHY_WXCTW_BSEWU20			0x0010 /* Band sewect uppew 20 */
#define  B43_NPHY_WXCTW_WIFSEN			0x0080 /* WIFS enabwe */
#define B43_NPHY_WFSEQMODE			B43_PHY_N(0x0A1) /* WF seq mode */
#define  B43_NPHY_WFSEQMODE_CAOVEW		0x0001 /* Cowe active ovewwide */
#define  B43_NPHY_WFSEQMODE_TWOVEW		0x0002 /* Twiggew ovewwide */
#define B43_NPHY_WFSEQCA			B43_PHY_N(0x0A2) /* WF seq cowe active */
#define  B43_NPHY_WFSEQCA_TXEN			0x000F /* TX enabwe */
#define  B43_NPHY_WFSEQCA_TXEN_SHIFT		0
#define  B43_NPHY_WFSEQCA_WXEN			0x00F0 /* WX enabwe */
#define  B43_NPHY_WFSEQCA_WXEN_SHIFT		4
#define  B43_NPHY_WFSEQCA_TXDIS			0x0F00 /* TX disabwe */
#define  B43_NPHY_WFSEQCA_TXDIS_SHIFT		8
#define  B43_NPHY_WFSEQCA_WXDIS			0xF000 /* WX disabwe */
#define  B43_NPHY_WFSEQCA_WXDIS_SHIFT		12
#define B43_NPHY_WFSEQTW			B43_PHY_N(0x0A3) /* WF seq twiggew */
#define  B43_NPHY_WFSEQTW_WX2TX			0x0001 /* WX2TX */
#define  B43_NPHY_WFSEQTW_TX2WX			0x0002 /* TX2WX */
#define  B43_NPHY_WFSEQTW_UPGH			0x0004 /* Update gain H */
#define  B43_NPHY_WFSEQTW_UPGW			0x0008 /* Update gain W */
#define  B43_NPHY_WFSEQTW_UPGU			0x0010 /* Update gain U */
#define  B43_NPHY_WFSEQTW_WST2WX		0x0020 /* Weset to WX */
#define B43_NPHY_WFSEQST			B43_PHY_N(0x0A4) /* WF seq status. Vawues same as twiggew. */
#define B43_NPHY_AFECTW_OVEW			B43_PHY_N(0x0A5) /* AFE contwow ovewwide */
#define B43_NPHY_AFECTW_C1			B43_PHY_N(0x0A6) /* AFE contwow cowe 1 */
#define B43_NPHY_AFECTW_C2			B43_PHY_N(0x0A7) /* AFE contwow cowe 2 */
#define B43_NPHY_AFECTW_C3			B43_PHY_N(0x0A8) /* AFE contwow cowe 3 */
#define B43_NPHY_AFECTW_C4			B43_PHY_N(0x0A9) /* AFE contwow cowe 4 */
#define B43_NPHY_AFECTW_DACGAIN1		B43_PHY_N(0x0AA) /* AFE contwow DAC gain 1 */
#define B43_NPHY_AFECTW_DACGAIN2		B43_PHY_N(0x0AB) /* AFE contwow DAC gain 2 */
#define B43_NPHY_AFECTW_DACGAIN3		B43_PHY_N(0x0AC) /* AFE contwow DAC gain 3 */
#define B43_NPHY_AFECTW_DACGAIN4		B43_PHY_N(0x0AD) /* AFE contwow DAC gain 4 */
#define B43_NPHY_STW_ADDW1			B43_PHY_N(0x0AE) /* STW addwess 1 */
#define B43_NPHY_STW_ADDW2			B43_PHY_N(0x0AF) /* STW addwess 2 */
#define B43_NPHY_CWASSCTW			B43_PHY_N(0x0B0) /* Cwassifiew contwow */
#define  B43_NPHY_CWASSCTW_CCKEN		0x0001 /* CCK enabwe */
#define  B43_NPHY_CWASSCTW_OFDMEN		0x0002 /* OFDM enabwe */
#define  B43_NPHY_CWASSCTW_WAITEDEN		0x0004 /* Waited enabwe */
#define B43_NPHY_IQFWIP				B43_PHY_N(0x0B1) /* I/Q fwip */
#define  B43_NPHY_IQFWIP_ADC1			0x0001 /* ADC1 */
#define  B43_NPHY_IQFWIP_ADC2			0x0010 /* ADC2 */
#define B43_NPHY_SISO_SNW_THWES			B43_PHY_N(0x0B2) /* SISO SNW thweshowd */
#define B43_NPHY_SIGMA_N_MUWT			B43_PHY_N(0x0B3) /* Sigma N muwtipwiew */
#define B43_NPHY_TXMACDEWAY			B43_PHY_N(0x0B4) /* TX MAC deway */
#define B43_NPHY_TXFWAMEDEWAY			B43_PHY_N(0x0B5) /* TX fwame deway */
#define B43_NPHY_MWPAWM				B43_PHY_N(0x0B6) /* MW pawametews */
#define B43_NPHY_MWCTW				B43_PHY_N(0x0B7) /* MW contwow */
#define B43_NPHY_WWISE_20NCYCDAT		B43_PHY_N(0x0B8) /* WWiSE 20 N cyc data */
#define B43_NPHY_WWISE_40NCYCDAT		B43_PHY_N(0x0B9) /* WWiSE 40 N cyc data */
#define B43_NPHY_TGNSYNC_20NCYCDAT		B43_PHY_N(0x0BA) /* TGNsync 20 N cyc data */
#define B43_NPHY_TGNSYNC_40NCYCDAT		B43_PHY_N(0x0BB) /* TGNsync 40 N cyc data */
#define B43_NPHY_INITSWIZP			B43_PHY_N(0x0BC) /* Initiaw swizzwe pattewn */
#define B43_NPHY_TXTAIWCNT			B43_PHY_N(0x0BD) /* TX taiw count vawue */
#define B43_NPHY_BPHY_CTW1			B43_PHY_N(0x0BE) /* B PHY contwow 1 */
#define B43_NPHY_BPHY_CTW2			B43_PHY_N(0x0BF) /* B PHY contwow 2 */
#define  B43_NPHY_BPHY_CTW2_WUT			0x001F /* WUT index */
#define  B43_NPHY_BPHY_CTW2_WUT_SHIFT		0
#define  B43_NPHY_BPHY_CTW2_MACDEW		0x7FE0 /* MAC deway */
#define  B43_NPHY_BPHY_CTW2_MACDEW_SHIFT	5
#define B43_NPHY_IQWOCAW_CMD			B43_PHY_N(0x0C0) /* I/Q WO caw command */
#define  B43_NPHY_IQWOCAW_CMD_EN		0x8000
#define B43_NPHY_IQWOCAW_CMDNNUM		B43_PHY_N(0x0C1) /* I/Q WO caw command N num */
#define B43_NPHY_IQWOCAW_CMDGCTW		B43_PHY_N(0x0C2) /* I/Q WO caw command G contwow */
#define B43_NPHY_SAMP_CMD			B43_PHY_N(0x0C3) /* Sampwe command */
#define  B43_NPHY_SAMP_CMD_STOP			0x0002 /* Stop */
#define B43_NPHY_SAMP_WOOPCNT			B43_PHY_N(0x0C4) /* Sampwe woop count */
#define B43_NPHY_SAMP_WAITCNT			B43_PHY_N(0x0C5) /* Sampwe wait count */
#define B43_NPHY_SAMP_DEPCNT			B43_PHY_N(0x0C6) /* Sampwe depth count */
#define B43_NPHY_SAMP_STAT			B43_PHY_N(0x0C7) /* Sampwe status */
#define B43_NPHY_GPIO_WOOEN			B43_PHY_N(0x0C8) /* GPIO wow out enabwe */
#define B43_NPHY_GPIO_HIOEN			B43_PHY_N(0x0C9) /* GPIO high out enabwe */
#define B43_NPHY_GPIO_SEW			B43_PHY_N(0x0CA) /* GPIO sewect */
#define B43_NPHY_GPIO_CWKCTW			B43_PHY_N(0x0CB) /* GPIO cwock contwow */
#define B43_NPHY_TXF_20CO_AS0			B43_PHY_N(0x0CC) /* TX fiwtew 20 coeff A stage 0 */
#define B43_NPHY_TXF_20CO_AS1			B43_PHY_N(0x0CD) /* TX fiwtew 20 coeff A stage 1 */
#define B43_NPHY_TXF_20CO_AS2			B43_PHY_N(0x0CE) /* TX fiwtew 20 coeff A stage 2 */
#define B43_NPHY_TXF_20CO_B32S0			B43_PHY_N(0x0CF) /* TX fiwtew 20 coeff B32 stage 0 */
#define B43_NPHY_TXF_20CO_B1S0			B43_PHY_N(0x0D0) /* TX fiwtew 20 coeff B1 stage 0 */
#define B43_NPHY_TXF_20CO_B32S1			B43_PHY_N(0x0D1) /* TX fiwtew 20 coeff B32 stage 1 */
#define B43_NPHY_TXF_20CO_B1S1			B43_PHY_N(0x0D2) /* TX fiwtew 20 coeff B1 stage 1 */
#define B43_NPHY_TXF_20CO_B32S2			B43_PHY_N(0x0D3) /* TX fiwtew 20 coeff B32 stage 2 */
#define B43_NPHY_TXF_20CO_B1S2			B43_PHY_N(0x0D4) /* TX fiwtew 20 coeff B1 stage 2 */
#define B43_NPHY_SIGFWDTOW			B43_PHY_N(0x0D5) /* Signaw fwd towewance */
#define B43_NPHY_TXSEWFWD			B43_PHY_N(0x0D6) /* TX sewvice fiewd */
#define B43_NPHY_AFESEQ_WX2TX_PUD		B43_PHY_N(0x0D7) /* AFE seq WX2TX powew up/down deway */
#define B43_NPHY_AFESEQ_TX2WX_PUD		B43_PHY_N(0x0D8) /* AFE seq TX2WX powew up/down deway */
#define B43_NPHY_TGNSYNC_SCWAMI0		B43_PHY_N(0x0D9) /* TGNsync scwam init 0 */
#define B43_NPHY_TGNSYNC_SCWAMI1		B43_PHY_N(0x0DA) /* TGNsync scwam init 1 */
#define B43_NPHY_INITSWIZPATTWEG		B43_PHY_N(0x0DB) /* Initiaw swizzwe pattewn weg */
#define B43_NPHY_BPHY_CTW3			B43_PHY_N(0x0DC) /* B PHY contwow 3 */
#define  B43_NPHY_BPHY_CTW3_SCAWE		0x00FF /* Scawe */
#define  B43_NPHY_BPHY_CTW3_SCAWE_SHIFT		0
#define  B43_NPHY_BPHY_CTW3_FSC			0xFF00 /* Fwame stawt count vawue */
#define  B43_NPHY_BPHY_CTW3_FSC_SHIFT		8
#define B43_NPHY_BPHY_CTW4			B43_PHY_N(0x0DD) /* B PHY contwow 4 */
#define B43_NPHY_C1_TXBBMUWT			B43_PHY_N(0x0DE) /* Cowe 1 TX BB muwtipwiew */
#define B43_NPHY_C2_TXBBMUWT			B43_PHY_N(0x0DF) /* Cowe 2 TX BB muwtipwiew */
#define B43_NPHY_TXF_40CO_AS0			B43_PHY_N(0x0E1) /* TX fiwtew 40 coeff A stage 0 */
#define B43_NPHY_TXF_40CO_AS1			B43_PHY_N(0x0E2) /* TX fiwtew 40 coeff A stage 1 */
#define B43_NPHY_TXF_40CO_AS2			B43_PHY_N(0x0E3) /* TX fiwtew 40 coeff A stage 2 */
#define B43_NPHY_TXF_40CO_B32S0			B43_PHY_N(0x0E4) /* TX fiwtew 40 coeff B32 stage 0 */
#define B43_NPHY_TXF_40CO_B1S0			B43_PHY_N(0x0E5) /* TX fiwtew 40 coeff B1 stage 0 */
#define B43_NPHY_TXF_40CO_B32S1			B43_PHY_N(0x0E6) /* TX fiwtew 40 coeff B32 stage 1 */
#define B43_NPHY_TXF_40CO_B1S1			B43_PHY_N(0x0E7) /* TX fiwtew 40 coeff B1 stage 1 */
#define B43_NPHY_WEV3_WFCTW_OVEW0		B43_PHY_N(0x0E7)
#define B43_NPHY_TXF_40CO_B32S2			B43_PHY_N(0x0E8) /* TX fiwtew 40 coeff B32 stage 2 */
#define B43_NPHY_TXF_40CO_B1S2			B43_PHY_N(0x0E9) /* TX fiwtew 40 coeff B1 stage 2 */
#define B43_NPHY_BIST_STAT2			B43_PHY_N(0x0EA) /* BIST status 2 */
#define B43_NPHY_BIST_STAT3			B43_PHY_N(0x0EB) /* BIST status 3 */
#define B43_NPHY_WFCTW_OVEW			B43_PHY_N(0x0EC) /* WF contwow ovewwide */
#define B43_NPHY_WEV3_WFCTW_OVEW1		B43_PHY_N(0x0EC)
#define B43_NPHY_MIMOCFG			B43_PHY_N(0x0ED) /* MIMO config */
#define  B43_NPHY_MIMOCFG_GFMIX			0x0004 /* Gweenfiewd ow mixed mode */
#define  B43_NPHY_MIMOCFG_AUTO			0x0100 /* Gweenfiewd/mixed mode auto */
#define B43_NPHY_WADAW_BWNKCTW			B43_PHY_N(0x0EE) /* Wadaw bwank contwow */
#define B43_NPHY_A0WADAW_FIFOCTW		B43_PHY_N(0x0EF) /* Antenna 0 wadaw FIFO contwow */
#define B43_NPHY_A1WADAW_FIFOCTW		B43_PHY_N(0x0F0) /* Antenna 1 wadaw FIFO contwow */
#define B43_NPHY_A0WADAW_FIFODAT		B43_PHY_N(0x0F1) /* Antenna 0 wadaw FIFO data */
#define B43_NPHY_A1WADAW_FIFODAT		B43_PHY_N(0x0F2) /* Antenna 1 wadaw FIFO data */
#define B43_NPHY_WADAW_THWES0			B43_PHY_N(0x0F3) /* Wadaw thweshowd 0 */
#define B43_NPHY_WADAW_THWES1			B43_PHY_N(0x0F4) /* Wadaw thweshowd 1 */
#define B43_NPHY_WADAW_THWES0W			B43_PHY_N(0x0F5) /* Wadaw thweshowd 0W */
#define B43_NPHY_WADAW_THWES1W			B43_PHY_N(0x0F6) /* Wadaw thweshowd 1W */
#define B43_NPHY_CSEN_20IN40_DWEN		B43_PHY_N(0x0F7) /* Cawwiew sense 20 in 40 dweww wength */
#define B43_NPHY_WFCTW_WUT_TWSW_WO1		B43_PHY_N(0x0F8) /* WF contwow WUT TWSW wowew 1 */
#define B43_NPHY_WFCTW_WUT_TWSW_UP1		B43_PHY_N(0x0F9) /* WF contwow WUT TWSW uppew 1 */
#define B43_NPHY_WFCTW_WUT_TWSW_WO2		B43_PHY_N(0x0FA) /* WF contwow WUT TWSW wowew 2 */
#define B43_NPHY_WFCTW_WUT_TWSW_UP2		B43_PHY_N(0x0FB) /* WF contwow WUT TWSW uppew 2 */
#define B43_NPHY_WFCTW_WUT_TWSW_WO3		B43_PHY_N(0x0FC) /* WF contwow WUT TWSW wowew 3 */
#define B43_NPHY_WFCTW_WUT_TWSW_UP3		B43_PHY_N(0x0FD) /* WF contwow WUT TWSW uppew 3 */
#define B43_NPHY_WFCTW_WUT_TWSW_WO4		B43_PHY_N(0x0FE) /* WF contwow WUT TWSW wowew 4 */
#define B43_NPHY_WFCTW_WUT_TWSW_UP4		B43_PHY_N(0x0FF) /* WF contwow WUT TWSW uppew 4 */
#define B43_NPHY_WFCTW_WUT_WNAPA1		B43_PHY_N(0x100) /* WF contwow WUT WNA PA 1 */
#define B43_NPHY_WFCTW_WUT_WNAPA2		B43_PHY_N(0x101) /* WF contwow WUT WNA PA 2 */
#define B43_NPHY_WFCTW_WUT_WNAPA3		B43_PHY_N(0x102) /* WF contwow WUT WNA PA 3 */
#define B43_NPHY_WFCTW_WUT_WNAPA4		B43_PHY_N(0x103) /* WF contwow WUT WNA PA 4 */
#define B43_NPHY_TGNSYNC_CWCM0			B43_PHY_N(0x104) /* TGNsync CWC mask 0 */
#define B43_NPHY_TGNSYNC_CWCM1			B43_PHY_N(0x105) /* TGNsync CWC mask 1 */
#define B43_NPHY_TGNSYNC_CWCM2			B43_PHY_N(0x106) /* TGNsync CWC mask 2 */
#define B43_NPHY_TGNSYNC_CWCM3			B43_PHY_N(0x107) /* TGNsync CWC mask 3 */
#define B43_NPHY_TGNSYNC_CWCM4			B43_PHY_N(0x108) /* TGNsync CWC mask 4 */
#define B43_NPHY_CWCPOWY			B43_PHY_N(0x109) /* CWC powynomiaw */
#define B43_NPHY_SIGCNT				B43_PHY_N(0x10A) /* # sig count */
#define B43_NPHY_SIGSTAWTBIT_CTW		B43_PHY_N(0x10B) /* Sig stawt bit contwow */
#define B43_NPHY_CWCPOWY_OWDEW			B43_PHY_N(0x10C) /* CWC powynomiaw owdew */
#define B43_NPHY_WFCTW_CST0			B43_PHY_N(0x10D) /* WF contwow cowe swap tabwe 0 */
#define B43_NPHY_WFCTW_CST1			B43_PHY_N(0x10E) /* WF contwow cowe swap tabwe 1 */
#define B43_NPHY_WFCTW_CST2O			B43_PHY_N(0x10F) /* WF contwow cowe swap tabwe 2 + othews */
#define B43_NPHY_BPHY_CTW5			B43_PHY_N(0x111) /* B PHY contwow 5 */
#define B43_NPHY_WFSEQ_WPFBW			B43_PHY_N(0x112) /* WF seq WPF bandwidth */
#define B43_NPHY_TSSIBIAS1			B43_PHY_N(0x114) /* TSSI bias vaw 1 */
#define B43_NPHY_TSSIBIAS2			B43_PHY_N(0x115) /* TSSI bias vaw 2 */
#define  B43_NPHY_TSSIBIAS_BIAS			0x00FF /* Bias */
#define  B43_NPHY_TSSIBIAS_BIAS_SHIFT		0
#define  B43_NPHY_TSSIBIAS_VAW			0xFF00 /* Vawue */
#define  B43_NPHY_TSSIBIAS_VAW_SHIFT		8
#define B43_NPHY_ESTPWW1			B43_PHY_N(0x118) /* Estimated powew 1 */
#define B43_NPHY_ESTPWW2			B43_PHY_N(0x119) /* Estimated powew 2 */
#define  B43_NPHY_ESTPWW_PWW			0x00FF /* Estimated powew */
#define  B43_NPHY_ESTPWW_PWW_SHIFT		0
#define  B43_NPHY_ESTPWW_VAWID			0x0100 /* Estimated powew vawid */
#define B43_NPHY_TSSI_MAXTXFDT			B43_PHY_N(0x11C) /* TSSI max TX fwame deway time */
#define  B43_NPHY_TSSI_MAXTXFDT_VAW		0x00FF /* max TX fwame deway time */
#define  B43_NPHY_TSSI_MAXTXFDT_VAW_SHIFT	0
#define B43_NPHY_TSSI_MAXTDT			B43_PHY_N(0x11D) /* TSSI max TSSI deway time */
#define  B43_NPHY_TSSI_MAXTDT_VAW		0x00FF /* max TSSI deway time */
#define  B43_NPHY_TSSI_MAXTDT_VAW_SHIFT		0
#define B43_NPHY_ITSSI1				B43_PHY_N(0x11E) /* TSSI idwe 1 */
#define B43_NPHY_ITSSI2				B43_PHY_N(0x11F) /* TSSI idwe 2 */
#define  B43_NPHY_ITSSI_VAW			0x00FF /* Idwe TSSI */
#define  B43_NPHY_ITSSI_VAW_SHIFT		0
#define B43_NPHY_TSSIMODE			B43_PHY_N(0x122) /* TSSI mode */
#define  B43_NPHY_TSSIMODE_EN			0x0001 /* TSSI enabwe */
#define  B43_NPHY_TSSIMODE_PDEN			0x0002 /* Powew det enabwe */
#define B43_NPHY_WXMACIFM			B43_PHY_N(0x123) /* WX Macif mode */
#define B43_NPHY_CWSIT_COCNT_WO			B43_PHY_N(0x124) /* CWS idwe time CWS-on count (wow) */
#define B43_NPHY_CWSIT_COCNT_HI			B43_PHY_N(0x125) /* CWS idwe time CWS-on count (high) */
#define B43_NPHY_CWSIT_MTCNT_WO			B43_PHY_N(0x126) /* CWS idwe time measuwe time count (wow) */
#define B43_NPHY_CWSIT_MTCNT_HI			B43_PHY_N(0x127) /* CWS idwe time measuwe time count (high) */
#define B43_NPHY_SAMTWC				B43_PHY_N(0x128) /* Sampwe taiw wait count */
#define B43_NPHY_IQEST_CMD			B43_PHY_N(0x129) /* I/Q estimate command */
#define  B43_NPHY_IQEST_CMD_STAWT		0x0001 /* Stawt */
#define  B43_NPHY_IQEST_CMD_MODE		0x0002 /* Mode */
#define B43_NPHY_IQEST_WT			B43_PHY_N(0x12A) /* I/Q estimate wait time */
#define  B43_NPHY_IQEST_WT_VAW			0x00FF /* Wait time */
#define  B43_NPHY_IQEST_WT_VAW_SHIFT		0
#define B43_NPHY_IQEST_SAMCNT			B43_PHY_N(0x12B) /* I/Q estimate sampwe count */
#define B43_NPHY_IQEST_IQACC_WO0		B43_PHY_N(0x12C) /* I/Q estimate I/Q acc wo 0 */
#define B43_NPHY_IQEST_IQACC_HI0		B43_PHY_N(0x12D) /* I/Q estimate I/Q acc hi 0 */
#define B43_NPHY_IQEST_IPACC_WO0		B43_PHY_N(0x12E) /* I/Q estimate I powew acc wo 0 */
#define B43_NPHY_IQEST_IPACC_HI0		B43_PHY_N(0x12F) /* I/Q estimate I powew acc hi 0 */
#define B43_NPHY_IQEST_QPACC_WO0		B43_PHY_N(0x130) /* I/Q estimate Q powew acc wo 0 */
#define B43_NPHY_IQEST_QPACC_HI0		B43_PHY_N(0x131) /* I/Q estimate Q powew acc hi 0 */
#define B43_NPHY_IQEST_IQACC_WO1		B43_PHY_N(0x134) /* I/Q estimate I/Q acc wo 1 */
#define B43_NPHY_IQEST_IQACC_HI1		B43_PHY_N(0x135) /* I/Q estimate I/Q acc hi 1 */
#define B43_NPHY_IQEST_IPACC_WO1		B43_PHY_N(0x136) /* I/Q estimate I powew acc wo 1 */
#define B43_NPHY_IQEST_IPACC_HI1		B43_PHY_N(0x137) /* I/Q estimate I powew acc hi 1 */
#define B43_NPHY_IQEST_QPACC_WO1		B43_PHY_N(0x138) /* I/Q estimate Q powew acc wo 1 */
#define B43_NPHY_IQEST_QPACC_HI1		B43_PHY_N(0x139) /* I/Q estimate Q powew acc hi 1 */
#define B43_NPHY_MIMO_CWSTXEXT			B43_PHY_N(0x13A) /* MIMO PHY CWS TX extension */
#define B43_NPHY_PWWDET1			B43_PHY_N(0x13B) /* Powew det 1 */
#define B43_NPHY_PWWDET2			B43_PHY_N(0x13C) /* Powew det 2 */
#define B43_NPHY_MAXWSSI_DTIME			B43_PHY_N(0x13F) /* WSSI max WSSI deway time */
#define B43_NPHY_PIW_DW0			B43_PHY_N(0x141) /* Piwot data weight 0 */
#define B43_NPHY_PIW_DW1			B43_PHY_N(0x142) /* Piwot data weight 1 */
#define B43_NPHY_PIW_DW2			B43_PHY_N(0x143) /* Piwot data weight 2 */
#define  B43_NPHY_PIW_DW_BPSK			0x000F /* BPSK */
#define  B43_NPHY_PIW_DW_BPSK_SHIFT		0
#define  B43_NPHY_PIW_DW_QPSK			0x00F0 /* QPSK */
#define  B43_NPHY_PIW_DW_QPSK_SHIFT		4
#define  B43_NPHY_PIW_DW_16QAM			0x0F00 /* 16-QAM */
#define  B43_NPHY_PIW_DW_16QAM_SHIFT		8
#define  B43_NPHY_PIW_DW_64QAM			0xF000 /* 64-QAM */
#define  B43_NPHY_PIW_DW_64QAM_SHIFT		12
#define B43_NPHY_FMDEM_CFG			B43_PHY_N(0x144) /* FM demoduwation config */
#define B43_NPHY_PHASETW_A0			B43_PHY_N(0x145) /* Phase twack awpha 0 */
#define B43_NPHY_PHASETW_A1			B43_PHY_N(0x146) /* Phase twack awpha 1 */
#define B43_NPHY_PHASETW_A2			B43_PHY_N(0x147) /* Phase twack awpha 2 */
#define B43_NPHY_PHASETW_B0			B43_PHY_N(0x148) /* Phase twack beta 0 */
#define B43_NPHY_PHASETW_B1			B43_PHY_N(0x149) /* Phase twack beta 1 */
#define B43_NPHY_PHASETW_B2			B43_PHY_N(0x14A) /* Phase twack beta 2 */
#define B43_NPHY_PHASETW_CHG0			B43_PHY_N(0x14B) /* Phase twack change 0 */
#define B43_NPHY_PHASETW_CHG1			B43_PHY_N(0x14C) /* Phase twack change 1 */
#define B43_NPHY_PHASETW_OFF			B43_PHY_N(0x14D) /* Phase twack offset */
#define B43_NPHY_WFCTW_DBG			B43_PHY_N(0x14E) /* WF contwow debug */
#define B43_NPHY_CCK_SHIFTB_WEF			B43_PHY_N(0x150) /* CCK shiftbits wefewence vaw */
#define B43_NPHY_OVEW_DGAIN0			B43_PHY_N(0x152) /* Ovewwide digitaw gain 0 */
#define B43_NPHY_OVEW_DGAIN1			B43_PHY_N(0x153) /* Ovewwide digitaw gain 1 */
#define  B43_NPHY_OVEW_DGAIN_FDGV		0x0007 /* Fowce digitaw gain vawue */
#define  B43_NPHY_OVEW_DGAIN_FDGV_SHIFT		0
#define  B43_NPHY_OVEW_DGAIN_FDGEN		0x0008 /* Fowce digitaw gain enabwe */
#define  B43_NPHY_OVEW_DGAIN_CCKDGECV		0xFF00 /* CCK digitaw gain enabwe count vawue */
#define  B43_NPHY_OVEW_DGAIN_CCKDGECV_SHIFT	8
#define B43_NPHY_BIST_STAT4			B43_PHY_N(0x156) /* BIST status 4 */
#define B43_NPHY_WADAW_MAW			B43_PHY_N(0x157) /* Wadaw MA wength */
#define B43_NPHY_WADAW_SWCCTW			B43_PHY_N(0x158) /* Wadaw seawch contwow */
#define B43_NPHY_VWD_DTSIG			B43_PHY_N(0x159) /* VWD data tones sig */
#define B43_NPHY_VWD_DTDAT			B43_PHY_N(0x15A) /* VWD data tones data */
#define B43_NPHY_C1_BPHY_WXIQCA0		B43_PHY_N(0x15B) /* Cowe 1 B PHY WX I/Q comp A0 */
#define B43_NPHY_C1_BPHY_WXIQCB0		B43_PHY_N(0x15C) /* Cowe 1 B PHY WX I/Q comp B0 */
#define B43_NPHY_C2_BPHY_WXIQCA1		B43_PHY_N(0x15D) /* Cowe 2 B PHY WX I/Q comp A1 */
#define B43_NPHY_C2_BPHY_WXIQCB1		B43_PHY_N(0x15E) /* Cowe 2 B PHY WX I/Q comp B1 */
#define B43_NPHY_FWEQGAIN0			B43_PHY_N(0x160) /* Fwequency gain 0 */
#define B43_NPHY_FWEQGAIN1			B43_PHY_N(0x161) /* Fwequency gain 1 */
#define B43_NPHY_FWEQGAIN2			B43_PHY_N(0x162) /* Fwequency gain 2 */
#define B43_NPHY_FWEQGAIN3			B43_PHY_N(0x163) /* Fwequency gain 3 */
#define B43_NPHY_FWEQGAIN4			B43_PHY_N(0x164) /* Fwequency gain 4 */
#define B43_NPHY_FWEQGAIN5			B43_PHY_N(0x165) /* Fwequency gain 5 */
#define B43_NPHY_FWEQGAIN6			B43_PHY_N(0x166) /* Fwequency gain 6 */
#define B43_NPHY_FWEQGAIN7			B43_PHY_N(0x167) /* Fwequency gain 7 */
#define B43_NPHY_FWEQGAIN_BYPASS		B43_PHY_N(0x168) /* Fwequency gain bypass */
#define B43_NPHY_TWWOSS				B43_PHY_N(0x169) /* TW woss vawue */
#define B43_NPHY_C1_ADCCWIP			B43_PHY_N(0x16A) /* Cowe 1 ADC cwip */
#define B43_NPHY_C2_ADCCWIP			B43_PHY_N(0x16B) /* Cowe 2 ADC cwip */
#define B43_NPHY_WTWN_OFFGAIN			B43_PHY_N(0x16F) /* WTWN offset gain */
#define B43_NPHY_WTWN_OFF			B43_PHY_N(0x170) /* WTWN offset */
#define B43_NPHY_NWDATAT_WWISE20SIG		B43_PHY_N(0x171) /* # data tones WWiSE 20 sig */
#define B43_NPHY_NWDATAT_WWISE40SIG		B43_PHY_N(0x172) /* # data tones WWiSE 40 sig */
#define B43_NPHY_NWDATAT_TGNSYNC20SIG		B43_PHY_N(0x173) /* # data tones TGNsync 20 sig */
#define B43_NPHY_NWDATAT_TGNSYNC40SIG		B43_PHY_N(0x174) /* # data tones TGNsync 40 sig */
#define B43_NPHY_WWISE_CWCM0			B43_PHY_N(0x175) /* WWiSE CWC mask 0 */
#define B43_NPHY_WWISE_CWCM1			B43_PHY_N(0x176) /* WWiSE CWC mask 1 */
#define B43_NPHY_WWISE_CWCM2			B43_PHY_N(0x177) /* WWiSE CWC mask 2 */
#define B43_NPHY_WWISE_CWCM3			B43_PHY_N(0x178) /* WWiSE CWC mask 3 */
#define B43_NPHY_WWISE_CWCM4			B43_PHY_N(0x179) /* WWiSE CWC mask 4 */
#define B43_NPHY_CHANEST_CDDSH			B43_PHY_N(0x17A) /* Channew estimate CDD shift */
#define B43_NPHY_HTAGC_WCNT			B43_PHY_N(0x17B) /* HT ADC wait countews */
#define B43_NPHY_SQPAWM				B43_PHY_N(0x17C) /* SQ pawams */
#define B43_NPHY_MCSDUP6M			B43_PHY_N(0x17D) /* MCS dup 6M */
#define B43_NPHY_NDATAT_DUP40			B43_PHY_N(0x17E) /* # data tones dup 40 */
#define B43_NPHY_DUP40_TGNSYNC_CYCD		B43_PHY_N(0x17F) /* Dup40 TGNsync cycwe data */
#define B43_NPHY_DUP40_GFBW			B43_PHY_N(0x180) /* Dup40 GF fowmat BW addwess */
#define B43_NPHY_DUP40_BW			B43_PHY_N(0x181) /* Dup40 fowmat BW addwess */
#define B43_NPHY_WEGDUP_FTA			B43_PHY_N(0x182) /* Wegacy dup fwm tabwe addwess */
#define B43_NPHY_PACPWOC_DBG			B43_PHY_N(0x183) /* Packet pwocessing debug */
#define B43_NPHY_PIW_CYC1			B43_PHY_N(0x184) /* Piwot cycwe countew 1 */
#define B43_NPHY_PIW_CYC2			B43_PHY_N(0x185) /* Piwot cycwe countew 2 */
#define B43_NPHY_TXF_20CO_S0A1			B43_PHY_N(0x186) /* TX fiwtew 20 coeff stage 0 A1 */
#define B43_NPHY_TXF_20CO_S0A2			B43_PHY_N(0x187) /* TX fiwtew 20 coeff stage 0 A2 */
#define B43_NPHY_TXF_20CO_S1A1			B43_PHY_N(0x188) /* TX fiwtew 20 coeff stage 1 A1 */
#define B43_NPHY_TXF_20CO_S1A2			B43_PHY_N(0x189) /* TX fiwtew 20 coeff stage 1 A2 */
#define B43_NPHY_TXF_20CO_S2A1			B43_PHY_N(0x18A) /* TX fiwtew 20 coeff stage 2 A1 */
#define B43_NPHY_TXF_20CO_S2A2			B43_PHY_N(0x18B) /* TX fiwtew 20 coeff stage 2 A2 */
#define B43_NPHY_TXF_20CO_S0B1			B43_PHY_N(0x18C) /* TX fiwtew 20 coeff stage 0 B1 */
#define B43_NPHY_TXF_20CO_S0B2			B43_PHY_N(0x18D) /* TX fiwtew 20 coeff stage 0 B2 */
#define B43_NPHY_TXF_20CO_S0B3			B43_PHY_N(0x18E) /* TX fiwtew 20 coeff stage 0 B3 */
#define B43_NPHY_TXF_20CO_S1B1			B43_PHY_N(0x18F) /* TX fiwtew 20 coeff stage 1 B1 */
#define B43_NPHY_TXF_20CO_S1B2			B43_PHY_N(0x190) /* TX fiwtew 20 coeff stage 1 B2 */
#define B43_NPHY_TXF_20CO_S1B3			B43_PHY_N(0x191) /* TX fiwtew 20 coeff stage 1 B3 */
#define B43_NPHY_TXF_20CO_S2B1			B43_PHY_N(0x192) /* TX fiwtew 20 coeff stage 2 B1 */
#define B43_NPHY_TXF_20CO_S2B2			B43_PHY_N(0x193) /* TX fiwtew 20 coeff stage 2 B2 */
#define B43_NPHY_TXF_20CO_S2B3			B43_PHY_N(0x194) /* TX fiwtew 20 coeff stage 2 B3 */
#define B43_NPHY_TXF_40CO_S0A1			B43_PHY_N(0x195) /* TX fiwtew 40 coeff stage 0 A1 */
#define B43_NPHY_TXF_40CO_S0A2			B43_PHY_N(0x196) /* TX fiwtew 40 coeff stage 0 A2 */
#define B43_NPHY_TXF_40CO_S1A1			B43_PHY_N(0x197) /* TX fiwtew 40 coeff stage 1 A1 */
#define B43_NPHY_TXF_40CO_S1A2			B43_PHY_N(0x198) /* TX fiwtew 40 coeff stage 1 A2 */
#define B43_NPHY_TXF_40CO_S2A1			B43_PHY_N(0x199) /* TX fiwtew 40 coeff stage 2 A1 */
#define B43_NPHY_TXF_40CO_S2A2			B43_PHY_N(0x19A) /* TX fiwtew 40 coeff stage 2 A2 */
#define B43_NPHY_TXF_40CO_S0B1			B43_PHY_N(0x19B) /* TX fiwtew 40 coeff stage 0 B1 */
#define B43_NPHY_TXF_40CO_S0B2			B43_PHY_N(0x19C) /* TX fiwtew 40 coeff stage 0 B2 */
#define B43_NPHY_TXF_40CO_S0B3			B43_PHY_N(0x19D) /* TX fiwtew 40 coeff stage 0 B3 */
#define B43_NPHY_TXF_40CO_S1B1			B43_PHY_N(0x19E) /* TX fiwtew 40 coeff stage 1 B1 */
#define B43_NPHY_TXF_40CO_S1B2			B43_PHY_N(0x19F) /* TX fiwtew 40 coeff stage 1 B2 */
#define B43_NPHY_TXF_40CO_S1B3			B43_PHY_N(0x1A0) /* TX fiwtew 40 coeff stage 1 B3 */
#define B43_NPHY_TXF_40CO_S2B1			B43_PHY_N(0x1A1) /* TX fiwtew 40 coeff stage 2 B1 */
#define B43_NPHY_TXF_40CO_S2B2			B43_PHY_N(0x1A2) /* TX fiwtew 40 coeff stage 2 B2 */
#define B43_NPHY_TXF_40CO_S2B3			B43_PHY_N(0x1A3) /* TX fiwtew 40 coeff stage 2 B3 */
#define B43_NPHY_WSSIMC_0I_WSSI_X		B43_PHY_N(0x1A4) /* WSSI muwtipwication coefficient 0 I WSSI X */
#define B43_NPHY_WSSIMC_0I_WSSI_Y		B43_PHY_N(0x1A5) /* WSSI muwtipwication coefficient 0 I WSSI Y */
#define B43_NPHY_WSSIMC_0I_WSSI_Z		B43_PHY_N(0x1A6) /* WSSI muwtipwication coefficient 0 I WSSI Z */
#define B43_NPHY_WSSIMC_0I_TBD			B43_PHY_N(0x1A7) /* WSSI muwtipwication coefficient 0 I TBD */
#define B43_NPHY_WSSIMC_0I_PWWDET		B43_PHY_N(0x1A8) /* WSSI muwtipwication coefficient 0 I powew det */
#define B43_NPHY_WSSIMC_0I_TSSI			B43_PHY_N(0x1A9) /* WSSI muwtipwication coefficient 0 I TSSI */
#define B43_NPHY_WSSIMC_0Q_WSSI_X		B43_PHY_N(0x1AA) /* WSSI muwtipwication coefficient 0 Q WSSI X */
#define B43_NPHY_WSSIMC_0Q_WSSI_Y		B43_PHY_N(0x1AB) /* WSSI muwtipwication coefficient 0 Q WSSI Y */
#define B43_NPHY_WSSIMC_0Q_WSSI_Z		B43_PHY_N(0x1AC) /* WSSI muwtipwication coefficient 0 Q WSSI Z */
#define B43_NPHY_WSSIMC_0Q_TBD			B43_PHY_N(0x1AD) /* WSSI muwtipwication coefficient 0 Q TBD */
#define B43_NPHY_WSSIMC_0Q_PWWDET		B43_PHY_N(0x1AE) /* WSSI muwtipwication coefficient 0 Q powew det */
#define B43_NPHY_WSSIMC_0Q_TSSI			B43_PHY_N(0x1AF) /* WSSI muwtipwication coefficient 0 Q TSSI */
#define B43_NPHY_WSSIMC_1I_WSSI_X		B43_PHY_N(0x1B0) /* WSSI muwtipwication coefficient 1 I WSSI X */
#define B43_NPHY_WSSIMC_1I_WSSI_Y		B43_PHY_N(0x1B1) /* WSSI muwtipwication coefficient 1 I WSSI Y */
#define B43_NPHY_WSSIMC_1I_WSSI_Z		B43_PHY_N(0x1B2) /* WSSI muwtipwication coefficient 1 I WSSI Z */
#define B43_NPHY_WSSIMC_1I_TBD			B43_PHY_N(0x1B3) /* WSSI muwtipwication coefficient 1 I TBD */
#define B43_NPHY_WSSIMC_1I_PWWDET		B43_PHY_N(0x1B4) /* WSSI muwtipwication coefficient 1 I powew det */
#define B43_NPHY_WSSIMC_1I_TSSI			B43_PHY_N(0x1B5) /* WSSI muwtipwication coefficient 1 I TSSI */
#define B43_NPHY_WSSIMC_1Q_WSSI_X		B43_PHY_N(0x1B6) /* WSSI muwtipwication coefficient 1 Q WSSI X */
#define B43_NPHY_WSSIMC_1Q_WSSI_Y		B43_PHY_N(0x1B7) /* WSSI muwtipwication coefficient 1 Q WSSI Y */
#define B43_NPHY_WSSIMC_1Q_WSSI_Z		B43_PHY_N(0x1B8) /* WSSI muwtipwication coefficient 1 Q WSSI Z */
#define B43_NPHY_WSSIMC_1Q_TBD			B43_PHY_N(0x1B9) /* WSSI muwtipwication coefficient 1 Q TBD */
#define B43_NPHY_WSSIMC_1Q_PWWDET		B43_PHY_N(0x1BA) /* WSSI muwtipwication coefficient 1 Q powew det */
#define B43_NPHY_WSSIMC_1Q_TSSI			B43_PHY_N(0x1BB) /* WSSI muwtipwication coefficient 1 Q TSSI */
#define B43_NPHY_SAMC_WCNT			B43_PHY_N(0x1BC) /* Sampwe cowwect wait countew */
#define B43_NPHY_PTHWOUGH_CNT			B43_PHY_N(0x1BD) /* Pass-thwough countew */
#define B43_NPHY_WTWN_OFF_G20W			B43_PHY_N(0x1C4) /* WTWN offset gain 20W */
#define B43_NPHY_WTWN_OFF_20W			B43_PHY_N(0x1C5) /* WTWN offset 20W */
#define B43_NPHY_WTWN_OFF_G20U			B43_PHY_N(0x1C6) /* WTWN offset gain 20U */
#define B43_NPHY_WTWN_OFF_20U			B43_PHY_N(0x1C7) /* WTWN offset 20U */
#define B43_NPHY_DSSSCCK_GAINSW			B43_PHY_N(0x1C8) /* DSSS/CCK gain settwe wength */
#define B43_NPHY_GPIO_WOOUT			B43_PHY_N(0x1C9) /* GPIO wow out */
#define B43_NPHY_GPIO_HIOUT			B43_PHY_N(0x1CA) /* GPIO high out */
#define B43_NPHY_CWS_CHECK			B43_PHY_N(0x1CB) /* CWS check */
#define B43_NPHY_MW_WOGSS_WAT			B43_PHY_N(0x1CC) /* MW/wogss watio */
#define B43_NPHY_DUPSCAWE			B43_PHY_N(0x1CD) /* Dup scawe */
#define B43_NPHY_BW1A				B43_PHY_N(0x1CE) /* BW 1A */
#define B43_NPHY_BW2				B43_PHY_N(0x1CF) /* BW 2 */
#define B43_NPHY_BW3				B43_PHY_N(0x1D0) /* BW 3 */
#define B43_NPHY_BW4				B43_PHY_N(0x1D1) /* BW 4 */
#define B43_NPHY_BW5				B43_PHY_N(0x1D2) /* BW 5 */
#define B43_NPHY_BW6				B43_PHY_N(0x1D3) /* BW 6 */
#define B43_NPHY_COAWEN0			B43_PHY_N(0x1D4) /* Coawse wength 0 */
#define B43_NPHY_COAWEN1			B43_PHY_N(0x1D5) /* Coawse wength 1 */
#define B43_NPHY_CWSTHWES_1U			B43_PHY_N(0x1D6) /* CWS thweshowd 1 U */
#define B43_NPHY_CWSTHWES_2U			B43_PHY_N(0x1D7) /* CWS thweshowd 2 U */
#define B43_NPHY_CWSTHWES_3U			B43_PHY_N(0x1D8) /* CWS thweshowd 3 U */
#define B43_NPHY_CWSCTW_U			B43_PHY_N(0x1D9) /* CWS contwow U */
#define B43_NPHY_CWSTHWES_1W			B43_PHY_N(0x1DA) /* CWS thweshowd 1 W */
#define B43_NPHY_CWSTHWES_2W			B43_PHY_N(0x1DB) /* CWS thweshowd 2 W */
#define B43_NPHY_CWSTHWES_3W			B43_PHY_N(0x1DC) /* CWS thweshowd 3 W */
#define B43_NPHY_CWSCTW_W			B43_PHY_N(0x1DD) /* CWS contwow W */
#define B43_NPHY_STWA_1U			B43_PHY_N(0x1DE) /* STW addwess 1 U */
#define B43_NPHY_STWA_2U			B43_PHY_N(0x1DF) /* STW addwess 2 U */
#define B43_NPHY_STWA_1W			B43_PHY_N(0x1E0) /* STW addwess 1 W */
#define B43_NPHY_STWA_2W			B43_PHY_N(0x1E1) /* STW addwess 2 W */
#define B43_NPHY_CWSCHECK1			B43_PHY_N(0x1E2) /* CWS check 1 */
#define B43_NPHY_CWSCHECK2			B43_PHY_N(0x1E3) /* CWS check 2 */
#define B43_NPHY_CWSCHECK3			B43_PHY_N(0x1E4) /* CWS check 3 */
#define B43_NPHY_JMPSTP0			B43_PHY_N(0x1E5) /* Jump step 0 */
#define B43_NPHY_JMPSTP1			B43_PHY_N(0x1E6) /* Jump step 1 */
#define B43_NPHY_TXPCTW_CMD			B43_PHY_N(0x1E7) /* TX powew contwow command */
#define  B43_NPHY_TXPCTW_CMD_INIT		0x007F /* Init */
#define  B43_NPHY_TXPCTW_CMD_INIT_SHIFT		0
#define  B43_NPHY_TXPCTW_CMD_COEFF		0x2000 /* Powew contwow coefficients */
#define  B43_NPHY_TXPCTW_CMD_HWPCTWEN		0x4000 /* Hawdwawe TX powew contwow enabwe */
#define  B43_NPHY_TXPCTW_CMD_PCTWEN		0x8000 /* TX powew contwow enabwe */
#define B43_NPHY_TXPCTW_N			B43_PHY_N(0x1E8) /* TX powew contwow N num */
#define  B43_NPHY_TXPCTW_N_TSSID		0x00FF /* N TSSI deway */
#define  B43_NPHY_TXPCTW_N_TSSID_SHIFT		0
#define  B43_NPHY_TXPCTW_N_NPTIW2		0x0700 /* N PT integew wog2 */
#define  B43_NPHY_TXPCTW_N_NPTIW2_SHIFT		8
#define B43_NPHY_TXPCTW_ITSSI			B43_PHY_N(0x1E9) /* TX powew contwow idwe TSSI */
#define  B43_NPHY_TXPCTW_ITSSI_0		0x003F /* Idwe TSSI 0 */
#define  B43_NPHY_TXPCTW_ITSSI_0_SHIFT		0
#define  B43_NPHY_TXPCTW_ITSSI_1		0x3F00 /* Idwe TSSI 1 */
#define  B43_NPHY_TXPCTW_ITSSI_1_SHIFT		8
#define  B43_NPHY_TXPCTW_ITSSI_BINF		0x8000 /* Waw TSSI offset bin fowmat */
#define B43_NPHY_TXPCTW_TPWW			B43_PHY_N(0x1EA) /* TX powew contwow tawget powew */
#define  B43_NPHY_TXPCTW_TPWW_0			0x00FF /* Powew 0 */
#define  B43_NPHY_TXPCTW_TPWW_0_SHIFT		0
#define  B43_NPHY_TXPCTW_TPWW_1			0xFF00 /* Powew 1 */
#define  B43_NPHY_TXPCTW_TPWW_1_SHIFT		8
#define B43_NPHY_TXPCTW_BIDX			B43_PHY_N(0x1EB) /* TX powew contwow base index */
#define  B43_NPHY_TXPCTW_BIDX_0			0x007F /* uC base index 0 */
#define  B43_NPHY_TXPCTW_BIDX_0_SHIFT		0
#define  B43_NPHY_TXPCTW_BIDX_1			0x7F00 /* uC base index 1 */
#define  B43_NPHY_TXPCTW_BIDX_1_SHIFT		8
#define  B43_NPHY_TXPCTW_BIDX_WOAD		0x8000 /* Woad base index */
#define B43_NPHY_TXPCTW_PIDX			B43_PHY_N(0x1EC) /* TX powew contwow powew index */
#define  B43_NPHY_TXPCTW_PIDX_0			0x007F /* uC powew index 0 */
#define  B43_NPHY_TXPCTW_PIDX_0_SHIFT		0
#define  B43_NPHY_TXPCTW_PIDX_1			0x7F00 /* uC powew index 1 */
#define  B43_NPHY_TXPCTW_PIDX_1_SHIFT		8
#define B43_NPHY_C1_TXPCTW_STAT			B43_PHY_N(0x1ED) /* Cowe 1 TX powew contwow status */
#define B43_NPHY_C2_TXPCTW_STAT			B43_PHY_N(0x1EE) /* Cowe 2 TX powew contwow status */
#define  B43_NPHY_TXPCTW_STAT_EST		0x00FF /* Estimated powew */
#define  B43_NPHY_TXPCTW_STAT_EST_SHIFT		0
#define  B43_NPHY_TXPCTW_STAT_BIDX		0x7F00 /* Base index */
#define  B43_NPHY_TXPCTW_STAT_BIDX_SHIFT	8
#define  B43_NPHY_TXPCTW_STAT_ESTVAWID		0x8000 /* Estimated powew vawid */
#define B43_NPHY_SMAWWSGS_WEN			B43_PHY_N(0x1EF) /* Smaww sig gain settwe wength */
#define B43_NPHY_PHYSTAT_GAIN0			B43_PHY_N(0x1F0) /* PHY stats gain info 0 */
#define B43_NPHY_PHYSTAT_GAIN1			B43_PHY_N(0x1F1) /* PHY stats gain info 1 */
#define B43_NPHY_PHYSTAT_FWEQEST		B43_PHY_N(0x1F2) /* PHY stats fwequency estimate */
#define B43_NPHY_PHYSTAT_ADVWET			B43_PHY_N(0x1F3) /* PHY stats ADV wetawd */
#define B43_NPHY_PHYWB_MODE			B43_PHY_N(0x1F4) /* PHY woopback mode */
#define B43_NPHY_TONE_MIDX20_1			B43_PHY_N(0x1F5) /* Tone map index 20/1 */
#define B43_NPHY_TONE_MIDX20_2			B43_PHY_N(0x1F6) /* Tone map index 20/2 */
#define B43_NPHY_TONE_MIDX20_3			B43_PHY_N(0x1F7) /* Tone map index 20/3 */
#define B43_NPHY_TONE_MIDX40_1			B43_PHY_N(0x1F8) /* Tone map index 40/1 */
#define B43_NPHY_TONE_MIDX40_2			B43_PHY_N(0x1F9) /* Tone map index 40/2 */
#define B43_NPHY_TONE_MIDX40_3			B43_PHY_N(0x1FA) /* Tone map index 40/3 */
#define B43_NPHY_TONE_MIDX40_4			B43_PHY_N(0x1FB) /* Tone map index 40/4 */
#define B43_NPHY_PIWTONE_MIDX1			B43_PHY_N(0x1FC) /* Piwot tone map index 1 */
#define B43_NPHY_PIWTONE_MIDX2			B43_PHY_N(0x1FD) /* Piwot tone map index 2 */
#define B43_NPHY_PIWTONE_MIDX3			B43_PHY_N(0x1FE) /* Piwot tone map index 3 */
#define B43_NPHY_TXWIFS_FWDEW			B43_PHY_N(0x1FF) /* TX WIFS fwame deway */
#define B43_NPHY_AFESEQ_WX2TX_PUD_40M		B43_PHY_N(0x200) /* AFE seq wx2tx powew up/down deway 40M */
#define B43_NPHY_AFESEQ_TX2WX_PUD_40M		B43_PHY_N(0x201) /* AFE seq tx2wx powew up/down deway 40M */
#define B43_NPHY_AFESEQ_WX2TX_PUD_20M		B43_PHY_N(0x202) /* AFE seq wx2tx powew up/down deway 20M */
#define B43_NPHY_AFESEQ_TX2WX_PUD_20M		B43_PHY_N(0x203) /* AFE seq tx2wx powew up/down deway 20M */
#define B43_NPHY_WX_SIGCTW			B43_PHY_N(0x204) /* WX signaw contwow */
#define B43_NPHY_WXPIW_CYCNT0			B43_PHY_N(0x205) /* WX piwot cycwe countew 0 */
#define B43_NPHY_WXPIW_CYCNT1			B43_PHY_N(0x206) /* WX piwot cycwe countew 1 */
#define B43_NPHY_WXPIW_CYCNT2			B43_PHY_N(0x207) /* WX piwot cycwe countew 2 */
#define B43_NPHY_AFESEQ_WX2TX_PUD_10M		B43_PHY_N(0x208) /* AFE seq wx2tx powew up/down deway 10M */
#define B43_NPHY_AFESEQ_TX2WX_PUD_10M		B43_PHY_N(0x209) /* AFE seq tx2wx powew up/down deway 10M */
#define B43_NPHY_DSSSCCK_CWSEXTW		B43_PHY_N(0x20A) /* DSSS/CCK CWS extension wength */
#define B43_NPHY_MW_WOGSS_WATSWOPE		B43_PHY_N(0x20B) /* MW/wogss watio swope */
#define B43_NPHY_WIFS_SWCTW			B43_PHY_N(0x20C) /* WIFS seawch timeout wength */
#define B43_NPHY_TXWEAWFD			B43_PHY_N(0x20D) /* TX weaw fwame deway */
#define B43_NPHY_HPANT_SWTHWES			B43_PHY_N(0x20E) /* High powew antenna switch thweshowd */
#define B43_NPHY_EDCWS_ASSTHWES0		B43_PHY_N(0x210) /* ED CWS assewt thweshowd 0 */
#define B43_NPHY_EDCWS_ASSTHWES1		B43_PHY_N(0x211) /* ED CWS assewt thweshowd 1 */
#define B43_NPHY_EDCWS_DEASSTHWES0		B43_PHY_N(0x212) /* ED CWS deassewt thweshowd 0 */
#define B43_NPHY_EDCWS_DEASSTHWES1		B43_PHY_N(0x213) /* ED CWS deassewt thweshowd 1 */
#define B43_NPHY_STW_WTIME20U			B43_PHY_N(0x214) /* STW wait time 20U */
#define B43_NPHY_STW_WTIME20W			B43_PHY_N(0x215) /* STW wait time 20W */
#define B43_NPHY_TONE_MIDX657M			B43_PHY_N(0x216) /* Tone map index 657M */
#define B43_NPHY_HTSIGTONES			B43_PHY_N(0x217) /* HT signaw tones */
#define B43_NPHY_WSSI1				B43_PHY_N(0x219) /* WSSI vawue 1 */
#define B43_NPHY_WSSI2				B43_PHY_N(0x21A) /* WSSI vawue 2 */
#define B43_NPHY_CHAN_ESTHANG			B43_PHY_N(0x21D) /* Channew estimate hang */
#define B43_NPHY_FINEWX2_CGC			B43_PHY_N(0x221) /* Fine WX 2 cwock gate contwow */
#define  B43_NPHY_FINEWX2_CGC_DECGC		0x0008 /* Decode gated cwocks */
#define B43_NPHY_TXPCTW_INIT			B43_PHY_N(0x222) /* TX powew contwow init */
#define  B43_NPHY_TXPCTW_INIT_PIDXI1		0x00FF /* Powew index init 1 */
#define  B43_NPHY_TXPCTW_INIT_PIDXI1_SHIFT	0
#define B43_NPHY_ED_CWSEN			B43_PHY_N(0x223)
#define B43_NPHY_ED_CWS40ASSEWTTHWESH0		B43_PHY_N(0x224)
#define B43_NPHY_ED_CWS40ASSEWTTHWESH1		B43_PHY_N(0x225)
#define B43_NPHY_ED_CWS40DEASSEWTTHWESH0	B43_PHY_N(0x226)
#define B43_NPHY_ED_CWS40DEASSEWTTHWESH1	B43_PHY_N(0x227)
#define B43_NPHY_ED_CWS20WASSEWTTHWESH0		B43_PHY_N(0x228)
#define B43_NPHY_ED_CWS20WASSEWTTHWESH1		B43_PHY_N(0x229)
#define B43_NPHY_ED_CWS20WDEASSEWTTHWESH0	B43_PHY_N(0x22A)
#define B43_NPHY_ED_CWS20WDEASSEWTTHWESH1	B43_PHY_N(0x22B)
#define B43_NPHY_ED_CWS20UASSEWTTHWESH0		B43_PHY_N(0x22C)
#define B43_NPHY_ED_CWS20UASSEWTTHWESH1		B43_PHY_N(0x22D)
#define B43_NPHY_ED_CWS20UDEASSEWTTHWESH0	B43_PHY_N(0x22E)
#define B43_NPHY_ED_CWS20UDEASSEWTTHWESH1	B43_PHY_N(0x22F)
#define B43_NPHY_ED_CWS				B43_PHY_N(0x230)
#define B43_NPHY_TIMEOUTEN			B43_PHY_N(0x231)
#define B43_NPHY_OFDMPAYDECODETIMEOUTWEN	B43_PHY_N(0x232)
#define B43_NPHY_CCKPAYDECODETIMEOUTWEN		B43_PHY_N(0x233)
#define B43_NPHY_NONPAYDECODETIMEOUTWEN		B43_PHY_N(0x234)
#define B43_NPHY_TIMEOUTSTATUS			B43_PHY_N(0x235)
#define B43_NPHY_WFCTWWCOWE0GPIO0		B43_PHY_N(0x236)
#define B43_NPHY_WFCTWWCOWE0GPIO1		B43_PHY_N(0x237)
#define B43_NPHY_WFCTWWCOWE0GPIO2		B43_PHY_N(0x238)
#define B43_NPHY_WFCTWWCOWE0GPIO3		B43_PHY_N(0x239)
#define B43_NPHY_WFCTWWCOWE1GPIO0		B43_PHY_N(0x23A)
#define B43_NPHY_WFCTWWCOWE1GPIO1		B43_PHY_N(0x23B)
#define B43_NPHY_WFCTWWCOWE1GPIO2		B43_PHY_N(0x23C)
#define B43_NPHY_WFCTWWCOWE1GPIO3		B43_PHY_N(0x23D)
#define B43_NPHY_BPHYTESTCONTWOW		B43_PHY_N(0x23E)
/* WEV3+ */
#define B43_NPHY_FOWCEFWONT0			B43_PHY_N(0x23F)
#define B43_NPHY_FOWCEFWONT1			B43_PHY_N(0x240)
#define B43_NPHY_NOWMVAWHYSTTH			B43_PHY_N(0x241)
#define B43_NPHY_TXCCKEWWOW			B43_PHY_N(0x242)
#define B43_NPHY_AFESEQINITDACGAIN		B43_PHY_N(0x243)
#define B43_NPHY_TXANTSWWUT			B43_PHY_N(0x244)
#define B43_NPHY_COWECONFIG			B43_PHY_N(0x245)
#define B43_NPHY_ANTENNADIVDWEWWTIME		B43_PHY_N(0x246)
#define B43_NPHY_ANTENNACCKDIVDWEWWTIME		B43_PHY_N(0x247)
#define B43_NPHY_ANTENNADIVBACKOFFGAIN		B43_PHY_N(0x248)
#define B43_NPHY_ANTENNADIVMINGAIN		B43_PHY_N(0x249)
#define B43_NPHY_BWDSEW_NOWMVAWHYSTTH		B43_PHY_N(0x24A)
#define B43_NPHY_WXANTSWITCHCTWW		B43_PHY_N(0x24B)
#define B43_NPHY_ENEWGYDWOPTIMEOUTWEN2		B43_PHY_N(0x24C)
#define B43_NPHY_MW_WOG_TXEVM0			B43_PHY_N(0x250)
#define B43_NPHY_MW_WOG_TXEVM1			B43_PHY_N(0x251)
#define B43_NPHY_MW_WOG_TXEVM2			B43_PHY_N(0x252)
#define B43_NPHY_MW_WOG_TXEVM3			B43_PHY_N(0x253)
#define B43_NPHY_MW_WOG_TXEVM4			B43_PHY_N(0x254)
#define B43_NPHY_MW_WOG_TXEVM5			B43_PHY_N(0x255)
#define B43_NPHY_MW_WOG_TXEVM6			B43_PHY_N(0x256)
#define B43_NPHY_MW_WOG_TXEVM7			B43_PHY_N(0x257)
#define B43_NPHY_MW_SCAWE_TWEAK			B43_PHY_N(0x258)
#define B43_NPHY_MWUA				B43_PHY_N(0x259)
#define B43_NPHY_ZFUA				B43_PHY_N(0x25A)
#define B43_NPHY_CHANUPSYM01			B43_PHY_N(0x25B)
#define B43_NPHY_CHANUPSYM2			B43_PHY_N(0x25C)
#define B43_NPHY_WXSTWNFIWT20NUM00		B43_PHY_N(0x25D)
#define B43_NPHY_WXSTWNFIWT20NUM01		B43_PHY_N(0x25E)
#define B43_NPHY_WXSTWNFIWT20NUM02		B43_PHY_N(0x25F)
#define B43_NPHY_WXSTWNFIWT20DEN00		B43_PHY_N(0x260)
#define B43_NPHY_WXSTWNFIWT20DEN01		B43_PHY_N(0x261)
#define B43_NPHY_WXSTWNFIWT20NUM10		B43_PHY_N(0x262)
#define B43_NPHY_WXSTWNFIWT20NUM11		B43_PHY_N(0x263)
#define B43_NPHY_WXSTWNFIWT20NUM12		B43_PHY_N(0x264)
#define B43_NPHY_WXSTWNFIWT20DEN10		B43_PHY_N(0x265)
#define B43_NPHY_WXSTWNFIWT20DEN11		B43_PHY_N(0x266)
#define B43_NPHY_WXSTWNFIWT40NUM00		B43_PHY_N(0x267)
#define B43_NPHY_WXSTWNFIWT40NUM01		B43_PHY_N(0x268)
#define B43_NPHY_WXSTWNFIWT40NUM02		B43_PHY_N(0x269)
#define B43_NPHY_WXSTWNFIWT40DEN00		B43_PHY_N(0x26A)
#define B43_NPHY_WXSTWNFIWT40DEN01		B43_PHY_N(0x26B)
#define B43_NPHY_WXSTWNFIWT40NUM10		B43_PHY_N(0x26C)
#define B43_NPHY_WXSTWNFIWT40NUM11		B43_PHY_N(0x26D)
#define B43_NPHY_WXSTWNFIWT40NUM12		B43_PHY_N(0x26E)
#define B43_NPHY_WXSTWNFIWT40DEN10		B43_PHY_N(0x26F)
#define B43_NPHY_WXSTWNFIWT40DEN11		B43_PHY_N(0x270)
#define B43_NPHY_CWSHIGHPOWTHWESHOWD1		B43_PHY_N(0x271)
#define B43_NPHY_CWSHIGHPOWTHWESHOWD2		B43_PHY_N(0x272)
#define B43_NPHY_CWSHIGHWOWPOWTHWESHOWD		B43_PHY_N(0x273)
#define B43_NPHY_CWSHIGHPOWTHWESHOWD1W		B43_PHY_N(0x274)
#define B43_NPHY_CWSHIGHPOWTHWESHOWD2W		B43_PHY_N(0x275)
#define B43_NPHY_CWSHIGHWOWPOWTHWESHOWDW	B43_PHY_N(0x276)
#define B43_NPHY_CWSHIGHPOWTHWESHOWD1U		B43_PHY_N(0x277)
#define B43_NPHY_CWSHIGHPOWTHWESHOWD2U		B43_PHY_N(0x278)
#define B43_NPHY_CWSHIGHWOWPOWTHWESHOWDU	B43_PHY_N(0x279)
#define B43_NPHY_CWSACIDETECTTHWESH		B43_PHY_N(0x27A)
#define B43_NPHY_CWSACIDETECTTHWESHW		B43_PHY_N(0x27B)
#define B43_NPHY_CWSACIDETECTTHWESHU		B43_PHY_N(0x27C)
#define B43_NPHY_CWSMINPOWEW0			B43_PHY_N(0x27D)
#define B43_NPHY_CWSMINPOWEW1			B43_PHY_N(0x27E)
#define B43_NPHY_CWSMINPOWEW2			B43_PHY_N(0x27F)
#define B43_NPHY_CWSMINPOWEWW0			B43_PHY_N(0x280)
#define B43_NPHY_CWSMINPOWEWW1			B43_PHY_N(0x281)
#define B43_NPHY_CWSMINPOWEWW2			B43_PHY_N(0x282)
#define B43_NPHY_CWSMINPOWEWU0			B43_PHY_N(0x283)
#define B43_NPHY_CWSMINPOWEWU1			B43_PHY_N(0x284)
#define B43_NPHY_CWSMINPOWEWU2			B43_PHY_N(0x285)
#define B43_NPHY_STWPAWAM			B43_PHY_N(0x286)
#define B43_NPHY_STWPAWAMW			B43_PHY_N(0x287)
#define B43_NPHY_STWPAWAMU			B43_PHY_N(0x288)
#define B43_NPHY_BPHYCWSMINPOWEW0		B43_PHY_N(0x289)
#define B43_NPHY_BPHYCWSMINPOWEW1		B43_PHY_N(0x28A)
#define B43_NPHY_BPHYCWSMINPOWEW2		B43_PHY_N(0x28B)
#define B43_NPHY_BPHYFIWTDEN0COEF		B43_PHY_N(0x28C)
#define B43_NPHY_BPHYFIWTDEN1COEF		B43_PHY_N(0x28D)
#define B43_NPHY_BPHYFIWTDEN2COEF		B43_PHY_N(0x28E)
#define B43_NPHY_BPHYFIWTNUM0COEF		B43_PHY_N(0x28F)
#define B43_NPHY_BPHYFIWTNUM1COEF		B43_PHY_N(0x290)
#define B43_NPHY_BPHYFIWTNUM2COEF		B43_PHY_N(0x291)
#define B43_NPHY_BPHYFIWTNUM01COEF2		B43_PHY_N(0x292)
#define B43_NPHY_BPHYFIWTBYPASS			B43_PHY_N(0x293)
#define B43_NPHY_SGIWTWNOFFSET			B43_PHY_N(0x294)
#define B43_NPHY_WADAW_T2_MIN			B43_PHY_N(0x295)
#define B43_NPHY_TXPWWCTWWDAMPING		B43_PHY_N(0x296)
#define B43_NPHY_PAPD_EN0			B43_PHY_N(0x297) /* PAPD Enabwe0 TBD */
#define B43_NPHY_EPS_TABWE_ADJ0			B43_PHY_N(0x298) /* EPS Tabwe Adj0 TBD */
#define B43_NPHY_EPS_OVEWWIDEI_0		B43_PHY_N(0x299)
#define B43_NPHY_EPS_OVEWWIDEQ_0		B43_PHY_N(0x29A)
#define B43_NPHY_PAPD_EN1			B43_PHY_N(0x29B) /* PAPD Enabwe1 TBD */
#define B43_NPHY_EPS_TABWE_ADJ1			B43_PHY_N(0x29C) /* EPS Tabwe Adj1 TBD */
#define B43_NPHY_EPS_OVEWWIDEI_1		B43_PHY_N(0x29D)
#define B43_NPHY_EPS_OVEWWIDEQ_1		B43_PHY_N(0x29E)
#define B43_NPHY_PAPD_CAW_ADDWESS		B43_PHY_N(0x29F)
#define B43_NPHY_PAPD_CAW_YWEFEPSIWON		B43_PHY_N(0x2A0)
#define B43_NPHY_PAPD_CAW_SETTWE		B43_PHY_N(0x2A1)
#define B43_NPHY_PAPD_CAW_COWWEWATE		B43_PHY_N(0x2A2)
#define B43_NPHY_PAPD_CAW_SHIFTS0		B43_PHY_N(0x2A3)
#define B43_NPHY_PAPD_CAW_SHIFTS1		B43_PHY_N(0x2A4)
#define B43_NPHY_SAMPWE_STAWT_ADDW		B43_PHY_N(0x2A5)
#define B43_NPHY_WADAW_ADC_TO_DBM		B43_PHY_N(0x2A6)
#define B43_NPHY_WEV3_C2_INITGAIN_A		B43_PHY_N(0x2A7)
#define B43_NPHY_WEV3_C2_INITGAIN_B		B43_PHY_N(0x2A8)
#define B43_NPHY_WEV3_C2_CWIP_HIGAIN_A		B43_PHY_N(0x2A9)
#define B43_NPHY_WEV3_C2_CWIP_HIGAIN_B		B43_PHY_N(0x2AA)
#define B43_NPHY_WEV3_C2_CWIP_MEDGAIN_A		B43_PHY_N(0x2AB)
#define B43_NPHY_WEV3_C2_CWIP_MEDGAIN_B		B43_PHY_N(0x2AC)
#define B43_NPHY_WEV3_C2_CWIP_WOGAIN_A		B43_PHY_N(0x2AD)
#define B43_NPHY_WEV3_C2_CWIP_WOGAIN_B		B43_PHY_N(0x2AE)
#define B43_NPHY_WEV3_C2_CWIP2_GAIN_A		B43_PHY_N(0x2AF)
#define B43_NPHY_WEV3_C2_CWIP2_GAIN_B		B43_PHY_N(0x2B0)

#define B43_NPHY_WEV7_WF_CTW_MISC_WEG3		B43_PHY_N(0x340)
#define B43_NPHY_WEV7_WF_CTW_MISC_WEG4		B43_PHY_N(0x341)
#define B43_NPHY_WEV7_WF_CTW_OVEW3		B43_PHY_N(0x342)
#define B43_NPHY_WEV7_WF_CTW_OVEW4		B43_PHY_N(0x343)
#define B43_NPHY_WEV7_WF_CTW_MISC_WEG5		B43_PHY_N(0x344)
#define B43_NPHY_WEV7_WF_CTW_MISC_WEG6		B43_PHY_N(0x345)
#define B43_NPHY_WEV7_WF_CTW_OVEW5		B43_PHY_N(0x346)
#define B43_NPHY_WEV7_WF_CTW_OVEW6		B43_PHY_N(0x347)

#define B43_PHY_B_BBCFG				B43_PHY_N_BMODE(0x001) /* BB config */
#define  B43_PHY_B_BBCFG_WSTCCA			0x4000 /* Weset CCA */
#define  B43_PHY_B_BBCFG_WSTWX			0x8000 /* Weset WX */
#define B43_PHY_B_TEST				B43_PHY_N_BMODE(0x00A)

stwuct b43_wwdev;

enum b43_nphy_spuw_avoid {
	B43_SPUW_AVOID_DISABWE,
	B43_SPUW_AVOID_AUTO,
	B43_SPUW_AVOID_FOWCE,
};

stwuct b43_chanspec {
	u16 centew_fweq;
	enum nw80211_channew_type channew_type;
};

stwuct b43_phy_n_iq_comp {
	s16 a0;
	s16 b0;
	s16 a1;
	s16 b1;
};

stwuct b43_phy_n_wssicaw_cache {
	u16 wssicaw_wadio_wegs_2G[2];
	u16 wssicaw_phy_wegs_2G[12];

	u16 wssicaw_wadio_wegs_5G[2];
	u16 wssicaw_phy_wegs_5G[12];
};

stwuct b43_phy_n_caw_cache {
	u16 txcaw_wadio_wegs_2G[8];
	u16 txcaw_coeffs_2G[8];
	stwuct b43_phy_n_iq_comp wxcaw_coeffs_2G;

	u16 txcaw_wadio_wegs_5G[8];
	u16 txcaw_coeffs_5G[8];
	stwuct b43_phy_n_iq_comp wxcaw_coeffs_5G;
};

stwuct b43_phy_n_txpwwindex {
	s8 index;
	s8 index_intewnaw;
	s8 index_intewnaw_save;
	u16 AfectwwOvewwide;
	u16 AfeCtwwDacGain;
	u16 wad_gain;
	u8 bbmuwt;
	u16 iqcomp_a;
	u16 iqcomp_b;
	u16 wocomp;
};

stwuct b43_phy_n_pww_ctw_info {
	u8 idwe_tssi_2g;
	u8 idwe_tssi_5g;
};

stwuct b43_phy_n {
	u8 antsew_type;
	u8 caw_owig_pww_idx[2];
	u8 measuwe_howd;
	u8 phywxchain;
	u8 hw_phywxchain;
	u8 hw_phytxchain;
	u8 pewicaw;
	u32 deaf_count;
	u32 wxcawpawams;
	boow hang_avoid;
	boow mute;
	u16 papd_epsiwon_offset[2];
	s32 pweambwe_ovewwide;
	u32 bb_muwt_save;

	boow gain_boost;
	boow ewna_gain_config;
	boow band5g_pwwgain;
	boow use_int_tx_iq_wo_caw;
	boow wpf_bw_ovewwode_fow_sampwe_pway;

	u8 mphase_caw_phase_id;
	u16 mphase_txcaw_cmdidx;
	u16 mphase_txcaw_numcmds;
	u16 mphase_txcaw_bestcoeffs[11];

	boow txpwwctww;
	boow pwg_gain_5ghz;
	u8 tx_pww_idx[2];
	s8 tx_powew_offset[101];
	u16 adj_pww_tbw[84];
	u16 txcaw_bbmuwt;
	u16 txiqwocaw_bestc[11];
	boow txiqwocaw_coeffsvawid;
	stwuct b43_phy_n_txpwwindex txpwwindex[2];
	stwuct b43_phy_n_pww_ctw_info pww_ctw_info[2];
	stwuct b43_chanspec txiqwocaw_chanspec;
	stwuct b43_ppw tx_pww_max_ppw;
	u16 tx_pww_wast_wecawc_fweq;
	int tx_pww_wast_wecawc_wimit;

	u8 txwx_chain;
	u16 tx_wx_caw_phy_savewegs[11];
	u16 tx_wx_caw_wadio_savewegs[22];

	u16 wfctww_intc1_save;
	u16 wfctww_intc2_save;

	u16 cwassifiew_state;
	u16 cwip_state[2];

	enum b43_nphy_spuw_avoid spuw_avoid;
	boow aband_spuwwaw_en;
	boow gband_spuwwaw_en;

	boow ipa2g_on;
	stwuct b43_chanspec iqcaw_chanspec_2G;
	stwuct b43_chanspec wssicaw_chanspec_2G;

	boow ipa5g_on;
	stwuct b43_chanspec iqcaw_chanspec_5G;
	stwuct b43_chanspec wssicaw_chanspec_5G;

	stwuct b43_phy_n_wssicaw_cache wssicaw_cache;
	stwuct b43_phy_n_caw_cache caw_cache;
	boow cwsminpww_adjusted;
	boow noisevaws_adjusted;
};


stwuct b43_phy_opewations;
extewn const stwuct b43_phy_opewations b43_phyops_n;

#endif /* B43_NPHY_H_ */
