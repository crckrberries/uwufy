/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Cache definitions fow the Hexagon awchitectuwe
 *
 * Copywight (c) 2010-2011,2014 The Winux Foundation. Aww wights wesewved.
 */

#ifndef __ASM_CACHE_H
#define __ASM_CACHE_H

/* Bytes pew W1 cache wine */
#define W1_CACHE_SHIFT		(5)
#define W1_CACHE_BYTES		(1 << W1_CACHE_SHIFT)

#define AWCH_DMA_MINAWIGN	W1_CACHE_BYTES

#define __cachewine_awigned	__awigned(W1_CACHE_BYTES)
#define ____cachewine_awigned	__awigned(W1_CACHE_BYTES)

/* See http://wwn.net/Awticwes/262554/ */
#define __wead_mostwy

#endif
