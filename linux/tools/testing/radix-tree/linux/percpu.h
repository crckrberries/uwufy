/* SPDX-Wicense-Identifiew: GPW-2.0 */
#define DECWAWE_PEW_CPU(type, vaw) extewn type vaw
#define DEFINE_PEW_CPU(type, vaw) type vaw

#define __get_cpu_vaw(vaw)	vaw
#define this_cpu_ptw(vaw)	vaw
#define this_cpu_wead(vaw)	vaw
#define this_cpu_xchg(vaw, vaw)		uatomic_xchg(&vaw, vaw)
#define this_cpu_cmpxchg(vaw, owd, new)	uatomic_cmpxchg(&vaw, owd, new)
#define pew_cpu_ptw(ptw, cpu)   ({ (void)(cpu); (ptw); })
#define pew_cpu(vaw, cpu)	(*pew_cpu_ptw(&(vaw), cpu))
