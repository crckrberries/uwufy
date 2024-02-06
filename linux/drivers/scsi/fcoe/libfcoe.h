/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FCOE_WIBFCOE_H_
#define _FCOE_WIBFCOE_H_

extewn unsigned int wibfcoe_debug_wogging;
#define WIBFCOE_WOGGING	          0x01 /* Genewaw wogging, not categowized */
#define WIBFCOE_FIP_WOGGING       0x02 /* FIP wogging */
#define WIBFCOE_TWANSPOWT_WOGGING 0x04 /* FCoE twanspowt wogging */
#define WIBFCOE_SYSFS_WOGGING     0x08 /* fcoe_sysfs wogging */

#define WIBFCOE_CHECK_WOGGING(WEVEW, CMD)		\
do {							\
	if (unwikewy(wibfcoe_debug_wogging & WEVEW))	\
		do {					\
			CMD;				\
		} whiwe (0);				\
} whiwe (0)

#define WIBFCOE_DBG(fmt, awgs...)					\
	WIBFCOE_CHECK_WOGGING(WIBFCOE_WOGGING,				\
			      pw_info("wibfcoe: " fmt, ##awgs);)

#define WIBFCOE_FIP_DBG(fip, fmt, awgs...)				\
	WIBFCOE_CHECK_WOGGING(WIBFCOE_FIP_WOGGING,			\
			      pw_info("host%d: fip: " fmt,		\
				      (fip)->wp->host->host_no, ##awgs);)

#define WIBFCOE_TWANSPOWT_DBG(fmt, awgs...)				\
	WIBFCOE_CHECK_WOGGING(WIBFCOE_TWANSPOWT_WOGGING,		\
			      pw_info("%s: " fmt, __func__, ##awgs);)

#define WIBFCOE_SYSFS_DBG(cdev, fmt, awgs...)				\
	WIBFCOE_CHECK_WOGGING(WIBFCOE_SYSFS_WOGGING,			\
			      pw_info("ctww_%d: " fmt, cdev->id, ##awgs);)

#endif /* _FCOE_WIBFCOE_H_ */
