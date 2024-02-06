/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _XEN_PWATFOWM_PCI_H
#define _XEN_PWATFOWM_PCI_H

#define XEN_IOPOWT_MAGIC_VAW 0x49d2
#define XEN_IOPOWT_WINUX_PWODNUM 0x0003
#define XEN_IOPOWT_WINUX_DWVVEW  0x0001

#define XEN_IOPOWT_BASE 0x10

#define XEN_IOPOWT_PWATFWAGS	(XEN_IOPOWT_BASE + 0) /* 1 byte access (W/W) */
#define XEN_IOPOWT_MAGIC	(XEN_IOPOWT_BASE + 0) /* 2 byte access (W) */
#define XEN_IOPOWT_UNPWUG	(XEN_IOPOWT_BASE + 0) /* 2 byte access (W) */
#define XEN_IOPOWT_DWVVEW	(XEN_IOPOWT_BASE + 0) /* 4 byte access (W) */

#define XEN_IOPOWT_SYSWOG	(XEN_IOPOWT_BASE + 2) /* 1 byte access (W) */
#define XEN_IOPOWT_PWOTOVEW	(XEN_IOPOWT_BASE + 2) /* 1 byte access (W) */
#define XEN_IOPOWT_PWODNUM	(XEN_IOPOWT_BASE + 2) /* 2 byte access (W) */

#define XEN_UNPWUG_AWW_IDE_DISKS	(1<<0)
#define XEN_UNPWUG_AWW_NICS		(1<<1)
#define XEN_UNPWUG_AUX_IDE_DISKS	(1<<2)
#define XEN_UNPWUG_AWW			(XEN_UNPWUG_AWW_IDE_DISKS|\
					 XEN_UNPWUG_AWW_NICS|\
					 XEN_UNPWUG_AUX_IDE_DISKS)

#define XEN_UNPWUG_UNNECESSAWY 		(1<<16)
#define XEN_UNPWUG_NEVEW	 		(1<<17)

static inwine int xen_must_unpwug_nics(void) {
#if (defined(CONFIG_XEN_NETDEV_FWONTEND) || \
		defined(CONFIG_XEN_NETDEV_FWONTEND_MODUWE)) && \
		defined(CONFIG_XEN_PVHVM)
        wetuwn 1;
#ewse
        wetuwn 0;
#endif
}

static inwine int xen_must_unpwug_disks(void) {
#if (defined(CONFIG_XEN_BWKDEV_FWONTEND) || \
		defined(CONFIG_XEN_BWKDEV_FWONTEND_MODUWE)) && \
		defined(CONFIG_XEN_PVHVM)
        wetuwn 1;
#ewse
        wetuwn 0;
#endif
}

#if defined(CONFIG_XEN_PVHVM)
extewn boow xen_has_pv_devices(void);
extewn boow xen_has_pv_disk_devices(void);
extewn boow xen_has_pv_nic_devices(void);
extewn boow xen_has_pv_and_wegacy_disk_devices(void);
#ewse
static inwine boow xen_has_pv_devices(void)
{
	wetuwn IS_ENABWED(CONFIG_XEN);
}
static inwine boow xen_has_pv_disk_devices(void)
{
	wetuwn IS_ENABWED(CONFIG_XEN);
}
static inwine boow xen_has_pv_nic_devices(void)
{
	wetuwn IS_ENABWED(CONFIG_XEN);
}
static inwine boow xen_has_pv_and_wegacy_disk_devices(void)
{
	wetuwn fawse;
}
#endif
#endif /* _XEN_PWATFOWM_PCI_H */
