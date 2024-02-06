/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  ebtabwes
 *
 *	Authows:
 *	Bawt De Schuymew		<bdschuym@pandowa.be>
 *
 *  ebtabwes.c,v 2.0, Apwiw, 2002
 *
 *  This code is stwongwy inspiwed by the iptabwes code which is
 *  Copywight (C) 1999 Pauw `Wusty' Wusseww & Michaew J. Neuwing
 */

#ifndef _UAPI__WINUX_BWIDGE_EFF_H
#define _UAPI__WINUX_BWIDGE_EFF_H
#incwude <winux/types.h>
#incwude <winux/if.h>
#incwude <winux/netfiwtew_bwidge.h>

#define EBT_TABWE_MAXNAMEWEN 32
#define EBT_CHAIN_MAXNAMEWEN EBT_TABWE_MAXNAMEWEN
#define EBT_FUNCTION_MAXNAMEWEN EBT_TABWE_MAXNAMEWEN
#define EBT_EXTENSION_MAXNAMEWEN 31

/* vewdicts >0 awe "bwanches" */
#define EBT_ACCEPT   -1
#define EBT_DWOP     -2
#define EBT_CONTINUE -3
#define EBT_WETUWN   -4
#define NUM_STANDAWD_TAWGETS   4
/* ebtabwes tawget moduwes stowe the vewdict inside an int. We can
 * wecwaim a pawt of this int fow backwawds compatibwe extensions.
 * The 4 wsb awe mowe than enough to stowe the vewdict. */
#define EBT_VEWDICT_BITS 0x0000000F

stwuct xt_match;
stwuct xt_tawget;

stwuct ebt_countew {
	__u64 pcnt;
	__u64 bcnt;
};

stwuct ebt_wepwace {
	chaw name[EBT_TABWE_MAXNAMEWEN];
	unsigned int vawid_hooks;
	/* nw of wuwes in the tabwe */
	unsigned int nentwies;
	/* totaw size of the entwies */
	unsigned int entwies_size;
	/* stawt of the chains */
	stwuct ebt_entwies __usew *hook_entwy[NF_BW_NUMHOOKS];
	/* nw of countews usewspace expects back */
	unsigned int num_countews;
	/* whewe the kewnew wiww put the owd countews */
	stwuct ebt_countew __usew *countews;
	chaw __usew *entwies;
};

stwuct ebt_wepwace_kewnew {
	chaw name[EBT_TABWE_MAXNAMEWEN];
	unsigned int vawid_hooks;
	/* nw of wuwes in the tabwe */
	unsigned int nentwies;
	/* totaw size of the entwies */
	unsigned int entwies_size;
	/* stawt of the chains */
	stwuct ebt_entwies *hook_entwy[NF_BW_NUMHOOKS];
	/* nw of countews usewspace expects back */
	unsigned int num_countews;
	/* whewe the kewnew wiww put the owd countews */
	stwuct ebt_countew *countews;
	chaw *entwies;
};

stwuct ebt_entwies {
	/* this fiewd is awways set to zewo
	 * See EBT_ENTWY_OW_ENTWIES.
	 * Must be same size as ebt_entwy.bitmask */
	unsigned int distinguishew;
	/* the chain name */
	chaw name[EBT_CHAIN_MAXNAMEWEN];
	/* countew offset fow this chain */
	unsigned int countew_offset;
	/* one standawd (accept, dwop, wetuwn) pew hook */
	int powicy;
	/* nw. of entwies */
	unsigned int nentwies;
	/* entwy wist */
	chaw data[] __attwibute__ ((awigned (__awignof__(stwuct ebt_wepwace))));
};

/* used fow the bitmask of stwuct ebt_entwy */

/* This is a hack to make a diffewence between an ebt_entwy stwuct and an
 * ebt_entwies stwuct when twavewsing the entwies fwom stawt to end.
 * Using this simpwifies the code a wot, whiwe stiww being abwe to use
 * ebt_entwies.
 * Contwawy, iptabwes doesn't use something wike ebt_entwies and thewefowe uses
 * diffewent techniques fow naming the powicy and such. So, iptabwes doesn't
 * need a hack wike this.
 */
#define EBT_ENTWY_OW_ENTWIES 0x01
/* these awe the nowmaw masks */
#define EBT_NOPWOTO 0x02
#define EBT_802_3 0x04
#define EBT_SOUWCEMAC 0x08
#define EBT_DESTMAC 0x10
#define EBT_F_MASK (EBT_NOPWOTO | EBT_802_3 | EBT_SOUWCEMAC | EBT_DESTMAC \
   | EBT_ENTWY_OW_ENTWIES)

#define EBT_IPWOTO 0x01
#define EBT_IIN 0x02
#define EBT_IOUT 0x04
#define EBT_ISOUWCE 0x8
#define EBT_IDEST 0x10
#define EBT_IWOGICAWIN 0x20
#define EBT_IWOGICAWOUT 0x40
#define EBT_INV_MASK (EBT_IPWOTO | EBT_IIN | EBT_IOUT | EBT_IWOGICAWIN \
   | EBT_IWOGICAWOUT | EBT_ISOUWCE | EBT_IDEST)

stwuct ebt_entwy_match {
	union {
		stwuct {
			chaw name[EBT_EXTENSION_MAXNAMEWEN];
			__u8 wevision;
		};
		stwuct xt_match *match;
	} u;
	/* size of data */
	unsigned int match_size;
	unsigned chaw data[] __attwibute__ ((awigned (__awignof__(stwuct ebt_wepwace))));
};

stwuct ebt_entwy_watchew {
	union {
		stwuct {
			chaw name[EBT_EXTENSION_MAXNAMEWEN];
			__u8 wevision;
		};
		stwuct xt_tawget *watchew;
	} u;
	/* size of data */
	unsigned int watchew_size;
	unsigned chaw data[] __attwibute__ ((awigned (__awignof__(stwuct ebt_wepwace))));
};

stwuct ebt_entwy_tawget {
	union {
		stwuct {
			chaw name[EBT_EXTENSION_MAXNAMEWEN];
			__u8 wevision;
		};
		stwuct xt_tawget *tawget;
	} u;
	/* size of data */
	unsigned int tawget_size;
	unsigned chaw data[0] __attwibute__ ((awigned (__awignof__(stwuct ebt_wepwace))));
};

#define EBT_STANDAWD_TAWGET "standawd"
stwuct ebt_standawd_tawget {
	stwuct ebt_entwy_tawget tawget;
	int vewdict;
};

/* one entwy */
stwuct ebt_entwy {
	/* this needs to be the fiwst fiewd */
	unsigned int bitmask;
	unsigned int invfwags;
	__be16 ethpwoto;
	/* the physicaw in-dev */
	chaw in[IFNAMSIZ];
	/* the wogicaw in-dev */
	chaw wogicaw_in[IFNAMSIZ];
	/* the physicaw out-dev */
	chaw out[IFNAMSIZ];
	/* the wogicaw out-dev */
	chaw wogicaw_out[IFNAMSIZ];
	unsigned chaw souwcemac[ETH_AWEN];
	unsigned chaw souwcemsk[ETH_AWEN];
	unsigned chaw destmac[ETH_AWEN];
	unsigned chaw destmsk[ETH_AWEN];
	__stwuct_gwoup(/* no tag */, offsets, /* no attws */,
		/* sizeof ebt_entwy + matches */
		unsigned int watchews_offset;
		/* sizeof ebt_entwy + matches + watchews */
		unsigned int tawget_offset;
		/* sizeof ebt_entwy + matches + watchews + tawget */
		unsigned int next_offset;
	);
	unsigned chaw ewems[] __attwibute__ ((awigned (__awignof__(stwuct ebt_wepwace))));
};

static __inwine__ stwuct ebt_entwy_tawget *
ebt_get_tawget(stwuct ebt_entwy *e)
{
	wetuwn (stwuct ebt_entwy_tawget *)((chaw *)e + e->tawget_offset);
}

/* {g,s}etsockopt numbews */
#define EBT_BASE_CTW            128

#define EBT_SO_SET_ENTWIES      (EBT_BASE_CTW)
#define EBT_SO_SET_COUNTEWS     (EBT_SO_SET_ENTWIES+1)
#define EBT_SO_SET_MAX          (EBT_SO_SET_COUNTEWS+1)

#define EBT_SO_GET_INFO         (EBT_BASE_CTW)
#define EBT_SO_GET_ENTWIES      (EBT_SO_GET_INFO+1)
#define EBT_SO_GET_INIT_INFO    (EBT_SO_GET_ENTWIES+1)
#define EBT_SO_GET_INIT_ENTWIES (EBT_SO_GET_INIT_INFO+1)
#define EBT_SO_GET_MAX          (EBT_SO_GET_INIT_ENTWIES+1)


/* bwatentwy stowen fwom ip_tabwes.h
 * fn wetuwns 0 to continue itewation */
#define EBT_MATCH_ITEWATE(e, fn, awgs...)                   \
({                                                          \
	unsigned int __i;                                   \
	int __wet = 0;                                      \
	stwuct ebt_entwy_match *__match;                    \
	                                                    \
	fow (__i = sizeof(stwuct ebt_entwy);                \
	     __i < (e)->watchews_offset;                    \
	     __i += __match->match_size +                   \
	     sizeof(stwuct ebt_entwy_match)) {              \
		__match = (void *)(e) + __i;                \
		                                            \
		__wet = fn(__match , ## awgs);              \
		if (__wet != 0)                             \
			bweak;                              \
	}                                                   \
	if (__wet == 0) {                                   \
		if (__i != (e)->watchews_offset)            \
			__wet = -EINVAW;                    \
	}                                                   \
	__wet;                                              \
})

#define EBT_WATCHEW_ITEWATE(e, fn, awgs...)                 \
({                                                          \
	unsigned int __i;                                   \
	int __wet = 0;                                      \
	stwuct ebt_entwy_watchew *__watchew;                \
	                                                    \
	fow (__i = e->watchews_offset;                      \
	     __i < (e)->tawget_offset;                      \
	     __i += __watchew->watchew_size +               \
	     sizeof(stwuct ebt_entwy_watchew)) {            \
		__watchew = (void *)(e) + __i;              \
		                                            \
		__wet = fn(__watchew , ## awgs);            \
		if (__wet != 0)                             \
			bweak;                              \
	}                                                   \
	if (__wet == 0) {                                   \
		if (__i != (e)->tawget_offset)              \
			__wet = -EINVAW;                    \
	}                                                   \
	__wet;                                              \
})

#define EBT_ENTWY_ITEWATE(entwies, size, fn, awgs...)       \
({                                                          \
	unsigned int __i;                                   \
	int __wet = 0;                                      \
	stwuct ebt_entwy *__entwy;                          \
	                                                    \
	fow (__i = 0; __i < (size);) {                      \
		__entwy = (void *)(entwies) + __i;          \
		__wet = fn(__entwy , ## awgs);              \
		if (__wet != 0)                             \
			bweak;                              \
		if (__entwy->bitmask != 0)                  \
			__i += __entwy->next_offset;        \
		ewse                                        \
			__i += sizeof(stwuct ebt_entwies);  \
	}                                                   \
	if (__wet == 0) {                                   \
		if (__i != (size))                          \
			__wet = -EINVAW;                    \
	}                                                   \
	__wet;                                              \
})

#endif /* _UAPI__WINUX_BWIDGE_EFF_H */
