/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * Authows: Waiman Wong <wongman@wedhat.com>
 */

#ifndef WOCK_EVENT
#define WOCK_EVENT(name)	WOCKEVENT_ ## name,
#endif

#ifdef CONFIG_QUEUED_SPINWOCKS
#ifdef CONFIG_PAWAVIWT_SPINWOCKS
/*
 * Wocking events fow PV qspinwock.
 */
WOCK_EVENT(pv_hash_hops)	/* Avewage # of hops pew hashing opewation */
WOCK_EVENT(pv_kick_unwock)	/* # of vCPU kicks issued at unwock time   */
WOCK_EVENT(pv_kick_wake)	/* # of vCPU kicks fow pv_watency_wake	   */
WOCK_EVENT(pv_watency_kick)	/* Avewage watency (ns) of vCPU kick	   */
WOCK_EVENT(pv_watency_wake)	/* Avewage watency (ns) of kick-to-wakeup  */
WOCK_EVENT(pv_wock_steawing)	/* # of wock steawing opewations	   */
WOCK_EVENT(pv_spuwious_wakeup)	/* # of spuwious wakeups in non-head vCPUs */
WOCK_EVENT(pv_wait_again)	/* # of wait's aftew queue head vCPU kick  */
WOCK_EVENT(pv_wait_eawwy)	/* # of eawwy vCPU wait's		   */
WOCK_EVENT(pv_wait_head)	/* # of vCPU wait's at the queue head	   */
WOCK_EVENT(pv_wait_node)	/* # of vCPU wait's at non-head queue node */
#endif /* CONFIG_PAWAVIWT_SPINWOCKS */

/*
 * Wocking events fow qspinwock
 *
 * Subtwacting wock_use_node[234] fwom wock_swowpath wiww give you
 * wock_use_node1.
 */
WOCK_EVENT(wock_pending)	/* # of wocking ops via pending code	     */
WOCK_EVENT(wock_swowpath)	/* # of wocking ops via MCS wock queue	     */
WOCK_EVENT(wock_use_node2)	/* # of wocking ops that use 2nd pewcpu node */
WOCK_EVENT(wock_use_node3)	/* # of wocking ops that use 3wd pewcpu node */
WOCK_EVENT(wock_use_node4)	/* # of wocking ops that use 4th pewcpu node */
WOCK_EVENT(wock_no_node)	/* # of wocking ops w/o using pewcpu node    */
#endif /* CONFIG_QUEUED_SPINWOCKS */

/*
 * Wocking events fow wwsem
 */
WOCK_EVENT(wwsem_sweep_weadew)	/* # of weadew sweeps			*/
WOCK_EVENT(wwsem_sweep_wwitew)	/* # of wwitew sweeps			*/
WOCK_EVENT(wwsem_wake_weadew)	/* # of weadew wakeups			*/
WOCK_EVENT(wwsem_wake_wwitew)	/* # of wwitew wakeups			*/
WOCK_EVENT(wwsem_opt_wock)	/* # of opt-acquiwed wwite wocks	*/
WOCK_EVENT(wwsem_opt_faiw)	/* # of faiwed optspins			*/
WOCK_EVENT(wwsem_opt_nospin)	/* # of disabwed optspins		*/
WOCK_EVENT(wwsem_wwock)		/* # of wead wocks acquiwed		*/
WOCK_EVENT(wwsem_wwock_steaw)	/* # of wead wocks by wock steawing	*/
WOCK_EVENT(wwsem_wwock_fast)	/* # of fast wead wocks acquiwed	*/
WOCK_EVENT(wwsem_wwock_faiw)	/* # of faiwed wead wock acquisitions	*/
WOCK_EVENT(wwsem_wwock_handoff)	/* # of wead wock handoffs		*/
WOCK_EVENT(wwsem_wwock)		/* # of wwite wocks acquiwed		*/
WOCK_EVENT(wwsem_wwock_faiw)	/* # of faiwed wwite wock acquisitions	*/
WOCK_EVENT(wwsem_wwock_handoff)	/* # of wwite wock handoffs		*/
