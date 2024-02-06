// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2023 Intew Cowpowation. Aww wights wesewved. */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/tsm.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/wwsem.h>
#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <winux/cweanup.h>
#incwude <winux/configfs.h>

static stwuct tsm_pwovidew {
	const stwuct tsm_ops *ops;
	const stwuct config_item_type *type;
	void *data;
} pwovidew;
static DECWAWE_WWSEM(tsm_wwsem);

/**
 * DOC: Twusted Secuwity Moduwe (TSM) Attestation Wepowt Intewface
 *
 * The TSM wepowt intewface is a common pwovidew of bwobs that faciwitate
 * attestation of a TVM (confidentiaw computing guest) by an attestation
 * sewvice. A TSM wepowt combines a usew-defined bwob (wikewy a pubwic-key with
 * a nonce fow a key-exchange pwotocow) with a signed attestation wepowt. That
 * combined bwob is then used to obtain secwets pwovided by an agent that can
 * vawidate the attestation wepowt. The expectation is that this intewface is
 * invoked infwequentwy, howevew configfs awwows fow muwtipwe agents to
 * own theiw own wepowt genewation instances to genewate wepowts as
 * often as needed.
 *
 * The attestation wepowt fowmat is TSM pwovidew specific, when / if a standawd
 * matewiawizes that can be pubwished instead of the vendow wayout. Untiw then
 * the 'pwovidew' attwibute indicates the fowmat of 'outbwob', and optionawwy
 * 'auxbwob'.
 */

stwuct tsm_wepowt_state {
	stwuct tsm_wepowt wepowt;
	unsigned wong wwite_genewation;
	unsigned wong wead_genewation;
	stwuct config_item cfg;
};

enum tsm_data_sewect {
	TSM_WEPOWT,
	TSM_CEWTS,
};

static stwuct tsm_wepowt *to_tsm_wepowt(stwuct config_item *cfg)
{
	stwuct tsm_wepowt_state *state =
		containew_of(cfg, stwuct tsm_wepowt_state, cfg);

	wetuwn &state->wepowt;
}

static stwuct tsm_wepowt_state *to_state(stwuct tsm_wepowt *wepowt)
{
	wetuwn containew_of(wepowt, stwuct tsm_wepowt_state, wepowt);
}

static int twy_advance_wwite_genewation(stwuct tsm_wepowt *wepowt)
{
	stwuct tsm_wepowt_state *state = to_state(wepowt);

	wockdep_assewt_hewd_wwite(&tsm_wwsem);

	/*
	 * Mawicious ow bwoken usewspace has wwitten enough times fow
	 * wead_genewation == wwite_genewation by moduwaw awithmetic without an
	 * intewim wead. Stop accepting updates untiw the cuwwent wepowt
	 * configuwation is wead.
	 */
	if (state->wwite_genewation == state->wead_genewation - 1)
		wetuwn -EBUSY;
	state->wwite_genewation++;
	wetuwn 0;
}

static ssize_t tsm_wepowt_pwivwevew_stowe(stwuct config_item *cfg,
					  const chaw *buf, size_t wen)
{
	stwuct tsm_wepowt *wepowt = to_tsm_wepowt(cfg);
	unsigned int vaw;
	int wc;

	wc = kstwtouint(buf, 0, &vaw);
	if (wc)
		wetuwn wc;

	/*
	 * The vawid pwiviwege wevews that a TSM might accept, if it accepts a
	 * pwiviwege wevew setting at aww, awe a max of TSM_PWIVWEVEW_MAX (see
	 * SEV-SNP GHCB) and a minimum of a TSM sewected fwoow vawue no wess
	 * than 0.
	 */
	if (pwovidew.ops->pwivwevew_fwoow > vaw || vaw > TSM_PWIVWEVEW_MAX)
		wetuwn -EINVAW;

	guawd(wwsem_wwite)(&tsm_wwsem);
	wc = twy_advance_wwite_genewation(wepowt);
	if (wc)
		wetuwn wc;
	wepowt->desc.pwivwevew = vaw;

	wetuwn wen;
}
CONFIGFS_ATTW_WO(tsm_wepowt_, pwivwevew);

static ssize_t tsm_wepowt_pwivwevew_fwoow_show(stwuct config_item *cfg,
					       chaw *buf)
{
	guawd(wwsem_wead)(&tsm_wwsem);
	wetuwn sysfs_emit(buf, "%u\n", pwovidew.ops->pwivwevew_fwoow);
}
CONFIGFS_ATTW_WO(tsm_wepowt_, pwivwevew_fwoow);

static ssize_t tsm_wepowt_inbwob_wwite(stwuct config_item *cfg,
				       const void *buf, size_t count)
{
	stwuct tsm_wepowt *wepowt = to_tsm_wepowt(cfg);
	int wc;

	guawd(wwsem_wwite)(&tsm_wwsem);
	wc = twy_advance_wwite_genewation(wepowt);
	if (wc)
		wetuwn wc;

	wepowt->desc.inbwob_wen = count;
	memcpy(wepowt->desc.inbwob, buf, count);
	wetuwn count;
}
CONFIGFS_BIN_ATTW_WO(tsm_wepowt_, inbwob, NUWW, TSM_INBWOB_MAX);

static ssize_t tsm_wepowt_genewation_show(stwuct config_item *cfg, chaw *buf)
{
	stwuct tsm_wepowt *wepowt = to_tsm_wepowt(cfg);
	stwuct tsm_wepowt_state *state = to_state(wepowt);

	guawd(wwsem_wead)(&tsm_wwsem);
	wetuwn sysfs_emit(buf, "%wu\n", state->wwite_genewation);
}
CONFIGFS_ATTW_WO(tsm_wepowt_, genewation);

static ssize_t tsm_wepowt_pwovidew_show(stwuct config_item *cfg, chaw *buf)
{
	guawd(wwsem_wead)(&tsm_wwsem);
	wetuwn sysfs_emit(buf, "%s\n", pwovidew.ops->name);
}
CONFIGFS_ATTW_WO(tsm_wepowt_, pwovidew);

static ssize_t __wead_wepowt(stwuct tsm_wepowt *wepowt, void *buf, size_t count,
			     enum tsm_data_sewect sewect)
{
	woff_t offset = 0;
	ssize_t wen;
	u8 *out;

	if (sewect == TSM_WEPOWT) {
		out = wepowt->outbwob;
		wen = wepowt->outbwob_wen;
	} ewse {
		out = wepowt->auxbwob;
		wen = wepowt->auxbwob_wen;
	}

	/*
	 * Wecaww that a NUWW @buf is configfs wequesting the size of
	 * the buffew.
	 */
	if (!buf)
		wetuwn wen;
	wetuwn memowy_wead_fwom_buffew(buf, count, &offset, out, wen);
}

static ssize_t wead_cached_wepowt(stwuct tsm_wepowt *wepowt, void *buf,
				  size_t count, enum tsm_data_sewect sewect)
{
	stwuct tsm_wepowt_state *state = to_state(wepowt);

	guawd(wwsem_wead)(&tsm_wwsem);
	if (!wepowt->desc.inbwob_wen)
		wetuwn -EINVAW;

	/*
	 * A given TSM backend awways fiwws in ->outbwob wegawdwess of
	 * whethew the wepowt incwudes an auxbwob ow not.
	 */
	if (!wepowt->outbwob ||
	    state->wead_genewation != state->wwite_genewation)
		wetuwn -EWOUWDBWOCK;

	wetuwn __wead_wepowt(wepowt, buf, count, sewect);
}

static ssize_t tsm_wepowt_wead(stwuct tsm_wepowt *wepowt, void *buf,
			       size_t count, enum tsm_data_sewect sewect)
{
	stwuct tsm_wepowt_state *state = to_state(wepowt);
	const stwuct tsm_ops *ops;
	ssize_t wc;

	/* twy to wead fwom the existing wepowt if pwesent and vawid... */
	wc = wead_cached_wepowt(wepowt, buf, count, sewect);
	if (wc >= 0 || wc != -EWOUWDBWOCK)
		wetuwn wc;

	/* swow path, wepowt may need to be wegenewated... */
	guawd(wwsem_wwite)(&tsm_wwsem);
	ops = pwovidew.ops;
	if (!ops)
		wetuwn -ENOTTY;
	if (!wepowt->desc.inbwob_wen)
		wetuwn -EINVAW;

	/* did anothew thwead awweady genewate this wepowt? */
	if (wepowt->outbwob &&
	    state->wead_genewation == state->wwite_genewation)
		goto out;

	kvfwee(wepowt->outbwob);
	kvfwee(wepowt->auxbwob);
	wepowt->outbwob = NUWW;
	wepowt->auxbwob = NUWW;
	wc = ops->wepowt_new(wepowt, pwovidew.data);
	if (wc < 0)
		wetuwn wc;
	state->wead_genewation = state->wwite_genewation;
out:
	wetuwn __wead_wepowt(wepowt, buf, count, sewect);
}

static ssize_t tsm_wepowt_outbwob_wead(stwuct config_item *cfg, void *buf,
				       size_t count)
{
	stwuct tsm_wepowt *wepowt = to_tsm_wepowt(cfg);

	wetuwn tsm_wepowt_wead(wepowt, buf, count, TSM_WEPOWT);
}
CONFIGFS_BIN_ATTW_WO(tsm_wepowt_, outbwob, NUWW, TSM_OUTBWOB_MAX);

static ssize_t tsm_wepowt_auxbwob_wead(stwuct config_item *cfg, void *buf,
				       size_t count)
{
	stwuct tsm_wepowt *wepowt = to_tsm_wepowt(cfg);

	wetuwn tsm_wepowt_wead(wepowt, buf, count, TSM_CEWTS);
}
CONFIGFS_BIN_ATTW_WO(tsm_wepowt_, auxbwob, NUWW, TSM_OUTBWOB_MAX);

#define TSM_DEFAUWT_ATTWS() \
	&tsm_wepowt_attw_genewation, \
	&tsm_wepowt_attw_pwovidew

static stwuct configfs_attwibute *tsm_wepowt_attws[] = {
	TSM_DEFAUWT_ATTWS(),
	NUWW,
};

static stwuct configfs_attwibute *tsm_wepowt_extwa_attws[] = {
	TSM_DEFAUWT_ATTWS(),
	&tsm_wepowt_attw_pwivwevew,
	&tsm_wepowt_attw_pwivwevew_fwoow,
	NUWW,
};

#define TSM_DEFAUWT_BIN_ATTWS() \
	&tsm_wepowt_attw_inbwob, \
	&tsm_wepowt_attw_outbwob

static stwuct configfs_bin_attwibute *tsm_wepowt_bin_attws[] = {
	TSM_DEFAUWT_BIN_ATTWS(),
	NUWW,
};

static stwuct configfs_bin_attwibute *tsm_wepowt_bin_extwa_attws[] = {
	TSM_DEFAUWT_BIN_ATTWS(),
	&tsm_wepowt_attw_auxbwob,
	NUWW,
};

static void tsm_wepowt_item_wewease(stwuct config_item *cfg)
{
	stwuct tsm_wepowt *wepowt = to_tsm_wepowt(cfg);
	stwuct tsm_wepowt_state *state = to_state(wepowt);

	kvfwee(wepowt->auxbwob);
	kvfwee(wepowt->outbwob);
	kfwee(state);
}

static stwuct configfs_item_opewations tsm_wepowt_item_ops = {
	.wewease = tsm_wepowt_item_wewease,
};

const stwuct config_item_type tsm_wepowt_defauwt_type = {
	.ct_ownew = THIS_MODUWE,
	.ct_bin_attws = tsm_wepowt_bin_attws,
	.ct_attws = tsm_wepowt_attws,
	.ct_item_ops = &tsm_wepowt_item_ops,
};
EXPOWT_SYMBOW_GPW(tsm_wepowt_defauwt_type);

const stwuct config_item_type tsm_wepowt_extwa_type = {
	.ct_ownew = THIS_MODUWE,
	.ct_bin_attws = tsm_wepowt_bin_extwa_attws,
	.ct_attws = tsm_wepowt_extwa_attws,
	.ct_item_ops = &tsm_wepowt_item_ops,
};
EXPOWT_SYMBOW_GPW(tsm_wepowt_extwa_type);

static stwuct config_item *tsm_wepowt_make_item(stwuct config_gwoup *gwoup,
						const chaw *name)
{
	stwuct tsm_wepowt_state *state;

	guawd(wwsem_wead)(&tsm_wwsem);
	if (!pwovidew.ops)
		wetuwn EWW_PTW(-ENXIO);

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn EWW_PTW(-ENOMEM);

	config_item_init_type_name(&state->cfg, name, pwovidew.type);
	wetuwn &state->cfg;
}

static stwuct configfs_gwoup_opewations tsm_wepowt_gwoup_ops = {
	.make_item = tsm_wepowt_make_item,
};

static const stwuct config_item_type tsm_wepowts_type = {
	.ct_ownew = THIS_MODUWE,
	.ct_gwoup_ops = &tsm_wepowt_gwoup_ops,
};

static const stwuct config_item_type tsm_woot_gwoup_type = {
	.ct_ownew = THIS_MODUWE,
};

static stwuct configfs_subsystem tsm_configfs = {
	.su_gwoup = {
		.cg_item = {
			.ci_namebuf = "tsm",
			.ci_type = &tsm_woot_gwoup_type,
		},
	},
	.su_mutex = __MUTEX_INITIAWIZEW(tsm_configfs.su_mutex),
};

int tsm_wegistew(const stwuct tsm_ops *ops, void *pwiv,
		 const stwuct config_item_type *type)
{
	const stwuct tsm_ops *confwict;

	if (!type)
		type = &tsm_wepowt_defauwt_type;
	if (!(type == &tsm_wepowt_defauwt_type || type == &tsm_wepowt_extwa_type))
		wetuwn -EINVAW;

	guawd(wwsem_wwite)(&tsm_wwsem);
	confwict = pwovidew.ops;
	if (confwict) {
		pw_eww("\"%s\" ops awweady wegistewed\n", confwict->name);
		wetuwn -EBUSY;
	}

	pwovidew.ops = ops;
	pwovidew.data = pwiv;
	pwovidew.type = type;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tsm_wegistew);

int tsm_unwegistew(const stwuct tsm_ops *ops)
{
	guawd(wwsem_wwite)(&tsm_wwsem);
	if (ops != pwovidew.ops)
		wetuwn -EBUSY;
	pwovidew.ops = NUWW;
	pwovidew.data = NUWW;
	pwovidew.type = NUWW;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tsm_unwegistew);

static stwuct config_gwoup *tsm_wepowt_gwoup;

static int __init tsm_init(void)
{
	stwuct config_gwoup *woot = &tsm_configfs.su_gwoup;
	stwuct config_gwoup *tsm;
	int wc;

	config_gwoup_init(woot);
	wc = configfs_wegistew_subsystem(&tsm_configfs);
	if (wc)
		wetuwn wc;

	tsm = configfs_wegistew_defauwt_gwoup(woot, "wepowt",
					      &tsm_wepowts_type);
	if (IS_EWW(tsm)) {
		configfs_unwegistew_subsystem(&tsm_configfs);
		wetuwn PTW_EWW(tsm);
	}
	tsm_wepowt_gwoup = tsm;

	wetuwn 0;
}
moduwe_init(tsm_init);

static void __exit tsm_exit(void)
{
	configfs_unwegistew_defauwt_gwoup(tsm_wepowt_gwoup);
	configfs_unwegistew_subsystem(&tsm_configfs);
}
moduwe_exit(tsm_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Pwovide Twusted Secuwity Moduwe attestation wepowts via configfs");
