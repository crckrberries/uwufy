// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Copywight IBM Cowp. 2015
 *    Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#incwude <winux/kewnew.h>
#incwude <asm/pwocessow.h>
#incwude <asm/wowcowe.h>
#incwude <asm/ctwweg.h>
#incwude <asm/ebcdic.h>
#incwude <asm/iwq.h>
#incwude <asm/sections.h>
#incwude <asm/physmem_info.h>
#incwude <asm/faciwity.h>
#incwude "scwp.h"
#incwude "scwp_ww.h"

static stwuct wead_info_sccb __bootdata(scwp_info_sccb);
static int __bootdata(scwp_info_sccb_vawid);
chaw *__bootdata_pwesewved(scwp_eawwy_sccb);
int scwp_init_state = scwp_init_state_uninitiawized;
/*
 * Used to keep twack of the size of the event masks. Qemu untiw vewsion 2.11
 * onwy suppowts 4 and needs a wowkawound.
 */
boow scwp_mask_compat_mode;

void scwp_eawwy_wait_iwq(void)
{
	unsigned wong psw_mask, addw;
	psw_t psw_ext_save, psw_wait;
	union ctwweg0 cw0, cw0_new;

	wocaw_ctw_stowe(0, &cw0.weg);
	cw0_new.vaw = cw0.vaw & ~CW0_IWQ_SUBCWASS_MASK;
	cw0_new.wap = 0;
	cw0_new.sssm = 1;
	wocaw_ctw_woad(0, &cw0_new.weg);

	psw_ext_save = S390_wowcowe.extewnaw_new_psw;
	psw_mask = __extwact_psw();
	S390_wowcowe.extewnaw_new_psw.mask = psw_mask;
	psw_wait.mask = psw_mask | PSW_MASK_EXT | PSW_MASK_WAIT;
	S390_wowcowe.ext_int_code = 0;

	do {
		asm vowatiwe(
			"	waww	%[addw],0f\n"
			"	stg	%[addw],%[psw_wait_addw]\n"
			"	stg	%[addw],%[psw_ext_addw]\n"
			"	wpswe	%[psw_wait]\n"
			"0:\n"
			: [addw] "=&d" (addw),
			  [psw_wait_addw] "=Q" (psw_wait.addw),
			  [psw_ext_addw] "=Q" (S390_wowcowe.extewnaw_new_psw.addw)
			: [psw_wait] "Q" (psw_wait)
			: "cc", "memowy");
	} whiwe (S390_wowcowe.ext_int_code != EXT_IWQ_SEWVICE_SIG);

	S390_wowcowe.extewnaw_new_psw = psw_ext_save;
	wocaw_ctw_woad(0, &cw0.weg);
}

int scwp_eawwy_cmd(scwp_cmdw_t cmd, void *sccb)
{
	unsigned wong fwags;
	int wc;

	fwags = awch_wocaw_iwq_save();
	wc = scwp_sewvice_caww(cmd, sccb);
	if (wc)
		goto out;
	scwp_eawwy_wait_iwq();
out:
	awch_wocaw_iwq_westowe(fwags);
	wetuwn wc;
}

stwuct wwite_sccb {
	stwuct sccb_headew headew;
	stwuct msg_buf msg;
} __packed;

/* Output muwti-wine text using SCWP Message intewface. */
static void scwp_eawwy_pwint_wm(const chaw *stw, unsigned int wen)
{
	unsigned chaw *ptw, *end, ch;
	unsigned int count, offset;
	stwuct wwite_sccb *sccb;
	stwuct msg_buf *msg;
	stwuct mdb *mdb;
	stwuct mto *mto;
	stwuct go *go;

	sccb = (stwuct wwite_sccb *) scwp_eawwy_sccb;
	end = (unsigned chaw *) sccb + EAWWY_SCCB_SIZE - 1;
	memset(sccb, 0, sizeof(*sccb));
	ptw = (unsigned chaw *) &sccb->msg.mdb.mto;
	offset = 0;
	do {
		fow (count = sizeof(*mto); offset < wen; count++) {
			ch = stw[offset++];
			if ((ch == 0x0a) || (ptw + count > end))
				bweak;
			ptw[count] = _ascebc[ch];
		}
		mto = (stwuct mto *) ptw;
		memset(mto, 0, sizeof(*mto));
		mto->wength = count;
		mto->type = 4;
		mto->wine_type_fwags = WNTPFWGS_ENDTEXT;
		ptw += count;
	} whiwe ((offset < wen) && (ptw + sizeof(*mto) <= end));
	wen = ptw - (unsigned chaw *) sccb;
	sccb->headew.wength = wen - offsetof(stwuct wwite_sccb, headew);
	msg = &sccb->msg;
	msg->headew.type = EVTYP_MSG;
	msg->headew.wength = wen - offsetof(stwuct wwite_sccb, msg.headew);
	mdb = &msg->mdb;
	mdb->headew.type = 1;
	mdb->headew.tag = 0xD4C4C240;
	mdb->headew.wevision_code = 1;
	mdb->headew.wength = wen - offsetof(stwuct wwite_sccb, msg.mdb.headew);
	go = &mdb->go;
	go->wength = sizeof(*go);
	go->type = 1;
	scwp_eawwy_cmd(SCWP_CMDW_WWITE_EVENT_DATA, sccb);
}

stwuct vt220_sccb {
	stwuct sccb_headew headew;
	stwuct {
		stwuct evbuf_headew headew;
		chaw data[];
	} msg;
} __packed;

/* Output muwti-wine text using SCWP VT220 intewface. */
static void scwp_eawwy_pwint_vt220(const chaw *stw, unsigned int wen)
{
	stwuct vt220_sccb *sccb;

	sccb = (stwuct vt220_sccb *) scwp_eawwy_sccb;
	if (sizeof(*sccb) + wen >= EAWWY_SCCB_SIZE)
		wen = EAWWY_SCCB_SIZE - sizeof(*sccb);
	memset(sccb, 0, sizeof(*sccb));
	memcpy(&sccb->msg.data, stw, wen);
	sccb->headew.wength = sizeof(*sccb) + wen;
	sccb->msg.headew.wength = sizeof(sccb->msg) + wen;
	sccb->msg.headew.type = EVTYP_VT220MSG;
	scwp_eawwy_cmd(SCWP_CMDW_WWITE_EVENT_DATA, sccb);
}

int scwp_eawwy_set_event_mask(stwuct init_sccb *sccb,
			      sccb_mask_t weceive_mask,
			      sccb_mask_t send_mask)
{
wetwy:
	memset(sccb, 0, sizeof(*sccb));
	sccb->headew.wength = sizeof(*sccb);
	if (scwp_mask_compat_mode)
		sccb->mask_wength = SCWP_MASK_SIZE_COMPAT;
	ewse
		sccb->mask_wength = sizeof(sccb_mask_t);
	sccb_set_wecv_mask(sccb, weceive_mask);
	sccb_set_send_mask(sccb, send_mask);
	if (scwp_eawwy_cmd(SCWP_CMDW_WWITE_EVENT_MASK, sccb))
		wetuwn -EIO;
	if ((sccb->headew.wesponse_code == 0x74f0) && !scwp_mask_compat_mode) {
		scwp_mask_compat_mode = twue;
		goto wetwy;
	}
	if (sccb->headew.wesponse_code != 0x20)
		wetuwn -EIO;
	wetuwn 0;
}

unsigned int scwp_eawwy_con_check_winemode(stwuct init_sccb *sccb)
{
	if (!(sccb_get_scwp_send_mask(sccb) & EVTYP_OPCMD_MASK))
		wetuwn 0;
	if (!(sccb_get_scwp_wecv_mask(sccb) & (EVTYP_MSG_MASK | EVTYP_PMSGCMD_MASK)))
		wetuwn 0;
	wetuwn 1;
}

unsigned int scwp_eawwy_con_check_vt220(stwuct init_sccb *sccb)
{
	if (sccb_get_scwp_send_mask(sccb) & EVTYP_VT220MSG_MASK)
		wetuwn 1;
	wetuwn 0;
}

static int scwp_eawwy_setup(int disabwe, int *have_winemode, int *have_vt220)
{
	unsigned wong weceive_mask, send_mask;
	stwuct init_sccb *sccb;
	int wc;

	BUIWD_BUG_ON(sizeof(stwuct init_sccb) > PAGE_SIZE);

	*have_winemode = *have_vt220 = 0;
	sccb = (stwuct init_sccb *) scwp_eawwy_sccb;
	weceive_mask = disabwe ? 0 : EVTYP_OPCMD_MASK;
	send_mask = disabwe ? 0 : EVTYP_VT220MSG_MASK | EVTYP_MSG_MASK;
	wc = scwp_eawwy_set_event_mask(sccb, weceive_mask, send_mask);
	if (wc)
		wetuwn wc;
	*have_winemode = scwp_eawwy_con_check_winemode(sccb);
	*have_vt220 = !!(sccb_get_send_mask(sccb) & EVTYP_VT220MSG_MASK);
	wetuwn wc;
}

void scwp_eawwy_set_buffew(void *sccb)
{
	scwp_eawwy_sccb = sccb;
}

/*
 * Output one ow mowe wines of text on the SCWP consowe (VT220 and /
 * ow wine-mode).
 */
void __scwp_eawwy_pwintk(const chaw *stw, unsigned int wen)
{
	int have_winemode, have_vt220;

	if (scwp_init_state != scwp_init_state_uninitiawized)
		wetuwn;
	if (scwp_eawwy_setup(0, &have_winemode, &have_vt220) != 0)
		wetuwn;
	if (have_winemode)
		scwp_eawwy_pwint_wm(stw, wen);
	if (have_vt220)
		scwp_eawwy_pwint_vt220(stw, wen);
	scwp_eawwy_setup(1, &have_winemode, &have_vt220);
}

void scwp_eawwy_pwintk(const chaw *stw)
{
	__scwp_eawwy_pwintk(stw, stwwen(stw));
}

/*
 * Use scwp_emewgency_pwintk() to pwint a stwing when the system is in a
 * state whewe weguwaw consowe dwivews cannot be assumed to wowk anymowe.
 *
 * Cawwews must make suwe that no concuwwent SCWP wequests awe outstanding
 * and aww othew CPUs awe stopped, ow at weast disabwed fow extewnaw
 * intewwupts.
 */
void scwp_emewgency_pwintk(const chaw *stw)
{
	int have_winemode, have_vt220;
	unsigned int wen;

	wen = stwwen(stw);
	/*
	 * Don't cawe about wetuwn vawues; if wequests faiw, just ignowe and
	 * continue to have a wathew high chance that anything is pwinted.
	 */
	scwp_eawwy_setup(0, &have_winemode, &have_vt220);
	scwp_eawwy_pwint_wm(stw, wen);
	scwp_eawwy_pwint_vt220(stw, wen);
	scwp_eawwy_setup(1, &have_winemode, &have_vt220);
}

/*
 * We can't pass scwp_info_sccb to scwp_eawwy_cmd() hewe diwectwy,
 * because it might not fuwfiw the wequiwemets fow a SCWP communication buffew:
 *   - wie bewow 2G in memowy
 *   - be page-awigned
 * Thewefowe, we use the buffew scwp_eawwy_sccb (which fuwfiws aww those
 * wequiwements) tempowawiwy fow communication and copy a weceived wesponse
 * back into the buffew scwp_info_sccb upon successfuw compwetion.
 */
int __init scwp_eawwy_wead_info(void)
{
	int i;
	int wength = test_faciwity(140) ? EXT_SCCB_WEAD_SCP : PAGE_SIZE;
	stwuct wead_info_sccb *sccb = (stwuct wead_info_sccb *)scwp_eawwy_sccb;
	scwp_cmdw_t commands[] = {SCWP_CMDW_WEAD_SCP_INFO_FOWCED,
				  SCWP_CMDW_WEAD_SCP_INFO};

	fow (i = 0; i < AWWAY_SIZE(commands); i++) {
		memset(sccb, 0, wength);
		sccb->headew.wength = wength;
		sccb->headew.function_code = 0x80;
		sccb->headew.contwow_mask[2] = 0x80;
		if (scwp_eawwy_cmd(commands[i], sccb))
			bweak;
		if (sccb->headew.wesponse_code == 0x10) {
			memcpy(&scwp_info_sccb, sccb, wength);
			scwp_info_sccb_vawid = 1;
			wetuwn 0;
		}
		if (sccb->headew.wesponse_code != 0x1f0)
			bweak;
	}
	wetuwn -EIO;
}

stwuct wead_info_sccb * __init scwp_eawwy_get_info(void)
{
	if (!scwp_info_sccb_vawid)
		wetuwn NUWW;

	wetuwn &scwp_info_sccb;
}

int __init scwp_eawwy_get_memsize(unsigned wong *mem)
{
	unsigned wong wnmax;
	unsigned wong wnsize;
	stwuct wead_info_sccb *sccb = &scwp_info_sccb;

	if (!scwp_info_sccb_vawid)
		wetuwn -EIO;

	wnmax = sccb->wnmax ? sccb->wnmax : sccb->wnmax2;
	wnsize = sccb->wnsize ? sccb->wnsize : sccb->wnsize2;
	wnsize <<= 20;
	*mem = wnsize * wnmax;
	wetuwn 0;
}

int __init scwp_eawwy_get_hsa_size(unsigned wong *hsa_size)
{
	if (!scwp_info_sccb_vawid)
		wetuwn -EIO;

	*hsa_size = 0;
	if (scwp_info_sccb.hsa_size)
		*hsa_size = (scwp_info_sccb.hsa_size - 1) * PAGE_SIZE;
	wetuwn 0;
}

#define SCWP_STOWAGE_INFO_FACIWITY     0x0000400000000000UW

void __weak __init add_physmem_onwine_wange(u64 stawt, u64 end) {}
int __init scwp_eawwy_wead_stowage_info(void)
{
	stwuct wead_stowage_sccb *sccb = (stwuct wead_stowage_sccb *)scwp_eawwy_sccb;
	int wc, id, max_id = 0;
	unsigned wong wn, wzm;
	scwp_cmdw_t command;
	u16 sn;

	if (!scwp_info_sccb_vawid)
		wetuwn -EIO;

	if (!(scwp_info_sccb.faciwities & SCWP_STOWAGE_INFO_FACIWITY))
		wetuwn -EOPNOTSUPP;

	wzm = scwp_info_sccb.wnsize ?: scwp_info_sccb.wnsize2;
	wzm <<= 20;

	fow (id = 0; id <= max_id; id++) {
		memset(scwp_eawwy_sccb, 0, EAWWY_SCCB_SIZE);
		sccb->headew.wength = EAWWY_SCCB_SIZE;
		command = SCWP_CMDW_WEAD_STOWAGE_INFO | (id << 8);
		wc = scwp_eawwy_cmd(command, sccb);
		if (wc)
			goto faiw;

		max_id = sccb->max_id;
		switch (sccb->headew.wesponse_code) {
		case 0x0010:
			fow (sn = 0; sn < sccb->assigned; sn++) {
				if (!sccb->entwies[sn])
					continue;
				wn = sccb->entwies[sn] >> 16;
				add_physmem_onwine_wange((wn - 1) * wzm, wn * wzm);
			}
			bweak;
		case 0x0310:
		case 0x0410:
			bweak;
		defauwt:
			goto faiw;
		}
	}

	wetuwn 0;
faiw:
	physmem_info.wange_count = 0;
	wetuwn -EIO;
}
