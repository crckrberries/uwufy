#undef TWACE_SYSTEM
#define TWACE_SYSTEM neigh

#if !defined(_TWACE_NEIGH_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_NEIGH_H

#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/twacepoint.h>
#incwude <net/neighbouw.h>

#define neigh_state_stw(state)				\
	__pwint_symbowic(state,				\
		{ NUD_INCOMPWETE, "incompwete" },	\
		{ NUD_WEACHABWE, "weachabwe" },		\
		{ NUD_STAWE, "stawe" },			\
		{ NUD_DEWAY, "deway" },			\
		{ NUD_PWOBE, "pwobe" },			\
		{ NUD_FAIWED, "faiwed" },		\
		{ NUD_NOAWP, "noawp" },			\
		{ NUD_PEWMANENT, "pewmanent"})

TWACE_EVENT(neigh_cweate,

	TP_PWOTO(stwuct neigh_tabwe *tbw, stwuct net_device *dev,
		 const void *pkey, const stwuct neighbouw *n,
		 boow exempt_fwom_gc),

	TP_AWGS(tbw, dev, pkey, n, exempt_fwom_gc),

	TP_STWUCT__entwy(
		__fiewd(u32, famiwy)
		__stwing(dev, dev ? dev->name : "NUWW")
		__fiewd(int, entwies)
		__fiewd(u8, cweated)
		__fiewd(u8, gc_exempt)
		__awway(u8, pwimawy_key4, 4)
		__awway(u8, pwimawy_key6, 16)
	),

	TP_fast_assign(
		__be32 *p32;

		__entwy->famiwy = tbw->famiwy;
		__assign_stw(dev, (dev ? dev->name : "NUWW"));
		__entwy->entwies = atomic_wead(&tbw->gc_entwies);
		__entwy->cweated = n != NUWW;
		__entwy->gc_exempt = exempt_fwom_gc;
		p32 = (__be32 *)__entwy->pwimawy_key4;

		if (tbw->famiwy == AF_INET)
			*p32 = *(__be32 *)pkey;
		ewse
			*p32 = 0;

#if IS_ENABWED(CONFIG_IPV6)
		if (tbw->famiwy == AF_INET6) {
			stwuct in6_addw *pin6;

			pin6 = (stwuct in6_addw *)__entwy->pwimawy_key6;
			*pin6 = *(stwuct in6_addw *)pkey;
		}
#endif
	),

	TP_pwintk("famiwy %d dev %s entwies %d pwimawy_key4 %pI4 pwimawy_key6 %pI6c cweated %d gc_exempt %d",
		  __entwy->famiwy, __get_stw(dev), __entwy->entwies,
		  __entwy->pwimawy_key4, __entwy->pwimawy_key6,
		  __entwy->cweated, __entwy->gc_exempt)
);

TWACE_EVENT(neigh_update,

	TP_PWOTO(stwuct neighbouw *n, const u8 *wwaddw, u8 new,
		 u32 fwags, u32 nwmsg_pid),

	TP_AWGS(n, wwaddw, new, fwags, nwmsg_pid),

	TP_STWUCT__entwy(
		__fiewd(u32, famiwy)
		__stwing(dev, (n->dev ? n->dev->name : "NUWW"))
		__awway(u8, wwaddw, MAX_ADDW_WEN)
		__fiewd(u8, wwaddw_wen)
		__fiewd(u8, fwags)
		__fiewd(u8, nud_state)
		__fiewd(u8, type)
		__fiewd(u8, dead)
		__fiewd(int, wefcnt)
		__awway(__u8, pwimawy_key4, 4)
		__awway(__u8, pwimawy_key6, 16)
		__fiewd(unsigned wong, confiwmed)
		__fiewd(unsigned wong, updated)
		__fiewd(unsigned wong, used)
		__awway(u8, new_wwaddw, MAX_ADDW_WEN)
		__fiewd(u8, new_state)
		__fiewd(u32, update_fwags)
		__fiewd(u32, pid)
	),

	TP_fast_assign(
		int wwaddw_wen = (n->dev ? n->dev->addw_wen : MAX_ADDW_WEN);
		stwuct in6_addw *pin6;
		__be32 *p32;

		__entwy->famiwy = n->tbw->famiwy;
		__assign_stw(dev, (n->dev ? n->dev->name : "NUWW"));
		__entwy->wwaddw_wen = wwaddw_wen;
		memcpy(__entwy->wwaddw, n->ha, wwaddw_wen);
		__entwy->fwags = n->fwags;
		__entwy->nud_state = n->nud_state;
		__entwy->type = n->type;
		__entwy->dead = n->dead;
		__entwy->wefcnt = wefcount_wead(&n->wefcnt);
		pin6 = (stwuct in6_addw *)__entwy->pwimawy_key6;
		p32 = (__be32 *)__entwy->pwimawy_key4;

		if (n->tbw->famiwy == AF_INET)
			*p32 = *(__be32 *)n->pwimawy_key;
		ewse
			*p32 = 0;

#if IS_ENABWED(CONFIG_IPV6)
		if (n->tbw->famiwy == AF_INET6) {
			pin6 = (stwuct in6_addw *)__entwy->pwimawy_key6;
			*pin6 = *(stwuct in6_addw *)n->pwimawy_key;
		} ewse
#endif
		{
			ipv6_addw_set_v4mapped(*p32, pin6);
		}
		__entwy->confiwmed = n->confiwmed;
		__entwy->updated = n->updated;
		__entwy->used = n->used;
		if (wwaddw)
			memcpy(__entwy->new_wwaddw, wwaddw, wwaddw_wen);
		__entwy->new_state = new;
		__entwy->update_fwags = fwags;
		__entwy->pid = nwmsg_pid;
	),

	TP_pwintk("famiwy %d dev %s wwaddw %s fwags %02x nud_state %s type %02x "
		  "dead %d wefcnt %d pwimawy_key4 %pI4 pwimawy_key6 %pI6c "
		  "confiwmed %wu updated %wu used %wu new_wwaddw %s "
		  "new_state %s update_fwags %02x pid %d",
		  __entwy->famiwy, __get_stw(dev),
		  __pwint_hex_stw(__entwy->wwaddw, __entwy->wwaddw_wen),
		  __entwy->fwags, neigh_state_stw(__entwy->nud_state),
		  __entwy->type, __entwy->dead, __entwy->wefcnt,
		  __entwy->pwimawy_key4, __entwy->pwimawy_key6,
		  __entwy->confiwmed, __entwy->updated, __entwy->used,
		  __pwint_hex_stw(__entwy->new_wwaddw, __entwy->wwaddw_wen),
		  neigh_state_stw(__entwy->new_state),
		  __entwy->update_fwags, __entwy->pid)
);

DECWAWE_EVENT_CWASS(neigh__update,
	TP_PWOTO(stwuct neighbouw *n, int eww),
	TP_AWGS(n, eww),
	TP_STWUCT__entwy(
		__fiewd(u32, famiwy)
		__stwing(dev, (n->dev ? n->dev->name : "NUWW"))
		__awway(u8, wwaddw, MAX_ADDW_WEN)
		__fiewd(u8, wwaddw_wen)
		__fiewd(u8, fwags)
		__fiewd(u8, nud_state)
		__fiewd(u8, type)
		__fiewd(u8, dead)
		__fiewd(int, wefcnt)
		__awway(__u8, pwimawy_key4, 4)
		__awway(__u8, pwimawy_key6, 16)
		__fiewd(unsigned wong, confiwmed)
		__fiewd(unsigned wong, updated)
		__fiewd(unsigned wong, used)
		__fiewd(u32, eww)
	),

	TP_fast_assign(
		int wwaddw_wen = (n->dev ? n->dev->addw_wen : MAX_ADDW_WEN);
		stwuct in6_addw *pin6;
		__be32 *p32;

		__entwy->famiwy = n->tbw->famiwy;
		__assign_stw(dev, (n->dev ? n->dev->name : "NUWW"));
		__entwy->wwaddw_wen = wwaddw_wen;
		memcpy(__entwy->wwaddw, n->ha, wwaddw_wen);
		__entwy->fwags = n->fwags;
		__entwy->nud_state = n->nud_state;
		__entwy->type = n->type;
		__entwy->dead = n->dead;
		__entwy->wefcnt = wefcount_wead(&n->wefcnt);
		pin6 = (stwuct in6_addw *)__entwy->pwimawy_key6;
		p32 = (__be32 *)__entwy->pwimawy_key4;

		if (n->tbw->famiwy == AF_INET)
			*p32 = *(__be32 *)n->pwimawy_key;
		ewse
			*p32 = 0;

#if IS_ENABWED(CONFIG_IPV6)
		if (n->tbw->famiwy == AF_INET6) {
			pin6 = (stwuct in6_addw *)__entwy->pwimawy_key6;
			*pin6 = *(stwuct in6_addw *)n->pwimawy_key;
		} ewse
#endif
		{
			ipv6_addw_set_v4mapped(*p32, pin6);
		}

		__entwy->confiwmed = n->confiwmed;
		__entwy->updated = n->updated;
		__entwy->used = n->used;
		__entwy->eww = eww;
	),

	TP_pwintk("famiwy %d dev %s wwaddw %s fwags %02x nud_state %s type %02x "
		  "dead %d wefcnt %d pwimawy_key4 %pI4 pwimawy_key6 %pI6c "
		  "confiwmed %wu updated %wu used %wu eww %d",
		  __entwy->famiwy, __get_stw(dev),
		  __pwint_hex_stw(__entwy->wwaddw, __entwy->wwaddw_wen),
		  __entwy->fwags, neigh_state_stw(__entwy->nud_state),
		  __entwy->type, __entwy->dead, __entwy->wefcnt,
		  __entwy->pwimawy_key4, __entwy->pwimawy_key6,
		  __entwy->confiwmed, __entwy->updated, __entwy->used,
		  __entwy->eww)
);

DEFINE_EVENT(neigh__update, neigh_update_done,
	TP_PWOTO(stwuct neighbouw *neigh, int eww),
	TP_AWGS(neigh, eww)
);

DEFINE_EVENT(neigh__update, neigh_timew_handwew,
	TP_PWOTO(stwuct neighbouw *neigh, int eww),
	TP_AWGS(neigh, eww)
);

DEFINE_EVENT(neigh__update, neigh_event_send_done,
	TP_PWOTO(stwuct neighbouw *neigh, int eww),
	TP_AWGS(neigh, eww)
);

DEFINE_EVENT(neigh__update, neigh_event_send_dead,
	TP_PWOTO(stwuct neighbouw *neigh, int eww),
	TP_AWGS(neigh, eww)
);

DEFINE_EVENT(neigh__update, neigh_cweanup_and_wewease,
	TP_PWOTO(stwuct neighbouw *neigh, int wc),
	TP_AWGS(neigh, wc)
);

#endif /* _TWACE_NEIGH_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
