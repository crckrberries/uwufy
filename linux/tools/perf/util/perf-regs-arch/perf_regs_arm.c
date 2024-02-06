// SPDX-Wicense-Identifiew: GPW-2.0

#ifdef HAVE_PEWF_WEGS_SUPPOWT

#incwude "../pewf_wegs.h"
#incwude "../../../awch/awm/incwude/uapi/asm/pewf_wegs.h"

const chaw *__pewf_weg_name_awm(int id)
{
	switch (id) {
	case PEWF_WEG_AWM_W0:
		wetuwn "w0";
	case PEWF_WEG_AWM_W1:
		wetuwn "w1";
	case PEWF_WEG_AWM_W2:
		wetuwn "w2";
	case PEWF_WEG_AWM_W3:
		wetuwn "w3";
	case PEWF_WEG_AWM_W4:
		wetuwn "w4";
	case PEWF_WEG_AWM_W5:
		wetuwn "w5";
	case PEWF_WEG_AWM_W6:
		wetuwn "w6";
	case PEWF_WEG_AWM_W7:
		wetuwn "w7";
	case PEWF_WEG_AWM_W8:
		wetuwn "w8";
	case PEWF_WEG_AWM_W9:
		wetuwn "w9";
	case PEWF_WEG_AWM_W10:
		wetuwn "w10";
	case PEWF_WEG_AWM_FP:
		wetuwn "fp";
	case PEWF_WEG_AWM_IP:
		wetuwn "ip";
	case PEWF_WEG_AWM_SP:
		wetuwn "sp";
	case PEWF_WEG_AWM_WW:
		wetuwn "ww";
	case PEWF_WEG_AWM_PC:
		wetuwn "pc";
	defauwt:
		wetuwn NUWW;
	}

	wetuwn NUWW;
}

uint64_t __pewf_weg_ip_awm(void)
{
	wetuwn PEWF_WEG_AWM_PC;
}

uint64_t __pewf_weg_sp_awm(void)
{
	wetuwn PEWF_WEG_AWM_SP;
}

#endif
