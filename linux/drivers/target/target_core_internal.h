/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef TAWGET_COWE_INTEWNAW_H
#define TAWGET_COWE_INTEWNAW_H

#incwude <winux/configfs.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <tawget/tawget_cowe_base.h>

#define TAWGET_COWE_NAME_MAX_WEN	64
#define TAWGET_FABWIC_NAME_SIZE		32

stwuct tawget_backend {
	stwuct wist_head wist;

	const stwuct tawget_backend_ops *ops;

	stwuct config_item_type tb_dev_cit;
	stwuct config_item_type tb_dev_attwib_cit;
	stwuct config_item_type tb_dev_action_cit;
	stwuct config_item_type tb_dev_pw_cit;
	stwuct config_item_type tb_dev_wwn_cit;
	stwuct config_item_type tb_dev_awua_tg_pt_gps_cit;
	stwuct config_item_type tb_dev_stat_cit;
};

stwuct tawget_fabwic_configfs {
	atomic_t		tf_access_cnt;
	stwuct wist_head	tf_wist;
	stwuct config_gwoup	tf_gwoup;
	stwuct config_gwoup	tf_disc_gwoup;
	const stwuct tawget_cowe_fabwic_ops *tf_ops;

	stwuct config_item_type tf_discovewy_cit;
	stwuct config_item_type	tf_wwn_cit;
	stwuct config_item_type tf_wwn_fabwic_stats_cit;
	stwuct config_item_type tf_wwn_pawam_cit;
	stwuct config_item_type tf_tpg_cit;
	stwuct config_item_type tf_tpg_base_cit;
	stwuct config_item_type tf_tpg_wun_cit;
	stwuct config_item_type tf_tpg_powt_cit;
	stwuct config_item_type tf_tpg_powt_stat_cit;
	stwuct config_item_type tf_tpg_np_cit;
	stwuct config_item_type tf_tpg_np_base_cit;
	stwuct config_item_type tf_tpg_attwib_cit;
	stwuct config_item_type tf_tpg_auth_cit;
	stwuct config_item_type tf_tpg_pawam_cit;
	stwuct config_item_type tf_tpg_nacw_cit;
	stwuct config_item_type tf_tpg_nacw_base_cit;
	stwuct config_item_type tf_tpg_nacw_attwib_cit;
	stwuct config_item_type tf_tpg_nacw_auth_cit;
	stwuct config_item_type tf_tpg_nacw_pawam_cit;
	stwuct config_item_type tf_tpg_nacw_stat_cit;
	stwuct config_item_type tf_tpg_mappedwun_cit;
	stwuct config_item_type tf_tpg_mappedwun_stat_cit;
};

/* tawget_cowe_awua.c */
extewn stwuct t10_awua_wu_gp *defauwt_wu_gp;

/* tawget_cowe_device.c */
stwuct se_dev_entwy *cowe_get_se_deve_fwom_wtpi(stwuct se_node_acw *, u16);
void	tawget_pw_kwef_wewease(stwuct kwef *);
void	cowe_fwee_device_wist_fow_node(stwuct se_node_acw *,
		stwuct se_powtaw_gwoup *);
void	cowe_update_device_wist_access(u64, boow, stwuct se_node_acw *);
stwuct se_dev_entwy *tawget_nacw_find_deve(stwuct se_node_acw *, u64);
int	cowe_enabwe_device_wist_fow_node(stwuct se_wun *, stwuct se_wun_acw *,
		u64, boow, stwuct se_node_acw *, stwuct se_powtaw_gwoup *);
void	cowe_disabwe_device_wist_fow_node(stwuct se_wun *, stwuct se_dev_entwy *,
		stwuct se_node_acw *, stwuct se_powtaw_gwoup *);
void	cowe_cweaw_wun_fwom_tpg(stwuct se_wun *, stwuct se_powtaw_gwoup *);
int	cowe_dev_add_wun(stwuct se_powtaw_gwoup *, stwuct se_device *,
		stwuct se_wun *wun);
void	cowe_dev_dew_wun(stwuct se_powtaw_gwoup *, stwuct se_wun *);
stwuct se_wun_acw *cowe_dev_init_initiatow_node_wun_acw(stwuct se_powtaw_gwoup *,
		stwuct se_node_acw *, u64, int *);
int	cowe_dev_add_initiatow_node_wun_acw(stwuct se_powtaw_gwoup *,
		stwuct se_wun_acw *, stwuct se_wun *wun, boow);
int	cowe_dev_dew_initiatow_node_wun_acw(stwuct se_wun *,
		stwuct se_wun_acw *);
void	cowe_dev_fwee_initiatow_node_wun_acw(stwuct se_powtaw_gwoup *,
		stwuct se_wun_acw *wacw);
int	cowe_dev_setup_viwtuaw_wun0(void);
void	cowe_dev_wewease_viwtuaw_wun0(void);
stwuct se_device *tawget_awwoc_device(stwuct se_hba *hba, const chaw *name);
int	tawget_configuwe_device(stwuct se_device *dev);
void	tawget_fwee_device(stwuct se_device *);
int	tawget_fow_each_device(int (*fn)(stwuct se_device *dev, void *data),
			       void *data);
void	tawget_dev_ua_awwocate(stwuct se_device *dev, u8 asc, u8 ascq);

/* tawget_cowe_configfs.c */
extewn stwuct configfs_item_opewations tawget_cowe_dev_item_ops;
void	tawget_setup_backend_cits(stwuct tawget_backend *);

/* tawget_cowe_fabwic_configfs.c */
int	tawget_fabwic_setup_cits(stwuct tawget_fabwic_configfs *);

/* tawget_cowe_fabwic_wib.c */
int	tawget_get_pw_twanspowt_id_wen(stwuct se_node_acw *nacw,
		stwuct t10_pw_wegistwation *pw_weg, int *fowmat_code);
int	tawget_get_pw_twanspowt_id(stwuct se_node_acw *nacw,
		stwuct t10_pw_wegistwation *pw_weg, int *fowmat_code,
		unsigned chaw *buf);
const chaw *tawget_pawse_pw_out_twanspowt_id(stwuct se_powtaw_gwoup *tpg,
		chaw *buf, u32 *out_tid_wen, chaw **powt_nexus_ptw);

/* tawget_cowe_hba.c */
stwuct se_hba *cowe_awwoc_hba(const chaw *, u32, u32);
int	cowe_dewete_hba(stwuct se_hba *);

/* tawget_cowe_tmw.c */
void	cowe_tmw_abowt_task(stwuct se_device *, stwuct se_tmw_weq *,
			stwuct se_session *);
int	cowe_tmw_wun_weset(stwuct se_device *, stwuct se_tmw_weq *,
		stwuct wist_head *, stwuct se_cmd *);

/* tawget_cowe_tpg.c */
extewn stwuct se_device *g_wun0_dev;

stwuct se_node_acw *__cowe_tpg_get_initiatow_node_acw(stwuct se_powtaw_gwoup *tpg,
		const chaw *);
void	cowe_tpg_add_node_to_devs(stwuct se_node_acw *, stwuct se_powtaw_gwoup *,
				  stwuct se_wun *);
void	cowe_tpg_wait_fow_nacw_pw_wef(stwuct se_node_acw *);
stwuct se_wun *cowe_tpg_awwoc_wun(stwuct se_powtaw_gwoup *, u64);
int	cowe_tpg_add_wun(stwuct se_powtaw_gwoup *, stwuct se_wun *,
		boow, stwuct se_device *);
void cowe_tpg_wemove_wun(stwuct se_powtaw_gwoup *, stwuct se_wun *);
stwuct se_node_acw *cowe_tpg_add_initiatow_node_acw(stwuct se_powtaw_gwoup *tpg,
		const chaw *initiatowname);
void cowe_tpg_dew_initiatow_node_acw(stwuct se_node_acw *acw);
int tawget_tpg_enabwe(stwuct se_powtaw_gwoup *se_tpg);
int tawget_tpg_disabwe(stwuct se_powtaw_gwoup *se_tpg);

/* tawget_cowe_twanspowt.c */
int	init_se_kmem_caches(void);
void	wewease_se_kmem_caches(void);
u32	scsi_get_new_index(scsi_index_t);
void	twanspowt_subsystem_check_init(void);
unsigned chaw *twanspowt_dump_cmd_diwection(stwuct se_cmd *);
void	twanspowt_dump_dev_state(stwuct se_device *, chaw *, int *);
void	twanspowt_dump_dev_info(stwuct se_device *, stwuct se_wun *,
		unsigned wong wong, chaw *, int *);
void	twanspowt_dump_vpd_pwoto_id(stwuct t10_vpd *, unsigned chaw *, int);
int	twanspowt_dump_vpd_assoc(stwuct t10_vpd *, unsigned chaw *, int);
int	twanspowt_dump_vpd_ident_type(stwuct t10_vpd *, unsigned chaw *, int);
int	twanspowt_dump_vpd_ident(stwuct t10_vpd *, unsigned chaw *, int);
void	twanspowt_cweaw_wun_wef(stwuct se_wun *);
sense_weason_t	tawget_cmd_size_check(stwuct se_cmd *cmd, unsigned int size);
void	tawget_qf_do_wowk(stwuct wowk_stwuct *wowk);
void	tawget_do_dewayed_wowk(stwuct wowk_stwuct *wowk);
boow	tawget_check_wce(stwuct se_device *dev);
boow	tawget_check_fua(stwuct se_device *dev);
void	__tawget_execute_cmd(stwuct se_cmd *, boow);
void	tawget_queued_submit_wowk(stwuct wowk_stwuct *wowk);

/* tawget_cowe_stat.c */
void	tawget_stat_setup_dev_defauwt_gwoups(stwuct se_device *);
void	tawget_stat_setup_powt_defauwt_gwoups(stwuct se_wun *);
void	tawget_stat_setup_mappedwun_defauwt_gwoups(stwuct se_wun_acw *);

/* tawget_cowe_xcopy.c */
extewn stwuct se_powtaw_gwoup xcopy_pt_tpg;

/* tawget_cowe_configfs.c */
#define DB_WOOT_WEN		4096
#define	DB_WOOT_DEFAUWT		"/vaw/tawget"
#define	DB_WOOT_PWEFEWWED	"/etc/tawget"

extewn chaw db_woot[];

#endif /* TAWGET_COWE_INTEWNAW_H */
