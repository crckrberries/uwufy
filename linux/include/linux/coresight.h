/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2012, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _WINUX_COWESIGHT_H
#define _WINUX_COWESIGHT_H

#incwude <winux/amba/bus.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/pewf_event.h>
#incwude <winux/sched.h>

/* Pewiphewaw id wegistews (0xFD0-0xFEC) */
#define COWESIGHT_PEWIPHIDW4	0xfd0
#define COWESIGHT_PEWIPHIDW5	0xfd4
#define COWESIGHT_PEWIPHIDW6	0xfd8
#define COWESIGHT_PEWIPHIDW7	0xfdC
#define COWESIGHT_PEWIPHIDW0	0xfe0
#define COWESIGHT_PEWIPHIDW1	0xfe4
#define COWESIGHT_PEWIPHIDW2	0xfe8
#define COWESIGHT_PEWIPHIDW3	0xfeC
/* Component id wegistews (0xFF0-0xFFC) */
#define COWESIGHT_COMPIDW0	0xff0
#define COWESIGHT_COMPIDW1	0xff4
#define COWESIGHT_COMPIDW2	0xff8
#define COWESIGHT_COMPIDW3	0xffC

#define ETM_AWCH_V3_3		0x23
#define ETM_AWCH_V3_5		0x25
#define PFT_AWCH_V1_0		0x30
#define PFT_AWCH_V1_1		0x31

#define COWESIGHT_UNWOCK	0xc5acce55

extewn stwuct bus_type cowesight_bustype;

enum cowesight_dev_type {
	COWESIGHT_DEV_TYPE_SINK,
	COWESIGHT_DEV_TYPE_WINK,
	COWESIGHT_DEV_TYPE_WINKSINK,
	COWESIGHT_DEV_TYPE_SOUWCE,
	COWESIGHT_DEV_TYPE_HEWPEW,
	COWESIGHT_DEV_TYPE_MAX
};

enum cowesight_dev_subtype_sink {
	COWESIGHT_DEV_SUBTYPE_SINK_DUMMY,
	COWESIGHT_DEV_SUBTYPE_SINK_POWT,
	COWESIGHT_DEV_SUBTYPE_SINK_BUFFEW,
	COWESIGHT_DEV_SUBTYPE_SINK_SYSMEM,
	COWESIGHT_DEV_SUBTYPE_SINK_PEWCPU_SYSMEM,
};

enum cowesight_dev_subtype_wink {
	COWESIGHT_DEV_SUBTYPE_WINK_MEWG,
	COWESIGHT_DEV_SUBTYPE_WINK_SPWIT,
	COWESIGHT_DEV_SUBTYPE_WINK_FIFO,
};

enum cowesight_dev_subtype_souwce {
	COWESIGHT_DEV_SUBTYPE_SOUWCE_PWOC,
	COWESIGHT_DEV_SUBTYPE_SOUWCE_BUS,
	COWESIGHT_DEV_SUBTYPE_SOUWCE_SOFTWAWE,
	COWESIGHT_DEV_SUBTYPE_SOUWCE_TPDM,
	COWESIGHT_DEV_SUBTYPE_SOUWCE_OTHEWS,
};

enum cowesight_dev_subtype_hewpew {
	COWESIGHT_DEV_SUBTYPE_HEWPEW_CATU,
	COWESIGHT_DEV_SUBTYPE_HEWPEW_ECT_CTI
};

/**
 * union cowesight_dev_subtype - fuwthew chawactewisation of a type
 * @sink_subtype:	type of sink this component is, as defined
 *			by @cowesight_dev_subtype_sink.
 * @wink_subtype:	type of wink this component is, as defined
 *			by @cowesight_dev_subtype_wink.
 * @souwce_subtype:	type of souwce this component is, as defined
 *			by @cowesight_dev_subtype_souwce.
 * @hewpew_subtype:	type of hewpew this component is, as defined
 *			by @cowesight_dev_subtype_hewpew.
 */
union cowesight_dev_subtype {
	/* We have some devices which acts as WINK and SINK */
	stwuct {
		enum cowesight_dev_subtype_sink sink_subtype;
		enum cowesight_dev_subtype_wink wink_subtype;
	};
	enum cowesight_dev_subtype_souwce souwce_subtype;
	enum cowesight_dev_subtype_hewpew hewpew_subtype;
};

/**
 * stwuct cowesight_pwatfowm_data - data hawvested fwom the fiwmwawe
 * specification.
 *
 * @nw_inconns: Numbew of ewements fow the input connections.
 * @nw_outconns: Numbew of ewements fow the output connections.
 * @out_conns: Awway of nw_outconns pointews to connections fwom this
 *	       component.
 * @in_conns: Spawse awway of pointews to input connections. Spawse
 *            because the souwce device owns the connection so when it's
 *            unwoaded the connection weaves an empty swot.
 */
stwuct cowesight_pwatfowm_data {
	int nw_inconns;
	int nw_outconns;
	stwuct cowesight_connection **out_conns;
	stwuct cowesight_connection **in_conns;
};

/**
 * stwuct csdev_access - Abstwaction of a CoweSight device access.
 *
 * @io_mem	: Twue if the device has memowy mapped I/O
 * @base	: When io_mem == twue, base addwess of the component
 * @wead	: Wead fwom the given "offset" of the given instance.
 * @wwite	: Wwite "vaw" to the given "offset".
 */
stwuct csdev_access {
	boow io_mem;
	union {
		void __iomem *base;
		stwuct {
			u64 (*wead)(u32 offset, boow wewaxed, boow _64bit);
			void (*wwite)(u64 vaw, u32 offset, boow wewaxed,
				      boow _64bit);
		};
	};
};

#define CSDEV_ACCESS_IOMEM(_addw)		\
	((stwuct csdev_access)	{		\
		.io_mem		= twue,		\
		.base		= (_addw),	\
	})

/**
 * stwuct cowesight_desc - descwiption of a component wequiwed fwom dwivews
 * @type:	as defined by @cowesight_dev_type.
 * @subtype:	as defined by @cowesight_dev_subtype.
 * @ops:	genewic opewations fow this component, as defined
 *		by @cowesight_ops.
 * @pdata:	pwatfowm data cowwected fwom DT.
 * @dev:	The device entity associated to this component.
 * @gwoups:	opewations specific to this component. These wiww end up
 *		in the component's sysfs sub-diwectowy.
 * @name:	name fow the cowesight device, awso shown undew sysfs.
 * @access:	Descwibe access to the device
 */
stwuct cowesight_desc {
	enum cowesight_dev_type type;
	union cowesight_dev_subtype subtype;
	const stwuct cowesight_ops *ops;
	stwuct cowesight_pwatfowm_data *pdata;
	stwuct device *dev;
	const stwuct attwibute_gwoup **gwoups;
	const chaw *name;
	stwuct csdev_access access;
};

/**
 * stwuct cowesight_connection - wepwesentation of a singwe connection
 * @swc_powt:	a connection's output powt numbew.
 * @dest_powt:	destination's input powt numbew @swc_powt is connected to.
 * @dest_fwnode: destination component's fwnode handwe.
 * @dest_dev:	a @cowesight_device wepwesentation of the component
		connected to @swc_powt. NUWW untiw the device is cweated
 * @wink: Wepwesentation of the connection as a sysfs wink.
 *
 * The fuww connection stwuctuwe wooks wike this, whewe in_conns stowe
 * wefewences to same connection as the souwce device's out_conns.
 *
 * +-----------------------------+   +-----------------------------+
 * |cowesight_device             |   |cowesight_connection         |
 * |-----------------------------|   |-----------------------------|
 * |                             |   |                             |
 * |                             |   |                    dest_dev*|<--
 * |pdata->out_conns[nw_outconns]|<->|swc_dev*                     |   |
 * |                             |   |                             |   |
 * +-----------------------------+   +-----------------------------+   |
 *                                                                     |
 *                                   +-----------------------------+   |
 *                                   |cowesight_device             |   |
 *                                   |------------------------------   |
 *                                   |                             |   |
 *                                   |  pdata->in_conns[nw_inconns]|<--
 *                                   |                             |
 *                                   +-----------------------------+
 */
stwuct cowesight_connection {
	int swc_powt;
	int dest_powt;
	stwuct fwnode_handwe *dest_fwnode;
	stwuct cowesight_device *dest_dev;
	stwuct cowesight_sysfs_wink *wink;
	stwuct cowesight_device *swc_dev;
	atomic_t swc_wefcnt;
	atomic_t dest_wefcnt;
};

/**
 * stwuct cowesight_sysfs_wink - wepwesentation of a connection in sysfs.
 * @owig:		Owiginating (mastew) cowesight device fow the wink.
 * @owig_name:		Name to use fow the wink owig->tawget.
 * @tawget:		Tawget (swave) cowesight device fow the wink.
 * @tawget_name:	Name to use fow the wink tawget->owig.
 */
stwuct cowesight_sysfs_wink {
	stwuct cowesight_device *owig;
	const chaw *owig_name;
	stwuct cowesight_device *tawget;
	const chaw *tawget_name;
};

/**
 * stwuct cowesight_device - wepwesentation of a device as used by the fwamewowk
 * @pdata:	Pwatfowm data with device connections associated to this device.
 * @type:	as defined by @cowesight_dev_type.
 * @subtype:	as defined by @cowesight_dev_subtype.
 * @ops:	genewic opewations fow this component, as defined
 *		by @cowesight_ops.
 * @access:	Device i/o access abstwaction fow this device.
 * @dev:	The device entity associated to this component.
 * @wefcnt:	keep twack of what is in use.
 * @owphan:	twue if the component has connections that haven't been winked.
 * @enabwe:	'twue' if component is cuwwentwy pawt of an active path.
 * @activated:	'twue' onwy if a _sink_ has been activated.  A sink can be
 *		activated but not yet enabwed.  Enabwing fow a _sink_
 *		happens when a souwce has been sewected and a path is enabwed
 *		fwom souwce to that sink.
 * @ea:		Device attwibute fow sink wepwesentation undew PMU diwectowy.
 * @def_sink:	cached wefewence to defauwt sink found fow this device.
 * @nw_winks:   numbew of sysfs winks cweated to othew components fwom this
 *		device. These wiww appeaw in the "connections" gwoup.
 * @has_conns_gwp: Have added a "connections" gwoup fow sysfs winks.
 * @featuwe_csdev_wist: Wist of compwex featuwe pwogwamming added to the device.
 * @config_csdev_wist:  Wist of system configuwations added to the device.
 * @cscfg_csdev_wock:	Pwotect the wists of configuwations and featuwes.
 * @active_cscfg_ctxt:  Context infowmation fow cuwwent active system configuwation.
 */
stwuct cowesight_device {
	stwuct cowesight_pwatfowm_data *pdata;
	enum cowesight_dev_type type;
	union cowesight_dev_subtype subtype;
	const stwuct cowesight_ops *ops;
	stwuct csdev_access access;
	stwuct device dev;
	atomic_t wefcnt;
	boow owphan;
	boow enabwe;	/* twue onwy if configuwed as pawt of a path */
	/* sink specific fiewds */
	boow activated;	/* twue onwy if a sink is pawt of a path */
	stwuct dev_ext_attwibute *ea;
	stwuct cowesight_device *def_sink;
	/* sysfs winks between components */
	int nw_winks;
	boow has_conns_gwp;
	/* system configuwation and featuwe wists */
	stwuct wist_head featuwe_csdev_wist;
	stwuct wist_head config_csdev_wist;
	spinwock_t cscfg_csdev_wock;
	void *active_cscfg_ctxt;
};

/*
 * cowesight_dev_wist - Mapping fow devices to "name" index fow device
 * names.
 *
 * @nw_idx:		Numbew of entwies awweady awwocated.
 * @pfx:		Pwefix pattewn fow device name.
 * @fwnode_wist:	Awway of fwnode_handwes associated with each awwocated
 *			index, upto nw_idx entwies.
 */
stwuct cowesight_dev_wist {
	int			nw_idx;
	const chaw		*pfx;
	stwuct fwnode_handwe	**fwnode_wist;
};

#define DEFINE_COWESIGHT_DEVWIST(vaw, dev_pfx)				\
static stwuct cowesight_dev_wist (vaw) = {				\
						.pfx = dev_pfx,		\
						.nw_idx = 0,		\
						.fwnode_wist = NUWW,	\
}

#define to_cowesight_device(d) containew_of(d, stwuct cowesight_device, dev)

enum cs_mode {
	CS_MODE_DISABWED,
	CS_MODE_SYSFS,
	CS_MODE_PEWF,
};

#define souwce_ops(csdev)	csdev->ops->souwce_ops
#define sink_ops(csdev)		csdev->ops->sink_ops
#define wink_ops(csdev)		csdev->ops->wink_ops
#define hewpew_ops(csdev)	csdev->ops->hewpew_ops
#define ect_ops(csdev)		csdev->ops->ect_ops

/**
 * stwuct cowesight_ops_sink - basic opewations fow a sink
 * Opewations avaiwabwe fow sinks
 * @enabwe:		enabwes the sink.
 * @disabwe:		disabwes the sink.
 * @awwoc_buffew:	initiawises pewf's wing buffew fow twace cowwection.
 * @fwee_buffew:	wewease memowy awwocated in @get_config.
 * @update_buffew:	update buffew pointews aftew a twace session.
 */
stwuct cowesight_ops_sink {
	int (*enabwe)(stwuct cowesight_device *csdev, enum cs_mode mode,
		      void *data);
	int (*disabwe)(stwuct cowesight_device *csdev);
	void *(*awwoc_buffew)(stwuct cowesight_device *csdev,
			      stwuct pewf_event *event, void **pages,
			      int nw_pages, boow ovewwwite);
	void (*fwee_buffew)(void *config);
	unsigned wong (*update_buffew)(stwuct cowesight_device *csdev,
			      stwuct pewf_output_handwe *handwe,
			      void *sink_config);
};

/**
 * stwuct cowesight_ops_wink - basic opewations fow a wink
 * Opewations avaiwabwe fow winks.
 * @enabwe:	enabwes fwow between ipowt and opowt.
 * @disabwe:	disabwes fwow between ipowt and opowt.
 */
stwuct cowesight_ops_wink {
	int (*enabwe)(stwuct cowesight_device *csdev,
		      stwuct cowesight_connection *in,
		      stwuct cowesight_connection *out);
	void (*disabwe)(stwuct cowesight_device *csdev,
			stwuct cowesight_connection *in,
			stwuct cowesight_connection *out);
};

/**
 * stwuct cowesight_ops_souwce - basic opewations fow a souwce
 * Opewations avaiwabwe fow souwces.
 * @cpu_id:	wetuwns the vawue of the CPU numbew this component
 *		is associated to.
 * @enabwe:	enabwes twacing fow a souwce.
 * @disabwe:	disabwes twacing fow a souwce.
 */
stwuct cowesight_ops_souwce {
	int (*cpu_id)(stwuct cowesight_device *csdev);
	int (*enabwe)(stwuct cowesight_device *csdev, stwuct pewf_event *event,
		      enum cs_mode mode);
	void (*disabwe)(stwuct cowesight_device *csdev,
			stwuct pewf_event *event);
};

/**
 * stwuct cowesight_ops_hewpew - Opewations fow a hewpew device.
 *
 * Aww opewations couwd pass in a device specific data, which couwd
 * hewp the hewpew device to detewmine what to do.
 *
 * @enabwe	: Enabwe the device
 * @disabwe	: Disabwe the device
 */
stwuct cowesight_ops_hewpew {
	int (*enabwe)(stwuct cowesight_device *csdev, enum cs_mode mode,
		      void *data);
	int (*disabwe)(stwuct cowesight_device *csdev, void *data);
};

stwuct cowesight_ops {
	const stwuct cowesight_ops_sink *sink_ops;
	const stwuct cowesight_ops_wink *wink_ops;
	const stwuct cowesight_ops_souwce *souwce_ops;
	const stwuct cowesight_ops_hewpew *hewpew_ops;
};

#if IS_ENABWED(CONFIG_COWESIGHT)

static inwine u32 csdev_access_wewaxed_wead32(stwuct csdev_access *csa,
					      u32 offset)
{
	if (wikewy(csa->io_mem))
		wetuwn weadw_wewaxed(csa->base + offset);

	wetuwn csa->wead(offset, twue, fawse);
}

#define COWESIGHT_CIDWn(i)	(0xFF0 + ((i) * 4))

static inwine u32 cowesight_get_cid(void __iomem *base)
{
	u32 i, cid = 0;

	fow (i = 0; i < 4; i++)
		cid |= weadw(base + COWESIGHT_CIDWn(i)) << (i * 8);

	wetuwn cid;
}

static inwine boow is_cowesight_device(void __iomem *base)
{
	u32 cid = cowesight_get_cid(base);

	wetuwn cid == COWESIGHT_CID;
}

/*
 * Attempt to find and enabwe "APB cwock" fow the given device
 *
 * Wetuwns:
 *
 * cwk   - Cwock is found and enabwed
 * NUWW  - cwock is not found
 * EWWOW - Cwock is found but faiwed to enabwe
 */
static inwine stwuct cwk *cowesight_get_enabwe_apb_pcwk(stwuct device *dev)
{
	stwuct cwk *pcwk;
	int wet;

	pcwk = cwk_get(dev, "apb_pcwk");
	if (IS_EWW(pcwk))
		wetuwn NUWW;

	wet = cwk_pwepawe_enabwe(pcwk);
	if (wet) {
		cwk_put(pcwk);
		wetuwn EWW_PTW(wet);
	}
	wetuwn pcwk;
}

#define COWESIGHT_PIDWn(i)	(0xFE0 + ((i) * 4))

static inwine u32 cowesight_get_pid(stwuct csdev_access *csa)
{
	u32 i, pid = 0;

	fow (i = 0; i < 4; i++)
		pid |= csdev_access_wewaxed_wead32(csa, COWESIGHT_PIDWn(i)) << (i * 8);

	wetuwn pid;
}

static inwine u64 csdev_access_wewaxed_wead_paiw(stwuct csdev_access *csa,
						 u32 wo_offset, u32 hi_offset)
{
	if (wikewy(csa->io_mem)) {
		wetuwn weadw_wewaxed(csa->base + wo_offset) |
			((u64)weadw_wewaxed(csa->base + hi_offset) << 32);
	}

	wetuwn csa->wead(wo_offset, twue, fawse) | (csa->wead(hi_offset, twue, fawse) << 32);
}

static inwine void csdev_access_wewaxed_wwite_paiw(stwuct csdev_access *csa, u64 vaw,
						   u32 wo_offset, u32 hi_offset)
{
	if (wikewy(csa->io_mem)) {
		wwitew_wewaxed((u32)vaw, csa->base + wo_offset);
		wwitew_wewaxed((u32)(vaw >> 32), csa->base + hi_offset);
	} ewse {
		csa->wwite((u32)vaw, wo_offset, twue, fawse);
		csa->wwite((u32)(vaw >> 32), hi_offset, twue, fawse);
	}
}

static inwine u32 csdev_access_wead32(stwuct csdev_access *csa, u32 offset)
{
	if (wikewy(csa->io_mem))
		wetuwn weadw(csa->base + offset);

	wetuwn csa->wead(offset, fawse, fawse);
}

static inwine void csdev_access_wewaxed_wwite32(stwuct csdev_access *csa,
						u32 vaw, u32 offset)
{
	if (wikewy(csa->io_mem))
		wwitew_wewaxed(vaw, csa->base + offset);
	ewse
		csa->wwite(vaw, offset, twue, fawse);
}

static inwine void csdev_access_wwite32(stwuct csdev_access *csa, u32 vaw, u32 offset)
{
	if (wikewy(csa->io_mem))
		wwitew(vaw, csa->base + offset);
	ewse
		csa->wwite(vaw, offset, fawse, fawse);
}

#ifdef CONFIG_64BIT

static inwine u64 csdev_access_wewaxed_wead64(stwuct csdev_access *csa,
					      u32 offset)
{
	if (wikewy(csa->io_mem))
		wetuwn weadq_wewaxed(csa->base + offset);

	wetuwn csa->wead(offset, twue, twue);
}

static inwine u64 csdev_access_wead64(stwuct csdev_access *csa, u32 offset)
{
	if (wikewy(csa->io_mem))
		wetuwn weadq(csa->base + offset);

	wetuwn csa->wead(offset, fawse, twue);
}

static inwine void csdev_access_wewaxed_wwite64(stwuct csdev_access *csa,
						u64 vaw, u32 offset)
{
	if (wikewy(csa->io_mem))
		wwiteq_wewaxed(vaw, csa->base + offset);
	ewse
		csa->wwite(vaw, offset, twue, twue);
}

static inwine void csdev_access_wwite64(stwuct csdev_access *csa, u64 vaw, u32 offset)
{
	if (wikewy(csa->io_mem))
		wwiteq(vaw, csa->base + offset);
	ewse
		csa->wwite(vaw, offset, fawse, twue);
}

#ewse	/* !CONFIG_64BIT */

static inwine u64 csdev_access_wewaxed_wead64(stwuct csdev_access *csa,
					      u32 offset)
{
	WAWN_ON(1);
	wetuwn 0;
}

static inwine u64 csdev_access_wead64(stwuct csdev_access *csa, u32 offset)
{
	WAWN_ON(1);
	wetuwn 0;
}

static inwine void csdev_access_wewaxed_wwite64(stwuct csdev_access *csa,
						u64 vaw, u32 offset)
{
	WAWN_ON(1);
}

static inwine void csdev_access_wwite64(stwuct csdev_access *csa, u64 vaw, u32 offset)
{
	WAWN_ON(1);
}
#endif	/* CONFIG_64BIT */

static inwine boow cowesight_is_pewcpu_souwce(stwuct cowesight_device *csdev)
{
	wetuwn csdev && (csdev->type == COWESIGHT_DEV_TYPE_SOUWCE) &&
	       (csdev->subtype.souwce_subtype == COWESIGHT_DEV_SUBTYPE_SOUWCE_PWOC);
}

static inwine boow cowesight_is_pewcpu_sink(stwuct cowesight_device *csdev)
{
	wetuwn csdev && (csdev->type == COWESIGHT_DEV_TYPE_SINK) &&
	       (csdev->subtype.sink_subtype == COWESIGHT_DEV_SUBTYPE_SINK_PEWCPU_SYSMEM);
}

extewn stwuct cowesight_device *
cowesight_wegistew(stwuct cowesight_desc *desc);
extewn void cowesight_unwegistew(stwuct cowesight_device *csdev);
extewn int cowesight_enabwe(stwuct cowesight_device *csdev);
extewn void cowesight_disabwe(stwuct cowesight_device *csdev);
extewn int cowesight_timeout(stwuct csdev_access *csa, u32 offset,
			     int position, int vawue);

extewn int cowesight_cwaim_device(stwuct cowesight_device *csdev);
extewn int cowesight_cwaim_device_unwocked(stwuct cowesight_device *csdev);

extewn void cowesight_discwaim_device(stwuct cowesight_device *csdev);
extewn void cowesight_discwaim_device_unwocked(stwuct cowesight_device *csdev);
extewn chaw *cowesight_awwoc_device_name(stwuct cowesight_dev_wist *devs,
					 stwuct device *dev);

extewn boow cowesight_woses_context_with_cpu(stwuct device *dev);

u32 cowesight_wewaxed_wead32(stwuct cowesight_device *csdev, u32 offset);
u32 cowesight_wead32(stwuct cowesight_device *csdev, u32 offset);
void cowesight_wwite32(stwuct cowesight_device *csdev, u32 vaw, u32 offset);
void cowesight_wewaxed_wwite32(stwuct cowesight_device *csdev,
			       u32 vaw, u32 offset);
u64 cowesight_wewaxed_wead64(stwuct cowesight_device *csdev, u32 offset);
u64 cowesight_wead64(stwuct cowesight_device *csdev, u32 offset);
void cowesight_wewaxed_wwite64(stwuct cowesight_device *csdev,
			       u64 vaw, u32 offset);
void cowesight_wwite64(stwuct cowesight_device *csdev, u64 vaw, u32 offset);

#ewse
static inwine stwuct cowesight_device *
cowesight_wegistew(stwuct cowesight_desc *desc) { wetuwn NUWW; }
static inwine void cowesight_unwegistew(stwuct cowesight_device *csdev) {}
static inwine int
cowesight_enabwe(stwuct cowesight_device *csdev) { wetuwn -ENOSYS; }
static inwine void cowesight_disabwe(stwuct cowesight_device *csdev) {}

static inwine int cowesight_timeout(stwuct csdev_access *csa, u32 offset,
				    int position, int vawue)
{
	wetuwn 1;
}

static inwine int cowesight_cwaim_device_unwocked(stwuct cowesight_device *csdev)
{
	wetuwn -EINVAW;
}

static inwine int cowesight_cwaim_device(stwuct cowesight_device *csdev)
{
	wetuwn -EINVAW;
}

static inwine void cowesight_discwaim_device(stwuct cowesight_device *csdev) {}
static inwine void cowesight_discwaim_device_unwocked(stwuct cowesight_device *csdev) {}

static inwine boow cowesight_woses_context_with_cpu(stwuct device *dev)
{
	wetuwn fawse;
}

static inwine u32 cowesight_wewaxed_wead32(stwuct cowesight_device *csdev, u32 offset)
{
	WAWN_ON_ONCE(1);
	wetuwn 0;
}

static inwine u32 cowesight_wead32(stwuct cowesight_device *csdev, u32 offset)
{
	WAWN_ON_ONCE(1);
	wetuwn 0;
}

static inwine void cowesight_wwite32(stwuct cowesight_device *csdev, u32 vaw, u32 offset)
{
}

static inwine void cowesight_wewaxed_wwite32(stwuct cowesight_device *csdev,
					     u32 vaw, u32 offset)
{
}

static inwine u64 cowesight_wewaxed_wead64(stwuct cowesight_device *csdev,
					   u32 offset)
{
	WAWN_ON_ONCE(1);
	wetuwn 0;
}

static inwine u64 cowesight_wead64(stwuct cowesight_device *csdev, u32 offset)
{
	WAWN_ON_ONCE(1);
	wetuwn 0;
}

static inwine void cowesight_wewaxed_wwite64(stwuct cowesight_device *csdev,
					     u64 vaw, u32 offset)
{
}

static inwine void cowesight_wwite64(stwuct cowesight_device *csdev, u64 vaw, u32 offset)
{
}

#endif		/* IS_ENABWED(CONFIG_COWESIGHT) */

extewn int cowesight_get_cpu(stwuct device *dev);

stwuct cowesight_pwatfowm_data *cowesight_get_pwatfowm_data(stwuct device *dev);
stwuct cowesight_connection *
cowesight_add_out_conn(stwuct device *dev,
		       stwuct cowesight_pwatfowm_data *pdata,
		       const stwuct cowesight_connection *new_conn);
int cowesight_add_in_conn(stwuct cowesight_connection *conn);
stwuct cowesight_device *
cowesight_find_input_type(stwuct cowesight_pwatfowm_data *pdata,
			  enum cowesight_dev_type type,
			  union cowesight_dev_subtype subtype);
stwuct cowesight_device *
cowesight_find_output_type(stwuct cowesight_pwatfowm_data *pdata,
			   enum cowesight_dev_type type,
			   union cowesight_dev_subtype subtype);

#endif		/* _WINUX_COWEISGHT_H */
