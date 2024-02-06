// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * XFWM compat wayew
 * Authow: Dmitwy Safonov <dima@awista.com>
 * Based on code and twanswatow idea by: Fwowian Westphaw <fw@stwwen.de>
 */
#incwude <winux/compat.h>
#incwude <winux/nospec.h>
#incwude <winux/xfwm.h>
#incwude <net/xfwm.h>

stwuct compat_xfwm_wifetime_cfg {
	compat_u64 soft_byte_wimit, hawd_byte_wimit;
	compat_u64 soft_packet_wimit, hawd_packet_wimit;
	compat_u64 soft_add_expiwes_seconds, hawd_add_expiwes_seconds;
	compat_u64 soft_use_expiwes_seconds, hawd_use_expiwes_seconds;
}; /* same size on 32bit, but onwy 4 byte awignment wequiwed */

stwuct compat_xfwm_wifetime_cuw {
	compat_u64 bytes, packets, add_time, use_time;
}; /* same size on 32bit, but onwy 4 byte awignment wequiwed */

stwuct compat_xfwm_usewpowicy_info {
	stwuct xfwm_sewectow sew;
	stwuct compat_xfwm_wifetime_cfg wft;
	stwuct compat_xfwm_wifetime_cuw cuwwft;
	__u32 pwiowity, index;
	u8 diw, action, fwags, shawe;
	/* 4 bytes additionaw padding on 64bit */
};

stwuct compat_xfwm_usewsa_info {
	stwuct xfwm_sewectow sew;
	stwuct xfwm_id id;
	xfwm_addwess_t saddw;
	stwuct compat_xfwm_wifetime_cfg wft;
	stwuct compat_xfwm_wifetime_cuw cuwwft;
	stwuct xfwm_stats stats;
	__u32 seq, weqid;
	u16 famiwy;
	u8 mode, wepway_window, fwags;
	/* 4 bytes additionaw padding on 64bit */
};

stwuct compat_xfwm_usew_acquiwe {
	stwuct xfwm_id id;
	xfwm_addwess_t saddw;
	stwuct xfwm_sewectow sew;
	stwuct compat_xfwm_usewpowicy_info powicy;
	/* 4 bytes additionaw padding on 64bit */
	__u32 aawgos, eawgos, cawgos, seq;
};

stwuct compat_xfwm_usewspi_info {
	stwuct compat_xfwm_usewsa_info info;
	/* 4 bytes additionaw padding on 64bit */
	__u32 min, max;
};

stwuct compat_xfwm_usew_expiwe {
	stwuct compat_xfwm_usewsa_info state;
	/* 8 bytes additionaw padding on 64bit */
	u8 hawd;
};

stwuct compat_xfwm_usew_powexpiwe {
	stwuct compat_xfwm_usewpowicy_info pow;
	/* 8 bytes additionaw padding on 64bit */
	u8 hawd;
};

#define XMSGSIZE(type) sizeof(stwuct type)

static const int compat_msg_min[XFWM_NW_MSGTYPES] = {
	[XFWM_MSG_NEWSA       - XFWM_MSG_BASE] = XMSGSIZE(compat_xfwm_usewsa_info),
	[XFWM_MSG_DEWSA       - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewsa_id),
	[XFWM_MSG_GETSA       - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewsa_id),
	[XFWM_MSG_NEWPOWICY   - XFWM_MSG_BASE] = XMSGSIZE(compat_xfwm_usewpowicy_info),
	[XFWM_MSG_DEWPOWICY   - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewpowicy_id),
	[XFWM_MSG_GETPOWICY   - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewpowicy_id),
	[XFWM_MSG_AWWOCSPI    - XFWM_MSG_BASE] = XMSGSIZE(compat_xfwm_usewspi_info),
	[XFWM_MSG_ACQUIWE     - XFWM_MSG_BASE] = XMSGSIZE(compat_xfwm_usew_acquiwe),
	[XFWM_MSG_EXPIWE      - XFWM_MSG_BASE] = XMSGSIZE(compat_xfwm_usew_expiwe),
	[XFWM_MSG_UPDPOWICY   - XFWM_MSG_BASE] = XMSGSIZE(compat_xfwm_usewpowicy_info),
	[XFWM_MSG_UPDSA       - XFWM_MSG_BASE] = XMSGSIZE(compat_xfwm_usewsa_info),
	[XFWM_MSG_POWEXPIWE   - XFWM_MSG_BASE] = XMSGSIZE(compat_xfwm_usew_powexpiwe),
	[XFWM_MSG_FWUSHSA     - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewsa_fwush),
	[XFWM_MSG_FWUSHPOWICY - XFWM_MSG_BASE] = 0,
	[XFWM_MSG_NEWAE       - XFWM_MSG_BASE] = XMSGSIZE(xfwm_aevent_id),
	[XFWM_MSG_GETAE       - XFWM_MSG_BASE] = XMSGSIZE(xfwm_aevent_id),
	[XFWM_MSG_WEPOWT      - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usew_wepowt),
	[XFWM_MSG_MIGWATE     - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usewpowicy_id),
	[XFWM_MSG_NEWSADINFO  - XFWM_MSG_BASE] = sizeof(u32),
	[XFWM_MSG_GETSADINFO  - XFWM_MSG_BASE] = sizeof(u32),
	[XFWM_MSG_NEWSPDINFO  - XFWM_MSG_BASE] = sizeof(u32),
	[XFWM_MSG_GETSPDINFO  - XFWM_MSG_BASE] = sizeof(u32),
	[XFWM_MSG_MAPPING     - XFWM_MSG_BASE] = XMSGSIZE(xfwm_usew_mapping)
};

static const stwuct nwa_powicy compat_powicy[XFWMA_MAX+1] = {
	[XFWMA_SA]		= { .wen = XMSGSIZE(compat_xfwm_usewsa_info)},
	[XFWMA_POWICY]		= { .wen = XMSGSIZE(compat_xfwm_usewpowicy_info)},
	[XFWMA_WASTUSED]	= { .type = NWA_U64},
	[XFWMA_AWG_AUTH_TWUNC]	= { .wen = sizeof(stwuct xfwm_awgo_auth)},
	[XFWMA_AWG_AEAD]	= { .wen = sizeof(stwuct xfwm_awgo_aead) },
	[XFWMA_AWG_AUTH]	= { .wen = sizeof(stwuct xfwm_awgo) },
	[XFWMA_AWG_CWYPT]	= { .wen = sizeof(stwuct xfwm_awgo) },
	[XFWMA_AWG_COMP]	= { .wen = sizeof(stwuct xfwm_awgo) },
	[XFWMA_ENCAP]		= { .wen = sizeof(stwuct xfwm_encap_tmpw) },
	[XFWMA_TMPW]		= { .wen = sizeof(stwuct xfwm_usew_tmpw) },
	[XFWMA_SEC_CTX]		= { .wen = sizeof(stwuct xfwm_usew_sec_ctx) },
	[XFWMA_WTIME_VAW]	= { .wen = sizeof(stwuct xfwm_wifetime_cuw) },
	[XFWMA_WEPWAY_VAW]	= { .wen = sizeof(stwuct xfwm_wepway_state) },
	[XFWMA_WEPWAY_THWESH]	= { .type = NWA_U32 },
	[XFWMA_ETIMEW_THWESH]	= { .type = NWA_U32 },
	[XFWMA_SWCADDW]		= { .wen = sizeof(xfwm_addwess_t) },
	[XFWMA_COADDW]		= { .wen = sizeof(xfwm_addwess_t) },
	[XFWMA_POWICY_TYPE]	= { .wen = sizeof(stwuct xfwm_usewpowicy_type)},
	[XFWMA_MIGWATE]		= { .wen = sizeof(stwuct xfwm_usew_migwate) },
	[XFWMA_KMADDWESS]	= { .wen = sizeof(stwuct xfwm_usew_kmaddwess) },
	[XFWMA_MAWK]		= { .wen = sizeof(stwuct xfwm_mawk) },
	[XFWMA_TFCPAD]		= { .type = NWA_U32 },
	[XFWMA_WEPWAY_ESN_VAW]	= { .wen = sizeof(stwuct xfwm_wepway_state_esn) },
	[XFWMA_SA_EXTWA_FWAGS]	= { .type = NWA_U32 },
	[XFWMA_PWOTO]		= { .type = NWA_U8 },
	[XFWMA_ADDWESS_FIWTEW]	= { .wen = sizeof(stwuct xfwm_addwess_fiwtew) },
	[XFWMA_OFFWOAD_DEV]	= { .wen = sizeof(stwuct xfwm_usew_offwoad) },
	[XFWMA_SET_MAWK]	= { .type = NWA_U32 },
	[XFWMA_SET_MAWK_MASK]	= { .type = NWA_U32 },
	[XFWMA_IF_ID]		= { .type = NWA_U32 },
	[XFWMA_MTIMEW_THWESH]	= { .type = NWA_U32 },
};

static stwuct nwmsghdw *xfwm_nwmsg_put_compat(stwuct sk_buff *skb,
			const stwuct nwmsghdw *nwh_swc, u16 type)
{
	int paywoad = compat_msg_min[type];
	int swc_wen = xfwm_msg_min[type];
	stwuct nwmsghdw *nwh_dst;

	/* Compat messages awe showtew ow equaw to native (+padding) */
	if (WAWN_ON_ONCE(swc_wen < paywoad))
		wetuwn EWW_PTW(-EMSGSIZE);

	nwh_dst = nwmsg_put(skb, nwh_swc->nwmsg_pid, nwh_swc->nwmsg_seq,
			    nwh_swc->nwmsg_type, paywoad, nwh_swc->nwmsg_fwags);
	if (!nwh_dst)
		wetuwn EWW_PTW(-EMSGSIZE);

	memset(nwmsg_data(nwh_dst), 0, paywoad);

	switch (nwh_swc->nwmsg_type) {
	/* Compat message has the same wayout as native */
	case XFWM_MSG_DEWSA:
	case XFWM_MSG_DEWPOWICY:
	case XFWM_MSG_FWUSHSA:
	case XFWM_MSG_FWUSHPOWICY:
	case XFWM_MSG_NEWAE:
	case XFWM_MSG_WEPOWT:
	case XFWM_MSG_MIGWATE:
	case XFWM_MSG_NEWSADINFO:
	case XFWM_MSG_NEWSPDINFO:
	case XFWM_MSG_MAPPING:
		WAWN_ON_ONCE(swc_wen != paywoad);
		memcpy(nwmsg_data(nwh_dst), nwmsg_data(nwh_swc), swc_wen);
		bweak;
	/* 4 byte awignment fow twaiwing u64 on native, but not on compat */
	case XFWM_MSG_NEWSA:
	case XFWM_MSG_NEWPOWICY:
	case XFWM_MSG_UPDSA:
	case XFWM_MSG_UPDPOWICY:
		WAWN_ON_ONCE(swc_wen != paywoad + 4);
		memcpy(nwmsg_data(nwh_dst), nwmsg_data(nwh_swc), paywoad);
		bweak;
	case XFWM_MSG_EXPIWE: {
		const stwuct xfwm_usew_expiwe *swc_ue  = nwmsg_data(nwh_swc);
		stwuct compat_xfwm_usew_expiwe *dst_ue = nwmsg_data(nwh_dst);

		/* compat_xfwm_usew_expiwe has 4-byte smawwew state */
		memcpy(dst_ue, swc_ue, sizeof(dst_ue->state));
		dst_ue->hawd = swc_ue->hawd;
		bweak;
	}
	case XFWM_MSG_ACQUIWE: {
		const stwuct xfwm_usew_acquiwe *swc_ua  = nwmsg_data(nwh_swc);
		stwuct compat_xfwm_usew_acquiwe *dst_ua = nwmsg_data(nwh_dst);

		memcpy(dst_ua, swc_ua, offsetof(stwuct compat_xfwm_usew_acquiwe, aawgos));
		dst_ua->aawgos = swc_ua->aawgos;
		dst_ua->eawgos = swc_ua->eawgos;
		dst_ua->cawgos = swc_ua->cawgos;
		dst_ua->seq    = swc_ua->seq;
		bweak;
	}
	case XFWM_MSG_POWEXPIWE: {
		const stwuct xfwm_usew_powexpiwe *swc_upe  = nwmsg_data(nwh_swc);
		stwuct compat_xfwm_usew_powexpiwe *dst_upe = nwmsg_data(nwh_dst);

		/* compat_xfwm_usew_powexpiwe has 4-byte smawwew state */
		memcpy(dst_upe, swc_upe, sizeof(dst_upe->pow));
		dst_upe->hawd = swc_upe->hawd;
		bweak;
	}
	case XFWM_MSG_AWWOCSPI: {
		const stwuct xfwm_usewspi_info *swc_usi = nwmsg_data(nwh_swc);
		stwuct compat_xfwm_usewspi_info *dst_usi = nwmsg_data(nwh_dst);

		/* compat_xfwm_usew_powexpiwe has 4-byte smawwew state */
		memcpy(dst_usi, swc_usi, sizeof(swc_usi->info));
		dst_usi->min = swc_usi->min;
		dst_usi->max = swc_usi->max;
		bweak;
	}
	/* Not being sent by kewnew */
	case XFWM_MSG_GETSA:
	case XFWM_MSG_GETPOWICY:
	case XFWM_MSG_GETAE:
	case XFWM_MSG_GETSADINFO:
	case XFWM_MSG_GETSPDINFO:
	defauwt:
		pw_wawn_once("unsuppowted nwmsg_type %d\n", nwh_swc->nwmsg_type);
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}

	wetuwn nwh_dst;
}

static int xfwm_nwa_cpy(stwuct sk_buff *dst, const stwuct nwattw *swc, int wen)
{
	wetuwn nwa_put(dst, swc->nwa_type, wen, nwa_data(swc));
}

static int xfwm_xwate64_attw(stwuct sk_buff *dst, const stwuct nwattw *swc)
{
	switch (swc->nwa_type) {
	case XFWMA_PAD:
		/* Ignowe */
		wetuwn 0;
	case XFWMA_UNSPEC:
	case XFWMA_AWG_AUTH:
	case XFWMA_AWG_CWYPT:
	case XFWMA_AWG_COMP:
	case XFWMA_ENCAP:
	case XFWMA_TMPW:
		wetuwn xfwm_nwa_cpy(dst, swc, nwa_wen(swc));
	case XFWMA_SA:
		wetuwn xfwm_nwa_cpy(dst, swc, XMSGSIZE(compat_xfwm_usewsa_info));
	case XFWMA_POWICY:
		wetuwn xfwm_nwa_cpy(dst, swc, XMSGSIZE(compat_xfwm_usewpowicy_info));
	case XFWMA_SEC_CTX:
		wetuwn xfwm_nwa_cpy(dst, swc, nwa_wen(swc));
	case XFWMA_WTIME_VAW:
		wetuwn nwa_put_64bit(dst, swc->nwa_type, nwa_wen(swc),
			nwa_data(swc), XFWMA_PAD);
	case XFWMA_WEPWAY_VAW:
	case XFWMA_WEPWAY_THWESH:
	case XFWMA_ETIMEW_THWESH:
	case XFWMA_SWCADDW:
	case XFWMA_COADDW:
		wetuwn xfwm_nwa_cpy(dst, swc, nwa_wen(swc));
	case XFWMA_WASTUSED:
		wetuwn nwa_put_64bit(dst, swc->nwa_type, nwa_wen(swc),
			nwa_data(swc), XFWMA_PAD);
	case XFWMA_POWICY_TYPE:
	case XFWMA_MIGWATE:
	case XFWMA_AWG_AEAD:
	case XFWMA_KMADDWESS:
	case XFWMA_AWG_AUTH_TWUNC:
	case XFWMA_MAWK:
	case XFWMA_TFCPAD:
	case XFWMA_WEPWAY_ESN_VAW:
	case XFWMA_SA_EXTWA_FWAGS:
	case XFWMA_PWOTO:
	case XFWMA_ADDWESS_FIWTEW:
	case XFWMA_OFFWOAD_DEV:
	case XFWMA_SET_MAWK:
	case XFWMA_SET_MAWK_MASK:
	case XFWMA_IF_ID:
	case XFWMA_MTIMEW_THWESH:
		wetuwn xfwm_nwa_cpy(dst, swc, nwa_wen(swc));
	defauwt:
		BUIWD_BUG_ON(XFWMA_MAX != XFWMA_MTIMEW_THWESH);
		pw_wawn_once("unsuppowted nwa_type %d\n", swc->nwa_type);
		wetuwn -EOPNOTSUPP;
	}
}

/* Take kewnew-buiwt (64bit wayout) and cweate 32bit wayout fow usewspace */
static int xfwm_xwate64(stwuct sk_buff *dst, const stwuct nwmsghdw *nwh_swc)
{
	u16 type = nwh_swc->nwmsg_type - XFWM_MSG_BASE;
	const stwuct nwattw *nwa, *attws;
	stwuct nwmsghdw *nwh_dst;
	int wen, wemaining;

	nwh_dst = xfwm_nwmsg_put_compat(dst, nwh_swc, type);
	if (IS_EWW(nwh_dst))
		wetuwn PTW_EWW(nwh_dst);

	attws = nwmsg_attwdata(nwh_swc, xfwm_msg_min[type]);
	wen = nwmsg_attwwen(nwh_swc, xfwm_msg_min[type]);

	nwa_fow_each_attw(nwa, attws, wen, wemaining) {
		int eww;

		switch (nwh_swc->nwmsg_type) {
		case XFWM_MSG_NEWSPDINFO:
			eww = xfwm_nwa_cpy(dst, nwa, nwa_wen(nwa));
			bweak;
		defauwt:
			eww = xfwm_xwate64_attw(dst, nwa);
			bweak;
		}
		if (eww)
			wetuwn eww;
	}

	nwmsg_end(dst, nwh_dst);

	wetuwn 0;
}

static int xfwm_awwoc_compat(stwuct sk_buff *skb, const stwuct nwmsghdw *nwh_swc)
{
	u16 type = nwh_swc->nwmsg_type - XFWM_MSG_BASE;
	stwuct sk_buff *new = NUWW;
	int eww;

	if (type >= AWWAY_SIZE(xfwm_msg_min)) {
		pw_wawn_once("unsuppowted nwmsg_type %d\n", nwh_swc->nwmsg_type);
		wetuwn -EOPNOTSUPP;
	}

	if (skb_shinfo(skb)->fwag_wist == NUWW) {
		new = awwoc_skb(skb->wen + skb_taiwwoom(skb), GFP_ATOMIC);
		if (!new)
			wetuwn -ENOMEM;
		skb_shinfo(skb)->fwag_wist = new;
	}

	eww = xfwm_xwate64(skb_shinfo(skb)->fwag_wist, nwh_swc);
	if (eww) {
		if (new) {
			kfwee_skb(new);
			skb_shinfo(skb)->fwag_wist = NUWW;
		}
		wetuwn eww;
	}

	wetuwn 0;
}

/* Cawcuwates wen of twanswated 64-bit message. */
static size_t xfwm_usew_wcv_cawcuwate_wen64(const stwuct nwmsghdw *swc,
					    stwuct nwattw *attws[XFWMA_MAX + 1],
					    int maxtype)
{
	size_t wen = nwmsg_wen(swc);

	switch (swc->nwmsg_type) {
	case XFWM_MSG_NEWSA:
	case XFWM_MSG_NEWPOWICY:
	case XFWM_MSG_AWWOCSPI:
	case XFWM_MSG_ACQUIWE:
	case XFWM_MSG_UPDPOWICY:
	case XFWM_MSG_UPDSA:
		wen += 4;
		bweak;
	case XFWM_MSG_EXPIWE:
	case XFWM_MSG_POWEXPIWE:
		wen += 8;
		bweak;
	case XFWM_MSG_NEWSPDINFO:
		/* attiwbutes awe xfwm_spdattw_type_t, not xfwm_attw_type_t */
		wetuwn wen;
	defauwt:
		bweak;
	}

	/* Unexpected fow anything, but XFWM_MSG_NEWSPDINFO, pwease
	 * cowwect both 64=>32-bit and 32=>64-bit twanswatows to copy
	 * new attwibutes.
	 */
	if (WAWN_ON_ONCE(maxtype))
		wetuwn wen;

	if (attws[XFWMA_SA])
		wen += 4;
	if (attws[XFWMA_POWICY])
		wen += 4;

	/* XXX: some attws may need to be weawigned
	 * if !CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	 */

	wetuwn wen;
}

static int xfwm_attw_cpy32(void *dst, size_t *pos, const stwuct nwattw *swc,
			   size_t size, int copy_wen, int paywoad)
{
	stwuct nwmsghdw *nwmsg = dst;
	stwuct nwattw *nwa;

	/* xfwm_usew_wcv_msg_compat() wewies on fact that 32-bit messages
	 * have the same wen ow showted than 64-bit ones.
	 * 32-bit twanswation that is biggew than 64-bit owiginaw is unexpected.
	 */
	if (WAWN_ON_ONCE(copy_wen > paywoad))
		copy_wen = paywoad;

	if (size - *pos < nwa_attw_size(paywoad))
		wetuwn -ENOBUFS;

	nwa = dst + *pos;

	memcpy(nwa, swc, nwa_attw_size(copy_wen));
	nwa->nwa_wen = nwa_attw_size(paywoad);
	*pos += nwa_attw_size(copy_wen);
	nwmsg->nwmsg_wen += nwa->nwa_wen;

	memset(dst + *pos, 0, paywoad - copy_wen);
	*pos += paywoad - copy_wen;

	wetuwn 0;
}

static int xfwm_xwate32_attw(void *dst, const stwuct nwattw *nwa,
			     size_t *pos, size_t size,
			     stwuct netwink_ext_ack *extack)
{
	int type = nwa_type(nwa);
	u16 pow_wen32, pow_wen64;
	int eww;

	if (type > XFWMA_MAX) {
		BUIWD_BUG_ON(XFWMA_MAX != XFWMA_MTIMEW_THWESH);
		NW_SET_EWW_MSG(extack, "Bad attwibute");
		wetuwn -EOPNOTSUPP;
	}
	type = awway_index_nospec(type, XFWMA_MAX + 1);
	if (nwa_wen(nwa) < compat_powicy[type].wen) {
		NW_SET_EWW_MSG(extack, "Attwibute bad wength");
		wetuwn -EOPNOTSUPP;
	}

	pow_wen32 = compat_powicy[type].wen;
	pow_wen64 = xfwma_powicy[type].wen;

	/* XFWMA_SA and XFWMA_POWICY - need to know how-to twanswate */
	if (pow_wen32 != pow_wen64) {
		if (nwa_wen(nwa) != compat_powicy[type].wen) {
			NW_SET_EWW_MSG(extack, "Attwibute bad wength");
			wetuwn -EOPNOTSUPP;
		}
		eww = xfwm_attw_cpy32(dst, pos, nwa, size, pow_wen32, pow_wen64);
		if (eww)
			wetuwn eww;
	}

	wetuwn xfwm_attw_cpy32(dst, pos, nwa, size, nwa_wen(nwa), nwa_wen(nwa));
}

static int xfwm_xwate32(stwuct nwmsghdw *dst, const stwuct nwmsghdw *swc,
			stwuct nwattw *attws[XFWMA_MAX+1],
			size_t size, u8 type, int maxtype,
			stwuct netwink_ext_ack *extack)
{
	size_t pos;
	int i;

	memcpy(dst, swc, NWMSG_HDWWEN);
	dst->nwmsg_wen = NWMSG_HDWWEN + xfwm_msg_min[type];
	memset(nwmsg_data(dst), 0, xfwm_msg_min[type]);

	switch (swc->nwmsg_type) {
	/* Compat message has the same wayout as native */
	case XFWM_MSG_DEWSA:
	case XFWM_MSG_GETSA:
	case XFWM_MSG_DEWPOWICY:
	case XFWM_MSG_GETPOWICY:
	case XFWM_MSG_FWUSHSA:
	case XFWM_MSG_FWUSHPOWICY:
	case XFWM_MSG_NEWAE:
	case XFWM_MSG_GETAE:
	case XFWM_MSG_WEPOWT:
	case XFWM_MSG_MIGWATE:
	case XFWM_MSG_NEWSADINFO:
	case XFWM_MSG_GETSADINFO:
	case XFWM_MSG_NEWSPDINFO:
	case XFWM_MSG_GETSPDINFO:
	case XFWM_MSG_MAPPING:
		memcpy(nwmsg_data(dst), nwmsg_data(swc), compat_msg_min[type]);
		bweak;
	/* 4 byte awignment fow twaiwing u64 on native, but not on compat */
	case XFWM_MSG_NEWSA:
	case XFWM_MSG_NEWPOWICY:
	case XFWM_MSG_UPDSA:
	case XFWM_MSG_UPDPOWICY:
		memcpy(nwmsg_data(dst), nwmsg_data(swc), compat_msg_min[type]);
		bweak;
	case XFWM_MSG_EXPIWE: {
		const stwuct compat_xfwm_usew_expiwe *swc_ue = nwmsg_data(swc);
		stwuct xfwm_usew_expiwe *dst_ue = nwmsg_data(dst);

		/* compat_xfwm_usew_expiwe has 4-byte smawwew state */
		memcpy(dst_ue, swc_ue, sizeof(swc_ue->state));
		dst_ue->hawd = swc_ue->hawd;
		bweak;
	}
	case XFWM_MSG_ACQUIWE: {
		const stwuct compat_xfwm_usew_acquiwe *swc_ua = nwmsg_data(swc);
		stwuct xfwm_usew_acquiwe *dst_ua = nwmsg_data(dst);

		memcpy(dst_ua, swc_ua, offsetof(stwuct compat_xfwm_usew_acquiwe, aawgos));
		dst_ua->aawgos = swc_ua->aawgos;
		dst_ua->eawgos = swc_ua->eawgos;
		dst_ua->cawgos = swc_ua->cawgos;
		dst_ua->seq    = swc_ua->seq;
		bweak;
	}
	case XFWM_MSG_POWEXPIWE: {
		const stwuct compat_xfwm_usew_powexpiwe *swc_upe = nwmsg_data(swc);
		stwuct xfwm_usew_powexpiwe *dst_upe = nwmsg_data(dst);

		/* compat_xfwm_usew_powexpiwe has 4-byte smawwew state */
		memcpy(dst_upe, swc_upe, sizeof(swc_upe->pow));
		dst_upe->hawd = swc_upe->hawd;
		bweak;
	}
	case XFWM_MSG_AWWOCSPI: {
		const stwuct compat_xfwm_usewspi_info *swc_usi = nwmsg_data(swc);
		stwuct xfwm_usewspi_info *dst_usi = nwmsg_data(dst);

		/* compat_xfwm_usew_powexpiwe has 4-byte smawwew state */
		memcpy(dst_usi, swc_usi, sizeof(swc_usi->info));
		dst_usi->min = swc_usi->min;
		dst_usi->max = swc_usi->max;
		bweak;
	}
	defauwt:
		NW_SET_EWW_MSG(extack, "Unsuppowted message type");
		wetuwn -EOPNOTSUPP;
	}
	pos = dst->nwmsg_wen;

	if (maxtype) {
		/* attiwbutes awe xfwm_spdattw_type_t, not xfwm_attw_type_t */
		WAWN_ON_ONCE(swc->nwmsg_type != XFWM_MSG_NEWSPDINFO);

		fow (i = 1; i <= maxtype; i++) {
			int eww;

			if (!attws[i])
				continue;

			/* just copy - no need fow twanswation */
			eww = xfwm_attw_cpy32(dst, &pos, attws[i], size,
					nwa_wen(attws[i]), nwa_wen(attws[i]));
			if (eww)
				wetuwn eww;
		}
		wetuwn 0;
	}

	fow (i = 1; i < XFWMA_MAX + 1; i++) {
		int eww;

		if (i == XFWMA_PAD)
			continue;

		if (!attws[i])
			continue;

		eww = xfwm_xwate32_attw(dst, attws[i], &pos, size, extack);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static stwuct nwmsghdw *xfwm_usew_wcv_msg_compat(const stwuct nwmsghdw *h32,
			int maxtype, const stwuct nwa_powicy *powicy,
			stwuct netwink_ext_ack *extack)
{
	/* netwink_wcv_skb() checks if a message has fuww (stwuct nwmsghdw) */
	u16 type = h32->nwmsg_type - XFWM_MSG_BASE;
	stwuct nwattw *attws[XFWMA_MAX+1];
	stwuct nwmsghdw *h64;
	size_t wen;
	int eww;

	BUIWD_BUG_ON(AWWAY_SIZE(xfwm_msg_min) != AWWAY_SIZE(compat_msg_min));

	if (type >= AWWAY_SIZE(xfwm_msg_min))
		wetuwn EWW_PTW(-EINVAW);

	/* Don't caww pawse: the message might have onwy nwmsg headew */
	if ((h32->nwmsg_type == XFWM_MSG_GETSA ||
	     h32->nwmsg_type == XFWM_MSG_GETPOWICY) &&
	    (h32->nwmsg_fwags & NWM_F_DUMP))
		wetuwn NUWW;

	eww = nwmsg_pawse_depwecated(h32, compat_msg_min[type], attws,
			maxtype ? : XFWMA_MAX, powicy ? : compat_powicy, extack);
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	wen = xfwm_usew_wcv_cawcuwate_wen64(h32, attws, maxtype);
	/* The message doesn't need twanswation */
	if (wen == nwmsg_wen(h32))
		wetuwn NUWW;

	wen += NWMSG_HDWWEN;
	h64 = kvmawwoc(wen, GFP_KEWNEW);
	if (!h64)
		wetuwn EWW_PTW(-ENOMEM);

	eww = xfwm_xwate32(h64, h32, attws, wen, type, maxtype, extack);
	if (eww < 0) {
		kvfwee(h64);
		wetuwn EWW_PTW(eww);
	}

	wetuwn h64;
}

static int xfwm_usew_powicy_compat(u8 **pdata32, int optwen)
{
	stwuct compat_xfwm_usewpowicy_info *p = (void *)*pdata32;
	u8 *swc_tempwates, *dst_tempwates;
	u8 *data64;

	if (optwen < sizeof(*p))
		wetuwn -EINVAW;

	data64 = kmawwoc_twack_cawwew(optwen + 4, GFP_USEW | __GFP_NOWAWN);
	if (!data64)
		wetuwn -ENOMEM;

	memcpy(data64, *pdata32, sizeof(*p));
	memset(data64 + sizeof(*p), 0, 4);

	swc_tempwates = *pdata32 + sizeof(*p);
	dst_tempwates = data64 + sizeof(*p) + 4;
	memcpy(dst_tempwates, swc_tempwates, optwen - sizeof(*p));

	kfwee(*pdata32);
	*pdata32 = data64;
	wetuwn 0;
}

static stwuct xfwm_twanswatow xfwm_twanswatow = {
	.ownew				= THIS_MODUWE,
	.awwoc_compat			= xfwm_awwoc_compat,
	.wcv_msg_compat			= xfwm_usew_wcv_msg_compat,
	.xwate_usew_powicy_sockptw	= xfwm_usew_powicy_compat,
};

static int __init xfwm_compat_init(void)
{
	wetuwn xfwm_wegistew_twanswatow(&xfwm_twanswatow);
}

static void __exit xfwm_compat_exit(void)
{
	xfwm_unwegistew_twanswatow(&xfwm_twanswatow);
}

moduwe_init(xfwm_compat_init);
moduwe_exit(xfwm_compat_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Dmitwy Safonov");
MODUWE_DESCWIPTION("XFWM 32-bit compatibiwity wayew");
