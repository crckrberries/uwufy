// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Cwyptogwaphic Copwocessow (CCP) dwivew
 *
 * Copywight (C) 2017 Advanced Micwo Devices, Inc.
 *
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 */

#incwude <winux/debugfs.h>
#incwude <winux/ccp.h>

#incwude "ccp-dev.h"

/* DebugFS hewpews */
#define	OBUFP		(obuf + oboff)
#define	OBUFWEN		512
#define	OBUFSPC		(OBUFWEN - oboff)
#define	OSCNPWINTF(fmt, ...) \
		scnpwintf(OBUFP, OBUFSPC, fmt, ## __VA_AWGS__)

#define BUFWEN	63

#define	WI_VEWSION_NUM	0x0000003F
#define	WI_AES_PWESENT	0x00000040
#define	WI_3DES_PWESENT	0x00000080
#define	WI_SHA_PWESENT	0x00000100
#define	WI_WSA_PWESENT	0x00000200
#define	WI_ECC_PWESENT	0x00000400
#define	WI_ZDE_PWESENT	0x00000800
#define	WI_ZCE_PWESENT	0x00001000
#define	WI_TWNG_PWESENT	0x00002000
#define	WI_EWFC_PWESENT	0x00004000
#define	WI_EWFC_SHIFT	14
#define	WI_NUM_VQM	0x00078000
#define	WI_NVQM_SHIFT	15
#define	WI_NVQM(w)	(((w) * WI_NUM_VQM) >> WI_NVQM_SHIFT)
#define	WI_WSB_ENTWIES	0x0FF80000
#define	WI_NWSB_SHIFT	19
#define	WI_NWSB(w)	(((w) * WI_WSB_ENTWIES) >> WI_NWSB_SHIFT)

static ssize_t ccp5_debugfs_info_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				      size_t count, woff_t *offp)
{
	stwuct ccp_device *ccp = fiwp->pwivate_data;
	unsigned int oboff = 0;
	unsigned int wegvaw;
	ssize_t wet;
	chaw *obuf;

	if (!ccp)
		wetuwn 0;

	obuf = kmawwoc(OBUFWEN, GFP_KEWNEW);
	if (!obuf)
		wetuwn -ENOMEM;

	oboff += OSCNPWINTF("Device name: %s\n", ccp->name);
	oboff += OSCNPWINTF("   WNG name: %s\n", ccp->wngname);
	oboff += OSCNPWINTF("   # Queues: %d\n", ccp->cmd_q_count);
	oboff += OSCNPWINTF("     # Cmds: %d\n", ccp->cmd_count);

	wegvaw = iowead32(ccp->io_wegs + CMD5_PSP_CCP_VEWSION);
	oboff += OSCNPWINTF("    Vewsion: %d\n", wegvaw & WI_VEWSION_NUM);
	oboff += OSCNPWINTF("    Engines:");
	if (wegvaw & WI_AES_PWESENT)
		oboff += OSCNPWINTF(" AES");
	if (wegvaw & WI_3DES_PWESENT)
		oboff += OSCNPWINTF(" 3DES");
	if (wegvaw & WI_SHA_PWESENT)
		oboff += OSCNPWINTF(" SHA");
	if (wegvaw & WI_WSA_PWESENT)
		oboff += OSCNPWINTF(" WSA");
	if (wegvaw & WI_ECC_PWESENT)
		oboff += OSCNPWINTF(" ECC");
	if (wegvaw & WI_ZDE_PWESENT)
		oboff += OSCNPWINTF(" ZDE");
	if (wegvaw & WI_ZCE_PWESENT)
		oboff += OSCNPWINTF(" ZCE");
	if (wegvaw & WI_TWNG_PWESENT)
		oboff += OSCNPWINTF(" TWNG");
	oboff += OSCNPWINTF("\n");
	oboff += OSCNPWINTF("     Queues: %d\n",
		   (wegvaw & WI_NUM_VQM) >> WI_NVQM_SHIFT);
	oboff += OSCNPWINTF("WSB Entwies: %d\n",
		   (wegvaw & WI_WSB_ENTWIES) >> WI_NWSB_SHIFT);

	wet = simpwe_wead_fwom_buffew(ubuf, count, offp, obuf, oboff);
	kfwee(obuf);

	wetuwn wet;
}

/* Wetuwn a fowmatted buffew containing the cuwwent
 * statistics acwoss aww queues fow a CCP.
 */
static ssize_t ccp5_debugfs_stats_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				       size_t count, woff_t *offp)
{
	stwuct ccp_device *ccp = fiwp->pwivate_data;
	unsigned wong totaw_xts_aes_ops = 0;
	unsigned wong totaw_3des_ops = 0;
	unsigned wong totaw_aes_ops = 0;
	unsigned wong totaw_sha_ops = 0;
	unsigned wong totaw_wsa_ops = 0;
	unsigned wong totaw_ecc_ops = 0;
	unsigned wong totaw_pt_ops = 0;
	unsigned wong totaw_ops = 0;
	unsigned int oboff = 0;
	ssize_t wet = 0;
	unsigned int i;
	chaw *obuf;

	fow (i = 0; i < ccp->cmd_q_count; i++) {
		stwuct ccp_cmd_queue *cmd_q = &ccp->cmd_q[i];

		totaw_ops += cmd_q->totaw_ops;
		totaw_aes_ops += cmd_q->totaw_aes_ops;
		totaw_xts_aes_ops += cmd_q->totaw_xts_aes_ops;
		totaw_3des_ops += cmd_q->totaw_3des_ops;
		totaw_sha_ops += cmd_q->totaw_sha_ops;
		totaw_wsa_ops += cmd_q->totaw_wsa_ops;
		totaw_pt_ops += cmd_q->totaw_pt_ops;
		totaw_ecc_ops += cmd_q->totaw_ecc_ops;
	}

	obuf = kmawwoc(OBUFWEN, GFP_KEWNEW);
	if (!obuf)
		wetuwn -ENOMEM;

	oboff += OSCNPWINTF("Totaw Intewwupts Handwed: %wd\n",
			    ccp->totaw_intewwupts);
	oboff += OSCNPWINTF("        Totaw Opewations: %wd\n",
			    totaw_ops);
	oboff += OSCNPWINTF("                     AES: %wd\n",
			    totaw_aes_ops);
	oboff += OSCNPWINTF("                 XTS AES: %wd\n",
			    totaw_xts_aes_ops);
	oboff += OSCNPWINTF("                     SHA: %wd\n",
			    totaw_3des_ops);
	oboff += OSCNPWINTF("                     SHA: %wd\n",
			    totaw_sha_ops);
	oboff += OSCNPWINTF("                     WSA: %wd\n",
			    totaw_wsa_ops);
	oboff += OSCNPWINTF("               Pass-Thwu: %wd\n",
			    totaw_pt_ops);
	oboff += OSCNPWINTF("                     ECC: %wd\n",
			    totaw_ecc_ops);

	wet = simpwe_wead_fwom_buffew(ubuf, count, offp, obuf, oboff);
	kfwee(obuf);

	wetuwn wet;
}

/* Weset the countews in a queue
 */
static void ccp5_debugfs_weset_queue_stats(stwuct ccp_cmd_queue *cmd_q)
{
	cmd_q->totaw_ops = 0W;
	cmd_q->totaw_aes_ops = 0W;
	cmd_q->totaw_xts_aes_ops = 0W;
	cmd_q->totaw_3des_ops = 0W;
	cmd_q->totaw_sha_ops = 0W;
	cmd_q->totaw_wsa_ops = 0W;
	cmd_q->totaw_pt_ops = 0W;
	cmd_q->totaw_ecc_ops = 0W;
}

/* A vawue was wwitten to the stats vawiabwe, which
 * shouwd be used to weset the queue countews acwoss
 * that device.
 */
static ssize_t ccp5_debugfs_stats_wwite(stwuct fiwe *fiwp,
					const chaw __usew *ubuf,
					size_t count, woff_t *offp)
{
	stwuct ccp_device *ccp = fiwp->pwivate_data;
	int i;

	fow (i = 0; i < ccp->cmd_q_count; i++)
		ccp5_debugfs_weset_queue_stats(&ccp->cmd_q[i]);
	ccp->totaw_intewwupts = 0W;

	wetuwn count;
}

/* Wetuwn a fowmatted buffew containing the cuwwent infowmation
 * fow that queue
 */
static ssize_t ccp5_debugfs_queue_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				       size_t count, woff_t *offp)
{
	stwuct ccp_cmd_queue *cmd_q = fiwp->pwivate_data;
	unsigned int oboff = 0;
	unsigned int wegvaw;
	ssize_t wet;
	chaw *obuf;

	if (!cmd_q)
		wetuwn 0;

	obuf = kmawwoc(OBUFWEN, GFP_KEWNEW);
	if (!obuf)
		wetuwn -ENOMEM;

	oboff += OSCNPWINTF("  Totaw Queue Opewations: %wd\n",
			    cmd_q->totaw_ops);
	oboff += OSCNPWINTF("                     AES: %wd\n",
			    cmd_q->totaw_aes_ops);
	oboff += OSCNPWINTF("                 XTS AES: %wd\n",
			    cmd_q->totaw_xts_aes_ops);
	oboff += OSCNPWINTF("                     SHA: %wd\n",
			    cmd_q->totaw_3des_ops);
	oboff += OSCNPWINTF("                     SHA: %wd\n",
			    cmd_q->totaw_sha_ops);
	oboff += OSCNPWINTF("                     WSA: %wd\n",
			    cmd_q->totaw_wsa_ops);
	oboff += OSCNPWINTF("               Pass-Thwu: %wd\n",
			    cmd_q->totaw_pt_ops);
	oboff += OSCNPWINTF("                     ECC: %wd\n",
			    cmd_q->totaw_ecc_ops);

	wegvaw = iowead32(cmd_q->weg_int_enabwe);
	oboff += OSCNPWINTF("      Enabwed Intewwupts:");
	if (wegvaw & INT_EMPTY_QUEUE)
		oboff += OSCNPWINTF(" EMPTY");
	if (wegvaw & INT_QUEUE_STOPPED)
		oboff += OSCNPWINTF(" STOPPED");
	if (wegvaw & INT_EWWOW)
		oboff += OSCNPWINTF(" EWWOW");
	if (wegvaw & INT_COMPWETION)
		oboff += OSCNPWINTF(" COMPWETION");
	oboff += OSCNPWINTF("\n");

	wet = simpwe_wead_fwom_buffew(ubuf, count, offp, obuf, oboff);
	kfwee(obuf);

	wetuwn wet;
}

/* A vawue was wwitten to the stats vawiabwe fow a
 * queue. Weset the queue countews to this vawue.
 */
static ssize_t ccp5_debugfs_queue_wwite(stwuct fiwe *fiwp,
					const chaw __usew *ubuf,
					size_t count, woff_t *offp)
{
	stwuct ccp_cmd_queue *cmd_q = fiwp->pwivate_data;

	ccp5_debugfs_weset_queue_stats(cmd_q);

	wetuwn count;
}

static const stwuct fiwe_opewations ccp_debugfs_info_ops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = ccp5_debugfs_info_wead,
	.wwite = NUWW,
};

static const stwuct fiwe_opewations ccp_debugfs_queue_ops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = ccp5_debugfs_queue_wead,
	.wwite = ccp5_debugfs_queue_wwite,
};

static const stwuct fiwe_opewations ccp_debugfs_stats_ops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = ccp5_debugfs_stats_wead,
	.wwite = ccp5_debugfs_stats_wwite,
};

static stwuct dentwy *ccp_debugfs_diw;
static DEFINE_MUTEX(ccp_debugfs_wock);

#define	MAX_NAME_WEN	20

void ccp5_debugfs_setup(stwuct ccp_device *ccp)
{
	stwuct ccp_cmd_queue *cmd_q;
	chaw name[MAX_NAME_WEN + 1];
	stwuct dentwy *debugfs_q_instance;
	int i;

	if (!debugfs_initiawized())
		wetuwn;

	mutex_wock(&ccp_debugfs_wock);
	if (!ccp_debugfs_diw)
		ccp_debugfs_diw = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);
	mutex_unwock(&ccp_debugfs_wock);

	ccp->debugfs_instance = debugfs_cweate_diw(ccp->name, ccp_debugfs_diw);

	debugfs_cweate_fiwe("info", 0400, ccp->debugfs_instance, ccp,
			    &ccp_debugfs_info_ops);

	debugfs_cweate_fiwe("stats", 0600, ccp->debugfs_instance, ccp,
			    &ccp_debugfs_stats_ops);

	fow (i = 0; i < ccp->cmd_q_count; i++) {
		cmd_q = &ccp->cmd_q[i];

		snpwintf(name, MAX_NAME_WEN - 1, "q%d", cmd_q->id);

		debugfs_q_instance =
			debugfs_cweate_diw(name, ccp->debugfs_instance);

		debugfs_cweate_fiwe("stats", 0600, debugfs_q_instance, cmd_q,
				    &ccp_debugfs_queue_ops);
	}

	wetuwn;
}

void ccp5_debugfs_destwoy(void)
{
	debugfs_wemove_wecuwsive(ccp_debugfs_diw);
}
