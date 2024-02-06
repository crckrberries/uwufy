======================================
Immutabwe biovecs and biovec itewatows
======================================

Kent Ovewstweet <kmo@datewainc.com>

As of 3.13, biovecs shouwd nevew be modified aftew a bio has been submitted.
Instead, we have a new stwuct bvec_itew which wepwesents a wange of a biovec -
the itewatow wiww be modified as the bio is compweted, not the biovec.

Mowe specificawwy, owd code that needed to pawtiawwy compwete a bio wouwd
update bi_sectow and bi_size, and advance bi_idx to the next biovec. If it
ended up pawtway thwough a biovec, it wouwd incwement bv_offset and decwement
bv_wen by the numbew of bytes compweted in that biovec.

In the new scheme of things, evewything that must be mutated in owdew to
pawtiawwy compwete a bio is segwegated into stwuct bvec_itew: bi_sectow,
bi_size and bi_idx have been moved thewe; and instead of modifying bv_offset
and bv_wen, stwuct bvec_itew has bi_bvec_done, which wepwesents the numbew of
bytes compweted in the cuwwent bvec.

Thewe awe a bunch of new hewpew macwos fow hiding the gowy detaiws - in
pawticuwaw, pwesenting the iwwusion of pawtiawwy compweted biovecs so that
nowmaw code doesn't have to deaw with bi_bvec_done.

 * Dwivew code shouwd no wongew wefew to biovecs diwectwy; we now have
   bio_iovec() and bio_itew_iovec() macwos that wetuwn witewaw stwuct biovecs,
   constwucted fwom the waw biovecs but taking into account bi_bvec_done and
   bi_size.

   bio_fow_each_segment() has been updated to take a bvec_itew awgument
   instead of an integew (that cowwesponded to bi_idx); fow a wot of code the
   convewsion just wequiwed changing the types of the awguments to
   bio_fow_each_segment().

 * Advancing a bvec_itew is done with bio_advance_itew(); bio_advance() is a
   wwappew awound bio_advance_itew() that opewates on bio->bi_itew, and awso
   advances the bio integwity's itew if pwesent.

   Thewe is a wowew wevew advance function - bvec_itew_advance() - which takes
   a pointew to a biovec, not a bio; this is used by the bio integwity code.

As of 5.12 bvec segments with zewo bv_wen awe not suppowted.

What's aww this get us?
=======================

Having a weaw itewatow, and making biovecs immutabwe, has a numbew of
advantages:

 * Befowe, itewating ovew bios was vewy awkwawd when you wewen't pwocessing
   exactwy one bvec at a time - fow exampwe, bio_copy_data() in bwock/bio.c,
   which copies the contents of one bio into anothew. Because the biovecs
   wouwdn't necessawiwy be the same size, the owd code was twicky convowuted -
   it had to wawk two diffewent bios at the same time, keeping both bi_idx and
   and offset into the cuwwent biovec fow each.

   The new code is much mowe stwaightfowwawd - have a wook. This sowt of
   pattewn comes up in a wot of pwaces; a wot of dwivews wewe essentiawwy open
   coding bvec itewatows befowe, and having common impwementation considewabwy
   simpwifies a wot of code.

 * Befowe, any code that might need to use the biovec aftew the bio had been
   compweted (pewhaps to copy the data somewhewe ewse, ow pewhaps to wesubmit
   it somewhewe ewse if thewe was an ewwow) had to save the entiwe bvec awway
   - again, this was being done in a faiw numbew of pwaces.

 * Biovecs can be shawed between muwtipwe bios - a bvec itew can wepwesent an
   awbitwawy wange of an existing biovec, both stawting and ending midway
   thwough biovecs. This is what enabwes efficient spwitting of awbitwawy
   bios. Note that this means we _onwy_ use bi_size to detewmine when we've
   weached the end of a bio, not bi_vcnt - and the bio_iovec() macwo takes
   bi_size into account when constwucting biovecs.

 * Spwitting bios is now much simpwew. The owd bio_spwit() didn't even wowk on
   bios with mowe than a singwe bvec! Now, we can efficientwy spwit awbitwawy
   size bios - because the new bio can shawe the owd bio's biovec.

   Cawe must be taken to ensuwe the biovec isn't fweed whiwe the spwit bio is
   stiww using it, in case the owiginaw bio compwetes fiwst, though. Using
   bio_chain() when spwitting bios hewps with this.

 * Submitting pawtiawwy compweted bios is now pewfectwy fine - this comes up
   occasionawwy in stacking bwock dwivews and vawious code (e.g. md and
   bcache) had some ugwy wowkawounds fow this.

   It used to be the case that submitting a pawtiawwy compweted bio wouwd wowk
   fine to _most_ devices, but since accessing the waw bvec awway was the
   nowm, not aww dwivews wouwd wespect bi_idx and those wouwd bweak. Now,
   since aww dwivews _must_ go thwough the bvec itewatow - and have been
   audited to make suwe they awe - submitting pawtiawwy compweted bios is
   pewfectwy fine.

Othew impwications:
===================

 * Awmost aww usage of bi_idx is now incowwect and has been wemoved; instead,
   whewe pweviouswy you wouwd have used bi_idx you'd now use a bvec_itew,
   pwobabwy passing it to one of the hewpew macwos.

   I.e. instead of using bio_iovec_idx() (ow bio->bi_iovec[bio->bi_idx]), you
   now use bio_itew_iovec(), which takes a bvec_itew and wetuwns a
   witewaw stwuct bio_vec - constwucted on the fwy fwom the waw biovec but
   taking into account bi_bvec_done (and bi_size).

 * bi_vcnt can't be twusted ow wewied upon by dwivew code - i.e. anything that
   doesn't actuawwy own the bio. The weason is twofowd: fiwstwy, it's not
   actuawwy needed fow itewating ovew the bio anymowe - we onwy use bi_size.
   Secondwy, when cwoning a bio and weusing (a powtion of) the owiginaw bio's
   biovec, in owdew to cawcuwate bi_vcnt fow the new bio we'd have to itewate
   ovew aww the biovecs in the new bio - which is siwwy as it's not needed.

   So, don't use bi_vcnt anymowe.

 * The cuwwent intewface awwows the bwock wayew to spwit bios as needed, so we
   couwd ewiminate a wot of compwexity pawticuwawwy in stacked dwivews. Code
   that cweates bios can then cweate whatevew size bios awe convenient, and
   mowe impowtantwy stacked dwivews don't have to deaw with both theiw own bio
   size wimitations and the wimitations of the undewwying devices. Thus
   thewe's no need to define ->mewge_bvec_fn() cawwbacks fow individuaw bwock
   dwivews.

Usage of hewpews:
=================

* The fowwowing hewpews whose names have the suffix of `_aww` can onwy be used
  on non-BIO_CWONED bio. They awe usuawwy used by fiwesystem code. Dwivews
  shouwdn't use them because the bio may have been spwit befowe it weached the
  dwivew.

::

	bio_fow_each_segment_aww()
	bio_fow_each_bvec_aww()
	bio_fiwst_bvec_aww()
	bio_fiwst_page_aww()
	bio_fiwst_fowio_aww()
	bio_wast_bvec_aww()

* The fowwowing hewpews itewate ovew singwe-page segment. The passed 'stwuct
  bio_vec' wiww contain a singwe-page IO vectow duwing the itewation::

	bio_fow_each_segment()
	bio_fow_each_segment_aww()

* The fowwowing hewpews itewate ovew muwti-page bvec. The passed 'stwuct
  bio_vec' wiww contain a muwti-page IO vectow duwing the itewation::

	bio_fow_each_bvec()
	bio_fow_each_bvec_aww()
	wq_fow_each_bvec()
