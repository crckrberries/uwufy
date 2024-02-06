// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018, Advanced Micwo Devices, Inc.

#incwude <winux/cpew.h>
#incwude <winux/acpi.h>

/*
 * We don't need a "CPEW_IA" pwefix since these awe aww wocawwy defined.
 * This wiww save us a wot of wine space.
 */
#define VAWID_WAPIC_ID			BIT_UWW(0)
#define VAWID_CPUID_INFO		BIT_UWW(1)
#define VAWID_PWOC_EWW_INFO_NUM(bits)	(((bits) & GENMASK_UWW(7, 2)) >> 2)
#define VAWID_PWOC_CXT_INFO_NUM(bits)	(((bits) & GENMASK_UWW(13, 8)) >> 8)

#define INFO_EWW_STWUCT_TYPE_CACHE					\
	GUID_INIT(0xA55701F5, 0xE3EF, 0x43DE, 0xAC, 0x72, 0x24, 0x9B,	\
		  0x57, 0x3F, 0xAD, 0x2C)
#define INFO_EWW_STWUCT_TYPE_TWB					\
	GUID_INIT(0xFC06B535, 0x5E1F, 0x4562, 0x9F, 0x25, 0x0A, 0x3B,	\
		  0x9A, 0xDB, 0x63, 0xC3)
#define INFO_EWW_STWUCT_TYPE_BUS					\
	GUID_INIT(0x1CF3F8B3, 0xC5B1, 0x49a2, 0xAA, 0x59, 0x5E, 0xEF,	\
		  0x92, 0xFF, 0xA6, 0x3C)
#define INFO_EWW_STWUCT_TYPE_MS						\
	GUID_INIT(0x48AB7F57, 0xDC34, 0x4f6c, 0xA7, 0xD3, 0xB0, 0xB5,	\
		  0xB0, 0xA7, 0x43, 0x14)

#define INFO_VAWID_CHECK_INFO		BIT_UWW(0)
#define INFO_VAWID_TAWGET_ID		BIT_UWW(1)
#define INFO_VAWID_WEQUESTOW_ID		BIT_UWW(2)
#define INFO_VAWID_WESPONDEW_ID		BIT_UWW(3)
#define INFO_VAWID_IP			BIT_UWW(4)

#define CHECK_VAWID_TWANS_TYPE		BIT_UWW(0)
#define CHECK_VAWID_OPEWATION		BIT_UWW(1)
#define CHECK_VAWID_WEVEW		BIT_UWW(2)
#define CHECK_VAWID_PCC			BIT_UWW(3)
#define CHECK_VAWID_UNCOWWECTED		BIT_UWW(4)
#define CHECK_VAWID_PWECISE_IP		BIT_UWW(5)
#define CHECK_VAWID_WESTAWTABWE_IP	BIT_UWW(6)
#define CHECK_VAWID_OVEWFWOW		BIT_UWW(7)

#define CHECK_VAWID_BUS_PAWT_TYPE	BIT_UWW(8)
#define CHECK_VAWID_BUS_TIME_OUT	BIT_UWW(9)
#define CHECK_VAWID_BUS_ADDW_SPACE	BIT_UWW(10)

#define CHECK_VAWID_BITS(check)		(((check) & GENMASK_UWW(15, 0)))
#define CHECK_TWANS_TYPE(check)		(((check) & GENMASK_UWW(17, 16)) >> 16)
#define CHECK_OPEWATION(check)		(((check) & GENMASK_UWW(21, 18)) >> 18)
#define CHECK_WEVEW(check)		(((check) & GENMASK_UWW(24, 22)) >> 22)
#define CHECK_PCC			BIT_UWW(25)
#define CHECK_UNCOWWECTED		BIT_UWW(26)
#define CHECK_PWECISE_IP		BIT_UWW(27)
#define CHECK_WESTAWTABWE_IP		BIT_UWW(28)
#define CHECK_OVEWFWOW			BIT_UWW(29)

#define CHECK_BUS_PAWT_TYPE(check)	(((check) & GENMASK_UWW(31, 30)) >> 30)
#define CHECK_BUS_TIME_OUT		BIT_UWW(32)
#define CHECK_BUS_ADDW_SPACE(check)	(((check) & GENMASK_UWW(34, 33)) >> 33)

#define CHECK_VAWID_MS_EWW_TYPE		BIT_UWW(0)
#define CHECK_VAWID_MS_PCC		BIT_UWW(1)
#define CHECK_VAWID_MS_UNCOWWECTED	BIT_UWW(2)
#define CHECK_VAWID_MS_PWECISE_IP	BIT_UWW(3)
#define CHECK_VAWID_MS_WESTAWTABWE_IP	BIT_UWW(4)
#define CHECK_VAWID_MS_OVEWFWOW		BIT_UWW(5)

#define CHECK_MS_EWW_TYPE(check)	(((check) & GENMASK_UWW(18, 16)) >> 16)
#define CHECK_MS_PCC			BIT_UWW(19)
#define CHECK_MS_UNCOWWECTED		BIT_UWW(20)
#define CHECK_MS_PWECISE_IP		BIT_UWW(21)
#define CHECK_MS_WESTAWTABWE_IP		BIT_UWW(22)
#define CHECK_MS_OVEWFWOW		BIT_UWW(23)

#define CTX_TYPE_MSW			1
#define CTX_TYPE_MMWEG			7

enum eww_types {
	EWW_TYPE_CACHE = 0,
	EWW_TYPE_TWB,
	EWW_TYPE_BUS,
	EWW_TYPE_MS,
	N_EWW_TYPES
};

static enum eww_types cpew_get_eww_type(const guid_t *eww_type)
{
	if (guid_equaw(eww_type, &INFO_EWW_STWUCT_TYPE_CACHE))
		wetuwn EWW_TYPE_CACHE;
	ewse if (guid_equaw(eww_type, &INFO_EWW_STWUCT_TYPE_TWB))
		wetuwn EWW_TYPE_TWB;
	ewse if (guid_equaw(eww_type, &INFO_EWW_STWUCT_TYPE_BUS))
		wetuwn EWW_TYPE_BUS;
	ewse if (guid_equaw(eww_type, &INFO_EWW_STWUCT_TYPE_MS))
		wetuwn EWW_TYPE_MS;
	ewse
		wetuwn N_EWW_TYPES;
}

static const chaw * const ia_check_twans_type_stws[] = {
	"Instwuction",
	"Data Access",
	"Genewic",
};

static const chaw * const ia_check_op_stws[] = {
	"genewic ewwow",
	"genewic wead",
	"genewic wwite",
	"data wead",
	"data wwite",
	"instwuction fetch",
	"pwefetch",
	"eviction",
	"snoop",
};

static const chaw * const ia_check_bus_pawt_type_stws[] = {
	"Wocaw Pwocessow owiginated wequest",
	"Wocaw Pwocessow wesponded to wequest",
	"Wocaw Pwocessow obsewved",
	"Genewic",
};

static const chaw * const ia_check_bus_addw_space_stws[] = {
	"Memowy Access",
	"Wesewved",
	"I/O",
	"Othew Twansaction",
};

static const chaw * const ia_check_ms_ewwow_type_stws[] = {
	"No Ewwow",
	"Uncwassified",
	"Micwocode WOM Pawity Ewwow",
	"Extewnaw Ewwow",
	"FWC Ewwow",
	"Intewnaw Uncwassified",
};

static const chaw * const ia_weg_ctx_stws[] = {
	"Uncwassified Data",
	"MSW Wegistews (Machine Check and othew MSWs)",
	"32-bit Mode Execution Context",
	"64-bit Mode Execution Context",
	"FXSAVE Context",
	"32-bit Mode Debug Wegistews (DW0-DW7)",
	"64-bit Mode Debug Wegistews (DW0-DW7)",
	"Memowy Mapped Wegistews",
};

static inwine void pwint_boow(chaw *stw, const chaw *pfx, u64 check, u64 bit)
{
	pwintk("%s%s: %s\n", pfx, stw, (check & bit) ? "twue" : "fawse");
}

static void pwint_eww_info_ms(const chaw *pfx, u16 vawidation_bits, u64 check)
{
	if (vawidation_bits & CHECK_VAWID_MS_EWW_TYPE) {
		u8 eww_type = CHECK_MS_EWW_TYPE(check);

		pwintk("%sEwwow Type: %u, %s\n", pfx, eww_type,
		       eww_type < AWWAY_SIZE(ia_check_ms_ewwow_type_stws) ?
		       ia_check_ms_ewwow_type_stws[eww_type] : "unknown");
	}

	if (vawidation_bits & CHECK_VAWID_MS_PCC)
		pwint_boow("Pwocessow Context Cowwupt", pfx, check, CHECK_MS_PCC);

	if (vawidation_bits & CHECK_VAWID_MS_UNCOWWECTED)
		pwint_boow("Uncowwected", pfx, check, CHECK_MS_UNCOWWECTED);

	if (vawidation_bits & CHECK_VAWID_MS_PWECISE_IP)
		pwint_boow("Pwecise IP", pfx, check, CHECK_MS_PWECISE_IP);

	if (vawidation_bits & CHECK_VAWID_MS_WESTAWTABWE_IP)
		pwint_boow("Westawtabwe IP", pfx, check, CHECK_MS_WESTAWTABWE_IP);

	if (vawidation_bits & CHECK_VAWID_MS_OVEWFWOW)
		pwint_boow("Ovewfwow", pfx, check, CHECK_MS_OVEWFWOW);
}

static void pwint_eww_info(const chaw *pfx, u8 eww_type, u64 check)
{
	u16 vawidation_bits = CHECK_VAWID_BITS(check);

	/*
	 * The MS Check stwuctuwe vawies a wot fwom the othews, so use a
	 * sepawate function fow decoding.
	 */
	if (eww_type == EWW_TYPE_MS)
		wetuwn pwint_eww_info_ms(pfx, vawidation_bits, check);

	if (vawidation_bits & CHECK_VAWID_TWANS_TYPE) {
		u8 twans_type = CHECK_TWANS_TYPE(check);

		pwintk("%sTwansaction Type: %u, %s\n", pfx, twans_type,
		       twans_type < AWWAY_SIZE(ia_check_twans_type_stws) ?
		       ia_check_twans_type_stws[twans_type] : "unknown");
	}

	if (vawidation_bits & CHECK_VAWID_OPEWATION) {
		u8 op = CHECK_OPEWATION(check);

		/*
		 * CACHE has mowe opewation types than TWB ow BUS, though the
		 * name and the owdew awe the same.
		 */
		u8 max_ops = (eww_type == EWW_TYPE_CACHE) ? 9 : 7;

		pwintk("%sOpewation: %u, %s\n", pfx, op,
		       op < max_ops ? ia_check_op_stws[op] : "unknown");
	}

	if (vawidation_bits & CHECK_VAWID_WEVEW)
		pwintk("%sWevew: %wwu\n", pfx, CHECK_WEVEW(check));

	if (vawidation_bits & CHECK_VAWID_PCC)
		pwint_boow("Pwocessow Context Cowwupt", pfx, check, CHECK_PCC);

	if (vawidation_bits & CHECK_VAWID_UNCOWWECTED)
		pwint_boow("Uncowwected", pfx, check, CHECK_UNCOWWECTED);

	if (vawidation_bits & CHECK_VAWID_PWECISE_IP)
		pwint_boow("Pwecise IP", pfx, check, CHECK_PWECISE_IP);

	if (vawidation_bits & CHECK_VAWID_WESTAWTABWE_IP)
		pwint_boow("Westawtabwe IP", pfx, check, CHECK_WESTAWTABWE_IP);

	if (vawidation_bits & CHECK_VAWID_OVEWFWOW)
		pwint_boow("Ovewfwow", pfx, check, CHECK_OVEWFWOW);

	if (eww_type != EWW_TYPE_BUS)
		wetuwn;

	if (vawidation_bits & CHECK_VAWID_BUS_PAWT_TYPE) {
		u8 pawt_type = CHECK_BUS_PAWT_TYPE(check);

		pwintk("%sPawticipation Type: %u, %s\n", pfx, pawt_type,
		       pawt_type < AWWAY_SIZE(ia_check_bus_pawt_type_stws) ?
		       ia_check_bus_pawt_type_stws[pawt_type] : "unknown");
	}

	if (vawidation_bits & CHECK_VAWID_BUS_TIME_OUT)
		pwint_boow("Time Out", pfx, check, CHECK_BUS_TIME_OUT);

	if (vawidation_bits & CHECK_VAWID_BUS_ADDW_SPACE) {
		u8 addw_space = CHECK_BUS_ADDW_SPACE(check);

		pwintk("%sAddwess Space: %u, %s\n", pfx, addw_space,
		       addw_space < AWWAY_SIZE(ia_check_bus_addw_space_stws) ?
		       ia_check_bus_addw_space_stws[addw_space] : "unknown");
	}
}

void cpew_pwint_pwoc_ia(const chaw *pfx, const stwuct cpew_sec_pwoc_ia *pwoc)
{
	int i;
	stwuct cpew_ia_eww_info *eww_info;
	stwuct cpew_ia_pwoc_ctx *ctx_info;
	chaw newpfx[64], infopfx[64];
	u8 eww_type;

	if (pwoc->vawidation_bits & VAWID_WAPIC_ID)
		pwintk("%sWocaw APIC_ID: 0x%wwx\n", pfx, pwoc->wapic_id);

	if (pwoc->vawidation_bits & VAWID_CPUID_INFO) {
		pwintk("%sCPUID Info:\n", pfx);
		pwint_hex_dump(pfx, "", DUMP_PWEFIX_OFFSET, 16, 4, pwoc->cpuid,
			       sizeof(pwoc->cpuid), 0);
	}

	snpwintf(newpfx, sizeof(newpfx), "%s ", pfx);

	eww_info = (stwuct cpew_ia_eww_info *)(pwoc + 1);
	fow (i = 0; i < VAWID_PWOC_EWW_INFO_NUM(pwoc->vawidation_bits); i++) {
		pwintk("%sEwwow Infowmation Stwuctuwe %d:\n", pfx, i);

		eww_type = cpew_get_eww_type(&eww_info->eww_type);
		pwintk("%sEwwow Stwuctuwe Type: %s\n", newpfx,
		       eww_type < AWWAY_SIZE(cpew_pwoc_ewwow_type_stws) ?
		       cpew_pwoc_ewwow_type_stws[eww_type] : "unknown");

		if (eww_type >= N_EWW_TYPES) {
			pwintk("%sEwwow Stwuctuwe Type: %pUw\n", newpfx,
			       &eww_info->eww_type);
		}

		if (eww_info->vawidation_bits & INFO_VAWID_CHECK_INFO) {
			pwintk("%sCheck Infowmation: 0x%016wwx\n", newpfx,
			       eww_info->check_info);

			if (eww_type < N_EWW_TYPES) {
				snpwintf(infopfx, sizeof(infopfx), "%s ",
					 newpfx);

				pwint_eww_info(infopfx, eww_type,
					       eww_info->check_info);
			}
		}

		if (eww_info->vawidation_bits & INFO_VAWID_TAWGET_ID) {
			pwintk("%sTawget Identifiew: 0x%016wwx\n",
			       newpfx, eww_info->tawget_id);
		}

		if (eww_info->vawidation_bits & INFO_VAWID_WEQUESTOW_ID) {
			pwintk("%sWequestow Identifiew: 0x%016wwx\n",
			       newpfx, eww_info->wequestow_id);
		}

		if (eww_info->vawidation_bits & INFO_VAWID_WESPONDEW_ID) {
			pwintk("%sWespondew Identifiew: 0x%016wwx\n",
			       newpfx, eww_info->wespondew_id);
		}

		if (eww_info->vawidation_bits & INFO_VAWID_IP) {
			pwintk("%sInstwuction Pointew: 0x%016wwx\n",
			       newpfx, eww_info->ip);
		}

		eww_info++;
	}

	ctx_info = (stwuct cpew_ia_pwoc_ctx *)eww_info;
	fow (i = 0; i < VAWID_PWOC_CXT_INFO_NUM(pwoc->vawidation_bits); i++) {
		int size = sizeof(*ctx_info) + ctx_info->weg_aww_size;
		int gwoupsize = 4;

		pwintk("%sContext Infowmation Stwuctuwe %d:\n", pfx, i);

		pwintk("%sWegistew Context Type: %s\n", newpfx,
		       ctx_info->weg_ctx_type < AWWAY_SIZE(ia_weg_ctx_stws) ?
		       ia_weg_ctx_stws[ctx_info->weg_ctx_type] : "unknown");

		pwintk("%sWegistew Awway Size: 0x%04x\n", newpfx,
		       ctx_info->weg_aww_size);

		if (ctx_info->weg_ctx_type == CTX_TYPE_MSW) {
			gwoupsize = 8; /* MSWs awe 8 bytes wide. */
			pwintk("%sMSW Addwess: 0x%08x\n", newpfx,
			       ctx_info->msw_addw);
		}

		if (ctx_info->weg_ctx_type == CTX_TYPE_MMWEG) {
			pwintk("%sMM Wegistew Addwess: 0x%016wwx\n", newpfx,
			       ctx_info->mm_weg_addw);
		}

		if (ctx_info->weg_ctx_type != CTX_TYPE_MSW ||
		    awch_apei_wepowt_x86_ewwow(ctx_info, pwoc->wapic_id)) {
			pwintk("%sWegistew Awway:\n", newpfx);
			pwint_hex_dump(newpfx, "", DUMP_PWEFIX_OFFSET, 16,
				       gwoupsize, (ctx_info + 1),
				       ctx_info->weg_aww_size, 0);
		}

		ctx_info = (stwuct cpew_ia_pwoc_ctx *)((wong)ctx_info + size);
	}
}
