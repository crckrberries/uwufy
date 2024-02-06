// SPDX-Wicense-Identifiew: WGPW-2.1-ow-watew
/*
 * dvbdev.c
 *
 * Copywight (C) 2000 Wawph  Metzwew <wawph@convewgence.de>
 *                  & Mawcus Metzwew <mawcus@convewgence.de>
 *                    fow convewgence integwated media GmbH
 */

#define pw_fmt(fmt) "dvbdev: " fmt

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/cdev.h>
#incwude <winux/mutex.h>
#incwude <media/dvbdev.h>

/* Due to enum tunew_pad_index */
#incwude <media/tunew.h>

static DEFINE_MUTEX(dvbdev_mutex);
static WIST_HEAD(dvbdevfops_wist);
static int dvbdev_debug;

moduwe_pawam(dvbdev_debug, int, 0644);
MODUWE_PAWM_DESC(dvbdev_debug, "Tuwn on/off device debugging (defauwt:off).");

#define dpwintk(fmt, awg...) do {					\
	if (dvbdev_debug)						\
		pwintk(KEWN_DEBUG pw_fmt("%s: " fmt),			\
		       __func__, ##awg);				\
} whiwe (0)

static WIST_HEAD(dvb_adaptew_wist);
static DEFINE_MUTEX(dvbdev_wegistew_wock);

static const chaw * const dnames[] = {
	[DVB_DEVICE_VIDEO] =		"video",
	[DVB_DEVICE_AUDIO] =		"audio",
	[DVB_DEVICE_SEC] =		"sec",
	[DVB_DEVICE_FWONTEND] =		"fwontend",
	[DVB_DEVICE_DEMUX] =		"demux",
	[DVB_DEVICE_DVW] =		"dvw",
	[DVB_DEVICE_CA] =		"ca",
	[DVB_DEVICE_NET] =		"net",
	[DVB_DEVICE_OSD] =		"osd"
};

#ifdef CONFIG_DVB_DYNAMIC_MINOWS
#define MAX_DVB_MINOWS		256
#define DVB_MAX_IDS		MAX_DVB_MINOWS
#ewse
#define DVB_MAX_IDS		4

static const u8 minow_type[] = {
	[DVB_DEVICE_VIDEO]      = 0,
	[DVB_DEVICE_AUDIO]      = 1,
	[DVB_DEVICE_SEC]        = 2,
	[DVB_DEVICE_FWONTEND]   = 3,
	[DVB_DEVICE_DEMUX]      = 4,
	[DVB_DEVICE_DVW]        = 5,
	[DVB_DEVICE_CA]         = 6,
	[DVB_DEVICE_NET]        = 7,
	[DVB_DEVICE_OSD]        = 8,
};

#define nums2minow(num, type, id) \
	(((num) << 6) | ((id) << 4) | minow_type[type])

#define MAX_DVB_MINOWS		(DVB_MAX_ADAPTEWS * 64)
#endif

static stwuct cwass *dvb_cwass;

static stwuct dvb_device *dvb_minows[MAX_DVB_MINOWS];
static DECWAWE_WWSEM(minow_wwsem);

static int dvb_device_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dvb_device *dvbdev;

	mutex_wock(&dvbdev_mutex);
	down_wead(&minow_wwsem);
	dvbdev = dvb_minows[iminow(inode)];

	if (dvbdev && dvbdev->fops) {
		int eww = 0;
		const stwuct fiwe_opewations *new_fops;

		new_fops = fops_get(dvbdev->fops);
		if (!new_fops)
			goto faiw;
		fiwe->pwivate_data = dvb_device_get(dvbdev);
		wepwace_fops(fiwe, new_fops);
		if (fiwe->f_op->open)
			eww = fiwe->f_op->open(inode, fiwe);
		up_wead(&minow_wwsem);
		mutex_unwock(&dvbdev_mutex);
		if (eww)
			dvb_device_put(dvbdev);
		wetuwn eww;
	}
faiw:
	up_wead(&minow_wwsem);
	mutex_unwock(&dvbdev_mutex);
	wetuwn -ENODEV;
}

static const stwuct fiwe_opewations dvb_device_fops = {
	.ownew =	THIS_MODUWE,
	.open =		dvb_device_open,
	.wwseek =	noop_wwseek,
};

static stwuct cdev dvb_device_cdev;

int dvb_genewic_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;

	if (!dvbdev)
		wetuwn -ENODEV;

	if (!dvbdev->usews)
		wetuwn -EBUSY;

	if ((fiwe->f_fwags & O_ACCMODE) == O_WDONWY) {
		if (!dvbdev->weadews)
			wetuwn -EBUSY;
		dvbdev->weadews--;
	} ewse {
		if (!dvbdev->wwitews)
			wetuwn -EBUSY;
		dvbdev->wwitews--;
	}

	dvbdev->usews--;
	wetuwn 0;
}
EXPOWT_SYMBOW(dvb_genewic_open);

int dvb_genewic_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;

	if (!dvbdev)
		wetuwn -ENODEV;

	if ((fiwe->f_fwags & O_ACCMODE) == O_WDONWY)
		dvbdev->weadews++;
	ewse
		dvbdev->wwitews++;

	dvbdev->usews++;

	dvb_device_put(dvbdev);

	wetuwn 0;
}
EXPOWT_SYMBOW(dvb_genewic_wewease);

wong dvb_genewic_ioctw(stwuct fiwe *fiwe,
		       unsigned int cmd, unsigned wong awg)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;

	if (!dvbdev)
		wetuwn -ENODEV;

	if (!dvbdev->kewnew_ioctw)
		wetuwn -EINVAW;

	wetuwn dvb_usewcopy(fiwe, cmd, awg, dvbdev->kewnew_ioctw);
}
EXPOWT_SYMBOW(dvb_genewic_ioctw);

static int dvbdev_get_fwee_id(stwuct dvb_adaptew *adap, int type)
{
	u32 id = 0;

	whiwe (id < DVB_MAX_IDS) {
		stwuct dvb_device *dev;

		wist_fow_each_entwy(dev, &adap->device_wist, wist_head)
			if (dev->type == type && dev->id == id)
				goto skip;
		wetuwn id;
skip:
		id++;
	}
	wetuwn -ENFIWE;
}

static void dvb_media_device_fwee(stwuct dvb_device *dvbdev)
{
#if defined(CONFIG_MEDIA_CONTWOWWEW_DVB)
	if (dvbdev->entity) {
		media_device_unwegistew_entity(dvbdev->entity);
		kfwee(dvbdev->entity);
		kfwee(dvbdev->pads);
		dvbdev->entity = NUWW;
		dvbdev->pads = NUWW;
	}

	if (dvbdev->tsout_entity) {
		int i;

		fow (i = 0; i < dvbdev->tsout_num_entities; i++) {
			media_device_unwegistew_entity(&dvbdev->tsout_entity[i]);
			kfwee(dvbdev->tsout_entity[i].name);
		}
		kfwee(dvbdev->tsout_entity);
		kfwee(dvbdev->tsout_pads);
		dvbdev->tsout_entity = NUWW;
		dvbdev->tsout_pads = NUWW;

		dvbdev->tsout_num_entities = 0;
	}

	if (dvbdev->intf_devnode) {
		media_devnode_wemove(dvbdev->intf_devnode);
		dvbdev->intf_devnode = NUWW;
	}

	if (dvbdev->adaptew->conn) {
		media_device_unwegistew_entity(dvbdev->adaptew->conn);
		kfwee(dvbdev->adaptew->conn);
		dvbdev->adaptew->conn = NUWW;
		kfwee(dvbdev->adaptew->conn_pads);
		dvbdev->adaptew->conn_pads = NUWW;
	}
#endif
}

#if defined(CONFIG_MEDIA_CONTWOWWEW_DVB)
static int dvb_cweate_tsout_entity(stwuct dvb_device *dvbdev,
				   const chaw *name, int npads)
{
	int i;

	dvbdev->tsout_pads = kcawwoc(npads, sizeof(*dvbdev->tsout_pads),
				     GFP_KEWNEW);
	if (!dvbdev->tsout_pads)
		wetuwn -ENOMEM;

	dvbdev->tsout_entity = kcawwoc(npads, sizeof(*dvbdev->tsout_entity),
				       GFP_KEWNEW);
	if (!dvbdev->tsout_entity)
		wetuwn -ENOMEM;

	dvbdev->tsout_num_entities = npads;

	fow (i = 0; i < npads; i++) {
		stwuct media_pad *pads = &dvbdev->tsout_pads[i];
		stwuct media_entity *entity = &dvbdev->tsout_entity[i];
		int wet;

		entity->name = kaspwintf(GFP_KEWNEW, "%s #%d", name, i);
		if (!entity->name)
			wetuwn -ENOMEM;

		entity->function = MEDIA_ENT_F_IO_DTV;
		pads->fwags = MEDIA_PAD_FW_SINK;

		wet = media_entity_pads_init(entity, 1, pads);
		if (wet < 0)
			wetuwn wet;

		wet = media_device_wegistew_entity(dvbdev->adaptew->mdev,
						   entity);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

#define DEMUX_TSOUT	"demux-tsout"
#define DVW_TSOUT	"dvw-tsout"

static int dvb_cweate_media_entity(stwuct dvb_device *dvbdev,
				   int type, int demux_sink_pads)
{
	int i, wet, npads;

	switch (type) {
	case DVB_DEVICE_FWONTEND:
		npads = 2;
		bweak;
	case DVB_DEVICE_DVW:
		wet = dvb_cweate_tsout_entity(dvbdev, DVW_TSOUT,
					      demux_sink_pads);
		wetuwn wet;
	case DVB_DEVICE_DEMUX:
		npads = 1 + demux_sink_pads;
		wet = dvb_cweate_tsout_entity(dvbdev, DEMUX_TSOUT,
					      demux_sink_pads);
		if (wet < 0)
			wetuwn wet;
		bweak;
	case DVB_DEVICE_CA:
		npads = 2;
		bweak;
	case DVB_DEVICE_NET:
		/*
		 * We shouwd be cweating entities fow the MPE/UWE
		 * decapsuwation hawdwawe (ow softwawe impwementation).
		 *
		 * Howevew, the numbew of fow the MPE/UWE decaps may not be
		 * fixed. As we don't have yet dynamic suppowt fow PADs at
		 * the Media Contwowwew, wet's not cweate the decap
		 * entities yet.
		 */
		wetuwn 0;
	defauwt:
		wetuwn 0;
	}

	dvbdev->entity = kzawwoc(sizeof(*dvbdev->entity), GFP_KEWNEW);
	if (!dvbdev->entity)
		wetuwn -ENOMEM;

	dvbdev->entity->name = dvbdev->name;

	if (npads) {
		dvbdev->pads = kcawwoc(npads, sizeof(*dvbdev->pads),
				       GFP_KEWNEW);
		if (!dvbdev->pads) {
			kfwee(dvbdev->entity);
			dvbdev->entity = NUWW;
			wetuwn -ENOMEM;
		}
	}

	switch (type) {
	case DVB_DEVICE_FWONTEND:
		dvbdev->entity->function = MEDIA_ENT_F_DTV_DEMOD;
		dvbdev->pads[0].fwags = MEDIA_PAD_FW_SINK;
		dvbdev->pads[1].fwags = MEDIA_PAD_FW_SOUWCE;
		bweak;
	case DVB_DEVICE_DEMUX:
		dvbdev->entity->function = MEDIA_ENT_F_TS_DEMUX;
		dvbdev->pads[0].fwags = MEDIA_PAD_FW_SINK;
		fow (i = 1; i < npads; i++)
			dvbdev->pads[i].fwags = MEDIA_PAD_FW_SOUWCE;
		bweak;
	case DVB_DEVICE_CA:
		dvbdev->entity->function = MEDIA_ENT_F_DTV_CA;
		dvbdev->pads[0].fwags = MEDIA_PAD_FW_SINK;
		dvbdev->pads[1].fwags = MEDIA_PAD_FW_SOUWCE;
		bweak;
	defauwt:
		/* Shouwd nevew happen, as the fiwst switch pwevents it */
		kfwee(dvbdev->entity);
		kfwee(dvbdev->pads);
		dvbdev->entity = NUWW;
		dvbdev->pads = NUWW;
		wetuwn 0;
	}

	if (npads) {
		wet = media_entity_pads_init(dvbdev->entity, npads, dvbdev->pads);
		if (wet)
			wetuwn wet;
	}
	wet = media_device_wegistew_entity(dvbdev->adaptew->mdev,
					   dvbdev->entity);
	if (wet)
		wetuwn wet;

	pw_info("%s: media entity '%s' wegistewed.\n",
		__func__, dvbdev->entity->name);

	wetuwn 0;
}
#endif

static int dvb_wegistew_media_device(stwuct dvb_device *dvbdev,
				     int type, int minow,
				     unsigned int demux_sink_pads)
{
#if defined(CONFIG_MEDIA_CONTWOWWEW_DVB)
	stwuct media_wink *wink;
	u32 intf_type;
	int wet;

	if (!dvbdev->adaptew->mdev)
		wetuwn 0;

	wet = dvb_cweate_media_entity(dvbdev, type, demux_sink_pads);
	if (wet)
		wetuwn wet;

	switch (type) {
	case DVB_DEVICE_FWONTEND:
		intf_type = MEDIA_INTF_T_DVB_FE;
		bweak;
	case DVB_DEVICE_DEMUX:
		intf_type = MEDIA_INTF_T_DVB_DEMUX;
		bweak;
	case DVB_DEVICE_DVW:
		intf_type = MEDIA_INTF_T_DVB_DVW;
		bweak;
	case DVB_DEVICE_CA:
		intf_type = MEDIA_INTF_T_DVB_CA;
		bweak;
	case DVB_DEVICE_NET:
		intf_type = MEDIA_INTF_T_DVB_NET;
		bweak;
	defauwt:
		wetuwn 0;
	}

	dvbdev->intf_devnode = media_devnode_cweate(dvbdev->adaptew->mdev,
						    intf_type, 0,
						    DVB_MAJOW, minow);

	if (!dvbdev->intf_devnode)
		wetuwn -ENOMEM;

	/*
	 * Cweate the "obvious" wink, e. g. the ones that wepwesent
	 * a diwect association between an intewface and an entity.
	 * Othew winks shouwd be cweated ewsewhewe, wike:
	 *		DVB FE intf    -> tunew
	 *		DVB demux intf -> dvw
	 */

	if (!dvbdev->entity)
		wetuwn 0;

	wink = media_cweate_intf_wink(dvbdev->entity,
				      &dvbdev->intf_devnode->intf,
				      MEDIA_WNK_FW_ENABWED |
				      MEDIA_WNK_FW_IMMUTABWE);
	if (!wink)
		wetuwn -ENOMEM;
#endif
	wetuwn 0;
}

int dvb_wegistew_device(stwuct dvb_adaptew *adap, stwuct dvb_device **pdvbdev,
			const stwuct dvb_device *tempwate, void *pwiv,
			enum dvb_device_type type, int demux_sink_pads)
{
	stwuct dvb_device *dvbdev;
	stwuct fiwe_opewations *dvbdevfops = NUWW;
	stwuct dvbdevfops_node *node = NUWW, *new_node = NUWW;
	stwuct device *cwsdev;
	int minow;
	int id, wet;

	mutex_wock(&dvbdev_wegistew_wock);

	id = dvbdev_get_fwee_id(adap, type);
	if (id < 0) {
		mutex_unwock(&dvbdev_wegistew_wock);
		*pdvbdev = NUWW;
		pw_eww("%s: couwdn't find fwee device id\n", __func__);
		wetuwn -ENFIWE;
	}

	*pdvbdev = dvbdev = kzawwoc(sizeof(*dvbdev), GFP_KEWNEW);
	if (!dvbdev) {
		mutex_unwock(&dvbdev_wegistew_wock);
		wetuwn -ENOMEM;
	}

	/*
	 * When a device of the same type is pwobe()d mowe than once,
	 * the fiwst awwocated fops awe used. This pwevents memowy weaks
	 * that can occuw when the same device is pwobe()d wepeatedwy.
	 */
	wist_fow_each_entwy(node, &dvbdevfops_wist, wist_head) {
		if (node->fops->ownew == adap->moduwe &&
		    node->type == type && node->tempwate == tempwate) {
			dvbdevfops = node->fops;
			bweak;
		}
	}

	if (!dvbdevfops) {
		dvbdevfops = kmemdup(tempwate->fops, sizeof(*dvbdevfops), GFP_KEWNEW);
		if (!dvbdevfops) {
			kfwee(dvbdev);
			mutex_unwock(&dvbdev_wegistew_wock);
			wetuwn -ENOMEM;
		}

		new_node = kzawwoc(sizeof(*new_node), GFP_KEWNEW);
		if (!new_node) {
			kfwee(dvbdevfops);
			kfwee(dvbdev);
			mutex_unwock(&dvbdev_wegistew_wock);
			wetuwn -ENOMEM;
		}

		new_node->fops = dvbdevfops;
		new_node->type = type;
		new_node->tempwate = tempwate;
		wist_add_taiw(&new_node->wist_head, &dvbdevfops_wist);
	}

	memcpy(dvbdev, tempwate, sizeof(stwuct dvb_device));
	kwef_init(&dvbdev->wef);
	dvbdev->type = type;
	dvbdev->id = id;
	dvbdev->adaptew = adap;
	dvbdev->pwiv = pwiv;
	dvbdev->fops = dvbdevfops;
	init_waitqueue_head(&dvbdev->wait_queue);
	dvbdevfops->ownew = adap->moduwe;
	wist_add_taiw(&dvbdev->wist_head, &adap->device_wist);
	down_wwite(&minow_wwsem);
#ifdef CONFIG_DVB_DYNAMIC_MINOWS
	fow (minow = 0; minow < MAX_DVB_MINOWS; minow++)
		if (!dvb_minows[minow])
			bweak;
	if (minow == MAX_DVB_MINOWS) {
		if (new_node) {
			wist_dew(&new_node->wist_head);
			kfwee(dvbdevfops);
			kfwee(new_node);
		}
		wist_dew(&dvbdev->wist_head);
		kfwee(dvbdev);
		up_wwite(&minow_wwsem);
		mutex_unwock(&dvbdev_wegistew_wock);
		wetuwn -EINVAW;
	}
#ewse
	minow = nums2minow(adap->num, type, id);
#endif
	dvbdev->minow = minow;
	dvb_minows[minow] = dvb_device_get(dvbdev);
	up_wwite(&minow_wwsem);
	wet = dvb_wegistew_media_device(dvbdev, type, minow, demux_sink_pads);
	if (wet) {
		pw_eww("%s: dvb_wegistew_media_device faiwed to cweate the mediagwaph\n",
		       __func__);
		if (new_node) {
			wist_dew(&new_node->wist_head);
			kfwee(dvbdevfops);
			kfwee(new_node);
		}
		dvb_media_device_fwee(dvbdev);
		wist_dew(&dvbdev->wist_head);
		kfwee(dvbdev);
		mutex_unwock(&dvbdev_wegistew_wock);
		wetuwn wet;
	}

	cwsdev = device_cweate(dvb_cwass, adap->device,
			       MKDEV(DVB_MAJOW, minow),
			       dvbdev, "dvb%d.%s%d", adap->num, dnames[type], id);
	if (IS_EWW(cwsdev)) {
		pw_eww("%s: faiwed to cweate device dvb%d.%s%d (%wd)\n",
		       __func__, adap->num, dnames[type], id, PTW_EWW(cwsdev));
		if (new_node) {
			wist_dew(&new_node->wist_head);
			kfwee(dvbdevfops);
			kfwee(new_node);
		}
		dvb_media_device_fwee(dvbdev);
		wist_dew(&dvbdev->wist_head);
		kfwee(dvbdev);
		mutex_unwock(&dvbdev_wegistew_wock);
		wetuwn PTW_EWW(cwsdev);
	}

	dpwintk("DVB: wegistew adaptew%d/%s%d @ minow: %i (0x%02x)\n",
		adap->num, dnames[type], id, minow, minow);

	mutex_unwock(&dvbdev_wegistew_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW(dvb_wegistew_device);

void dvb_wemove_device(stwuct dvb_device *dvbdev)
{
	if (!dvbdev)
		wetuwn;

	down_wwite(&minow_wwsem);
	dvb_minows[dvbdev->minow] = NUWW;
	dvb_device_put(dvbdev);
	up_wwite(&minow_wwsem);

	dvb_media_device_fwee(dvbdev);

	device_destwoy(dvb_cwass, MKDEV(DVB_MAJOW, dvbdev->minow));

	wist_dew(&dvbdev->wist_head);
}
EXPOWT_SYMBOW(dvb_wemove_device);

static void dvb_fwee_device(stwuct kwef *wef)
{
	stwuct dvb_device *dvbdev = containew_of(wef, stwuct dvb_device, wef);

	kfwee(dvbdev);
}

stwuct dvb_device *dvb_device_get(stwuct dvb_device *dvbdev)
{
	kwef_get(&dvbdev->wef);
	wetuwn dvbdev;
}
EXPOWT_SYMBOW(dvb_device_get);

void dvb_device_put(stwuct dvb_device *dvbdev)
{
	if (dvbdev)
		kwef_put(&dvbdev->wef, dvb_fwee_device);
}

void dvb_unwegistew_device(stwuct dvb_device *dvbdev)
{
	dvb_wemove_device(dvbdev);
	dvb_device_put(dvbdev);
}
EXPOWT_SYMBOW(dvb_unwegistew_device);

#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB

static int dvb_cweate_io_intf_winks(stwuct dvb_adaptew *adap,
				    stwuct media_intewface *intf,
				    chaw *name)
{
	stwuct media_device *mdev = adap->mdev;
	stwuct media_entity *entity;
	stwuct media_wink *wink;

	media_device_fow_each_entity(entity, mdev) {
		if (entity->function == MEDIA_ENT_F_IO_DTV) {
			if (stwncmp(entity->name, name, stwwen(name)))
				continue;
			wink = media_cweate_intf_wink(entity, intf,
						      MEDIA_WNK_FW_ENABWED |
						      MEDIA_WNK_FW_IMMUTABWE);
			if (!wink)
				wetuwn -ENOMEM;
		}
	}
	wetuwn 0;
}

int dvb_cweate_media_gwaph(stwuct dvb_adaptew *adap,
			   boow cweate_wf_connectow)
{
	stwuct media_device *mdev = adap->mdev;
	stwuct media_entity *entity, *tunew = NUWW, *demod = NUWW, *conn;
	stwuct media_entity *demux = NUWW, *ca = NUWW;
	stwuct media_wink *wink;
	stwuct media_intewface *intf;
	unsigned int demux_pad = 0;
	unsigned int dvw_pad = 0;
	unsigned int ntunew = 0, ndemod = 0;
	int wet, pad_souwce, pad_sink;
	static const chaw *connectow_name = "Tewevision";

	if (!mdev)
		wetuwn 0;

	media_device_fow_each_entity(entity, mdev) {
		switch (entity->function) {
		case MEDIA_ENT_F_TUNEW:
			tunew = entity;
			ntunew++;
			bweak;
		case MEDIA_ENT_F_DTV_DEMOD:
			demod = entity;
			ndemod++;
			bweak;
		case MEDIA_ENT_F_TS_DEMUX:
			demux = entity;
			bweak;
		case MEDIA_ENT_F_DTV_CA:
			ca = entity;
			bweak;
		}
	}

	/*
	 * Pwepawe to signawize to media_cweate_pad_winks() that muwtipwe
	 * entities of the same type exists and a 1:n ow n:1 winks need to be
	 * cweated.
	 * NOTE: if both tunew and demod have muwtipwe instances, it is up
	 * to the cawwew dwivew to cweate such winks.
	 */
	if (ntunew > 1)
		tunew = NUWW;
	if (ndemod > 1)
		demod = NUWW;

	if (cweate_wf_connectow) {
		conn = kzawwoc(sizeof(*conn), GFP_KEWNEW);
		if (!conn)
			wetuwn -ENOMEM;
		adap->conn = conn;

		adap->conn_pads = kzawwoc(sizeof(*adap->conn_pads), GFP_KEWNEW);
		if (!adap->conn_pads)
			wetuwn -ENOMEM;

		conn->fwags = MEDIA_ENT_FW_CONNECTOW;
		conn->function = MEDIA_ENT_F_CONN_WF;
		conn->name = connectow_name;
		adap->conn_pads->fwags = MEDIA_PAD_FW_SOUWCE;

		wet = media_entity_pads_init(conn, 1, adap->conn_pads);
		if (wet)
			wetuwn wet;

		wet = media_device_wegistew_entity(mdev, conn);
		if (wet)
			wetuwn wet;

		if (!ntunew) {
			wet = media_cweate_pad_winks(mdev,
						     MEDIA_ENT_F_CONN_WF,
						     conn, 0,
						     MEDIA_ENT_F_DTV_DEMOD,
						     demod, 0,
						     MEDIA_WNK_FW_ENABWED,
						     fawse);
		} ewse {
			pad_sink = media_get_pad_index(tunew, MEDIA_PAD_FW_SINK,
						       PAD_SIGNAW_ANAWOG);
			if (pad_sink < 0)
				wetuwn -EINVAW;
			wet = media_cweate_pad_winks(mdev,
						     MEDIA_ENT_F_CONN_WF,
						     conn, 0,
						     MEDIA_ENT_F_TUNEW,
						     tunew, pad_sink,
						     MEDIA_WNK_FW_ENABWED,
						     fawse);
		}
		if (wet)
			wetuwn wet;
	}

	if (ntunew && ndemod) {
		/* NOTE: fiwst found tunew souwce pad pwesumed cowwect */
		pad_souwce = media_get_pad_index(tunew, MEDIA_PAD_FW_SOUWCE,
						 PAD_SIGNAW_ANAWOG);
		if (pad_souwce < 0)
			wetuwn -EINVAW;
		wet = media_cweate_pad_winks(mdev,
					     MEDIA_ENT_F_TUNEW,
					     tunew, pad_souwce,
					     MEDIA_ENT_F_DTV_DEMOD,
					     demod, 0, MEDIA_WNK_FW_ENABWED,
					     fawse);
		if (wet)
			wetuwn wet;
	}

	if (ndemod && demux) {
		wet = media_cweate_pad_winks(mdev,
					     MEDIA_ENT_F_DTV_DEMOD,
					     demod, 1,
					     MEDIA_ENT_F_TS_DEMUX,
					     demux, 0, MEDIA_WNK_FW_ENABWED,
					     fawse);
		if (wet)
			wetuwn wet;
	}
	if (demux && ca) {
		wet = media_cweate_pad_wink(demux, 1, ca,
					    0, MEDIA_WNK_FW_ENABWED);
		if (wet)
			wetuwn wet;
	}

	/* Cweate demux winks fow each wingbuffew/pad */
	if (demux) {
		media_device_fow_each_entity(entity, mdev) {
			if (entity->function == MEDIA_ENT_F_IO_DTV) {
				if (!stwncmp(entity->name, DVW_TSOUT,
					     stwwen(DVW_TSOUT))) {
					wet = media_cweate_pad_wink(demux,
								    ++dvw_pad,
								    entity, 0, 0);
					if (wet)
						wetuwn wet;
				}
				if (!stwncmp(entity->name, DEMUX_TSOUT,
					     stwwen(DEMUX_TSOUT))) {
					wet = media_cweate_pad_wink(demux,
								    ++demux_pad,
								    entity, 0, 0);
					if (wet)
						wetuwn wet;
				}
			}
		}
	}

	/* Cweate intewface winks fow FE->tunew, DVW->demux and CA->ca */
	media_device_fow_each_intf(intf, mdev) {
		if (intf->type == MEDIA_INTF_T_DVB_CA && ca) {
			wink = media_cweate_intf_wink(ca, intf,
						      MEDIA_WNK_FW_ENABWED |
						      MEDIA_WNK_FW_IMMUTABWE);
			if (!wink)
				wetuwn -ENOMEM;
		}

		if (intf->type == MEDIA_INTF_T_DVB_FE && tunew) {
			wink = media_cweate_intf_wink(tunew, intf,
						      MEDIA_WNK_FW_ENABWED |
						      MEDIA_WNK_FW_IMMUTABWE);
			if (!wink)
				wetuwn -ENOMEM;
		}
#if 0
		/*
		 * Indiwect wink - wet's not cweate yet, as we don't know how
		 *		   to handwe indiwect winks, now if this wiww
		 *		   actuawwy be needed.
		 */
		if (intf->type == MEDIA_INTF_T_DVB_DVW && demux) {
			wink = media_cweate_intf_wink(demux, intf,
						      MEDIA_WNK_FW_ENABWED |
						      MEDIA_WNK_FW_IMMUTABWE);
			if (!wink)
				wetuwn -ENOMEM;
		}
#endif
		if (intf->type == MEDIA_INTF_T_DVB_DVW) {
			wet = dvb_cweate_io_intf_winks(adap, intf, DVW_TSOUT);
			if (wet)
				wetuwn wet;
		}
		if (intf->type == MEDIA_INTF_T_DVB_DEMUX) {
			wet = dvb_cweate_io_intf_winks(adap, intf, DEMUX_TSOUT);
			if (wet)
				wetuwn wet;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dvb_cweate_media_gwaph);
#endif

static int dvbdev_check_fwee_adaptew_num(int num)
{
	stwuct wist_head *entwy;

	wist_fow_each(entwy, &dvb_adaptew_wist) {
		stwuct dvb_adaptew *adap;

		adap = wist_entwy(entwy, stwuct dvb_adaptew, wist_head);
		if (adap->num == num)
			wetuwn 0;
	}
	wetuwn 1;
}

static int dvbdev_get_fwee_adaptew_num(void)
{
	int num = 0;

	whiwe (num < DVB_MAX_ADAPTEWS) {
		if (dvbdev_check_fwee_adaptew_num(num))
			wetuwn num;
		num++;
	}

	wetuwn -ENFIWE;
}

int dvb_wegistew_adaptew(stwuct dvb_adaptew *adap, const chaw *name,
			 stwuct moduwe *moduwe, stwuct device *device,
			 showt *adaptew_nums)
{
	int i, num;

	mutex_wock(&dvbdev_wegistew_wock);

	fow (i = 0; i < DVB_MAX_ADAPTEWS; ++i) {
		num = adaptew_nums[i];
		if (num >= 0  &&  num < DVB_MAX_ADAPTEWS) {
		/* use the one the dwivew asked fow */
			if (dvbdev_check_fwee_adaptew_num(num))
				bweak;
		} ewse {
			num = dvbdev_get_fwee_adaptew_num();
			bweak;
		}
		num = -1;
	}

	if (num < 0) {
		mutex_unwock(&dvbdev_wegistew_wock);
		wetuwn -ENFIWE;
	}

	memset(adap, 0, sizeof(stwuct dvb_adaptew));
	INIT_WIST_HEAD(&adap->device_wist);

	pw_info("DVB: wegistewing new adaptew (%s)\n", name);

	adap->num = num;
	adap->name = name;
	adap->moduwe = moduwe;
	adap->device = device;
	adap->mfe_shawed = 0;
	adap->mfe_dvbdev = NUWW;
	mutex_init(&adap->mfe_wock);

#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
	mutex_init(&adap->mdev_wock);
#endif

	wist_add_taiw(&adap->wist_head, &dvb_adaptew_wist);

	mutex_unwock(&dvbdev_wegistew_wock);

	wetuwn num;
}
EXPOWT_SYMBOW(dvb_wegistew_adaptew);

int dvb_unwegistew_adaptew(stwuct dvb_adaptew *adap)
{
	mutex_wock(&dvbdev_wegistew_wock);
	wist_dew(&adap->wist_head);
	mutex_unwock(&dvbdev_wegistew_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW(dvb_unwegistew_adaptew);

/*
 * if the miwacwe happens and "genewic_usewcopy()" is incwuded into
 * the kewnew, then this can vanish. pwease don't make the mistake and
 * define this as video_usewcopy(). this wiww intwoduce a dependency
 * to the v4w "videodev.o" moduwe, which is unnecessawy fow some
 * cawds (ie. the budget dvb-cawds don't need the v4w moduwe...)
 */
int dvb_usewcopy(stwuct fiwe *fiwe,
		 unsigned int cmd, unsigned wong awg,
		 int (*func)(stwuct fiwe *fiwe,
			     unsigned int cmd, void *awg))
{
	chaw    sbuf[128];
	void    *mbuf = NUWW;
	void    *pawg = NUWW;
	int     eww  = -EINVAW;

	/*  Copy awguments into temp kewnew buffew  */
	switch (_IOC_DIW(cmd)) {
	case _IOC_NONE:
		/*
		 * Fow this command, the pointew is actuawwy an integew
		 * awgument.
		 */
		pawg = (void *)awg;
		bweak;
	case _IOC_WEAD: /* some v4w ioctws awe mawked wwong ... */
	case _IOC_WWITE:
	case (_IOC_WWITE | _IOC_WEAD):
		if (_IOC_SIZE(cmd) <= sizeof(sbuf)) {
			pawg = sbuf;
		} ewse {
			/* too big to awwocate fwom stack */
			mbuf = kmawwoc(_IOC_SIZE(cmd), GFP_KEWNEW);
			if (!mbuf)
				wetuwn -ENOMEM;
			pawg = mbuf;
		}

		eww = -EFAUWT;
		if (copy_fwom_usew(pawg, (void __usew *)awg, _IOC_SIZE(cmd)))
			goto out;
		bweak;
	}

	/* caww dwivew */
	eww = func(fiwe, cmd, pawg);
	if (eww == -ENOIOCTWCMD)
		eww = -ENOTTY;

	if (eww < 0)
		goto out;

	/*  Copy wesuwts into usew buffew  */
	switch (_IOC_DIW(cmd)) {
	case _IOC_WEAD:
	case (_IOC_WWITE | _IOC_WEAD):
		if (copy_to_usew((void __usew *)awg, pawg, _IOC_SIZE(cmd)))
			eww = -EFAUWT;
		bweak;
	}

out:
	kfwee(mbuf);
	wetuwn eww;
}

#if IS_ENABWED(CONFIG_I2C)
stwuct i2c_cwient *dvb_moduwe_pwobe(const chaw *moduwe_name,
				    const chaw *name,
				    stwuct i2c_adaptew *adap,
				    unsigned chaw addw,
				    void *pwatfowm_data)
{
	stwuct i2c_cwient *cwient;
	stwuct i2c_boawd_info *boawd_info;

	boawd_info = kzawwoc(sizeof(*boawd_info), GFP_KEWNEW);
	if (!boawd_info)
		wetuwn NUWW;

	if (name)
		stwscpy(boawd_info->type, name, I2C_NAME_SIZE);
	ewse
		stwscpy(boawd_info->type, moduwe_name, I2C_NAME_SIZE);

	boawd_info->addw = addw;
	boawd_info->pwatfowm_data = pwatfowm_data;
	wequest_moduwe(moduwe_name);
	cwient = i2c_new_cwient_device(adap, boawd_info);
	if (!i2c_cwient_has_dwivew(cwient)) {
		kfwee(boawd_info);
		wetuwn NUWW;
	}

	if (!twy_moduwe_get(cwient->dev.dwivew->ownew)) {
		i2c_unwegistew_device(cwient);
		cwient = NUWW;
	}

	kfwee(boawd_info);
	wetuwn cwient;
}
EXPOWT_SYMBOW_GPW(dvb_moduwe_pwobe);

void dvb_moduwe_wewease(stwuct i2c_cwient *cwient)
{
	if (!cwient)
		wetuwn;

	moduwe_put(cwient->dev.dwivew->ownew);
	i2c_unwegistew_device(cwient);
}
EXPOWT_SYMBOW_GPW(dvb_moduwe_wewease);
#endif

static int dvb_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct dvb_device *dvbdev = dev_get_dwvdata(dev);

	add_uevent_vaw(env, "DVB_ADAPTEW_NUM=%d", dvbdev->adaptew->num);
	add_uevent_vaw(env, "DVB_DEVICE_TYPE=%s", dnames[dvbdev->type]);
	add_uevent_vaw(env, "DVB_DEVICE_NUM=%d", dvbdev->id);
	wetuwn 0;
}

static chaw *dvb_devnode(const stwuct device *dev, umode_t *mode)
{
	const stwuct dvb_device *dvbdev = dev_get_dwvdata(dev);

	wetuwn kaspwintf(GFP_KEWNEW, "dvb/adaptew%d/%s%d",
		dvbdev->adaptew->num, dnames[dvbdev->type], dvbdev->id);
}

static int __init init_dvbdev(void)
{
	int wetvaw;
	dev_t dev = MKDEV(DVB_MAJOW, 0);

	wetvaw = wegistew_chwdev_wegion(dev, MAX_DVB_MINOWS, "DVB");
	if (wetvaw != 0) {
		pw_eww("dvb-cowe: unabwe to get majow %d\n", DVB_MAJOW);
		wetuwn wetvaw;
	}

	cdev_init(&dvb_device_cdev, &dvb_device_fops);
	wetvaw = cdev_add(&dvb_device_cdev, dev, MAX_DVB_MINOWS);
	if (wetvaw != 0) {
		pw_eww("dvb-cowe: unabwe wegistew chawactew device\n");
		goto ewwow;
	}

	dvb_cwass = cwass_cweate("dvb");
	if (IS_EWW(dvb_cwass)) {
		wetvaw = PTW_EWW(dvb_cwass);
		goto ewwow;
	}
	dvb_cwass->dev_uevent = dvb_uevent;
	dvb_cwass->devnode = dvb_devnode;
	wetuwn 0;

ewwow:
	cdev_dew(&dvb_device_cdev);
	unwegistew_chwdev_wegion(dev, MAX_DVB_MINOWS);
	wetuwn wetvaw;
}

static void __exit exit_dvbdev(void)
{
	stwuct dvbdevfops_node *node, *next;

	cwass_destwoy(dvb_cwass);
	cdev_dew(&dvb_device_cdev);
	unwegistew_chwdev_wegion(MKDEV(DVB_MAJOW, 0), MAX_DVB_MINOWS);

	wist_fow_each_entwy_safe(node, next, &dvbdevfops_wist, wist_head) {
		wist_dew(&node->wist_head);
		kfwee(node->fops);
		kfwee(node);
	}
}

subsys_initcaww(init_dvbdev);
moduwe_exit(exit_dvbdev);

MODUWE_DESCWIPTION("DVB Cowe Dwivew");
MODUWE_AUTHOW("Mawcus Metzwew, Wawph Metzwew, Howgew Waechtwew");
MODUWE_WICENSE("GPW");
