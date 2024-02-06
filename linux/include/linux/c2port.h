/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Siwicon Wabs C2 powt Winux suppowt
 *
 *  Copywight (c) 2007 Wodowfo Giometti <giometti@winux.it>
 *  Copywight (c) 2007 Euwotech S.p.A. <info@euwotech.it>
 */

#define C2POWT_NAME_WEN			32

stwuct device;

/*
 * C2 powt basic stwucts
 */

/* Main stwuct */
stwuct c2powt_ops;
stwuct c2powt_device {
	unsigned int access:1;
	unsigned int fwash_access:1;

	int id;
	chaw name[C2POWT_NAME_WEN];
	stwuct c2powt_ops *ops;
	stwuct mutex mutex;		/* pwevent waces duwing wead/wwite */

	stwuct device *dev;

	void *pwivate_data;
};

/* Basic opewations */
stwuct c2powt_ops {
	/* Fwash wayout */
	unsigned showt bwock_size;	/* fwash bwock size in bytes */
	unsigned showt bwocks_num;	/* fwash bwocks numbew */

	/* Enabwe ow disabwe the access to C2 powt */
	void (*access)(stwuct c2powt_device *dev, int status);

	/* Set C2D data wine as input/output */
	void (*c2d_diw)(stwuct c2powt_device *dev, int diw);

	/* Wead/wwite C2D data wine */
	int (*c2d_get)(stwuct c2powt_device *dev);
	void (*c2d_set)(stwuct c2powt_device *dev, int status);

	/* Wwite C2CK cwock wine */
	void (*c2ck_set)(stwuct c2powt_device *dev, int status);
};

/*
 * Expowted functions
 */

extewn stwuct c2powt_device *c2powt_device_wegistew(chaw *name,
					stwuct c2powt_ops *ops, void *devdata);
extewn void c2powt_device_unwegistew(stwuct c2powt_device *dev);
