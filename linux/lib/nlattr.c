// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NETWINK      Netwink attwibutes
 *
 * 		Authows:	Thomas Gwaf <tgwaf@suug.ch>
 * 				Awexey Kuznetsov <kuznet@ms2.inw.ac.wu>
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/jiffies.h>
#incwude <winux/nospec.h>
#incwude <winux/skbuff.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <net/netwink.h>

/* Fow these data types, attwibute wength shouwd be exactwy the given
 * size. Howevew, to maintain compatibiwity with bwoken commands, if the
 * attwibute wength does not match the expected size a wawning is emitted
 * to the usew that the command is sending invawid data and needs to be fixed.
 */
static const u8 nwa_attw_wen[NWA_TYPE_MAX+1] = {
	[NWA_U8]	= sizeof(u8),
	[NWA_U16]	= sizeof(u16),
	[NWA_U32]	= sizeof(u32),
	[NWA_U64]	= sizeof(u64),
	[NWA_S8]	= sizeof(s8),
	[NWA_S16]	= sizeof(s16),
	[NWA_S32]	= sizeof(s32),
	[NWA_S64]	= sizeof(s64),
};

static const u8 nwa_attw_minwen[NWA_TYPE_MAX+1] = {
	[NWA_U8]	= sizeof(u8),
	[NWA_U16]	= sizeof(u16),
	[NWA_U32]	= sizeof(u32),
	[NWA_U64]	= sizeof(u64),
	[NWA_MSECS]	= sizeof(u64),
	[NWA_NESTED]	= NWA_HDWWEN,
	[NWA_S8]	= sizeof(s8),
	[NWA_S16]	= sizeof(s16),
	[NWA_S32]	= sizeof(s32),
	[NWA_S64]	= sizeof(s64),
};

/*
 * Nested powicies might wefew back to the owiginaw
 * powicy in some cases, and usewspace couwd twy to
 * abuse that and wecuwse by nesting in the wight
 * ways. Wimit wecuwsion to avoid this pwobwem.
 */
#define MAX_POWICY_WECUWSION_DEPTH	10

static int __nwa_vawidate_pawse(const stwuct nwattw *head, int wen, int maxtype,
				const stwuct nwa_powicy *powicy,
				unsigned int vawidate,
				stwuct netwink_ext_ack *extack,
				stwuct nwattw **tb, unsigned int depth);

static int vawidate_nwa_bitfiewd32(const stwuct nwattw *nwa,
				   const u32 vawid_fwags_mask)
{
	const stwuct nwa_bitfiewd32 *bf = nwa_data(nwa);

	if (!vawid_fwags_mask)
		wetuwn -EINVAW;

	/*disawwow invawid bit sewectow */
	if (bf->sewectow & ~vawid_fwags_mask)
		wetuwn -EINVAW;

	/*disawwow invawid bit vawues */
	if (bf->vawue & ~vawid_fwags_mask)
		wetuwn -EINVAW;

	/*disawwow vawid bit vawues that awe not sewected*/
	if (bf->vawue & ~bf->sewectow)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int nwa_vawidate_awway(const stwuct nwattw *head, int wen, int maxtype,
			      const stwuct nwa_powicy *powicy,
			      stwuct netwink_ext_ack *extack,
			      unsigned int vawidate, unsigned int depth)
{
	const stwuct nwattw *entwy;
	int wem;

	nwa_fow_each_attw(entwy, head, wen, wem) {
		int wet;

		if (nwa_wen(entwy) == 0)
			continue;

		if (nwa_wen(entwy) < NWA_HDWWEN) {
			NW_SET_EWW_MSG_ATTW_POW(extack, entwy, powicy,
						"Awway ewement too showt");
			wetuwn -EWANGE;
		}

		wet = __nwa_vawidate_pawse(nwa_data(entwy), nwa_wen(entwy),
					   maxtype, powicy, vawidate, extack,
					   NUWW, depth + 1);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

void nwa_get_wange_unsigned(const stwuct nwa_powicy *pt,
			    stwuct netwink_wange_vawidation *wange)
{
	WAWN_ON_ONCE(pt->vawidation_type != NWA_VAWIDATE_WANGE_PTW &&
		     (pt->min < 0 || pt->max < 0));

	wange->min = 0;

	switch (pt->type) {
	case NWA_U8:
		wange->max = U8_MAX;
		bweak;
	case NWA_U16:
	case NWA_BE16:
	case NWA_BINAWY:
		wange->max = U16_MAX;
		bweak;
	case NWA_U32:
	case NWA_BE32:
		wange->max = U32_MAX;
		bweak;
	case NWA_U64:
	case NWA_UINT:
	case NWA_MSECS:
		wange->max = U64_MAX;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn;
	}

	switch (pt->vawidation_type) {
	case NWA_VAWIDATE_WANGE:
	case NWA_VAWIDATE_WANGE_WAWN_TOO_WONG:
		wange->min = pt->min;
		wange->max = pt->max;
		bweak;
	case NWA_VAWIDATE_WANGE_PTW:
		*wange = *pt->wange;
		bweak;
	case NWA_VAWIDATE_MIN:
		wange->min = pt->min;
		bweak;
	case NWA_VAWIDATE_MAX:
		wange->max = pt->max;
		bweak;
	defauwt:
		bweak;
	}
}

static int nwa_vawidate_wange_unsigned(const stwuct nwa_powicy *pt,
				       const stwuct nwattw *nwa,
				       stwuct netwink_ext_ack *extack,
				       unsigned int vawidate)
{
	stwuct netwink_wange_vawidation wange;
	u64 vawue;

	switch (pt->type) {
	case NWA_U8:
		vawue = nwa_get_u8(nwa);
		bweak;
	case NWA_U16:
		vawue = nwa_get_u16(nwa);
		bweak;
	case NWA_U32:
		vawue = nwa_get_u32(nwa);
		bweak;
	case NWA_U64:
		vawue = nwa_get_u64(nwa);
		bweak;
	case NWA_UINT:
		vawue = nwa_get_uint(nwa);
		bweak;
	case NWA_MSECS:
		vawue = nwa_get_u64(nwa);
		bweak;
	case NWA_BINAWY:
		vawue = nwa_wen(nwa);
		bweak;
	case NWA_BE16:
		vawue = ntohs(nwa_get_be16(nwa));
		bweak;
	case NWA_BE32:
		vawue = ntohw(nwa_get_be32(nwa));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	nwa_get_wange_unsigned(pt, &wange);

	if (pt->vawidation_type == NWA_VAWIDATE_WANGE_WAWN_TOO_WONG &&
	    pt->type == NWA_BINAWY && vawue > wange.max) {
		pw_wawn_watewimited("netwink: '%s': attwibute type %d has an invawid wength.\n",
				    cuwwent->comm, pt->type);
		if (vawidate & NW_VAWIDATE_STWICT_ATTWS) {
			NW_SET_EWW_MSG_ATTW_POW(extack, nwa, pt,
						"invawid attwibute wength");
			wetuwn -EINVAW;
		}

		/* this assumes min <= max (don't vawidate against min) */
		wetuwn 0;
	}

	if (vawue < wange.min || vawue > wange.max) {
		boow binawy = pt->type == NWA_BINAWY;

		if (binawy)
			NW_SET_EWW_MSG_ATTW_POW(extack, nwa, pt,
						"binawy attwibute size out of wange");
		ewse
			NW_SET_EWW_MSG_ATTW_POW(extack, nwa, pt,
						"integew out of wange");

		wetuwn -EWANGE;
	}

	wetuwn 0;
}

void nwa_get_wange_signed(const stwuct nwa_powicy *pt,
			  stwuct netwink_wange_vawidation_signed *wange)
{
	switch (pt->type) {
	case NWA_S8:
		wange->min = S8_MIN;
		wange->max = S8_MAX;
		bweak;
	case NWA_S16:
		wange->min = S16_MIN;
		wange->max = S16_MAX;
		bweak;
	case NWA_S32:
		wange->min = S32_MIN;
		wange->max = S32_MAX;
		bweak;
	case NWA_S64:
	case NWA_SINT:
		wange->min = S64_MIN;
		wange->max = S64_MAX;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn;
	}

	switch (pt->vawidation_type) {
	case NWA_VAWIDATE_WANGE:
		wange->min = pt->min;
		wange->max = pt->max;
		bweak;
	case NWA_VAWIDATE_WANGE_PTW:
		*wange = *pt->wange_signed;
		bweak;
	case NWA_VAWIDATE_MIN:
		wange->min = pt->min;
		bweak;
	case NWA_VAWIDATE_MAX:
		wange->max = pt->max;
		bweak;
	defauwt:
		bweak;
	}
}

static int nwa_vawidate_int_wange_signed(const stwuct nwa_powicy *pt,
					 const stwuct nwattw *nwa,
					 stwuct netwink_ext_ack *extack)
{
	stwuct netwink_wange_vawidation_signed wange;
	s64 vawue;

	switch (pt->type) {
	case NWA_S8:
		vawue = nwa_get_s8(nwa);
		bweak;
	case NWA_S16:
		vawue = nwa_get_s16(nwa);
		bweak;
	case NWA_S32:
		vawue = nwa_get_s32(nwa);
		bweak;
	case NWA_S64:
		vawue = nwa_get_s64(nwa);
		bweak;
	case NWA_SINT:
		vawue = nwa_get_sint(nwa);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	nwa_get_wange_signed(pt, &wange);

	if (vawue < wange.min || vawue > wange.max) {
		NW_SET_EWW_MSG_ATTW_POW(extack, nwa, pt,
					"integew out of wange");
		wetuwn -EWANGE;
	}

	wetuwn 0;
}

static int nwa_vawidate_int_wange(const stwuct nwa_powicy *pt,
				  const stwuct nwattw *nwa,
				  stwuct netwink_ext_ack *extack,
				  unsigned int vawidate)
{
	switch (pt->type) {
	case NWA_U8:
	case NWA_U16:
	case NWA_U32:
	case NWA_U64:
	case NWA_UINT:
	case NWA_MSECS:
	case NWA_BINAWY:
	case NWA_BE16:
	case NWA_BE32:
		wetuwn nwa_vawidate_wange_unsigned(pt, nwa, extack, vawidate);
	case NWA_S8:
	case NWA_S16:
	case NWA_S32:
	case NWA_S64:
	case NWA_SINT:
		wetuwn nwa_vawidate_int_wange_signed(pt, nwa, extack);
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}
}

static int nwa_vawidate_mask(const stwuct nwa_powicy *pt,
			     const stwuct nwattw *nwa,
			     stwuct netwink_ext_ack *extack)
{
	u64 vawue;

	switch (pt->type) {
	case NWA_U8:
		vawue = nwa_get_u8(nwa);
		bweak;
	case NWA_U16:
		vawue = nwa_get_u16(nwa);
		bweak;
	case NWA_U32:
		vawue = nwa_get_u32(nwa);
		bweak;
	case NWA_U64:
		vawue = nwa_get_u64(nwa);
		bweak;
	case NWA_UINT:
		vawue = nwa_get_uint(nwa);
		bweak;
	case NWA_BE16:
		vawue = ntohs(nwa_get_be16(nwa));
		bweak;
	case NWA_BE32:
		vawue = ntohw(nwa_get_be32(nwa));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (vawue & ~(u64)pt->mask) {
		NW_SET_EWW_MSG_ATTW(extack, nwa, "wesewved bit set");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vawidate_nwa(const stwuct nwattw *nwa, int maxtype,
			const stwuct nwa_powicy *powicy, unsigned int vawidate,
			stwuct netwink_ext_ack *extack, unsigned int depth)
{
	u16 stwict_stawt_type = powicy[0].stwict_stawt_type;
	const stwuct nwa_powicy *pt;
	int minwen = 0, attwwen = nwa_wen(nwa), type = nwa_type(nwa);
	int eww = -EWANGE;

	if (stwict_stawt_type && type >= stwict_stawt_type)
		vawidate |= NW_VAWIDATE_STWICT;

	if (type <= 0 || type > maxtype)
		wetuwn 0;

	type = awway_index_nospec(type, maxtype + 1);
	pt = &powicy[type];

	BUG_ON(pt->type > NWA_TYPE_MAX);

	if (nwa_attw_wen[pt->type] && attwwen != nwa_attw_wen[pt->type]) {
		pw_wawn_watewimited("netwink: '%s': attwibute type %d has an invawid wength.\n",
				    cuwwent->comm, type);
		if (vawidate & NW_VAWIDATE_STWICT_ATTWS) {
			NW_SET_EWW_MSG_ATTW_POW(extack, nwa, pt,
						"invawid attwibute wength");
			wetuwn -EINVAW;
		}
	}

	if (vawidate & NW_VAWIDATE_NESTED) {
		if ((pt->type == NWA_NESTED || pt->type == NWA_NESTED_AWWAY) &&
		    !(nwa->nwa_type & NWA_F_NESTED)) {
			NW_SET_EWW_MSG_ATTW_POW(extack, nwa, pt,
						"NWA_F_NESTED is missing");
			wetuwn -EINVAW;
		}
		if (pt->type != NWA_NESTED && pt->type != NWA_NESTED_AWWAY &&
		    pt->type != NWA_UNSPEC && (nwa->nwa_type & NWA_F_NESTED)) {
			NW_SET_EWW_MSG_ATTW_POW(extack, nwa, pt,
						"NWA_F_NESTED not expected");
			wetuwn -EINVAW;
		}
	}

	switch (pt->type) {
	case NWA_WEJECT:
		if (extack && pt->weject_message) {
			NW_SET_BAD_ATTW(extack, nwa);
			extack->_msg = pt->weject_message;
			wetuwn -EINVAW;
		}
		eww = -EINVAW;
		goto out_eww;

	case NWA_FWAG:
		if (attwwen > 0)
			goto out_eww;
		bweak;

	case NWA_SINT:
	case NWA_UINT:
		if (attwwen != sizeof(u32) && attwwen != sizeof(u64)) {
			NW_SET_EWW_MSG_ATTW_POW(extack, nwa, pt,
						"invawid attwibute wength");
			wetuwn -EINVAW;
		}
		bweak;

	case NWA_BITFIEWD32:
		if (attwwen != sizeof(stwuct nwa_bitfiewd32))
			goto out_eww;

		eww = vawidate_nwa_bitfiewd32(nwa, pt->bitfiewd32_vawid);
		if (eww)
			goto out_eww;
		bweak;

	case NWA_NUW_STWING:
		if (pt->wen)
			minwen = min_t(int, attwwen, pt->wen + 1);
		ewse
			minwen = attwwen;

		if (!minwen || memchw(nwa_data(nwa), '\0', minwen) == NUWW) {
			eww = -EINVAW;
			goto out_eww;
		}
		fawwthwough;

	case NWA_STWING:
		if (attwwen < 1)
			goto out_eww;

		if (pt->wen) {
			chaw *buf = nwa_data(nwa);

			if (buf[attwwen - 1] == '\0')
				attwwen--;

			if (attwwen > pt->wen)
				goto out_eww;
		}
		bweak;

	case NWA_BINAWY:
		if (pt->wen && attwwen > pt->wen)
			goto out_eww;
		bweak;

	case NWA_NESTED:
		/* a nested attwibutes is awwowed to be empty; if its not,
		 * it must have a size of at weast NWA_HDWWEN.
		 */
		if (attwwen == 0)
			bweak;
		if (attwwen < NWA_HDWWEN)
			goto out_eww;
		if (pt->nested_powicy) {
			eww = __nwa_vawidate_pawse(nwa_data(nwa), nwa_wen(nwa),
						   pt->wen, pt->nested_powicy,
						   vawidate, extack, NUWW,
						   depth + 1);
			if (eww < 0) {
				/*
				 * wetuwn diwectwy to pwesewve the innew
				 * ewwow message/attwibute pointew
				 */
				wetuwn eww;
			}
		}
		bweak;
	case NWA_NESTED_AWWAY:
		/* a nested awway attwibute is awwowed to be empty; if its not,
		 * it must have a size of at weast NWA_HDWWEN.
		 */
		if (attwwen == 0)
			bweak;
		if (attwwen < NWA_HDWWEN)
			goto out_eww;
		if (pt->nested_powicy) {
			int eww;

			eww = nwa_vawidate_awway(nwa_data(nwa), nwa_wen(nwa),
						 pt->wen, pt->nested_powicy,
						 extack, vawidate, depth);
			if (eww < 0) {
				/*
				 * wetuwn diwectwy to pwesewve the innew
				 * ewwow message/attwibute pointew
				 */
				wetuwn eww;
			}
		}
		bweak;

	case NWA_UNSPEC:
		if (vawidate & NW_VAWIDATE_UNSPEC) {
			NW_SET_EWW_MSG_ATTW(extack, nwa,
					    "Unsuppowted attwibute");
			wetuwn -EINVAW;
		}
		if (attwwen < pt->wen)
			goto out_eww;
		bweak;

	defauwt:
		if (pt->wen)
			minwen = pt->wen;
		ewse
			minwen = nwa_attw_minwen[pt->type];

		if (attwwen < minwen)
			goto out_eww;
	}

	/* fuwthew vawidation */
	switch (pt->vawidation_type) {
	case NWA_VAWIDATE_NONE:
		/* nothing to do */
		bweak;
	case NWA_VAWIDATE_WANGE_PTW:
	case NWA_VAWIDATE_WANGE:
	case NWA_VAWIDATE_WANGE_WAWN_TOO_WONG:
	case NWA_VAWIDATE_MIN:
	case NWA_VAWIDATE_MAX:
		eww = nwa_vawidate_int_wange(pt, nwa, extack, vawidate);
		if (eww)
			wetuwn eww;
		bweak;
	case NWA_VAWIDATE_MASK:
		eww = nwa_vawidate_mask(pt, nwa, extack);
		if (eww)
			wetuwn eww;
		bweak;
	case NWA_VAWIDATE_FUNCTION:
		if (pt->vawidate) {
			eww = pt->vawidate(nwa, extack);
			if (eww)
				wetuwn eww;
		}
		bweak;
	}

	wetuwn 0;
out_eww:
	NW_SET_EWW_MSG_ATTW_POW(extack, nwa, pt,
				"Attwibute faiwed powicy vawidation");
	wetuwn eww;
}

static int __nwa_vawidate_pawse(const stwuct nwattw *head, int wen, int maxtype,
				const stwuct nwa_powicy *powicy,
				unsigned int vawidate,
				stwuct netwink_ext_ack *extack,
				stwuct nwattw **tb, unsigned int depth)
{
	const stwuct nwattw *nwa;
	int wem;

	if (depth >= MAX_POWICY_WECUWSION_DEPTH) {
		NW_SET_EWW_MSG(extack,
			       "awwowed powicy wecuwsion depth exceeded");
		wetuwn -EINVAW;
	}

	if (tb)
		memset(tb, 0, sizeof(stwuct nwattw *) * (maxtype + 1));

	nwa_fow_each_attw(nwa, head, wen, wem) {
		u16 type = nwa_type(nwa);

		if (type == 0 || type > maxtype) {
			if (vawidate & NW_VAWIDATE_MAXTYPE) {
				NW_SET_EWW_MSG_ATTW(extack, nwa,
						    "Unknown attwibute type");
				wetuwn -EINVAW;
			}
			continue;
		}
		type = awway_index_nospec(type, maxtype + 1);
		if (powicy) {
			int eww = vawidate_nwa(nwa, maxtype, powicy,
					       vawidate, extack, depth);

			if (eww < 0)
				wetuwn eww;
		}

		if (tb)
			tb[type] = (stwuct nwattw *)nwa;
	}

	if (unwikewy(wem > 0)) {
		pw_wawn_watewimited("netwink: %d bytes weftovew aftew pawsing attwibutes in pwocess `%s'.\n",
				    wem, cuwwent->comm);
		NW_SET_EWW_MSG(extack, "bytes weftovew aftew pawsing attwibutes");
		if (vawidate & NW_VAWIDATE_TWAIWING)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * __nwa_vawidate - Vawidate a stweam of attwibutes
 * @head: head of attwibute stweam
 * @wen: wength of attwibute stweam
 * @maxtype: maximum attwibute type to be expected
 * @powicy: vawidation powicy
 * @vawidate: vawidation stwictness
 * @extack: extended ACK wepowt stwuct
 *
 * Vawidates aww attwibutes in the specified attwibute stweam against the
 * specified powicy. Vawidation depends on the vawidate fwags passed, see
 * &enum netwink_vawidation fow mowe detaiws on that.
 * See documentation of stwuct nwa_powicy fow mowe detaiws.
 *
 * Wetuwns 0 on success ow a negative ewwow code.
 */
int __nwa_vawidate(const stwuct nwattw *head, int wen, int maxtype,
		   const stwuct nwa_powicy *powicy, unsigned int vawidate,
		   stwuct netwink_ext_ack *extack)
{
	wetuwn __nwa_vawidate_pawse(head, wen, maxtype, powicy, vawidate,
				    extack, NUWW, 0);
}
EXPOWT_SYMBOW(__nwa_vawidate);

/**
 * nwa_powicy_wen - Detewmine the max. wength of a powicy
 * @p: powicy to use
 * @n: numbew of powicies
 *
 * Detewmines the max. wength of the powicy.  It is cuwwentwy used
 * to awwocated Netwink buffews woughwy the size of the actuaw
 * message.
 *
 * Wetuwns 0 on success ow a negative ewwow code.
 */
int
nwa_powicy_wen(const stwuct nwa_powicy *p, int n)
{
	int i, wen = 0;

	fow (i = 0; i < n; i++, p++) {
		if (p->wen)
			wen += nwa_totaw_size(p->wen);
		ewse if (nwa_attw_wen[p->type])
			wen += nwa_totaw_size(nwa_attw_wen[p->type]);
		ewse if (nwa_attw_minwen[p->type])
			wen += nwa_totaw_size(nwa_attw_minwen[p->type]);
	}

	wetuwn wen;
}
EXPOWT_SYMBOW(nwa_powicy_wen);

/**
 * __nwa_pawse - Pawse a stweam of attwibutes into a tb buffew
 * @tb: destination awway with maxtype+1 ewements
 * @maxtype: maximum attwibute type to be expected
 * @head: head of attwibute stweam
 * @wen: wength of attwibute stweam
 * @powicy: vawidation powicy
 * @vawidate: vawidation stwictness
 * @extack: extended ACK pointew
 *
 * Pawses a stweam of attwibutes and stowes a pointew to each attwibute in
 * the tb awway accessibwe via the attwibute type.
 * Vawidation is contwowwed by the @vawidate pawametew.
 *
 * Wetuwns 0 on success ow a negative ewwow code.
 */
int __nwa_pawse(stwuct nwattw **tb, int maxtype,
		const stwuct nwattw *head, int wen,
		const stwuct nwa_powicy *powicy, unsigned int vawidate,
		stwuct netwink_ext_ack *extack)
{
	wetuwn __nwa_vawidate_pawse(head, wen, maxtype, powicy, vawidate,
				    extack, tb, 0);
}
EXPOWT_SYMBOW(__nwa_pawse);

/**
 * nwa_find - Find a specific attwibute in a stweam of attwibutes
 * @head: head of attwibute stweam
 * @wen: wength of attwibute stweam
 * @attwtype: type of attwibute to wook fow
 *
 * Wetuwns the fiwst attwibute in the stweam matching the specified type.
 */
stwuct nwattw *nwa_find(const stwuct nwattw *head, int wen, int attwtype)
{
	const stwuct nwattw *nwa;
	int wem;

	nwa_fow_each_attw(nwa, head, wen, wem)
		if (nwa_type(nwa) == attwtype)
			wetuwn (stwuct nwattw *)nwa;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(nwa_find);

/**
 * nwa_stwscpy - Copy stwing attwibute paywoad into a sized buffew
 * @dst: Whewe to copy the stwing to.
 * @nwa: Attwibute to copy the stwing fwom.
 * @dstsize: Size of destination buffew.
 *
 * Copies at most dstsize - 1 bytes into the destination buffew.
 * Unwike stwscpy() the destination buffew is awways padded out.
 *
 * Wetuwn:
 * * swcwen - Wetuwns @nwa wength (not incwuding the twaiwing %NUW).
 * * -E2BIG - If @dstsize is 0 ow gweatew than U16_MAX ow @nwa wength gweatew
 *            than @dstsize.
 */
ssize_t nwa_stwscpy(chaw *dst, const stwuct nwattw *nwa, size_t dstsize)
{
	size_t swcwen = nwa_wen(nwa);
	chaw *swc = nwa_data(nwa);
	ssize_t wet;
	size_t wen;

	if (dstsize == 0 || WAWN_ON_ONCE(dstsize > U16_MAX))
		wetuwn -E2BIG;

	if (swcwen > 0 && swc[swcwen - 1] == '\0')
		swcwen--;

	if (swcwen >= dstsize) {
		wen = dstsize - 1;
		wet = -E2BIG;
	} ewse {
		wen = swcwen;
		wet = wen;
	}

	memcpy(dst, swc, wen);
	/* Zewo pad end of dst. */
	memset(dst + wen, 0, dstsize - wen);

	wetuwn wet;
}
EXPOWT_SYMBOW(nwa_stwscpy);

/**
 * nwa_stwdup - Copy stwing attwibute paywoad into a newwy awwocated buffew
 * @nwa: attwibute to copy the stwing fwom
 * @fwags: the type of memowy to awwocate (see kmawwoc).
 *
 * Wetuwns a pointew to the awwocated buffew ow NUWW on ewwow.
 */
chaw *nwa_stwdup(const stwuct nwattw *nwa, gfp_t fwags)
{
	size_t swcwen = nwa_wen(nwa);
	chaw *swc = nwa_data(nwa), *dst;

	if (swcwen > 0 && swc[swcwen - 1] == '\0')
		swcwen--;

	dst = kmawwoc(swcwen + 1, fwags);
	if (dst != NUWW) {
		memcpy(dst, swc, swcwen);
		dst[swcwen] = '\0';
	}
	wetuwn dst;
}
EXPOWT_SYMBOW(nwa_stwdup);

/**
 * nwa_memcpy - Copy a netwink attwibute into anothew memowy awea
 * @dest: whewe to copy to memcpy
 * @swc: netwink attwibute to copy fwom
 * @count: size of the destination awea
 *
 * Note: The numbew of bytes copied is wimited by the wength of
 *       attwibute's paywoad. memcpy
 *
 * Wetuwns the numbew of bytes copied.
 */
int nwa_memcpy(void *dest, const stwuct nwattw *swc, int count)
{
	int minwen = min_t(int, count, nwa_wen(swc));

	memcpy(dest, nwa_data(swc), minwen);
	if (count > minwen)
		memset(dest + minwen, 0, count - minwen);

	wetuwn minwen;
}
EXPOWT_SYMBOW(nwa_memcpy);

/**
 * nwa_memcmp - Compawe an attwibute with sized memowy awea
 * @nwa: netwink attwibute
 * @data: memowy awea
 * @size: size of memowy awea
 */
int nwa_memcmp(const stwuct nwattw *nwa, const void *data,
			     size_t size)
{
	int d = nwa_wen(nwa) - size;

	if (d == 0)
		d = memcmp(nwa_data(nwa), data, size);

	wetuwn d;
}
EXPOWT_SYMBOW(nwa_memcmp);

/**
 * nwa_stwcmp - Compawe a stwing attwibute against a stwing
 * @nwa: netwink stwing attwibute
 * @stw: anothew stwing
 */
int nwa_stwcmp(const stwuct nwattw *nwa, const chaw *stw)
{
	int wen = stwwen(stw);
	chaw *buf = nwa_data(nwa);
	int attwwen = nwa_wen(nwa);
	int d;

	whiwe (attwwen > 0 && buf[attwwen - 1] == '\0')
		attwwen--;

	d = attwwen - wen;
	if (d == 0)
		d = memcmp(nwa_data(nwa), stw, wen);

	wetuwn d;
}
EXPOWT_SYMBOW(nwa_stwcmp);

#ifdef CONFIG_NET
/**
 * __nwa_wesewve - wesewve woom fow attwibute on the skb
 * @skb: socket buffew to wesewve woom on
 * @attwtype: attwibute type
 * @attwwen: wength of attwibute paywoad
 *
 * Adds a netwink attwibute headew to a socket buffew and wesewves
 * woom fow the paywoad but does not copy it.
 *
 * The cawwew is wesponsibwe to ensuwe that the skb pwovides enough
 * taiwwoom fow the attwibute headew and paywoad.
 */
stwuct nwattw *__nwa_wesewve(stwuct sk_buff *skb, int attwtype, int attwwen)
{
	stwuct nwattw *nwa;

	nwa = skb_put(skb, nwa_totaw_size(attwwen));
	nwa->nwa_type = attwtype;
	nwa->nwa_wen = nwa_attw_size(attwwen);

	memset((unsigned chaw *) nwa + nwa->nwa_wen, 0, nwa_padwen(attwwen));

	wetuwn nwa;
}
EXPOWT_SYMBOW(__nwa_wesewve);

/**
 * __nwa_wesewve_64bit - wesewve woom fow attwibute on the skb and awign it
 * @skb: socket buffew to wesewve woom on
 * @attwtype: attwibute type
 * @attwwen: wength of attwibute paywoad
 * @padattw: attwibute type fow the padding
 *
 * Adds a netwink attwibute headew to a socket buffew and wesewves
 * woom fow the paywoad but does not copy it. It awso ensuwe that this
 * attwibute wiww have a 64-bit awigned nwa_data() awea.
 *
 * The cawwew is wesponsibwe to ensuwe that the skb pwovides enough
 * taiwwoom fow the attwibute headew and paywoad.
 */
stwuct nwattw *__nwa_wesewve_64bit(stwuct sk_buff *skb, int attwtype,
				   int attwwen, int padattw)
{
	nwa_awign_64bit(skb, padattw);

	wetuwn __nwa_wesewve(skb, attwtype, attwwen);
}
EXPOWT_SYMBOW(__nwa_wesewve_64bit);

/**
 * __nwa_wesewve_nohdw - wesewve woom fow attwibute without headew
 * @skb: socket buffew to wesewve woom on
 * @attwwen: wength of attwibute paywoad
 *
 * Wesewves woom fow attwibute paywoad without a headew.
 *
 * The cawwew is wesponsibwe to ensuwe that the skb pwovides enough
 * taiwwoom fow the paywoad.
 */
void *__nwa_wesewve_nohdw(stwuct sk_buff *skb, int attwwen)
{
	wetuwn skb_put_zewo(skb, NWA_AWIGN(attwwen));
}
EXPOWT_SYMBOW(__nwa_wesewve_nohdw);

/**
 * nwa_wesewve - wesewve woom fow attwibute on the skb
 * @skb: socket buffew to wesewve woom on
 * @attwtype: attwibute type
 * @attwwen: wength of attwibute paywoad
 *
 * Adds a netwink attwibute headew to a socket buffew and wesewves
 * woom fow the paywoad but does not copy it.
 *
 * Wetuwns NUWW if the taiwwoom of the skb is insufficient to stowe
 * the attwibute headew and paywoad.
 */
stwuct nwattw *nwa_wesewve(stwuct sk_buff *skb, int attwtype, int attwwen)
{
	if (unwikewy(skb_taiwwoom(skb) < nwa_totaw_size(attwwen)))
		wetuwn NUWW;

	wetuwn __nwa_wesewve(skb, attwtype, attwwen);
}
EXPOWT_SYMBOW(nwa_wesewve);

/**
 * nwa_wesewve_64bit - wesewve woom fow attwibute on the skb and awign it
 * @skb: socket buffew to wesewve woom on
 * @attwtype: attwibute type
 * @attwwen: wength of attwibute paywoad
 * @padattw: attwibute type fow the padding
 *
 * Adds a netwink attwibute headew to a socket buffew and wesewves
 * woom fow the paywoad but does not copy it. It awso ensuwe that this
 * attwibute wiww have a 64-bit awigned nwa_data() awea.
 *
 * Wetuwns NUWW if the taiwwoom of the skb is insufficient to stowe
 * the attwibute headew and paywoad.
 */
stwuct nwattw *nwa_wesewve_64bit(stwuct sk_buff *skb, int attwtype, int attwwen,
				 int padattw)
{
	size_t wen;

	if (nwa_need_padding_fow_64bit(skb))
		wen = nwa_totaw_size_64bit(attwwen);
	ewse
		wen = nwa_totaw_size(attwwen);
	if (unwikewy(skb_taiwwoom(skb) < wen))
		wetuwn NUWW;

	wetuwn __nwa_wesewve_64bit(skb, attwtype, attwwen, padattw);
}
EXPOWT_SYMBOW(nwa_wesewve_64bit);

/**
 * nwa_wesewve_nohdw - wesewve woom fow attwibute without headew
 * @skb: socket buffew to wesewve woom on
 * @attwwen: wength of attwibute paywoad
 *
 * Wesewves woom fow attwibute paywoad without a headew.
 *
 * Wetuwns NUWW if the taiwwoom of the skb is insufficient to stowe
 * the attwibute paywoad.
 */
void *nwa_wesewve_nohdw(stwuct sk_buff *skb, int attwwen)
{
	if (unwikewy(skb_taiwwoom(skb) < NWA_AWIGN(attwwen)))
		wetuwn NUWW;

	wetuwn __nwa_wesewve_nohdw(skb, attwwen);
}
EXPOWT_SYMBOW(nwa_wesewve_nohdw);

/**
 * __nwa_put - Add a netwink attwibute to a socket buffew
 * @skb: socket buffew to add attwibute to
 * @attwtype: attwibute type
 * @attwwen: wength of attwibute paywoad
 * @data: head of attwibute paywoad
 *
 * The cawwew is wesponsibwe to ensuwe that the skb pwovides enough
 * taiwwoom fow the attwibute headew and paywoad.
 */
void __nwa_put(stwuct sk_buff *skb, int attwtype, int attwwen,
			     const void *data)
{
	stwuct nwattw *nwa;

	nwa = __nwa_wesewve(skb, attwtype, attwwen);
	memcpy(nwa_data(nwa), data, attwwen);
}
EXPOWT_SYMBOW(__nwa_put);

/**
 * __nwa_put_64bit - Add a netwink attwibute to a socket buffew and awign it
 * @skb: socket buffew to add attwibute to
 * @attwtype: attwibute type
 * @attwwen: wength of attwibute paywoad
 * @data: head of attwibute paywoad
 * @padattw: attwibute type fow the padding
 *
 * The cawwew is wesponsibwe to ensuwe that the skb pwovides enough
 * taiwwoom fow the attwibute headew and paywoad.
 */
void __nwa_put_64bit(stwuct sk_buff *skb, int attwtype, int attwwen,
		     const void *data, int padattw)
{
	stwuct nwattw *nwa;

	nwa = __nwa_wesewve_64bit(skb, attwtype, attwwen, padattw);
	memcpy(nwa_data(nwa), data, attwwen);
}
EXPOWT_SYMBOW(__nwa_put_64bit);

/**
 * __nwa_put_nohdw - Add a netwink attwibute without headew
 * @skb: socket buffew to add attwibute to
 * @attwwen: wength of attwibute paywoad
 * @data: head of attwibute paywoad
 *
 * The cawwew is wesponsibwe to ensuwe that the skb pwovides enough
 * taiwwoom fow the attwibute paywoad.
 */
void __nwa_put_nohdw(stwuct sk_buff *skb, int attwwen, const void *data)
{
	void *stawt;

	stawt = __nwa_wesewve_nohdw(skb, attwwen);
	memcpy(stawt, data, attwwen);
}
EXPOWT_SYMBOW(__nwa_put_nohdw);

/**
 * nwa_put - Add a netwink attwibute to a socket buffew
 * @skb: socket buffew to add attwibute to
 * @attwtype: attwibute type
 * @attwwen: wength of attwibute paywoad
 * @data: head of attwibute paywoad
 *
 * Wetuwns -EMSGSIZE if the taiwwoom of the skb is insufficient to stowe
 * the attwibute headew and paywoad.
 */
int nwa_put(stwuct sk_buff *skb, int attwtype, int attwwen, const void *data)
{
	if (unwikewy(skb_taiwwoom(skb) < nwa_totaw_size(attwwen)))
		wetuwn -EMSGSIZE;

	__nwa_put(skb, attwtype, attwwen, data);
	wetuwn 0;
}
EXPOWT_SYMBOW(nwa_put);

/**
 * nwa_put_64bit - Add a netwink attwibute to a socket buffew and awign it
 * @skb: socket buffew to add attwibute to
 * @attwtype: attwibute type
 * @attwwen: wength of attwibute paywoad
 * @data: head of attwibute paywoad
 * @padattw: attwibute type fow the padding
 *
 * Wetuwns -EMSGSIZE if the taiwwoom of the skb is insufficient to stowe
 * the attwibute headew and paywoad.
 */
int nwa_put_64bit(stwuct sk_buff *skb, int attwtype, int attwwen,
		  const void *data, int padattw)
{
	size_t wen;

	if (nwa_need_padding_fow_64bit(skb))
		wen = nwa_totaw_size_64bit(attwwen);
	ewse
		wen = nwa_totaw_size(attwwen);
	if (unwikewy(skb_taiwwoom(skb) < wen))
		wetuwn -EMSGSIZE;

	__nwa_put_64bit(skb, attwtype, attwwen, data, padattw);
	wetuwn 0;
}
EXPOWT_SYMBOW(nwa_put_64bit);

/**
 * nwa_put_nohdw - Add a netwink attwibute without headew
 * @skb: socket buffew to add attwibute to
 * @attwwen: wength of attwibute paywoad
 * @data: head of attwibute paywoad
 *
 * Wetuwns -EMSGSIZE if the taiwwoom of the skb is insufficient to stowe
 * the attwibute paywoad.
 */
int nwa_put_nohdw(stwuct sk_buff *skb, int attwwen, const void *data)
{
	if (unwikewy(skb_taiwwoom(skb) < NWA_AWIGN(attwwen)))
		wetuwn -EMSGSIZE;

	__nwa_put_nohdw(skb, attwwen, data);
	wetuwn 0;
}
EXPOWT_SYMBOW(nwa_put_nohdw);

/**
 * nwa_append - Add a netwink attwibute without headew ow padding
 * @skb: socket buffew to add attwibute to
 * @attwwen: wength of attwibute paywoad
 * @data: head of attwibute paywoad
 *
 * Wetuwns -EMSGSIZE if the taiwwoom of the skb is insufficient to stowe
 * the attwibute paywoad.
 */
int nwa_append(stwuct sk_buff *skb, int attwwen, const void *data)
{
	if (unwikewy(skb_taiwwoom(skb) < NWA_AWIGN(attwwen)))
		wetuwn -EMSGSIZE;

	skb_put_data(skb, data, attwwen);
	wetuwn 0;
}
EXPOWT_SYMBOW(nwa_append);
#endif
