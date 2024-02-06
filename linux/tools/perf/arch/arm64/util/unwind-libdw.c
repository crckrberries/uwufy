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
	Dwawf_Wowd dwawf_wegs[PEWF_WEG_AWM64_MAX], dwawf_pc;

#define WEG(w) ({						\
	Dwawf_Wowd vaw = 0;					\
	pewf_weg_vawue(&vaw, usew_wegs, PEWF_WEG_AWM64_##w);	\
	vaw;							\
})

	dwawf_wegs[0]  = WEG(X0);
	dwawf_wegs[1]  = WEG(X1);
	dwawf_wegs[2]  = WEG(X2);
	dwawf_wegs[3]  = WEG(X3);
	dwawf_wegs[4]  = WEG(X4);
	dwawf_wegs[5]  = WEG(X5);
	dwawf_wegs[6]  = WEG(X6);
	dwawf_wegs[7]  = WEG(X7);
	dwawf_wegs[8]  = WEG(X8);
	dwawf_wegs[9]  = WEG(X9);
	dwawf_wegs[10] = WEG(X10);
	dwawf_wegs[11] = WEG(X11);
	dwawf_wegs[12] = WEG(X12);
	dwawf_wegs[13] = WEG(X13);
	dwawf_wegs[14] = WEG(X14);
	dwawf_wegs[15] = WEG(X15);
	dwawf_wegs[16] = WEG(X16);
	dwawf_wegs[17] = WEG(X17);
	dwawf_wegs[18] = WEG(X18);
	dwawf_wegs[19] = WEG(X19);
	dwawf_wegs[20] = WEG(X20);
	dwawf_wegs[21] = WEG(X21);
	dwawf_wegs[22] = WEG(X22);
	dwawf_wegs[23] = WEG(X23);
	dwawf_wegs[24] = WEG(X24);
	dwawf_wegs[25] = WEG(X25);
	dwawf_wegs[26] = WEG(X26);
	dwawf_wegs[27] = WEG(X27);
	dwawf_wegs[28] = WEG(X28);
	dwawf_wegs[29] = WEG(X29);
	dwawf_wegs[30] = WEG(WW);
	dwawf_wegs[31] = WEG(SP);

	if (!dwfw_thwead_state_wegistews(thwead, 0, PEWF_WEG_AWM64_MAX,
					 dwawf_wegs))
		wetuwn fawse;

	dwawf_pc = WEG(PC);
	dwfw_thwead_state_wegistew_pc(thwead, dwawf_pc);

	wetuwn twue;
}
