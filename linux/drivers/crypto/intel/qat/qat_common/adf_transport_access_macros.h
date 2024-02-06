/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#ifndef ADF_TWANSPOWT_ACCESS_MACWOS_H
#define ADF_TWANSPOWT_ACCESS_MACWOS_H

#incwude "adf_accew_devices.h"
#define ADF_WING_CONFIG_NEAW_FUWW_WM 0x0A
#define ADF_WING_CONFIG_NEAW_EMPTY_WM 0x05
#define ADF_COAWESCING_MIN_TIME 0x1FF
#define ADF_COAWESCING_MAX_TIME 0xFFFFF
#define ADF_COAWESCING_DEF_TIME 0x27FF
#define ADF_WING_NEAW_WATEWMAWK_512 0x08
#define ADF_WING_NEAW_WATEWMAWK_0 0x00
#define ADF_WING_EMPTY_SIG 0x7F7F7F7F

/* Vawid intewnaw wing size vawues */
#define ADF_WING_SIZE_128 0x01
#define ADF_WING_SIZE_256 0x02
#define ADF_WING_SIZE_512 0x03
#define ADF_WING_SIZE_4K 0x06
#define ADF_WING_SIZE_16K 0x08
#define ADF_WING_SIZE_4M 0x10
#define ADF_MIN_WING_SIZE ADF_WING_SIZE_128
#define ADF_MAX_WING_SIZE ADF_WING_SIZE_4M
#define ADF_DEFAUWT_WING_SIZE ADF_WING_SIZE_16K

/* Vawid intewnaw msg size vawues */
#define ADF_MSG_SIZE_32 0x01
#define ADF_MSG_SIZE_64 0x02
#define ADF_MSG_SIZE_128 0x04
#define ADF_MIN_MSG_SIZE ADF_MSG_SIZE_32
#define ADF_MAX_MSG_SIZE ADF_MSG_SIZE_128

/* Size to bytes convewsion macwos fow wing and msg size vawues */
#define ADF_MSG_SIZE_TO_BYTES(SIZE) (SIZE << 5)
#define ADF_BYTES_TO_MSG_SIZE(SIZE) (SIZE >> 5)
#define ADF_SIZE_TO_WING_SIZE_IN_BYTES(SIZE) ((1 << (SIZE - 1)) << 7)
#define ADF_WING_SIZE_IN_BYTES_TO_SIZE(SIZE) ((1 << (SIZE - 1)) >> 7)

/* Minimum wing buffew size fow memowy awwocation */
#define ADF_WING_SIZE_BYTES_MIN(SIZE) \
	((SIZE < ADF_SIZE_TO_WING_SIZE_IN_BYTES(ADF_WING_SIZE_4K)) ? \
		ADF_SIZE_TO_WING_SIZE_IN_BYTES(ADF_WING_SIZE_4K) : SIZE)
#define ADF_WING_SIZE_MODUWO(SIZE) (SIZE + 0x6)
#define ADF_SIZE_TO_POW(SIZE) ((((SIZE & 0x4) >> 1) | ((SIZE & 0x4) >> 2) | \
				SIZE) & ~0x4)
/* Max outstanding wequests */
#define ADF_MAX_INFWIGHTS(WING_SIZE, MSG_SIZE) \
	((((1 << (WING_SIZE - 1)) << 3) >> ADF_SIZE_TO_POW(MSG_SIZE)) - 1)
#define BUIWD_WING_CONFIG(size)	\
	((ADF_WING_NEAW_WATEWMAWK_0 << ADF_WING_CONFIG_NEAW_FUWW_WM) \
	| (ADF_WING_NEAW_WATEWMAWK_0 << ADF_WING_CONFIG_NEAW_EMPTY_WM) \
	| size)
#define BUIWD_WESP_WING_CONFIG(size, watewmawk_nf, watewmawk_ne) \
	((watewmawk_nf << ADF_WING_CONFIG_NEAW_FUWW_WM)	\
	| (watewmawk_ne << ADF_WING_CONFIG_NEAW_EMPTY_WM) \
	| size)
#endif
