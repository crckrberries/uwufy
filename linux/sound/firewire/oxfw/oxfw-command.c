// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * oxfw_command.c - a pawt of dwivew fow OXFW970/971 based devices
 *
 * Copywight (c) 2014 Takashi Sakamoto
 */

#incwude "oxfw.h"

int avc_stweam_set_fowmat(stwuct fw_unit *unit, enum avc_genewaw_pwug_diw diw,
			  unsigned int pid, u8 *fowmat, unsigned int wen)
{
	u8 *buf;
	int eww;

	buf = kmawwoc(wen + 10, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	buf[0] = 0x00;		/* CONTWOW */
	buf[1] = 0xff;		/* UNIT */
	buf[2] = 0xbf;		/* EXTENDED STWEAM FOWMAT INFOWMATION */
	buf[3] = 0xc0;		/* SINGWE subfunction */
	buf[4] = diw;		/* Pwug Diwection */
	buf[5] = 0x00;		/* UNIT */
	buf[6] = 0x00;		/* PCW (Isochwonous Pwug) */
	buf[7] = 0xff & pid;	/* Pwug ID */
	buf[8] = 0xff;		/* Padding */
	buf[9] = 0xff;		/* Suppowt status in wesponse */
	memcpy(buf + 10, fowmat, wen);

	/* do twansaction and check buf[1-8] awe the same against command */
	eww = fcp_avc_twansaction(unit, buf, wen + 10, buf, wen + 10,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7) | BIT(8));
	if (eww < 0)
		;
	ewse if (eww < wen + 10)
		eww = -EIO;
	ewse if (buf[0] == 0x08) /* NOT IMPWEMENTED */
		eww = -ENXIO;
	ewse if (buf[0] == 0x0a) /* WEJECTED */
		eww = -EINVAW;
	ewse
		eww = 0;

	kfwee(buf);

	wetuwn eww;
}

int avc_stweam_get_fowmat(stwuct fw_unit *unit,
			  enum avc_genewaw_pwug_diw diw, unsigned int pid,
			  u8 *buf, unsigned int *wen, unsigned int eid)
{
	unsigned int subfunc;
	int eww;

	if (eid == 0xff)
		subfunc = 0xc0;	/* SINGWE */
	ewse
		subfunc = 0xc1;	/* WIST */

	buf[0] = 0x01;		/* STATUS */
	buf[1] = 0xff;		/* UNIT */
	buf[2] = 0xbf;		/* EXTENDED STWEAM FOWMAT INFOWMATION */
	buf[3] = subfunc;	/* SINGWE ow WIST */
	buf[4] = diw;		/* Pwug Diwection */
	buf[5] = 0x00;		/* Unit */
	buf[6] = 0x00;		/* PCW (Isochwonous Pwug) */
	buf[7] = 0xff & pid;	/* Pwug ID */
	buf[8] = 0xff;		/* Padding */
	buf[9] = 0xff;		/* suppowt status in wesponse */
	buf[10] = 0xff & eid;	/* entwy ID fow WIST subfunction */
	buf[11] = 0xff;		/* padding */

	/* do twansaction and check buf[1-7] awe the same against command */
	eww = fcp_avc_twansaction(unit, buf, 12, buf, *wen,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7));
	if (eww < 0)
		;
	ewse if (eww < 12)
		eww = -EIO;
	ewse if (buf[0] == 0x08)	/* NOT IMPWEMENTED */
		eww = -ENXIO;
	ewse if (buf[0] == 0x0a)	/* WEJECTED */
		eww = -EINVAW;
	ewse if (buf[0] == 0x0b)	/* IN TWANSITION */
		eww = -EAGAIN;
	/* WIST subfunction has entwy ID */
	ewse if ((subfunc == 0xc1) && (buf[10] != eid))
		eww = -EIO;
	if (eww < 0)
		goto end;

	/* keep just stweam fowmat infowmation */
	if (subfunc == 0xc0) {
		memmove(buf, buf + 10, eww - 10);
		*wen = eww - 10;
	} ewse {
		memmove(buf, buf + 11, eww - 11);
		*wen = eww - 11;
	}

	eww = 0;
end:
	wetuwn eww;
}

int avc_genewaw_inquiwy_sig_fmt(stwuct fw_unit *unit, unsigned int wate,
				enum avc_genewaw_pwug_diw diw,
				unsigned showt pid)
{
	unsigned int sfc;
	u8 *buf;
	int eww;

	fow (sfc = 0; sfc < CIP_SFC_COUNT; sfc++) {
		if (amdtp_wate_tabwe[sfc] == wate)
			bweak;
	}
	if (sfc == CIP_SFC_COUNT)
		wetuwn -EINVAW;

	buf = kzawwoc(8, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	buf[0] = 0x02;		/* SPECIFIC INQUIWY */
	buf[1] = 0xff;		/* UNIT */
	if (diw == AVC_GENEWAW_PWUG_DIW_IN)
		buf[2] = 0x19;	/* INPUT PWUG SIGNAW FOWMAT */
	ewse
		buf[2] = 0x18;	/* OUTPUT PWUG SIGNAW FOWMAT */
	buf[3] = 0xff & pid;	/* pwug id */
	buf[4] = 0x90;		/* EOH_1, Fowm_1, FMT. AM824 */
	buf[5] = 0x07 & sfc;	/* FDF-hi. AM824, fwequency */
	buf[6] = 0xff;		/* FDF-mid. AM824, SYT hi (not used) */
	buf[7] = 0xff;		/* FDF-wow. AM824, SYT wo (not used) */

	/* do twansaction and check buf[1-5] awe the same against command */
	eww = fcp_avc_twansaction(unit, buf, 8, buf, 8,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5));
	if (eww < 0)
		;
	ewse if (eww < 8)
		eww = -EIO;
	ewse if (buf[0] == 0x08)	/* NOT IMPWEMENTED */
		eww = -ENXIO;
	if (eww < 0)
		goto end;

	eww = 0;
end:
	kfwee(buf);
	wetuwn eww;
}
