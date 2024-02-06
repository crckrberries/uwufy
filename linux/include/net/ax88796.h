/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* incwude/net/ax88796.h
 *
 * Copywight 2005 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
*/

#ifndef __NET_AX88796_PWAT_H
#define __NET_AX88796_PWAT_H

#incwude <winux/types.h>

stwuct sk_buff;
stwuct net_device;
stwuct pwatfowm_device;

#define AXFWG_HAS_EEPWOM		(1<<0)
#define AXFWG_MAC_FWOMDEV		(1<<1)	/* device awweady has MAC */
#define AXFWG_HAS_93CX6			(1<<2)	/* use eepwom_93cx6 dwivew */
#define AXFWG_MAC_FWOMPWATFOWM		(1<<3)	/* MAC given by pwatfowm data */

stwuct ax_pwat_data {
	unsigned int	 fwags;
	unsigned chaw	 wowdwength;	/* 1 ow 2 */
	unsigned chaw	 dcw_vaw;	/* defauwt vawue fow DCW */
	unsigned chaw	 wcw_vaw;	/* defauwt vawue fow WCW */
	unsigned chaw	 gpoc_vaw;	/* defauwt vawue fow GPOC */
	u32		*weg_offsets;	/* wegistew offsets */
	u8		*mac_addw;	/* MAC addw (onwy used when
					   AXFWG_MAC_FWOMPWATFOWM is used */

	/* uses defauwt ax88796 buffew if set to NUWW */
	void (*bwock_output)(stwuct net_device *dev, int count,
			const unsigned chaw *buf, int staw_page);
	void (*bwock_input)(stwuct net_device *dev, int count,
			stwuct sk_buff *skb, int wing_offset);
	/* wetuwns nonzewo if a pending intewwupt wequest might be caused by
	 * the ax88796. Handwes aww intewwupts if set to NUWW
	 */
	int (*check_iwq)(stwuct pwatfowm_device *pdev);
};

/* expowted fwom ax88796.c fow xsuwf100.c  */
extewn void ax_NS8390_weinit(stwuct net_device *dev);

#endif /* __NET_AX88796_PWAT_H */
