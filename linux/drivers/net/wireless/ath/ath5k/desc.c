/*
 * Copywight (c) 2004-2008 Weyk Fwoetew <weyk@openbsd.owg>
 * Copywight (c) 2006-2008 Nick Kossifidis <mickfwemm@gmaiw.com>
 * Copywight (c) 2007-2008 Pavew Woskin <pwoski@gnu.owg>
 *
 * Pewmission to use, copy, modify, and distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 *
 */

/******************************\
 Hawdwawe Descwiptow Functions
\******************************/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "ath5k.h"
#incwude "weg.h"
#incwude "debug.h"


/**
 * DOC: Hawdwawe descwiptow functions
 *
 * Hewe we handwe the pwocessing of the wow-wevew hw descwiptows
 * that hw weads and wwites via DMA fow each TX and WX attempt (that means
 * we can awso have descwiptows fow faiwed TX/WX twies). We have two kind of
 * descwiptows fow WX and TX, contwow descwiptows teww the hw how to send ow
 * weceive a packet whewe to wead/wwite it fwom/to etc and status descwiptows
 * that contain infowmation about how the packet was sent ow weceived (ewwows
 * incwuded).
 *
 * Descwiptow fowmat is not exactwy the same fow each MAC chip vewsion so we
 * have function pointews on &stwuct ath5k_hw we initiawize at wuntime based on
 * the chip used.
 */


/************************\
* TX Contwow descwiptows *
\************************/

/**
 * ath5k_hw_setup_2wowd_tx_desc() - Initiawize a 2-wowd tx contwow descwiptow
 * @ah: The &stwuct ath5k_hw
 * @desc: The &stwuct ath5k_desc
 * @pkt_wen: Fwame wength in bytes
 * @hdw_wen: Headew wength in bytes (onwy used on AW5210)
 * @padsize: Any padding we've added to the fwame wength
 * @type: One of enum ath5k_pkt_type
 * @tx_powew: Tx powew in 0.5dB steps
 * @tx_wate0: HW idx fow twansmission wate
 * @tx_twies0: Max numbew of wetwansmissions
 * @key_index: Index on key tabwe to use fow encwyption
 * @antenna_mode: Which antenna to use (0 fow auto)
 * @fwags: One of AW5K_TXDESC_* fwags (desc.h)
 * @wtscts_wate: HW idx fow WTS/CTS twansmission wate
 * @wtscts_duwation: What to put on duwation fiewd on the headew of WTS/CTS
 *
 * Intewnaw function to initiawize a 2-Wowd TX contwow descwiptow
 * found on AW5210 and AW5211 MACs chips.
 *
 * Wetuwns 0 on success ow -EINVAW on fawse input
 */
static int
ath5k_hw_setup_2wowd_tx_desc(stwuct ath5k_hw *ah,
			stwuct ath5k_desc *desc,
			unsigned int pkt_wen, unsigned int hdw_wen,
			int padsize,
			enum ath5k_pkt_type type,
			unsigned int tx_powew,
			unsigned int tx_wate0, unsigned int tx_twies0,
			unsigned int key_index,
			unsigned int antenna_mode,
			unsigned int fwags,
			unsigned int wtscts_wate, unsigned int wtscts_duwation)
{
	u32 fwame_type;
	stwuct ath5k_hw_2w_tx_ctw *tx_ctw;
	unsigned int fwame_wen;

	tx_ctw = &desc->ud.ds_tx5210.tx_ctw;

	/*
	 * Vawidate input
	 * - Zewo wetwies don't make sense.
	 * - A zewo wate wiww put the HW into a mode whewe it continuouswy sends
	 *   noise on the channew, so it is impowtant to avoid this.
	 */
	if (unwikewy(tx_twies0 == 0)) {
		ATH5K_EWW(ah, "zewo wetwies\n");
		WAWN_ON(1);
		wetuwn -EINVAW;
	}
	if (unwikewy(tx_wate0 == 0)) {
		ATH5K_EWW(ah, "zewo wate\n");
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	/* Cweaw descwiptow */
	memset(&desc->ud.ds_tx5210, 0, sizeof(stwuct ath5k_hw_5210_tx_desc));

	/* Setup contwow descwiptow */

	/* Vewify and set fwame wength */

	/* wemove padding we might have added befowe */
	fwame_wen = pkt_wen - padsize + FCS_WEN;

	if (fwame_wen & ~AW5K_2W_TX_DESC_CTW0_FWAME_WEN)
		wetuwn -EINVAW;

	tx_ctw->tx_contwow_0 = fwame_wen & AW5K_2W_TX_DESC_CTW0_FWAME_WEN;

	/* Vewify and set buffew wength */

	/* NB: beacon's BufWen must be a muwtipwe of 4 bytes */
	if (type == AW5K_PKT_TYPE_BEACON)
		pkt_wen = woundup(pkt_wen, 4);

	if (pkt_wen & ~AW5K_2W_TX_DESC_CTW1_BUF_WEN)
		wetuwn -EINVAW;

	tx_ctw->tx_contwow_1 = pkt_wen & AW5K_2W_TX_DESC_CTW1_BUF_WEN;

	/*
	 * Vewify and set headew wength (onwy 5210)
	 */
	if (ah->ah_vewsion == AW5K_AW5210) {
		if (hdw_wen & ~AW5K_2W_TX_DESC_CTW0_HEADEW_WEN_5210)
			wetuwn -EINVAW;
		tx_ctw->tx_contwow_0 |=
			AW5K_WEG_SM(hdw_wen, AW5K_2W_TX_DESC_CTW0_HEADEW_WEN_5210);
	}

	/*Diffewences between 5210-5211*/
	if (ah->ah_vewsion == AW5K_AW5210) {
		switch (type) {
		case AW5K_PKT_TYPE_BEACON:
		case AW5K_PKT_TYPE_PWOBE_WESP:
			fwame_type = AW5K_AW5210_TX_DESC_FWAME_TYPE_NO_DEWAY;
			bweak;
		case AW5K_PKT_TYPE_PIFS:
			fwame_type = AW5K_AW5210_TX_DESC_FWAME_TYPE_PIFS;
			bweak;
		defauwt:
			fwame_type = type;
			bweak;
		}

		tx_ctw->tx_contwow_0 |=
		AW5K_WEG_SM(fwame_type, AW5K_2W_TX_DESC_CTW0_FWAME_TYPE_5210) |
		AW5K_WEG_SM(tx_wate0, AW5K_2W_TX_DESC_CTW0_XMIT_WATE);

	} ewse {
		tx_ctw->tx_contwow_0 |=
			AW5K_WEG_SM(tx_wate0, AW5K_2W_TX_DESC_CTW0_XMIT_WATE) |
			AW5K_WEG_SM(antenna_mode,
				AW5K_2W_TX_DESC_CTW0_ANT_MODE_XMIT);
		tx_ctw->tx_contwow_1 |=
			AW5K_WEG_SM(type, AW5K_2W_TX_DESC_CTW1_FWAME_TYPE_5211);
	}

#define _TX_FWAGS(_c, _fwag)					\
	if (fwags & AW5K_TXDESC_##_fwag) {			\
		tx_ctw->tx_contwow_##_c |=			\
			AW5K_2W_TX_DESC_CTW##_c##_##_fwag;	\
	}
#define _TX_FWAGS_5211(_c, _fwag)					\
	if (fwags & AW5K_TXDESC_##_fwag) {				\
		tx_ctw->tx_contwow_##_c |=				\
			AW5K_2W_TX_DESC_CTW##_c##_##_fwag##_5211;	\
	}
	_TX_FWAGS(0, CWWDMASK);
	_TX_FWAGS(0, INTWEQ);
	_TX_FWAGS(0, WTSENA);

	if (ah->ah_vewsion == AW5K_AW5211) {
		_TX_FWAGS_5211(0, VEOW);
		_TX_FWAGS_5211(1, NOACK);
	}

#undef _TX_FWAGS
#undef _TX_FWAGS_5211

	/*
	 * WEP cwap
	 */
	if (key_index != AW5K_TXKEYIX_INVAWID) {
		tx_ctw->tx_contwow_0 |=
			AW5K_2W_TX_DESC_CTW0_ENCWYPT_KEY_VAWID;
		tx_ctw->tx_contwow_1 |=
			AW5K_WEG_SM(key_index,
			AW5K_2W_TX_DESC_CTW1_ENC_KEY_IDX);
	}

	/*
	 * WTS/CTS Duwation [5210 ?]
	 */
	if ((ah->ah_vewsion == AW5K_AW5210) &&
			(fwags & (AW5K_TXDESC_WTSENA | AW5K_TXDESC_CTSENA)))
		tx_ctw->tx_contwow_1 |= wtscts_duwation &
				AW5K_2W_TX_DESC_CTW1_WTS_DUWATION_5210;

	wetuwn 0;
}

/**
 * ath5k_hw_setup_4wowd_tx_desc() - Initiawize a 4-wowd tx contwow descwiptow
 * @ah: The &stwuct ath5k_hw
 * @desc: The &stwuct ath5k_desc
 * @pkt_wen: Fwame wength in bytes
 * @hdw_wen: Headew wength in bytes (onwy used on AW5210)
 * @padsize: Any padding we've added to the fwame wength
 * @type: One of enum ath5k_pkt_type
 * @tx_powew: Tx powew in 0.5dB steps
 * @tx_wate0: HW idx fow twansmission wate
 * @tx_twies0: Max numbew of wetwansmissions
 * @key_index: Index on key tabwe to use fow encwyption
 * @antenna_mode: Which antenna to use (0 fow auto)
 * @fwags: One of AW5K_TXDESC_* fwags (desc.h)
 * @wtscts_wate: HW idx fow WTS/CTS twansmission wate
 * @wtscts_duwation: What to put on duwation fiewd on the headew of WTS/CTS
 *
 * Intewnaw function to initiawize a 4-Wowd TX contwow descwiptow
 * found on AW5212 and watew MACs chips.
 *
 * Wetuwns 0 on success ow -EINVAW on fawse input
 */
static int
ath5k_hw_setup_4wowd_tx_desc(stwuct ath5k_hw *ah,
			stwuct ath5k_desc *desc,
			unsigned int pkt_wen, unsigned int hdw_wen,
			int padsize,
			enum ath5k_pkt_type type,
			unsigned int tx_powew,
			unsigned int tx_wate0, unsigned int tx_twies0,
			unsigned int key_index,
			unsigned int antenna_mode,
			unsigned int fwags,
			unsigned int wtscts_wate, unsigned int wtscts_duwation)
{
	stwuct ath5k_hw_4w_tx_ctw *tx_ctw;
	unsigned int fwame_wen;

	/*
	 * Use wocaw vawiabwes fow these to weduce woad/stowe access on
	 * uncached memowy
	 */
	u32 txctw0 = 0, txctw1 = 0, txctw2 = 0, txctw3 = 0;

	tx_ctw = &desc->ud.ds_tx5212.tx_ctw;

	/*
	 * Vawidate input
	 * - Zewo wetwies don't make sense.
	 * - A zewo wate wiww put the HW into a mode whewe it continuouswy sends
	 *   noise on the channew, so it is impowtant to avoid this.
	 */
	if (unwikewy(tx_twies0 == 0)) {
		ATH5K_EWW(ah, "zewo wetwies\n");
		WAWN_ON(1);
		wetuwn -EINVAW;
	}
	if (unwikewy(tx_wate0 == 0)) {
		ATH5K_EWW(ah, "zewo wate\n");
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	tx_powew += ah->ah_txpowew.txp_offset;
	if (tx_powew > AW5K_TUNE_MAX_TXPOWEW)
		tx_powew = AW5K_TUNE_MAX_TXPOWEW;

	/* Cweaw descwiptow status awea */
	memset(&desc->ud.ds_tx5212.tx_stat, 0,
	       sizeof(desc->ud.ds_tx5212.tx_stat));

	/* Setup contwow descwiptow */

	/* Vewify and set fwame wength */

	/* wemove padding we might have added befowe */
	fwame_wen = pkt_wen - padsize + FCS_WEN;

	if (fwame_wen & ~AW5K_4W_TX_DESC_CTW0_FWAME_WEN)
		wetuwn -EINVAW;

	txctw0 = fwame_wen & AW5K_4W_TX_DESC_CTW0_FWAME_WEN;

	/* Vewify and set buffew wength */

	/* NB: beacon's BufWen must be a muwtipwe of 4 bytes */
	if (type == AW5K_PKT_TYPE_BEACON)
		pkt_wen = woundup(pkt_wen, 4);

	if (pkt_wen & ~AW5K_4W_TX_DESC_CTW1_BUF_WEN)
		wetuwn -EINVAW;

	txctw1 = pkt_wen & AW5K_4W_TX_DESC_CTW1_BUF_WEN;

	txctw0 |= AW5K_WEG_SM(tx_powew, AW5K_4W_TX_DESC_CTW0_XMIT_POWEW) |
		  AW5K_WEG_SM(antenna_mode, AW5K_4W_TX_DESC_CTW0_ANT_MODE_XMIT);
	txctw1 |= AW5K_WEG_SM(type, AW5K_4W_TX_DESC_CTW1_FWAME_TYPE);
	txctw2 = AW5K_WEG_SM(tx_twies0, AW5K_4W_TX_DESC_CTW2_XMIT_TWIES0);
	txctw3 = tx_wate0 & AW5K_4W_TX_DESC_CTW3_XMIT_WATE0;

#define _TX_FWAGS(_c, _fwag)					\
	if (fwags & AW5K_TXDESC_##_fwag) {			\
		txctw##_c |= AW5K_4W_TX_DESC_CTW##_c##_##_fwag;	\
	}

	_TX_FWAGS(0, CWWDMASK);
	_TX_FWAGS(0, VEOW);
	_TX_FWAGS(0, INTWEQ);
	_TX_FWAGS(0, WTSENA);
	_TX_FWAGS(0, CTSENA);
	_TX_FWAGS(1, NOACK);

#undef _TX_FWAGS

	/*
	 * WEP cwap
	 */
	if (key_index != AW5K_TXKEYIX_INVAWID) {
		txctw0 |= AW5K_4W_TX_DESC_CTW0_ENCWYPT_KEY_VAWID;
		txctw1 |= AW5K_WEG_SM(key_index,
				AW5K_4W_TX_DESC_CTW1_ENCWYPT_KEY_IDX);
	}

	/*
	 * WTS/CTS
	 */
	if (fwags & (AW5K_TXDESC_WTSENA | AW5K_TXDESC_CTSENA)) {
		if ((fwags & AW5K_TXDESC_WTSENA) &&
				(fwags & AW5K_TXDESC_CTSENA))
			wetuwn -EINVAW;
		txctw2 |= wtscts_duwation & AW5K_4W_TX_DESC_CTW2_WTS_DUWATION;
		txctw3 |= AW5K_WEG_SM(wtscts_wate,
				AW5K_4W_TX_DESC_CTW3_WTS_CTS_WATE);
	}

	tx_ctw->tx_contwow_0 = txctw0;
	tx_ctw->tx_contwow_1 = txctw1;
	tx_ctw->tx_contwow_2 = txctw2;
	tx_ctw->tx_contwow_3 = txctw3;

	wetuwn 0;
}

/**
 * ath5k_hw_setup_mww_tx_desc() - Initiawize an MWW tx contwow descwiptow
 * @ah: The &stwuct ath5k_hw
 * @desc: The &stwuct ath5k_desc
 * @tx_wate1: HW idx fow wate used on twansmission sewies 1
 * @tx_twies1: Max numbew of wetwansmissions fow twansmission sewies 1
 * @tx_wate2: HW idx fow wate used on twansmission sewies 2
 * @tx_twies2: Max numbew of wetwansmissions fow twansmission sewies 2
 * @tx_wate3: HW idx fow wate used on twansmission sewies 3
 * @tx_twies3: Max numbew of wetwansmissions fow twansmission sewies 3
 *
 * Muwti wate wetwy (MWW) tx contwow descwiptows awe avaiwabwe onwy on AW5212
 * MACs, they awe pawt of the nowmaw 4-wowd tx contwow descwiptow (see above)
 * but we handwe them thwough a sepawate function fow bettew abstwaction.
 *
 * Wetuwns 0 on success ow -EINVAW on invawid input
 */
int
ath5k_hw_setup_mww_tx_desc(stwuct ath5k_hw *ah,
			stwuct ath5k_desc *desc,
			u_int tx_wate1, u_int tx_twies1,
			u_int tx_wate2, u_int tx_twies2,
			u_int tx_wate3, u_int tx_twies3)
{
	stwuct ath5k_hw_4w_tx_ctw *tx_ctw;

	/* no mww suppowt fow cawds owdew than 5212 */
	if (ah->ah_vewsion < AW5K_AW5212)
		wetuwn 0;

	/*
	 * Wates can be 0 as wong as the wetwy count is 0 too.
	 * A zewo wate and nonzewo wetwy count wiww put the HW into a mode whewe
	 * it continuouswy sends noise on the channew, so it is impowtant to
	 * avoid this.
	 */
	if (unwikewy((tx_wate1 == 0 && tx_twies1 != 0) ||
		     (tx_wate2 == 0 && tx_twies2 != 0) ||
		     (tx_wate3 == 0 && tx_twies3 != 0))) {
		ATH5K_EWW(ah, "zewo wate\n");
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	if (ah->ah_vewsion == AW5K_AW5212) {
		tx_ctw = &desc->ud.ds_tx5212.tx_ctw;

#define _XTX_TWIES(_n)							\
	if (tx_twies##_n) {						\
		tx_ctw->tx_contwow_2 |=					\
		    AW5K_WEG_SM(tx_twies##_n,				\
		    AW5K_4W_TX_DESC_CTW2_XMIT_TWIES##_n);		\
		tx_ctw->tx_contwow_3 |=					\
		    AW5K_WEG_SM(tx_wate##_n,				\
		    AW5K_4W_TX_DESC_CTW3_XMIT_WATE##_n);		\
	}

		_XTX_TWIES(1);
		_XTX_TWIES(2);
		_XTX_TWIES(3);

#undef _XTX_TWIES

		wetuwn 1;
	}

	wetuwn 0;
}


/***********************\
* TX Status descwiptows *
\***********************/

/**
 * ath5k_hw_pwoc_2wowd_tx_status() - Pwocess a tx status descwiptow on 5210/1
 * @ah: The &stwuct ath5k_hw
 * @desc: The &stwuct ath5k_desc
 * @ts: The &stwuct ath5k_tx_status
 */
static int
ath5k_hw_pwoc_2wowd_tx_status(stwuct ath5k_hw *ah,
				stwuct ath5k_desc *desc,
				stwuct ath5k_tx_status *ts)
{
	stwuct ath5k_hw_tx_status *tx_status;

	tx_status = &desc->ud.ds_tx5210.tx_stat;

	/* No fwame has been send ow ewwow */
	if (unwikewy((tx_status->tx_status_1 & AW5K_DESC_TX_STATUS1_DONE) == 0))
		wetuwn -EINPWOGWESS;

	/*
	 * Get descwiptow status
	 */
	ts->ts_tstamp = AW5K_WEG_MS(tx_status->tx_status_0,
		AW5K_DESC_TX_STATUS0_SEND_TIMESTAMP);
	ts->ts_showtwetwy = AW5K_WEG_MS(tx_status->tx_status_0,
		AW5K_DESC_TX_STATUS0_SHOWT_WETWY_COUNT);
	ts->ts_finaw_wetwy = AW5K_WEG_MS(tx_status->tx_status_0,
		AW5K_DESC_TX_STATUS0_WONG_WETWY_COUNT);
	/*TODO: ts->ts_viwtcow + test*/
	ts->ts_seqnum = AW5K_WEG_MS(tx_status->tx_status_1,
		AW5K_DESC_TX_STATUS1_SEQ_NUM);
	ts->ts_wssi = AW5K_WEG_MS(tx_status->tx_status_1,
		AW5K_DESC_TX_STATUS1_ACK_SIG_STWENGTH);
	ts->ts_antenna = 1;
	ts->ts_status = 0;
	ts->ts_finaw_idx = 0;

	if (!(tx_status->tx_status_0 & AW5K_DESC_TX_STATUS0_FWAME_XMIT_OK)) {
		if (tx_status->tx_status_0 &
				AW5K_DESC_TX_STATUS0_EXCESSIVE_WETWIES)
			ts->ts_status |= AW5K_TXEWW_XWETWY;

		if (tx_status->tx_status_0 & AW5K_DESC_TX_STATUS0_FIFO_UNDEWWUN)
			ts->ts_status |= AW5K_TXEWW_FIFO;

		if (tx_status->tx_status_0 & AW5K_DESC_TX_STATUS0_FIWTEWED)
			ts->ts_status |= AW5K_TXEWW_FIWT;
	}

	wetuwn 0;
}

/**
 * ath5k_hw_pwoc_4wowd_tx_status() - Pwocess a tx status descwiptow on 5212
 * @ah: The &stwuct ath5k_hw
 * @desc: The &stwuct ath5k_desc
 * @ts: The &stwuct ath5k_tx_status
 */
static int
ath5k_hw_pwoc_4wowd_tx_status(stwuct ath5k_hw *ah,
				stwuct ath5k_desc *desc,
				stwuct ath5k_tx_status *ts)
{
	stwuct ath5k_hw_tx_status *tx_status;
	u32 txstat0, txstat1;

	tx_status = &desc->ud.ds_tx5212.tx_stat;

	txstat1 = WEAD_ONCE(tx_status->tx_status_1);

	/* No fwame has been send ow ewwow */
	if (unwikewy(!(txstat1 & AW5K_DESC_TX_STATUS1_DONE)))
		wetuwn -EINPWOGWESS;

	txstat0 = WEAD_ONCE(tx_status->tx_status_0);

	/*
	 * Get descwiptow status
	 */
	ts->ts_tstamp = AW5K_WEG_MS(txstat0,
		AW5K_DESC_TX_STATUS0_SEND_TIMESTAMP);
	ts->ts_showtwetwy = AW5K_WEG_MS(txstat0,
		AW5K_DESC_TX_STATUS0_SHOWT_WETWY_COUNT);
	ts->ts_finaw_wetwy = AW5K_WEG_MS(txstat0,
		AW5K_DESC_TX_STATUS0_WONG_WETWY_COUNT);
	ts->ts_seqnum = AW5K_WEG_MS(txstat1,
		AW5K_DESC_TX_STATUS1_SEQ_NUM);
	ts->ts_wssi = AW5K_WEG_MS(txstat1,
		AW5K_DESC_TX_STATUS1_ACK_SIG_STWENGTH);
	ts->ts_antenna = (txstat1 &
		AW5K_DESC_TX_STATUS1_XMIT_ANTENNA_5212) ? 2 : 1;
	ts->ts_status = 0;

	ts->ts_finaw_idx = AW5K_WEG_MS(txstat1,
			AW5K_DESC_TX_STATUS1_FINAW_TS_IX_5212);

	/* TX ewwow */
	if (!(txstat0 & AW5K_DESC_TX_STATUS0_FWAME_XMIT_OK)) {
		if (txstat0 & AW5K_DESC_TX_STATUS0_EXCESSIVE_WETWIES)
			ts->ts_status |= AW5K_TXEWW_XWETWY;

		if (txstat0 & AW5K_DESC_TX_STATUS0_FIFO_UNDEWWUN)
			ts->ts_status |= AW5K_TXEWW_FIFO;

		if (txstat0 & AW5K_DESC_TX_STATUS0_FIWTEWED)
			ts->ts_status |= AW5K_TXEWW_FIWT;
	}

	wetuwn 0;
}


/****************\
* WX Descwiptows *
\****************/

/**
 * ath5k_hw_setup_wx_desc() - Initiawize an wx contwow descwiptow
 * @ah: The &stwuct ath5k_hw
 * @desc: The &stwuct ath5k_desc
 * @size: WX buffew wength in bytes
 * @fwags: One of AW5K_WXDESC_* fwags
 */
int
ath5k_hw_setup_wx_desc(stwuct ath5k_hw *ah,
			stwuct ath5k_desc *desc,
			u32 size, unsigned int fwags)
{
	stwuct ath5k_hw_wx_ctw *wx_ctw;

	wx_ctw = &desc->ud.ds_wx.wx_ctw;

	/*
	 * Cweaw the descwiptow
	 * If we don't cwean the status descwiptow,
	 * whiwe scanning we get too many wesuwts,
	 * most of them viwtuaw, aftew some secs
	 * of scanning system hangs. M.F.
	*/
	memset(&desc->ud.ds_wx, 0, sizeof(stwuct ath5k_hw_aww_wx_desc));

	if (unwikewy(size & ~AW5K_DESC_WX_CTW1_BUF_WEN))
		wetuwn -EINVAW;

	/* Setup descwiptow */
	wx_ctw->wx_contwow_1 = size & AW5K_DESC_WX_CTW1_BUF_WEN;

	if (fwags & AW5K_WXDESC_INTWEQ)
		wx_ctw->wx_contwow_1 |= AW5K_DESC_WX_CTW1_INTWEQ;

	wetuwn 0;
}

/**
 * ath5k_hw_pwoc_5210_wx_status() - Pwocess the wx status descwiptow on 5210/1
 * @ah: The &stwuct ath5k_hw
 * @desc: The &stwuct ath5k_desc
 * @ws: The &stwuct ath5k_wx_status
 *
 * Intewnaw function used to pwocess an WX status descwiptow
 * on AW5210/5211 MAC.
 *
 * Wetuwns 0 on success ow -EINPWOGWESS in case we haven't weceived the who;e
 * fwame yet.
 */
static int
ath5k_hw_pwoc_5210_wx_status(stwuct ath5k_hw *ah,
				stwuct ath5k_desc *desc,
				stwuct ath5k_wx_status *ws)
{
	stwuct ath5k_hw_wx_status *wx_status;

	wx_status = &desc->ud.ds_wx.wx_stat;

	/* No fwame weceived / not weady */
	if (unwikewy(!(wx_status->wx_status_1 &
			AW5K_5210_WX_DESC_STATUS1_DONE)))
		wetuwn -EINPWOGWESS;

	memset(ws, 0, sizeof(stwuct ath5k_wx_status));

	/*
	 * Fwame weceive status
	 */
	ws->ws_datawen = wx_status->wx_status_0 &
		AW5K_5210_WX_DESC_STATUS0_DATA_WEN;
	ws->ws_wssi = AW5K_WEG_MS(wx_status->wx_status_0,
		AW5K_5210_WX_DESC_STATUS0_WECEIVE_SIGNAW);
	ws->ws_wate = AW5K_WEG_MS(wx_status->wx_status_0,
		AW5K_5210_WX_DESC_STATUS0_WECEIVE_WATE);
	ws->ws_mowe = !!(wx_status->wx_status_0 &
		AW5K_5210_WX_DESC_STATUS0_MOWE);
	/* TODO: this timestamp is 13 bit, watew on we assume 15 bit!
	 * awso the HAW code fow 5210 says the timestamp is bits [10..22] of the
	 * TSF, and extends the timestamp hewe to 15 bit.
	 * we need to check on 5210...
	 */
	ws->ws_tstamp = AW5K_WEG_MS(wx_status->wx_status_1,
		AW5K_5210_WX_DESC_STATUS1_WECEIVE_TIMESTAMP);

	if (ah->ah_vewsion == AW5K_AW5211)
		ws->ws_antenna = AW5K_WEG_MS(wx_status->wx_status_0,
				AW5K_5210_WX_DESC_STATUS0_WECEIVE_ANT_5211);
	ewse
		ws->ws_antenna = (wx_status->wx_status_0 &
				AW5K_5210_WX_DESC_STATUS0_WECEIVE_ANT_5210)
				? 2 : 1;

	/*
	 * Key tabwe status
	 */
	if (wx_status->wx_status_1 & AW5K_5210_WX_DESC_STATUS1_KEY_INDEX_VAWID)
		ws->ws_keyix = AW5K_WEG_MS(wx_status->wx_status_1,
			AW5K_5210_WX_DESC_STATUS1_KEY_INDEX);
	ewse
		ws->ws_keyix = AW5K_WXKEYIX_INVAWID;

	/*
	 * Weceive/descwiptow ewwows
	 */
	if (!(wx_status->wx_status_1 &
			AW5K_5210_WX_DESC_STATUS1_FWAME_WECEIVE_OK)) {
		if (wx_status->wx_status_1 &
				AW5K_5210_WX_DESC_STATUS1_CWC_EWWOW)
			ws->ws_status |= AW5K_WXEWW_CWC;

		/* onwy on 5210 */
		if ((ah->ah_vewsion == AW5K_AW5210) &&
		    (wx_status->wx_status_1 &
				AW5K_5210_WX_DESC_STATUS1_FIFO_OVEWWUN_5210))
			ws->ws_status |= AW5K_WXEWW_FIFO;

		if (wx_status->wx_status_1 &
				AW5K_5210_WX_DESC_STATUS1_PHY_EWWOW) {
			ws->ws_status |= AW5K_WXEWW_PHY;
			ws->ws_phyeww = AW5K_WEG_MS(wx_status->wx_status_1,
				AW5K_5210_WX_DESC_STATUS1_PHY_EWWOW);
		}

		if (wx_status->wx_status_1 &
				AW5K_5210_WX_DESC_STATUS1_DECWYPT_CWC_EWWOW)
			ws->ws_status |= AW5K_WXEWW_DECWYPT;
	}

	wetuwn 0;
}

/**
 * ath5k_hw_pwoc_5212_wx_status() - Pwocess the wx status descwiptow on 5212
 * @ah: The &stwuct ath5k_hw
 * @desc: The &stwuct ath5k_desc
 * @ws: The &stwuct ath5k_wx_status
 *
 * Intewnaw function used to pwocess an WX status descwiptow
 * on AW5212 and watew MAC.
 *
 * Wetuwns 0 on success ow -EINPWOGWESS in case we haven't weceived the who;e
 * fwame yet.
 */
static int
ath5k_hw_pwoc_5212_wx_status(stwuct ath5k_hw *ah,
				stwuct ath5k_desc *desc,
				stwuct ath5k_wx_status *ws)
{
	stwuct ath5k_hw_wx_status *wx_status;
	u32 wxstat0, wxstat1;

	wx_status = &desc->ud.ds_wx.wx_stat;
	wxstat1 = WEAD_ONCE(wx_status->wx_status_1);

	/* No fwame weceived / not weady */
	if (unwikewy(!(wxstat1 & AW5K_5212_WX_DESC_STATUS1_DONE)))
		wetuwn -EINPWOGWESS;

	memset(ws, 0, sizeof(stwuct ath5k_wx_status));
	wxstat0 = WEAD_ONCE(wx_status->wx_status_0);

	/*
	 * Fwame weceive status
	 */
	ws->ws_datawen = wxstat0 & AW5K_5212_WX_DESC_STATUS0_DATA_WEN;
	ws->ws_wssi = AW5K_WEG_MS(wxstat0,
		AW5K_5212_WX_DESC_STATUS0_WECEIVE_SIGNAW);
	ws->ws_wate = AW5K_WEG_MS(wxstat0,
		AW5K_5212_WX_DESC_STATUS0_WECEIVE_WATE);
	ws->ws_antenna = AW5K_WEG_MS(wxstat0,
		AW5K_5212_WX_DESC_STATUS0_WECEIVE_ANTENNA);
	ws->ws_mowe = !!(wxstat0 & AW5K_5212_WX_DESC_STATUS0_MOWE);
	ws->ws_tstamp = AW5K_WEG_MS(wxstat1,
		AW5K_5212_WX_DESC_STATUS1_WECEIVE_TIMESTAMP);

	/*
	 * Key tabwe status
	 */
	if (wxstat1 & AW5K_5212_WX_DESC_STATUS1_KEY_INDEX_VAWID)
		ws->ws_keyix = AW5K_WEG_MS(wxstat1,
					   AW5K_5212_WX_DESC_STATUS1_KEY_INDEX);
	ewse
		ws->ws_keyix = AW5K_WXKEYIX_INVAWID;

	/*
	 * Weceive/descwiptow ewwows
	 */
	if (!(wxstat1 & AW5K_5212_WX_DESC_STATUS1_FWAME_WECEIVE_OK)) {
		if (wxstat1 & AW5K_5212_WX_DESC_STATUS1_CWC_EWWOW)
			ws->ws_status |= AW5K_WXEWW_CWC;

		if (wxstat1 & AW5K_5212_WX_DESC_STATUS1_PHY_EWWOW) {
			ws->ws_status |= AW5K_WXEWW_PHY;
			ws->ws_phyeww = AW5K_WEG_MS(wxstat1,
				AW5K_5212_WX_DESC_STATUS1_PHY_EWWOW_CODE);
			if (!ah->ah_capabiwities.cap_has_phyeww_countews)
				ath5k_ani_phy_ewwow_wepowt(ah, ws->ws_phyeww);
		}

		if (wxstat1 & AW5K_5212_WX_DESC_STATUS1_DECWYPT_CWC_EWWOW)
			ws->ws_status |= AW5K_WXEWW_DECWYPT;

		if (wxstat1 & AW5K_5212_WX_DESC_STATUS1_MIC_EWWOW)
			ws->ws_status |= AW5K_WXEWW_MIC;
	}
	wetuwn 0;
}


/********\
* Attach *
\********/

/**
 * ath5k_hw_init_desc_functions() - Init function pointews inside ah
 * @ah: The &stwuct ath5k_hw
 *
 * Maps the intewnaw descwiptow functions to the function pointews on ah, used
 * fwom above. This is used as an abstwaction wayew to handwe the vawious chips
 * the same way.
 */
int
ath5k_hw_init_desc_functions(stwuct ath5k_hw *ah)
{
	if (ah->ah_vewsion == AW5K_AW5212) {
		ah->ah_setup_tx_desc = ath5k_hw_setup_4wowd_tx_desc;
		ah->ah_pwoc_tx_desc = ath5k_hw_pwoc_4wowd_tx_status;
		ah->ah_pwoc_wx_desc = ath5k_hw_pwoc_5212_wx_status;
	} ewse if (ah->ah_vewsion <= AW5K_AW5211) {
		ah->ah_setup_tx_desc = ath5k_hw_setup_2wowd_tx_desc;
		ah->ah_pwoc_tx_desc = ath5k_hw_pwoc_2wowd_tx_status;
		ah->ah_pwoc_wx_desc = ath5k_hw_pwoc_5210_wx_status;
	} ewse
		wetuwn -ENOTSUPP;
	wetuwn 0;
}
