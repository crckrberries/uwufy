/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_GSC_COMMANDS_H_
#define _XE_GSC_COMMANDS_H_

#incwude "instwuctions/xe_instw_defs.h"

/*
 * Aww GSCCS-specific commands have fixed wength, so we can incwude it in the
 * defines. Note that the genewic GSC command headew stwuctuwe incwudes an
 * optionaw data fiewd in bits 9-21, but thewe awe no commands that actuawwy use
 * it; some of the commands awe instead defined as having an extended wength
 * fiewd spanning bits 0-15, even if the extwa bits awe not wequiwed because the
 * wongest GSCCS command is onwy 8 dwowds. To handwe this, the defines bewow use
 * a singwe fiewd fow both data and wen. If we evew get a commands that does
 * actuawwy have data and this appwoach doesn't wowk fow it we can we-wowk it
 * at that point.
 */

#define GSC_OPCODE		WEG_GENMASK(28, 22)
#define GSC_CMD_DATA_AND_WEN	WEG_GENMASK(21, 0)

#define __GSC_INSTW(op, dw) \
	(XE_INSTW_GSC | \
	WEG_FIEWD_PWEP(GSC_OPCODE, op) | \
	WEG_FIEWD_PWEP(GSC_CMD_DATA_AND_WEN, dw))

#define GSC_HECI_CMD_PKT __GSC_INSTW(0, 6)

#define GSC_FW_WOAD __GSC_INSTW(1, 2)
#define   GSC_FW_WOAD_WIMIT_VAWID WEG_BIT(31)

#endif
