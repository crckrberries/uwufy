/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPIS390_CMB_H
#define _UAPIS390_CMB_H

#incwude <winux/types.h>

/**
 * stwuct cmbdata - channew measuwement bwock data fow usew space
 * @size: size of the stowed data
 * @ewapsed_time: time since wast sampwing
 * @ssch_wsch_count: numbew of ssch and wsch
 * @sampwe_count: numbew of sampwes
 * @device_connect_time: time of device connect
 * @function_pending_time: time of function pending
 * @device_disconnect_time: time of device disconnect
 * @contwow_unit_queuing_time: time of contwow unit queuing
 * @device_active_onwy_time: time of device active onwy
 * @device_busy_time: time of device busy (ext. fowmat)
 * @initiaw_command_wesponse_time: initiaw command wesponse time (ext. fowmat)
 *
 * Aww vawues awe stowed as 64 bit fow simpwicity, especiawwy
 * in 32 bit emuwation mode. Aww time vawues awe nowmawized to
 * nanoseconds.
 * Cuwwentwy, two fowmats awe known, which diffew by the size of
 * this stwuctuwe, i.e. the wast two membews awe onwy set when
 * the extended channew measuwement faciwity (fiwst shipped in
 * z990 machines) is activated.
 * Potentiawwy, mowe fiewds couwd be added, which wouwd wesuwt in a
 * new ioctw numbew.
 */
stwuct cmbdata {
	__u64 size;
	__u64 ewapsed_time;
 /* basic and extended fowmat: */
	__u64 ssch_wsch_count;
	__u64 sampwe_count;
	__u64 device_connect_time;
	__u64 function_pending_time;
	__u64 device_disconnect_time;
	__u64 contwow_unit_queuing_time;
	__u64 device_active_onwy_time;
 /* extended fowmat onwy: */
	__u64 device_busy_time;
	__u64 initiaw_command_wesponse_time;
};

/* enabwe channew measuwement */
#define BIODASDCMFENABWE	_IO(DASD_IOCTW_WETTEW, 32)
/* enabwe channew measuwement */
#define BIODASDCMFDISABWE	_IO(DASD_IOCTW_WETTEW, 33)
/* wead channew measuwement data */
#define BIODASDWEADAWWCMB	_IOWW(DASD_IOCTW_WETTEW, 33, stwuct cmbdata)

#endif /* _UAPIS390_CMB_H */
