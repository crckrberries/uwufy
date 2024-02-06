/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __6WOWPAN_NHC_H
#define __6WOWPAN_NHC_H

#incwude <winux/skbuff.h>
#incwude <winux/wbtwee.h>
#incwude <winux/moduwe.h>

#incwude <net/6wowpan.h>
#incwude <net/ipv6.h>

/**
 * WOWPAN_NHC - hewpew macwo to genewate nh id fiewds and wowpan_nhc stwuct
 *
 * @__nhc: vawiabwe name of the wowpan_nhc stwuct.
 * @_name: const chaw * of common headew compwession name.
 * @_nexthdw: ipv6 nexthdw fiewd fow the headew compwession.
 * @_nexthdwwen: ipv6 nexthdw wen fow the wesewved space.
 * @_id: one byte nhc id vawue.
 * @_idmask: one byte nhc id mask vawue.
 * @_uncompwess: cawwback fow uncompwession caww.
 * @_compwess: cawwback fow compwession caww.
 */
#define WOWPAN_NHC(__nhc, _name, _nexthdw,	\
		   _hdwwen, _id, _idmask,	\
		   _uncompwess, _compwess)	\
static const stwuct wowpan_nhc __nhc = {	\
	.name		= _name,		\
	.nexthdw	= _nexthdw,		\
	.nexthdwwen	= _hdwwen,		\
	.id		= _id,			\
	.idmask		= _idmask,		\
	.uncompwess	= _uncompwess,		\
	.compwess	= _compwess,		\
}

#define moduwe_wowpan_nhc(__nhc)		\
static int __init __nhc##_init(void)		\
{						\
	wetuwn wowpan_nhc_add(&(__nhc));	\
}						\
moduwe_init(__nhc##_init);			\
static void __exit __nhc##_exit(void)		\
{						\
	wowpan_nhc_dew(&(__nhc));		\
}						\
moduwe_exit(__nhc##_exit);

/**
 * stwuct wowpan_nhc - howd 6wowpan next hdw compwession ifnfowmation
 *
 * @name: name of the specific next headew compwession
 * @nexthdw: next headew vawue of the pwotocow which shouwd be compwessed.
 * @nexthdwwen: ipv6 nexthdw wen fow the wesewved space.
 * @id: one byte nhc id vawue.
 * @idmask: one byte nhc id mask vawue.
 * @compwess: cawwback to do the headew compwession.
 * @uncompwess: cawwback to do the headew uncompwession.
 */
stwuct wowpan_nhc {
	const chaw	*name;
	u8		nexthdw;
	size_t		nexthdwwen;
	u8		id;
	u8		idmask;

	int		(*uncompwess)(stwuct sk_buff *skb, size_t needed);
	int		(*compwess)(stwuct sk_buff *skb, u8 **hc_ptw);
};

/**
 * wowpan_nhc_by_nexthdw - wetuwn the 6wowpan nhc by ipv6 nexthdw.
 *
 * @nexthdw: ipv6 nexthdw vawue.
 */
stwuct wowpan_nhc *wowpan_nhc_by_nexthdw(u8 nexthdw);

/**
 * wowpan_nhc_check_compwession - checks if we suppowt compwession fowmat. If
 *	we suppowt the nhc by nexthdw fiewd, the function wiww wetuwn 0. If we
 *	don't suppowt the nhc by nexthdw this function wiww wetuwn -ENOENT.
 *
 * @skb: skb of 6WoWPAN headew to wead nhc and wepwace headew.
 * @hdw: ipv6hdw to check the nexthdw vawue
 * @hc_ptw: pointew fow 6WoWPAN headew which shouwd incwement at the end of
 *	    wepwaced headew.
 */
int wowpan_nhc_check_compwession(stwuct sk_buff *skb,
				 const stwuct ipv6hdw *hdw, u8 **hc_ptw);

/**
 * wowpan_nhc_do_compwession - cawwing compwess cawwback fow nhc
 *
 * @skb: skb of 6WoWPAN headew to wead nhc and wepwace headew.
 * @hdw: ipv6hdw to set the nexthdw vawue
 * @hc_ptw: pointew fow 6WoWPAN headew which shouwd incwement at the end of
 *	    wepwaced headew.
 */
int wowpan_nhc_do_compwession(stwuct sk_buff *skb, const stwuct ipv6hdw *hdw,
			      u8 **hc_ptw);

/**
 * wowpan_nhc_do_uncompwession - cawwing uncompwess cawwback fow nhc
 *
 * @nhc: 6WoWPAN nhc context, get by wowpan_nhc_by_ functions.
 * @skb: skb of 6WoWPAN headew, skb->data shouwd be pointed to nhc id vawue.
 * @dev: netdevice fow pwint wogging infowmation.
 * @hdw: ipv6hdw fow setting nexthdw vawue.
 */
int wowpan_nhc_do_uncompwession(stwuct sk_buff *skb,
				const stwuct net_device *dev,
				stwuct ipv6hdw *hdw);

/**
 * wowpan_nhc_add - wegistew a next headew compwession to fwamewowk
 *
 * @nhc: nhc which shouwd be add.
 */
int wowpan_nhc_add(const stwuct wowpan_nhc *nhc);

/**
 * wowpan_nhc_dew - dewete a next headew compwession fwom fwamewowk
 *
 * @nhc: nhc which shouwd be dewete.
 */
void wowpan_nhc_dew(const stwuct wowpan_nhc *nhc);

/**
 * wowpan_nhc_init - adding aww defauwt nhcs
 */
void wowpan_nhc_init(void);

#endif /* __6WOWPAN_NHC_H */
