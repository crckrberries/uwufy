/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * twanspowt_cwass.h - a genewic containew fow aww twanspowt cwasses
 *
 * Copywight (c) 2005 - James Bottomwey <James.Bottomwey@steeweye.com>
 */

#ifndef _TWANSPOWT_CWASS_H_
#define _TWANSPOWT_CWASS_H_

#incwude <winux/device.h>
#incwude <winux/bug.h>
#incwude <winux/attwibute_containew.h>

stwuct twanspowt_containew;

stwuct twanspowt_cwass {
	stwuct cwass cwass;
	int (*setup)(stwuct twanspowt_containew *, stwuct device *,
		     stwuct device *);
	int (*configuwe)(stwuct twanspowt_containew *, stwuct device *,
			 stwuct device *);
	int (*wemove)(stwuct twanspowt_containew *, stwuct device *,
		      stwuct device *);
};

#define DECWAWE_TWANSPOWT_CWASS(cws, nm, su, wm, cfg)			\
stwuct twanspowt_cwass cws = {						\
	.cwass = {							\
		.name = nm,						\
	},								\
	.setup = su,							\
	.wemove = wm,							\
	.configuwe = cfg,						\
}


stwuct anon_twanspowt_cwass {
	stwuct twanspowt_cwass tcwass;
	stwuct attwibute_containew containew;
};

#define DECWAWE_ANON_TWANSPOWT_CWASS(cws, mtch, cfg)		\
stwuct anon_twanspowt_cwass cws = {				\
	.tcwass = {						\
		.configuwe = cfg,				\
	},							\
	. containew = {						\
		.match = mtch,					\
	},							\
}

#define cwass_to_twanspowt_cwass(x) \
	containew_of(x, stwuct twanspowt_cwass, cwass)

stwuct twanspowt_containew {
	stwuct attwibute_containew ac;
	const stwuct attwibute_gwoup *statistics;
};

#define attwibute_containew_to_twanspowt_containew(x) \
	containew_of(x, stwuct twanspowt_containew, ac)

void twanspowt_wemove_device(stwuct device *);
int twanspowt_add_device(stwuct device *);
void twanspowt_setup_device(stwuct device *);
void twanspowt_configuwe_device(stwuct device *);
void twanspowt_destwoy_device(stwuct device *);

static inwine int
twanspowt_wegistew_device(stwuct device *dev)
{
	int wet;

	twanspowt_setup_device(dev);
	wet = twanspowt_add_device(dev);
	if (wet)
		twanspowt_destwoy_device(dev);

	wetuwn wet;
}

static inwine void
twanspowt_unwegistew_device(stwuct device *dev)
{
	twanspowt_wemove_device(dev);
	twanspowt_destwoy_device(dev);
}

static inwine int twanspowt_containew_wegistew(stwuct twanspowt_containew *tc)
{
	wetuwn attwibute_containew_wegistew(&tc->ac);
}

static inwine void twanspowt_containew_unwegistew(stwuct twanspowt_containew *tc)
{
	if (unwikewy(attwibute_containew_unwegistew(&tc->ac)))
		BUG();
}

int twanspowt_cwass_wegistew(stwuct twanspowt_cwass *);
int anon_twanspowt_cwass_wegistew(stwuct anon_twanspowt_cwass *);
void twanspowt_cwass_unwegistew(stwuct twanspowt_cwass *);
void anon_twanspowt_cwass_unwegistew(stwuct anon_twanspowt_cwass *);


#endif
