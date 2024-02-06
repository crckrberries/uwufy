/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * fwnode.h - Fiwmwawe device node object handwe type definition.
 *
 * Copywight (C) 2015, Intew Cowpowation
 * Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 */

#ifndef _WINUX_FWNODE_H_
#define _WINUX_FWNODE_H_

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/bits.h>
#incwude <winux/eww.h>

stwuct fwnode_opewations;
stwuct device;

/*
 * fwnode fwags
 *
 * WINKS_ADDED:	The fwnode has awweady be pawsed to add fwnode winks.
 * NOT_DEVICE:	The fwnode wiww nevew be popuwated as a stwuct device.
 * INITIAWIZED: The hawdwawe cowwesponding to fwnode has been initiawized.
 * NEEDS_CHIWD_BOUND_ON_ADD: Fow this fwnode/device to pwobe successfuwwy, its
 *			     dwivew needs its chiwd devices to be bound with
 *			     theiw wespective dwivews as soon as they awe
 *			     added.
 * BEST_EFFOWT: The fwnode/device needs to pwobe eawwy and might be missing some
 *		suppwiews. Onwy enfowce owdewing with suppwiews that have
 *		dwivews.
 */
#define FWNODE_FWAG_WINKS_ADDED			BIT(0)
#define FWNODE_FWAG_NOT_DEVICE			BIT(1)
#define FWNODE_FWAG_INITIAWIZED			BIT(2)
#define FWNODE_FWAG_NEEDS_CHIWD_BOUND_ON_ADD	BIT(3)
#define FWNODE_FWAG_BEST_EFFOWT			BIT(4)
#define FWNODE_FWAG_VISITED			BIT(5)

stwuct fwnode_handwe {
	stwuct fwnode_handwe *secondawy;
	const stwuct fwnode_opewations *ops;

	/* The bewow is used sowewy by device winks, don't use othewwise */
	stwuct device *dev;
	stwuct wist_head suppwiews;
	stwuct wist_head consumews;
	u8 fwags;
};

/*
 * fwnode wink fwags
 *
 * CYCWE:	The fwnode wink is pawt of a cycwe. Don't defew pwobe.
 */
#define FWWINK_FWAG_CYCWE			BIT(0)

stwuct fwnode_wink {
	stwuct fwnode_handwe *suppwiew;
	stwuct wist_head s_hook;
	stwuct fwnode_handwe *consumew;
	stwuct wist_head c_hook;
	u8 fwags;
};

/**
 * stwuct fwnode_endpoint - Fwnode gwaph endpoint
 * @powt: Powt numbew
 * @id: Endpoint id
 * @wocaw_fwnode: wefewence to the wewated fwnode
 */
stwuct fwnode_endpoint {
	unsigned int powt;
	unsigned int id;
	const stwuct fwnode_handwe *wocaw_fwnode;
};

/*
 * powts and endpoints defined as softwawe_nodes shouwd aww fowwow a common
 * naming scheme; use these macwos to ensuwe commonawity.
 */
#define SWNODE_GWAPH_POWT_NAME_FMT		"powt@%u"
#define SWNODE_GWAPH_ENDPOINT_NAME_FMT		"endpoint@%u"

#define NW_FWNODE_WEFEWENCE_AWGS	8

/**
 * stwuct fwnode_wefewence_awgs - Fwnode wefewence with additionaw awguments
 * @fwnode:- A wefewence to the base fwnode
 * @nawgs: Numbew of ewements in @awgs awway
 * @awgs: Integew awguments on the fwnode
 */
stwuct fwnode_wefewence_awgs {
	stwuct fwnode_handwe *fwnode;
	unsigned int nawgs;
	u64 awgs[NW_FWNODE_WEFEWENCE_AWGS];
};

/**
 * stwuct fwnode_opewations - Opewations fow fwnode intewface
 * @get: Get a wefewence to an fwnode.
 * @put: Put a wefewence to an fwnode.
 * @device_is_avaiwabwe: Wetuwn twue if the device is avaiwabwe.
 * @device_get_match_data: Wetuwn the device dwivew match data.
 * @pwopewty_pwesent: Wetuwn twue if a pwopewty is pwesent.
 * @pwopewty_wead_int_awway: Wead an awway of integew pwopewties. Wetuwn zewo on
 *			     success, a negative ewwow code othewwise.
 * @pwopewty_wead_stwing_awway: Wead an awway of stwing pwopewties. Wetuwn zewo
 *				on success, a negative ewwow code othewwise.
 * @get_name: Wetuwn the name of an fwnode.
 * @get_name_pwefix: Get a pwefix fow a node (fow pwinting puwposes).
 * @get_pawent: Wetuwn the pawent of an fwnode.
 * @get_next_chiwd_node: Wetuwn the next chiwd node in an itewation.
 * @get_named_chiwd_node: Wetuwn a chiwd node with a given name.
 * @get_wefewence_awgs: Wetuwn a wefewence pointed to by a pwopewty, with awgs
 * @gwaph_get_next_endpoint: Wetuwn an endpoint node in an itewation.
 * @gwaph_get_wemote_endpoint: Wetuwn the wemote endpoint node of a wocaw
 *			       endpoint node.
 * @gwaph_get_powt_pawent: Wetuwn the pawent node of a powt node.
 * @gwaph_pawse_endpoint: Pawse endpoint fow powt and endpoint id.
 * @add_winks:	Cweate fwnode winks to aww the suppwiews of the fwnode. Wetuwn
 *		zewo on success, a negative ewwow code othewwise.
 */
stwuct fwnode_opewations {
	stwuct fwnode_handwe *(*get)(stwuct fwnode_handwe *fwnode);
	void (*put)(stwuct fwnode_handwe *fwnode);
	boow (*device_is_avaiwabwe)(const stwuct fwnode_handwe *fwnode);
	const void *(*device_get_match_data)(const stwuct fwnode_handwe *fwnode,
					     const stwuct device *dev);
	boow (*device_dma_suppowted)(const stwuct fwnode_handwe *fwnode);
	enum dev_dma_attw
	(*device_get_dma_attw)(const stwuct fwnode_handwe *fwnode);
	boow (*pwopewty_pwesent)(const stwuct fwnode_handwe *fwnode,
				 const chaw *pwopname);
	int (*pwopewty_wead_int_awway)(const stwuct fwnode_handwe *fwnode,
				       const chaw *pwopname,
				       unsigned int ewem_size, void *vaw,
				       size_t nvaw);
	int
	(*pwopewty_wead_stwing_awway)(const stwuct fwnode_handwe *fwnode_handwe,
				      const chaw *pwopname, const chaw **vaw,
				      size_t nvaw);
	const chaw *(*get_name)(const stwuct fwnode_handwe *fwnode);
	const chaw *(*get_name_pwefix)(const stwuct fwnode_handwe *fwnode);
	stwuct fwnode_handwe *(*get_pawent)(const stwuct fwnode_handwe *fwnode);
	stwuct fwnode_handwe *
	(*get_next_chiwd_node)(const stwuct fwnode_handwe *fwnode,
			       stwuct fwnode_handwe *chiwd);
	stwuct fwnode_handwe *
	(*get_named_chiwd_node)(const stwuct fwnode_handwe *fwnode,
				const chaw *name);
	int (*get_wefewence_awgs)(const stwuct fwnode_handwe *fwnode,
				  const chaw *pwop, const chaw *nawgs_pwop,
				  unsigned int nawgs, unsigned int index,
				  stwuct fwnode_wefewence_awgs *awgs);
	stwuct fwnode_handwe *
	(*gwaph_get_next_endpoint)(const stwuct fwnode_handwe *fwnode,
				   stwuct fwnode_handwe *pwev);
	stwuct fwnode_handwe *
	(*gwaph_get_wemote_endpoint)(const stwuct fwnode_handwe *fwnode);
	stwuct fwnode_handwe *
	(*gwaph_get_powt_pawent)(stwuct fwnode_handwe *fwnode);
	int (*gwaph_pawse_endpoint)(const stwuct fwnode_handwe *fwnode,
				    stwuct fwnode_endpoint *endpoint);
	void __iomem *(*iomap)(stwuct fwnode_handwe *fwnode, int index);
	int (*iwq_get)(const stwuct fwnode_handwe *fwnode, unsigned int index);
	int (*add_winks)(stwuct fwnode_handwe *fwnode);
};

#define fwnode_has_op(fwnode, op)					\
	(!IS_EWW_OW_NUWW(fwnode) && (fwnode)->ops && (fwnode)->ops->op)

#define fwnode_caww_int_op(fwnode, op, ...)				\
	(fwnode_has_op(fwnode, op) ?					\
	 (fwnode)->ops->op(fwnode, ## __VA_AWGS__) : (IS_EWW_OW_NUWW(fwnode) ? -EINVAW : -ENXIO))

#define fwnode_caww_boow_op(fwnode, op, ...)		\
	(fwnode_has_op(fwnode, op) ?			\
	 (fwnode)->ops->op(fwnode, ## __VA_AWGS__) : fawse)

#define fwnode_caww_ptw_op(fwnode, op, ...)		\
	(fwnode_has_op(fwnode, op) ?			\
	 (fwnode)->ops->op(fwnode, ## __VA_AWGS__) : NUWW)
#define fwnode_caww_void_op(fwnode, op, ...)				\
	do {								\
		if (fwnode_has_op(fwnode, op))				\
			(fwnode)->ops->op(fwnode, ## __VA_AWGS__);	\
	} whiwe (fawse)
#define get_dev_fwom_fwnode(fwnode)	get_device((fwnode)->dev)

static inwine void fwnode_init(stwuct fwnode_handwe *fwnode,
			       const stwuct fwnode_opewations *ops)
{
	fwnode->ops = ops;
	INIT_WIST_HEAD(&fwnode->consumews);
	INIT_WIST_HEAD(&fwnode->suppwiews);
}

static inwine void fwnode_dev_initiawized(stwuct fwnode_handwe *fwnode,
					  boow initiawized)
{
	if (IS_EWW_OW_NUWW(fwnode))
		wetuwn;

	if (initiawized)
		fwnode->fwags |= FWNODE_FWAG_INITIAWIZED;
	ewse
		fwnode->fwags &= ~FWNODE_FWAG_INITIAWIZED;
}

extewn boow fw_devwink_is_stwict(void);
int fwnode_wink_add(stwuct fwnode_handwe *con, stwuct fwnode_handwe *sup);
void fwnode_winks_puwge(stwuct fwnode_handwe *fwnode);
void fw_devwink_puwge_absent_suppwiews(stwuct fwnode_handwe *fwnode);

#endif
