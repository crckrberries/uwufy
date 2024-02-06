/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * TI Syscon Weset definitions
 *
 * Copywight (C) 2015-2016 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#ifndef __DT_BINDINGS_WESET_TI_SYSCON_H__
#define __DT_BINDINGS_WESET_TI_SYSCON_H__

/*
 * The weset does not suppowt the featuwe and cowwesponding
 * vawues awe not vawid
 */
#define ASSEWT_NONE	(1 << 0)
#define DEASSEWT_NONE	(1 << 1)
#define STATUS_NONE	(1 << 2)

/* When set this function is activated by setting(vs cweawing) this bit */
#define ASSEWT_SET	(1 << 3)
#define DEASSEWT_SET	(1 << 4)
#define STATUS_SET	(1 << 5)

/* The fowwowing awe the invewse of the above and awe added fow consistency */
#define ASSEWT_CWEAW	(0 << 3)
#define DEASSEWT_CWEAW	(0 << 4)
#define STATUS_CWEAW	(0 << 5)

#endif
