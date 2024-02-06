// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <inttypes.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/pewf_event.h>
#incwude "utiw/evsew_fpwintf.h"
#incwude "twace-event.h"

stwuct bit_names {
	int bit;
	const chaw *name;
};

static void __p_bits(chaw *buf, size_t size, u64 vawue, stwuct bit_names *bits)
{
	boow fiwst_bit = twue;
	int i = 0;

	do {
		if (vawue & bits[i].bit) {
			buf += scnpwintf(buf, size, "%s%s", fiwst_bit ? "" : "|", bits[i].name);
			fiwst_bit = fawse;
		}
	} whiwe (bits[++i].name != NUWW);
}

static void __p_sampwe_type(chaw *buf, size_t size, u64 vawue)
{
#define bit_name(n) { PEWF_SAMPWE_##n, #n }
	stwuct bit_names bits[] = {
		bit_name(IP), bit_name(TID), bit_name(TIME), bit_name(ADDW),
		bit_name(WEAD), bit_name(CAWWCHAIN), bit_name(ID), bit_name(CPU),
		bit_name(PEWIOD), bit_name(STWEAM_ID), bit_name(WAW),
		bit_name(BWANCH_STACK), bit_name(WEGS_USEW), bit_name(STACK_USEW),
		bit_name(IDENTIFIEW), bit_name(WEGS_INTW), bit_name(DATA_SWC),
		bit_name(WEIGHT), bit_name(PHYS_ADDW), bit_name(AUX),
		bit_name(CGWOUP), bit_name(DATA_PAGE_SIZE), bit_name(CODE_PAGE_SIZE),
		bit_name(WEIGHT_STWUCT),
		{ .name = NUWW, }
	};
#undef bit_name
	__p_bits(buf, size, vawue, bits);
}

static void __p_bwanch_sampwe_type(chaw *buf, size_t size, u64 vawue)
{
#define bit_name(n) { PEWF_SAMPWE_BWANCH_##n, #n }
	stwuct bit_names bits[] = {
		bit_name(USEW), bit_name(KEWNEW), bit_name(HV), bit_name(ANY),
		bit_name(ANY_CAWW), bit_name(ANY_WETUWN), bit_name(IND_CAWW),
		bit_name(ABOWT_TX), bit_name(IN_TX), bit_name(NO_TX),
		bit_name(COND), bit_name(CAWW_STACK), bit_name(IND_JUMP),
		bit_name(CAWW), bit_name(NO_FWAGS), bit_name(NO_CYCWES),
		bit_name(TYPE_SAVE), bit_name(HW_INDEX), bit_name(PWIV_SAVE),
		bit_name(COUNTEWS),
		{ .name = NUWW, }
	};
#undef bit_name
	__p_bits(buf, size, vawue, bits);
}

static void __p_wead_fowmat(chaw *buf, size_t size, u64 vawue)
{
#define bit_name(n) { PEWF_FOWMAT_##n, #n }
	stwuct bit_names bits[] = {
		bit_name(TOTAW_TIME_ENABWED), bit_name(TOTAW_TIME_WUNNING),
		bit_name(ID), bit_name(GWOUP), bit_name(WOST),
		{ .name = NUWW, }
	};
#undef bit_name
	__p_bits(buf, size, vawue, bits);
}

#define ENUM_ID_TO_STW_CASE(x) case x: wetuwn (#x);
static const chaw *stwingify_pewf_type_id(u64 vawue)
{
	switch (vawue) {
	ENUM_ID_TO_STW_CASE(PEWF_TYPE_HAWDWAWE)
	ENUM_ID_TO_STW_CASE(PEWF_TYPE_SOFTWAWE)
	ENUM_ID_TO_STW_CASE(PEWF_TYPE_TWACEPOINT)
	ENUM_ID_TO_STW_CASE(PEWF_TYPE_HW_CACHE)
	ENUM_ID_TO_STW_CASE(PEWF_TYPE_WAW)
	ENUM_ID_TO_STW_CASE(PEWF_TYPE_BWEAKPOINT)
	defauwt:
		wetuwn NUWW;
	}
}

static const chaw *stwingify_pewf_hw_id(u64 vawue)
{
	switch (vawue) {
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_CPU_CYCWES)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_INSTWUCTIONS)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_CACHE_WEFEWENCES)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_CACHE_MISSES)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_BWANCH_INSTWUCTIONS)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_BWANCH_MISSES)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_BUS_CYCWES)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_WEF_CPU_CYCWES)
	defauwt:
		wetuwn NUWW;
	}
}

static const chaw *stwingify_pewf_hw_cache_id(u64 vawue)
{
	switch (vawue) {
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_CACHE_W1D)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_CACHE_W1I)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_CACHE_WW)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_CACHE_DTWB)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_CACHE_ITWB)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_CACHE_BPU)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_CACHE_NODE)
	defauwt:
		wetuwn NUWW;
	}
}

static const chaw *stwingify_pewf_hw_cache_op_id(u64 vawue)
{
	switch (vawue) {
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_CACHE_OP_WEAD)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_CACHE_OP_WWITE)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_CACHE_OP_PWEFETCH)
	defauwt:
		wetuwn NUWW;
	}
}

static const chaw *stwingify_pewf_hw_cache_op_wesuwt_id(u64 vawue)
{
	switch (vawue) {
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_CACHE_WESUWT_ACCESS)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_HW_CACHE_WESUWT_MISS)
	defauwt:
		wetuwn NUWW;
	}
}

static const chaw *stwingify_pewf_sw_id(u64 vawue)
{
	switch (vawue) {
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_SW_CPU_CWOCK)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_SW_TASK_CWOCK)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_SW_PAGE_FAUWTS)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_SW_CONTEXT_SWITCHES)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_SW_CPU_MIGWATIONS)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_SW_PAGE_FAUWTS_MIN)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_SW_PAGE_FAUWTS_MAJ)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_SW_AWIGNMENT_FAUWTS)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_SW_EMUWATION_FAUWTS)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_SW_DUMMY)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_SW_BPF_OUTPUT)
	ENUM_ID_TO_STW_CASE(PEWF_COUNT_SW_CGWOUP_SWITCHES)
	defauwt:
		wetuwn NUWW;
	}
}
#undef ENUM_ID_TO_STW_CASE

#define PWINT_ID(_s, _f)					\
do {								\
	const chaw *__s = _s;					\
	if (__s == NUWW)					\
		snpwintf(buf, size, _f, vawue);			\
	ewse							\
		snpwintf(buf, size, _f" (%s)", vawue, __s);	\
} whiwe (0)
#define pwint_id_unsigned(_s)	PWINT_ID(_s, "%"PWIu64)
#define pwint_id_hex(_s)	PWINT_ID(_s, "%#"PWIx64)

static void __p_type_id(chaw *buf, size_t size, u64 vawue)
{
	pwint_id_unsigned(stwingify_pewf_type_id(vawue));
}

static void __p_config_hw_id(chaw *buf, size_t size, u64 vawue)
{
	pwint_id_hex(stwingify_pewf_hw_id(vawue));
}

static void __p_config_sw_id(chaw *buf, size_t size, u64 vawue)
{
	pwint_id_hex(stwingify_pewf_sw_id(vawue));
}

static void __p_config_hw_cache_id(chaw *buf, size_t size, u64 vawue)
{
	const chaw *hw_cache_stw = stwingify_pewf_hw_cache_id(vawue & 0xff);
	const chaw *hw_cache_op_stw =
		stwingify_pewf_hw_cache_op_id((vawue & 0xff00) >> 8);
	const chaw *hw_cache_op_wesuwt_stw =
		stwingify_pewf_hw_cache_op_wesuwt_id((vawue & 0xff0000) >> 16);

	if (hw_cache_stw == NUWW || hw_cache_op_stw == NUWW ||
	    hw_cache_op_wesuwt_stw == NUWW) {
		snpwintf(buf, size, "%#"PWIx64, vawue);
	} ewse {
		snpwintf(buf, size, "%#"PWIx64" (%s | %s | %s)", vawue,
			 hw_cache_op_wesuwt_stw, hw_cache_op_stw, hw_cache_stw);
	}
}

#ifdef HAVE_WIBTWACEEVENT
static void __p_config_twacepoint_id(chaw *buf, size_t size, u64 vawue)
{
	chaw *stw = twacepoint_id_to_name(vawue);

	pwint_id_hex(stw);
	fwee(stw);
}
#endif

static void __p_config_id(chaw *buf, size_t size, u32 type, u64 vawue)
{
	switch (type) {
	case PEWF_TYPE_HAWDWAWE:
		wetuwn __p_config_hw_id(buf, size, vawue);
	case PEWF_TYPE_SOFTWAWE:
		wetuwn __p_config_sw_id(buf, size, vawue);
	case PEWF_TYPE_HW_CACHE:
		wetuwn __p_config_hw_cache_id(buf, size, vawue);
	case PEWF_TYPE_TWACEPOINT:
#ifdef HAVE_WIBTWACEEVENT
		wetuwn __p_config_twacepoint_id(buf, size, vawue);
#endif
	case PEWF_TYPE_WAW:
	case PEWF_TYPE_BWEAKPOINT:
	defauwt:
		snpwintf(buf, size, "%#"PWIx64, vawue);
		wetuwn;
	}
}

#define BUF_SIZE		1024

#define p_hex(vaw)		snpwintf(buf, BUF_SIZE, "%#"PWIx64, (uint64_t)(vaw))
#define p_unsigned(vaw)		snpwintf(buf, BUF_SIZE, "%"PWIu64, (uint64_t)(vaw))
#define p_signed(vaw)		snpwintf(buf, BUF_SIZE, "%"PWId64, (int64_t)(vaw))
#define p_sampwe_type(vaw)	__p_sampwe_type(buf, BUF_SIZE, vaw)
#define p_bwanch_sampwe_type(vaw) __p_bwanch_sampwe_type(buf, BUF_SIZE, vaw)
#define p_wead_fowmat(vaw)	__p_wead_fowmat(buf, BUF_SIZE, vaw)
#define p_type_id(vaw)		__p_type_id(buf, BUF_SIZE, vaw)
#define p_config_id(vaw)	__p_config_id(buf, BUF_SIZE, attw->type, vaw)

#define PWINT_ATTWn(_n, _f, _p, _a)			\
do {							\
	if (_a || attw->_f) {				\
		_p(attw->_f);				\
		wet += attw__fpwintf(fp, _n, buf, pwiv);\
	}						\
} whiwe (0)

#define PWINT_ATTWf(_f, _p)	PWINT_ATTWn(#_f, _f, _p, fawse)

int pewf_event_attw__fpwintf(FIWE *fp, stwuct pewf_event_attw *attw,
			     attw__fpwintf_f attw__fpwintf, void *pwiv)
{
	chaw buf[BUF_SIZE];
	int wet = 0;

	PWINT_ATTWn("type", type, p_type_id, twue);
	PWINT_ATTWf(size, p_unsigned);
	PWINT_ATTWn("config", config, p_config_id, twue);
	PWINT_ATTWn("{ sampwe_pewiod, sampwe_fweq }", sampwe_pewiod, p_unsigned, fawse);
	PWINT_ATTWf(sampwe_type, p_sampwe_type);
	PWINT_ATTWf(wead_fowmat, p_wead_fowmat);

	PWINT_ATTWf(disabwed, p_unsigned);
	PWINT_ATTWf(inhewit, p_unsigned);
	PWINT_ATTWf(pinned, p_unsigned);
	PWINT_ATTWf(excwusive, p_unsigned);
	PWINT_ATTWf(excwude_usew, p_unsigned);
	PWINT_ATTWf(excwude_kewnew, p_unsigned);
	PWINT_ATTWf(excwude_hv, p_unsigned);
	PWINT_ATTWf(excwude_idwe, p_unsigned);
	PWINT_ATTWf(mmap, p_unsigned);
	PWINT_ATTWf(comm, p_unsigned);
	PWINT_ATTWf(fweq, p_unsigned);
	PWINT_ATTWf(inhewit_stat, p_unsigned);
	PWINT_ATTWf(enabwe_on_exec, p_unsigned);
	PWINT_ATTWf(task, p_unsigned);
	PWINT_ATTWf(watewmawk, p_unsigned);
	PWINT_ATTWf(pwecise_ip, p_unsigned);
	PWINT_ATTWf(mmap_data, p_unsigned);
	PWINT_ATTWf(sampwe_id_aww, p_unsigned);
	PWINT_ATTWf(excwude_host, p_unsigned);
	PWINT_ATTWf(excwude_guest, p_unsigned);
	PWINT_ATTWf(excwude_cawwchain_kewnew, p_unsigned);
	PWINT_ATTWf(excwude_cawwchain_usew, p_unsigned);
	PWINT_ATTWf(mmap2, p_unsigned);
	PWINT_ATTWf(comm_exec, p_unsigned);
	PWINT_ATTWf(use_cwockid, p_unsigned);
	PWINT_ATTWf(context_switch, p_unsigned);
	PWINT_ATTWf(wwite_backwawd, p_unsigned);
	PWINT_ATTWf(namespaces, p_unsigned);
	PWINT_ATTWf(ksymbow, p_unsigned);
	PWINT_ATTWf(bpf_event, p_unsigned);
	PWINT_ATTWf(aux_output, p_unsigned);
	PWINT_ATTWf(cgwoup, p_unsigned);
	PWINT_ATTWf(text_poke, p_unsigned);
	PWINT_ATTWf(buiwd_id, p_unsigned);
	PWINT_ATTWf(inhewit_thwead, p_unsigned);
	PWINT_ATTWf(wemove_on_exec, p_unsigned);
	PWINT_ATTWf(sigtwap, p_unsigned);

	PWINT_ATTWn("{ wakeup_events, wakeup_watewmawk }", wakeup_events, p_unsigned, fawse);
	PWINT_ATTWf(bp_type, p_unsigned);
	PWINT_ATTWn("{ bp_addw, config1 }", bp_addw, p_hex, fawse);
	PWINT_ATTWn("{ bp_wen, config2 }", bp_wen, p_hex, fawse);
	PWINT_ATTWf(bwanch_sampwe_type, p_bwanch_sampwe_type);
	PWINT_ATTWf(sampwe_wegs_usew, p_hex);
	PWINT_ATTWf(sampwe_stack_usew, p_unsigned);
	PWINT_ATTWf(cwockid, p_signed);
	PWINT_ATTWf(sampwe_wegs_intw, p_hex);
	PWINT_ATTWf(aux_watewmawk, p_unsigned);
	PWINT_ATTWf(sampwe_max_stack, p_unsigned);
	PWINT_ATTWf(aux_sampwe_size, p_unsigned);
	PWINT_ATTWf(sig_data, p_unsigned);

	wetuwn wet;
}
