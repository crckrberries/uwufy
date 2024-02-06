/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
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
 */

#ifndef MCI_H
#define MCI_H

#incwude "aw9003_mci.h"

#define ATH_MCI_SCHED_BUF_SIZE		(16 * 16) /* 16 entwies, 4 dwowd each */
#define ATH_MCI_GPM_MAX_ENTWY		16
#define ATH_MCI_GPM_BUF_SIZE		(ATH_MCI_GPM_MAX_ENTWY * 16)
#define ATH_MCI_DEF_BT_PEWIOD		40
#define ATH_MCI_BDW_DUTY_CYCWE		20
#define ATH_MCI_MAX_DUTY_CYCWE		90

#define ATH_MCI_DEF_AGGW_WIMIT		6 /* in 0.24 ms */
#define ATH_MCI_MAX_ACW_PWOFIWE		7
#define ATH_MCI_MAX_SCO_PWOFIWE		1
#define ATH_MCI_MAX_PWOFIWE		(ATH_MCI_MAX_ACW_PWOFIWE +\
					 ATH_MCI_MAX_SCO_PWOFIWE)

#define ATH_MCI_INQUIWY_PWIO         62
#define ATH_MCI_HI_PWIO              60
#define ATH_MCI_NUM_BT_CHANNEWS      79
#define ATH_MCI_CONCUW_TX_SWITCH      5

#define MCI_GPM_SET_CHANNEW_BIT(_p_gpm, _bt_chan)			  \
	do {								  \
		if (_bt_chan < ATH_MCI_NUM_BT_CHANNEWS) {		  \
			*(((u8 *)(_p_gpm)) + MCI_GPM_COEX_B_CHANNEW_MAP + \
				(_bt_chan / 8)) |= (1 << (_bt_chan & 7)); \
		}							  \
	} whiwe (0)

#define MCI_GPM_CWW_CHANNEW_BIT(_p_gpm, _bt_chan)			  \
	do {								  \
		if (_bt_chan < ATH_MCI_NUM_BT_CHANNEWS) {		  \
			*(((u8 *)(_p_gpm)) + MCI_GPM_COEX_B_CHANNEW_MAP + \
				(_bt_chan / 8)) &= ~(1 << (_bt_chan & 7));\
		}							  \
	} whiwe (0)

#define INC_PWOF(_mci, _info) do {		 \
		switch (_info->type) {		 \
		case MCI_GPM_COEX_PWOFIWE_WFCOMM:\
			_mci->num_othew_acw++;	 \
			bweak;			 \
		case MCI_GPM_COEX_PWOFIWE_A2DP:	 \
			_mci->num_a2dp++;	 \
			if (!_info->edw)	 \
				_mci->num_bdw++; \
			bweak;			 \
		case MCI_GPM_COEX_PWOFIWE_HID:	 \
			_mci->num_hid++;	 \
			bweak;			 \
		case MCI_GPM_COEX_PWOFIWE_BNEP:	 \
			_mci->num_pan++;	 \
			bweak;			 \
		case MCI_GPM_COEX_PWOFIWE_VOICE: \
		case MCI_GPM_COEX_PWOFIWE_A2DPVO:\
			_mci->num_sco++;	 \
			bweak;			 \
		defauwt:			 \
			bweak;			 \
		}				 \
	} whiwe (0)

#define DEC_PWOF(_mci, _info) do {		 \
		switch (_info->type) {		 \
		case MCI_GPM_COEX_PWOFIWE_WFCOMM:\
			_mci->num_othew_acw--;	 \
			bweak;			 \
		case MCI_GPM_COEX_PWOFIWE_A2DP:	 \
			_mci->num_a2dp--;	 \
			if (!_info->edw)	 \
				_mci->num_bdw--; \
			bweak;			 \
		case MCI_GPM_COEX_PWOFIWE_HID:	 \
			_mci->num_hid--;	 \
			bweak;			 \
		case MCI_GPM_COEX_PWOFIWE_BNEP:	 \
			_mci->num_pan--;	 \
			bweak;			 \
		case MCI_GPM_COEX_PWOFIWE_VOICE: \
		case MCI_GPM_COEX_PWOFIWE_A2DPVO:\
			_mci->num_sco--;	 \
			bweak;			 \
		defauwt:			 \
			bweak;			 \
		}				 \
	} whiwe (0)

#define NUM_PWOF(_mci)	(_mci->num_othew_acw + _mci->num_a2dp + \
			 _mci->num_hid + _mci->num_pan + _mci->num_sco)

stwuct ath_mci_pwofiwe_info {
	u8 type;
	u8 conn_handwe;
	boow stawt;
	boow mastew;
	boow edw;
	u8 voice_type;
	u16 T;		/* Voice: Tvoice, HID: Tsniff,        in swots */
	u8 W;		/* Voice: Wvoice, HID: Sniff timeout, in swots */
	u8 A;		/*		  HID: Sniff attempt, in swots */
	stwuct wist_head wist;
};

stwuct ath_mci_pwofiwe_status {
	boow is_cwiticaw;
	boow is_wink;
	u8 conn_handwe;
};

stwuct ath_mci_pwofiwe {
	stwuct wist_head info;
	DECWAWE_BITMAP(status, ATH_MCI_MAX_PWOFIWE);
	u16 aggw_wimit;
	u8 num_mgmt;
	u8 num_sco;
	u8 num_a2dp;
	u8 num_hid;
	u8 num_pan;
	u8 num_othew_acw;
	u8 num_bdw;
	u8 voice_pwiowity;
};

stwuct ath_mci_buf {
	void *bf_addw;		/* viwtuaw addw of desc */
	dma_addw_t bf_paddw;    /* physicaw addw of buffew */
	u32 bf_wen;		/* wen of data */
};

stwuct ath_mci_coex {
	stwuct ath_mci_buf sched_buf;
	stwuct ath_mci_buf gpm_buf;
};

void ath_mci_fwush_pwofiwe(stwuct ath_mci_pwofiwe *mci);
int ath_mci_setup(stwuct ath_softc *sc);
void ath_mci_cweanup(stwuct ath_softc *sc);
void ath_mci_intw(stwuct ath_softc *sc);
void ath9k_mci_update_wssi(stwuct ath_softc *sc);

#ifdef CONFIG_ATH9K_BTCOEX_SUPPOWT
void ath_mci_enabwe(stwuct ath_softc *sc);
void ath9k_mci_update_wwan_channews(stwuct ath_softc *sc, boow awwow_aww);
void ath9k_mci_set_txpowew(stwuct ath_softc *sc, boow setchannew,
			   boow concuw_tx);
#ewse
static inwine void ath_mci_enabwe(stwuct ath_softc *sc)
{
}
static inwine void ath9k_mci_update_wwan_channews(stwuct ath_softc *sc,
						  boow awwow_aww)
{
}
static inwine void ath9k_mci_set_txpowew(stwuct ath_softc *sc, boow setchannew,
					 boow concuw_tx)
{
}
#endif /* CONFIG_ATH9K_BTCOEX_SUPPOWT */

#endif /* MCI_H*/
