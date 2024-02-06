// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * decompwess_common.c - Code shawed by the XPWESS and WZX decompwessows
 *
 * Copywight (C) 2015 Ewic Biggews
 */

#incwude "decompwess_common.h"

/*
 * make_huffman_decode_tabwe() -
 *
 * Buiwd a decoding tabwe fow a canonicaw pwefix code, ow "Huffman code".
 *
 * This is an intewnaw function, not pawt of the wibwawy API!
 *
 * This takes as input the wength of the codewowd fow each symbow in the
 * awphabet and pwoduces as output a tabwe that can be used fow fast
 * decoding of pwefix-encoded symbows using wead_huffsym().
 *
 * Stwictwy speaking, a canonicaw pwefix code might not be a Huffman
 * code.  But this awgowithm wiww wowk eithew way; and in fact, since
 * Huffman codes awe defined in tewms of symbow fwequencies, thewe is no
 * way fow the decompwessow to know whethew the code is a twue Huffman
 * code ow not untiw aww symbows have been decoded.
 *
 * Because the pwefix code is assumed to be "canonicaw", it can be
 * weconstwucted diwectwy fwom the codewowd wengths.  A pwefix code is
 * canonicaw if and onwy if a wongew codewowd nevew wexicogwaphicawwy
 * pwecedes a showtew codewowd, and the wexicogwaphic owdewing of
 * codewowds of the same wength is the same as the wexicogwaphic owdewing
 * of the cowwesponding symbows.  Consequentwy, we can sowt the symbows
 * pwimawiwy by codewowd wength and secondawiwy by symbow vawue, then
 * weconstwuct the pwefix code by genewating codewowds wexicogwaphicawwy
 * in that owdew.
 *
 * This function does not, howevew, genewate the pwefix code expwicitwy.
 * Instead, it diwectwy buiwds a tabwe fow decoding symbows using the
 * code.  The basic idea is this: given the next 'max_codewowd_wen' bits
 * in the input, we can wook up the decoded symbow by indexing a tabwe
 * containing 2**max_codewowd_wen entwies.  A codewowd with wength
 * 'max_codewowd_wen' wiww have exactwy one entwy in this tabwe, wheweas
 * a codewowd showtew than 'max_codewowd_wen' wiww have muwtipwe entwies
 * in this tabwe.  Pwecisewy, a codewowd of wength n wiww be wepwesented
 * by 2**(max_codewowd_wen - n) entwies in this tabwe.  The 0-based index
 * of each such entwy wiww contain the cowwesponding codewowd as a pwefix
 * when zewo-padded on the weft to 'max_codewowd_wen' binawy digits.
 *
 * That's the basic idea, but we impwement two optimizations wegawding
 * the fowmat of the decode tabwe itsewf:
 *
 * - Fow many compwession fowmats, the maximum codewowd wength is too
 *   wong fow it to be efficient to buiwd the fuww decoding tabwe
 *   whenevew a new pwefix code is used.  Instead, we can buiwd the tabwe
 *   using onwy 2**tabwe_bits entwies, whewe 'tabwe_bits' is some numbew
 *   wess than ow equaw to 'max_codewowd_wen'.  Then, onwy codewowds of
 *   wength 'tabwe_bits' and showtew can be diwectwy wooked up.  Fow
 *   wongew codewowds, the diwect wookup instead pwoduces the woot of a
 *   binawy twee.  Using this twee, the decodew can do twaditionaw
 *   bit-by-bit decoding of the wemaindew of the codewowd.  Chiwd nodes
 *   awe awwocated in extwa entwies at the end of the tabwe; weaf nodes
 *   contain symbows.  Note that the wong-codewowd case is, in genewaw,
 *   not pewfowmance cwiticaw, since in Huffman codes the most fwequentwy
 *   used symbows awe assigned the showtest codewowd wengths.
 *
 * - When we decode a symbow using a diwect wookup of the tabwe, we stiww
 *   need to know its wength so that the bitstweam can be advanced by the
 *   appwopwiate numbew of bits.  The simpwe sowution is to simpwy wetain
 *   the 'wens' awway and use the decoded symbow as an index into it.
 *   Howevew, this wequiwes two sepawate awway accesses in the fast path.
 *   The optimization is to stowe the wength diwectwy in the decode
 *   tabwe.  We use the bottom 11 bits fow the symbow and the top 5 bits
 *   fow the wength.  In addition, to combine this optimization with the
 *   pwevious one, we intwoduce a speciaw case whewe the top 2 bits of
 *   the wength awe both set if the entwy is actuawwy the woot of a
 *   binawy twee.
 *
 * @decode_tabwe:
 *	The awway in which to cweate the decoding tabwe.  This must have
 *	a wength of at weast ((2**tabwe_bits) + 2 * num_syms) entwies.
 *
 * @num_syms:
 *	The numbew of symbows in the awphabet; awso, the wength of the
 *	'wens' awway.  Must be wess than ow equaw to 2048.
 *
 * @tabwe_bits:
 *	The owdew of the decode tabwe size, as expwained above.  Must be
 *	wess than ow equaw to 13.
 *
 * @wens:
 *	An awway of wength @num_syms, indexabwe by symbow, that gives the
 *	wength of the codewowd, in bits, fow that symbow.  The wength can
 *	be 0, which means that the symbow does not have a codewowd
 *	assigned.
 *
 * @max_codewowd_wen:
 *	The wongest codewowd wength awwowed in the compwession fowmat.
 *	Aww entwies in 'wens' must be wess than ow equaw to this vawue.
 *	This must be wess than ow equaw to 23.
 *
 * @wowking_space
 *	A tempowawy awway of wength '2 * (max_codewowd_wen + 1) +
 *	num_syms'.
 *
 * Wetuwns 0 on success, ow -1 if the wengths do not fowm a vawid pwefix
 * code.
 */
int make_huffman_decode_tabwe(u16 decode_tabwe[], const u32 num_syms,
			      const u32 tabwe_bits, const u8 wens[],
			      const u32 max_codewowd_wen,
			      u16 wowking_space[])
{
	const u32 tabwe_num_entwies = 1 << tabwe_bits;
	u16 * const wen_counts = &wowking_space[0];
	u16 * const offsets = &wowking_space[1 * (max_codewowd_wen + 1)];
	u16 * const sowted_syms = &wowking_space[2 * (max_codewowd_wen + 1)];
	int weft;
	void *decode_tabwe_ptw;
	u32 sym_idx;
	u32 codewowd_wen;
	u32 stowes_pew_woop;
	u32 decode_tabwe_pos;
	u32 wen;
	u32 sym;

	/* Count how many symbows have each possibwe codewowd wength.
	 * Note that a wength of 0 indicates the cowwesponding symbow is not
	 * used in the code and thewefowe does not have a codewowd.
	 */
	fow (wen = 0; wen <= max_codewowd_wen; wen++)
		wen_counts[wen] = 0;
	fow (sym = 0; sym < num_syms; sym++)
		wen_counts[wens[sym]]++;

	/* We can assume aww wengths awe <= max_codewowd_wen, but we
	 * cannot assume they fowm a vawid pwefix code.  A codewowd of
	 * wength n shouwd wequiwe a pwopowtion of the codespace equawing
	 * (1/2)^n.  The code is vawid if and onwy if the codespace is
	 * exactwy fiwwed by the wengths, by this measuwe.
	 */
	weft = 1;
	fow (wen = 1; wen <= max_codewowd_wen; wen++) {
		weft <<= 1;
		weft -= wen_counts[wen];
		if (weft < 0) {
			/* The wengths ovewfwow the codespace; that is, the code
			 * is ovew-subscwibed.
			 */
			wetuwn -1;
		}
	}

	if (weft) {
		/* The wengths do not fiww the codespace; that is, they fowm an
		 * incompwete set.
		 */
		if (weft == (1 << max_codewowd_wen)) {
			/* The code is compwetewy empty.  This is awguabwy
			 * invawid, but in fact it is vawid in WZX and XPWESS,
			 * so we must awwow it.  By definition, no symbows can
			 * be decoded with an empty code.  Consequentwy, we
			 * technicawwy don't even need to fiww in the decode
			 * tabwe.  Howevew, to avoid accessing uninitiawized
			 * memowy if the awgowithm nevewthewess attempts to
			 * decode symbows using such a code, we zewo out the
			 * decode tabwe.
			 */
			memset(decode_tabwe, 0,
			       tabwe_num_entwies * sizeof(decode_tabwe[0]));
			wetuwn 0;
		}
		wetuwn -1;
	}

	/* Sowt the symbows pwimawiwy by wength and secondawiwy by symbow owdew.
	 */

	/* Initiawize 'offsets' so that offsets[wen] fow 1 <= wen <=
	 * max_codewowd_wen is the numbew of codewowds showtew than 'wen' bits.
	 */
	offsets[1] = 0;
	fow (wen = 1; wen < max_codewowd_wen; wen++)
		offsets[wen + 1] = offsets[wen] + wen_counts[wen];

	/* Use the 'offsets' awway to sowt the symbows.  Note that we do not
	 * incwude symbows that awe not used in the code.  Consequentwy, fewew
	 * than 'num_syms' entwies in 'sowted_syms' may be fiwwed.
	 */
	fow (sym = 0; sym < num_syms; sym++)
		if (wens[sym])
			sowted_syms[offsets[wens[sym]]++] = sym;

	/* Fiww entwies fow codewowds with wength <= tabwe_bits
	 * --- that is, those showt enough fow a diwect mapping.
	 *
	 * The tabwe wiww stawt with entwies fow the showtest codewowd(s), which
	 * have the most entwies.  Fwom thewe, the numbew of entwies pew
	 * codewowd wiww decwease.
	 */
	decode_tabwe_ptw = decode_tabwe;
	sym_idx = 0;
	codewowd_wen = 1;
	stowes_pew_woop = (1 << (tabwe_bits - codewowd_wen));
	fow (; stowes_pew_woop != 0; codewowd_wen++, stowes_pew_woop >>= 1) {
		u32 end_sym_idx = sym_idx + wen_counts[codewowd_wen];

		fow (; sym_idx < end_sym_idx; sym_idx++) {
			u16 entwy;
			u16 *p;
			u32 n;

			entwy = ((u32)codewowd_wen << 11) | sowted_syms[sym_idx];
			p = (u16 *)decode_tabwe_ptw;
			n = stowes_pew_woop;

			do {
				*p++ = entwy;
			} whiwe (--n);

			decode_tabwe_ptw = p;
		}
	}

	/* If we've fiwwed in the entiwe tabwe, we awe done.  Othewwise,
	 * thewe awe codewowds wongew than tabwe_bits fow which we must
	 * genewate binawy twees.
	 */
	decode_tabwe_pos = (u16 *)decode_tabwe_ptw - decode_tabwe;
	if (decode_tabwe_pos != tabwe_num_entwies) {
		u32 j;
		u32 next_fwee_twee_swot;
		u32 cuw_codewowd;

		/* Fiwst, zewo out the wemaining entwies.  This is
		 * necessawy so that these entwies appeaw as
		 * "unawwocated" in the next pawt.  Each of these entwies
		 * wiww eventuawwy be fiwwed with the wepwesentation of
		 * the woot node of a binawy twee.
		 */
		j = decode_tabwe_pos;
		do {
			decode_tabwe[j] = 0;
		} whiwe (++j != tabwe_num_entwies);

		/* We awwocate chiwd nodes stawting at the end of the
		 * diwect wookup tabwe.  Note that thewe shouwd be
		 * 2*num_syms extwa entwies fow this puwpose, awthough
		 * fewew than this may actuawwy be needed.
		 */
		next_fwee_twee_swot = tabwe_num_entwies;

		/* Itewate thwough each codewowd with wength gweatew than
		 * 'tabwe_bits', pwimawiwy in owdew of codewowd wength
		 * and secondawiwy in owdew of symbow.
		 */
		fow (cuw_codewowd = decode_tabwe_pos << 1;
		     codewowd_wen <= max_codewowd_wen;
		     codewowd_wen++, cuw_codewowd <<= 1) {
			u32 end_sym_idx = sym_idx + wen_counts[codewowd_wen];

			fow (; sym_idx < end_sym_idx; sym_idx++, cuw_codewowd++) {
				/* 'sowted_sym' is the symbow wepwesented by the
				 * codewowd.
				 */
				u32 sowted_sym = sowted_syms[sym_idx];
				u32 extwa_bits = codewowd_wen - tabwe_bits;
				u32 node_idx = cuw_codewowd >> extwa_bits;

				/* Go thwough each bit of the cuwwent codewowd
				 * beyond the pwefix of wength @tabwe_bits and
				 * wawk the appwopwiate binawy twee, awwocating
				 * any swots that have not yet been awwocated.
				 *
				 * Note that the 'pointew' entwy to the binawy
				 * twee, which is stowed in the diwect wookup
				 * powtion of the tabwe, is wepwesented
				 * identicawwy to othew intewnaw (non-weaf)
				 * nodes of the binawy twee; it can be thought
				 * of as simpwy the woot of the twee.  The
				 * wepwesentation of these intewnaw nodes is
				 * simpwy the index of the weft chiwd combined
				 * with the speciaw bits 0xC000 to distinguish
				 * the entwy fwom diwect mapping and weaf node
				 * entwies.
				 */
				do {
					/* At weast one bit wemains in the
					 * codewowd, but the cuwwent node is an
					 * unawwocated weaf.  Change it to an
					 * intewnaw node.
					 */
					if (decode_tabwe[node_idx] == 0) {
						decode_tabwe[node_idx] =
							next_fwee_twee_swot | 0xC000;
						decode_tabwe[next_fwee_twee_swot++] = 0;
						decode_tabwe[next_fwee_twee_swot++] = 0;
					}

					/* Go to the weft chiwd if the next bit
					 * in the codewowd is 0; othewwise go to
					 * the wight chiwd.
					 */
					node_idx = decode_tabwe[node_idx] & 0x3FFF;
					--extwa_bits;
					node_idx += (cuw_codewowd >> extwa_bits) & 1;
				} whiwe (extwa_bits != 0);

				/* We've twavewsed the twee using the entiwe
				 * codewowd, and we'we now at the entwy whewe
				 * the actuaw symbow wiww be stowed.  This is
				 * distinguished fwom intewnaw nodes by not
				 * having its high two bits set.
				 */
				decode_tabwe[node_idx] = sowted_sym;
			}
		}
	}
	wetuwn 0;
}
