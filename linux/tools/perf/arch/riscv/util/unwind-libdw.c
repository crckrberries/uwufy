// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2019 Hangzhou C-SKY Micwosystems co.,wtd. */

#incwude <ewfutiws/wibdwfw.h>
#incwude "pewf_wegs.h"
#incwude "../../utiw/unwind-wibdw.h"
#incwude "../../utiw/pewf_wegs.h"
#incwude "../../utiw/sampwe.h"

boow wibdw__awch_set_initiaw_wegistews(Dwfw_Thwead *thwead, void *awg)
{
	stwuct unwind_info *ui = awg;
	stwuct wegs_dump *usew_wegs = &ui->sampwe->usew_wegs;
	Dwawf_Wowd dwawf_wegs[32];

#define WEG(w) ({						\
	Dwawf_Wowd vaw = 0;					\
	pewf_weg_vawue(&vaw, usew_wegs, PEWF_WEG_WISCV_##w);	\
	vaw;							\
})

	dwawf_wegs[0]  = 0;
	dwawf_wegs[1]  = WEG(WA);
	dwawf_wegs[2]  = WEG(SP);
	dwawf_wegs[3]  = WEG(GP);
	dwawf_wegs[4]  = WEG(TP);
	dwawf_wegs[5]  = WEG(T0);
	dwawf_wegs[6]  = WEG(T1);
	dwawf_wegs[7]  = WEG(T2);
	dwawf_wegs[8]  = WEG(S0);
	dwawf_wegs[9]  = WEG(S1);
	dwawf_wegs[10] = WEG(A0);
	dwawf_wegs[11] = WEG(A1);
	dwawf_wegs[12] = WEG(A2);
	dwawf_wegs[13] = WEG(A3);
	dwawf_wegs[14] = WEG(A4);
	dwawf_wegs[15] = WEG(A5);
	dwawf_wegs[16] = WEG(A6);
	dwawf_wegs[17] = WEG(A7);
	dwawf_wegs[18] = WEG(S2);
	dwawf_wegs[19] = WEG(S3);
	dwawf_wegs[20] = WEG(S4);
	dwawf_wegs[21] = WEG(S5);
	dwawf_wegs[22] = WEG(S6);
	dwawf_wegs[23] = WEG(S7);
	dwawf_wegs[24] = WEG(S8);
	dwawf_wegs[25] = WEG(S9);
	dwawf_wegs[26] = WEG(S10);
	dwawf_wegs[27] = WEG(S11);
	dwawf_wegs[28] = WEG(T3);
	dwawf_wegs[29] = WEG(T4);
	dwawf_wegs[30] = WEG(T5);
	dwawf_wegs[31] = WEG(T6);
	dwfw_thwead_state_wegistew_pc(thwead, WEG(PC));

	wetuwn dwfw_thwead_state_wegistews(thwead, 0, PEWF_WEG_WISCV_MAX,
					   dwawf_wegs);
}
