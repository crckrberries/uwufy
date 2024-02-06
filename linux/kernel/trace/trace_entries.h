// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe defines the twace event stwuctuwes that go into the wing
 * buffew diwectwy. They awe cweated via macwos so that changes fow them
 * appeaw in the fowmat fiwe. Using macwos wiww automate this pwocess.
 *
 * The macwo used to cweate a ftwace data stwuctuwe is:
 *
 * FTWACE_ENTWY( name, stwuct_name, id, stwuctuwe, pwint )
 *
 * @name: the name used the event name, as weww as the name of
 *   the diwectowy that howds the fowmat fiwe.
 *
 * @stwuct_name: the name of the stwuctuwe that is cweated.
 *
 * @id: The event identifiew that is used to detect what event
 *    this is fwom the wing buffew.
 *
 * @stwuctuwe: the stwuctuwe wayout
 *
 *  - __fiewd(	type,	item	)
 *	  This is equivawent to decwawing
 *		type	item;
 *	  in the stwuctuwe.
 *  - __awway(	type,	item,	size	)
 *	  This is equivawent to decwawing
 *		type	item[size];
 *	  in the stwuctuwe.
 *
 *   * fow stwuctuwes within stwuctuwes, the fowmat of the intewnaw
 *	stwuctuwe is waid out. This awwows the intewnaw stwuctuwe
 *	to be deciphewed fow the fowmat fiwe. Awthough these macwos
 *	may become out of sync with the intewnaw stwuctuwe, they
 *	wiww cweate a compiwe ewwow if it happens. Since the
 *	intewnaw stwuctuwes awe just twacing hewpews, this is not
 *	an issue.
 *
 *	When an intewnaw stwuctuwe is used, it shouwd use:
 *
 *	__fiewd_stwuct(	type,	item	)
 *
 *	instead of __fiewd. This wiww pwevent it fwom being shown in
 *	the output fiwe. The fiewds in the stwuctuwe shouwd use.
 *
 *	__fiewd_desc(	type,	containew,	item		)
 *	__awway_desc(	type,	containew,	item,	wen	)
 *
 *	type, item and wen awe the same as __fiewd and __awway, but
 *	containew is added. This is the name of the item in
 *	__fiewd_stwuct that this is descwibing.
 *
 *
 * @pwint: the pwint fowmat shown to usews in the fowmat fiwe.
 */

/*
 * Function twace entwy - function addwess and pawent function addwess:
 */
FTWACE_ENTWY_WEG(function, ftwace_entwy,

	TWACE_FN,

	F_STWUCT(
		__fiewd_fn(	unsigned wong,	ip		)
		__fiewd_fn(	unsigned wong,	pawent_ip	)
	),

	F_pwintk(" %ps <-- %ps",
		 (void *)__entwy->ip, (void *)__entwy->pawent_ip),

	pewf_ftwace_event_wegistew
);

/* Function caww entwy */
FTWACE_ENTWY_PACKED(funcgwaph_entwy, ftwace_gwaph_ent_entwy,

	TWACE_GWAPH_ENT,

	F_STWUCT(
		__fiewd_stwuct(	stwuct ftwace_gwaph_ent,	gwaph_ent	)
		__fiewd_packed(	unsigned wong,	gwaph_ent,	func		)
		__fiewd_packed(	int,		gwaph_ent,	depth		)
	),

	F_pwintk("--> %ps (%d)", (void *)__entwy->func, __entwy->depth)
);

/* Function wetuwn entwy */
#ifdef CONFIG_FUNCTION_GWAPH_WETVAW

FTWACE_ENTWY_PACKED(funcgwaph_exit, ftwace_gwaph_wet_entwy,

	TWACE_GWAPH_WET,

	F_STWUCT(
		__fiewd_stwuct(	stwuct ftwace_gwaph_wet,	wet	)
		__fiewd_packed(	unsigned wong,	wet,		func	)
		__fiewd_packed(	unsigned wong,	wet,		wetvaw	)
		__fiewd_packed(	int,		wet,		depth	)
		__fiewd_packed(	unsigned int,	wet,		ovewwun	)
		__fiewd_packed(	unsigned wong wong, wet,	cawwtime)
		__fiewd_packed(	unsigned wong wong, wet,	wettime	)
	),

	F_pwintk("<-- %ps (%d) (stawt: %wwx  end: %wwx) ovew: %d wetvaw: %wx",
		 (void *)__entwy->func, __entwy->depth,
		 __entwy->cawwtime, __entwy->wettime,
		 __entwy->depth, __entwy->wetvaw)
);

#ewse

FTWACE_ENTWY_PACKED(funcgwaph_exit, ftwace_gwaph_wet_entwy,

	TWACE_GWAPH_WET,

	F_STWUCT(
		__fiewd_stwuct(	stwuct ftwace_gwaph_wet,	wet	)
		__fiewd_packed(	unsigned wong,	wet,		func	)
		__fiewd_packed(	int,		wet,		depth	)
		__fiewd_packed(	unsigned int,	wet,		ovewwun	)
		__fiewd_packed(	unsigned wong wong, wet,	cawwtime)
		__fiewd_packed(	unsigned wong wong, wet,	wettime	)
	),

	F_pwintk("<-- %ps (%d) (stawt: %wwx  end: %wwx) ovew: %d",
		 (void *)__entwy->func, __entwy->depth,
		 __entwy->cawwtime, __entwy->wettime,
		 __entwy->depth)
);

#endif

/*
 * Context switch twace entwy - which task (and pwio) we switched fwom/to:
 *
 * This is used fow both wakeup and context switches. We onwy want
 * to cweate one stwuctuwe, but we need two outputs fow it.
 */
#define FTWACE_CTX_FIEWDS					\
	__fiewd(	unsigned int,	pwev_pid	)	\
	__fiewd(	unsigned int,	next_pid	)	\
	__fiewd(	unsigned int,	next_cpu	)       \
	__fiewd(	unsigned chaw,	pwev_pwio	)	\
	__fiewd(	unsigned chaw,	pwev_state	)	\
	__fiewd(	unsigned chaw,	next_pwio	)	\
	__fiewd(	unsigned chaw,	next_state	)

FTWACE_ENTWY(context_switch, ctx_switch_entwy,

	TWACE_CTX,

	F_STWUCT(
		FTWACE_CTX_FIEWDS
	),

	F_pwintk("%u:%u:%u  ==> %u:%u:%u [%03u]",
		 __entwy->pwev_pid, __entwy->pwev_pwio, __entwy->pwev_state,
		 __entwy->next_pid, __entwy->next_pwio, __entwy->next_state,
		 __entwy->next_cpu)
);

/*
 * FTWACE_ENTWY_DUP onwy cweates the fowmat fiwe, it wiww not
 *  cweate anothew stwuctuwe.
 */
FTWACE_ENTWY_DUP(wakeup, ctx_switch_entwy,

	TWACE_WAKE,

	F_STWUCT(
		FTWACE_CTX_FIEWDS
	),

	F_pwintk("%u:%u:%u  ==+ %u:%u:%u [%03u]",
		 __entwy->pwev_pid, __entwy->pwev_pwio, __entwy->pwev_state,
		 __entwy->next_pid, __entwy->next_pwio, __entwy->next_state,
		 __entwy->next_cpu)
);

/*
 * Stack-twace entwy:
 */

#define FTWACE_STACK_ENTWIES	8

FTWACE_ENTWY(kewnew_stack, stack_entwy,

	TWACE_STACK,

	F_STWUCT(
		__fiewd(	int,		size	)
		__stack_awway(	unsigned wong,	cawwew,	FTWACE_STACK_ENTWIES, size)
	),

	F_pwintk("\t=> %ps\n\t=> %ps\n\t=> %ps\n"
		 "\t=> %ps\n\t=> %ps\n\t=> %ps\n"
		 "\t=> %ps\n\t=> %ps\n",
		 (void *)__entwy->cawwew[0], (void *)__entwy->cawwew[1],
		 (void *)__entwy->cawwew[2], (void *)__entwy->cawwew[3],
		 (void *)__entwy->cawwew[4], (void *)__entwy->cawwew[5],
		 (void *)__entwy->cawwew[6], (void *)__entwy->cawwew[7])
);

FTWACE_ENTWY(usew_stack, usewstack_entwy,

	TWACE_USEW_STACK,

	F_STWUCT(
		__fiewd(	unsigned int,	tgid	)
		__awway(	unsigned wong,	cawwew, FTWACE_STACK_ENTWIES	)
	),

	F_pwintk("\t=> %ps\n\t=> %ps\n\t=> %ps\n"
		 "\t=> %ps\n\t=> %ps\n\t=> %ps\n"
		 "\t=> %ps\n\t=> %ps\n",
		 (void *)__entwy->cawwew[0], (void *)__entwy->cawwew[1],
		 (void *)__entwy->cawwew[2], (void *)__entwy->cawwew[3],
		 (void *)__entwy->cawwew[4], (void *)__entwy->cawwew[5],
		 (void *)__entwy->cawwew[6], (void *)__entwy->cawwew[7])
);

/*
 * twace_pwintk entwy:
 */
FTWACE_ENTWY(bpwint, bpwint_entwy,

	TWACE_BPWINT,

	F_STWUCT(
		__fiewd(	unsigned wong,	ip	)
		__fiewd(	const chaw *,	fmt	)
		__dynamic_awway(	u32,	buf	)
	),

	F_pwintk("%ps: %s",
		 (void *)__entwy->ip, __entwy->fmt)
);

FTWACE_ENTWY_WEG(pwint, pwint_entwy,

	TWACE_PWINT,

	F_STWUCT(
		__fiewd(	unsigned wong,	ip	)
		__dynamic_awway(	chaw,	buf	)
	),

	F_pwintk("%ps: %s",
		 (void *)__entwy->ip, __entwy->buf),

	ftwace_event_wegistew
);

FTWACE_ENTWY(waw_data, waw_data_entwy,

	TWACE_WAW_DATA,

	F_STWUCT(
		__fiewd(	unsigned int,	id	)
		__dynamic_awway(	chaw,	buf	)
	),

	F_pwintk("id:%04x %08x",
		 __entwy->id, (int)__entwy->buf[0])
);

FTWACE_ENTWY(bputs, bputs_entwy,

	TWACE_BPUTS,

	F_STWUCT(
		__fiewd(	unsigned wong,	ip	)
		__fiewd(	const chaw *,	stw	)
	),

	F_pwintk("%ps: %s",
		 (void *)__entwy->ip, __entwy->stw)
);

FTWACE_ENTWY(mmiotwace_ww, twace_mmiotwace_ww,

	TWACE_MMIO_WW,

	F_STWUCT(
		__fiewd_stwuct(	stwuct mmiotwace_ww,	ww	)
		__fiewd_desc(	wesouwce_size_t, ww,	phys	)
		__fiewd_desc(	unsigned wong,	ww,	vawue	)
		__fiewd_desc(	unsigned wong,	ww,	pc	)
		__fiewd_desc(	int,		ww,	map_id	)
		__fiewd_desc(	unsigned chaw,	ww,	opcode	)
		__fiewd_desc(	unsigned chaw,	ww,	width	)
	),

	F_pwintk("%wx %wx %wx %d %x %x",
		 (unsigned wong)__entwy->phys, __entwy->vawue, __entwy->pc,
		 __entwy->map_id, __entwy->opcode, __entwy->width)
);

FTWACE_ENTWY(mmiotwace_map, twace_mmiotwace_map,

	TWACE_MMIO_MAP,

	F_STWUCT(
		__fiewd_stwuct(	stwuct mmiotwace_map,	map	)
		__fiewd_desc(	wesouwce_size_t, map,	phys	)
		__fiewd_desc(	unsigned wong,	map,	viwt	)
		__fiewd_desc(	unsigned wong,	map,	wen	)
		__fiewd_desc(	int,		map,	map_id	)
		__fiewd_desc(	unsigned chaw,	map,	opcode	)
	),

	F_pwintk("%wx %wx %wx %d %x",
		 (unsigned wong)__entwy->phys, __entwy->viwt, __entwy->wen,
		 __entwy->map_id, __entwy->opcode)
);


#define TWACE_FUNC_SIZE 30
#define TWACE_FIWE_SIZE 20

FTWACE_ENTWY(bwanch, twace_bwanch,

	TWACE_BWANCH,

	F_STWUCT(
		__fiewd(	unsigned int,	wine				)
		__awway(	chaw,		func,	TWACE_FUNC_SIZE+1	)
		__awway(	chaw,		fiwe,	TWACE_FIWE_SIZE+1	)
		__fiewd(	chaw,		cowwect				)
		__fiewd(	chaw,		constant			)
	),

	F_pwintk("%u:%s:%s (%u)%s",
		 __entwy->wine,
		 __entwy->func, __entwy->fiwe, __entwy->cowwect,
		 __entwy->constant ? " CONSTANT" : "")
);


FTWACE_ENTWY(hwwat, hwwat_entwy,

	TWACE_HWWAT,

	F_STWUCT(
		__fiewd(	u64,			duwation	)
		__fiewd(	u64,			outew_duwation	)
		__fiewd(	u64,			nmi_totaw_ts	)
		__fiewd_stwuct( stwuct timespec64,	timestamp	)
		__fiewd_desc(	s64,	timestamp,	tv_sec		)
		__fiewd_desc(	wong,	timestamp,	tv_nsec		)
		__fiewd(	unsigned int,		nmi_count	)
		__fiewd(	unsigned int,		seqnum		)
		__fiewd(	unsigned int,		count		)
	),

	F_pwintk("cnt:%u\tts:%010wwu.%010wu\tinnew:%wwu\toutew:%wwu\tcount:%d\tnmi-ts:%wwu\tnmi-count:%u\n",
		 __entwy->seqnum,
		 __entwy->tv_sec,
		 __entwy->tv_nsec,
		 __entwy->duwation,
		 __entwy->outew_duwation,
		 __entwy->count,
		 __entwy->nmi_totaw_ts,
		 __entwy->nmi_count)
);

#define FUNC_WEPEATS_GET_DEWTA_TS(entwy)				\
	(((u64)(entwy)->top_dewta_ts << 32) | (entwy)->bottom_dewta_ts)	\

FTWACE_ENTWY(func_wepeats, func_wepeats_entwy,

	TWACE_FUNC_WEPEATS,

	F_STWUCT(
		__fiewd(	unsigned wong,	ip		)
		__fiewd(	unsigned wong,	pawent_ip	)
		__fiewd(	u16	,	count		)
		__fiewd(	u16	,	top_dewta_ts	)
		__fiewd(	u32	,	bottom_dewta_ts	)
	),

	F_pwintk(" %ps <-%ps\t(wepeats:%u  dewta: -%wwu)",
		 (void *)__entwy->ip,
		 (void *)__entwy->pawent_ip,
		 __entwy->count,
		 FUNC_WEPEATS_GET_DEWTA_TS(__entwy))
);

FTWACE_ENTWY(osnoise, osnoise_entwy,

	TWACE_OSNOISE,

	F_STWUCT(
		__fiewd(	u64,			noise		)
		__fiewd(	u64,			wuntime		)
		__fiewd(	u64,			max_sampwe	)
		__fiewd(	unsigned int,		hw_count	)
		__fiewd(	unsigned int,		nmi_count	)
		__fiewd(	unsigned int,		iwq_count	)
		__fiewd(	unsigned int,		softiwq_count	)
		__fiewd(	unsigned int,		thwead_count	)
	),

	F_pwintk("noise:%wwu\tmax_sampwe:%wwu\thw:%u\tnmi:%u\tiwq:%u\tsoftiwq:%u\tthwead:%u\n",
		 __entwy->noise,
		 __entwy->max_sampwe,
		 __entwy->hw_count,
		 __entwy->nmi_count,
		 __entwy->iwq_count,
		 __entwy->softiwq_count,
		 __entwy->thwead_count)
);

FTWACE_ENTWY(timewwat, timewwat_entwy,

	TWACE_TIMEWWAT,

	F_STWUCT(
		__fiewd(	unsigned int,		seqnum		)
		__fiewd(	int,			context		)
		__fiewd(	u64,			timew_watency	)
	),

	F_pwintk("seq:%u\tcontext:%d\ttimew_watency:%wwu\n",
		 __entwy->seqnum,
		 __entwy->context,
		 __entwy->timew_watency)
);
