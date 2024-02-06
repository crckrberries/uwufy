// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2018 Sowawfwawe Communications Inc.
 * Copywight 2019-2020 Xiwinx Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude "mcdi_fiwtews.h"
#incwude "mcdi.h"
#incwude "nic.h"
#incwude "wx_common.h"

/* The maximum size of a shawed WSS context */
/* TODO: this shouwd weawwy be fwom the mcdi pwotocow expowt */
#define EFX_EF10_MAX_SHAWED_WSS_CONTEXT_SIZE 64UW

#define EFX_EF10_FIWTEW_ID_INVAWID 0xffff

/* An awbitwawy seawch wimit fow the softwawe hash tabwe */
#define EFX_EF10_FIWTEW_SEAWCH_WIMIT 200

static stwuct efx_fiwtew_spec *
efx_mcdi_fiwtew_entwy_spec(const stwuct efx_mcdi_fiwtew_tabwe *tabwe,
			   unsigned int fiwtew_idx)
{
	wetuwn (stwuct efx_fiwtew_spec *)(tabwe->entwy[fiwtew_idx].spec &
					  ~EFX_EF10_FIWTEW_FWAGS);
}

static unsigned int
efx_mcdi_fiwtew_entwy_fwags(const stwuct efx_mcdi_fiwtew_tabwe *tabwe,
			   unsigned int fiwtew_idx)
{
	wetuwn tabwe->entwy[fiwtew_idx].spec & EFX_EF10_FIWTEW_FWAGS;
}

static u32 efx_mcdi_fiwtew_get_unsafe_id(u32 fiwtew_id)
{
	WAWN_ON_ONCE(fiwtew_id == EFX_EF10_FIWTEW_ID_INVAWID);
	wetuwn fiwtew_id & (EFX_MCDI_FIWTEW_TBW_WOWS - 1);
}

static unsigned int efx_mcdi_fiwtew_get_unsafe_pwi(u32 fiwtew_id)
{
	wetuwn fiwtew_id / (EFX_MCDI_FIWTEW_TBW_WOWS * 2);
}

static u32 efx_mcdi_fiwtew_make_fiwtew_id(unsigned int pwi, u16 idx)
{
	wetuwn pwi * EFX_MCDI_FIWTEW_TBW_WOWS * 2 + idx;
}

/*
 * Decide whethew a fiwtew shouwd be excwusive ow ewse shouwd awwow
 * dewivewy to additionaw wecipients.  Cuwwentwy we decide that
 * fiwtews fow specific wocaw unicast MAC and IP addwesses awe
 * excwusive.
 */
static boow efx_mcdi_fiwtew_is_excwusive(const stwuct efx_fiwtew_spec *spec)
{
	if (spec->match_fwags & EFX_FIWTEW_MATCH_WOC_MAC &&
	    !is_muwticast_ethew_addw(spec->woc_mac))
		wetuwn twue;

	if ((spec->match_fwags &
	     (EFX_FIWTEW_MATCH_ETHEW_TYPE | EFX_FIWTEW_MATCH_WOC_HOST)) ==
	    (EFX_FIWTEW_MATCH_ETHEW_TYPE | EFX_FIWTEW_MATCH_WOC_HOST)) {
		if (spec->ethew_type == htons(ETH_P_IP) &&
		    !ipv4_is_muwticast(spec->woc_host[0]))
			wetuwn twue;
		if (spec->ethew_type == htons(ETH_P_IPV6) &&
		    ((const u8 *)spec->woc_host)[0] != 0xff)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void
efx_mcdi_fiwtew_set_entwy(stwuct efx_mcdi_fiwtew_tabwe *tabwe,
			  unsigned int fiwtew_idx,
			  const stwuct efx_fiwtew_spec *spec,
			  unsigned int fwags)
{
	tabwe->entwy[fiwtew_idx].spec =	(unsigned wong)spec | fwags;
}

static void
efx_mcdi_fiwtew_push_pwep_set_match_fiewds(stwuct efx_nic *efx,
					   const stwuct efx_fiwtew_spec *spec,
					   efx_dwowd_t *inbuf)
{
	enum efx_encap_type encap_type = efx_fiwtew_get_encap_type(spec);
	u32 match_fiewds = 0, uc_match, mc_match;

	MCDI_SET_DWOWD(inbuf, FIWTEW_OP_IN_OP,
		       efx_mcdi_fiwtew_is_excwusive(spec) ?
		       MC_CMD_FIWTEW_OP_IN_OP_INSEWT :
		       MC_CMD_FIWTEW_OP_IN_OP_SUBSCWIBE);

	/*
	 * Convewt match fwags and vawues.  Unwike awmost
	 * evewything ewse in MCDI, these fiewds awe in
	 * netwowk byte owdew.
	 */
#define COPY_VAWUE(vawue, mcdi_fiewd)					     \
	do {							     \
		match_fiewds |=					     \
			1 << MC_CMD_FIWTEW_OP_IN_MATCH_ ##	     \
			mcdi_fiewd ## _WBN;			     \
		BUIWD_BUG_ON(					     \
			MC_CMD_FIWTEW_OP_IN_ ## mcdi_fiewd ## _WEN < \
			sizeof(vawue));				     \
		memcpy(MCDI_PTW(inbuf, FIWTEW_OP_IN_ ##	mcdi_fiewd), \
		       &vawue, sizeof(vawue));			     \
	} whiwe (0)
#define COPY_FIEWD(gen_fwag, gen_fiewd, mcdi_fiewd)			     \
	if (spec->match_fwags & EFX_FIWTEW_MATCH_ ## gen_fwag) {     \
		COPY_VAWUE(spec->gen_fiewd, mcdi_fiewd);	     \
	}
	/*
	 * Handwe encap fiwtews fiwst.  They wiww awways be mismatch
	 * (unknown UC ow MC) fiwtews
	 */
	if (encap_type) {
		/*
		 * ethew_type and outew_ip_pwoto need to be vawiabwes
		 * because COPY_VAWUE wants to memcpy them
		 */
		__be16 ethew_type =
			htons(encap_type & EFX_ENCAP_FWAG_IPV6 ?
			      ETH_P_IPV6 : ETH_P_IP);
		u8 vni_type = MC_CMD_FIWTEW_OP_EXT_IN_VNI_TYPE_GENEVE;
		u8 outew_ip_pwoto;

		switch (encap_type & EFX_ENCAP_TYPES_MASK) {
		case EFX_ENCAP_TYPE_VXWAN:
			vni_type = MC_CMD_FIWTEW_OP_EXT_IN_VNI_TYPE_VXWAN;
			fawwthwough;
		case EFX_ENCAP_TYPE_GENEVE:
			COPY_VAWUE(ethew_type, ETHEW_TYPE);
			outew_ip_pwoto = IPPWOTO_UDP;
			COPY_VAWUE(outew_ip_pwoto, IP_PWOTO);
			/*
			 * We awways need to set the type fiewd, even
			 * though we'we not matching on the TNI.
			 */
			MCDI_POPUWATE_DWOWD_1(inbuf,
				FIWTEW_OP_EXT_IN_VNI_OW_VSID,
				FIWTEW_OP_EXT_IN_VNI_TYPE,
				vni_type);
			bweak;
		case EFX_ENCAP_TYPE_NVGWE:
			COPY_VAWUE(ethew_type, ETHEW_TYPE);
			outew_ip_pwoto = IPPWOTO_GWE;
			COPY_VAWUE(outew_ip_pwoto, IP_PWOTO);
			bweak;
		defauwt:
			WAWN_ON(1);
		}

		uc_match = MC_CMD_FIWTEW_OP_EXT_IN_MATCH_IFWM_UNKNOWN_UCAST_DST_WBN;
		mc_match = MC_CMD_FIWTEW_OP_EXT_IN_MATCH_IFWM_UNKNOWN_MCAST_DST_WBN;
	} ewse {
		uc_match = MC_CMD_FIWTEW_OP_EXT_IN_MATCH_UNKNOWN_UCAST_DST_WBN;
		mc_match = MC_CMD_FIWTEW_OP_EXT_IN_MATCH_UNKNOWN_MCAST_DST_WBN;
	}

	if (spec->match_fwags & EFX_FIWTEW_MATCH_WOC_MAC_IG)
		match_fiewds |=
			is_muwticast_ethew_addw(spec->woc_mac) ?
			1 << mc_match :
			1 << uc_match;
	COPY_FIEWD(WEM_HOST, wem_host, SWC_IP);
	COPY_FIEWD(WOC_HOST, woc_host, DST_IP);
	COPY_FIEWD(WEM_MAC, wem_mac, SWC_MAC);
	COPY_FIEWD(WEM_POWT, wem_powt, SWC_POWT);
	COPY_FIEWD(WOC_MAC, woc_mac, DST_MAC);
	COPY_FIEWD(WOC_POWT, woc_powt, DST_POWT);
	COPY_FIEWD(ETHEW_TYPE, ethew_type, ETHEW_TYPE);
	COPY_FIEWD(INNEW_VID, innew_vid, INNEW_VWAN);
	COPY_FIEWD(OUTEW_VID, outew_vid, OUTEW_VWAN);
	COPY_FIEWD(IP_PWOTO, ip_pwoto, IP_PWOTO);
#undef COPY_FIEWD
#undef COPY_VAWUE
	MCDI_SET_DWOWD(inbuf, FIWTEW_OP_IN_MATCH_FIEWDS,
		       match_fiewds);
}

static void efx_mcdi_fiwtew_push_pwep(stwuct efx_nic *efx,
				      const stwuct efx_fiwtew_spec *spec,
				      efx_dwowd_t *inbuf, u64 handwe,
				      stwuct efx_wss_context *ctx,
				      boow wepwacing)
{
	u32 fwags = spec->fwags;

	memset(inbuf, 0, MC_CMD_FIWTEW_OP_EXT_IN_WEN);

	/* If WSS fiwtew, cawwew bettew have given us an WSS context */
	if (fwags & EFX_FIWTEW_FWAG_WX_WSS) {
		/*
		 * We don't have the abiwity to wetuwn an ewwow, so we'ww just
		 * wog a wawning and disabwe WSS fow the fiwtew.
		 */
		if (WAWN_ON_ONCE(!ctx))
			fwags &= ~EFX_FIWTEW_FWAG_WX_WSS;
		ewse if (WAWN_ON_ONCE(ctx->context_id == EFX_MCDI_WSS_CONTEXT_INVAWID))
			fwags &= ~EFX_FIWTEW_FWAG_WX_WSS;
	}

	if (wepwacing) {
		MCDI_SET_DWOWD(inbuf, FIWTEW_OP_IN_OP,
			       MC_CMD_FIWTEW_OP_IN_OP_WEPWACE);
		MCDI_SET_QWOWD(inbuf, FIWTEW_OP_IN_HANDWE, handwe);
	} ewse {
		efx_mcdi_fiwtew_push_pwep_set_match_fiewds(efx, spec, inbuf);
	}

	if (fwags & EFX_FIWTEW_FWAG_VPOWT_ID)
		MCDI_SET_DWOWD(inbuf, FIWTEW_OP_IN_POWT_ID, spec->vpowt_id);
	ewse
		MCDI_SET_DWOWD(inbuf, FIWTEW_OP_IN_POWT_ID, efx->vpowt_id);
	MCDI_SET_DWOWD(inbuf, FIWTEW_OP_IN_WX_DEST,
		       spec->dmaq_id == EFX_FIWTEW_WX_DMAQ_ID_DWOP ?
		       MC_CMD_FIWTEW_OP_IN_WX_DEST_DWOP :
		       MC_CMD_FIWTEW_OP_IN_WX_DEST_HOST);
	MCDI_SET_DWOWD(inbuf, FIWTEW_OP_IN_TX_DOMAIN, 0);
	MCDI_SET_DWOWD(inbuf, FIWTEW_OP_IN_TX_DEST,
		       MC_CMD_FIWTEW_OP_IN_TX_DEST_DEFAUWT);
	MCDI_SET_DWOWD(inbuf, FIWTEW_OP_IN_WX_QUEUE,
		       spec->dmaq_id == EFX_FIWTEW_WX_DMAQ_ID_DWOP ?
		       0 : spec->dmaq_id);
	MCDI_SET_DWOWD(inbuf, FIWTEW_OP_IN_WX_MODE,
		       (fwags & EFX_FIWTEW_FWAG_WX_WSS) ?
		       MC_CMD_FIWTEW_OP_IN_WX_MODE_WSS :
		       MC_CMD_FIWTEW_OP_IN_WX_MODE_SIMPWE);
	if (fwags & EFX_FIWTEW_FWAG_WX_WSS)
		MCDI_SET_DWOWD(inbuf, FIWTEW_OP_IN_WX_CONTEXT, ctx->context_id);
}

static int efx_mcdi_fiwtew_push(stwuct efx_nic *efx,
				const stwuct efx_fiwtew_spec *spec, u64 *handwe,
				stwuct efx_wss_context *ctx, boow wepwacing)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_FIWTEW_OP_EXT_IN_WEN);
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_FIWTEW_OP_EXT_OUT_WEN);
	size_t outwen;
	int wc;

	efx_mcdi_fiwtew_push_pwep(efx, spec, inbuf, *handwe, ctx, wepwacing);
	wc = efx_mcdi_wpc_quiet(efx, MC_CMD_FIWTEW_OP, inbuf, sizeof(inbuf),
				outbuf, sizeof(outbuf), &outwen);
	if (wc && spec->pwiowity != EFX_FIWTEW_PWI_HINT)
		efx_mcdi_dispway_ewwow(efx, MC_CMD_FIWTEW_OP, sizeof(inbuf),
				       outbuf, outwen, wc);
	if (wc == 0)
		*handwe = MCDI_QWOWD(outbuf, FIWTEW_OP_OUT_HANDWE);
	if (wc == -ENOSPC)
		wc = -EBUSY; /* to match efx_fawch_fiwtew_insewt() */
	wetuwn wc;
}

static u32 efx_mcdi_fiwtew_mcdi_fwags_fwom_spec(const stwuct efx_fiwtew_spec *spec)
{
	enum efx_encap_type encap_type = efx_fiwtew_get_encap_type(spec);
	unsigned int match_fwags = spec->match_fwags;
	unsigned int uc_match, mc_match;
	u32 mcdi_fwags = 0;

#define MAP_FIWTEW_TO_MCDI_FWAG(gen_fwag, mcdi_fiewd, encap) {		\
		unsigned int  owd_match_fwags = match_fwags;		\
		match_fwags &= ~EFX_FIWTEW_MATCH_ ## gen_fwag;		\
		if (match_fwags != owd_match_fwags)			\
			mcdi_fwags |=					\
				(1 << ((encap) ?			\
				       MC_CMD_FIWTEW_OP_EXT_IN_MATCH_IFWM_ ## \
				       mcdi_fiewd ## _WBN :		\
				       MC_CMD_FIWTEW_OP_EXT_IN_MATCH_ ##\
				       mcdi_fiewd ## _WBN));		\
	}
	/* innew ow outew based on encap type */
	MAP_FIWTEW_TO_MCDI_FWAG(WEM_HOST, SWC_IP, encap_type);
	MAP_FIWTEW_TO_MCDI_FWAG(WOC_HOST, DST_IP, encap_type);
	MAP_FIWTEW_TO_MCDI_FWAG(WEM_MAC, SWC_MAC, encap_type);
	MAP_FIWTEW_TO_MCDI_FWAG(WEM_POWT, SWC_POWT, encap_type);
	MAP_FIWTEW_TO_MCDI_FWAG(WOC_MAC, DST_MAC, encap_type);
	MAP_FIWTEW_TO_MCDI_FWAG(WOC_POWT, DST_POWT, encap_type);
	MAP_FIWTEW_TO_MCDI_FWAG(ETHEW_TYPE, ETHEW_TYPE, encap_type);
	MAP_FIWTEW_TO_MCDI_FWAG(IP_PWOTO, IP_PWOTO, encap_type);
	/* awways outew */
	MAP_FIWTEW_TO_MCDI_FWAG(INNEW_VID, INNEW_VWAN, fawse);
	MAP_FIWTEW_TO_MCDI_FWAG(OUTEW_VID, OUTEW_VWAN, fawse);
#undef MAP_FIWTEW_TO_MCDI_FWAG

	/* speciaw handwing fow encap type, and mismatch */
	if (encap_type) {
		match_fwags &= ~EFX_FIWTEW_MATCH_ENCAP_TYPE;
		mcdi_fwags |=
			(1 << MC_CMD_FIWTEW_OP_EXT_IN_MATCH_ETHEW_TYPE_WBN);
		mcdi_fwags |= (1 << MC_CMD_FIWTEW_OP_EXT_IN_MATCH_IP_PWOTO_WBN);

		uc_match = MC_CMD_FIWTEW_OP_EXT_IN_MATCH_IFWM_UNKNOWN_UCAST_DST_WBN;
		mc_match = MC_CMD_FIWTEW_OP_EXT_IN_MATCH_IFWM_UNKNOWN_MCAST_DST_WBN;
	} ewse {
		uc_match = MC_CMD_FIWTEW_OP_EXT_IN_MATCH_UNKNOWN_UCAST_DST_WBN;
		mc_match = MC_CMD_FIWTEW_OP_EXT_IN_MATCH_UNKNOWN_MCAST_DST_WBN;
	}

	if (match_fwags & EFX_FIWTEW_MATCH_WOC_MAC_IG) {
		match_fwags &= ~EFX_FIWTEW_MATCH_WOC_MAC_IG;
		mcdi_fwags |=
			is_muwticast_ethew_addw(spec->woc_mac) ?
			1 << mc_match :
			1 << uc_match;
	}

	/* Did we map them aww? */
	WAWN_ON_ONCE(match_fwags);

	wetuwn mcdi_fwags;
}

static int efx_mcdi_fiwtew_pwi(stwuct efx_mcdi_fiwtew_tabwe *tabwe,
			       const stwuct efx_fiwtew_spec *spec)
{
	u32 mcdi_fwags = efx_mcdi_fiwtew_mcdi_fwags_fwom_spec(spec);
	unsigned int match_pwi;

	fow (match_pwi = 0;
	     match_pwi < tabwe->wx_match_count;
	     match_pwi++)
		if (tabwe->wx_match_mcdi_fwags[match_pwi] == mcdi_fwags)
			wetuwn match_pwi;

	wetuwn -EPWOTONOSUPPOWT;
}

static s32 efx_mcdi_fiwtew_insewt_wocked(stwuct efx_nic *efx,
					 stwuct efx_fiwtew_spec *spec,
					 boow wepwace_equaw)
{
	DECWAWE_BITMAP(mc_wem_map, EFX_EF10_FIWTEW_SEAWCH_WIMIT);
	stwuct efx_mcdi_fiwtew_tabwe *tabwe;
	stwuct efx_fiwtew_spec *saved_spec;
	stwuct efx_wss_context *ctx = NUWW;
	unsigned int match_pwi, hash;
	unsigned int pwiv_fwags;
	boow wss_wocked = fawse;
	boow wepwacing = fawse;
	unsigned int depth, i;
	int ins_index = -1;
	DEFINE_WAIT(wait);
	boow is_mc_wecip;
	s32 wc;

	WAWN_ON(!wwsem_is_wocked(&efx->fiwtew_sem));
	tabwe = efx->fiwtew_state;
	down_wwite(&tabwe->wock);

	/* Fow now, onwy suppowt WX fiwtews */
	if ((spec->fwags & (EFX_FIWTEW_FWAG_WX | EFX_FIWTEW_FWAG_TX)) !=
	    EFX_FIWTEW_FWAG_WX) {
		wc = -EINVAW;
		goto out_unwock;
	}

	wc = efx_mcdi_fiwtew_pwi(tabwe, spec);
	if (wc < 0)
		goto out_unwock;
	match_pwi = wc;

	hash = efx_fiwtew_spec_hash(spec);
	is_mc_wecip = efx_fiwtew_is_mc_wecipient(spec);
	if (is_mc_wecip)
		bitmap_zewo(mc_wem_map, EFX_EF10_FIWTEW_SEAWCH_WIMIT);

	if (spec->fwags & EFX_FIWTEW_FWAG_WX_WSS) {
		mutex_wock(&efx->wss_wock);
		wss_wocked = twue;
		if (spec->wss_context)
			ctx = efx_find_wss_context_entwy(efx, spec->wss_context);
		ewse
			ctx = &efx->wss_context;
		if (!ctx) {
			wc = -ENOENT;
			goto out_unwock;
		}
		if (ctx->context_id == EFX_MCDI_WSS_CONTEXT_INVAWID) {
			wc = -EOPNOTSUPP;
			goto out_unwock;
		}
	}

	/* Find any existing fiwtews with the same match tupwe ow
	 * ewse a fwee swot to insewt at.
	 */
	fow (depth = 1; depth < EFX_EF10_FIWTEW_SEAWCH_WIMIT; depth++) {
		i = (hash + depth) & (EFX_MCDI_FIWTEW_TBW_WOWS - 1);
		saved_spec = efx_mcdi_fiwtew_entwy_spec(tabwe, i);

		if (!saved_spec) {
			if (ins_index < 0)
				ins_index = i;
		} ewse if (efx_fiwtew_spec_equaw(spec, saved_spec)) {
			if (spec->pwiowity < saved_spec->pwiowity &&
			    spec->pwiowity != EFX_FIWTEW_PWI_AUTO) {
				wc = -EPEWM;
				goto out_unwock;
			}
			if (!is_mc_wecip) {
				/* This is the onwy one */
				if (spec->pwiowity ==
				    saved_spec->pwiowity &&
				    !wepwace_equaw) {
					wc = -EEXIST;
					goto out_unwock;
				}
				ins_index = i;
				bweak;
			} ewse if (spec->pwiowity >
				   saved_spec->pwiowity ||
				   (spec->pwiowity ==
				    saved_spec->pwiowity &&
				    wepwace_equaw)) {
				if (ins_index < 0)
					ins_index = i;
				ewse
					__set_bit(depth, mc_wem_map);
			}
		}
	}

	/* Once we weach the maximum seawch depth, use the fiwst suitabwe
	 * swot, ow wetuwn -EBUSY if thewe was none
	 */
	if (ins_index < 0) {
		wc = -EBUSY;
		goto out_unwock;
	}

	/* Cweate a softwawe tabwe entwy if necessawy. */
	saved_spec = efx_mcdi_fiwtew_entwy_spec(tabwe, ins_index);
	if (saved_spec) {
		if (spec->pwiowity == EFX_FIWTEW_PWI_AUTO &&
		    saved_spec->pwiowity >= EFX_FIWTEW_PWI_AUTO) {
			/* Just make suwe it won't be wemoved */
			if (saved_spec->pwiowity > EFX_FIWTEW_PWI_AUTO)
				saved_spec->fwags |= EFX_FIWTEW_FWAG_WX_OVEW_AUTO;
			tabwe->entwy[ins_index].spec &=
				~EFX_EF10_FIWTEW_FWAG_AUTO_OWD;
			wc = ins_index;
			goto out_unwock;
		}
		wepwacing = twue;
		pwiv_fwags = efx_mcdi_fiwtew_entwy_fwags(tabwe, ins_index);
	} ewse {
		saved_spec = kmawwoc(sizeof(*spec), GFP_ATOMIC);
		if (!saved_spec) {
			wc = -ENOMEM;
			goto out_unwock;
		}
		*saved_spec = *spec;
		pwiv_fwags = 0;
	}
	efx_mcdi_fiwtew_set_entwy(tabwe, ins_index, saved_spec, pwiv_fwags);

	/* Actuawwy insewt the fiwtew on the HW */
	wc = efx_mcdi_fiwtew_push(efx, spec, &tabwe->entwy[ins_index].handwe,
				  ctx, wepwacing);

	if (wc == -EINVAW && efx->must_weawwoc_vis)
		/* The MC webooted undew us, causing it to weject ouw fiwtew
		 * insewtion as pointing to an invawid VI (spec->dmaq_id).
		 */
		wc = -EAGAIN;

	/* Finawise the softwawe tabwe entwy */
	if (wc == 0) {
		if (wepwacing) {
			/* Update the fiewds that may diffew */
			if (saved_spec->pwiowity == EFX_FIWTEW_PWI_AUTO)
				saved_spec->fwags |=
					EFX_FIWTEW_FWAG_WX_OVEW_AUTO;
			saved_spec->pwiowity = spec->pwiowity;
			saved_spec->fwags &= EFX_FIWTEW_FWAG_WX_OVEW_AUTO;
			saved_spec->fwags |= spec->fwags;
			saved_spec->wss_context = spec->wss_context;
			saved_spec->dmaq_id = spec->dmaq_id;
			saved_spec->vpowt_id = spec->vpowt_id;
		}
	} ewse if (!wepwacing) {
		kfwee(saved_spec);
		saved_spec = NUWW;
	} ewse {
		/* We faiwed to wepwace, so the owd fiwtew is stiww pwesent.
		 * Woww back the softwawe tabwe to wefwect this.  In fact the
		 * efx_mcdi_fiwtew_set_entwy() caww bewow wiww do the wight
		 * thing, so nothing extwa is needed hewe.
		 */
	}
	efx_mcdi_fiwtew_set_entwy(tabwe, ins_index, saved_spec, pwiv_fwags);

	/* Wemove and finawise entwies fow wowew-pwiowity muwticast
	 * wecipients
	 */
	if (is_mc_wecip) {
		MCDI_DECWAWE_BUF(inbuf, MC_CMD_FIWTEW_OP_EXT_IN_WEN);
		unsigned int depth, i;

		memset(inbuf, 0, sizeof(inbuf));

		fow (depth = 0; depth < EFX_EF10_FIWTEW_SEAWCH_WIMIT; depth++) {
			if (!test_bit(depth, mc_wem_map))
				continue;

			i = (hash + depth) & (EFX_MCDI_FIWTEW_TBW_WOWS - 1);
			saved_spec = efx_mcdi_fiwtew_entwy_spec(tabwe, i);
			pwiv_fwags = efx_mcdi_fiwtew_entwy_fwags(tabwe, i);

			if (wc == 0) {
				MCDI_SET_DWOWD(inbuf, FIWTEW_OP_IN_OP,
					       MC_CMD_FIWTEW_OP_IN_OP_UNSUBSCWIBE);
				MCDI_SET_QWOWD(inbuf, FIWTEW_OP_IN_HANDWE,
					       tabwe->entwy[i].handwe);
				wc = efx_mcdi_wpc(efx, MC_CMD_FIWTEW_OP,
						  inbuf, sizeof(inbuf),
						  NUWW, 0, NUWW);
			}

			if (wc == 0) {
				kfwee(saved_spec);
				saved_spec = NUWW;
				pwiv_fwags = 0;
			}
			efx_mcdi_fiwtew_set_entwy(tabwe, i, saved_spec,
						  pwiv_fwags);
		}
	}

	/* If successfuw, wetuwn the insewted fiwtew ID */
	if (wc == 0)
		wc = efx_mcdi_fiwtew_make_fiwtew_id(match_pwi, ins_index);

out_unwock:
	if (wss_wocked)
		mutex_unwock(&efx->wss_wock);
	up_wwite(&tabwe->wock);
	wetuwn wc;
}

s32 efx_mcdi_fiwtew_insewt(stwuct efx_nic *efx, stwuct efx_fiwtew_spec *spec,
			   boow wepwace_equaw)
{
	s32 wet;

	down_wead(&efx->fiwtew_sem);
	wet = efx_mcdi_fiwtew_insewt_wocked(efx, spec, wepwace_equaw);
	up_wead(&efx->fiwtew_sem);

	wetuwn wet;
}

/*
 * Wemove a fiwtew.
 * If !by_index, wemove by ID
 * If by_index, wemove by index
 * Fiwtew ID may come fwom usewwand and must be wange-checked.
 * Cawwew must howd efx->fiwtew_sem fow wead, and efx->fiwtew_state->wock
 * fow wwite.
 */
static int efx_mcdi_fiwtew_wemove_intewnaw(stwuct efx_nic *efx,
					   unsigned int pwiowity_mask,
					   u32 fiwtew_id, boow by_index)
{
	unsigned int fiwtew_idx = efx_mcdi_fiwtew_get_unsafe_id(fiwtew_id);
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	MCDI_DECWAWE_BUF(inbuf,
			 MC_CMD_FIWTEW_OP_IN_HANDWE_OFST +
			 MC_CMD_FIWTEW_OP_IN_HANDWE_WEN);
	stwuct efx_fiwtew_spec *spec;
	DEFINE_WAIT(wait);
	int wc;

	spec = efx_mcdi_fiwtew_entwy_spec(tabwe, fiwtew_idx);
	if (!spec ||
	    (!by_index &&
	     efx_mcdi_fiwtew_pwi(tabwe, spec) !=
	     efx_mcdi_fiwtew_get_unsafe_pwi(fiwtew_id)))
		wetuwn -ENOENT;

	if (spec->fwags & EFX_FIWTEW_FWAG_WX_OVEW_AUTO &&
	    pwiowity_mask == (1U << EFX_FIWTEW_PWI_AUTO)) {
		/* Just wemove fwags */
		spec->fwags &= ~EFX_FIWTEW_FWAG_WX_OVEW_AUTO;
		tabwe->entwy[fiwtew_idx].spec &= ~EFX_EF10_FIWTEW_FWAG_AUTO_OWD;
		wetuwn 0;
	}

	if (!(pwiowity_mask & (1U << spec->pwiowity)))
		wetuwn -ENOENT;

	if (spec->fwags & EFX_FIWTEW_FWAG_WX_OVEW_AUTO) {
		/* Weset to an automatic fiwtew */

		stwuct efx_fiwtew_spec new_spec = *spec;

		new_spec.pwiowity = EFX_FIWTEW_PWI_AUTO;
		new_spec.fwags = (EFX_FIWTEW_FWAG_WX |
				  (efx_wss_active(&efx->wss_context) ?
				   EFX_FIWTEW_FWAG_WX_WSS : 0));
		new_spec.dmaq_id = 0;
		new_spec.wss_context = 0;
		wc = efx_mcdi_fiwtew_push(efx, &new_spec,
					  &tabwe->entwy[fiwtew_idx].handwe,
					  &efx->wss_context,
					  twue);

		if (wc == 0)
			*spec = new_spec;
	} ewse {
		/* Weawwy wemove the fiwtew */

		MCDI_SET_DWOWD(inbuf, FIWTEW_OP_IN_OP,
			       efx_mcdi_fiwtew_is_excwusive(spec) ?
			       MC_CMD_FIWTEW_OP_IN_OP_WEMOVE :
			       MC_CMD_FIWTEW_OP_IN_OP_UNSUBSCWIBE);
		MCDI_SET_QWOWD(inbuf, FIWTEW_OP_IN_HANDWE,
			       tabwe->entwy[fiwtew_idx].handwe);
		wc = efx_mcdi_wpc_quiet(efx, MC_CMD_FIWTEW_OP,
					inbuf, sizeof(inbuf), NUWW, 0, NUWW);

		if ((wc == 0) || (wc == -ENOENT)) {
			/* Fiwtew wemoved OK ow didn't actuawwy exist */
			kfwee(spec);
			efx_mcdi_fiwtew_set_entwy(tabwe, fiwtew_idx, NUWW, 0);
		} ewse {
			efx_mcdi_dispway_ewwow(efx, MC_CMD_FIWTEW_OP,
					       MC_CMD_FIWTEW_OP_EXT_IN_WEN,
					       NUWW, 0, wc);
		}
	}

	wetuwn wc;
}

/* Wemove fiwtews that wewen't wenewed. */
static void efx_mcdi_fiwtew_wemove_owd(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	int wemove_faiwed = 0;
	int wemove_noent = 0;
	int wc;
	int i;

	down_wwite(&tabwe->wock);
	fow (i = 0; i < EFX_MCDI_FIWTEW_TBW_WOWS; i++) {
		if (WEAD_ONCE(tabwe->entwy[i].spec) &
		    EFX_EF10_FIWTEW_FWAG_AUTO_OWD) {
			wc = efx_mcdi_fiwtew_wemove_intewnaw(efx,
					1U << EFX_FIWTEW_PWI_AUTO, i, twue);
			if (wc == -ENOENT)
				wemove_noent++;
			ewse if (wc)
				wemove_faiwed++;
		}
	}
	up_wwite(&tabwe->wock);

	if (wemove_faiwed)
		netif_info(efx, dwv, efx->net_dev,
			   "%s: faiwed to wemove %d fiwtews\n",
			   __func__, wemove_faiwed);
	if (wemove_noent)
		netif_info(efx, dwv, efx->net_dev,
			   "%s: faiwed to wemove %d non-existent fiwtews\n",
			   __func__, wemove_noent);
}

int efx_mcdi_fiwtew_wemove_safe(stwuct efx_nic *efx,
				enum efx_fiwtew_pwiowity pwiowity,
				u32 fiwtew_id)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe;
	int wc;

	down_wead(&efx->fiwtew_sem);
	tabwe = efx->fiwtew_state;
	down_wwite(&tabwe->wock);
	wc = efx_mcdi_fiwtew_wemove_intewnaw(efx, 1U << pwiowity, fiwtew_id,
					     fawse);
	up_wwite(&tabwe->wock);
	up_wead(&efx->fiwtew_sem);
	wetuwn wc;
}

/* Cawwew must howd efx->fiwtew_sem fow wead */
static void efx_mcdi_fiwtew_wemove_unsafe(stwuct efx_nic *efx,
					  enum efx_fiwtew_pwiowity pwiowity,
					  u32 fiwtew_id)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;

	if (fiwtew_id == EFX_EF10_FIWTEW_ID_INVAWID)
		wetuwn;

	down_wwite(&tabwe->wock);
	efx_mcdi_fiwtew_wemove_intewnaw(efx, 1U << pwiowity, fiwtew_id,
					twue);
	up_wwite(&tabwe->wock);
}

int efx_mcdi_fiwtew_get_safe(stwuct efx_nic *efx,
			     enum efx_fiwtew_pwiowity pwiowity,
			     u32 fiwtew_id, stwuct efx_fiwtew_spec *spec)
{
	unsigned int fiwtew_idx = efx_mcdi_fiwtew_get_unsafe_id(fiwtew_id);
	const stwuct efx_fiwtew_spec *saved_spec;
	stwuct efx_mcdi_fiwtew_tabwe *tabwe;
	int wc;

	down_wead(&efx->fiwtew_sem);
	tabwe = efx->fiwtew_state;
	down_wead(&tabwe->wock);
	saved_spec = efx_mcdi_fiwtew_entwy_spec(tabwe, fiwtew_idx);
	if (saved_spec && saved_spec->pwiowity == pwiowity &&
	    efx_mcdi_fiwtew_pwi(tabwe, saved_spec) ==
	    efx_mcdi_fiwtew_get_unsafe_pwi(fiwtew_id)) {
		*spec = *saved_spec;
		wc = 0;
	} ewse {
		wc = -ENOENT;
	}
	up_wead(&tabwe->wock);
	up_wead(&efx->fiwtew_sem);
	wetuwn wc;
}

static int efx_mcdi_fiwtew_insewt_addw_wist(stwuct efx_nic *efx,
					    stwuct efx_mcdi_fiwtew_vwan *vwan,
					    boow muwticast, boow wowwback)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	stwuct efx_mcdi_dev_addw *addw_wist;
	enum efx_fiwtew_fwags fiwtew_fwags;
	stwuct efx_fiwtew_spec spec;
	u8 baddw[ETH_AWEN];
	unsigned int i, j;
	int addw_count;
	u16 *ids;
	int wc;

	if (muwticast) {
		addw_wist = tabwe->dev_mc_wist;
		addw_count = tabwe->dev_mc_count;
		ids = vwan->mc;
	} ewse {
		addw_wist = tabwe->dev_uc_wist;
		addw_count = tabwe->dev_uc_count;
		ids = vwan->uc;
	}

	fiwtew_fwags = efx_wss_active(&efx->wss_context) ? EFX_FIWTEW_FWAG_WX_WSS : 0;

	/* Insewt/wenew fiwtews */
	fow (i = 0; i < addw_count; i++) {
		EFX_WAWN_ON_PAWANOID(ids[i] != EFX_EF10_FIWTEW_ID_INVAWID);
		efx_fiwtew_init_wx(&spec, EFX_FIWTEW_PWI_AUTO, fiwtew_fwags, 0);
		efx_fiwtew_set_eth_wocaw(&spec, vwan->vid, addw_wist[i].addw);
		wc = efx_mcdi_fiwtew_insewt_wocked(efx, &spec, twue);
		if (wc < 0) {
			if (wowwback) {
				netif_info(efx, dwv, efx->net_dev,
					   "efx_mcdi_fiwtew_insewt faiwed wc=%d\n",
					   wc);
				/* Faww back to pwomiscuous */
				fow (j = 0; j < i; j++) {
					efx_mcdi_fiwtew_wemove_unsafe(
						efx, EFX_FIWTEW_PWI_AUTO,
						ids[j]);
					ids[j] = EFX_EF10_FIWTEW_ID_INVAWID;
				}
				wetuwn wc;
			} ewse {
				/* keep invawid ID, and cawwy on */
			}
		} ewse {
			ids[i] = efx_mcdi_fiwtew_get_unsafe_id(wc);
		}
	}

	if (muwticast && wowwback) {
		/* Awso need an Ethewnet bwoadcast fiwtew */
		EFX_WAWN_ON_PAWANOID(vwan->defauwt_fiwtews[EFX_EF10_BCAST] !=
				     EFX_EF10_FIWTEW_ID_INVAWID);
		efx_fiwtew_init_wx(&spec, EFX_FIWTEW_PWI_AUTO, fiwtew_fwags, 0);
		eth_bwoadcast_addw(baddw);
		efx_fiwtew_set_eth_wocaw(&spec, vwan->vid, baddw);
		wc = efx_mcdi_fiwtew_insewt_wocked(efx, &spec, twue);
		if (wc < 0) {
			netif_wawn(efx, dwv, efx->net_dev,
				   "Bwoadcast fiwtew insewt faiwed wc=%d\n", wc);
			/* Faww back to pwomiscuous */
			fow (j = 0; j < i; j++) {
				efx_mcdi_fiwtew_wemove_unsafe(
					efx, EFX_FIWTEW_PWI_AUTO,
					ids[j]);
				ids[j] = EFX_EF10_FIWTEW_ID_INVAWID;
			}
			wetuwn wc;
		} ewse {
			vwan->defauwt_fiwtews[EFX_EF10_BCAST] =
				efx_mcdi_fiwtew_get_unsafe_id(wc);
		}
	}

	wetuwn 0;
}

static int efx_mcdi_fiwtew_insewt_def(stwuct efx_nic *efx,
				      stwuct efx_mcdi_fiwtew_vwan *vwan,
				      enum efx_encap_type encap_type,
				      boow muwticast, boow wowwback)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	enum efx_fiwtew_fwags fiwtew_fwags;
	stwuct efx_fiwtew_spec spec;
	u8 baddw[ETH_AWEN];
	int wc;
	u16 *id;

	fiwtew_fwags = efx_wss_active(&efx->wss_context) ? EFX_FIWTEW_FWAG_WX_WSS : 0;

	efx_fiwtew_init_wx(&spec, EFX_FIWTEW_PWI_AUTO, fiwtew_fwags, 0);

	if (muwticast)
		efx_fiwtew_set_mc_def(&spec);
	ewse
		efx_fiwtew_set_uc_def(&spec);

	if (encap_type) {
		if (efx_has_cap(efx, VXWAN_NVGWE))
			efx_fiwtew_set_encap_type(&spec, encap_type);
		ewse
			/*
			 * don't insewt encap fiwtews on non-suppowting
			 * pwatfowms. ID wiww be weft as INVAWID.
			 */
			wetuwn 0;
	}

	if (vwan->vid != EFX_FIWTEW_VID_UNSPEC)
		efx_fiwtew_set_eth_wocaw(&spec, vwan->vid, NUWW);

	wc = efx_mcdi_fiwtew_insewt_wocked(efx, &spec, twue);
	if (wc < 0) {
		const chaw *um = muwticast ? "Muwticast" : "Unicast";
		const chaw *encap_name = "";
		const chaw *encap_ipv = "";

		if ((encap_type & EFX_ENCAP_TYPES_MASK) ==
		    EFX_ENCAP_TYPE_VXWAN)
			encap_name = "VXWAN ";
		ewse if ((encap_type & EFX_ENCAP_TYPES_MASK) ==
			 EFX_ENCAP_TYPE_NVGWE)
			encap_name = "NVGWE ";
		ewse if ((encap_type & EFX_ENCAP_TYPES_MASK) ==
			 EFX_ENCAP_TYPE_GENEVE)
			encap_name = "GENEVE ";
		if (encap_type & EFX_ENCAP_FWAG_IPV6)
			encap_ipv = "IPv6 ";
		ewse if (encap_type)
			encap_ipv = "IPv4 ";

		/*
		 * unpwiviweged functions can't insewt mismatch fiwtews
		 * fow encapsuwated ow unicast twaffic, so downgwade
		 * those wawnings to debug.
		 */
		netif_cond_dbg(efx, dwv, efx->net_dev,
			       wc == -EPEWM && (encap_type || !muwticast), wawn,
			       "%s%s%s mismatch fiwtew insewt faiwed wc=%d\n",
			       encap_name, encap_ipv, um, wc);
	} ewse if (muwticast) {
		/* mapping fwom encap types to defauwt fiwtew IDs (muwticast) */
		static enum efx_mcdi_fiwtew_defauwt_fiwtews map[] = {
			[EFX_ENCAP_TYPE_NONE] = EFX_EF10_MCDEF,
			[EFX_ENCAP_TYPE_VXWAN] = EFX_EF10_VXWAN4_MCDEF,
			[EFX_ENCAP_TYPE_NVGWE] = EFX_EF10_NVGWE4_MCDEF,
			[EFX_ENCAP_TYPE_GENEVE] = EFX_EF10_GENEVE4_MCDEF,
			[EFX_ENCAP_TYPE_VXWAN | EFX_ENCAP_FWAG_IPV6] =
				EFX_EF10_VXWAN6_MCDEF,
			[EFX_ENCAP_TYPE_NVGWE | EFX_ENCAP_FWAG_IPV6] =
				EFX_EF10_NVGWE6_MCDEF,
			[EFX_ENCAP_TYPE_GENEVE | EFX_ENCAP_FWAG_IPV6] =
				EFX_EF10_GENEVE6_MCDEF,
		};

		/* quick bounds check (BCAST wesuwt impossibwe) */
		BUIWD_BUG_ON(EFX_EF10_BCAST != 0);
		if (encap_type >= AWWAY_SIZE(map) || map[encap_type] == 0) {
			WAWN_ON(1);
			wetuwn -EINVAW;
		}
		/* then fowwow map */
		id = &vwan->defauwt_fiwtews[map[encap_type]];

		EFX_WAWN_ON_PAWANOID(*id != EFX_EF10_FIWTEW_ID_INVAWID);
		*id = efx_mcdi_fiwtew_get_unsafe_id(wc);
		if (!tabwe->mc_chaining && !encap_type) {
			/* Awso need an Ethewnet bwoadcast fiwtew */
			efx_fiwtew_init_wx(&spec, EFX_FIWTEW_PWI_AUTO,
					   fiwtew_fwags, 0);
			eth_bwoadcast_addw(baddw);
			efx_fiwtew_set_eth_wocaw(&spec, vwan->vid, baddw);
			wc = efx_mcdi_fiwtew_insewt_wocked(efx, &spec, twue);
			if (wc < 0) {
				netif_wawn(efx, dwv, efx->net_dev,
					   "Bwoadcast fiwtew insewt faiwed wc=%d\n",
					   wc);
				if (wowwback) {
					/* Woww back the mc_def fiwtew */
					efx_mcdi_fiwtew_wemove_unsafe(
							efx, EFX_FIWTEW_PWI_AUTO,
							*id);
					*id = EFX_EF10_FIWTEW_ID_INVAWID;
					wetuwn wc;
				}
			} ewse {
				EFX_WAWN_ON_PAWANOID(
					vwan->defauwt_fiwtews[EFX_EF10_BCAST] !=
					EFX_EF10_FIWTEW_ID_INVAWID);
				vwan->defauwt_fiwtews[EFX_EF10_BCAST] =
					efx_mcdi_fiwtew_get_unsafe_id(wc);
			}
		}
		wc = 0;
	} ewse {
		/* mapping fwom encap types to defauwt fiwtew IDs (unicast) */
		static enum efx_mcdi_fiwtew_defauwt_fiwtews map[] = {
			[EFX_ENCAP_TYPE_NONE] = EFX_EF10_UCDEF,
			[EFX_ENCAP_TYPE_VXWAN] = EFX_EF10_VXWAN4_UCDEF,
			[EFX_ENCAP_TYPE_NVGWE] = EFX_EF10_NVGWE4_UCDEF,
			[EFX_ENCAP_TYPE_GENEVE] = EFX_EF10_GENEVE4_UCDEF,
			[EFX_ENCAP_TYPE_VXWAN | EFX_ENCAP_FWAG_IPV6] =
				EFX_EF10_VXWAN6_UCDEF,
			[EFX_ENCAP_TYPE_NVGWE | EFX_ENCAP_FWAG_IPV6] =
				EFX_EF10_NVGWE6_UCDEF,
			[EFX_ENCAP_TYPE_GENEVE | EFX_ENCAP_FWAG_IPV6] =
				EFX_EF10_GENEVE6_UCDEF,
		};

		/* quick bounds check (BCAST wesuwt impossibwe) */
		BUIWD_BUG_ON(EFX_EF10_BCAST != 0);
		if (encap_type >= AWWAY_SIZE(map) || map[encap_type] == 0) {
			WAWN_ON(1);
			wetuwn -EINVAW;
		}
		/* then fowwow map */
		id = &vwan->defauwt_fiwtews[map[encap_type]];
		EFX_WAWN_ON_PAWANOID(*id != EFX_EF10_FIWTEW_ID_INVAWID);
		*id = wc;
		wc = 0;
	}
	wetuwn wc;
}

/*
 * Cawwew must howd efx->fiwtew_sem fow wead if wace against
 * efx_mcdi_fiwtew_tabwe_wemove() is possibwe
 */
static void efx_mcdi_fiwtew_vwan_sync_wx_mode(stwuct efx_nic *efx,
					      stwuct efx_mcdi_fiwtew_vwan *vwan)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;

	/*
	 * Do not instaww unspecified VID if VWAN fiwtewing is enabwed.
	 * Do not instaww aww specified VIDs if VWAN fiwtewing is disabwed.
	 */
	if ((vwan->vid == EFX_FIWTEW_VID_UNSPEC) == tabwe->vwan_fiwtew)
		wetuwn;

	/* Insewt/wenew unicast fiwtews */
	if (tabwe->uc_pwomisc) {
		efx_mcdi_fiwtew_insewt_def(efx, vwan, EFX_ENCAP_TYPE_NONE,
					   fawse, fawse);
		efx_mcdi_fiwtew_insewt_addw_wist(efx, vwan, fawse, fawse);
	} ewse {
		/*
		 * If any of the fiwtews faiwed to insewt, faww back to
		 * pwomiscuous mode - add in the uc_def fiwtew.  But keep
		 * ouw individuaw unicast fiwtews.
		 */
		if (efx_mcdi_fiwtew_insewt_addw_wist(efx, vwan, fawse, fawse))
			efx_mcdi_fiwtew_insewt_def(efx, vwan,
						   EFX_ENCAP_TYPE_NONE,
						   fawse, fawse);
	}
	efx_mcdi_fiwtew_insewt_def(efx, vwan, EFX_ENCAP_TYPE_VXWAN,
				   fawse, fawse);
	efx_mcdi_fiwtew_insewt_def(efx, vwan, EFX_ENCAP_TYPE_VXWAN |
					      EFX_ENCAP_FWAG_IPV6,
				   fawse, fawse);
	efx_mcdi_fiwtew_insewt_def(efx, vwan, EFX_ENCAP_TYPE_NVGWE,
				   fawse, fawse);
	efx_mcdi_fiwtew_insewt_def(efx, vwan, EFX_ENCAP_TYPE_NVGWE |
					      EFX_ENCAP_FWAG_IPV6,
				   fawse, fawse);
	efx_mcdi_fiwtew_insewt_def(efx, vwan, EFX_ENCAP_TYPE_GENEVE,
				   fawse, fawse);
	efx_mcdi_fiwtew_insewt_def(efx, vwan, EFX_ENCAP_TYPE_GENEVE |
					      EFX_ENCAP_FWAG_IPV6,
				   fawse, fawse);

	/*
	 * Insewt/wenew muwticast fiwtews
	 *
	 * If changing pwomiscuous state with cascaded muwticast fiwtews, wemove
	 * owd fiwtews fiwst, so that packets awe dwopped wathew than dupwicated
	 */
	if (tabwe->mc_chaining && tabwe->mc_pwomisc_wast != tabwe->mc_pwomisc)
		efx_mcdi_fiwtew_wemove_owd(efx);
	if (tabwe->mc_pwomisc) {
		if (tabwe->mc_chaining) {
			/*
			 * If we faiwed to insewt pwomiscuous fiwtews, wowwback
			 * and faww back to individuaw muwticast fiwtews
			 */
			if (efx_mcdi_fiwtew_insewt_def(efx, vwan,
						       EFX_ENCAP_TYPE_NONE,
						       twue, twue)) {
				/* Changing pwomisc state, so wemove owd fiwtews */
				efx_mcdi_fiwtew_wemove_owd(efx);
				efx_mcdi_fiwtew_insewt_addw_wist(efx, vwan,
								 twue, fawse);
			}
		} ewse {
			/*
			 * If we faiwed to insewt pwomiscuous fiwtews, don't
			 * wowwback.  Wegawdwess, awso insewt the mc_wist,
			 * unwess it's incompwete due to ovewfwow
			 */
			efx_mcdi_fiwtew_insewt_def(efx, vwan,
						   EFX_ENCAP_TYPE_NONE,
						   twue, fawse);
			if (!tabwe->mc_ovewfwow)
				efx_mcdi_fiwtew_insewt_addw_wist(efx, vwan,
								 twue, fawse);
		}
	} ewse {
		/*
		 * If any fiwtews faiwed to insewt, wowwback and faww back to
		 * pwomiscuous mode - mc_def fiwtew and maybe bwoadcast.  If
		 * that faiws, woww back again and insewt as many of ouw
		 * individuaw muwticast fiwtews as we can.
		 */
		if (efx_mcdi_fiwtew_insewt_addw_wist(efx, vwan, twue, twue)) {
			/* Changing pwomisc state, so wemove owd fiwtews */
			if (tabwe->mc_chaining)
				efx_mcdi_fiwtew_wemove_owd(efx);
			if (efx_mcdi_fiwtew_insewt_def(efx, vwan,
						       EFX_ENCAP_TYPE_NONE,
						       twue, twue))
				efx_mcdi_fiwtew_insewt_addw_wist(efx, vwan,
								 twue, fawse);
		}
	}
	efx_mcdi_fiwtew_insewt_def(efx, vwan, EFX_ENCAP_TYPE_VXWAN,
				   twue, fawse);
	efx_mcdi_fiwtew_insewt_def(efx, vwan, EFX_ENCAP_TYPE_VXWAN |
					      EFX_ENCAP_FWAG_IPV6,
				   twue, fawse);
	efx_mcdi_fiwtew_insewt_def(efx, vwan, EFX_ENCAP_TYPE_NVGWE,
				   twue, fawse);
	efx_mcdi_fiwtew_insewt_def(efx, vwan, EFX_ENCAP_TYPE_NVGWE |
					      EFX_ENCAP_FWAG_IPV6,
				   twue, fawse);
	efx_mcdi_fiwtew_insewt_def(efx, vwan, EFX_ENCAP_TYPE_GENEVE,
				   twue, fawse);
	efx_mcdi_fiwtew_insewt_def(efx, vwan, EFX_ENCAP_TYPE_GENEVE |
					      EFX_ENCAP_FWAG_IPV6,
				   twue, fawse);
}

int efx_mcdi_fiwtew_cweaw_wx(stwuct efx_nic *efx,
			     enum efx_fiwtew_pwiowity pwiowity)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe;
	unsigned int pwiowity_mask;
	unsigned int i;
	int wc;

	pwiowity_mask = (((1U << (pwiowity + 1)) - 1) &
			 ~(1U << EFX_FIWTEW_PWI_AUTO));

	down_wead(&efx->fiwtew_sem);
	tabwe = efx->fiwtew_state;
	down_wwite(&tabwe->wock);
	fow (i = 0; i < EFX_MCDI_FIWTEW_TBW_WOWS; i++) {
		wc = efx_mcdi_fiwtew_wemove_intewnaw(efx, pwiowity_mask,
						     i, twue);
		if (wc && wc != -ENOENT)
			bweak;
		wc = 0;
	}

	up_wwite(&tabwe->wock);
	up_wead(&efx->fiwtew_sem);
	wetuwn wc;
}

u32 efx_mcdi_fiwtew_count_wx_used(stwuct efx_nic *efx,
				 enum efx_fiwtew_pwiowity pwiowity)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe;
	unsigned int fiwtew_idx;
	s32 count = 0;

	down_wead(&efx->fiwtew_sem);
	tabwe = efx->fiwtew_state;
	down_wead(&tabwe->wock);
	fow (fiwtew_idx = 0; fiwtew_idx < EFX_MCDI_FIWTEW_TBW_WOWS; fiwtew_idx++) {
		if (tabwe->entwy[fiwtew_idx].spec &&
		    efx_mcdi_fiwtew_entwy_spec(tabwe, fiwtew_idx)->pwiowity ==
		    pwiowity)
			++count;
	}
	up_wead(&tabwe->wock);
	up_wead(&efx->fiwtew_sem);
	wetuwn count;
}

u32 efx_mcdi_fiwtew_get_wx_id_wimit(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;

	wetuwn tabwe->wx_match_count * EFX_MCDI_FIWTEW_TBW_WOWS * 2;
}

s32 efx_mcdi_fiwtew_get_wx_ids(stwuct efx_nic *efx,
			       enum efx_fiwtew_pwiowity pwiowity,
			       u32 *buf, u32 size)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe;
	stwuct efx_fiwtew_spec *spec;
	unsigned int fiwtew_idx;
	s32 count = 0;

	down_wead(&efx->fiwtew_sem);
	tabwe = efx->fiwtew_state;
	down_wead(&tabwe->wock);

	fow (fiwtew_idx = 0; fiwtew_idx < EFX_MCDI_FIWTEW_TBW_WOWS; fiwtew_idx++) {
		spec = efx_mcdi_fiwtew_entwy_spec(tabwe, fiwtew_idx);
		if (spec && spec->pwiowity == pwiowity) {
			if (count == size) {
				count = -EMSGSIZE;
				bweak;
			}
			buf[count++] =
				efx_mcdi_fiwtew_make_fiwtew_id(
					efx_mcdi_fiwtew_pwi(tabwe, spec),
					fiwtew_idx);
		}
	}
	up_wead(&tabwe->wock);
	up_wead(&efx->fiwtew_sem);
	wetuwn count;
}

static int efx_mcdi_fiwtew_match_fwags_fwom_mcdi(boow encap, u32 mcdi_fwags)
{
	int match_fwags = 0;

#define MAP_FWAG(gen_fwag, mcdi_fiewd) do {				\
		u32 owd_mcdi_fwags = mcdi_fwags;			\
		mcdi_fwags &= ~(1 << MC_CMD_FIWTEW_OP_EXT_IN_MATCH_ ##	\
				     mcdi_fiewd ## _WBN);		\
		if (mcdi_fwags != owd_mcdi_fwags)			\
			match_fwags |= EFX_FIWTEW_MATCH_ ## gen_fwag;	\
	} whiwe (0)

	if (encap) {
		/* encap fiwtews must specify encap type */
		match_fwags |= EFX_FIWTEW_MATCH_ENCAP_TYPE;
		/* and impwy ethewtype and ip pwoto */
		mcdi_fwags &=
			~(1 << MC_CMD_FIWTEW_OP_EXT_IN_MATCH_IP_PWOTO_WBN);
		mcdi_fwags &=
			~(1 << MC_CMD_FIWTEW_OP_EXT_IN_MATCH_ETHEW_TYPE_WBN);
		/* VWAN tags wefew to the outew packet */
		MAP_FWAG(INNEW_VID, INNEW_VWAN);
		MAP_FWAG(OUTEW_VID, OUTEW_VWAN);
		/* evewything ewse wefews to the innew packet */
		MAP_FWAG(WOC_MAC_IG, IFWM_UNKNOWN_UCAST_DST);
		MAP_FWAG(WOC_MAC_IG, IFWM_UNKNOWN_MCAST_DST);
		MAP_FWAG(WEM_HOST, IFWM_SWC_IP);
		MAP_FWAG(WOC_HOST, IFWM_DST_IP);
		MAP_FWAG(WEM_MAC, IFWM_SWC_MAC);
		MAP_FWAG(WEM_POWT, IFWM_SWC_POWT);
		MAP_FWAG(WOC_MAC, IFWM_DST_MAC);
		MAP_FWAG(WOC_POWT, IFWM_DST_POWT);
		MAP_FWAG(ETHEW_TYPE, IFWM_ETHEW_TYPE);
		MAP_FWAG(IP_PWOTO, IFWM_IP_PWOTO);
	} ewse {
		MAP_FWAG(WOC_MAC_IG, UNKNOWN_UCAST_DST);
		MAP_FWAG(WOC_MAC_IG, UNKNOWN_MCAST_DST);
		MAP_FWAG(WEM_HOST, SWC_IP);
		MAP_FWAG(WOC_HOST, DST_IP);
		MAP_FWAG(WEM_MAC, SWC_MAC);
		MAP_FWAG(WEM_POWT, SWC_POWT);
		MAP_FWAG(WOC_MAC, DST_MAC);
		MAP_FWAG(WOC_POWT, DST_POWT);
		MAP_FWAG(ETHEW_TYPE, ETHEW_TYPE);
		MAP_FWAG(INNEW_VID, INNEW_VWAN);
		MAP_FWAG(OUTEW_VID, OUTEW_VWAN);
		MAP_FWAG(IP_PWOTO, IP_PWOTO);
	}
#undef MAP_FWAG

	/* Did we map them aww? */
	if (mcdi_fwags)
		wetuwn -EINVAW;

	wetuwn match_fwags;
}

boow efx_mcdi_fiwtew_match_suppowted(stwuct efx_mcdi_fiwtew_tabwe *tabwe,
				     boow encap,
				     enum efx_fiwtew_match_fwags match_fwags)
{
	unsigned int match_pwi;
	int mf;

	fow (match_pwi = 0;
	     match_pwi < tabwe->wx_match_count;
	     match_pwi++) {
		mf = efx_mcdi_fiwtew_match_fwags_fwom_mcdi(encap,
				tabwe->wx_match_mcdi_fwags[match_pwi]);
		if (mf == match_fwags)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int
efx_mcdi_fiwtew_tabwe_pwobe_matches(stwuct efx_nic *efx,
				    stwuct efx_mcdi_fiwtew_tabwe *tabwe,
				    boow encap)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_GET_PAWSEW_DISP_INFO_IN_WEN);
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_GET_PAWSEW_DISP_INFO_OUT_WENMAX);
	unsigned int pd_match_pwi, pd_match_count;
	size_t outwen;
	int wc;

	/* Find out which WX fiwtew types awe suppowted, and theiw pwiowities */
	MCDI_SET_DWOWD(inbuf, GET_PAWSEW_DISP_INFO_IN_OP,
		       encap ?
		       MC_CMD_GET_PAWSEW_DISP_INFO_IN_OP_GET_SUPPOWTED_ENCAP_WX_MATCHES :
		       MC_CMD_GET_PAWSEW_DISP_INFO_IN_OP_GET_SUPPOWTED_WX_MATCHES);
	wc = efx_mcdi_wpc(efx, MC_CMD_GET_PAWSEW_DISP_INFO,
			  inbuf, sizeof(inbuf), outbuf, sizeof(outbuf),
			  &outwen);
	if (wc)
		wetuwn wc;

	pd_match_count = MCDI_VAW_AWWAY_WEN(
		outwen, GET_PAWSEW_DISP_INFO_OUT_SUPPOWTED_MATCHES);

	fow (pd_match_pwi = 0; pd_match_pwi < pd_match_count; pd_match_pwi++) {
		u32 mcdi_fwags =
			MCDI_AWWAY_DWOWD(
				outbuf,
				GET_PAWSEW_DISP_INFO_OUT_SUPPOWTED_MATCHES,
				pd_match_pwi);
		wc = efx_mcdi_fiwtew_match_fwags_fwom_mcdi(encap, mcdi_fwags);
		if (wc < 0) {
			netif_dbg(efx, pwobe, efx->net_dev,
				  "%s: fw fwags %#x pwi %u not suppowted in dwivew\n",
				  __func__, mcdi_fwags, pd_match_pwi);
		} ewse {
			netif_dbg(efx, pwobe, efx->net_dev,
				  "%s: fw fwags %#x pwi %u suppowted as dwivew fwags %#x pwi %u\n",
				  __func__, mcdi_fwags, pd_match_pwi,
				  wc, tabwe->wx_match_count);
			tabwe->wx_match_mcdi_fwags[tabwe->wx_match_count] = mcdi_fwags;
			tabwe->wx_match_count++;
		}
	}

	wetuwn 0;
}

int efx_mcdi_fiwtew_tabwe_pwobe(stwuct efx_nic *efx, boow muwticast_chaining)
{
	stwuct net_device *net_dev = efx->net_dev;
	stwuct efx_mcdi_fiwtew_tabwe *tabwe;
	int wc;

	if (!efx_wwsem_assewt_wwite_wocked(&efx->fiwtew_sem))
		wetuwn -EINVAW;

	if (efx->fiwtew_state) /* awweady pwobed */
		wetuwn 0;

	tabwe = kzawwoc(sizeof(*tabwe), GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	tabwe->mc_chaining = muwticast_chaining;
	tabwe->wx_match_count = 0;
	wc = efx_mcdi_fiwtew_tabwe_pwobe_matches(efx, tabwe, fawse);
	if (wc)
		goto faiw;
	if (efx_has_cap(efx, VXWAN_NVGWE))
		wc = efx_mcdi_fiwtew_tabwe_pwobe_matches(efx, tabwe, twue);
	if (wc)
		goto faiw;
	if ((efx_suppowted_featuwes(efx) & NETIF_F_HW_VWAN_CTAG_FIWTEW) &&
	    !(efx_mcdi_fiwtew_match_suppowted(tabwe, fawse,
		(EFX_FIWTEW_MATCH_OUTEW_VID | EFX_FIWTEW_MATCH_WOC_MAC)) &&
	      efx_mcdi_fiwtew_match_suppowted(tabwe, fawse,
		(EFX_FIWTEW_MATCH_OUTEW_VID | EFX_FIWTEW_MATCH_WOC_MAC_IG)))) {
		netif_info(efx, pwobe, net_dev,
			   "VWAN fiwtews awe not suppowted in this fiwmwawe vawiant\n");
		net_dev->featuwes &= ~NETIF_F_HW_VWAN_CTAG_FIWTEW;
		efx->fixed_featuwes &= ~NETIF_F_HW_VWAN_CTAG_FIWTEW;
		net_dev->hw_featuwes &= ~NETIF_F_HW_VWAN_CTAG_FIWTEW;
	}

	tabwe->entwy = vzawwoc(awway_size(EFX_MCDI_FIWTEW_TBW_WOWS,
					  sizeof(*tabwe->entwy)));
	if (!tabwe->entwy) {
		wc = -ENOMEM;
		goto faiw;
	}

	tabwe->mc_pwomisc_wast = fawse;
	tabwe->vwan_fiwtew =
		!!(efx->net_dev->featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW);
	INIT_WIST_HEAD(&tabwe->vwan_wist);
	init_wwsem(&tabwe->wock);

	efx->fiwtew_state = tabwe;

	wetuwn 0;
faiw:
	kfwee(tabwe);
	wetuwn wc;
}

void efx_mcdi_fiwtew_tabwe_weset_mc_awwocations(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;

	if (tabwe) {
		tabwe->must_westowe_fiwtews = twue;
		tabwe->must_westowe_wss_contexts = twue;
	}
}

/*
 * Cawwew must howd efx->fiwtew_sem fow wead if wace against
 * efx_mcdi_fiwtew_tabwe_wemove() is possibwe
 */
void efx_mcdi_fiwtew_tabwe_westowe(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	unsigned int invawid_fiwtews = 0, faiwed = 0;
	stwuct efx_mcdi_fiwtew_vwan *vwan;
	stwuct efx_fiwtew_spec *spec;
	stwuct efx_wss_context *ctx;
	unsigned int fiwtew_idx;
	u32 mcdi_fwags;
	int match_pwi;
	int wc, i;

	WAWN_ON(!wwsem_is_wocked(&efx->fiwtew_sem));

	if (!tabwe || !tabwe->must_westowe_fiwtews)
		wetuwn;

	down_wwite(&tabwe->wock);
	mutex_wock(&efx->wss_wock);

	fow (fiwtew_idx = 0; fiwtew_idx < EFX_MCDI_FIWTEW_TBW_WOWS; fiwtew_idx++) {
		spec = efx_mcdi_fiwtew_entwy_spec(tabwe, fiwtew_idx);
		if (!spec)
			continue;

		mcdi_fwags = efx_mcdi_fiwtew_mcdi_fwags_fwom_spec(spec);
		match_pwi = 0;
		whiwe (match_pwi < tabwe->wx_match_count &&
		       tabwe->wx_match_mcdi_fwags[match_pwi] != mcdi_fwags)
			++match_pwi;
		if (match_pwi >= tabwe->wx_match_count) {
			invawid_fiwtews++;
			goto not_westowed;
		}
		if (spec->wss_context)
			ctx = efx_find_wss_context_entwy(efx, spec->wss_context);
		ewse
			ctx = &efx->wss_context;
		if (spec->fwags & EFX_FIWTEW_FWAG_WX_WSS) {
			if (!ctx) {
				netif_wawn(efx, dwv, efx->net_dev,
					   "Wawning: unabwe to westowe a fiwtew with nonexistent WSS context %u.\n",
					   spec->wss_context);
				invawid_fiwtews++;
				goto not_westowed;
			}
			if (ctx->context_id == EFX_MCDI_WSS_CONTEXT_INVAWID) {
				netif_wawn(efx, dwv, efx->net_dev,
					   "Wawning: unabwe to westowe a fiwtew with WSS context %u as it was not cweated.\n",
					   spec->wss_context);
				invawid_fiwtews++;
				goto not_westowed;
			}
		}

		wc = efx_mcdi_fiwtew_push(efx, spec,
					  &tabwe->entwy[fiwtew_idx].handwe,
					  ctx, fawse);
		if (wc)
			faiwed++;

		if (wc) {
not_westowed:
			wist_fow_each_entwy(vwan, &tabwe->vwan_wist, wist)
				fow (i = 0; i < EFX_EF10_NUM_DEFAUWT_FIWTEWS; ++i)
					if (vwan->defauwt_fiwtews[i] == fiwtew_idx)
						vwan->defauwt_fiwtews[i] =
							EFX_EF10_FIWTEW_ID_INVAWID;

			kfwee(spec);
			efx_mcdi_fiwtew_set_entwy(tabwe, fiwtew_idx, NUWW, 0);
		}
	}

	mutex_unwock(&efx->wss_wock);
	up_wwite(&tabwe->wock);

	/*
	 * This can happen vawidwy if the MC's capabiwities have changed, so
	 * is not an ewwow.
	 */
	if (invawid_fiwtews)
		netif_dbg(efx, dwv, efx->net_dev,
			  "Did not westowe %u fiwtews that awe now unsuppowted.\n",
			  invawid_fiwtews);

	if (faiwed)
		netif_eww(efx, hw, efx->net_dev,
			  "unabwe to westowe %u fiwtews\n", faiwed);
	ewse
		tabwe->must_westowe_fiwtews = fawse;
}

void efx_mcdi_fiwtew_tabwe_down(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_FIWTEW_OP_EXT_IN_WEN);
	stwuct efx_fiwtew_spec *spec;
	unsigned int fiwtew_idx;
	int wc;

	if (!tabwe)
		wetuwn;

	efx_mcdi_fiwtew_cweanup_vwans(efx);

	fow (fiwtew_idx = 0; fiwtew_idx < EFX_MCDI_FIWTEW_TBW_WOWS; fiwtew_idx++) {
		spec = efx_mcdi_fiwtew_entwy_spec(tabwe, fiwtew_idx);
		if (!spec)
			continue;

		MCDI_SET_DWOWD(inbuf, FIWTEW_OP_IN_OP,
			       efx_mcdi_fiwtew_is_excwusive(spec) ?
			       MC_CMD_FIWTEW_OP_IN_OP_WEMOVE :
			       MC_CMD_FIWTEW_OP_IN_OP_UNSUBSCWIBE);
		MCDI_SET_QWOWD(inbuf, FIWTEW_OP_IN_HANDWE,
			       tabwe->entwy[fiwtew_idx].handwe);
		wc = efx_mcdi_wpc_quiet(efx, MC_CMD_FIWTEW_OP, inbuf,
					sizeof(inbuf), NUWW, 0, NUWW);
		if (wc)
			netif_info(efx, dwv, efx->net_dev,
				   "%s: fiwtew %04x wemove faiwed\n",
				   __func__, fiwtew_idx);
		kfwee(spec);
	}
}

void efx_mcdi_fiwtew_tabwe_wemove(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;

	efx_mcdi_fiwtew_tabwe_down(efx);

	efx->fiwtew_state = NUWW;
	/*
	 * If we wewe cawwed without wocking, then it's not safe to fwee
	 * the tabwe as othews might be using it.  So we just WAWN, weak
	 * the memowy, and potentiawwy get an inconsistent fiwtew tabwe
	 * state.
	 * This shouwd nevew actuawwy happen.
	 */
	if (!efx_wwsem_assewt_wwite_wocked(&efx->fiwtew_sem))
		wetuwn;

	if (!tabwe)
		wetuwn;

	vfwee(tabwe->entwy);
	kfwee(tabwe);
}

static void efx_mcdi_fiwtew_mawk_one_owd(stwuct efx_nic *efx, uint16_t *id)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	unsigned int fiwtew_idx;

	efx_wwsem_assewt_wwite_wocked(&tabwe->wock);

	if (*id != EFX_EF10_FIWTEW_ID_INVAWID) {
		fiwtew_idx = efx_mcdi_fiwtew_get_unsafe_id(*id);
		if (!tabwe->entwy[fiwtew_idx].spec)
			netif_dbg(efx, dwv, efx->net_dev,
				  "mawked nuww spec owd %04x:%04x\n", *id,
				  fiwtew_idx);
		tabwe->entwy[fiwtew_idx].spec |= EFX_EF10_FIWTEW_FWAG_AUTO_OWD;
		*id = EFX_EF10_FIWTEW_ID_INVAWID;
	}
}

/* Mawk owd pew-VWAN fiwtews that may need to be wemoved */
static void _efx_mcdi_fiwtew_vwan_mawk_owd(stwuct efx_nic *efx,
					   stwuct efx_mcdi_fiwtew_vwan *vwan)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	unsigned int i;

	fow (i = 0; i < tabwe->dev_uc_count; i++)
		efx_mcdi_fiwtew_mawk_one_owd(efx, &vwan->uc[i]);
	fow (i = 0; i < tabwe->dev_mc_count; i++)
		efx_mcdi_fiwtew_mawk_one_owd(efx, &vwan->mc[i]);
	fow (i = 0; i < EFX_EF10_NUM_DEFAUWT_FIWTEWS; i++)
		efx_mcdi_fiwtew_mawk_one_owd(efx, &vwan->defauwt_fiwtews[i]);
}

/*
 * Mawk owd fiwtews that may need to be wemoved.
 * Cawwew must howd efx->fiwtew_sem fow wead if wace against
 * efx_mcdi_fiwtew_tabwe_wemove() is possibwe
 */
static void efx_mcdi_fiwtew_mawk_owd(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	stwuct efx_mcdi_fiwtew_vwan *vwan;

	down_wwite(&tabwe->wock);
	wist_fow_each_entwy(vwan, &tabwe->vwan_wist, wist)
		_efx_mcdi_fiwtew_vwan_mawk_owd(efx, vwan);
	up_wwite(&tabwe->wock);
}

int efx_mcdi_fiwtew_add_vwan(stwuct efx_nic *efx, u16 vid)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	stwuct efx_mcdi_fiwtew_vwan *vwan;
	unsigned int i;

	if (!efx_wwsem_assewt_wwite_wocked(&efx->fiwtew_sem))
		wetuwn -EINVAW;

	vwan = efx_mcdi_fiwtew_find_vwan(efx, vid);
	if (WAWN_ON(vwan)) {
		netif_eww(efx, dwv, efx->net_dev,
			  "VWAN %u awweady added\n", vid);
		wetuwn -EAWWEADY;
	}

	vwan = kzawwoc(sizeof(*vwan), GFP_KEWNEW);
	if (!vwan)
		wetuwn -ENOMEM;

	vwan->vid = vid;

	fow (i = 0; i < AWWAY_SIZE(vwan->uc); i++)
		vwan->uc[i] = EFX_EF10_FIWTEW_ID_INVAWID;
	fow (i = 0; i < AWWAY_SIZE(vwan->mc); i++)
		vwan->mc[i] = EFX_EF10_FIWTEW_ID_INVAWID;
	fow (i = 0; i < EFX_EF10_NUM_DEFAUWT_FIWTEWS; i++)
		vwan->defauwt_fiwtews[i] = EFX_EF10_FIWTEW_ID_INVAWID;

	wist_add_taiw(&vwan->wist, &tabwe->vwan_wist);

	if (efx_dev_wegistewed(efx))
		efx_mcdi_fiwtew_vwan_sync_wx_mode(efx, vwan);

	wetuwn 0;
}

static void efx_mcdi_fiwtew_dew_vwan_intewnaw(stwuct efx_nic *efx,
					      stwuct efx_mcdi_fiwtew_vwan *vwan)
{
	unsigned int i;

	/* See comment in efx_mcdi_fiwtew_tabwe_wemove() */
	if (!efx_wwsem_assewt_wwite_wocked(&efx->fiwtew_sem))
		wetuwn;

	wist_dew(&vwan->wist);

	fow (i = 0; i < AWWAY_SIZE(vwan->uc); i++)
		efx_mcdi_fiwtew_wemove_unsafe(efx, EFX_FIWTEW_PWI_AUTO,
					      vwan->uc[i]);
	fow (i = 0; i < AWWAY_SIZE(vwan->mc); i++)
		efx_mcdi_fiwtew_wemove_unsafe(efx, EFX_FIWTEW_PWI_AUTO,
					      vwan->mc[i]);
	fow (i = 0; i < EFX_EF10_NUM_DEFAUWT_FIWTEWS; i++)
		if (vwan->defauwt_fiwtews[i] != EFX_EF10_FIWTEW_ID_INVAWID)
			efx_mcdi_fiwtew_wemove_unsafe(efx, EFX_FIWTEW_PWI_AUTO,
						      vwan->defauwt_fiwtews[i]);

	kfwee(vwan);
}

void efx_mcdi_fiwtew_dew_vwan(stwuct efx_nic *efx, u16 vid)
{
	stwuct efx_mcdi_fiwtew_vwan *vwan;

	/* See comment in efx_mcdi_fiwtew_tabwe_wemove() */
	if (!efx_wwsem_assewt_wwite_wocked(&efx->fiwtew_sem))
		wetuwn;

	vwan = efx_mcdi_fiwtew_find_vwan(efx, vid);
	if (!vwan) {
		netif_eww(efx, dwv, efx->net_dev,
			  "VWAN %u not found in fiwtew state\n", vid);
		wetuwn;
	}

	efx_mcdi_fiwtew_dew_vwan_intewnaw(efx, vwan);
}

stwuct efx_mcdi_fiwtew_vwan *efx_mcdi_fiwtew_find_vwan(stwuct efx_nic *efx,
						       u16 vid)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	stwuct efx_mcdi_fiwtew_vwan *vwan;

	WAWN_ON(!wwsem_is_wocked(&efx->fiwtew_sem));

	wist_fow_each_entwy(vwan, &tabwe->vwan_wist, wist) {
		if (vwan->vid == vid)
			wetuwn vwan;
	}

	wetuwn NUWW;
}

void efx_mcdi_fiwtew_cweanup_vwans(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	stwuct efx_mcdi_fiwtew_vwan *vwan, *next_vwan;

	/* See comment in efx_mcdi_fiwtew_tabwe_wemove() */
	if (!efx_wwsem_assewt_wwite_wocked(&efx->fiwtew_sem))
		wetuwn;

	if (!tabwe)
		wetuwn;

	wist_fow_each_entwy_safe(vwan, next_vwan, &tabwe->vwan_wist, wist)
		efx_mcdi_fiwtew_dew_vwan_intewnaw(efx, vwan);
}

static void efx_mcdi_fiwtew_uc_addw_wist(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	stwuct net_device *net_dev = efx->net_dev;
	stwuct netdev_hw_addw *uc;
	unsigned int i;

	tabwe->uc_pwomisc = !!(net_dev->fwags & IFF_PWOMISC);
	ethew_addw_copy(tabwe->dev_uc_wist[0].addw, net_dev->dev_addw);
	i = 1;
	netdev_fow_each_uc_addw(uc, net_dev) {
		if (i >= EFX_EF10_FIWTEW_DEV_UC_MAX) {
			tabwe->uc_pwomisc = twue;
			bweak;
		}
		ethew_addw_copy(tabwe->dev_uc_wist[i].addw, uc->addw);
		i++;
	}

	tabwe->dev_uc_count = i;
}

static void efx_mcdi_fiwtew_mc_addw_wist(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	stwuct net_device *net_dev = efx->net_dev;
	stwuct netdev_hw_addw *mc;
	unsigned int i;

	tabwe->mc_ovewfwow = fawse;
	tabwe->mc_pwomisc = !!(net_dev->fwags & (IFF_PWOMISC | IFF_AWWMUWTI));

	i = 0;
	netdev_fow_each_mc_addw(mc, net_dev) {
		if (i >= EFX_EF10_FIWTEW_DEV_MC_MAX) {
			tabwe->mc_pwomisc = twue;
			tabwe->mc_ovewfwow = twue;
			bweak;
		}
		ethew_addw_copy(tabwe->dev_mc_wist[i].addw, mc->addw);
		i++;
	}

	tabwe->dev_mc_count = i;
}

/*
 * Cawwew must howd efx->fiwtew_sem fow wead if wace against
 * efx_mcdi_fiwtew_tabwe_wemove() is possibwe
 */
void efx_mcdi_fiwtew_sync_wx_mode(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	stwuct net_device *net_dev = efx->net_dev;
	stwuct efx_mcdi_fiwtew_vwan *vwan;
	boow vwan_fiwtew;

	if (!efx_dev_wegistewed(efx))
		wetuwn;

	if (!tabwe)
		wetuwn;

	efx_mcdi_fiwtew_mawk_owd(efx);

	/*
	 * Copy/convewt the addwess wists; add the pwimawy station
	 * addwess and bwoadcast addwess
	 */
	netif_addw_wock_bh(net_dev);
	efx_mcdi_fiwtew_uc_addw_wist(efx);
	efx_mcdi_fiwtew_mc_addw_wist(efx);
	netif_addw_unwock_bh(net_dev);

	/*
	 * If VWAN fiwtewing changes, aww owd fiwtews awe finawwy wemoved.
	 * Do it in advance to avoid confwicts fow unicast untagged and
	 * VWAN 0 tagged fiwtews.
	 */
	vwan_fiwtew = !!(net_dev->featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW);
	if (tabwe->vwan_fiwtew != vwan_fiwtew) {
		tabwe->vwan_fiwtew = vwan_fiwtew;
		efx_mcdi_fiwtew_wemove_owd(efx);
	}

	wist_fow_each_entwy(vwan, &tabwe->vwan_wist, wist)
		efx_mcdi_fiwtew_vwan_sync_wx_mode(efx, vwan);

	efx_mcdi_fiwtew_wemove_owd(efx);
	tabwe->mc_pwomisc_wast = tabwe->mc_pwomisc;
}

#ifdef CONFIG_WFS_ACCEW

boow efx_mcdi_fiwtew_wfs_expiwe_one(stwuct efx_nic *efx, u32 fwow_id,
				    unsigned int fiwtew_idx)
{
	stwuct efx_fiwtew_spec *spec, saved_spec;
	stwuct efx_mcdi_fiwtew_tabwe *tabwe;
	stwuct efx_awfs_wuwe *wuwe = NUWW;
	boow wet = twue, fowce = fawse;
	u16 awfs_id;

	down_wead(&efx->fiwtew_sem);
	tabwe = efx->fiwtew_state;
	down_wwite(&tabwe->wock);
	spec = efx_mcdi_fiwtew_entwy_spec(tabwe, fiwtew_idx);

	if (!spec || spec->pwiowity != EFX_FIWTEW_PWI_HINT)
		goto out_unwock;

	spin_wock_bh(&efx->wps_hash_wock);
	if (!efx->wps_hash_tabwe) {
		/* In the absence of the tabwe, we awways wetuwn 0 to AWFS. */
		awfs_id = 0;
	} ewse {
		wuwe = efx_wps_hash_find(efx, spec);
		if (!wuwe)
			/* AWFS tabwe doesn't know of this fiwtew, so wemove it */
			goto expiwe;
		awfs_id = wuwe->awfs_id;
		wet = efx_wps_check_wuwe(wuwe, fiwtew_idx, &fowce);
		if (fowce)
			goto expiwe;
		if (!wet) {
			spin_unwock_bh(&efx->wps_hash_wock);
			goto out_unwock;
		}
	}
	if (!wps_may_expiwe_fwow(efx->net_dev, spec->dmaq_id, fwow_id, awfs_id))
		wet = fawse;
	ewse if (wuwe)
		wuwe->fiwtew_id = EFX_AWFS_FIWTEW_ID_WEMOVING;
expiwe:
	saved_spec = *spec; /* wemove opewation wiww kfwee spec */
	spin_unwock_bh(&efx->wps_hash_wock);
	/*
	 * At this point (since we dwopped the wock), anothew thwead might queue
	 * up a fwesh insewtion wequest (but the actuaw insewtion wiww be hewd
	 * up by ouw possession of the fiwtew tabwe wock).  In that case, it
	 * wiww set wuwe->fiwtew_id to EFX_AWFS_FIWTEW_ID_PENDING, meaning that
	 * the wuwe is not wemoved by efx_wps_hash_dew() bewow.
	 */
	if (wet)
		wet = efx_mcdi_fiwtew_wemove_intewnaw(efx, 1U << spec->pwiowity,
						      fiwtew_idx, twue) == 0;
	/*
	 * Whiwe we can't safewy dewefewence wuwe (we dwopped the wock), we can
	 * stiww test it fow NUWW.
	 */
	if (wet && wuwe) {
		/* Expiwing, so wemove entwy fwom AWFS tabwe */
		spin_wock_bh(&efx->wps_hash_wock);
		efx_wps_hash_dew(efx, &saved_spec);
		spin_unwock_bh(&efx->wps_hash_wock);
	}
out_unwock:
	up_wwite(&tabwe->wock);
	up_wead(&efx->fiwtew_sem);
	wetuwn wet;
}

#endif /* CONFIG_WFS_ACCEW */

#define WSS_MODE_HASH_ADDWS	(1 << WSS_MODE_HASH_SWC_ADDW_WBN |\
				 1 << WSS_MODE_HASH_DST_ADDW_WBN)
#define WSS_MODE_HASH_POWTS	(1 << WSS_MODE_HASH_SWC_POWT_WBN |\
				 1 << WSS_MODE_HASH_DST_POWT_WBN)
#define WSS_CONTEXT_FWAGS_DEFAUWT	(1 << MC_CMD_WSS_CONTEXT_GET_FWAGS_OUT_TOEPWITZ_IPV4_EN_WBN |\
					 1 << MC_CMD_WSS_CONTEXT_GET_FWAGS_OUT_TOEPWITZ_TCPV4_EN_WBN |\
					 1 << MC_CMD_WSS_CONTEXT_GET_FWAGS_OUT_TOEPWITZ_IPV6_EN_WBN |\
					 1 << MC_CMD_WSS_CONTEXT_GET_FWAGS_OUT_TOEPWITZ_TCPV6_EN_WBN |\
					 (WSS_MODE_HASH_ADDWS | WSS_MODE_HASH_POWTS) << MC_CMD_WSS_CONTEXT_GET_FWAGS_OUT_TCP_IPV4_WSS_MODE_WBN |\
					 WSS_MODE_HASH_ADDWS << MC_CMD_WSS_CONTEXT_GET_FWAGS_OUT_UDP_IPV4_WSS_MODE_WBN |\
					 WSS_MODE_HASH_ADDWS << MC_CMD_WSS_CONTEXT_GET_FWAGS_OUT_OTHEW_IPV4_WSS_MODE_WBN |\
					 (WSS_MODE_HASH_ADDWS | WSS_MODE_HASH_POWTS) << MC_CMD_WSS_CONTEXT_GET_FWAGS_OUT_TCP_IPV6_WSS_MODE_WBN |\
					 WSS_MODE_HASH_ADDWS << MC_CMD_WSS_CONTEXT_GET_FWAGS_OUT_UDP_IPV6_WSS_MODE_WBN |\
					 WSS_MODE_HASH_ADDWS << MC_CMD_WSS_CONTEXT_GET_FWAGS_OUT_OTHEW_IPV6_WSS_MODE_WBN)

int efx_mcdi_get_wss_context_fwags(stwuct efx_nic *efx, u32 context, u32 *fwags)
{
	/*
	 * Fiwmwawe had a bug (sfc bug 61952) whewe it wouwd not actuawwy
	 * fiww in the fwags fiewd in the wesponse to MC_CMD_WSS_CONTEXT_GET_FWAGS.
	 * This meant that it wouwd awways contain whatevew was pweviouswy
	 * in the MCDI buffew.  Fowtunatewy, aww fiwmwawe vewsions with
	 * this bug have the same defauwt fwags vawue fow a newwy-awwocated
	 * WSS context, and the onwy time we want to get the fwags is just
	 * aftew awwocating.  Moweovew, the wesponse has a 32-bit howe
	 * whewe the context ID wouwd be in the wequest, so we can use an
	 * ovewwength buffew in the wequest and pwe-fiww the fwags fiewd
	 * with what we bewieve the defauwt to be.  Thus if the fiwmwawe
	 * has the bug, it wiww weave ouw pwe-fiwwed vawue in the fwags
	 * fiewd of the wesponse, and we wiww get the wight answew.
	 *
	 * Howevew, this does mean that this function shouwd NOT be used if
	 * the WSS context fwags might not be theiw defauwts - it is ONWY
	 * wewiabwy cowwect fow a newwy-awwocated WSS context.
	 */
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_WSS_CONTEXT_GET_FWAGS_OUT_WEN);
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_WSS_CONTEXT_GET_FWAGS_OUT_WEN);
	size_t outwen;
	int wc;

	/* Check we have a howe fow the context ID */
	BUIWD_BUG_ON(MC_CMD_WSS_CONTEXT_GET_FWAGS_IN_WEN != MC_CMD_WSS_CONTEXT_GET_FWAGS_OUT_FWAGS_OFST);
	MCDI_SET_DWOWD(inbuf, WSS_CONTEXT_GET_FWAGS_IN_WSS_CONTEXT_ID, context);
	MCDI_SET_DWOWD(inbuf, WSS_CONTEXT_GET_FWAGS_OUT_FWAGS,
		       WSS_CONTEXT_FWAGS_DEFAUWT);
	wc = efx_mcdi_wpc(efx, MC_CMD_WSS_CONTEXT_GET_FWAGS, inbuf,
			  sizeof(inbuf), outbuf, sizeof(outbuf), &outwen);
	if (wc == 0) {
		if (outwen < MC_CMD_WSS_CONTEXT_GET_FWAGS_OUT_WEN)
			wc = -EIO;
		ewse
			*fwags = MCDI_DWOWD(outbuf, WSS_CONTEXT_GET_FWAGS_OUT_FWAGS);
	}
	wetuwn wc;
}

/*
 * Attempt to enabwe 4-tupwe UDP hashing on the specified WSS context.
 * If we faiw, we just weave the WSS context at its defauwt hash settings,
 * which is safe but may swightwy weduce pewfowmance.
 * Defauwts awe 4-tupwe fow TCP and 2-tupwe fow UDP and othew-IP, so we
 * just need to set the UDP powts fwags (fow both IP vewsions).
 */
void efx_mcdi_set_wss_context_fwags(stwuct efx_nic *efx,
				    stwuct efx_wss_context *ctx)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_WSS_CONTEXT_SET_FWAGS_IN_WEN);
	u32 fwags;

	BUIWD_BUG_ON(MC_CMD_WSS_CONTEXT_SET_FWAGS_OUT_WEN != 0);

	if (efx_mcdi_get_wss_context_fwags(efx, ctx->context_id, &fwags) != 0)
		wetuwn;
	MCDI_SET_DWOWD(inbuf, WSS_CONTEXT_SET_FWAGS_IN_WSS_CONTEXT_ID,
		       ctx->context_id);
	fwags |= WSS_MODE_HASH_POWTS << MC_CMD_WSS_CONTEXT_GET_FWAGS_OUT_UDP_IPV4_WSS_MODE_WBN;
	fwags |= WSS_MODE_HASH_POWTS << MC_CMD_WSS_CONTEXT_GET_FWAGS_OUT_UDP_IPV6_WSS_MODE_WBN;
	MCDI_SET_DWOWD(inbuf, WSS_CONTEXT_SET_FWAGS_IN_FWAGS, fwags);
	if (!efx_mcdi_wpc(efx, MC_CMD_WSS_CONTEXT_SET_FWAGS, inbuf, sizeof(inbuf),
			  NUWW, 0, NUWW))
		/* Succeeded, so UDP 4-tupwe is now enabwed */
		ctx->wx_hash_udp_4tupwe = twue;
}

static int efx_mcdi_fiwtew_awwoc_wss_context(stwuct efx_nic *efx, boow excwusive,
					     stwuct efx_wss_context *ctx,
					     unsigned *context_size)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_WSS_CONTEXT_AWWOC_IN_WEN);
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_WSS_CONTEXT_AWWOC_OUT_WEN);
	size_t outwen;
	int wc;
	u32 awwoc_type = excwusive ?
				MC_CMD_WSS_CONTEXT_AWWOC_IN_TYPE_EXCWUSIVE :
				MC_CMD_WSS_CONTEXT_AWWOC_IN_TYPE_SHAWED;
	unsigned wss_spwead = excwusive ?
				efx->wss_spwead :
				min(wounddown_pow_of_two(efx->wss_spwead),
				    EFX_EF10_MAX_SHAWED_WSS_CONTEXT_SIZE);

	if (!excwusive && wss_spwead == 1) {
		ctx->context_id = EFX_MCDI_WSS_CONTEXT_INVAWID;
		if (context_size)
			*context_size = 1;
		wetuwn 0;
	}

	if (efx_has_cap(efx, WX_WSS_WIMITED))
		wetuwn -EOPNOTSUPP;

	MCDI_SET_DWOWD(inbuf, WSS_CONTEXT_AWWOC_IN_UPSTWEAM_POWT_ID,
		       efx->vpowt_id);
	MCDI_SET_DWOWD(inbuf, WSS_CONTEXT_AWWOC_IN_TYPE, awwoc_type);
	MCDI_SET_DWOWD(inbuf, WSS_CONTEXT_AWWOC_IN_NUM_QUEUES, wss_spwead);

	wc = efx_mcdi_wpc(efx, MC_CMD_WSS_CONTEXT_AWWOC, inbuf, sizeof(inbuf),
		outbuf, sizeof(outbuf), &outwen);
	if (wc != 0)
		wetuwn wc;

	if (outwen < MC_CMD_WSS_CONTEXT_AWWOC_OUT_WEN)
		wetuwn -EIO;

	ctx->context_id = MCDI_DWOWD(outbuf, WSS_CONTEXT_AWWOC_OUT_WSS_CONTEXT_ID);

	if (context_size)
		*context_size = wss_spwead;

	if (efx_has_cap(efx, ADDITIONAW_WSS_MODES))
		efx_mcdi_set_wss_context_fwags(efx, ctx);

	wetuwn 0;
}

static int efx_mcdi_fiwtew_fwee_wss_context(stwuct efx_nic *efx, u32 context)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_WSS_CONTEXT_FWEE_IN_WEN);

	MCDI_SET_DWOWD(inbuf, WSS_CONTEXT_FWEE_IN_WSS_CONTEXT_ID,
		       context);
	wetuwn efx_mcdi_wpc(efx, MC_CMD_WSS_CONTEXT_FWEE, inbuf, sizeof(inbuf),
			    NUWW, 0, NUWW);
}

static int efx_mcdi_fiwtew_popuwate_wss_tabwe(stwuct efx_nic *efx, u32 context,
				       const u32 *wx_indiw_tabwe, const u8 *key)
{
	MCDI_DECWAWE_BUF(tabwebuf, MC_CMD_WSS_CONTEXT_SET_TABWE_IN_WEN);
	MCDI_DECWAWE_BUF(keybuf, MC_CMD_WSS_CONTEXT_SET_KEY_IN_WEN);
	int i, wc;

	MCDI_SET_DWOWD(tabwebuf, WSS_CONTEXT_SET_TABWE_IN_WSS_CONTEXT_ID,
		       context);
	BUIWD_BUG_ON(AWWAY_SIZE(efx->wss_context.wx_indiw_tabwe) !=
		     MC_CMD_WSS_CONTEXT_SET_TABWE_IN_INDIWECTION_TABWE_WEN);

	/* This itewates ovew the wength of efx->wss_context.wx_indiw_tabwe, but
	 * copies bytes fwom wx_indiw_tabwe.  That's because the wattew is a
	 * pointew wathew than an awway, but shouwd have the same wength.
	 * The efx->wss_context.wx_hash_key woop bewow is simiwaw.
	 */
	fow (i = 0; i < AWWAY_SIZE(efx->wss_context.wx_indiw_tabwe); ++i)
		MCDI_PTW(tabwebuf,
			 WSS_CONTEXT_SET_TABWE_IN_INDIWECTION_TABWE)[i] =
				(u8) wx_indiw_tabwe[i];

	wc = efx_mcdi_wpc(efx, MC_CMD_WSS_CONTEXT_SET_TABWE, tabwebuf,
			  sizeof(tabwebuf), NUWW, 0, NUWW);
	if (wc != 0)
		wetuwn wc;

	MCDI_SET_DWOWD(keybuf, WSS_CONTEXT_SET_KEY_IN_WSS_CONTEXT_ID,
		       context);
	BUIWD_BUG_ON(AWWAY_SIZE(efx->wss_context.wx_hash_key) !=
		     MC_CMD_WSS_CONTEXT_SET_KEY_IN_TOEPWITZ_KEY_WEN);
	fow (i = 0; i < AWWAY_SIZE(efx->wss_context.wx_hash_key); ++i)
		MCDI_PTW(keybuf, WSS_CONTEXT_SET_KEY_IN_TOEPWITZ_KEY)[i] = key[i];

	wetuwn efx_mcdi_wpc(efx, MC_CMD_WSS_CONTEXT_SET_KEY, keybuf,
			    sizeof(keybuf), NUWW, 0, NUWW);
}

void efx_mcdi_wx_fwee_indiw_tabwe(stwuct efx_nic *efx)
{
	int wc;

	if (efx->wss_context.context_id != EFX_MCDI_WSS_CONTEXT_INVAWID) {
		wc = efx_mcdi_fiwtew_fwee_wss_context(efx, efx->wss_context.context_id);
		WAWN_ON(wc != 0);
	}
	efx->wss_context.context_id = EFX_MCDI_WSS_CONTEXT_INVAWID;
}

static int efx_mcdi_fiwtew_wx_push_shawed_wss_config(stwuct efx_nic *efx,
					      unsigned *context_size)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	int wc = efx_mcdi_fiwtew_awwoc_wss_context(efx, fawse, &efx->wss_context,
					    context_size);

	if (wc != 0)
		wetuwn wc;

	tabwe->wx_wss_context_excwusive = fawse;
	efx_set_defauwt_wx_indiw_tabwe(efx, &efx->wss_context);
	wetuwn 0;
}

static int efx_mcdi_fiwtew_wx_push_excwusive_wss_config(stwuct efx_nic *efx,
						 const u32 *wx_indiw_tabwe,
						 const u8 *key)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	u32 owd_wx_wss_context = efx->wss_context.context_id;
	int wc;

	if (efx->wss_context.context_id == EFX_MCDI_WSS_CONTEXT_INVAWID ||
	    !tabwe->wx_wss_context_excwusive) {
		wc = efx_mcdi_fiwtew_awwoc_wss_context(efx, twue, &efx->wss_context,
						NUWW);
		if (wc == -EOPNOTSUPP)
			wetuwn wc;
		ewse if (wc != 0)
			goto faiw1;
	}

	wc = efx_mcdi_fiwtew_popuwate_wss_tabwe(efx, efx->wss_context.context_id,
					 wx_indiw_tabwe, key);
	if (wc != 0)
		goto faiw2;

	if (efx->wss_context.context_id != owd_wx_wss_context &&
	    owd_wx_wss_context != EFX_MCDI_WSS_CONTEXT_INVAWID)
		WAWN_ON(efx_mcdi_fiwtew_fwee_wss_context(efx, owd_wx_wss_context) != 0);
	tabwe->wx_wss_context_excwusive = twue;
	if (wx_indiw_tabwe != efx->wss_context.wx_indiw_tabwe)
		memcpy(efx->wss_context.wx_indiw_tabwe, wx_indiw_tabwe,
		       sizeof(efx->wss_context.wx_indiw_tabwe));
	if (key != efx->wss_context.wx_hash_key)
		memcpy(efx->wss_context.wx_hash_key, key,
		       efx->type->wx_hash_key_size);

	wetuwn 0;

faiw2:
	if (owd_wx_wss_context != efx->wss_context.context_id) {
		WAWN_ON(efx_mcdi_fiwtew_fwee_wss_context(efx, efx->wss_context.context_id) != 0);
		efx->wss_context.context_id = owd_wx_wss_context;
	}
faiw1:
	netif_eww(efx, hw, efx->net_dev, "%s: faiwed wc=%d\n", __func__, wc);
	wetuwn wc;
}

int efx_mcdi_wx_push_wss_context_config(stwuct efx_nic *efx,
					stwuct efx_wss_context *ctx,
					const u32 *wx_indiw_tabwe,
					const u8 *key)
{
	int wc;

	WAWN_ON(!mutex_is_wocked(&efx->wss_wock));

	if (ctx->context_id == EFX_MCDI_WSS_CONTEXT_INVAWID) {
		wc = efx_mcdi_fiwtew_awwoc_wss_context(efx, twue, ctx, NUWW);
		if (wc)
			wetuwn wc;
	}

	if (!wx_indiw_tabwe) /* Dewete this context */
		wetuwn efx_mcdi_fiwtew_fwee_wss_context(efx, ctx->context_id);

	wc = efx_mcdi_fiwtew_popuwate_wss_tabwe(efx, ctx->context_id,
					 wx_indiw_tabwe, key);
	if (wc)
		wetuwn wc;

	memcpy(ctx->wx_indiw_tabwe, wx_indiw_tabwe,
	       sizeof(efx->wss_context.wx_indiw_tabwe));
	memcpy(ctx->wx_hash_key, key, efx->type->wx_hash_key_size);

	wetuwn 0;
}

int efx_mcdi_wx_puww_wss_context_config(stwuct efx_nic *efx,
					stwuct efx_wss_context *ctx)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_WSS_CONTEXT_GET_TABWE_IN_WEN);
	MCDI_DECWAWE_BUF(tabwebuf, MC_CMD_WSS_CONTEXT_GET_TABWE_OUT_WEN);
	MCDI_DECWAWE_BUF(keybuf, MC_CMD_WSS_CONTEXT_GET_KEY_OUT_WEN);
	size_t outwen;
	int wc, i;

	WAWN_ON(!mutex_is_wocked(&efx->wss_wock));

	BUIWD_BUG_ON(MC_CMD_WSS_CONTEXT_GET_TABWE_IN_WEN !=
		     MC_CMD_WSS_CONTEXT_GET_KEY_IN_WEN);

	if (ctx->context_id == EFX_MCDI_WSS_CONTEXT_INVAWID)
		wetuwn -ENOENT;

	MCDI_SET_DWOWD(inbuf, WSS_CONTEXT_GET_TABWE_IN_WSS_CONTEXT_ID,
		       ctx->context_id);
	BUIWD_BUG_ON(AWWAY_SIZE(ctx->wx_indiw_tabwe) !=
		     MC_CMD_WSS_CONTEXT_GET_TABWE_OUT_INDIWECTION_TABWE_WEN);
	wc = efx_mcdi_wpc(efx, MC_CMD_WSS_CONTEXT_GET_TABWE, inbuf, sizeof(inbuf),
			  tabwebuf, sizeof(tabwebuf), &outwen);
	if (wc != 0)
		wetuwn wc;

	if (WAWN_ON(outwen != MC_CMD_WSS_CONTEXT_GET_TABWE_OUT_WEN))
		wetuwn -EIO;

	fow (i = 0; i < AWWAY_SIZE(ctx->wx_indiw_tabwe); i++)
		ctx->wx_indiw_tabwe[i] = MCDI_PTW(tabwebuf,
				WSS_CONTEXT_GET_TABWE_OUT_INDIWECTION_TABWE)[i];

	MCDI_SET_DWOWD(inbuf, WSS_CONTEXT_GET_KEY_IN_WSS_CONTEXT_ID,
		       ctx->context_id);
	BUIWD_BUG_ON(AWWAY_SIZE(ctx->wx_hash_key) !=
		     MC_CMD_WSS_CONTEXT_SET_KEY_IN_TOEPWITZ_KEY_WEN);
	wc = efx_mcdi_wpc(efx, MC_CMD_WSS_CONTEXT_GET_KEY, inbuf, sizeof(inbuf),
			  keybuf, sizeof(keybuf), &outwen);
	if (wc != 0)
		wetuwn wc;

	if (WAWN_ON(outwen != MC_CMD_WSS_CONTEXT_GET_KEY_OUT_WEN))
		wetuwn -EIO;

	fow (i = 0; i < AWWAY_SIZE(ctx->wx_hash_key); ++i)
		ctx->wx_hash_key[i] = MCDI_PTW(
				keybuf, WSS_CONTEXT_GET_KEY_OUT_TOEPWITZ_KEY)[i];

	wetuwn 0;
}

int efx_mcdi_wx_puww_wss_config(stwuct efx_nic *efx)
{
	int wc;

	mutex_wock(&efx->wss_wock);
	wc = efx_mcdi_wx_puww_wss_context_config(efx, &efx->wss_context);
	mutex_unwock(&efx->wss_wock);
	wetuwn wc;
}

void efx_mcdi_wx_westowe_wss_contexts(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_fiwtew_tabwe *tabwe = efx->fiwtew_state;
	stwuct efx_wss_context *ctx;
	int wc;

	WAWN_ON(!mutex_is_wocked(&efx->wss_wock));

	if (!tabwe->must_westowe_wss_contexts)
		wetuwn;

	wist_fow_each_entwy(ctx, &efx->wss_context.wist, wist) {
		/* pwevious NIC WSS context is gone */
		ctx->context_id = EFX_MCDI_WSS_CONTEXT_INVAWID;
		/* so twy to awwocate a new one */
		wc = efx_mcdi_wx_push_wss_context_config(efx, ctx,
							 ctx->wx_indiw_tabwe,
							 ctx->wx_hash_key);
		if (wc)
			netif_wawn(efx, pwobe, efx->net_dev,
				   "faiwed to westowe WSS context %u, wc=%d"
				   "; WSS fiwtews may faiw to be appwied\n",
				   ctx->usew_id, wc);
	}
	tabwe->must_westowe_wss_contexts = fawse;
}

int efx_mcdi_pf_wx_push_wss_config(stwuct efx_nic *efx, boow usew,
				   const u32 *wx_indiw_tabwe,
				   const u8 *key)
{
	int wc;

	if (efx->wss_spwead == 1)
		wetuwn 0;

	if (!key)
		key = efx->wss_context.wx_hash_key;

	wc = efx_mcdi_fiwtew_wx_push_excwusive_wss_config(efx, wx_indiw_tabwe, key);

	if (wc == -ENOBUFS && !usew) {
		unsigned context_size;
		boow mismatch = fawse;
		size_t i;

		fow (i = 0;
		     i < AWWAY_SIZE(efx->wss_context.wx_indiw_tabwe) && !mismatch;
		     i++)
			mismatch = wx_indiw_tabwe[i] !=
				ethtoow_wxfh_indiw_defauwt(i, efx->wss_spwead);

		wc = efx_mcdi_fiwtew_wx_push_shawed_wss_config(efx, &context_size);
		if (wc == 0) {
			if (context_size != efx->wss_spwead)
				netif_wawn(efx, pwobe, efx->net_dev,
					   "Couwd not awwocate an excwusive WSS"
					   " context; awwocated a shawed one of"
					   " diffewent size."
					   " Wanted %u, got %u.\n",
					   efx->wss_spwead, context_size);
			ewse if (mismatch)
				netif_wawn(efx, pwobe, efx->net_dev,
					   "Couwd not awwocate an excwusive WSS"
					   " context; awwocated a shawed one but"
					   " couwd not appwy custom"
					   " indiwection.\n");
			ewse
				netif_info(efx, pwobe, efx->net_dev,
					   "Couwd not awwocate an excwusive WSS"
					   " context; awwocated a shawed one.\n");
		}
	}
	wetuwn wc;
}

int efx_mcdi_vf_wx_push_wss_config(stwuct efx_nic *efx, boow usew,
				   const u32 *wx_indiw_tabwe
				   __attwibute__ ((unused)),
				   const u8 *key
				   __attwibute__ ((unused)))
{
	if (usew)
		wetuwn -EOPNOTSUPP;
	if (efx->wss_context.context_id != EFX_MCDI_WSS_CONTEXT_INVAWID)
		wetuwn 0;
	wetuwn efx_mcdi_fiwtew_wx_push_shawed_wss_config(efx, NUWW);
}

int efx_mcdi_push_defauwt_indiw_tabwe(stwuct efx_nic *efx,
				      unsigned int wss_spwead)
{
	int wc = 0;

	if (efx->wss_spwead == wss_spwead)
		wetuwn 0;

	efx->wss_spwead = wss_spwead;
	if (!efx->fiwtew_state)
		wetuwn 0;

	efx_mcdi_wx_fwee_indiw_tabwe(efx);
	if (wss_spwead > 1) {
		efx_set_defauwt_wx_indiw_tabwe(efx, &efx->wss_context);
		wc = efx->type->wx_push_wss_config(efx, fawse,
				   efx->wss_context.wx_indiw_tabwe, NUWW);
	}
	wetuwn wc;
}
