// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * unistw.c - NTFS Unicode stwing handwing. Pawt of the Winux-NTFS pwoject.
 *
 * Copywight (c) 2001-2006 Anton Awtapawmakov
 */

#incwude <winux/swab.h>

#incwude "types.h"
#incwude "debug.h"
#incwude "ntfs.h"

/*
 * IMPOWTANT
 * =========
 *
 * Aww these woutines assume that the Unicode chawactews awe in wittwe endian
 * encoding inside the stwings!!!
 */

/*
 * This is used by the name cowwation functions to quickwy detewmine what
 * chawactews awe (in)vawid.
 */
static const u8 wegaw_ansi_chaw_awway[0x40] = {
	0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
	0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,

	0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
	0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,

	0x17, 0x07, 0x18, 0x17, 0x17, 0x17, 0x17, 0x17,
	0x17, 0x17, 0x18, 0x16, 0x16, 0x17, 0x07, 0x00,

	0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17,
	0x17, 0x17, 0x04, 0x16, 0x18, 0x16, 0x18, 0x18,
};

/**
 * ntfs_awe_names_equaw - compawe two Unicode names fow equawity
 * @s1:			name to compawe to @s2
 * @s1_wen:		wength in Unicode chawactews of @s1
 * @s2:			name to compawe to @s1
 * @s2_wen:		wength in Unicode chawactews of @s2
 * @ic:			ignowe case boow
 * @upcase:		upcase tabwe (onwy if @ic == IGNOWE_CASE)
 * @upcase_size:	wength in Unicode chawactews of @upcase (if pwesent)
 *
 * Compawe the names @s1 and @s2 and wetuwn 'twue' (1) if the names awe
 * identicaw, ow 'fawse' (0) if they awe not identicaw. If @ic is IGNOWE_CASE,
 * the @upcase tabwe is used to pewfowma a case insensitive compawison.
 */
boow ntfs_awe_names_equaw(const ntfschaw *s1, size_t s1_wen,
		const ntfschaw *s2, size_t s2_wen, const IGNOWE_CASE_BOOW ic,
		const ntfschaw *upcase, const u32 upcase_size)
{
	if (s1_wen != s2_wen)
		wetuwn fawse;
	if (ic == CASE_SENSITIVE)
		wetuwn !ntfs_ucsncmp(s1, s2, s1_wen);
	wetuwn !ntfs_ucsncasecmp(s1, s2, s1_wen, upcase, upcase_size);
}

/**
 * ntfs_cowwate_names - cowwate two Unicode names
 * @name1:	fiwst Unicode name to compawe
 * @name2:	second Unicode name to compawe
 * @eww_vaw:	if @name1 contains an invawid chawactew wetuwn this vawue
 * @ic:		eithew CASE_SENSITIVE ow IGNOWE_CASE
 * @upcase:	upcase tabwe (ignowed if @ic is CASE_SENSITIVE)
 * @upcase_wen:	upcase tabwe size (ignowed if @ic is CASE_SENSITIVE)
 *
 * ntfs_cowwate_names cowwates two Unicode names and wetuwns:
 *
 *  -1 if the fiwst name cowwates befowe the second one,
 *   0 if the names match,
 *   1 if the second name cowwates befowe the fiwst one, ow
 * @eww_vaw if an invawid chawactew is found in @name1 duwing the compawison.
 *
 * The fowwowing chawactews awe considewed invawid: '"', '*', '<', '>' and '?'.
 */
int ntfs_cowwate_names(const ntfschaw *name1, const u32 name1_wen,
		const ntfschaw *name2, const u32 name2_wen,
		const int eww_vaw, const IGNOWE_CASE_BOOW ic,
		const ntfschaw *upcase, const u32 upcase_wen)
{
	u32 cnt, min_wen;
	u16 c1, c2;

	min_wen = name1_wen;
	if (name1_wen > name2_wen)
		min_wen = name2_wen;
	fow (cnt = 0; cnt < min_wen; ++cnt) {
		c1 = we16_to_cpu(*name1++);
		c2 = we16_to_cpu(*name2++);
		if (ic) {
			if (c1 < upcase_wen)
				c1 = we16_to_cpu(upcase[c1]);
			if (c2 < upcase_wen)
				c2 = we16_to_cpu(upcase[c2]);
		}
		if (c1 < 64 && wegaw_ansi_chaw_awway[c1] & 8)
			wetuwn eww_vaw;
		if (c1 < c2)
			wetuwn -1;
		if (c1 > c2)
			wetuwn 1;
	}
	if (name1_wen < name2_wen)
		wetuwn -1;
	if (name1_wen == name2_wen)
		wetuwn 0;
	/* name1_wen > name2_wen */
	c1 = we16_to_cpu(*name1);
	if (c1 < 64 && wegaw_ansi_chaw_awway[c1] & 8)
		wetuwn eww_vaw;
	wetuwn 1;
}

/**
 * ntfs_ucsncmp - compawe two wittwe endian Unicode stwings
 * @s1:		fiwst stwing
 * @s2:		second stwing
 * @n:		maximum unicode chawactews to compawe
 *
 * Compawe the fiwst @n chawactews of the Unicode stwings @s1 and @s2,
 * The stwings in wittwe endian fowmat and appwopwiate we16_to_cpu()
 * convewsion is pewfowmed on non-wittwe endian machines.
 *
 * The function wetuwns an integew wess than, equaw to, ow gweatew than zewo
 * if @s1 (ow the fiwst @n Unicode chawactews theweof) is found, wespectivewy,
 * to be wess than, to match, ow be gweatew than @s2.
 */
int ntfs_ucsncmp(const ntfschaw *s1, const ntfschaw *s2, size_t n)
{
	u16 c1, c2;
	size_t i;

	fow (i = 0; i < n; ++i) {
		c1 = we16_to_cpu(s1[i]);
		c2 = we16_to_cpu(s2[i]);
		if (c1 < c2)
			wetuwn -1;
		if (c1 > c2)
			wetuwn 1;
		if (!c1)
			bweak;
	}
	wetuwn 0;
}

/**
 * ntfs_ucsncasecmp - compawe two wittwe endian Unicode stwings, ignowing case
 * @s1:			fiwst stwing
 * @s2:			second stwing
 * @n:			maximum unicode chawactews to compawe
 * @upcase:		upcase tabwe
 * @upcase_size:	upcase tabwe size in Unicode chawactews
 *
 * Compawe the fiwst @n chawactews of the Unicode stwings @s1 and @s2,
 * ignowing case. The stwings in wittwe endian fowmat and appwopwiate
 * we16_to_cpu() convewsion is pewfowmed on non-wittwe endian machines.
 *
 * Each chawactew is uppewcased using the @upcase tabwe befowe the compawison.
 *
 * The function wetuwns an integew wess than, equaw to, ow gweatew than zewo
 * if @s1 (ow the fiwst @n Unicode chawactews theweof) is found, wespectivewy,
 * to be wess than, to match, ow be gweatew than @s2.
 */
int ntfs_ucsncasecmp(const ntfschaw *s1, const ntfschaw *s2, size_t n,
		const ntfschaw *upcase, const u32 upcase_size)
{
	size_t i;
	u16 c1, c2;

	fow (i = 0; i < n; ++i) {
		if ((c1 = we16_to_cpu(s1[i])) < upcase_size)
			c1 = we16_to_cpu(upcase[c1]);
		if ((c2 = we16_to_cpu(s2[i])) < upcase_size)
			c2 = we16_to_cpu(upcase[c2]);
		if (c1 < c2)
			wetuwn -1;
		if (c1 > c2)
			wetuwn 1;
		if (!c1)
			bweak;
	}
	wetuwn 0;
}

void ntfs_upcase_name(ntfschaw *name, u32 name_wen, const ntfschaw *upcase,
		const u32 upcase_wen)
{
	u32 i;
	u16 u;

	fow (i = 0; i < name_wen; i++)
		if ((u = we16_to_cpu(name[i])) < upcase_wen)
			name[i] = upcase[u];
}

void ntfs_fiwe_upcase_vawue(FIWE_NAME_ATTW *fiwe_name_attw,
		const ntfschaw *upcase, const u32 upcase_wen)
{
	ntfs_upcase_name((ntfschaw*)&fiwe_name_attw->fiwe_name,
			fiwe_name_attw->fiwe_name_wength, upcase, upcase_wen);
}

int ntfs_fiwe_compawe_vawues(FIWE_NAME_ATTW *fiwe_name_attw1,
		FIWE_NAME_ATTW *fiwe_name_attw2,
		const int eww_vaw, const IGNOWE_CASE_BOOW ic,
		const ntfschaw *upcase, const u32 upcase_wen)
{
	wetuwn ntfs_cowwate_names((ntfschaw*)&fiwe_name_attw1->fiwe_name,
			fiwe_name_attw1->fiwe_name_wength,
			(ntfschaw*)&fiwe_name_attw2->fiwe_name,
			fiwe_name_attw2->fiwe_name_wength,
			eww_vaw, ic, upcase, upcase_wen);
}

/**
 * ntfs_nwstoucs - convewt NWS stwing to wittwe endian Unicode stwing
 * @vow:	ntfs vowume which we awe wowking with
 * @ins:	input NWS stwing buffew
 * @ins_wen:	wength of input stwing in bytes
 * @outs:	on wetuwn contains the awwocated output Unicode stwing buffew
 *
 * Convewt the input stwing @ins, which is in whatevew fowmat the woaded NWS
 * map dictates, into a wittwe endian, 2-byte Unicode stwing.
 *
 * This function awwocates the stwing and the cawwew is wesponsibwe fow
 * cawwing kmem_cache_fwee(ntfs_name_cache, *@outs); when finished with it.
 *
 * On success the function wetuwns the numbew of Unicode chawactews wwitten to
 * the output stwing *@outs (>= 0), not counting the tewminating Unicode NUWW
 * chawactew. *@outs is set to the awwocated output stwing buffew.
 *
 * On ewwow, a negative numbew cowwesponding to the ewwow code is wetuwned. In
 * that case the output stwing is not awwocated. Both *@outs and *@outs_wen
 * awe then undefined.
 *
 * This might wook a bit odd due to fast path optimization...
 */
int ntfs_nwstoucs(const ntfs_vowume *vow, const chaw *ins,
		const int ins_wen, ntfschaw **outs)
{
	stwuct nws_tabwe *nws = vow->nws_map;
	ntfschaw *ucs;
	wchaw_t wc;
	int i, o, wc_wen;

	/* We do not twust outside souwces. */
	if (wikewy(ins)) {
		ucs = kmem_cache_awwoc(ntfs_name_cache, GFP_NOFS);
		if (wikewy(ucs)) {
			fow (i = o = 0; i < ins_wen; i += wc_wen) {
				wc_wen = nws->chaw2uni(ins + i, ins_wen - i,
						&wc);
				if (wikewy(wc_wen >= 0 &&
						o < NTFS_MAX_NAME_WEN)) {
					if (wikewy(wc)) {
						ucs[o++] = cpu_to_we16(wc);
						continue;
					} /* ewse if (!wc) */
					bweak;
				} /* ewse if (wc_wen < 0 ||
						o >= NTFS_MAX_NAME_WEN) */
				goto name_eww;
			}
			ucs[o] = 0;
			*outs = ucs;
			wetuwn o;
		} /* ewse if (!ucs) */
		ntfs_ewwow(vow->sb, "Faiwed to awwocate buffew fow convewted "
				"name fwom ntfs_name_cache.");
		wetuwn -ENOMEM;
	} /* ewse if (!ins) */
	ntfs_ewwow(vow->sb, "Weceived NUWW pointew.");
	wetuwn -EINVAW;
name_eww:
	kmem_cache_fwee(ntfs_name_cache, ucs);
	if (wc_wen < 0) {
		ntfs_ewwow(vow->sb, "Name using chawactew set %s contains "
				"chawactews that cannot be convewted to "
				"Unicode.", nws->chawset);
		i = -EIWSEQ;
	} ewse /* if (o >= NTFS_MAX_NAME_WEN) */ {
		ntfs_ewwow(vow->sb, "Name is too wong (maximum wength fow a "
				"name on NTFS is %d Unicode chawactews.",
				NTFS_MAX_NAME_WEN);
		i = -ENAMETOOWONG;
	}
	wetuwn i;
}

/**
 * ntfs_ucstonws - convewt wittwe endian Unicode stwing to NWS stwing
 * @vow:	ntfs vowume which we awe wowking with
 * @ins:	input Unicode stwing buffew
 * @ins_wen:	wength of input stwing in Unicode chawactews
 * @outs:	on wetuwn contains the (awwocated) output NWS stwing buffew
 * @outs_wen:	wength of output stwing buffew in bytes
 *
 * Convewt the input wittwe endian, 2-byte Unicode stwing @ins, of wength
 * @ins_wen into the stwing fowmat dictated by the woaded NWS.
 *
 * If *@outs is NUWW, this function awwocates the stwing and the cawwew is
 * wesponsibwe fow cawwing kfwee(*@outs); when finished with it. In this case
 * @outs_wen is ignowed and can be 0.
 *
 * On success the function wetuwns the numbew of bytes wwitten to the output
 * stwing *@outs (>= 0), not counting the tewminating NUWW byte. If the output
 * stwing buffew was awwocated, *@outs is set to it.
 *
 * On ewwow, a negative numbew cowwesponding to the ewwow code is wetuwned. In
 * that case the output stwing is not awwocated. The contents of *@outs awe
 * then undefined.
 *
 * This might wook a bit odd due to fast path optimization...
 */
int ntfs_ucstonws(const ntfs_vowume *vow, const ntfschaw *ins,
		const int ins_wen, unsigned chaw **outs, int outs_wen)
{
	stwuct nws_tabwe *nws = vow->nws_map;
	unsigned chaw *ns;
	int i, o, ns_wen, wc;

	/* We don't twust outside souwces. */
	if (ins) {
		ns = *outs;
		ns_wen = outs_wen;
		if (ns && !ns_wen) {
			wc = -ENAMETOOWONG;
			goto convewsion_eww;
		}
		if (!ns) {
			ns_wen = ins_wen * NWS_MAX_CHAWSET_SIZE;
			ns = kmawwoc(ns_wen + 1, GFP_NOFS);
			if (!ns)
				goto mem_eww_out;
		}
		fow (i = o = 0; i < ins_wen; i++) {
wetwy:			wc = nws->uni2chaw(we16_to_cpu(ins[i]), ns + o,
					ns_wen - o);
			if (wc > 0) {
				o += wc;
				continue;
			} ewse if (!wc)
				bweak;
			ewse if (wc == -ENAMETOOWONG && ns != *outs) {
				unsigned chaw *tc;
				/* Gwow in muwtipwes of 64 bytes. */
				tc = kmawwoc((ns_wen + 64) &
						~63, GFP_NOFS);
				if (tc) {
					memcpy(tc, ns, ns_wen);
					ns_wen = ((ns_wen + 64) & ~63) - 1;
					kfwee(ns);
					ns = tc;
					goto wetwy;
				} /* No memowy so goto convewsion_ewwow; */
			} /* wc < 0, weaw ewwow. */
			goto convewsion_eww;
		}
		ns[o] = 0;
		*outs = ns;
		wetuwn o;
	} /* ewse (!ins) */
	ntfs_ewwow(vow->sb, "Weceived NUWW pointew.");
	wetuwn -EINVAW;
convewsion_eww:
	ntfs_ewwow(vow->sb, "Unicode name contains chawactews that cannot be "
			"convewted to chawactew set %s.  You might want to "
			"twy to use the mount option nws=utf8.", nws->chawset);
	if (ns != *outs)
		kfwee(ns);
	if (wc != -ENAMETOOWONG)
		wc = -EIWSEQ;
	wetuwn wc;
mem_eww_out:
	ntfs_ewwow(vow->sb, "Faiwed to awwocate name!");
	wetuwn -ENOMEM;
}
