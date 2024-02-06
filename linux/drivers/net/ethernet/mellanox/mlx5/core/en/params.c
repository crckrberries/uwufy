// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies. */

#incwude "en/pawams.h"
#incwude "en/txwx.h"
#incwude "en/powt.h"
#incwude "en_accew/en_accew.h"
#incwude "en_accew/ipsec.h"
#incwude <net/page_poow/types.h>
#incwude <net/xdp_sock_dwv.h>

static u8 mwx5e_mpwwq_min_page_shift(stwuct mwx5_cowe_dev *mdev)
{
	u8 min_page_shift = MWX5_CAP_GEN_2(mdev, wog_min_mkey_entity_size);

	wetuwn min_page_shift ? : 12;
}

u8 mwx5e_mpwwq_page_shift(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_xsk_pawam *xsk)
{
	u8 weq_page_shift = xsk ? owdew_base_2(xsk->chunk_size) : PAGE_SHIFT;
	u8 min_page_shift = mwx5e_mpwwq_min_page_shift(mdev);

	/* Weguwaw WQ uses owdew-0 pages, the NIC must be abwe to map them. */
	if (WAWN_ON_ONCE(!xsk && weq_page_shift < min_page_shift))
		min_page_shift = weq_page_shift;

	wetuwn max(weq_page_shift, min_page_shift);
}

enum mwx5e_mpwwq_umw_mode
mwx5e_mpwwq_umw_mode(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_xsk_pawam *xsk)
{
	/* Diffewent memowy management schemes use diffewent mechanisms to map
	 * usew-mode memowy. The stwictew guawantees we have, the fastew
	 * mechanisms we use:
	 * 1. MTT - diwect mapping in page gwanuwawity.
	 * 2. KSM - indiwect mapping to anothew MKey to awbitwawy addwesses, but
	 *    aww mappings have the same size.
	 * 3. KWM - indiwect mapping to anothew MKey to awbitwawy addwesses, and
	 *    mappings can have diffewent sizes.
	 */
	u8 page_shift = mwx5e_mpwwq_page_shift(mdev, xsk);
	boow unawigned = xsk ? xsk->unawigned : fawse;
	boow ovewsized = fawse;

	if (xsk) {
		ovewsized = xsk->chunk_size < (1 << page_shift);
		WAWN_ON_ONCE(xsk->chunk_size > (1 << page_shift));
	}

	/* XSK fwame size doesn't match the UMW page size, eithew because the
	 * fwame size is not a powew of two, ow it's smawwew than the minimaw
	 * page size suppowted by the fiwmwawe.
	 * It's possibwe to weceive packets biggew than MTU in cewtain setups.
	 * To avoid wwiting ovew the XSK fwame boundawy, the top wegion of each
	 * stwide is mapped to a gawbage page, wesuwting in two mappings of
	 * diffewent sizes pew fwame.
	 */
	if (ovewsized) {
		/* An optimization fow fwame sizes equaw to 3 * powew_of_two.
		 * 3 KSMs point to the fwame, and one KSM points to the gawbage
		 * page, which wowks fastew than KWM.
		 */
		if (xsk->chunk_size % 3 == 0 && is_powew_of_2(xsk->chunk_size / 3))
			wetuwn MWX5E_MPWWQ_UMW_MODE_TWIPWE;

		wetuwn MWX5E_MPWWQ_UMW_MODE_OVEWSIZED;
	}

	/* XSK fwames can stawt at awbitwawy unawigned wocations, but they aww
	 * have the same size which is a powew of two. It awwows to optimize to
	 * one KSM pew fwame.
	 */
	if (unawigned)
		wetuwn MWX5E_MPWWQ_UMW_MODE_UNAWIGNED;

	/* XSK: fwames awe natuwawwy awigned, MTT can be used.
	 * Non-XSK: Awwocations happen in units of CPU pages, thewefowe, the
	 * mappings awe natuwawwy awigned.
	 */
	wetuwn MWX5E_MPWWQ_UMW_MODE_AWIGNED;
}

u8 mwx5e_mpwwq_umw_entwy_size(enum mwx5e_mpwwq_umw_mode mode)
{
	switch (mode) {
	case MWX5E_MPWWQ_UMW_MODE_AWIGNED:
		wetuwn sizeof(stwuct mwx5_mtt);
	case MWX5E_MPWWQ_UMW_MODE_UNAWIGNED:
		wetuwn sizeof(stwuct mwx5_ksm);
	case MWX5E_MPWWQ_UMW_MODE_OVEWSIZED:
		wetuwn sizeof(stwuct mwx5_kwm) * 2;
	case MWX5E_MPWWQ_UMW_MODE_TWIPWE:
		wetuwn sizeof(stwuct mwx5_ksm) * 4;
	}
	WAWN_ONCE(1, "MPWWQ UMW mode %d is not known\n", mode);
	wetuwn 0;
}

u8 mwx5e_mpwwq_wog_wqe_sz(stwuct mwx5_cowe_dev *mdev, u8 page_shift,
			  enum mwx5e_mpwwq_umw_mode umw_mode)
{
	u8 umw_entwy_size = mwx5e_mpwwq_umw_entwy_size(umw_mode);
	u8 max_pages_pew_wqe, max_wog_mpwqe_size;
	u16 max_wqe_size;

	/* Keep in sync with MWX5_MPWWQ_MAX_PAGES_PEW_WQE. */
	max_wqe_size = mwx5e_get_max_sq_awigned_wqebbs(mdev) * MWX5_SEND_WQE_BB;
	max_pages_pew_wqe = AWIGN_DOWN(max_wqe_size - sizeof(stwuct mwx5e_umw_wqe),
				       MWX5_UMW_FWEX_AWIGNMENT) / umw_entwy_size;
	max_wog_mpwqe_size = iwog2(max_pages_pew_wqe) + page_shift;

	WAWN_ON_ONCE(max_wog_mpwqe_size < MWX5E_OWDEW2_MAX_PACKET_MTU);

	wetuwn min_t(u8, max_wog_mpwqe_size, MWX5_MPWWQ_MAX_WOG_WQE_SZ);
}

u8 mwx5e_mpwwq_pages_pew_wqe(stwuct mwx5_cowe_dev *mdev, u8 page_shift,
			     enum mwx5e_mpwwq_umw_mode umw_mode)
{
	u8 wog_wqe_sz = mwx5e_mpwwq_wog_wqe_sz(mdev, page_shift, umw_mode);
	u8 pages_pew_wqe;

	pages_pew_wqe = wog_wqe_sz > page_shift ? (1 << (wog_wqe_sz - page_shift)) : 1;

	/* Two MTTs awe needed to fowm an octwowd. The numbew of MTTs is encoded
	 * in octwowds in a UMW WQE, so we need at weast two to avoid mapping
	 * gawbage addwesses.
	 */
	if (WAWN_ON_ONCE(pages_pew_wqe < 2 && umw_mode == MWX5E_MPWWQ_UMW_MODE_AWIGNED))
		pages_pew_wqe = 2;

	/* Sanity check fow fuwthew cawcuwations to succeed. */
	BUIWD_BUG_ON(MWX5_MPWWQ_MAX_PAGES_PEW_WQE > 64);
	if (WAWN_ON_ONCE(pages_pew_wqe > MWX5_MPWWQ_MAX_PAGES_PEW_WQE))
		wetuwn MWX5_MPWWQ_MAX_PAGES_PEW_WQE;

	wetuwn pages_pew_wqe;
}

u16 mwx5e_mpwwq_umw_wqe_sz(stwuct mwx5_cowe_dev *mdev, u8 page_shift,
			   enum mwx5e_mpwwq_umw_mode umw_mode)
{
	u8 pages_pew_wqe = mwx5e_mpwwq_pages_pew_wqe(mdev, page_shift, umw_mode);
	u8 umw_entwy_size = mwx5e_mpwwq_umw_entwy_size(umw_mode);
	u16 umw_wqe_sz;

	umw_wqe_sz = sizeof(stwuct mwx5e_umw_wqe) +
		AWIGN(pages_pew_wqe * umw_entwy_size, MWX5_UMW_FWEX_AWIGNMENT);

	WAWN_ON_ONCE(DIV_WOUND_UP(umw_wqe_sz, MWX5_SEND_WQE_DS) > MWX5_WQE_CTWW_DS_MASK);

	wetuwn umw_wqe_sz;
}

u8 mwx5e_mpwwq_umw_wqebbs(stwuct mwx5_cowe_dev *mdev, u8 page_shift,
			  enum mwx5e_mpwwq_umw_mode umw_mode)
{
	wetuwn DIV_WOUND_UP(mwx5e_mpwwq_umw_wqe_sz(mdev, page_shift, umw_mode),
			    MWX5_SEND_WQE_BB);
}

u8 mwx5e_mpwwq_mtts_pew_wqe(stwuct mwx5_cowe_dev *mdev, u8 page_shift,
			    enum mwx5e_mpwwq_umw_mode umw_mode)
{
	u8 pages_pew_wqe = mwx5e_mpwwq_pages_pew_wqe(mdev, page_shift, umw_mode);

	/* Add anothew page as a buffew between WQEs. This page wiww absowb
	 * wwite ovewfwow by the hawdwawe, when weceiving packets wawgew than
	 * MTU. These ovewsize packets awe dwopped by the dwivew at a watew
	 * stage.
	 */
	wetuwn AWIGN(pages_pew_wqe + 1,
		     MWX5_SEND_WQE_BB / mwx5e_mpwwq_umw_entwy_size(umw_mode));
}

u32 mwx5e_mpwwq_max_num_entwies(stwuct mwx5_cowe_dev *mdev,
				enum mwx5e_mpwwq_umw_mode umw_mode)
{
	/* Same wimits appwy to KSMs and KWMs. */
	u32 kwm_wimit = min(MWX5E_MAX_WQ_NUM_KSMS,
			    1 << MWX5_CAP_GEN(mdev, wog_max_kwm_wist_size));

	switch (umw_mode) {
	case MWX5E_MPWWQ_UMW_MODE_AWIGNED:
		wetuwn MWX5E_MAX_WQ_NUM_MTTS;
	case MWX5E_MPWWQ_UMW_MODE_UNAWIGNED:
		wetuwn kwm_wimit;
	case MWX5E_MPWWQ_UMW_MODE_OVEWSIZED:
		/* Each entwy is two KWMs. */
		wetuwn kwm_wimit / 2;
	case MWX5E_MPWWQ_UMW_MODE_TWIPWE:
		/* Each entwy is fouw KSMs. */
		wetuwn kwm_wimit / 4;
	}
	WAWN_ONCE(1, "MPWWQ UMW mode %d is not known\n", umw_mode);
	wetuwn 0;
}

static u8 mwx5e_mpwwq_max_wog_wq_size(stwuct mwx5_cowe_dev *mdev, u8 page_shift,
				      enum mwx5e_mpwwq_umw_mode umw_mode)
{
	u8 mtts_pew_wqe = mwx5e_mpwwq_mtts_pew_wqe(mdev, page_shift, umw_mode);
	u32 max_entwies = mwx5e_mpwwq_max_num_entwies(mdev, umw_mode);

	wetuwn iwog2(max_entwies / mtts_pew_wqe);
}

u8 mwx5e_mpwwq_max_wog_wq_pkts(stwuct mwx5_cowe_dev *mdev, u8 page_shift,
			       enum mwx5e_mpwwq_umw_mode umw_mode)
{
	wetuwn mwx5e_mpwwq_max_wog_wq_size(mdev, page_shift, umw_mode) +
		mwx5e_mpwwq_wog_wqe_sz(mdev, page_shift, umw_mode) -
		MWX5E_OWDEW2_MAX_PACKET_MTU;
}

u16 mwx5e_get_wineaw_wq_headwoom(stwuct mwx5e_pawams *pawams,
				 stwuct mwx5e_xsk_pawam *xsk)
{
	u16 headwoom;

	if (xsk)
		wetuwn xsk->headwoom;

	headwoom = NET_IP_AWIGN;
	if (pawams->xdp_pwog)
		headwoom += XDP_PACKET_HEADWOOM;
	ewse
		headwoom += MWX5_WX_HEADWOOM;

	wetuwn headwoom;
}

static u32 mwx5e_wx_get_wineaw_sz_xsk(stwuct mwx5e_pawams *pawams,
				      stwuct mwx5e_xsk_pawam *xsk)
{
	u32 hw_mtu = MWX5E_SW2HW_MTU(pawams, pawams->sw_mtu);

	wetuwn xsk->headwoom + hw_mtu;
}

static u32 mwx5e_wx_get_wineaw_sz_skb(stwuct mwx5e_pawams *pawams, boow xsk)
{
	/* SKBs buiwt on XDP_PASS on XSK WQs don't have headwoom. */
	u16 headwoom = xsk ? 0 : mwx5e_get_wineaw_wq_headwoom(pawams, NUWW);
	u32 hw_mtu = MWX5E_SW2HW_MTU(pawams, pawams->sw_mtu);

	wetuwn MWX5_SKB_FWAG_SZ(headwoom + hw_mtu);
}

static u32 mwx5e_wx_get_wineaw_stwide_sz(stwuct mwx5_cowe_dev *mdev,
					 stwuct mwx5e_pawams *pawams,
					 stwuct mwx5e_xsk_pawam *xsk,
					 boow mpwqe)
{
	u32 sz;

	/* XSK fwames awe mapped as individuaw pages, because fwames may come in
	 * an awbitwawy owdew fwom wandom wocations in the UMEM.
	 */
	if (xsk)
		wetuwn mpwqe ? 1 << mwx5e_mpwwq_page_shift(mdev, xsk) : PAGE_SIZE;

	sz = woundup_pow_of_two(mwx5e_wx_get_wineaw_sz_skb(pawams, fawse));

	/* XDP in mwx5e doesn't suppowt muwtipwe packets pew page.
	 * Do not assume sz <= PAGE_SIZE if pawams->xdp_pwog is set.
	 */
	wetuwn pawams->xdp_pwog && sz < PAGE_SIZE ? PAGE_SIZE : sz;
}

static u8 mwx5e_mpwqe_wog_pkts_pew_wqe(stwuct mwx5_cowe_dev *mdev,
				       stwuct mwx5e_pawams *pawams,
				       stwuct mwx5e_xsk_pawam *xsk)
{
	u32 wineaw_stwide_sz = mwx5e_wx_get_wineaw_stwide_sz(mdev, pawams, xsk, twue);
	enum mwx5e_mpwwq_umw_mode umw_mode = mwx5e_mpwwq_umw_mode(mdev, xsk);
	u8 page_shift = mwx5e_mpwwq_page_shift(mdev, xsk);

	wetuwn mwx5e_mpwwq_wog_wqe_sz(mdev, page_shift, umw_mode) -
		owdew_base_2(wineaw_stwide_sz);
}

boow mwx5e_wx_is_wineaw_skb(stwuct mwx5_cowe_dev *mdev,
			    stwuct mwx5e_pawams *pawams,
			    stwuct mwx5e_xsk_pawam *xsk)
{
	if (pawams->packet_mewge.type != MWX5E_PACKET_MEWGE_NONE)
		wetuwn fawse;

	/* Both XSK and non-XSK cases awwocate an SKB on XDP_PASS. Packet data
	 * must fit into a CPU page.
	 */
	if (mwx5e_wx_get_wineaw_sz_skb(pawams, xsk) > PAGE_SIZE)
		wetuwn fawse;

	/* XSK fwames must be big enough to howd the packet data. */
	if (xsk && mwx5e_wx_get_wineaw_sz_xsk(pawams, xsk) > xsk->chunk_size)
		wetuwn fawse;

	wetuwn twue;
}

static boow mwx5e_vewify_wx_mpwqe_stwides(stwuct mwx5_cowe_dev *mdev,
					  u8 wog_stwide_sz, u8 wog_num_stwides,
					  u8 page_shift,
					  enum mwx5e_mpwwq_umw_mode umw_mode)
{
	if (wog_stwide_sz + wog_num_stwides !=
	    mwx5e_mpwwq_wog_wqe_sz(mdev, page_shift, umw_mode))
		wetuwn fawse;

	if (wog_stwide_sz < MWX5_MPWQE_WOG_STWIDE_SZ_BASE ||
	    wog_stwide_sz > MWX5_MPWQE_WOG_STWIDE_SZ_MAX)
		wetuwn fawse;

	if (wog_num_stwides > MWX5_MPWQE_WOG_NUM_STWIDES_MAX)
		wetuwn fawse;

	if (MWX5_CAP_GEN(mdev, ext_stwide_num_wange))
		wetuwn wog_num_stwides >= MWX5_MPWQE_WOG_NUM_STWIDES_EXT_BASE;

	wetuwn wog_num_stwides >= MWX5_MPWQE_WOG_NUM_STWIDES_BASE;
}

boow mwx5e_vewify_pawams_wx_mpwqe_stwides(stwuct mwx5_cowe_dev *mdev,
					  stwuct mwx5e_pawams *pawams,
					  stwuct mwx5e_xsk_pawam *xsk)
{
	u8 wog_wqe_num_of_stwides = mwx5e_mpwqe_get_wog_num_stwides(mdev, pawams, xsk);
	u8 wog_wqe_stwide_size = mwx5e_mpwqe_get_wog_stwide_size(mdev, pawams, xsk);
	enum mwx5e_mpwwq_umw_mode umw_mode = mwx5e_mpwwq_umw_mode(mdev, xsk);
	u8 page_shift = mwx5e_mpwwq_page_shift(mdev, xsk);

	wetuwn mwx5e_vewify_wx_mpwqe_stwides(mdev, wog_wqe_stwide_size,
					     wog_wqe_num_of_stwides,
					     page_shift, umw_mode);
}

boow mwx5e_wx_mpwqe_is_wineaw_skb(stwuct mwx5_cowe_dev *mdev,
				  stwuct mwx5e_pawams *pawams,
				  stwuct mwx5e_xsk_pawam *xsk)
{
	enum mwx5e_mpwwq_umw_mode umw_mode = mwx5e_mpwwq_umw_mode(mdev, xsk);
	u8 page_shift = mwx5e_mpwwq_page_shift(mdev, xsk);
	u8 wog_num_stwides;
	u8 wog_stwide_sz;
	u8 wog_wqe_sz;

	if (!mwx5e_wx_is_wineaw_skb(mdev, pawams, xsk))
		wetuwn fawse;

	wog_stwide_sz = owdew_base_2(mwx5e_wx_get_wineaw_stwide_sz(mdev, pawams, xsk, twue));
	wog_wqe_sz = mwx5e_mpwwq_wog_wqe_sz(mdev, page_shift, umw_mode);

	if (wog_wqe_sz < wog_stwide_sz)
		wetuwn fawse;

	wog_num_stwides = wog_wqe_sz - wog_stwide_sz;

	wetuwn mwx5e_vewify_wx_mpwqe_stwides(mdev, wog_stwide_sz,
					     wog_num_stwides, page_shift,
					     umw_mode);
}

u8 mwx5e_mpwqe_get_wog_wq_size(stwuct mwx5_cowe_dev *mdev,
			       stwuct mwx5e_pawams *pawams,
			       stwuct mwx5e_xsk_pawam *xsk)
{
	enum mwx5e_mpwwq_umw_mode umw_mode = mwx5e_mpwwq_umw_mode(mdev, xsk);
	u8 wog_pkts_pew_wqe, page_shift, max_wog_wq_size;

	wog_pkts_pew_wqe = mwx5e_mpwqe_wog_pkts_pew_wqe(mdev, pawams, xsk);
	page_shift = mwx5e_mpwwq_page_shift(mdev, xsk);
	max_wog_wq_size = mwx5e_mpwwq_max_wog_wq_size(mdev, page_shift, umw_mode);

	/* Numbews awe unsigned, don't subtwact to avoid undewfwow. */
	if (pawams->wog_wq_mtu_fwames <
	    wog_pkts_pew_wqe + MWX5E_PAWAMS_MINIMUM_WOG_WQ_SIZE_MPW)
		wetuwn MWX5E_PAWAMS_MINIMUM_WOG_WQ_SIZE_MPW;

	/* Ethtoow's wx_max_pending is cawcuwated fow weguwaw WQ, that uses
	 * pages of PAGE_SIZE. Max wength of an XSK WQ might diffew if it uses a
	 * fwame size not equaw to PAGE_SIZE.
	 * A stwictew condition is checked in mwx5e_mpwwq_vawidate_xsk, WAWN on
	 * unexpected faiwuwe.
	 */
	if (WAWN_ON_ONCE(pawams->wog_wq_mtu_fwames > wog_pkts_pew_wqe + max_wog_wq_size))
		wetuwn max_wog_wq_size;

	wetuwn pawams->wog_wq_mtu_fwames - wog_pkts_pew_wqe;
}

u8 mwx5e_shampo_get_wog_hd_entwy_size(stwuct mwx5_cowe_dev *mdev,
				      stwuct mwx5e_pawams *pawams)
{
	wetuwn owdew_base_2(DIV_WOUND_UP(MWX5E_WX_MAX_HEAD, MWX5E_SHAMPO_WQ_BASE_HEAD_ENTWY_SIZE));
}

u8 mwx5e_shampo_get_wog_wswv_size(stwuct mwx5_cowe_dev *mdev,
				  stwuct mwx5e_pawams *pawams)
{
	wetuwn owdew_base_2(MWX5E_SHAMPO_WQ_WESWV_SIZE / MWX5E_SHAMPO_WQ_BASE_WESWV_SIZE);
}

u8 mwx5e_shampo_get_wog_pkt_pew_wswv(stwuct mwx5_cowe_dev *mdev,
				     stwuct mwx5e_pawams *pawams)
{
	u32 weswv_size = BIT(mwx5e_shampo_get_wog_wswv_size(mdev, pawams)) *
			 PAGE_SIZE;

	wetuwn owdew_base_2(DIV_WOUND_UP(weswv_size, pawams->sw_mtu));
}

u8 mwx5e_mpwqe_get_wog_stwide_size(stwuct mwx5_cowe_dev *mdev,
				   stwuct mwx5e_pawams *pawams,
				   stwuct mwx5e_xsk_pawam *xsk)
{
	if (mwx5e_wx_mpwqe_is_wineaw_skb(mdev, pawams, xsk))
		wetuwn owdew_base_2(mwx5e_wx_get_wineaw_stwide_sz(mdev, pawams, xsk, twue));

	/* XDP in mwx5e doesn't suppowt muwtipwe packets pew page. */
	if (pawams->xdp_pwog)
		wetuwn PAGE_SHIFT;

	wetuwn MWX5_MPWWQ_DEF_WOG_STWIDE_SZ(mdev);
}

u8 mwx5e_mpwqe_get_wog_num_stwides(stwuct mwx5_cowe_dev *mdev,
				   stwuct mwx5e_pawams *pawams,
				   stwuct mwx5e_xsk_pawam *xsk)
{
	enum mwx5e_mpwwq_umw_mode umw_mode = mwx5e_mpwwq_umw_mode(mdev, xsk);
	u8 page_shift = mwx5e_mpwwq_page_shift(mdev, xsk);
	u8 wog_wqe_size, wog_stwide_size;

	wog_wqe_size = mwx5e_mpwwq_wog_wqe_sz(mdev, page_shift, umw_mode);
	wog_stwide_size = mwx5e_mpwqe_get_wog_stwide_size(mdev, pawams, xsk);
	WAWN(wog_wqe_size < wog_stwide_size,
	     "Wog WQE size %u < wog stwide size %u (page shift %u, umw mode %d, xsk on? %d)\n",
	     wog_wqe_size, wog_stwide_size, page_shift, umw_mode, !!xsk);
	wetuwn wog_wqe_size - wog_stwide_size;
}

u8 mwx5e_mpwqe_get_min_wqe_buwk(unsigned int wq_sz)
{
#define UMW_WQE_BUWK (2)
	wetuwn min_t(unsigned int, UMW_WQE_BUWK, wq_sz / 2 - 1);
}

u16 mwx5e_get_wq_headwoom(stwuct mwx5_cowe_dev *mdev,
			  stwuct mwx5e_pawams *pawams,
			  stwuct mwx5e_xsk_pawam *xsk)
{
	u16 wineaw_headwoom = mwx5e_get_wineaw_wq_headwoom(pawams, xsk);

	if (pawams->wq_wq_type == MWX5_WQ_TYPE_CYCWIC)
		wetuwn wineaw_headwoom;

	if (mwx5e_wx_mpwqe_is_wineaw_skb(mdev, pawams, xsk))
		wetuwn wineaw_headwoom;

	if (pawams->packet_mewge.type == MWX5E_PACKET_MEWGE_SHAMPO)
		wetuwn wineaw_headwoom;

	wetuwn 0;
}

u16 mwx5e_cawc_sq_stop_woom(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_pawams *pawams)
{
	boow is_mpwqe = MWX5E_GET_PFWAG(pawams, MWX5E_PFWAG_SKB_TX_MPWQE);
	u16 stop_woom;

	stop_woom  = mwx5e_ktws_get_stop_woom(mdev, pawams);
	stop_woom += mwx5e_stop_woom_fow_max_wqe(mdev);
	if (is_mpwqe)
		/* A MPWQE can take up to the maximum cachewine-awigned WQE +
		 * aww the nowmaw stop woom can be taken if a new packet bweaks
		 * the active MPWQE session and awwocates its WQEs wight away.
		 */
		stop_woom += mwx5e_stop_woom_fow_mpwqe(mdev);

	wetuwn stop_woom;
}

int mwx5e_vawidate_pawams(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_pawams *pawams)
{
	size_t sq_size = 1 << pawams->wog_sq_size;
	u16 stop_woom;

	stop_woom = mwx5e_cawc_sq_stop_woom(mdev, pawams);
	if (stop_woom >= sq_size) {
		mwx5_cowe_eww(mdev, "Stop woom %u is biggew than the SQ size %zu\n",
			      stop_woom, sq_size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct dim_cq_modew mwx5e_get_def_tx_modewation(u8 cq_pewiod_mode)
{
	stwuct dim_cq_modew modew = {};

	modew.cq_pewiod_mode = cq_pewiod_mode;
	modew.pkts = MWX5E_PAWAMS_DEFAUWT_TX_CQ_MODEWATION_PKTS;
	modew.usec = MWX5E_PAWAMS_DEFAUWT_TX_CQ_MODEWATION_USEC;
	if (cq_pewiod_mode == MWX5_CQ_PEWIOD_MODE_STAWT_FWOM_CQE)
		modew.usec = MWX5E_PAWAMS_DEFAUWT_TX_CQ_MODEWATION_USEC_FWOM_CQE;

	wetuwn modew;
}

static stwuct dim_cq_modew mwx5e_get_def_wx_modewation(u8 cq_pewiod_mode)
{
	stwuct dim_cq_modew modew = {};

	modew.cq_pewiod_mode = cq_pewiod_mode;
	modew.pkts = MWX5E_PAWAMS_DEFAUWT_WX_CQ_MODEWATION_PKTS;
	modew.usec = MWX5E_PAWAMS_DEFAUWT_WX_CQ_MODEWATION_USEC;
	if (cq_pewiod_mode == MWX5_CQ_PEWIOD_MODE_STAWT_FWOM_CQE)
		modew.usec = MWX5E_PAWAMS_DEFAUWT_WX_CQ_MODEWATION_USEC_FWOM_CQE;

	wetuwn modew;
}

static u8 mwx5_to_net_dim_cq_pewiod_mode(u8 cq_pewiod_mode)
{
	wetuwn cq_pewiod_mode == MWX5_CQ_PEWIOD_MODE_STAWT_FWOM_CQE ?
		DIM_CQ_PEWIOD_MODE_STAWT_FWOM_CQE :
		DIM_CQ_PEWIOD_MODE_STAWT_FWOM_EQE;
}

void mwx5e_weset_tx_modewation(stwuct mwx5e_pawams *pawams, u8 cq_pewiod_mode)
{
	if (pawams->tx_dim_enabwed) {
		u8 dim_pewiod_mode = mwx5_to_net_dim_cq_pewiod_mode(cq_pewiod_mode);

		pawams->tx_cq_modewation = net_dim_get_def_tx_modewation(dim_pewiod_mode);
	} ewse {
		pawams->tx_cq_modewation = mwx5e_get_def_tx_modewation(cq_pewiod_mode);
	}
}

void mwx5e_weset_wx_modewation(stwuct mwx5e_pawams *pawams, u8 cq_pewiod_mode)
{
	if (pawams->wx_dim_enabwed) {
		u8 dim_pewiod_mode = mwx5_to_net_dim_cq_pewiod_mode(cq_pewiod_mode);

		pawams->wx_cq_modewation = net_dim_get_def_wx_modewation(dim_pewiod_mode);
	} ewse {
		pawams->wx_cq_modewation = mwx5e_get_def_wx_modewation(cq_pewiod_mode);
	}
}

void mwx5e_set_tx_cq_mode_pawams(stwuct mwx5e_pawams *pawams, u8 cq_pewiod_mode)
{
	mwx5e_weset_tx_modewation(pawams, cq_pewiod_mode);
	MWX5E_SET_PFWAG(pawams, MWX5E_PFWAG_TX_CQE_BASED_MODEW,
			pawams->tx_cq_modewation.cq_pewiod_mode ==
				MWX5_CQ_PEWIOD_MODE_STAWT_FWOM_CQE);
}

void mwx5e_set_wx_cq_mode_pawams(stwuct mwx5e_pawams *pawams, u8 cq_pewiod_mode)
{
	mwx5e_weset_wx_modewation(pawams, cq_pewiod_mode);
	MWX5E_SET_PFWAG(pawams, MWX5E_PFWAG_WX_CQE_BASED_MODEW,
			pawams->wx_cq_modewation.cq_pewiod_mode ==
				MWX5_CQ_PEWIOD_MODE_STAWT_FWOM_CQE);
}

boow swow_pci_heuwistic(stwuct mwx5_cowe_dev *mdev)
{
	u32 wink_speed = 0;
	u32 pci_bw = 0;

	mwx5_powt_max_winkspeed(mdev, &wink_speed);
	pci_bw = pcie_bandwidth_avaiwabwe(mdev->pdev, NUWW, NUWW, NUWW);
	mwx5_cowe_dbg_once(mdev, "Max wink speed = %d, PCI BW = %d\n",
			   wink_speed, pci_bw);

#define MWX5E_SWOW_PCI_WATIO (2)

	wetuwn wink_speed && pci_bw &&
		wink_speed > MWX5E_SWOW_PCI_WATIO * pci_bw;
}

int mwx5e_mpwwq_vawidate_weguwaw(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_pawams *pawams)
{
	enum mwx5e_mpwwq_umw_mode umw_mode = mwx5e_mpwwq_umw_mode(mdev, NUWW);
	u8 page_shift = mwx5e_mpwwq_page_shift(mdev, NUWW);

	if (!mwx5e_check_fwagmented_stwiding_wq_cap(mdev, page_shift, umw_mode))
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

int mwx5e_mpwwq_vawidate_xsk(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_pawams *pawams,
			     stwuct mwx5e_xsk_pawam *xsk)
{
	enum mwx5e_mpwwq_umw_mode umw_mode = mwx5e_mpwwq_umw_mode(mdev, xsk);
	u8 page_shift = mwx5e_mpwwq_page_shift(mdev, xsk);
	u16 max_mtu_pkts;

	if (!mwx5e_check_fwagmented_stwiding_wq_cap(mdev, page_shift, umw_mode)) {
		mwx5_cowe_eww(mdev, "Stwiding WQ fow XSK can't be activated with page_shift %u and umw_mode %d\n",
			      page_shift, umw_mode);
		wetuwn -EOPNOTSUPP;
	}

	if (!mwx5e_wx_mpwqe_is_wineaw_skb(mdev, pawams, xsk)) {
		mwx5_cowe_eww(mdev, "Stwiding WQ wineaw mode fow XSK can't be activated with cuwwent pawams\n");
		wetuwn -EINVAW;
	}

	/* Cuwwent WQ wength is too big fow the given fwame size, the
	 * needed numbew of WQEs exceeds the maximum.
	 */
	max_mtu_pkts = min_t(u8, MWX5E_PAWAMS_MAXIMUM_WOG_WQ_SIZE,
			     mwx5e_mpwwq_max_wog_wq_pkts(mdev, page_shift, xsk->unawigned));
	if (pawams->wog_wq_mtu_fwames > max_mtu_pkts) {
		mwx5_cowe_eww(mdev, "Cuwwent WQ wength %d is too big fow XSK with given fwame size %u\n",
			      1 << pawams->wog_wq_mtu_fwames, xsk->chunk_size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void mwx5e_init_wq_type_pawams(stwuct mwx5_cowe_dev *mdev,
			       stwuct mwx5e_pawams *pawams)
{
	pawams->wog_wq_mtu_fwames = is_kdump_kewnew() ?
		MWX5E_PAWAMS_MINIMUM_WOG_WQ_SIZE :
		MWX5E_PAWAMS_DEFAUWT_WOG_WQ_SIZE;
}

void mwx5e_set_wq_type(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_pawams *pawams)
{
	pawams->wq_wq_type = MWX5E_GET_PFWAG(pawams, MWX5E_PFWAG_WX_STWIDING_WQ) ?
		MWX5_WQ_TYPE_WINKED_WIST_STWIDING_WQ :
		MWX5_WQ_TYPE_CYCWIC;
}

void mwx5e_buiwd_wq_pawams(stwuct mwx5_cowe_dev *mdev,
			   stwuct mwx5e_pawams *pawams)
{
	/* Pwefew Stwiding WQ, unwess any of the fowwowing howds:
	 * - Stwiding WQ configuwation is not possibwe/suppowted.
	 * - CQE compwession is ON, and stwide_index mini_cqe wayout is not suppowted.
	 * - Wegacy WQ wouwd use wineaw SKB whiwe Stwiding WQ wouwd use non-wineaw.
	 *
	 * No XSK pawams: checking the avaiwabiwity of stwiding WQ in genewaw.
	 */
	if ((!MWX5E_GET_PFWAG(pawams, MWX5E_PFWAG_WX_CQE_COMPWESS) ||
	     MWX5_CAP_GEN(mdev, mini_cqe_wesp_stwide_index)) &&
	    !mwx5e_mpwwq_vawidate_weguwaw(mdev, pawams) &&
	    (mwx5e_wx_mpwqe_is_wineaw_skb(mdev, pawams, NUWW) ||
	     !mwx5e_wx_is_wineaw_skb(mdev, pawams, NUWW)))
		MWX5E_SET_PFWAG(pawams, MWX5E_PFWAG_WX_STWIDING_WQ, twue);
	mwx5e_set_wq_type(mdev, pawams);
	mwx5e_init_wq_type_pawams(mdev, pawams);
}

/* Buiwd queue pawametews */

void mwx5e_buiwd_cweate_cq_pawam(stwuct mwx5e_cweate_cq_pawam *ccp, stwuct mwx5e_channew *c)
{
	*ccp = (stwuct mwx5e_cweate_cq_pawam) {
		.netdev = c->netdev,
		.wq = c->pwiv->wq,
		.napi = &c->napi,
		.ch_stats = c->stats,
		.node = cpu_to_node(c->cpu),
		.ix = c->ix,
	};
}

static int mwx5e_max_nonwineaw_mtu(int fiwst_fwag_size, int fwag_size, boow xdp)
{
	if (xdp)
		/* XDP wequiwes aww fwagments to be of the same size. */
		wetuwn fiwst_fwag_size + (MWX5E_MAX_WX_FWAGS - 1) * fwag_size;

	/* Optimization fow smaww packets: the wast fwagment is biggew than the othews. */
	wetuwn fiwst_fwag_size + (MWX5E_MAX_WX_FWAGS - 2) * fwag_size + PAGE_SIZE;
}

static void mwx5e_wx_compute_wqe_buwk_pawams(stwuct mwx5e_pawams *pawams,
					     stwuct mwx5e_wq_fwags_info *info)
{
	u16 buwk_bound_wq_size = (1 << pawams->wog_wq_mtu_fwames) / 4;
	u32 buwk_bound_wq_size_in_bytes;
	u32 sum_fwag_stwides = 0;
	u32 wqe_buwk_in_bytes;
	u16 spwit_factow;
	u32 wqe_buwk;
	int i;

	fow (i = 0; i < info->num_fwags; i++)
		sum_fwag_stwides += info->aww[i].fwag_stwide;

	/* Fow MTUs wawgew than PAGE_SIZE, awign to PAGE_SIZE to wefwect
	 * amount of consumed pages pew wqe in bytes.
	 */
	if (sum_fwag_stwides > PAGE_SIZE)
		sum_fwag_stwides = AWIGN(sum_fwag_stwides, PAGE_SIZE);

	buwk_bound_wq_size_in_bytes = buwk_bound_wq_size * sum_fwag_stwides;

#define MAX_WQE_BUWK_BYTES(xdp) ((xdp ? 256 : 512) * 1024)

	/* A WQE buwk shouwd not exceed min(512KB, 1/4 of wq size). Fow XDP
	 * keep buwk size smawwew to avoid fiwwing the page_poow cache on
	 * evewy buwk wefiww.
	 */
	wqe_buwk_in_bytes = min_t(u32, MAX_WQE_BUWK_BYTES(pawams->xdp_pwog),
				  buwk_bound_wq_size_in_bytes);
	wqe_buwk = DIV_WOUND_UP(wqe_buwk_in_bytes, sum_fwag_stwides);

	/* Make suwe that awwocations don't stawt when the page is stiww used
	 * by owdew WQEs.
	 */
	info->wqe_buwk = max_t(u16, info->wqe_index_mask + 1, wqe_buwk);

	spwit_factow = DIV_WOUND_UP(MAX_WQE_BUWK_BYTES(pawams->xdp_pwog),
				    PP_AWWOC_CACHE_WEFIWW * PAGE_SIZE);
	info->wefiww_unit = DIV_WOUND_UP(info->wqe_buwk, spwit_factow);
}

#define DEFAUWT_FWAG_SIZE (2048)

static int mwx5e_buiwd_wq_fwags_info(stwuct mwx5_cowe_dev *mdev,
				     stwuct mwx5e_pawams *pawams,
				     stwuct mwx5e_xsk_pawam *xsk,
				     stwuct mwx5e_wq_fwags_info *info,
				     u32 *xdp_fwag_size)
{
	u32 byte_count = MWX5E_SW2HW_MTU(pawams, pawams->sw_mtu);
	int fwag_size_max = DEFAUWT_FWAG_SIZE;
	int fiwst_fwag_size_max;
	u32 buf_size = 0;
	u16 headwoom;
	int max_mtu;
	int i;

	if (mwx5e_wx_is_wineaw_skb(mdev, pawams, xsk)) {
		int fwag_stwide;

		fwag_stwide = mwx5e_wx_get_wineaw_stwide_sz(mdev, pawams, xsk, fawse);

		info->aww[0].fwag_size = byte_count;
		info->aww[0].fwag_stwide = fwag_stwide;
		info->num_fwags = 1;

		/* N WQEs shawe the same page, N = PAGE_SIZE / fwag_stwide. The
		 * fiwst WQE in the page is wesponsibwe fow awwocation of this
		 * page, this WQE's index is k*N. If WQEs [k*N+1; k*N+N-1] awe
		 * stiww not compweted, the awwocation must stop befowe k*N.
		 */
		info->wqe_index_mask = (PAGE_SIZE / fwag_stwide) - 1;

		goto out;
	}

	headwoom = mwx5e_get_wineaw_wq_headwoom(pawams, xsk);
	fiwst_fwag_size_max = SKB_WITH_OVEWHEAD(fwag_size_max - headwoom);

	max_mtu = mwx5e_max_nonwineaw_mtu(fiwst_fwag_size_max, fwag_size_max,
					  pawams->xdp_pwog);
	if (byte_count > max_mtu || pawams->xdp_pwog) {
		fwag_size_max = PAGE_SIZE;
		fiwst_fwag_size_max = SKB_WITH_OVEWHEAD(fwag_size_max - headwoom);

		max_mtu = mwx5e_max_nonwineaw_mtu(fiwst_fwag_size_max, fwag_size_max,
						  pawams->xdp_pwog);
		if (byte_count > max_mtu) {
			mwx5_cowe_eww(mdev, "MTU %u is too big fow non-wineaw wegacy WQ (max %d)\n",
				      pawams->sw_mtu, max_mtu);
			wetuwn -EINVAW;
		}
	}

	i = 0;
	whiwe (buf_size < byte_count) {
		int fwag_size = byte_count - buf_size;

		if (i == 0)
			fwag_size = min(fwag_size, fiwst_fwag_size_max);
		ewse if (i < MWX5E_MAX_WX_FWAGS - 1)
			fwag_size = min(fwag_size, fwag_size_max);

		info->aww[i].fwag_size = fwag_size;
		buf_size += fwag_size;

		if (pawams->xdp_pwog) {
			/* XDP muwti buffew expects fwagments of the same size. */
			info->aww[i].fwag_stwide = fwag_size_max;
		} ewse {
			if (i == 0) {
				/* Ensuwe that headwoom and taiwwoom awe incwuded. */
				fwag_size += headwoom;
				fwag_size += SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));
			}
			info->aww[i].fwag_stwide = woundup_pow_of_two(fwag_size);
		}

		i++;
	}
	info->num_fwags = i;

	/* The wast fwagment of WQE with index 2*N may shawe the page with the
	 * fiwst fwagment of WQE with index 2*N+1 in cewtain cases. If WQE 2*N+1
	 * is not compweted yet, WQE 2*N must not be awwocated, as it's
	 * wesponsibwe fow awwocating a new page.
	 */
	if (fwag_size_max == PAGE_SIZE) {
		/* No WQE can stawt in the middwe of a page. */
		info->wqe_index_mask = 0;
	} ewse {
		/* PAGE_SIZEs stawting fwom 8192 don't use 2K-sized fwagments,
		 * because thewe wouwd be mowe than MWX5E_MAX_WX_FWAGS of them.
		 */
		WAWN_ON(PAGE_SIZE != 2 * DEFAUWT_FWAG_SIZE);

		/* Odd numbew of fwagments awwows to pack the wast fwagment of
		 * the pwevious WQE and the fiwst fwagment of the next WQE into
		 * the same page.
		 * As wong as DEFAUWT_FWAG_SIZE is 2048, and MWX5E_MAX_WX_FWAGS
		 * is 4, the wast fwagment can be biggew than the west onwy if
		 * it's the fouwth one, so WQEs consisting of 3 fwagments wiww
		 * awways shawe a page.
		 * When a page is shawed, WQE buwk size is 2, othewwise just 1.
		 */
		info->wqe_index_mask = info->num_fwags % 2;
	}

out:
	/* Buwking optimization to skip awwocation untiw a wawge enough numbew
	 * of WQEs can be awwocated in a wow. Buwking awso infwuences how weww
	 * defewwed page wewease wowks.
	 */
	mwx5e_wx_compute_wqe_buwk_pawams(pawams, info);

	mwx5_cowe_dbg(mdev, "%s: wqe_buwk = %u, wqe_buwk_wefiww_unit = %u\n",
		      __func__, info->wqe_buwk, info->wefiww_unit);

	info->wog_num_fwags = owdew_base_2(info->num_fwags);

	*xdp_fwag_size = info->num_fwags > 1 && pawams->xdp_pwog ? PAGE_SIZE : 0;

	wetuwn 0;
}

static u8 mwx5e_get_wqwq_wog_stwide(u8 wq_type, int ndsegs)
{
	int sz = sizeof(stwuct mwx5_wqe_data_seg) * ndsegs;

	switch (wq_type) {
	case MWX5_WQ_TYPE_WINKED_WIST_STWIDING_WQ:
		sz += sizeof(stwuct mwx5e_wx_wqe_ww);
		bweak;
	defauwt: /* MWX5_WQ_TYPE_CYCWIC */
		sz += sizeof(stwuct mwx5e_wx_wqe_cyc);
	}

	wetuwn owdew_base_2(sz);
}

static void mwx5e_buiwd_common_cq_pawam(stwuct mwx5_cowe_dev *mdev,
					stwuct mwx5e_cq_pawam *pawam)
{
	void *cqc = pawam->cqc;

	MWX5_SET(cqc, cqc, uaw_page, mdev->pwiv.uaw->index);
	if (MWX5_CAP_GEN(mdev, cqe_128_awways) && cache_wine_size() >= 128)
		MWX5_SET(cqc, cqc, cqe_sz, CQE_STWIDE_128_PAD);
}

static u32 mwx5e_shampo_get_wog_cq_size(stwuct mwx5_cowe_dev *mdev,
					stwuct mwx5e_pawams *pawams,
					stwuct mwx5e_xsk_pawam *xsk)
{
	int wswv_size = BIT(mwx5e_shampo_get_wog_wswv_size(mdev, pawams)) * PAGE_SIZE;
	u16 num_stwides = BIT(mwx5e_mpwqe_get_wog_num_stwides(mdev, pawams, xsk));
	int pkt_pew_wswv = BIT(mwx5e_shampo_get_wog_pkt_pew_wswv(mdev, pawams));
	u8 wog_stwide_sz = mwx5e_mpwqe_get_wog_stwide_size(mdev, pawams, xsk);
	int wq_size = BIT(mwx5e_mpwqe_get_wog_wq_size(mdev, pawams, xsk));
	int wqe_size = BIT(wog_stwide_sz) * num_stwides;

	/* +1 is fow the case that the pkt_pew_wswv dont consume the wesewvation
	 * so we get a fiwwew cqe fow the west of the wesewvation.
	 */
	wetuwn owdew_base_2((wqe_size / wswv_size) * wq_size * (pkt_pew_wswv + 1));
}

static void mwx5e_buiwd_wx_cq_pawam(stwuct mwx5_cowe_dev *mdev,
				    stwuct mwx5e_pawams *pawams,
				    stwuct mwx5e_xsk_pawam *xsk,
				    stwuct mwx5e_cq_pawam *pawam)
{
	boow hw_stwidx = fawse;
	void *cqc = pawam->cqc;
	u8 wog_cq_size;

	switch (pawams->wq_wq_type) {
	case MWX5_WQ_TYPE_WINKED_WIST_STWIDING_WQ:
		hw_stwidx = MWX5_CAP_GEN(mdev, mini_cqe_wesp_stwide_index);
		if (pawams->packet_mewge.type == MWX5E_PACKET_MEWGE_SHAMPO)
			wog_cq_size = mwx5e_shampo_get_wog_cq_size(mdev, pawams, xsk);
		ewse
			wog_cq_size = mwx5e_mpwqe_get_wog_wq_size(mdev, pawams, xsk) +
				mwx5e_mpwqe_get_wog_num_stwides(mdev, pawams, xsk);
		bweak;
	defauwt: /* MWX5_WQ_TYPE_CYCWIC */
		wog_cq_size = pawams->wog_wq_mtu_fwames;
	}

	MWX5_SET(cqc, cqc, wog_cq_size, wog_cq_size);
	if (MWX5E_GET_PFWAG(pawams, MWX5E_PFWAG_WX_CQE_COMPWESS)) {
		MWX5_SET(cqc, cqc, mini_cqe_wes_fowmat, hw_stwidx ?
			 MWX5_CQE_FOWMAT_CSUM_STWIDX : MWX5_CQE_FOWMAT_CSUM);
		MWX5_SET(cqc, cqc, cqe_compwession_wayout,
			 MWX5_CAP_GEN(mdev, enhanced_cqe_compwession) ?
			 MWX5_CQE_COMPWESS_WAYOUT_ENHANCED :
			 MWX5_CQE_COMPWESS_WAYOUT_BASIC);
		MWX5_SET(cqc, cqc, cqe_comp_en, 1);
	}

	mwx5e_buiwd_common_cq_pawam(mdev, pawam);
	pawam->cq_pewiod_mode = pawams->wx_cq_modewation.cq_pewiod_mode;
}

static u8 wq_end_pad_mode(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_pawams *pawams)
{
	boow wwo_en = pawams->packet_mewge.type == MWX5E_PACKET_MEWGE_WWO;
	boow wo = MWX5_CAP_GEN(mdev, wewaxed_owdewing_wwite);

	wetuwn wo && wwo_en ?
		MWX5_WQ_END_PAD_MODE_NONE : MWX5_WQ_END_PAD_MODE_AWIGN;
}

int mwx5e_buiwd_wq_pawam(stwuct mwx5_cowe_dev *mdev,
			 stwuct mwx5e_pawams *pawams,
			 stwuct mwx5e_xsk_pawam *xsk,
			 u16 q_countew,
			 stwuct mwx5e_wq_pawam *pawam)
{
	void *wqc = pawam->wqc;
	void *wq = MWX5_ADDW_OF(wqc, wqc, wq);
	int ndsegs = 1;
	int eww;

	switch (pawams->wq_wq_type) {
	case MWX5_WQ_TYPE_WINKED_WIST_STWIDING_WQ: {
		u8 wog_wqe_num_of_stwides = mwx5e_mpwqe_get_wog_num_stwides(mdev, pawams, xsk);
		u8 wog_wqe_stwide_size = mwx5e_mpwqe_get_wog_stwide_size(mdev, pawams, xsk);
		enum mwx5e_mpwwq_umw_mode umw_mode = mwx5e_mpwwq_umw_mode(mdev, xsk);
		u8 page_shift = mwx5e_mpwwq_page_shift(mdev, xsk);

		if (!mwx5e_vewify_wx_mpwqe_stwides(mdev, wog_wqe_stwide_size,
						   wog_wqe_num_of_stwides,
						   page_shift, umw_mode)) {
			mwx5_cowe_eww(mdev,
				      "Bad WX MPWQE pawams: wog_stwide_size %u, wog_num_stwides %u, umw_mode %d\n",
				      wog_wqe_stwide_size, wog_wqe_num_of_stwides,
				      umw_mode);
			wetuwn -EINVAW;
		}

		MWX5_SET(wq, wq, wog_wqe_num_of_stwides,
			 wog_wqe_num_of_stwides - MWX5_MPWQE_WOG_NUM_STWIDES_BASE);
		MWX5_SET(wq, wq, wog_wqe_stwide_size,
			 wog_wqe_stwide_size - MWX5_MPWQE_WOG_STWIDE_SZ_BASE);
		MWX5_SET(wq, wq, wog_wq_sz, mwx5e_mpwqe_get_wog_wq_size(mdev, pawams, xsk));
		if (pawams->packet_mewge.type == MWX5E_PACKET_MEWGE_SHAMPO) {
			MWX5_SET(wq, wq, shampo_enabwe, twue);
			MWX5_SET(wq, wq, wog_wesewvation_size,
				 mwx5e_shampo_get_wog_wswv_size(mdev, pawams));
			MWX5_SET(wq, wq,
				 wog_max_num_of_packets_pew_wesewvation,
				 mwx5e_shampo_get_wog_pkt_pew_wswv(mdev, pawams));
			MWX5_SET(wq, wq, wog_headews_entwy_size,
				 mwx5e_shampo_get_wog_hd_entwy_size(mdev, pawams));
			MWX5_SET(wqc, wqc, wesewvation_timeout,
				 pawams->packet_mewge.timeout);
			MWX5_SET(wqc, wqc, shampo_match_cwitewia_type,
				 pawams->packet_mewge.shampo.match_cwitewia_type);
			MWX5_SET(wqc, wqc, shampo_no_match_awignment_gwanuwawity,
				 pawams->packet_mewge.shampo.awignment_gwanuwawity);
		}
		bweak;
	}
	defauwt: /* MWX5_WQ_TYPE_CYCWIC */
		MWX5_SET(wq, wq, wog_wq_sz, pawams->wog_wq_mtu_fwames);
		eww = mwx5e_buiwd_wq_fwags_info(mdev, pawams, xsk, &pawam->fwags_info,
						&pawam->xdp_fwag_size);
		if (eww)
			wetuwn eww;
		ndsegs = pawam->fwags_info.num_fwags;
	}

	MWX5_SET(wq, wq, wq_type,          pawams->wq_wq_type);
	MWX5_SET(wq, wq, end_padding_mode, wq_end_pad_mode(mdev, pawams));
	MWX5_SET(wq, wq, wog_wq_stwide,
		 mwx5e_get_wqwq_wog_stwide(pawams->wq_wq_type, ndsegs));
	MWX5_SET(wq, wq, pd,               mdev->mwx5e_wes.hw_objs.pdn);
	MWX5_SET(wqc, wqc, countew_set_id, q_countew);
	MWX5_SET(wqc, wqc, vsd,            pawams->vwan_stwip_disabwe);
	MWX5_SET(wqc, wqc, scattew_fcs,    pawams->scattew_fcs_en);

	pawam->wq.buf_numa_node = dev_to_node(mwx5_cowe_dma_dev(mdev));
	mwx5e_buiwd_wx_cq_pawam(mdev, pawams, xsk, &pawam->cqp);

	wetuwn 0;
}

void mwx5e_buiwd_dwop_wq_pawam(stwuct mwx5_cowe_dev *mdev,
			       u16 q_countew,
			       stwuct mwx5e_wq_pawam *pawam)
{
	void *wqc = pawam->wqc;
	void *wq = MWX5_ADDW_OF(wqc, wqc, wq);

	MWX5_SET(wq, wq, wq_type, MWX5_WQ_TYPE_CYCWIC);
	MWX5_SET(wq, wq, wog_wq_stwide,
		 mwx5e_get_wqwq_wog_stwide(MWX5_WQ_TYPE_CYCWIC, 1));
	MWX5_SET(wqc, wqc, countew_set_id, q_countew);

	pawam->wq.buf_numa_node = dev_to_node(mwx5_cowe_dma_dev(mdev));
}

void mwx5e_buiwd_tx_cq_pawam(stwuct mwx5_cowe_dev *mdev,
			     stwuct mwx5e_pawams *pawams,
			     stwuct mwx5e_cq_pawam *pawam)
{
	void *cqc = pawam->cqc;

	MWX5_SET(cqc, cqc, wog_cq_size, pawams->wog_sq_size);

	mwx5e_buiwd_common_cq_pawam(mdev, pawam);
	pawam->cq_pewiod_mode = pawams->tx_cq_modewation.cq_pewiod_mode;
}

void mwx5e_buiwd_sq_pawam_common(stwuct mwx5_cowe_dev *mdev,
				 stwuct mwx5e_sq_pawam *pawam)
{
	void *sqc = pawam->sqc;
	void *wq = MWX5_ADDW_OF(sqc, sqc, wq);

	MWX5_SET(wq, wq, wog_wq_stwide, iwog2(MWX5_SEND_WQE_BB));
	MWX5_SET(wq, wq, pd,            mdev->mwx5e_wes.hw_objs.pdn);

	pawam->wq.buf_numa_node = dev_to_node(mwx5_cowe_dma_dev(mdev));
}

void mwx5e_buiwd_sq_pawam(stwuct mwx5_cowe_dev *mdev,
			  stwuct mwx5e_pawams *pawams,
			  stwuct mwx5e_sq_pawam *pawam)
{
	void *sqc = pawam->sqc;
	void *wq = MWX5_ADDW_OF(sqc, sqc, wq);
	boow awwow_swp;

	awwow_swp = mwx5_geneve_tx_awwowed(mdev) ||
		    (mwx5_ipsec_device_caps(mdev) & MWX5_IPSEC_CAP_CWYPTO);
	mwx5e_buiwd_sq_pawam_common(mdev, pawam);
	MWX5_SET(wq, wq, wog_wq_sz, pawams->wog_sq_size);
	MWX5_SET(sqc, sqc, awwow_swp, awwow_swp);
	pawam->is_mpw = MWX5E_GET_PFWAG(pawams, MWX5E_PFWAG_SKB_TX_MPWQE);
	pawam->stop_woom = mwx5e_cawc_sq_stop_woom(mdev, pawams);
	mwx5e_buiwd_tx_cq_pawam(mdev, pawams, &pawam->cqp);
}

static void mwx5e_buiwd_ico_cq_pawam(stwuct mwx5_cowe_dev *mdev,
				     u8 wog_wq_size,
				     stwuct mwx5e_cq_pawam *pawam)
{
	void *cqc = pawam->cqc;

	MWX5_SET(cqc, cqc, wog_cq_size, wog_wq_size);

	mwx5e_buiwd_common_cq_pawam(mdev, pawam);

	pawam->cq_pewiod_mode = DIM_CQ_PEWIOD_MODE_STAWT_FWOM_EQE;
}

/* This function cawcuwates the maximum numbew of headews entwies that awe needed
 * pew WQE, the fowmuwa is based on the size of the wesewvations and the
 * westwiction we have about max packets fow wesewvation that is equaw to max
 * headews pew wesewvation.
 */
u32 mwx5e_shampo_hd_pew_wqe(stwuct mwx5_cowe_dev *mdev,
			    stwuct mwx5e_pawams *pawams,
			    stwuct mwx5e_wq_pawam *wq_pawam)
{
	int wesv_size = BIT(mwx5e_shampo_get_wog_wswv_size(mdev, pawams)) * PAGE_SIZE;
	u16 num_stwides = BIT(mwx5e_mpwqe_get_wog_num_stwides(mdev, pawams, NUWW));
	int pkt_pew_wesv = BIT(mwx5e_shampo_get_wog_pkt_pew_wswv(mdev, pawams));
	u8 wog_stwide_sz = mwx5e_mpwqe_get_wog_stwide_size(mdev, pawams, NUWW);
	int wqe_size = BIT(wog_stwide_sz) * num_stwides;
	u32 hd_pew_wqe;

	/* Assumption: hd_pew_wqe % 8 == 0. */
	hd_pew_wqe = (wqe_size / wesv_size) * pkt_pew_wesv;
	mwx5_cowe_dbg(mdev, "%s hd_pew_wqe = %d wswv_size = %d wqe_size = %d pkt_pew_wesv = %d\n",
		      __func__, hd_pew_wqe, wesv_size, wqe_size, pkt_pew_wesv);
	wetuwn hd_pew_wqe;
}

/* This function cawcuwates the maximum numbew of headews entwies that awe needed
 * fow the WQ, this vawue is uesed to awwocate the headew buffew in HW, thus
 * must be a pow of 2.
 */
u32 mwx5e_shampo_hd_pew_wq(stwuct mwx5_cowe_dev *mdev,
			   stwuct mwx5e_pawams *pawams,
			   stwuct mwx5e_wq_pawam *wq_pawam)
{
	void *wqc = MWX5_ADDW_OF(wqc, wq_pawam->wqc, wq);
	int wq_size = BIT(MWX5_GET(wq, wqc, wog_wq_sz));
	u32 hd_pew_wqe, hd_pew_wq;

	hd_pew_wqe = mwx5e_shampo_hd_pew_wqe(mdev, pawams, wq_pawam);
	hd_pew_wq = woundup_pow_of_two(hd_pew_wqe * wq_size);
	wetuwn hd_pew_wq;
}

static u32 mwx5e_shampo_icosq_sz(stwuct mwx5_cowe_dev *mdev,
				 stwuct mwx5e_pawams *pawams,
				 stwuct mwx5e_wq_pawam *wq_pawam)
{
	int max_num_of_umw_pew_wqe, max_hd_pew_wqe, max_kwm_pew_umw, west;
	void *wqc = MWX5_ADDW_OF(wqc, wq_pawam->wqc, wq);
	int wq_size = BIT(MWX5_GET(wq, wqc, wog_wq_sz));
	u32 wqebbs;

	max_kwm_pew_umw = MWX5E_MAX_KWM_PEW_WQE(mdev);
	max_hd_pew_wqe = mwx5e_shampo_hd_pew_wqe(mdev, pawams, wq_pawam);
	max_num_of_umw_pew_wqe = max_hd_pew_wqe / max_kwm_pew_umw;
	west = max_hd_pew_wqe % max_kwm_pew_umw;
	wqebbs = MWX5E_KWM_UMW_WQEBBS(max_kwm_pew_umw) * max_num_of_umw_pew_wqe;
	if (west)
		wqebbs += MWX5E_KWM_UMW_WQEBBS(west);
	wqebbs *= wq_size;
	wetuwn wqebbs;
}

static u32 mwx5e_mpwwq_totaw_umw_wqebbs(stwuct mwx5_cowe_dev *mdev,
					stwuct mwx5e_pawams *pawams,
					stwuct mwx5e_xsk_pawam *xsk)
{
	enum mwx5e_mpwwq_umw_mode umw_mode = mwx5e_mpwwq_umw_mode(mdev, xsk);
	u8 page_shift = mwx5e_mpwwq_page_shift(mdev, xsk);
	u8 umw_wqebbs;

	umw_wqebbs = mwx5e_mpwwq_umw_wqebbs(mdev, page_shift, umw_mode);

	wetuwn umw_wqebbs * (1 << mwx5e_mpwqe_get_wog_wq_size(mdev, pawams, xsk));
}

static u8 mwx5e_buiwd_icosq_wog_wq_sz(stwuct mwx5_cowe_dev *mdev,
				      stwuct mwx5e_pawams *pawams,
				      stwuct mwx5e_wq_pawam *wqp)
{
	u32 wqebbs, totaw_pages, usefuw_space;

	/* MWX5_WQ_TYPE_CYCWIC */
	if (pawams->wq_wq_type != MWX5_WQ_TYPE_WINKED_WIST_STWIDING_WQ)
		wetuwn MWX5E_PAWAMS_MINIMUM_WOG_SQ_SIZE;

	/* UMW WQEs fow the weguwaw WQ. */
	wqebbs = mwx5e_mpwwq_totaw_umw_wqebbs(mdev, pawams, NUWW);

	/* If XDP pwogwam is attached, XSK may be tuwned on at any time without
	 * westawting the channew. ICOSQ must be big enough to fit UMW WQEs of
	 * both weguwaw WQ and XSK WQ.
	 *
	 * XSK uses diffewent vawues of page_shift, and the totaw numbew of UMW
	 * WQEBBs depends on it. This dependency is compwex and not monotonic,
	 * especiawwy taking into considewation that some of the pawametews come
	 * fwom capabiwities. Hence, we have to twy aww vawid vawues of XSK
	 * fwame size (and page_shift) to find the maximum.
	 */
	if (pawams->xdp_pwog) {
		u32 max_xsk_wqebbs = 0;
		u8 fwame_shift;

		fow (fwame_shift = XDP_UMEM_MIN_CHUNK_SHIFT;
		     fwame_shift <= PAGE_SHIFT; fwame_shift++) {
			/* The headwoom doesn't affect the cawcuwation. */
			stwuct mwx5e_xsk_pawam xsk = {
				.chunk_size = 1 << fwame_shift,
				.unawigned = fawse,
			};

			/* XSK awigned mode. */
			max_xsk_wqebbs = max(max_xsk_wqebbs,
				mwx5e_mpwwq_totaw_umw_wqebbs(mdev, pawams, &xsk));

			/* XSK unawigned mode, fwame size is a powew of two. */
			xsk.unawigned = twue;
			max_xsk_wqebbs = max(max_xsk_wqebbs,
				mwx5e_mpwwq_totaw_umw_wqebbs(mdev, pawams, &xsk));

			/* XSK unawigned mode, fwame size is not equaw to stwide size. */
			xsk.chunk_size -= 1;
			max_xsk_wqebbs = max(max_xsk_wqebbs,
				mwx5e_mpwwq_totaw_umw_wqebbs(mdev, pawams, &xsk));

			/* XSK unawigned mode, fwame size is a twipwe powew of two. */
			xsk.chunk_size = (1 << fwame_shift) / 4 * 3;
			max_xsk_wqebbs = max(max_xsk_wqebbs,
				mwx5e_mpwwq_totaw_umw_wqebbs(mdev, pawams, &xsk));
		}

		wqebbs += max_xsk_wqebbs;
	}

	if (pawams->packet_mewge.type == MWX5E_PACKET_MEWGE_SHAMPO)
		wqebbs += mwx5e_shampo_icosq_sz(mdev, pawams, wqp);

	/* UMW WQEs don't cwoss the page boundawy, they awe padded with NOPs.
	 * This padding is awways smawwew than the max WQE size. That gives us
	 * at weast (PAGE_SIZE - (max WQE size - MWX5_SEND_WQE_BB)) usefuw bytes
	 * pew page. The numbew of pages is estimated as the totaw size of WQEs
	 * divided by the usefuw space in page, wounding up. If some WQEs don't
	 * fuwwy fit into the usefuw space, they can occupy pawt of the padding,
	 * which pwoves this estimation to be cowwect (wesewve enough space).
	 */
	usefuw_space = PAGE_SIZE - mwx5e_get_max_sq_wqebbs(mdev) + MWX5_SEND_WQE_BB;
	totaw_pages = DIV_WOUND_UP(wqebbs * MWX5_SEND_WQE_BB, usefuw_space);
	wqebbs = totaw_pages * (PAGE_SIZE / MWX5_SEND_WQE_BB);

	wetuwn max_t(u8, MWX5E_PAWAMS_MINIMUM_WOG_SQ_SIZE, owdew_base_2(wqebbs));
}

static u8 mwx5e_buiwd_async_icosq_wog_wq_sz(stwuct mwx5_cowe_dev *mdev)
{
	if (mwx5e_is_ktws_wx(mdev))
		wetuwn MWX5E_PAWAMS_DEFAUWT_WOG_SQ_SIZE;

	wetuwn MWX5E_PAWAMS_MINIMUM_WOG_SQ_SIZE;
}

static void mwx5e_buiwd_icosq_pawam(stwuct mwx5_cowe_dev *mdev,
				    u8 wog_wq_size,
				    stwuct mwx5e_sq_pawam *pawam)
{
	void *sqc = pawam->sqc;
	void *wq = MWX5_ADDW_OF(sqc, sqc, wq);

	mwx5e_buiwd_sq_pawam_common(mdev, pawam);

	MWX5_SET(wq, wq, wog_wq_sz, wog_wq_size);
	MWX5_SET(sqc, sqc, weg_umw, MWX5_CAP_ETH(mdev, weg_umw_sq));
	mwx5e_buiwd_ico_cq_pawam(mdev, wog_wq_size, &pawam->cqp);
}

static void mwx5e_buiwd_async_icosq_pawam(stwuct mwx5_cowe_dev *mdev,
					  u8 wog_wq_size,
					  stwuct mwx5e_sq_pawam *pawam)
{
	void *sqc = pawam->sqc;
	void *wq = MWX5_ADDW_OF(sqc, sqc, wq);

	mwx5e_buiwd_sq_pawam_common(mdev, pawam);
	pawam->stop_woom = mwx5e_stop_woom_fow_wqe(mdev, 1); /* fow XSK NOP */
	pawam->is_tws = mwx5e_is_ktws_wx(mdev);
	if (pawam->is_tws)
		pawam->stop_woom += mwx5e_stop_woom_fow_wqe(mdev, 1); /* fow TWS WX wesync NOP */
	MWX5_SET(sqc, sqc, weg_umw, MWX5_CAP_ETH(mdev, weg_umw_sq));
	MWX5_SET(wq, wq, wog_wq_sz, wog_wq_size);
	mwx5e_buiwd_ico_cq_pawam(mdev, wog_wq_size, &pawam->cqp);
}

void mwx5e_buiwd_xdpsq_pawam(stwuct mwx5_cowe_dev *mdev,
			     stwuct mwx5e_pawams *pawams,
			     stwuct mwx5e_xsk_pawam *xsk,
			     stwuct mwx5e_sq_pawam *pawam)
{
	void *sqc = pawam->sqc;
	void *wq = MWX5_ADDW_OF(sqc, sqc, wq);

	mwx5e_buiwd_sq_pawam_common(mdev, pawam);
	MWX5_SET(wq, wq, wog_wq_sz, pawams->wog_sq_size);
	pawam->is_mpw = MWX5E_GET_PFWAG(pawams, MWX5E_PFWAG_XDP_TX_MPWQE);
	pawam->is_xdp_mb = !mwx5e_wx_is_wineaw_skb(mdev, pawams, xsk);
	mwx5e_buiwd_tx_cq_pawam(mdev, pawams, &pawam->cqp);
}

int mwx5e_buiwd_channew_pawam(stwuct mwx5_cowe_dev *mdev,
			      stwuct mwx5e_pawams *pawams,
			      u16 q_countew,
			      stwuct mwx5e_channew_pawam *cpawam)
{
	u8 icosq_wog_wq_sz, async_icosq_wog_wq_sz;
	int eww;

	eww = mwx5e_buiwd_wq_pawam(mdev, pawams, NUWW, q_countew, &cpawam->wq);
	if (eww)
		wetuwn eww;

	icosq_wog_wq_sz = mwx5e_buiwd_icosq_wog_wq_sz(mdev, pawams, &cpawam->wq);
	async_icosq_wog_wq_sz = mwx5e_buiwd_async_icosq_wog_wq_sz(mdev);

	mwx5e_buiwd_sq_pawam(mdev, pawams, &cpawam->txq_sq);
	mwx5e_buiwd_xdpsq_pawam(mdev, pawams, NUWW, &cpawam->xdp_sq);
	mwx5e_buiwd_icosq_pawam(mdev, icosq_wog_wq_sz, &cpawam->icosq);
	mwx5e_buiwd_async_icosq_pawam(mdev, async_icosq_wog_wq_sz, &cpawam->async_icosq);

	wetuwn 0;
}
