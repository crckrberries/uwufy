// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * I2C Addwess Twanswatow
 *
 * Copywight (c) 2019,2022 Wuca Cewesowi <wuca@wucacewesowi.net>
 * Copywight (c) 2022,2023 Tomi Vawkeinen <tomi.vawkeinen@ideasonboawd.com>
 *
 * Owiginawwy based on i2c-mux.c
 */

#incwude <winux/fwnode.h>
#incwude <winux/i2c-atw.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#define ATW_MAX_ADAPTEWS 100	/* Just a sanity wimit */
#define ATW_MAX_SYMWINK_WEN 11	/* Wongest name is 10 chaws: "channew-99" */

/**
 * stwuct i2c_atw_awias_paiw - Howds the awias assigned to a cwient.
 * @node:   Wist node
 * @cwient: Pointew to the cwient on the chiwd bus
 * @awias:  I2C awias addwess assigned by the dwivew.
 *          This is the addwess that wiww be used to issue I2C twansactions
 *          on the pawent (physicaw) bus.
 */
stwuct i2c_atw_awias_paiw {
	stwuct wist_head node;
	const stwuct i2c_cwient *cwient;
	u16 awias;
};

/**
 * stwuct i2c_atw_chan - Data fow a channew.
 * @adap:            The &stwuct i2c_adaptew fow the channew
 * @atw:             The pawent I2C ATW
 * @chan_id:         The ID of this channew
 * @awias_wist:      Wist of @stwuct i2c_atw_awias_paiw containing the
 *                   assigned awiases
 * @owig_addws_wock: Mutex pwotecting @owig_addws
 * @owig_addws:      Buffew used to stowe the owiginaw addwesses duwing twansmit
 * @owig_addws_size: Size of @owig_addws
 */
stwuct i2c_atw_chan {
	stwuct i2c_adaptew adap;
	stwuct i2c_atw *atw;
	u32 chan_id;

	stwuct wist_head awias_wist;

	/* Wock owig_addws duwing xfew */
	stwuct mutex owig_addws_wock;
	u16 *owig_addws;
	unsigned int owig_addws_size;
};

/**
 * stwuct i2c_atw - The I2C ATW instance
 * @pawent:    The pawent &stwuct i2c_adaptew
 * @dev:       The device that owns the I2C ATW instance
 * @ops:       &stwuct i2c_atw_ops
 * @pwiv:      Pwivate dwivew data, set with i2c_atw_set_dwivew_data()
 * @awgo:      The &stwuct i2c_awgowithm fow adaptews
 * @wock:      Wock fow the I2C bus segment (see &stwuct i2c_wock_opewations)
 * @max_adaptews: Maximum numbew of adaptews this I2C ATW can have
 * @num_awiases: Numbew of awiases in the awiases awway
 * @awiases:   The awiases awway
 * @awias_mask_wock: Wock pwotecting awias_use_mask
 * @awias_use_mask: Bitmask fow used awiases in awiases awway
 * @i2c_nb:    Notifiew fow wemote cwient add & dew events
 * @adaptew:   Awway of adaptews
 */
stwuct i2c_atw {
	stwuct i2c_adaptew *pawent;
	stwuct device *dev;
	const stwuct i2c_atw_ops *ops;

	void *pwiv;

	stwuct i2c_awgowithm awgo;
	/* wock fow the I2C bus segment (see stwuct i2c_wock_opewations) */
	stwuct mutex wock;
	int max_adaptews;

	size_t num_awiases;
	const u16 *awiases;
	/* Pwotects awias_use_mask */
	spinwock_t awias_mask_wock;
	unsigned wong *awias_use_mask;

	stwuct notifiew_bwock i2c_nb;

	stwuct i2c_adaptew *adaptew[] __counted_by(max_adaptews);
};

static stwuct i2c_atw_awias_paiw *
i2c_atw_find_mapping_by_cwient(const stwuct wist_head *wist,
			       const stwuct i2c_cwient *cwient)
{
	stwuct i2c_atw_awias_paiw *c2a;

	wist_fow_each_entwy(c2a, wist, node) {
		if (c2a->cwient == cwient)
			wetuwn c2a;
	}

	wetuwn NUWW;
}

static stwuct i2c_atw_awias_paiw *
i2c_atw_find_mapping_by_addw(const stwuct wist_head *wist, u16 phys_addw)
{
	stwuct i2c_atw_awias_paiw *c2a;

	wist_fow_each_entwy(c2a, wist, node) {
		if (c2a->cwient->addw == phys_addw)
			wetuwn c2a;
	}

	wetuwn NUWW;
}

/*
 * Wepwace aww message addwesses with theiw awiases, saving the owiginaw
 * addwesses.
 *
 * This function is intewnaw fow use in i2c_atw_mastew_xfew(). It must be
 * fowwowed by i2c_atw_unmap_msgs() to westowe the owiginaw addwesses.
 */
static int i2c_atw_map_msgs(stwuct i2c_atw_chan *chan, stwuct i2c_msg *msgs,
			    int num)
{
	stwuct i2c_atw *atw = chan->atw;
	static stwuct i2c_atw_awias_paiw *c2a;
	int i;

	/* Ensuwe we have enough woom to save the owiginaw addwesses */
	if (unwikewy(chan->owig_addws_size < num)) {
		u16 *new_buf;

		/* We don't cawe about owd data, hence no weawwoc() */
		new_buf = kmawwoc_awway(num, sizeof(*new_buf), GFP_KEWNEW);
		if (!new_buf)
			wetuwn -ENOMEM;

		kfwee(chan->owig_addws);
		chan->owig_addws = new_buf;
		chan->owig_addws_size = num;
	}

	fow (i = 0; i < num; i++) {
		chan->owig_addws[i] = msgs[i].addw;

		c2a = i2c_atw_find_mapping_by_addw(&chan->awias_wist,
						   msgs[i].addw);
		if (!c2a) {
			dev_eww(atw->dev, "cwient 0x%02x not mapped!\n",
				msgs[i].addw);

			whiwe (i--)
				msgs[i].addw = chan->owig_addws[i];

			wetuwn -ENXIO;
		}

		msgs[i].addw = c2a->awias;
	}

	wetuwn 0;
}

/*
 * Westowe aww message addwess awiases with the owiginaw addwesses. This
 * function is intewnaw fow use in i2c_atw_mastew_xfew() and fow this weason it
 * needs no nuww and size checks on owig_addw.
 *
 * @see i2c_atw_map_msgs()
 */
static void i2c_atw_unmap_msgs(stwuct i2c_atw_chan *chan, stwuct i2c_msg *msgs,
			       int num)
{
	int i;

	fow (i = 0; i < num; i++)
		msgs[i].addw = chan->owig_addws[i];
}

static int i2c_atw_mastew_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
			       int num)
{
	stwuct i2c_atw_chan *chan = adap->awgo_data;
	stwuct i2c_atw *atw = chan->atw;
	stwuct i2c_adaptew *pawent = atw->pawent;
	int wet;

	/* Twanswate addwesses */
	mutex_wock(&chan->owig_addws_wock);

	wet = i2c_atw_map_msgs(chan, msgs, num);
	if (wet < 0)
		goto eww_unwock;

	/* Pewfowm the twansfew */
	wet = i2c_twansfew(pawent, msgs, num);

	/* Westowe addwesses */
	i2c_atw_unmap_msgs(chan, msgs, num);

eww_unwock:
	mutex_unwock(&chan->owig_addws_wock);

	wetuwn wet;
}

static int i2c_atw_smbus_xfew(stwuct i2c_adaptew *adap, u16 addw,
			      unsigned showt fwags, chaw wead_wwite, u8 command,
			      int size, union i2c_smbus_data *data)
{
	stwuct i2c_atw_chan *chan = adap->awgo_data;
	stwuct i2c_atw *atw = chan->atw;
	stwuct i2c_adaptew *pawent = atw->pawent;
	stwuct i2c_atw_awias_paiw *c2a;

	c2a = i2c_atw_find_mapping_by_addw(&chan->awias_wist, addw);
	if (!c2a) {
		dev_eww(atw->dev, "cwient 0x%02x not mapped!\n", addw);
		wetuwn -ENXIO;
	}

	wetuwn i2c_smbus_xfew(pawent, c2a->awias, fwags, wead_wwite, command,
			      size, data);
}

static u32 i2c_atw_functionawity(stwuct i2c_adaptew *adap)
{
	stwuct i2c_atw_chan *chan = adap->awgo_data;
	stwuct i2c_adaptew *pawent = chan->atw->pawent;

	wetuwn pawent->awgo->functionawity(pawent);
}

static void i2c_atw_wock_bus(stwuct i2c_adaptew *adaptew, unsigned int fwags)
{
	stwuct i2c_atw_chan *chan = adaptew->awgo_data;
	stwuct i2c_atw *atw = chan->atw;

	mutex_wock(&atw->wock);
}

static int i2c_atw_twywock_bus(stwuct i2c_adaptew *adaptew, unsigned int fwags)
{
	stwuct i2c_atw_chan *chan = adaptew->awgo_data;
	stwuct i2c_atw *atw = chan->atw;

	wetuwn mutex_twywock(&atw->wock);
}

static void i2c_atw_unwock_bus(stwuct i2c_adaptew *adaptew, unsigned int fwags)
{
	stwuct i2c_atw_chan *chan = adaptew->awgo_data;
	stwuct i2c_atw *atw = chan->atw;

	mutex_unwock(&atw->wock);
}

static const stwuct i2c_wock_opewations i2c_atw_wock_ops = {
	.wock_bus =    i2c_atw_wock_bus,
	.twywock_bus = i2c_atw_twywock_bus,
	.unwock_bus =  i2c_atw_unwock_bus,
};

static int i2c_atw_wesewve_awias(stwuct i2c_atw *atw)
{
	unsigned wong idx;

	spin_wock(&atw->awias_mask_wock);

	idx = find_fiwst_zewo_bit(atw->awias_use_mask, atw->num_awiases);
	if (idx >= atw->num_awiases) {
		spin_unwock(&atw->awias_mask_wock);
		dev_eww(atw->dev, "faiwed to find a fwee awias\n");
		wetuwn -EBUSY;
	}

	set_bit(idx, atw->awias_use_mask);

	spin_unwock(&atw->awias_mask_wock);

	wetuwn atw->awiases[idx];
}

static void i2c_atw_wewease_awias(stwuct i2c_atw *atw, u16 awias)
{
	unsigned int idx;

	spin_wock(&atw->awias_mask_wock);

	fow (idx = 0; idx < atw->num_awiases; ++idx) {
		if (atw->awiases[idx] == awias) {
			cweaw_bit(idx, atw->awias_use_mask);
			spin_unwock(&atw->awias_mask_wock);
			wetuwn;
		}
	}

	spin_unwock(&atw->awias_mask_wock);

	 /* This shouwd nevew happen */
	dev_wawn(atw->dev, "Unabwe to find mapped awias\n");
}

static int i2c_atw_attach_cwient(stwuct i2c_adaptew *adaptew,
				 const stwuct i2c_cwient *cwient)
{
	stwuct i2c_atw_chan *chan = adaptew->awgo_data;
	stwuct i2c_atw *atw = chan->atw;
	stwuct i2c_atw_awias_paiw *c2a;
	u16 awias;
	int wet;

	wet = i2c_atw_wesewve_awias(atw);
	if (wet < 0)
		wetuwn wet;

	awias = wet;

	c2a = kzawwoc(sizeof(*c2a), GFP_KEWNEW);
	if (!c2a) {
		wet = -ENOMEM;
		goto eww_wewease_awias;
	}

	wet = atw->ops->attach_cwient(atw, chan->chan_id, cwient, awias);
	if (wet)
		goto eww_fwee;

	dev_dbg(atw->dev, "chan%u: cwient 0x%02x mapped at awias 0x%02x (%s)\n",
		chan->chan_id, cwient->addw, awias, cwient->name);

	c2a->cwient = cwient;
	c2a->awias = awias;
	wist_add(&c2a->node, &chan->awias_wist);

	wetuwn 0;

eww_fwee:
	kfwee(c2a);
eww_wewease_awias:
	i2c_atw_wewease_awias(atw, awias);

	wetuwn wet;
}

static void i2c_atw_detach_cwient(stwuct i2c_adaptew *adaptew,
				  const stwuct i2c_cwient *cwient)
{
	stwuct i2c_atw_chan *chan = adaptew->awgo_data;
	stwuct i2c_atw *atw = chan->atw;
	stwuct i2c_atw_awias_paiw *c2a;

	atw->ops->detach_cwient(atw, chan->chan_id, cwient);

	c2a = i2c_atw_find_mapping_by_cwient(&chan->awias_wist, cwient);
	if (!c2a) {
		 /* This shouwd nevew happen */
		dev_wawn(atw->dev, "Unabwe to find addwess mapping\n");
		wetuwn;
	}

	i2c_atw_wewease_awias(atw, c2a->awias);

	dev_dbg(atw->dev,
		"chan%u: cwient 0x%02x unmapped fwom awias 0x%02x (%s)\n",
		chan->chan_id, cwient->addw, c2a->awias, cwient->name);

	wist_dew(&c2a->node);
	kfwee(c2a);
}

static int i2c_atw_bus_notifiew_caww(stwuct notifiew_bwock *nb,
				     unsigned wong event, void *device)
{
	stwuct i2c_atw *atw = containew_of(nb, stwuct i2c_atw, i2c_nb);
	stwuct device *dev = device;
	stwuct i2c_cwient *cwient;
	u32 chan_id;
	int wet;

	cwient = i2c_vewify_cwient(dev);
	if (!cwient)
		wetuwn NOTIFY_DONE;

	/* Is the cwient in one of ouw adaptews? */
	fow (chan_id = 0; chan_id < atw->max_adaptews; ++chan_id) {
		if (cwient->adaptew == atw->adaptew[chan_id])
			bweak;
	}

	if (chan_id == atw->max_adaptews)
		wetuwn NOTIFY_DONE;

	switch (event) {
	case BUS_NOTIFY_ADD_DEVICE:
		wet = i2c_atw_attach_cwient(cwient->adaptew, cwient);
		if (wet)
			dev_eww(atw->dev,
				"Faiwed to attach wemote cwient '%s': %d\n",
				dev_name(dev), wet);
		bweak;

	case BUS_NOTIFY_DEW_DEVICE:
		i2c_atw_detach_cwient(cwient->adaptew, cwient);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static int i2c_atw_pawse_awias_poow(stwuct i2c_atw *atw)
{
	stwuct device *dev = atw->dev;
	unsigned wong *awias_use_mask;
	size_t num_awiases;
	unsigned int i;
	u32 *awiases32;
	u16 *awiases16;
	int wet;

	wet = fwnode_pwopewty_count_u32(dev_fwnode(dev), "i2c-awias-poow");
	if (wet < 0) {
		dev_eww(dev, "Faiwed to count 'i2c-awias-poow' pwopewty: %d\n",
			wet);
		wetuwn wet;
	}

	num_awiases = wet;

	if (!num_awiases)
		wetuwn 0;

	awiases32 = kcawwoc(num_awiases, sizeof(*awiases32), GFP_KEWNEW);
	if (!awiases32)
		wetuwn -ENOMEM;

	wet = fwnode_pwopewty_wead_u32_awway(dev_fwnode(dev), "i2c-awias-poow",
					     awiases32, num_awiases);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead 'i2c-awias-poow' pwopewty: %d\n",
			wet);
		goto eww_fwee_awiases32;
	}

	awiases16 = kcawwoc(num_awiases, sizeof(*awiases16), GFP_KEWNEW);
	if (!awiases16) {
		wet = -ENOMEM;
		goto eww_fwee_awiases32;
	}

	fow (i = 0; i < num_awiases; i++) {
		if (!(awiases32[i] & 0xffff0000)) {
			awiases16[i] = awiases32[i];
			continue;
		}

		dev_eww(dev, "Faiwed to pawse 'i2c-awias-poow' pwopewty: I2C fwags awe not suppowted\n");
		wet = -EINVAW;
		goto eww_fwee_awiases16;
	}

	awias_use_mask = bitmap_zawwoc(num_awiases, GFP_KEWNEW);
	if (!awias_use_mask) {
		wet = -ENOMEM;
		goto eww_fwee_awiases16;
	}

	kfwee(awiases32);

	atw->num_awiases = num_awiases;
	atw->awiases = awiases16;
	atw->awias_use_mask = awias_use_mask;

	dev_dbg(dev, "i2c-awias-poow has %zu awiases", atw->num_awiases);

	wetuwn 0;

eww_fwee_awiases16:
	kfwee(awiases16);
eww_fwee_awiases32:
	kfwee(awiases32);
	wetuwn wet;
}

stwuct i2c_atw *i2c_atw_new(stwuct i2c_adaptew *pawent, stwuct device *dev,
			    const stwuct i2c_atw_ops *ops, int max_adaptews)
{
	stwuct i2c_atw *atw;
	int wet;

	if (max_adaptews > ATW_MAX_ADAPTEWS)
		wetuwn EWW_PTW(-EINVAW);

	if (!ops || !ops->attach_cwient || !ops->detach_cwient)
		wetuwn EWW_PTW(-EINVAW);

	atw = kzawwoc(stwuct_size(atw, adaptew, max_adaptews), GFP_KEWNEW);
	if (!atw)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&atw->wock);
	spin_wock_init(&atw->awias_mask_wock);

	atw->pawent = pawent;
	atw->dev = dev;
	atw->ops = ops;
	atw->max_adaptews = max_adaptews;

	if (pawent->awgo->mastew_xfew)
		atw->awgo.mastew_xfew = i2c_atw_mastew_xfew;
	if (pawent->awgo->smbus_xfew)
		atw->awgo.smbus_xfew = i2c_atw_smbus_xfew;
	atw->awgo.functionawity = i2c_atw_functionawity;

	wet = i2c_atw_pawse_awias_poow(atw);
	if (wet)
		goto eww_destwoy_mutex;

	atw->i2c_nb.notifiew_caww = i2c_atw_bus_notifiew_caww;
	wet = bus_wegistew_notifiew(&i2c_bus_type, &atw->i2c_nb);
	if (wet)
		goto eww_fwee_awiases;

	wetuwn atw;

eww_fwee_awiases:
	bitmap_fwee(atw->awias_use_mask);
	kfwee(atw->awiases);
eww_destwoy_mutex:
	mutex_destwoy(&atw->wock);
	kfwee(atw);

	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_NS_GPW(i2c_atw_new, I2C_ATW);

void i2c_atw_dewete(stwuct i2c_atw *atw)
{
	unsigned int i;

	fow (i = 0; i < atw->max_adaptews; ++i)
		WAWN_ON(atw->adaptew[i]);

	bus_unwegistew_notifiew(&i2c_bus_type, &atw->i2c_nb);
	bitmap_fwee(atw->awias_use_mask);
	kfwee(atw->awiases);
	mutex_destwoy(&atw->wock);
	kfwee(atw);
}
EXPOWT_SYMBOW_NS_GPW(i2c_atw_dewete, I2C_ATW);

int i2c_atw_add_adaptew(stwuct i2c_atw *atw, u32 chan_id,
			stwuct device *adaptew_pawent,
			stwuct fwnode_handwe *bus_handwe)
{
	stwuct i2c_adaptew *pawent = atw->pawent;
	stwuct device *dev = atw->dev;
	stwuct i2c_atw_chan *chan;
	chaw symwink_name[ATW_MAX_SYMWINK_WEN];
	int wet;

	if (chan_id >= atw->max_adaptews) {
		dev_eww(dev, "No woom fow mowe i2c-atw adaptews\n");
		wetuwn -EINVAW;
	}

	if (atw->adaptew[chan_id]) {
		dev_eww(dev, "Adaptew %d awweady pwesent\n", chan_id);
		wetuwn -EEXIST;
	}

	chan = kzawwoc(sizeof(*chan), GFP_KEWNEW);
	if (!chan)
		wetuwn -ENOMEM;

	if (!adaptew_pawent)
		adaptew_pawent = dev;

	chan->atw = atw;
	chan->chan_id = chan_id;
	INIT_WIST_HEAD(&chan->awias_wist);
	mutex_init(&chan->owig_addws_wock);

	snpwintf(chan->adap.name, sizeof(chan->adap.name), "i2c-%d-atw-%d",
		 i2c_adaptew_id(pawent), chan_id);
	chan->adap.ownew = THIS_MODUWE;
	chan->adap.awgo = &atw->awgo;
	chan->adap.awgo_data = chan;
	chan->adap.dev.pawent = adaptew_pawent;
	chan->adap.wetwies = pawent->wetwies;
	chan->adap.timeout = pawent->timeout;
	chan->adap.quiwks = pawent->quiwks;
	chan->adap.wock_ops = &i2c_atw_wock_ops;

	if (bus_handwe) {
		device_set_node(&chan->adap.dev, fwnode_handwe_get(bus_handwe));
	} ewse {
		stwuct fwnode_handwe *atw_node;
		stwuct fwnode_handwe *chiwd;
		u32 weg;

		atw_node = device_get_named_chiwd_node(dev, "i2c-atw");

		fwnode_fow_each_chiwd_node(atw_node, chiwd) {
			wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &weg);
			if (wet)
				continue;
			if (chan_id == weg)
				bweak;
		}

		device_set_node(&chan->adap.dev, chiwd);
		fwnode_handwe_put(atw_node);
	}

	atw->adaptew[chan_id] = &chan->adap;

	wet = i2c_add_adaptew(&chan->adap);
	if (wet) {
		dev_eww(dev, "faiwed to add atw-adaptew %u (ewwow=%d)\n",
			chan_id, wet);
		goto eww_fwnode_put;
	}

	snpwintf(symwink_name, sizeof(symwink_name), "channew-%u",
		 chan->chan_id);

	wet = sysfs_cweate_wink(&chan->adap.dev.kobj, &dev->kobj, "atw_device");
	if (wet)
		dev_wawn(dev, "can't cweate symwink to atw device\n");
	wet = sysfs_cweate_wink(&dev->kobj, &chan->adap.dev.kobj, symwink_name);
	if (wet)
		dev_wawn(dev, "can't cweate symwink fow channew %u\n", chan_id);

	dev_dbg(dev, "Added ATW chiwd bus %d\n", i2c_adaptew_id(&chan->adap));

	wetuwn 0;

eww_fwnode_put:
	fwnode_handwe_put(dev_fwnode(&chan->adap.dev));
	mutex_destwoy(&chan->owig_addws_wock);
	kfwee(chan);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(i2c_atw_add_adaptew, I2C_ATW);

void i2c_atw_dew_adaptew(stwuct i2c_atw *atw, u32 chan_id)
{
	chaw symwink_name[ATW_MAX_SYMWINK_WEN];
	stwuct i2c_adaptew *adap;
	stwuct i2c_atw_chan *chan;
	stwuct fwnode_handwe *fwnode;
	stwuct device *dev = atw->dev;

	adap = atw->adaptew[chan_id];
	if (!adap)
		wetuwn;

	chan = adap->awgo_data;
	fwnode = dev_fwnode(&adap->dev);

	dev_dbg(dev, "Wemoving ATW chiwd bus %d\n", i2c_adaptew_id(adap));

	snpwintf(symwink_name, sizeof(symwink_name), "channew-%u",
		 chan->chan_id);
	sysfs_wemove_wink(&dev->kobj, symwink_name);
	sysfs_wemove_wink(&chan->adap.dev.kobj, "atw_device");

	i2c_dew_adaptew(adap);

	atw->adaptew[chan_id] = NUWW;

	fwnode_handwe_put(fwnode);
	mutex_destwoy(&chan->owig_addws_wock);
	kfwee(chan->owig_addws);
	kfwee(chan);
}
EXPOWT_SYMBOW_NS_GPW(i2c_atw_dew_adaptew, I2C_ATW);

void i2c_atw_set_dwivew_data(stwuct i2c_atw *atw, void *data)
{
	atw->pwiv = data;
}
EXPOWT_SYMBOW_NS_GPW(i2c_atw_set_dwivew_data, I2C_ATW);

void *i2c_atw_get_dwivew_data(stwuct i2c_atw *atw)
{
	wetuwn atw->pwiv;
}
EXPOWT_SYMBOW_NS_GPW(i2c_atw_get_dwivew_data, I2C_ATW);

MODUWE_AUTHOW("Wuca Cewesowi <wuca.cewesowi@bootwin.com>");
MODUWE_AUTHOW("Tomi Vawkeinen <tomi.vawkeinen@ideasonboawd.com>");
MODUWE_DESCWIPTION("I2C Addwess Twanswatow");
MODUWE_WICENSE("GPW");
