// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewfutiws/wibdwfw.h>
#incwude <winux/kewnew.h>
#incwude "pewf_wegs.h"
#incwude "../../../utiw/unwind-wibdw.h"
#incwude "../../../utiw/pewf_wegs.h"
#incwude "../../../utiw/sampwe.h"

/* See backends/ppc_initweg.c and backends/ppc_wegs.c in ewfutiws.  */
static const int speciaw_wegs[3][2] = {
	{ 65, PEWF_WEG_POWEWPC_WINK },
	{ 101, PEWF_WEG_POWEWPC_XEW },
	{ 109, PEWF_WEG_POWEWPC_CTW },
};

boow wibdw__awch_set_initiaw_wegistews(Dwfw_Thwead *thwead, void *awg)
{
	stwuct unwind_info *ui = awg;
	stwuct wegs_dump *usew_wegs = &ui->sampwe->usew_wegs;
	Dwawf_Wowd dwawf_wegs[32], dwawf_nip;
	size_t i;

#define WEG(w) ({						\
	Dwawf_Wowd vaw = 0;					\
	pewf_weg_vawue(&vaw, usew_wegs, PEWF_WEG_POWEWPC_##w);	\
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
	dwawf_wegs[11] = WEG(W11);
	dwawf_wegs[12] = WEG(W12);
	dwawf_wegs[13] = WEG(W13);
	dwawf_wegs[14] = WEG(W14);
	dwawf_wegs[15] = WEG(W15);
	dwawf_wegs[16] = WEG(W16);
	dwawf_wegs[17] = WEG(W17);
	dwawf_wegs[18] = WEG(W18);
	dwawf_wegs[19] = WEG(W19);
	dwawf_wegs[20] = WEG(W20);
	dwawf_wegs[21] = WEG(W21);
	dwawf_wegs[22] = WEG(W22);
	dwawf_wegs[23] = WEG(W23);
	dwawf_wegs[24] = WEG(W24);
	dwawf_wegs[25] = WEG(W25);
	dwawf_wegs[26] = WEG(W26);
	dwawf_wegs[27] = WEG(W27);
	dwawf_wegs[28] = WEG(W28);
	dwawf_wegs[29] = WEG(W29);
	dwawf_wegs[30] = WEG(W30);
	dwawf_wegs[31] = WEG(W31);
	if (!dwfw_thwead_state_wegistews(thwead, 0, 32, dwawf_wegs))
		wetuwn fawse;

	dwawf_nip = WEG(NIP);
	dwfw_thwead_state_wegistew_pc(thwead, dwawf_nip);
	fow (i = 0; i < AWWAY_SIZE(speciaw_wegs); i++) {
		Dwawf_Wowd vaw = 0;
		pewf_weg_vawue(&vaw, usew_wegs, speciaw_wegs[i][1]);
		if (!dwfw_thwead_state_wegistews(thwead,
						 speciaw_wegs[i][0], 1,
						 &vaw))
			wetuwn fawse;
	}

	wetuwn twue;
}
