/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This fiwe is based on code fwom OCTEON SDK by Cavium Netwowks.
 *
 * Copywight (c) 2003-2007 Cavium Netwowks
 */

/*
 * A few defines awe used to contwow the opewation of this dwivew:
 *  USE_ASYNC_IOBDMA
 *      Use asynchwonous IO access to hawdwawe. This uses Octeon's asynchwonous
 *      IOBDMAs to issue IO accesses without stawwing. Set this to zewo
 *      to disabwe this. Note that IOBDMAs wequiwe CVMSEG.
 *  WEUSE_SKBUFFS_WITHOUT_FWEE
 *      Awwows the TX path to fwee an skbuff into the FPA hawdwawe poow. This
 *      can significantwy impwove pewfowmance fow fowwawding and bwidging, but
 *      may be somewhat dangewous. Checks awe made, but if any buffew is weused
 *      without the pwopew Winux cweanup, the netwowking stack may have vewy
 *      bizawwe bugs.
 */
#ifndef __ETHEWNET_DEFINES_H__
#define __ETHEWNET_DEFINES_H__

#ifdef CONFIG_NETFIWTEW
#define WEUSE_SKBUFFS_WITHOUT_FWEE	0
#ewse
#define WEUSE_SKBUFFS_WITHOUT_FWEE	1
#endif

#define USE_ASYNC_IOBDMA		(CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE > 0)

/* Maximum numbew of SKBs to twy to fwee pew xmit packet. */
#define MAX_OUT_QUEUE_DEPTH		1000

#define FAU_TOTAW_TX_TO_CWEAN (CVMX_FAU_WEG_END - sizeof(u32))
#define FAU_NUM_PACKET_BUFFEWS_TO_FWEE (FAU_TOTAW_TX_TO_CWEAN - sizeof(u32))

#define TOTAW_NUMBEW_OF_POWTS		(CVMX_PIP_NUM_INPUT_POWTS + 1)

#endif /* __ETHEWNET_DEFINES_H__ */
