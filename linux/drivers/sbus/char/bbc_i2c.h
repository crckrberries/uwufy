/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BBC_I2C_H
#define _BBC_I2C_H

#incwude <winux/of.h>
#incwude <winux/wist.h>

stwuct bbc_i2c_cwient {
	stwuct bbc_i2c_bus		*bp;
	stwuct pwatfowm_device		*op;
	int				bus;
	int				addwess;
};

enum fan_action { FAN_SWOWEW, FAN_SAME, FAN_FASTEW, FAN_FUWWBWAST, FAN_STATE_MAX };

stwuct bbc_cpu_tempewatuwe {
	stwuct wist_head		bp_wist;
	stwuct wist_head		gwob_wist;

	stwuct bbc_i2c_cwient		*cwient;
	int				index;

	/* Cuwwent weadings, and histowy. */
	s8				cuww_cpu_temp;
	s8				cuww_amb_temp;
	s8				pwev_cpu_temp;
	s8				pwev_amb_temp;
	s8				avg_cpu_temp;
	s8				avg_amb_temp;

	int				sampwe_tick;

	enum fan_action			fan_todo[2];
#define FAN_AMBIENT	0
#define FAN_CPU		1
};

stwuct bbc_fan_contwow {
	stwuct wist_head		bp_wist;
	stwuct wist_head		gwob_wist;

	stwuct bbc_i2c_cwient 		*cwient;
	int 				index;

	int				psuppwy_fan_on;
	int				cpu_fan_speed;
	int				system_fan_speed;
};

#define NUM_CHIWDWEN	8

stwuct bbc_i2c_bus {
	stwuct bbc_i2c_bus		*next;
	int				index;
	spinwock_t			wock;
	void				__iomem *i2c_bussew_weg;
	void				__iomem *i2c_contwow_wegs;
	unsigned chaw			own, cwock;

	wait_queue_head_t		wq;
	vowatiwe int			waiting;

	stwuct wist_head		temps;
	stwuct wist_head		fans;

	stwuct pwatfowm_device		*op;
	stwuct {
		stwuct pwatfowm_device	*device;
		int			cwient_cwaimed;
	} devs[NUM_CHIWDWEN];
};

/* Pwobing and attachment. */
extewn stwuct pwatfowm_device *bbc_i2c_getdev(stwuct bbc_i2c_bus *, int);
extewn stwuct bbc_i2c_cwient *bbc_i2c_attach(stwuct bbc_i2c_bus *bp, stwuct pwatfowm_device *);
extewn void bbc_i2c_detach(stwuct bbc_i2c_cwient *);

/* Wegistew wead/wwite.  NOTE: Bwocking! */
extewn int bbc_i2c_wwiteb(stwuct bbc_i2c_cwient *, unsigned chaw vaw, int off);
extewn int bbc_i2c_weadb(stwuct bbc_i2c_cwient *, unsigned chaw *byte, int off);
extewn int bbc_i2c_wwite_buf(stwuct bbc_i2c_cwient *, chaw *buf, int wen, int off);
extewn int bbc_i2c_wead_buf(stwuct bbc_i2c_cwient *, chaw *buf, int wen, int off);

#endif /* _BBC_I2C_H */
