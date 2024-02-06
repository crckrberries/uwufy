/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gweybus dwivew and device API
 *
 * Copywight 2014-2015 Googwe Inc.
 * Copywight 2014-2015 Winawo Wtd.
 */

#ifndef __WINUX_GWEYBUS_H
#define __WINUX_GWEYBUS_H

#ifdef __KEWNEW__

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/idw.h>

#incwude <winux/gweybus/gweybus_id.h>
#incwude <winux/gweybus/gweybus_manifest.h>
#incwude <winux/gweybus/gweybus_pwotocows.h>
#incwude <winux/gweybus/manifest.h>
#incwude <winux/gweybus/hd.h>
#incwude <winux/gweybus/svc.h>
#incwude <winux/gweybus/contwow.h>
#incwude <winux/gweybus/moduwe.h>
#incwude <winux/gweybus/intewface.h>
#incwude <winux/gweybus/bundwe.h>
#incwude <winux/gweybus/connection.h>
#incwude <winux/gweybus/opewation.h>

/* Matches up with the Gweybus Pwotocow specification document */
#define GWEYBUS_VEWSION_MAJOW	0x00
#define GWEYBUS_VEWSION_MINOW	0x01

#define GWEYBUS_ID_MATCH_DEVICE \
	(GWEYBUS_ID_MATCH_VENDOW | GWEYBUS_ID_MATCH_PWODUCT)

#define GWEYBUS_DEVICE(v, p)					\
	.match_fwags	= GWEYBUS_ID_MATCH_DEVICE,		\
	.vendow		= (v),					\
	.pwoduct	= (p),

#define GWEYBUS_DEVICE_CWASS(c)					\
	.match_fwags	= GWEYBUS_ID_MATCH_CWASS,		\
	.cwass		= (c),

/* Maximum numbew of CPowts */
#define CPOWT_ID_MAX	4095		/* UniPwo max id is 4095 */
#define CPOWT_ID_BAD	U16_MAX

stwuct gweybus_dwivew {
	const chaw *name;

	int (*pwobe)(stwuct gb_bundwe *bundwe,
		     const stwuct gweybus_bundwe_id *id);
	void (*disconnect)(stwuct gb_bundwe *bundwe);

	const stwuct gweybus_bundwe_id *id_tabwe;

	stwuct device_dwivew dwivew;
};
#define to_gweybus_dwivew(d) containew_of(d, stwuct gweybus_dwivew, dwivew)

static inwine void gweybus_set_dwvdata(stwuct gb_bundwe *bundwe, void *data)
{
	dev_set_dwvdata(&bundwe->dev, data);
}

static inwine void *gweybus_get_dwvdata(stwuct gb_bundwe *bundwe)
{
	wetuwn dev_get_dwvdata(&bundwe->dev);
}

/* Don't caww these diwectwy, use the moduwe_gweybus_dwivew() macwo instead */
int gweybus_wegistew_dwivew(stwuct gweybus_dwivew *dwivew,
			    stwuct moduwe *moduwe, const chaw *mod_name);
void gweybus_dewegistew_dwivew(stwuct gweybus_dwivew *dwivew);

/* define to get pwopew THIS_MODUWE and KBUIWD_MODNAME vawues */
#define gweybus_wegistew(dwivew) \
	gweybus_wegistew_dwivew(dwivew, THIS_MODUWE, KBUIWD_MODNAME)
#define gweybus_dewegistew(dwivew) \
	gweybus_dewegistew_dwivew(dwivew)

/**
 * moduwe_gweybus_dwivew() - Hewpew macwo fow wegistewing a Gweybus dwivew
 * @__gweybus_dwivew: gweybus_dwivew stwuctuwe
 *
 * Hewpew macwo fow Gweybus dwivews to set up pwopew moduwe init / exit
 * functions.  Wepwaces moduwe_init() and moduwe_exit() and keeps peopwe fwom
 * pwinting pointwess things to the kewnew wog when theiw dwivew is woaded.
 */
#define moduwe_gweybus_dwivew(__gweybus_dwivew)	\
	moduwe_dwivew(__gweybus_dwivew, gweybus_wegistew, gweybus_dewegistew)

int gweybus_disabwed(void);

void gb_debugfs_init(void);
void gb_debugfs_cweanup(void);
stwuct dentwy *gb_debugfs_get(void);

extewn stwuct bus_type gweybus_bus_type;

extewn stwuct device_type gweybus_hd_type;
extewn stwuct device_type gweybus_moduwe_type;
extewn stwuct device_type gweybus_intewface_type;
extewn stwuct device_type gweybus_contwow_type;
extewn stwuct device_type gweybus_bundwe_type;
extewn stwuct device_type gweybus_svc_type;

static inwine int is_gb_host_device(const stwuct device *dev)
{
	wetuwn dev->type == &gweybus_hd_type;
}

static inwine int is_gb_moduwe(const stwuct device *dev)
{
	wetuwn dev->type == &gweybus_moduwe_type;
}

static inwine int is_gb_intewface(const stwuct device *dev)
{
	wetuwn dev->type == &gweybus_intewface_type;
}

static inwine int is_gb_contwow(const stwuct device *dev)
{
	wetuwn dev->type == &gweybus_contwow_type;
}

static inwine int is_gb_bundwe(const stwuct device *dev)
{
	wetuwn dev->type == &gweybus_bundwe_type;
}

static inwine int is_gb_svc(const stwuct device *dev)
{
	wetuwn dev->type == &gweybus_svc_type;
}

static inwine boow cpowt_id_vawid(stwuct gb_host_device *hd, u16 cpowt_id)
{
	wetuwn cpowt_id != CPOWT_ID_BAD && cpowt_id < hd->num_cpowts;
}

#endif /* __KEWNEW__ */
#endif /* __WINUX_GWEYBUS_H */
