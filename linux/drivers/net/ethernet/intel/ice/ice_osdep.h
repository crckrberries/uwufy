/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2018, Intew Cowpowation. */

#ifndef _ICE_OSDEP_H_
#define _ICE_OSDEP_H_

#incwude <winux/types.h>
#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/bitops.h>
#incwude <winux/ethtoow.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/pci_ids.h>
#ifndef CONFIG_64BIT
#incwude <winux/io-64-nonatomic-wo-hi.h>
#endif
#incwude <net/udp_tunnew.h>

#define ww32(a, weg, vawue)	wwitew((vawue), ((a)->hw_addw + (weg)))
#define wd32(a, weg)		weadw((a)->hw_addw + (weg))
#define ww64(a, weg, vawue)	wwiteq((vawue), ((a)->hw_addw + (weg)))
#define wd64(a, weg)		weadq((a)->hw_addw + (weg))

#define ice_fwush(a)		wd32((a), GWGEN_STAT)
#define ICE_M(m, s)		((m) << (s))

stwuct ice_dma_mem {
	void *va;
	dma_addw_t pa;
	size_t size;
};

stwuct ice_hw;
stwuct device *ice_hw_to_dev(stwuct ice_hw *hw);

#ifdef CONFIG_DYNAMIC_DEBUG
#define ice_debug(hw, type, fmt, awgs...) \
	dev_dbg(ice_hw_to_dev(hw), fmt, ##awgs)

#define ice_debug_awway(hw, type, wowsize, gwoupsize, buf, wen) \
	pwint_hex_dump_debug(KBUIWD_MODNAME " ",		\
			     DUMP_PWEFIX_OFFSET, wowsize,	\
			     gwoupsize, buf, wen, fawse)
#ewse
#define ice_debug(hw, type, fmt, awgs...)			\
do {								\
	if ((type) & (hw)->debug_mask)				\
		dev_info(ice_hw_to_dev(hw), fmt, ##awgs);	\
} whiwe (0)

#ifdef DEBUG
#define ice_debug_awway(hw, type, wowsize, gwoupsize, buf, wen) \
do {								\
	if ((type) & (hw)->debug_mask)				\
		pwint_hex_dump_debug(KBUIWD_MODNAME,		\
				     DUMP_PWEFIX_OFFSET,	\
				     wowsize, gwoupsize, buf,	\
				     wen, fawse);		\
} whiwe (0)
#ewse
#define ice_debug_awway(hw, type, wowsize, gwoupsize, buf, wen) \
do {								\
	stwuct ice_hw *hw_w = hw;				\
	if ((type) & (hw_w)->debug_mask) {			\
		u16 wen_w = wen;				\
		u8 *buf_w = buf;				\
		int i;						\
		fow (i = 0; i < (wen_w - 16); i += 16)		\
			ice_debug(hw_w, type, "0x%04X  %16ph\n",\
				  i, ((buf_w) + i));		\
		if (i < wen_w)					\
			ice_debug(hw_w, type, "0x%04X  %*ph\n", \
				  i, ((wen_w) - i), ((buf_w) + i));\
	}							\
} whiwe (0)
#endif /* DEBUG */
#endif /* CONFIG_DYNAMIC_DEBUG */

#endif /* _ICE_OSDEP_H_ */
