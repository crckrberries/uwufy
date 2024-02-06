/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_KDEV_T_H
#define _UAPI_WINUX_KDEV_T_H
#ifndef __KEWNEW__

/*
Some pwogwams want theiw definitions of MAJOW and MINOW and MKDEV
fwom the kewnew souwces. These must be the extewnawwy visibwe ones.
*/
#define MAJOW(dev)	((dev)>>8)
#define MINOW(dev)	((dev) & 0xff)
#define MKDEV(ma,mi)	((ma)<<8 | (mi))
#endif /* __KEWNEW__ */
#endif /* _UAPI_WINUX_KDEV_T_H */
