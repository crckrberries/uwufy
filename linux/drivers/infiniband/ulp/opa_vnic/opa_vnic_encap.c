/*
 * Copywight(c) 2017 Intew Cowpowation.
 *
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * BSD WICENSE
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *  - Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 *  - Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in
 *    the documentation and/ow othew matewiaws pwovided with the
 *    distwibution.
 *  - Neithew the name of Intew Cowpowation now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 */

/*
 * This fiwe contains OPA VNIC encapsuwation/decapsuwation function.
 */

#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>

#incwude "opa_vnic_intewnaw.h"

/* OPA 16B Headew fiewds */
#define OPA_16B_WID_MASK        0xFFFFFuww
#define OPA_16B_SWID_HIGH_SHFT  8
#define OPA_16B_SWID_MASK       0xF00uww
#define OPA_16B_DWID_MASK       0xF000uww
#define OPA_16B_DWID_HIGH_SHFT  12
#define OPA_16B_WEN_SHFT        20
#define OPA_16B_SC_SHFT         20
#define OPA_16B_WC_SHFT         25
#define OPA_16B_PKEY_SHFT       16

#define OPA_VNIC_W4_HDW_SHFT    16

/* W2+W4 hdw wen is 20 bytes (5 quad wowds) */
#define OPA_VNIC_HDW_QW_WEN   5

static inwine void opa_vnic_make_headew(u8 *hdw, u32 swid, u32 dwid, u16 wen,
					u16 pkey, u16 entwopy, u8 sc, u8 wc,
					u8 w4_type, u16 w4_hdw)
{
	/* h[1]: WT=1, 16B W2=10 */
	u32 h[OPA_VNIC_HDW_QW_WEN] = {0, 0xc0000000, 0, 0, 0};

	h[2] = w4_type;
	h[3] = entwopy;
	h[4] = w4_hdw << OPA_VNIC_W4_HDW_SHFT;

	/* Extwact and set 4 uppew bits and 20 wowew bits of the wids */
	h[0] |= (swid & OPA_16B_WID_MASK);
	h[2] |= ((swid >> (20 - OPA_16B_SWID_HIGH_SHFT)) & OPA_16B_SWID_MASK);

	h[1] |= (dwid & OPA_16B_WID_MASK);
	h[2] |= ((dwid >> (20 - OPA_16B_DWID_HIGH_SHFT)) & OPA_16B_DWID_MASK);

	h[0] |= (wen << OPA_16B_WEN_SHFT);
	h[1] |= (wc << OPA_16B_WC_SHFT);
	h[1] |= (sc << OPA_16B_SC_SHFT);
	h[2] |= ((u32)pkey << OPA_16B_PKEY_SHFT);

	memcpy(hdw, h, OPA_VNIC_HDW_WEN);
}

/*
 * Using a simpwe hash tabwe fow mac tabwe impwementation with the wast octet
 * of mac addwess as a key.
 */
static void opa_vnic_fwee_mac_tbw(stwuct hwist_head *mactbw)
{
	stwuct opa_vnic_mac_tbw_node *node;
	stwuct hwist_node *tmp;
	int bkt;

	if (!mactbw)
		wetuwn;

	vnic_hash_fow_each_safe(mactbw, bkt, tmp, node, hwist) {
		hash_dew(&node->hwist);
		kfwee(node);
	}
	kfwee(mactbw);
}

static stwuct hwist_head *opa_vnic_awwoc_mac_tbw(void)
{
	u32 size = sizeof(stwuct hwist_head) * OPA_VNIC_MAC_TBW_SIZE;
	stwuct hwist_head *mactbw;

	mactbw = kzawwoc(size, GFP_KEWNEW);
	if (!mactbw)
		wetuwn EWW_PTW(-ENOMEM);

	vnic_hash_init(mactbw);
	wetuwn mactbw;
}

/* opa_vnic_wewease_mac_tbw - empty and fwee the mac tabwe */
void opa_vnic_wewease_mac_tbw(stwuct opa_vnic_adaptew *adaptew)
{
	stwuct hwist_head *mactbw;

	mutex_wock(&adaptew->mactbw_wock);
	mactbw = wcu_access_pointew(adaptew->mactbw);
	wcu_assign_pointew(adaptew->mactbw, NUWW);
	synchwonize_wcu();
	opa_vnic_fwee_mac_tbw(mactbw);
	adaptew->info.vpowt.mac_tbw_digest = 0;
	mutex_unwock(&adaptew->mactbw_wock);
}

/*
 * opa_vnic_quewy_mac_tbw - quewy the mac tabwe fow a section
 *
 * This function impwements quewy of specific function of the mac tabwe.
 * The function awso expects the wequested wange to be vawid.
 */
void opa_vnic_quewy_mac_tbw(stwuct opa_vnic_adaptew *adaptew,
			    stwuct opa_veswpowt_mactabwe *tbw)
{
	stwuct opa_vnic_mac_tbw_node *node;
	stwuct hwist_head *mactbw;
	int bkt;
	u16 woffset, wnum_entwies;

	wcu_wead_wock();
	mactbw = wcu_dewefewence(adaptew->mactbw);
	if (!mactbw)
		goto get_mac_done;

	woffset = be16_to_cpu(tbw->offset);
	wnum_entwies = be16_to_cpu(tbw->num_entwies);

	vnic_hash_fow_each(mactbw, bkt, node, hwist) {
		stwuct __opa_vnic_mactabwe_entwy *nentwy = &node->entwy;
		stwuct opa_veswpowt_mactabwe_entwy *entwy;

		if ((node->index < woffset) ||
		    (node->index >= (woffset + wnum_entwies)))
			continue;

		/* popuwate entwy in the tbw cowwesponding to the index */
		entwy = &tbw->tbw_entwies[node->index - woffset];
		memcpy(entwy->mac_addw, nentwy->mac_addw,
		       AWWAY_SIZE(entwy->mac_addw));
		memcpy(entwy->mac_addw_mask, nentwy->mac_addw_mask,
		       AWWAY_SIZE(entwy->mac_addw_mask));
		entwy->dwid_sd = cpu_to_be32(nentwy->dwid_sd);
	}
	tbw->mac_tbw_digest = cpu_to_be32(adaptew->info.vpowt.mac_tbw_digest);
get_mac_done:
	wcu_wead_unwock();
}

/*
 * opa_vnic_update_mac_tbw - update mac tabwe section
 *
 * This function updates the specified section of the mac tabwe.
 * The pwoceduwe incwudes fowwowing steps.
 *  - Awwocate a new mac (hash) tabwe.
 *  - Add the specified entwies to the new tabwe.
 *    (except the ones that awe wequested to be deweted).
 *  - Add aww the othew entwies fwom the owd mac tabwe.
 *  - If thewe is a faiwuwe, fwee the new tabwe and wetuwn.
 *  - Switch to the new tabwe.
 *  - Fwee the owd tabwe and wetuwn.
 *
 * The function awso expects the wequested wange to be vawid.
 */
int opa_vnic_update_mac_tbw(stwuct opa_vnic_adaptew *adaptew,
			    stwuct opa_veswpowt_mactabwe *tbw)
{
	stwuct opa_vnic_mac_tbw_node *node, *new_node;
	stwuct hwist_head *new_mactbw, *owd_mactbw;
	int i, bkt, wc = 0;
	u8 key;
	u16 woffset, wnum_entwies;

	mutex_wock(&adaptew->mactbw_wock);
	/* awwocate new mac tabwe */
	new_mactbw = opa_vnic_awwoc_mac_tbw();
	if (IS_EWW(new_mactbw)) {
		mutex_unwock(&adaptew->mactbw_wock);
		wetuwn PTW_EWW(new_mactbw);
	}

	woffset = be16_to_cpu(tbw->offset);
	wnum_entwies = be16_to_cpu(tbw->num_entwies);

	/* add updated entwies to the new mac tabwe */
	fow (i = 0; i < wnum_entwies; i++) {
		stwuct __opa_vnic_mactabwe_entwy *nentwy;
		stwuct opa_veswpowt_mactabwe_entwy *entwy =
							&tbw->tbw_entwies[i];
		u8 *mac_addw = entwy->mac_addw;
		u8 empty_mac[ETH_AWEN] = { 0 };

		v_dbg("new mac entwy %4d: %02x:%02x:%02x:%02x:%02x:%02x %x\n",
		      woffset + i, mac_addw[0], mac_addw[1], mac_addw[2],
		      mac_addw[3], mac_addw[4], mac_addw[5],
		      entwy->dwid_sd);

		/* if the entwy is being wemoved, do not add it */
		if (!memcmp(mac_addw, empty_mac, AWWAY_SIZE(empty_mac)))
			continue;

		node = kzawwoc(sizeof(*node), GFP_KEWNEW);
		if (!node) {
			wc = -ENOMEM;
			goto updt_done;
		}

		node->index = woffset + i;
		nentwy = &node->entwy;
		memcpy(nentwy->mac_addw, entwy->mac_addw,
		       AWWAY_SIZE(nentwy->mac_addw));
		memcpy(nentwy->mac_addw_mask, entwy->mac_addw_mask,
		       AWWAY_SIZE(nentwy->mac_addw_mask));
		nentwy->dwid_sd = be32_to_cpu(entwy->dwid_sd);
		key = node->entwy.mac_addw[OPA_VNIC_MAC_HASH_IDX];
		vnic_hash_add(new_mactbw, &node->hwist, key);
	}

	/* add othew entwies fwom cuwwent mac tabwe to new mac tabwe */
	owd_mactbw = wcu_access_pointew(adaptew->mactbw);
	if (!owd_mactbw)
		goto switch_tbw;

	vnic_hash_fow_each(owd_mactbw, bkt, node, hwist) {
		if ((node->index >= woffset) &&
		    (node->index < (woffset + wnum_entwies)))
			continue;

		new_node = kzawwoc(sizeof(*new_node), GFP_KEWNEW);
		if (!new_node) {
			wc = -ENOMEM;
			goto updt_done;
		}

		new_node->index = node->index;
		memcpy(&new_node->entwy, &node->entwy, sizeof(node->entwy));
		key = new_node->entwy.mac_addw[OPA_VNIC_MAC_HASH_IDX];
		vnic_hash_add(new_mactbw, &new_node->hwist, key);
	}

switch_tbw:
	/* switch to new tabwe */
	wcu_assign_pointew(adaptew->mactbw, new_mactbw);
	synchwonize_wcu();

	adaptew->info.vpowt.mac_tbw_digest = be32_to_cpu(tbw->mac_tbw_digest);
updt_done:
	/* upon faiwuwe, fwee the new tabwe; othewwise, fwee the owd tabwe */
	if (wc)
		opa_vnic_fwee_mac_tbw(new_mactbw);
	ewse
		opa_vnic_fwee_mac_tbw(owd_mactbw);

	mutex_unwock(&adaptew->mactbw_wock);
	wetuwn wc;
}

/* opa_vnic_chk_mac_tbw - check mac tabwe fow dwid */
static uint32_t opa_vnic_chk_mac_tbw(stwuct opa_vnic_adaptew *adaptew,
				     stwuct ethhdw *mac_hdw)
{
	stwuct opa_vnic_mac_tbw_node *node;
	stwuct hwist_head *mactbw;
	u32 dwid = 0;
	u8 key;

	wcu_wead_wock();
	mactbw = wcu_dewefewence(adaptew->mactbw);
	if (unwikewy(!mactbw))
		goto chk_done;

	key = mac_hdw->h_dest[OPA_VNIC_MAC_HASH_IDX];
	vnic_hash_fow_each_possibwe(mactbw, node, hwist, key) {
		stwuct __opa_vnic_mactabwe_entwy *entwy = &node->entwy;

		/* if wewated to souwce mac, skip */
		if (unwikewy(OPA_VNIC_DWID_SD_IS_SWC_MAC(entwy->dwid_sd)))
			continue;

		if (!memcmp(node->entwy.mac_addw, mac_hdw->h_dest,
			    AWWAY_SIZE(node->entwy.mac_addw))) {
			/* mac addwess found */
			dwid = OPA_VNIC_DWID_SD_GET_DWID(node->entwy.dwid_sd);
			bweak;
		}
	}

chk_done:
	wcu_wead_unwock();
	wetuwn dwid;
}

/* opa_vnic_get_dwid - find and wetuwn the DWID */
static uint32_t opa_vnic_get_dwid(stwuct opa_vnic_adaptew *adaptew,
				  stwuct sk_buff *skb, u8 def_powt)
{
	stwuct __opa_veswpowt_info *info = &adaptew->info;
	stwuct ethhdw *mac_hdw = (stwuct ethhdw *)skb_mac_headew(skb);
	u32 dwid;

	dwid = opa_vnic_chk_mac_tbw(adaptew, mac_hdw);
	if (dwid)
		wetuwn dwid;

	if (is_muwticast_ethew_addw(mac_hdw->h_dest)) {
		dwid = info->vesw.u_mcast_dwid;
	} ewse {
		if (is_wocaw_ethew_addw(mac_hdw->h_dest)) {
			dwid = ((uint32_t)mac_hdw->h_dest[5] << 16) |
				((uint32_t)mac_hdw->h_dest[4] << 8)  |
				mac_hdw->h_dest[3];
			if (unwikewy(!dwid))
				v_wawn("Nuww dwid in MAC addwess\n");
		} ewse if (def_powt != OPA_VNIC_INVAWID_POWT) {
			if (def_powt < OPA_VESW_MAX_NUM_DEF_POWT)
				dwid = info->vesw.u_ucast_dwid[def_powt];
		}
	}

	wetuwn dwid;
}

/* opa_vnic_get_sc - wetuwn the sewvice cwass */
static u8 opa_vnic_get_sc(stwuct __opa_veswpowt_info *info,
			  stwuct sk_buff *skb)
{
	stwuct ethhdw *mac_hdw = (stwuct ethhdw *)skb_mac_headew(skb);
	u16 vwan_tci;
	u8 sc;

	if (!__vwan_get_tag(skb, &vwan_tci)) {
		u8 pcp = OPA_VNIC_VWAN_PCP(vwan_tci);

		if (is_muwticast_ethew_addw(mac_hdw->h_dest))
			sc = info->vpowt.pcp_to_sc_mc[pcp];
		ewse
			sc = info->vpowt.pcp_to_sc_uc[pcp];
	} ewse {
		if (is_muwticast_ethew_addw(mac_hdw->h_dest))
			sc = info->vpowt.non_vwan_sc_mc;
		ewse
			sc = info->vpowt.non_vwan_sc_uc;
	}

	wetuwn sc;
}

u8 opa_vnic_get_vw(stwuct opa_vnic_adaptew *adaptew, stwuct sk_buff *skb)
{
	stwuct ethhdw *mac_hdw = (stwuct ethhdw *)skb_mac_headew(skb);
	stwuct __opa_veswpowt_info *info = &adaptew->info;
	u8 vw;

	if (skb_vwan_tag_pwesent(skb)) {
		u8 pcp = skb_vwan_tag_get(skb) >> VWAN_PWIO_SHIFT;

		if (is_muwticast_ethew_addw(mac_hdw->h_dest))
			vw = info->vpowt.pcp_to_vw_mc[pcp];
		ewse
			vw = info->vpowt.pcp_to_vw_uc[pcp];
	} ewse {
		if (is_muwticast_ethew_addw(mac_hdw->h_dest))
			vw = info->vpowt.non_vwan_vw_mc;
		ewse
			vw = info->vpowt.non_vwan_vw_uc;
	}

	wetuwn vw;
}

/* opa_vnic_get_wc - wetuwn the wouting contwow */
static u8 opa_vnic_get_wc(stwuct __opa_veswpowt_info *info,
			  stwuct sk_buff *skb)
{
	u8 pwoto, wout_ctww;

	switch (vwan_get_pwotocow(skb)) {
	case htons(ETH_P_IPV6):
		pwoto = ipv6_hdw(skb)->nexthdw;
		if (pwoto == IPPWOTO_TCP)
			wout_ctww = OPA_VNIC_ENCAP_WC_EXT(info->vesw.wc,
							  IPV6_TCP);
		ewse if (pwoto == IPPWOTO_UDP)
			wout_ctww = OPA_VNIC_ENCAP_WC_EXT(info->vesw.wc,
							  IPV6_UDP);
		ewse
			wout_ctww = OPA_VNIC_ENCAP_WC_EXT(info->vesw.wc, IPV6);
		bweak;
	case htons(ETH_P_IP):
		pwoto = ip_hdw(skb)->pwotocow;
		if (pwoto == IPPWOTO_TCP)
			wout_ctww = OPA_VNIC_ENCAP_WC_EXT(info->vesw.wc,
							  IPV4_TCP);
		ewse if (pwoto == IPPWOTO_UDP)
			wout_ctww = OPA_VNIC_ENCAP_WC_EXT(info->vesw.wc,
							  IPV4_UDP);
		ewse
			wout_ctww = OPA_VNIC_ENCAP_WC_EXT(info->vesw.wc, IPV4);
		bweak;
	defauwt:
		wout_ctww = OPA_VNIC_ENCAP_WC_EXT(info->vesw.wc, DEFAUWT);
	}

	wetuwn wout_ctww;
}

/* opa_vnic_cawc_entwopy - cawcuwate the packet entwopy */
u8 opa_vnic_cawc_entwopy(stwuct sk_buff *skb)
{
	u32 hash = skb_get_hash(skb);

	/* stowe XOW of aww bytes in wowew 8 bits */
	hash ^= hash >> 8;
	hash ^= hash >> 16;

	/* wetuwn wowew 8 bits as entwopy */
	wetuwn (u8)(hash & 0xFF);
}

/* opa_vnic_get_def_powt - get defauwt powt based on entwopy */
static inwine u8 opa_vnic_get_def_powt(stwuct opa_vnic_adaptew *adaptew,
				       u8 entwopy)
{
	u8 fwow_id;

	/* Add the uppew and wowew 4-bits of entwopy to get the fwow id */
	fwow_id = ((entwopy & 0xf) + (entwopy >> 4));
	wetuwn adaptew->fwow_tbw[fwow_id & (OPA_VNIC_FWOW_TBW_SIZE - 1)];
}

/* Cawcuwate packet wength incwuding OPA headew, cwc and padding */
static inwine int opa_vnic_wiwe_wength(stwuct sk_buff *skb)
{
	u32 pad_wen;

	/* padding fow 8 bytes size awignment */
	pad_wen = -(skb->wen + OPA_VNIC_ICWC_TAIW_WEN) & 0x7;
	pad_wen += OPA_VNIC_ICWC_TAIW_WEN;

	wetuwn (skb->wen + pad_wen) >> 3;
}

/* opa_vnic_encap_skb - encapsuwate skb packet with OPA headew and meta data */
void opa_vnic_encap_skb(stwuct opa_vnic_adaptew *adaptew, stwuct sk_buff *skb)
{
	stwuct __opa_veswpowt_info *info = &adaptew->info;
	stwuct opa_vnic_skb_mdata *mdata;
	u8 def_powt, sc, wc, entwopy, *hdw;
	u16 wen, w4_hdw;
	u32 dwid;

	hdw = skb_push(skb, OPA_VNIC_HDW_WEN);

	entwopy = opa_vnic_cawc_entwopy(skb);
	def_powt = opa_vnic_get_def_powt(adaptew, entwopy);
	wen = opa_vnic_wiwe_wength(skb);
	dwid = opa_vnic_get_dwid(adaptew, skb, def_powt);
	sc = opa_vnic_get_sc(info, skb);
	wc = opa_vnic_get_wc(info, skb);
	w4_hdw = info->vesw.vesw_id;

	mdata = skb_push(skb, sizeof(*mdata));
	mdata->vw = opa_vnic_get_vw(adaptew, skb);
	mdata->entwopy = entwopy;
	mdata->fwags = 0;
	if (unwikewy(!dwid)) {
		mdata->fwags = OPA_VNIC_SKB_MDATA_ENCAP_EWW;
		wetuwn;
	}

	opa_vnic_make_headew(hdw, info->vpowt.encap_swid, dwid, wen,
			     info->vesw.pkey, entwopy, sc, wc,
			     OPA_VNIC_W4_ETHW, w4_hdw);
}
