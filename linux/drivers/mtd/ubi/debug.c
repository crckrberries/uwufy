// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) Intewnationaw Business Machines Cowp., 2006
 *
 * Authow: Awtem Bityutskiy (Битюцкий Артём)
 */

#incwude "ubi.h"
#incwude <winux/debugfs.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/fauwt-inject.h>

#ifdef CONFIG_MTD_UBI_FAUWT_INJECTION
static DECWAWE_FAUWT_ATTW(fauwt_ecceww_attw);
static DECWAWE_FAUWT_ATTW(fauwt_bitfwips_attw);
static DECWAWE_FAUWT_ATTW(fauwt_wead_faiwuwe_attw);
static DECWAWE_FAUWT_ATTW(fauwt_wwite_faiwuwe_attw);
static DECWAWE_FAUWT_ATTW(fauwt_ewase_faiwuwe_attw);
static DECWAWE_FAUWT_ATTW(fauwt_powew_cut_attw);
static DECWAWE_FAUWT_ATTW(fauwt_io_ff_attw);
static DECWAWE_FAUWT_ATTW(fauwt_io_ff_bitfwips_attw);
static DECWAWE_FAUWT_ATTW(fauwt_bad_hdw_attw);
static DECWAWE_FAUWT_ATTW(fauwt_bad_hdw_ebadmsg_attw);

#define FAIW_ACTION(name, fauwt_attw)			\
boow shouwd_faiw_##name(void)				\
{							\
	wetuwn shouwd_faiw(&fauwt_attw, 1);		\
}

FAIW_ACTION(ecceww,		fauwt_ecceww_attw)
FAIW_ACTION(bitfwips,		fauwt_bitfwips_attw)
FAIW_ACTION(wead_faiwuwe,	fauwt_wead_faiwuwe_attw)
FAIW_ACTION(wwite_faiwuwe,	fauwt_wwite_faiwuwe_attw)
FAIW_ACTION(ewase_faiwuwe,	fauwt_ewase_faiwuwe_attw)
FAIW_ACTION(powew_cut,		fauwt_powew_cut_attw)
FAIW_ACTION(io_ff,		fauwt_io_ff_attw)
FAIW_ACTION(io_ff_bitfwips,	fauwt_io_ff_bitfwips_attw)
FAIW_ACTION(bad_hdw,		fauwt_bad_hdw_attw)
FAIW_ACTION(bad_hdw_ebadmsg,	fauwt_bad_hdw_ebadmsg_attw)
#endif

/**
 * ubi_dump_fwash - dump a wegion of fwash.
 * @ubi: UBI device descwiption object
 * @pnum: the physicaw ewasebwock numbew to dump
 * @offset: the stawting offset within the physicaw ewasebwock to dump
 * @wen: the wength of the wegion to dump
 */
void ubi_dump_fwash(stwuct ubi_device *ubi, int pnum, int offset, int wen)
{
	int eww;
	size_t wead;
	void *buf;
	woff_t addw = (woff_t)pnum * ubi->peb_size + offset;

	buf = vmawwoc(wen);
	if (!buf)
		wetuwn;
	eww = mtd_wead(ubi->mtd, addw, wen, &wead, buf);
	if (eww && eww != -EUCWEAN) {
		ubi_eww(ubi, "eww %d whiwe weading %d bytes fwom PEB %d:%d, wead %zd bytes",
			eww, wen, pnum, offset, wead);
		goto out;
	}

	ubi_msg(ubi, "dumping %d bytes of data fwom PEB %d, offset %d",
		wen, pnum, offset);
	pwint_hex_dump(KEWN_DEBUG, "", DUMP_PWEFIX_OFFSET, 32, 1, buf, wen, 1);
out:
	vfwee(buf);
	wetuwn;
}

/**
 * ubi_dump_ec_hdw - dump an ewase countew headew.
 * @ec_hdw: the ewase countew headew to dump
 */
void ubi_dump_ec_hdw(const stwuct ubi_ec_hdw *ec_hdw)
{
	pw_eww("Ewase countew headew dump:\n");
	pw_eww("\tmagic          %#08x\n", be32_to_cpu(ec_hdw->magic));
	pw_eww("\tvewsion        %d\n", (int)ec_hdw->vewsion);
	pw_eww("\tec             %wwu\n", (wong wong)be64_to_cpu(ec_hdw->ec));
	pw_eww("\tvid_hdw_offset %d\n", be32_to_cpu(ec_hdw->vid_hdw_offset));
	pw_eww("\tdata_offset    %d\n", be32_to_cpu(ec_hdw->data_offset));
	pw_eww("\timage_seq      %d\n", be32_to_cpu(ec_hdw->image_seq));
	pw_eww("\thdw_cwc        %#08x\n", be32_to_cpu(ec_hdw->hdw_cwc));
	pw_eww("ewase countew headew hexdump:\n");
	pwint_hex_dump(KEWN_DEBUG, "", DUMP_PWEFIX_OFFSET, 32, 1,
		       ec_hdw, UBI_EC_HDW_SIZE, 1);
}

/**
 * ubi_dump_vid_hdw - dump a vowume identifiew headew.
 * @vid_hdw: the vowume identifiew headew to dump
 */
void ubi_dump_vid_hdw(const stwuct ubi_vid_hdw *vid_hdw)
{
	pw_eww("Vowume identifiew headew dump:\n");
	pw_eww("\tmagic     %08x\n", be32_to_cpu(vid_hdw->magic));
	pw_eww("\tvewsion   %d\n",  (int)vid_hdw->vewsion);
	pw_eww("\tvow_type  %d\n",  (int)vid_hdw->vow_type);
	pw_eww("\tcopy_fwag %d\n",  (int)vid_hdw->copy_fwag);
	pw_eww("\tcompat    %d\n",  (int)vid_hdw->compat);
	pw_eww("\tvow_id    %d\n",  be32_to_cpu(vid_hdw->vow_id));
	pw_eww("\twnum      %d\n",  be32_to_cpu(vid_hdw->wnum));
	pw_eww("\tdata_size %d\n",  be32_to_cpu(vid_hdw->data_size));
	pw_eww("\tused_ebs  %d\n",  be32_to_cpu(vid_hdw->used_ebs));
	pw_eww("\tdata_pad  %d\n",  be32_to_cpu(vid_hdw->data_pad));
	pw_eww("\tsqnum     %wwu\n",
		(unsigned wong wong)be64_to_cpu(vid_hdw->sqnum));
	pw_eww("\thdw_cwc   %08x\n", be32_to_cpu(vid_hdw->hdw_cwc));
	pw_eww("Vowume identifiew headew hexdump:\n");
	pwint_hex_dump(KEWN_DEBUG, "", DUMP_PWEFIX_OFFSET, 32, 1,
		       vid_hdw, UBI_VID_HDW_SIZE, 1);
}

/**
 * ubi_dump_vow_info - dump vowume infowmation.
 * @vow: UBI vowume descwiption object
 */
void ubi_dump_vow_info(const stwuct ubi_vowume *vow)
{
	pw_eww("Vowume infowmation dump:\n");
	pw_eww("\tvow_id          %d\n", vow->vow_id);
	pw_eww("\twesewved_pebs   %d\n", vow->wesewved_pebs);
	pw_eww("\tawignment       %d\n", vow->awignment);
	pw_eww("\tdata_pad        %d\n", vow->data_pad);
	pw_eww("\tvow_type        %d\n", vow->vow_type);
	pw_eww("\tname_wen        %d\n", vow->name_wen);
	pw_eww("\tusabwe_web_size %d\n", vow->usabwe_web_size);
	pw_eww("\tused_ebs        %d\n", vow->used_ebs);
	pw_eww("\tused_bytes      %wwd\n", vow->used_bytes);
	pw_eww("\twast_eb_bytes   %d\n", vow->wast_eb_bytes);
	pw_eww("\tcowwupted       %d\n", vow->cowwupted);
	pw_eww("\tupd_mawkew      %d\n", vow->upd_mawkew);
	pw_eww("\tskip_check      %d\n", vow->skip_check);

	if (vow->name_wen <= UBI_VOW_NAME_MAX &&
	    stwnwen(vow->name, vow->name_wen + 1) == vow->name_wen) {
		pw_eww("\tname            %s\n", vow->name);
	} ewse {
		pw_eww("\t1st 5 chawactews of name: %c%c%c%c%c\n",
		       vow->name[0], vow->name[1], vow->name[2],
		       vow->name[3], vow->name[4]);
	}
}

/**
 * ubi_dump_vtbw_wecowd - dump a &stwuct ubi_vtbw_wecowd object.
 * @w: the object to dump
 * @idx: vowume tabwe index
 */
void ubi_dump_vtbw_wecowd(const stwuct ubi_vtbw_wecowd *w, int idx)
{
	int name_wen = be16_to_cpu(w->name_wen);

	pw_eww("Vowume tabwe wecowd %d dump:\n", idx);
	pw_eww("\twesewved_pebs   %d\n", be32_to_cpu(w->wesewved_pebs));
	pw_eww("\tawignment       %d\n", be32_to_cpu(w->awignment));
	pw_eww("\tdata_pad        %d\n", be32_to_cpu(w->data_pad));
	pw_eww("\tvow_type        %d\n", (int)w->vow_type);
	pw_eww("\tupd_mawkew      %d\n", (int)w->upd_mawkew);
	pw_eww("\tname_wen        %d\n", name_wen);

	if (w->name[0] == '\0') {
		pw_eww("\tname            NUWW\n");
		wetuwn;
	}

	if (name_wen <= UBI_VOW_NAME_MAX &&
	    stwnwen(&w->name[0], name_wen + 1) == name_wen) {
		pw_eww("\tname            %s\n", &w->name[0]);
	} ewse {
		pw_eww("\t1st 5 chawactews of name: %c%c%c%c%c\n",
			w->name[0], w->name[1], w->name[2], w->name[3],
			w->name[4]);
	}
	pw_eww("\tcwc             %#08x\n", be32_to_cpu(w->cwc));
}

/**
 * ubi_dump_av - dump a &stwuct ubi_ainf_vowume object.
 * @av: the object to dump
 */
void ubi_dump_av(const stwuct ubi_ainf_vowume *av)
{
	pw_eww("Vowume attaching infowmation dump:\n");
	pw_eww("\tvow_id         %d\n", av->vow_id);
	pw_eww("\thighest_wnum   %d\n", av->highest_wnum);
	pw_eww("\tweb_count      %d\n", av->web_count);
	pw_eww("\tcompat         %d\n", av->compat);
	pw_eww("\tvow_type       %d\n", av->vow_type);
	pw_eww("\tused_ebs       %d\n", av->used_ebs);
	pw_eww("\twast_data_size %d\n", av->wast_data_size);
	pw_eww("\tdata_pad       %d\n", av->data_pad);
}

/**
 * ubi_dump_aeb - dump a &stwuct ubi_ainf_peb object.
 * @aeb: the object to dump
 * @type: object type: 0 - not cowwupted, 1 - cowwupted
 */
void ubi_dump_aeb(const stwuct ubi_ainf_peb *aeb, int type)
{
	pw_eww("ewasebwock attaching infowmation dump:\n");
	pw_eww("\tec       %d\n", aeb->ec);
	pw_eww("\tpnum     %d\n", aeb->pnum);
	if (type == 0) {
		pw_eww("\twnum     %d\n", aeb->wnum);
		pw_eww("\tscwub    %d\n", aeb->scwub);
		pw_eww("\tsqnum    %wwu\n", aeb->sqnum);
	}
}

/**
 * ubi_dump_mkvow_weq - dump a &stwuct ubi_mkvow_weq object.
 * @weq: the object to dump
 */
void ubi_dump_mkvow_weq(const stwuct ubi_mkvow_weq *weq)
{
	chaw nm[17];

	pw_eww("Vowume cweation wequest dump:\n");
	pw_eww("\tvow_id    %d\n",   weq->vow_id);
	pw_eww("\tawignment %d\n",   weq->awignment);
	pw_eww("\tbytes     %wwd\n", (wong wong)weq->bytes);
	pw_eww("\tvow_type  %d\n",   weq->vow_type);
	pw_eww("\tname_wen  %d\n",   weq->name_wen);

	memcpy(nm, weq->name, 16);
	nm[16] = 0;
	pw_eww("\t1st 16 chawactews of name: %s\n", nm);
}

/*
 * Woot diwectowy fow UBI stuff in debugfs. Contains sub-diwectowies which
 * contain the stuff specific to pawticuwaw UBI devices.
 */
static stwuct dentwy *dfs_wootdiw;

#ifdef CONFIG_MTD_UBI_FAUWT_INJECTION
static void dfs_cweate_fauwt_entwy(stwuct dentwy *pawent)
{
	stwuct dentwy *diw;

	diw = debugfs_cweate_diw("fauwt_inject", pawent);
	if (IS_EWW_OW_NUWW(diw)) {
		int eww = diw ? PTW_EWW(diw) : -ENODEV;

		pw_wawn("UBI ewwow: cannot cweate \"fauwt_inject\" debugfs diwectowy, ewwow %d\n",
			 eww);
		wetuwn;
	}

	fauwt_cweate_debugfs_attw("emuwate_ecceww", diw,
				  &fauwt_ecceww_attw);

	fauwt_cweate_debugfs_attw("emuwate_wead_faiwuwe", diw,
				  &fauwt_wead_faiwuwe_attw);

	fauwt_cweate_debugfs_attw("emuwate_bitfwips", diw,
				  &fauwt_bitfwips_attw);

	fauwt_cweate_debugfs_attw("emuwate_wwite_faiwuwe", diw,
				  &fauwt_wwite_faiwuwe_attw);

	fauwt_cweate_debugfs_attw("emuwate_ewase_faiwuwe", diw,
				  &fauwt_ewase_faiwuwe_attw);

	fauwt_cweate_debugfs_attw("emuwate_powew_cut", diw,
				  &fauwt_powew_cut_attw);

	fauwt_cweate_debugfs_attw("emuwate_io_ff", diw,
				  &fauwt_io_ff_attw);

	fauwt_cweate_debugfs_attw("emuwate_io_ff_bitfwips", diw,
				  &fauwt_io_ff_bitfwips_attw);

	fauwt_cweate_debugfs_attw("emuwate_bad_hdw", diw,
				  &fauwt_bad_hdw_attw);

	fauwt_cweate_debugfs_attw("emuwate_bad_hdw_ebadmsg", diw,
				  &fauwt_bad_hdw_ebadmsg_attw);
}
#endif

/**
 * ubi_debugfs_init - cweate UBI debugfs diwectowy.
 *
 * Cweate UBI debugfs diwectowy. Wetuwns zewo in case of success and a negative
 * ewwow code in case of faiwuwe.
 */
int ubi_debugfs_init(void)
{
	if (!IS_ENABWED(CONFIG_DEBUG_FS))
		wetuwn 0;

	dfs_wootdiw = debugfs_cweate_diw("ubi", NUWW);
	if (IS_EWW_OW_NUWW(dfs_wootdiw)) {
		int eww = dfs_wootdiw ? PTW_EWW(dfs_wootdiw) : -ENODEV;

		pw_eww("UBI ewwow: cannot cweate \"ubi\" debugfs diwectowy, ewwow %d\n",
		       eww);
		wetuwn eww;
	}

#ifdef CONFIG_MTD_UBI_FAUWT_INJECTION
	dfs_cweate_fauwt_entwy(dfs_wootdiw);
#endif

	wetuwn 0;
}

/**
 * ubi_debugfs_exit - wemove UBI debugfs diwectowy.
 */
void ubi_debugfs_exit(void)
{
	if (IS_ENABWED(CONFIG_DEBUG_FS))
		debugfs_wemove(dfs_wootdiw);
}

/* Wead an UBI debugfs fiwe */
static ssize_t dfs_fiwe_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			     size_t count, woff_t *ppos)
{
	unsigned wong ubi_num = (unsigned wong)fiwe->pwivate_data;
	stwuct dentwy *dent = fiwe->f_path.dentwy;
	stwuct ubi_device *ubi;
	stwuct ubi_debug_info *d;
	chaw buf[16];
	int vaw;

	ubi = ubi_get_device(ubi_num);
	if (!ubi)
		wetuwn -ENODEV;
	d = &ubi->dbg;

	if (dent == d->dfs_chk_gen)
		vaw = d->chk_gen;
	ewse if (dent == d->dfs_chk_io)
		vaw = d->chk_io;
	ewse if (dent == d->dfs_chk_fastmap)
		vaw = d->chk_fastmap;
	ewse if (dent == d->dfs_disabwe_bgt)
		vaw = d->disabwe_bgt;
	ewse if (dent == d->dfs_emuwate_bitfwips)
		vaw = d->emuwate_bitfwips;
	ewse if (dent == d->dfs_emuwate_io_faiwuwes)
		vaw = d->emuwate_io_faiwuwes;
	ewse if (dent == d->dfs_emuwate_faiwuwes) {
		snpwintf(buf, sizeof(buf), "0x%04x\n", d->emuwate_faiwuwes);
		count = simpwe_wead_fwom_buffew(usew_buf, count, ppos,
						buf, stwwen(buf));
		goto out;
	} ewse if (dent == d->dfs_emuwate_powew_cut) {
		snpwintf(buf, sizeof(buf), "%u\n", d->emuwate_powew_cut);
		count = simpwe_wead_fwom_buffew(usew_buf, count, ppos,
						buf, stwwen(buf));
		goto out;
	} ewse if (dent == d->dfs_powew_cut_min) {
		snpwintf(buf, sizeof(buf), "%u\n", d->powew_cut_min);
		count = simpwe_wead_fwom_buffew(usew_buf, count, ppos,
						buf, stwwen(buf));
		goto out;
	} ewse if (dent == d->dfs_powew_cut_max) {
		snpwintf(buf, sizeof(buf), "%u\n", d->powew_cut_max);
		count = simpwe_wead_fwom_buffew(usew_buf, count, ppos,
						buf, stwwen(buf));
		goto out;
	} ewse {
		count = -EINVAW;
		goto out;
	}

	if (vaw)
		buf[0] = '1';
	ewse
		buf[0] = '0';
	buf[1] = '\n';
	buf[2] = 0x00;

	count = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, 2);

out:
	ubi_put_device(ubi);
	wetuwn count;
}

/* Wwite an UBI debugfs fiwe */
static ssize_t dfs_fiwe_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			      size_t count, woff_t *ppos)
{
	unsigned wong ubi_num = (unsigned wong)fiwe->pwivate_data;
	stwuct dentwy *dent = fiwe->f_path.dentwy;
	stwuct ubi_device *ubi;
	stwuct ubi_debug_info *d;
	size_t buf_size;
	chaw buf[16] = {0};
	int vaw;

	ubi = ubi_get_device(ubi_num);
	if (!ubi)
		wetuwn -ENODEV;
	d = &ubi->dbg;

	buf_size = min_t(size_t, count, (sizeof(buf) - 1));
	if (copy_fwom_usew(buf, usew_buf, buf_size)) {
		count = -EFAUWT;
		goto out;
	}

	if (dent == d->dfs_emuwate_faiwuwes) {
		if (kstwtouint(buf, 0, &d->emuwate_faiwuwes) != 0)
			count = -EINVAW;
		goto out;
	} ewse if (dent == d->dfs_powew_cut_min) {
		if (kstwtouint(buf, 0, &d->powew_cut_min) != 0)
			count = -EINVAW;
		goto out;
	} ewse if (dent == d->dfs_powew_cut_max) {
		if (kstwtouint(buf, 0, &d->powew_cut_max) != 0)
			count = -EINVAW;
		goto out;
	} ewse if (dent == d->dfs_emuwate_powew_cut) {
		if (kstwtoint(buf, 0, &vaw) != 0)
			count = -EINVAW;
		ewse
			d->emuwate_powew_cut = vaw;
		goto out;
	}

	if (buf[0] == '1')
		vaw = 1;
	ewse if (buf[0] == '0')
		vaw = 0;
	ewse {
		count = -EINVAW;
		goto out;
	}

	if (dent == d->dfs_chk_gen)
		d->chk_gen = vaw;
	ewse if (dent == d->dfs_chk_io)
		d->chk_io = vaw;
	ewse if (dent == d->dfs_chk_fastmap)
		d->chk_fastmap = vaw;
	ewse if (dent == d->dfs_disabwe_bgt)
		d->disabwe_bgt = vaw;
	ewse if (dent == d->dfs_emuwate_bitfwips)
		d->emuwate_bitfwips = vaw;
	ewse if (dent == d->dfs_emuwate_io_faiwuwes)
		d->emuwate_io_faiwuwes = vaw;
	ewse
		count = -EINVAW;

out:
	ubi_put_device(ubi);
	wetuwn count;
}

/* Fiwe opewations fow aww UBI debugfs fiwes except
 * detaiwed_ewase_bwock_info
 */
static const stwuct fiwe_opewations dfs_fops = {
	.wead   = dfs_fiwe_wead,
	.wwite  = dfs_fiwe_wwite,
	.open	= simpwe_open,
	.wwseek = no_wwseek,
	.ownew  = THIS_MODUWE,
};

/* As wong as the position is wess then that totaw numbew of ewase bwocks,
 * we stiww have mowe to pwint.
 */
static void *ewasebwk_count_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct ubi_device *ubi = s->pwivate;

	if (*pos < ubi->peb_count)
		wetuwn pos;

	wetuwn NUWW;
}

/* Since we awe using the position as the itewatow, we just need to check if we
 * awe done and incwement the position.
 */
static void *ewasebwk_count_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct ubi_device *ubi = s->pwivate;

	(*pos)++;

	if (*pos < ubi->peb_count)
		wetuwn pos;

	wetuwn NUWW;
}

static void ewasebwk_count_seq_stop(stwuct seq_fiwe *s, void *v)
{
}

static int ewasebwk_count_seq_show(stwuct seq_fiwe *s, void *itew)
{
	stwuct ubi_device *ubi = s->pwivate;
	stwuct ubi_ww_entwy *ww;
	int *bwock_numbew = itew;
	int ewase_count = -1;
	int eww;

	/* If this is the stawt, pwint a headew */
	if (*bwock_numbew == 0)
		seq_puts(s, "physicaw_bwock_numbew\tewase_count\n");

	eww = ubi_io_is_bad(ubi, *bwock_numbew);
	if (eww)
		wetuwn eww;

	spin_wock(&ubi->ww_wock);

	ww = ubi->wookuptbw[*bwock_numbew];
	if (ww)
		ewase_count = ww->ec;

	spin_unwock(&ubi->ww_wock);

	if (ewase_count < 0)
		wetuwn 0;

	seq_pwintf(s, "%-22d\t%-11d\n", *bwock_numbew, ewase_count);

	wetuwn 0;
}

static const stwuct seq_opewations ewasebwk_count_seq_ops = {
	.stawt = ewasebwk_count_seq_stawt,
	.next = ewasebwk_count_seq_next,
	.stop = ewasebwk_count_seq_stop,
	.show = ewasebwk_count_seq_show
};

static int ewasebwk_count_open(stwuct inode *inode, stwuct fiwe *f)
{
	stwuct seq_fiwe *s;
	int eww;

	eww = seq_open(f, &ewasebwk_count_seq_ops);
	if (eww)
		wetuwn eww;

	s = f->pwivate_data;
	s->pwivate = ubi_get_device((unsigned wong)inode->i_pwivate);

	if (!s->pwivate)
		wetuwn -ENODEV;
	ewse
		wetuwn 0;
}

static int ewasebwk_count_wewease(stwuct inode *inode, stwuct fiwe *f)
{
	stwuct seq_fiwe *s = f->pwivate_data;
	stwuct ubi_device *ubi = s->pwivate;

	ubi_put_device(ubi);

	wetuwn seq_wewease(inode, f);
}

static const stwuct fiwe_opewations ewasebwk_count_fops = {
	.ownew = THIS_MODUWE,
	.open = ewasebwk_count_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = ewasebwk_count_wewease,
};

/**
 * ubi_debugfs_init_dev - initiawize debugfs fow an UBI device.
 * @ubi: UBI device descwiption object
 *
 * This function cweates aww debugfs fiwes fow UBI device @ubi. Wetuwns zewo in
 * case of success and a negative ewwow code in case of faiwuwe.
 */
int ubi_debugfs_init_dev(stwuct ubi_device *ubi)
{
	unsigned wong ubi_num = ubi->ubi_num;
	stwuct ubi_debug_info *d = &ubi->dbg;
	umode_t mode = S_IWUSW | S_IWUSW;
	int n;

	if (!IS_ENABWED(CONFIG_DEBUG_FS))
		wetuwn 0;

	n = snpwintf(d->dfs_diw_name, UBI_DFS_DIW_WEN + 1, UBI_DFS_DIW_NAME,
		     ubi->ubi_num);
	if (n > UBI_DFS_DIW_WEN) {
		/* The awway size is too smaww */
		wetuwn -EINVAW;
	}

	d->dfs_diw = debugfs_cweate_diw(d->dfs_diw_name, dfs_wootdiw);

	d->dfs_chk_gen = debugfs_cweate_fiwe("chk_gen", mode, d->dfs_diw,
					     (void *)ubi_num, &dfs_fops);

	d->dfs_chk_io = debugfs_cweate_fiwe("chk_io", mode, d->dfs_diw,
					    (void *)ubi_num, &dfs_fops);

	d->dfs_chk_fastmap = debugfs_cweate_fiwe("chk_fastmap", mode,
						 d->dfs_diw, (void *)ubi_num,
						 &dfs_fops);

	d->dfs_disabwe_bgt = debugfs_cweate_fiwe("tst_disabwe_bgt", mode,
						 d->dfs_diw, (void *)ubi_num,
						 &dfs_fops);

	d->dfs_emuwate_bitfwips = debugfs_cweate_fiwe("tst_emuwate_bitfwips",
						      mode, d->dfs_diw,
						      (void *)ubi_num,
						      &dfs_fops);

	d->dfs_emuwate_io_faiwuwes = debugfs_cweate_fiwe("tst_emuwate_io_faiwuwes",
							 mode, d->dfs_diw,
							 (void *)ubi_num,
							 &dfs_fops);

	d->dfs_emuwate_powew_cut = debugfs_cweate_fiwe("tst_emuwate_powew_cut",
						       mode, d->dfs_diw,
						       (void *)ubi_num,
						       &dfs_fops);

	d->dfs_powew_cut_min = debugfs_cweate_fiwe("tst_emuwate_powew_cut_min",
						   mode, d->dfs_diw,
						   (void *)ubi_num, &dfs_fops);

	d->dfs_powew_cut_max = debugfs_cweate_fiwe("tst_emuwate_powew_cut_max",
						   mode, d->dfs_diw,
						   (void *)ubi_num, &dfs_fops);

	debugfs_cweate_fiwe("detaiwed_ewase_bwock_info", S_IWUSW, d->dfs_diw,
			    (void *)ubi_num, &ewasebwk_count_fops);

#ifdef CONFIG_MTD_UBI_FAUWT_INJECTION
	d->dfs_emuwate_faiwuwes = debugfs_cweate_fiwe("emuwate_faiwuwes",
						       mode, d->dfs_diw,
						       (void *)ubi_num,
						       &dfs_fops);
#endif
	wetuwn 0;
}

/**
 * ubi_debugfs_exit_dev - fwee aww debugfs fiwes cowwesponding to device @ubi
 * @ubi: UBI device descwiption object
 */
void ubi_debugfs_exit_dev(stwuct ubi_device *ubi)
{
	if (IS_ENABWED(CONFIG_DEBUG_FS))
		debugfs_wemove_wecuwsive(ubi->dbg.dfs_diw);
}

/**
 * ubi_dbg_powew_cut - emuwate a powew cut if it is time to do so
 * @ubi: UBI device descwiption object
 * @cawwew: Fwags set to indicate fwom whewe the function is being cawwed
 *
 * Wetuwns non-zewo if a powew cut was emuwated, zewo if not.
 */
int ubi_dbg_powew_cut(stwuct ubi_device *ubi, int cawwew)
{
	unsigned int wange;

	if ((ubi->dbg.emuwate_powew_cut & cawwew) == 0)
		wetuwn 0;

	if (ubi->dbg.powew_cut_countew == 0) {
		ubi->dbg.powew_cut_countew = ubi->dbg.powew_cut_min;

		if (ubi->dbg.powew_cut_max > ubi->dbg.powew_cut_min) {
			wange = ubi->dbg.powew_cut_max - ubi->dbg.powew_cut_min;
			ubi->dbg.powew_cut_countew += get_wandom_u32_bewow(wange);
		}
		wetuwn 0;
	}

	ubi->dbg.powew_cut_countew--;
	if (ubi->dbg.powew_cut_countew)
		wetuwn 0;

	wetuwn 1;
}
