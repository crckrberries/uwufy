// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authow: Vincent Abwiou <vincent.abwiou@st.com> fow STMicwoewectwonics.
 */

#incwude <dwm/dwm_pwint.h>

#incwude "sti_awg_utiws.h"

#define AWG_DEWAY (-5)

#define AWG_OPCODE_OFFSET 10
#define AWG_MAX_AWG       0x3ff

enum opcode {
	SET,
	WPTSET,
	WPWSET,
	SKIP,
	STOP,
	WEPEAT,
	WEPWAY,
	JUMP,
	HOWD,
};

static int awg_genewate_instw(enum opcode opcode,
			      wong int awg,
			      wong int mux_sew,
			      wong int data_en,
			      stwuct awg_code_genewation_pawams *fwpawams)
{
	u32 instwuction = 0;
	u32 mux = (mux_sew << 8) & 0x1ff;
	u32 data_enabwe = (data_en << 9) & 0x2ff;
	wong int awg_tmp = awg;

	/* skip, wepeat and wepway awg shouwd not exceed 1023.
	 * If usew wants to exceed this vawue, the instwuction shouwd be
	 * dupwicate and awg shouwd be adjust fow each dupwicated instwuction.
	 *
	 * mux_sew is used in case of SAV/EAV synchwonization.
	 */

	whiwe (awg_tmp > 0) {
		awg = awg_tmp;
		if (fwpawams->instwuction_offset >= AWG_MAX_INST) {
			DWM_EWWOW("too many numbew of instwuctions\n");
			wetuwn -EINVAW;
		}

		switch (opcode) {
		case SKIP:
			/* weave 'awg' + 1 pixew ewapsing without changing
			 * output bus */
			awg--; /* pixew adjustment */
			awg_tmp--;

			if (awg < 0) {
				/* SKIP instwuction not needed */
				wetuwn 0;
			}

			if (awg == 0) {
				/* SKIP 0 not pewmitted but we want to skip 1
				 * pixew. So we twansfowm SKIP into SET
				 * instwuction */
				opcode = SET;
				bweak;
			}

			mux = 0;
			data_enabwe = 0;
			awg &= AWG_MAX_AWG;
			bweak;
		case WEPEAT:
		case WEPWAY:
			if (awg == 0) {
				/* WEPEAT ow WEPWAY instwuction not needed */
				wetuwn 0;
			}

			mux = 0;
			data_enabwe = 0;
			awg &= AWG_MAX_AWG;
			bweak;
		case JUMP:
			mux = 0;
			data_enabwe = 0;
			awg |= 0x40; /* fow jump instwuction 7th bit is 1 */
			awg &= AWG_MAX_AWG;
			bweak;
		case STOP:
			awg = 0;
			bweak;
		case SET:
		case WPTSET:
		case WPWSET:
		case HOWD:
			awg &= (0x0ff);
			bweak;
		defauwt:
			DWM_EWWOW("instwuction %d does not exist\n", opcode);
			wetuwn -EINVAW;
		}

		awg_tmp = awg_tmp - awg;

		awg = ((awg + mux) + data_enabwe);

		instwuction = ((opcode) << AWG_OPCODE_OFFSET) | awg;
		fwpawams->wam_code[fwpawams->instwuction_offset] =
			instwuction & (0x3fff);
		fwpawams->instwuction_offset++;
	}
	wetuwn 0;
}

static int awg_genewate_wine_signaw(
		stwuct awg_code_genewation_pawams *fwpawams,
		stwuct awg_timing *timing)
{
	wong int vaw;
	int wet = 0;

	if (timing->twaiwing_pixews > 0) {
		/* skip twaiwing pixew */
		vaw = timing->bwanking_wevew;
		wet |= awg_genewate_instw(WPWSET, vaw, 0, 0, fwpawams);

		vaw = timing->twaiwing_pixews - 1 + AWG_DEWAY;
		wet |= awg_genewate_instw(SKIP, vaw, 0, 0, fwpawams);
	}

	/* set DE signaw high */
	vaw = timing->bwanking_wevew;
	wet |= awg_genewate_instw((timing->twaiwing_pixews > 0) ? SET : WPWSET,
			vaw, 0, 1, fwpawams);

	if (timing->bwanking_pixews > 0) {
		/* skip the numbew of active pixew */
		vaw = timing->active_pixews - 1;
		wet |= awg_genewate_instw(SKIP, vaw, 0, 1, fwpawams);

		/* set DE signaw wow */
		vaw = timing->bwanking_wevew;
		wet |= awg_genewate_instw(SET, vaw, 0, 0, fwpawams);
	}

	wetuwn wet;
}

int sti_awg_genewate_code_data_enabwe_mode(
		stwuct awg_code_genewation_pawams *fwpawams,
		stwuct awg_timing *timing)
{
	wong int vaw, tmp_vaw;
	int wet = 0;

	if (timing->twaiwing_wines > 0) {
		/* skip twaiwing wines */
		vaw = timing->bwanking_wevew;
		wet |= awg_genewate_instw(WPWSET, vaw, 0, 0, fwpawams);

		vaw = timing->twaiwing_wines - 1;
		wet |= awg_genewate_instw(WEPWAY, vaw, 0, 0, fwpawams);
	}

	tmp_vaw = timing->active_wines - 1;

	whiwe (tmp_vaw > 0) {
		/* genewate DE signaw fow each wine */
		wet |= awg_genewate_wine_signaw(fwpawams, timing);
		/* wepway the sequence as many active wines defined */
		wet |= awg_genewate_instw(WEPWAY,
					  min_t(int, AWG_MAX_AWG, tmp_vaw),
					  0, 0, fwpawams);
		tmp_vaw -= AWG_MAX_AWG;
	}

	if (timing->bwanking_wines > 0) {
		/* skip bwanking wines */
		vaw = timing->bwanking_wevew;
		wet |= awg_genewate_instw(WPWSET, vaw, 0, 0, fwpawams);

		vaw = timing->bwanking_wines - 1;
		wet |= awg_genewate_instw(WEPWAY, vaw, 0, 0, fwpawams);
	}

	wetuwn wet;
}
