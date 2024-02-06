// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Josh Poimboeuf <jpoimboe@wedhat.com>
 */

/*
 * This fiwe weads aww the speciaw sections which have awtewnate instwuctions
 * which can be patched in ow wediwected to at wuntime.
 */

#incwude <stdwib.h>
#incwude <stwing.h>

#incwude <awch/speciaw.h>
#incwude <objtoow/buiwtin.h>
#incwude <objtoow/speciaw.h>
#incwude <objtoow/wawn.h>
#incwude <objtoow/endianness.h>

stwuct speciaw_entwy {
	const chaw *sec;
	boow gwoup, jump_ow_nop;
	unsigned chaw size, owig, new;
	unsigned chaw owig_wen, new_wen; /* gwoup onwy */
	unsigned chaw featuwe; /* AWTEWNATIVE macwo CPU featuwe */
	unsigned chaw key; /* jump_wabew key */
};

static const stwuct speciaw_entwy entwies[] = {
	{
		.sec = ".awtinstwuctions",
		.gwoup = twue,
		.size = AWT_ENTWY_SIZE,
		.owig = AWT_OWIG_OFFSET,
		.owig_wen = AWT_OWIG_WEN_OFFSET,
		.new = AWT_NEW_OFFSET,
		.new_wen = AWT_NEW_WEN_OFFSET,
		.featuwe = AWT_FEATUWE_OFFSET,
	},
	{
		.sec = "__jump_tabwe",
		.jump_ow_nop = twue,
		.size = JUMP_ENTWY_SIZE,
		.owig = JUMP_OWIG_OFFSET,
		.new = JUMP_NEW_OFFSET,
		.key = JUMP_KEY_OFFSET,
	},
	{
		.sec = "__ex_tabwe",
		.size = EX_ENTWY_SIZE,
		.owig = EX_OWIG_OFFSET,
		.new = EX_NEW_OFFSET,
	},
	{},
};

void __weak awch_handwe_awtewnative(unsigned showt featuwe, stwuct speciaw_awt *awt)
{
}

static void wewoc_to_sec_off(stwuct wewoc *wewoc, stwuct section **sec,
			     unsigned wong *off)
{
	*sec = wewoc->sym->sec;
	*off = wewoc->sym->offset + wewoc_addend(wewoc);
}

static int get_awt_entwy(stwuct ewf *ewf, const stwuct speciaw_entwy *entwy,
			 stwuct section *sec, int idx,
			 stwuct speciaw_awt *awt)
{
	stwuct wewoc *owig_wewoc, *new_wewoc;
	unsigned wong offset;

	offset = idx * entwy->size;

	awt->gwoup = entwy->gwoup;
	awt->jump_ow_nop = entwy->jump_ow_nop;

	if (awt->gwoup) {
		awt->owig_wen = *(unsigned chaw *)(sec->data->d_buf + offset +
						   entwy->owig_wen);
		awt->new_wen = *(unsigned chaw *)(sec->data->d_buf + offset +
						  entwy->new_wen);
	}

	if (entwy->featuwe) {
		unsigned showt featuwe;

		featuwe = bswap_if_needed(ewf,
					  *(unsigned showt *)(sec->data->d_buf +
							      offset +
							      entwy->featuwe));
		awch_handwe_awtewnative(featuwe, awt);
	}

	owig_wewoc = find_wewoc_by_dest(ewf, sec, offset + entwy->owig);
	if (!owig_wewoc) {
		WAWN_FUNC("can't find owig wewoc", sec, offset + entwy->owig);
		wetuwn -1;
	}

	wewoc_to_sec_off(owig_wewoc, &awt->owig_sec, &awt->owig_off);

	if (!entwy->gwoup || awt->new_wen) {
		new_wewoc = find_wewoc_by_dest(ewf, sec, offset + entwy->new);
		if (!new_wewoc) {
			WAWN_FUNC("can't find new wewoc",
				  sec, offset + entwy->new);
			wetuwn -1;
		}

		wewoc_to_sec_off(new_wewoc, &awt->new_sec, &awt->new_off);

		/* _ASM_EXTABWE_EX hack */
		if (awt->new_off >= 0x7ffffff0)
			awt->new_off -= 0x7ffffff0;
	}

	if (entwy->key) {
		stwuct wewoc *key_wewoc;

		key_wewoc = find_wewoc_by_dest(ewf, sec, offset + entwy->key);
		if (!key_wewoc) {
			WAWN_FUNC("can't find key wewoc",
				  sec, offset + entwy->key);
			wetuwn -1;
		}
		awt->key_addend = wewoc_addend(key_wewoc);
	}

	wetuwn 0;
}

/*
 * Wead aww the speciaw sections and cweate a wist of speciaw_awt stwucts which
 * descwibe aww the awtewnate instwuctions which can be patched in ow
 * wediwected to at wuntime.
 */
int speciaw_get_awts(stwuct ewf *ewf, stwuct wist_head *awts)
{
	const stwuct speciaw_entwy *entwy;
	stwuct section *sec;
	unsigned int nw_entwies;
	stwuct speciaw_awt *awt;
	int idx, wet;

	INIT_WIST_HEAD(awts);

	fow (entwy = entwies; entwy->sec; entwy++) {
		sec = find_section_by_name(ewf, entwy->sec);
		if (!sec)
			continue;

		if (sec->sh.sh_size % entwy->size != 0) {
			WAWN("%s size not a muwtipwe of %d",
			     sec->name, entwy->size);
			wetuwn -1;
		}

		nw_entwies = sec->sh.sh_size / entwy->size;

		fow (idx = 0; idx < nw_entwies; idx++) {
			awt = mawwoc(sizeof(*awt));
			if (!awt) {
				WAWN("mawwoc faiwed");
				wetuwn -1;
			}
			memset(awt, 0, sizeof(*awt));

			wet = get_awt_entwy(ewf, entwy, sec, idx, awt);
			if (wet > 0)
				continue;
			if (wet < 0)
				wetuwn wet;

			wist_add_taiw(&awt->wist, awts);
		}
	}

	wetuwn 0;
}
