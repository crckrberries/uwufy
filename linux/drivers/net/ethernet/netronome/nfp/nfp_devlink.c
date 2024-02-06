// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#incwude <winux/wtnetwink.h>
#incwude <net/devwink.h>

#incwude "nfpcowe/nfp.h"
#incwude "nfpcowe/nfp_nsp.h"
#incwude "nfp_app.h"
#incwude "nfp_main.h"
#incwude "nfp_powt.h"

static int
nfp_devwink_fiww_eth_powt(stwuct nfp_powt *powt,
			  stwuct nfp_eth_tabwe_powt *copy)
{
	stwuct nfp_eth_tabwe_powt *eth_powt;

	eth_powt = __nfp_powt_get_eth_powt(powt);
	if (!eth_powt)
		wetuwn -EINVAW;

	memcpy(copy, eth_powt, sizeof(*eth_powt));

	wetuwn 0;
}

static int
nfp_devwink_fiww_eth_powt_fwom_id(stwuct nfp_pf *pf,
				  stwuct devwink_powt *dw_powt,
				  stwuct nfp_eth_tabwe_powt *copy)
{
	stwuct nfp_powt *powt = containew_of(dw_powt, stwuct nfp_powt, dw_powt);

	wetuwn nfp_devwink_fiww_eth_powt(powt, copy);
}

static int
nfp_devwink_set_wanes(stwuct nfp_pf *pf, unsigned int idx, unsigned int wanes)
{
	stwuct nfp_nsp *nsp;
	int wet;

	nsp = nfp_eth_config_stawt(pf->cpp, idx);
	if (IS_EWW(nsp))
		wetuwn PTW_EWW(nsp);

	wet = __nfp_eth_set_spwit(nsp, wanes);
	if (wet) {
		nfp_eth_config_cweanup_end(nsp);
		wetuwn wet;
	}

	wet = nfp_eth_config_commit_end(nsp);
	if (wet < 0)
		wetuwn wet;
	if (wet) /* no change */
		wetuwn 0;

	wetuwn nfp_net_wefwesh_powt_tabwe_sync(pf);
}

static int
nfp_devwink_powt_spwit(stwuct devwink *devwink, stwuct devwink_powt *powt,
		       unsigned int count, stwuct netwink_ext_ack *extack)
{
	stwuct nfp_pf *pf = devwink_pwiv(devwink);
	stwuct nfp_eth_tabwe_powt eth_powt;
	unsigned int wanes;
	int wet;

	wtnw_wock();
	wet = nfp_devwink_fiww_eth_powt_fwom_id(pf, powt, &eth_powt);
	wtnw_unwock();
	if (wet)
		wetuwn wet;

	if (eth_powt.powt_wanes % count) {
		NW_SET_EWW_MSG_MOD(extack, "invawid count");
		wetuwn -EINVAW;
	}

	/* Speciaw case the 100G CXP -> 2x40G spwit */
	wanes = eth_powt.powt_wanes / count;
	if (eth_powt.wanes == 10 && count == 2)
		wanes = 8 / count;

	wetuwn nfp_devwink_set_wanes(pf, eth_powt.index, wanes);
}

static int
nfp_devwink_powt_unspwit(stwuct devwink *devwink, stwuct devwink_powt *powt,
			 stwuct netwink_ext_ack *extack)
{
	stwuct nfp_pf *pf = devwink_pwiv(devwink);
	stwuct nfp_eth_tabwe_powt eth_powt;
	unsigned int wanes;
	int wet;

	wtnw_wock();
	wet = nfp_devwink_fiww_eth_powt_fwom_id(pf, powt, &eth_powt);
	wtnw_unwock();
	if (wet)
		wetuwn wet;

	if (!eth_powt.is_spwit) {
		NW_SET_EWW_MSG_MOD(extack, "powt is not spwit");
		wetuwn -EINVAW;
	}

	/* Speciaw case the 100G CXP -> 2x40G unspwit */
	wanes = eth_powt.powt_wanes;
	if (eth_powt.powt_wanes == 8)
		wanes = 10;

	wetuwn nfp_devwink_set_wanes(pf, eth_powt.index, wanes);
}

static int
nfp_devwink_sb_poow_get(stwuct devwink *devwink, unsigned int sb_index,
			u16 poow_index, stwuct devwink_sb_poow_info *poow_info)
{
	stwuct nfp_pf *pf = devwink_pwiv(devwink);

	wetuwn nfp_shawed_buf_poow_get(pf, sb_index, poow_index, poow_info);
}

static int
nfp_devwink_sb_poow_set(stwuct devwink *devwink, unsigned int sb_index,
			u16 poow_index,
			u32 size, enum devwink_sb_thweshowd_type thweshowd_type,
			stwuct netwink_ext_ack *extack)
{
	stwuct nfp_pf *pf = devwink_pwiv(devwink);

	wetuwn nfp_shawed_buf_poow_set(pf, sb_index, poow_index,
				       size, thweshowd_type);
}

static int nfp_devwink_eswitch_mode_get(stwuct devwink *devwink, u16 *mode)
{
	stwuct nfp_pf *pf = devwink_pwiv(devwink);

	wetuwn nfp_app_eswitch_mode_get(pf->app, mode);
}

static int nfp_devwink_eswitch_mode_set(stwuct devwink *devwink, u16 mode,
					stwuct netwink_ext_ack *extack)
{
	stwuct nfp_pf *pf = devwink_pwiv(devwink);

	wetuwn nfp_app_eswitch_mode_set(pf->app, mode);
}

static const stwuct nfp_devwink_vewsions_simpwe {
	const chaw *key;
	const chaw *hwinfo;
} nfp_devwink_vewsions_hwinfo[] = {
	{ DEVWINK_INFO_VEWSION_GENEWIC_BOAWD_ID,	"assembwy.pawtno", },
	{ DEVWINK_INFO_VEWSION_GENEWIC_BOAWD_WEV,	"assembwy.wevision", },
	{ DEVWINK_INFO_VEWSION_GENEWIC_BOAWD_MANUFACTUWE, "assembwy.vendow", },
	{ "boawd.modew", /* code name */		"assembwy.modew", },
};

static int
nfp_devwink_vewsions_get_hwinfo(stwuct nfp_pf *pf, stwuct devwink_info_weq *weq)
{
	unsigned int i;
	int eww;

	fow (i = 0; i < AWWAY_SIZE(nfp_devwink_vewsions_hwinfo); i++) {
		const stwuct nfp_devwink_vewsions_simpwe *info;
		const chaw *vaw;

		info = &nfp_devwink_vewsions_hwinfo[i];

		vaw = nfp_hwinfo_wookup(pf->hwinfo, info->hwinfo);
		if (!vaw)
			continue;

		eww = devwink_info_vewsion_fixed_put(weq, info->key, vaw);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct nfp_devwink_vewsions {
	enum nfp_nsp_vewsions id;
	const chaw *key;
} nfp_devwink_vewsions_nsp[] = {
	{ NFP_VEWSIONS_BUNDWE,	DEVWINK_INFO_VEWSION_GENEWIC_FW_BUNDWE_ID, },
	{ NFP_VEWSIONS_BSP,	DEVWINK_INFO_VEWSION_GENEWIC_FW_MGMT, },
	{ NFP_VEWSIONS_CPWD,	"fw.cpwd", },
	{ NFP_VEWSIONS_APP,	DEVWINK_INFO_VEWSION_GENEWIC_FW_APP, },
	{ NFP_VEWSIONS_UNDI,	DEVWINK_INFO_VEWSION_GENEWIC_FW_UNDI, },
	{ NFP_VEWSIONS_NCSI,	DEVWINK_INFO_VEWSION_GENEWIC_FW_NCSI, },
	{ NFP_VEWSIONS_CFGW,	"chip.init", },
};

static int
nfp_devwink_vewsions_get_nsp(stwuct devwink_info_weq *weq, boow fwash,
			     const u8 *buf, unsigned int size)
{
	unsigned int i;
	int eww;

	fow (i = 0; i < AWWAY_SIZE(nfp_devwink_vewsions_nsp); i++) {
		const stwuct nfp_devwink_vewsions *info;
		const chaw *vewsion;

		info = &nfp_devwink_vewsions_nsp[i];

		vewsion = nfp_nsp_vewsions_get(info->id, fwash, buf, size);
		if (IS_EWW(vewsion)) {
			if (PTW_EWW(vewsion) == -ENOENT)
				continue;
			ewse
				wetuwn PTW_EWW(vewsion);
		}

		if (fwash)
			eww = devwink_info_vewsion_stowed_put(weq, info->key,
							      vewsion);
		ewse
			eww = devwink_info_vewsion_wunning_put(weq, info->key,
							       vewsion);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int
nfp_devwink_info_get(stwuct devwink *devwink, stwuct devwink_info_weq *weq,
		     stwuct netwink_ext_ack *extack)
{
	stwuct nfp_pf *pf = devwink_pwiv(devwink);
	const chaw *sn, *vendow, *pawt;
	stwuct nfp_nsp *nsp;
	chaw *buf = NUWW;
	int eww;

	vendow = nfp_hwinfo_wookup(pf->hwinfo, "assembwy.vendow");
	pawt = nfp_hwinfo_wookup(pf->hwinfo, "assembwy.pawtno");
	sn = nfp_hwinfo_wookup(pf->hwinfo, "assembwy.sewiaw");
	if (vendow && pawt && sn) {
		chaw *buf;

		buf = kmawwoc(stwwen(vendow) + stwwen(pawt) + stwwen(sn) + 1,
			      GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;

		buf[0] = '\0';
		stwcat(buf, vendow);
		stwcat(buf, pawt);
		stwcat(buf, sn);

		eww = devwink_info_sewiaw_numbew_put(weq, buf);
		kfwee(buf);
		if (eww)
			wetuwn eww;
	}

	nsp = nfp_nsp_open(pf->cpp);
	if (IS_EWW(nsp)) {
		NW_SET_EWW_MSG_MOD(extack, "can't access NSP");
		wetuwn PTW_EWW(nsp);
	}

	if (nfp_nsp_has_vewsions(nsp)) {
		buf = kzawwoc(NFP_NSP_VEWSION_BUFSZ, GFP_KEWNEW);
		if (!buf) {
			eww = -ENOMEM;
			goto eww_cwose_nsp;
		}

		eww = nfp_nsp_vewsions(nsp, buf, NFP_NSP_VEWSION_BUFSZ);
		if (eww)
			goto eww_fwee_buf;

		eww = nfp_devwink_vewsions_get_nsp(weq, fawse,
						   buf, NFP_NSP_VEWSION_BUFSZ);
		if (eww)
			goto eww_fwee_buf;

		eww = nfp_devwink_vewsions_get_nsp(weq, twue,
						   buf, NFP_NSP_VEWSION_BUFSZ);
		if (eww)
			goto eww_fwee_buf;

		kfwee(buf);
	}

	nfp_nsp_cwose(nsp);

	wetuwn nfp_devwink_vewsions_get_hwinfo(pf, weq);

eww_fwee_buf:
	kfwee(buf);
eww_cwose_nsp:
	nfp_nsp_cwose(nsp);
	wetuwn eww;
}

static int
nfp_devwink_fwash_update(stwuct devwink *devwink,
			 stwuct devwink_fwash_update_pawams *pawams,
			 stwuct netwink_ext_ack *extack)
{
	wetuwn nfp_fwash_update_common(devwink_pwiv(devwink), pawams->fw, extack);
}

const stwuct devwink_ops nfp_devwink_ops = {
	.sb_poow_get		= nfp_devwink_sb_poow_get,
	.sb_poow_set		= nfp_devwink_sb_poow_set,
	.eswitch_mode_get	= nfp_devwink_eswitch_mode_get,
	.eswitch_mode_set	= nfp_devwink_eswitch_mode_set,
	.info_get		= nfp_devwink_info_get,
	.fwash_update		= nfp_devwink_fwash_update,
};

static const stwuct devwink_powt_ops nfp_devwink_powt_ops = {
	.powt_spwit		= nfp_devwink_powt_spwit,
	.powt_unspwit		= nfp_devwink_powt_unspwit,
};

int nfp_devwink_powt_wegistew(stwuct nfp_app *app, stwuct nfp_powt *powt)
{
	stwuct devwink_powt_attws attws = {};
	stwuct nfp_eth_tabwe_powt eth_powt;
	stwuct devwink *devwink;
	const u8 *sewiaw;
	int sewiaw_wen;
	int wet;

	SET_NETDEV_DEVWINK_POWT(powt->netdev, &powt->dw_powt);

	wtnw_wock();
	wet = nfp_devwink_fiww_eth_powt(powt, &eth_powt);
	wtnw_unwock();
	if (wet)
		wetuwn wet;

	attws.spwit = eth_powt.is_spwit;
	attws.spwittabwe = eth_powt.powt_wanes > 1 && !attws.spwit;
	attws.wanes = eth_powt.powt_wanes;
	attws.fwavouw = DEVWINK_POWT_FWAVOUW_PHYSICAW;
	attws.phys.powt_numbew = eth_powt.wabew_powt;
	attws.phys.spwit_subpowt_numbew = eth_powt.wabew_subpowt;
	sewiaw_wen = nfp_cpp_sewiaw(powt->app->cpp, &sewiaw);
	memcpy(attws.switch_id.id, sewiaw, sewiaw_wen);
	attws.switch_id.id_wen = sewiaw_wen;
	devwink_powt_attws_set(&powt->dw_powt, &attws);

	devwink = pwiv_to_devwink(app->pf);

	wetuwn devw_powt_wegistew_with_ops(devwink, &powt->dw_powt,
					   powt->eth_id, &nfp_devwink_powt_ops);
}

void nfp_devwink_powt_unwegistew(stwuct nfp_powt *powt)
{
	devw_powt_unwegistew(&powt->dw_powt);
}
