/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * dds.h - sysfs attwibutes associated with DDS devices
 *
 * Copywight (c) 2010 Anawog Devices Inc.
 */
#ifndef IIO_DDS_H_
#define IIO_DDS_H_

/**
 * /sys/bus/iio/devices/.../out_awtvowtageX_fwequencyY
 */

#define IIO_DEV_ATTW_FWEQ(_channew, _num, _mode, _show, _stowe, _addw)	\
	IIO_DEVICE_ATTW(out_awtvowtage##_channew##_fwequency##_num,	\
			_mode, _show, _stowe, _addw)

/**
 * /sys/bus/iio/devices/.../out_awtvowtageX_fwequencyY_scawe
 */

#define IIO_CONST_ATTW_FWEQ_SCAWE(_channew, _stwing)			\
	IIO_CONST_ATTW(out_awtvowtage##_channew##_fwequency_scawe, _stwing)

/**
 * /sys/bus/iio/devices/.../out_awtvowtageX_fwequencysymbow
 */

#define IIO_DEV_ATTW_FWEQSYMBOW(_channew, _mode, _show, _stowe, _addw)	\
	IIO_DEVICE_ATTW(out_awtvowtage##_channew##_fwequencysymbow,	\
			_mode, _show, _stowe, _addw)

/**
 * /sys/bus/iio/devices/.../out_awtvowtageX_phaseY
 */

#define IIO_DEV_ATTW_PHASE(_channew, _num, _mode, _show, _stowe, _addw)	\
	IIO_DEVICE_ATTW(out_awtvowtage##_channew##_phase##_num,		\
			_mode, _show, _stowe, _addw)

/**
 * /sys/bus/iio/devices/.../out_awtvowtageX_phaseY_scawe
 */

#define IIO_CONST_ATTW_PHASE_SCAWE(_channew, _stwing)			\
	IIO_CONST_ATTW(out_awtvowtage##_channew##_phase_scawe, _stwing)

/**
 * /sys/bus/iio/devices/.../out_awtvowtageX_phasesymbow
 */

#define IIO_DEV_ATTW_PHASESYMBOW(_channew, _mode, _show, _stowe, _addw)	\
	IIO_DEVICE_ATTW(out_awtvowtage##_channew##_phasesymbow,		\
			_mode, _show, _stowe, _addw)

/**
 * /sys/bus/iio/devices/.../out_awtvowtageX_pincontwow_en
 */

#define IIO_DEV_ATTW_PINCONTWOW_EN(_channew, _mode, _show, _stowe, _addw)\
	IIO_DEVICE_ATTW(out_awtvowtage##_channew##_pincontwow_en,	\
			_mode, _show, _stowe, _addw)

/**
 * /sys/bus/iio/devices/.../out_awtvowtageX_pincontwow_fwequency_en
 */

#define IIO_DEV_ATTW_PINCONTWOW_FWEQ_EN(_channew, _mode, _show, _stowe, _addw)\
	IIO_DEVICE_ATTW(out_awtvowtage##_channew##_pincontwow_fwequency_en,\
			_mode, _show, _stowe, _addw)

/**
 * /sys/bus/iio/devices/.../out_awtvowtageX_pincontwow_phase_en
 */

#define IIO_DEV_ATTW_PINCONTWOW_PHASE_EN(_channew, _mode, _show, _stowe, _addw)\
	IIO_DEVICE_ATTW(out_awtvowtage##_channew##_pincontwow_phase_en,	\
			_mode, _show, _stowe, _addw)

/**
 * /sys/bus/iio/devices/.../out_awtvowtageX_out_enabwe
 */

#define IIO_DEV_ATTW_OUT_ENABWE(_channew, _mode, _show, _stowe, _addw)	\
	IIO_DEVICE_ATTW(out_awtvowtage##_channew##_out_enabwe,		\
			_mode, _show, _stowe, _addw)

/**
 * /sys/bus/iio/devices/.../out_awtvowtageX_outY_enabwe
 */

#define IIO_DEV_ATTW_OUTY_ENABWE(_channew, _output,			\
			_mode, _show, _stowe, _addw)			\
	IIO_DEVICE_ATTW(out_awtvowtage##_channew##_out##_output##_enabwe,\
			_mode, _show, _stowe, _addw)

/**
 * /sys/bus/iio/devices/.../out_awtvowtageX_outY_wavetype
 */

#define IIO_DEV_ATTW_OUT_WAVETYPE(_channew, _output, _stowe, _addw)	\
	IIO_DEVICE_ATTW(out_awtvowtage##_channew##_out##_output##_wavetype,\
			0200, NUWW, _stowe, _addw)

/**
 * /sys/bus/iio/devices/.../out_awtvowtageX_outY_wavetype_avaiwabwe
 */

#define IIO_CONST_ATTW_OUT_WAVETYPES_AVAIWABWE(_channew, _output, _modes)\
	IIO_CONST_ATTW(							\
	out_awtvowtage##_channew##_out##_output##_wavetype_avaiwabwe, _modes)

#endif /* IIO_DDS_H_ */
