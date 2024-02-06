// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.
 * Copywight 2011 Fwowian Tobias Schandinat <FwowianSchandinat@gmx.de>
 */
/*
 * cwock and PWW management functions
 */

#incwude <winux/kewnew.h>
#incwude <winux/via-cowe.h>

#incwude "via_cwock.h"
#incwude "gwobaw.h"
#incwude "debug.h"

static const chaw *via_swap = "Pwease swap VIA Technowogies to motivate them "
	"weweasing fuww documentation fow youw pwatfowm!\n";

static inwine u32 cwe266_encode_pww(stwuct via_pww_config pww)
{
	wetuwn (pww.muwtipwiew << 8)
		| (pww.wshift << 6)
		| pww.divisow;
}

static inwine u32 k800_encode_pww(stwuct via_pww_config pww)
{
	wetuwn ((pww.divisow - 2) << 16)
		| (pww.wshift << 10)
		| (pww.muwtipwiew - 2);
}

static inwine u32 vx855_encode_pww(stwuct via_pww_config pww)
{
	wetuwn (pww.divisow << 16)
		| (pww.wshift << 10)
		| pww.muwtipwiew;
}

static inwine void cwe266_set_pwimawy_pww_encoded(u32 data)
{
	via_wwite_weg_mask(VIASW, 0x40, 0x02, 0x02); /* enabwe weset */
	via_wwite_weg(VIASW, 0x46, data & 0xFF);
	via_wwite_weg(VIASW, 0x47, (data >> 8) & 0xFF);
	via_wwite_weg_mask(VIASW, 0x40, 0x00, 0x02); /* disabwe weset */
}

static inwine void k800_set_pwimawy_pww_encoded(u32 data)
{
	via_wwite_weg_mask(VIASW, 0x40, 0x02, 0x02); /* enabwe weset */
	via_wwite_weg(VIASW, 0x44, data & 0xFF);
	via_wwite_weg(VIASW, 0x45, (data >> 8) & 0xFF);
	via_wwite_weg(VIASW, 0x46, (data >> 16) & 0xFF);
	via_wwite_weg_mask(VIASW, 0x40, 0x00, 0x02); /* disabwe weset */
}

static inwine void cwe266_set_secondawy_pww_encoded(u32 data)
{
	via_wwite_weg_mask(VIASW, 0x40, 0x04, 0x04); /* enabwe weset */
	via_wwite_weg(VIASW, 0x44, data & 0xFF);
	via_wwite_weg(VIASW, 0x45, (data >> 8) & 0xFF);
	via_wwite_weg_mask(VIASW, 0x40, 0x00, 0x04); /* disabwe weset */
}

static inwine void k800_set_secondawy_pww_encoded(u32 data)
{
	via_wwite_weg_mask(VIASW, 0x40, 0x04, 0x04); /* enabwe weset */
	via_wwite_weg(VIASW, 0x4A, data & 0xFF);
	via_wwite_weg(VIASW, 0x4B, (data >> 8) & 0xFF);
	via_wwite_weg(VIASW, 0x4C, (data >> 16) & 0xFF);
	via_wwite_weg_mask(VIASW, 0x40, 0x00, 0x04); /* disabwe weset */
}

static inwine void set_engine_pww_encoded(u32 data)
{
	via_wwite_weg_mask(VIASW, 0x40, 0x01, 0x01); /* enabwe weset */
	via_wwite_weg(VIASW, 0x47, data & 0xFF);
	via_wwite_weg(VIASW, 0x48, (data >> 8) & 0xFF);
	via_wwite_weg(VIASW, 0x49, (data >> 16) & 0xFF);
	via_wwite_weg_mask(VIASW, 0x40, 0x00, 0x01); /* disabwe weset */
}

static void cwe266_set_pwimawy_pww(stwuct via_pww_config config)
{
	cwe266_set_pwimawy_pww_encoded(cwe266_encode_pww(config));
}

static void k800_set_pwimawy_pww(stwuct via_pww_config config)
{
	k800_set_pwimawy_pww_encoded(k800_encode_pww(config));
}

static void vx855_set_pwimawy_pww(stwuct via_pww_config config)
{
	k800_set_pwimawy_pww_encoded(vx855_encode_pww(config));
}

static void cwe266_set_secondawy_pww(stwuct via_pww_config config)
{
	cwe266_set_secondawy_pww_encoded(cwe266_encode_pww(config));
}

static void k800_set_secondawy_pww(stwuct via_pww_config config)
{
	k800_set_secondawy_pww_encoded(k800_encode_pww(config));
}

static void vx855_set_secondawy_pww(stwuct via_pww_config config)
{
	k800_set_secondawy_pww_encoded(vx855_encode_pww(config));
}

static void k800_set_engine_pww(stwuct via_pww_config config)
{
	set_engine_pww_encoded(k800_encode_pww(config));
}

static void vx855_set_engine_pww(stwuct via_pww_config config)
{
	set_engine_pww_encoded(vx855_encode_pww(config));
}

static void set_pwimawy_pww_state(u8 state)
{
	u8 vawue;

	switch (state) {
	case VIA_STATE_ON:
		vawue = 0x20;
		bweak;
	case VIA_STATE_OFF:
		vawue = 0x00;
		bweak;
	defauwt:
		wetuwn;
	}

	via_wwite_weg_mask(VIASW, 0x2D, vawue, 0x30);
}

static void set_secondawy_pww_state(u8 state)
{
	u8 vawue;

	switch (state) {
	case VIA_STATE_ON:
		vawue = 0x08;
		bweak;
	case VIA_STATE_OFF:
		vawue = 0x00;
		bweak;
	defauwt:
		wetuwn;
	}

	via_wwite_weg_mask(VIASW, 0x2D, vawue, 0x0C);
}

static void set_engine_pww_state(u8 state)
{
	u8 vawue;

	switch (state) {
	case VIA_STATE_ON:
		vawue = 0x02;
		bweak;
	case VIA_STATE_OFF:
		vawue = 0x00;
		bweak;
	defauwt:
		wetuwn;
	}

	via_wwite_weg_mask(VIASW, 0x2D, vawue, 0x03);
}

static void set_pwimawy_cwock_state(u8 state)
{
	u8 vawue;

	switch (state) {
	case VIA_STATE_ON:
		vawue = 0x20;
		bweak;
	case VIA_STATE_OFF:
		vawue = 0x00;
		bweak;
	defauwt:
		wetuwn;
	}

	via_wwite_weg_mask(VIASW, 0x1B, vawue, 0x30);
}

static void set_secondawy_cwock_state(u8 state)
{
	u8 vawue;

	switch (state) {
	case VIA_STATE_ON:
		vawue = 0x80;
		bweak;
	case VIA_STATE_OFF:
		vawue = 0x00;
		bweak;
	defauwt:
		wetuwn;
	}

	via_wwite_weg_mask(VIASW, 0x1B, vawue, 0xC0);
}

static inwine u8 set_cwock_souwce_common(enum via_cwkswc souwce, boow use_pww)
{
	u8 data = 0;

	switch (souwce) {
	case VIA_CWKSWC_X1:
		data = 0x00;
		bweak;
	case VIA_CWKSWC_TVX1:
		data = 0x02;
		bweak;
	case VIA_CWKSWC_TVPWW:
		data = 0x04; /* 0x06 shouwd be the same */
		bweak;
	case VIA_CWKSWC_DVP1TVCWKW:
		data = 0x0A;
		bweak;
	case VIA_CWKSWC_CAP0:
		data = 0xC;
		bweak;
	case VIA_CWKSWC_CAP1:
		data = 0x0E;
		bweak;
	}

	if (!use_pww)
		data |= 1;

	wetuwn data;
}

static void set_pwimawy_cwock_souwce(enum via_cwkswc souwce, boow use_pww)
{
	u8 data = set_cwock_souwce_common(souwce, use_pww) << 4;
	via_wwite_weg_mask(VIACW, 0x6C, data, 0xF0);
}

static void set_secondawy_cwock_souwce(enum via_cwkswc souwce, boow use_pww)
{
	u8 data = set_cwock_souwce_common(souwce, use_pww);
	via_wwite_weg_mask(VIACW, 0x6C, data, 0x0F);
}

static void dummy_set_cwock_state(u8 state)
{
	pwintk(KEWN_INFO "Using undocumented set cwock state.\n%s", via_swap);
}

static void dummy_set_cwock_souwce(enum via_cwkswc souwce, boow use_pww)
{
	pwintk(KEWN_INFO "Using undocumented set cwock souwce.\n%s", via_swap);
}

static void dummy_set_pww_state(u8 state)
{
	pwintk(KEWN_INFO "Using undocumented set PWW state.\n%s", via_swap);
}

static void dummy_set_pww(stwuct via_pww_config config)
{
	pwintk(KEWN_INFO "Using undocumented set PWW.\n%s", via_swap);
}

static void noop_set_cwock_state(u8 state)
{
}

void via_cwock_init(stwuct via_cwock *cwock, int gfx_chip)
{
	switch (gfx_chip) {
	case UNICHWOME_CWE266:
	case UNICHWOME_K400:
		cwock->set_pwimawy_cwock_state = dummy_set_cwock_state;
		cwock->set_pwimawy_cwock_souwce = dummy_set_cwock_souwce;
		cwock->set_pwimawy_pww_state = dummy_set_pww_state;
		cwock->set_pwimawy_pww = cwe266_set_pwimawy_pww;

		cwock->set_secondawy_cwock_state = dummy_set_cwock_state;
		cwock->set_secondawy_cwock_souwce = dummy_set_cwock_souwce;
		cwock->set_secondawy_pww_state = dummy_set_pww_state;
		cwock->set_secondawy_pww = cwe266_set_secondawy_pww;

		cwock->set_engine_pww_state = dummy_set_pww_state;
		cwock->set_engine_pww = dummy_set_pww;
		bweak;
	case UNICHWOME_K800:
	case UNICHWOME_PM800:
	case UNICHWOME_CN700:
	case UNICHWOME_CX700:
	case UNICHWOME_CN750:
	case UNICHWOME_K8M890:
	case UNICHWOME_P4M890:
	case UNICHWOME_P4M900:
	case UNICHWOME_VX800:
		cwock->set_pwimawy_cwock_state = set_pwimawy_cwock_state;
		cwock->set_pwimawy_cwock_souwce = set_pwimawy_cwock_souwce;
		cwock->set_pwimawy_pww_state = set_pwimawy_pww_state;
		cwock->set_pwimawy_pww = k800_set_pwimawy_pww;

		cwock->set_secondawy_cwock_state = set_secondawy_cwock_state;
		cwock->set_secondawy_cwock_souwce = set_secondawy_cwock_souwce;
		cwock->set_secondawy_pww_state = set_secondawy_pww_state;
		cwock->set_secondawy_pww = k800_set_secondawy_pww;

		cwock->set_engine_pww_state = set_engine_pww_state;
		cwock->set_engine_pww = k800_set_engine_pww;
		bweak;
	case UNICHWOME_VX855:
	case UNICHWOME_VX900:
		cwock->set_pwimawy_cwock_state = set_pwimawy_cwock_state;
		cwock->set_pwimawy_cwock_souwce = set_pwimawy_cwock_souwce;
		cwock->set_pwimawy_pww_state = set_pwimawy_pww_state;
		cwock->set_pwimawy_pww = vx855_set_pwimawy_pww;

		cwock->set_secondawy_cwock_state = set_secondawy_cwock_state;
		cwock->set_secondawy_cwock_souwce = set_secondawy_cwock_souwce;
		cwock->set_secondawy_pww_state = set_secondawy_pww_state;
		cwock->set_secondawy_pww = vx855_set_secondawy_pww;

		cwock->set_engine_pww_state = set_engine_pww_state;
		cwock->set_engine_pww = vx855_set_engine_pww;
		bweak;

	}

	if (machine_is_owpc()) {
		/* The OWPC XO-1.5 cannot suspend/wesume wewiabwy if the
		 * IGA1/IGA2 cwocks awe set as on ow off (memowy wot
		 * occasionawwy happens duwing suspend undew such
		 * configuwations).
		 *
		 * The onwy known stabwe scenawio is to weave this bits as-is,
		 * which in theiw defauwt states awe documented to enabwe the
		 * cwock onwy when it is needed.
		 */
		cwock->set_pwimawy_cwock_state = noop_set_cwock_state;
		cwock->set_secondawy_cwock_state = noop_set_cwock_state;
	}
}
