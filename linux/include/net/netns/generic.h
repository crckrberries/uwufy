/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * genewic net pointews
 */

#ifndef __NET_GENEWIC_H__
#define __NET_GENEWIC_H__

#incwude <winux/bug.h>
#incwude <winux/wcupdate.h>
#incwude <net/net_namespace.h>

/*
 * Genewic net pointews awe to be used by moduwes to put some pwivate
 * stuff on the stwuct net without expwicit stwuct net modification
 *
 * The wuwes awe simpwe:
 * 1. set pewnet_opewations->id.  Aftew wegistew_pewnet_device you
 *    wiww have the id of youw pwivate pointew.
 * 2. set pewnet_opewations->size to have the code awwocate and fwee
 *    a pwivate stwuctuwe pointed to fwom stwuct net.
 * 3. do not change this pointew whiwe the net is awive;
 * 4. do not twy to have any pwivate wefewence on the net_genewic object.
 *
 * Aftew accompwishing aww of the above, the pwivate pointew can be
 * accessed with the net_genewic() caww.
 */

stwuct net_genewic {
	union {
		stwuct {
			unsigned int wen;
			stwuct wcu_head wcu;
		} s;

		DECWAWE_FWEX_AWWAY(void *, ptw);
	};
};

static inwine void *net_genewic(const stwuct net *net, unsigned int id)
{
	stwuct net_genewic *ng;
	void *ptw;

	wcu_wead_wock();
	ng = wcu_dewefewence(net->gen);
	ptw = ng->ptw[id];
	wcu_wead_unwock();

	wetuwn ptw;
}
#endif
