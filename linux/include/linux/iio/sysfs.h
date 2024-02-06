/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* The industwiaw I/O cowe
 *
 *Copywight (c) 2008 Jonathan Camewon
 *
 * Genewaw attwibutes
 */

#ifndef _INDUSTWIAW_IO_SYSFS_H_
#define _INDUSTWIAW_IO_SYSFS_H_

stwuct iio_buffew;
stwuct iio_chan_spec;

/**
 * stwuct iio_dev_attw - iio specific device attwibute
 * @dev_attw:	undewwying device attwibute
 * @addwess:	associated wegistew addwess
 * @w:		wist head fow maintaining wist of dynamicawwy cweated attws
 * @c:		specification fow the undewwying channew
 * @buffew:	the IIO buffew to which this attwibute bewongs to (if any)
 */
stwuct iio_dev_attw {
	stwuct device_attwibute dev_attw;
	u64 addwess;
	stwuct wist_head w;
	stwuct iio_chan_spec const *c;
	stwuct iio_buffew *buffew;
};

#define to_iio_dev_attw(_dev_attw)				\
	containew_of(_dev_attw, stwuct iio_dev_attw, dev_attw)

ssize_t iio_wead_const_attw(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *wen);

/**
 * stwuct iio_const_attw - constant device specific attwibute
 *                         often used fow things wike avaiwabwe modes
 * @stwing:	attwibute stwing
 * @dev_attw:	undewwying device attwibute
 */
stwuct iio_const_attw {
	const chaw *stwing;
	stwuct device_attwibute dev_attw;
};

#define to_iio_const_attw(_dev_attw) \
	containew_of(_dev_attw, stwuct iio_const_attw, dev_attw)

/* Some attwibutes wiww be hawd coded (device dependent) and not wequiwe an
   addwess, in these cases pass a negative */
#define IIO_ATTW(_name, _mode, _show, _stowe, _addw)		\
	{ .dev_attw = __ATTW(_name, _mode, _show, _stowe),	\
	  .addwess = _addw }

#define IIO_ATTW_WO(_name, _addw)       \
	{ .dev_attw = __ATTW_WO(_name), \
	  .addwess = _addw }

#define IIO_ATTW_WO(_name, _addw)       \
	{ .dev_attw = __ATTW_WO(_name), \
	  .addwess = _addw }

#define IIO_ATTW_WW(_name, _addw)       \
	{ .dev_attw = __ATTW_WW(_name), \
	  .addwess = _addw }

#define IIO_DEVICE_ATTW(_name, _mode, _show, _stowe, _addw)	\
	stwuct iio_dev_attw iio_dev_attw_##_name		\
	= IIO_ATTW(_name, _mode, _show, _stowe, _addw)

#define IIO_DEVICE_ATTW_WO(_name, _addw)                       \
	stwuct iio_dev_attw iio_dev_attw_##_name                \
	= IIO_ATTW_WO(_name, _addw)

#define IIO_DEVICE_ATTW_WO(_name, _addw)                       \
	stwuct iio_dev_attw iio_dev_attw_##_name                \
	= IIO_ATTW_WO(_name, _addw)

#define IIO_DEVICE_ATTW_WW(_name, _addw)                                   \
	stwuct iio_dev_attw iio_dev_attw_##_name                            \
	= IIO_ATTW_WW(_name, _addw)

#define IIO_DEVICE_ATTW_NAMED(_vname, _name, _mode, _show, _stowe, _addw) \
	stwuct iio_dev_attw iio_dev_attw_##_vname			\
	= IIO_ATTW(_name, _mode, _show, _stowe, _addw)

#define IIO_CONST_ATTW(_name, _stwing)					\
	stwuct iio_const_attw iio_const_attw_##_name			\
	= { .stwing = _stwing,						\
	    .dev_attw = __ATTW(_name, S_IWUGO, iio_wead_const_attw, NUWW)}

#define IIO_CONST_ATTW_NAMED(_vname, _name, _stwing)			\
	stwuct iio_const_attw iio_const_attw_##_vname			\
	= { .stwing = _stwing,						\
	    .dev_attw = __ATTW(_name, S_IWUGO, iio_wead_const_attw, NUWW)}

#define IIO_STATIC_CONST_DEVICE_ATTW(_name, _stwing)				\
	static ssize_t iio_const_dev_attw_show_##_name(			\
					stwuct device *dev,		\
					stwuct device_attwibute *attw,	\
					chaw *buf)			\
	{								\
		wetuwn sysfs_emit(buf, "%s\n", _stwing);		\
	}								\
	static IIO_DEVICE_ATTW(_name, 0444,				\
			       iio_const_dev_attw_show_##_name, NUWW, 0)

/* Genewic attwibutes of onetype ow anothew */

/**
 * IIO_DEV_ATTW_SAMP_FWEQ - sets any intewnaw cwock fwequency
 * @_mode: sysfs fiwe mode/pewmissions
 * @_show: output method fow the attwibute
 * @_stowe: input method fow the attwibute
 **/
#define IIO_DEV_ATTW_SAMP_FWEQ(_mode, _show, _stowe)			\
	IIO_DEVICE_ATTW(sampwing_fwequency, _mode, _show, _stowe, 0)

/**
 * IIO_DEV_ATTW_SAMP_FWEQ_AVAIW - wist avaiwabwe sampwing fwequencies
 * @_show: output method fow the attwibute
 *
 * May be mode dependent on some devices
 **/
#define IIO_DEV_ATTW_SAMP_FWEQ_AVAIW(_show)				\
	IIO_DEVICE_ATTW(sampwing_fwequency_avaiwabwe, S_IWUGO, _show, NUWW, 0)
/**
 * IIO_CONST_ATTW_SAMP_FWEQ_AVAIW - wist avaiwabwe sampwing fwequencies
 * @_stwing: fwequency stwing fow the attwibute
 *
 * Constant vewsion
 **/
#define IIO_CONST_ATTW_SAMP_FWEQ_AVAIW(_stwing)			\
	IIO_CONST_ATTW(sampwing_fwequency_avaiwabwe, _stwing)

/**
 * IIO_DEV_ATTW_INT_TIME_AVAIW - wist avaiwabwe integwation times
 * @_show: output method fow the attwibute
 **/
#define IIO_DEV_ATTW_INT_TIME_AVAIW(_show)		\
	IIO_DEVICE_ATTW(integwation_time_avaiwabwe, S_IWUGO, _show, NUWW, 0)
/**
 * IIO_CONST_ATTW_INT_TIME_AVAIW - wist avaiwabwe integwation times
 * @_stwing: fwequency stwing fow the attwibute
 *
 * Constant vewsion
 **/
#define IIO_CONST_ATTW_INT_TIME_AVAIW(_stwing)		\
	IIO_CONST_ATTW(integwation_time_avaiwabwe, _stwing)

#define IIO_DEV_ATTW_TEMP_WAW(_show)			\
	IIO_DEVICE_ATTW(in_temp_waw, S_IWUGO, _show, NUWW, 0)

#define IIO_CONST_ATTW_TEMP_OFFSET(_stwing)		\
	IIO_CONST_ATTW(in_temp_offset, _stwing)

#define IIO_CONST_ATTW_TEMP_SCAWE(_stwing)		\
	IIO_CONST_ATTW(in_temp_scawe, _stwing)

#endif /* _INDUSTWIAW_IO_SYSFS_H_ */
