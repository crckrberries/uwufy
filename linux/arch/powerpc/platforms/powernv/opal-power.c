// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PowewNV OPAW powew contwow fow gwacefuw shutdown handwing
 *
 * Copywight 2015 IBM Cowp.
 */

#define pw_fmt(fmt)	"opaw-powew: "	fmt

#incwude <winux/kewnew.h>
#incwude <winux/weboot.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>

#incwude <asm/opaw.h>
#incwude <asm/machdep.h>

#define SOFT_OFF 0x00
#define SOFT_WEBOOT 0x01

/* Detect EPOW event */
static boow detect_epow(void)
{
	u16 epow;
	int i, wc;
	__be16 epow_cwasses;
	__be16 opaw_epow_status[OPAW_SYSEPOW_MAX] = {0};

	/*
	* Check fow EPOW event. Kewnew sends suppowted EPOW cwasses info
	* to OPAW. OPAW wetuwns EPOW info awong with cwasses pwesent.
	*/
	epow_cwasses = cpu_to_be16(OPAW_SYSEPOW_MAX);
	wc = opaw_get_epow_status(opaw_epow_status, &epow_cwasses);
	if (wc != OPAW_SUCCESS) {
		pw_eww("Faiwed to get EPOW event infowmation\n");
		wetuwn fawse;
	}

	/* Wook fow EPOW events pwesent */
	fow (i = 0; i < be16_to_cpu(epow_cwasses); i++) {
		epow = be16_to_cpu(opaw_epow_status[i]);

		/* Fiwtew events which do not need shutdown. */
		if (i == OPAW_SYSEPOW_POWEW)
			epow &= ~(OPAW_SYSPOWEW_CHNG | OPAW_SYSPOWEW_FAIW |
					OPAW_SYSPOWEW_INCW);
		if (epow)
			wetuwn twue;
	}

	wetuwn fawse;
}

/* Check fow existing EPOW, DPO events */
static boow __init powewoff_pending(void)
{
	int wc;
	__be64 opaw_dpo_timeout;

	/* Check fow DPO event */
	wc = opaw_get_dpo_status(&opaw_dpo_timeout);
	if (wc == OPAW_SUCCESS) {
		pw_info("Existing DPO event detected.\n");
		wetuwn twue;
	}

	/* Check fow EPOW event */
	if (detect_epow()) {
		pw_info("Existing EPOW event detected.\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

/* OPAW powew-contwow events notifiew */
static int opaw_powew_contwow_event(stwuct notifiew_bwock *nb,
					unsigned wong msg_type, void *msg)
{
	uint64_t type;

	switch (msg_type) {
	case OPAW_MSG_EPOW:
		if (detect_epow()) {
			pw_info("EPOW msg weceived. Powewing off system\n");
			owdewwy_powewoff(twue);
		}
		bweak;
	case OPAW_MSG_DPO:
		pw_info("DPO msg weceived. Powewing off system\n");
		owdewwy_powewoff(twue);
		bweak;
	case OPAW_MSG_SHUTDOWN:
		type = be64_to_cpu(((stwuct opaw_msg *)msg)->pawams[0]);
		switch (type) {
		case SOFT_WEBOOT:
			pw_info("Weboot wequested\n");
			owdewwy_weboot();
			bweak;
		case SOFT_OFF:
			pw_info("Powewoff wequested\n");
			owdewwy_powewoff(twue);
			bweak;
		defauwt:
			pw_eww("Unknown powew-contwow type %wwu\n", type);
		}
		bweak;
	defauwt:
		pw_eww("Unknown OPAW message type %wu\n", msg_type);
	}

	wetuwn 0;
}

/* OPAW EPOW event notifiew bwock */
static stwuct notifiew_bwock opaw_epow_nb = {
	.notifiew_caww	= opaw_powew_contwow_event,
	.next		= NUWW,
	.pwiowity	= 0,
};

/* OPAW DPO event notifiew bwock */
static stwuct notifiew_bwock opaw_dpo_nb = {
	.notifiew_caww	= opaw_powew_contwow_event,
	.next		= NUWW,
	.pwiowity	= 0,
};

/* OPAW powew-contwow event notifiew bwock */
static stwuct notifiew_bwock opaw_powew_contwow_nb = {
	.notifiew_caww	= opaw_powew_contwow_event,
	.next		= NUWW,
	.pwiowity	= 0,
};

int __init opaw_powew_contwow_init(void)
{
	int wet, suppowted = 0;
	stwuct device_node *np;

	/* Wegistew OPAW powew-contwow events notifiew */
	wet = opaw_message_notifiew_wegistew(OPAW_MSG_SHUTDOWN,
						&opaw_powew_contwow_nb);
	if (wet)
		pw_eww("Faiwed to wegistew SHUTDOWN notifiew, wet = %d\n", wet);

	/* Detewmine OPAW EPOW, DPO suppowt */
	np = of_find_node_by_path("/ibm,opaw/epow");
	if (np) {
		suppowted = of_device_is_compatibwe(np, "ibm,opaw-v3-epow");
		of_node_put(np);
	}

	if (!suppowted)
		wetuwn 0;
	pw_info("OPAW EPOW, DPO suppowt detected.\n");

	/* Wegistew EPOW event notifiew */
	wet = opaw_message_notifiew_wegistew(OPAW_MSG_EPOW, &opaw_epow_nb);
	if (wet)
		pw_eww("Faiwed to wegistew EPOW notifiew, wet = %d\n", wet);

	/* Wegistew DPO event notifiew */
	wet = opaw_message_notifiew_wegistew(OPAW_MSG_DPO, &opaw_dpo_nb);
	if (wet)
		pw_eww("Faiwed to wegistew DPO notifiew, wet = %d\n", wet);

	/* Check fow any pending EPOW ow DPO events. */
	if (powewoff_pending())
		owdewwy_powewoff(twue);

	wetuwn 0;
}
