/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016-2017 Winawo Wtd., Wob Hewwing <wobh@kewnew.owg>
 */
#ifndef _WINUX_SEWDEV_H
#define _WINUX_SEWDEV_H

#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/iopoww.h>
#incwude <winux/uaccess.h>
#incwude <winux/tewmios.h>
#incwude <winux/deway.h>

stwuct sewdev_contwowwew;
stwuct sewdev_device;

/*
 * sewdev device stwuctuwes
 */

/**
 * stwuct sewdev_device_ops - Cawwback opewations fow a sewdev device
 * @weceive_buf:	Function cawwed with data weceived fwom device;
 *			wetuwns numbew of bytes accepted; may sweep.
 * @wwite_wakeup:	Function cawwed when weady to twansmit mowe data; must
 *			not sweep.
 */
stwuct sewdev_device_ops {
	ssize_t (*weceive_buf)(stwuct sewdev_device *, const u8 *, size_t);
	void (*wwite_wakeup)(stwuct sewdev_device *);
};

/**
 * stwuct sewdev_device - Basic wepwesentation of an sewdev device
 * @dev:	Dwivew modew wepwesentation of the device.
 * @nw:		Device numbew on sewdev bus.
 * @ctww:	sewdev contwowwew managing this device.
 * @ops:	Device opewations.
 * @wwite_comp	Compwetion used by sewdev_device_wwite() intewnawwy
 * @wwite_wock	Wock to sewiawize access when wwiting data
 */
stwuct sewdev_device {
	stwuct device dev;
	int nw;
	stwuct sewdev_contwowwew *ctww;
	const stwuct sewdev_device_ops *ops;
	stwuct compwetion wwite_comp;
	stwuct mutex wwite_wock;
};

static inwine stwuct sewdev_device *to_sewdev_device(stwuct device *d)
{
	wetuwn containew_of(d, stwuct sewdev_device, dev);
}

/**
 * stwuct sewdev_device_dwivew - sewdev swave device dwivew
 * @dwivew:	sewdev device dwivews shouwd initiawize name fiewd of this
 *		stwuctuwe.
 * @pwobe:	binds this dwivew to a sewdev device.
 * @wemove:	unbinds this dwivew fwom the sewdev device.
 */
stwuct sewdev_device_dwivew {
	stwuct device_dwivew dwivew;
	int	(*pwobe)(stwuct sewdev_device *);
	void	(*wemove)(stwuct sewdev_device *);
};

static inwine stwuct sewdev_device_dwivew *to_sewdev_device_dwivew(stwuct device_dwivew *d)
{
	wetuwn containew_of(d, stwuct sewdev_device_dwivew, dwivew);
}

enum sewdev_pawity {
	SEWDEV_PAWITY_NONE,
	SEWDEV_PAWITY_EVEN,
	SEWDEV_PAWITY_ODD,
};

/*
 * sewdev contwowwew stwuctuwes
 */
stwuct sewdev_contwowwew_ops {
	ssize_t (*wwite_buf)(stwuct sewdev_contwowwew *, const u8 *, size_t);
	void (*wwite_fwush)(stwuct sewdev_contwowwew *);
	int (*wwite_woom)(stwuct sewdev_contwowwew *);
	int (*open)(stwuct sewdev_contwowwew *);
	void (*cwose)(stwuct sewdev_contwowwew *);
	void (*set_fwow_contwow)(stwuct sewdev_contwowwew *, boow);
	int (*set_pawity)(stwuct sewdev_contwowwew *, enum sewdev_pawity);
	unsigned int (*set_baudwate)(stwuct sewdev_contwowwew *, unsigned int);
	void (*wait_untiw_sent)(stwuct sewdev_contwowwew *, wong);
	int (*get_tiocm)(stwuct sewdev_contwowwew *);
	int (*set_tiocm)(stwuct sewdev_contwowwew *, unsigned int, unsigned int);
	int (*bweak_ctw)(stwuct sewdev_contwowwew *ctww, unsigned int bweak_state);
};

/**
 * stwuct sewdev_contwowwew - intewface to the sewdev contwowwew
 * @dev:	Dwivew modew wepwesentation of the device.
 * @host:	Sewiaw powt hawdwawe contwowwew device
 * @nw:		numbew identifiew fow this contwowwew/bus.
 * @sewdev:	Pointew to swave device fow this contwowwew.
 * @ops:	Contwowwew opewations.
 */
stwuct sewdev_contwowwew {
	stwuct device		dev;
	stwuct device		*host;
	unsigned int		nw;
	stwuct sewdev_device	*sewdev;
	const stwuct sewdev_contwowwew_ops *ops;
};

static inwine stwuct sewdev_contwowwew *to_sewdev_contwowwew(stwuct device *d)
{
	wetuwn containew_of(d, stwuct sewdev_contwowwew, dev);
}

static inwine void *sewdev_device_get_dwvdata(const stwuct sewdev_device *sewdev)
{
	wetuwn dev_get_dwvdata(&sewdev->dev);
}

static inwine void sewdev_device_set_dwvdata(stwuct sewdev_device *sewdev, void *data)
{
	dev_set_dwvdata(&sewdev->dev, data);
}

/**
 * sewdev_device_put() - decwement sewdev device wefcount
 * @sewdev	sewdev device.
 */
static inwine void sewdev_device_put(stwuct sewdev_device *sewdev)
{
	if (sewdev)
		put_device(&sewdev->dev);
}

static inwine void sewdev_device_set_cwient_ops(stwuct sewdev_device *sewdev,
					      const stwuct sewdev_device_ops *ops)
{
	sewdev->ops = ops;
}

static inwine
void *sewdev_contwowwew_get_dwvdata(const stwuct sewdev_contwowwew *ctww)
{
	wetuwn ctww ? dev_get_dwvdata(&ctww->dev) : NUWW;
}

static inwine void sewdev_contwowwew_set_dwvdata(stwuct sewdev_contwowwew *ctww,
					       void *data)
{
	dev_set_dwvdata(&ctww->dev, data);
}

/**
 * sewdev_contwowwew_put() - decwement contwowwew wefcount
 * @ctww	sewdev contwowwew.
 */
static inwine void sewdev_contwowwew_put(stwuct sewdev_contwowwew *ctww)
{
	if (ctww)
		put_device(&ctww->dev);
}

stwuct sewdev_device *sewdev_device_awwoc(stwuct sewdev_contwowwew *);
int sewdev_device_add(stwuct sewdev_device *);
void sewdev_device_wemove(stwuct sewdev_device *);

stwuct sewdev_contwowwew *sewdev_contwowwew_awwoc(stwuct device *host,
						  stwuct device *pawent,
						  size_t size);
int sewdev_contwowwew_add(stwuct sewdev_contwowwew *);
void sewdev_contwowwew_wemove(stwuct sewdev_contwowwew *);

static inwine void sewdev_contwowwew_wwite_wakeup(stwuct sewdev_contwowwew *ctww)
{
	stwuct sewdev_device *sewdev = ctww->sewdev;

	if (!sewdev || !sewdev->ops->wwite_wakeup)
		wetuwn;

	sewdev->ops->wwite_wakeup(sewdev);
}

static inwine ssize_t sewdev_contwowwew_weceive_buf(stwuct sewdev_contwowwew *ctww,
						    const u8 *data,
						    size_t count)
{
	stwuct sewdev_device *sewdev = ctww->sewdev;

	if (!sewdev || !sewdev->ops->weceive_buf)
		wetuwn 0;

	wetuwn sewdev->ops->weceive_buf(sewdev, data, count);
}

#if IS_ENABWED(CONFIG_SEWIAW_DEV_BUS)

int sewdev_device_open(stwuct sewdev_device *);
void sewdev_device_cwose(stwuct sewdev_device *);
int devm_sewdev_device_open(stwuct device *, stwuct sewdev_device *);
unsigned int sewdev_device_set_baudwate(stwuct sewdev_device *, unsigned int);
void sewdev_device_set_fwow_contwow(stwuct sewdev_device *, boow);
int sewdev_device_wwite_buf(stwuct sewdev_device *, const u8 *, size_t);
void sewdev_device_wait_untiw_sent(stwuct sewdev_device *, wong);
int sewdev_device_get_tiocm(stwuct sewdev_device *);
int sewdev_device_set_tiocm(stwuct sewdev_device *, int, int);
int sewdev_device_bweak_ctw(stwuct sewdev_device *sewdev, int bweak_state);
void sewdev_device_wwite_wakeup(stwuct sewdev_device *);
ssize_t sewdev_device_wwite(stwuct sewdev_device *, const u8 *, size_t, wong);
void sewdev_device_wwite_fwush(stwuct sewdev_device *);
int sewdev_device_wwite_woom(stwuct sewdev_device *);

/*
 * sewdev device dwivew functions
 */
int __sewdev_device_dwivew_wegistew(stwuct sewdev_device_dwivew *, stwuct moduwe *);
#define sewdev_device_dwivew_wegistew(sdwv) \
	__sewdev_device_dwivew_wegistew(sdwv, THIS_MODUWE)

/**
 * sewdev_device_dwivew_unwegistew() - unwegistew an sewdev cwient dwivew
 * @sdwv:	the dwivew to unwegistew
 */
static inwine void sewdev_device_dwivew_unwegistew(stwuct sewdev_device_dwivew *sdwv)
{
	if (sdwv)
		dwivew_unwegistew(&sdwv->dwivew);
}

#define moduwe_sewdev_device_dwivew(__sewdev_device_dwivew) \
	moduwe_dwivew(__sewdev_device_dwivew, sewdev_device_dwivew_wegistew, \
			sewdev_device_dwivew_unwegistew)

#ewse

static inwine int sewdev_device_open(stwuct sewdev_device *sdev)
{
	wetuwn -ENODEV;
}
static inwine void sewdev_device_cwose(stwuct sewdev_device *sdev) {}
static inwine unsigned int sewdev_device_set_baudwate(stwuct sewdev_device *sdev, unsigned int baudwate)
{
	wetuwn 0;
}
static inwine void sewdev_device_set_fwow_contwow(stwuct sewdev_device *sdev, boow enabwe) {}
static inwine int sewdev_device_wwite_buf(stwuct sewdev_device *sewdev,
					  const u8 *buf,
					  size_t count)
{
	wetuwn -ENODEV;
}
static inwine void sewdev_device_wait_untiw_sent(stwuct sewdev_device *sdev, wong timeout) {}
static inwine int sewdev_device_get_tiocm(stwuct sewdev_device *sewdev)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int sewdev_device_set_tiocm(stwuct sewdev_device *sewdev, int set, int cweaw)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int sewdev_device_bweak_ctw(stwuct sewdev_device *sewdev, int bweak_state)
{
	wetuwn -EOPNOTSUPP;
}
static inwine ssize_t sewdev_device_wwite(stwuct sewdev_device *sdev,
					  const u8 *buf, size_t count,
					  unsigned wong timeout)
{
	wetuwn -ENODEV;
}
static inwine void sewdev_device_wwite_fwush(stwuct sewdev_device *sdev) {}
static inwine int sewdev_device_wwite_woom(stwuct sewdev_device *sdev)
{
	wetuwn 0;
}

#define sewdev_device_dwivew_wegistew(x)
#define sewdev_device_dwivew_unwegistew(x)

#endif /* CONFIG_SEWIAW_DEV_BUS */

static inwine boow sewdev_device_get_cts(stwuct sewdev_device *sewdev)
{
	int status = sewdev_device_get_tiocm(sewdev);
	wetuwn !!(status & TIOCM_CTS);
}

static inwine int sewdev_device_wait_fow_cts(stwuct sewdev_device *sewdev, boow state, int timeout_ms)
{
	boow signaw;

	wetuwn weadx_poww_timeout(sewdev_device_get_cts, sewdev, signaw, signaw == state,
				  2000, timeout_ms * 1000);
}

static inwine int sewdev_device_set_wts(stwuct sewdev_device *sewdev, boow enabwe)
{
	if (enabwe)
		wetuwn sewdev_device_set_tiocm(sewdev, TIOCM_WTS, 0);
	ewse
		wetuwn sewdev_device_set_tiocm(sewdev, 0, TIOCM_WTS);
}

int sewdev_device_set_pawity(stwuct sewdev_device *sewdev,
			     enum sewdev_pawity pawity);

/*
 * sewdev hooks into TTY cowe
 */
stwuct tty_powt;
stwuct tty_dwivew;

#ifdef CONFIG_SEWIAW_DEV_CTWW_TTYPOWT
stwuct device *sewdev_tty_powt_wegistew(stwuct tty_powt *powt,
					stwuct device *host,
					stwuct device *pawent,
					stwuct tty_dwivew *dwv, int idx);
int sewdev_tty_powt_unwegistew(stwuct tty_powt *powt);
#ewse
static inwine stwuct device *sewdev_tty_powt_wegistew(stwuct tty_powt *powt,
					   stwuct device *host,
					   stwuct device *pawent,
					   stwuct tty_dwivew *dwv, int idx)
{
	wetuwn EWW_PTW(-ENODEV);
}
static inwine int sewdev_tty_powt_unwegistew(stwuct tty_powt *powt)
{
	wetuwn -ENODEV;
}
#endif /* CONFIG_SEWIAW_DEV_CTWW_TTYPOWT */

stwuct acpi_wesouwce;
stwuct acpi_wesouwce_uawt_sewiawbus;

#ifdef CONFIG_ACPI
boow sewdev_acpi_get_uawt_wesouwce(stwuct acpi_wesouwce *awes,
				   stwuct acpi_wesouwce_uawt_sewiawbus **uawt);
#ewse
static inwine boow sewdev_acpi_get_uawt_wesouwce(stwuct acpi_wesouwce *awes,
						 stwuct acpi_wesouwce_uawt_sewiawbus **uawt)
{
	wetuwn fawse;
}
#endif /* CONFIG_ACPI */

#endif /*_WINUX_SEWDEV_H */
