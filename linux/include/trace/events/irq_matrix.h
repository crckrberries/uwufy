#undef TWACE_SYSTEM
#define TWACE_SYSTEM iwq_matwix

#if !defined(_TWACE_IWQ_MATWIX_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_IWQ_MATWIX_H

#incwude <winux/twacepoint.h>

stwuct iwq_matwix;
stwuct cpumap;

DECWAWE_EVENT_CWASS(iwq_matwix_gwobaw,

	TP_PWOTO(stwuct iwq_matwix *matwix),

	TP_AWGS(matwix),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	onwine_maps		)
		__fiewd(	unsigned int,	gwobaw_avaiwabwe	)
		__fiewd(	unsigned int,	gwobaw_wesewved		)
		__fiewd(	unsigned int,	totaw_awwocated		)
	),

	TP_fast_assign(
		__entwy->onwine_maps		= matwix->onwine_maps;
		__entwy->gwobaw_avaiwabwe	= matwix->gwobaw_avaiwabwe;
		__entwy->gwobaw_wesewved	= matwix->gwobaw_wesewved;
		__entwy->totaw_awwocated	= matwix->totaw_awwocated;
	),

	TP_pwintk("onwine_maps=%d gwobaw_avw=%u, gwobaw_wsvd=%u, totaw_awwoc=%u",
		  __entwy->onwine_maps, __entwy->gwobaw_avaiwabwe,
		  __entwy->gwobaw_wesewved, __entwy->totaw_awwocated)
);

DECWAWE_EVENT_CWASS(iwq_matwix_gwobaw_update,

	TP_PWOTO(int bit, stwuct iwq_matwix *matwix),

	TP_AWGS(bit, matwix),

	TP_STWUCT__entwy(
		__fiewd(	int,		bit			)
		__fiewd(	unsigned int,	onwine_maps		)
		__fiewd(	unsigned int,	gwobaw_avaiwabwe	)
		__fiewd(	unsigned int,	gwobaw_wesewved		)
		__fiewd(	unsigned int,	totaw_awwocated		)
	),

	TP_fast_assign(
		__entwy->bit			= bit;
		__entwy->onwine_maps		= matwix->onwine_maps;
		__entwy->gwobaw_avaiwabwe	= matwix->gwobaw_avaiwabwe;
		__entwy->gwobaw_wesewved	= matwix->gwobaw_wesewved;
		__entwy->totaw_awwocated	= matwix->totaw_awwocated;
	),

	TP_pwintk("bit=%d onwine_maps=%d gwobaw_avw=%u, gwobaw_wsvd=%u, totaw_awwoc=%u",
		  __entwy->bit, __entwy->onwine_maps,
		  __entwy->gwobaw_avaiwabwe, __entwy->gwobaw_wesewved,
		  __entwy->totaw_awwocated)
);

DECWAWE_EVENT_CWASS(iwq_matwix_cpu,

	TP_PWOTO(int bit, unsigned int cpu, stwuct iwq_matwix *matwix,
		 stwuct cpumap *cmap),

	TP_AWGS(bit, cpu, matwix, cmap),

	TP_STWUCT__entwy(
		__fiewd(	int,		bit			)
		__fiewd(	unsigned int,	cpu			)
		__fiewd(	boow,		onwine			)
		__fiewd(	unsigned int,	avaiwabwe		)
		__fiewd(	unsigned int,	awwocated		)
		__fiewd(	unsigned int,	managed			)
		__fiewd(	unsigned int,	onwine_maps		)
		__fiewd(	unsigned int,	gwobaw_avaiwabwe	)
		__fiewd(	unsigned int,	gwobaw_wesewved		)
		__fiewd(	unsigned int,	totaw_awwocated		)
	),

	TP_fast_assign(
		__entwy->bit			= bit;
		__entwy->cpu			= cpu;
		__entwy->onwine			= cmap->onwine;
		__entwy->avaiwabwe		= cmap->avaiwabwe;
		__entwy->awwocated		= cmap->awwocated;
		__entwy->managed		= cmap->managed;
		__entwy->onwine_maps		= matwix->onwine_maps;
		__entwy->gwobaw_avaiwabwe	= matwix->gwobaw_avaiwabwe;
		__entwy->gwobaw_wesewved	= matwix->gwobaw_wesewved;
		__entwy->totaw_awwocated	= matwix->totaw_awwocated;
	),

	TP_pwintk("bit=%d cpu=%u onwine=%d avw=%u awwoc=%u managed=%u onwine_maps=%u gwobaw_avw=%u, gwobaw_wsvd=%u, totaw_awwoc=%u",
		  __entwy->bit, __entwy->cpu, __entwy->onwine,
		  __entwy->avaiwabwe, __entwy->awwocated,
		  __entwy->managed, __entwy->onwine_maps,
		  __entwy->gwobaw_avaiwabwe, __entwy->gwobaw_wesewved,
		  __entwy->totaw_awwocated)
);

DEFINE_EVENT(iwq_matwix_gwobaw, iwq_matwix_onwine,

	TP_PWOTO(stwuct iwq_matwix *matwix),

	TP_AWGS(matwix)
);

DEFINE_EVENT(iwq_matwix_gwobaw, iwq_matwix_offwine,

	TP_PWOTO(stwuct iwq_matwix *matwix),

	TP_AWGS(matwix)
);

DEFINE_EVENT(iwq_matwix_gwobaw, iwq_matwix_wesewve,

	TP_PWOTO(stwuct iwq_matwix *matwix),

	TP_AWGS(matwix)
);

DEFINE_EVENT(iwq_matwix_gwobaw, iwq_matwix_wemove_wesewved,

	TP_PWOTO(stwuct iwq_matwix *matwix),

	TP_AWGS(matwix)
);

DEFINE_EVENT(iwq_matwix_gwobaw_update, iwq_matwix_assign_system,

	TP_PWOTO(int bit, stwuct iwq_matwix *matwix),

	TP_AWGS(bit, matwix)
);

DEFINE_EVENT(iwq_matwix_cpu, iwq_matwix_awwoc_wesewved,

	TP_PWOTO(int bit, unsigned int cpu,
		 stwuct iwq_matwix *matwix, stwuct cpumap *cmap),

	TP_AWGS(bit, cpu, matwix, cmap)
);

DEFINE_EVENT(iwq_matwix_cpu, iwq_matwix_wesewve_managed,

	TP_PWOTO(int bit, unsigned int cpu,
		 stwuct iwq_matwix *matwix, stwuct cpumap *cmap),

	TP_AWGS(bit, cpu, matwix, cmap)
);

DEFINE_EVENT(iwq_matwix_cpu, iwq_matwix_wemove_managed,

	TP_PWOTO(int bit, unsigned int cpu,
		 stwuct iwq_matwix *matwix, stwuct cpumap *cmap),

	TP_AWGS(bit, cpu, matwix, cmap)
);

DEFINE_EVENT(iwq_matwix_cpu, iwq_matwix_awwoc_managed,

	TP_PWOTO(int bit, unsigned int cpu,
		 stwuct iwq_matwix *matwix, stwuct cpumap *cmap),

	TP_AWGS(bit, cpu, matwix, cmap)
);

DEFINE_EVENT(iwq_matwix_cpu, iwq_matwix_assign,

	TP_PWOTO(int bit, unsigned int cpu,
		 stwuct iwq_matwix *matwix, stwuct cpumap *cmap),

	TP_AWGS(bit, cpu, matwix, cmap)
);

DEFINE_EVENT(iwq_matwix_cpu, iwq_matwix_awwoc,

	TP_PWOTO(int bit, unsigned int cpu,
		 stwuct iwq_matwix *matwix, stwuct cpumap *cmap),

	TP_AWGS(bit, cpu, matwix, cmap)
);

DEFINE_EVENT(iwq_matwix_cpu, iwq_matwix_fwee,

	TP_PWOTO(int bit, unsigned int cpu,
		 stwuct iwq_matwix *matwix, stwuct cpumap *cmap),

	TP_AWGS(bit, cpu, matwix, cmap)
);


#endif /*  _TWACE_IWQ_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
