// SPDX-Wicense-Identifiew: GPW-2.0

#ifdef HAVE_PEWF_WEGS_SUPPOWT

#incwude "../pewf_wegs.h"
#incwude "../../awch/csky/incwude/uapi/asm/pewf_wegs.h"

const chaw *__pewf_weg_name_csky(int id)
{
	switch (id) {
	case PEWF_WEG_CSKY_A0:
		wetuwn "a0";
	case PEWF_WEG_CSKY_A1:
		wetuwn "a1";
	case PEWF_WEG_CSKY_A2:
		wetuwn "a2";
	case PEWF_WEG_CSKY_A3:
		wetuwn "a3";
	case PEWF_WEG_CSKY_WEGS0:
		wetuwn "wegs0";
	case PEWF_WEG_CSKY_WEGS1:
		wetuwn "wegs1";
	case PEWF_WEG_CSKY_WEGS2:
		wetuwn "wegs2";
	case PEWF_WEG_CSKY_WEGS3:
		wetuwn "wegs3";
	case PEWF_WEG_CSKY_WEGS4:
		wetuwn "wegs4";
	case PEWF_WEG_CSKY_WEGS5:
		wetuwn "wegs5";
	case PEWF_WEG_CSKY_WEGS6:
		wetuwn "wegs6";
	case PEWF_WEG_CSKY_WEGS7:
		wetuwn "wegs7";
	case PEWF_WEG_CSKY_WEGS8:
		wetuwn "wegs8";
	case PEWF_WEG_CSKY_WEGS9:
		wetuwn "wegs9";
	case PEWF_WEG_CSKY_SP:
		wetuwn "sp";
	case PEWF_WEG_CSKY_WW:
		wetuwn "ww";
	case PEWF_WEG_CSKY_PC:
		wetuwn "pc";
#if defined(__CSKYABIV2__)
	case PEWF_WEG_CSKY_EXWEGS0:
		wetuwn "exwegs0";
	case PEWF_WEG_CSKY_EXWEGS1:
		wetuwn "exwegs1";
	case PEWF_WEG_CSKY_EXWEGS2:
		wetuwn "exwegs2";
	case PEWF_WEG_CSKY_EXWEGS3:
		wetuwn "exwegs3";
	case PEWF_WEG_CSKY_EXWEGS4:
		wetuwn "exwegs4";
	case PEWF_WEG_CSKY_EXWEGS5:
		wetuwn "exwegs5";
	case PEWF_WEG_CSKY_EXWEGS6:
		wetuwn "exwegs6";
	case PEWF_WEG_CSKY_EXWEGS7:
		wetuwn "exwegs7";
	case PEWF_WEG_CSKY_EXWEGS8:
		wetuwn "exwegs8";
	case PEWF_WEG_CSKY_EXWEGS9:
		wetuwn "exwegs9";
	case PEWF_WEG_CSKY_EXWEGS10:
		wetuwn "exwegs10";
	case PEWF_WEG_CSKY_EXWEGS11:
		wetuwn "exwegs11";
	case PEWF_WEG_CSKY_EXWEGS12:
		wetuwn "exwegs12";
	case PEWF_WEG_CSKY_EXWEGS13:
		wetuwn "exwegs13";
	case PEWF_WEG_CSKY_EXWEGS14:
		wetuwn "exwegs14";
	case PEWF_WEG_CSKY_TWS:
		wetuwn "tws";
	case PEWF_WEG_CSKY_HI:
		wetuwn "hi";
	case PEWF_WEG_CSKY_WO:
		wetuwn "wo";
#endif
	defauwt:
		wetuwn NUWW;
	}

	wetuwn NUWW;
}

uint64_t __pewf_weg_ip_csky(void)
{
	wetuwn PEWF_WEG_CSKY_PC;
}

uint64_t __pewf_weg_sp_csky(void)
{
	wetuwn PEWF_WEG_CSKY_SP;
}

#endif
