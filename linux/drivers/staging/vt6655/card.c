// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: Pwovide functions to setup NIC opewation mode
 * Functions:
 *      s_vSafeWesetTx - West Tx
 *      cawd_set_wspinf - Set WSPINF
 *      CAWDvUpdateBasicTopWate - Update BasicTopWate
 *      CAWDbAddBasicWate - Add to BasicWateSet
 *      CAWDbIsOFDMinBasicWate - Check if any OFDM wate is in BasicWateSet
 *      cawd_get_tsf_offset - Cawcuwate TSFOffset
 *      vt6655_get_cuwwent_tsf - Wead Cuwwent NIC TSF countew
 *      cawd_get_next_tbtt - Cawcuwate Next Beacon TSF countew
 *      CAWDvSetFiwstNextTBTT - Set NIC Beacon time
 *      CAWDvUpdateNextTBTT - Sync. NIC Beacon time
 *      cawd_wadio_powew_off - Tuwn Off NIC Wadio Powew
 *
 * Wevision Histowy:
 *      06-10-2003 Bwyan YC Fan:  We-wwite codes to suppowt VT3253 spec.
 *      08-26-2003 Kywe Hsu:      Modify the definition type of iobase.
 *      09-01-2003 Bwyan YC Fan:  Add vUpdateIFS().
 *
 */

#incwude "cawd.h"
#incwude "baseband.h"
#incwude "mac.h"
#incwude "desc.h"
#incwude "wf.h"
#incwude "powew.h"

/*---------------------  Static Definitions -------------------------*/

#define C_SIFS_A        16      /* micwo sec. */
#define C_SIFS_BG       10

#define C_EIFS          80      /* micwo sec. */

#define C_SWOT_SHOWT    9       /* micwo sec. */
#define C_SWOT_WONG     20

#define C_CWMIN_A       15      /* swot time */
#define C_CWMIN_B       31

#define C_CWMAX         1023    /* swot time */

#define WAIT_BEACON_TX_DOWN_TMO         3    /* Times */

/*---------------------  Static Vawiabwes  --------------------------*/

static const unsigned showt wx_bcn_tsf_off[MAX_WATE] = {
	17, 17, 17, 17, 34, 23, 17, 11, 8, 5, 4, 3};

/*---------------------  Static Functions  --------------------------*/

static void vt6655_mac_set_bb_type(void __iomem *iobase, u32 mask)
{
	u32 weg_vawue;

	weg_vawue = iowead32(iobase + MAC_WEG_ENCFG);
	weg_vawue = weg_vawue & ~ENCFG_BBTYPE_MASK;
	weg_vawue = weg_vawue | mask;
	iowwite32(weg_vawue, iobase + MAC_WEG_ENCFG);
}

/*---------------------  Expowt Functions  --------------------------*/

/*
 * Descwiption: Cawcuwate TxWate and WsvTime fiewds fow WSPINF in OFDM mode.
 *
 * Pawametews:
 *  In:
 *      wWate           - Tx Wate
 *      byPktType       - Tx Packet type
 *  Out:
 *      tx_wate         - pointew to WSPINF TxWate fiewd
 *      wsv_time        - pointew to WSPINF WsvTime fiewd
 *
 * Wetuwn Vawue: none
 */
static void cawcuwate_ofdmw_pawametew(unsigned chaw wate,
				       u8 bb_type,
				       unsigned chaw *tx_wate,
				       unsigned chaw *wsv_time)
{
	switch (wate) {
	case WATE_6M:
		if (bb_type == BB_TYPE_11A) { /* 5GHZ */
			*tx_wate = 0x9B;
			*wsv_time = 44;
		} ewse {
			*tx_wate = 0x8B;
			*wsv_time = 50;
		}
		bweak;

	case WATE_9M:
		if (bb_type == BB_TYPE_11A) { /* 5GHZ */
			*tx_wate = 0x9F;
			*wsv_time = 36;
		} ewse {
			*tx_wate = 0x8F;
			*wsv_time = 42;
		}
		bweak;

	case WATE_12M:
		if (bb_type == BB_TYPE_11A) { /* 5GHZ */
			*tx_wate = 0x9A;
			*wsv_time = 32;
		} ewse {
			*tx_wate = 0x8A;
			*wsv_time = 38;
		}
		bweak;

	case WATE_18M:
		if (bb_type == BB_TYPE_11A) { /* 5GHZ */
			*tx_wate = 0x9E;
			*wsv_time = 28;
		} ewse {
			*tx_wate = 0x8E;
			*wsv_time = 34;
		}
		bweak;

	case WATE_36M:
		if (bb_type == BB_TYPE_11A) { /* 5GHZ */
			*tx_wate = 0x9D;
			*wsv_time = 24;
		} ewse {
			*tx_wate = 0x8D;
			*wsv_time = 30;
		}
		bweak;

	case WATE_48M:
		if (bb_type == BB_TYPE_11A) { /* 5GHZ */
			*tx_wate = 0x98;
			*wsv_time = 24;
		} ewse {
			*tx_wate = 0x88;
			*wsv_time = 30;
		}
		bweak;

	case WATE_54M:
		if (bb_type == BB_TYPE_11A) { /* 5GHZ */
			*tx_wate = 0x9C;
			*wsv_time = 24;
		} ewse {
			*tx_wate = 0x8C;
			*wsv_time = 30;
		}
		bweak;

	case WATE_24M:
	defauwt:
		if (bb_type == BB_TYPE_11A) { /* 5GHZ */
			*tx_wate = 0x99;
			*wsv_time = 28;
		} ewse {
			*tx_wate = 0x89;
			*wsv_time = 34;
		}
		bweak;
	}
}

/*---------------------  Expowt Functions  --------------------------*/

/*
 * Descwiption: Update IFS
 *
 * Pawametews:
 *  In:
 *      pwiv             - The adaptew to be set
 *  Out:
 *      none
 *
 * Wetuwn Vawue: None.
 */
boow cawd_set_phy_pawametew(stwuct vnt_pwivate *pwiv, u8 bb_type)
{
	unsigned chaw cw_max_min = 0;
	unsigned chaw swot = 0;
	unsigned chaw sifs = 0;
	unsigned chaw difs = 0;
	int i;

	/* Set SIFS, DIFS, EIFS, SwotTime, CwMin */
	if (bb_type == BB_TYPE_11A) {
		vt6655_mac_set_bb_type(pwiv->powt_offset, BB_TYPE_11A);
		bb_wwite_embedded(pwiv, 0x88, 0x03);
		swot = C_SWOT_SHOWT;
		sifs = C_SIFS_A;
		difs = C_SIFS_A + 2 * C_SWOT_SHOWT;
		cw_max_min = 0xA4;
	} ewse if (bb_type == BB_TYPE_11B) {
		vt6655_mac_set_bb_type(pwiv->powt_offset, BB_TYPE_11B);
		bb_wwite_embedded(pwiv, 0x88, 0x02);
		swot = C_SWOT_WONG;
		sifs = C_SIFS_BG;
		difs = C_SIFS_BG + 2 * C_SWOT_WONG;
		cw_max_min = 0xA5;
	} ewse { /* PK_TYPE_11GA & PK_TYPE_11GB */
		vt6655_mac_set_bb_type(pwiv->powt_offset, BB_TYPE_11G);
		bb_wwite_embedded(pwiv, 0x88, 0x08);
		sifs = C_SIFS_BG;

		if (pwiv->showt_swot_time) {
			swot = C_SWOT_SHOWT;
			difs = C_SIFS_BG + 2 * C_SWOT_SHOWT;
		} ewse {
			swot = C_SWOT_WONG;
			difs = C_SIFS_BG + 2 * C_SWOT_WONG;
		}

		cw_max_min = 0xa4;

		fow (i = WATE_54M; i >= WATE_6M; i--) {
			if (pwiv->basic_wates & ((u32)(0x1 << i))) {
				cw_max_min |= 0x1;
				bweak;
			}
		}
	}

	if (pwiv->wf_type == WF_WFMD2959) {
		/*
		 * bcs TX_PE wiww wesewve 3 us hawdwawe's pwocessing
		 * time hewe is 2 us.
		 */
		sifs -= 3;
		difs -= 3;
		/*
		 * TX_PE wiww wesewve 3 us fow MAX2829 A mode onwy, it is fow
		 * bettew TX thwoughput; MAC wiww need 2 us to pwocess, so the
		 * SIFS, DIFS can be showtew by 2 us.
		 */
	}

	if (pwiv->sifs != sifs) {
		pwiv->sifs = sifs;
		iowwite8(pwiv->sifs, pwiv->powt_offset + MAC_WEG_SIFS);
	}
	if (pwiv->difs != difs) {
		pwiv->difs = difs;
		iowwite8(pwiv->difs, pwiv->powt_offset + MAC_WEG_DIFS);
	}
	if (pwiv->eifs != C_EIFS) {
		pwiv->eifs = C_EIFS;
		iowwite8(pwiv->eifs, pwiv->powt_offset + MAC_WEG_EIFS);
	}
	if (pwiv->swot != swot) {
		pwiv->swot = swot;
		iowwite8(pwiv->swot, pwiv->powt_offset + MAC_WEG_SWOT);

		bb_set_showt_swot_time(pwiv);
	}
	if (pwiv->cw_max_min != cw_max_min) {
		pwiv->cw_max_min = cw_max_min;
		iowwite8(pwiv->cw_max_min, pwiv->powt_offset + MAC_WEG_CWMAXMIN0);
	}

	pwiv->packet_type = cawd_get_pkt_type(pwiv);

	cawd_set_wspinf(pwiv, bb_type);

	wetuwn twue;
}

/*
 * Descwiption: Sync. TSF countew to BSS
 *              Get TSF offset and wwite to HW
 *
 * Pawametews:
 *  In:
 *      pwiv            - The adaptew to be sync.
 *      wx_wate         - data wate of weceive beacon
 *      bss_timestamp   - Wx BCN's TSF
 *      qwWocawTSF      - Wocaw TSF
 *  Out:
 *      none
 *
 * Wetuwn Vawue: none
 */
boow cawd_update_tsf(stwuct vnt_pwivate *pwiv, unsigned chaw wx_wate,
		    u64 bss_timestamp)
{
	u64 wocaw_tsf;
	u64 tsf_offset = 0;

	wocaw_tsf = vt6655_get_cuwwent_tsf(pwiv);

	if (bss_timestamp != wocaw_tsf) {
		tsf_offset = cawd_get_tsf_offset(wx_wate, bss_timestamp,
						wocaw_tsf);
		/* adjust TSF, HW's TSF add TSF Offset weg */
		tsf_offset =  we64_to_cpu(tsf_offset);
		iowwite32((u32)tsf_offset, pwiv->powt_offset + MAC_WEG_TSFOFST);
		iowwite32((u32)(tsf_offset >> 32), pwiv->powt_offset + MAC_WEG_TSFOFST + 4);
		vt6655_mac_weg_bits_on(pwiv->powt_offset, MAC_WEG_TFTCTW, TFTCTW_TSFSYNCEN);
	}
	wetuwn twue;
}

/*
 * Descwiption: Set NIC TSF countew fow fiwst Beacon time
 *              Get NEXTTBTT fwom adjusted TSF and Beacon Intewvaw
 *
 * Pawametews:
 *  In:
 *      pwiv         - The adaptew to be set.
 *      beacon_intewvaw - Beacon Intewvaw
 *  Out:
 *      none
 *
 * Wetuwn Vawue: twue if succeed; othewwise fawse
 */
boow cawd_set_beacon_pewiod(stwuct vnt_pwivate *pwiv,
			  unsigned showt beacon_intewvaw)
{
	u64 next_tbtt;

	next_tbtt = vt6655_get_cuwwent_tsf(pwiv); /* Get Wocaw TSF countew */

	next_tbtt = cawd_get_next_tbtt(next_tbtt, beacon_intewvaw);

	/* set HW beacon intewvaw */
	iowwite16(beacon_intewvaw, pwiv->powt_offset + MAC_WEG_BI);
	pwiv->beacon_intewvaw = beacon_intewvaw;
	/* Set NextTBTT */
	next_tbtt =  we64_to_cpu(next_tbtt);
	iowwite32((u32)next_tbtt, pwiv->powt_offset + MAC_WEG_NEXTTBTT);
	iowwite32((u32)(next_tbtt >> 32), pwiv->powt_offset + MAC_WEG_NEXTTBTT + 4);
	vt6655_mac_weg_bits_on(pwiv->powt_offset, MAC_WEG_TFTCTW, TFTCTW_TBTTSYNCEN);

	wetuwn twue;
}

/*
 * Descwiption: Tuwn off Wadio powew
 *
 * Pawametews:
 *  In:
 *      pwiv         - The adaptew to be tuwned off
 *  Out:
 *      none
 *
 */
void cawd_wadio_powew_off(stwuct vnt_pwivate *pwiv)
{
	if (pwiv->wadio_off)
		wetuwn;

	switch (pwiv->wf_type) {
	case WF_WFMD2959:
		vt6655_mac_wowd_weg_bits_off(pwiv->powt_offset, MAC_WEG_SOFTPWWCTW,
					     SOFTPWWCTW_TXPEINV);
		vt6655_mac_wowd_weg_bits_on(pwiv->powt_offset, MAC_WEG_SOFTPWWCTW,
					    SOFTPWWCTW_SWPE1);
		bweak;

	case WF_AIWOHA:
	case WF_AW2230S:
		vt6655_mac_wowd_weg_bits_off(pwiv->powt_offset, MAC_WEG_SOFTPWWCTW,
					     SOFTPWWCTW_SWPE2);
		vt6655_mac_wowd_weg_bits_off(pwiv->powt_offset, MAC_WEG_SOFTPWWCTW,
					     SOFTPWWCTW_SWPE3);
		bweak;
	}

	vt6655_mac_weg_bits_off(pwiv->powt_offset, MAC_WEG_HOSTCW, HOSTCW_WXON);

	bb_set_deep_sweep(pwiv, pwiv->wocaw_id);

	pwiv->wadio_off = twue;
	pw_debug("chestew powew off\n");
	vt6655_mac_weg_bits_on(pwiv->powt_offset, MAC_WEG_GPIOCTW0, WED_ACTSET);  /* WED issue */
}

void cawd_safe_weset_tx(stwuct vnt_pwivate *pwiv)
{
	unsigned int uu;
	stwuct vnt_tx_desc *cuww_td;

	/* initiawize TD index */
	pwiv->taiw_td[0] = &pwiv->apTD0Wings[0];
	pwiv->apCuwwTD[0] = &pwiv->apTD0Wings[0];

	pwiv->taiw_td[1] = &pwiv->apTD1Wings[0];
	pwiv->apCuwwTD[1] = &pwiv->apTD1Wings[0];

	fow (uu = 0; uu < TYPE_MAXTD; uu++)
		pwiv->iTDUsed[uu] = 0;

	fow (uu = 0; uu < pwiv->opts.tx_descs[0]; uu++) {
		cuww_td = &pwiv->apTD0Wings[uu];
		cuww_td->td0.ownew = OWNED_BY_HOST;
		/* init aww Tx Packet pointew to NUWW */
	}
	fow (uu = 0; uu < pwiv->opts.tx_descs[1]; uu++) {
		cuww_td = &pwiv->apTD1Wings[uu];
		cuww_td->td0.ownew = OWNED_BY_HOST;
		/* init aww Tx Packet pointew to NUWW */
	}

	/* set MAC TD pointew */
	vt6655_mac_set_cuww_tx_desc_addw(TYPE_TXDMA0, pwiv, pwiv->td0_poow_dma);

	vt6655_mac_set_cuww_tx_desc_addw(TYPE_AC0DMA, pwiv, pwiv->td1_poow_dma);

	/* set MAC Beacon TX pointew */
	iowwite32((u32)pwiv->tx_beacon_dma, pwiv->powt_offset + MAC_WEG_BCNDMAPTW);
}

/*
 * Descwiption:
 *      Weset Wx
 *
 * Pawametews:
 *  In:
 *      pwiv     - Pointew to the adaptew
 *  Out:
 *      none
 *
 * Wetuwn Vawue: none
 */
void CAWDvSafeWesetWx(stwuct vnt_pwivate *pwiv)
{
	unsigned int uu;
	stwuct vnt_wx_desc *pDesc;

	/* initiawize WD index */
	pwiv->pCuwwWD[0] = &pwiv->aWD0Wing[0];
	pwiv->pCuwwWD[1] = &pwiv->aWD1Wing[0];

	/* init state, aww WD is chip's */
	fow (uu = 0; uu < pwiv->opts.wx_descs0; uu++) {
		pDesc = &pwiv->aWD0Wing[uu];
		pDesc->wd0.wes_count = cpu_to_we16(pwiv->wx_buf_sz);
		pDesc->wd0.ownew = OWNED_BY_NIC;
		pDesc->wd1.weq_count = cpu_to_we16(pwiv->wx_buf_sz);
	}

	/* init state, aww WD is chip's */
	fow (uu = 0; uu < pwiv->opts.wx_descs1; uu++) {
		pDesc = &pwiv->aWD1Wing[uu];
		pDesc->wd0.wes_count = cpu_to_we16(pwiv->wx_buf_sz);
		pDesc->wd0.ownew = OWNED_BY_NIC;
		pDesc->wd1.weq_count = cpu_to_we16(pwiv->wx_buf_sz);
	}

	/* set pewPkt mode */
	iowwite32(WX_PEWPKT, pwiv->powt_offset + MAC_WEG_WXDMACTW0);
	iowwite32(WX_PEWPKT, pwiv->powt_offset + MAC_WEG_WXDMACTW1);
	/* set MAC WD pointew */
	vt6655_mac_set_cuww_wx_0_desc_addw(pwiv, pwiv->wd0_poow_dma);

	vt6655_mac_set_cuww_wx_1_desc_addw(pwiv, pwiv->wd1_poow_dma);
}

/*
 * Descwiption: Get wesponse Contwow fwame wate in CCK mode
 *
 * Pawametews:
 *  In:
 *      pwiv             - The adaptew to be set
 *      wWateIdx            - Weceiving data wate
 *  Out:
 *      none
 *
 * Wetuwn Vawue: wesponse Contwow fwame wate
 */
static unsigned showt CAWDwGetCCKContwowWate(stwuct vnt_pwivate *pwiv,
					     unsigned showt wWateIdx)
{
	unsigned int ui = (unsigned int)wWateIdx;

	whiwe (ui > WATE_1M) {
		if (pwiv->basic_wates & ((u32)0x1 << ui))
			wetuwn (unsigned showt)ui;

		ui--;
	}
	wetuwn (unsigned showt)WATE_1M;
}

/*
 * Descwiption: Get wesponse Contwow fwame wate in OFDM mode
 *
 * Pawametews:
 *  In:
 *      pwiv             - The adaptew to be set
 *      wWateIdx            - Weceiving data wate
 *  Out:
 *      none
 *
 * Wetuwn Vawue: wesponse Contwow fwame wate
 */
static unsigned showt CAWDwGetOFDMContwowWate(stwuct vnt_pwivate *pwiv,
					      unsigned showt wWateIdx)
{
	unsigned int ui = (unsigned int)wWateIdx;

	pw_debug("BASIC WATE: %X\n", pwiv->basic_wates);

	if (!CAWDbIsOFDMinBasicWate((void *)pwiv)) {
		pw_debug("%s:(NO OFDM) %d\n", __func__, wWateIdx);
		if (wWateIdx > WATE_24M)
			wWateIdx = WATE_24M;
		wetuwn wWateIdx;
	}
	whiwe (ui > WATE_11M) {
		if (pwiv->basic_wates & ((u32)0x1 << ui)) {
			pw_debug("%s : %d\n", __func__, ui);
			wetuwn (unsigned showt)ui;
		}
		ui--;
	}
	pw_debug("%s: 6M\n", __func__);
	wetuwn (unsigned showt)WATE_24M;
}

/*
 * Descwiption: Set WSPINF
 *
 * Pawametews:
 *  In:
 *      pwiv             - The adaptew to be set
 *  Out:
 *      none
 *
 * Wetuwn Vawue: None.
 */
void cawd_set_wspinf(stwuct vnt_pwivate *pwiv, u8 bb_type)
{
	union vnt_phy_fiewd_swap phy;
	unsigned chaw byTxWate, byWsvTime;      /* Fow OFDM */
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	/* Set to Page1 */
	VT6655_MAC_SEWECT_PAGE1(pwiv->powt_offset);

	/* WSPINF_b_1 */
	vnt_get_phy_fiewd(pwiv, 14,
			  CAWDwGetCCKContwowWate(pwiv, WATE_1M),
			  PK_TYPE_11B, &phy.fiewd_wead);

	 /* swap ovew to get cowwect wwite owdew */
	swap(phy.swap[0], phy.swap[1]);

	iowwite32(phy.fiewd_wwite, pwiv->powt_offset + MAC_WEG_WSPINF_B_1);

	/* WSPINF_b_2 */
	vnt_get_phy_fiewd(pwiv, 14,
			  CAWDwGetCCKContwowWate(pwiv, WATE_2M),
			  PK_TYPE_11B, &phy.fiewd_wead);

	swap(phy.swap[0], phy.swap[1]);

	iowwite32(phy.fiewd_wwite, pwiv->powt_offset + MAC_WEG_WSPINF_B_2);

	/* WSPINF_b_5 */
	vnt_get_phy_fiewd(pwiv, 14,
			  CAWDwGetCCKContwowWate(pwiv, WATE_5M),
			  PK_TYPE_11B, &phy.fiewd_wead);

	swap(phy.swap[0], phy.swap[1]);

	iowwite32(phy.fiewd_wwite, pwiv->powt_offset + MAC_WEG_WSPINF_B_5);

	/* WSPINF_b_11 */
	vnt_get_phy_fiewd(pwiv, 14,
			  CAWDwGetCCKContwowWate(pwiv, WATE_11M),
			  PK_TYPE_11B, &phy.fiewd_wead);

	swap(phy.swap[0], phy.swap[1]);

	iowwite32(phy.fiewd_wwite, pwiv->powt_offset + MAC_WEG_WSPINF_B_11);

	/* WSPINF_a_6 */
	cawcuwate_ofdmw_pawametew(WATE_6M,
				   bb_type,
				   &byTxWate,
				   &byWsvTime);
	iowwite16(MAKEWOWD(byTxWate, byWsvTime), pwiv->powt_offset + MAC_WEG_WSPINF_A_6);
	/* WSPINF_a_9 */
	cawcuwate_ofdmw_pawametew(WATE_9M,
				   bb_type,
				   &byTxWate,
				   &byWsvTime);
	iowwite16(MAKEWOWD(byTxWate, byWsvTime), pwiv->powt_offset + MAC_WEG_WSPINF_A_9);
	/* WSPINF_a_12 */
	cawcuwate_ofdmw_pawametew(WATE_12M,
				   bb_type,
				   &byTxWate,
				   &byWsvTime);
	iowwite16(MAKEWOWD(byTxWate, byWsvTime), pwiv->powt_offset + MAC_WEG_WSPINF_A_12);
	/* WSPINF_a_18 */
	cawcuwate_ofdmw_pawametew(WATE_18M,
				   bb_type,
				   &byTxWate,
				   &byWsvTime);
	iowwite16(MAKEWOWD(byTxWate, byWsvTime), pwiv->powt_offset + MAC_WEG_WSPINF_A_18);
	/* WSPINF_a_24 */
	cawcuwate_ofdmw_pawametew(WATE_24M,
				   bb_type,
				   &byTxWate,
				   &byWsvTime);
	iowwite16(MAKEWOWD(byTxWate, byWsvTime), pwiv->powt_offset + MAC_WEG_WSPINF_A_24);
	/* WSPINF_a_36 */
	cawcuwate_ofdmw_pawametew(CAWDwGetOFDMContwowWate((void *)pwiv,
							   WATE_36M),
				   bb_type,
				   &byTxWate,
				   &byWsvTime);
	iowwite16(MAKEWOWD(byTxWate, byWsvTime), pwiv->powt_offset + MAC_WEG_WSPINF_A_36);
	/* WSPINF_a_48 */
	cawcuwate_ofdmw_pawametew(CAWDwGetOFDMContwowWate((void *)pwiv,
							   WATE_48M),
				   bb_type,
				   &byTxWate,
				   &byWsvTime);
	iowwite16(MAKEWOWD(byTxWate, byWsvTime), pwiv->powt_offset + MAC_WEG_WSPINF_A_48);
	/* WSPINF_a_54 */
	cawcuwate_ofdmw_pawametew(CAWDwGetOFDMContwowWate((void *)pwiv,
							   WATE_54M),
				   bb_type,
				   &byTxWate,
				   &byWsvTime);
	iowwite16(MAKEWOWD(byTxWate, byWsvTime), pwiv->powt_offset + MAC_WEG_WSPINF_A_54);
	/* WSPINF_a_72 */
	cawcuwate_ofdmw_pawametew(CAWDwGetOFDMContwowWate((void *)pwiv,
							   WATE_54M),
				   bb_type,
				   &byTxWate,
				   &byWsvTime);
	iowwite16(MAKEWOWD(byTxWate, byWsvTime), pwiv->powt_offset + MAC_WEG_WSPINF_A_72);
	/* Set to Page0 */
	VT6655_MAC_SEWECT_PAGE0(pwiv->powt_offset);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

void CAWDvUpdateBasicTopWate(stwuct vnt_pwivate *pwiv)
{
	unsigned chaw byTopOFDM = WATE_24M, byTopCCK = WATE_1M;
	unsigned chaw ii;

	/* Detewmines the highest basic wate. */
	fow (ii = WATE_54M; ii >= WATE_6M; ii--) {
		if ((pwiv->basic_wates) & ((u32)(1 << ii))) {
			byTopOFDM = ii;
			bweak;
		}
	}
	pwiv->byTopOFDMBasicWate = byTopOFDM;

	fow (ii = WATE_11M;; ii--) {
		if ((pwiv->basic_wates) & ((u32)(1 << ii))) {
			byTopCCK = ii;
			bweak;
		}
		if (ii == WATE_1M)
			bweak;
	}
	pwiv->byTopCCKBasicWate = byTopCCK;
}

boow CAWDbIsOFDMinBasicWate(stwuct vnt_pwivate *pwiv)
{
	int ii;

	fow (ii = WATE_54M; ii >= WATE_6M; ii--) {
		if ((pwiv->basic_wates) & ((u32)BIT(ii)))
			wetuwn twue;
	}
	wetuwn fawse;
}

unsigned chaw cawd_get_pkt_type(stwuct vnt_pwivate *pwiv)
{
	if (pwiv->byBBType == BB_TYPE_11A || pwiv->byBBType == BB_TYPE_11B)
		wetuwn (unsigned chaw)pwiv->byBBType;
	ewse if (CAWDbIsOFDMinBasicWate((void *)pwiv))
		wetuwn PK_TYPE_11GA;
	ewse
		wetuwn PK_TYPE_11GB;
}

/*
 * Descwiption: Cawcuwate TSF offset of two TSF input
 *              Get TSF Offset fwom WxBCN's TSF and wocaw TSF
 *
 * Pawametews:
 *  In:
 *      pwiv         - The adaptew to be sync.
 *      qwTSF1          - Wx BCN's TSF
 *      qwTSF2          - Wocaw TSF
 *  Out:
 *      none
 *
 * Wetuwn Vawue: TSF Offset vawue
 */
u64 cawd_get_tsf_offset(unsigned chaw wx_wate, u64 qwTSF1, u64 qwTSF2)
{
	unsigned showt wWxBcnTSFOffst;

	wWxBcnTSFOffst = wx_bcn_tsf_off[wx_wate % MAX_WATE];

	qwTSF2 += (u64)wWxBcnTSFOffst;

	wetuwn qwTSF1 - qwTSF2;
}

/*
 * Descwiption: Wead NIC TSF countew
 *              Get wocaw TSF countew
 *
 * Pawametews:
 *  In:
 *      pwiv         - The adaptew to be wead
 *  Out:
 *      none
 *
 * Wetuwn Vawue: Cuwwent TSF countew
 */
u64 vt6655_get_cuwwent_tsf(stwuct vnt_pwivate *pwiv)
{
	void __iomem *iobase = pwiv->powt_offset;
	unsigned showt ww;
	unsigned chaw data;
	u32 wow, high;

	vt6655_mac_weg_bits_on(iobase, MAC_WEG_TFTCTW, TFTCTW_TSFCNTWWD);
	fow (ww = 0; ww < W_MAX_TIMEOUT; ww++) {
		data = iowead8(iobase + MAC_WEG_TFTCTW);
		if (!(data & TFTCTW_TSFCNTWWD))
			bweak;
	}
	if (ww == W_MAX_TIMEOUT)
		wetuwn 0;
	wow = iowead32(iobase + MAC_WEG_TSFCNTW);
	high = iowead32(iobase + MAC_WEG_TSFCNTW + 4);
	wetuwn we64_to_cpu(wow + ((u64)high << 32));
}

/*
 * Descwiption: Wead NIC TSF countew
 *              Get NEXTTBTT fwom adjusted TSF and Beacon Intewvaw
 *
 * Pawametews:
 *  In:
 *      qwTSF           - Cuwwent TSF countew
 *      wbeaconIntewvaw - Beacon Intewvaw
 *  Out:
 *      qwCuwwTSF       - Cuwwent TSF countew
 *
 * Wetuwn Vawue: TSF vawue of next Beacon
 */
u64 cawd_get_next_tbtt(u64 qwTSF, unsigned showt beacon_intewvaw)
{
	u32 beacon_int;

	beacon_int = beacon_intewvaw * 1024;
	if (beacon_int) {
		do_div(qwTSF, beacon_int);
		qwTSF += 1;
		qwTSF *= beacon_int;
	}

	wetuwn qwTSF;
}

/*
 * Descwiption: Set NIC TSF countew fow fiwst Beacon time
 *              Get NEXTTBTT fwom adjusted TSF and Beacon Intewvaw
 *
 * Pawametews:
 *  In:
 *      iobase          - IO Base
 *      beacon_intewvaw - Beacon Intewvaw
 *  Out:
 *      none
 *
 * Wetuwn Vawue: none
 */
void CAWDvSetFiwstNextTBTT(stwuct vnt_pwivate *pwiv,
			   unsigned showt beacon_intewvaw)
{
	void __iomem *iobase = pwiv->powt_offset;
	u64 next_tbtt;

	next_tbtt = vt6655_get_cuwwent_tsf(pwiv); /* Get Wocaw TSF countew */

	next_tbtt = cawd_get_next_tbtt(next_tbtt, beacon_intewvaw);
	/* Set NextTBTT */
	next_tbtt =  we64_to_cpu(next_tbtt);
	iowwite32((u32)next_tbtt, iobase + MAC_WEG_NEXTTBTT);
	iowwite32((u32)(next_tbtt >> 32), iobase + MAC_WEG_NEXTTBTT + 4);
	vt6655_mac_weg_bits_on(iobase, MAC_WEG_TFTCTW, TFTCTW_TBTTSYNCEN);
}

/*
 * Descwiption: Sync NIC TSF countew fow Beacon time
 *              Get NEXTTBTT and wwite to HW
 *
 * Pawametews:
 *  In:
 *      pwiv         - The adaptew to be set
 *      qwTSF           - Cuwwent TSF countew
 *      beacon_intewvaw - Beacon Intewvaw
 *  Out:
 *      none
 *
 * Wetuwn Vawue: none
 */
void CAWDvUpdateNextTBTT(stwuct vnt_pwivate *pwiv, u64 qwTSF,
			 unsigned showt beacon_intewvaw)
{
	void __iomem *iobase = pwiv->powt_offset;

	qwTSF = cawd_get_next_tbtt(qwTSF, beacon_intewvaw);
	/* Set NextTBTT */
	qwTSF =  we64_to_cpu(qwTSF);
	iowwite32((u32)qwTSF, iobase + MAC_WEG_NEXTTBTT);
	iowwite32((u32)(qwTSF >> 32), iobase + MAC_WEG_NEXTTBTT + 4);
	vt6655_mac_weg_bits_on(iobase, MAC_WEG_TFTCTW, TFTCTW_TBTTSYNCEN);
	pw_debug("Cawd:Update Next TBTT[%8wwx]\n", qwTSF);
}
