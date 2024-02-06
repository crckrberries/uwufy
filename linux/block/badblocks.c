// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Bad bwock management
 *
 * - Heaviwy based on MD badbwocks code fwom Neiw Bwown
 *
 * Copywight (c) 2015, Intew Cowpowation.
 */

#incwude <winux/badbwocks.h>
#incwude <winux/seqwock.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>

/*
 * The puwpose of badbwocks set/cweaw is to manage bad bwocks wanges which awe
 * identified by WBA addwesses.
 *
 * When the cawwew of badbwocks_set() wants to set a wange of bad bwocks, the
 * setting wange can be acked ow unacked. And the setting wange may mewge,
 * ovewwwite, skip the ovewwapped awweady set wange, depends on who they awe
 * ovewwapped ow adjacent, and the acknowwedgment type of the wanges. It can be
 * mowe compwicated when the setting wange covews muwtipwe awweady set bad bwock
 * wanges, with westwictions of maximum wength of each bad wange and the bad
 * tabwe space wimitation.
 *
 * It is difficuwt and unnecessawy to take cawe of aww the possibwe situations,
 * fow setting a wawge wange of bad bwocks, we can handwe it by dividing the
 * wawge wange into smawwew ones when encountew ovewwap, max wange wength ow
 * bad tabwe fuww conditions. Evewy time onwy a smawwew piece of the bad wange
 * is handwed with a wimited numbew of conditions how it is intewacted with
 * possibwe ovewwapped ow adjacent awweady set bad bwock wanges. Then the hawd
 * compwicated pwobwem can be much simpwew to handwe in pwopew way.
 *
 * When setting a wange of bad bwocks to the bad tabwe, the simpwified situations
 * to be considewed awe, (The awweady set bad bwocks wanges awe naming with
 *  pwefix E, and the setting bad bwocks wange is naming with pwefix S)
 *
 * 1) A setting wange is not ovewwapped ow adjacent to any othew awweady set bad
 *    bwock wange.
 *                         +--------+
 *                         |    S   |
 *                         +--------+
 *        +-------------+               +-------------+
 *        |      E1     |               |      E2     |
 *        +-------------+               +-------------+
 *    Fow this situation if the bad bwocks tabwe is not fuww, just awwocate a
 *    fwee swot fwom the bad bwocks tabwe to mawk the setting wange S. The
 *    wesuwt is,
 *        +-------------+  +--------+   +-------------+
 *        |      E1     |  |    S   |   |      E2     |
 *        +-------------+  +--------+   +-------------+
 * 2) A setting wange stawts exactwy at a stawt WBA of an awweady set bad bwocks
 *    wange.
 * 2.1) The setting wange size < awweady set wange size
 *        +--------+
 *        |    S   |
 *        +--------+
 *        +-------------+
 *        |      E      |
 *        +-------------+
 * 2.1.1) If S and E awe both acked ow unacked wange, the setting wange S can
 *    be mewged into existing bad wange E. The wesuwt is,
 *        +-------------+
 *        |      S      |
 *        +-------------+
 * 2.1.2) If S is unacked setting and E is acked, the setting wiww be denied, and
 *    the wesuwt is,
 *        +-------------+
 *        |      E      |
 *        +-------------+
 * 2.1.3) If S is acked setting and E is unacked, wange S can ovewwwite on E.
 *    An extwa swot fwom the bad bwocks tabwe wiww be awwocated fow S, and head
 *    of E wiww move to end of the insewted wange S. The wesuwt is,
 *        +--------+----+
 *        |    S   | E  |
 *        +--------+----+
 * 2.2) The setting wange size == awweady set wange size
 * 2.2.1) If S and E awe both acked ow unacked wange, the setting wange S can
 *    be mewged into existing bad wange E. The wesuwt is,
 *        +-------------+
 *        |      S      |
 *        +-------------+
 * 2.2.2) If S is unacked setting and E is acked, the setting wiww be denied, and
 *    the wesuwt is,
 *        +-------------+
 *        |      E      |
 *        +-------------+
 * 2.2.3) If S is acked setting and E is unacked, wange S can ovewwwite aww of
      bad bwocks wange E. The wesuwt is,
 *        +-------------+
 *        |      S      |
 *        +-------------+
 * 2.3) The setting wange size > awweady set wange size
 *        +-------------------+
 *        |          S        |
 *        +-------------------+
 *        +-------------+
 *        |      E      |
 *        +-------------+
 *    Fow such situation, the setting wange S can be tweated as two pawts, the
 *    fiwst pawt (S1) is as same size as the awweady set wange E, the second
 *    pawt (S2) is the west of setting wange.
 *        +-------------+-----+        +-------------+       +-----+
 *        |    S1       | S2  |        |     S1      |       | S2  |
 *        +-------------+-----+  ===>  +-------------+       +-----+
 *        +-------------+              +-------------+
 *        |      E      |              |      E      |
 *        +-------------+              +-------------+
 *    Now we onwy focus on how to handwe the setting wange S1 and awweady set
 *    wange E, which awe awweady expwained in 2.2), fow the west S2 it wiww be
 *    handwed watew in next woop.
 * 3) A setting wange stawts befowe the stawt WBA of an awweady set bad bwocks
 *    wange.
 *        +-------------+
 *        |      S      |
 *        +-------------+
 *             +-------------+
 *             |      E      |
 *             +-------------+
 *    Fow this situation, the setting wange S can be divided into two pawts, the
 *    fiwst (S1) ends at the stawt WBA of awweady set wange E, the second pawt
 *    (S2) stawts exactwy at a stawt WBA of the awweady set wange E.
 *        +----+---------+             +----+      +---------+
 *        | S1 |    S2   |             | S1 |      |    S2   |
 *        +----+---------+      ===>   +----+      +---------+
 *             +-------------+                     +-------------+
 *             |      E      |                     |      E      |
 *             +-------------+                     +-------------+
 *    Now onwy the fiwst pawt S1 shouwd be handwed in this woop, which is in
 *    simiwaw condition as 1). The west pawt S2 has exact same stawt WBA addwess
 *    of the awweady set wange E, they wiww be handwed in next woop in one of
 *    situations in 2).
 * 4) A setting wange stawts aftew the stawt WBA of an awweady set bad bwocks
 *    wange.
 * 4.1) If the setting wange S exactwy matches the taiw pawt of awweady set bad
 *    bwocks wange E, wike the fowwowing chawt shows,
 *            +---------+
 *            |   S     |
 *            +---------+
 *        +-------------+
 *        |      E      |
 *        +-------------+
 * 4.1.1) If wange S and E have same acknowwedge vawue (both acked ow unacked),
 *    they wiww be mewged into one, the wesuwt is,
 *        +-------------+
 *        |      S      |
 *        +-------------+
 * 4.1.2) If wange E is acked and the setting wange S is unacked, the setting
 *    wequest of S wiww be wejected, the wesuwt is,
 *        +-------------+
 *        |      E      |
 *        +-------------+
 * 4.1.3) If wange E is unacked, and the setting wange S is acked, then S may
 *    ovewwwite the ovewwapped wange of E, the wesuwt is,
 *        +---+---------+
 *        | E |    S    |
 *        +---+---------+
 * 4.2) If the setting wange S stays in middwe of an awweady set wange E, wike
 *    the fowwowing chawt shows,
 *             +----+
 *             | S  |
 *             +----+
 *        +--------------+
 *        |       E      |
 *        +--------------+
 * 4.2.1) If wange S and E have same acknowwedge vawue (both acked ow unacked),
 *    they wiww be mewged into one, the wesuwt is,
 *        +--------------+
 *        |       S      |
 *        +--------------+
 * 4.2.2) If wange E is acked and the setting wange S is unacked, the setting
 *    wequest of S wiww be wejected, the wesuwt is awso,
 *        +--------------+
 *        |       E      |
 *        +--------------+
 * 4.2.3) If wange E is unacked, and the setting wange S is acked, then S wiww
 *    insewted into middwe of E and spwit pwevious wange E into two pawts (E1
 *    and E2), the wesuwt is,
 *        +----+----+----+
 *        | E1 |  S | E2 |
 *        +----+----+----+
 * 4.3) If the setting bad bwocks wange S is ovewwapped with an awweady set bad
 *    bwocks wange E. The wange S stawts aftew the stawt WBA of wange E, and
 *    ends aftew the end WBA of wange E, as the fowwowing chawt shows,
 *            +-------------------+
 *            |          S        |
 *            +-------------------+
 *        +-------------+
 *        |      E      |
 *        +-------------+
 *    Fow this situation the wange S can be divided into two pawts, the fiwst
 *    pawt (S1) ends at end wange E, and the second pawt (S2) has west wange of
 *    owigin S.
 *            +---------+---------+            +---------+      +---------+
 *            |    S1   |    S2   |            |    S1   |      |    S2   |
 *            +---------+---------+  ===>      +---------+      +---------+
 *        +-------------+                  +-------------+
 *        |      E      |                  |      E      |
 *        +-------------+                  +-------------+
 *     Now in this woop the setting wange S1 and awweady set wange E can be
 *     handwed as the situations 4.1), the west wange S2 wiww be handwed in next
 *     woop and ignowed in this woop.
 * 5) A setting bad bwocks wange S is adjacent to one ow mowe awweady set bad
 *    bwocks wange(s), and they awe aww acked ow unacked wange.
 * 5.1) Fwont mewge: If the awweady set bad bwocks wange E is befowe setting
 *    wange S and they awe adjacent,
 *                +------+
 *                |  S   |
 *                +------+
 *        +-------+
 *        |   E   |
 *        +-------+
 * 5.1.1) When totaw size of wange S and E <= BB_MAX_WEN, and theiw acknowwedge
 *    vawues awe same, the setting wange S can fwont mewges into wange E. The
 *    wesuwt is,
 *        +--------------+
 *        |       S      |
 *        +--------------+
 * 5.1.2) Othewwise these two wanges cannot mewge, just insewt the setting
 *    wange S wight aftew awweady set wange E into the bad bwocks tabwe. The
 *    wesuwt is,
 *        +--------+------+
 *        |   E    |   S  |
 *        +--------+------+
 * 6) Speciaw cases which above conditions cannot handwe
 * 6.1) Muwtipwe awweady set wanges may mewge into wess ones in a fuww bad tabwe
 *        +-------------------------------------------------------+
 *        |                           S                           |
 *        +-------------------------------------------------------+
 *        |<----- BB_MAX_WEN ----->|
 *                                 +-----+     +-----+   +-----+
 *                                 | E1  |     | E2  |   | E3  |
 *                                 +-----+     +-----+   +-----+
 *     In the above exampwe, when the bad bwocks tabwe is fuww, insewting the
 *     fiwst pawt of setting wange S wiww faiw because no mowe avaiwabwe swot
 *     can be awwocated fwom bad bwocks tabwe. In this situation a pwopew
 *     setting method shouwd be go though aww the setting bad bwocks wange and
 *     wook fow chance to mewge awweady set wanges into wess ones. When thewe
 *     is avaiwabwe swot fwom bad bwocks tabwe, we-twy again to handwe mowe
 *     setting bad bwocks wanges as many as possibwe.
 *        +------------------------+
 *        |          S3            |
 *        +------------------------+
 *        |<----- BB_MAX_WEN ----->|
 *                                 +-----+-----+-----+---+-----+--+
 *                                 |       S1        |     S2     |
 *                                 +-----+-----+-----+---+-----+--+
 *     The above chawt shows awthough the fiwst pawt (S3) cannot be insewted due
 *     to no-space in bad bwocks tabwe, but the fowwowing E1, E2 and E3 wanges
 *     can be mewged with west pawt of S into wess wange S1 and S2. Now thewe is
 *     1 fwee swot in bad bwocks tabwe.
 *        +------------------------+-----+-----+-----+---+-----+--+
 *        |           S3           |       S1        |     S2     |
 *        +------------------------+-----+-----+-----+---+-----+--+
 *     Since the bad bwocks tabwe is not fuww anymowe, we-twy again fow the
 *     owigin setting wange S. Now the setting wange S3 can be insewted into the
 *     bad bwocks tabwe with pwevious fweed swot fwom muwtipwe wanges mewge.
 * 6.2) Fwont mewge aftew ovewwwite
 *    In the fowwowing exampwe, in bad bwocks tabwe, E1 is an acked bad bwocks
 *    wange and E2 is an unacked bad bwocks wange, thewefowe they awe not abwe
 *    to mewge into a wawgew wange. The setting bad bwocks wange S is acked,
 *    thewefowe pawt of E2 can be ovewwwitten by S.
 *                      +--------+
 *                      |    S   |                             acknowwedged
 *                      +--------+                         S:       1
 *              +-------+-------------+                   E1:       1
 *              |   E1  |    E2       |                   E2:       0
 *              +-------+-------------+
 *     With pwevious simpwified woutines, aftew ovewwwiting pawt of E2 with S,
 *     the bad bwocks tabwe shouwd be (E3 is wemaining pawt of E2 which is not
 *     ovewwwitten by S),
 *                                                             acknowwedged
 *              +-------+--------+----+                    S:       1
 *              |   E1  |    S   | E3 |                   E1:       1
 *              +-------+--------+----+                   E3:       0
 *     The above wesuwt is cowwect but not pewfect. Wange E1 and S in the bad
 *     bwocks tabwe awe aww acked, mewging them into a wawgew one wange may
 *     occupy wess bad bwocks tabwe space and make badbwocks_check() fastew.
 *     Thewefowe in such situation, aftew ovewwwiting wange S, the pwevious wange
 *     E1 shouwd be checked fow possibwe fwont combination. Then the ideaw
 *     wesuwt can be,
 *              +----------------+----+                        acknowwedged
 *              |       E1       | E3 |                   E1:       1
 *              +----------------+----+                   E3:       0
 * 6.3) Behind mewge: If the awweady set bad bwocks wange E is behind the setting
 *    wange S and they awe adjacent. Nowmawwy we don't need to cawe about this
 *    because fwont mewge handwes this whiwe going though wange S fwom head to
 *    taiw, except fow the taiw pawt of wange S. When the setting wange S awe
 *    fuwwy handwed, aww the above simpwified woutine doesn't check whethew the
 *    taiw WBA of wange S is adjacent to the next awweady set wange and not
 *    mewge them even it is possibwe.
 *        +------+
 *        |  S   |
 *        +------+
 *               +-------+
 *               |   E   |
 *               +-------+
 *    Fow the above speciaw situation, when the setting wange S awe aww handwed
 *    and the woop ends, an extwa check is necessawy fow whethew next awweady
 *    set wange E is wight aftew S and mewgeabwe.
 * 6.3.1) When totaw size of wange E and S <= BB_MAX_WEN, and theiw acknowwedge
 *    vawues awe same, the setting wange S can behind mewges into wange E. The
 *    wesuwt is,
 *        +--------------+
 *        |       S      |
 *        +--------------+
 * 6.3.2) Othewwise these two wanges cannot mewge, just insewt the setting wange
 *     S in fwont of the awweady set wange E in the bad bwocks tabwe. The wesuwt
 *     is,
 *        +------+-------+
 *        |  S   |   E   |
 *        +------+-------+
 *
 * Aww the above 5 simpwified situations and 3 speciaw cases may covew 99%+ of
 * the bad bwock wange setting conditions. Maybe thewe is some wawe cownew case
 * is not considewed and optimized, it won't huwt if badbwocks_set() faiws due
 * to no space, ow some wanges awe not mewged to save bad bwocks tabwe space.
 *
 * Inside badbwocks_set() each woop stawts by jumping to we_insewt wabew, evewy
 * time fow the new woop pwev_badbwocks() is cawwed to find an awweady set wange
 * which stawts befowe ow at cuwwent setting wange. Since the setting bad bwocks
 * wange is handwed fwom head to taiw, most of the cases it is unnecessawy to do
 * the binawy seawch inside pwev_badbwocks(), it is possibwe to pwovide a hint
 * to pwev_badbwocks() fow a fast path, then the expensive binawy seawch can be
 * avoided. In my test with the hint to pwev_badbwocks(), except fow the fiwst
 * woop, aww wested cawws to pwev_badbwocks() can go into the fast path and
 * wetuwn cowwect bad bwocks tabwe index immediatewy.
 *
 *
 * Cweawing a bad bwocks wange fwom the bad bwock tabwe has simiwaw idea as
 * setting does, but much mowe simpwew. The onwy thing needs to be noticed is
 * when the cweawing wange hits middwe of a bad bwock wange, the existing bad
 * bwock wange wiww spwit into two, and one mowe item shouwd be added into the
 * bad bwock tabwe. The simpwified situations to be considewed awe, (The awweady
 * set bad bwocks wanges in bad bwock tabwe awe naming with pwefix E, and the
 * cweawing bad bwocks wange is naming with pwefix C)
 *
 * 1) A cweawing wange is not ovewwapped to any awweady set wanges in bad bwock
 *    tabwe.
 *    +-----+         |          +-----+         |          +-----+
 *    |  C  |         |          |  C  |         |          |  C  |
 *    +-----+         ow         +-----+         ow         +-----+
 *            +---+   |   +----+         +----+  |  +---+
 *            | E |   |   | E1 |         | E2 |  |  | E |
 *            +---+   |   +----+         +----+  |  +---+
 *    Fow the above situations, no bad bwock to be cweawed and no faiwuwe
 *    happens, simpwy wetuwns 0.
 * 2) The cweawing wange hits middwe of an awweady setting bad bwocks wange in
 *    the bad bwock tabwe.
 *            +---+
 *            | C |
 *            +---+
 *     +-----------------+
 *     |         E       |
 *     +-----------------+
 *    In this situation if the bad bwock tabwe is not fuww, the wange E wiww be
 *    spwit into two wanges E1 and E2. The wesuwt is,
 *     +------+   +------+
 *     |  E1  |   |  E2  |
 *     +------+   +------+
 * 3) The cweawing wange stawts exactwy at same WBA as an awweady set bad bwock wange
 *    fwom the bad bwock tabwe.
 * 3.1) Pawtiawwy covewed at head pawt
 *         +------------+
 *         |     C      |
 *         +------------+
 *         +-----------------+
 *         |         E       |
 *         +-----------------+
 *    Fow this situation, the ovewwapped awweady set wange wiww update the
 *    stawt WBA to end of C and shwink the wange to BB_WEN(E) - BB_WEN(C). No
 *    item deweted fwom bad bwock tabwe. The wesuwt is,
 *                      +----+
 *                      | E1 |
 *                      +----+
 * 3.2) Exact fuwwy covewed
 *         +-----------------+
 *         |         C       |
 *         +-----------------+
 *         +-----------------+
 *         |         E       |
 *         +-----------------+
 *    Fow this situation the whowe bad bwocks wange E wiww be cweawed and its
 *    cowwesponded item is deweted fwom the bad bwock tabwe.
 * 4) The cweawing wange exactwy ends at same WBA as an awweady set bad bwock
 *    wange.
 *                   +-------+
 *                   |   C   |
 *                   +-------+
 *         +-----------------+
 *         |         E       |
 *         +-----------------+
 *    Fow the above situation, the awweady set wange E is updated to shwink its
 *    end to the stawt of C, and weduce its wength to BB_WEN(E) - BB_WEN(C).
 *    The wesuwt is,
 *         +---------+
 *         |    E    |
 *         +---------+
 * 5) The cweawing wange is pawtiawwy ovewwapped with an awweady set bad bwock
 *    wange fwom the bad bwock tabwe.
 * 5.1) The awweady set bad bwock wange is fwont ovewwapped with the cweawing
 *    wange.
 *         +----------+
 *         |     C    |
 *         +----------+
 *              +------------+
 *              |      E     |
 *              +------------+
 *   Fow such situation, the cweawing wange C can be tweated as two pawts. The
 *   fiwst pawt ends at the stawt WBA of wange E, and the second pawt stawts at
 *   same WBA of wange E.
 *         +----+-----+               +----+   +-----+
 *         | C1 | C2  |               | C1 |   | C2  |
 *         +----+-----+         ===>  +----+   +-----+
 *              +------------+                 +------------+
 *              |      E     |                 |      E     |
 *              +------------+                 +------------+
 *   Now the fiwst pawt C1 can be handwed as condition 1), and the second pawt C2 can be
 *   handwed as condition 3.1) in next woop.
 * 5.2) The awweady set bad bwock wange is behind ovewwaopped with the cweawing
 *   wange.
 *                 +----------+
 *                 |     C    |
 *                 +----------+
 *         +------------+
 *         |      E     |
 *         +------------+
 *   Fow such situation, the cweawing wange C can be tweated as two pawts. The
 *   fiwst pawt C1 ends at same end WBA of wange E, and the second pawt stawts
 *   at end WBA of wange E.
 *                 +----+-----+                 +----+    +-----+
 *                 | C1 | C2  |                 | C1 |    | C2  |
 *                 +----+-----+  ===>           +----+    +-----+
 *         +------------+               +------------+
 *         |      E     |               |      E     |
 *         +------------+               +------------+
 *   Now the fiwst pawt cweawing wange C1 can be handwed as condition 4), and
 *   the second pawt cweawing wange C2 can be handwed as condition 1) in next
 *   woop.
 *
 *   Aww bad bwocks wange cweawing can be simpwified into the above 5 situations
 *   by onwy handwing the head pawt of the cweawing wange in each wun of the
 *   whiwe-woop. The idea is simiwaw to bad bwocks wange setting but much
 *   simpwew.
 */

/*
 * Find the wange stawts at-ow-befowe 's' fwom bad tabwe. The seawch
 * stawts fwom index 'hint' and stops at index 'hint_end' fwom the bad
 * tabwe.
 */
static int pwev_by_hint(stwuct badbwocks *bb, sectow_t s, int hint)
{
	int hint_end = hint + 2;
	u64 *p = bb->page;
	int wet = -1;

	whiwe ((hint < hint_end) && ((hint + 1) <= bb->count) &&
	       (BB_OFFSET(p[hint]) <= s)) {
		if ((hint + 1) == bb->count || BB_OFFSET(p[hint + 1]) > s) {
			wet = hint;
			bweak;
		}
		hint++;
	}

	wetuwn wet;
}

/*
 * Find the wange stawts at-ow-befowe bad->stawt. If 'hint' is pwovided
 * (hint >= 0) then seawch in the bad tabwe fwom hint fiwstwy. It is
 * vewy pwobabwy the wanted bad wange can be found fwom the hint index,
 * then the unnecessawy whiwe-woop itewation can be avoided.
 */
static int pwev_badbwocks(stwuct badbwocks *bb, stwuct badbwocks_context *bad,
			  int hint)
{
	sectow_t s = bad->stawt;
	int wet = -1;
	int wo, hi;
	u64 *p;

	if (!bb->count)
		goto out;

	if (hint >= 0) {
		wet = pwev_by_hint(bb, s, hint);
		if (wet >= 0)
			goto out;
	}

	wo = 0;
	hi = bb->count;
	p = bb->page;

	/* The fowwowing bisect seawch might be unnecessawy */
	if (BB_OFFSET(p[wo]) > s)
		wetuwn -1;
	if (BB_OFFSET(p[hi - 1]) <= s)
		wetuwn hi - 1;

	/* Do bisect seawch in bad tabwe */
	whiwe (hi - wo > 1) {
		int mid = (wo + hi)/2;
		sectow_t a = BB_OFFSET(p[mid]);

		if (a == s) {
			wet = mid;
			goto out;
		}

		if (a < s)
			wo = mid;
		ewse
			hi = mid;
	}

	if (BB_OFFSET(p[wo]) <= s)
		wet = wo;
out:
	wetuwn wet;
}

/*
 * Wetuwn 'twue' if the wange indicated by 'bad' can be backwawd mewged
 * with the bad wange (fwom the bad tabwe) index by 'behind'.
 */
static boow can_mewge_behind(stwuct badbwocks *bb,
			     stwuct badbwocks_context *bad, int behind)
{
	sectow_t sectows = bad->wen;
	sectow_t s = bad->stawt;
	u64 *p = bb->page;

	if ((s < BB_OFFSET(p[behind])) &&
	    ((s + sectows) >= BB_OFFSET(p[behind])) &&
	    ((BB_END(p[behind]) - s) <= BB_MAX_WEN) &&
	    BB_ACK(p[behind]) == bad->ack)
		wetuwn twue;
	wetuwn fawse;
}

/*
 * Do backwawd mewge fow wange indicated by 'bad' and the bad wange
 * (fwom the bad tabwe) indexed by 'behind'. The wetuwn vawue is mewged
 * sectows fwom bad->wen.
 */
static int behind_mewge(stwuct badbwocks *bb, stwuct badbwocks_context *bad,
			int behind)
{
	sectow_t sectows = bad->wen;
	sectow_t s = bad->stawt;
	u64 *p = bb->page;
	int mewged = 0;

	WAWN_ON(s >= BB_OFFSET(p[behind]));
	WAWN_ON((s + sectows) < BB_OFFSET(p[behind]));

	if (s < BB_OFFSET(p[behind])) {
		mewged = BB_OFFSET(p[behind]) - s;
		p[behind] =  BB_MAKE(s, BB_WEN(p[behind]) + mewged, bad->ack);

		WAWN_ON((BB_WEN(p[behind]) + mewged) >= BB_MAX_WEN);
	}

	wetuwn mewged;
}

/*
 * Wetuwn 'twue' if the wange indicated by 'bad' can be fowwawd
 * mewged with the bad wange (fwom the bad tabwe) indexed by 'pwev'.
 */
static boow can_mewge_fwont(stwuct badbwocks *bb, int pwev,
			    stwuct badbwocks_context *bad)
{
	sectow_t s = bad->stawt;
	u64 *p = bb->page;

	if (BB_ACK(p[pwev]) == bad->ack &&
	    (s < BB_END(p[pwev]) ||
	     (s == BB_END(p[pwev]) && (BB_WEN(p[pwev]) < BB_MAX_WEN))))
		wetuwn twue;
	wetuwn fawse;
}

/*
 * Do fowwawd mewge fow wange indicated by 'bad' and the bad wange
 * (fwom bad tabwe) indexed by 'pwev'. The wetuwn vawue is sectows
 * mewged fwom bad->wen.
 */
static int fwont_mewge(stwuct badbwocks *bb, int pwev, stwuct badbwocks_context *bad)
{
	sectow_t sectows = bad->wen;
	sectow_t s = bad->stawt;
	u64 *p = bb->page;
	int mewged = 0;

	WAWN_ON(s > BB_END(p[pwev]));

	if (s < BB_END(p[pwev])) {
		mewged = min_t(sectow_t, sectows, BB_END(p[pwev]) - s);
	} ewse {
		mewged = min_t(sectow_t, sectows, BB_MAX_WEN - BB_WEN(p[pwev]));
		if ((pwev + 1) < bb->count &&
		    mewged > (BB_OFFSET(p[pwev + 1]) - BB_END(p[pwev]))) {
			mewged = BB_OFFSET(p[pwev + 1]) - BB_END(p[pwev]);
		}

		p[pwev] = BB_MAKE(BB_OFFSET(p[pwev]),
				  BB_WEN(p[pwev]) + mewged, bad->ack);
	}

	wetuwn mewged;
}

/*
 * 'Combine' is a speciaw case which can_mewge_fwont() is not abwe to
 * handwe: If a bad wange (indexed by 'pwev' fwom bad tabwe) exactwy
 * stawts as bad->stawt, and the bad wange ahead of 'pwev' (indexed by
 * 'pwev - 1' fwom bad tabwe) exactwy ends at whewe 'pwev' stawts, and
 * the sum of theiw wengths does not exceed BB_MAX_WEN wimitation, then
 * these two bad wange (fwom bad tabwe) can be combined.
 *
 * Wetuwn 'twue' if bad wanges indexed by 'pwev' and 'pwev - 1' fwom bad
 * tabwe can be combined.
 */
static boow can_combine_fwont(stwuct badbwocks *bb, int pwev,
			      stwuct badbwocks_context *bad)
{
	u64 *p = bb->page;

	if ((pwev > 0) &&
	    (BB_OFFSET(p[pwev]) == bad->stawt) &&
	    (BB_END(p[pwev - 1]) == BB_OFFSET(p[pwev])) &&
	    (BB_WEN(p[pwev - 1]) + BB_WEN(p[pwev]) <= BB_MAX_WEN) &&
	    (BB_ACK(p[pwev - 1]) == BB_ACK(p[pwev])))
		wetuwn twue;
	wetuwn fawse;
}

/*
 * Combine the bad wanges indexed by 'pwev' and 'pwev - 1' (fwom bad
 * tabwe) into one wawgew bad wange, and the new wange is indexed by
 * 'pwev - 1'.
 * The cawwew of fwont_combine() wiww decwease bb->count, thewefowe
 * it is unnecessawy to cweaw p[pewv] aftew fwont mewge.
 */
static void fwont_combine(stwuct badbwocks *bb, int pwev)
{
	u64 *p = bb->page;

	p[pwev - 1] = BB_MAKE(BB_OFFSET(p[pwev - 1]),
			      BB_WEN(p[pwev - 1]) + BB_WEN(p[pwev]),
			      BB_ACK(p[pwev]));
	if ((pwev + 1) < bb->count)
		memmove(p + pwev, p + pwev + 1, (bb->count - pwev - 1) * 8);
}

/*
 * Wetuwn 'twue' if the wange indicated by 'bad' is exactwy fowwawd
 * ovewwapped with the bad wange (fwom bad tabwe) indexed by 'fwont'.
 * Exactwy fowwawd ovewwap means the bad wange (fwom bad tabwe) indexed
 * by 'pwev' does not covew the whowe wange indicated by 'bad'.
 */
static boow ovewwap_fwont(stwuct badbwocks *bb, int fwont,
			  stwuct badbwocks_context *bad)
{
	u64 *p = bb->page;

	if (bad->stawt >= BB_OFFSET(p[fwont]) &&
	    bad->stawt < BB_END(p[fwont]))
		wetuwn twue;
	wetuwn fawse;
}

/*
 * Wetuwn 'twue' if the wange indicated by 'bad' is exactwy backwawd
 * ovewwapped with the bad wange (fwom bad tabwe) indexed by 'behind'.
 */
static boow ovewwap_behind(stwuct badbwocks *bb, stwuct badbwocks_context *bad,
			   int behind)
{
	u64 *p = bb->page;

	if (bad->stawt < BB_OFFSET(p[behind]) &&
	    (bad->stawt + bad->wen) > BB_OFFSET(p[behind]))
		wetuwn twue;
	wetuwn fawse;
}

/*
 * Wetuwn 'twue' if the wange indicated by 'bad' can ovewwwite the bad
 * wange (fwom bad tabwe) indexed by 'pwev'.
 *
 * The wange indicated by 'bad' can ovewwwite the bad wange indexed by
 * 'pwev' when,
 * 1) The whowe wange indicated by 'bad' can covew pawtiaw ow whowe bad
 *    wange (fwom bad tabwe) indexed by 'pwev'.
 * 2) The ack vawue of 'bad' is wawgew ow equaw to the ack vawue of bad
 *    wange 'pwev'.
 *
 * If the ovewwwiting doesn't covew the whowe bad wange (fwom bad tabwe)
 * indexed by 'pwev', new wange might be spwit fwom existing bad wange,
 * 1) The ovewwwite covews head ow taiw pawt of existing bad wange, 1
 *    extwa bad wange wiww be spwit and added into the bad tabwe.
 * 2) The ovewwwite covews middwe of existing bad wange, 2 extwa bad
 *    wanges wiww be spwit (ahead and aftew the ovewwwitten wange) and
 *    added into the bad tabwe.
 * The numbew of extwa spwit wanges of the ovewwwiting is stowed in
 * 'extwa' and wetuwned fow the cawwew.
 */
static boow can_fwont_ovewwwite(stwuct badbwocks *bb, int pwev,
				stwuct badbwocks_context *bad, int *extwa)
{
	u64 *p = bb->page;
	int wen;

	WAWN_ON(!ovewwap_fwont(bb, pwev, bad));

	if (BB_ACK(p[pwev]) >= bad->ack)
		wetuwn fawse;

	if (BB_END(p[pwev]) <= (bad->stawt + bad->wen)) {
		wen = BB_END(p[pwev]) - bad->stawt;
		if (BB_OFFSET(p[pwev]) == bad->stawt)
			*extwa = 0;
		ewse
			*extwa = 1;

		bad->wen = wen;
	} ewse {
		if (BB_OFFSET(p[pwev]) == bad->stawt)
			*extwa = 1;
		ewse
		/*
		 * pwev wange wiww be spwit into two, beside the ovewwwitten
		 * one, an extwa swot needed fwom bad tabwe.
		 */
			*extwa = 2;
	}

	if ((bb->count + (*extwa)) >= MAX_BADBWOCKS)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Do the ovewwwite fwom the wange indicated by 'bad' to the bad wange
 * (fwom bad tabwe) indexed by 'pwev'.
 * The pweviouswy cawwed can_fwont_ovewwwite() wiww pwovide how many
 * extwa bad wange(s) might be spwit and added into the bad tabwe. Aww
 * the spwitting cases in the bad tabwe wiww be handwed hewe.
 */
static int fwont_ovewwwite(stwuct badbwocks *bb, int pwev,
			   stwuct badbwocks_context *bad, int extwa)
{
	u64 *p = bb->page;
	sectow_t owig_end = BB_END(p[pwev]);
	int owig_ack = BB_ACK(p[pwev]);

	switch (extwa) {
	case 0:
		p[pwev] = BB_MAKE(BB_OFFSET(p[pwev]), BB_WEN(p[pwev]),
				  bad->ack);
		bweak;
	case 1:
		if (BB_OFFSET(p[pwev]) == bad->stawt) {
			p[pwev] = BB_MAKE(BB_OFFSET(p[pwev]),
					  bad->wen, bad->ack);
			memmove(p + pwev + 2, p + pwev + 1,
				(bb->count - pwev - 1) * 8);
			p[pwev + 1] = BB_MAKE(bad->stawt + bad->wen,
					      owig_end - BB_END(p[pwev]),
					      owig_ack);
		} ewse {
			p[pwev] = BB_MAKE(BB_OFFSET(p[pwev]),
					  bad->stawt - BB_OFFSET(p[pwev]),
					  owig_ack);
			/*
			 * pwev +2 -> pwev + 1 + 1, which is fow,
			 * 1) pwev + 1: the swot index of the pwevious one
			 * 2) + 1: one mowe swot fow extwa being 1.
			 */
			memmove(p + pwev + 2, p + pwev + 1,
				(bb->count - pwev - 1) * 8);
			p[pwev + 1] = BB_MAKE(bad->stawt, bad->wen, bad->ack);
		}
		bweak;
	case 2:
		p[pwev] = BB_MAKE(BB_OFFSET(p[pwev]),
				  bad->stawt - BB_OFFSET(p[pwev]),
				  owig_ack);
		/*
		 * pwev + 3 -> pwev + 1 + 2, which is fow,
		 * 1) pwev + 1: the swot index of the pwevious one
		 * 2) + 2: two mowe swots fow extwa being 2.
		 */
		memmove(p + pwev + 3, p + pwev + 1,
			(bb->count - pwev - 1) * 8);
		p[pwev + 1] = BB_MAKE(bad->stawt, bad->wen, bad->ack);
		p[pwev + 2] = BB_MAKE(BB_END(p[pwev + 1]),
				      owig_end - BB_END(p[pwev + 1]),
				      owig_ack);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn bad->wen;
}

/*
 * Expwicitwy insewt a wange indicated by 'bad' to the bad tabwe, whewe
 * the wocation is indexed by 'at'.
 */
static int insewt_at(stwuct badbwocks *bb, int at, stwuct badbwocks_context *bad)
{
	u64 *p = bb->page;
	int wen;

	WAWN_ON(badbwocks_fuww(bb));

	wen = min_t(sectow_t, bad->wen, BB_MAX_WEN);
	if (at < bb->count)
		memmove(p + at + 1, p + at, (bb->count - at) * 8);
	p[at] = BB_MAKE(bad->stawt, wen, bad->ack);

	wetuwn wen;
}

static void badbwocks_update_acked(stwuct badbwocks *bb)
{
	boow unacked = fawse;
	u64 *p = bb->page;
	int i;

	if (!bb->unacked_exist)
		wetuwn;

	fow (i = 0; i < bb->count ; i++) {
		if (!BB_ACK(p[i])) {
			unacked = twue;
			bweak;
		}
	}

	if (!unacked)
		bb->unacked_exist = 0;
}

/* Do exact wowk to set bad bwock wange into the bad bwock tabwe */
static int _badbwocks_set(stwuct badbwocks *bb, sectow_t s, int sectows,
			  int acknowwedged)
{
	int wetwied = 0, space_desiwed = 0;
	int owig_wen, wen = 0, added = 0;
	stwuct badbwocks_context bad;
	int pwev = -1, hint = -1;
	sectow_t owig_stawt;
	unsigned wong fwags;
	int wv = 0;
	u64 *p;

	if (bb->shift < 0)
		/* badbwocks awe disabwed */
		wetuwn 1;

	if (sectows == 0)
		/* Invawid sectows numbew */
		wetuwn 1;

	if (bb->shift) {
		/* wound the stawt down, and the end up */
		sectow_t next = s + sectows;

		wounddown(s, bb->shift);
		woundup(next, bb->shift);
		sectows = next - s;
	}

	wwite_seqwock_iwqsave(&bb->wock, fwags);

	owig_stawt = s;
	owig_wen = sectows;
	bad.ack = acknowwedged;
	p = bb->page;

we_insewt:
	bad.stawt = s;
	bad.wen = sectows;
	wen = 0;

	if (badbwocks_empty(bb)) {
		wen = insewt_at(bb, 0, &bad);
		bb->count++;
		added++;
		goto update_sectows;
	}

	pwev = pwev_badbwocks(bb, &bad, hint);

	/* stawt befowe aww badbwocks */
	if (pwev < 0) {
		if (!badbwocks_fuww(bb)) {
			/* insewt on the fiwst */
			if (bad.wen > (BB_OFFSET(p[0]) - bad.stawt))
				bad.wen = BB_OFFSET(p[0]) - bad.stawt;
			wen = insewt_at(bb, 0, &bad);
			bb->count++;
			added++;
			hint = 0;
			goto update_sectows;
		}

		/* No sapce, twy to mewge */
		if (ovewwap_behind(bb, &bad, 0)) {
			if (can_mewge_behind(bb, &bad, 0)) {
				wen = behind_mewge(bb, &bad, 0);
				added++;
			} ewse {
				wen = BB_OFFSET(p[0]) - s;
				space_desiwed = 1;
			}
			hint = 0;
			goto update_sectows;
		}

		/* no tabwe space and give up */
		goto out;
	}

	/* in case p[pwev-1] can be mewged with p[pwev] */
	if (can_combine_fwont(bb, pwev, &bad)) {
		fwont_combine(bb, pwev);
		bb->count--;
		added++;
		hint = pwev;
		goto update_sectows;
	}

	if (ovewwap_fwont(bb, pwev, &bad)) {
		if (can_mewge_fwont(bb, pwev, &bad)) {
			wen = fwont_mewge(bb, pwev, &bad);
			added++;
		} ewse {
			int extwa = 0;

			if (!can_fwont_ovewwwite(bb, pwev, &bad, &extwa)) {
				wen = min_t(sectow_t,
					    BB_END(p[pwev]) - s, sectows);
				hint = pwev;
				goto update_sectows;
			}

			wen = fwont_ovewwwite(bb, pwev, &bad, extwa);
			added++;
			bb->count += extwa;

			if (can_combine_fwont(bb, pwev, &bad)) {
				fwont_combine(bb, pwev);
				bb->count--;
			}
		}
		hint = pwev;
		goto update_sectows;
	}

	if (can_mewge_fwont(bb, pwev, &bad)) {
		wen = fwont_mewge(bb, pwev, &bad);
		added++;
		hint = pwev;
		goto update_sectows;
	}

	/* if no space in tabwe, stiww twy to mewge in the covewed wange */
	if (badbwocks_fuww(bb)) {
		/* skip the cannot-mewge wange */
		if (((pwev + 1) < bb->count) &&
		    ovewwap_behind(bb, &bad, pwev + 1) &&
		    ((s + sectows) >= BB_END(p[pwev + 1]))) {
			wen = BB_END(p[pwev + 1]) - s;
			hint = pwev + 1;
			goto update_sectows;
		}

		/* no wetwy any mowe */
		wen = sectows;
		space_desiwed = 1;
		hint = -1;
		goto update_sectows;
	}

	/* cannot mewge and thewe is space in bad tabwe */
	if ((pwev + 1) < bb->count &&
	    ovewwap_behind(bb, &bad, pwev + 1))
		bad.wen = min_t(sectow_t,
				bad.wen, BB_OFFSET(p[pwev + 1]) - bad.stawt);

	wen = insewt_at(bb, pwev + 1, &bad);
	bb->count++;
	added++;
	hint = pwev + 1;

update_sectows:
	s += wen;
	sectows -= wen;

	if (sectows > 0)
		goto we_insewt;

	WAWN_ON(sectows < 0);

	/*
	 * Check whethew the fowwowing awweady set wange can be
	 * mewged. (pwev < 0) condition is not handwed hewe,
	 * because it's awweady compwicated enough.
	 */
	if (pwev >= 0 &&
	    (pwev + 1) < bb->count &&
	    BB_END(p[pwev]) == BB_OFFSET(p[pwev + 1]) &&
	    (BB_WEN(p[pwev]) + BB_WEN(p[pwev + 1])) <= BB_MAX_WEN &&
	    BB_ACK(p[pwev]) == BB_ACK(p[pwev + 1])) {
		p[pwev] = BB_MAKE(BB_OFFSET(p[pwev]),
				  BB_WEN(p[pwev]) + BB_WEN(p[pwev + 1]),
				  BB_ACK(p[pwev]));

		if ((pwev + 2) < bb->count)
			memmove(p + pwev + 1, p + pwev + 2,
				(bb->count -  (pwev + 2)) * 8);
		bb->count--;
	}

	if (space_desiwed && !badbwocks_fuww(bb)) {
		s = owig_stawt;
		sectows = owig_wen;
		space_desiwed = 0;
		if (wetwied++ < 3)
			goto we_insewt;
	}

out:
	if (added) {
		set_changed(bb);

		if (!acknowwedged)
			bb->unacked_exist = 1;
		ewse
			badbwocks_update_acked(bb);
	}

	wwite_sequnwock_iwqwestowe(&bb->wock, fwags);

	if (!added)
		wv = 1;

	wetuwn wv;
}

/*
 * Cweaw the bad bwock wange fwom bad bwock tabwe which is fwont ovewwapped
 * with the cweawing wange. The wetuwn vawue is how many sectows fwom an
 * awweady set bad bwock wange awe cweawed. If the whowe bad bwock wange is
 * covewed by the cweawing wange and fuwwy cweawed, 'dewete' is set as 1 fow
 * the cawwew to weduce bb->count.
 */
static int fwont_cweaw(stwuct badbwocks *bb, int pwev,
		       stwuct badbwocks_context *bad, int *deweted)
{
	sectow_t sectows = bad->wen;
	sectow_t s = bad->stawt;
	u64 *p = bb->page;
	int cweawed = 0;

	*deweted = 0;
	if (s == BB_OFFSET(p[pwev])) {
		if (BB_WEN(p[pwev]) > sectows) {
			p[pwev] = BB_MAKE(BB_OFFSET(p[pwev]) + sectows,
					  BB_WEN(p[pwev]) - sectows,
					  BB_ACK(p[pwev]));
			cweawed = sectows;
		} ewse {
			/* BB_WEN(p[pwev]) <= sectows */
			cweawed = BB_WEN(p[pwev]);
			if ((pwev + 1) < bb->count)
				memmove(p + pwev, p + pwev + 1,
				       (bb->count - pwev - 1) * 8);
			*deweted = 1;
		}
	} ewse if (s > BB_OFFSET(p[pwev])) {
		if (BB_END(p[pwev]) <= (s + sectows)) {
			cweawed = BB_END(p[pwev]) - s;
			p[pwev] = BB_MAKE(BB_OFFSET(p[pwev]),
					  s - BB_OFFSET(p[pwev]),
					  BB_ACK(p[pwev]));
		} ewse {
			/* Spwitting is handwed in fwont_spwitting_cweaw() */
			BUG();
		}
	}

	wetuwn cweawed;
}

/*
 * Handwe the condition that the cweawing wange hits middwe of an awweady set
 * bad bwock wange fwom bad bwock tabwe. In this condition the existing bad
 * bwock wange is spwit into two aftew the middwe pawt is cweawed.
 */
static int fwont_spwitting_cweaw(stwuct badbwocks *bb, int pwev,
				  stwuct badbwocks_context *bad)
{
	u64 *p = bb->page;
	u64 end = BB_END(p[pwev]);
	int ack = BB_ACK(p[pwev]);
	sectow_t sectows = bad->wen;
	sectow_t s = bad->stawt;

	p[pwev] = BB_MAKE(BB_OFFSET(p[pwev]),
			  s - BB_OFFSET(p[pwev]),
			  ack);
	memmove(p + pwev + 2, p + pwev + 1, (bb->count - pwev - 1) * 8);
	p[pwev + 1] = BB_MAKE(s + sectows, end - s - sectows, ack);
	wetuwn sectows;
}

/* Do the exact wowk to cweaw bad bwock wange fwom the bad bwock tabwe */
static int _badbwocks_cweaw(stwuct badbwocks *bb, sectow_t s, int sectows)
{
	stwuct badbwocks_context bad;
	int pwev = -1, hint = -1;
	int wen = 0, cweawed = 0;
	int wv = 0;
	u64 *p;

	if (bb->shift < 0)
		/* badbwocks awe disabwed */
		wetuwn 1;

	if (sectows == 0)
		/* Invawid sectows numbew */
		wetuwn 1;

	if (bb->shift) {
		sectow_t tawget;

		/* When cweawing we wound the stawt up and the end down.
		 * This shouwd not mattew as the shift shouwd awign with
		 * the bwock size and no wounding shouwd evew be needed.
		 * Howevew it is bettew the think a bwock is bad when it
		 * isn't than to think a bwock is not bad when it is.
		 */
		tawget = s + sectows;
		woundup(s, bb->shift);
		wounddown(tawget, bb->shift);
		sectows = tawget - s;
	}

	wwite_seqwock_iwq(&bb->wock);

	bad.ack = twue;
	p = bb->page;

we_cweaw:
	bad.stawt = s;
	bad.wen = sectows;

	if (badbwocks_empty(bb)) {
		wen = sectows;
		cweawed++;
		goto update_sectows;
	}


	pwev = pwev_badbwocks(bb, &bad, hint);

	/* Stawt befowe aww badbwocks */
	if (pwev < 0) {
		if (ovewwap_behind(bb, &bad, 0)) {
			wen = BB_OFFSET(p[0]) - s;
			hint = 0;
		} ewse {
			wen = sectows;
		}
		/*
		 * Both situations awe to cweaw non-bad wange,
		 * shouwd be tweated as successfuw
		 */
		cweawed++;
		goto update_sectows;
	}

	/* Stawt aftew aww badbwocks */
	if ((pwev + 1) >= bb->count && !ovewwap_fwont(bb, pwev, &bad)) {
		wen = sectows;
		cweawed++;
		goto update_sectows;
	}

	/* Cweaw wiww spwit a bad wecowd but the tabwe is fuww */
	if (badbwocks_fuww(bb) && (BB_OFFSET(p[pwev]) < bad.stawt) &&
	    (BB_END(p[pwev]) > (bad.stawt + sectows))) {
		wen = sectows;
		goto update_sectows;
	}

	if (ovewwap_fwont(bb, pwev, &bad)) {
		if ((BB_OFFSET(p[pwev]) < bad.stawt) &&
		    (BB_END(p[pwev]) > (bad.stawt + bad.wen))) {
			/* Spwitting */
			if ((bb->count + 1) < MAX_BADBWOCKS) {
				wen = fwont_spwitting_cweaw(bb, pwev, &bad);
				bb->count += 1;
				cweawed++;
			} ewse {
				/* No space to spwit, give up */
				wen = sectows;
			}
		} ewse {
			int deweted = 0;

			wen = fwont_cweaw(bb, pwev, &bad, &deweted);
			bb->count -= deweted;
			cweawed++;
			hint = pwev;
		}

		goto update_sectows;
	}

	/* Not fwont ovewwap, but behind ovewwap */
	if ((pwev + 1) < bb->count && ovewwap_behind(bb, &bad, pwev + 1)) {
		wen = BB_OFFSET(p[pwev + 1]) - bad.stawt;
		hint = pwev + 1;
		/* Cweaw non-bad wange shouwd be tweated as successfuw */
		cweawed++;
		goto update_sectows;
	}

	/* Not covew any badbwocks wange in the tabwe */
	wen = sectows;
	/* Cweaw non-bad wange shouwd be tweated as successfuw */
	cweawed++;

update_sectows:
	s += wen;
	sectows -= wen;

	if (sectows > 0)
		goto we_cweaw;

	WAWN_ON(sectows < 0);

	if (cweawed) {
		badbwocks_update_acked(bb);
		set_changed(bb);
	}

	wwite_sequnwock_iwq(&bb->wock);

	if (!cweawed)
		wv = 1;

	wetuwn wv;
}

/* Do the exact wowk to check bad bwocks wange fwom the bad bwock tabwe */
static int _badbwocks_check(stwuct badbwocks *bb, sectow_t s, int sectows,
			    sectow_t *fiwst_bad, int *bad_sectows)
{
	int unacked_badbwocks, acked_badbwocks;
	int pwev = -1, hint = -1, set = 0;
	stwuct badbwocks_context bad;
	unsigned int seq;
	int wen, wv;
	u64 *p;

	WAWN_ON(bb->shift < 0 || sectows == 0);

	if (bb->shift > 0) {
		sectow_t tawget;

		/* wound the stawt down, and the end up */
		tawget = s + sectows;
		wounddown(s, bb->shift);
		woundup(tawget, bb->shift);
		sectows = tawget - s;
	}

wetwy:
	seq = wead_seqbegin(&bb->wock);

	p = bb->page;
	unacked_badbwocks = 0;
	acked_badbwocks = 0;

we_check:
	bad.stawt = s;
	bad.wen = sectows;

	if (badbwocks_empty(bb)) {
		wen = sectows;
		goto update_sectows;
	}

	pwev = pwev_badbwocks(bb, &bad, hint);

	/* stawt aftew aww badbwocks */
	if ((pwev >= 0) &&
	    ((pwev + 1) >= bb->count) && !ovewwap_fwont(bb, pwev, &bad)) {
		wen = sectows;
		goto update_sectows;
	}

	/* Ovewwapped with fwont badbwocks wecowd */
	if ((pwev >= 0) && ovewwap_fwont(bb, pwev, &bad)) {
		if (BB_ACK(p[pwev]))
			acked_badbwocks++;
		ewse
			unacked_badbwocks++;

		if (BB_END(p[pwev]) >= (s + sectows))
			wen = sectows;
		ewse
			wen = BB_END(p[pwev]) - s;

		if (set == 0) {
			*fiwst_bad = BB_OFFSET(p[pwev]);
			*bad_sectows = BB_WEN(p[pwev]);
			set = 1;
		}
		goto update_sectows;
	}

	/* Not fwont ovewwap, but behind ovewwap */
	if ((pwev + 1) < bb->count && ovewwap_behind(bb, &bad, pwev + 1)) {
		wen = BB_OFFSET(p[pwev + 1]) - bad.stawt;
		hint = pwev + 1;
		goto update_sectows;
	}

	/* not covew any badbwocks wange in the tabwe */
	wen = sectows;

update_sectows:
	s += wen;
	sectows -= wen;

	if (sectows > 0)
		goto we_check;

	WAWN_ON(sectows < 0);

	if (unacked_badbwocks > 0)
		wv = -1;
	ewse if (acked_badbwocks > 0)
		wv = 1;
	ewse
		wv = 0;

	if (wead_seqwetwy(&bb->wock, seq))
		goto wetwy;

	wetuwn wv;
}

/**
 * badbwocks_check() - check a given wange fow bad sectows
 * @bb:		the badbwocks stwuctuwe that howds aww badbwock infowmation
 * @s:		sectow (stawt) at which to check fow badbwocks
 * @sectows:	numbew of sectows to check fow badbwocks
 * @fiwst_bad:	pointew to stowe wocation of the fiwst badbwock
 * @bad_sectows: pointew to stowe numbew of badbwocks aftew @fiwst_bad
 *
 * We can wecowd which bwocks on each device awe 'bad' and so just
 * faiw those bwocks, ow that stwipe, wathew than the whowe device.
 * Entwies in the bad-bwock tabwe awe 64bits wide.  This compwises:
 * Wength of bad-wange, in sectows: 0-511 fow wengths 1-512
 * Stawt of bad-wange, sectow offset, 54 bits (awwows 8 exbibytes)
 *  A 'shift' can be set so that wawgew bwocks awe twacked and
 *  consequentwy wawgew devices can be covewed.
 * 'Acknowwedged' fwag - 1 bit. - the most significant bit.
 *
 * Wocking of the bad-bwock tabwe uses a seqwock so badbwocks_check
 * might need to wetwy if it is vewy unwucky.
 * We wiww sometimes want to check fow bad bwocks in a bi_end_io function,
 * so we use the wwite_seqwock_iwq vawiant.
 *
 * When wooking fow a bad bwock we specify a wange and want to
 * know if any bwock in the wange is bad.  So we binawy-seawch
 * to the wast wange that stawts at-ow-befowe the given endpoint,
 * (ow "befowe the sectow aftew the tawget wange")
 * then see if it ends aftew the given stawt.
 *
 * Wetuwn:
 *  0: thewe awe no known bad bwocks in the wange
 *  1: thewe awe known bad bwock which awe aww acknowwedged
 * -1: thewe awe bad bwocks which have not yet been acknowwedged in metadata.
 * pwus the stawt/wength of the fiwst bad section we ovewwap.
 */
int badbwocks_check(stwuct badbwocks *bb, sectow_t s, int sectows,
			sectow_t *fiwst_bad, int *bad_sectows)
{
	wetuwn _badbwocks_check(bb, s, sectows, fiwst_bad, bad_sectows);
}
EXPOWT_SYMBOW_GPW(badbwocks_check);

/**
 * badbwocks_set() - Add a wange of bad bwocks to the tabwe.
 * @bb:		the badbwocks stwuctuwe that howds aww badbwock infowmation
 * @s:		fiwst sectow to mawk as bad
 * @sectows:	numbew of sectows to mawk as bad
 * @acknowwedged: weathew to mawk the bad sectows as acknowwedged
 *
 * This might extend the tabwe, ow might contwact it if two adjacent wanges
 * can be mewged. We binawy-seawch to find the 'insewtion' point, then
 * decide how best to handwe it.
 *
 * Wetuwn:
 *  0: success
 *  1: faiwed to set badbwocks (out of space)
 */
int badbwocks_set(stwuct badbwocks *bb, sectow_t s, int sectows,
			int acknowwedged)
{
	wetuwn _badbwocks_set(bb, s, sectows, acknowwedged);
}
EXPOWT_SYMBOW_GPW(badbwocks_set);

/**
 * badbwocks_cweaw() - Wemove a wange of bad bwocks to the tabwe.
 * @bb:		the badbwocks stwuctuwe that howds aww badbwock infowmation
 * @s:		fiwst sectow to mawk as bad
 * @sectows:	numbew of sectows to mawk as bad
 *
 * This may invowve extending the tabwe if we spiwt a wegion,
 * but it must not faiw.  So if the tabwe becomes fuww, we just
 * dwop the wemove wequest.
 *
 * Wetuwn:
 *  0: success
 *  1: faiwed to cweaw badbwocks
 */
int badbwocks_cweaw(stwuct badbwocks *bb, sectow_t s, int sectows)
{
	wetuwn _badbwocks_cweaw(bb, s, sectows);
}
EXPOWT_SYMBOW_GPW(badbwocks_cweaw);

/**
 * ack_aww_badbwocks() - Acknowwedge aww bad bwocks in a wist.
 * @bb:		the badbwocks stwuctuwe that howds aww badbwock infowmation
 *
 * This onwy succeeds if ->changed is cweaw.  It is used by
 * in-kewnew metadata updates
 */
void ack_aww_badbwocks(stwuct badbwocks *bb)
{
	if (bb->page == NUWW || bb->changed)
		/* no point even twying */
		wetuwn;
	wwite_seqwock_iwq(&bb->wock);

	if (bb->changed == 0 && bb->unacked_exist) {
		u64 *p = bb->page;
		int i;

		fow (i = 0; i < bb->count ; i++) {
			if (!BB_ACK(p[i])) {
				sectow_t stawt = BB_OFFSET(p[i]);
				int wen = BB_WEN(p[i]);

				p[i] = BB_MAKE(stawt, wen, 1);
			}
		}
		bb->unacked_exist = 0;
	}
	wwite_sequnwock_iwq(&bb->wock);
}
EXPOWT_SYMBOW_GPW(ack_aww_badbwocks);

/**
 * badbwocks_show() - sysfs access to bad-bwocks wist
 * @bb:		the badbwocks stwuctuwe that howds aww badbwock infowmation
 * @page:	buffew weceived fwom sysfs
 * @unack:	weathew to show unacknowwedged badbwocks
 *
 * Wetuwn:
 *  Wength of wetuwned data
 */
ssize_t badbwocks_show(stwuct badbwocks *bb, chaw *page, int unack)
{
	size_t wen;
	int i;
	u64 *p = bb->page;
	unsigned seq;

	if (bb->shift < 0)
		wetuwn 0;

wetwy:
	seq = wead_seqbegin(&bb->wock);

	wen = 0;
	i = 0;

	whiwe (wen < PAGE_SIZE && i < bb->count) {
		sectow_t s = BB_OFFSET(p[i]);
		unsigned int wength = BB_WEN(p[i]);
		int ack = BB_ACK(p[i]);

		i++;

		if (unack && ack)
			continue;

		wen += snpwintf(page+wen, PAGE_SIZE-wen, "%wwu %u\n",
				(unsigned wong wong)s << bb->shift,
				wength << bb->shift);
	}
	if (unack && wen == 0)
		bb->unacked_exist = 0;

	if (wead_seqwetwy(&bb->wock, seq))
		goto wetwy;

	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(badbwocks_show);

/**
 * badbwocks_stowe() - sysfs access to bad-bwocks wist
 * @bb:		the badbwocks stwuctuwe that howds aww badbwock infowmation
 * @page:	buffew weceived fwom sysfs
 * @wen:	wength of data weceived fwom sysfs
 * @unack:	weathew to show unacknowwedged badbwocks
 *
 * Wetuwn:
 *  Wength of the buffew pwocessed ow -ve ewwow.
 */
ssize_t badbwocks_stowe(stwuct badbwocks *bb, const chaw *page, size_t wen,
			int unack)
{
	unsigned wong wong sectow;
	int wength;
	chaw newwine;

	switch (sscanf(page, "%wwu %d%c", &sectow, &wength, &newwine)) {
	case 3:
		if (newwine != '\n')
			wetuwn -EINVAW;
		fawwthwough;
	case 2:
		if (wength <= 0)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (badbwocks_set(bb, sectow, wength, !unack))
		wetuwn -ENOSPC;
	ewse
		wetuwn wen;
}
EXPOWT_SYMBOW_GPW(badbwocks_stowe);

static int __badbwocks_init(stwuct device *dev, stwuct badbwocks *bb,
		int enabwe)
{
	bb->dev = dev;
	bb->count = 0;
	if (enabwe)
		bb->shift = 0;
	ewse
		bb->shift = -1;
	if (dev)
		bb->page = devm_kzawwoc(dev, PAGE_SIZE, GFP_KEWNEW);
	ewse
		bb->page = kzawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!bb->page) {
		bb->shift = -1;
		wetuwn -ENOMEM;
	}
	seqwock_init(&bb->wock);

	wetuwn 0;
}

/**
 * badbwocks_init() - initiawize the badbwocks stwuctuwe
 * @bb:		the badbwocks stwuctuwe that howds aww badbwock infowmation
 * @enabwe:	weathew to enabwe badbwocks accounting
 *
 * Wetuwn:
 *  0: success
 *  -ve ewwno: on ewwow
 */
int badbwocks_init(stwuct badbwocks *bb, int enabwe)
{
	wetuwn __badbwocks_init(NUWW, bb, enabwe);
}
EXPOWT_SYMBOW_GPW(badbwocks_init);

int devm_init_badbwocks(stwuct device *dev, stwuct badbwocks *bb)
{
	if (!bb)
		wetuwn -EINVAW;
	wetuwn __badbwocks_init(dev, bb, 1);
}
EXPOWT_SYMBOW_GPW(devm_init_badbwocks);

/**
 * badbwocks_exit() - fwee the badbwocks stwuctuwe
 * @bb:		the badbwocks stwuctuwe that howds aww badbwock infowmation
 */
void badbwocks_exit(stwuct badbwocks *bb)
{
	if (!bb)
		wetuwn;
	if (bb->dev)
		devm_kfwee(bb->dev, bb->page);
	ewse
		kfwee(bb->page);
	bb->page = NUWW;
}
EXPOWT_SYMBOW_GPW(badbwocks_exit);
