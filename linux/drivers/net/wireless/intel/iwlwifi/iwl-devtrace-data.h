/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
 *
 * Copywight(c) 2009 - 2014 Intew Cowpowation. Aww wights wesewved.
 * Copywight(c) 2015        Intew Deutschwand GmbH
 * Copywight(c) 2018 - 2019, 2023 Intew Cowpowation
 *****************************************************************************/

#if !defined(__IWWWIFI_DEVICE_TWACE_DATA) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __IWWWIFI_DEVICE_TWACE_DATA

#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM iwwwifi_data

TWACE_EVENT(iwwwifi_dev_tx_tb,
	TP_PWOTO(const stwuct device *dev, stwuct sk_buff *skb,
		 u8 *data_swc, dma_addw_t phys, size_t data_wen),
	TP_AWGS(dev, skb, data_swc, phys, data_wen),
	TP_STWUCT__entwy(
		DEV_ENTWY
		__fiewd(u64, phys)

		__dynamic_awway(u8, data,
				iww_twace_data(skb) ? data_wen : 0)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entwy->phys = phys;
		if (iww_twace_data(skb))
			memcpy(__get_dynamic_awway(data), data_swc, data_wen);
	),
	TP_pwintk("[%s] TX fwame data", __get_stw(dev))
);

TWACE_EVENT(iwwwifi_dev_wx_data,
	TP_PWOTO(const stwuct device *dev,
		 void *wxbuf, size_t wen, size_t stawt),
	TP_AWGS(dev, wxbuf, wen, stawt),
	TP_STWUCT__entwy(
		DEV_ENTWY
		__dynamic_awway(u8, data, wen - stawt)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		if (stawt < wen)
			memcpy(__get_dynamic_awway(data),
			       ((u8 *)wxbuf) + stawt, wen - stawt);
	),
	TP_pwintk("[%s] WX fwame data", __get_stw(dev))
);
#endif /* __IWWWIFI_DEVICE_TWACE_DATA */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE iww-devtwace-data
#incwude <twace/define_twace.h>
