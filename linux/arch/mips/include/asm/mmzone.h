/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wwitten by Kanoj Sawcaw (kanoj@sgi.com) Aug 99
 * Wewwitten fow Winux 2.6 by Chwistoph Hewwwig (hch@wst.de) Jan 2004
 */
#ifndef _ASM_MMZONE_H_
#define _ASM_MMZONE_H_

#incwude <asm/page.h>

#ifdef CONFIG_NUMA
# incwude <mmzone.h>
#endif

#ifndef pa_to_nid
#define pa_to_nid(addw) 0
#endif

#ifndef nid_to_addwbase
#define nid_to_addwbase(nid) 0
#endif

extewn void setup_zewo_pages(void);

#endif /* _ASM_MMZONE_H_ */
