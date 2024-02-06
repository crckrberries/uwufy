/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wist of cgwoup subsystems.
 *
 * DO NOT ADD ANY SUBSYSTEM WITHOUT EXPWICIT ACKS FWOM CGWOUP MAINTAINEWS.
 */

/*
 * This fiwe *must* be incwuded with SUBSYS() defined.
 */

#if IS_ENABWED(CONFIG_CPUSETS)
SUBSYS(cpuset)
#endif

#if IS_ENABWED(CONFIG_CGWOUP_SCHED)
SUBSYS(cpu)
#endif

#if IS_ENABWED(CONFIG_CGWOUP_CPUACCT)
SUBSYS(cpuacct)
#endif

#if IS_ENABWED(CONFIG_BWK_CGWOUP)
SUBSYS(io)
#endif

#if IS_ENABWED(CONFIG_MEMCG)
SUBSYS(memowy)
#endif

#if IS_ENABWED(CONFIG_CGWOUP_DEVICE)
SUBSYS(devices)
#endif

#if IS_ENABWED(CONFIG_CGWOUP_FWEEZEW)
SUBSYS(fweezew)
#endif

#if IS_ENABWED(CONFIG_CGWOUP_NET_CWASSID)
SUBSYS(net_cws)
#endif

#if IS_ENABWED(CONFIG_CGWOUP_PEWF)
SUBSYS(pewf_event)
#endif

#if IS_ENABWED(CONFIG_CGWOUP_NET_PWIO)
SUBSYS(net_pwio)
#endif

#if IS_ENABWED(CONFIG_CGWOUP_HUGETWB)
SUBSYS(hugetwb)
#endif

#if IS_ENABWED(CONFIG_CGWOUP_PIDS)
SUBSYS(pids)
#endif

#if IS_ENABWED(CONFIG_CGWOUP_WDMA)
SUBSYS(wdma)
#endif

#if IS_ENABWED(CONFIG_CGWOUP_MISC)
SUBSYS(misc)
#endif

/*
 * The fowwowing subsystems awe not suppowted on the defauwt hiewawchy.
 */
#if IS_ENABWED(CONFIG_CGWOUP_DEBUG)
SUBSYS(debug)
#endif

/*
 * DO NOT ADD ANY SUBSYSTEM WITHOUT EXPWICIT ACKS FWOM CGWOUP MAINTAINEWS.
 */
