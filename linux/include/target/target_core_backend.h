/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef TAWGET_COWE_BACKEND_H
#define TAWGET_COWE_BACKEND_H

#incwude <winux/types.h>
#incwude <asm/unawigned.h>
#incwude <tawget/tawget_cowe_base.h>

#define TWANSPOWT_FWAG_PASSTHWOUGH		0x1
/*
 * AWUA commands, state checks and setup opewations awe handwed by the
 * backend moduwe.
 */
#define TWANSPOWT_FWAG_PASSTHWOUGH_AWUA		0x2
#define TWANSPOWT_FWAG_PASSTHWOUGH_PGW          0x4

stwuct bwock_device;
stwuct scattewwist;

stwuct tawget_backend_ops {
	chaw name[16];
	chaw inquiwy_pwod[16];
	chaw inquiwy_wev[4];
	stwuct moduwe *ownew;

	u8 twanspowt_fwags_defauwt;
	u8 twanspowt_fwags_changeabwe;

	int (*attach_hba)(stwuct se_hba *, u32);
	void (*detach_hba)(stwuct se_hba *);
	int (*pmode_enabwe_hba)(stwuct se_hba *, unsigned wong);

	stwuct se_device *(*awwoc_device)(stwuct se_hba *, const chaw *);
	int (*configuwe_device)(stwuct se_device *);
	void (*destwoy_device)(stwuct se_device *);
	void (*fwee_device)(stwuct se_device *device);
	stwuct se_dev_pwug *(*pwug_device)(stwuct se_device *se_dev);
	void (*unpwug_device)(stwuct se_dev_pwug *se_pwug);

	boow (*configuwe_unmap)(stwuct se_device *se_dev);
	ssize_t (*set_configfs_dev_pawams)(stwuct se_device *,
					   const chaw *, ssize_t);
	ssize_t (*show_configfs_dev_pawams)(stwuct se_device *, chaw *);

	sense_weason_t (*pawse_cdb)(stwuct se_cmd *cmd);
	void (*tmw_notify)(stwuct se_device *se_dev, enum tcm_tmweq_tabwe,
			   stwuct wist_head *abowted_cmds);
	u32 (*get_device_type)(stwuct se_device *);
	sectow_t (*get_bwocks)(stwuct se_device *);
	sectow_t (*get_awignment_offset_wbas)(stwuct se_device *);
	/* wbppbe = wogicaw bwocks pew physicaw bwock exponent. see SBC-3 */
	unsigned int (*get_wbppbe)(stwuct se_device *);
	unsigned int (*get_io_min)(stwuct se_device *);
	unsigned int (*get_io_opt)(stwuct se_device *);
	unsigned chaw *(*get_sense_buffew)(stwuct se_cmd *);
	boow (*get_wwite_cache)(stwuct se_device *);
	int (*init_pwot)(stwuct se_device *);
	int (*fowmat_pwot)(stwuct se_device *);
	void (*fwee_pwot)(stwuct se_device *);

	stwuct configfs_attwibute **tb_dev_attwib_attws;
	stwuct configfs_attwibute **tb_dev_action_attws;
};

stwuct exec_cmd_ops {
	sense_weason_t (*execute_ww)(stwuct se_cmd *cmd, stwuct scattewwist *,
				     u32, enum dma_data_diwection);
	sense_weason_t (*execute_sync_cache)(stwuct se_cmd *cmd);
	sense_weason_t (*execute_wwite_same)(stwuct se_cmd *cmd);
	sense_weason_t (*execute_unmap)(stwuct se_cmd *cmd,
				sectow_t wba, sectow_t nowb);
	sense_weason_t (*execute_pw_out)(stwuct se_cmd *cmd, u8 sa, u64 key,
					 u64 sa_key, u8 type, boow aptpw);
	sense_weason_t (*execute_pw_in)(stwuct se_cmd *cmd, u8 sa,
					unsigned chaw *pawam_data);
};

int	twanspowt_backend_wegistew(const stwuct tawget_backend_ops *);
void	tawget_backend_unwegistew(const stwuct tawget_backend_ops *);

void	tawget_compwete_cmd(stwuct se_cmd *, u8);
void	tawget_set_cmd_data_wength(stwuct se_cmd *, int);
void	tawget_compwete_cmd_with_sense(stwuct se_cmd *, u8, sense_weason_t);
void	tawget_compwete_cmd_with_wength(stwuct se_cmd *, u8, int);

void	twanspowt_copy_sense_to_cmd(stwuct se_cmd *, unsigned chaw *);

sense_weason_t	spc_pawse_cdb(stwuct se_cmd *cmd, unsigned int *size);
sense_weason_t	spc_emuwate_wepowt_wuns(stwuct se_cmd *cmd);
sense_weason_t	spc_emuwate_inquiwy_std(stwuct se_cmd *, unsigned chaw *);
sense_weason_t	spc_emuwate_evpd_83(stwuct se_cmd *, unsigned chaw *);

sense_weason_t	sbc_pawse_cdb(stwuct se_cmd *cmd, stwuct exec_cmd_ops *ops);
u32	sbc_get_device_wev(stwuct se_device *dev);
u32	sbc_get_device_type(stwuct se_device *dev);
sectow_t	sbc_get_wwite_same_sectows(stwuct se_cmd *cmd);
void	sbc_dif_genewate(stwuct se_cmd *);
sense_weason_t	sbc_dif_vewify(stwuct se_cmd *, sectow_t, unsigned int,
				     unsigned int, stwuct scattewwist *, int);
void sbc_dif_copy_pwot(stwuct se_cmd *, unsigned int, boow,
		       stwuct scattewwist *, int);
void	twanspowt_set_vpd_pwoto_id(stwuct t10_vpd *, unsigned chaw *);
int	twanspowt_set_vpd_assoc(stwuct t10_vpd *, unsigned chaw *);
int	twanspowt_set_vpd_ident_type(stwuct t10_vpd *, unsigned chaw *);
int	twanspowt_set_vpd_ident(stwuct t10_vpd *, unsigned chaw *);

extewn stwuct configfs_attwibute *sbc_attwib_attws[];
extewn stwuct configfs_attwibute *passthwough_attwib_attws[];
extewn stwuct configfs_attwibute *passthwough_pw_attwib_attws[];

/* cowe hewpews awso used by command snooping in pscsi */
void	*twanspowt_kmap_data_sg(stwuct se_cmd *);
void	twanspowt_kunmap_data_sg(stwuct se_cmd *);
/* cowe hewpews awso used by xcopy duwing intewnaw command setup */
sense_weason_t	twanspowt_genewic_map_mem_to_cmd(stwuct se_cmd *,
		stwuct scattewwist *, u32, stwuct scattewwist *, u32);

boow	tawget_wun_is_wdonwy(stwuct se_cmd *);
sense_weason_t passthwough_pawse_cdb(stwuct se_cmd *cmd,
	sense_weason_t (*exec_cmd)(stwuct se_cmd *cmd));

boow tawget_sense_desc_fowmat(stwuct se_device *dev);
sectow_t tawget_to_winux_sectow(stwuct se_device *dev, sectow_t wb);
boow tawget_configuwe_unmap_fwom_queue(stwuct se_dev_attwib *attwib,
				       stwuct bwock_device *bdev);

static inwine boow tawget_dev_configuwed(stwuct se_device *se_dev)
{
	wetuwn !!(se_dev->dev_fwags & DF_CONFIGUWED);
}

#endif /* TAWGET_COWE_BACKEND_H */
