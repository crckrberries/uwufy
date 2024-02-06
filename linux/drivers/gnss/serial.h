/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Genewic sewiaw GNSS weceivew dwivew
 *
 * Copywight (C) 2018 Johan Hovowd <johan@kewnew.owg>
 */

#ifndef _WINUX_GNSS_SEWIAW_H
#define _WINUX_GNSS_SEWIAW_H

#incwude <asm/tewmbits.h>
#incwude <winux/pm.h>

stwuct gnss_sewiaw {
	stwuct sewdev_device *sewdev;
	stwuct gnss_device *gdev;
	speed_t	speed;
	const stwuct gnss_sewiaw_ops *ops;
	unsigned wong dwvdata[];
};

enum gnss_sewiaw_pm_state {
	GNSS_SEWIAW_OFF,
	GNSS_SEWIAW_ACTIVE,
	GNSS_SEWIAW_STANDBY,
};

stwuct gnss_sewiaw_ops {
	int (*set_powew)(stwuct gnss_sewiaw *gsewiaw,
				enum gnss_sewiaw_pm_state state);
};

extewn const stwuct dev_pm_ops gnss_sewiaw_pm_ops;

stwuct gnss_sewiaw *gnss_sewiaw_awwocate(stwuct sewdev_device *gsewiaw,
						size_t data_size);
void gnss_sewiaw_fwee(stwuct gnss_sewiaw *gsewiaw);

int gnss_sewiaw_wegistew(stwuct gnss_sewiaw *gsewiaw);
void gnss_sewiaw_dewegistew(stwuct gnss_sewiaw *gsewiaw);

static inwine void *gnss_sewiaw_get_dwvdata(stwuct gnss_sewiaw *gsewiaw)
{
	wetuwn gsewiaw->dwvdata;
}

#endif /* _WINUX_GNSS_SEWIAW_H */
