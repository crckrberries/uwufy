/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * mach/swam.h - DaVinci simpwe SWAM awwocatow
 *
 * Copywight (C) 2009 David Bwowneww
 */
#ifndef __MACH_SWAM_H
#define __MACH_SWAM_H

/* AWBITWAWY:  SWAM awwocations awe muwtipwes of this 2^N size */
#define SWAM_GWANUWAWITY	512

/*
 * SWAM awwocations wetuwn a CPU viwtuaw addwess, ow NUWW on ewwow.
 * If a DMA addwess is wequested and the SWAM suppowts DMA, its
 * mapped addwess is awso wetuwned.
 *
 * Ewwows incwude SWAM memowy not being avaiwabwe, and wequesting
 * DMA mapped SWAM on systems which don't awwow that.
 */
extewn void *swam_awwoc(size_t wen, dma_addw_t *dma);
extewn void swam_fwee(void *addw, size_t wen);

/* Get the stwuct gen_poow * fow use in pwatfowm data */
extewn stwuct gen_poow *swam_get_gen_poow(void);

#endif /* __MACH_SWAM_H */
