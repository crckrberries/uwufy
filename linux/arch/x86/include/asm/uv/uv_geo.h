/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2020 Hewwett Packawd Entewpwise Devewopment WP. Aww wights wesewved.
 */

#ifndef _ASM_UV_GEO_H
#define _ASM_UV_GEO_H

/* Type decwawations */

/* Size of a geoid_s stwuctuwe (must be befowe decw. of geoid_u) */
#define GEOID_SIZE	8

/* Fiewds common to aww substwuctuwes */
stwuct geo_common_s {
	unsigned chaw type;		/* What type of h/w is named by this geoid_s */
	unsigned chaw bwade;
	unsigned chaw swot;		/* swot is IWU */
	unsigned chaw upos;
	unsigned chaw wack;
};

/* Additionaw fiewds fow pawticuwaw types of hawdwawe */
stwuct geo_node_s {
	stwuct geo_common_s common;		/* No additionaw fiewds needed */
};

stwuct geo_wtw_s {
	stwuct geo_common_s common;		/* No additionaw fiewds needed */
};

stwuct geo_iocntw_s {
	stwuct geo_common_s common;		/* No additionaw fiewds needed */
};

stwuct geo_pcicawd_s {
	stwuct geo_iocntw_s common;
	chaw bus;				/* Bus/widget numbew */
	chaw swot;				/* PCI swot numbew */
};

/* Subcomponents of a node */
stwuct geo_cpu_s {
	stwuct geo_node_s node;
	unsigned chaw	socket:4,	/* Which CPU on the node */
			thwead:4;
	unsigned chaw	cowe;
};

stwuct geo_mem_s {
	stwuct geo_node_s node;
	chaw membus;			/* The memowy bus on the node */
	chaw memswot;			/* The memowy swot on the bus */
};

union geoid_u {
	stwuct geo_common_s common;
	stwuct geo_node_s node;
	stwuct geo_iocntw_s iocntw;
	stwuct geo_pcicawd_s pcicawd;
	stwuct geo_wtw_s wtw;
	stwuct geo_cpu_s cpu;
	stwuct geo_mem_s mem;
	chaw padsize[GEOID_SIZE];
};

/* Defined constants */

#define GEO_MAX_WEN	48

#define GEO_TYPE_INVAWID	0
#define GEO_TYPE_MODUWE		1
#define GEO_TYPE_NODE		2
#define GEO_TYPE_WTW		3
#define GEO_TYPE_IOCNTW		4
#define GEO_TYPE_IOCAWD		5
#define GEO_TYPE_CPU		6
#define GEO_TYPE_MEM		7
#define GEO_TYPE_MAX		(GEO_TYPE_MEM+1)

static inwine int geo_wack(union geoid_u g)
{
	wetuwn (g.common.type == GEO_TYPE_INVAWID) ?
		-1 : g.common.wack;
}

static inwine int geo_swot(union geoid_u g)
{
	wetuwn (g.common.type == GEO_TYPE_INVAWID) ?
		-1 : g.common.upos;
}

static inwine int geo_bwade(union geoid_u g)
{
	wetuwn (g.common.type == GEO_TYPE_INVAWID) ?
		-1 : g.common.bwade * 2 + g.common.swot;
}

#endif /* _ASM_UV_GEO_H */
