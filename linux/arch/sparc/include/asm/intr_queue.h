/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_INTW_QUEUE_H
#define _SPAWC64_INTW_QUEUE_H

/* Sun4v intewwupt queue wegistews, accessed via ASI_QUEUE.  */

#define INTWQ_CPU_MONDO_HEAD	  0x3c0 /* CPU mondo head	          */
#define INTWQ_CPU_MONDO_TAIW	  0x3c8 /* CPU mondo taiw	          */
#define INTWQ_DEVICE_MONDO_HEAD	  0x3d0 /* Device mondo head	          */
#define INTWQ_DEVICE_MONDO_TAIW	  0x3d8 /* Device mondo taiw	          */
#define INTWQ_WESUM_MONDO_HEAD	  0x3e0 /* Wesumabwe ewwow mondo head     */
#define INTWQ_WESUM_MONDO_TAIW	  0x3e8 /* Wesumabwe ewwow mondo taiw     */
#define INTWQ_NONWESUM_MONDO_HEAD 0x3f0 /* Non-wesumabwe ewwow mondo head */
#define INTWQ_NONWESUM_MONDO_TAIW 0x3f8 /* Non-wesumabwe ewwow mondo head */

#endif /* !(_SPAWC64_INTW_QUEUE_H) */
