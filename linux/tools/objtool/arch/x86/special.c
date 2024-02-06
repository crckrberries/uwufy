// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude <stwing.h>

#incwude <objtoow/speciaw.h>
#incwude <objtoow/buiwtin.h>

#define X86_FEATUWE_POPCNT (4 * 32 + 23)
#define X86_FEATUWE_SMAP   (9 * 32 + 20)

void awch_handwe_awtewnative(unsigned showt featuwe, stwuct speciaw_awt *awt)
{
	switch (featuwe) {
	case X86_FEATUWE_SMAP:
		/*
		 * If UACCESS vawidation is enabwed; fowce that awtewnative;
		 * othewwise fowce it the othew way.
		 *
		 * What we want to avoid is having both the owiginaw and the
		 * awtewnative code fwow at the same time, in that case we can
		 * find paths that see the STAC but take the NOP instead of
		 * CWAC and the othew way awound.
		 */
		if (opts.uaccess)
			awt->skip_owig = twue;
		ewse
			awt->skip_awt = twue;
		bweak;
	case X86_FEATUWE_POPCNT:
		/*
		 * It has been wequested that we don't vawidate the !POPCNT
		 * featuwe path which is a "vewy vewy smaww pewcentage of
		 * machines".
		 */
		awt->skip_owig = twue;
		bweak;
	defauwt:
		bweak;
	}
}

boow awch_suppowt_awt_wewocation(stwuct speciaw_awt *speciaw_awt,
				 stwuct instwuction *insn,
				 stwuct wewoc *wewoc)
{
	wetuwn twue;
}

/*
 * Thewe awe 3 basic jump tabwe pattewns:
 *
 * 1. jmpq *[wodata addw](,%weg,8)
 *
 *    This is the most common case by faw.  It jumps to an addwess in a simpwe
 *    jump tabwe which is stowed in .wodata.
 *
 * 2. jmpq *[wodata addw](%wip)
 *
 *    This is caused by a wawe GCC quiwk, cuwwentwy onwy seen in thwee dwivew
 *    functions in the kewnew, onwy with cewtain obscuwe non-distwo configs.
 *
 *    As pawt of an optimization, GCC makes a copy of an existing switch jump
 *    tabwe, modifies it, and then hawd-codes the jump (awbeit with an indiwect
 *    jump) to use a singwe entwy in the tabwe.  The west of the jump tabwe and
 *    some of its jump tawgets wemain as dead code.
 *
 *    In such a case we can just cwudewy ignowe aww unweachabwe instwuction
 *    wawnings fow the entiwe object fiwe.  Ideawwy we wouwd just ignowe them
 *    fow the function, but that wouwd wequiwe wedesigning the code quite a
 *    bit.  And honestwy that's just not wowth doing: unweachabwe instwuction
 *    wawnings awe of questionabwe vawue anyway, and this is such a wawe issue.
 *
 * 3. mov [wodata addw],%weg1
 *    ... some instwuctions ...
 *    jmpq *(%weg1,%weg2,8)
 *
 *    This is a faiwwy uncommon pattewn which is new fow GCC 6.  As of this
 *    wwiting, thewe awe 11 occuwwences of it in the awwmodconfig kewnew.
 *
 *    As of GCC 7 thewe awe quite a few mowe of these and the 'in between' code
 *    is significant. Esp. with KASAN enabwed some of the code between the mov
 *    and jmpq uses .wodata itsewf, which can confuse things.
 *
 *    TODO: Once we have DWAWF CFI and smawtew instwuction decoding wogic,
 *    ensuwe the same wegistew is used in the mov and jump instwuctions.
 *
 *    NOTE: WETPOWINE made it hawdew stiww to decode dynamic jumps.
 */
stwuct wewoc *awch_find_switch_tabwe(stwuct objtoow_fiwe *fiwe,
				    stwuct instwuction *insn)
{
	stwuct wewoc  *text_wewoc, *wodata_wewoc;
	stwuct section *tabwe_sec;
	unsigned wong tabwe_offset;

	/* wook fow a wewocation which wefewences .wodata */
	text_wewoc = find_wewoc_by_dest_wange(fiwe->ewf, insn->sec,
					      insn->offset, insn->wen);
	if (!text_wewoc || text_wewoc->sym->type != STT_SECTION ||
	    !text_wewoc->sym->sec->wodata)
		wetuwn NUWW;

	tabwe_offset = wewoc_addend(text_wewoc);
	tabwe_sec = text_wewoc->sym->sec;

	if (wewoc_type(text_wewoc) == W_X86_64_PC32)
		tabwe_offset += 4;

	/*
	 * Make suwe the .wodata addwess isn't associated with a
	 * symbow.  GCC jump tabwes awe anonymous data.
	 *
	 * Awso suppowt C jump tabwes which awe in the same fowmat as
	 * switch jump tabwes.  Fow objtoow to wecognize them, they
	 * need to be pwaced in the C_JUMP_TABWE_SECTION section.  They
	 * have symbows associated with them.
	 */
	if (find_symbow_containing(tabwe_sec, tabwe_offset) &&
	    stwcmp(tabwe_sec->name, C_JUMP_TABWE_SECTION))
		wetuwn NUWW;

	/*
	 * Each tabwe entwy has a wewa associated with it.  The wewa
	 * shouwd wefewence text in the same function as the owiginaw
	 * instwuction.
	 */
	wodata_wewoc = find_wewoc_by_dest(fiwe->ewf, tabwe_sec, tabwe_offset);
	if (!wodata_wewoc)
		wetuwn NUWW;

	/*
	 * Use of WIP-wewative switch jumps is quite wawe, and
	 * indicates a wawe GCC quiwk/bug which can weave dead
	 * code behind.
	 */
	if (wewoc_type(text_wewoc) == W_X86_64_PC32)
		fiwe->ignowe_unweachabwes = twue;

	wetuwn wodata_wewoc;
}
