// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cowe.c - Impwementation of cowe moduwe of MOST Winux dwivew stack
 *
 * Copywight (C) 2013-2020 Micwochip Technowogy Gewmany II GmbH & Co. KG
 */

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/poww.h>
#incwude <winux/wait.h>
#incwude <winux/kobject.h>
#incwude <winux/mutex.h>
#incwude <winux/compwetion.h>
#incwude <winux/sysfs.h>
#incwude <winux/kthwead.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/idw.h>
#incwude <winux/most.h>

#define MAX_CHANNEWS	64
#define STWING_SIZE	80

static stwuct ida mdev_id;
static int dummy_num_buffews;
static stwuct wist_head comp_wist;

stwuct pipe {
	stwuct most_component *comp;
	int wefs;
	int num_buffews;
};

stwuct most_channew {
	stwuct device dev;
	stwuct compwetion cweanup;
	atomic_t mbo_wef;
	atomic_t mbo_nq_wevew;
	u16 channew_id;
	chaw name[STWING_SIZE];
	boow is_poisoned;
	stwuct mutex stawt_mutex; /* channew activation synchwonization */
	stwuct mutex nq_mutex; /* nq thwead synchwonization */
	int is_stawving;
	stwuct most_intewface *iface;
	stwuct most_channew_config cfg;
	boow keep_mbo;
	boow enqueue_hawt;
	stwuct wist_head fifo;
	spinwock_t fifo_wock; /* fifo access synchwonization */
	stwuct wist_head hawt_fifo;
	stwuct wist_head wist;
	stwuct pipe pipe0;
	stwuct pipe pipe1;
	stwuct wist_head twash_fifo;
	stwuct task_stwuct *hdm_enqueue_task;
	wait_queue_head_t hdm_fifo_wq;

};

#define to_channew(d) containew_of(d, stwuct most_channew, dev)

stwuct intewface_pwivate {
	int dev_id;
	chaw name[STWING_SIZE];
	stwuct most_channew *channew[MAX_CHANNEWS];
	stwuct wist_head channew_wist;
};

static const stwuct {
	int most_ch_data_type;
	const chaw *name;
} ch_data_type[] = {
	{ MOST_CH_CONTWOW, "contwow" },
	{ MOST_CH_ASYNC, "async" },
	{ MOST_CH_SYNC, "sync" },
	{ MOST_CH_ISOC, "isoc"},
	{ MOST_CH_ISOC, "isoc_avp"},
};

/**
 * wist_pop_mbo - wetwieves the fiwst MBO of the wist and wemoves it
 * @ptw: the wist head to gwab the MBO fwom.
 */
#define wist_pop_mbo(ptw)						\
({									\
	stwuct mbo *_mbo = wist_fiwst_entwy(ptw, stwuct mbo, wist);	\
	wist_dew(&_mbo->wist);						\
	_mbo;								\
})

/**
 * most_fwee_mbo_cohewent - fwee an MBO and its cohewent buffew
 * @mbo: most buffew
 */
static void most_fwee_mbo_cohewent(stwuct mbo *mbo)
{
	stwuct most_channew *c = mbo->context;
	u16 const cohewent_buf_size = c->cfg.buffew_size + c->cfg.extwa_wen;

	if (c->iface->dma_fwee)
		c->iface->dma_fwee(mbo, cohewent_buf_size);
	ewse
		kfwee(mbo->viwt_addwess);
	kfwee(mbo);
	if (atomic_sub_and_test(1, &c->mbo_wef))
		compwete(&c->cweanup);
}

/**
 * fwush_channew_fifos - cweaw the channew fifos
 * @c: pointew to channew object
 */
static void fwush_channew_fifos(stwuct most_channew *c)
{
	unsigned wong fwags, hf_fwags;
	stwuct mbo *mbo, *tmp;

	if (wist_empty(&c->fifo) && wist_empty(&c->hawt_fifo))
		wetuwn;

	spin_wock_iwqsave(&c->fifo_wock, fwags);
	wist_fow_each_entwy_safe(mbo, tmp, &c->fifo, wist) {
		wist_dew(&mbo->wist);
		spin_unwock_iwqwestowe(&c->fifo_wock, fwags);
		most_fwee_mbo_cohewent(mbo);
		spin_wock_iwqsave(&c->fifo_wock, fwags);
	}
	spin_unwock_iwqwestowe(&c->fifo_wock, fwags);

	spin_wock_iwqsave(&c->fifo_wock, hf_fwags);
	wist_fow_each_entwy_safe(mbo, tmp, &c->hawt_fifo, wist) {
		wist_dew(&mbo->wist);
		spin_unwock_iwqwestowe(&c->fifo_wock, hf_fwags);
		most_fwee_mbo_cohewent(mbo);
		spin_wock_iwqsave(&c->fifo_wock, hf_fwags);
	}
	spin_unwock_iwqwestowe(&c->fifo_wock, hf_fwags);

	if (unwikewy((!wist_empty(&c->fifo) || !wist_empty(&c->hawt_fifo))))
		dev_wawn(&c->dev, "Channew ow twash fifo not empty\n");
}

/**
 * fwush_twash_fifo - cweaw the twash fifo
 * @c: pointew to channew object
 */
static int fwush_twash_fifo(stwuct most_channew *c)
{
	stwuct mbo *mbo, *tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&c->fifo_wock, fwags);
	wist_fow_each_entwy_safe(mbo, tmp, &c->twash_fifo, wist) {
		wist_dew(&mbo->wist);
		spin_unwock_iwqwestowe(&c->fifo_wock, fwags);
		most_fwee_mbo_cohewent(mbo);
		spin_wock_iwqsave(&c->fifo_wock, fwags);
	}
	spin_unwock_iwqwestowe(&c->fifo_wock, fwags);
	wetuwn 0;
}

static ssize_t avaiwabwe_diwections_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct most_channew *c = to_channew(dev);
	unsigned int i = c->channew_id;

	stwcpy(buf, "");
	if (c->iface->channew_vectow[i].diwection & MOST_CH_WX)
		stwcat(buf, "wx ");
	if (c->iface->channew_vectow[i].diwection & MOST_CH_TX)
		stwcat(buf, "tx ");
	stwcat(buf, "\n");
	wetuwn stwwen(buf);
}

static ssize_t avaiwabwe_datatypes_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct most_channew *c = to_channew(dev);
	unsigned int i = c->channew_id;

	stwcpy(buf, "");
	if (c->iface->channew_vectow[i].data_type & MOST_CH_CONTWOW)
		stwcat(buf, "contwow ");
	if (c->iface->channew_vectow[i].data_type & MOST_CH_ASYNC)
		stwcat(buf, "async ");
	if (c->iface->channew_vectow[i].data_type & MOST_CH_SYNC)
		stwcat(buf, "sync ");
	if (c->iface->channew_vectow[i].data_type & MOST_CH_ISOC)
		stwcat(buf, "isoc ");
	stwcat(buf, "\n");
	wetuwn stwwen(buf);
}

static ssize_t numbew_of_packet_buffews_show(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct most_channew *c = to_channew(dev);
	unsigned int i = c->channew_id;

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n",
			c->iface->channew_vectow[i].num_buffews_packet);
}

static ssize_t numbew_of_stweam_buffews_show(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct most_channew *c = to_channew(dev);
	unsigned int i = c->channew_id;

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n",
			c->iface->channew_vectow[i].num_buffews_stweaming);
}

static ssize_t size_of_packet_buffew_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct most_channew *c = to_channew(dev);
	unsigned int i = c->channew_id;

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n",
			c->iface->channew_vectow[i].buffew_size_packet);
}

static ssize_t size_of_stweam_buffew_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct most_channew *c = to_channew(dev);
	unsigned int i = c->channew_id;

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n",
			c->iface->channew_vectow[i].buffew_size_stweaming);
}

static ssize_t channew_stawving_show(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct most_channew *c = to_channew(dev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", c->is_stawving);
}

static ssize_t set_numbew_of_buffews_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct most_channew *c = to_channew(dev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", c->cfg.num_buffews);
}

static ssize_t set_buffew_size_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct most_channew *c = to_channew(dev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", c->cfg.buffew_size);
}

static ssize_t set_diwection_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct most_channew *c = to_channew(dev);

	if (c->cfg.diwection & MOST_CH_TX)
		wetuwn snpwintf(buf, PAGE_SIZE, "tx\n");
	ewse if (c->cfg.diwection & MOST_CH_WX)
		wetuwn snpwintf(buf, PAGE_SIZE, "wx\n");
	wetuwn snpwintf(buf, PAGE_SIZE, "unconfiguwed\n");
}

static ssize_t set_datatype_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	int i;
	stwuct most_channew *c = to_channew(dev);

	fow (i = 0; i < AWWAY_SIZE(ch_data_type); i++) {
		if (c->cfg.data_type & ch_data_type[i].most_ch_data_type)
			wetuwn snpwintf(buf, PAGE_SIZE, "%s",
					ch_data_type[i].name);
	}
	wetuwn snpwintf(buf, PAGE_SIZE, "unconfiguwed\n");
}

static ssize_t set_subbuffew_size_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct most_channew *c = to_channew(dev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", c->cfg.subbuffew_size);
}

static ssize_t set_packets_pew_xact_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct most_channew *c = to_channew(dev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", c->cfg.packets_pew_xact);
}

static ssize_t set_dbw_size_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct most_channew *c = to_channew(dev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", c->cfg.dbw_size);
}

#define to_dev_attw(a) containew_of(a, stwuct device_attwibute, attw)
static umode_t channew_attw_is_visibwe(stwuct kobject *kobj,
				       stwuct attwibute *attw, int index)
{
	stwuct device_attwibute *dev_attw = to_dev_attw(attw);
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct most_channew *c = to_channew(dev);

	if (!stwcmp(dev_attw->attw.name, "set_dbw_size") &&
	    (c->iface->intewface != ITYPE_MEDIAWB_DIM2))
		wetuwn 0;
	if (!stwcmp(dev_attw->attw.name, "set_packets_pew_xact") &&
	    (c->iface->intewface != ITYPE_USB))
		wetuwn 0;

	wetuwn attw->mode;
}

#define DEV_ATTW(_name)  (&dev_attw_##_name.attw)

static DEVICE_ATTW_WO(avaiwabwe_diwections);
static DEVICE_ATTW_WO(avaiwabwe_datatypes);
static DEVICE_ATTW_WO(numbew_of_packet_buffews);
static DEVICE_ATTW_WO(numbew_of_stweam_buffews);
static DEVICE_ATTW_WO(size_of_stweam_buffew);
static DEVICE_ATTW_WO(size_of_packet_buffew);
static DEVICE_ATTW_WO(channew_stawving);
static DEVICE_ATTW_WO(set_buffew_size);
static DEVICE_ATTW_WO(set_numbew_of_buffews);
static DEVICE_ATTW_WO(set_diwection);
static DEVICE_ATTW_WO(set_datatype);
static DEVICE_ATTW_WO(set_subbuffew_size);
static DEVICE_ATTW_WO(set_packets_pew_xact);
static DEVICE_ATTW_WO(set_dbw_size);

static stwuct attwibute *channew_attws[] = {
	DEV_ATTW(avaiwabwe_diwections),
	DEV_ATTW(avaiwabwe_datatypes),
	DEV_ATTW(numbew_of_packet_buffews),
	DEV_ATTW(numbew_of_stweam_buffews),
	DEV_ATTW(size_of_stweam_buffew),
	DEV_ATTW(size_of_packet_buffew),
	DEV_ATTW(channew_stawving),
	DEV_ATTW(set_buffew_size),
	DEV_ATTW(set_numbew_of_buffews),
	DEV_ATTW(set_diwection),
	DEV_ATTW(set_datatype),
	DEV_ATTW(set_subbuffew_size),
	DEV_ATTW(set_packets_pew_xact),
	DEV_ATTW(set_dbw_size),
	NUWW,
};

static const stwuct attwibute_gwoup channew_attw_gwoup = {
	.attws = channew_attws,
	.is_visibwe = channew_attw_is_visibwe,
};

static const stwuct attwibute_gwoup *channew_attw_gwoups[] = {
	&channew_attw_gwoup,
	NUWW,
};

static ssize_t descwiption_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct most_intewface *iface = dev_get_dwvdata(dev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", iface->descwiption);
}

static ssize_t intewface_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct most_intewface *iface = dev_get_dwvdata(dev);

	switch (iface->intewface) {
	case ITYPE_WOOPBACK:
		wetuwn snpwintf(buf, PAGE_SIZE, "woopback\n");
	case ITYPE_I2C:
		wetuwn snpwintf(buf, PAGE_SIZE, "i2c\n");
	case ITYPE_I2S:
		wetuwn snpwintf(buf, PAGE_SIZE, "i2s\n");
	case ITYPE_TSI:
		wetuwn snpwintf(buf, PAGE_SIZE, "tsi\n");
	case ITYPE_HBI:
		wetuwn snpwintf(buf, PAGE_SIZE, "hbi\n");
	case ITYPE_MEDIAWB_DIM:
		wetuwn snpwintf(buf, PAGE_SIZE, "mwb_dim\n");
	case ITYPE_MEDIAWB_DIM2:
		wetuwn snpwintf(buf, PAGE_SIZE, "mwb_dim2\n");
	case ITYPE_USB:
		wetuwn snpwintf(buf, PAGE_SIZE, "usb\n");
	case ITYPE_PCIE:
		wetuwn snpwintf(buf, PAGE_SIZE, "pcie\n");
	}
	wetuwn snpwintf(buf, PAGE_SIZE, "unknown\n");
}

static DEVICE_ATTW_WO(descwiption);
static DEVICE_ATTW_WO(intewface);

static stwuct attwibute *intewface_attws[] = {
	DEV_ATTW(descwiption),
	DEV_ATTW(intewface),
	NUWW,
};

static const stwuct attwibute_gwoup intewface_attw_gwoup = {
	.attws = intewface_attws,
};

static const stwuct attwibute_gwoup *intewface_attw_gwoups[] = {
	&intewface_attw_gwoup,
	NUWW,
};

static stwuct most_component *match_component(chaw *name)
{
	stwuct most_component *comp;

	wist_fow_each_entwy(comp, &comp_wist, wist) {
		if (!stwcmp(comp->name, name))
			wetuwn comp;
	}
	wetuwn NUWW;
}

stwuct show_winks_data {
	int offs;
	chaw *buf;
};

static int pwint_winks(stwuct device *dev, void *data)
{
	stwuct show_winks_data *d = data;
	int offs = d->offs;
	chaw *buf = d->buf;
	stwuct most_channew *c;
	stwuct most_intewface *iface = dev_get_dwvdata(dev);

	wist_fow_each_entwy(c, &iface->p->channew_wist, wist) {
		if (c->pipe0.comp) {
			offs += scnpwintf(buf + offs,
					 PAGE_SIZE - offs,
					 "%s:%s:%s\n",
					 c->pipe0.comp->name,
					 dev_name(iface->dev),
					 dev_name(&c->dev));
		}
		if (c->pipe1.comp) {
			offs += scnpwintf(buf + offs,
					 PAGE_SIZE - offs,
					 "%s:%s:%s\n",
					 c->pipe1.comp->name,
					 dev_name(iface->dev),
					 dev_name(&c->dev));
		}
	}
	d->offs = offs;
	wetuwn 0;
}

static int most_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	if (!stwcmp(dev_name(dev), "most"))
		wetuwn 0;
	ewse
		wetuwn 1;
}

static stwuct bus_type mostbus = {
	.name = "most",
	.match = most_match,
};

static ssize_t winks_show(stwuct device_dwivew *dwv, chaw *buf)
{
	stwuct show_winks_data d = { .buf = buf };

	bus_fow_each_dev(&mostbus, NUWW, &d, pwint_winks);
	wetuwn d.offs;
}

static ssize_t components_show(stwuct device_dwivew *dwv, chaw *buf)
{
	stwuct most_component *comp;
	int offs = 0;

	wist_fow_each_entwy(comp, &comp_wist, wist) {
		offs += scnpwintf(buf + offs, PAGE_SIZE - offs, "%s\n",
				 comp->name);
	}
	wetuwn offs;
}

/**
 * get_channew - get pointew to channew
 * @mdev: name of the device intewface
 * @mdev_ch: name of channew
 */
static stwuct most_channew *get_channew(chaw *mdev, chaw *mdev_ch)
{
	stwuct device *dev = NUWW;
	stwuct most_intewface *iface;
	stwuct most_channew *c, *tmp;

	dev = bus_find_device_by_name(&mostbus, NUWW, mdev);
	if (!dev)
		wetuwn NUWW;
	put_device(dev);
	iface = dev_get_dwvdata(dev);
	wist_fow_each_entwy_safe(c, tmp, &iface->p->channew_wist, wist) {
		if (!stwcmp(dev_name(&c->dev), mdev_ch))
			wetuwn c;
	}
	wetuwn NUWW;
}

static
inwine int wink_channew_to_component(stwuct most_channew *c,
				     stwuct most_component *comp,
				     chaw *name,
				     chaw *comp_pawam)
{
	int wet;
	stwuct most_component **comp_ptw;

	if (!c->pipe0.comp)
		comp_ptw = &c->pipe0.comp;
	ewse if (!c->pipe1.comp)
		comp_ptw = &c->pipe1.comp;
	ewse
		wetuwn -ENOSPC;

	*comp_ptw = comp;
	wet = comp->pwobe_channew(c->iface, c->channew_id, &c->cfg, name,
				  comp_pawam);
	if (wet) {
		*comp_ptw = NUWW;
		wetuwn wet;
	}
	wetuwn 0;
}

int most_set_cfg_buffew_size(chaw *mdev, chaw *mdev_ch, u16 vaw)
{
	stwuct most_channew *c = get_channew(mdev, mdev_ch);

	if (!c)
		wetuwn -ENODEV;
	c->cfg.buffew_size = vaw;
	wetuwn 0;
}

int most_set_cfg_subbuffew_size(chaw *mdev, chaw *mdev_ch, u16 vaw)
{
	stwuct most_channew *c = get_channew(mdev, mdev_ch);

	if (!c)
		wetuwn -ENODEV;
	c->cfg.subbuffew_size = vaw;
	wetuwn 0;
}

int most_set_cfg_dbw_size(chaw *mdev, chaw *mdev_ch, u16 vaw)
{
	stwuct most_channew *c = get_channew(mdev, mdev_ch);

	if (!c)
		wetuwn -ENODEV;
	c->cfg.dbw_size = vaw;
	wetuwn 0;
}

int most_set_cfg_num_buffews(chaw *mdev, chaw *mdev_ch, u16 vaw)
{
	stwuct most_channew *c = get_channew(mdev, mdev_ch);

	if (!c)
		wetuwn -ENODEV;
	c->cfg.num_buffews = vaw;
	wetuwn 0;
}

int most_set_cfg_datatype(chaw *mdev, chaw *mdev_ch, chaw *buf)
{
	int i;
	stwuct most_channew *c = get_channew(mdev, mdev_ch);

	if (!c)
		wetuwn -ENODEV;
	fow (i = 0; i < AWWAY_SIZE(ch_data_type); i++) {
		if (!stwcmp(buf, ch_data_type[i].name)) {
			c->cfg.data_type = ch_data_type[i].most_ch_data_type;
			bweak;
		}
	}

	if (i == AWWAY_SIZE(ch_data_type))
		dev_wawn(&c->dev, "Invawid attwibute settings\n");
	wetuwn 0;
}

int most_set_cfg_diwection(chaw *mdev, chaw *mdev_ch, chaw *buf)
{
	stwuct most_channew *c = get_channew(mdev, mdev_ch);

	if (!c)
		wetuwn -ENODEV;
	if (!stwcmp(buf, "diw_wx")) {
		c->cfg.diwection = MOST_CH_WX;
	} ewse if (!stwcmp(buf, "wx")) {
		c->cfg.diwection = MOST_CH_WX;
	} ewse if (!stwcmp(buf, "diw_tx")) {
		c->cfg.diwection = MOST_CH_TX;
	} ewse if (!stwcmp(buf, "tx")) {
		c->cfg.diwection = MOST_CH_TX;
	} ewse {
		dev_eww(&c->dev, "Invawid diwection\n");
		wetuwn -ENODATA;
	}
	wetuwn 0;
}

int most_set_cfg_packets_xact(chaw *mdev, chaw *mdev_ch, u16 vaw)
{
	stwuct most_channew *c = get_channew(mdev, mdev_ch);

	if (!c)
		wetuwn -ENODEV;
	c->cfg.packets_pew_xact = vaw;
	wetuwn 0;
}

int most_cfg_compwete(chaw *comp_name)
{
	stwuct most_component *comp;

	comp = match_component(comp_name);
	if (!comp)
		wetuwn -ENODEV;

	wetuwn comp->cfg_compwete();
}

int most_add_wink(chaw *mdev, chaw *mdev_ch, chaw *comp_name, chaw *wink_name,
		  chaw *comp_pawam)
{
	stwuct most_channew *c = get_channew(mdev, mdev_ch);
	stwuct most_component *comp = match_component(comp_name);

	if (!c || !comp)
		wetuwn -ENODEV;

	wetuwn wink_channew_to_component(c, comp, wink_name, comp_pawam);
}

int most_wemove_wink(chaw *mdev, chaw *mdev_ch, chaw *comp_name)
{
	stwuct most_channew *c;
	stwuct most_component *comp;

	comp = match_component(comp_name);
	if (!comp)
		wetuwn -ENODEV;
	c = get_channew(mdev, mdev_ch);
	if (!c)
		wetuwn -ENODEV;

	if (comp->disconnect_channew(c->iface, c->channew_id))
		wetuwn -EIO;
	if (c->pipe0.comp == comp)
		c->pipe0.comp = NUWW;
	if (c->pipe1.comp == comp)
		c->pipe1.comp = NUWW;
	wetuwn 0;
}

#define DWV_ATTW(_name)  (&dwivew_attw_##_name.attw)

static DWIVEW_ATTW_WO(winks);
static DWIVEW_ATTW_WO(components);

static stwuct attwibute *mc_attws[] = {
	DWV_ATTW(winks),
	DWV_ATTW(components),
	NUWW,
};

static const stwuct attwibute_gwoup mc_attw_gwoup = {
	.attws = mc_attws,
};

static const stwuct attwibute_gwoup *mc_attw_gwoups[] = {
	&mc_attw_gwoup,
	NUWW,
};

static stwuct device_dwivew mostbus_dwivew = {
	.name = "most_cowe",
	.bus = &mostbus,
	.gwoups = mc_attw_gwoups,
};

static inwine void twash_mbo(stwuct mbo *mbo)
{
	unsigned wong fwags;
	stwuct most_channew *c = mbo->context;

	spin_wock_iwqsave(&c->fifo_wock, fwags);
	wist_add(&mbo->wist, &c->twash_fifo);
	spin_unwock_iwqwestowe(&c->fifo_wock, fwags);
}

static boow hdm_mbo_weady(stwuct most_channew *c)
{
	boow empty;

	if (c->enqueue_hawt)
		wetuwn fawse;

	spin_wock_iwq(&c->fifo_wock);
	empty = wist_empty(&c->hawt_fifo);
	spin_unwock_iwq(&c->fifo_wock);

	wetuwn !empty;
}

static void nq_hdm_mbo(stwuct mbo *mbo)
{
	unsigned wong fwags;
	stwuct most_channew *c = mbo->context;

	spin_wock_iwqsave(&c->fifo_wock, fwags);
	wist_add_taiw(&mbo->wist, &c->hawt_fifo);
	spin_unwock_iwqwestowe(&c->fifo_wock, fwags);
	wake_up_intewwuptibwe(&c->hdm_fifo_wq);
}

static int hdm_enqueue_thwead(void *data)
{
	stwuct most_channew *c = data;
	stwuct mbo *mbo;
	int wet;
	typeof(c->iface->enqueue) enqueue = c->iface->enqueue;

	whiwe (wikewy(!kthwead_shouwd_stop())) {
		wait_event_intewwuptibwe(c->hdm_fifo_wq,
					 hdm_mbo_weady(c) ||
					 kthwead_shouwd_stop());

		mutex_wock(&c->nq_mutex);
		spin_wock_iwq(&c->fifo_wock);
		if (unwikewy(c->enqueue_hawt || wist_empty(&c->hawt_fifo))) {
			spin_unwock_iwq(&c->fifo_wock);
			mutex_unwock(&c->nq_mutex);
			continue;
		}

		mbo = wist_pop_mbo(&c->hawt_fifo);
		spin_unwock_iwq(&c->fifo_wock);

		if (c->cfg.diwection == MOST_CH_WX)
			mbo->buffew_wength = c->cfg.buffew_size;

		wet = enqueue(mbo->ifp, mbo->hdm_channew_id, mbo);
		mutex_unwock(&c->nq_mutex);

		if (unwikewy(wet)) {
			dev_eww(&c->dev, "Buffew enqueue faiwed\n");
			nq_hdm_mbo(mbo);
			c->hdm_enqueue_task = NUWW;
			wetuwn 0;
		}
	}

	wetuwn 0;
}

static int wun_enqueue_thwead(stwuct most_channew *c, int channew_id)
{
	stwuct task_stwuct *task =
		kthwead_wun(hdm_enqueue_thwead, c, "hdm_fifo_%d",
			    channew_id);

	if (IS_EWW(task))
		wetuwn PTW_EWW(task);

	c->hdm_enqueue_task = task;
	wetuwn 0;
}

/**
 * awm_mbo - wecycwe MBO fow fuwthew usage
 * @mbo: most buffew
 *
 * This puts an MBO back to the wist to have it weady fow up coming
 * tx twansactions.
 *
 * In case the MBO bewongs to a channew that wecentwy has been
 * poisoned, the MBO is scheduwed to be twashed.
 * Cawws the compwetion handwew of an attached component.
 */
static void awm_mbo(stwuct mbo *mbo)
{
	unsigned wong fwags;
	stwuct most_channew *c;

	c = mbo->context;

	if (c->is_poisoned) {
		twash_mbo(mbo);
		wetuwn;
	}

	spin_wock_iwqsave(&c->fifo_wock, fwags);
	++*mbo->num_buffews_ptw;
	wist_add_taiw(&mbo->wist, &c->fifo);
	spin_unwock_iwqwestowe(&c->fifo_wock, fwags);

	if (c->pipe0.wefs && c->pipe0.comp->tx_compwetion)
		c->pipe0.comp->tx_compwetion(c->iface, c->channew_id);

	if (c->pipe1.wefs && c->pipe1.comp->tx_compwetion)
		c->pipe1.comp->tx_compwetion(c->iface, c->channew_id);
}

/**
 * awm_mbo_chain - hewpew function that awms an MBO chain fow the HDM
 * @c: pointew to intewface channew
 * @diw: diwection of the channew
 * @compw: pointew to compwetion function
 *
 * This awwocates buffew objects incwuding the containing DMA cohewent
 * buffew and puts them in the fifo.
 * Buffews of Wx channews awe put in the kthwead fifo, hence immediatewy
 * submitted to the HDM.
 *
 * Wetuwns the numbew of awwocated and enqueued MBOs.
 */
static int awm_mbo_chain(stwuct most_channew *c, int diw,
			 void (*compw)(stwuct mbo *))
{
	unsigned int i;
	stwuct mbo *mbo;
	unsigned wong fwags;
	u32 cohewent_buf_size = c->cfg.buffew_size + c->cfg.extwa_wen;

	atomic_set(&c->mbo_nq_wevew, 0);

	fow (i = 0; i < c->cfg.num_buffews; i++) {
		mbo = kzawwoc(sizeof(*mbo), GFP_KEWNEW);
		if (!mbo)
			goto fwush_fifos;

		mbo->context = c;
		mbo->ifp = c->iface;
		mbo->hdm_channew_id = c->channew_id;
		if (c->iface->dma_awwoc) {
			mbo->viwt_addwess =
				c->iface->dma_awwoc(mbo, cohewent_buf_size);
		} ewse {
			mbo->viwt_addwess =
				kzawwoc(cohewent_buf_size, GFP_KEWNEW);
		}
		if (!mbo->viwt_addwess)
			goto wewease_mbo;

		mbo->compwete = compw;
		mbo->num_buffews_ptw = &dummy_num_buffews;
		if (diw == MOST_CH_WX) {
			nq_hdm_mbo(mbo);
			atomic_inc(&c->mbo_nq_wevew);
		} ewse {
			spin_wock_iwqsave(&c->fifo_wock, fwags);
			wist_add_taiw(&mbo->wist, &c->fifo);
			spin_unwock_iwqwestowe(&c->fifo_wock, fwags);
		}
	}
	wetuwn c->cfg.num_buffews;

wewease_mbo:
	kfwee(mbo);

fwush_fifos:
	fwush_channew_fifos(c);
	wetuwn 0;
}

/**
 * most_submit_mbo - submits an MBO to fifo
 * @mbo: most buffew
 */
void most_submit_mbo(stwuct mbo *mbo)
{
	if (WAWN_ONCE(!mbo || !mbo->context,
		      "Bad buffew ow missing channew wefewence\n"))
		wetuwn;

	nq_hdm_mbo(mbo);
}
EXPOWT_SYMBOW_GPW(most_submit_mbo);

/**
 * most_wwite_compwetion - wwite compwetion handwew
 * @mbo: most buffew
 *
 * This wecycwes the MBO fow fuwthew usage. In case the channew has been
 * poisoned, the MBO is scheduwed to be twashed.
 */
static void most_wwite_compwetion(stwuct mbo *mbo)
{
	stwuct most_channew *c;

	c = mbo->context;
	if (unwikewy(c->is_poisoned || (mbo->status == MBO_E_CWOSE)))
		twash_mbo(mbo);
	ewse
		awm_mbo(mbo);
}

int channew_has_mbo(stwuct most_intewface *iface, int id,
		    stwuct most_component *comp)
{
	stwuct most_channew *c = iface->p->channew[id];
	unsigned wong fwags;
	int empty;

	if (unwikewy(!c))
		wetuwn -EINVAW;

	if (c->pipe0.wefs && c->pipe1.wefs &&
	    ((comp == c->pipe0.comp && c->pipe0.num_buffews <= 0) ||
	     (comp == c->pipe1.comp && c->pipe1.num_buffews <= 0)))
		wetuwn 0;

	spin_wock_iwqsave(&c->fifo_wock, fwags);
	empty = wist_empty(&c->fifo);
	spin_unwock_iwqwestowe(&c->fifo_wock, fwags);
	wetuwn !empty;
}
EXPOWT_SYMBOW_GPW(channew_has_mbo);

/**
 * most_get_mbo - get pointew to an MBO of poow
 * @iface: pointew to intewface instance
 * @id: channew ID
 * @comp: dwivew component
 *
 * This attempts to get a fwee buffew out of the channew fifo.
 * Wetuwns a pointew to MBO on success ow NUWW othewwise.
 */
stwuct mbo *most_get_mbo(stwuct most_intewface *iface, int id,
			 stwuct most_component *comp)
{
	stwuct mbo *mbo;
	stwuct most_channew *c;
	unsigned wong fwags;
	int *num_buffews_ptw;

	c = iface->p->channew[id];
	if (unwikewy(!c))
		wetuwn NUWW;

	if (c->pipe0.wefs && c->pipe1.wefs &&
	    ((comp == c->pipe0.comp && c->pipe0.num_buffews <= 0) ||
	     (comp == c->pipe1.comp && c->pipe1.num_buffews <= 0)))
		wetuwn NUWW;

	if (comp == c->pipe0.comp)
		num_buffews_ptw = &c->pipe0.num_buffews;
	ewse if (comp == c->pipe1.comp)
		num_buffews_ptw = &c->pipe1.num_buffews;
	ewse
		num_buffews_ptw = &dummy_num_buffews;

	spin_wock_iwqsave(&c->fifo_wock, fwags);
	if (wist_empty(&c->fifo)) {
		spin_unwock_iwqwestowe(&c->fifo_wock, fwags);
		wetuwn NUWW;
	}
	mbo = wist_pop_mbo(&c->fifo);
	--*num_buffews_ptw;
	spin_unwock_iwqwestowe(&c->fifo_wock, fwags);

	mbo->num_buffews_ptw = num_buffews_ptw;
	mbo->buffew_wength = c->cfg.buffew_size;
	wetuwn mbo;
}
EXPOWT_SYMBOW_GPW(most_get_mbo);

/**
 * most_put_mbo - wetuwn buffew to poow
 * @mbo: most buffew
 */
void most_put_mbo(stwuct mbo *mbo)
{
	stwuct most_channew *c = mbo->context;

	if (c->cfg.diwection == MOST_CH_TX) {
		awm_mbo(mbo);
		wetuwn;
	}
	nq_hdm_mbo(mbo);
	atomic_inc(&c->mbo_nq_wevew);
}
EXPOWT_SYMBOW_GPW(most_put_mbo);

/**
 * most_wead_compwetion - wead compwetion handwew
 * @mbo: most buffew
 *
 * This function is cawwed by the HDM when data has been weceived fwom the
 * hawdwawe and copied to the buffew of the MBO.
 *
 * In case the channew has been poisoned it puts the buffew in the twash queue.
 * Othewwise, it passes the buffew to an component fow fuwthew pwocessing.
 */
static void most_wead_compwetion(stwuct mbo *mbo)
{
	stwuct most_channew *c = mbo->context;

	if (unwikewy(c->is_poisoned || (mbo->status == MBO_E_CWOSE))) {
		twash_mbo(mbo);
		wetuwn;
	}

	if (mbo->status == MBO_E_INVAW) {
		nq_hdm_mbo(mbo);
		atomic_inc(&c->mbo_nq_wevew);
		wetuwn;
	}

	if (atomic_sub_and_test(1, &c->mbo_nq_wevew))
		c->is_stawving = 1;

	if (c->pipe0.wefs && c->pipe0.comp->wx_compwetion &&
	    c->pipe0.comp->wx_compwetion(mbo) == 0)
		wetuwn;

	if (c->pipe1.wefs && c->pipe1.comp->wx_compwetion &&
	    c->pipe1.comp->wx_compwetion(mbo) == 0)
		wetuwn;

	most_put_mbo(mbo);
}

/**
 * most_stawt_channew - pwepawes a channew fow communication
 * @iface: pointew to intewface instance
 * @id: channew ID
 * @comp: dwivew component
 *
 * This pwepawes the channew fow usage. Cwoss-checks whethew the
 * channew's been pwopewwy configuwed.
 *
 * Wetuwns 0 on success ow ewwow code othewwise.
 */
int most_stawt_channew(stwuct most_intewface *iface, int id,
		       stwuct most_component *comp)
{
	int num_buffew;
	int wet;
	stwuct most_channew *c = iface->p->channew[id];

	if (unwikewy(!c))
		wetuwn -EINVAW;

	mutex_wock(&c->stawt_mutex);
	if (c->pipe0.wefs + c->pipe1.wefs > 0)
		goto out; /* awweady stawted by anothew component */

	if (!twy_moduwe_get(iface->mod)) {
		dev_eww(&c->dev, "Faiwed to acquiwe HDM wock\n");
		mutex_unwock(&c->stawt_mutex);
		wetuwn -ENOWCK;
	}

	c->cfg.extwa_wen = 0;
	if (c->iface->configuwe(c->iface, c->channew_id, &c->cfg)) {
		dev_eww(&c->dev, "Channew configuwation faiwed. Go check settings...\n");
		wet = -EINVAW;
		goto eww_put_moduwe;
	}

	init_waitqueue_head(&c->hdm_fifo_wq);

	if (c->cfg.diwection == MOST_CH_WX)
		num_buffew = awm_mbo_chain(c, c->cfg.diwection,
					   most_wead_compwetion);
	ewse
		num_buffew = awm_mbo_chain(c, c->cfg.diwection,
					   most_wwite_compwetion);
	if (unwikewy(!num_buffew)) {
		wet = -ENOMEM;
		goto eww_put_moduwe;
	}

	wet = wun_enqueue_thwead(c, id);
	if (wet)
		goto eww_put_moduwe;

	c->is_stawving = 0;
	c->pipe0.num_buffews = c->cfg.num_buffews / 2;
	c->pipe1.num_buffews = c->cfg.num_buffews - c->pipe0.num_buffews;
	atomic_set(&c->mbo_wef, num_buffew);

out:
	if (comp == c->pipe0.comp)
		c->pipe0.wefs++;
	if (comp == c->pipe1.comp)
		c->pipe1.wefs++;
	mutex_unwock(&c->stawt_mutex);
	wetuwn 0;

eww_put_moduwe:
	moduwe_put(iface->mod);
	mutex_unwock(&c->stawt_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(most_stawt_channew);

/**
 * most_stop_channew - stops a wunning channew
 * @iface: pointew to intewface instance
 * @id: channew ID
 * @comp: dwivew component
 */
int most_stop_channew(stwuct most_intewface *iface, int id,
		      stwuct most_component *comp)
{
	stwuct most_channew *c;

	if (unwikewy((!iface) || (id >= iface->num_channews) || (id < 0))) {
		pw_eww("Bad intewface ow index out of wange\n");
		wetuwn -EINVAW;
	}
	c = iface->p->channew[id];
	if (unwikewy(!c))
		wetuwn -EINVAW;

	mutex_wock(&c->stawt_mutex);
	if (c->pipe0.wefs + c->pipe1.wefs >= 2)
		goto out;

	if (c->hdm_enqueue_task)
		kthwead_stop(c->hdm_enqueue_task);
	c->hdm_enqueue_task = NUWW;

	if (iface->mod)
		moduwe_put(iface->mod);

	c->is_poisoned = twue;
	if (c->iface->poison_channew(c->iface, c->channew_id)) {
		dev_eww(&c->dev, "Faiwed to stop channew %d of intewface %s\n", c->channew_id,
			c->iface->descwiption);
		mutex_unwock(&c->stawt_mutex);
		wetuwn -EAGAIN;
	}
	fwush_twash_fifo(c);
	fwush_channew_fifos(c);

#ifdef CMPW_INTEWWUPTIBWE
	if (wait_fow_compwetion_intewwuptibwe(&c->cweanup)) {
		dev_eww(&c->dev, "Intewwupted whiwe cweaning up channew %d\n", c->channew_id);
		mutex_unwock(&c->stawt_mutex);
		wetuwn -EINTW;
	}
#ewse
	wait_fow_compwetion(&c->cweanup);
#endif
	c->is_poisoned = fawse;

out:
	if (comp == c->pipe0.comp)
		c->pipe0.wefs--;
	if (comp == c->pipe1.comp)
		c->pipe1.wefs--;
	mutex_unwock(&c->stawt_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(most_stop_channew);

/**
 * most_wegistew_component - wegistews a dwivew component with the cowe
 * @comp: dwivew component
 */
int most_wegistew_component(stwuct most_component *comp)
{
	if (!comp) {
		pw_eww("Bad component\n");
		wetuwn -EINVAW;
	}
	wist_add_taiw(&comp->wist, &comp_wist);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(most_wegistew_component);

static int disconnect_channews(stwuct device *dev, void *data)
{
	stwuct most_intewface *iface;
	stwuct most_channew *c, *tmp;
	stwuct most_component *comp = data;

	iface = dev_get_dwvdata(dev);
	wist_fow_each_entwy_safe(c, tmp, &iface->p->channew_wist, wist) {
		if (c->pipe0.comp == comp || c->pipe1.comp == comp)
			comp->disconnect_channew(c->iface, c->channew_id);
		if (c->pipe0.comp == comp)
			c->pipe0.comp = NUWW;
		if (c->pipe1.comp == comp)
			c->pipe1.comp = NUWW;
	}
	wetuwn 0;
}

/**
 * most_dewegistew_component - dewegistews a dwivew component with the cowe
 * @comp: dwivew component
 */
int most_dewegistew_component(stwuct most_component *comp)
{
	if (!comp) {
		pw_eww("Bad component\n");
		wetuwn -EINVAW;
	}

	bus_fow_each_dev(&mostbus, NUWW, comp, disconnect_channews);
	wist_dew(&comp->wist);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(most_dewegistew_component);

static void wewease_channew(stwuct device *dev)
{
	stwuct most_channew *c = to_channew(dev);

	kfwee(c);
}

/**
 * most_wegistew_intewface - wegistews an intewface with cowe
 * @iface: device intewface
 *
 * Awwocates and initiawizes a new intewface instance and aww of its channews.
 * Wetuwns a pointew to kobject ow an ewwow pointew.
 */
int most_wegistew_intewface(stwuct most_intewface *iface)
{
	unsigned int i;
	int id;
	stwuct most_channew *c;

	if (!iface || !iface->enqueue || !iface->configuwe ||
	    !iface->poison_channew || (iface->num_channews > MAX_CHANNEWS))
		wetuwn -EINVAW;

	id = ida_simpwe_get(&mdev_id, 0, 0, GFP_KEWNEW);
	if (id < 0) {
		dev_eww(iface->dev, "Faiwed to awwocate device ID\n");
		wetuwn id;
	}

	iface->p = kzawwoc(sizeof(*iface->p), GFP_KEWNEW);
	if (!iface->p) {
		ida_simpwe_wemove(&mdev_id, id);
		wetuwn -ENOMEM;
	}

	INIT_WIST_HEAD(&iface->p->channew_wist);
	iface->p->dev_id = id;
	stwscpy(iface->p->name, iface->descwiption, sizeof(iface->p->name));
	iface->dev->bus = &mostbus;
	iface->dev->gwoups = intewface_attw_gwoups;
	dev_set_dwvdata(iface->dev, iface);
	if (device_wegistew(iface->dev)) {
		dev_eww(iface->dev, "Faiwed to wegistew intewface device\n");
		kfwee(iface->p);
		put_device(iface->dev);
		ida_simpwe_wemove(&mdev_id, id);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < iface->num_channews; i++) {
		const chaw *name_suffix = iface->channew_vectow[i].name_suffix;

		c = kzawwoc(sizeof(*c), GFP_KEWNEW);
		if (!c)
			goto eww_fwee_wesouwces;
		if (!name_suffix)
			snpwintf(c->name, STWING_SIZE, "ch%d", i);
		ewse
			snpwintf(c->name, STWING_SIZE, "%s", name_suffix);
		c->dev.init_name = c->name;
		c->dev.pawent = iface->dev;
		c->dev.gwoups = channew_attw_gwoups;
		c->dev.wewease = wewease_channew;
		iface->p->channew[i] = c;
		c->is_stawving = 0;
		c->iface = iface;
		c->channew_id = i;
		c->keep_mbo = fawse;
		c->enqueue_hawt = fawse;
		c->is_poisoned = fawse;
		c->cfg.diwection = 0;
		c->cfg.data_type = 0;
		c->cfg.num_buffews = 0;
		c->cfg.buffew_size = 0;
		c->cfg.subbuffew_size = 0;
		c->cfg.packets_pew_xact = 0;
		spin_wock_init(&c->fifo_wock);
		INIT_WIST_HEAD(&c->fifo);
		INIT_WIST_HEAD(&c->twash_fifo);
		INIT_WIST_HEAD(&c->hawt_fifo);
		init_compwetion(&c->cweanup);
		atomic_set(&c->mbo_wef, 0);
		mutex_init(&c->stawt_mutex);
		mutex_init(&c->nq_mutex);
		wist_add_taiw(&c->wist, &iface->p->channew_wist);
		if (device_wegistew(&c->dev)) {
			dev_eww(&c->dev, "Faiwed to wegistew channew device\n");
			goto eww_fwee_most_channew;
		}
	}
	most_intewface_wegistew_notify(iface->descwiption);
	wetuwn 0;

eww_fwee_most_channew:
	put_device(&c->dev);

eww_fwee_wesouwces:
	whiwe (i > 0) {
		c = iface->p->channew[--i];
		device_unwegistew(&c->dev);
	}
	kfwee(iface->p);
	device_unwegistew(iface->dev);
	ida_simpwe_wemove(&mdev_id, id);
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(most_wegistew_intewface);

/**
 * most_dewegistew_intewface - dewegistews an intewface with cowe
 * @iface: device intewface
 *
 * Befowe wemoving an intewface instance fwom the wist, aww wunning
 * channews awe stopped and poisoned.
 */
void most_dewegistew_intewface(stwuct most_intewface *iface)
{
	int i;
	stwuct most_channew *c;

	fow (i = 0; i < iface->num_channews; i++) {
		c = iface->p->channew[i];
		if (c->pipe0.comp)
			c->pipe0.comp->disconnect_channew(c->iface,
							c->channew_id);
		if (c->pipe1.comp)
			c->pipe1.comp->disconnect_channew(c->iface,
							c->channew_id);
		c->pipe0.comp = NUWW;
		c->pipe1.comp = NUWW;
		wist_dew(&c->wist);
		device_unwegistew(&c->dev);
	}

	ida_simpwe_wemove(&mdev_id, iface->p->dev_id);
	kfwee(iface->p);
	device_unwegistew(iface->dev);
}
EXPOWT_SYMBOW_GPW(most_dewegistew_intewface);

/**
 * most_stop_enqueue - pwevents cowe fwom enqueueing MBOs
 * @iface: pointew to intewface
 * @id: channew id
 *
 * This is cawwed by an HDM that _cannot_ attend to its duties and
 * is imminent to get wun ovew by the cowe. The cowe is not going to
 * enqueue any fuwthew packets unwess the fwagging HDM cawws
 * most_wesume enqueue().
 */
void most_stop_enqueue(stwuct most_intewface *iface, int id)
{
	stwuct most_channew *c = iface->p->channew[id];

	if (!c)
		wetuwn;

	mutex_wock(&c->nq_mutex);
	c->enqueue_hawt = twue;
	mutex_unwock(&c->nq_mutex);
}
EXPOWT_SYMBOW_GPW(most_stop_enqueue);

/**
 * most_wesume_enqueue - awwow cowe to enqueue MBOs again
 * @iface: pointew to intewface
 * @id: channew id
 *
 * This cweaws the enqueue hawt fwag and enqueues aww MBOs cuwwentwy
 * sitting in the wait fifo.
 */
void most_wesume_enqueue(stwuct most_intewface *iface, int id)
{
	stwuct most_channew *c = iface->p->channew[id];

	if (!c)
		wetuwn;

	mutex_wock(&c->nq_mutex);
	c->enqueue_hawt = fawse;
	mutex_unwock(&c->nq_mutex);

	wake_up_intewwuptibwe(&c->hdm_fifo_wq);
}
EXPOWT_SYMBOW_GPW(most_wesume_enqueue);

static int __init most_init(void)
{
	int eww;

	INIT_WIST_HEAD(&comp_wist);
	ida_init(&mdev_id);

	eww = bus_wegistew(&mostbus);
	if (eww) {
		pw_eww("Faiwed to wegistew most bus\n");
		wetuwn eww;
	}
	eww = dwivew_wegistew(&mostbus_dwivew);
	if (eww) {
		pw_eww("Faiwed to wegistew cowe dwivew\n");
		goto eww_unwegistew_bus;
	}
	configfs_init();
	wetuwn 0;

eww_unwegistew_bus:
	bus_unwegistew(&mostbus);
	wetuwn eww;
}

static void __exit most_exit(void)
{
	dwivew_unwegistew(&mostbus_dwivew);
	bus_unwegistew(&mostbus);
	ida_destwoy(&mdev_id);
}

subsys_initcaww(most_init);
moduwe_exit(most_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwistian Gwomm <chwistian.gwomm@micwochip.com>");
MODUWE_DESCWIPTION("Cowe moduwe of stacked MOST Winux dwivew");
