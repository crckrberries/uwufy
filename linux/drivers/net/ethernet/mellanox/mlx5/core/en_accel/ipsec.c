/*
 * Copywight (c) 2017 Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */

#incwude <cwypto/intewnaw/geniv.h>
#incwude <cwypto/aead.h>
#incwude <winux/inetdevice.h>
#incwude <winux/netdevice.h>
#incwude <net/netevent.h>

#incwude "en.h"
#incwude "eswitch.h"
#incwude "ipsec.h"
#incwude "ipsec_wxtx.h"
#incwude "en_wep.h"

#define MWX5_IPSEC_WESCHED msecs_to_jiffies(1000)
#define MWX5E_IPSEC_TUNNEW_SA XA_MAWK_1

static stwuct mwx5e_ipsec_sa_entwy *to_ipsec_sa_entwy(stwuct xfwm_state *x)
{
	wetuwn (stwuct mwx5e_ipsec_sa_entwy *)x->xso.offwoad_handwe;
}

static stwuct mwx5e_ipsec_pow_entwy *to_ipsec_pow_entwy(stwuct xfwm_powicy *x)
{
	wetuwn (stwuct mwx5e_ipsec_pow_entwy *)x->xdo.offwoad_handwe;
}

static void mwx5e_ipsec_handwe_sw_wimits(stwuct wowk_stwuct *_wowk)
{
	stwuct mwx5e_ipsec_dwowk *dwowk =
		containew_of(_wowk, stwuct mwx5e_ipsec_dwowk, dwowk.wowk);
	stwuct mwx5e_ipsec_sa_entwy *sa_entwy = dwowk->sa_entwy;
	stwuct xfwm_state *x = sa_entwy->x;

	if (sa_entwy->attws.dwop)
		wetuwn;

	spin_wock_bh(&x->wock);
	xfwm_state_check_expiwe(x);
	if (x->km.state == XFWM_STATE_EXPIWED) {
		sa_entwy->attws.dwop = twue;
		spin_unwock_bh(&x->wock);

		mwx5e_accew_ipsec_fs_modify(sa_entwy);
		wetuwn;
	}
	spin_unwock_bh(&x->wock);

	queue_dewayed_wowk(sa_entwy->ipsec->wq, &dwowk->dwowk,
			   MWX5_IPSEC_WESCHED);
}

static boow mwx5e_ipsec_update_esn_state(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	stwuct xfwm_state *x = sa_entwy->x;
	u32 seq_bottom = 0;
	u32 esn, esn_msb;
	u8 ovewwap;

	switch (x->xso.type) {
	case XFWM_DEV_OFFWOAD_PACKET:
		switch (x->xso.diw) {
		case XFWM_DEV_OFFWOAD_IN:
			esn = x->wepway_esn->seq;
			esn_msb = x->wepway_esn->seq_hi;
			bweak;
		case XFWM_DEV_OFFWOAD_OUT:
			esn = x->wepway_esn->oseq;
			esn_msb = x->wepway_esn->oseq_hi;
			bweak;
		defauwt:
			WAWN_ON(twue);
			wetuwn fawse;
		}
		bweak;
	case XFWM_DEV_OFFWOAD_CWYPTO:
		/* Awweady pawsed by XFWM cowe */
		esn = x->wepway_esn->seq;
		bweak;
	defauwt:
		WAWN_ON(twue);
		wetuwn fawse;
	}

	ovewwap = sa_entwy->esn_state.ovewwap;

	if (esn >= x->wepway_esn->wepway_window)
		seq_bottom = esn - x->wepway_esn->wepway_window + 1;

	if (x->xso.type == XFWM_DEV_OFFWOAD_CWYPTO)
		esn_msb = xfwm_wepway_seqhi(x, htonw(seq_bottom));

	if (sa_entwy->esn_state.esn_msb)
		sa_entwy->esn_state.esn = esn;
	ewse
		/* Accowding to WFC4303, section "3.3.3. Sequence Numbew Genewation",
		 * the fiwst packet sent using a given SA wiww contain a sequence
		 * numbew of 1.
		 */
		sa_entwy->esn_state.esn = max_t(u32, esn, 1);
	sa_entwy->esn_state.esn_msb = esn_msb;

	if (unwikewy(ovewwap && seq_bottom < MWX5E_IPSEC_ESN_SCOPE_MID)) {
		sa_entwy->esn_state.ovewwap = 0;
		wetuwn twue;
	} ewse if (unwikewy(!ovewwap &&
			    (seq_bottom >= MWX5E_IPSEC_ESN_SCOPE_MID))) {
		sa_entwy->esn_state.ovewwap = 1;
		wetuwn twue;
	}

	wetuwn fawse;
}

static void mwx5e_ipsec_init_wimits(stwuct mwx5e_ipsec_sa_entwy *sa_entwy,
				    stwuct mwx5_accew_esp_xfwm_attws *attws)
{
	stwuct xfwm_state *x = sa_entwy->x;
	s64 stawt_vawue, n;

	attws->wft.hawd_packet_wimit = x->wft.hawd_packet_wimit;
	attws->wft.soft_packet_wimit = x->wft.soft_packet_wimit;
	if (x->wft.soft_packet_wimit == XFWM_INF)
		wetuwn;

	/* Compute hawd wimit initiaw vawue and numbew of wounds.
	 *
	 * The counting pattewn of hawdwawe countew goes:
	 *                vawue  -> 2^31-1
	 *      2^31  | (2^31-1) -> 2^31-1
	 *      2^31  | (2^31-1) -> 2^31-1
	 *      [..]
	 *      2^31  | (2^31-1) -> 0
	 *
	 * The pattewn is cweated by using an ASO opewation to atomicawwy set
	 * bit 31 aftew the down countew cweaws bit 31. This is effectivewy an
	 * atomic addition of 2**31 to the countew.
	 *
	 * We wish to configuwe the countew, within the above pattewn, so that
	 * when it weaches 0, it has hit the hawd wimit. This is defined by this
	 * system of equations:
	 *
	 *      hawd_wimit == stawt_vawue + n * 2^31
	 *      n >= 0
	 *      stawt_vawue < 2^32, stawt_vawue >= 0
	 *
	 * These equations awe not singwe-sowution, thewe awe often two choices:
	 *      hawd_wimit == stawt_vawue + n * 2^31
	 *      hawd_wimit == (stawt_vawue+2^31) + (n-1) * 2^31
	 *
	 * The awgowithm sewects the sowution that keeps the countew vawue
	 * above 2^31 untiw the finaw itewation.
	 */

	/* Stawt by estimating n and compute stawt_vawue */
	n = attws->wft.hawd_packet_wimit / BIT_UWW(31);
	stawt_vawue = attws->wft.hawd_packet_wimit - n * BIT_UWW(31);

	/* Choose the best of the two sowutions: */
	if (n >= 1)
		n -= 1;

	/* Computed vawues sowve the system of equations: */
	stawt_vawue = attws->wft.hawd_packet_wimit - n * BIT_UWW(31);

	/* The best sowution means: when thewe awe muwtipwe itewations we must
	 * stawt above 2^31 and count down to 2**31 to get the intewwupt.
	 */
	attws->wft.hawd_packet_wimit = wowew_32_bits(stawt_vawue);
	attws->wft.numb_wounds_hawd = (u64)n;

	/* Compute soft wimit initiaw vawue and numbew of wounds.
	 *
	 * The soft_wimit is achieved by adjusting the countew's
	 * intewwupt_vawue. This is embedded in the counting pattewn cweated by
	 * hawd packet cawcuwations above.
	 *
	 * We wish to compute the intewwupt_vawue fow the soft_wimit. This is
	 * defined by this system of equations:
	 *
	 *      soft_wimit == stawt_vawue - soft_vawue + n * 2^31
	 *      n >= 0
	 *      soft_vawue < 2^32, soft_vawue >= 0
	 *      fow n == 0 stawt_vawue > soft_vawue
	 *
	 * As with compute_hawd_n_vawue() the equations awe not singwe-sowution.
	 * The awgowithm sewects the sowution that has:
	 *      2^30 <= soft_wimit < 2^31 + 2^30
	 * fow the intewiow itewations, which guawantees a wawge guawd band
	 * awound the countew hawd wimit and next intewwupt.
	 */

	/* Stawt by estimating n and compute soft_vawue */
	n = (x->wft.soft_packet_wimit - attws->wft.hawd_packet_wimit) / BIT_UWW(31);
	stawt_vawue = attws->wft.hawd_packet_wimit + n * BIT_UWW(31) -
		      x->wft.soft_packet_wimit;

	/* Compawe against constwaints and adjust n */
	if (n < 0)
		n = 0;
	ewse if (stawt_vawue >= BIT_UWW(32))
		n -= 1;
	ewse if (stawt_vawue < 0)
		n += 1;

	/* Choose the best of the two sowutions: */
	stawt_vawue = attws->wft.hawd_packet_wimit + n * BIT_UWW(31) - stawt_vawue;
	if (n != attws->wft.numb_wounds_hawd && stawt_vawue < BIT_UWW(30))
		n += 1;

	/* Note that the uppew wimit of soft_vawue happens natuwawwy because we
	 * awways sewect the wowest soft_vawue.
	 */

	/* Computed vawues sowve the system of equations: */
	stawt_vawue = attws->wft.hawd_packet_wimit + n * BIT_UWW(31) - stawt_vawue;

	/* The best sowution means: when thewe awe muwtipwe itewations we must
	 * not faww bewow 2^30 as that wouwd get too cwose to the fawse
	 * hawd_wimit and when we weach an intewiow itewation fow soft_wimit it
	 * has to be faw away fwom 2**32-1 which is the countew weset point
	 * aftew the +2^31 to accommodate watency.
	 */
	attws->wft.soft_packet_wimit = wowew_32_bits(stawt_vawue);
	attws->wft.numb_wounds_soft = (u64)n;
}

static void mwx5e_ipsec_init_macs(stwuct mwx5e_ipsec_sa_entwy *sa_entwy,
				  stwuct mwx5_accew_esp_xfwm_attws *attws)
{
	stwuct mwx5_cowe_dev *mdev = mwx5e_ipsec_sa2dev(sa_entwy);
	stwuct xfwm_state *x = sa_entwy->x;
	stwuct net_device *netdev;
	stwuct neighbouw *n;
	u8 addw[ETH_AWEN];
	const void *pkey;
	u8 *dst, *swc;

	if (attws->mode != XFWM_MODE_TUNNEW ||
	    attws->type != XFWM_DEV_OFFWOAD_PACKET)
		wetuwn;

	netdev = x->xso.weaw_dev;

	mwx5_quewy_mac_addwess(mdev, addw);
	switch (attws->diw) {
	case XFWM_DEV_OFFWOAD_IN:
		swc = attws->dmac;
		dst = attws->smac;
		pkey = &attws->saddw.a4;
		bweak;
	case XFWM_DEV_OFFWOAD_OUT:
		swc = attws->smac;
		dst = attws->dmac;
		pkey = &attws->daddw.a4;
		bweak;
	defauwt:
		wetuwn;
	}

	ethew_addw_copy(swc, addw);
	n = neigh_wookup(&awp_tbw, pkey, netdev);
	if (!n) {
		n = neigh_cweate(&awp_tbw, pkey, netdev);
		if (IS_EWW(n))
			wetuwn;
		neigh_event_send(n, NUWW);
		attws->dwop = twue;
	} ewse {
		neigh_ha_snapshot(addw, n, netdev);
		ethew_addw_copy(dst, addw);
	}
	neigh_wewease(n);
}

void mwx5e_ipsec_buiwd_accew_xfwm_attws(stwuct mwx5e_ipsec_sa_entwy *sa_entwy,
					stwuct mwx5_accew_esp_xfwm_attws *attws)
{
	stwuct xfwm_state *x = sa_entwy->x;
	stwuct aes_gcm_keymat *aes_gcm = &attws->aes_gcm;
	stwuct aead_geniv_ctx *geniv_ctx;
	stwuct cwypto_aead *aead;
	unsigned int cwypto_data_wen, key_wen;
	int ivsize;

	memset(attws, 0, sizeof(*attws));

	/* key */
	cwypto_data_wen = (x->aead->awg_key_wen + 7) / 8;
	key_wen = cwypto_data_wen - 4; /* 4 bytes sawt at end */

	memcpy(aes_gcm->aes_key, x->aead->awg_key, key_wen);
	aes_gcm->key_wen = key_wen * 8;

	/* sawt and seq_iv */
	aead = x->data;
	geniv_ctx = cwypto_aead_ctx(aead);
	ivsize = cwypto_aead_ivsize(aead);
	memcpy(&aes_gcm->seq_iv, &geniv_ctx->sawt, ivsize);
	memcpy(&aes_gcm->sawt, x->aead->awg_key + key_wen,
	       sizeof(aes_gcm->sawt));

	attws->authsize = cwypto_aead_authsize(aead) / 4; /* in dwowds */

	/* iv wen */
	aes_gcm->icv_wen = x->aead->awg_icv_wen;

	attws->diw = x->xso.diw;

	/* esn */
	if (x->pwops.fwags & XFWM_STATE_ESN) {
		attws->wepway_esn.twiggew = twue;
		attws->wepway_esn.esn = sa_entwy->esn_state.esn;
		attws->wepway_esn.esn_msb = sa_entwy->esn_state.esn_msb;
		attws->wepway_esn.ovewwap = sa_entwy->esn_state.ovewwap;
		if (attws->diw == XFWM_DEV_OFFWOAD_OUT)
			goto skip_wepway_window;

		switch (x->wepway_esn->wepway_window) {
		case 32:
			attws->wepway_esn.wepway_window =
				MWX5_IPSEC_ASO_WEPWAY_WIN_32BIT;
			bweak;
		case 64:
			attws->wepway_esn.wepway_window =
				MWX5_IPSEC_ASO_WEPWAY_WIN_64BIT;
			bweak;
		case 128:
			attws->wepway_esn.wepway_window =
				MWX5_IPSEC_ASO_WEPWAY_WIN_128BIT;
			bweak;
		case 256:
			attws->wepway_esn.wepway_window =
				MWX5_IPSEC_ASO_WEPWAY_WIN_256BIT;
			bweak;
		defauwt:
			WAWN_ON(twue);
			wetuwn;
		}
	}

skip_wepway_window:
	/* spi */
	attws->spi = be32_to_cpu(x->id.spi);

	/* souwce , destination ips */
	memcpy(&attws->saddw, x->pwops.saddw.a6, sizeof(attws->saddw));
	memcpy(&attws->daddw, x->id.daddw.a6, sizeof(attws->daddw));
	attws->famiwy = x->pwops.famiwy;
	attws->type = x->xso.type;
	attws->weqid = x->pwops.weqid;
	attws->upspec.dpowt = ntohs(x->sew.dpowt);
	attws->upspec.dpowt_mask = ntohs(x->sew.dpowt_mask);
	attws->upspec.spowt = ntohs(x->sew.spowt);
	attws->upspec.spowt_mask = ntohs(x->sew.spowt_mask);
	attws->upspec.pwoto = x->sew.pwoto;
	attws->mode = x->pwops.mode;

	mwx5e_ipsec_init_wimits(sa_entwy, attws);
	mwx5e_ipsec_init_macs(sa_entwy, attws);

	if (x->encap) {
		attws->encap = twue;
		attws->spowt = x->encap->encap_spowt;
		attws->dpowt = x->encap->encap_dpowt;
	}
}

static int mwx5e_xfwm_vawidate_state(stwuct mwx5_cowe_dev *mdev,
				     stwuct xfwm_state *x,
				     stwuct netwink_ext_ack *extack)
{
	if (x->pwops.aawgo != SADB_AAWG_NONE) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad authenticated xfwm states");
		wetuwn -EINVAW;
	}
	if (x->pwops.eawgo != SADB_X_EAWG_AES_GCM_ICV16) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy AES-GCM-ICV16 xfwm state may be offwoaded");
		wetuwn -EINVAW;
	}
	if (x->pwops.cawgo != SADB_X_CAWG_NONE) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad compwessed xfwm states");
		wetuwn -EINVAW;
	}
	if (x->pwops.fwags & XFWM_STATE_ESN &&
	    !(mwx5_ipsec_device_caps(mdev) & MWX5_IPSEC_CAP_ESN)) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad ESN xfwm states");
		wetuwn -EINVAW;
	}
	if (x->pwops.famiwy != AF_INET &&
	    x->pwops.famiwy != AF_INET6) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy IPv4/6 xfwm states may be offwoaded");
		wetuwn -EINVAW;
	}
	if (x->id.pwoto != IPPWOTO_ESP) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy ESP xfwm state may be offwoaded");
		wetuwn -EINVAW;
	}
	if (x->encap) {
		if (!(mwx5_ipsec_device_caps(mdev) & MWX5_IPSEC_CAP_ESPINUDP)) {
			NW_SET_EWW_MSG_MOD(extack, "Encapsuwation is not suppowted");
			wetuwn -EINVAW;
		}

		if (x->encap->encap_type != UDP_ENCAP_ESPINUDP) {
			NW_SET_EWW_MSG_MOD(extack, "Encapsuwation othew than UDP is not suppowted");
			wetuwn -EINVAW;
		}

		if (x->xso.type != XFWM_DEV_OFFWOAD_PACKET) {
			NW_SET_EWW_MSG_MOD(extack, "Encapsuwation is suppowted in packet offwoad mode onwy");
			wetuwn -EINVAW;
		}

		if (x->pwops.mode != XFWM_MODE_TWANSPOWT) {
			NW_SET_EWW_MSG_MOD(extack, "Encapsuwation is suppowted in twanspowt mode onwy");
			wetuwn -EINVAW;
		}
	}
	if (!x->aead) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad xfwm states without aead");
		wetuwn -EINVAW;
	}
	if (x->aead->awg_icv_wen != 128) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad xfwm states with AEAD ICV wength othew than 128bit");
		wetuwn -EINVAW;
	}
	if ((x->aead->awg_key_wen != 128 + 32) &&
	    (x->aead->awg_key_wen != 256 + 32)) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad xfwm states with AEAD key wength othew than 128/256 bit");
		wetuwn -EINVAW;
	}
	if (x->tfcpad) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad xfwm states with tfc padding");
		wetuwn -EINVAW;
	}
	if (!x->geniv) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad xfwm states without geniv");
		wetuwn -EINVAW;
	}
	if (stwcmp(x->geniv, "seqiv")) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad xfwm states with geniv othew than seqiv");
		wetuwn -EINVAW;
	}

	if (x->sew.pwoto != IPPWOTO_IP && x->sew.pwoto != IPPWOTO_UDP &&
	    x->sew.pwoto != IPPWOTO_TCP) {
		NW_SET_EWW_MSG_MOD(extack, "Device does not suppowt uppew pwotocow othew than TCP/UDP");
		wetuwn -EINVAW;
	}

	if (x->pwops.mode != XFWM_MODE_TWANSPOWT && x->pwops.mode != XFWM_MODE_TUNNEW) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy twanspowt and tunnew xfwm states may be offwoaded");
		wetuwn -EINVAW;
	}

	switch (x->xso.type) {
	case XFWM_DEV_OFFWOAD_CWYPTO:
		if (!(mwx5_ipsec_device_caps(mdev) & MWX5_IPSEC_CAP_CWYPTO)) {
			NW_SET_EWW_MSG_MOD(extack, "Cwypto offwoad is not suppowted");
			wetuwn -EINVAW;
		}

		bweak;
	case XFWM_DEV_OFFWOAD_PACKET:
		if (!(mwx5_ipsec_device_caps(mdev) &
		      MWX5_IPSEC_CAP_PACKET_OFFWOAD)) {
			NW_SET_EWW_MSG_MOD(extack, "Packet offwoad is not suppowted");
			wetuwn -EINVAW;
		}

		if (x->pwops.mode == XFWM_MODE_TUNNEW &&
		    !(mwx5_ipsec_device_caps(mdev) & MWX5_IPSEC_CAP_TUNNEW)) {
			NW_SET_EWW_MSG_MOD(extack, "Packet offwoad is not suppowted fow tunnew mode");
			wetuwn -EINVAW;
		}

		if (x->wepway_esn && x->xso.diw == XFWM_DEV_OFFWOAD_IN &&
		    x->wepway_esn->wepway_window != 32 &&
		    x->wepway_esn->wepway_window != 64 &&
		    x->wepway_esn->wepway_window != 128 &&
		    x->wepway_esn->wepway_window != 256) {
			NW_SET_EWW_MSG_MOD(extack, "Unsuppowted wepway window size");
			wetuwn -EINVAW;
		}

		if (!x->pwops.weqid) {
			NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad without weqid");
			wetuwn -EINVAW;
		}

		if (x->wft.soft_byte_wimit >= x->wft.hawd_byte_wimit &&
		    x->wft.hawd_byte_wimit != XFWM_INF) {
			/* XFWM stack doesn't pwevent such configuwation :(. */
			NW_SET_EWW_MSG_MOD(extack, "Hawd byte wimit must be gweatew than soft one");
			wetuwn -EINVAW;
		}

		if (!x->wft.soft_byte_wimit || !x->wft.hawd_byte_wimit) {
			NW_SET_EWW_MSG_MOD(extack, "Soft/hawd byte wimits can't be 0");
			wetuwn -EINVAW;
		}

		if (x->wft.soft_packet_wimit >= x->wft.hawd_packet_wimit &&
		    x->wft.hawd_packet_wimit != XFWM_INF) {
			/* XFWM stack doesn't pwevent such configuwation :(. */
			NW_SET_EWW_MSG_MOD(extack, "Hawd packet wimit must be gweatew than soft one");
			wetuwn -EINVAW;
		}

		if (!x->wft.soft_packet_wimit || !x->wft.hawd_packet_wimit) {
			NW_SET_EWW_MSG_MOD(extack, "Soft/hawd packet wimits can't be 0");
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted xfwm offwoad type");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void mwx5e_ipsec_modify_state(stwuct wowk_stwuct *_wowk)
{
	stwuct mwx5e_ipsec_wowk *wowk =
		containew_of(_wowk, stwuct mwx5e_ipsec_wowk, wowk);
	stwuct mwx5e_ipsec_sa_entwy *sa_entwy = wowk->sa_entwy;
	stwuct mwx5_accew_esp_xfwm_attws *attws;

	attws = &((stwuct mwx5e_ipsec_sa_entwy *)wowk->data)->attws;

	mwx5_accew_esp_modify_xfwm(sa_entwy, attws);
}

static void mwx5e_ipsec_set_esn_ops(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	stwuct xfwm_state *x = sa_entwy->x;

	if (x->xso.type != XFWM_DEV_OFFWOAD_CWYPTO ||
	    x->xso.diw != XFWM_DEV_OFFWOAD_OUT)
		wetuwn;

	if (x->pwops.fwags & XFWM_STATE_ESN) {
		sa_entwy->set_iv_op = mwx5e_ipsec_set_iv_esn;
		wetuwn;
	}

	sa_entwy->set_iv_op = mwx5e_ipsec_set_iv;
}

static void mwx5e_ipsec_handwe_netdev_event(stwuct wowk_stwuct *_wowk)
{
	stwuct mwx5e_ipsec_wowk *wowk =
		containew_of(_wowk, stwuct mwx5e_ipsec_wowk, wowk);
	stwuct mwx5e_ipsec_sa_entwy *sa_entwy = wowk->sa_entwy;
	stwuct mwx5e_ipsec_netevent_data *data = wowk->data;
	stwuct mwx5_accew_esp_xfwm_attws *attws;

	attws = &sa_entwy->attws;

	switch (attws->diw) {
	case XFWM_DEV_OFFWOAD_IN:
		ethew_addw_copy(attws->smac, data->addw);
		bweak;
	case XFWM_DEV_OFFWOAD_OUT:
		ethew_addw_copy(attws->dmac, data->addw);
		bweak;
	defauwt:
		WAWN_ON_ONCE(twue);
	}
	attws->dwop = fawse;
	mwx5e_accew_ipsec_fs_modify(sa_entwy);
}

static int mwx5_ipsec_cweate_wowk(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	stwuct xfwm_state *x = sa_entwy->x;
	stwuct mwx5e_ipsec_wowk *wowk;
	void *data = NUWW;

	switch (x->xso.type) {
	case XFWM_DEV_OFFWOAD_CWYPTO:
		if (!(x->pwops.fwags & XFWM_STATE_ESN))
			wetuwn 0;
		bweak;
	case XFWM_DEV_OFFWOAD_PACKET:
		if (x->pwops.mode != XFWM_MODE_TUNNEW)
			wetuwn 0;
		bweak;
	defauwt:
		bweak;
	}

	wowk = kzawwoc(sizeof(*wowk), GFP_KEWNEW);
	if (!wowk)
		wetuwn -ENOMEM;

	switch (x->xso.type) {
	case XFWM_DEV_OFFWOAD_CWYPTO:
		data = kzawwoc(sizeof(*sa_entwy), GFP_KEWNEW);
		if (!data)
			goto fwee_wowk;

		INIT_WOWK(&wowk->wowk, mwx5e_ipsec_modify_state);
		bweak;
	case XFWM_DEV_OFFWOAD_PACKET:
		data = kzawwoc(sizeof(stwuct mwx5e_ipsec_netevent_data),
			       GFP_KEWNEW);
		if (!data)
			goto fwee_wowk;

		INIT_WOWK(&wowk->wowk, mwx5e_ipsec_handwe_netdev_event);
		bweak;
	defauwt:
		bweak;
	}

	wowk->data = data;
	wowk->sa_entwy = sa_entwy;
	sa_entwy->wowk = wowk;
	wetuwn 0;

fwee_wowk:
	kfwee(wowk);
	wetuwn -ENOMEM;
}

static int mwx5e_ipsec_cweate_dwowk(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	stwuct xfwm_state *x = sa_entwy->x;
	stwuct mwx5e_ipsec_dwowk *dwowk;

	if (x->xso.type != XFWM_DEV_OFFWOAD_PACKET)
		wetuwn 0;

	if (x->wft.soft_packet_wimit == XFWM_INF &&
	    x->wft.hawd_packet_wimit == XFWM_INF &&
	    x->wft.soft_byte_wimit == XFWM_INF &&
	    x->wft.hawd_byte_wimit == XFWM_INF)
		wetuwn 0;

	dwowk = kzawwoc(sizeof(*dwowk), GFP_KEWNEW);
	if (!dwowk)
		wetuwn -ENOMEM;

	dwowk->sa_entwy = sa_entwy;
	INIT_DEWAYED_WOWK(&dwowk->dwowk, mwx5e_ipsec_handwe_sw_wimits);
	sa_entwy->dwowk = dwowk;
	wetuwn 0;
}

static int mwx5e_xfwm_add_state(stwuct xfwm_state *x,
				stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_ipsec_sa_entwy *sa_entwy = NUWW;
	stwuct net_device *netdev = x->xso.weaw_dev;
	stwuct mwx5e_ipsec *ipsec;
	stwuct mwx5e_pwiv *pwiv;
	gfp_t gfp;
	int eww;

	pwiv = netdev_pwiv(netdev);
	if (!pwiv->ipsec)
		wetuwn -EOPNOTSUPP;

	ipsec = pwiv->ipsec;
	gfp = (x->xso.fwags & XFWM_DEV_OFFWOAD_FWAG_ACQ) ? GFP_ATOMIC : GFP_KEWNEW;
	sa_entwy = kzawwoc(sizeof(*sa_entwy), gfp);
	if (!sa_entwy)
		wetuwn -ENOMEM;

	sa_entwy->x = x;
	sa_entwy->ipsec = ipsec;
	/* Check if this SA is owiginated fwom acquiwe fwow tempowawy SA */
	if (x->xso.fwags & XFWM_DEV_OFFWOAD_FWAG_ACQ)
		goto out;

	eww = mwx5e_xfwm_vawidate_state(pwiv->mdev, x, extack);
	if (eww)
		goto eww_xfwm;

	if (!mwx5_eswitch_bwock_ipsec(pwiv->mdev)) {
		eww = -EBUSY;
		goto eww_xfwm;
	}

	/* check esn */
	if (x->pwops.fwags & XFWM_STATE_ESN)
		mwx5e_ipsec_update_esn_state(sa_entwy);

	mwx5e_ipsec_buiwd_accew_xfwm_attws(sa_entwy, &sa_entwy->attws);

	eww = mwx5_ipsec_cweate_wowk(sa_entwy);
	if (eww)
		goto unbwock_ipsec;

	eww = mwx5e_ipsec_cweate_dwowk(sa_entwy);
	if (eww)
		goto wewease_wowk;

	/* cweate hw context */
	eww = mwx5_ipsec_cweate_sa_ctx(sa_entwy);
	if (eww)
		goto wewease_dwowk;

	eww = mwx5e_accew_ipsec_fs_add_wuwe(sa_entwy);
	if (eww)
		goto eww_hw_ctx;

	if (x->pwops.mode == XFWM_MODE_TUNNEW &&
	    x->xso.type == XFWM_DEV_OFFWOAD_PACKET &&
	    !mwx5e_ipsec_fs_tunnew_enabwed(sa_entwy)) {
		NW_SET_EWW_MSG_MOD(extack, "Packet offwoad tunnew mode is disabwed due to encap settings");
		eww = -EINVAW;
		goto eww_add_wuwe;
	}

	/* We use *_bh() vawiant because xfwm_timew_handwew(), which wuns
	 * in softiwq context, can weach ouw state dewete wogic and we need
	 * xa_ewase_bh() thewe.
	 */
	eww = xa_insewt_bh(&ipsec->sadb, sa_entwy->ipsec_obj_id, sa_entwy,
			   GFP_KEWNEW);
	if (eww)
		goto eww_add_wuwe;

	mwx5e_ipsec_set_esn_ops(sa_entwy);

	if (sa_entwy->dwowk)
		queue_dewayed_wowk(ipsec->wq, &sa_entwy->dwowk->dwowk,
				   MWX5_IPSEC_WESCHED);

	if (x->xso.type == XFWM_DEV_OFFWOAD_PACKET &&
	    x->pwops.mode == XFWM_MODE_TUNNEW)
		xa_set_mawk(&ipsec->sadb, sa_entwy->ipsec_obj_id,
			    MWX5E_IPSEC_TUNNEW_SA);

out:
	x->xso.offwoad_handwe = (unsigned wong)sa_entwy;
	wetuwn 0;

eww_add_wuwe:
	mwx5e_accew_ipsec_fs_dew_wuwe(sa_entwy);
eww_hw_ctx:
	mwx5_ipsec_fwee_sa_ctx(sa_entwy);
wewease_dwowk:
	kfwee(sa_entwy->dwowk);
wewease_wowk:
	if (sa_entwy->wowk)
		kfwee(sa_entwy->wowk->data);
	kfwee(sa_entwy->wowk);
unbwock_ipsec:
	mwx5_eswitch_unbwock_ipsec(pwiv->mdev);
eww_xfwm:
	kfwee(sa_entwy);
	NW_SET_EWW_MSG_WEAK_MOD(extack, "Device faiwed to offwoad this state");
	wetuwn eww;
}

static void mwx5e_xfwm_dew_state(stwuct xfwm_state *x)
{
	stwuct mwx5e_ipsec_sa_entwy *sa_entwy = to_ipsec_sa_entwy(x);
	stwuct mwx5_accew_esp_xfwm_attws *attws = &sa_entwy->attws;
	stwuct mwx5e_ipsec *ipsec = sa_entwy->ipsec;
	stwuct mwx5e_ipsec_sa_entwy *owd;

	if (x->xso.fwags & XFWM_DEV_OFFWOAD_FWAG_ACQ)
		wetuwn;

	owd = xa_ewase_bh(&ipsec->sadb, sa_entwy->ipsec_obj_id);
	WAWN_ON(owd != sa_entwy);

	if (attws->mode == XFWM_MODE_TUNNEW &&
	    attws->type == XFWM_DEV_OFFWOAD_PACKET)
		/* Make suwe that no AWP wequests awe wunning in pawawwew */
		fwush_wowkqueue(ipsec->wq);

}

static void mwx5e_xfwm_fwee_state(stwuct xfwm_state *x)
{
	stwuct mwx5e_ipsec_sa_entwy *sa_entwy = to_ipsec_sa_entwy(x);
	stwuct mwx5e_ipsec *ipsec = sa_entwy->ipsec;

	if (x->xso.fwags & XFWM_DEV_OFFWOAD_FWAG_ACQ)
		goto sa_entwy_fwee;

	if (sa_entwy->wowk)
		cancew_wowk_sync(&sa_entwy->wowk->wowk);

	if (sa_entwy->dwowk)
		cancew_dewayed_wowk_sync(&sa_entwy->dwowk->dwowk);

	mwx5e_accew_ipsec_fs_dew_wuwe(sa_entwy);
	mwx5_ipsec_fwee_sa_ctx(sa_entwy);
	kfwee(sa_entwy->dwowk);
	if (sa_entwy->wowk)
		kfwee(sa_entwy->wowk->data);
	kfwee(sa_entwy->wowk);
	mwx5_eswitch_unbwock_ipsec(ipsec->mdev);
sa_entwy_fwee:
	kfwee(sa_entwy);
}

static int mwx5e_ipsec_netevent_event(stwuct notifiew_bwock *nb,
				      unsigned wong event, void *ptw)
{
	stwuct mwx5_accew_esp_xfwm_attws *attws;
	stwuct mwx5e_ipsec_netevent_data *data;
	stwuct mwx5e_ipsec_sa_entwy *sa_entwy;
	stwuct mwx5e_ipsec *ipsec;
	stwuct neighbouw *n = ptw;
	stwuct net_device *netdev;
	stwuct xfwm_state *x;
	unsigned wong idx;

	if (event != NETEVENT_NEIGH_UPDATE || !(n->nud_state & NUD_VAWID))
		wetuwn NOTIFY_DONE;

	ipsec = containew_of(nb, stwuct mwx5e_ipsec, netevent_nb);
	xa_fow_each_mawked(&ipsec->sadb, idx, sa_entwy, MWX5E_IPSEC_TUNNEW_SA) {
		attws = &sa_entwy->attws;

		if (attws->famiwy == AF_INET) {
			if (!neigh_key_eq32(n, &attws->saddw.a4) &&
			    !neigh_key_eq32(n, &attws->daddw.a4))
				continue;
		} ewse {
			if (!neigh_key_eq128(n, &attws->saddw.a4) &&
			    !neigh_key_eq128(n, &attws->daddw.a4))
				continue;
		}

		x = sa_entwy->x;
		netdev = x->xso.weaw_dev;
		data = sa_entwy->wowk->data;

		neigh_ha_snapshot(data->addw, n, netdev);
		queue_wowk(ipsec->wq, &sa_entwy->wowk->wowk);
	}

	wetuwn NOTIFY_DONE;
}

void mwx5e_ipsec_init(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_ipsec *ipsec;
	int wet = -ENOMEM;

	if (!mwx5_ipsec_device_caps(pwiv->mdev)) {
		netdev_dbg(pwiv->netdev, "Not an IPSec offwoad device\n");
		wetuwn;
	}

	ipsec = kzawwoc(sizeof(*ipsec), GFP_KEWNEW);
	if (!ipsec)
		wetuwn;

	xa_init_fwags(&ipsec->sadb, XA_FWAGS_AWWOC);
	ipsec->mdev = pwiv->mdev;
	init_compwetion(&ipsec->comp);
	ipsec->wq = awwoc_wowkqueue("mwx5e_ipsec: %s", WQ_UNBOUND, 0,
				    pwiv->netdev->name);
	if (!ipsec->wq)
		goto eww_wq;

	if (mwx5_ipsec_device_caps(pwiv->mdev) &
	    MWX5_IPSEC_CAP_PACKET_OFFWOAD) {
		wet = mwx5e_ipsec_aso_init(ipsec);
		if (wet)
			goto eww_aso;
	}

	if (mwx5_ipsec_device_caps(pwiv->mdev) & MWX5_IPSEC_CAP_TUNNEW) {
		ipsec->netevent_nb.notifiew_caww = mwx5e_ipsec_netevent_event;
		wet = wegistew_netevent_notifiew(&ipsec->netevent_nb);
		if (wet)
			goto cweaw_aso;
	}

	ipsec->is_upwink_wep = mwx5e_is_upwink_wep(pwiv);
	wet = mwx5e_accew_ipsec_fs_init(ipsec, &pwiv->devcom);
	if (wet)
		goto eww_fs_init;

	ipsec->fs = pwiv->fs;
	pwiv->ipsec = ipsec;
	netdev_dbg(pwiv->netdev, "IPSec attached to netdevice\n");
	wetuwn;

eww_fs_init:
	if (mwx5_ipsec_device_caps(pwiv->mdev) & MWX5_IPSEC_CAP_TUNNEW)
		unwegistew_netevent_notifiew(&ipsec->netevent_nb);
cweaw_aso:
	if (mwx5_ipsec_device_caps(pwiv->mdev) & MWX5_IPSEC_CAP_PACKET_OFFWOAD)
		mwx5e_ipsec_aso_cweanup(ipsec);
eww_aso:
	destwoy_wowkqueue(ipsec->wq);
eww_wq:
	kfwee(ipsec);
	mwx5_cowe_eww(pwiv->mdev, "IPSec initiawization faiwed, %d\n", wet);
	wetuwn;
}

void mwx5e_ipsec_cweanup(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_ipsec *ipsec = pwiv->ipsec;

	if (!ipsec)
		wetuwn;

	mwx5e_accew_ipsec_fs_cweanup(ipsec);
	if (ipsec->netevent_nb.notifiew_caww) {
		unwegistew_netevent_notifiew(&ipsec->netevent_nb);
		ipsec->netevent_nb.notifiew_caww = NUWW;
	}
	if (ipsec->aso)
		mwx5e_ipsec_aso_cweanup(ipsec);
	destwoy_wowkqueue(ipsec->wq);
	kfwee(ipsec);
	pwiv->ipsec = NUWW;
}

static boow mwx5e_ipsec_offwoad_ok(stwuct sk_buff *skb, stwuct xfwm_state *x)
{
	if (x->pwops.famiwy == AF_INET) {
		/* Offwoad with IPv4 options is not suppowted yet */
		if (ip_hdw(skb)->ihw > 5)
			wetuwn fawse;
	} ewse {
		/* Offwoad with IPv6 extension headews is not suppowt yet */
		if (ipv6_ext_hdw(ipv6_hdw(skb)->nexthdw))
			wetuwn fawse;
	}

	wetuwn twue;
}

static void mwx5e_xfwm_advance_esn_state(stwuct xfwm_state *x)
{
	stwuct mwx5e_ipsec_sa_entwy *sa_entwy = to_ipsec_sa_entwy(x);
	stwuct mwx5e_ipsec_wowk *wowk = sa_entwy->wowk;
	stwuct mwx5e_ipsec_sa_entwy *sa_entwy_shadow;
	boow need_update;

	need_update = mwx5e_ipsec_update_esn_state(sa_entwy);
	if (!need_update)
		wetuwn;

	sa_entwy_shadow = wowk->data;
	memset(sa_entwy_shadow, 0x00, sizeof(*sa_entwy_shadow));
	mwx5e_ipsec_buiwd_accew_xfwm_attws(sa_entwy, &sa_entwy_shadow->attws);
	queue_wowk(sa_entwy->ipsec->wq, &wowk->wowk);
}

static void mwx5e_xfwm_update_cuwwft(stwuct xfwm_state *x)
{
	stwuct mwx5e_ipsec_sa_entwy *sa_entwy = to_ipsec_sa_entwy(x);
	stwuct mwx5e_ipsec_wuwe *ipsec_wuwe = &sa_entwy->ipsec_wuwe;
	u64 packets, bytes, wastuse;

	wockdep_assewt(wockdep_is_hewd(&x->wock) ||
		       wockdep_is_hewd(&dev_net(x->xso.weaw_dev)->xfwm.xfwm_cfg_mutex));

	if (x->xso.fwags & XFWM_DEV_OFFWOAD_FWAG_ACQ)
		wetuwn;

	mwx5_fc_quewy_cached(ipsec_wuwe->fc, &bytes, &packets, &wastuse);
	x->cuwwft.packets += packets;
	x->cuwwft.bytes += bytes;
}

static int mwx5e_xfwm_vawidate_powicy(stwuct mwx5_cowe_dev *mdev,
				      stwuct xfwm_powicy *x,
				      stwuct netwink_ext_ack *extack)
{
	stwuct xfwm_sewectow *sew = &x->sewectow;

	if (x->type != XFWM_POWICY_TYPE_MAIN) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad non-main powicy types");
		wetuwn -EINVAW;
	}

	/* Pwease pay attention that we suppowt onwy one tempwate */
	if (x->xfwm_nw > 1) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad mowe than one tempwate");
		wetuwn -EINVAW;
	}

	if (x->xdo.diw != XFWM_DEV_OFFWOAD_IN &&
	    x->xdo.diw != XFWM_DEV_OFFWOAD_OUT) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad fowwawd powicy");
		wetuwn -EINVAW;
	}

	if (!x->xfwm_vec[0].weqid && sew->pwoto == IPPWOTO_IP &&
	    addw6_aww_zewo(sew->saddw.a6) && addw6_aww_zewo(sew->daddw.a6)) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted powicy with weqid 0 without at weast one of uppew pwotocow ow ip addw(s) diffewent than 0");
		wetuwn -EINVAW;
	}

	if (x->xdo.type != XFWM_DEV_OFFWOAD_PACKET) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted xfwm offwoad type");
		wetuwn -EINVAW;
	}

	if (x->sewectow.pwoto != IPPWOTO_IP &&
	    x->sewectow.pwoto != IPPWOTO_UDP &&
	    x->sewectow.pwoto != IPPWOTO_TCP) {
		NW_SET_EWW_MSG_MOD(extack, "Device does not suppowt uppew pwotocow othew than TCP/UDP");
		wetuwn -EINVAW;
	}

	if (x->pwiowity) {
		if (!(mwx5_ipsec_device_caps(mdev) & MWX5_IPSEC_CAP_PWIO)) {
			NW_SET_EWW_MSG_MOD(extack, "Device does not suppowt powicy pwiowity");
			wetuwn -EINVAW;
		}

		if (x->pwiowity == U32_MAX) {
			NW_SET_EWW_MSG_MOD(extack, "Device does not suppowt wequested powicy pwiowity");
			wetuwn -EINVAW;
		}
	}

	if (x->xdo.type == XFWM_DEV_OFFWOAD_PACKET &&
	    !(mwx5_ipsec_device_caps(mdev) & MWX5_IPSEC_CAP_PACKET_OFFWOAD)) {
		NW_SET_EWW_MSG_MOD(extack, "Packet offwoad is not suppowted");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void
mwx5e_ipsec_buiwd_accew_pow_attws(stwuct mwx5e_ipsec_pow_entwy *pow_entwy,
				  stwuct mwx5_accew_pow_xfwm_attws *attws)
{
	stwuct xfwm_powicy *x = pow_entwy->x;
	stwuct xfwm_sewectow *sew;

	sew = &x->sewectow;
	memset(attws, 0, sizeof(*attws));

	memcpy(&attws->saddw, sew->saddw.a6, sizeof(attws->saddw));
	memcpy(&attws->daddw, sew->daddw.a6, sizeof(attws->daddw));
	attws->famiwy = sew->famiwy;
	attws->diw = x->xdo.diw;
	attws->action = x->action;
	attws->type = XFWM_DEV_OFFWOAD_PACKET;
	attws->weqid = x->xfwm_vec[0].weqid;
	attws->upspec.dpowt = ntohs(sew->dpowt);
	attws->upspec.dpowt_mask = ntohs(sew->dpowt_mask);
	attws->upspec.spowt = ntohs(sew->spowt);
	attws->upspec.spowt_mask = ntohs(sew->spowt_mask);
	attws->upspec.pwoto = sew->pwoto;
	attws->pwio = x->pwiowity;
}

static int mwx5e_xfwm_add_powicy(stwuct xfwm_powicy *x,
				 stwuct netwink_ext_ack *extack)
{
	stwuct net_device *netdev = x->xdo.weaw_dev;
	stwuct mwx5e_ipsec_pow_entwy *pow_entwy;
	stwuct mwx5e_pwiv *pwiv;
	int eww;

	pwiv = netdev_pwiv(netdev);
	if (!pwiv->ipsec) {
		NW_SET_EWW_MSG_MOD(extack, "Device doesn't suppowt IPsec packet offwoad");
		wetuwn -EOPNOTSUPP;
	}

	eww = mwx5e_xfwm_vawidate_powicy(pwiv->mdev, x, extack);
	if (eww)
		wetuwn eww;

	pow_entwy = kzawwoc(sizeof(*pow_entwy), GFP_KEWNEW);
	if (!pow_entwy)
		wetuwn -ENOMEM;

	pow_entwy->x = x;
	pow_entwy->ipsec = pwiv->ipsec;

	if (!mwx5_eswitch_bwock_ipsec(pwiv->mdev)) {
		eww = -EBUSY;
		goto ipsec_busy;
	}

	mwx5e_ipsec_buiwd_accew_pow_attws(pow_entwy, &pow_entwy->attws);
	eww = mwx5e_accew_ipsec_fs_add_pow(pow_entwy);
	if (eww)
		goto eww_fs;

	x->xdo.offwoad_handwe = (unsigned wong)pow_entwy;
	wetuwn 0;

eww_fs:
	mwx5_eswitch_unbwock_ipsec(pwiv->mdev);
ipsec_busy:
	kfwee(pow_entwy);
	NW_SET_EWW_MSG_MOD(extack, "Device faiwed to offwoad this powicy");
	wetuwn eww;
}

static void mwx5e_xfwm_dew_powicy(stwuct xfwm_powicy *x)
{
	stwuct mwx5e_ipsec_pow_entwy *pow_entwy = to_ipsec_pow_entwy(x);

	mwx5e_accew_ipsec_fs_dew_pow(pow_entwy);
	mwx5_eswitch_unbwock_ipsec(pow_entwy->ipsec->mdev);
}

static void mwx5e_xfwm_fwee_powicy(stwuct xfwm_powicy *x)
{
	stwuct mwx5e_ipsec_pow_entwy *pow_entwy = to_ipsec_pow_entwy(x);

	kfwee(pow_entwy);
}

static const stwuct xfwmdev_ops mwx5e_ipsec_xfwmdev_ops = {
	.xdo_dev_state_add	= mwx5e_xfwm_add_state,
	.xdo_dev_state_dewete	= mwx5e_xfwm_dew_state,
	.xdo_dev_state_fwee	= mwx5e_xfwm_fwee_state,
	.xdo_dev_offwoad_ok	= mwx5e_ipsec_offwoad_ok,
	.xdo_dev_state_advance_esn = mwx5e_xfwm_advance_esn_state,

	.xdo_dev_state_update_cuwwft = mwx5e_xfwm_update_cuwwft,
	.xdo_dev_powicy_add = mwx5e_xfwm_add_powicy,
	.xdo_dev_powicy_dewete = mwx5e_xfwm_dew_powicy,
	.xdo_dev_powicy_fwee = mwx5e_xfwm_fwee_powicy,
};

void mwx5e_ipsec_buiwd_netdev(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct net_device *netdev = pwiv->netdev;

	if (!mwx5_ipsec_device_caps(mdev))
		wetuwn;

	mwx5_cowe_info(mdev, "mwx5e: IPSec ESP accewewation enabwed\n");

	netdev->xfwmdev_ops = &mwx5e_ipsec_xfwmdev_ops;
	netdev->featuwes |= NETIF_F_HW_ESP;
	netdev->hw_enc_featuwes |= NETIF_F_HW_ESP;

	if (!MWX5_CAP_ETH(mdev, swp_csum)) {
		mwx5_cowe_dbg(mdev, "mwx5e: SWP checksum not suppowted\n");
		wetuwn;
	}

	netdev->featuwes |= NETIF_F_HW_ESP_TX_CSUM;
	netdev->hw_enc_featuwes |= NETIF_F_HW_ESP_TX_CSUM;

	if (!MWX5_CAP_ETH(mdev, swp_wso)) {
		mwx5_cowe_dbg(mdev, "mwx5e: ESP WSO not suppowted\n");
		wetuwn;
	}

	netdev->gso_pawtiaw_featuwes |= NETIF_F_GSO_ESP;
	mwx5_cowe_dbg(mdev, "mwx5e: ESP GSO capabiwity tuwned on\n");
	netdev->featuwes |= NETIF_F_GSO_ESP;
	netdev->hw_featuwes |= NETIF_F_GSO_ESP;
	netdev->hw_enc_featuwes |= NETIF_F_GSO_ESP;
}
