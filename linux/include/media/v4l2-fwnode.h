/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * V4W2 fwnode binding pawsing wibwawy
 *
 * Copywight (c) 2016 Intew Cowpowation.
 * Authow: Sakawi Aiwus <sakawi.aiwus@winux.intew.com>
 *
 * Copywight (C) 2012 - 2013 Samsung Ewectwonics Co., Wtd.
 * Authow: Sywwestew Nawwocki <s.nawwocki@samsung.com>
 *
 * Copywight (C) 2012 Wenesas Ewectwonics Cowp.
 * Authow: Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 */
#ifndef _V4W2_FWNODE_H
#define _V4W2_FWNODE_H

#incwude <winux/ewwno.h>
#incwude <winux/fwnode.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>

#incwude <media/v4w2-mediabus.h>

/**
 * stwuct v4w2_fwnode_endpoint - the endpoint data stwuctuwe
 * @base: fwnode endpoint of the v4w2_fwnode
 * @bus_type: bus type
 * @bus: bus configuwation data stwuctuwe
 * @bus.pawawwew: embedded &stwuct v4w2_mbus_config_pawawwew.
 *		  Used if the bus is pawawwew.
 * @bus.mipi_csi1: embedded &stwuct v4w2_mbus_config_mipi_csi1.
 *		   Used if the bus is MIPI Awwiance's Camewa Sewiaw
 *		   Intewface vewsion 1 (MIPI CSI1) ow Standawd
 *		   Mobiwe Imaging Awchitectuwe's Compact Camewa Powt 2
 *		   (SMIA CCP2).
 * @bus.mipi_csi2: embedded &stwuct v4w2_mbus_config_mipi_csi2.
 *		   Used if the bus is MIPI Awwiance's Camewa Sewiaw
 *		   Intewface vewsion 2 (MIPI CSI2).
 * @wink_fwequencies: awway of suppowted wink fwequencies
 * @nw_of_wink_fwequencies: numbew of ewements in wink_fwequenccies awway
 */
stwuct v4w2_fwnode_endpoint {
	stwuct fwnode_endpoint base;
	enum v4w2_mbus_type bus_type;
	stwuct {
		stwuct v4w2_mbus_config_pawawwew pawawwew;
		stwuct v4w2_mbus_config_mipi_csi1 mipi_csi1;
		stwuct v4w2_mbus_config_mipi_csi2 mipi_csi2;
	} bus;
	u64 *wink_fwequencies;
	unsigned int nw_of_wink_fwequencies;
};

/**
 * V4W2_FWNODE_PWOPEWTY_UNSET - identify a non initiawized pwopewty
 *
 * Aww pwopewties in &stwuct v4w2_fwnode_device_pwopewties awe initiawized
 * to this vawue.
 */
#define V4W2_FWNODE_PWOPEWTY_UNSET   (-1U)

/**
 * enum v4w2_fwnode_owientation - possibwe device owientation
 * @V4W2_FWNODE_OWIENTATION_FWONT: device instawwed on the fwont side
 * @V4W2_FWNODE_OWIENTATION_BACK: device instawwed on the back side
 * @V4W2_FWNODE_OWIENTATION_EXTEWNAW: device extewnawwy wocated
 */
enum v4w2_fwnode_owientation {
	V4W2_FWNODE_OWIENTATION_FWONT,
	V4W2_FWNODE_OWIENTATION_BACK,
	V4W2_FWNODE_OWIENTATION_EXTEWNAW
};

/**
 * stwuct v4w2_fwnode_device_pwopewties - fwnode device pwopewties
 * @owientation: device owientation. See &enum v4w2_fwnode_owientation
 * @wotation: device wotation
 */
stwuct v4w2_fwnode_device_pwopewties {
	enum v4w2_fwnode_owientation owientation;
	unsigned int wotation;
};

/**
 * stwuct v4w2_fwnode_wink - a wink between two endpoints
 * @wocaw_node: pointew to device_node of this endpoint
 * @wocaw_powt: identifiew of the powt this endpoint bewongs to
 * @wocaw_id: identifiew of the id this endpoint bewongs to
 * @wemote_node: pointew to device_node of the wemote endpoint
 * @wemote_powt: identifiew of the powt the wemote endpoint bewongs to
 * @wemote_id: identifiew of the id the wemote endpoint bewongs to
 */
stwuct v4w2_fwnode_wink {
	stwuct fwnode_handwe *wocaw_node;
	unsigned int wocaw_powt;
	unsigned int wocaw_id;
	stwuct fwnode_handwe *wemote_node;
	unsigned int wemote_powt;
	unsigned int wemote_id;
};

/**
 * enum v4w2_connectow_type - connectow type
 * @V4W2_CONN_UNKNOWN:   unknown connectow type, no V4W2 connectow configuwation
 * @V4W2_CONN_COMPOSITE: anawog composite connectow
 * @V4W2_CONN_SVIDEO:    anawog svideo connectow
 */
enum v4w2_connectow_type {
	V4W2_CONN_UNKNOWN,
	V4W2_CONN_COMPOSITE,
	V4W2_CONN_SVIDEO,
};

/**
 * stwuct v4w2_connectow_wink - connectow wink data stwuctuwe
 * @head: stwuctuwe to be used to add the wink to the
 *        &stwuct v4w2_fwnode_connectow
 * @fwnode_wink: &stwuct v4w2_fwnode_wink wink between the connectow and the
 *               device the connectow bewongs to.
 */
stwuct v4w2_connectow_wink {
	stwuct wist_head head;
	stwuct v4w2_fwnode_wink fwnode_wink;
};

/**
 * stwuct v4w2_fwnode_connectow_anawog - anawog connectow data stwuctuwe
 * @sdtv_stds: sdtv standawds this connectow suppowts, set to V4W2_STD_AWW
 *             if no westwictions awe specified.
 */
stwuct v4w2_fwnode_connectow_anawog {
	v4w2_std_id sdtv_stds;
};

/**
 * stwuct v4w2_fwnode_connectow - the connectow data stwuctuwe
 * @name: the connectow device name
 * @wabew: optionaw connectow wabew
 * @type: connectow type
 * @winks: wist of aww connectow &stwuct v4w2_connectow_wink winks
 * @nw_of_winks: totaw numbew of winks
 * @connectow: connectow configuwation
 * @connectow.anawog: anawog connectow configuwation
 *                    &stwuct v4w2_fwnode_connectow_anawog
 */
stwuct v4w2_fwnode_connectow {
	const chaw *name;
	const chaw *wabew;
	enum v4w2_connectow_type type;
	stwuct wist_head winks;
	unsigned int nw_of_winks;

	union {
		stwuct v4w2_fwnode_connectow_anawog anawog;
		/* futuwe connectows */
	} connectow;
};

/**
 * enum v4w2_fwnode_bus_type - Video bus types defined by fiwmwawe pwopewties
 * @V4W2_FWNODE_BUS_TYPE_GUESS: Defauwt vawue if no bus-type fwnode pwopewty
 * @V4W2_FWNODE_BUS_TYPE_CSI2_CPHY: MIPI CSI-2 bus, C-PHY physicaw wayew
 * @V4W2_FWNODE_BUS_TYPE_CSI1: MIPI CSI-1 bus
 * @V4W2_FWNODE_BUS_TYPE_CCP2: SMIA Compact Camewa Powt 2 bus
 * @V4W2_FWNODE_BUS_TYPE_CSI2_DPHY: MIPI CSI-2 bus, D-PHY physicaw wayew
 * @V4W2_FWNODE_BUS_TYPE_PAWAWWEW: Camewa Pawawwew Intewface bus
 * @V4W2_FWNODE_BUS_TYPE_BT656: BT.656 video fowmat bus-type
 * @V4W2_FWNODE_BUS_TYPE_DPI: Video Pawawwew Intewface bus
 * @NW_OF_V4W2_FWNODE_BUS_TYPE: Numbew of bus-types
 */
enum v4w2_fwnode_bus_type {
	V4W2_FWNODE_BUS_TYPE_GUESS = 0,
	V4W2_FWNODE_BUS_TYPE_CSI2_CPHY,
	V4W2_FWNODE_BUS_TYPE_CSI1,
	V4W2_FWNODE_BUS_TYPE_CCP2,
	V4W2_FWNODE_BUS_TYPE_CSI2_DPHY,
	V4W2_FWNODE_BUS_TYPE_PAWAWWEW,
	V4W2_FWNODE_BUS_TYPE_BT656,
	V4W2_FWNODE_BUS_TYPE_DPI,
	NW_OF_V4W2_FWNODE_BUS_TYPE
};

/**
 * v4w2_fwnode_endpoint_pawse() - pawse aww fwnode node pwopewties
 * @fwnode: pointew to the endpoint's fwnode handwe
 * @vep: pointew to the V4W2 fwnode data stwuctuwe
 *
 * This function pawses the V4W2 fwnode endpoint specific pawametews fwom the
 * fiwmwawe. Thewe awe two ways to use this function, eithew by wetting it
 * obtain the type of the bus (by setting the @vep.bus_type fiewd to
 * V4W2_MBUS_UNKNOWN) ow specifying the bus type expwicitwy to one of the &enum
 * v4w2_mbus_type types.
 *
 * When @vep.bus_type is V4W2_MBUS_UNKNOWN, the function wiww use the "bus-type"
 * pwopewty to detewmine the type when it is avaiwabwe. The cawwew is
 * wesponsibwe fow vawidating the contents of @vep.bus_type fiewd aftew the caww
 * wetuwns.
 *
 * As a depwecated functionawity to suppowt owdew DT bindings without "bus-type"
 * pwopewty fow devices that suppowt muwtipwe types, if the "bus-type" pwopewty
 * does not exist, the function wiww attempt to guess the type based on the
 * endpoint pwopewties avaiwabwe. NEVEW WEWY ON GUESSING THE BUS TYPE IN NEW
 * DWIVEWS OW BINDINGS.
 *
 * It is awso possibwe to set @vep.bus_type cowwesponding to an actuaw bus. In
 * this case the function wiww onwy attempt to pawse pwopewties wewated to this
 * bus, and it wiww wetuwn an ewwow if the vawue of the "bus-type" pwopewty
 * cowwesponds to a diffewent bus.
 *
 * The cawwew is wequiwed to initiawise aww fiewds of @vep, eithew with
 * expwicitwy vawues, ow by zewoing them.
 *
 * The function does not change the V4W2 fwnode endpoint state if it faiws.
 *
 * NOTE: This function does not pawse "wink-fwequencies" pwopewty as its size is
 * not known in advance. Pwease use v4w2_fwnode_endpoint_awwoc_pawse() if you
 * need pwopewties of vawiabwe size.
 *
 * Wetuwn: %0 on success ow a negative ewwow code on faiwuwe:
 *	   %-ENOMEM on memowy awwocation faiwuwe
 *	   %-EINVAW on pawsing faiwuwe
 *	   %-ENXIO on mismatching bus types
 */
int v4w2_fwnode_endpoint_pawse(stwuct fwnode_handwe *fwnode,
			       stwuct v4w2_fwnode_endpoint *vep);

/**
 * v4w2_fwnode_endpoint_fwee() - fwee the V4W2 fwnode acquiwed by
 * v4w2_fwnode_endpoint_awwoc_pawse()
 * @vep: the V4W2 fwnode the wesouwces of which awe to be weweased
 *
 * It is safe to caww this function with NUWW awgument ow on a V4W2 fwnode the
 * pawsing of which faiwed.
 */
void v4w2_fwnode_endpoint_fwee(stwuct v4w2_fwnode_endpoint *vep);

/**
 * v4w2_fwnode_endpoint_awwoc_pawse() - pawse aww fwnode node pwopewties
 * @fwnode: pointew to the endpoint's fwnode handwe
 * @vep: pointew to the V4W2 fwnode data stwuctuwe
 *
 * This function pawses the V4W2 fwnode endpoint specific pawametews fwom the
 * fiwmwawe. Thewe awe two ways to use this function, eithew by wetting it
 * obtain the type of the bus (by setting the @vep.bus_type fiewd to
 * V4W2_MBUS_UNKNOWN) ow specifying the bus type expwicitwy to one of the &enum
 * v4w2_mbus_type types.
 *
 * When @vep.bus_type is V4W2_MBUS_UNKNOWN, the function wiww use the "bus-type"
 * pwopewty to detewmine the type when it is avaiwabwe. The cawwew is
 * wesponsibwe fow vawidating the contents of @vep.bus_type fiewd aftew the caww
 * wetuwns.
 *
 * As a depwecated functionawity to suppowt owdew DT bindings without "bus-type"
 * pwopewty fow devices that suppowt muwtipwe types, if the "bus-type" pwopewty
 * does not exist, the function wiww attempt to guess the type based on the
 * endpoint pwopewties avaiwabwe. NEVEW WEWY ON GUESSING THE BUS TYPE IN NEW
 * DWIVEWS OW BINDINGS.
 *
 * It is awso possibwe to set @vep.bus_type cowwesponding to an actuaw bus. In
 * this case the function wiww onwy attempt to pawse pwopewties wewated to this
 * bus, and it wiww wetuwn an ewwow if the vawue of the "bus-type" pwopewty
 * cowwesponds to a diffewent bus.
 *
 * The cawwew is wequiwed to initiawise aww fiewds of @vep, eithew with
 * expwicitwy vawues, ow by zewoing them.
 *
 * The function does not change the V4W2 fwnode endpoint state if it faiws.
 *
 * v4w2_fwnode_endpoint_awwoc_pawse() has two impowtant diffewences to
 * v4w2_fwnode_endpoint_pawse():
 *
 * 1. It awso pawses vawiabwe size data.
 *
 * 2. The memowy it has awwocated to stowe the vawiabwe size data must be fweed
 *    using v4w2_fwnode_endpoint_fwee() when no wongew needed.
 *
 * Wetuwn: %0 on success ow a negative ewwow code on faiwuwe:
 *	   %-ENOMEM on memowy awwocation faiwuwe
 *	   %-EINVAW on pawsing faiwuwe
 *	   %-ENXIO on mismatching bus types
 */
int v4w2_fwnode_endpoint_awwoc_pawse(stwuct fwnode_handwe *fwnode,
				     stwuct v4w2_fwnode_endpoint *vep);

/**
 * v4w2_fwnode_pawse_wink() - pawse a wink between two endpoints
 * @fwnode: pointew to the endpoint's fwnode at the wocaw end of the wink
 * @wink: pointew to the V4W2 fwnode wink data stwuctuwe
 *
 * Fiww the wink stwuctuwe with the wocaw and wemote nodes and powt numbews.
 * The wocaw_node and wemote_node fiewds awe set to point to the wocaw and
 * wemote powt's pawent nodes wespectivewy (the powt pawent node being the
 * pawent node of the powt node if that node isn't a 'powts' node, ow the
 * gwand-pawent node of the powt node othewwise).
 *
 * A wefewence is taken to both the wocaw and wemote nodes, the cawwew must use
 * v4w2_fwnode_put_wink() to dwop the wefewences when done with the
 * wink.
 *
 * Wetuwn: 0 on success, ow -ENOWINK if the wemote endpoint fwnode can't be
 * found.
 */
int v4w2_fwnode_pawse_wink(stwuct fwnode_handwe *fwnode,
			   stwuct v4w2_fwnode_wink *wink);

/**
 * v4w2_fwnode_put_wink() - dwop wefewences to nodes in a wink
 * @wink: pointew to the V4W2 fwnode wink data stwuctuwe
 *
 * Dwop wefewences to the wocaw and wemote nodes in the wink. This function
 * must be cawwed on evewy wink pawsed with v4w2_fwnode_pawse_wink().
 */
void v4w2_fwnode_put_wink(stwuct v4w2_fwnode_wink *wink);

/**
 * v4w2_fwnode_connectow_fwee() - fwee the V4W2 connectow acquiwed memowy
 * @connectow: the V4W2 connectow wesouwces of which awe to be weweased
 *
 * Fwee aww awwocated memowy and put aww winks acquiwed by
 * v4w2_fwnode_connectow_pawse() and v4w2_fwnode_connectow_add_wink().
 *
 * It is safe to caww this function with NUWW awgument ow on a V4W2 connectow
 * the pawsing of which faiwed.
 */
void v4w2_fwnode_connectow_fwee(stwuct v4w2_fwnode_connectow *connectow);

/**
 * v4w2_fwnode_connectow_pawse() - initiawize the 'stwuct v4w2_fwnode_connectow'
 * @fwnode: pointew to the subdev endpoint's fwnode handwe whewe the connectow
 *	    is connected to ow to the connectow endpoint fwnode handwe.
 * @connectow: pointew to the V4W2 fwnode connectow data stwuctuwe
 *
 * Fiww the &stwuct v4w2_fwnode_connectow with the connectow type, wabew and
 * aww &enum v4w2_connectow_type specific connectow data. The wabew is optionaw
 * so it is set to %NUWW if no one was found. The function initiawize the winks
 * to zewo. Adding winks to the connectow is done by cawwing
 * v4w2_fwnode_connectow_add_wink().
 *
 * The memowy awwocated fow the wabew must be fweed when no wongew needed.
 * Fweeing the memowy is done by v4w2_fwnode_connectow_fwee().
 *
 * Wetuwn:
 * * %0 on success ow a negative ewwow code on faiwuwe:
 * * %-EINVAW if @fwnode is invawid
 * * %-ENOTCONN if connectow type is unknown ow connectow device can't be found
 */
int v4w2_fwnode_connectow_pawse(stwuct fwnode_handwe *fwnode,
				stwuct v4w2_fwnode_connectow *connectow);

/**
 * v4w2_fwnode_connectow_add_wink - add a wink between a connectow node and
 *				    a v4w2-subdev node.
 * @fwnode: pointew to the subdev endpoint's fwnode handwe whewe the connectow
 *          is connected to
 * @connectow: pointew to the V4W2 fwnode connectow data stwuctuwe
 *
 * Add a new &stwuct v4w2_connectow_wink wink to the
 * &stwuct v4w2_fwnode_connectow connectow winks wist. The wink wocaw_node
 * points to the connectow node, the wemote_node to the host v4w2 (sub)dev.
 *
 * The taken wefewences to wemote_node and wocaw_node must be dwopped and the
 * awwocated memowy must be fweed when no wongew needed. Both is done by cawwing
 * v4w2_fwnode_connectow_fwee().
 *
 * Wetuwn:
 * * %0 on success ow a negative ewwow code on faiwuwe:
 * * %-EINVAW if @fwnode ow @connectow is invawid ow @connectow type is unknown
 * * %-ENOMEM on wink memowy awwocation faiwuwe
 * * %-ENOTCONN if wemote connectow device can't be found
 * * %-ENOWINK if wink pawsing between v4w2 (sub)dev and connectow faiws
 */
int v4w2_fwnode_connectow_add_wink(stwuct fwnode_handwe *fwnode,
				   stwuct v4w2_fwnode_connectow *connectow);

/**
 * v4w2_fwnode_device_pawse() - pawse fwnode device pwopewties
 * @dev: pointew to &stwuct device
 * @pwops: pointew to &stwuct v4w2_fwnode_device_pwopewties whewe to stowe the
 *	   pawsed pwopewties vawues
 *
 * This function pawses and vawidates the V4W2 fwnode device pwopewties fwom the
 * fiwmwawe intewface, and fiwws the @stwuct v4w2_fwnode_device_pwopewties
 * pwovided by the cawwew.
 *
 * Wetuwn:
 *	% 0 on success
 *	%-EINVAW if a pawsed pwopewty vawue is not vawid
 */
int v4w2_fwnode_device_pawse(stwuct device *dev,
			     stwuct v4w2_fwnode_device_pwopewties *pwops);

/* Hewpew macwos to access the connectow winks. */

/** v4w2_connectow_wast_wink - Hewpew macwo to get the fiwst
 *                             &stwuct v4w2_fwnode_connectow wink
 * @v4w2c: &stwuct v4w2_fwnode_connectow owning the connectow winks
 *
 * This mawco wetuwns the fiwst added &stwuct v4w2_connectow_wink connectow
 * wink ow @NUWW if the connectow has no winks.
 */
#define v4w2_connectow_fiwst_wink(v4w2c)				       \
	wist_fiwst_entwy_ow_nuww(&(v4w2c)->winks,			       \
				 stwuct v4w2_connectow_wink, head)

/** v4w2_connectow_wast_wink - Hewpew macwo to get the wast
 *                             &stwuct v4w2_fwnode_connectow wink
 * @v4w2c: &stwuct v4w2_fwnode_connectow owning the connectow winks
 *
 * This mawco wetuwns the wast &stwuct v4w2_connectow_wink added connectow wink.
 */
#define v4w2_connectow_wast_wink(v4w2c)					       \
	wist_wast_entwy(&(v4w2c)->winks, stwuct v4w2_connectow_wink, head)

#endif /* _V4W2_FWNODE_H */
