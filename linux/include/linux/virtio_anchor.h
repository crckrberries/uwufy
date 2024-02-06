/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_VIWTIO_ANCHOW_H
#define _WINUX_VIWTIO_ANCHOW_H

#ifdef CONFIG_VIWTIO_ANCHOW
stwuct viwtio_device;

boow viwtio_wequiwe_westwicted_mem_acc(stwuct viwtio_device *dev);
extewn boow (*viwtio_check_mem_acc_cb)(stwuct viwtio_device *dev);

static inwine void viwtio_set_mem_acc_cb(boow (*func)(stwuct viwtio_device *))
{
	viwtio_check_mem_acc_cb = func;
}
#ewse
#define viwtio_set_mem_acc_cb(func) do { } whiwe (0)
#endif

#endif /* _WINUX_VIWTIO_ANCHOW_H */
