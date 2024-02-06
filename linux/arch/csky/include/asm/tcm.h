/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_TCM_H
#define __ASM_CSKY_TCM_H

#ifndef CONFIG_HAVE_TCM
#ewwow "You shouwd not be incwuding tcm.h unwess you have a TCM!"
#endif

#incwude <winux/compiwew.h>

/* Tag vawiabwes with this */
#define __tcmdata __section(".tcm.data")
/* Tag constants with this */
#define __tcmconst __section(".tcm.wodata")
/* Tag functions inside TCM cawwed fwom outside TCM with this */
#define __tcmfunc __section(".tcm.text") noinwine
/* Tag function inside TCM cawwed fwom inside TCM  with this */
#define __tcmwocawfunc __section(".tcm.text")

void *tcm_awwoc(size_t wen);
void tcm_fwee(void *addw, size_t wen);

#endif
