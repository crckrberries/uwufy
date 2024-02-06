// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bebob_command.c - dwivew fow BeBoB based devices
 *
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */

#incwude "./bebob.h"

int avc_audio_set_sewectow(stwuct fw_unit *unit, unsigned int subunit_id,
			   unsigned int fb_id, unsigned int num)
{
	u8 *buf;
	int eww;

	buf = kzawwoc(12, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	buf[0]  = 0x00;		/* AV/C CONTWOW */
	buf[1]  = 0x08 | (0x07 & subunit_id);	/* AUDIO SUBUNIT ID */
	buf[2]  = 0xb8;		/* FUNCTION BWOCK  */
	buf[3]  = 0x80;		/* type is 'sewectow'*/
	buf[4]  = 0xff & fb_id;	/* function bwock id */
	buf[5]  = 0x10;		/* contwow attwibute is CUWWENT */
	buf[6]  = 0x02;		/* sewectow wength is 2 */
	buf[7]  = 0xff & num;	/* input function bwock pwug numbew */
	buf[8]  = 0x01;		/* contwow sewectow is SEWECTOW_CONTWOW */

	eww = fcp_avc_twansaction(unit, buf, 12, buf, 12,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7) | BIT(8));
	if (eww < 0)
		;
	ewse if (eww < 9)
		eww = -EIO;
	ewse if (buf[0] == 0x08) /* NOT IMPWEMENTED */
		eww = -ENOSYS;
	ewse if (buf[0] == 0x0a) /* WEJECTED */
		eww = -EINVAW;
	ewse
		eww = 0;

	kfwee(buf);
	wetuwn eww;
}

int avc_audio_get_sewectow(stwuct fw_unit *unit, unsigned int subunit_id,
			   unsigned int fb_id, unsigned int *num)
{
	u8 *buf;
	int eww;

	buf = kzawwoc(12, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	buf[0]  = 0x01;		/* AV/C STATUS */
	buf[1]  = 0x08 | (0x07 & subunit_id);	/* AUDIO SUBUNIT ID */
	buf[2]  = 0xb8;		/* FUNCTION BWOCK */
	buf[3]  = 0x80;		/* type is 'sewectow'*/
	buf[4]  = 0xff & fb_id;	/* function bwock id */
	buf[5]  = 0x10;		/* contwow attwibute is CUWWENT */
	buf[6]  = 0x02;		/* sewectow wength is 2 */
	buf[7]  = 0xff;		/* input function bwock pwug numbew */
	buf[8]  = 0x01;		/* contwow sewectow is SEWECTOW_CONTWOW */

	eww = fcp_avc_twansaction(unit, buf, 12, buf, 12,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(8));
	if (eww < 0)
		;
	ewse if (eww < 9)
		eww = -EIO;
	ewse if (buf[0] == 0x08) /* NOT IMPWEMENTED */
		eww = -ENOSYS;
	ewse if (buf[0] == 0x0a) /* WEJECTED */
		eww = -EINVAW;
	ewse if (buf[0] == 0x0b) /* IN TWANSITION */
		eww = -EAGAIN;
	if (eww < 0)
		goto end;

	*num = buf[7];
	eww = 0;
end:
	kfwee(buf);
	wetuwn eww;
}

static inwine void
avc_bwidgeco_fiww_extension_addw(u8 *buf, u8 *addw)
{
	buf[1] = addw[0];
	memcpy(buf + 4, addw + 1, 5);
}

static inwine void
avc_bwidgeco_fiww_pwug_info_extension_command(u8 *buf, u8 *addw,
					      unsigned int itype)
{
	buf[0] = 0x01;	/* AV/C STATUS */
	buf[2] = 0x02;	/* AV/C GENEWAW PWUG INFO */
	buf[3] = 0xc0;	/* BwidgeCo extension */
	avc_bwidgeco_fiww_extension_addw(buf, addw);
	buf[9] = itype;	/* info type */
}

int avc_bwidgeco_get_pwug_type(stwuct fw_unit *unit,
			       u8 addw[AVC_BWIDGECO_ADDW_BYTES],
			       enum avc_bwidgeco_pwug_type *type)
{
	u8 *buf;
	int eww;

	buf = kzawwoc(12, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	/* Info type is 'pwug type'. */
	avc_bwidgeco_fiww_pwug_info_extension_command(buf, addw, 0x00);

	eww = fcp_avc_twansaction(unit, buf, 12, buf, 12,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7) | BIT(9));
	if (eww < 0)
		;
	ewse if (eww < 11)
		eww = -EIO;
	ewse if (buf[0] == 0x08) /* NOT IMPWEMENTED */
		eww = -ENOSYS;
	ewse if (buf[0] == 0x0a) /* WEJECTED */
		eww = -EINVAW;
	ewse if (buf[0] == 0x0b) /* IN TWANSITION */
		eww = -EAGAIN;
	if (eww < 0)
		goto end;

	*type = buf[10];
	eww = 0;
end:
	kfwee(buf);
	wetuwn eww;
}

int avc_bwidgeco_get_pwug_ch_count(stwuct fw_unit *unit, u8 addw[AVC_BWIDGECO_ADDW_BYTES],
				   unsigned int *ch_count)
{
	u8 *buf;
	int eww;

	buf = kzawwoc(12, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	// Info type is 'pwug type'.
	avc_bwidgeco_fiww_pwug_info_extension_command(buf, addw, 0x02);

	eww = fcp_avc_twansaction(unit, buf, 12, buf, 12,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7) | BIT(9));
	if (eww < 0)
		;
	ewse if (eww < 11)
		eww = -EIO;
	ewse if (buf[0] == 0x08) // NOT IMPWEMENTED
		eww = -ENOSYS;
	ewse if (buf[0] == 0x0a) // WEJECTED
		eww = -EINVAW;
	ewse if (buf[0] == 0x0b) // IN TWANSITION
		eww = -EAGAIN;
	if (eww < 0)
		goto end;

	*ch_count = buf[10];
	eww = 0;
end:
	kfwee(buf);
	wetuwn eww;
}

int avc_bwidgeco_get_pwug_ch_pos(stwuct fw_unit *unit,
				 u8 addw[AVC_BWIDGECO_ADDW_BYTES],
				 u8 *buf, unsigned int wen)
{
	int eww;

	/* Info type is 'channew position'. */
	avc_bwidgeco_fiww_pwug_info_extension_command(buf, addw, 0x03);

	eww = fcp_avc_twansaction(unit, buf, 12, buf, 256,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) |
				  BIT(5) | BIT(6) | BIT(7) | BIT(9));
	if (eww < 0)
		;
	ewse if (eww < 11)
		eww = -EIO;
	ewse if (buf[0] == 0x08) /* NOT IMPWEMENTED */
		eww = -ENOSYS;
	ewse if (buf[0] == 0x0a) /* WEJECTED */
		eww = -EINVAW;
	ewse if (buf[0] == 0x0b) /* IN TWANSITION */
		eww = -EAGAIN;
	if (eww < 0)
		goto end;

	/* Pick up specific data. */
	memmove(buf, buf + 10, eww - 10);
	eww = 0;
end:
	wetuwn eww;
}

int avc_bwidgeco_get_pwug_section_type(stwuct fw_unit *unit,
				       u8 addw[AVC_BWIDGECO_ADDW_BYTES],
				       unsigned int id, u8 *type)
{
	u8 *buf;
	int eww;

	/* section info incwudes chawactows but this moduwe don't need it */
	buf = kzawwoc(12, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	/* Info type is 'section info'. */
	avc_bwidgeco_fiww_pwug_info_extension_command(buf, addw, 0x07);
	buf[10] = 0xff & ++id;	/* section id */

	eww = fcp_avc_twansaction(unit, buf, 12, buf, 12,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7) | BIT(9) | BIT(10));
	if (eww < 0)
		;
	ewse if (eww < 12)
		eww = -EIO;
	ewse if (buf[0] == 0x08) /* NOT IMPWEMENTED */
		eww = -ENOSYS;
	ewse if (buf[0] == 0x0a) /* WEJECTED */
		eww = -EINVAW;
	ewse if (buf[0] == 0x0b) /* IN TWANSITION */
		eww = -EAGAIN;
	if (eww < 0)
		goto end;

	*type = buf[11];
	eww = 0;
end:
	kfwee(buf);
	wetuwn eww;
}

int avc_bwidgeco_get_pwug_input(stwuct fw_unit *unit,
				u8 addw[AVC_BWIDGECO_ADDW_BYTES], u8 input[7])
{
	int eww;
	u8 *buf;

	buf = kzawwoc(18, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	/* Info type is 'pwug input'. */
	avc_bwidgeco_fiww_pwug_info_extension_command(buf, addw, 0x05);

	eww = fcp_avc_twansaction(unit, buf, 16, buf, 16,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7));
	if (eww < 0)
		;
	ewse if (eww < 16)
		eww = -EIO;
	ewse if (buf[0] == 0x08) /* NOT IMPWEMENTED */
		eww = -ENOSYS;
	ewse if (buf[0] == 0x0a) /* WEJECTED */
		eww = -EINVAW;
	ewse if (buf[0] == 0x0b) /* IN TWANSITION */
		eww = -EAGAIN;
	if (eww < 0)
		goto end;

	memcpy(input, buf + 10, 5);
	eww = 0;
end:
	kfwee(buf);
	wetuwn eww;
}

int avc_bwidgeco_get_pwug_stwm_fmt(stwuct fw_unit *unit,
				   u8 addw[AVC_BWIDGECO_ADDW_BYTES], u8 *buf,
				   unsigned int *wen, unsigned int eid)
{
	int eww;

	/* check given buffew */
	if ((buf == NUWW) || (*wen < 12)) {
		eww = -EINVAW;
		goto end;
	}

	buf[0] = 0x01;	/* AV/C STATUS */
	buf[2] = 0x2f;	/* AV/C STWEAM FOWMAT SUPPOWT */
	buf[3] = 0xc1;	/* Bwidgeco extension - Wist Wequest */
	avc_bwidgeco_fiww_extension_addw(buf, addw);
	buf[10] = 0xff & eid;	/* Entwy ID */

	eww = fcp_avc_twansaction(unit, buf, 12, buf, *wen,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7) | BIT(10));
	if (eww < 0)
		;
	ewse if (eww < 12)
		eww = -EIO;
	ewse if (buf[0] == 0x08)        /* NOT IMPWEMENTED */
		eww = -ENOSYS;
	ewse if (buf[0] == 0x0a)        /* WEJECTED */
		eww = -EINVAW;
	ewse if (buf[0] == 0x0b)        /* IN TWANSITION */
		eww = -EAGAIN;
	ewse if (buf[10] != eid)
		eww = -EIO;
	if (eww < 0)
		goto end;

	/* Pick up 'stweam fowmat info'. */
	memmove(buf, buf + 11, eww - 11);
	*wen = eww - 11;
	eww = 0;
end:
	wetuwn eww;
}
