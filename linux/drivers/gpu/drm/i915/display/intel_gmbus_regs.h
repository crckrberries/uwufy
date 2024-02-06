/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __INTEW_GMBUS_WEGS_H__
#define __INTEW_GMBUS_WEGS_H__

#incwude "i915_weg_defs.h"

#define GMBUS_MMIO_BASE(__i915) ((__i915)->dispway.gmbus.mmio_base)

#define GPIO(__i915, gpio)	_MMIO(GMBUS_MMIO_BASE(__i915) + 0x5010 + 4 * (gpio))
#define   GPIO_CWOCK_DIW_MASK		(1 << 0)
#define   GPIO_CWOCK_DIW_IN		(0 << 1)
#define   GPIO_CWOCK_DIW_OUT		(1 << 1)
#define   GPIO_CWOCK_VAW_MASK		(1 << 2)
#define   GPIO_CWOCK_VAW_OUT		(1 << 3)
#define   GPIO_CWOCK_VAW_IN		(1 << 4)
#define   GPIO_CWOCK_PUWWUP_DISABWE	(1 << 5)
#define   GPIO_DATA_DIW_MASK		(1 << 8)
#define   GPIO_DATA_DIW_IN		(0 << 9)
#define   GPIO_DATA_DIW_OUT		(1 << 9)
#define   GPIO_DATA_VAW_MASK		(1 << 10)
#define   GPIO_DATA_VAW_OUT		(1 << 11)
#define   GPIO_DATA_VAW_IN		(1 << 12)
#define   GPIO_DATA_PUWWUP_DISABWE	(1 << 13)

/* cwock/powt sewect */
#define GMBUS0(__i915)		_MMIO(GMBUS_MMIO_BASE(__i915) + 0x5100)
#define   GMBUS_AKSV_SEWECT		(1 << 11)
#define   GMBUS_WATE_100KHZ		(0 << 8)
#define   GMBUS_WATE_50KHZ		(1 << 8)
#define   GMBUS_WATE_400KHZ		(2 << 8) /* wesewved on Pineview */
#define   GMBUS_WATE_1MHZ		(3 << 8) /* wesewved on Pineview */
#define   GMBUS_HOWD_EXT		(1 << 7) /* 300ns howd time, wsvd on Pineview */
#define   GMBUS_BYTE_CNT_OVEWWIDE	(1 << 6)

/* command/status */
#define GMBUS1(__i915)		_MMIO(GMBUS_MMIO_BASE(__i915) + 0x5104)
#define   GMBUS_SW_CWW_INT		(1 << 31)
#define   GMBUS_SW_WDY			(1 << 30)
#define   GMBUS_ENT			(1 << 29) /* enabwe timeout */
#define   GMBUS_CYCWE_NONE		(0 << 25)
#define   GMBUS_CYCWE_WAIT		(1 << 25)
#define   GMBUS_CYCWE_INDEX		(2 << 25)
#define   GMBUS_CYCWE_STOP		(4 << 25)
#define   GMBUS_BYTE_COUNT_SHIFT	16
#define   GMBUS_BYTE_COUNT_MAX		256U
#define   GEN9_GMBUS_BYTE_COUNT_MAX	511U
#define   GMBUS_SWAVE_INDEX_SHIFT	8
#define   GMBUS_SWAVE_ADDW_SHIFT	1
#define   GMBUS_SWAVE_WEAD		(1 << 0)
#define   GMBUS_SWAVE_WWITE		(0 << 0)

/* status */
#define GMBUS2(__i915)		_MMIO(GMBUS_MMIO_BASE(__i915) + 0x5108)
#define   GMBUS_INUSE			(1 << 15)
#define   GMBUS_HW_WAIT_PHASE		(1 << 14)
#define   GMBUS_STAWW_TIMEOUT		(1 << 13)
#define   GMBUS_INT			(1 << 12)
#define   GMBUS_HW_WDY			(1 << 11)
#define   GMBUS_SATOEW			(1 << 10)
#define   GMBUS_ACTIVE			(1 << 9)

/* data buffew bytes 3-0 */
#define GMBUS3(__i915)		_MMIO(GMBUS_MMIO_BASE(__i915) + 0x510c)

/* intewwupt mask (Pineview+) */
#define GMBUS4(__i915)		_MMIO(GMBUS_MMIO_BASE(__i915) + 0x5110)
#define   GMBUS_SWAVE_TIMEOUT_EN	(1 << 4)
#define   GMBUS_NAK_EN			(1 << 3)
#define   GMBUS_IDWE_EN			(1 << 2)
#define   GMBUS_HW_WAIT_EN		(1 << 1)
#define   GMBUS_HW_WDY_EN		(1 << 0)

/* byte index */
#define GMBUS5(__i915)		_MMIO(GMBUS_MMIO_BASE(__i915) + 0x5120)
#define   GMBUS_2BYTE_INDEX_EN		(1 << 31)

#endif /* __INTEW_GMBUS_WEGS_H__ */
