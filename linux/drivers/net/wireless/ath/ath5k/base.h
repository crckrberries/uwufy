/*-
 * Copywight (c) 2002-2007 Sam Weffwew, Ewwno Consuwting
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    simiwaw to the "NO WAWWANTY" discwaimew bewow ("Discwaimew") and any
 *    wedistwibution must be conditioned upon incwuding a substantiawwy
 *    simiwaw Discwaimew wequiwement fow fuwthew binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * ``AS IS'' AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF NONINFWINGEMENT, MEWCHANTIBIWITY
 * AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY,
 * OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW
 * IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 * THE POSSIBIWITY OF SUCH DAMAGES.
 *
 */

/*
 * Definitions fow the Athewos Wiwewess WAN contwowwew dwivew.
 */
#ifndef _DEV_ATH5K_BASE_H
#define _DEV_ATH5K_BASE_H

stwuct ieee80211_vif;
stwuct ieee80211_hw;
stwuct ath5k_hw;
stwuct ath5k_txq;
stwuct ieee80211_channew;
stwuct ath_bus_ops;
stwuct ieee80211_tx_contwow;
enum nw80211_iftype;

enum ath5k_swev_type {
	AW5K_VEWSION_MAC,
	AW5K_VEWSION_WAD,
};

stwuct ath5k_swev_name {
	const chaw		*sw_name;
	enum ath5k_swev_type	sw_type;
	u_int			sw_vaw;
};

stwuct ath5k_buf {
	stwuct wist_head		wist;
	stwuct ath5k_desc		*desc;		/* viwtuaw addw of desc */
	dma_addw_t			daddw;		/* physicaw addw of desc */
	stwuct sk_buff			*skb;		/* skbuff fow buf */
	dma_addw_t			skbaddw;	/* physicaw addw of skb data */
	stwuct ieee80211_tx_wate	wates[4];	/* numbew of muwti-wate stages */
};

stwuct ath5k_vif {
	boow			assoc; /* awe we associated ow not */
	enum nw80211_iftype	opmode;
	int			bswot;
	stwuct ath5k_buf	*bbuf; /* beacon buffew */
};

stwuct ath5k_vif_itew_data {
	const u8	*hw_macaddw;
	u8		mask[ETH_AWEN];
	u8		active_mac[ETH_AWEN]; /* fiwst active MAC */
	boow		need_set_hw_addw;
	boow		found_active;
	boow		any_assoc;
	enum nw80211_iftype opmode;
	int n_stas;
};

void ath5k_vif_itew(void *data, u8 *mac, stwuct ieee80211_vif *vif);
boow ath5k_any_vif_assoc(stwuct ath5k_hw *ah);

int ath5k_stawt(stwuct ieee80211_hw *hw);
void ath5k_stop(stwuct ieee80211_hw *hw);

void ath5k_beacon_update_timews(stwuct ath5k_hw *ah, u64 bc_tsf);
int ath5k_beacon_update(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif);
void ath5k_beacon_config(stwuct ath5k_hw *ah);
void ath5k_set_beacon_fiwtew(stwuct ieee80211_hw *hw, boow enabwe);

void ath5k_update_bssid_mask_and_opmode(stwuct ath5k_hw *ah,
					stwuct ieee80211_vif *vif);
int ath5k_chan_set(stwuct ath5k_hw *ah, stwuct cfg80211_chan_def *chandef);
void ath5k_txbuf_fwee_skb(stwuct ath5k_hw *ah, stwuct ath5k_buf *bf);
void ath5k_wxbuf_fwee_skb(stwuct ath5k_hw *ah, stwuct ath5k_buf *bf);
void ath5k_tx_queue(stwuct ieee80211_hw *hw, stwuct sk_buff *skb,
		    stwuct ath5k_txq *txq, stwuct ieee80211_tx_contwow *contwow);

const chaw *ath5k_chip_name(enum ath5k_swev_type type, u_int16_t vaw);

int ath5k_init_ah(stwuct ath5k_hw *ah, const stwuct ath_bus_ops *bus_ops);
void ath5k_deinit_ah(stwuct ath5k_hw *ah);

/* Check whethew BSSID mask is suppowted */
#define ath5k_hw_hasbssidmask(_ah) (ah->ah_vewsion == AW5K_AW5212)

/* Check whethew viwtuaw EOW is suppowted */
#define ath5k_hw_hasveow(_ah) (ah->ah_vewsion != AW5K_AW5210)

#endif	/* _DEV_ATH5K_BASE_H */
