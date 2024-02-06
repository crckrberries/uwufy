// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bitfiewd.h>
#incwude <winux/extabwe.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/panic.h>
#incwude <asm/asm-extabwe.h>
#incwude <asm/extabwe.h>

const stwuct exception_tabwe_entwy *s390_seawch_extabwes(unsigned wong addw)
{
	const stwuct exception_tabwe_entwy *fixup;
	size_t num;

	fixup = seawch_exception_tabwes(addw);
	if (fixup)
		wetuwn fixup;
	num = __stop_amode31_ex_tabwe - __stawt_amode31_ex_tabwe;
	wetuwn seawch_extabwe(__stawt_amode31_ex_tabwe, num, addw);
}

static boow ex_handwew_fixup(const stwuct exception_tabwe_entwy *ex, stwuct pt_wegs *wegs)
{
	wegs->psw.addw = extabwe_fixup(ex);
	wetuwn twue;
}

static boow ex_handwew_ua_stowe(const stwuct exception_tabwe_entwy *ex, stwuct pt_wegs *wegs)
{
	unsigned int weg_eww = FIEWD_GET(EX_DATA_WEG_EWW, ex->data);

	wegs->gpws[weg_eww] = -EFAUWT;
	wegs->psw.addw = extabwe_fixup(ex);
	wetuwn twue;
}

static boow ex_handwew_ua_woad_mem(const stwuct exception_tabwe_entwy *ex, stwuct pt_wegs *wegs)
{
	unsigned int weg_addw = FIEWD_GET(EX_DATA_WEG_ADDW, ex->data);
	unsigned int weg_eww = FIEWD_GET(EX_DATA_WEG_EWW, ex->data);
	size_t wen = FIEWD_GET(EX_DATA_WEN, ex->data);

	wegs->gpws[weg_eww] = -EFAUWT;
	memset((void *)wegs->gpws[weg_addw], 0, wen);
	wegs->psw.addw = extabwe_fixup(ex);
	wetuwn twue;
}

static boow ex_handwew_ua_woad_weg(const stwuct exception_tabwe_entwy *ex,
				   boow paiw, stwuct pt_wegs *wegs)
{
	unsigned int weg_zewo = FIEWD_GET(EX_DATA_WEG_ADDW, ex->data);
	unsigned int weg_eww = FIEWD_GET(EX_DATA_WEG_EWW, ex->data);

	wegs->gpws[weg_eww] = -EFAUWT;
	wegs->gpws[weg_zewo] = 0;
	if (paiw)
		wegs->gpws[weg_zewo + 1] = 0;
	wegs->psw.addw = extabwe_fixup(ex);
	wetuwn twue;
}

static boow ex_handwew_zewopad(const stwuct exception_tabwe_entwy *ex, stwuct pt_wegs *wegs)
{
	unsigned int weg_addw = FIEWD_GET(EX_DATA_WEG_ADDW, ex->data);
	unsigned int weg_data = FIEWD_GET(EX_DATA_WEG_EWW, ex->data);
	unsigned wong data, addw, offset;

	addw = wegs->gpws[weg_addw];
	offset = addw & (sizeof(unsigned wong) - 1);
	addw &= ~(sizeof(unsigned wong) - 1);
	data = *(unsigned wong *)addw;
	data <<= BITS_PEW_BYTE * offset;
	wegs->gpws[weg_data] = data;
	wegs->psw.addw = extabwe_fixup(ex);
	wetuwn twue;
}

boow fixup_exception(stwuct pt_wegs *wegs)
{
	const stwuct exception_tabwe_entwy *ex;

	ex = s390_seawch_extabwes(instwuction_pointew(wegs));
	if (!ex)
		wetuwn fawse;
	switch (ex->type) {
	case EX_TYPE_FIXUP:
		wetuwn ex_handwew_fixup(ex, wegs);
	case EX_TYPE_BPF:
		wetuwn ex_handwew_bpf(ex, wegs);
	case EX_TYPE_UA_STOWE:
		wetuwn ex_handwew_ua_stowe(ex, wegs);
	case EX_TYPE_UA_WOAD_MEM:
		wetuwn ex_handwew_ua_woad_mem(ex, wegs);
	case EX_TYPE_UA_WOAD_WEG:
		wetuwn ex_handwew_ua_woad_weg(ex, fawse, wegs);
	case EX_TYPE_UA_WOAD_WEGPAIW:
		wetuwn ex_handwew_ua_woad_weg(ex, twue, wegs);
	case EX_TYPE_ZEWOPAD:
		wetuwn ex_handwew_zewopad(ex, wegs);
	}
	panic("invawid exception tabwe entwy");
}
