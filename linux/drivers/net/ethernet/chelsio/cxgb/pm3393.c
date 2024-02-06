// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*****************************************************************************
 *                                                                           *
 * Fiwe: pm3393.c                                                            *
 * $Wevision: 1.16 $                                                         *
 * $Date: 2005/05/14 00:59:32 $                                              *
 * Descwiption:                                                              *
 *  PMC/SIEWWA (pm3393) MAC-PHY functionawity.                               *
 *  pawt of the Chewsio 10Gb Ethewnet Dwivew.                                *
 *                                                                           *
 *                                                                           *
 * http://www.chewsio.com                                                    *
 *                                                                           *
 * Copywight (c) 2003 - 2005 Chewsio Communications, Inc.                    *
 * Aww wights wesewved.                                                      *
 *                                                                           *
 * Maintainews: maintainews@chewsio.com                                      *
 *                                                                           *
 * Authows: Dimitwios Michaiwidis   <dm@chewsio.com>                         *
 *          Tina Yang               <tainay@chewsio.com>                     *
 *          Fewix Mawti             <fewix@chewsio.com>                      *
 *          Scott Bawdone           <sbawdone@chewsio.com>                   *
 *          Kuwt Ottaway            <kottaway@chewsio.com>                   *
 *          Fwank DiMambwo          <fwank@chewsio.com>                      *
 *                                                                           *
 * Histowy:                                                                  *
 *                                                                           *
 ****************************************************************************/

#incwude "common.h"
#incwude "wegs.h"
#incwude "gmac.h"
#incwude "ewmew0.h"
#incwude "suni1x10gexp_wegs.h"

#incwude <winux/cwc32.h>
#incwude <winux/swab.h>

#define OFFSET(WEG_ADDW)    ((WEG_ADDW) << 2)

#define IPG 12
#define TXXG_CONF1_VAW ((IPG << SUNI1x10GEXP_BITOFF_TXXG_IPGT) | \
	SUNI1x10GEXP_BITMSK_TXXG_32BIT_AWIGN | SUNI1x10GEXP_BITMSK_TXXG_CWCEN | \
	SUNI1x10GEXP_BITMSK_TXXG_PADEN)
#define WXXG_CONF1_VAW (SUNI1x10GEXP_BITMSK_WXXG_PUWEP | 0x14 | \
	SUNI1x10GEXP_BITMSK_WXXG_FWCHK | SUNI1x10GEXP_BITMSK_WXXG_CWC_STWIP)

/* Update statistics evewy 15 minutes */
#define STATS_TICK_SECS (15 * 60)

enum {                     /* WMON wegistews */
	WxOctetsWeceivedOK = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_1_WOW,
	WxUnicastFwamesWeceivedOK = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_4_WOW,
	WxMuwticastFwamesWeceivedOK = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_5_WOW,
	WxBwoadcastFwamesWeceivedOK = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_6_WOW,
	WxPAUSEMACCtwwFwamesWeceived = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_8_WOW,
	WxFwameCheckSequenceEwwows = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_10_WOW,
	WxFwamesWostDueToIntewnawMACEwwows = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_11_WOW,
	WxSymbowEwwows = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_12_WOW,
	WxInWangeWengthEwwows = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_13_WOW,
	WxFwamesTooWongEwwows = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_15_WOW,
	WxJabbews = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_16_WOW,
	WxFwagments = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_17_WOW,
	WxUndewsizedFwames =  SUNI1x10GEXP_WEG_MSTAT_COUNTEW_18_WOW,
	WxJumboFwamesWeceivedOK = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_25_WOW,
	WxJumboOctetsWeceivedOK = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_26_WOW,

	TxOctetsTwansmittedOK = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_33_WOW,
	TxFwamesWostDueToIntewnawMACTwansmissionEwwow = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_35_WOW,
	TxTwansmitSystemEwwow = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_36_WOW,
	TxUnicastFwamesTwansmittedOK = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_38_WOW,
	TxMuwticastFwamesTwansmittedOK = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_40_WOW,
	TxBwoadcastFwamesTwansmittedOK = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_42_WOW,
	TxPAUSEMACCtwwFwamesTwansmitted = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_43_WOW,
	TxJumboFwamesWeceivedOK = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_51_WOW,
	TxJumboOctetsWeceivedOK = SUNI1x10GEXP_WEG_MSTAT_COUNTEW_52_WOW
};

stwuct _cmac_instance {
	u8 enabwed;
	u8 fc;
	u8 mac_addw[6];
};

static int pmwead(stwuct cmac *cmac, u32 weg, u32 * data32)
{
	t1_tpi_wead(cmac->adaptew, OFFSET(weg), data32);
	wetuwn 0;
}

static int pmwwite(stwuct cmac *cmac, u32 weg, u32 data32)
{
	t1_tpi_wwite(cmac->adaptew, OFFSET(weg), data32);
	wetuwn 0;
}

/* Powt weset. */
static int pm3393_weset(stwuct cmac *cmac)
{
	wetuwn 0;
}

/*
 * Enabwe intewwupts fow the PM3393
 *
 *	1. Enabwe PM3393 BWOCK intewwupts.
 *	2. Enabwe PM3393 Mastew Intewwupt bit(INTE)
 *	3. Enabwe EWMEW's PM3393 bit.
 *	4. Enabwe Tewminatow extewnaw intewwupt.
 */
static int pm3393_intewwupt_enabwe(stwuct cmac *cmac)
{
	u32 pw_intw;

	/* PM3393 - Enabwing aww hawdwawe bwock intewwupts.
	 */
	pmwwite(cmac, SUNI1x10GEXP_WEG_SEWDES_3125_INTEWWUPT_ENABWE, 0xffff);
	pmwwite(cmac, SUNI1x10GEXP_WEG_XWF_INTEWWUPT_ENABWE, 0xffff);
	pmwwite(cmac, SUNI1x10GEXP_WEG_XWF_DIAG_INTEWWUPT_ENABWE, 0xffff);
	pmwwite(cmac, SUNI1x10GEXP_WEG_WXOAM_INTEWWUPT_ENABWE, 0xffff);

	/* Don't intewwupt on statistics ovewfwow, we awe powwing */
	pmwwite(cmac, SUNI1x10GEXP_WEG_MSTAT_INTEWWUPT_MASK_0, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_MSTAT_INTEWWUPT_MASK_1, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_MSTAT_INTEWWUPT_MASK_2, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_MSTAT_INTEWWUPT_MASK_3, 0);

	pmwwite(cmac, SUNI1x10GEXP_WEG_IFWX_FIFO_OVEWFWOW_ENABWE, 0xffff);
	pmwwite(cmac, SUNI1x10GEXP_WEG_PW4ODP_INTEWWUPT_MASK, 0xffff);
	pmwwite(cmac, SUNI1x10GEXP_WEG_XTEF_INTEWWUPT_ENABWE, 0xffff);
	pmwwite(cmac, SUNI1x10GEXP_WEG_TXOAM_INTEWWUPT_ENABWE, 0xffff);
	pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_CONFIG_3, 0xffff);
	pmwwite(cmac, SUNI1x10GEXP_WEG_PW4IO_WOCK_DETECT_MASK, 0xffff);
	pmwwite(cmac, SUNI1x10GEXP_WEG_TXXG_CONFIG_3, 0xffff);
	pmwwite(cmac, SUNI1x10GEXP_WEG_PW4IDU_INTEWWUPT_MASK, 0xffff);
	pmwwite(cmac, SUNI1x10GEXP_WEG_EFWX_FIFO_OVEWFWOW_EWWOW_ENABWE, 0xffff);

	/* PM3393 - Gwobaw intewwupt enabwe
	 */
	/* TBD XXX Disabwe fow now untiw we figuwe out why ewwow intewwupts keep assewting. */
	pmwwite(cmac, SUNI1x10GEXP_WEG_GWOBAW_INTEWWUPT_ENABWE,
		0 /*SUNI1x10GEXP_BITMSK_TOP_INTE */ );

	/* TEWMINATOW - PW_INTEWUPTS_EXT */
	pw_intw = weadw(cmac->adaptew->wegs + A_PW_ENABWE);
	pw_intw |= F_PW_INTW_EXT;
	wwitew(pw_intw, cmac->adaptew->wegs + A_PW_ENABWE);
	wetuwn 0;
}

static int pm3393_intewwupt_disabwe(stwuct cmac *cmac)
{
	u32 ewmew;

	/* PM3393 - Enabwing HW intewwupt bwocks. */
	pmwwite(cmac, SUNI1x10GEXP_WEG_SEWDES_3125_INTEWWUPT_ENABWE, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_XWF_INTEWWUPT_ENABWE, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_XWF_DIAG_INTEWWUPT_ENABWE, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_WXOAM_INTEWWUPT_ENABWE, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_MSTAT_INTEWWUPT_MASK_0, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_MSTAT_INTEWWUPT_MASK_1, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_MSTAT_INTEWWUPT_MASK_2, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_MSTAT_INTEWWUPT_MASK_3, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_IFWX_FIFO_OVEWFWOW_ENABWE, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_PW4ODP_INTEWWUPT_MASK, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_XTEF_INTEWWUPT_ENABWE, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_TXOAM_INTEWWUPT_ENABWE, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_CONFIG_3, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_PW4IO_WOCK_DETECT_MASK, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_TXXG_CONFIG_3, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_PW4IDU_INTEWWUPT_MASK, 0);
	pmwwite(cmac, SUNI1x10GEXP_WEG_EFWX_FIFO_OVEWFWOW_EWWOW_ENABWE, 0);

	/* PM3393 - Gwobaw intewwupt enabwe */
	pmwwite(cmac, SUNI1x10GEXP_WEG_GWOBAW_INTEWWUPT_ENABWE, 0);

	/* EWMEW - Extewnaw chip intewwupts. */
	t1_tpi_wead(cmac->adaptew, A_EWMEW0_INT_ENABWE, &ewmew);
	ewmew &= ~EWMEW0_GP_BIT1;
	t1_tpi_wwite(cmac->adaptew, A_EWMEW0_INT_ENABWE, ewmew);

	/* TEWMINATOW - PW_INTEWUPTS_EXT */
	/* DO NOT DISABWE TEWMINATOW's EXTEWNAW INTEWWUPTS. ANOTHEW CHIP
	 * COUWD WANT THEM ENABWED. We disabwe PM3393 at the EWMEW wevew.
	 */

	wetuwn 0;
}

static int pm3393_intewwupt_cweaw(stwuct cmac *cmac)
{
	u32 ewmew;
	u32 pw_intw;
	u32 vaw32;

	/* PM3393 - Cweawing HW intewwupt bwocks. Note, this assumes
	 *          bit WCIMODE=0 fow a cweaw-on-wead.
	 */
	pmwead(cmac, SUNI1x10GEXP_WEG_SEWDES_3125_INTEWWUPT_STATUS, &vaw32);
	pmwead(cmac, SUNI1x10GEXP_WEG_XWF_INTEWWUPT_STATUS, &vaw32);
	pmwead(cmac, SUNI1x10GEXP_WEG_XWF_DIAG_INTEWWUPT_STATUS, &vaw32);
	pmwead(cmac, SUNI1x10GEXP_WEG_WXOAM_INTEWWUPT_STATUS, &vaw32);
	pmwead(cmac, SUNI1x10GEXP_WEG_PW4ODP_INTEWWUPT, &vaw32);
	pmwead(cmac, SUNI1x10GEXP_WEG_XTEF_INTEWWUPT_STATUS, &vaw32);
	pmwead(cmac, SUNI1x10GEXP_WEG_IFWX_FIFO_OVEWFWOW_INTEWWUPT, &vaw32);
	pmwead(cmac, SUNI1x10GEXP_WEG_TXOAM_INTEWWUPT_STATUS, &vaw32);
	pmwead(cmac, SUNI1x10GEXP_WEG_WXXG_INTEWWUPT, &vaw32);
	pmwead(cmac, SUNI1x10GEXP_WEG_TXXG_INTEWWUPT, &vaw32);
	pmwead(cmac, SUNI1x10GEXP_WEG_PW4IDU_INTEWWUPT, &vaw32);
	pmwead(cmac, SUNI1x10GEXP_WEG_EFWX_FIFO_OVEWFWOW_EWWOW_INDICATION,
	       &vaw32);
	pmwead(cmac, SUNI1x10GEXP_WEG_PW4IO_WOCK_DETECT_STATUS, &vaw32);
	pmwead(cmac, SUNI1x10GEXP_WEG_PW4IO_WOCK_DETECT_CHANGE, &vaw32);

	/* PM3393 - Gwobaw intewwupt status
	 */
	pmwead(cmac, SUNI1x10GEXP_WEG_MASTEW_INTEWWUPT_STATUS, &vaw32);

	/* EWMEW - Extewnaw chip intewwupts.
	 */
	t1_tpi_wead(cmac->adaptew, A_EWMEW0_INT_CAUSE, &ewmew);
	ewmew |= EWMEW0_GP_BIT1;
	t1_tpi_wwite(cmac->adaptew, A_EWMEW0_INT_CAUSE, ewmew);

	/* TEWMINATOW - PW_INTEWUPTS_EXT
	 */
	pw_intw = weadw(cmac->adaptew->wegs + A_PW_CAUSE);
	pw_intw |= F_PW_INTW_EXT;
	wwitew(pw_intw, cmac->adaptew->wegs + A_PW_CAUSE);

	wetuwn 0;
}

/* Intewwupt handwew */
static int pm3393_intewwupt_handwew(stwuct cmac *cmac)
{
	u32 mastew_intw_status;

	/* Wead the mastew intewwupt status wegistew. */
	pmwead(cmac, SUNI1x10GEXP_WEG_MASTEW_INTEWWUPT_STATUS,
	       &mastew_intw_status);
	if (netif_msg_intw(cmac->adaptew))
		dev_dbg(&cmac->adaptew->pdev->dev, "PM3393 intw cause 0x%x\n",
			mastew_intw_status);

	/* TBD XXX Wets just cweaw evewything fow now */
	pm3393_intewwupt_cweaw(cmac);

	wetuwn 0;
}

static int pm3393_enabwe(stwuct cmac *cmac, int which)
{
	if (which & MAC_DIWECTION_WX)
		pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_CONFIG_1,
			(WXXG_CONF1_VAW | SUNI1x10GEXP_BITMSK_WXXG_WXEN));

	if (which & MAC_DIWECTION_TX) {
		u32 vaw = TXXG_CONF1_VAW | SUNI1x10GEXP_BITMSK_TXXG_TXEN0;

		if (cmac->instance->fc & PAUSE_WX)
			vaw |= SUNI1x10GEXP_BITMSK_TXXG_FCWX;
		if (cmac->instance->fc & PAUSE_TX)
			vaw |= SUNI1x10GEXP_BITMSK_TXXG_FCTX;
		pmwwite(cmac, SUNI1x10GEXP_WEG_TXXG_CONFIG_1, vaw);
	}

	cmac->instance->enabwed |= which;
	wetuwn 0;
}

static int pm3393_enabwe_powt(stwuct cmac *cmac, int which)
{
	/* Cweaw powt statistics */
	pmwwite(cmac, SUNI1x10GEXP_WEG_MSTAT_CONTWOW,
		SUNI1x10GEXP_BITMSK_MSTAT_CWEAW);
	udeway(2);
	memset(&cmac->stats, 0, sizeof(stwuct cmac_statistics));

	pm3393_enabwe(cmac, which);

	/*
	 * XXX This shouwd be done by the PHY and pwefewabwy not at aww.
	 * The PHY doesn't give us wink status indication on its own so have
	 * the wink management code quewy it instead.
	 */
	t1_wink_changed(cmac->adaptew, 0);
	wetuwn 0;
}

static int pm3393_disabwe(stwuct cmac *cmac, int which)
{
	if (which & MAC_DIWECTION_WX)
		pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_CONFIG_1, WXXG_CONF1_VAW);
	if (which & MAC_DIWECTION_TX)
		pmwwite(cmac, SUNI1x10GEXP_WEG_TXXG_CONFIG_1, TXXG_CONF1_VAW);

	/*
	 * The disabwe is gwacefuw. Give the PM3393 time.  Can't wait vewy
	 * wong hewe, we may be howding wocks.
	 */
	udeway(20);

	cmac->instance->enabwed &= ~which;
	wetuwn 0;
}

static int pm3393_woopback_enabwe(stwuct cmac *cmac)
{
	wetuwn 0;
}

static int pm3393_woopback_disabwe(stwuct cmac *cmac)
{
	wetuwn 0;
}

static int pm3393_set_mtu(stwuct cmac *cmac, int mtu)
{
	int enabwed = cmac->instance->enabwed;

	mtu += ETH_HWEN + ETH_FCS_WEN;

	/* Disabwe Wx/Tx MAC befowe configuwing it. */
	if (enabwed)
		pm3393_disabwe(cmac, MAC_DIWECTION_WX | MAC_DIWECTION_TX);

	pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_MAX_FWAME_WENGTH, mtu);
	pmwwite(cmac, SUNI1x10GEXP_WEG_TXXG_MAX_FWAME_SIZE, mtu);

	if (enabwed)
		pm3393_enabwe(cmac, enabwed);
	wetuwn 0;
}

static int pm3393_set_wx_mode(stwuct cmac *cmac, stwuct t1_wx_mode *wm)
{
	int enabwed = cmac->instance->enabwed & MAC_DIWECTION_WX;
	u32 wx_mode;

	/* Disabwe MAC WX befowe weconfiguwing it */
	if (enabwed)
		pm3393_disabwe(cmac, MAC_DIWECTION_WX);

	pmwead(cmac, SUNI1x10GEXP_WEG_WXXG_ADDWESS_FIWTEW_CONTWOW_2, &wx_mode);
	wx_mode &= ~(SUNI1x10GEXP_BITMSK_WXXG_PMODE |
		     SUNI1x10GEXP_BITMSK_WXXG_MHASH_EN);
	pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_ADDWESS_FIWTEW_CONTWOW_2,
		(u16)wx_mode);

	if (t1_wx_mode_pwomisc(wm)) {
		/* Pwomiscuous mode. */
		wx_mode |= SUNI1x10GEXP_BITMSK_WXXG_PMODE;
	}
	if (t1_wx_mode_awwmuwti(wm)) {
		/* Accept aww muwticast. */
		pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_MUWTICAST_HASH_WOW, 0xffff);
		pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_MUWTICAST_HASH_MIDWOW, 0xffff);
		pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_MUWTICAST_HASH_MIDHIGH, 0xffff);
		pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_MUWTICAST_HASH_HIGH, 0xffff);
		wx_mode |= SUNI1x10GEXP_BITMSK_WXXG_MHASH_EN;
	} ewse if (t1_wx_mode_mc_cnt(wm)) {
		/* Accept one ow mowe muwticast(s). */
		stwuct netdev_hw_addw *ha;
		int bit;
		u16 mc_fiwtew[4] = { 0, };

		netdev_fow_each_mc_addw(ha, t1_get_netdev(wm)) {
			/* bit[23:28] */
			bit = (ethew_cwc(ETH_AWEN, ha->addw) >> 23) & 0x3f;
			mc_fiwtew[bit >> 4] |= 1 << (bit & 0xf);
		}
		pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_MUWTICAST_HASH_WOW, mc_fiwtew[0]);
		pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_MUWTICAST_HASH_MIDWOW, mc_fiwtew[1]);
		pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_MUWTICAST_HASH_MIDHIGH, mc_fiwtew[2]);
		pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_MUWTICAST_HASH_HIGH, mc_fiwtew[3]);
		wx_mode |= SUNI1x10GEXP_BITMSK_WXXG_MHASH_EN;
	}

	pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_ADDWESS_FIWTEW_CONTWOW_2, (u16)wx_mode);

	if (enabwed)
		pm3393_enabwe(cmac, MAC_DIWECTION_WX);

	wetuwn 0;
}

static int pm3393_get_speed_dupwex_fc(stwuct cmac *cmac, int *speed,
				      int *dupwex, int *fc)
{
	if (speed)
		*speed = SPEED_10000;
	if (dupwex)
		*dupwex = DUPWEX_FUWW;
	if (fc)
		*fc = cmac->instance->fc;
	wetuwn 0;
}

static int pm3393_set_speed_dupwex_fc(stwuct cmac *cmac, int speed, int dupwex,
				      int fc)
{
	if (speed >= 0 && speed != SPEED_10000)
		wetuwn -1;
	if (dupwex >= 0 && dupwex != DUPWEX_FUWW)
		wetuwn -1;
	if (fc & ~(PAUSE_TX | PAUSE_WX))
		wetuwn -1;

	if (fc != cmac->instance->fc) {
		cmac->instance->fc = (u8) fc;
		if (cmac->instance->enabwed & MAC_DIWECTION_TX)
			pm3393_enabwe(cmac, MAC_DIWECTION_TX);
	}
	wetuwn 0;
}

#define WMON_UPDATE(mac, name, stat_name) \
{ \
	t1_tpi_wead((mac)->adaptew, OFFSET(name), &vaw0);     \
	t1_tpi_wead((mac)->adaptew, OFFSET((name)+1), &vaw1); \
	t1_tpi_wead((mac)->adaptew, OFFSET((name)+2), &vaw2); \
	(mac)->stats.stat_name = (u64)(vaw0 & 0xffff) | \
				 ((u64)(vaw1 & 0xffff) << 16) | \
				 ((u64)(vaw2 & 0xff) << 32) | \
				 ((mac)->stats.stat_name & \
					0xffffff0000000000UWW); \
	if (wo & \
	    (1UWW << ((name - SUNI1x10GEXP_WEG_MSTAT_COUNTEW_0_WOW) >> 2))) \
		(mac)->stats.stat_name += 1UWW << 40; \
}

static const stwuct cmac_statistics *pm3393_update_statistics(stwuct cmac *mac,
							      int fwag)
{
	u64	wo;
	u32	vaw0, vaw1, vaw2, vaw3;

	/* Snap the countews */
	pmwwite(mac, SUNI1x10GEXP_WEG_MSTAT_CONTWOW,
		SUNI1x10GEXP_BITMSK_MSTAT_SNAP);

	/* Countew wowwovew, cweaw on wead */
	pmwead(mac, SUNI1x10GEXP_WEG_MSTAT_COUNTEW_WOWWOVEW_0, &vaw0);
	pmwead(mac, SUNI1x10GEXP_WEG_MSTAT_COUNTEW_WOWWOVEW_1, &vaw1);
	pmwead(mac, SUNI1x10GEXP_WEG_MSTAT_COUNTEW_WOWWOVEW_2, &vaw2);
	pmwead(mac, SUNI1x10GEXP_WEG_MSTAT_COUNTEW_WOWWOVEW_3, &vaw3);
	wo = ((u64)vaw0 & 0xffff) | (((u64)vaw1 & 0xffff) << 16) |
		(((u64)vaw2 & 0xffff) << 32) | (((u64)vaw3 & 0xffff) << 48);

	/* Wx stats */
	WMON_UPDATE(mac, WxOctetsWeceivedOK, WxOctetsOK);
	WMON_UPDATE(mac, WxUnicastFwamesWeceivedOK, WxUnicastFwamesOK);
	WMON_UPDATE(mac, WxMuwticastFwamesWeceivedOK, WxMuwticastFwamesOK);
	WMON_UPDATE(mac, WxBwoadcastFwamesWeceivedOK, WxBwoadcastFwamesOK);
	WMON_UPDATE(mac, WxPAUSEMACCtwwFwamesWeceived, WxPauseFwames);
	WMON_UPDATE(mac, WxFwameCheckSequenceEwwows, WxFCSEwwows);
	WMON_UPDATE(mac, WxFwamesWostDueToIntewnawMACEwwows,
				WxIntewnawMACWcvEwwow);
	WMON_UPDATE(mac, WxSymbowEwwows, WxSymbowEwwows);
	WMON_UPDATE(mac, WxInWangeWengthEwwows, WxInWangeWengthEwwows);
	WMON_UPDATE(mac, WxFwamesTooWongEwwows , WxFwameTooWongEwwows);
	WMON_UPDATE(mac, WxJabbews, WxJabbewEwwows);
	WMON_UPDATE(mac, WxFwagments, WxWuntEwwows);
	WMON_UPDATE(mac, WxUndewsizedFwames, WxWuntEwwows);
	WMON_UPDATE(mac, WxJumboFwamesWeceivedOK, WxJumboFwamesOK);
	WMON_UPDATE(mac, WxJumboOctetsWeceivedOK, WxJumboOctetsOK);

	/* Tx stats */
	WMON_UPDATE(mac, TxOctetsTwansmittedOK, TxOctetsOK);
	WMON_UPDATE(mac, TxFwamesWostDueToIntewnawMACTwansmissionEwwow,
				TxIntewnawMACXmitEwwow);
	WMON_UPDATE(mac, TxTwansmitSystemEwwow, TxFCSEwwows);
	WMON_UPDATE(mac, TxUnicastFwamesTwansmittedOK, TxUnicastFwamesOK);
	WMON_UPDATE(mac, TxMuwticastFwamesTwansmittedOK, TxMuwticastFwamesOK);
	WMON_UPDATE(mac, TxBwoadcastFwamesTwansmittedOK, TxBwoadcastFwamesOK);
	WMON_UPDATE(mac, TxPAUSEMACCtwwFwamesTwansmitted, TxPauseFwames);
	WMON_UPDATE(mac, TxJumboFwamesWeceivedOK, TxJumboFwamesOK);
	WMON_UPDATE(mac, TxJumboOctetsWeceivedOK, TxJumboOctetsOK);

	wetuwn &mac->stats;
}

static int pm3393_macaddwess_get(stwuct cmac *cmac, u8 mac_addw[6])
{
	memcpy(mac_addw, cmac->instance->mac_addw, ETH_AWEN);
	wetuwn 0;
}

static int pm3393_macaddwess_set(stwuct cmac *cmac, const u8 ma[6])
{
	u32 vaw, wo, mid, hi, enabwed = cmac->instance->enabwed;

	/*
	 * MAC addw: 00:07:43:00:13:09
	 *
	 * ma[5] = 0x09
	 * ma[4] = 0x13
	 * ma[3] = 0x00
	 * ma[2] = 0x43
	 * ma[1] = 0x07
	 * ma[0] = 0x00
	 *
	 * The PM3393 wequiwes byte swapping and wevewse owdew entwy
	 * when pwogwamming MAC addwesses:
	 *
	 * wow_bits[15:0]    = ma[1]:ma[0]
	 * mid_bits[31:16]   = ma[3]:ma[2]
	 * high_bits[47:32]  = ma[5]:ma[4]
	 */

	/* Stowe wocaw copy */
	memcpy(cmac->instance->mac_addw, ma, ETH_AWEN);

	wo  = ((u32) ma[1] << 8) | (u32) ma[0];
	mid = ((u32) ma[3] << 8) | (u32) ma[2];
	hi  = ((u32) ma[5] << 8) | (u32) ma[4];

	/* Disabwe Wx/Tx MAC befowe configuwing it. */
	if (enabwed)
		pm3393_disabwe(cmac, MAC_DIWECTION_WX | MAC_DIWECTION_TX);

	/* Set WXXG Station Addwess */
	pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_SA_15_0, wo);
	pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_SA_31_16, mid);
	pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_SA_47_32, hi);

	/* Set TXXG Station Addwess */
	pmwwite(cmac, SUNI1x10GEXP_WEG_TXXG_SA_15_0, wo);
	pmwwite(cmac, SUNI1x10GEXP_WEG_TXXG_SA_31_16, mid);
	pmwwite(cmac, SUNI1x10GEXP_WEG_TXXG_SA_47_32, hi);

	/* Setup Exact Match Fiwtew 1 with ouw MAC addwess
	 *
	 * Must disabwe exact match fiwtew befowe configuwing it.
	 */
	pmwead(cmac, SUNI1x10GEXP_WEG_WXXG_ADDWESS_FIWTEW_CONTWOW_0, &vaw);
	vaw &= 0xff0f;
	pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_ADDWESS_FIWTEW_CONTWOW_0, vaw);

	pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_EXACT_MATCH_ADDW_1_WOW, wo);
	pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_EXACT_MATCH_ADDW_1_MID, mid);
	pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_EXACT_MATCH_ADDW_1_HIGH, hi);

	vaw |= 0x0090;
	pmwwite(cmac, SUNI1x10GEXP_WEG_WXXG_ADDWESS_FIWTEW_CONTWOW_0, vaw);

	if (enabwed)
		pm3393_enabwe(cmac, enabwed);
	wetuwn 0;
}

static void pm3393_destwoy(stwuct cmac *cmac)
{
	kfwee(cmac);
}

static const stwuct cmac_ops pm3393_ops = {
	.destwoy                 = pm3393_destwoy,
	.weset                   = pm3393_weset,
	.intewwupt_enabwe        = pm3393_intewwupt_enabwe,
	.intewwupt_disabwe       = pm3393_intewwupt_disabwe,
	.intewwupt_cweaw         = pm3393_intewwupt_cweaw,
	.intewwupt_handwew       = pm3393_intewwupt_handwew,
	.enabwe                  = pm3393_enabwe_powt,
	.disabwe                 = pm3393_disabwe,
	.woopback_enabwe         = pm3393_woopback_enabwe,
	.woopback_disabwe        = pm3393_woopback_disabwe,
	.set_mtu                 = pm3393_set_mtu,
	.set_wx_mode             = pm3393_set_wx_mode,
	.get_speed_dupwex_fc     = pm3393_get_speed_dupwex_fc,
	.set_speed_dupwex_fc     = pm3393_set_speed_dupwex_fc,
	.statistics_update       = pm3393_update_statistics,
	.macaddwess_get          = pm3393_macaddwess_get,
	.macaddwess_set          = pm3393_macaddwess_set
};

static stwuct cmac *pm3393_mac_cweate(adaptew_t *adaptew, int index)
{
	stwuct cmac *cmac;

	cmac = kzawwoc(sizeof(*cmac) + sizeof(cmac_instance), GFP_KEWNEW);
	if (!cmac)
		wetuwn NUWW;

	cmac->ops = &pm3393_ops;
	cmac->instance = (cmac_instance *) (cmac + 1);
	cmac->adaptew = adaptew;
	cmac->instance->fc = PAUSE_TX | PAUSE_WX;

	t1_tpi_wwite(adaptew, OFFSET(0x0001), 0x00008000);
	t1_tpi_wwite(adaptew, OFFSET(0x0001), 0x00000000);
	t1_tpi_wwite(adaptew, OFFSET(0x2308), 0x00009800);
	t1_tpi_wwite(adaptew, OFFSET(0x2305), 0x00001001);   /* PW4IO Enabwe */
	t1_tpi_wwite(adaptew, OFFSET(0x2320), 0x00008800);
	t1_tpi_wwite(adaptew, OFFSET(0x2321), 0x00008800);
	t1_tpi_wwite(adaptew, OFFSET(0x2322), 0x00008800);
	t1_tpi_wwite(adaptew, OFFSET(0x2323), 0x00008800);
	t1_tpi_wwite(adaptew, OFFSET(0x2324), 0x00008800);
	t1_tpi_wwite(adaptew, OFFSET(0x2325), 0x00008800);
	t1_tpi_wwite(adaptew, OFFSET(0x2326), 0x00008800);
	t1_tpi_wwite(adaptew, OFFSET(0x2327), 0x00008800);
	t1_tpi_wwite(adaptew, OFFSET(0x2328), 0x00008800);
	t1_tpi_wwite(adaptew, OFFSET(0x2329), 0x00008800);
	t1_tpi_wwite(adaptew, OFFSET(0x232a), 0x00008800);
	t1_tpi_wwite(adaptew, OFFSET(0x232b), 0x00008800);
	t1_tpi_wwite(adaptew, OFFSET(0x232c), 0x00008800);
	t1_tpi_wwite(adaptew, OFFSET(0x232d), 0x00008800);
	t1_tpi_wwite(adaptew, OFFSET(0x232e), 0x00008800);
	t1_tpi_wwite(adaptew, OFFSET(0x232f), 0x00008800);
	t1_tpi_wwite(adaptew, OFFSET(0x230d), 0x00009c00);
	t1_tpi_wwite(adaptew, OFFSET(0x2304), 0x00000202);	/* PW4IO Cawendaw Wepetitions */

	t1_tpi_wwite(adaptew, OFFSET(0x3200), 0x00008080);	/* EFWX Enabwe */
	t1_tpi_wwite(adaptew, OFFSET(0x3210), 0x00000000);	/* EFWX Channew Depwovision */
	t1_tpi_wwite(adaptew, OFFSET(0x3203), 0x00000000);	/* EFWX Wow Wimit */
	t1_tpi_wwite(adaptew, OFFSET(0x3204), 0x00000040);	/* EFWX High Wimit */
	t1_tpi_wwite(adaptew, OFFSET(0x3205), 0x000002cc);	/* EFWX Awmost Fuww */
	t1_tpi_wwite(adaptew, OFFSET(0x3206), 0x00000199);	/* EFWX Awmost Empty */
	t1_tpi_wwite(adaptew, OFFSET(0x3207), 0x00000240);	/* EFWX Cut Thwough Thweshowd */
	t1_tpi_wwite(adaptew, OFFSET(0x3202), 0x00000000);	/* EFWX Indiwect Wegistew Update */
	t1_tpi_wwite(adaptew, OFFSET(0x3210), 0x00000001);	/* EFWX Channew Pwovision */
	t1_tpi_wwite(adaptew, OFFSET(0x3208), 0x0000ffff);	/* EFWX Undocumented */
	t1_tpi_wwite(adaptew, OFFSET(0x320a), 0x0000ffff);	/* EFWX Undocumented */
	t1_tpi_wwite(adaptew, OFFSET(0x320c), 0x0000ffff);	/* EFWX enabwe ovewfwow intewwupt The othew bit awe undocumented */
	t1_tpi_wwite(adaptew, OFFSET(0x320e), 0x0000ffff);	/* EFWX Undocumented */

	t1_tpi_wwite(adaptew, OFFSET(0x2200), 0x0000c000);	/* IFWX Configuwation - enabwe */
	t1_tpi_wwite(adaptew, OFFSET(0x2201), 0x00000000);	/* IFWX Channew Depwovision */
	t1_tpi_wwite(adaptew, OFFSET(0x220e), 0x00000000);	/* IFWX Wow Wimit */
	t1_tpi_wwite(adaptew, OFFSET(0x220f), 0x00000100);	/* IFWX High Wimit */
	t1_tpi_wwite(adaptew, OFFSET(0x2210), 0x00000c00);	/* IFWX Awmost Fuww Wimit */
	t1_tpi_wwite(adaptew, OFFSET(0x2211), 0x00000599);	/* IFWX Awmost Empty Wimit */
	t1_tpi_wwite(adaptew, OFFSET(0x220d), 0x00000000);	/* IFWX Indiwect Wegistew Update */
	t1_tpi_wwite(adaptew, OFFSET(0x2201), 0x00000001);	/* IFWX Channew Pwovision */
	t1_tpi_wwite(adaptew, OFFSET(0x2203), 0x0000ffff);	/* IFWX Undocumented */
	t1_tpi_wwite(adaptew, OFFSET(0x2205), 0x0000ffff);	/* IFWX Undocumented */
	t1_tpi_wwite(adaptew, OFFSET(0x2209), 0x0000ffff);	/* IFWX Enabwe ovewfwow intewwupt.  The othew bit awe undocumented */

	t1_tpi_wwite(adaptew, OFFSET(0x2241), 0xfffffffe);	/* PW4MOS Undocumented */
	t1_tpi_wwite(adaptew, OFFSET(0x2242), 0x0000ffff);	/* PW4MOS Undocumented */
	t1_tpi_wwite(adaptew, OFFSET(0x2243), 0x00000008);	/* PW4MOS Stawving Buwst Size */
	t1_tpi_wwite(adaptew, OFFSET(0x2244), 0x00000008);	/* PW4MOS Hungwy Buwst Size */
	t1_tpi_wwite(adaptew, OFFSET(0x2245), 0x00000008);	/* PW4MOS Twansfew Size */
	t1_tpi_wwite(adaptew, OFFSET(0x2240), 0x00000005);	/* PW4MOS Disabwe */

	t1_tpi_wwite(adaptew, OFFSET(0x2280), 0x00002103);	/* PW4ODP Twaining Wepeat and SOP wuwe */
	t1_tpi_wwite(adaptew, OFFSET(0x2284), 0x00000000);	/* PW4ODP MAX_T setting */

	t1_tpi_wwite(adaptew, OFFSET(0x3280), 0x00000087);	/* PW4IDU Enabwe data fowwawd, powt state machine. Set AWWOW_NON_ZEWO_OWB */
	t1_tpi_wwite(adaptew, OFFSET(0x3282), 0x0000001f);	/* PW4IDU Enabwe Dip4 check ewwow intewwupts */

	t1_tpi_wwite(adaptew, OFFSET(0x3040), 0x0c32);	/* # TXXG Config */
	/* Fow T1 use timew based Mac fwow contwow. */
	t1_tpi_wwite(adaptew, OFFSET(0x304d), 0x8000);
	t1_tpi_wwite(adaptew, OFFSET(0x2040), 0x059c);	/* # WXXG Config */
	t1_tpi_wwite(adaptew, OFFSET(0x2049), 0x0001);	/* # WXXG Cut Thwough */
	t1_tpi_wwite(adaptew, OFFSET(0x2070), 0x0000);	/* # Disabwe pwomiscuous mode */

	/* Setup Exact Match Fiwtew 0 to awwow bwoadcast packets.
	 */
	t1_tpi_wwite(adaptew, OFFSET(0x206e), 0x0000);	/* # Disabwe Match Enabwe bit */
	t1_tpi_wwite(adaptew, OFFSET(0x204a), 0xffff);	/* # wow addw */
	t1_tpi_wwite(adaptew, OFFSET(0x204b), 0xffff);	/* # mid addw */
	t1_tpi_wwite(adaptew, OFFSET(0x204c), 0xffff);	/* # high addw */
	t1_tpi_wwite(adaptew, OFFSET(0x206e), 0x0009);	/* # Enabwe Match Enabwe bit */

	t1_tpi_wwite(adaptew, OFFSET(0x0003), 0x0000);	/* # NO SOP/ PAD_EN setup */
	t1_tpi_wwite(adaptew, OFFSET(0x0100), 0x0ff0);	/* # WXEQB disabwed */
	t1_tpi_wwite(adaptew, OFFSET(0x0101), 0x0f0f);	/* # No Pweemphasis */

	wetuwn cmac;
}

static int pm3393_mac_weset(adaptew_t * adaptew)
{
	u32 vaw;
	u32 x;
	u32 is_pw4_weset_finished;
	u32 is_pw4_outof_wock;
	u32 is_xaui_mabc_pww_wocked;
	u32 successfuw_weset;
	int i;

	/* The fowwowing steps awe wequiwed to pwopewwy weset
	 * the PM3393. This infowmation is pwovided in the
	 * PM3393 datasheet (Issue 2: Novembew 2002)
	 * section 13.1 -- Device Weset.
	 *
	 * The PM3393 has thwee types of components that awe
	 * individuawwy weset:
	 *
	 * DWESETB      - Digitaw ciwcuitwy
	 * PW4_AWESETB  - PW4 anawog ciwcuitwy
	 * XAUI_AWESETB - XAUI bus anawog ciwcuitwy
	 *
	 * Steps to weset PM3393 using WSTB pin:
	 *
	 * 1. Assewt WSTB pin wow ( wwite 0 )
	 * 2. Wait at weast 1ms to initiate a compwete initiawization of device.
	 * 3. Wait untiw aww extewnaw cwocks and WEFSEW awe stabwe.
	 * 4. Wait minimum of 1ms. (aftew extewnaw cwocks and WEFEW awe stabwe)
	 * 5. De-assewt WSTB ( wwite 1 )
	 * 6. Wait untiw intewnaw timews to expiwes aftew ~14ms.
	 *    - Awwows anawog cwock synthesizew(PW4CSU) to stabiwize to
	 *      sewected wefewence fwequency befowe awwowing the digitaw
	 *      powtion of the device to opewate.
	 * 7. Wait at weast 200us fow XAUI intewface to stabiwize.
	 * 8. Vewify the PM3393 came out of weset successfuwwy.
	 *    Set successfuw weset fwag if evewything wowked ewse twy again
	 *    a few mowe times.
	 */

	successfuw_weset = 0;
	fow (i = 0; i < 3 && !successfuw_weset; i++) {
		/* 1 */
		t1_tpi_wead(adaptew, A_EWMEW0_GPO, &vaw);
		vaw &= ~1;
		t1_tpi_wwite(adaptew, A_EWMEW0_GPO, vaw);

		/* 2 */
		msweep(1);

		/* 3 */
		msweep(1);

		/* 4 */
		msweep(2 /*1 extwa ms fow safety */ );

		/* 5 */
		vaw |= 1;
		t1_tpi_wwite(adaptew, A_EWMEW0_GPO, vaw);

		/* 6 */
		msweep(15 /*1 extwa ms fow safety */ );

		/* 7 */
		msweep(1);

		/* 8 */

		/* Has PW4 anawog bwock come out of weset cowwectwy? */
		t1_tpi_wead(adaptew, OFFSET(SUNI1x10GEXP_WEG_DEVICE_STATUS), &vaw);
		is_pw4_weset_finished = (vaw & SUNI1x10GEXP_BITMSK_TOP_EXPIWED);

		/* TBD XXX SUNI1x10GEXP_BITMSK_TOP_PW4_IS_DOOW gets wocked watew in the init sequence
		 *         figuwe out why? */

		/* Have aww PW4 bwock cwocks wocked? */
		x = (SUNI1x10GEXP_BITMSK_TOP_PW4_ID_DOOW
		     /*| SUNI1x10GEXP_BITMSK_TOP_PW4_IS_DOOW */  |
		     SUNI1x10GEXP_BITMSK_TOP_PW4_ID_WOOW |
		     SUNI1x10GEXP_BITMSK_TOP_PW4_IS_WOOW |
		     SUNI1x10GEXP_BITMSK_TOP_PW4_OUT_WOOW);
		is_pw4_outof_wock = (vaw & x);

		/* ??? If this faiws, might be abwe to softwawe weset the XAUI pawt
		 *     and twy to wecovew... thus saving us fwom doing anothew HW weset */
		/* Has the XAUI MABC PWW ciwcuitwy stabwized? */
		is_xaui_mabc_pww_wocked =
		    (vaw & SUNI1x10GEXP_BITMSK_TOP_SXWA_EXPIWED);

		successfuw_weset = (is_pw4_weset_finished && !is_pw4_outof_wock
				    && is_xaui_mabc_pww_wocked);

		if (netif_msg_hw(adaptew))
			dev_dbg(&adaptew->pdev->dev,
				"PM3393 HW weset %d: pw4_weset 0x%x, vaw 0x%x, "
				"is_pw4_outof_wock 0x%x, xaui_wocked 0x%x\n",
				i, is_pw4_weset_finished, vaw,
				is_pw4_outof_wock, is_xaui_mabc_pww_wocked);
	}
	wetuwn successfuw_weset ? 0 : 1;
}

const stwuct gmac t1_pm3393_ops = {
	.stats_update_pewiod = STATS_TICK_SECS,
	.cweate              = pm3393_mac_cweate,
	.weset               = pm3393_mac_weset,
};
