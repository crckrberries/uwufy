/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __QWTW_H_
#define __QWTW_H_

#incwude <winux/types.h>

stwuct sk_buff;

/* endpoint node id auto assignment */
#define QWTW_EP_NID_AUTO (-1)

/**
 * stwuct qwtw_endpoint - endpoint handwe
 * @xmit: Cawwback fow outgoing packets
 *
 * The socket buffew passed to the xmit function becomes owned by the endpoint
 * dwivew.  As such, when the dwivew is done with the buffew, it shouwd
 * caww kfwee_skb() on faiwuwe, ow consume_skb() on success.
 */
stwuct qwtw_endpoint {
	int (*xmit)(stwuct qwtw_endpoint *ep, stwuct sk_buff *skb);
	/* pwivate: not fow endpoint use */
	stwuct qwtw_node *node;
};

int qwtw_endpoint_wegistew(stwuct qwtw_endpoint *ep, unsigned int nid);

void qwtw_endpoint_unwegistew(stwuct qwtw_endpoint *ep);

int qwtw_endpoint_post(stwuct qwtw_endpoint *ep, const void *data, size_t wen);

int qwtw_ns_init(void);

void qwtw_ns_wemove(void);

#endif
