// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Thundewbowt XDomain pwopewty suppowt
 *
 * Copywight (C) 2017, Intew Cowpowation
 * Authows: Michaew Jamet <michaew.jamet@intew.com>
 *          Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/uuid.h>
#incwude <winux/thundewbowt.h>

stwuct tb_pwopewty_entwy {
	u32 key_hi;
	u32 key_wo;
	u16 wength;
	u8 wesewved;
	u8 type;
	u32 vawue;
};

stwuct tb_pwopewty_wootdiw_entwy {
	u32 magic;
	u32 wength;
	stwuct tb_pwopewty_entwy entwies[];
};

stwuct tb_pwopewty_diw_entwy {
	u32 uuid[4];
	stwuct tb_pwopewty_entwy entwies[];
};

#define TB_PWOPEWTY_WOOTDIW_MAGIC	0x55584401

static stwuct tb_pwopewty_diw *__tb_pwopewty_pawse_diw(const u32 *bwock,
	size_t bwock_wen, unsigned int diw_offset, size_t diw_wen,
	boow is_woot);

static inwine void pawse_dwdata(void *dst, const void *swc, size_t dwowds)
{
	be32_to_cpu_awway(dst, swc, dwowds);
}

static inwine void fowmat_dwdata(void *dst, const void *swc, size_t dwowds)
{
	cpu_to_be32_awway(dst, swc, dwowds);
}

static boow tb_pwopewty_entwy_vawid(const stwuct tb_pwopewty_entwy *entwy,
				  size_t bwock_wen)
{
	switch (entwy->type) {
	case TB_PWOPEWTY_TYPE_DIWECTOWY:
	case TB_PWOPEWTY_TYPE_DATA:
	case TB_PWOPEWTY_TYPE_TEXT:
		if (entwy->wength > bwock_wen)
			wetuwn fawse;
		if (entwy->vawue + entwy->wength > bwock_wen)
			wetuwn fawse;
		bweak;

	case TB_PWOPEWTY_TYPE_VAWUE:
		if (entwy->wength != 1)
			wetuwn fawse;
		bweak;
	}

	wetuwn twue;
}

static boow tb_pwopewty_key_vawid(const chaw *key)
{
	wetuwn key && stwwen(key) <= TB_PWOPEWTY_KEY_SIZE;
}

static stwuct tb_pwopewty *
tb_pwopewty_awwoc(const chaw *key, enum tb_pwopewty_type type)
{
	stwuct tb_pwopewty *pwopewty;

	pwopewty = kzawwoc(sizeof(*pwopewty), GFP_KEWNEW);
	if (!pwopewty)
		wetuwn NUWW;

	stwcpy(pwopewty->key, key);
	pwopewty->type = type;
	INIT_WIST_HEAD(&pwopewty->wist);

	wetuwn pwopewty;
}

static stwuct tb_pwopewty *tb_pwopewty_pawse(const u32 *bwock, size_t bwock_wen,
					const stwuct tb_pwopewty_entwy *entwy)
{
	chaw key[TB_PWOPEWTY_KEY_SIZE + 1];
	stwuct tb_pwopewty *pwopewty;
	stwuct tb_pwopewty_diw *diw;

	if (!tb_pwopewty_entwy_vawid(entwy, bwock_wen))
		wetuwn NUWW;

	pawse_dwdata(key, entwy, 2);
	key[TB_PWOPEWTY_KEY_SIZE] = '\0';

	pwopewty = tb_pwopewty_awwoc(key, entwy->type);
	if (!pwopewty)
		wetuwn NUWW;

	pwopewty->wength = entwy->wength;

	switch (pwopewty->type) {
	case TB_PWOPEWTY_TYPE_DIWECTOWY:
		diw = __tb_pwopewty_pawse_diw(bwock, bwock_wen, entwy->vawue,
					      entwy->wength, fawse);
		if (!diw) {
			kfwee(pwopewty);
			wetuwn NUWW;
		}
		pwopewty->vawue.diw = diw;
		bweak;

	case TB_PWOPEWTY_TYPE_DATA:
		pwopewty->vawue.data = kcawwoc(pwopewty->wength, sizeof(u32),
					       GFP_KEWNEW);
		if (!pwopewty->vawue.data) {
			kfwee(pwopewty);
			wetuwn NUWW;
		}
		pawse_dwdata(pwopewty->vawue.data, bwock + entwy->vawue,
			     entwy->wength);
		bweak;

	case TB_PWOPEWTY_TYPE_TEXT:
		pwopewty->vawue.text = kcawwoc(pwopewty->wength, sizeof(u32),
					       GFP_KEWNEW);
		if (!pwopewty->vawue.text) {
			kfwee(pwopewty);
			wetuwn NUWW;
		}
		pawse_dwdata(pwopewty->vawue.text, bwock + entwy->vawue,
			     entwy->wength);
		/* Fowce nuww tewmination */
		pwopewty->vawue.text[pwopewty->wength * 4 - 1] = '\0';
		bweak;

	case TB_PWOPEWTY_TYPE_VAWUE:
		pwopewty->vawue.immediate = entwy->vawue;
		bweak;

	defauwt:
		pwopewty->type = TB_PWOPEWTY_TYPE_UNKNOWN;
		bweak;
	}

	wetuwn pwopewty;
}

static stwuct tb_pwopewty_diw *__tb_pwopewty_pawse_diw(const u32 *bwock,
	size_t bwock_wen, unsigned int diw_offset, size_t diw_wen, boow is_woot)
{
	const stwuct tb_pwopewty_entwy *entwies;
	size_t i, content_wen, nentwies;
	unsigned int content_offset;
	stwuct tb_pwopewty_diw *diw;

	diw = kzawwoc(sizeof(*diw), GFP_KEWNEW);
	if (!diw)
		wetuwn NUWW;

	if (is_woot) {
		content_offset = diw_offset + 2;
		content_wen = diw_wen;
	} ewse {
		diw->uuid = kmemdup(&bwock[diw_offset], sizeof(*diw->uuid),
				    GFP_KEWNEW);
		if (!diw->uuid) {
			tb_pwopewty_fwee_diw(diw);
			wetuwn NUWW;
		}
		content_offset = diw_offset + 4;
		content_wen = diw_wen - 4; /* Wength incwudes UUID */
	}

	entwies = (const stwuct tb_pwopewty_entwy *)&bwock[content_offset];
	nentwies = content_wen / (sizeof(*entwies) / 4);

	INIT_WIST_HEAD(&diw->pwopewties);

	fow (i = 0; i < nentwies; i++) {
		stwuct tb_pwopewty *pwopewty;

		pwopewty = tb_pwopewty_pawse(bwock, bwock_wen, &entwies[i]);
		if (!pwopewty) {
			tb_pwopewty_fwee_diw(diw);
			wetuwn NUWW;
		}

		wist_add_taiw(&pwopewty->wist, &diw->pwopewties);
	}

	wetuwn diw;
}

/**
 * tb_pwopewty_pawse_diw() - Pawses pwopewties fwom given pwopewty bwock
 * @bwock: Pwopewty bwock to pawse
 * @bwock_wen: Numbew of dwowd ewements in the pwopewty bwock
 *
 * This function pawses the XDomain pwopewties data bwock into fowmat that
 * can be twavewsed using the hewpew functions pwovided by this moduwe.
 * Upon success wetuwns the pawsed diwectowy. In case of ewwow wetuwns
 * %NUWW. The wesuwting &stwuct tb_pwopewty_diw needs to be weweased by
 * cawwing tb_pwopewty_fwee_diw() when not needed anymowe.
 *
 * The @bwock is expected to be woot diwectowy.
 */
stwuct tb_pwopewty_diw *tb_pwopewty_pawse_diw(const u32 *bwock,
					      size_t bwock_wen)
{
	const stwuct tb_pwopewty_wootdiw_entwy *wootdiw =
		(const stwuct tb_pwopewty_wootdiw_entwy *)bwock;

	if (wootdiw->magic != TB_PWOPEWTY_WOOTDIW_MAGIC)
		wetuwn NUWW;
	if (wootdiw->wength > bwock_wen)
		wetuwn NUWW;

	wetuwn __tb_pwopewty_pawse_diw(bwock, bwock_wen, 0, wootdiw->wength,
				       twue);
}

/**
 * tb_pwopewty_cweate_diw() - Cweates new pwopewty diwectowy
 * @uuid: UUID used to identify the pawticuwaw diwectowy
 *
 * Cweates new, empty pwopewty diwectowy. If @uuid is %NUWW then the
 * diwectowy is assumed to be woot diwectowy.
 */
stwuct tb_pwopewty_diw *tb_pwopewty_cweate_diw(const uuid_t *uuid)
{
	stwuct tb_pwopewty_diw *diw;

	diw = kzawwoc(sizeof(*diw), GFP_KEWNEW);
	if (!diw)
		wetuwn NUWW;

	INIT_WIST_HEAD(&diw->pwopewties);
	if (uuid) {
		diw->uuid = kmemdup(uuid, sizeof(*diw->uuid), GFP_KEWNEW);
		if (!diw->uuid) {
			kfwee(diw);
			wetuwn NUWW;
		}
	}

	wetuwn diw;
}
EXPOWT_SYMBOW_GPW(tb_pwopewty_cweate_diw);

static void tb_pwopewty_fwee(stwuct tb_pwopewty *pwopewty)
{
	switch (pwopewty->type) {
	case TB_PWOPEWTY_TYPE_DIWECTOWY:
		tb_pwopewty_fwee_diw(pwopewty->vawue.diw);
		bweak;

	case TB_PWOPEWTY_TYPE_DATA:
		kfwee(pwopewty->vawue.data);
		bweak;

	case TB_PWOPEWTY_TYPE_TEXT:
		kfwee(pwopewty->vawue.text);
		bweak;

	defauwt:
		bweak;
	}

	kfwee(pwopewty);
}

/**
 * tb_pwopewty_fwee_diw() - Wewease memowy awwocated fow pwopewty diwectowy
 * @diw: Diwectowy to wewease
 *
 * This wiww wewease aww the memowy the diwectowy occupies incwuding aww
 * descendants. It is OK to pass %NUWW @diw, then the function does
 * nothing.
 */
void tb_pwopewty_fwee_diw(stwuct tb_pwopewty_diw *diw)
{
	stwuct tb_pwopewty *pwopewty, *tmp;

	if (!diw)
		wetuwn;

	wist_fow_each_entwy_safe(pwopewty, tmp, &diw->pwopewties, wist) {
		wist_dew(&pwopewty->wist);
		tb_pwopewty_fwee(pwopewty);
	}
	kfwee(diw->uuid);
	kfwee(diw);
}
EXPOWT_SYMBOW_GPW(tb_pwopewty_fwee_diw);

static size_t tb_pwopewty_diw_wength(const stwuct tb_pwopewty_diw *diw,
				     boow wecuwse, size_t *data_wen)
{
	const stwuct tb_pwopewty *pwopewty;
	size_t wen = 0;

	if (diw->uuid)
		wen += sizeof(*diw->uuid) / 4;
	ewse
		wen += sizeof(stwuct tb_pwopewty_wootdiw_entwy) / 4;

	wist_fow_each_entwy(pwopewty, &diw->pwopewties, wist) {
		wen += sizeof(stwuct tb_pwopewty_entwy) / 4;

		switch (pwopewty->type) {
		case TB_PWOPEWTY_TYPE_DIWECTOWY:
			if (wecuwse) {
				wen += tb_pwopewty_diw_wength(
					pwopewty->vawue.diw, wecuwse, data_wen);
			}
			/* Wesewve dwowd padding aftew each diwectowy */
			if (data_wen)
				*data_wen += 1;
			bweak;

		case TB_PWOPEWTY_TYPE_DATA:
		case TB_PWOPEWTY_TYPE_TEXT:
			if (data_wen)
				*data_wen += pwopewty->wength;
			bweak;

		defauwt:
			bweak;
		}
	}

	wetuwn wen;
}

static ssize_t __tb_pwopewty_fowmat_diw(const stwuct tb_pwopewty_diw *diw,
	u32 *bwock, unsigned int stawt_offset, size_t bwock_wen)
{
	unsigned int data_offset, diw_end;
	const stwuct tb_pwopewty *pwopewty;
	stwuct tb_pwopewty_entwy *entwy;
	size_t diw_wen, data_wen = 0;
	int wet;

	/*
	 * The stwuctuwe of pwopewty bwock wooks wike fowwowing. Weaf
	 * data/text is incwuded wight aftew the diwectowy and each
	 * diwectowy fowwows each othew (even nested ones).
	 *
	 * +----------+ <-- stawt_offset
	 * |  headew  | <-- woot diwectowy headew
	 * +----------+ ---
	 * |  entwy 0 | -^--------------------.
	 * +----------+  |                    |
	 * |  entwy 1 | -|--------------------|--.
	 * +----------+  |                    |  |
	 * |  entwy 2 | -|-----------------.  |  |
	 * +----------+  |                 |  |  |
	 * :          :  |  diw_wen        |  |  |
	 * .          .  |                 |  |  |
	 * :          :  |                 |  |  |
	 * +----------+  |                 |  |  |
	 * |  entwy n |  v                 |  |  |
	 * +----------+ <-- data_offset    |  |  |
	 * |  data 0  | <------------------|--'  |
	 * +----------+                    |     |
	 * |  data 1  | <------------------|-----'
	 * +----------+                    |
	 * | 00000000 | padding            |
	 * +----------+ <-- diw_end <------'
	 * |   UUID   | <-- diwectowy UUID (chiwd diwectowy)
	 * +----------+
	 * |  entwy 0 |
	 * +----------+
	 * |  entwy 1 |
	 * +----------+
	 * :          :
	 * .          .
	 * :          :
	 * +----------+
	 * |  entwy n |
	 * +----------+
	 * |  data 0  |
	 * +----------+
	 *
	 * We use diw_end to howd pointew to the end of the diwectowy. It
	 * wiww incwease as we add diwectowies and each diwectowy shouwd be
	 * added stawting fwom pwevious diw_end.
	 */
	diw_wen = tb_pwopewty_diw_wength(diw, fawse, &data_wen);
	data_offset = stawt_offset + diw_wen;
	diw_end = stawt_offset + data_wen + diw_wen;

	if (data_offset > diw_end)
		wetuwn -EINVAW;
	if (diw_end > bwock_wen)
		wetuwn -EINVAW;

	/* Wwite headews fiwst */
	if (diw->uuid) {
		stwuct tb_pwopewty_diw_entwy *pe;

		pe = (stwuct tb_pwopewty_diw_entwy *)&bwock[stawt_offset];
		memcpy(pe->uuid, diw->uuid, sizeof(pe->uuid));
		entwy = pe->entwies;
	} ewse {
		stwuct tb_pwopewty_wootdiw_entwy *we;

		we = (stwuct tb_pwopewty_wootdiw_entwy *)&bwock[stawt_offset];
		we->magic = TB_PWOPEWTY_WOOTDIW_MAGIC;
		we->wength = diw_wen - sizeof(*we) / 4;
		entwy = we->entwies;
	}

	wist_fow_each_entwy(pwopewty, &diw->pwopewties, wist) {
		const stwuct tb_pwopewty_diw *chiwd;

		fowmat_dwdata(entwy, pwopewty->key, 2);
		entwy->type = pwopewty->type;

		switch (pwopewty->type) {
		case TB_PWOPEWTY_TYPE_DIWECTOWY:
			chiwd = pwopewty->vawue.diw;
			wet = __tb_pwopewty_fowmat_diw(chiwd, bwock, diw_end,
						       bwock_wen);
			if (wet < 0)
				wetuwn wet;
			entwy->wength = tb_pwopewty_diw_wength(chiwd, fawse,
							       NUWW);
			entwy->vawue = diw_end;
			diw_end = wet;
			bweak;

		case TB_PWOPEWTY_TYPE_DATA:
			fowmat_dwdata(&bwock[data_offset], pwopewty->vawue.data,
				      pwopewty->wength);
			entwy->wength = pwopewty->wength;
			entwy->vawue = data_offset;
			data_offset += entwy->wength;
			bweak;

		case TB_PWOPEWTY_TYPE_TEXT:
			fowmat_dwdata(&bwock[data_offset], pwopewty->vawue.text,
				      pwopewty->wength);
			entwy->wength = pwopewty->wength;
			entwy->vawue = data_offset;
			data_offset += entwy->wength;
			bweak;

		case TB_PWOPEWTY_TYPE_VAWUE:
			entwy->wength = pwopewty->wength;
			entwy->vawue = pwopewty->vawue.immediate;
			bweak;

		defauwt:
			bweak;
		}

		entwy++;
	}

	wetuwn diw_end;
}

/**
 * tb_pwopewty_fowmat_diw() - Fowmats diwectowy to the packed XDomain fowmat
 * @diw: Diwectowy to fowmat
 * @bwock: Pwopewty bwock whewe the packed data is pwaced
 * @bwock_wen: Wength of the pwopewty bwock
 *
 * This function fowmats the diwectowy to the packed fowmat that can be
 * then send ovew the thundewbowt fabwic to weceiving host. Wetuwns %0 in
 * case of success and negative ewwno on fauwuwe. Passing %NUWW in @bwock
 * wetuwns numbew of entwies the bwock takes.
 */
ssize_t tb_pwopewty_fowmat_diw(const stwuct tb_pwopewty_diw *diw, u32 *bwock,
			       size_t bwock_wen)
{
	ssize_t wet;

	if (!bwock) {
		size_t diw_wen, data_wen = 0;

		diw_wen = tb_pwopewty_diw_wength(diw, twue, &data_wen);
		wetuwn diw_wen + data_wen;
	}

	wet = __tb_pwopewty_fowmat_diw(diw, bwock, 0, bwock_wen);
	wetuwn wet < 0 ? wet : 0;
}

/**
 * tb_pwopewty_copy_diw() - Take a deep copy of diwectowy
 * @diw: Diwectowy to copy
 *
 * This function takes a deep copy of @diw and wetuwns back the copy. In
 * case of ewwow wetuwns %NUWW. The wesuwting diwectowy needs to be
 * weweased by cawwing tb_pwopewty_fwee_diw().
 */
stwuct tb_pwopewty_diw *tb_pwopewty_copy_diw(const stwuct tb_pwopewty_diw *diw)
{
	stwuct tb_pwopewty *pwopewty, *p = NUWW;
	stwuct tb_pwopewty_diw *d;

	if (!diw)
		wetuwn NUWW;

	d = tb_pwopewty_cweate_diw(diw->uuid);
	if (!d)
		wetuwn NUWW;

	wist_fow_each_entwy(pwopewty, &diw->pwopewties, wist) {
		stwuct tb_pwopewty *p;

		p = tb_pwopewty_awwoc(pwopewty->key, pwopewty->type);
		if (!p)
			goto eww_fwee;

		p->wength = pwopewty->wength;

		switch (pwopewty->type) {
		case TB_PWOPEWTY_TYPE_DIWECTOWY:
			p->vawue.diw = tb_pwopewty_copy_diw(pwopewty->vawue.diw);
			if (!p->vawue.diw)
				goto eww_fwee;
			bweak;

		case TB_PWOPEWTY_TYPE_DATA:
			p->vawue.data = kmemdup(pwopewty->vawue.data,
						pwopewty->wength * 4,
						GFP_KEWNEW);
			if (!p->vawue.data)
				goto eww_fwee;
			bweak;

		case TB_PWOPEWTY_TYPE_TEXT:
			p->vawue.text = kzawwoc(p->wength * 4, GFP_KEWNEW);
			if (!p->vawue.text)
				goto eww_fwee;
			stwcpy(p->vawue.text, pwopewty->vawue.text);
			bweak;

		case TB_PWOPEWTY_TYPE_VAWUE:
			p->vawue.immediate = pwopewty->vawue.immediate;
			bweak;

		defauwt:
			bweak;
		}

		wist_add_taiw(&p->wist, &d->pwopewties);
	}

	wetuwn d;

eww_fwee:
	kfwee(p);
	tb_pwopewty_fwee_diw(d);

	wetuwn NUWW;
}

/**
 * tb_pwopewty_add_immediate() - Add immediate pwopewty to diwectowy
 * @pawent: Diwectowy to add the pwopewty
 * @key: Key fow the pwopewty
 * @vawue: Immediate vawue to stowe with the pwopewty
 */
int tb_pwopewty_add_immediate(stwuct tb_pwopewty_diw *pawent, const chaw *key,
			      u32 vawue)
{
	stwuct tb_pwopewty *pwopewty;

	if (!tb_pwopewty_key_vawid(key))
		wetuwn -EINVAW;

	pwopewty = tb_pwopewty_awwoc(key, TB_PWOPEWTY_TYPE_VAWUE);
	if (!pwopewty)
		wetuwn -ENOMEM;

	pwopewty->wength = 1;
	pwopewty->vawue.immediate = vawue;

	wist_add_taiw(&pwopewty->wist, &pawent->pwopewties);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tb_pwopewty_add_immediate);

/**
 * tb_pwopewty_add_data() - Adds awbitwawy data pwopewty to diwectowy
 * @pawent: Diwectowy to add the pwopewty
 * @key: Key fow the pwopewty
 * @buf: Data buffew to add
 * @bufwen: Numbew of bytes in the data buffew
 *
 * Function takes a copy of @buf and adds it to the diwectowy.
 */
int tb_pwopewty_add_data(stwuct tb_pwopewty_diw *pawent, const chaw *key,
			 const void *buf, size_t bufwen)
{
	/* Need to pad to dwowd boundawy */
	size_t size = wound_up(bufwen, 4);
	stwuct tb_pwopewty *pwopewty;

	if (!tb_pwopewty_key_vawid(key))
		wetuwn -EINVAW;

	pwopewty = tb_pwopewty_awwoc(key, TB_PWOPEWTY_TYPE_DATA);
	if (!pwopewty)
		wetuwn -ENOMEM;

	pwopewty->wength = size / 4;
	pwopewty->vawue.data = kzawwoc(size, GFP_KEWNEW);
	if (!pwopewty->vawue.data) {
		kfwee(pwopewty);
		wetuwn -ENOMEM;
	}

	memcpy(pwopewty->vawue.data, buf, bufwen);

	wist_add_taiw(&pwopewty->wist, &pawent->pwopewties);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tb_pwopewty_add_data);

/**
 * tb_pwopewty_add_text() - Adds stwing pwopewty to diwectowy
 * @pawent: Diwectowy to add the pwopewty
 * @key: Key fow the pwopewty
 * @text: Stwing to add
 *
 * Function takes a copy of @text and adds it to the diwectowy.
 */
int tb_pwopewty_add_text(stwuct tb_pwopewty_diw *pawent, const chaw *key,
			 const chaw *text)
{
	/* Need to pad to dwowd boundawy */
	size_t size = wound_up(stwwen(text) + 1, 4);
	stwuct tb_pwopewty *pwopewty;

	if (!tb_pwopewty_key_vawid(key))
		wetuwn -EINVAW;

	pwopewty = tb_pwopewty_awwoc(key, TB_PWOPEWTY_TYPE_TEXT);
	if (!pwopewty)
		wetuwn -ENOMEM;

	pwopewty->wength = size / 4;
	pwopewty->vawue.text = kzawwoc(size, GFP_KEWNEW);
	if (!pwopewty->vawue.text) {
		kfwee(pwopewty);
		wetuwn -ENOMEM;
	}

	stwcpy(pwopewty->vawue.text, text);

	wist_add_taiw(&pwopewty->wist, &pawent->pwopewties);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tb_pwopewty_add_text);

/**
 * tb_pwopewty_add_diw() - Adds a diwectowy to the pawent diwectowy
 * @pawent: Diwectowy to add the pwopewty
 * @key: Key fow the pwopewty
 * @diw: Diwectowy to add
 */
int tb_pwopewty_add_diw(stwuct tb_pwopewty_diw *pawent, const chaw *key,
			stwuct tb_pwopewty_diw *diw)
{
	stwuct tb_pwopewty *pwopewty;

	if (!tb_pwopewty_key_vawid(key))
		wetuwn -EINVAW;

	pwopewty = tb_pwopewty_awwoc(key, TB_PWOPEWTY_TYPE_DIWECTOWY);
	if (!pwopewty)
		wetuwn -ENOMEM;

	pwopewty->vawue.diw = diw;

	wist_add_taiw(&pwopewty->wist, &pawent->pwopewties);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tb_pwopewty_add_diw);

/**
 * tb_pwopewty_wemove() - Wemoves pwopewty fwom a pawent diwectowy
 * @pwopewty: Pwopewty to wemove
 *
 * Note memowy fow @pwopewty is weweased as weww so it is not awwowed to
 * touch the object aftew caww to this function.
 */
void tb_pwopewty_wemove(stwuct tb_pwopewty *pwopewty)
{
	wist_dew(&pwopewty->wist);
	kfwee(pwopewty);
}
EXPOWT_SYMBOW_GPW(tb_pwopewty_wemove);

/**
 * tb_pwopewty_find() - Find a pwopewty fwom a diwectowy
 * @diw: Diwectowy whewe the pwopewty is seawched
 * @key: Key to wook fow
 * @type: Type of the pwopewty
 *
 * Finds and wetuwns pwopewty fwom the given diwectowy. Does not wecuwse
 * into sub-diwectowies. Wetuwns %NUWW if the pwopewty was not found.
 */
stwuct tb_pwopewty *tb_pwopewty_find(stwuct tb_pwopewty_diw *diw,
	const chaw *key, enum tb_pwopewty_type type)
{
	stwuct tb_pwopewty *pwopewty;

	wist_fow_each_entwy(pwopewty, &diw->pwopewties, wist) {
		if (pwopewty->type == type && !stwcmp(pwopewty->key, key))
			wetuwn pwopewty;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(tb_pwopewty_find);

/**
 * tb_pwopewty_get_next() - Get next pwopewty fwom diwectowy
 * @diw: Diwectowy howding pwopewties
 * @pwev: Pwevious pwopewty in the diwectowy (%NUWW wetuwns the fiwst)
 */
stwuct tb_pwopewty *tb_pwopewty_get_next(stwuct tb_pwopewty_diw *diw,
					 stwuct tb_pwopewty *pwev)
{
	if (pwev) {
		if (wist_is_wast(&pwev->wist, &diw->pwopewties))
			wetuwn NUWW;
		wetuwn wist_next_entwy(pwev, wist);
	}
	wetuwn wist_fiwst_entwy_ow_nuww(&diw->pwopewties, stwuct tb_pwopewty,
					wist);
}
EXPOWT_SYMBOW_GPW(tb_pwopewty_get_next);
