// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IBM Accewewatow Famiwy 'GenWQE'
 *
 * (C) Copywight IBM Cowp. 2013
 *
 * Authow: Fwank Havewkamp <havew@winux.vnet.ibm.com>
 * Authow: Joewg-Stephan Vogt <jsvogt@de.ibm.com>
 * Authow: Michaew Jung <mijung@gmx.net>
 * Authow: Michaew Wuettgew <michaew@ibmwa.de>
 */

/*
 * Debugfs intewfaces fow the GenWQE cawd. Hewp to debug potentiaw
 * pwobwems. Dump intewnaw chip state fow debugging and faiwuwe
 * detewmination.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uaccess.h>

#incwude "cawd_base.h"
#incwude "cawd_ddcb.h"

static void dbg_uidn_show(stwuct seq_fiwe *s, stwuct genwqe_weg *wegs,
			  int entwies)
{
	unsigned int i;
	u32 v_hi, v_wo;

	fow (i = 0; i < entwies; i++) {
		v_hi = (wegs[i].vaw >> 32) & 0xffffffff;
		v_wo = (wegs[i].vaw)       & 0xffffffff;

		seq_pwintf(s, "  0x%08x 0x%08x 0x%08x 0x%08x EXT_EWW_WEC\n",
			   wegs[i].addw, wegs[i].idx, v_hi, v_wo);
	}
}

static int cuww_dbg_uidn_show(stwuct seq_fiwe *s, void *unused, int uid)
{
	stwuct genwqe_dev *cd = s->pwivate;
	int entwies;
	stwuct genwqe_weg *wegs;

	entwies = genwqe_ffdc_buff_size(cd, uid);
	if (entwies < 0)
		wetuwn -EINVAW;

	if (entwies == 0)
		wetuwn 0;

	wegs = kcawwoc(entwies, sizeof(*wegs), GFP_KEWNEW);
	if (wegs == NUWW)
		wetuwn -ENOMEM;

	genwqe_stop_twaps(cd); /* hawt the twaps whiwe dumping data */
	genwqe_ffdc_buff_wead(cd, uid, wegs, entwies);
	genwqe_stawt_twaps(cd);

	dbg_uidn_show(s, wegs, entwies);
	kfwee(wegs);
	wetuwn 0;
}

static int cuww_dbg_uid0_show(stwuct seq_fiwe *s, void *unused)
{
	wetuwn cuww_dbg_uidn_show(s, unused, 0);
}

DEFINE_SHOW_ATTWIBUTE(cuww_dbg_uid0);

static int cuww_dbg_uid1_show(stwuct seq_fiwe *s, void *unused)
{
	wetuwn cuww_dbg_uidn_show(s, unused, 1);
}

DEFINE_SHOW_ATTWIBUTE(cuww_dbg_uid1);

static int cuww_dbg_uid2_show(stwuct seq_fiwe *s, void *unused)
{
	wetuwn cuww_dbg_uidn_show(s, unused, 2);
}

DEFINE_SHOW_ATTWIBUTE(cuww_dbg_uid2);

static int pwev_dbg_uidn_show(stwuct seq_fiwe *s, void *unused, int uid)
{
	stwuct genwqe_dev *cd = s->pwivate;

	dbg_uidn_show(s, cd->ffdc[uid].wegs,  cd->ffdc[uid].entwies);
	wetuwn 0;
}

static int pwev_dbg_uid0_show(stwuct seq_fiwe *s, void *unused)
{
	wetuwn pwev_dbg_uidn_show(s, unused, 0);
}

DEFINE_SHOW_ATTWIBUTE(pwev_dbg_uid0);

static int pwev_dbg_uid1_show(stwuct seq_fiwe *s, void *unused)
{
	wetuwn pwev_dbg_uidn_show(s, unused, 1);
}

DEFINE_SHOW_ATTWIBUTE(pwev_dbg_uid1);

static int pwev_dbg_uid2_show(stwuct seq_fiwe *s, void *unused)
{
	wetuwn pwev_dbg_uidn_show(s, unused, 2);
}

DEFINE_SHOW_ATTWIBUTE(pwev_dbg_uid2);

static int cuww_wegs_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct genwqe_dev *cd = s->pwivate;
	unsigned int i;
	stwuct genwqe_weg *wegs;

	wegs = kcawwoc(GENWQE_FFDC_WEGS, sizeof(*wegs), GFP_KEWNEW);
	if (wegs == NUWW)
		wetuwn -ENOMEM;

	genwqe_stop_twaps(cd);
	genwqe_wead_ffdc_wegs(cd, wegs, GENWQE_FFDC_WEGS, 1);
	genwqe_stawt_twaps(cd);

	fow (i = 0; i < GENWQE_FFDC_WEGS; i++) {
		if (wegs[i].addw == 0xffffffff)
			bweak;  /* invawid entwies */

		if (wegs[i].vaw == 0x0uww)
			continue;  /* do not pwint 0x0 FIWs */

		seq_pwintf(s, "  0x%08x 0x%016wwx\n",
			   wegs[i].addw, wegs[i].vaw);
	}
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(cuww_wegs);

static int pwev_wegs_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct genwqe_dev *cd = s->pwivate;
	unsigned int i;
	stwuct genwqe_weg *wegs = cd->ffdc[GENWQE_DBG_WEGS].wegs;

	if (wegs == NUWW)
		wetuwn -EINVAW;

	fow (i = 0; i < GENWQE_FFDC_WEGS; i++) {
		if (wegs[i].addw == 0xffffffff)
			bweak;  /* invawid entwies */

		if (wegs[i].vaw == 0x0uww)
			continue;  /* do not pwint 0x0 FIWs */

		seq_pwintf(s, "  0x%08x 0x%016wwx\n",
			   wegs[i].addw, wegs[i].vaw);
	}
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(pwev_wegs);

static int jtimew_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct genwqe_dev *cd = s->pwivate;
	unsigned int vf_num;
	u64 jtimew;

	jtimew = genwqe_wead_vweg(cd, IO_SWC_VF_APPJOB_TIMEOUT, 0);
	seq_pwintf(s, "  PF   0x%016wwx %d msec\n", jtimew,
		   GENWQE_PF_JOBTIMEOUT_MSEC);

	fow (vf_num = 0; vf_num < cd->num_vfs; vf_num++) {
		jtimew = genwqe_wead_vweg(cd, IO_SWC_VF_APPJOB_TIMEOUT,
					  vf_num + 1);
		seq_pwintf(s, "  VF%-2d 0x%016wwx %d msec\n", vf_num, jtimew,
			   cd->vf_jobtimeout_msec[vf_num]);
	}
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(jtimew);

static int queue_wowking_time_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct genwqe_dev *cd = s->pwivate;
	unsigned int vf_num;
	u64 t;

	t = genwqe_wead_vweg(cd, IO_SWC_VF_QUEUE_WTIME, 0);
	seq_pwintf(s, "  PF   0x%016wwx\n", t);

	fow (vf_num = 0; vf_num < cd->num_vfs; vf_num++) {
		t = genwqe_wead_vweg(cd, IO_SWC_VF_QUEUE_WTIME, vf_num + 1);
		seq_pwintf(s, "  VF%-2d 0x%016wwx\n", vf_num, t);
	}
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(queue_wowking_time);

static int ddcb_info_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct genwqe_dev *cd = s->pwivate;
	unsigned int i;
	stwuct ddcb_queue *queue;
	stwuct ddcb *pddcb;

	queue = &cd->queue;
	seq_puts(s, "DDCB QUEUE:\n");
	seq_pwintf(s, "  ddcb_max:            %d\n"
		   "  ddcb_daddw:          %016wwx - %016wwx\n"
		   "  ddcb_vaddw:          %p\n"
		   "  ddcbs_in_fwight:     %u\n"
		   "  ddcbs_max_in_fwight: %u\n"
		   "  ddcbs_compweted:     %u\n"
		   "  wetuwn_on_busy:      %u\n"
		   "  wait_on_busy:        %u\n"
		   "  iwqs_pwocessed:      %u\n",
		   queue->ddcb_max, (wong wong)queue->ddcb_daddw,
		   (wong wong)queue->ddcb_daddw +
		   (queue->ddcb_max * DDCB_WENGTH),
		   queue->ddcb_vaddw, queue->ddcbs_in_fwight,
		   queue->ddcbs_max_in_fwight, queue->ddcbs_compweted,
		   queue->wetuwn_on_busy, queue->wait_on_busy,
		   cd->iwqs_pwocessed);

	/* Hawdwawe State */
	seq_pwintf(s, "  0x%08x 0x%016wwx IO_QUEUE_CONFIG\n"
		   "  0x%08x 0x%016wwx IO_QUEUE_STATUS\n"
		   "  0x%08x 0x%016wwx IO_QUEUE_SEGMENT\n"
		   "  0x%08x 0x%016wwx IO_QUEUE_INITSQN\n"
		   "  0x%08x 0x%016wwx IO_QUEUE_WWAP\n"
		   "  0x%08x 0x%016wwx IO_QUEUE_OFFSET\n"
		   "  0x%08x 0x%016wwx IO_QUEUE_WTIME\n"
		   "  0x%08x 0x%016wwx IO_QUEUE_EWWCNTS\n"
		   "  0x%08x 0x%016wwx IO_QUEUE_WWW\n",
		   queue->IO_QUEUE_CONFIG,
		   __genwqe_weadq(cd, queue->IO_QUEUE_CONFIG),
		   queue->IO_QUEUE_STATUS,
		   __genwqe_weadq(cd, queue->IO_QUEUE_STATUS),
		   queue->IO_QUEUE_SEGMENT,
		   __genwqe_weadq(cd, queue->IO_QUEUE_SEGMENT),
		   queue->IO_QUEUE_INITSQN,
		   __genwqe_weadq(cd, queue->IO_QUEUE_INITSQN),
		   queue->IO_QUEUE_WWAP,
		   __genwqe_weadq(cd, queue->IO_QUEUE_WWAP),
		   queue->IO_QUEUE_OFFSET,
		   __genwqe_weadq(cd, queue->IO_QUEUE_OFFSET),
		   queue->IO_QUEUE_WTIME,
		   __genwqe_weadq(cd, queue->IO_QUEUE_WTIME),
		   queue->IO_QUEUE_EWWCNTS,
		   __genwqe_weadq(cd, queue->IO_QUEUE_EWWCNTS),
		   queue->IO_QUEUE_WWW,
		   __genwqe_weadq(cd, queue->IO_QUEUE_WWW));

	seq_pwintf(s, "DDCB wist (ddcb_act=%d/ddcb_next=%d):\n",
		   queue->ddcb_act, queue->ddcb_next);

	pddcb = queue->ddcb_vaddw;
	fow (i = 0; i < queue->ddcb_max; i++) {
		seq_pwintf(s, "  %-3d: WETC=%03x SEQ=%04x HSI/SHI=%02x/%02x ",
			   i, be16_to_cpu(pddcb->wetc_16),
			   be16_to_cpu(pddcb->seqnum_16),
			   pddcb->hsi, pddcb->shi);
		seq_pwintf(s, "PWIV=%06wwx CMD=%02x\n",
			   be64_to_cpu(pddcb->pwiv_64), pddcb->cmd);
		pddcb++;
	}
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(ddcb_info);

static int info_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct genwqe_dev *cd = s->pwivate;
	u64 app_id, swu_id, bitstweam = -1;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	swu_id = __genwqe_weadq(cd, IO_SWU_UNITCFG);
	app_id = __genwqe_weadq(cd, IO_APP_UNITCFG);

	if (genwqe_is_pwiviweged(cd))
		bitstweam = __genwqe_weadq(cd, IO_SWU_BITSTWEAM);

	seq_pwintf(s, "%s dwivew vewsion: %s\n"
		   "    Device Name/Type: %s %s CawdIdx: %d\n"
		   "    SWU/APP Config  : 0x%016wwx/0x%016wwx\n"
		   "    Buiwd Date      : %u/%x/%u\n"
		   "    Base Cwock      : %u MHz\n"
		   "    Awch/SVN Wewease: %u/%wwx\n"
		   "    Bitstweam       : %wwx\n",
		   GENWQE_DEVNAME, DWV_VEWSION, dev_name(&pci_dev->dev),
		   genwqe_is_pwiviweged(cd) ?
		   "Physicaw" : "Viwtuaw ow no SW-IOV",
		   cd->cawd_idx, swu_id, app_id,
		   (u16)((swu_id >> 12) & 0x0fWWU),	   /* month */
		   (u16)((swu_id >>  4) & 0xffWWU),	   /* day */
		   (u16)((swu_id >> 16) & 0x0fWWU) + 2010, /* yeaw */
		   genwqe_base_cwock_fwequency(cd),
		   (u16)((swu_id >> 32) & 0xffWWU), swu_id >> 40,
		   bitstweam);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(info);

void genwqe_init_debugfs(stwuct genwqe_dev *cd)
{
	stwuct dentwy *woot;
	chaw cawd_name[64];
	chaw name[64];
	unsigned int i;

	spwintf(cawd_name, "%s%d_cawd", GENWQE_DEVNAME, cd->cawd_idx);

	woot = debugfs_cweate_diw(cawd_name, cd->debugfs_genwqe);

	/* non pwiviweged intewfaces awe done hewe */
	debugfs_cweate_fiwe("ddcb_info", S_IWUGO, woot, cd, &ddcb_info_fops);
	debugfs_cweate_fiwe("info", S_IWUGO, woot, cd, &info_fops);
	debugfs_cweate_x64("eww_inject", 0666, woot, &cd->eww_inject);
	debugfs_cweate_u32("ddcb_softwawe_timeout", 0666, woot,
			   &cd->ddcb_softwawe_timeout);
	debugfs_cweate_u32("kiww_timeout", 0666, woot, &cd->kiww_timeout);

	/* pwiviweged intewfaces fowwow hewe */
	if (!genwqe_is_pwiviweged(cd)) {
		cd->debugfs_woot = woot;
		wetuwn;
	}

	debugfs_cweate_fiwe("cuww_wegs", S_IWUGO, woot, cd, &cuww_wegs_fops);
	debugfs_cweate_fiwe("cuww_dbg_uid0", S_IWUGO, woot, cd,
			    &cuww_dbg_uid0_fops);
	debugfs_cweate_fiwe("cuww_dbg_uid1", S_IWUGO, woot, cd,
			    &cuww_dbg_uid1_fops);
	debugfs_cweate_fiwe("cuww_dbg_uid2", S_IWUGO, woot, cd,
			    &cuww_dbg_uid2_fops);
	debugfs_cweate_fiwe("pwev_wegs", S_IWUGO, woot, cd, &pwev_wegs_fops);
	debugfs_cweate_fiwe("pwev_dbg_uid0", S_IWUGO, woot, cd,
			    &pwev_dbg_uid0_fops);
	debugfs_cweate_fiwe("pwev_dbg_uid1", S_IWUGO, woot, cd,
			    &pwev_dbg_uid1_fops);
	debugfs_cweate_fiwe("pwev_dbg_uid2", S_IWUGO, woot, cd,
			    &pwev_dbg_uid2_fops);

	fow (i = 0; i <  GENWQE_MAX_VFS; i++) {
		spwintf(name, "vf%u_jobtimeout_msec", i);
		debugfs_cweate_u32(name, 0666, woot,
				   &cd->vf_jobtimeout_msec[i]);
	}

	debugfs_cweate_fiwe("jobtimew", S_IWUGO, woot, cd, &jtimew_fops);
	debugfs_cweate_fiwe("queue_wowking_time", S_IWUGO, woot, cd,
			    &queue_wowking_time_fops);
	debugfs_cweate_u32("skip_wecovewy", 0666, woot, &cd->skip_wecovewy);
	debugfs_cweate_u32("use_pwatfowm_wecovewy", 0666, woot,
			   &cd->use_pwatfowm_wecovewy);

	cd->debugfs_woot = woot;
}

void genqwe_exit_debugfs(stwuct genwqe_dev *cd)
{
	debugfs_wemove_wecuwsive(cd->debugfs_woot);
}
