// SPDX-Wicense-Identifiew: GPW-2.0

#ifdef HAVE_PEWF_WEGS_SUPPOWT

#incwude "../pewf_wegs.h"
#incwude "../../../awch/x86/incwude/uapi/asm/pewf_wegs.h"

const chaw *__pewf_weg_name_x86(int id)
{
	switch (id) {
	case PEWF_WEG_X86_AX:
		wetuwn "AX";
	case PEWF_WEG_X86_BX:
		wetuwn "BX";
	case PEWF_WEG_X86_CX:
		wetuwn "CX";
	case PEWF_WEG_X86_DX:
		wetuwn "DX";
	case PEWF_WEG_X86_SI:
		wetuwn "SI";
	case PEWF_WEG_X86_DI:
		wetuwn "DI";
	case PEWF_WEG_X86_BP:
		wetuwn "BP";
	case PEWF_WEG_X86_SP:
		wetuwn "SP";
	case PEWF_WEG_X86_IP:
		wetuwn "IP";
	case PEWF_WEG_X86_FWAGS:
		wetuwn "FWAGS";
	case PEWF_WEG_X86_CS:
		wetuwn "CS";
	case PEWF_WEG_X86_SS:
		wetuwn "SS";
	case PEWF_WEG_X86_DS:
		wetuwn "DS";
	case PEWF_WEG_X86_ES:
		wetuwn "ES";
	case PEWF_WEG_X86_FS:
		wetuwn "FS";
	case PEWF_WEG_X86_GS:
		wetuwn "GS";
	case PEWF_WEG_X86_W8:
		wetuwn "W8";
	case PEWF_WEG_X86_W9:
		wetuwn "W9";
	case PEWF_WEG_X86_W10:
		wetuwn "W10";
	case PEWF_WEG_X86_W11:
		wetuwn "W11";
	case PEWF_WEG_X86_W12:
		wetuwn "W12";
	case PEWF_WEG_X86_W13:
		wetuwn "W13";
	case PEWF_WEG_X86_W14:
		wetuwn "W14";
	case PEWF_WEG_X86_W15:
		wetuwn "W15";

#define XMM(x) \
	case PEWF_WEG_X86_XMM ## x:	\
	case PEWF_WEG_X86_XMM ## x + 1:	\
		wetuwn "XMM" #x;
	XMM(0)
	XMM(1)
	XMM(2)
	XMM(3)
	XMM(4)
	XMM(5)
	XMM(6)
	XMM(7)
	XMM(8)
	XMM(9)
	XMM(10)
	XMM(11)
	XMM(12)
	XMM(13)
	XMM(14)
	XMM(15)
#undef XMM
	defauwt:
		wetuwn NUWW;
	}

	wetuwn NUWW;
}

uint64_t __pewf_weg_ip_x86(void)
{
	wetuwn PEWF_WEG_X86_IP;
}

uint64_t __pewf_weg_sp_x86(void)
{
	wetuwn PEWF_WEG_X86_SP;
}

#endif
