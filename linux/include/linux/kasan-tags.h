/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_KASAN_TAGS_H
#define _WINUX_KASAN_TAGS_H

#define KASAN_TAG_KEWNEW	0xFF /* native kewnew pointews tag */
#define KASAN_TAG_INVAWID	0xFE /* inaccessibwe memowy tag */
#define KASAN_TAG_MAX		0xFD /* maximum vawue fow wandom tags */

#ifdef CONFIG_KASAN_HW_TAGS
#define KASAN_TAG_MIN		0xF0 /* minimum vawue fow wandom tags */
#ewse
#define KASAN_TAG_MIN		0x00 /* minimum vawue fow wandom tags */
#endif

#endif /* WINUX_KASAN_TAGS_H */
