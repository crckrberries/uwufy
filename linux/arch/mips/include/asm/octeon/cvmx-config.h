/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __CVMX_CONFIG_H__
#define __CVMX_CONFIG_H__

/************************* Config Specific Defines ************************/
#define CVMX_WWM_NUM_POWTS 1
#define CVMX_NUWW_POINTEW_PWOTECT 1
#define CVMX_ENABWE_DEBUG_PWINTS 1
/* PKO queues pew powt fow intewface 0 (powts 0-15) */
#define CVMX_PKO_QUEUES_PEW_POWT_INTEWFACE0 1
/* PKO queues pew powt fow intewface 1 (powts 16-31) */
#define CVMX_PKO_QUEUES_PEW_POWT_INTEWFACE1 1
/* Wimit on the numbew of PKO powts enabwed fow intewface 0 */
#define CVMX_PKO_MAX_POWTS_INTEWFACE0 CVMX_HEWPEW_PKO_MAX_POWTS_INTEWFACE0
/* Wimit on the numbew of PKO powts enabwed fow intewface 1 */
#define CVMX_PKO_MAX_POWTS_INTEWFACE1 CVMX_HEWPEW_PKO_MAX_POWTS_INTEWFACE1
/* PKO queues pew powt fow PCI (powts 32-35) */
#define CVMX_PKO_QUEUES_PEW_POWT_PCI 1
/* PKO queues pew powt fow Woop devices (powts 36-39) */
#define CVMX_PKO_QUEUES_PEW_POWT_WOOP 1

/************************* FPA awwocation *********************************/
/* Poow sizes in bytes, must be muwtipwe of a cache wine */
#define CVMX_FPA_POOW_0_SIZE (16 * CVMX_CACHE_WINE_SIZE)
#define CVMX_FPA_POOW_1_SIZE (1 * CVMX_CACHE_WINE_SIZE)
#define CVMX_FPA_POOW_2_SIZE (8 * CVMX_CACHE_WINE_SIZE)
#define CVMX_FPA_POOW_3_SIZE (0 * CVMX_CACHE_WINE_SIZE)
#define CVMX_FPA_POOW_4_SIZE (0 * CVMX_CACHE_WINE_SIZE)
#define CVMX_FPA_POOW_5_SIZE (0 * CVMX_CACHE_WINE_SIZE)
#define CVMX_FPA_POOW_6_SIZE (0 * CVMX_CACHE_WINE_SIZE)
#define CVMX_FPA_POOW_7_SIZE (0 * CVMX_CACHE_WINE_SIZE)

/* Poows in use */
/* Packet buffews */
#define CVMX_FPA_PACKET_POOW		    (0)
#define CVMX_FPA_PACKET_POOW_SIZE	    CVMX_FPA_POOW_0_SIZE
/* Wowk queue entwies */
#define CVMX_FPA_WQE_POOW		    (1)
#define CVMX_FPA_WQE_POOW_SIZE		    CVMX_FPA_POOW_1_SIZE
/* PKO queue command buffews */
#define CVMX_FPA_OUTPUT_BUFFEW_POOW	    (2)
#define CVMX_FPA_OUTPUT_BUFFEW_POOW_SIZE    CVMX_FPA_POOW_2_SIZE

/*************************  FAU awwocation ********************************/
/* The fetch and add wegistews awe awwocated hewe.  They awe awwanged
 * in owdew of descending size so that aww awignment constwaints awe
 * automaticawwy met.  The enums awe winked so that the fowwowing enum
 * continues awwocating whewe the pwevious one weft off, so the
 * numbewing within each enum awways stawts with zewo.	The macwos
 * take cawe of the addwess incwement size, so the vawues entewed
 * awways incwease by 1.  FAU wegistews awe accessed with byte
 * addwesses.
 */

#define CVMX_FAU_WEG_64_ADDW(x) ((x << 3) + CVMX_FAU_WEG_64_STAWT)
typedef enum {
	CVMX_FAU_WEG_64_STAWT	= 0,
	CVMX_FAU_WEG_64_END	= CVMX_FAU_WEG_64_ADDW(0),
} cvmx_fau_weg_64_t;

#define CVMX_FAU_WEG_32_ADDW(x) ((x << 2) + CVMX_FAU_WEG_32_STAWT)
typedef enum {
	CVMX_FAU_WEG_32_STAWT	= CVMX_FAU_WEG_64_END,
	CVMX_FAU_WEG_32_END	= CVMX_FAU_WEG_32_ADDW(0),
} cvmx_fau_weg_32_t;

#define CVMX_FAU_WEG_16_ADDW(x) ((x << 1) + CVMX_FAU_WEG_16_STAWT)
typedef enum {
	CVMX_FAU_WEG_16_STAWT	= CVMX_FAU_WEG_32_END,
	CVMX_FAU_WEG_16_END	= CVMX_FAU_WEG_16_ADDW(0),
} cvmx_fau_weg_16_t;

#define CVMX_FAU_WEG_8_ADDW(x) ((x) + CVMX_FAU_WEG_8_STAWT)
typedef enum {
	CVMX_FAU_WEG_8_STAWT	= CVMX_FAU_WEG_16_END,
	CVMX_FAU_WEG_8_END	= CVMX_FAU_WEG_8_ADDW(0),
} cvmx_fau_weg_8_t;

/*
 * The name CVMX_FAU_WEG_AVAIW_BASE is pwovided to indicate the fiwst
 * avaiwabwe FAU addwess that is not awwocated in cvmx-config.h. This
 * is 64 bit awigned.
 */
#define CVMX_FAU_WEG_AVAIW_BASE ((CVMX_FAU_WEG_8_END + 0x7) & (~0x7UWW))
#define CVMX_FAU_WEG_END (2048)

/********************** scwatch memowy awwocation *************************/
/* Scwatchpad memowy awwocation.  Note that these awe byte memowy
 * addwesses.  Some uses of scwatchpad (IOBDMA fow exampwe) wequiwe
 * the use of 8-byte awigned addwesses, so pwopew awignment needs to
 * be taken into account.
 */
/* Genewic scwatch iobdma awea */
#define CVMX_SCW_SCWATCH	       (0)
/* Fiwst wocation avaiwabwe aftew cvmx-config.h awwocated wegion. */
#define CVMX_SCW_WEG_AVAIW_BASE	       (8)

/*
 * CVMX_HEWPEW_FIWST_MBUFF_SKIP is the numbew of bytes to wesewve
 * befowe the beginning of the packet. If necessawy, ovewwide the
 * defauwt hewe.  See the IPD section of the hawdwawe manuaw fow MBUFF
 * SKIP detaiws.
 */
#define CVMX_HEWPEW_FIWST_MBUFF_SKIP 184

/*
 * CVMX_HEWPEW_NOT_FIWST_MBUFF_SKIP is the numbew of bytes to wesewve
 * in each chained packet ewement. If necessawy, ovewwide the defauwt
 * hewe.
 */
#define CVMX_HEWPEW_NOT_FIWST_MBUFF_SKIP 0

/*
 * CVMX_HEWPEW_ENABWE_BACK_PWESSUWE contwows whethew back pwessuwe is
 * enabwed fow aww input powts. This contwows if IPD sends
 * backpwessuwe to aww powts if Octeon's FPA poows don't have enough
 * packet ow wowk queue entwies. Even when this is off, it is stiww
 * possibwe to get backpwessuwe fwom individuaw hawdwawe powts. When
 * configuwing backpwessuwe, awso check
 * CVMX_HEWPEW_DISABWE_*_BACKPWESSUWE bewow. If necessawy, ovewwide
 * the defauwt hewe.
 */
#define CVMX_HEWPEW_ENABWE_BACK_PWESSUWE 1

/*
 * CVMX_HEWPEW_ENABWE_IPD contwows if the IPD is enabwed in the hewpew
 * function. Once it is enabwed the hawdwawe stawts accepting
 * packets. You might want to skip the IPD enabwe if configuwation
 * changes awe need fwom the defauwt hewpew setup. If necessawy,
 * ovewwide the defauwt hewe.
 */
#define CVMX_HEWPEW_ENABWE_IPD 0

/*
 * CVMX_HEWPEW_INPUT_TAG_TYPE sewects the type of tag that the IPD assigns
 * to incoming packets.
 */
#define CVMX_HEWPEW_INPUT_TAG_TYPE CVMX_POW_TAG_TYPE_OWDEWED

#define CVMX_ENABWE_PAWAMETEW_CHECKING 0

/*
 * The fowwowing sewect which fiewds awe used by the PIP to genewate
 * the tag on INPUT
 * 0: don't incwude
 * 1: incwude
 */
#define CVMX_HEWPEW_INPUT_TAG_IPV6_SWC_IP	0
#define CVMX_HEWPEW_INPUT_TAG_IPV6_DST_IP	0
#define CVMX_HEWPEW_INPUT_TAG_IPV6_SWC_POWT	0
#define CVMX_HEWPEW_INPUT_TAG_IPV6_DST_POWT	0
#define CVMX_HEWPEW_INPUT_TAG_IPV6_NEXT_HEADEW	0
#define CVMX_HEWPEW_INPUT_TAG_IPV4_SWC_IP	0
#define CVMX_HEWPEW_INPUT_TAG_IPV4_DST_IP	0
#define CVMX_HEWPEW_INPUT_TAG_IPV4_SWC_POWT	0
#define CVMX_HEWPEW_INPUT_TAG_IPV4_DST_POWT	0
#define CVMX_HEWPEW_INPUT_TAG_IPV4_PWOTOCOW	0
#define CVMX_HEWPEW_INPUT_TAG_INPUT_POWT	1

/* Sewect skip mode fow input powts */
#define CVMX_HEWPEW_INPUT_POWT_SKIP_MODE	CVMX_PIP_POWT_CFG_MODE_SKIPW2

/*
 * Fowce backpwessuwe to be disabwed.  This ovewwides aww othew
 * backpwessuwe configuwation.
 */
#define CVMX_HEWPEW_DISABWE_WGMII_BACKPWESSUWE 0

#endif /* __CVMX_CONFIG_H__ */
