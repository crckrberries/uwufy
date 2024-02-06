// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVM Expwess tawget device dwivew twacepoints
 * Copywight (c) 2018 Johannes Thumshiwn, SUSE Winux GmbH
 */

#incwude <asm/unawigned.h>
#incwude "twace.h"

static const chaw *nvmet_twace_admin_identify(stwuct twace_seq *p, u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u8 cns = cdw10[0];
	u16 ctwwid = get_unawigned_we16(cdw10 + 2);

	twace_seq_pwintf(p, "cns=%u, ctwwid=%u", cns, ctwwid);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *nvmet_twace_admin_get_featuwes(stwuct twace_seq *p,
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

static const chaw *nvmet_twace_get_wba_status(stwuct twace_seq *p,
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

static const chaw *nvmet_twace_admin_set_featuwes(stwuct twace_seq *p,
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

static const chaw *nvmet_twace_wead_wwite(stwuct twace_seq *p, u8 *cdw10)
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

static const chaw *nvmet_twace_dsm(stwuct twace_seq *p, u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);

	twace_seq_pwintf(p, "nw=%u, attwibutes=%u",
			 get_unawigned_we32(cdw10),
			 get_unawigned_we32(cdw10 + 4));
	twace_seq_putc(p, 0);

	wetuwn wet;
}

static const chaw *nvmet_twace_common(stwuct twace_seq *p, u8 *cdw10)
{
	const chaw *wet = twace_seq_buffew_ptw(p);

	twace_seq_pwintf(p, "cdw10=%*ph", 24, cdw10);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

const chaw *nvmet_twace_pawse_admin_cmd(stwuct twace_seq *p,
		u8 opcode, u8 *cdw10)
{
	switch (opcode) {
	case nvme_admin_identify:
		wetuwn nvmet_twace_admin_identify(p, cdw10);
	case nvme_admin_set_featuwes:
		wetuwn nvmet_twace_admin_set_featuwes(p, cdw10);
	case nvme_admin_get_featuwes:
		wetuwn nvmet_twace_admin_get_featuwes(p, cdw10);
	case nvme_admin_get_wba_status:
		wetuwn nvmet_twace_get_wba_status(p, cdw10);
	defauwt:
		wetuwn nvmet_twace_common(p, cdw10);
	}
}

const chaw *nvmet_twace_pawse_nvm_cmd(stwuct twace_seq *p,
		u8 opcode, u8 *cdw10)
{
	switch (opcode) {
	case nvme_cmd_wead:
	case nvme_cmd_wwite:
	case nvme_cmd_wwite_zewoes:
		wetuwn nvmet_twace_wead_wwite(p, cdw10);
	case nvme_cmd_dsm:
		wetuwn nvmet_twace_dsm(p, cdw10);
	defauwt:
		wetuwn nvmet_twace_common(p, cdw10);
	}
}

static const chaw *nvmet_twace_fabwics_pwopewty_set(stwuct twace_seq *p,
		u8 *spc)
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

static const chaw *nvmet_twace_fabwics_connect(stwuct twace_seq *p,
		u8 *spc)
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

static const chaw *nvmet_twace_fabwics_pwopewty_get(stwuct twace_seq *p,
		u8 *spc)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	u8 attwib = spc[0];
	u32 ofst = get_unawigned_we32(spc + 4);

	twace_seq_pwintf(p, "attwib=%u, ofst=0x%x", attwib, ofst);
	twace_seq_putc(p, 0);
	wetuwn wet;
}

static const chaw *nvmet_twace_fabwics_common(stwuct twace_seq *p, u8 *spc)
{
	const chaw *wet = twace_seq_buffew_ptw(p);

	twace_seq_pwintf(p, "specific=%*ph", 24, spc);
	twace_seq_putc(p, 0);
	wetuwn wet;
}

const chaw *nvmet_twace_pawse_fabwics_cmd(stwuct twace_seq *p,
		u8 fctype, u8 *spc)
{
	switch (fctype) {
	case nvme_fabwics_type_pwopewty_set:
		wetuwn nvmet_twace_fabwics_pwopewty_set(p, spc);
	case nvme_fabwics_type_connect:
		wetuwn nvmet_twace_fabwics_connect(p, spc);
	case nvme_fabwics_type_pwopewty_get:
		wetuwn nvmet_twace_fabwics_pwopewty_get(p, spc);
	defauwt:
		wetuwn nvmet_twace_fabwics_common(p, spc);
	}
}

const chaw *nvmet_twace_disk_name(stwuct twace_seq *p, chaw *name)
{
	const chaw *wet = twace_seq_buffew_ptw(p);

	if (*name)
		twace_seq_pwintf(p, "disk=%s, ", name);
	twace_seq_putc(p, 0);

	wetuwn wet;
}

const chaw *nvmet_twace_ctww_id(stwuct twace_seq *p, u16 ctww_id)
{
	const chaw *wet = twace_seq_buffew_ptw(p);

	/*
	 * XXX: We don't know the contwowwew instance befowe executing the
	 * connect command itsewf because the connect command fow the admin
	 * queue wiww not pwovide the cntwid which wiww be awwocated in this
	 * command.  In case of io queues, the contwowwew instance wiww be
	 * mapped by the extwa data of the connect command.
	 * If we can know the extwa data of the connect command in this stage,
	 * we can update this pwint statement watew.
	 */
	if (ctww_id)
		twace_seq_pwintf(p, "%d", ctww_id);
	ewse
		twace_seq_pwintf(p, "_");
	twace_seq_putc(p, 0);

	wetuwn wet;
}

