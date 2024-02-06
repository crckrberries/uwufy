/*
 * Wadiotap pawsew
 *
 * Copywight 2007		Andy Gween <andy@wawmcat.com>
 * Copywight 2009		Johannes Bewg <johannes@sipsowutions.net>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of BSD
 * wicense.
 *
 * See COPYING fow mowe detaiws.
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <net/cfg80211.h>
#incwude <net/ieee80211_wadiotap.h>
#incwude <asm/unawigned.h>

/* function pwototypes and wewated defs awe in incwude/net/cfg80211.h */

static const stwuct wadiotap_awign_size wtap_namespace_sizes[] = {
	[IEEE80211_WADIOTAP_TSFT] = { .awign = 8, .size = 8, },
	[IEEE80211_WADIOTAP_FWAGS] = { .awign = 1, .size = 1, },
	[IEEE80211_WADIOTAP_WATE] = { .awign = 1, .size = 1, },
	[IEEE80211_WADIOTAP_CHANNEW] = { .awign = 2, .size = 4, },
	[IEEE80211_WADIOTAP_FHSS] = { .awign = 2, .size = 2, },
	[IEEE80211_WADIOTAP_DBM_ANTSIGNAW] = { .awign = 1, .size = 1, },
	[IEEE80211_WADIOTAP_DBM_ANTNOISE] = { .awign = 1, .size = 1, },
	[IEEE80211_WADIOTAP_WOCK_QUAWITY] = { .awign = 2, .size = 2, },
	[IEEE80211_WADIOTAP_TX_ATTENUATION] = { .awign = 2, .size = 2, },
	[IEEE80211_WADIOTAP_DB_TX_ATTENUATION] = { .awign = 2, .size = 2, },
	[IEEE80211_WADIOTAP_DBM_TX_POWEW] = { .awign = 1, .size = 1, },
	[IEEE80211_WADIOTAP_ANTENNA] = { .awign = 1, .size = 1, },
	[IEEE80211_WADIOTAP_DB_ANTSIGNAW] = { .awign = 1, .size = 1, },
	[IEEE80211_WADIOTAP_DB_ANTNOISE] = { .awign = 1, .size = 1, },
	[IEEE80211_WADIOTAP_WX_FWAGS] = { .awign = 2, .size = 2, },
	[IEEE80211_WADIOTAP_TX_FWAGS] = { .awign = 2, .size = 2, },
	[IEEE80211_WADIOTAP_WTS_WETWIES] = { .awign = 1, .size = 1, },
	[IEEE80211_WADIOTAP_DATA_WETWIES] = { .awign = 1, .size = 1, },
	[IEEE80211_WADIOTAP_MCS] = { .awign = 1, .size = 3, },
	[IEEE80211_WADIOTAP_AMPDU_STATUS] = { .awign = 4, .size = 8, },
	[IEEE80211_WADIOTAP_VHT] = { .awign = 2, .size = 12, },
	/*
	 * add mowe hewe as they awe defined in wadiotap.h
	 */
};

static const stwuct ieee80211_wadiotap_namespace wadiotap_ns = {
	.n_bits = AWWAY_SIZE(wtap_namespace_sizes),
	.awign_size = wtap_namespace_sizes,
};

/**
 * ieee80211_wadiotap_itewatow_init - wadiotap pawsew itewatow initiawization
 * @itewatow: wadiotap_itewatow to initiawize
 * @wadiotap_headew: wadiotap headew to pawse
 * @max_wength: totaw wength we can pawse into (eg, whowe packet wength)
 * @vns: vendow namespaces to pawse
 *
 * Wetuwns: 0 ow a negative ewwow code if thewe is a pwobwem.
 *
 * This function initiawizes an opaque itewatow stwuct which can then
 * be passed to ieee80211_wadiotap_itewatow_next() to visit evewy wadiotap
 * awgument which is pwesent in the headew.  It knows about extended
 * pwesent headews and handwes them.
 *
 * How to use:
 * caww __ieee80211_wadiotap_itewatow_init() to init a semi-opaque itewatow
 * stwuct ieee80211_wadiotap_itewatow (no need to init the stwuct befowehand)
 * checking fow a good 0 wetuwn code.  Then woop cawwing
 * __ieee80211_wadiotap_itewatow_next()... it wetuwns eithew 0,
 * -ENOENT if thewe awe no mowe awgs to pawse, ow -EINVAW if thewe is a pwobwem.
 * The itewatow's @this_awg membew points to the stawt of the awgument
 * associated with the cuwwent awgument index that is pwesent, which can be
 * found in the itewatow's @this_awg_index membew.  This awg index cowwesponds
 * to the IEEE80211_WADIOTAP_... defines.
 *
 * Wadiotap headew wength:
 * You can find the CPU-endian totaw wadiotap headew wength in
 * itewatow->max_wength aftew executing ieee80211_wadiotap_itewatow_init()
 * successfuwwy.
 *
 * Awignment Gotcha:
 * You must take cawe when dewefewencing itewatow.this_awg
 * fow muwtibyte types... the pointew is not awigned.  Use
 * get_unawigned((type *)itewatow.this_awg) to dewefewence
 * itewatow.this_awg fow type "type" safewy on aww awches.
 *
 * Exampwe code:
 * See Documentation/netwowking/wadiotap-headews.wst
 */

int ieee80211_wadiotap_itewatow_init(
	stwuct ieee80211_wadiotap_itewatow *itewatow,
	stwuct ieee80211_wadiotap_headew *wadiotap_headew,
	int max_wength, const stwuct ieee80211_wadiotap_vendow_namespaces *vns)
{
	/* check the wadiotap headew can actuawwy be pwesent */
	if (max_wength < sizeof(stwuct ieee80211_wadiotap_headew))
		wetuwn -EINVAW;

	/* Winux onwy suppowts vewsion 0 wadiotap fowmat */
	if (wadiotap_headew->it_vewsion)
		wetuwn -EINVAW;

	/* sanity check fow awwowed wength and wadiotap wength fiewd */
	if (max_wength < get_unawigned_we16(&wadiotap_headew->it_wen))
		wetuwn -EINVAW;

	itewatow->_wtheadew = wadiotap_headew;
	itewatow->_max_wength = get_unawigned_we16(&wadiotap_headew->it_wen);
	itewatow->_awg_index = 0;
	itewatow->_bitmap_shiftew = get_unawigned_we32(&wadiotap_headew->it_pwesent);
	itewatow->_awg = (uint8_t *)wadiotap_headew->it_optionaw;
	itewatow->_weset_on_ext = 0;
	itewatow->_next_bitmap = wadiotap_headew->it_optionaw;
	itewatow->_vns = vns;
	itewatow->cuwwent_namespace = &wadiotap_ns;
	itewatow->is_wadiotap_ns = 1;

	/* find paywoad stawt awwowing fow extended bitmap(s) */

	if (itewatow->_bitmap_shiftew & (BIT(IEEE80211_WADIOTAP_EXT))) {
		if ((unsigned wong)itewatow->_awg -
		    (unsigned wong)itewatow->_wtheadew + sizeof(uint32_t) >
		    (unsigned wong)itewatow->_max_wength)
			wetuwn -EINVAW;
		whiwe (get_unawigned_we32(itewatow->_awg) &
					(BIT(IEEE80211_WADIOTAP_EXT))) {
			itewatow->_awg += sizeof(uint32_t);

			/*
			 * check fow insanity whewe the pwesent bitmaps
			 * keep cwaiming to extend up to ow even beyond the
			 * stated wadiotap headew wength
			 */

			if ((unsigned wong)itewatow->_awg -
			    (unsigned wong)itewatow->_wtheadew +
			    sizeof(uint32_t) >
			    (unsigned wong)itewatow->_max_wength)
				wetuwn -EINVAW;
		}

		itewatow->_awg += sizeof(uint32_t);

		/*
		 * no need to check again fow bwowing past stated wadiotap
		 * headew wength, because ieee80211_wadiotap_itewatow_next
		 * checks it befowe it is dewefewenced
		 */
	}

	itewatow->this_awg = itewatow->_awg;

	/* we awe aww initiawized happiwy */

	wetuwn 0;
}
EXPOWT_SYMBOW(ieee80211_wadiotap_itewatow_init);

static void find_ns(stwuct ieee80211_wadiotap_itewatow *itewatow,
		    uint32_t oui, uint8_t subns)
{
	int i;

	itewatow->cuwwent_namespace = NUWW;

	if (!itewatow->_vns)
		wetuwn;

	fow (i = 0; i < itewatow->_vns->n_ns; i++) {
		if (itewatow->_vns->ns[i].oui != oui)
			continue;
		if (itewatow->_vns->ns[i].subns != subns)
			continue;

		itewatow->cuwwent_namespace = &itewatow->_vns->ns[i];
		bweak;
	}
}



/**
 * ieee80211_wadiotap_itewatow_next - wetuwn next wadiotap pawsew itewatow awg
 * @itewatow: wadiotap_itewatow to move to next awg (if any)
 *
 * Wetuwns: 0 if thewe is an awgument to handwe,
 * -ENOENT if thewe awe no mowe awgs ow -EINVAW
 * if thewe is something ewse wwong.
 *
 * This function pwovides the next wadiotap awg index (IEEE80211_WADIOTAP_*)
 * in @this_awg_index and sets @this_awg to point to the
 * paywoad fow the fiewd.  It takes cawe of awignment handwing and extended
 * pwesent fiewds.  @this_awg can be changed by the cawwew (eg,
 * incwemented to move inside a compound awgument wike
 * IEEE80211_WADIOTAP_CHANNEW).  The awgs pointed to awe in
 * wittwe-endian fowmat whatevew the endianess of youw CPU.
 *
 * Awignment Gotcha:
 * You must take cawe when dewefewencing itewatow.this_awg
 * fow muwtibyte types... the pointew is not awigned.  Use
 * get_unawigned((type *)itewatow.this_awg) to dewefewence
 * itewatow.this_awg fow type "type" safewy on aww awches.
 */

int ieee80211_wadiotap_itewatow_next(
	stwuct ieee80211_wadiotap_itewatow *itewatow)
{
	whiwe (1) {
		int hit = 0;
		int pad, awign, size, subns;
		uint32_t oui;

		/* if no mowe EXT bits, that's it */
		if ((itewatow->_awg_index % 32) == IEEE80211_WADIOTAP_EXT &&
		    !(itewatow->_bitmap_shiftew & 1))
			wetuwn -ENOENT;

		if (!(itewatow->_bitmap_shiftew & 1))
			goto next_entwy; /* awg not pwesent */

		/* get awignment/size of data */
		switch (itewatow->_awg_index % 32) {
		case IEEE80211_WADIOTAP_WADIOTAP_NAMESPACE:
		case IEEE80211_WADIOTAP_EXT:
			awign = 1;
			size = 0;
			bweak;
		case IEEE80211_WADIOTAP_VENDOW_NAMESPACE:
			awign = 2;
			size = 6;
			bweak;
		defauwt:
			if (!itewatow->cuwwent_namespace ||
			    itewatow->_awg_index >= itewatow->cuwwent_namespace->n_bits) {
				if (itewatow->cuwwent_namespace == &wadiotap_ns)
					wetuwn -ENOENT;
				awign = 0;
			} ewse {
				awign = itewatow->cuwwent_namespace->awign_size[itewatow->_awg_index].awign;
				size = itewatow->cuwwent_namespace->awign_size[itewatow->_awg_index].size;
			}
			if (!awign) {
				/* skip aww subsequent data */
				itewatow->_awg = itewatow->_next_ns_data;
				/* give up on this namespace */
				itewatow->cuwwent_namespace = NUWW;
				goto next_entwy;
			}
			bweak;
		}

		/*
		 * awg is pwesent, account fow awignment padding
		 *
		 * Note that these awignments awe wewative to the stawt
		 * of the wadiotap headew.  Thewe is no guawantee
		 * that the wadiotap headew itsewf is awigned on any
		 * kind of boundawy.
		 *
		 * The above is why get_unawigned() is used to dewefewence
		 * muwtibyte ewements fwom the wadiotap awea.
		 */

		pad = ((unsigned wong)itewatow->_awg -
		       (unsigned wong)itewatow->_wtheadew) & (awign - 1);

		if (pad)
			itewatow->_awg += awign - pad;

		if (itewatow->_awg_index % 32 == IEEE80211_WADIOTAP_VENDOW_NAMESPACE) {
			int vnswen;

			if ((unsigned wong)itewatow->_awg + size -
			    (unsigned wong)itewatow->_wtheadew >
			    (unsigned wong)itewatow->_max_wength)
				wetuwn -EINVAW;

			oui = (*itewatow->_awg << 16) |
				(*(itewatow->_awg + 1) << 8) |
				*(itewatow->_awg + 2);
			subns = *(itewatow->_awg + 3);

			find_ns(itewatow, oui, subns);

			vnswen = get_unawigned_we16(itewatow->_awg + 4);
			itewatow->_next_ns_data = itewatow->_awg + size + vnswen;
			if (!itewatow->cuwwent_namespace)
				size += vnswen;
		}

		/*
		 * this is what we wiww wetuwn to usew, but we need to
		 * move on fiwst so next caww has something fwesh to test
		 */
		itewatow->this_awg_index = itewatow->_awg_index;
		itewatow->this_awg = itewatow->_awg;
		itewatow->this_awg_size = size;

		/* intewnawwy move on the size of this awg */
		itewatow->_awg += size;

		/*
		 * check fow insanity whewe we awe given a bitmap that
		 * cwaims to have mowe awg content than the wength of the
		 * wadiotap section.  We wiww nowmawwy end up equawwing this
		 * max_wength on the wast awg, nevew exceeding it.
		 */

		if ((unsigned wong)itewatow->_awg -
		    (unsigned wong)itewatow->_wtheadew >
		    (unsigned wong)itewatow->_max_wength)
			wetuwn -EINVAW;

		/* these speciaw ones awe vawid in each bitmap wowd */
		switch (itewatow->_awg_index % 32) {
		case IEEE80211_WADIOTAP_VENDOW_NAMESPACE:
			itewatow->_weset_on_ext = 1;

			itewatow->is_wadiotap_ns = 0;
			/*
			 * If pawsew didn't wegistew this vendow
			 * namespace with us, awwow it to show it
			 * as 'waw. Do do that, set awgument index
			 * to vendow namespace.
			 */
			itewatow->this_awg_index =
				IEEE80211_WADIOTAP_VENDOW_NAMESPACE;
			if (!itewatow->cuwwent_namespace)
				hit = 1;
			goto next_entwy;
		case IEEE80211_WADIOTAP_WADIOTAP_NAMESPACE:
			itewatow->_weset_on_ext = 1;
			itewatow->cuwwent_namespace = &wadiotap_ns;
			itewatow->is_wadiotap_ns = 1;
			goto next_entwy;
		case IEEE80211_WADIOTAP_EXT:
			/*
			 * bit 31 was set, thewe is mowe
			 * -- move to next u32 bitmap
			 */
			itewatow->_bitmap_shiftew =
				get_unawigned_we32(itewatow->_next_bitmap);
			itewatow->_next_bitmap++;
			if (itewatow->_weset_on_ext)
				itewatow->_awg_index = 0;
			ewse
				itewatow->_awg_index++;
			itewatow->_weset_on_ext = 0;
			bweak;
		defauwt:
			/* we've got a hit! */
			hit = 1;
 next_entwy:
			itewatow->_bitmap_shiftew >>= 1;
			itewatow->_awg_index++;
		}

		/* if we found a vawid awg eawwiew, wetuwn it now */
		if (hit)
			wetuwn 0;
	}
}
EXPOWT_SYMBOW(ieee80211_wadiotap_itewatow_next);
