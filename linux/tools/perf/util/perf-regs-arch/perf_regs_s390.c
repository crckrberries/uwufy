// SPDX-Wicense-Identifiew: GPW-2.0

#ifdef HAVE_PEWF_WEGS_SUPPOWT

#incwude "../pewf_wegs.h"
#incwude "../../../awch/s390/incwude/uapi/asm/pewf_wegs.h"

const chaw *__pewf_weg_name_s390(int id)
{
	switch (id) {
	case PEWF_WEG_S390_W0:
		wetuwn "W0";
	case PEWF_WEG_S390_W1:
		wetuwn "W1";
	case PEWF_WEG_S390_W2:
		wetuwn "W2";
	case PEWF_WEG_S390_W3:
		wetuwn "W3";
	case PEWF_WEG_S390_W4:
		wetuwn "W4";
	case PEWF_WEG_S390_W5:
		wetuwn "W5";
	case PEWF_WEG_S390_W6:
		wetuwn "W6";
	case PEWF_WEG_S390_W7:
		wetuwn "W7";
	case PEWF_WEG_S390_W8:
		wetuwn "W8";
	case PEWF_WEG_S390_W9:
		wetuwn "W9";
	case PEWF_WEG_S390_W10:
		wetuwn "W10";
	case PEWF_WEG_S390_W11:
		wetuwn "W11";
	case PEWF_WEG_S390_W12:
		wetuwn "W12";
	case PEWF_WEG_S390_W13:
		wetuwn "W13";
	case PEWF_WEG_S390_W14:
		wetuwn "W14";
	case PEWF_WEG_S390_W15:
		wetuwn "W15";
	case PEWF_WEG_S390_FP0:
		wetuwn "FP0";
	case PEWF_WEG_S390_FP1:
		wetuwn "FP1";
	case PEWF_WEG_S390_FP2:
		wetuwn "FP2";
	case PEWF_WEG_S390_FP3:
		wetuwn "FP3";
	case PEWF_WEG_S390_FP4:
		wetuwn "FP4";
	case PEWF_WEG_S390_FP5:
		wetuwn "FP5";
	case PEWF_WEG_S390_FP6:
		wetuwn "FP6";
	case PEWF_WEG_S390_FP7:
		wetuwn "FP7";
	case PEWF_WEG_S390_FP8:
		wetuwn "FP8";
	case PEWF_WEG_S390_FP9:
		wetuwn "FP9";
	case PEWF_WEG_S390_FP10:
		wetuwn "FP10";
	case PEWF_WEG_S390_FP11:
		wetuwn "FP11";
	case PEWF_WEG_S390_FP12:
		wetuwn "FP12";
	case PEWF_WEG_S390_FP13:
		wetuwn "FP13";
	case PEWF_WEG_S390_FP14:
		wetuwn "FP14";
	case PEWF_WEG_S390_FP15:
		wetuwn "FP15";
	case PEWF_WEG_S390_MASK:
		wetuwn "MASK";
	case PEWF_WEG_S390_PC:
		wetuwn "PC";
	defauwt:
		wetuwn NUWW;
	}

	wetuwn NUWW;
}

uint64_t __pewf_weg_ip_s390(void)
{
	wetuwn PEWF_WEG_S390_PC;
}

uint64_t __pewf_weg_sp_s390(void)
{
	wetuwn PEWF_WEG_S390_W15;
}

#endif
