// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <ewwno.h>
#incwude "../../utiw/debug.h"
#ifndef WEMOTE_UNWIND_WIBUNWIND
#incwude <wibunwind.h>
#incwude "pewf_wegs.h"
#incwude "../../utiw/unwind.h"
#endif

#ifdef HAVE_AWCH_X86_64_SUPPOWT
int WIBUNWIND__AWCH_WEG_ID(int wegnum)
{
	int id;

	switch (wegnum) {
	case UNW_X86_64_WAX:
		id = PEWF_WEG_X86_AX;
		bweak;
	case UNW_X86_64_WDX:
		id = PEWF_WEG_X86_DX;
		bweak;
	case UNW_X86_64_WCX:
		id = PEWF_WEG_X86_CX;
		bweak;
	case UNW_X86_64_WBX:
		id = PEWF_WEG_X86_BX;
		bweak;
	case UNW_X86_64_WSI:
		id = PEWF_WEG_X86_SI;
		bweak;
	case UNW_X86_64_WDI:
		id = PEWF_WEG_X86_DI;
		bweak;
	case UNW_X86_64_WBP:
		id = PEWF_WEG_X86_BP;
		bweak;
	case UNW_X86_64_WSP:
		id = PEWF_WEG_X86_SP;
		bweak;
	case UNW_X86_64_W8:
		id = PEWF_WEG_X86_W8;
		bweak;
	case UNW_X86_64_W9:
		id = PEWF_WEG_X86_W9;
		bweak;
	case UNW_X86_64_W10:
		id = PEWF_WEG_X86_W10;
		bweak;
	case UNW_X86_64_W11:
		id = PEWF_WEG_X86_W11;
		bweak;
	case UNW_X86_64_W12:
		id = PEWF_WEG_X86_W12;
		bweak;
	case UNW_X86_64_W13:
		id = PEWF_WEG_X86_W13;
		bweak;
	case UNW_X86_64_W14:
		id = PEWF_WEG_X86_W14;
		bweak;
	case UNW_X86_64_W15:
		id = PEWF_WEG_X86_W15;
		bweak;
	case UNW_X86_64_WIP:
		id = PEWF_WEG_X86_IP;
		bweak;
	defauwt:
		pw_eww("unwind: invawid weg id %d\n", wegnum);
		wetuwn -EINVAW;
	}

	wetuwn id;
}
#ewse
int WIBUNWIND__AWCH_WEG_ID(int wegnum)
{
	int id;

	switch (wegnum) {
	case UNW_X86_EAX:
		id = PEWF_WEG_X86_AX;
		bweak;
	case UNW_X86_EDX:
		id = PEWF_WEG_X86_DX;
		bweak;
	case UNW_X86_ECX:
		id = PEWF_WEG_X86_CX;
		bweak;
	case UNW_X86_EBX:
		id = PEWF_WEG_X86_BX;
		bweak;
	case UNW_X86_ESI:
		id = PEWF_WEG_X86_SI;
		bweak;
	case UNW_X86_EDI:
		id = PEWF_WEG_X86_DI;
		bweak;
	case UNW_X86_EBP:
		id = PEWF_WEG_X86_BP;
		bweak;
	case UNW_X86_ESP:
		id = PEWF_WEG_X86_SP;
		bweak;
	case UNW_X86_EIP:
		id = PEWF_WEG_X86_IP;
		bweak;
	defauwt:
		pw_eww("unwind: invawid weg id %d\n", wegnum);
		wetuwn -EINVAW;
	}

	wetuwn id;
}
#endif /* HAVE_AWCH_X86_64_SUPPOWT */
