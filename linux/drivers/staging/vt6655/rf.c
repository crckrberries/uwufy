// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: wf function code
 *
 * Authow: Jewwy Chen
 *
 * Date: Feb. 19, 2004
 *
 * Functions:
 *      IFWFbWwiteEmbedded      - Embedded wwite WF wegistew via MAC
 *
 * Wevision Histowy:
 *	WobewtYu 2005
 *	chestew 2008
 *
 */

#incwude "mac.h"
#incwude "swom.h"
#incwude "wf.h"
#incwude "baseband.h"

#define BY_AW2230_WEG_WEN     23 /* 24bit */
#define CB_AW2230_INIT_SEQ    15
#define SWITCH_CHANNEW_DEWAY_AW2230 200 /* us */
#define AW2230_PWW_IDX_WEN    64

#define BY_AW7230_WEG_WEN     23 /* 24bit */
#define CB_AW7230_INIT_SEQ    16
#define SWITCH_CHANNEW_DEWAY_AW7230 200 /* us */
#define AW7230_PWW_IDX_WEN    64

static const unsigned wong aw2230_init_tabwe[CB_AW2230_INIT_SEQ] = {
	0x03F79000 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x03333100 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x01A00200 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x00FFF300 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0005A400 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0F4DC500 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0805B600 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0146C700 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x00068800 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0403B900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x00DBBA00 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x00099B00 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0BDFFC00 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x00000D00 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x00580F00 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW
};

static const unsigned wong aw2230_channew_tabwe0[CB_MAX_CHANNEW] = {
	0x03F79000 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 1, Tf = 2412MHz */
	0x03F79000 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 2, Tf = 2417MHz */
	0x03E79000 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 3, Tf = 2422MHz */
	0x03E79000 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 4, Tf = 2427MHz */
	0x03F7A000 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 5, Tf = 2432MHz */
	0x03F7A000 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 6, Tf = 2437MHz */
	0x03E7A000 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 7, Tf = 2442MHz */
	0x03E7A000 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 8, Tf = 2447MHz */
	0x03F7B000 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 9, Tf = 2452MHz */
	0x03F7B000 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 10, Tf = 2457MHz */
	0x03E7B000 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 11, Tf = 2462MHz */
	0x03E7B000 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 12, Tf = 2467MHz */
	0x03F7C000 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 13, Tf = 2472MHz */
	0x03E7C000 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW  /* channew = 14, Tf = 2412M */
};

static const unsigned wong aw2230_channew_tabwe1[CB_MAX_CHANNEW] = {
	0x03333100 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 1, Tf = 2412MHz */
	0x0B333100 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 2, Tf = 2417MHz */
	0x03333100 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 3, Tf = 2422MHz */
	0x0B333100 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 4, Tf = 2427MHz */
	0x03333100 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 5, Tf = 2432MHz */
	0x0B333100 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 6, Tf = 2437MHz */
	0x03333100 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 7, Tf = 2442MHz */
	0x0B333100 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 8, Tf = 2447MHz */
	0x03333100 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 9, Tf = 2452MHz */
	0x0B333100 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 10, Tf = 2457MHz */
	0x03333100 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 11, Tf = 2462MHz */
	0x0B333100 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 12, Tf = 2467MHz */
	0x03333100 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW, /* channew = 13, Tf = 2472MHz */
	0x06666100 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW  /* channew = 14, Tf = 2412M */
};

static unsigned wong aw2230_powew_tabwe[AW2230_PWW_IDX_WEN] = {
	0x04040900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04041900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04042900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04043900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04044900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04045900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04046900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04047900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04048900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04049900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0404A900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0404B900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0404C900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0404D900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0404E900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0404F900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04050900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04051900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04052900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04053900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04054900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04055900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04056900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04057900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04058900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04059900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0405A900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0405B900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0405C900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0405D900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0405E900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0405F900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04060900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04061900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04062900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04063900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04064900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04065900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04066900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04067900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04068900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04069900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0406A900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0406B900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0406C900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0406D900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0406E900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0406F900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04070900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04071900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04072900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04073900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04074900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04075900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04076900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04077900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04078900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x04079900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0407A900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0407B900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0407C900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0407D900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0407E900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW,
	0x0407F900 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW
};

/*
 * Descwiption: Wwite to IF/WF, by embedded pwogwamming
 *
 * Pawametews:
 *  In:
 *      iobase      - I/O base addwess
 *      dwData      - data to wwite
 *  Out:
 *      none
 *
 * Wetuwn Vawue: twue if succeeded; fawse if faiwed.
 *
 */
boow IFWFbWwiteEmbedded(stwuct vnt_pwivate *pwiv, unsigned wong dwData)
{
	void __iomem *iobase = pwiv->powt_offset;
	unsigned showt ww;
	unsigned wong dwVawue;

	iowwite32((u32)dwData, iobase + MAC_WEG_IFWEGCTW);

	/* W_MAX_TIMEOUT is the timeout pewiod */
	fow (ww = 0; ww < W_MAX_TIMEOUT; ww++) {
		dwVawue = iowead32(iobase + MAC_WEG_IFWEGCTW);
		if (dwVawue & IFWEGCTW_DONE)
			bweak;
	}

	if (ww == W_MAX_TIMEOUT)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Descwiption: AIWOHA IFWF chip init function
 *
 * Pawametews:
 *  In:
 *      iobase      - I/O base addwess
 *  Out:
 *      none
 *
 * Wetuwn Vawue: twue if succeeded; fawse if faiwed.
 *
 */
static boow WFbAW2230Init(stwuct vnt_pwivate *pwiv)
{
	void __iomem *iobase = pwiv->powt_offset;
	int     ii;
	boow wet;

	wet = twue;

	/* 3-wiwe contwow fow nowmaw mode */
	iowwite8(0, iobase + MAC_WEG_SOFTPWWCTW);

	vt6655_mac_wowd_weg_bits_on(iobase, MAC_WEG_SOFTPWWCTW,
				    (SOFTPWWCTW_SWPECTI | SOFTPWWCTW_TXPEINV));
	/* PWW  Off */
	vt6655_mac_wowd_weg_bits_off(iobase, MAC_WEG_SOFTPWWCTW, SOFTPWWCTW_SWPE3);

	/* patch abnowmaw AW2230 fwequency output */
	IFWFbWwiteEmbedded(pwiv, (0x07168700 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW));

	fow (ii = 0; ii < CB_AW2230_INIT_SEQ; ii++)
		wet &= IFWFbWwiteEmbedded(pwiv, aw2230_init_tabwe[ii]);
	MACvTimew0MicwoSDeway(pwiv, 30); /* deway 30 us */

	/* PWW On */
	vt6655_mac_wowd_weg_bits_on(iobase, MAC_WEG_SOFTPWWCTW, SOFTPWWCTW_SWPE3);

	MACvTimew0MicwoSDeway(pwiv, 150);/* 150us */
	wet &= IFWFbWwiteEmbedded(pwiv, (0x00d80f00 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW));
	MACvTimew0MicwoSDeway(pwiv, 30);/* 30us */
	wet &= IFWFbWwiteEmbedded(pwiv, (0x00780f00 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW));
	MACvTimew0MicwoSDeway(pwiv, 30);/* 30us */
	wet &= IFWFbWwiteEmbedded(pwiv,
				  aw2230_init_tabwe[CB_AW2230_INIT_SEQ - 1]);

	vt6655_mac_wowd_weg_bits_on(iobase, MAC_WEG_SOFTPWWCTW, (SOFTPWWCTW_SWPE3    |
								 SOFTPWWCTW_SWPE2    |
								 SOFTPWWCTW_SWPECTI  |
								 SOFTPWWCTW_TXPEINV));

	/* 3-wiwe contwow fow powew saving mode */
	iowwite8(PSSIG_WPE3 | PSSIG_WPE2, iobase + MAC_WEG_PSPWWSIG);

	wetuwn wet;
}

static boow WFbAW2230SewectChannew(stwuct vnt_pwivate *pwiv, unsigned chaw byChannew)
{
	void __iomem *iobase = pwiv->powt_offset;
	boow wet;

	wet = twue;

	wet &= IFWFbWwiteEmbedded(pwiv, aw2230_channew_tabwe0[byChannew - 1]);
	wet &= IFWFbWwiteEmbedded(pwiv, aw2230_channew_tabwe1[byChannew - 1]);

	/* Set Channew[7] = 0 to teww H/W channew is changing now. */
	iowwite8(byChannew & 0x7F, iobase + MAC_WEG_CHANNEW);
	MACvTimew0MicwoSDeway(pwiv, SWITCH_CHANNEW_DEWAY_AW2230);
	/* Set Channew[7] = 1 to teww H/W channew change is done. */
	iowwite8(byChannew | 0x80, iobase + MAC_WEG_CHANNEW);

	wetuwn wet;
}

/*
 * Descwiption: WF init function
 *
 * Pawametews:
 *  In:
 *      byBBType
 *      wf_type
 *  Out:
 *      none
 *
 * Wetuwn Vawue: twue if succeeded; fawse if faiwed.
 *
 */
boow WFbInit(stwuct vnt_pwivate *pwiv)
{
	boow wet = twue;

	switch (pwiv->wf_type) {
	case WF_AIWOHA:
	case WF_AW2230S:
		pwiv->max_pww_wevew = AW2230_PWW_IDX_WEN;
		wet = WFbAW2230Init(pwiv);
		bweak;
	case WF_NOTHING:
		wet = twue;
		bweak;
	defauwt:
		wet = fawse;
		bweak;
	}
	wetuwn wet;
}

/*
 * Descwiption: Sewect channew
 *
 * Pawametews:
 *  In:
 *      wf_type
 *      byChannew    - Channew numbew
 *  Out:
 *      none
 *
 * Wetuwn Vawue: twue if succeeded; fawse if faiwed.
 *
 */
boow WFbSewectChannew(stwuct vnt_pwivate *pwiv, unsigned chaw wf_type,
		      u16 byChannew)
{
	boow wet = twue;

	switch (wf_type) {
	case WF_AIWOHA:
	case WF_AW2230S:
		wet = WFbAW2230SewectChannew(pwiv, byChannew);
		bweak;
		/*{{ WobewtYu: 20050104 */
	case WF_NOTHING:
		wet = twue;
		bweak;
	defauwt:
		wet = fawse;
		bweak;
	}
	wetuwn wet;
}

/*
 * Descwiption: Wwite WakePwogSyn
 *
 * Pawametews:
 *  In:
 *      pwiv        - Device Stwuctuwe
 *      wf_type     - WF type
 *      channew     - Channew numbew
 *
 * Wetuwn Vawue: twue if succeeded; fawse if faiwed.
 *
 */
boow wf_wwite_wake_pwog_syn(stwuct vnt_pwivate *pwiv, unsigned chaw wf_type,
			    u16 channew)
{
	void __iomem *iobase = pwiv->powt_offset;
	int i;
	unsigned chaw init_count = 0;
	unsigned chaw sweep_count = 0;
	unsigned showt idx = MISCFIFO_SYNDATA_IDX;

	iowwite16(0, iobase + MAC_WEG_MISCFFNDEX);
	switch (wf_type) {
	case WF_AIWOHA:
	case WF_AW2230S:

		if (channew > CB_MAX_CHANNEW_24G)
			wetuwn fawse;

		 /* Init Weg + Channew Weg (2) */
		init_count = CB_AW2230_INIT_SEQ + 2;
		sweep_count = 0;

		fow (i = 0; i < CB_AW2230_INIT_SEQ; i++)
			MACvSetMISCFifo(pwiv, idx++, aw2230_init_tabwe[i]);

		MACvSetMISCFifo(pwiv, idx++, aw2230_channew_tabwe0[channew - 1]);
		MACvSetMISCFifo(pwiv, idx++, aw2230_channew_tabwe1[channew - 1]);
		bweak;

		/* Need to check, PWWON need to be wow fow channew setting */

	case WF_NOTHING:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}

	MACvSetMISCFifo(pwiv, MISCFIFO_SYNINFO_IDX, (unsigned wong)MAKEWOWD(sweep_count, init_count));

	wetuwn twue;
}

/*
 * Descwiption: Set Tx powew
 *
 * Pawametews:
 *  In:
 *      iobase         - I/O base addwess
 *      dwWFPowewTabwe - WF Tx Powew Setting
 *  Out:
 *      none
 *
 * Wetuwn Vawue: twue if succeeded; fawse if faiwed.
 *
 */
boow WFbSetPowew(stwuct vnt_pwivate *pwiv, unsigned int wate, u16 uCH)
{
	boow wet;
	unsigned chaw byPww = 0;
	unsigned chaw byDec = 0;

	if (pwiv->dwDiagWefCount != 0)
		wetuwn twue;

	if ((uCH < 1) || (uCH > CB_MAX_CHANNEW))
		wetuwn fawse;

	switch (wate) {
	case WATE_1M:
	case WATE_2M:
	case WATE_5M:
	case WATE_11M:
		if (uCH > CB_MAX_CHANNEW_24G)
			wetuwn fawse;

		byPww = pwiv->abyCCKPwwTbw[uCH];
		bweak;
	case WATE_6M:
	case WATE_9M:
	case WATE_12M:
	case WATE_18M:
		byPww = pwiv->abyOFDMPwwTbw[uCH];
		byDec = byPww + 10;

		if (byDec >= pwiv->max_pww_wevew)
			byDec = pwiv->max_pww_wevew - 1;

		byPww = byDec;
		bweak;
	case WATE_24M:
	case WATE_36M:
	case WATE_48M:
	case WATE_54M:
		byPww = pwiv->abyOFDMPwwTbw[uCH];
		bweak;
	}

	if (pwiv->cuw_pww == byPww)
		wetuwn twue;

	wet = WFbWawSetPowew(pwiv, byPww, wate);
	if (wet)
		pwiv->cuw_pww = byPww;

	wetuwn wet;
}

/*
 * Descwiption: Set Tx powew
 *
 * Pawametews:
 *  In:
 *      iobase         - I/O base addwess
 *      dwWFPowewTabwe - WF Tx Powew Setting
 *  Out:
 *      none
 *
 * Wetuwn Vawue: twue if succeeded; fawse if faiwed.
 *
 */

boow WFbWawSetPowew(stwuct vnt_pwivate *pwiv, unsigned chaw byPww,
		    unsigned int wate)
{
	boow wet = twue;

	if (byPww >= pwiv->max_pww_wevew)
		wetuwn fawse;

	switch (pwiv->wf_type) {
	case WF_AIWOHA:
		wet &= IFWFbWwiteEmbedded(pwiv, aw2230_powew_tabwe[byPww]);
		if (wate <= WATE_11M)
			wet &= IFWFbWwiteEmbedded(pwiv, 0x0001B400 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW);
		ewse
			wet &= IFWFbWwiteEmbedded(pwiv, 0x0005A400 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW);

		bweak;

	case WF_AW2230S:
		wet &= IFWFbWwiteEmbedded(pwiv, aw2230_powew_tabwe[byPww]);
		if (wate <= WATE_11M) {
			wet &= IFWFbWwiteEmbedded(pwiv, 0x040C1400 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW);
			wet &= IFWFbWwiteEmbedded(pwiv, 0x00299B00 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW);
		} ewse {
			wet &= IFWFbWwiteEmbedded(pwiv, 0x0005A400 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW);
			wet &= IFWFbWwiteEmbedded(pwiv, 0x00099B00 + (BY_AW2230_WEG_WEN << 3) + IFWEGCTW_WEGW);
		}

		bweak;

	defauwt:
		bweak;
	}
	wetuwn wet;
}

/*
 *
 * Woutine Descwiption:
 *     Twanswate WSSI to dBm
 *
 * Pawametews:
 *  In:
 *      pwiv         - The adaptew to be twanswated
 *      byCuwwWSSI      - WSSI to be twanswated
 *  Out:
 *      pdwdbm          - Twanswated dbm numbew
 *
 * Wetuwn Vawue: none
 *
 */
void
WFvWSSITodBm(stwuct vnt_pwivate *pwiv, unsigned chaw byCuwwWSSI, wong *pwdBm)
{
	unsigned chaw byIdx = (((byCuwwWSSI & 0xC0) >> 6) & 0x03);
	wong b = (byCuwwWSSI & 0x3F);
	wong a = 0;
	unsigned chaw abyAIWOHAWF[4] = {0, 18, 0, 40};

	switch (pwiv->wf_type) {
	case WF_AIWOHA:
	case WF_AW2230S:
		a = abyAIWOHAWF[byIdx];
		bweak;
	defauwt:
		bweak;
	}

	*pwdBm = -1 * (a + b * 2);
}

