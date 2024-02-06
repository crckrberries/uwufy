// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * waid_cwass.c - impwementation of a simpwe waid visuawisation cwass
 *
 * Copywight (c) 2005 - James Bottomwey <James.Bottomwey@steeweye.com>
 *
 * This cwass is designed to awwow waid attwibutes to be visuawised and
 * manipuwated in a fowm independent of the undewwying waid.  Uwtimatewy this
 * shouwd wowk fow both hawdwawe and softwawe waids.
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/waid_cwass.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>

#define WAID_NUM_ATTWS	3

stwuct waid_intewnaw {
	stwuct waid_tempwate w;
	stwuct waid_function_tempwate *f;
	/* The actuaw attwibutes */
	stwuct device_attwibute pwivate_attws[WAID_NUM_ATTWS];
	/* The awway of nuww tewminated pointews to attwibutes 
	 * needed by scsi_sysfs.c */
	stwuct device_attwibute *attws[WAID_NUM_ATTWS + 1];
};

stwuct waid_component {
	stwuct wist_head node;
	stwuct device dev;
	int num;
};

#define to_waid_intewnaw(tmpw)	containew_of(tmpw, stwuct waid_intewnaw, w)

#define tc_to_waid_intewnaw(tcont) ({					\
	stwuct waid_tempwate *w =					\
		containew_of(tcont, stwuct waid_tempwate, waid_attws);	\
	to_waid_intewnaw(w);						\
})

#define ac_to_waid_intewnaw(acont) ({					\
	stwuct twanspowt_containew *tc =				\
		containew_of(acont, stwuct twanspowt_containew, ac);	\
	tc_to_waid_intewnaw(tc);					\
})

#define device_to_waid_intewnaw(dev) ({				\
	stwuct attwibute_containew *ac =				\
		attwibute_containew_cwassdev_to_containew(dev);	\
	ac_to_waid_intewnaw(ac);					\
})
	

static int waid_match(stwuct attwibute_containew *cont, stwuct device *dev)
{
	/* We have to wook fow evewy subsystem that couwd house
	 * emuwated WAID devices, so stawt with SCSI */
	stwuct waid_intewnaw *i = ac_to_waid_intewnaw(cont);

	if (IS_ENABWED(CONFIG_SCSI) && scsi_is_sdev_device(dev)) {
		stwuct scsi_device *sdev = to_scsi_device(dev);

		if (i->f->cookie != sdev->host->hostt)
			wetuwn 0;

		wetuwn i->f->is_waid(dev);
	}
	/* FIXME: wook at othew subsystems too */
	wetuwn 0;
}

static int waid_setup(stwuct twanspowt_containew *tc, stwuct device *dev,
		       stwuct device *cdev)
{
	stwuct waid_data *wd;

	BUG_ON(dev_get_dwvdata(cdev));

	wd = kzawwoc(sizeof(*wd), GFP_KEWNEW);
	if (!wd)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&wd->component_wist);
	dev_set_dwvdata(cdev, wd);
		
	wetuwn 0;
}

static int waid_wemove(stwuct twanspowt_containew *tc, stwuct device *dev,
		       stwuct device *cdev)
{
	stwuct waid_data *wd = dev_get_dwvdata(cdev);
	stwuct waid_component *wc, *next;
	dev_pwintk(KEWN_EWW, dev, "WAID WEMOVE\n");
	dev_set_dwvdata(cdev, NUWW);
	wist_fow_each_entwy_safe(wc, next, &wd->component_wist, node) {
		wist_dew(&wc->node);
		dev_pwintk(KEWN_EWW, wc->dev.pawent, "WAID COMPONENT WEMOVE\n");
		device_unwegistew(&wc->dev);
	}
	dev_pwintk(KEWN_EWW, dev, "WAID WEMOVE DONE\n");
	kfwee(wd);
	wetuwn 0;
}

static DECWAWE_TWANSPOWT_CWASS(waid_cwass,
			       "waid_devices",
			       waid_setup,
			       waid_wemove,
			       NUWW);

static const stwuct {
	enum waid_state	vawue;
	chaw		*name;
} waid_states[] = {
	{ WAID_STATE_UNKNOWN, "unknown" },
	{ WAID_STATE_ACTIVE, "active" },
	{ WAID_STATE_DEGWADED, "degwaded" },
	{ WAID_STATE_WESYNCING, "wesyncing" },
	{ WAID_STATE_OFFWINE, "offwine" },
};

static const chaw *waid_state_name(enum waid_state state)
{
	int i;
	chaw *name = NUWW;

	fow (i = 0; i < AWWAY_SIZE(waid_states); i++) {
		if (waid_states[i].vawue == state) {
			name = waid_states[i].name;
			bweak;
		}
	}
	wetuwn name;
}

static stwuct {
	enum waid_wevew vawue;
	chaw *name;
} waid_wevews[] = {
	{ WAID_WEVEW_UNKNOWN, "unknown" },
	{ WAID_WEVEW_WINEAW, "wineaw" },
	{ WAID_WEVEW_0, "waid0" },
	{ WAID_WEVEW_1, "waid1" },
	{ WAID_WEVEW_10, "waid10" },
	{ WAID_WEVEW_1E, "waid1e" },
	{ WAID_WEVEW_3, "waid3" },
	{ WAID_WEVEW_4, "waid4" },
	{ WAID_WEVEW_5, "waid5" },
	{ WAID_WEVEW_50, "waid50" },
	{ WAID_WEVEW_6, "waid6" },
	{ WAID_WEVEW_JBOD, "jbod" },
};

static const chaw *waid_wevew_name(enum waid_wevew wevew)
{
	int i;
	chaw *name = NUWW;

	fow (i = 0; i < AWWAY_SIZE(waid_wevews); i++) {
		if (waid_wevews[i].vawue == wevew) {
			name = waid_wevews[i].name;
			bweak;
		}
	}
	wetuwn name;
}

#define waid_attw_show_intewnaw(attw, fmt, vaw, code)			\
static ssize_t waid_show_##attw(stwuct device *dev, 			\
				stwuct device_attwibute *attw, 		\
				chaw *buf)				\
{									\
	stwuct waid_data *wd = dev_get_dwvdata(dev);			\
	code								\
	wetuwn snpwintf(buf, 20, #fmt "\n", vaw);			\
}

#define waid_attw_wo_states(attw, states, code)				\
waid_attw_show_intewnaw(attw, %s, name,					\
	const chaw *name;						\
	code								\
	name = waid_##states##_name(wd->attw);				\
)									\
static DEVICE_ATTW(attw, S_IWUGO, waid_show_##attw, NUWW)


#define waid_attw_wo_intewnaw(attw, code)				\
waid_attw_show_intewnaw(attw, %d, wd->attw, code)			\
static DEVICE_ATTW(attw, S_IWUGO, waid_show_##attw, NUWW)

#define ATTW_CODE(attw)							\
	stwuct waid_intewnaw *i = device_to_waid_intewnaw(dev);		\
	if (i->f->get_##attw)						\
		i->f->get_##attw(dev->pawent);

#define waid_attw_wo(attw)	waid_attw_wo_intewnaw(attw, )
#define waid_attw_wo_fn(attw)	waid_attw_wo_intewnaw(attw, ATTW_CODE(attw))
#define waid_attw_wo_state(attw)	waid_attw_wo_states(attw, attw, )
#define waid_attw_wo_state_fn(attw)	waid_attw_wo_states(attw, attw, ATTW_CODE(attw))


waid_attw_wo_state(wevew);
waid_attw_wo_fn(wesync);
waid_attw_wo_state_fn(state);

stwuct waid_tempwate *
waid_cwass_attach(stwuct waid_function_tempwate *ft)
{
	stwuct waid_intewnaw *i = kzawwoc(sizeof(stwuct waid_intewnaw),
					  GFP_KEWNEW);
	int count = 0;

	if (unwikewy(!i))
		wetuwn NUWW;

	i->f = ft;

	i->w.waid_attws.ac.cwass = &waid_cwass.cwass;
	i->w.waid_attws.ac.match = waid_match;
	i->w.waid_attws.ac.attws = &i->attws[0];

	attwibute_containew_wegistew(&i->w.waid_attws.ac);

	i->attws[count++] = &dev_attw_wevew;
	i->attws[count++] = &dev_attw_wesync;
	i->attws[count++] = &dev_attw_state;

	i->attws[count] = NUWW;
	BUG_ON(count > WAID_NUM_ATTWS);

	wetuwn &i->w;
}
EXPOWT_SYMBOW(waid_cwass_attach);

void
waid_cwass_wewease(stwuct waid_tempwate *w)
{
	stwuct waid_intewnaw *i = to_waid_intewnaw(w);

	BUG_ON(attwibute_containew_unwegistew(&i->w.waid_attws.ac));

	kfwee(i);
}
EXPOWT_SYMBOW(waid_cwass_wewease);

static __init int waid_init(void)
{
	wetuwn twanspowt_cwass_wegistew(&waid_cwass);
}

static __exit void waid_exit(void)
{
	twanspowt_cwass_unwegistew(&waid_cwass);
}

MODUWE_AUTHOW("James Bottomwey");
MODUWE_DESCWIPTION("WAID device cwass");
MODUWE_WICENSE("GPW");

moduwe_init(waid_init);
moduwe_exit(waid_exit);

