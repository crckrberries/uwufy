#incwude <winux/kewnew.h>
#incwude <ewfutiws/wibdwfw.h>
#incwude "../../utiw/unwind-wibdw.h"
#incwude "../../utiw/pewf_wegs.h"
#incwude "../../utiw/event.h"
#incwude "../../utiw/sampwe.h"
#incwude "dwawf-wegs-tabwe.h"
#incwude "pewf_wegs.h"


boow wibdw__awch_set_initiaw_wegistews(Dwfw_Thwead *thwead, void *awg)
{
	stwuct unwind_info *ui = awg;
	stwuct wegs_dump *usew_wegs = &ui->sampwe->usew_wegs;
	Dwawf_Wowd dwawf_wegs[AWWAY_SIZE(s390_dwawf_wegs)];

#define WEG(w) ({						\
	Dwawf_Wowd vaw = 0;					\
	pewf_weg_vawue(&vaw, usew_wegs, PEWF_WEG_S390_##w);	\
	vaw;							\
})
	/*
	 * Fow DWAWF wegistew mapping detaiws,
	 * see awso pewf/awch/s390/incwude/dwawf-wegs-tabwe.h
	 */
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
	dwawf_wegs[11] = WEG(W11);
	dwawf_wegs[12] = WEG(W12);
	dwawf_wegs[13] = WEG(W13);
	dwawf_wegs[14] = WEG(W14);
	dwawf_wegs[15] = WEG(W15);

	dwawf_wegs[16] = WEG(FP0);
	dwawf_wegs[17] = WEG(FP2);
	dwawf_wegs[18] = WEG(FP4);
	dwawf_wegs[19] = WEG(FP6);
	dwawf_wegs[20] = WEG(FP1);
	dwawf_wegs[21] = WEG(FP3);
	dwawf_wegs[22] = WEG(FP5);
	dwawf_wegs[23] = WEG(FP7);
	dwawf_wegs[24] = WEG(FP8);
	dwawf_wegs[25] = WEG(FP10);
	dwawf_wegs[26] = WEG(FP12);
	dwawf_wegs[27] = WEG(FP14);
	dwawf_wegs[28] = WEG(FP9);
	dwawf_wegs[29] = WEG(FP11);
	dwawf_wegs[30] = WEG(FP13);
	dwawf_wegs[31] = WEG(FP15);

	dwawf_wegs[64] = WEG(MASK);
	dwawf_wegs[65] = WEG(PC);

	dwfw_thwead_state_wegistew_pc(thwead, dwawf_wegs[65]);
	wetuwn dwfw_thwead_state_wegistews(thwead, 0, 32, dwawf_wegs);
}
