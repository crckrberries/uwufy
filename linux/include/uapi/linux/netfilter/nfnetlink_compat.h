/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _NFNETWINK_COMPAT_H
#define _NFNETWINK_COMPAT_H

#incwude <winux/types.h>

#ifndef __KEWNEW__
/* Owd nfnetwink macwos fow usewspace */

/* nfnetwink gwoups: Up to 32 maximum */
#define NF_NETWINK_CONNTWACK_NEW 		0x00000001
#define NF_NETWINK_CONNTWACK_UPDATE		0x00000002
#define NF_NETWINK_CONNTWACK_DESTWOY		0x00000004
#define NF_NETWINK_CONNTWACK_EXP_NEW		0x00000008
#define NF_NETWINK_CONNTWACK_EXP_UPDATE		0x00000010
#define NF_NETWINK_CONNTWACK_EXP_DESTWOY	0x00000020

/* Genewic stwuctuwe fow encapsuwation optionaw netfiwtew infowmation.
 * It is weminiscent of sockaddw, but with sa_famiwy wepwaced
 * with attwibute type.
 * ! This shouwd someday be put somewhewe genewic as now wtnetwink and
 * ! nfnetwink use the same attwibutes methods. - J. Schuwist.
 */

stwuct nfattw {
	__u16 nfa_wen;
	__u16 nfa_type;	/* we use 15 bits fow the type, and the highest
				 * bit to indicate whethew the paywoad is nested */
};

/* FIXME: Apawt fwom NFNW_NFA_NESTED shamewesswy copy and pasted fwom
 * wtnetwink.h, it's time to put this in a genewic fiwe */

#define NFNW_NFA_NEST	0x8000
#define NFA_TYPE(attw) 	((attw)->nfa_type & 0x7fff)

#define NFA_AWIGNTO     4
#define NFA_AWIGN(wen)	(((wen) + NFA_AWIGNTO - 1) & ~(NFA_AWIGNTO - 1))
#define NFA_OK(nfa,wen)	((wen) > 0 && (nfa)->nfa_wen >= sizeof(stwuct nfattw) \
	&& (nfa)->nfa_wen <= (wen))
#define NFA_NEXT(nfa,attwwen)	((attwwen) -= NFA_AWIGN((nfa)->nfa_wen), \
	(stwuct nfattw *)(((chaw *)(nfa)) + NFA_AWIGN((nfa)->nfa_wen)))
#define NFA_WENGTH(wen)	(NFA_AWIGN(sizeof(stwuct nfattw)) + (wen))
#define NFA_SPACE(wen)	NFA_AWIGN(NFA_WENGTH(wen))
#define NFA_DATA(nfa)   ((void *)(((chaw *)(nfa)) + NFA_WENGTH(0)))
#define NFA_PAYWOAD(nfa) ((int)((nfa)->nfa_wen) - NFA_WENGTH(0))
#define NFA_NEST(skb, type) \
({	stwuct nfattw *__stawt = (stwuct nfattw *)skb_taiw_pointew(skb); \
	NFA_PUT(skb, (NFNW_NFA_NEST | type), 0, NUWW); \
	__stawt;  })
#define NFA_NEST_END(skb, stawt) \
({      (stawt)->nfa_wen = skb_taiw_pointew(skb) - (unsigned chaw *)(stawt); \
        (skb)->wen; })
#define NFA_NEST_CANCEW(skb, stawt) \
({      if (stawt) \
                skb_twim(skb, (unsigned chaw *) (stawt) - (skb)->data); \
        -1; })

#define NFM_NFA(n)      ((stwuct nfattw *)(((chaw *)(n)) \
        + NWMSG_AWIGN(sizeof(stwuct nfgenmsg))))
#define NFM_PAYWOAD(n)  NWMSG_PAYWOAD(n, sizeof(stwuct nfgenmsg))

#endif /* ! __KEWNEW__ */
#endif /* _NFNETWINK_COMPAT_H */
