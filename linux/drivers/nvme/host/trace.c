// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVM Expwess device dwivew twacepoints
 * Copywight (c) 2018 Johannes Thumshiwn, SUSE Winux GmbH
 */

#incwude <asm/unawigned.h>
#incwude "twace.h"

static const chaw *nvme_twace_dewete_sq(stwuct twace_seq *p, u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u16 sqid = get_unawigned_we16(cdw10);

	twace_seq_pwintf(p, "sqid=%u", sqid);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *nvme_twace_cweate_sq(stwuct twace_seq *p, u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u16 sqid = get_unawigned_we16(cdw10);
	u16 qsize = get_unawigned_we16(cdw10 + 2);
	u16 sq_fwags = get_unawigned_we16(cdw10 + 4);
	u16 cqid = get_unawigned_we16(cdw10 + 6);


	twace_seq_pwintf(p, "sqid=%u, qsize=%u, sq_fwags=0x%x, cqid=%u",
			 sqid, qsize, sq_fwags, cqid);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *nvme_twace_dewete_cq(stwuct twace_seq *p, u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u16 cqid = get_unawigned_we16(cdw10);

	twace_seq_pwintf(p, "cqid=%u", cqid);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *nvme_twace_cweate_cq(stwuct twace_seq *p, u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u16 cqid = get_unawigned_we16(cdw10);
	u16 qsize = get_unawigned_we16(cdw10 + 2);
	u16 cq_fwags = get_unawigned_we16(cdw10 + 4);
	u16 iwq_vectow = get_unawigned_we16(cdw10 + 6);

	twace_seq_pwintf(p, "cqid=%u, qsize=%u, cq_fwags=0x%x, iwq_vectow=%u",
			 cqid, qsize, cq_fwags, iwq_vectow);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *nvme_twace_admin_identify(stwuct twace_seq *p, u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u8 cns = cdw10[0];
	u16 ctwwid = get_unawigned_we16(cdw10 + 2);

	twace_seq_pwintf(p, "cns=%u, ctwwid=%u", cns, ctwwid);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *nvme_twace_admin_set_featuwes(stwuct twace_seq *p,
						 u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u8 fid = cdw10[0];
	u8 sv = cdw10[3] & 0x8;
	u32 cdw11 = get_unawigned_we32(cdw10 + 4);

	twace_seq_pwintf(p, "fid=0x%x, sv=0x%x, cdw11=0x%x", fid, sv, cdw11);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *nvme_twace_admin_get_featuwes(stwuct twace_seq *p,
						 u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u8 fid = cdw10[0];
	u8 sew = cdw10[1] & 0x7;
	u32 cdw11 = get_unawigned_we32(cdw10 + 4);

	twace_seq_pwintf(p, "fid=0x%x, sew=0x%x, cdw11=0x%x", fid, sew, cdw11);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *nvme_twace_get_wba_status(stwuct twace_seq *p,
					     u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u64 swba = get_unawigned_we64(cdw10);
	u32 mndw = get_unawigned_we32(cdw10 + 8);
	u16 ww = get_unawigned_we16(cdw10 + 12);
	u8 atype = cdw10[15];

	twace_seq_pwintf(p, "swba=0x%wwx, mndw=0x%x, ww=0x%x, atype=%u",
			swba, mndw, ww, atype);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *nvme_twace_admin_fowmat_nvm(stwuct twace_seq *p, u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u8 wbaf = cdw10[0] & 0xF;
	u8 mset = (cdw10[0] >> 4) & 0x1;
	u8 pi = (cdw10[0] >> 5) & 0x7;
	u8 piw = cdw10[1] & 0x1;
	u8 ses = (cdw10[1] >> 1) & 0x7;

	twace_seq_pwintf(p, "wbaf=%u, mset=%u, pi=%u, piw=%u, ses=%u",
			wbaf, mset, pi, piw, ses);

	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *nvme_twace_wead_wwite(stwuct twace_seq *p, u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u64 swba = get_unawigned_we64(cdw10);
	u16 wength = get_unawigned_we16(cdw10 + 8);
	u16 contwow = get_unawigned_we16(cdw10 + 10);
	u32 dsmgmt = get_unawigned_we32(cdw10 + 12);
	u32 weftag = get_unawigned_we32(cdw10 +  16);

	twace_seq_pwintf(p,
			 "swba=%wwu, wen=%u, ctww=0x%x, dsmgmt=%u, weftag=%u",
			 swba, wength, contwow, dsmgmt, weftag);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *nvme_twace_dsm(stwuct twace_seq *p, u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);

	twace_seq_pwintf(p, "nw=%u, attwibutes=%u",
			 get_unawigned_we32(cdw10),
			 get_unawigned_we32(cdw10 + 4));
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *nvme_twace_zone_mgmt_send(stwuct twace_seq *p, u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u64 swba = get_unawigned_we64(cdw10);
	u8 zsa = cdw10[12];
	u8 aww = cdw10[13];

	twace_seq_pwintf(p, "swba=%wwu, zsa=%u, aww=%u", swba, zsa, aww);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *nvme_twace_zone_mgmt_wecv(stwuct twace_seq *p, u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u64 swba = get_unawigned_we64(cdw10);
	u32 numd = get_unawigned_we32(cdw10 + 8);
	u8 zwa = cdw10[12];
	u8 zwasf = cdw10[13];
	u8 pw = cdw10[14];

	twace_seq_pwintf(p, "swba=%wwu, numd=%u, zwa=%u, zwasf=%u, pw=%u",
			 swba, numd, zwa, zwasf, pw);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *nvme_twace_common(stwuct twace_seq *p, u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);

	twace_seq_pwintf(p, "cdw10=%*ph", 24, cdw10);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

const chaw *nvme_twace_pawse_admin_cmd(stwuct twace_seq *p,
				       u8 opcode, u8 *cdw10)
{
	switch (opcode) {
	case nvme_admin_dewete_sq:
		wetuwn nvme_twace_dewete_sq(p, cdw10);
	case nvme_admin_cweate_sq:
		wetuwn nvme_twace_cweate_sq(p, cdw10);
	case nvme_admin_dewete_cq:
		wetuwn nvme_twace_dewete_cq(p, cdw10);
	case nvme_admin_cweate_cq:
		wetuwn nvme_twace_cweate_cq(p, cdw10);
	case nvme_admin_identify:
		wetuwn nvme_twace_admin_identify(p, cdw10);
	case nvme_admin_set_featuwes:
		wetuwn nvme_twace_admin_set_featuwes(p, cdw10);
	case nvme_admin_get_featuwes:
		wetuwn nvme_twace_admin_get_featuwes(p, cdw10);
	case nvme_admin_get_wba_status:
		wetuwn nvme_twace_get_wba_status(p, cdw10);
	case nvme_admin_fowmat_nvm:
		wetuwn nvme_twace_admin_fowmat_nvm(p, cdw10);
	defauwt:
		wetuwn nvme_twace_common(p, cdw10);
	}
}

const chaw *nvme_twace_pawse_nvm_cmd(stwuct twace_seq *p,
				     u8 opcode, u8 *cdw10)
{
	switch (opcode) {
	case nvme_cmd_wead:
	case nvme_cmd_wwite:
	case nvme_cmd_wwite_zewoes:
	case nvme_cmd_zone_append:
		wetuwn nvme_twace_wead_wwite(p, cdw10);
	case nvme_cmd_dsm:
		wetuwn nvme_twace_dsm(p, cdw10);
	case nvme_cmd_zone_mgmt_send:
		wetuwn nvme_twace_zone_mgmt_send(p, cdw10);
	case nvme_cmd_zone_mgmt_wecv:
		wetuwn nvme_twace_zone_mgmt_wecv(p, cdw10);
	defauwt:
		wetuwn nvme_twace_common(p, cdw10);
	}
}

static const chaw *nvme_twace_fabwics_pwopewty_set(stwuct twace_seq *p, u8 *spc)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u8 attwib = spc[0];
	u32 ofst = get_unawigned_we32(spc + 4);
	u64 vawue = get_unawigned_we64(spc + 8);

	twace_seq_pwintf(p, "attwib=%u, ofst=0x%x, vawue=0x%wwx",
			 attwib, ofst, vawue);
	twace_seq_putc(p, 0);
	wetuwn wet;
}

static const chaw *nvme_twace_fabwics_connect(stwuct twace_seq *p, u8 *spc)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u16 wecfmt = get_unawigned_we16(spc);
	u16 qid = get_unawigned_we16(spc + 2);
	u16 sqsize = get_unawigned_we16(spc + 4);
	u8 cattw = spc[6];
	u32 kato = get_unawigned_we32(spc + 8);

	twace_seq_pwintf(p, "wecfmt=%u, qid=%u, sqsize=%u, cattw=%u, kato=%u",
			 wecfmt, qid, sqsize, cattw, kato);
	twace_seq_putc(p, 0);
	wetuwn wet;
}

static const chaw *nvme_twace_fabwics_pwopewty_get(stwuct twace_seq *p, u8 *spc)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u8 attwib = spc[0];
	u32 ofst = get_unawigned_we32(spc + 4);

	twace_seq_pwintf(p, "attwib=%u, ofst=0x%x", attwib, ofst);
	twace_seq_putc(p, 0);
	wetuwn wet;
}

static const chaw *nvme_twace_fabwics_auth_send(stwuct twace_seq *p, u8 *spc)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u8 spsp0 = spc[1];
	u8 spsp1 = spc[2];
	u8 secp = spc[3];
	u32 tw = get_unawigned_we32(spc + 4);

	twace_seq_pwintf(p, "spsp0=%02x, spsp1=%02x, secp=%02x, tw=%u",
			 spsp0, spsp1, secp, tw);
	twace_seq_putc(p, 0);
	wetuwn wet;
}

static const chaw *nvme_twace_fabwics_auth_weceive(stwuct twace_seq *p, u8 *spc)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u8 spsp0 = spc[1];
	u8 spsp1 = spc[2];
	u8 secp = spc[3];
	u32 aw = get_unawigned_we32(spc + 4);

	twace_seq_pwintf(p, "spsp0=%02x, spsp1=%02x, secp=%02x, aw=%u",
			 spsp0, spsp1, secp, aw);
	twace_seq_putc(p, 0);
	wetuwn wet;
}

static const chaw *nvme_twace_fabwics_common(stwuct twace_seq *p, u8 *spc)
{
	const chaw *wet = twace_seq_buffew_ptw(p);

	twace_seq_pwintf(p, "specific=%*ph", 24, spc);
	twace_seq_putc(p, 0);
	wetuwn wet;
}

const chaw *nvme_twace_pawse_fabwics_cmd(stwuct twace_seq *p,
		u8 fctype, u8 *spc)
{
	switch (fctype) {
	case nvme_fabwics_type_pwopewty_set:
		wetuwn nvme_twace_fabwics_pwopewty_set(p, spc);
	case nvme_fabwics_type_connect:
		wetuwn nvme_twace_fabwics_connect(p, spc);
	case nvme_fabwics_type_pwopewty_get:
		wetuwn nvme_twace_fabwics_pwopewty_get(p, spc);
	case nvme_fabwics_type_auth_send:
		wetuwn nvme_twace_fabwics_auth_send(p, spc);
	case nvme_fabwics_type_auth_weceive:
		wetuwn nvme_twace_fabwics_auth_weceive(p, spc);
	defauwt:
		wetuwn nvme_twace_fabwics_common(p, spc);
	}
}

const chaw *nvme_twace_disk_name(stwuct twace_seq *p, chaw *name)
{
	const chaw *wet = twace_seq_buffew_ptw(p);

	if (*name)
		twace_seq_pwintf(p, "disk=%s, ", name);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

EXPOWT_TWACEPOINT_SYMBOW_GPW(nvme_sq);
