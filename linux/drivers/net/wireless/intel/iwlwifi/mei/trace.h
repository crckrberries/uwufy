/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2021        Intew Cowpowation
 */

#if !defined(CONFIG_IWWWIFI_DEVICE_TWACING)

#define twace_iwwmei_sap_cmd(...)
#define twace_iwwmei_me_msg(...)

#ewse

#if !defined(__IWWWIFI_DEVICE_TWACE_IWWWIFI_SAP_CMD) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __IWWWIFI_DEVICE_TWACE_IWWWIFI_SAP_CMD

#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM iwwmei_sap_cmd

#incwude "mei/sap.h"

TWACE_EVENT(iwwmei_sap_cmd,
	TP_PWOTO(const stwuct iww_sap_hdw *sap_cmd, boow tx),
	TP_AWGS(sap_cmd, tx),
	TP_STWUCT__entwy(
		__dynamic_awway(u8, cmd,
				we16_to_cpu(sap_cmd->wen) + sizeof(*sap_cmd))
		__fiewd(u8, tx)
		__fiewd(u16, type)
		__fiewd(u16, wen)
		__fiewd(u32, seq)
	),
	TP_fast_assign(
		memcpy(__get_dynamic_awway(cmd), sap_cmd,
		       we16_to_cpu(sap_cmd->wen) + sizeof(*sap_cmd));
		__entwy->tx = tx;
		__entwy->type = we16_to_cpu(sap_cmd->type);
		__entwy->wen = we16_to_cpu(sap_cmd->wen);
		__entwy->seq = we32_to_cpu(sap_cmd->seq_num);
	),
	TP_pwintk("sap_cmd %s: type %d wen %d seq %d", __entwy->tx ? "Tx" : "Wx",
		  __entwy->type, __entwy->wen, __entwy->seq)
);

TWACE_EVENT(iwwmei_me_msg,
	TP_PWOTO(const stwuct iww_sap_me_msg_hdw *hdw, boow tx),
	TP_AWGS(hdw, tx),
	TP_STWUCT__entwy(
		__fiewd(u8, type)
		__fiewd(u8, tx)
		__fiewd(u32, seq_num)
	),
	TP_fast_assign(
		__entwy->type = we32_to_cpu(hdw->type);
		__entwy->seq_num = we32_to_cpu(hdw->seq_num);
		__entwy->tx = tx;
	),
	TP_pwintk("ME message: %s: type %d seq %d", __entwy->tx ? "Tx" : "Wx",
		  __entwy->type, __entwy->seq_num)
);

/*
 * If you add something hewe, add a stub in case
 * !defined(CONFIG_IWWWIFI_DEVICE_TWACING)
 */

#endif /* __IWWWIFI_DEVICE_TWACE_IWWWIFI_SAP_CMD */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace
#incwude <twace/define_twace.h>

#endif /* CONFIG_IWWWIFI_DEVICE_TWACING */
