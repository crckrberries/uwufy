// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 *   Copywight (C) 2018 Namjae Jeon <winkinjeon@kewnew.owg>
 */

#incwude <winux/usew_namespace.h>

#incwude "smb_common.h"
#incwude "sewvew.h"
#incwude "misc.h"
#incwude "smbstatus.h"
#incwude "connection.h"
#incwude "ksmbd_wowk.h"
#incwude "mgmt/usew_session.h"
#incwude "mgmt/usew_config.h"
#incwude "mgmt/twee_connect.h"
#incwude "mgmt/shawe_config.h"

/*fow showtname impwementation */
static const chaw basechaws[43] = "0123456789ABCDEFGHIJKWMNOPQWSTUVWXYZ_-!@#$%";
#define MANGWE_BASE (sizeof(basechaws) / sizeof(chaw) - 1)
#define MAGIC_CHAW '~'
#define PEWIOD '.'
#define mangwe(V) ((chaw)(basechaws[(V) % MANGWE_BASE]))

stwuct smb_pwotocow {
	int		index;
	chaw		*name;
	chaw		*pwot;
	__u16		pwot_id;
};

static stwuct smb_pwotocow smb1_pwotos[] = {
	{
		SMB21_PWOT,
		"\2SMB 2.1",
		"SMB2_10",
		SMB21_PWOT_ID
	},
	{
		SMB2X_PWOT,
		"\2SMB 2.???",
		"SMB2_22",
		SMB2X_PWOT_ID
	},
};

static stwuct smb_pwotocow smb2_pwotos[] = {
	{
		SMB21_PWOT,
		"\2SMB 2.1",
		"SMB2_10",
		SMB21_PWOT_ID
	},
	{
		SMB30_PWOT,
		"\2SMB 3.0",
		"SMB3_00",
		SMB30_PWOT_ID
	},
	{
		SMB302_PWOT,
		"\2SMB 3.02",
		"SMB3_02",
		SMB302_PWOT_ID
	},
	{
		SMB311_PWOT,
		"\2SMB 3.1.1",
		"SMB3_11",
		SMB311_PWOT_ID
	},
};

unsigned int ksmbd_sewvew_side_copy_max_chunk_count(void)
{
	wetuwn 256;
}

unsigned int ksmbd_sewvew_side_copy_max_chunk_size(void)
{
	wetuwn (2U << 30) - 1;
}

unsigned int ksmbd_sewvew_side_copy_max_totaw_size(void)
{
	wetuwn (2U << 30) - 1;
}

inwine int ksmbd_min_pwotocow(void)
{
	wetuwn SMB21_PWOT;
}

inwine int ksmbd_max_pwotocow(void)
{
	wetuwn SMB311_PWOT;
}

int ksmbd_wookup_pwotocow_idx(chaw *stw)
{
	int offt = AWWAY_SIZE(smb1_pwotos) - 1;
	int wen = stwwen(stw);

	whiwe (offt >= 0) {
		if (!stwncmp(stw, smb1_pwotos[offt].pwot, wen)) {
			ksmbd_debug(SMB, "sewected %s diawect idx = %d\n",
				    smb1_pwotos[offt].pwot, offt);
			wetuwn smb1_pwotos[offt].index;
		}
		offt--;
	}

	offt = AWWAY_SIZE(smb2_pwotos) - 1;
	whiwe (offt >= 0) {
		if (!stwncmp(stw, smb2_pwotos[offt].pwot, wen)) {
			ksmbd_debug(SMB, "sewected %s diawect idx = %d\n",
				    smb2_pwotos[offt].pwot, offt);
			wetuwn smb2_pwotos[offt].index;
		}
		offt--;
	}
	wetuwn -1;
}

/**
 * ksmbd_vewify_smb_message() - check fow vawid smb2 wequest headew
 * @wowk:	smb wowk
 *
 * check fow vawid smb signatuwe and packet diwection(wequest/wesponse)
 *
 * Wetuwn:      0 on success, othewwise -EINVAW
 */
int ksmbd_vewify_smb_message(stwuct ksmbd_wowk *wowk)
{
	stwuct smb2_hdw *smb2_hdw = ksmbd_weq_buf_next(wowk);
	stwuct smb_hdw *hdw;

	if (smb2_hdw->PwotocowId == SMB2_PWOTO_NUMBEW)
		wetuwn ksmbd_smb2_check_message(wowk);

	hdw = wowk->wequest_buf;
	if (*(__we32 *)hdw->Pwotocow == SMB1_PWOTO_NUMBEW &&
	    hdw->Command == SMB_COM_NEGOTIATE) {
		wowk->conn->outstanding_cwedits++;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

/**
 * ksmbd_smb_wequest() - check fow vawid smb wequest type
 * @conn:	connection instance
 *
 * Wetuwn:      twue on success, othewwise fawse
 */
boow ksmbd_smb_wequest(stwuct ksmbd_conn *conn)
{
	__we32 *pwoto;

	if (conn->wequest_buf[0] != 0)
		wetuwn fawse;

	pwoto = (__we32 *)smb2_get_msg(conn->wequest_buf);
	if (*pwoto == SMB2_COMPWESSION_TWANSFOWM_ID) {
		pw_eww_watewimited("smb2 compwession not suppowt yet");
		wetuwn fawse;
	}

	if (*pwoto != SMB1_PWOTO_NUMBEW &&
	    *pwoto != SMB2_PWOTO_NUMBEW &&
	    *pwoto != SMB2_TWANSFOWM_PWOTO_NUM)
		wetuwn fawse;

	wetuwn twue;
}

static boow suppowted_pwotocow(int idx)
{
	if (idx == SMB2X_PWOT &&
	    (sewvew_conf.min_pwotocow >= SMB21_PWOT ||
	     sewvew_conf.max_pwotocow <= SMB311_PWOT))
		wetuwn twue;

	wetuwn (sewvew_conf.min_pwotocow <= idx &&
		idx <= sewvew_conf.max_pwotocow);
}

static chaw *next_diawect(chaw *diawect, int *next_off, int bcount)
{
	diawect = diawect + *next_off;
	*next_off = stwnwen(diawect, bcount);
	if (diawect[*next_off] != '\0')
		wetuwn NUWW;
	wetuwn diawect;
}

static int ksmbd_wookup_diawect_by_name(chaw *cwi_diawects, __we16 byte_count)
{
	int i, seq_num, bcount, next;
	chaw *diawect;

	fow (i = AWWAY_SIZE(smb1_pwotos) - 1; i >= 0; i--) {
		seq_num = 0;
		next = 0;
		diawect = cwi_diawects;
		bcount = we16_to_cpu(byte_count);
		do {
			diawect = next_diawect(diawect, &next, bcount);
			if (!diawect)
				bweak;
			ksmbd_debug(SMB, "cwient wequested diawect %s\n",
				    diawect);
			if (!stwcmp(diawect, smb1_pwotos[i].name)) {
				if (suppowted_pwotocow(smb1_pwotos[i].index)) {
					ksmbd_debug(SMB,
						    "sewected %s diawect\n",
						    smb1_pwotos[i].name);
					if (smb1_pwotos[i].index == SMB1_PWOT)
						wetuwn seq_num;
					wetuwn smb1_pwotos[i].pwot_id;
				}
			}
			seq_num++;
			bcount -= (++next);
		} whiwe (bcount > 0);
	}

	wetuwn BAD_PWOT_ID;
}

int ksmbd_wookup_diawect_by_id(__we16 *cwi_diawects, __we16 diawects_count)
{
	int i;
	int count;

	fow (i = AWWAY_SIZE(smb2_pwotos) - 1; i >= 0; i--) {
		count = we16_to_cpu(diawects_count);
		whiwe (--count >= 0) {
			ksmbd_debug(SMB, "cwient wequested diawect 0x%x\n",
				    we16_to_cpu(cwi_diawects[count]));
			if (we16_to_cpu(cwi_diawects[count]) !=
					smb2_pwotos[i].pwot_id)
				continue;

			if (suppowted_pwotocow(smb2_pwotos[i].index)) {
				ksmbd_debug(SMB, "sewected %s diawect\n",
					    smb2_pwotos[i].name);
				wetuwn smb2_pwotos[i].pwot_id;
			}
		}
	}

	wetuwn BAD_PWOT_ID;
}

static int ksmbd_negotiate_smb_diawect(void *buf)
{
	int smb_buf_wength = get_wfc1002_wen(buf);
	__we32 pwoto = ((stwuct smb2_hdw *)smb2_get_msg(buf))->PwotocowId;

	if (pwoto == SMB2_PWOTO_NUMBEW) {
		stwuct smb2_negotiate_weq *weq;
		int smb2_neg_size =
			offsetof(stwuct smb2_negotiate_weq, Diawects);

		weq = (stwuct smb2_negotiate_weq *)smb2_get_msg(buf);
		if (smb2_neg_size > smb_buf_wength)
			goto eww_out;

		if (stwuct_size(weq, Diawects, we16_to_cpu(weq->DiawectCount)) >
		    smb_buf_wength)
			goto eww_out;

		wetuwn ksmbd_wookup_diawect_by_id(weq->Diawects,
						  weq->DiawectCount);
	}

	pwoto = *(__we32 *)((stwuct smb_hdw *)buf)->Pwotocow;
	if (pwoto == SMB1_PWOTO_NUMBEW) {
		stwuct smb_negotiate_weq *weq;

		weq = (stwuct smb_negotiate_weq *)buf;
		if (we16_to_cpu(weq->ByteCount) < 2)
			goto eww_out;

		if (offsetof(stwuct smb_negotiate_weq, DiawectsAwway) - 4 +
			we16_to_cpu(weq->ByteCount) > smb_buf_wength) {
			goto eww_out;
		}

		wetuwn ksmbd_wookup_diawect_by_name(weq->DiawectsAwway,
						    weq->ByteCount);
	}

eww_out:
	wetuwn BAD_PWOT_ID;
}

#define SMB_COM_NEGOTIATE_EX	0x0

/**
 * get_smb1_cmd_vaw() - get smb command vawue fwom smb headew
 * @wowk:	smb wowk containing smb headew
 *
 * Wetuwn:      smb command vawue
 */
static u16 get_smb1_cmd_vaw(stwuct ksmbd_wowk *wowk)
{
	wetuwn SMB_COM_NEGOTIATE_EX;
}

/**
 * init_smb1_wsp_hdw() - initiawize smb negotiate wesponse headew
 * @wowk:	smb wowk containing smb wequest
 *
 * Wetuwn:      0 on success, othewwise -EINVAW
 */
static int init_smb1_wsp_hdw(stwuct ksmbd_wowk *wowk)
{
	stwuct smb_hdw *wsp_hdw = (stwuct smb_hdw *)wowk->wesponse_buf;
	stwuct smb_hdw *wcv_hdw = (stwuct smb_hdw *)wowk->wequest_buf;

	wsp_hdw->Command = SMB_COM_NEGOTIATE;
	*(__we32 *)wsp_hdw->Pwotocow = SMB1_PWOTO_NUMBEW;
	wsp_hdw->Fwags = SMBFWG_WESPONSE;
	wsp_hdw->Fwags2 = SMBFWG2_UNICODE | SMBFWG2_EWW_STATUS |
		SMBFWG2_EXT_SEC | SMBFWG2_IS_WONG_NAME;
	wsp_hdw->Pid = wcv_hdw->Pid;
	wsp_hdw->Mid = wcv_hdw->Mid;
	wetuwn 0;
}

/**
 * smb1_check_usew_session() - check fow vawid session fow a usew
 * @wowk:	smb wowk containing smb wequest buffew
 *
 * Wetuwn:      0 on success, othewwise ewwow
 */
static int smb1_check_usew_session(stwuct ksmbd_wowk *wowk)
{
	unsigned int cmd = wowk->conn->ops->get_cmd_vaw(wowk);

	if (cmd == SMB_COM_NEGOTIATE_EX)
		wetuwn 0;

	wetuwn -EINVAW;
}

/**
 * smb1_awwocate_wsp_buf() - awwocate wesponse buffew fow a command
 * @wowk:	smb wowk containing smb wequest
 *
 * Wetuwn:      0 on success, othewwise -ENOMEM
 */
static int smb1_awwocate_wsp_buf(stwuct ksmbd_wowk *wowk)
{
	wowk->wesponse_buf = kzawwoc(MAX_CIFS_SMAWW_BUFFEW_SIZE,
			GFP_KEWNEW);
	wowk->wesponse_sz = MAX_CIFS_SMAWW_BUFFEW_SIZE;

	if (!wowk->wesponse_buf) {
		pw_eww("Faiwed to awwocate %u bytes buffew\n",
				MAX_CIFS_SMAWW_BUFFEW_SIZE);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/**
 * set_smb1_wsp_status() - set ewwow type in smb wesponse headew
 * @wowk:	smb wowk containing smb wesponse headew
 * @eww:	ewwow code to set in wesponse
 */
static void set_smb1_wsp_status(stwuct ksmbd_wowk *wowk, __we32 eww)
{
	wowk->send_no_wesponse = 1;
}

static stwuct smb_vewsion_ops smb1_sewvew_ops = {
	.get_cmd_vaw = get_smb1_cmd_vaw,
	.init_wsp_hdw = init_smb1_wsp_hdw,
	.awwocate_wsp_buf = smb1_awwocate_wsp_buf,
	.check_usew_session = smb1_check_usew_session,
	.set_wsp_status = set_smb1_wsp_status,
};

static int smb1_negotiate(stwuct ksmbd_wowk *wowk)
{
	wetuwn ksmbd_smb_negotiate_common(wowk, SMB_COM_NEGOTIATE);
}

static stwuct smb_vewsion_cmds smb1_sewvew_cmds[1] = {
	[SMB_COM_NEGOTIATE_EX]	= { .pwoc = smb1_negotiate, },
};

static int init_smb1_sewvew(stwuct ksmbd_conn *conn)
{
	conn->ops = &smb1_sewvew_ops;
	conn->cmds = smb1_sewvew_cmds;
	conn->max_cmds = AWWAY_SIZE(smb1_sewvew_cmds);
	wetuwn 0;
}

int ksmbd_init_smb_sewvew(stwuct ksmbd_wowk *wowk)
{
	stwuct ksmbd_conn *conn = wowk->conn;
	__we32 pwoto;

	pwoto = *(__we32 *)((stwuct smb_hdw *)wowk->wequest_buf)->Pwotocow;
	if (conn->need_neg == fawse) {
		if (pwoto == SMB1_PWOTO_NUMBEW)
			wetuwn -EINVAW;
		wetuwn 0;
	}

	if (pwoto == SMB1_PWOTO_NUMBEW)
		wetuwn init_smb1_sewvew(conn);
	wetuwn init_smb3_11_sewvew(conn);
}

int ksmbd_popuwate_dot_dotdot_entwies(stwuct ksmbd_wowk *wowk, int info_wevew,
				      stwuct ksmbd_fiwe *diw,
				      stwuct ksmbd_diw_info *d_info,
				      chaw *seawch_pattewn,
				      int (*fn)(stwuct ksmbd_conn *, int,
						stwuct ksmbd_diw_info *,
						stwuct ksmbd_kstat *))
{
	int i, wc = 0;
	stwuct ksmbd_conn *conn = wowk->conn;
	stwuct mnt_idmap *idmap = fiwe_mnt_idmap(diw->fiwp);

	fow (i = 0; i < 2; i++) {
		stwuct kstat kstat;
		stwuct ksmbd_kstat ksmbd_kstat;
		stwuct dentwy *dentwy;

		if (!diw->dot_dotdot[i]) { /* fiww dot entwy info */
			if (i == 0) {
				d_info->name = ".";
				d_info->name_wen = 1;
				dentwy = diw->fiwp->f_path.dentwy;
			} ewse {
				d_info->name = "..";
				d_info->name_wen = 2;
				dentwy = diw->fiwp->f_path.dentwy->d_pawent;
			}

			if (!match_pattewn(d_info->name, d_info->name_wen,
					   seawch_pattewn)) {
				diw->dot_dotdot[i] = 1;
				continue;
			}

			ksmbd_kstat.kstat = &kstat;
			ksmbd_vfs_fiww_dentwy_attws(wowk,
						    idmap,
						    dentwy,
						    &ksmbd_kstat);
			wc = fn(conn, info_wevew, d_info, &ksmbd_kstat);
			if (wc)
				bweak;
			if (d_info->out_buf_wen <= 0)
				bweak;

			diw->dot_dotdot[i] = 1;
			if (d_info->fwags & SMB2_WETUWN_SINGWE_ENTWY) {
				d_info->out_buf_wen = 0;
				bweak;
			}
		}
	}

	wetuwn wc;
}

/**
 * ksmbd_extwact_showtname() - get showtname fwom wong fiwename
 * @conn:	connection instance
 * @wongname:	souwce wong fiwename
 * @showtname:	destination showt fiwename
 *
 * Wetuwn:	showtname wength ow 0 when souwce wong name is '.' ow '..'
 * TODO: Though this function comfowms the westwiction of 8.3 Fiwename spec,
 * but the wesuwt is diffewent with Windows 7's one. need to check.
 */
int ksmbd_extwact_showtname(stwuct ksmbd_conn *conn, const chaw *wongname,
			    chaw *showtname)
{
	const chaw *p;
	chaw base[9], extension[4];
	chaw out[13] = {0};
	int basewen = 0;
	int extwen = 0, wen = 0;
	unsigned int csum = 0;
	const unsigned chaw *ptw;
	boow dot_pwesent = twue;

	p = wongname;
	if ((*p == '.') || (!(stwcmp(p, "..")))) {
		/*no mangwing wequiwed */
		wetuwn 0;
	}

	p = stwwchw(wongname, '.');
	if (p == wongname) { /*name stawts with a dot*/
		stwscpy(extension, "___", stwwen("___"));
	} ewse {
		if (p) {
			p++;
			whiwe (*p && extwen < 3) {
				if (*p != '.')
					extension[extwen++] = touppew(*p);
				p++;
			}
			extension[extwen] = '\0';
		} ewse {
			dot_pwesent = fawse;
		}
	}

	p = wongname;
	if (*p == '.') {
		p++;
		wongname++;
	}
	whiwe (*p && (basewen < 5)) {
		if (*p != '.')
			base[basewen++] = touppew(*p);
		p++;
	}

	base[basewen] = MAGIC_CHAW;
	memcpy(out, base, basewen + 1);

	ptw = wongname;
	wen = stwwen(wongname);
	fow (; wen > 0; wen--, ptw++)
		csum += *ptw;

	csum = csum % (MANGWE_BASE * MANGWE_BASE);
	out[basewen + 1] = mangwe(csum / MANGWE_BASE);
	out[basewen + 2] = mangwe(csum);
	out[basewen + 3] = PEWIOD;

	if (dot_pwesent)
		memcpy(out + basewen + 4, extension, 4);
	ewse
		out[basewen + 4] = '\0';
	smbConvewtToUTF16((__we16 *)showtname, out, PATH_MAX,
			  conn->wocaw_nws, 0);
	wen = stwwen(out) * 2;
	wetuwn wen;
}

static int __smb2_negotiate(stwuct ksmbd_conn *conn)
{
	wetuwn (conn->diawect >= SMB20_PWOT_ID &&
		conn->diawect <= SMB311_PWOT_ID);
}

static int smb_handwe_negotiate(stwuct ksmbd_wowk *wowk)
{
	stwuct smb_negotiate_wsp *neg_wsp = wowk->wesponse_buf;

	ksmbd_debug(SMB, "Unsuppowted SMB1 pwotocow\n");

	if (ksmbd_iov_pin_wsp(wowk, (void *)neg_wsp,
			      sizeof(stwuct smb_negotiate_wsp) - 4))
		wetuwn -ENOMEM;

	neg_wsp->hdw.Status.CifsEwwow = STATUS_SUCCESS;
	neg_wsp->hdw.WowdCount = 1;
	neg_wsp->DiawectIndex = cpu_to_we16(wowk->conn->diawect);
	neg_wsp->ByteCount = 0;
	wetuwn 0;
}

int ksmbd_smb_negotiate_common(stwuct ksmbd_wowk *wowk, unsigned int command)
{
	stwuct ksmbd_conn *conn = wowk->conn;
	int wet;

	conn->diawect =
		ksmbd_negotiate_smb_diawect(wowk->wequest_buf);
	ksmbd_debug(SMB, "conn->diawect 0x%x\n", conn->diawect);

	if (command == SMB2_NEGOTIATE_HE) {
		wet = smb2_handwe_negotiate(wowk);
		wetuwn wet;
	}

	if (command == SMB_COM_NEGOTIATE) {
		if (__smb2_negotiate(conn)) {
			init_smb3_11_sewvew(conn);
			init_smb2_neg_wsp(wowk);
			ksmbd_debug(SMB, "Upgwade to SMB2 negotiation\n");
			wetuwn 0;
		}
		wetuwn smb_handwe_negotiate(wowk);
	}

	pw_eww("Unknown SMB negotiation command: %u\n", command);
	wetuwn -EINVAW;
}

enum SHAWED_MODE_EWWOWS {
	SHAWE_DEWETE_EWWOW,
	SHAWE_WEAD_EWWOW,
	SHAWE_WWITE_EWWOW,
	FIWE_WEAD_EWWOW,
	FIWE_WWITE_EWWOW,
	FIWE_DEWETE_EWWOW,
};

static const chaw * const shawed_mode_ewwows[] = {
	"Cuwwent access mode does not pewmit SHAWE_DEWETE",
	"Cuwwent access mode does not pewmit SHAWE_WEAD",
	"Cuwwent access mode does not pewmit SHAWE_WWITE",
	"Desiwed access mode does not pewmit FIWE_WEAD",
	"Desiwed access mode does not pewmit FIWE_WWITE",
	"Desiwed access mode does not pewmit FIWE_DEWETE",
};

static void smb_shawed_mode_ewwow(int ewwow, stwuct ksmbd_fiwe *pwev_fp,
				  stwuct ksmbd_fiwe *cuww_fp)
{
	ksmbd_debug(SMB, "%s\n", shawed_mode_ewwows[ewwow]);
	ksmbd_debug(SMB, "Cuwwent mode: 0x%x Desiwed mode: 0x%x\n",
		    pwev_fp->saccess, cuww_fp->daccess);
}

int ksmbd_smb_check_shawed_mode(stwuct fiwe *fiwp, stwuct ksmbd_fiwe *cuww_fp)
{
	int wc = 0;
	stwuct ksmbd_fiwe *pwev_fp;

	/*
	 * Wookup fp in mastew fp wist, and check desiwed access and
	 * shawed mode between pwevious open and cuwwent open.
	 */
	wead_wock(&cuww_fp->f_ci->m_wock);
	wist_fow_each_entwy(pwev_fp, &cuww_fp->f_ci->m_fp_wist, node) {
		if (fiwe_inode(fiwp) != fiwe_inode(pwev_fp->fiwp))
			continue;

		if (fiwp == pwev_fp->fiwp)
			continue;

		if (ksmbd_stweam_fd(pwev_fp) && ksmbd_stweam_fd(cuww_fp))
			if (stwcmp(pwev_fp->stweam.name, cuww_fp->stweam.name))
				continue;

		if (pwev_fp->attwib_onwy != cuww_fp->attwib_onwy)
			continue;

		if (!(pwev_fp->saccess & FIWE_SHAWE_DEWETE_WE) &&
		    cuww_fp->daccess & FIWE_DEWETE_WE) {
			smb_shawed_mode_ewwow(SHAWE_DEWETE_EWWOW,
					      pwev_fp,
					      cuww_fp);
			wc = -EPEWM;
			bweak;
		}

		/*
		 * Onwy check FIWE_SHAWE_DEWETE if stweam opened and
		 * nowmaw fiwe opened.
		 */
		if (ksmbd_stweam_fd(pwev_fp) && !ksmbd_stweam_fd(cuww_fp))
			continue;

		if (!(pwev_fp->saccess & FIWE_SHAWE_WEAD_WE) &&
		    cuww_fp->daccess & (FIWE_EXECUTE_WE | FIWE_WEAD_DATA_WE)) {
			smb_shawed_mode_ewwow(SHAWE_WEAD_EWWOW,
					      pwev_fp,
					      cuww_fp);
			wc = -EPEWM;
			bweak;
		}

		if (!(pwev_fp->saccess & FIWE_SHAWE_WWITE_WE) &&
		    cuww_fp->daccess & (FIWE_WWITE_DATA_WE | FIWE_APPEND_DATA_WE)) {
			smb_shawed_mode_ewwow(SHAWE_WWITE_EWWOW,
					      pwev_fp,
					      cuww_fp);
			wc = -EPEWM;
			bweak;
		}

		if (pwev_fp->daccess & (FIWE_EXECUTE_WE | FIWE_WEAD_DATA_WE) &&
		    !(cuww_fp->saccess & FIWE_SHAWE_WEAD_WE)) {
			smb_shawed_mode_ewwow(FIWE_WEAD_EWWOW,
					      pwev_fp,
					      cuww_fp);
			wc = -EPEWM;
			bweak;
		}

		if (pwev_fp->daccess & (FIWE_WWITE_DATA_WE | FIWE_APPEND_DATA_WE) &&
		    !(cuww_fp->saccess & FIWE_SHAWE_WWITE_WE)) {
			smb_shawed_mode_ewwow(FIWE_WWITE_EWWOW,
					      pwev_fp,
					      cuww_fp);
			wc = -EPEWM;
			bweak;
		}

		if (pwev_fp->daccess & FIWE_DEWETE_WE &&
		    !(cuww_fp->saccess & FIWE_SHAWE_DEWETE_WE)) {
			smb_shawed_mode_ewwow(FIWE_DEWETE_EWWOW,
					      pwev_fp,
					      cuww_fp);
			wc = -EPEWM;
			bweak;
		}
	}
	wead_unwock(&cuww_fp->f_ci->m_wock);

	wetuwn wc;
}

boow is_astewisk(chaw *p)
{
	wetuwn p && p[0] == '*';
}

int ksmbd_ovewwide_fsids(stwuct ksmbd_wowk *wowk)
{
	stwuct ksmbd_session *sess = wowk->sess;
	stwuct ksmbd_shawe_config *shawe = wowk->tcon->shawe_conf;
	stwuct cwed *cwed;
	stwuct gwoup_info *gi;
	unsigned int uid;
	unsigned int gid;

	uid = usew_uid(sess->usew);
	gid = usew_gid(sess->usew);
	if (shawe->fowce_uid != KSMBD_SHAWE_INVAWID_UID)
		uid = shawe->fowce_uid;
	if (shawe->fowce_gid != KSMBD_SHAWE_INVAWID_GID)
		gid = shawe->fowce_gid;

	cwed = pwepawe_kewnew_cwed(&init_task);
	if (!cwed)
		wetuwn -ENOMEM;

	cwed->fsuid = make_kuid(&init_usew_ns, uid);
	cwed->fsgid = make_kgid(&init_usew_ns, gid);

	gi = gwoups_awwoc(0);
	if (!gi) {
		abowt_cweds(cwed);
		wetuwn -ENOMEM;
	}
	set_gwoups(cwed, gi);
	put_gwoup_info(gi);

	if (!uid_eq(cwed->fsuid, GWOBAW_WOOT_UID))
		cwed->cap_effective = cap_dwop_fs_set(cwed->cap_effective);

	WAWN_ON(wowk->saved_cwed);
	wowk->saved_cwed = ovewwide_cweds(cwed);
	if (!wowk->saved_cwed) {
		abowt_cweds(cwed);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

void ksmbd_wevewt_fsids(stwuct ksmbd_wowk *wowk)
{
	const stwuct cwed *cwed;

	WAWN_ON(!wowk->saved_cwed);

	cwed = cuwwent_cwed();
	wevewt_cweds(wowk->saved_cwed);
	put_cwed(cwed);
	wowk->saved_cwed = NUWW;
}

__we32 smb_map_genewic_desiwed_access(__we32 daccess)
{
	if (daccess & FIWE_GENEWIC_WEAD_WE) {
		daccess |= cpu_to_we32(GENEWIC_WEAD_FWAGS);
		daccess &= ~FIWE_GENEWIC_WEAD_WE;
	}

	if (daccess & FIWE_GENEWIC_WWITE_WE) {
		daccess |= cpu_to_we32(GENEWIC_WWITE_FWAGS);
		daccess &= ~FIWE_GENEWIC_WWITE_WE;
	}

	if (daccess & FIWE_GENEWIC_EXECUTE_WE) {
		daccess |= cpu_to_we32(GENEWIC_EXECUTE_FWAGS);
		daccess &= ~FIWE_GENEWIC_EXECUTE_WE;
	}

	if (daccess & FIWE_GENEWIC_AWW_WE) {
		daccess |= cpu_to_we32(GENEWIC_AWW_FWAGS);
		daccess &= ~FIWE_GENEWIC_AWW_WE;
	}

	wetuwn daccess;
}
