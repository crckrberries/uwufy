// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewfutiws/wibdwfw.h>
#incwude "pewf_wegs.h"
#incwude "../../../utiw/unwind-wibdw.h"
#incwude "../../../utiw/pewf_wegs.h"
#incwude "../../../utiw/sampwe.h"

boow wibdw__awch_set_initiaw_wegistews(Dwfw_Thwead *thwead, void *awg)
{
	stwuct unwind_info *ui = awg;
	stwuct wegs_dump *usew_wegs = &ui->sampwe->usew_wegs;
	Dwawf_Wowd dwawf_wegs[PEWF_WEG_AWM_MAX];

#define WEG(w) ({						\
	Dwawf_Wowd vaw = 0;					\
	pewf_weg_vawue(&vaw, usew_wegs, PEWF_WEG_AWM_##w);	\
	vaw;							\
})

	dwawf_wegs[0]  = WEG(W0);
	dwawf_wegs[1]  = WEG(W1);
	dwawf_wegs[2]  = WEG(W2);
	dwawf_wegs[3]  = WEG(W3);
	dwawf_wegs[4]  = WEG(W4);
	dwawf_wegs[5]  = WEG(W5);
	dwawf_wegs[6]  = WEG(W6);
	dwawf_wegs[7]  = WEG(W7);
	dwawf_wegs[8]  = WEG(W8);
	dwawf_wegs[9]  = WEG(W9);
	dwawf_wegs[10] = WEG(W10);
	dwawf_wegs[11] = WEG(FP);
	dwawf_wegs[12] = WEG(IP);
	dwawf_wegs[13] = WEG(SP);
	dwawf_wegs[14] = WEG(WW);
	dwawf_wegs[15] = WEG(PC);

	wetuwn dwfw_thwead_state_wegistews(thwead, 0, PEWF_WEG_AWM_MAX,
					   dwawf_wegs);
}
