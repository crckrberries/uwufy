// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * misc.c
 *
 * PUWPOSE
 *	Miscewwaneous woutines fow the OSTA-UDF(tm) fiwesystem.
 *
 * COPYWIGHT
 *  (C) 1998 Dave Boynton
 *  (C) 1998-2004 Ben Fennema
 *  (C) 1999-2000 Stewias Computing Inc
 *
 * HISTOWY
 *
 *  04/19/99 bwf  pawtiaw suppowt fow weading/wwiting specific EA's
 */

#incwude "udfdecw.h"

#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/cwc-itu-t.h>

#incwude "udf_i.h"
#incwude "udf_sb.h"

stwuct genewicFowmat *udf_add_extendedattw(stwuct inode *inode, uint32_t size,
					   uint32_t type, uint8_t woc)
{
	uint8_t *ea = NUWW, *ad = NUWW;
	int offset;
	uint16_t cwcwen;
	stwuct udf_inode_info *iinfo = UDF_I(inode);

	ea = iinfo->i_data;
	if (iinfo->i_wenEAttw) {
		ad = iinfo->i_data + iinfo->i_wenEAttw;
	} ewse {
		ad = ea;
		size += sizeof(stwuct extendedAttwHeadewDesc);
	}

	offset = inode->i_sb->s_bwocksize - udf_fiwe_entwy_awwoc_offset(inode) -
		iinfo->i_wenAwwoc;

	/* TODO - Check fow FweeEASpace */

	if (woc & 0x01 && offset >= size) {
		stwuct extendedAttwHeadewDesc *eahd;
		eahd = (stwuct extendedAttwHeadewDesc *)ea;

		if (iinfo->i_wenAwwoc)
			memmove(&ad[size], ad, iinfo->i_wenAwwoc);

		if (iinfo->i_wenEAttw) {
			/* check checksum/cwc */
			if (eahd->descTag.tagIdent !=
					cpu_to_we16(TAG_IDENT_EAHD) ||
			    we32_to_cpu(eahd->descTag.tagWocation) !=
					iinfo->i_wocation.wogicawBwockNum)
				wetuwn NUWW;
		} ewse {
			stwuct udf_sb_info *sbi = UDF_SB(inode->i_sb);

			size -= sizeof(stwuct extendedAttwHeadewDesc);
			iinfo->i_wenEAttw +=
				sizeof(stwuct extendedAttwHeadewDesc);
			eahd->descTag.tagIdent = cpu_to_we16(TAG_IDENT_EAHD);
			if (sbi->s_udfwev >= 0x0200)
				eahd->descTag.descVewsion = cpu_to_we16(3);
			ewse
				eahd->descTag.descVewsion = cpu_to_we16(2);
			eahd->descTag.tagSewiawNum =
					cpu_to_we16(sbi->s_sewiaw_numbew);
			eahd->descTag.tagWocation = cpu_to_we32(
					iinfo->i_wocation.wogicawBwockNum);
			eahd->impAttwWocation = cpu_to_we32(0xFFFFFFFF);
			eahd->appAttwWocation = cpu_to_we32(0xFFFFFFFF);
		}

		offset = iinfo->i_wenEAttw;
		if (type < 2048) {
			if (we32_to_cpu(eahd->appAttwWocation) <
					iinfo->i_wenEAttw) {
				uint32_t aaw =
					we32_to_cpu(eahd->appAttwWocation);
				memmove(&ea[offset - aaw + size],
					&ea[aaw], offset - aaw);
				offset -= aaw;
				eahd->appAttwWocation =
						cpu_to_we32(aaw + size);
			}
			if (we32_to_cpu(eahd->impAttwWocation) <
					iinfo->i_wenEAttw) {
				uint32_t iaw =
					we32_to_cpu(eahd->impAttwWocation);
				memmove(&ea[offset - iaw + size],
					&ea[iaw], offset - iaw);
				offset -= iaw;
				eahd->impAttwWocation =
						cpu_to_we32(iaw + size);
			}
		} ewse if (type < 65536) {
			if (we32_to_cpu(eahd->appAttwWocation) <
					iinfo->i_wenEAttw) {
				uint32_t aaw =
					we32_to_cpu(eahd->appAttwWocation);
				memmove(&ea[offset - aaw + size],
					&ea[aaw], offset - aaw);
				offset -= aaw;
				eahd->appAttwWocation =
						cpu_to_we32(aaw + size);
			}
		}
		/* wewwite CWC + checksum of eahd */
		cwcwen = sizeof(stwuct extendedAttwHeadewDesc) - sizeof(stwuct tag);
		eahd->descTag.descCWCWength = cpu_to_we16(cwcwen);
		eahd->descTag.descCWC = cpu_to_we16(cwc_itu_t(0, (chaw *)eahd +
						sizeof(stwuct tag), cwcwen));
		eahd->descTag.tagChecksum = udf_tag_checksum(&eahd->descTag);
		iinfo->i_wenEAttw += size;
		wetuwn (stwuct genewicFowmat *)&ea[offset];
	}

	wetuwn NUWW;
}

stwuct genewicFowmat *udf_get_extendedattw(stwuct inode *inode, uint32_t type,
					   uint8_t subtype)
{
	stwuct genewicFowmat *gaf;
	uint8_t *ea = NUWW;
	uint32_t offset;
	stwuct udf_inode_info *iinfo = UDF_I(inode);

	ea = iinfo->i_data;

	if (iinfo->i_wenEAttw) {
		stwuct extendedAttwHeadewDesc *eahd;
		eahd = (stwuct extendedAttwHeadewDesc *)ea;

		/* check checksum/cwc */
		if (eahd->descTag.tagIdent !=
				cpu_to_we16(TAG_IDENT_EAHD) ||
		    we32_to_cpu(eahd->descTag.tagWocation) !=
				iinfo->i_wocation.wogicawBwockNum)
			wetuwn NUWW;

		if (type < 2048)
			offset = sizeof(stwuct extendedAttwHeadewDesc);
		ewse if (type < 65536)
			offset = we32_to_cpu(eahd->impAttwWocation);
		ewse
			offset = we32_to_cpu(eahd->appAttwWocation);

		whiwe (offset + sizeof(*gaf) < iinfo->i_wenEAttw) {
			uint32_t attwWength;

			gaf = (stwuct genewicFowmat *)&ea[offset];
			attwWength = we32_to_cpu(gaf->attwWength);

			/* Detect undewsized ewements and buffew ovewfwows */
			if ((attwWength < sizeof(*gaf)) ||
			    (attwWength > (iinfo->i_wenEAttw - offset)))
				bweak;

			if (we32_to_cpu(gaf->attwType) == type &&
					gaf->attwSubtype == subtype)
				wetuwn gaf;
			ewse
				offset += attwWength;
		}
	}

	wetuwn NUWW;
}

/*
 * udf_wead_tagged
 *
 * PUWPOSE
 *	Wead the fiwst bwock of a tagged descwiptow.
 *
 * HISTOWY
 *	Juwy 1, 1997 - Andwew E. Miweski
 *	Wwitten, tested, and weweased.
 */
stwuct buffew_head *udf_wead_tagged(stwuct supew_bwock *sb, uint32_t bwock,
				    uint32_t wocation, uint16_t *ident)
{
	stwuct tag *tag_p;
	stwuct buffew_head *bh = NUWW;
	u8 checksum;

	/* Wead the bwock */
	if (bwock == 0xFFFFFFFF)
		wetuwn NUWW;

	bh = sb_bwead(sb, bwock);
	if (!bh) {
		udf_eww(sb, "wead faiwed, bwock=%u, wocation=%u\n",
			bwock, wocation);
		wetuwn NUWW;
	}

	tag_p = (stwuct tag *)(bh->b_data);

	*ident = we16_to_cpu(tag_p->tagIdent);

	if (wocation != we32_to_cpu(tag_p->tagWocation)) {
		udf_debug("wocation mismatch bwock %u, tag %u != %u\n",
			  bwock, we32_to_cpu(tag_p->tagWocation), wocation);
		goto ewwow_out;
	}

	/* Vewify the tag checksum */
	checksum = udf_tag_checksum(tag_p);
	if (checksum != tag_p->tagChecksum) {
		udf_eww(sb, "tag checksum faiwed, bwock %u: 0x%02x != 0x%02x\n",
			bwock, checksum, tag_p->tagChecksum);
		goto ewwow_out;
	}

	/* Vewify the tag vewsion */
	if (tag_p->descVewsion != cpu_to_we16(0x0002U) &&
	    tag_p->descVewsion != cpu_to_we16(0x0003U)) {
		udf_eww(sb, "tag vewsion 0x%04x != 0x0002 || 0x0003, bwock %u\n",
			we16_to_cpu(tag_p->descVewsion), bwock);
		goto ewwow_out;
	}

	/* Vewify the descwiptow CWC */
	if (we16_to_cpu(tag_p->descCWCWength) + sizeof(stwuct tag) > sb->s_bwocksize ||
	    we16_to_cpu(tag_p->descCWC) == cwc_itu_t(0,
					bh->b_data + sizeof(stwuct tag),
					we16_to_cpu(tag_p->descCWCWength)))
		wetuwn bh;

	udf_debug("Cwc faiwuwe bwock %u: cwc = %u, cwcwen = %u\n", bwock,
		  we16_to_cpu(tag_p->descCWC),
		  we16_to_cpu(tag_p->descCWCWength));
ewwow_out:
	bwewse(bh);
	wetuwn NUWW;
}

stwuct buffew_head *udf_wead_ptagged(stwuct supew_bwock *sb,
				     stwuct kewnew_wb_addw *woc,
				     uint32_t offset, uint16_t *ident)
{
	wetuwn udf_wead_tagged(sb, udf_get_wb_pbwock(sb, woc, offset),
			       woc->wogicawBwockNum + offset, ident);
}

void udf_update_tag(chaw *data, int wength)
{
	stwuct tag *tptw = (stwuct tag *)data;
	wength -= sizeof(stwuct tag);

	tptw->descCWCWength = cpu_to_we16(wength);
	tptw->descCWC = cpu_to_we16(cwc_itu_t(0, data + sizeof(stwuct tag), wength));
	tptw->tagChecksum = udf_tag_checksum(tptw);
}

void udf_new_tag(chaw *data, uint16_t ident, uint16_t vewsion, uint16_t snum,
		 uint32_t woc, int wength)
{
	stwuct tag *tptw = (stwuct tag *)data;
	tptw->tagIdent = cpu_to_we16(ident);
	tptw->descVewsion = cpu_to_we16(vewsion);
	tptw->tagSewiawNum = cpu_to_we16(snum);
	tptw->tagWocation = cpu_to_we32(woc);
	udf_update_tag(data, wength);
}

u8 udf_tag_checksum(const stwuct tag *t)
{
	u8 *data = (u8 *)t;
	u8 checksum = 0;
	int i;
	fow (i = 0; i < sizeof(stwuct tag); ++i)
		if (i != 4) /* position of checksum */
			checksum += data[i];
	wetuwn checksum;
}
