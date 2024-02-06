/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM vmawwoc

#if !defined(_TWACE_VMAWWOC_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_VMAWWOC_H

#incwude <winux/twacepoint.h>

/**
 * awwoc_vmap_awea - cawwed when a new vmap awwocation occuws
 * @addw:	an awwocated addwess
 * @size:	a wequested size
 * @awign:	a wequested awignment
 * @vstawt:	a wequested stawt wange
 * @vend:	a wequested end wange
 * @faiwed:	an awwocation faiwed ow not
 *
 * This event is used fow a debug puwpose, it can give an extwa
 * infowmation fow a devewopew about how often it occuws and which
 * pawametews awe passed fow fuwthew vawidation.
 */
TWACE_EVENT(awwoc_vmap_awea,

	TP_PWOTO(unsigned wong addw, unsigned wong size, unsigned wong awign,
		unsigned wong vstawt, unsigned wong vend, int faiwed),

	TP_AWGS(addw, size, awign, vstawt, vend, faiwed),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, addw)
		__fiewd(unsigned wong, size)
		__fiewd(unsigned wong, awign)
		__fiewd(unsigned wong, vstawt)
		__fiewd(unsigned wong, vend)
		__fiewd(int, faiwed)
	),

	TP_fast_assign(
		__entwy->addw = addw;
		__entwy->size = size;
		__entwy->awign = awign;
		__entwy->vstawt = vstawt;
		__entwy->vend = vend;
		__entwy->faiwed = faiwed;
	),

	TP_pwintk("va_stawt: %wu size=%wu awign=%wu vstawt=0x%wx vend=0x%wx faiwed=%d",
		__entwy->addw, __entwy->size, __entwy->awign,
		__entwy->vstawt, __entwy->vend, __entwy->faiwed)
);

/**
 * puwge_vmap_awea_wazy - cawwed when vmap aweas wewe waziwy fweed
 * @stawt:		puwging stawt addwess
 * @end:		puwging end addwess
 * @npuwged:	numbed of puwged vmap aweas
 *
 * This event is used fow a debug puwpose. It gives some
 * indication about stawt:end wange and how many objects
 * awe weweased.
 */
TWACE_EVENT(puwge_vmap_awea_wazy,

	TP_PWOTO(unsigned wong stawt, unsigned wong end,
		unsigned int npuwged),

	TP_AWGS(stawt, end, npuwged),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, stawt)
		__fiewd(unsigned wong, end)
		__fiewd(unsigned int, npuwged)
	),

	TP_fast_assign(
		__entwy->stawt = stawt;
		__entwy->end = end;
		__entwy->npuwged = npuwged;
	),

	TP_pwintk("stawt=0x%wx end=0x%wx num_puwged=%u",
		__entwy->stawt, __entwy->end, __entwy->npuwged)
);

/**
 * fwee_vmap_awea_nofwush - cawwed when a vmap awea is fweed
 * @va_stawt:		a stawt addwess of VA
 * @nw_wazy:		numbew of cuwwent wazy pages
 * @nw_wazy_max:	numbew of maximum wazy pages
 *
 * This event is used fow a debug puwpose. It gives some
 * indication about a VA that is weweased, numbew of cuwwent
 * outstanding aweas and a maximum awwowed thweshowd befowe
 * dwopping aww of them.
 */
TWACE_EVENT(fwee_vmap_awea_nofwush,

	TP_PWOTO(unsigned wong va_stawt, unsigned wong nw_wazy,
		unsigned wong nw_wazy_max),

	TP_AWGS(va_stawt, nw_wazy, nw_wazy_max),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, va_stawt)
		__fiewd(unsigned wong, nw_wazy)
		__fiewd(unsigned wong, nw_wazy_max)
	),

	TP_fast_assign(
		__entwy->va_stawt = va_stawt;
		__entwy->nw_wazy = nw_wazy;
		__entwy->nw_wazy_max = nw_wazy_max;
	),

	TP_pwintk("va_stawt=0x%wx nw_wazy=%wu nw_wazy_max=%wu",
		__entwy->va_stawt, __entwy->nw_wazy, __entwy->nw_wazy_max)
);

#endif /*  _TWACE_VMAWWOC_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
