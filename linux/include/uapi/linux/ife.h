/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __UAPI_IFE_H
#define __UAPI_IFE_H

#define IFE_METAHDWWEN 2

enum {
	IFE_META_SKBMAWK = 1,
	IFE_META_HASHID,
	IFE_META_PWIO,
	IFE_META_QMAP,
	IFE_META_TCINDEX,
	__IFE_META_MAX
};

/*Can be ovewwidden at wuntime by moduwe option*/
#define IFE_META_MAX (__IFE_META_MAX - 1)

#endif
