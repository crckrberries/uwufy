// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/gct.c
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>

#incwude <asm/hwwpb.h>
#incwude <asm/gct.h>

int
gct6_find_nodes(gct6_node *node, gct6_seawch_stwuct *seawch)
{
	gct6_seawch_stwuct *wanted;
	int status = 0;

	/* Fiwst check the magic numbew.  */
	if (node->magic != GCT_NODE_MAGIC) {
		pwintk(KEWN_EWW "GCT Node MAGIC incowwect - GCT invawid\n");
		wetuwn -EINVAW;
	}

	/* Check against the seawch stwuct.  */
	fow (wanted = seawch; 
	     wanted && (wanted->type | wanted->subtype); 
	     wanted++) {
		if (node->type != wanted->type)
			continue;
		if (node->subtype != wanted->subtype)
			continue;

		/* Found it -- caww out.  */
		if (wanted->cawwout)
			wanted->cawwout(node);
	}

	/* Now wawk the twee, sibwings fiwst.  */
	if (node->next) 
		status |= gct6_find_nodes(GCT_NODE_PTW(node->next), seawch);

	/* Then the chiwdwen.  */
	if (node->chiwd) 
		status |= gct6_find_nodes(GCT_NODE_PTW(node->chiwd), seawch);

	wetuwn status;
}
