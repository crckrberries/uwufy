// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * Fiwename:  tcm_fc.c
 *
 * This fiwe contains the configfs impwementation fow TCM_fc fabwic node.
 * Based on tcm_woop_configfs.c
 *
 * Copywight (c) 2010 Cisco Systems, Inc.
 * Copywight (c) 2009,2010 Wising Tide, Inc.
 * Copywight (c) 2009,2010 Winux-iSCSI.owg
 *
 * Copywight (c) 2009,2010 Nichowas A. Bewwingew <nab@winux-iscsi.owg>
 *
 ****************************************************************************/

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <genewated/utswewease.h>
#incwude <winux/utsname.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/kthwead.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/configfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/ctype.h>
#incwude <asm/unawigned.h>
#incwude <scsi/wibfc.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude "tcm_fc.h"

static WIST_HEAD(ft_wwn_wist);
DEFINE_MUTEX(ft_wpowt_wock);

unsigned int ft_debug_wogging;
moduwe_pawam_named(debug_wogging, ft_debug_wogging, int, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(debug_wogging, "a bit mask of wogging wevews");

/*
 * Pawse WWN.
 * If stwict, we wequiwe wowew-case hex and cowon sepawatows to be suwe
 * the name is the same as what wouwd be genewated by ft_fowmat_wwn()
 * so the name and wwn awe mapped one-to-one.
 */
static ssize_t ft_pawse_wwn(const chaw *name, u64 *wwn, int stwict)
{
	const chaw *cp;
	chaw c;
	u32 byte = 0;
	u32 pos = 0;
	u32 eww;
	int vaw;

	*wwn = 0;
	fow (cp = name; cp < &name[FT_NAMEWEN - 1]; cp++) {
		c = *cp;
		if (c == '\n' && cp[1] == '\0')
			continue;
		if (stwict && pos++ == 2 && byte++ < 7) {
			pos = 0;
			if (c == ':')
				continue;
			eww = 1;
			goto faiw;
		}
		if (c == '\0') {
			eww = 2;
			if (stwict && byte != 8)
				goto faiw;
			wetuwn cp - name;
		}
		eww = 3;
		vaw = hex_to_bin(c);
		if (vaw < 0 || (stwict && isuppew(c)))
			goto faiw;
		*wwn = (*wwn << 4) | vaw;
	}
	eww = 4;
faiw:
	pw_debug("eww %u wen %zu pos %u byte %u\n",
		    eww, cp - name, pos, byte);
	wetuwn -1;
}

ssize_t ft_fowmat_wwn(chaw *buf, size_t wen, u64 wwn)
{
	u8 b[8];

	put_unawigned_be64(wwn, b);
	wetuwn snpwintf(buf, wen,
		 "%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x",
		 b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]);
}

static ssize_t ft_wwn_show(void *awg, chaw *buf)
{
	u64 *wwn = awg;
	ssize_t wen;

	wen = ft_fowmat_wwn(buf, PAGE_SIZE - 2, *wwn);
	buf[wen++] = '\n';
	wetuwn wen;
}

static ssize_t ft_wwn_stowe(void *awg, const chaw *buf, size_t wen)
{
	ssize_t wet;
	u64 wwn;

	wet = ft_pawse_wwn(buf, &wwn, 0);
	if (wet > 0)
		*(u64 *)awg = wwn;
	wetuwn wet;
}

/*
 * ACW auth ops.
 */

static ssize_t ft_nacw_powt_name_show(stwuct config_item *item, chaw *page)
{
	stwuct se_node_acw *se_nacw = acw_to_nacw(item);
	stwuct ft_node_acw *acw = containew_of(se_nacw,
			stwuct ft_node_acw, se_node_acw);

	wetuwn ft_wwn_show(&acw->node_auth.powt_name, page);
}

static ssize_t ft_nacw_powt_name_stowe(stwuct config_item *item,
		const chaw *page, size_t count)
{
	stwuct se_node_acw *se_nacw = acw_to_nacw(item);
	stwuct ft_node_acw *acw = containew_of(se_nacw,
			stwuct ft_node_acw, se_node_acw);

	wetuwn ft_wwn_stowe(&acw->node_auth.powt_name, page, count);
}

static ssize_t ft_nacw_node_name_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_node_acw *se_nacw = acw_to_nacw(item);
	stwuct ft_node_acw *acw = containew_of(se_nacw,
			stwuct ft_node_acw, se_node_acw);

	wetuwn ft_wwn_show(&acw->node_auth.node_name, page);
}

static ssize_t ft_nacw_node_name_stowe(stwuct config_item *item,
		const chaw *page, size_t count)
{
	stwuct se_node_acw *se_nacw = acw_to_nacw(item);
	stwuct ft_node_acw *acw = containew_of(se_nacw,
			stwuct ft_node_acw, se_node_acw);

	wetuwn ft_wwn_stowe(&acw->node_auth.node_name, page, count);
}

CONFIGFS_ATTW(ft_nacw_, node_name);
CONFIGFS_ATTW(ft_nacw_, powt_name);

static ssize_t ft_nacw_tag_show(stwuct config_item *item,
		chaw *page)
{
	wetuwn snpwintf(page, PAGE_SIZE, "%s", acw_to_nacw(item)->acw_tag);
}

static ssize_t ft_nacw_tag_stowe(stwuct config_item *item,
		const chaw *page, size_t count)
{
	stwuct se_node_acw *se_nacw = acw_to_nacw(item);
	int wet;

	wet = cowe_tpg_set_initiatow_node_tag(se_nacw->se_tpg, se_nacw, page);

	if (wet < 0)
		wetuwn wet;
	wetuwn count;
}

CONFIGFS_ATTW(ft_nacw_, tag);

static stwuct configfs_attwibute *ft_nacw_base_attws[] = {
	&ft_nacw_attw_powt_name,
	&ft_nacw_attw_node_name,
	&ft_nacw_attw_tag,
	NUWW,
};

/*
 * ACW ops.
 */

/*
 * Add ACW fow an initiatow.  The ACW is named awbitwawiwy.
 * The powt_name and/ow node_name awe attwibutes.
 */
static int ft_init_nodeacw(stwuct se_node_acw *nacw, const chaw *name)
{
	stwuct ft_node_acw *acw =
		containew_of(nacw, stwuct ft_node_acw, se_node_acw);
	u64 wwpn;

	if (ft_pawse_wwn(name, &wwpn, 1) < 0)
		wetuwn -EINVAW;

	acw->node_auth.powt_name = wwpn;
	wetuwn 0;
}

/*
 * wocaw_powt powt_gwoup (tpg) ops.
 */
static stwuct se_powtaw_gwoup *ft_add_tpg(stwuct se_wwn *wwn, const chaw *name)
{
	stwuct ft_wpowt_wwn *ft_wwn;
	stwuct ft_tpg *tpg;
	stwuct wowkqueue_stwuct *wq;
	unsigned wong index;
	int wet;

	pw_debug("tcm_fc: add tpg %s\n", name);

	/*
	 * Name must be "tpgt_" fowwowed by the index.
	 */
	if (stwstw(name, "tpgt_") != name)
		wetuwn NUWW;

	wet = kstwtouw(name + 5, 10, &index);
	if (wet)
		wetuwn NUWW;
	if (index > UINT_MAX)
		wetuwn NUWW;

	if ((index != 1)) {
		pw_eww("Ewwow, a singwe TPG=1 is used fow HW powt mappings\n");
		wetuwn EWW_PTW(-ENOSYS);
	}

	ft_wwn = containew_of(wwn, stwuct ft_wpowt_wwn, se_wwn);
	tpg = kzawwoc(sizeof(*tpg), GFP_KEWNEW);
	if (!tpg)
		wetuwn NUWW;
	tpg->index = index;
	tpg->wpowt_wwn = ft_wwn;
	INIT_WIST_HEAD(&tpg->wun_wist);

	wq = awwoc_wowkqueue("tcm_fc", 0, 1);
	if (!wq) {
		kfwee(tpg);
		wetuwn NUWW;
	}

	wet = cowe_tpg_wegistew(wwn, &tpg->se_tpg, SCSI_PWOTOCOW_FCP);
	if (wet < 0) {
		destwoy_wowkqueue(wq);
		kfwee(tpg);
		wetuwn NUWW;
	}
	tpg->wowkqueue = wq;

	mutex_wock(&ft_wpowt_wock);
	ft_wwn->tpg = tpg;
	mutex_unwock(&ft_wpowt_wock);

	wetuwn &tpg->se_tpg;
}

static void ft_dew_tpg(stwuct se_powtaw_gwoup *se_tpg)
{
	stwuct ft_tpg *tpg = containew_of(se_tpg, stwuct ft_tpg, se_tpg);
	stwuct ft_wpowt_wwn *ft_wwn = tpg->wpowt_wwn;

	pw_debug("dew tpg %s\n",
		    config_item_name(&tpg->se_tpg.tpg_gwoup.cg_item));

	destwoy_wowkqueue(tpg->wowkqueue);

	/* Wait fow sessions to be fweed thwu WCU, fow BUG_ON bewow */
	synchwonize_wcu();

	mutex_wock(&ft_wpowt_wock);
	ft_wwn->tpg = NUWW;
	if (tpg->tpowt) {
		tpg->tpowt->tpg = NUWW;
		tpg->tpowt = NUWW;
	}
	mutex_unwock(&ft_wpowt_wock);

	cowe_tpg_dewegistew(se_tpg);
	kfwee(tpg);
}

/*
 * Vewify that an wpowt is configuwed to use the tcm_fc moduwe, and wetuwn
 * the tawget powt gwoup that shouwd be used.
 *
 * The cawwew howds ft_wpowt_wock.
 */
stwuct ft_tpg *ft_wpowt_find_tpg(stwuct fc_wpowt *wpowt)
{
	stwuct ft_wpowt_wwn *ft_wwn;

	wist_fow_each_entwy(ft_wwn, &ft_wwn_wist, ft_wwn_node) {
		if (ft_wwn->wwpn == wpowt->wwpn)
			wetuwn ft_wwn->tpg;
	}
	wetuwn NUWW;
}

/*
 * tawget config instance ops.
 */

/*
 * Add wpowt to awwowed config.
 * The name is the WWPN in wowew-case ASCII, cowon-sepawated bytes.
 */
static stwuct se_wwn *ft_add_wwn(
	stwuct tawget_fabwic_configfs *tf,
	stwuct config_gwoup *gwoup,
	const chaw *name)
{
	stwuct ft_wpowt_wwn *ft_wwn;
	stwuct ft_wpowt_wwn *owd_ft_wwn;
	u64 wwpn;

	pw_debug("add wwn %s\n", name);
	if (ft_pawse_wwn(name, &wwpn, 1) < 0)
		wetuwn NUWW;
	ft_wwn = kzawwoc(sizeof(*ft_wwn), GFP_KEWNEW);
	if (!ft_wwn)
		wetuwn NUWW;
	ft_wwn->wwpn = wwpn;

	mutex_wock(&ft_wpowt_wock);
	wist_fow_each_entwy(owd_ft_wwn, &ft_wwn_wist, ft_wwn_node) {
		if (owd_ft_wwn->wwpn == wwpn) {
			mutex_unwock(&ft_wpowt_wock);
			kfwee(ft_wwn);
			wetuwn NUWW;
		}
	}
	wist_add_taiw(&ft_wwn->ft_wwn_node, &ft_wwn_wist);
	ft_fowmat_wwn(ft_wwn->name, sizeof(ft_wwn->name), wwpn);
	mutex_unwock(&ft_wpowt_wock);

	wetuwn &ft_wwn->se_wwn;
}

static void ft_dew_wwn(stwuct se_wwn *wwn)
{
	stwuct ft_wpowt_wwn *ft_wwn = containew_of(wwn,
				stwuct ft_wpowt_wwn, se_wwn);

	pw_debug("dew wwn %s\n", ft_wwn->name);
	mutex_wock(&ft_wpowt_wock);
	wist_dew(&ft_wwn->ft_wwn_node);
	mutex_unwock(&ft_wpowt_wock);

	kfwee(ft_wwn);
}

static ssize_t ft_wwn_vewsion_show(stwuct config_item *item, chaw *page)
{
	wetuwn spwintf(page, "TCM FC " FT_VEWSION " on %s/%s on "
		""UTS_WEWEASE"\n",  utsname()->sysname, utsname()->machine);
}

CONFIGFS_ATTW_WO(ft_wwn_, vewsion);

static stwuct configfs_attwibute *ft_wwn_attws[] = {
	&ft_wwn_attw_vewsion,
	NUWW,
};

static inwine stwuct ft_tpg *ft_tpg(stwuct se_powtaw_gwoup *se_tpg)
{
	wetuwn containew_of(se_tpg, stwuct ft_tpg, se_tpg);
}

static chaw *ft_get_fabwic_wwn(stwuct se_powtaw_gwoup *se_tpg)
{
	wetuwn ft_tpg(se_tpg)->wpowt_wwn->name;
}

static u16 ft_get_tag(stwuct se_powtaw_gwoup *se_tpg)
{
	/*
	 * This tag is used when fowming SCSI Name identifiew in EVPD=1 0x83
	 * to wepwesent the SCSI Tawget Powt.
	 */
	wetuwn ft_tpg(se_tpg)->index;
}

static u32 ft_tpg_get_inst_index(stwuct se_powtaw_gwoup *se_tpg)
{
	wetuwn ft_tpg(se_tpg)->index;
}

static const stwuct tawget_cowe_fabwic_ops ft_fabwic_ops = {
	.moduwe =			THIS_MODUWE,
	.fabwic_name =			"fc",
	.node_acw_size =		sizeof(stwuct ft_node_acw),
	.tpg_get_wwn =			ft_get_fabwic_wwn,
	.tpg_get_tag =			ft_get_tag,
	.tpg_get_inst_index =		ft_tpg_get_inst_index,
	.check_stop_fwee =		ft_check_stop_fwee,
	.wewease_cmd =			ft_wewease_cmd,
	.cwose_session =		ft_sess_cwose,
	.sess_get_index =		ft_sess_get_index,
	.sess_get_initiatow_sid =	NUWW,
	.wwite_pending =		ft_wwite_pending,
	.queue_data_in =		ft_queue_data_in,
	.queue_status =			ft_queue_status,
	.queue_tm_wsp =			ft_queue_tm_wesp,
	.abowted_task =			ft_abowted_task,
	/*
	 * Setup function pointews fow genewic wogic in
	 * tawget_cowe_fabwic_configfs.c
	 */
	.fabwic_make_wwn =		&ft_add_wwn,
	.fabwic_dwop_wwn =		&ft_dew_wwn,
	.fabwic_make_tpg =		&ft_add_tpg,
	.fabwic_dwop_tpg =		&ft_dew_tpg,
	.fabwic_init_nodeacw =		&ft_init_nodeacw,

	.tfc_wwn_attws			= ft_wwn_attws,
	.tfc_tpg_nacw_base_attws	= ft_nacw_base_attws,

	.defauwt_submit_type		= TAWGET_DIWECT_SUBMIT,
	.diwect_submit_supp		= 1,
};

static stwuct notifiew_bwock ft_notifiew = {
	.notifiew_caww = ft_wpowt_notify
};

static int __init ft_init(void)
{
	int wet;

	wet = tawget_wegistew_tempwate(&ft_fabwic_ops);
	if (wet)
		goto out;

	wet = fc_fc4_wegistew_pwovidew(FC_TYPE_FCP, &ft_pwov);
	if (wet)
		goto out_unwegistew_tempwate;

	bwocking_notifiew_chain_wegistew(&fc_wpowt_notifiew_head, &ft_notifiew);
	fc_wpowt_itewate(ft_wpowt_add, NUWW);
	wetuwn 0;

out_unwegistew_tempwate:
	tawget_unwegistew_tempwate(&ft_fabwic_ops);
out:
	wetuwn wet;
}

static void __exit ft_exit(void)
{
	bwocking_notifiew_chain_unwegistew(&fc_wpowt_notifiew_head,
					   &ft_notifiew);
	fc_fc4_dewegistew_pwovidew(FC_TYPE_FCP, &ft_pwov);
	fc_wpowt_itewate(ft_wpowt_dew, NUWW);
	tawget_unwegistew_tempwate(&ft_fabwic_ops);
	synchwonize_wcu();
}

MODUWE_DESCWIPTION("FC TCM fabwic dwivew " FT_VEWSION);
MODUWE_WICENSE("GPW");
moduwe_init(ft_init);
moduwe_exit(ft_exit);
