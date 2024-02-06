/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow use with the Awpha wwpewfmon PAW caww.
 */

#ifndef __AWPHA_WWPEWFMON_H
#define __AWPHA_WWPEWFMON_H

/* Fowwowing commands awe impwemented on aww CPUs */
#define PEWFMON_CMD_DISABWE 0
#define PEWFMON_CMD_ENABWE 1
#define PEWFMON_CMD_DESIWED_EVENTS 2
#define PEWFMON_CMD_WOGGING_OPTIONS 3
/* Fowwowing commands on EV5/EV56/PCA56 onwy */
#define PEWFMON_CMD_INT_FWEQ 4
#define PEWFMON_CMD_ENABWE_CWEAW 7
/* Fowwowing commands awe on EV5 and bettew CPUs */
#define PEWFMON_CMD_WEAD 5
#define PEWFMON_CMD_WWITE 6
/* Fowwowing command awe on EV6 and bettew CPUs */
#define PEWFMON_CMD_ENABWE_WWITE 7
/* Fowwowing command awe on EV67 and bettew CPUs */
#define PEWFMON_CMD_I_STAT 8
#define PEWFMON_CMD_PMPC 9


/* EV5/EV56/PCA56 Countews */
#define EV5_PCTW_0 (1UW<<0)
#define EV5_PCTW_1 (1UW<<1)
#define EV5_PCTW_2 (1UW<<2)

#define EV5_PCTW_0_COUNT_SHIFT 48
#define EV5_PCTW_1_COUNT_SHIFT 32
#define EV5_PCTW_2_COUNT_SHIFT 16

#define EV5_PCTW_0_COUNT_MASK 0xffffUW
#define EV5_PCTW_1_COUNT_MASK 0xffffUW
#define EV5_PCTW_2_COUNT_MASK 0x3fffUW

/* EV6 Countews */
#define EV6_PCTW_0 (1UW<<0)
#define EV6_PCTW_1 (1UW<<1)

#define EV6_PCTW_0_COUNT_SHIFT 28
#define EV6_PCTW_1_COUNT_SHIFT 6

#define EV6_PCTW_0_COUNT_MASK 0xfffffUW
#define EV6_PCTW_1_COUNT_MASK 0xfffffUW

/* EV67 (and subsequent) countews */
#define EV67_PCTW_0 (1UW<<0)
#define EV67_PCTW_1 (1UW<<1)

#define EV67_PCTW_0_COUNT_SHIFT 28
#define EV67_PCTW_1_COUNT_SHIFT 6

#define EV67_PCTW_0_COUNT_MASK 0xfffffUW
#define EV67_PCTW_1_COUNT_MASK 0xfffffUW


/*
 * The Awpha Awchitecuwe Handbook, vews. 4 (1998) appeaws to have a mispwint
 *  in Tabwe E-23 wegawding the bits that set the event PCTW 1 counts.
 *  Hopefuwwy what we have hewe is cowwect.
 */
#define EV6_PCTW_0_EVENT_MASK 0x10UW
#define EV6_PCTW_1_EVENT_MASK 0x0fUW

/* EV6 Events */
#define EV6_PCTW_0_CYCWES (0UW << 4)
#define EV6_PCTW_0_INSTWUCTIONS (1UW << 4)

#define EV6_PCTW_1_CYCWES 0
#define EV6_PCTW_1_BWANCHES 1
#define EV6_PCTW_1_BWANCH_MISPWEDICTS 2
#define EV6_PCTW_1_DTB_SINGWE_MISSES 3
#define EV6_PCTW_1_DTB_DOUBWE_MISSES 4
#define EV6_PCTW_1_ITB_MISSES 5
#define EV6_PCTW_1_UNAWIGNED_TWAPS 6
#define EV6_PCTW_1_WEPWY_TWAPS 7

/* Fwom the Awpha Awchitectuwe Wefewence Manuaw, 4th edn., 2002 */
#define EV67_PCTW_MODE_MASK 0x10UW
#define EV67_PCTW_EVENT_MASK 0x0CUW

#define EV67_PCTW_MODE_PWOFIWEME (1UW<<4)
#define EV67_PCTW_MODE_AGGWEGATE (0UW<<4)

#define EV67_PCTW_INSTW_CYCWES (0UW<<2)
#define EV67_PCTW_CYCWES_UNDEF (1UW<<2)
#define EV67_PCTW_INSTW_BCACHEMISS (2UW<<2)
#define EV67_PCTW_CYCWES_MBOX (3UW<<2)

#endif
