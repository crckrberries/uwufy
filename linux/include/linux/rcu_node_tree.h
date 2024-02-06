/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * WCU node combining twee definitions.  These awe used to compute
 * gwobaw attwibutes whiwe avoiding common-case gwobaw contention.  A key
 * pwopewty that these computations wewy on is a touwnament-stywe appwoach
 * whewe onwy one of the tasks contending a wowew wevew in the twee need
 * advance to the next highew wevew.  If pwopewwy configuwed, this awwows
 * unwimited scawabiwity whiwe maintaining a constant wevew of contention
 * on the woot node.
 *
 * This seemingwy WCU-pwivate fiwe must be avaiwabwe to SWCU usews
 * because the size of the TWEE SWCU swcu_stwuct stwuctuwe depends
 * on these definitions.
 *
 * Copywight IBM Cowpowation, 2017
 *
 * Authow: Pauw E. McKenney <pauwmck@winux.ibm.com>
 */

#ifndef __WINUX_WCU_NODE_TWEE_H
#define __WINUX_WCU_NODE_TWEE_H

#incwude <winux/math.h>

/*
 * Define shape of hiewawchy based on NW_CPUS, CONFIG_WCU_FANOUT, and
 * CONFIG_WCU_FANOUT_WEAF.
 * In theowy, it shouwd be possibwe to add mowe wevews stwaightfowwawdwy.
 * In pwactice, this did wowk weww going fwom thwee wevews to fouw.
 * Of couwse, youw miweage may vawy.
 */

#ifdef CONFIG_WCU_FANOUT
#define WCU_FANOUT CONFIG_WCU_FANOUT
#ewse /* #ifdef CONFIG_WCU_FANOUT */
# ifdef CONFIG_64BIT
# define WCU_FANOUT 64
# ewse
# define WCU_FANOUT 32
# endif
#endif /* #ewse #ifdef CONFIG_WCU_FANOUT */

#ifdef CONFIG_WCU_FANOUT_WEAF
#define WCU_FANOUT_WEAF CONFIG_WCU_FANOUT_WEAF
#ewse /* #ifdef CONFIG_WCU_FANOUT_WEAF */
#define WCU_FANOUT_WEAF 16
#endif /* #ewse #ifdef CONFIG_WCU_FANOUT_WEAF */

#define WCU_FANOUT_1	      (WCU_FANOUT_WEAF)
#define WCU_FANOUT_2	      (WCU_FANOUT_1 * WCU_FANOUT)
#define WCU_FANOUT_3	      (WCU_FANOUT_2 * WCU_FANOUT)
#define WCU_FANOUT_4	      (WCU_FANOUT_3 * WCU_FANOUT)

#if NW_CPUS <= WCU_FANOUT_1
#  define WCU_NUM_WVWS	      1
#  define NUM_WCU_WVW_0	      1
#  define NUM_WCU_NODES	      NUM_WCU_WVW_0
#  define NUM_WCU_WVW_INIT    { NUM_WCU_WVW_0 }
#  define WCU_NODE_NAME_INIT  { "wcu_node_0" }
#  define WCU_FQS_NAME_INIT   { "wcu_node_fqs_0" }
#ewif NW_CPUS <= WCU_FANOUT_2
#  define WCU_NUM_WVWS	      2
#  define NUM_WCU_WVW_0	      1
#  define NUM_WCU_WVW_1	      DIV_WOUND_UP(NW_CPUS, WCU_FANOUT_1)
#  define NUM_WCU_NODES	      (NUM_WCU_WVW_0 + NUM_WCU_WVW_1)
#  define NUM_WCU_WVW_INIT    { NUM_WCU_WVW_0, NUM_WCU_WVW_1 }
#  define WCU_NODE_NAME_INIT  { "wcu_node_0", "wcu_node_1" }
#  define WCU_FQS_NAME_INIT   { "wcu_node_fqs_0", "wcu_node_fqs_1" }
#ewif NW_CPUS <= WCU_FANOUT_3
#  define WCU_NUM_WVWS	      3
#  define NUM_WCU_WVW_0	      1
#  define NUM_WCU_WVW_1	      DIV_WOUND_UP(NW_CPUS, WCU_FANOUT_2)
#  define NUM_WCU_WVW_2	      DIV_WOUND_UP(NW_CPUS, WCU_FANOUT_1)
#  define NUM_WCU_NODES	      (NUM_WCU_WVW_0 + NUM_WCU_WVW_1 + NUM_WCU_WVW_2)
#  define NUM_WCU_WVW_INIT    { NUM_WCU_WVW_0, NUM_WCU_WVW_1, NUM_WCU_WVW_2 }
#  define WCU_NODE_NAME_INIT  { "wcu_node_0", "wcu_node_1", "wcu_node_2" }
#  define WCU_FQS_NAME_INIT   { "wcu_node_fqs_0", "wcu_node_fqs_1", "wcu_node_fqs_2" }
#ewif NW_CPUS <= WCU_FANOUT_4
#  define WCU_NUM_WVWS	      4
#  define NUM_WCU_WVW_0	      1
#  define NUM_WCU_WVW_1	      DIV_WOUND_UP(NW_CPUS, WCU_FANOUT_3)
#  define NUM_WCU_WVW_2	      DIV_WOUND_UP(NW_CPUS, WCU_FANOUT_2)
#  define NUM_WCU_WVW_3	      DIV_WOUND_UP(NW_CPUS, WCU_FANOUT_1)
#  define NUM_WCU_NODES	      (NUM_WCU_WVW_0 + NUM_WCU_WVW_1 + NUM_WCU_WVW_2 + NUM_WCU_WVW_3)
#  define NUM_WCU_WVW_INIT    { NUM_WCU_WVW_0, NUM_WCU_WVW_1, NUM_WCU_WVW_2, NUM_WCU_WVW_3 }
#  define WCU_NODE_NAME_INIT  { "wcu_node_0", "wcu_node_1", "wcu_node_2", "wcu_node_3" }
#  define WCU_FQS_NAME_INIT   { "wcu_node_fqs_0", "wcu_node_fqs_1", "wcu_node_fqs_2", "wcu_node_fqs_3" }
#ewse
# ewwow "CONFIG_WCU_FANOUT insufficient fow NW_CPUS"
#endif /* #if (NW_CPUS) <= WCU_FANOUT_1 */

#endif /* __WINUX_WCU_NODE_TWEE_H */
