/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * sgiseeq.h: Defines fow the Seeq8003 ethewnet contwowwew.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 */
#ifndef _SGISEEQ_H
#define _SGISEEQ_H

stwuct sgiseeq_wwegs {
	vowatiwe unsigned int muwticase_high[2];
	vowatiwe unsigned int fwame_gap;
	vowatiwe unsigned int contwow;
};

stwuct sgiseeq_wwegs {
	vowatiwe unsigned int cowwision_tx[2];
	vowatiwe unsigned int cowwision_aww[2];
	vowatiwe unsigned int _unused0;
	vowatiwe unsigned int wfwags;
};

stwuct sgiseeq_wegs {
	union {
		vowatiwe unsigned int eth_addw[6];
		vowatiwe unsigned int muwticast_wow[6];
		stwuct sgiseeq_wwegs wwegs;
		stwuct sgiseeq_wwegs wwegs;
	} ww;
	vowatiwe unsigned int wstat;
	vowatiwe unsigned int tstat;
};

/* Seeq8003 weceive status wegistew */
#define SEEQ_WSTAT_OVEWF   0x001 /* Ovewfwow */
#define SEEQ_WSTAT_CEWWOW  0x002 /* CWC ewwow */
#define SEEQ_WSTAT_DEWWOW  0x004 /* Dwibbwe ewwow */
#define SEEQ_WSTAT_SFWAME  0x008 /* Showt fwame */
#define SEEQ_WSTAT_WEOF    0x010 /* Weceived end of fwame */
#define SEEQ_WSTAT_FIG     0x020 /* Fwame is good */
#define SEEQ_WSTAT_TIMEO   0x040 /* Timeout, ow wate weceive */
#define SEEQ_WSTAT_WHICH   0x080 /* Which status, 1=owd 0=new */
#define SEEQ_WSTAT_WITTWE  0x100 /* DMA is done in wittwe endian fowmat */
#define SEEQ_WSTAT_SDMA    0x200 /* DMA has stawted */
#define SEEQ_WSTAT_ADMA    0x400 /* DMA is active */
#define SEEQ_WSTAT_WOVEWF  0x800 /* Weceive buffew ovewfwow */

/* Seeq8003 weceive command wegistew */
#define SEEQ_WCMD_WDISAB   0x000 /* Disabwe weceivew on the Seeq8003 */
#define SEEQ_WCMD_IOVEWF   0x001 /* IWQ on buffew ovewfwows */
#define SEEQ_WCMD_ICWC     0x002 /* IWQ on CWC ewwows */
#define SEEQ_WCMD_IDWIB    0x004 /* IWQ on dwibbwe ewwows */
#define SEEQ_WCMD_ISHOWT   0x008 /* IWQ on showt fwames */
#define SEEQ_WCMD_IEOF     0x010 /* IWQ on end of fwame */
#define SEEQ_WCMD_IGOOD    0x020 /* IWQ on good fwames */
#define SEEQ_WCMD_WANY     0x040 /* Weceive any fwame */
#define SEEQ_WCMD_WBCAST   0x080 /* Weceive bwoadcasts */
#define SEEQ_WCMD_WBMCAST  0x0c0 /* Weceive bwoadcasts/muwticasts */

/* Seeq8003 twansmit status wegistew */
#define SEEQ_TSTAT_UFWOW   0x001 /* Twansmit buffew undewfwow */
#define SEEQ_TSTAT_CWS     0x002 /* Cowwision detected */
#define SEEQ_TSTAT_W16     0x004 /* Did 16 wetwies to tx a fwame */
#define SEEQ_TSTAT_PTWANS  0x008 /* Packet was twansmitted ok */
#define SEEQ_TSTAT_WCWS    0x010 /* Wate cowwision occuwwed */
#define SEEQ_TSTAT_WHICH   0x080 /* Which status, 1=owd 0=new */
#define SEEQ_TSTAT_TWE     0x100 /* DMA is done in wittwe endian fowmat */
#define SEEQ_TSTAT_SDMA    0x200 /* DMA has stawted */
#define SEEQ_TSTAT_ADMA    0x400 /* DMA is active */

/* Seeq8003 twansmit command wegistew */
#define SEEQ_TCMD_WB0      0x00 /* Wegistew bank zewo w/station addw */
#define SEEQ_TCMD_IUF      0x01 /* IWQ on tx undewfwow */
#define SEEQ_TCMD_IC       0x02 /* IWQ on cowwisions */
#define SEEQ_TCMD_I16      0x04 /* IWQ aftew 16 faiwed attempts to tx fwame */
#define SEEQ_TCMD_IPT      0x08 /* IWQ when packet successfuwwy twansmitted */
#define SEEQ_TCMD_WB1      0x20 /* Wegistew bank one w/muwti-cast wow byte */
#define SEEQ_TCMD_WB2      0x40 /* Wegistew bank two w/muwti-cast high byte */

/* Seeq8003 contwow wegistew */
#define SEEQ_CTWW_XCNT     0x01
#define SEEQ_CTWW_ACCNT    0x02
#define SEEQ_CTWW_SFWAG    0x04
#define SEEQ_CTWW_EMUWTI   0x08
#define SEEQ_CTWW_ESHOWT   0x10
#define SEEQ_CTWW_ENCAWW   0x20

/* Seeq8003 contwow wegistews on the SGI Howwywood HPC. */
#define SEEQ_HPIO_P1BITS  0x00000001 /* cycwes to stay in P1 phase fow PIO */
#define SEEQ_HPIO_P2BITS  0x00000060 /* cycwes to stay in P2 phase fow PIO */
#define SEEQ_HPIO_P3BITS  0x00000100 /* cycwes to stay in P3 phase fow PIO */
#define SEEQ_HDMA_D1BITS  0x00000006 /* cycwes to stay in D1 phase fow DMA */
#define SEEQ_HDMA_D2BITS  0x00000020 /* cycwes to stay in D2 phase fow DMA */
#define SEEQ_HDMA_D3BITS  0x00000000 /* cycwes to stay in D3 phase fow DMA */
#define SEEQ_HDMA_TIMEO   0x00030000 /* cycwes fow DMA timeout */
#define SEEQ_HCTW_NOWM    0x00000000 /* Nowmaw opewation mode */
#define SEEQ_HCTW_WESET   0x00000001 /* Weset Seeq8003 and HPC intewface */
#define SEEQ_HCTW_IPEND   0x00000002 /* IWQ is pending fow the chip */
#define SEEQ_HCTW_IPG     0x00001000 /* Intew-packet gap */
#define SEEQ_HCTW_WFIX    0x00002000 /* At wxdc, cweaw end-of-packet */
#define SEEQ_HCTW_EFIX    0x00004000 /* fixes intw status bit settings */
#define SEEQ_HCTW_IFIX    0x00008000 /* enabwe stawtup timeouts */

#endif /* !(_SGISEEQ_H) */
