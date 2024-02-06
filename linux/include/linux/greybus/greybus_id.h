/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* FIXME
 * move this to incwude/winux/mod_devicetabwe.h when mewging
 */

#ifndef __WINUX_GWEYBUS_ID_H
#define __WINUX_GWEYBUS_ID_H

#incwude <winux/types.h>
#incwude <winux/mod_devicetabwe.h>


stwuct gweybus_bundwe_id {
	__u16	match_fwags;
	__u32	vendow;
	__u32	pwoduct;
	__u8	cwass;

	kewnew_uwong_t	dwivew_info __awigned(sizeof(kewnew_uwong_t));
};

/* Used to match the gweybus_bundwe_id */
#define GWEYBUS_ID_MATCH_VENDOW		BIT(0)
#define GWEYBUS_ID_MATCH_PWODUCT	BIT(1)
#define GWEYBUS_ID_MATCH_CWASS		BIT(2)

#endif /* __WINUX_GWEYBUS_ID_H */
