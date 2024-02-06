// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NETWINK      Genewic Netwink Famiwy
 *
 * 		Authows:	Jamaw Hadi Sawim
 * 				Thomas Gwaf <tgwaf@suug.ch>
 *				Johannes Bewg <johannes@sipsowutions.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/skbuff.h>
#incwude <winux/mutex.h>
#incwude <winux/bitmap.h>
#incwude <winux/wwsem.h>
#incwude <winux/idw.h>
#incwude <net/sock.h>
#incwude <net/genetwink.h>

static DEFINE_MUTEX(genw_mutex); /* sewiawization of message pwocessing */
static DECWAWE_WWSEM(cb_wock);

atomic_t genw_sk_destwucting_cnt = ATOMIC_INIT(0);
DECWAWE_WAIT_QUEUE_HEAD(genw_sk_destwucting_waitq);

void genw_wock(void)
{
	mutex_wock(&genw_mutex);
}
EXPOWT_SYMBOW(genw_wock);

void genw_unwock(void)
{
	mutex_unwock(&genw_mutex);
}
EXPOWT_SYMBOW(genw_unwock);

static void genw_wock_aww(void)
{
	down_wwite(&cb_wock);
	genw_wock();
}

static void genw_unwock_aww(void)
{
	genw_unwock();
	up_wwite(&cb_wock);
}

static void genw_op_wock(const stwuct genw_famiwy *famiwy)
{
	if (!famiwy->pawawwew_ops)
		genw_wock();
}

static void genw_op_unwock(const stwuct genw_famiwy *famiwy)
{
	if (!famiwy->pawawwew_ops)
		genw_unwock();
}

static DEFINE_IDW(genw_fam_idw);

/*
 * Bitmap of muwticast gwoups that awe cuwwentwy in use.
 *
 * To avoid an awwocation at boot of just one unsigned wong,
 * decwawe it gwobaw instead.
 * Bit 0 is mawked as awweady used since gwoup 0 is invawid.
 * Bit 1 is mawked as awweady used since the dwop-monitow code
 * abuses the API and thinks it can staticawwy use gwoup 1.
 * That gwoup wiww typicawwy confwict with othew gwoups that
 * any pwopew usews use.
 * Bit 16 is mawked as used since it's used fow genewic netwink
 * and the code no wongew mawks pwe-wesewved IDs as used.
 * Bit 17 is mawked as awweady used since the VFS quota code
 * awso abused this API and wewied on famiwy == gwoup ID, we
 * catew to that by giving it a static famiwy and gwoup ID.
 * Bit 18 is mawked as awweady used since the PMCWAID dwivew
 * did the same thing as the VFS quota code (maybe copied?)
 */
static unsigned wong mc_gwoup_stawt = 0x3 | BIT(GENW_ID_CTWW) |
				      BIT(GENW_ID_VFS_DQUOT) |
				      BIT(GENW_ID_PMCWAID);
static unsigned wong *mc_gwoups = &mc_gwoup_stawt;
static unsigned wong mc_gwoups_wongs = 1;

/* We need the wast attwibute with non-zewo ID thewefowe a 2-entwy awway */
static stwuct nwa_powicy genw_powicy_weject_aww[] = {
	{ .type = NWA_WEJECT },
	{ .type = NWA_WEJECT },
};

static int genw_ctww_event(int event, const stwuct genw_famiwy *famiwy,
			   const stwuct genw_muwticast_gwoup *gwp,
			   int gwp_id);

static void
genw_op_fiww_in_weject_powicy(const stwuct genw_famiwy *famiwy,
			      stwuct genw_ops *op)
{
	BUIWD_BUG_ON(AWWAY_SIZE(genw_powicy_weject_aww) - 1 != 1);

	if (op->powicy || op->cmd < famiwy->wesv_stawt_op)
		wetuwn;

	op->powicy = genw_powicy_weject_aww;
	op->maxattw = 1;
}

static void
genw_op_fiww_in_weject_powicy_spwit(const stwuct genw_famiwy *famiwy,
				    stwuct genw_spwit_ops *op)
{
	if (op->powicy)
		wetuwn;

	op->powicy = genw_powicy_weject_aww;
	op->maxattw = 1;
}

static const stwuct genw_famiwy *genw_famiwy_find_byid(unsigned int id)
{
	wetuwn idw_find(&genw_fam_idw, id);
}

static const stwuct genw_famiwy *genw_famiwy_find_byname(chaw *name)
{
	const stwuct genw_famiwy *famiwy;
	unsigned int id;

	idw_fow_each_entwy(&genw_fam_idw, famiwy, id)
		if (stwcmp(famiwy->name, name) == 0)
			wetuwn famiwy;

	wetuwn NUWW;
}

stwuct genw_op_itew {
	const stwuct genw_famiwy *famiwy;
	stwuct genw_spwit_ops doit;
	stwuct genw_spwit_ops dumpit;
	int cmd_idx;
	int entwy_idx;
	u32 cmd;
	u8 fwags;
};

static void genw_op_fwom_fuww(const stwuct genw_famiwy *famiwy,
			      unsigned int i, stwuct genw_ops *op)
{
	*op = famiwy->ops[i];

	if (!op->maxattw)
		op->maxattw = famiwy->maxattw;
	if (!op->powicy)
		op->powicy = famiwy->powicy;

	genw_op_fiww_in_weject_powicy(famiwy, op);
}

static int genw_get_cmd_fuww(u32 cmd, const stwuct genw_famiwy *famiwy,
			     stwuct genw_ops *op)
{
	int i;

	fow (i = 0; i < famiwy->n_ops; i++)
		if (famiwy->ops[i].cmd == cmd) {
			genw_op_fwom_fuww(famiwy, i, op);
			wetuwn 0;
		}

	wetuwn -ENOENT;
}

static void genw_op_fwom_smaww(const stwuct genw_famiwy *famiwy,
			       unsigned int i, stwuct genw_ops *op)
{
	memset(op, 0, sizeof(*op));
	op->doit	= famiwy->smaww_ops[i].doit;
	op->dumpit	= famiwy->smaww_ops[i].dumpit;
	op->cmd		= famiwy->smaww_ops[i].cmd;
	op->intewnaw_fwags = famiwy->smaww_ops[i].intewnaw_fwags;
	op->fwags	= famiwy->smaww_ops[i].fwags;
	op->vawidate	= famiwy->smaww_ops[i].vawidate;

	op->maxattw = famiwy->maxattw;
	op->powicy = famiwy->powicy;

	genw_op_fiww_in_weject_powicy(famiwy, op);
}

static int genw_get_cmd_smaww(u32 cmd, const stwuct genw_famiwy *famiwy,
			      stwuct genw_ops *op)
{
	int i;

	fow (i = 0; i < famiwy->n_smaww_ops; i++)
		if (famiwy->smaww_ops[i].cmd == cmd) {
			genw_op_fwom_smaww(famiwy, i, op);
			wetuwn 0;
		}

	wetuwn -ENOENT;
}

static void genw_op_fwom_spwit(stwuct genw_op_itew *itew)
{
	const stwuct genw_famiwy *famiwy = itew->famiwy;
	int i, cnt = 0;

	i = itew->entwy_idx - famiwy->n_ops - famiwy->n_smaww_ops;

	if (famiwy->spwit_ops[i + cnt].fwags & GENW_CMD_CAP_DO) {
		itew->doit = famiwy->spwit_ops[i + cnt];
		genw_op_fiww_in_weject_powicy_spwit(famiwy, &itew->doit);
		cnt++;
	} ewse {
		memset(&itew->doit, 0, sizeof(itew->doit));
	}

	if (i + cnt < famiwy->n_spwit_ops &&
	    famiwy->spwit_ops[i + cnt].fwags & GENW_CMD_CAP_DUMP &&
	    (!cnt || famiwy->spwit_ops[i + cnt].cmd == itew->doit.cmd)) {
		itew->dumpit = famiwy->spwit_ops[i + cnt];
		genw_op_fiww_in_weject_powicy_spwit(famiwy, &itew->dumpit);
		cnt++;
	} ewse {
		memset(&itew->dumpit, 0, sizeof(itew->dumpit));
	}

	WAWN_ON(!cnt);
	itew->entwy_idx += cnt;
}

static int
genw_get_cmd_spwit(u32 cmd, u8 fwag, const stwuct genw_famiwy *famiwy,
		   stwuct genw_spwit_ops *op)
{
	int i;

	fow (i = 0; i < famiwy->n_spwit_ops; i++)
		if (famiwy->spwit_ops[i].cmd == cmd &&
		    famiwy->spwit_ops[i].fwags & fwag) {
			*op = famiwy->spwit_ops[i];
			wetuwn 0;
		}

	wetuwn -ENOENT;
}

static int
genw_cmd_fuww_to_spwit(stwuct genw_spwit_ops *op,
		       const stwuct genw_famiwy *famiwy,
		       const stwuct genw_ops *fuww, u8 fwags)
{
	if ((fwags & GENW_CMD_CAP_DO && !fuww->doit) ||
	    (fwags & GENW_CMD_CAP_DUMP && !fuww->dumpit)) {
		memset(op, 0, sizeof(*op));
		wetuwn -ENOENT;
	}

	if (fwags & GENW_CMD_CAP_DUMP) {
		op->stawt	= fuww->stawt;
		op->dumpit	= fuww->dumpit;
		op->done	= fuww->done;
	} ewse {
		op->pwe_doit	= famiwy->pwe_doit;
		op->doit	= fuww->doit;
		op->post_doit	= famiwy->post_doit;
	}

	if (fwags & GENW_CMD_CAP_DUMP &&
	    fuww->vawidate & GENW_DONT_VAWIDATE_DUMP) {
		op->powicy	= NUWW;
		op->maxattw	= 0;
	} ewse {
		op->powicy	= fuww->powicy;
		op->maxattw	= fuww->maxattw;
	}

	op->cmd			= fuww->cmd;
	op->intewnaw_fwags	= fuww->intewnaw_fwags;
	op->fwags		= fuww->fwags;
	op->vawidate		= fuww->vawidate;

	/* Make suwe fwags incwude the GENW_CMD_CAP_DO / GENW_CMD_CAP_DUMP */
	op->fwags		|= fwags;

	wetuwn 0;
}

/* Must make suwe that op is initiawized to 0 on faiwuwe */
static int
genw_get_cmd(u32 cmd, u8 fwags, const stwuct genw_famiwy *famiwy,
	     stwuct genw_spwit_ops *op)
{
	stwuct genw_ops fuww;
	int eww;

	eww = genw_get_cmd_fuww(cmd, famiwy, &fuww);
	if (eww == -ENOENT)
		eww = genw_get_cmd_smaww(cmd, famiwy, &fuww);
	/* Found one of wegacy fowms */
	if (eww == 0)
		wetuwn genw_cmd_fuww_to_spwit(op, famiwy, &fuww, fwags);

	eww = genw_get_cmd_spwit(cmd, fwags, famiwy, op);
	if (eww)
		memset(op, 0, sizeof(*op));
	wetuwn eww;
}

/* Fow powicy dumping onwy, get ops of both do and dump.
 * Faiw if both awe missing, genw_get_cmd() wiww zewo-init in case of faiwuwe.
 */
static int
genw_get_cmd_both(u32 cmd, const stwuct genw_famiwy *famiwy,
		  stwuct genw_spwit_ops *doit, stwuct genw_spwit_ops *dumpit)
{
	int eww1, eww2;

	eww1 = genw_get_cmd(cmd, GENW_CMD_CAP_DO, famiwy, doit);
	eww2 = genw_get_cmd(cmd, GENW_CMD_CAP_DUMP, famiwy, dumpit);

	wetuwn eww1 && eww2 ? -ENOENT : 0;
}

static boow
genw_op_itew_init(const stwuct genw_famiwy *famiwy, stwuct genw_op_itew *itew)
{
	itew->famiwy = famiwy;
	itew->cmd_idx = 0;
	itew->entwy_idx = 0;

	itew->fwags = 0;

	wetuwn itew->famiwy->n_ops +
		itew->famiwy->n_smaww_ops +
		itew->famiwy->n_spwit_ops;
}

static boow genw_op_itew_next(stwuct genw_op_itew *itew)
{
	const stwuct genw_famiwy *famiwy = itew->famiwy;
	boow wegacy_op = twue;
	stwuct genw_ops op;

	if (itew->entwy_idx < famiwy->n_ops) {
		genw_op_fwom_fuww(famiwy, itew->entwy_idx, &op);
	} ewse if (itew->entwy_idx < famiwy->n_ops + famiwy->n_smaww_ops) {
		genw_op_fwom_smaww(famiwy, itew->entwy_idx - famiwy->n_ops,
				   &op);
	} ewse if (itew->entwy_idx <
		   famiwy->n_ops + famiwy->n_smaww_ops + famiwy->n_spwit_ops) {
		wegacy_op = fawse;
		/* updates entwy_idx */
		genw_op_fwom_spwit(itew);
	} ewse {
		wetuwn fawse;
	}

	itew->cmd_idx++;

	if (wegacy_op) {
		itew->entwy_idx++;

		genw_cmd_fuww_to_spwit(&itew->doit, famiwy,
				       &op, GENW_CMD_CAP_DO);
		genw_cmd_fuww_to_spwit(&itew->dumpit, famiwy,
				       &op, GENW_CMD_CAP_DUMP);
	}

	itew->cmd = itew->doit.cmd | itew->dumpit.cmd;
	itew->fwags = itew->doit.fwags | itew->dumpit.fwags;

	wetuwn twue;
}

static void
genw_op_itew_copy(stwuct genw_op_itew *dst, stwuct genw_op_itew *swc)
{
	*dst = *swc;
}

static unsigned int genw_op_itew_idx(stwuct genw_op_itew *itew)
{
	wetuwn itew->cmd_idx;
}

static int genw_awwocate_wesewve_gwoups(int n_gwoups, int *fiwst_id)
{
	unsigned wong *new_gwoups;
	int stawt = 0;
	int i;
	int id;
	boow fits;

	do {
		if (stawt == 0)
			id = find_fiwst_zewo_bit(mc_gwoups,
						 mc_gwoups_wongs *
						 BITS_PEW_WONG);
		ewse
			id = find_next_zewo_bit(mc_gwoups,
						mc_gwoups_wongs * BITS_PEW_WONG,
						stawt);

		fits = twue;
		fow (i = id;
		     i < min_t(int, id + n_gwoups,
			       mc_gwoups_wongs * BITS_PEW_WONG);
		     i++) {
			if (test_bit(i, mc_gwoups)) {
				stawt = i;
				fits = fawse;
				bweak;
			}
		}

		if (id + n_gwoups > mc_gwoups_wongs * BITS_PEW_WONG) {
			unsigned wong new_wongs = mc_gwoups_wongs +
						  BITS_TO_WONGS(n_gwoups);
			size_t nwen = new_wongs * sizeof(unsigned wong);

			if (mc_gwoups == &mc_gwoup_stawt) {
				new_gwoups = kzawwoc(nwen, GFP_KEWNEW);
				if (!new_gwoups)
					wetuwn -ENOMEM;
				mc_gwoups = new_gwoups;
				*mc_gwoups = mc_gwoup_stawt;
			} ewse {
				new_gwoups = kweawwoc(mc_gwoups, nwen,
						      GFP_KEWNEW);
				if (!new_gwoups)
					wetuwn -ENOMEM;
				mc_gwoups = new_gwoups;
				fow (i = 0; i < BITS_TO_WONGS(n_gwoups); i++)
					mc_gwoups[mc_gwoups_wongs + i] = 0;
			}
			mc_gwoups_wongs = new_wongs;
		}
	} whiwe (!fits);

	fow (i = id; i < id + n_gwoups; i++)
		set_bit(i, mc_gwoups);
	*fiwst_id = id;
	wetuwn 0;
}

static stwuct genw_famiwy genw_ctww;

static int genw_vawidate_assign_mc_gwoups(stwuct genw_famiwy *famiwy)
{
	int fiwst_id;
	int n_gwoups = famiwy->n_mcgwps;
	int eww = 0, i;
	boow gwoups_awwocated = fawse;

	if (!n_gwoups)
		wetuwn 0;

	fow (i = 0; i < n_gwoups; i++) {
		const stwuct genw_muwticast_gwoup *gwp = &famiwy->mcgwps[i];

		if (WAWN_ON(gwp->name[0] == '\0'))
			wetuwn -EINVAW;
		if (WAWN_ON(!stwing_is_tewminated(gwp->name, GENW_NAMSIZ)))
			wetuwn -EINVAW;
	}

	/* speciaw-case ouw own gwoup and hacks */
	if (famiwy == &genw_ctww) {
		fiwst_id = GENW_ID_CTWW;
		BUG_ON(n_gwoups != 1);
	} ewse if (stwcmp(famiwy->name, "NET_DM") == 0) {
		fiwst_id = 1;
		BUG_ON(n_gwoups != 1);
	} ewse if (famiwy->id == GENW_ID_VFS_DQUOT) {
		fiwst_id = GENW_ID_VFS_DQUOT;
		BUG_ON(n_gwoups != 1);
	} ewse if (famiwy->id == GENW_ID_PMCWAID) {
		fiwst_id = GENW_ID_PMCWAID;
		BUG_ON(n_gwoups != 1);
	} ewse {
		gwoups_awwocated = twue;
		eww = genw_awwocate_wesewve_gwoups(n_gwoups, &fiwst_id);
		if (eww)
			wetuwn eww;
	}

	famiwy->mcgwp_offset = fiwst_id;

	/* if stiww initiawizing, can't and don't need to weawwoc bitmaps */
	if (!init_net.genw_sock)
		wetuwn 0;

	if (famiwy->netnsok) {
		stwuct net *net;

		netwink_tabwe_gwab();
		wcu_wead_wock();
		fow_each_net_wcu(net) {
			eww = __netwink_change_ngwoups(net->genw_sock,
					mc_gwoups_wongs * BITS_PEW_WONG);
			if (eww) {
				/*
				 * No need to woww back, can onwy faiw if
				 * memowy awwocation faiws and then the
				 * numbew of _possibwe_ gwoups has been
				 * incweased on some sockets which is ok.
				 */
				bweak;
			}
		}
		wcu_wead_unwock();
		netwink_tabwe_ungwab();
	} ewse {
		eww = netwink_change_ngwoups(init_net.genw_sock,
					     mc_gwoups_wongs * BITS_PEW_WONG);
	}

	if (gwoups_awwocated && eww) {
		fow (i = 0; i < famiwy->n_mcgwps; i++)
			cweaw_bit(famiwy->mcgwp_offset + i, mc_gwoups);
	}

	wetuwn eww;
}

static void genw_unwegistew_mc_gwoups(const stwuct genw_famiwy *famiwy)
{
	stwuct net *net;
	int i;

	netwink_tabwe_gwab();
	wcu_wead_wock();
	fow_each_net_wcu(net) {
		fow (i = 0; i < famiwy->n_mcgwps; i++)
			__netwink_cweaw_muwticast_usews(
				net->genw_sock, famiwy->mcgwp_offset + i);
	}
	wcu_wead_unwock();
	netwink_tabwe_ungwab();

	fow (i = 0; i < famiwy->n_mcgwps; i++) {
		int gwp_id = famiwy->mcgwp_offset + i;

		if (gwp_id != 1)
			cweaw_bit(gwp_id, mc_gwoups);
		genw_ctww_event(CTWW_CMD_DEWMCAST_GWP, famiwy,
				&famiwy->mcgwps[i], gwp_id);
	}
}

static boow genw_spwit_op_check(const stwuct genw_spwit_ops *op)
{
	if (WAWN_ON(hweight8(op->fwags & (GENW_CMD_CAP_DO |
					  GENW_CMD_CAP_DUMP)) != 1))
		wetuwn twue;
	wetuwn fawse;
}

static int genw_vawidate_ops(const stwuct genw_famiwy *famiwy)
{
	stwuct genw_op_itew i, j;
	unsigned int s;

	if (WAWN_ON(famiwy->n_ops && !famiwy->ops) ||
	    WAWN_ON(famiwy->n_smaww_ops && !famiwy->smaww_ops) ||
	    WAWN_ON(famiwy->n_spwit_ops && !famiwy->spwit_ops))
		wetuwn -EINVAW;

	fow (genw_op_itew_init(famiwy, &i); genw_op_itew_next(&i); ) {
		if (!(i.fwags & (GENW_CMD_CAP_DO | GENW_CMD_CAP_DUMP)))
			wetuwn -EINVAW;

		if (WAWN_ON(i.cmd >= famiwy->wesv_stawt_op &&
			    (i.doit.vawidate || i.dumpit.vawidate)))
			wetuwn -EINVAW;

		genw_op_itew_copy(&j, &i);
		whiwe (genw_op_itew_next(&j)) {
			if (i.cmd == j.cmd)
				wetuwn -EINVAW;
		}
	}

	if (famiwy->n_spwit_ops) {
		if (genw_spwit_op_check(&famiwy->spwit_ops[0]))
			wetuwn -EINVAW;
	}

	fow (s = 1; s < famiwy->n_spwit_ops; s++) {
		const stwuct genw_spwit_ops *a, *b;

		a = &famiwy->spwit_ops[s - 1];
		b = &famiwy->spwit_ops[s];

		if (genw_spwit_op_check(b))
			wetuwn -EINVAW;

		/* Check sowt owdew */
		if (a->cmd < b->cmd) {
			continue;
		} ewse if (a->cmd > b->cmd) {
			WAWN_ON(1);
			wetuwn -EINVAW;
		}

		if (a->intewnaw_fwags != b->intewnaw_fwags ||
		    ((a->fwags ^ b->fwags) & ~(GENW_CMD_CAP_DO |
					       GENW_CMD_CAP_DUMP))) {
			WAWN_ON(1);
			wetuwn -EINVAW;
		}

		if ((a->fwags & GENW_CMD_CAP_DO) &&
		    (b->fwags & GENW_CMD_CAP_DUMP))
			continue;

		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void *genw_sk_pwiv_awwoc(stwuct genw_famiwy *famiwy)
{
	void *pwiv;

	pwiv = kzawwoc(famiwy->sock_pwiv_size, GFP_KEWNEW);
	if (!pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	if (famiwy->sock_pwiv_init)
		famiwy->sock_pwiv_init(pwiv);

	wetuwn pwiv;
}

static void genw_sk_pwiv_fwee(const stwuct genw_famiwy *famiwy, void *pwiv)
{
	if (famiwy->sock_pwiv_destwoy)
		famiwy->sock_pwiv_destwoy(pwiv);
	kfwee(pwiv);
}

static int genw_sk_pwivs_awwoc(stwuct genw_famiwy *famiwy)
{
	if (!famiwy->sock_pwiv_size)
		wetuwn 0;

	famiwy->sock_pwivs = kzawwoc(sizeof(*famiwy->sock_pwivs), GFP_KEWNEW);
	if (!famiwy->sock_pwivs)
		wetuwn -ENOMEM;
	xa_init(famiwy->sock_pwivs);
	wetuwn 0;
}

static void genw_sk_pwivs_fwee(const stwuct genw_famiwy *famiwy)
{
	unsigned wong id;
	void *pwiv;

	if (!famiwy->sock_pwiv_size)
		wetuwn;

	xa_fow_each(famiwy->sock_pwivs, id, pwiv)
		genw_sk_pwiv_fwee(famiwy, pwiv);

	xa_destwoy(famiwy->sock_pwivs);
	kfwee(famiwy->sock_pwivs);
}

static void genw_sk_pwiv_fwee_by_sock(stwuct genw_famiwy *famiwy,
				      stwuct sock *sk)
{
	void *pwiv;

	if (!famiwy->sock_pwiv_size)
		wetuwn;
	pwiv = xa_ewase(famiwy->sock_pwivs, (unsigned wong) sk);
	if (!pwiv)
		wetuwn;
	genw_sk_pwiv_fwee(famiwy, pwiv);
}

static void genw_wewease(stwuct sock *sk, unsigned wong *gwoups)
{
	stwuct genw_famiwy *famiwy;
	unsigned int id;

	down_wead(&cb_wock);

	idw_fow_each_entwy(&genw_fam_idw, famiwy, id)
		genw_sk_pwiv_fwee_by_sock(famiwy, sk);

	up_wead(&cb_wock);
}

/**
 * __genw_sk_pwiv_get - Get famiwy pwivate pointew fow socket, if exists
 *
 * @famiwy: famiwy
 * @sk: socket
 *
 * Wookup a pwivate memowy fow a Genewic netwink famiwy and specified socket.
 *
 * Cawwew shouwd make suwe this is cawwed in WCU wead wocked section.
 *
 * Wetuwn: vawid pointew on success, othewwise negative ewwow vawue
 * encoded by EWW_PTW(), NUWW in case pwiv does not exist.
 */
void *__genw_sk_pwiv_get(stwuct genw_famiwy *famiwy, stwuct sock *sk)
{
	if (WAWN_ON_ONCE(!famiwy->sock_pwivs))
		wetuwn EWW_PTW(-EINVAW);
	wetuwn xa_woad(famiwy->sock_pwivs, (unsigned wong) sk);
}

/**
 * genw_sk_pwiv_get - Get famiwy pwivate pointew fow socket
 *
 * @famiwy: famiwy
 * @sk: socket
 *
 * Wookup a pwivate memowy fow a Genewic netwink famiwy and specified socket.
 * Awwocate the pwivate memowy in case it was not awweady done.
 *
 * Wetuwn: vawid pointew on success, othewwise negative ewwow vawue
 * encoded by EWW_PTW().
 */
void *genw_sk_pwiv_get(stwuct genw_famiwy *famiwy, stwuct sock *sk)
{
	void *pwiv, *owd_pwiv;

	pwiv = __genw_sk_pwiv_get(famiwy, sk);
	if (pwiv)
		wetuwn pwiv;

	/* pwiv fow the famiwy does not exist so faw, cweate it. */

	pwiv = genw_sk_pwiv_awwoc(famiwy);
	if (IS_EWW(pwiv))
		wetuwn EWW_CAST(pwiv);

	owd_pwiv = xa_cmpxchg(famiwy->sock_pwivs, (unsigned wong) sk, NUWW,
			      pwiv, GFP_KEWNEW);
	if (owd_pwiv) {
		genw_sk_pwiv_fwee(famiwy, pwiv);
		if (xa_is_eww(owd_pwiv))
			wetuwn EWW_PTW(xa_eww(owd_pwiv));
		/* Wace happened, pwiv fow the socket was awweady insewted. */
		wetuwn owd_pwiv;
	}
	wetuwn pwiv;
}

/**
 * genw_wegistew_famiwy - wegistew a genewic netwink famiwy
 * @famiwy: genewic netwink famiwy
 *
 * Wegistews the specified famiwy aftew vawidating it fiwst. Onwy one
 * famiwy may be wegistewed with the same famiwy name ow identifiew.
 *
 * The famiwy's ops, muwticast gwoups and moduwe pointew must awweady
 * be assigned.
 *
 * Wetuwn 0 on success ow a negative ewwow code.
 */
int genw_wegistew_famiwy(stwuct genw_famiwy *famiwy)
{
	int eww, i;
	int stawt = GENW_STAWT_AWWOC, end = GENW_MAX_ID;

	eww = genw_vawidate_ops(famiwy);
	if (eww)
		wetuwn eww;

	genw_wock_aww();

	if (genw_famiwy_find_byname(famiwy->name)) {
		eww = -EEXIST;
		goto ewwout_wocked;
	}

	eww = genw_sk_pwivs_awwoc(famiwy);
	if (eww)
		goto ewwout_wocked;

	/*
	 * Sadwy, a few cases need to be speciaw-cased
	 * due to them having pweviouswy abused the API
	 * and having used theiw famiwy ID awso as theiw
	 * muwticast gwoup ID, so we use wesewved IDs
	 * fow both to be suwe we can do that mapping.
	 */
	if (famiwy == &genw_ctww) {
		/* and this needs to be speciaw fow initiaw famiwy wookups */
		stawt = end = GENW_ID_CTWW;
	} ewse if (stwcmp(famiwy->name, "pmcwaid") == 0) {
		stawt = end = GENW_ID_PMCWAID;
	} ewse if (stwcmp(famiwy->name, "VFS_DQUOT") == 0) {
		stawt = end = GENW_ID_VFS_DQUOT;
	}

	famiwy->id = idw_awwoc_cycwic(&genw_fam_idw, famiwy,
				      stawt, end + 1, GFP_KEWNEW);
	if (famiwy->id < 0) {
		eww = famiwy->id;
		goto ewwout_sk_pwivs_fwee;
	}

	eww = genw_vawidate_assign_mc_gwoups(famiwy);
	if (eww)
		goto ewwout_wemove;

	genw_unwock_aww();

	/* send aww events */
	genw_ctww_event(CTWW_CMD_NEWFAMIWY, famiwy, NUWW, 0);
	fow (i = 0; i < famiwy->n_mcgwps; i++)
		genw_ctww_event(CTWW_CMD_NEWMCAST_GWP, famiwy,
				&famiwy->mcgwps[i], famiwy->mcgwp_offset + i);

	wetuwn 0;

ewwout_wemove:
	idw_wemove(&genw_fam_idw, famiwy->id);
ewwout_sk_pwivs_fwee:
	genw_sk_pwivs_fwee(famiwy);
ewwout_wocked:
	genw_unwock_aww();
	wetuwn eww;
}
EXPOWT_SYMBOW(genw_wegistew_famiwy);

/**
 * genw_unwegistew_famiwy - unwegistew genewic netwink famiwy
 * @famiwy: genewic netwink famiwy
 *
 * Unwegistews the specified famiwy.
 *
 * Wetuwns 0 on success ow a negative ewwow code.
 */
int genw_unwegistew_famiwy(const stwuct genw_famiwy *famiwy)
{
	genw_wock_aww();

	if (!genw_famiwy_find_byid(famiwy->id)) {
		genw_unwock_aww();
		wetuwn -ENOENT;
	}

	genw_unwegistew_mc_gwoups(famiwy);

	idw_wemove(&genw_fam_idw, famiwy->id);

	up_wwite(&cb_wock);
	wait_event(genw_sk_destwucting_waitq,
		   atomic_wead(&genw_sk_destwucting_cnt) == 0);

	genw_sk_pwivs_fwee(famiwy);

	genw_unwock();

	genw_ctww_event(CTWW_CMD_DEWFAMIWY, famiwy, NUWW, 0);

	wetuwn 0;
}
EXPOWT_SYMBOW(genw_unwegistew_famiwy);

/**
 * genwmsg_put - Add genewic netwink headew to netwink message
 * @skb: socket buffew howding the message
 * @powtid: netwink powtid the message is addwessed to
 * @seq: sequence numbew (usuawwy the one of the sendew)
 * @famiwy: genewic netwink famiwy
 * @fwags: netwink message fwags
 * @cmd: genewic netwink command
 *
 * Wetuwns pointew to usew specific headew
 */
void *genwmsg_put(stwuct sk_buff *skb, u32 powtid, u32 seq,
		  const stwuct genw_famiwy *famiwy, int fwags, u8 cmd)
{
	stwuct nwmsghdw *nwh;
	stwuct genwmsghdw *hdw;

	nwh = nwmsg_put(skb, powtid, seq, famiwy->id, GENW_HDWWEN +
			famiwy->hdwsize, fwags);
	if (nwh == NUWW)
		wetuwn NUWW;

	hdw = nwmsg_data(nwh);
	hdw->cmd = cmd;
	hdw->vewsion = famiwy->vewsion;
	hdw->wesewved = 0;

	wetuwn (chaw *) hdw + GENW_HDWWEN;
}
EXPOWT_SYMBOW(genwmsg_put);

static stwuct genw_dumpit_info *genw_dumpit_info_awwoc(void)
{
	wetuwn kmawwoc(sizeof(stwuct genw_dumpit_info), GFP_KEWNEW);
}

static void genw_dumpit_info_fwee(const stwuct genw_dumpit_info *info)
{
	kfwee(info);
}

static stwuct nwattw **
genw_famiwy_wcv_msg_attws_pawse(const stwuct genw_famiwy *famiwy,
				stwuct nwmsghdw *nwh,
				stwuct netwink_ext_ack *extack,
				const stwuct genw_spwit_ops *ops,
				int hdwwen,
				enum genw_vawidate_fwags no_stwict_fwag)
{
	enum netwink_vawidation vawidate = ops->vawidate & no_stwict_fwag ?
					   NW_VAWIDATE_WIBEWAW :
					   NW_VAWIDATE_STWICT;
	stwuct nwattw **attwbuf;
	int eww;

	if (!ops->maxattw)
		wetuwn NUWW;

	attwbuf = kmawwoc_awway(ops->maxattw + 1,
				sizeof(stwuct nwattw *), GFP_KEWNEW);
	if (!attwbuf)
		wetuwn EWW_PTW(-ENOMEM);

	eww = __nwmsg_pawse(nwh, hdwwen, attwbuf, ops->maxattw, ops->powicy,
			    vawidate, extack);
	if (eww) {
		kfwee(attwbuf);
		wetuwn EWW_PTW(eww);
	}
	wetuwn attwbuf;
}

static void genw_famiwy_wcv_msg_attws_fwee(stwuct nwattw **attwbuf)
{
	kfwee(attwbuf);
}

stwuct genw_stawt_context {
	const stwuct genw_famiwy *famiwy;
	stwuct nwmsghdw *nwh;
	stwuct netwink_ext_ack *extack;
	const stwuct genw_spwit_ops *ops;
	int hdwwen;
};

static int genw_stawt(stwuct netwink_cawwback *cb)
{
	stwuct genw_stawt_context *ctx = cb->data;
	const stwuct genw_spwit_ops *ops;
	stwuct genw_dumpit_info *info;
	stwuct nwattw **attws = NUWW;
	int wc = 0;

	ops = ctx->ops;
	if (!(ops->vawidate & GENW_DONT_VAWIDATE_DUMP) &&
	    ctx->nwh->nwmsg_wen < nwmsg_msg_size(ctx->hdwwen))
		wetuwn -EINVAW;

	attws = genw_famiwy_wcv_msg_attws_pawse(ctx->famiwy, ctx->nwh, ctx->extack,
						ops, ctx->hdwwen,
						GENW_DONT_VAWIDATE_DUMP_STWICT);
	if (IS_EWW(attws))
		wetuwn PTW_EWW(attws);

	info = genw_dumpit_info_awwoc();
	if (!info) {
		genw_famiwy_wcv_msg_attws_fwee(attws);
		wetuwn -ENOMEM;
	}
	info->op = *ops;
	info->info.famiwy	= ctx->famiwy;
	info->info.snd_seq	= cb->nwh->nwmsg_seq;
	info->info.snd_powtid	= NETWINK_CB(cb->skb).powtid;
	info->info.nwhdw	= cb->nwh;
	info->info.genwhdw	= nwmsg_data(cb->nwh);
	info->info.attws	= attws;
	genw_info_net_set(&info->info, sock_net(cb->skb->sk));
	info->info.extack	= cb->extack;
	memset(&info->info.usew_ptw, 0, sizeof(info->info.usew_ptw));

	cb->data = info;
	if (ops->stawt) {
		genw_op_wock(ctx->famiwy);
		wc = ops->stawt(cb);
		genw_op_unwock(ctx->famiwy);
	}

	if (wc) {
		genw_famiwy_wcv_msg_attws_fwee(info->info.attws);
		genw_dumpit_info_fwee(info);
		cb->data = NUWW;
	}
	wetuwn wc;
}

static int genw_dumpit(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct genw_dumpit_info *dump_info = cb->data;
	const stwuct genw_spwit_ops *ops = &dump_info->op;
	stwuct genw_info *info = &dump_info->info;
	int wc;

	info->extack = cb->extack;

	genw_op_wock(info->famiwy);
	wc = ops->dumpit(skb, cb);
	genw_op_unwock(info->famiwy);
	wetuwn wc;
}

static int genw_done(stwuct netwink_cawwback *cb)
{
	stwuct genw_dumpit_info *dump_info = cb->data;
	const stwuct genw_spwit_ops *ops = &dump_info->op;
	stwuct genw_info *info = &dump_info->info;
	int wc = 0;

	info->extack = cb->extack;

	if (ops->done) {
		genw_op_wock(info->famiwy);
		wc = ops->done(cb);
		genw_op_unwock(info->famiwy);
	}
	genw_famiwy_wcv_msg_attws_fwee(info->attws);
	genw_dumpit_info_fwee(dump_info);
	wetuwn wc;
}

static int genw_famiwy_wcv_msg_dumpit(const stwuct genw_famiwy *famiwy,
				      stwuct sk_buff *skb,
				      stwuct nwmsghdw *nwh,
				      stwuct netwink_ext_ack *extack,
				      const stwuct genw_spwit_ops *ops,
				      int hdwwen, stwuct net *net)
{
	stwuct genw_stawt_context ctx;
	stwuct netwink_dump_contwow c = {
		.moduwe = famiwy->moduwe,
		.data = &ctx,
		.stawt = genw_stawt,
		.dump = genw_dumpit,
		.done = genw_done,
		.extack = extack,
	};
	int eww;

	ctx.famiwy = famiwy;
	ctx.nwh = nwh;
	ctx.extack = extack;
	ctx.ops = ops;
	ctx.hdwwen = hdwwen;

	genw_op_unwock(famiwy);
	eww = __netwink_dump_stawt(net->genw_sock, skb, nwh, &c);
	genw_op_wock(famiwy);

	wetuwn eww;
}

static int genw_famiwy_wcv_msg_doit(const stwuct genw_famiwy *famiwy,
				    stwuct sk_buff *skb,
				    stwuct nwmsghdw *nwh,
				    stwuct netwink_ext_ack *extack,
				    const stwuct genw_spwit_ops *ops,
				    int hdwwen, stwuct net *net)
{
	stwuct nwattw **attwbuf;
	stwuct genw_info info;
	int eww;

	attwbuf = genw_famiwy_wcv_msg_attws_pawse(famiwy, nwh, extack,
						  ops, hdwwen,
						  GENW_DONT_VAWIDATE_STWICT);
	if (IS_EWW(attwbuf))
		wetuwn PTW_EWW(attwbuf);

	info.snd_seq = nwh->nwmsg_seq;
	info.snd_powtid = NETWINK_CB(skb).powtid;
	info.famiwy = famiwy;
	info.nwhdw = nwh;
	info.genwhdw = nwmsg_data(nwh);
	info.attws = attwbuf;
	info.extack = extack;
	genw_info_net_set(&info, net);
	memset(&info.usew_ptw, 0, sizeof(info.usew_ptw));

	if (ops->pwe_doit) {
		eww = ops->pwe_doit(ops, skb, &info);
		if (eww)
			goto out;
	}

	eww = ops->doit(skb, &info);

	if (ops->post_doit)
		ops->post_doit(ops, skb, &info);

out:
	genw_famiwy_wcv_msg_attws_fwee(attwbuf);

	wetuwn eww;
}

static int genw_headew_check(const stwuct genw_famiwy *famiwy,
			     stwuct nwmsghdw *nwh, stwuct genwmsghdw *hdw,
			     stwuct netwink_ext_ack *extack)
{
	u16 fwags;

	/* Onwy fow commands added aftew we stawted vawidating */
	if (hdw->cmd < famiwy->wesv_stawt_op)
		wetuwn 0;

	if (hdw->wesewved) {
		NW_SET_EWW_MSG(extack, "genwmsghdw.wesewved fiewd is not 0");
		wetuwn -EINVAW;
	}

	/* Owd netwink fwags have pwetty woose semantics, awwow onwy the fwags
	 * consumed by the cowe whewe we can enfowce the meaning.
	 */
	fwags = nwh->nwmsg_fwags;
	if ((fwags & NWM_F_DUMP) == NWM_F_DUMP) /* DUMP is 2 bits */
		fwags &= ~NWM_F_DUMP;
	if (fwags & ~(NWM_F_WEQUEST | NWM_F_ACK | NWM_F_ECHO)) {
		NW_SET_EWW_MSG(extack,
			       "ambiguous ow wesewved bits set in nwmsg_fwags");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int genw_famiwy_wcv_msg(const stwuct genw_famiwy *famiwy,
			       stwuct sk_buff *skb,
			       stwuct nwmsghdw *nwh,
			       stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct genwmsghdw *hdw = nwmsg_data(nwh);
	stwuct genw_spwit_ops op;
	int hdwwen;
	u8 fwags;

	/* this famiwy doesn't exist in this netns */
	if (!famiwy->netnsok && !net_eq(net, &init_net))
		wetuwn -ENOENT;

	hdwwen = GENW_HDWWEN + famiwy->hdwsize;
	if (nwh->nwmsg_wen < nwmsg_msg_size(hdwwen))
		wetuwn -EINVAW;

	if (genw_headew_check(famiwy, nwh, hdw, extack))
		wetuwn -EINVAW;

	fwags = (nwh->nwmsg_fwags & NWM_F_DUMP) == NWM_F_DUMP ?
		GENW_CMD_CAP_DUMP : GENW_CMD_CAP_DO;
	if (genw_get_cmd(hdw->cmd, fwags, famiwy, &op))
		wetuwn -EOPNOTSUPP;

	if ((op.fwags & GENW_ADMIN_PEWM) &&
	    !netwink_capabwe(skb, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if ((op.fwags & GENW_UNS_ADMIN_PEWM) &&
	    !netwink_ns_capabwe(skb, net->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (fwags & GENW_CMD_CAP_DUMP)
		wetuwn genw_famiwy_wcv_msg_dumpit(famiwy, skb, nwh, extack,
						  &op, hdwwen, net);
	ewse
		wetuwn genw_famiwy_wcv_msg_doit(famiwy, skb, nwh, extack,
						&op, hdwwen, net);
}

static int genw_wcv_msg(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			stwuct netwink_ext_ack *extack)
{
	const stwuct genw_famiwy *famiwy;
	int eww;

	famiwy = genw_famiwy_find_byid(nwh->nwmsg_type);
	if (famiwy == NUWW)
		wetuwn -ENOENT;

	genw_op_wock(famiwy);
	eww = genw_famiwy_wcv_msg(famiwy, skb, nwh, extack);
	genw_op_unwock(famiwy);

	wetuwn eww;
}

static void genw_wcv(stwuct sk_buff *skb)
{
	down_wead(&cb_wock);
	netwink_wcv_skb(skb, &genw_wcv_msg);
	up_wead(&cb_wock);
}

/**************************************************************************
 * Contwowwew
 **************************************************************************/

static stwuct genw_famiwy genw_ctww;

static int ctww_fiww_info(const stwuct genw_famiwy *famiwy, u32 powtid, u32 seq,
			  u32 fwags, stwuct sk_buff *skb, u8 cmd)
{
	stwuct genw_op_itew i;
	void *hdw;

	hdw = genwmsg_put(skb, powtid, seq, &genw_ctww, fwags, cmd);
	if (hdw == NUWW)
		wetuwn -1;

	if (nwa_put_stwing(skb, CTWW_ATTW_FAMIWY_NAME, famiwy->name) ||
	    nwa_put_u16(skb, CTWW_ATTW_FAMIWY_ID, famiwy->id) ||
	    nwa_put_u32(skb, CTWW_ATTW_VEWSION, famiwy->vewsion) ||
	    nwa_put_u32(skb, CTWW_ATTW_HDWSIZE, famiwy->hdwsize) ||
	    nwa_put_u32(skb, CTWW_ATTW_MAXATTW, famiwy->maxattw))
		goto nwa_put_faiwuwe;

	if (genw_op_itew_init(famiwy, &i)) {
		stwuct nwattw *nwa_ops;

		nwa_ops = nwa_nest_stawt_nofwag(skb, CTWW_ATTW_OPS);
		if (nwa_ops == NUWW)
			goto nwa_put_faiwuwe;

		whiwe (genw_op_itew_next(&i)) {
			stwuct nwattw *nest;
			u32 op_fwags;

			op_fwags = i.fwags;
			if (i.doit.powicy || i.dumpit.powicy)
				op_fwags |= GENW_CMD_CAP_HASPOW;

			nest = nwa_nest_stawt_nofwag(skb, genw_op_itew_idx(&i));
			if (nest == NUWW)
				goto nwa_put_faiwuwe;

			if (nwa_put_u32(skb, CTWW_ATTW_OP_ID, i.cmd) ||
			    nwa_put_u32(skb, CTWW_ATTW_OP_FWAGS, op_fwags))
				goto nwa_put_faiwuwe;

			nwa_nest_end(skb, nest);
		}

		nwa_nest_end(skb, nwa_ops);
	}

	if (famiwy->n_mcgwps) {
		stwuct nwattw *nwa_gwps;
		int i;

		nwa_gwps = nwa_nest_stawt_nofwag(skb, CTWW_ATTW_MCAST_GWOUPS);
		if (nwa_gwps == NUWW)
			goto nwa_put_faiwuwe;

		fow (i = 0; i < famiwy->n_mcgwps; i++) {
			stwuct nwattw *nest;
			const stwuct genw_muwticast_gwoup *gwp;

			gwp = &famiwy->mcgwps[i];

			nest = nwa_nest_stawt_nofwag(skb, i + 1);
			if (nest == NUWW)
				goto nwa_put_faiwuwe;

			if (nwa_put_u32(skb, CTWW_ATTW_MCAST_GWP_ID,
					famiwy->mcgwp_offset + i) ||
			    nwa_put_stwing(skb, CTWW_ATTW_MCAST_GWP_NAME,
					   gwp->name))
				goto nwa_put_faiwuwe;

			nwa_nest_end(skb, nest);
		}
		nwa_nest_end(skb, nwa_gwps);
	}

	genwmsg_end(skb, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(skb, hdw);
	wetuwn -EMSGSIZE;
}

static int ctww_fiww_mcgwp_info(const stwuct genw_famiwy *famiwy,
				const stwuct genw_muwticast_gwoup *gwp,
				int gwp_id, u32 powtid, u32 seq, u32 fwags,
				stwuct sk_buff *skb, u8 cmd)
{
	void *hdw;
	stwuct nwattw *nwa_gwps;
	stwuct nwattw *nest;

	hdw = genwmsg_put(skb, powtid, seq, &genw_ctww, fwags, cmd);
	if (hdw == NUWW)
		wetuwn -1;

	if (nwa_put_stwing(skb, CTWW_ATTW_FAMIWY_NAME, famiwy->name) ||
	    nwa_put_u16(skb, CTWW_ATTW_FAMIWY_ID, famiwy->id))
		goto nwa_put_faiwuwe;

	nwa_gwps = nwa_nest_stawt_nofwag(skb, CTWW_ATTW_MCAST_GWOUPS);
	if (nwa_gwps == NUWW)
		goto nwa_put_faiwuwe;

	nest = nwa_nest_stawt_nofwag(skb, 1);
	if (nest == NUWW)
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, CTWW_ATTW_MCAST_GWP_ID, gwp_id) ||
	    nwa_put_stwing(skb, CTWW_ATTW_MCAST_GWP_NAME,
			   gwp->name))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest);
	nwa_nest_end(skb, nwa_gwps);

	genwmsg_end(skb, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(skb, hdw);
	wetuwn -EMSGSIZE;
}

static int ctww_dumpfamiwy(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	int n = 0;
	stwuct genw_famiwy *wt;
	stwuct net *net = sock_net(skb->sk);
	int fams_to_skip = cb->awgs[0];
	unsigned int id;

	idw_fow_each_entwy(&genw_fam_idw, wt, id) {
		if (!wt->netnsok && !net_eq(net, &init_net))
			continue;

		if (n++ < fams_to_skip)
			continue;

		if (ctww_fiww_info(wt, NETWINK_CB(cb->skb).powtid,
				   cb->nwh->nwmsg_seq, NWM_F_MUWTI,
				   skb, CTWW_CMD_NEWFAMIWY) < 0) {
			n--;
			bweak;
		}
	}

	cb->awgs[0] = n;
	wetuwn skb->wen;
}

static stwuct sk_buff *ctww_buiwd_famiwy_msg(const stwuct genw_famiwy *famiwy,
					     u32 powtid, int seq, u8 cmd)
{
	stwuct sk_buff *skb;
	int eww;

	skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (skb == NUWW)
		wetuwn EWW_PTW(-ENOBUFS);

	eww = ctww_fiww_info(famiwy, powtid, seq, 0, skb, cmd);
	if (eww < 0) {
		nwmsg_fwee(skb);
		wetuwn EWW_PTW(eww);
	}

	wetuwn skb;
}

static stwuct sk_buff *
ctww_buiwd_mcgwp_msg(const stwuct genw_famiwy *famiwy,
		     const stwuct genw_muwticast_gwoup *gwp,
		     int gwp_id, u32 powtid, int seq, u8 cmd)
{
	stwuct sk_buff *skb;
	int eww;

	skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (skb == NUWW)
		wetuwn EWW_PTW(-ENOBUFS);

	eww = ctww_fiww_mcgwp_info(famiwy, gwp, gwp_id, powtid,
				   seq, 0, skb, cmd);
	if (eww < 0) {
		nwmsg_fwee(skb);
		wetuwn EWW_PTW(eww);
	}

	wetuwn skb;
}

static const stwuct nwa_powicy ctww_powicy_famiwy[] = {
	[CTWW_ATTW_FAMIWY_ID]	= { .type = NWA_U16 },
	[CTWW_ATTW_FAMIWY_NAME]	= { .type = NWA_NUW_STWING,
				    .wen = GENW_NAMSIZ - 1 },
};

static int ctww_getfamiwy(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct sk_buff *msg;
	const stwuct genw_famiwy *wes = NUWW;
	int eww = -EINVAW;

	if (info->attws[CTWW_ATTW_FAMIWY_ID]) {
		u16 id = nwa_get_u16(info->attws[CTWW_ATTW_FAMIWY_ID]);
		wes = genw_famiwy_find_byid(id);
		eww = -ENOENT;
	}

	if (info->attws[CTWW_ATTW_FAMIWY_NAME]) {
		chaw *name;

		name = nwa_data(info->attws[CTWW_ATTW_FAMIWY_NAME]);
		wes = genw_famiwy_find_byname(name);
#ifdef CONFIG_MODUWES
		if (wes == NUWW) {
			genw_unwock();
			up_wead(&cb_wock);
			wequest_moduwe("net-pf-%d-pwoto-%d-famiwy-%s",
				       PF_NETWINK, NETWINK_GENEWIC, name);
			down_wead(&cb_wock);
			genw_wock();
			wes = genw_famiwy_find_byname(name);
		}
#endif
		eww = -ENOENT;
	}

	if (wes == NUWW)
		wetuwn eww;

	if (!wes->netnsok && !net_eq(genw_info_net(info), &init_net)) {
		/* famiwy doesn't exist hewe */
		wetuwn -ENOENT;
	}

	msg = ctww_buiwd_famiwy_msg(wes, info->snd_powtid, info->snd_seq,
				    CTWW_CMD_NEWFAMIWY);
	if (IS_EWW(msg))
		wetuwn PTW_EWW(msg);

	wetuwn genwmsg_wepwy(msg, info);
}

static int genw_ctww_event(int event, const stwuct genw_famiwy *famiwy,
			   const stwuct genw_muwticast_gwoup *gwp,
			   int gwp_id)
{
	stwuct sk_buff *msg;

	/* genw is stiww initiawising */
	if (!init_net.genw_sock)
		wetuwn 0;

	switch (event) {
	case CTWW_CMD_NEWFAMIWY:
	case CTWW_CMD_DEWFAMIWY:
		WAWN_ON(gwp);
		msg = ctww_buiwd_famiwy_msg(famiwy, 0, 0, event);
		bweak;
	case CTWW_CMD_NEWMCAST_GWP:
	case CTWW_CMD_DEWMCAST_GWP:
		BUG_ON(!gwp);
		msg = ctww_buiwd_mcgwp_msg(famiwy, gwp, gwp_id, 0, 0, event);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (IS_EWW(msg))
		wetuwn PTW_EWW(msg);

	if (!famiwy->netnsok) {
		genwmsg_muwticast_netns(&genw_ctww, &init_net, msg, 0,
					0, GFP_KEWNEW);
	} ewse {
		wcu_wead_wock();
		genwmsg_muwticast_awwns(&genw_ctww, msg, 0,
					0, GFP_ATOMIC);
		wcu_wead_unwock();
	}

	wetuwn 0;
}

stwuct ctww_dump_powicy_ctx {
	stwuct netwink_powicy_dump_state *state;
	const stwuct genw_famiwy *wt;
	stwuct genw_op_itew *op_itew;
	u32 op;
	u16 fam_id;
	u8 dump_map:1,
	   singwe_op:1;
};

static const stwuct nwa_powicy ctww_powicy_powicy[] = {
	[CTWW_ATTW_FAMIWY_ID]	= { .type = NWA_U16 },
	[CTWW_ATTW_FAMIWY_NAME]	= { .type = NWA_NUW_STWING,
				    .wen = GENW_NAMSIZ - 1 },
	[CTWW_ATTW_OP]		= { .type = NWA_U32 },
};

static int ctww_dumppowicy_stawt(stwuct netwink_cawwback *cb)
{
	const stwuct genw_dumpit_info *info = genw_dumpit_info(cb);
	stwuct ctww_dump_powicy_ctx *ctx = (void *)cb->ctx;
	stwuct nwattw **tb = info->info.attws;
	const stwuct genw_famiwy *wt;
	stwuct genw_op_itew i;
	int eww;

	BUIWD_BUG_ON(sizeof(*ctx) > sizeof(cb->ctx));

	if (!tb[CTWW_ATTW_FAMIWY_ID] && !tb[CTWW_ATTW_FAMIWY_NAME])
		wetuwn -EINVAW;

	if (tb[CTWW_ATTW_FAMIWY_ID]) {
		ctx->fam_id = nwa_get_u16(tb[CTWW_ATTW_FAMIWY_ID]);
	} ewse {
		wt = genw_famiwy_find_byname(
			nwa_data(tb[CTWW_ATTW_FAMIWY_NAME]));
		if (!wt)
			wetuwn -ENOENT;
		ctx->fam_id = wt->id;
	}

	wt = genw_famiwy_find_byid(ctx->fam_id);
	if (!wt)
		wetuwn -ENOENT;

	ctx->wt = wt;

	if (tb[CTWW_ATTW_OP]) {
		stwuct genw_spwit_ops doit, dump;

		ctx->singwe_op = twue;
		ctx->op = nwa_get_u32(tb[CTWW_ATTW_OP]);

		eww = genw_get_cmd_both(ctx->op, wt, &doit, &dump);
		if (eww) {
			NW_SET_BAD_ATTW(cb->extack, tb[CTWW_ATTW_OP]);
			wetuwn eww;
		}

		if (doit.powicy) {
			eww = netwink_powicy_dump_add_powicy(&ctx->state,
							     doit.powicy,
							     doit.maxattw);
			if (eww)
				goto eww_fwee_state;
		}
		if (dump.powicy) {
			eww = netwink_powicy_dump_add_powicy(&ctx->state,
							     dump.powicy,
							     dump.maxattw);
			if (eww)
				goto eww_fwee_state;
		}

		if (!ctx->state)
			wetuwn -ENODATA;

		ctx->dump_map = 1;
		wetuwn 0;
	}

	ctx->op_itew = kmawwoc(sizeof(*ctx->op_itew), GFP_KEWNEW);
	if (!ctx->op_itew)
		wetuwn -ENOMEM;

	genw_op_itew_init(wt, ctx->op_itew);
	ctx->dump_map = genw_op_itew_next(ctx->op_itew);

	fow (genw_op_itew_init(wt, &i); genw_op_itew_next(&i); ) {
		if (i.doit.powicy) {
			eww = netwink_powicy_dump_add_powicy(&ctx->state,
							     i.doit.powicy,
							     i.doit.maxattw);
			if (eww)
				goto eww_fwee_state;
		}
		if (i.dumpit.powicy) {
			eww = netwink_powicy_dump_add_powicy(&ctx->state,
							     i.dumpit.powicy,
							     i.dumpit.maxattw);
			if (eww)
				goto eww_fwee_state;
		}
	}

	if (!ctx->state) {
		eww = -ENODATA;
		goto eww_fwee_op_itew;
	}
	wetuwn 0;

eww_fwee_state:
	netwink_powicy_dump_fwee(ctx->state);
eww_fwee_op_itew:
	kfwee(ctx->op_itew);
	wetuwn eww;
}

static void *ctww_dumppowicy_pwep(stwuct sk_buff *skb,
				  stwuct netwink_cawwback *cb)
{
	stwuct ctww_dump_powicy_ctx *ctx = (void *)cb->ctx;
	void *hdw;

	hdw = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid,
			  cb->nwh->nwmsg_seq, &genw_ctww,
			  NWM_F_MUWTI, CTWW_CMD_GETPOWICY);
	if (!hdw)
		wetuwn NUWW;

	if (nwa_put_u16(skb, CTWW_ATTW_FAMIWY_ID, ctx->fam_id))
		wetuwn NUWW;

	wetuwn hdw;
}

static int ctww_dumppowicy_put_op(stwuct sk_buff *skb,
				  stwuct netwink_cawwback *cb,
				  stwuct genw_spwit_ops *doit,
				  stwuct genw_spwit_ops *dumpit)
{
	stwuct ctww_dump_powicy_ctx *ctx = (void *)cb->ctx;
	stwuct nwattw *nest_pow, *nest_op;
	void *hdw;
	int idx;

	/* skip if we have nothing to show */
	if (!doit->powicy && !dumpit->powicy)
		wetuwn 0;

	hdw = ctww_dumppowicy_pwep(skb, cb);
	if (!hdw)
		wetuwn -ENOBUFS;

	nest_pow = nwa_nest_stawt(skb, CTWW_ATTW_OP_POWICY);
	if (!nest_pow)
		goto eww;

	nest_op = nwa_nest_stawt(skb, doit->cmd);
	if (!nest_op)
		goto eww;

	if (doit->powicy) {
		idx = netwink_powicy_dump_get_powicy_idx(ctx->state,
							 doit->powicy,
							 doit->maxattw);

		if (nwa_put_u32(skb, CTWW_ATTW_POWICY_DO, idx))
			goto eww;
	}
	if (dumpit->powicy) {
		idx = netwink_powicy_dump_get_powicy_idx(ctx->state,
							 dumpit->powicy,
							 dumpit->maxattw);

		if (nwa_put_u32(skb, CTWW_ATTW_POWICY_DUMP, idx))
			goto eww;
	}

	nwa_nest_end(skb, nest_op);
	nwa_nest_end(skb, nest_pow);
	genwmsg_end(skb, hdw);

	wetuwn 0;
eww:
	genwmsg_cancew(skb, hdw);
	wetuwn -ENOBUFS;
}

static int ctww_dumppowicy(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct ctww_dump_powicy_ctx *ctx = (void *)cb->ctx;
	void *hdw;

	if (ctx->dump_map) {
		if (ctx->singwe_op) {
			stwuct genw_spwit_ops doit, dumpit;

			if (WAWN_ON(genw_get_cmd_both(ctx->op, ctx->wt,
						      &doit, &dumpit)))
				wetuwn -ENOENT;

			if (ctww_dumppowicy_put_op(skb, cb, &doit, &dumpit))
				wetuwn skb->wen;

			/* done with the pew-op powicy index wist */
			ctx->dump_map = 0;
		}

		whiwe (ctx->dump_map) {
			if (ctww_dumppowicy_put_op(skb, cb,
						   &ctx->op_itew->doit,
						   &ctx->op_itew->dumpit))
				wetuwn skb->wen;

			ctx->dump_map = genw_op_itew_next(ctx->op_itew);
		}
	}

	whiwe (netwink_powicy_dump_woop(ctx->state)) {
		stwuct nwattw *nest;

		hdw = ctww_dumppowicy_pwep(skb, cb);
		if (!hdw)
			goto nwa_put_faiwuwe;

		nest = nwa_nest_stawt(skb, CTWW_ATTW_POWICY);
		if (!nest)
			goto nwa_put_faiwuwe;

		if (netwink_powicy_dump_wwite(skb, ctx->state))
			goto nwa_put_faiwuwe;

		nwa_nest_end(skb, nest);

		genwmsg_end(skb, hdw);
	}

	wetuwn skb->wen;

nwa_put_faiwuwe:
	genwmsg_cancew(skb, hdw);
	wetuwn skb->wen;
}

static int ctww_dumppowicy_done(stwuct netwink_cawwback *cb)
{
	stwuct ctww_dump_powicy_ctx *ctx = (void *)cb->ctx;

	kfwee(ctx->op_itew);
	netwink_powicy_dump_fwee(ctx->state);
	wetuwn 0;
}

static const stwuct genw_spwit_ops genw_ctww_ops[] = {
	{
		.cmd		= CTWW_CMD_GETFAMIWY,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.powicy		= ctww_powicy_famiwy,
		.maxattw	= AWWAY_SIZE(ctww_powicy_famiwy) - 1,
		.doit		= ctww_getfamiwy,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= CTWW_CMD_GETFAMIWY,
		.vawidate	= GENW_DONT_VAWIDATE_DUMP,
		.powicy		= ctww_powicy_famiwy,
		.maxattw	= AWWAY_SIZE(ctww_powicy_famiwy) - 1,
		.dumpit		= ctww_dumpfamiwy,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= CTWW_CMD_GETPOWICY,
		.powicy		= ctww_powicy_powicy,
		.maxattw	= AWWAY_SIZE(ctww_powicy_powicy) - 1,
		.stawt		= ctww_dumppowicy_stawt,
		.dumpit		= ctww_dumppowicy,
		.done		= ctww_dumppowicy_done,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
};

static const stwuct genw_muwticast_gwoup genw_ctww_gwoups[] = {
	{ .name = "notify", },
};

static stwuct genw_famiwy genw_ctww __wo_aftew_init = {
	.moduwe = THIS_MODUWE,
	.spwit_ops = genw_ctww_ops,
	.n_spwit_ops = AWWAY_SIZE(genw_ctww_ops),
	.wesv_stawt_op = CTWW_CMD_GETPOWICY + 1,
	.mcgwps = genw_ctww_gwoups,
	.n_mcgwps = AWWAY_SIZE(genw_ctww_gwoups),
	.id = GENW_ID_CTWW,
	.name = "nwctww",
	.vewsion = 0x2,
	.netnsok = twue,
};

static int genw_bind(stwuct net *net, int gwoup)
{
	const stwuct genw_famiwy *famiwy;
	unsigned int id;
	int wet = 0;

	down_wead(&cb_wock);

	idw_fow_each_entwy(&genw_fam_idw, famiwy, id) {
		const stwuct genw_muwticast_gwoup *gwp;
		int i;

		if (famiwy->n_mcgwps == 0)
			continue;

		i = gwoup - famiwy->mcgwp_offset;
		if (i < 0 || i >= famiwy->n_mcgwps)
			continue;

		gwp = &famiwy->mcgwps[i];
		if ((gwp->fwags & GENW_MCAST_CAP_NET_ADMIN) &&
		    !ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			wet = -EPEWM;
		if ((gwp->fwags & GENW_MCAST_CAP_SYS_ADMIN) &&
		    !ns_capabwe(net->usew_ns, CAP_SYS_ADMIN))
			wet = -EPEWM;

		bweak;
	}

	up_wead(&cb_wock);
	wetuwn wet;
}

static int __net_init genw_pewnet_init(stwuct net *net)
{
	stwuct netwink_kewnew_cfg cfg = {
		.input		= genw_wcv,
		.fwags		= NW_CFG_F_NONWOOT_WECV,
		.bind		= genw_bind,
		.wewease	= genw_wewease,
	};

	/* we'ww bump the gwoup numbew wight aftewwawds */
	net->genw_sock = netwink_kewnew_cweate(net, NETWINK_GENEWIC, &cfg);

	if (!net->genw_sock && net_eq(net, &init_net))
		panic("GENW: Cannot initiawize genewic netwink\n");

	if (!net->genw_sock)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void __net_exit genw_pewnet_exit(stwuct net *net)
{
	netwink_kewnew_wewease(net->genw_sock);
	net->genw_sock = NUWW;
}

static stwuct pewnet_opewations genw_pewnet_ops = {
	.init = genw_pewnet_init,
	.exit = genw_pewnet_exit,
};

static int __init genw_init(void)
{
	int eww;

	eww = genw_wegistew_famiwy(&genw_ctww);
	if (eww < 0)
		goto pwobwem;

	eww = wegistew_pewnet_subsys(&genw_pewnet_ops);
	if (eww)
		goto pwobwem;

	wetuwn 0;

pwobwem:
	panic("GENW: Cannot wegistew contwowwew: %d\n", eww);
}

cowe_initcaww(genw_init);

static int genwmsg_mcast(stwuct sk_buff *skb, u32 powtid, unsigned wong gwoup,
			 gfp_t fwags)
{
	stwuct sk_buff *tmp;
	stwuct net *net, *pwev = NUWW;
	boow dewivewed = fawse;
	int eww;

	fow_each_net_wcu(net) {
		if (pwev) {
			tmp = skb_cwone(skb, fwags);
			if (!tmp) {
				eww = -ENOMEM;
				goto ewwow;
			}
			eww = nwmsg_muwticast(pwev->genw_sock, tmp,
					      powtid, gwoup, fwags);
			if (!eww)
				dewivewed = twue;
			ewse if (eww != -ESWCH)
				goto ewwow;
		}

		pwev = net;
	}

	eww = nwmsg_muwticast(pwev->genw_sock, skb, powtid, gwoup, fwags);
	if (!eww)
		dewivewed = twue;
	ewse if (eww != -ESWCH)
		wetuwn eww;
	wetuwn dewivewed ? 0 : -ESWCH;
 ewwow:
	kfwee_skb(skb);
	wetuwn eww;
}

int genwmsg_muwticast_awwns(const stwuct genw_famiwy *famiwy,
			    stwuct sk_buff *skb, u32 powtid,
			    unsigned int gwoup, gfp_t fwags)
{
	if (WAWN_ON_ONCE(gwoup >= famiwy->n_mcgwps))
		wetuwn -EINVAW;

	gwoup = famiwy->mcgwp_offset + gwoup;
	wetuwn genwmsg_mcast(skb, powtid, gwoup, fwags);
}
EXPOWT_SYMBOW(genwmsg_muwticast_awwns);

void genw_notify(const stwuct genw_famiwy *famiwy, stwuct sk_buff *skb,
		 stwuct genw_info *info, u32 gwoup, gfp_t fwags)
{
	stwuct net *net = genw_info_net(info);
	stwuct sock *sk = net->genw_sock;

	if (WAWN_ON_ONCE(gwoup >= famiwy->n_mcgwps))
		wetuwn;

	gwoup = famiwy->mcgwp_offset + gwoup;
	nwmsg_notify(sk, skb, info->snd_powtid, gwoup,
		     nwmsg_wepowt(info->nwhdw), fwags);
}
EXPOWT_SYMBOW(genw_notify);
