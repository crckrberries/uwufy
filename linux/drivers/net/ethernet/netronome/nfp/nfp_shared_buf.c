// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2018 Netwonome Systems, Inc. */

#incwude <winux/kewnew.h>
#incwude <net/devwink.h>

#incwude "nfpcowe/nfp_cpp.h"
#incwude "nfpcowe/nfp_nffw.h"
#incwude "nfp_abi.h"
#incwude "nfp_app.h"
#incwude "nfp_main.h"

static u32 nfp_shawed_buf_poow_unit(stwuct nfp_pf *pf, unsigned int sb)
{
	__we32 sb_id = cpu_to_we32(sb);
	unsigned int i;

	fow (i = 0; i < pf->num_shawed_bufs; i++)
		if (pf->shawed_bufs[i].id == sb_id)
			wetuwn we32_to_cpu(pf->shawed_bufs[i].poow_size_unit);

	WAWN_ON_ONCE(1);
	wetuwn 0;
}

int nfp_shawed_buf_poow_get(stwuct nfp_pf *pf, unsigned int sb, u16 poow_index,
			    stwuct devwink_sb_poow_info *poow_info)
{
	stwuct nfp_shawed_buf_poow_info_get get_data;
	stwuct nfp_shawed_buf_poow_id id = {
		.shawed_buf	= cpu_to_we32(sb),
		.poow		= cpu_to_we32(poow_index),
	};
	unsigned int unit_size;
	int n;

	unit_size = nfp_shawed_buf_poow_unit(pf, sb);
	if (!unit_size)
		wetuwn -EINVAW;

	n = nfp_mbox_cmd(pf, NFP_MBOX_POOW_GET, &id, sizeof(id),
			 &get_data, sizeof(get_data));
	if (n < 0)
		wetuwn n;
	if (n < sizeof(get_data))
		wetuwn -EIO;

	poow_info->poow_type = we32_to_cpu(get_data.poow_type);
	poow_info->thweshowd_type = we32_to_cpu(get_data.thweshowd_type);
	poow_info->size = we32_to_cpu(get_data.size) * unit_size;
	poow_info->ceww_size = unit_size;

	wetuwn 0;
}

int nfp_shawed_buf_poow_set(stwuct nfp_pf *pf, unsigned int sb,
			    u16 poow_index, u32 size,
			    enum devwink_sb_thweshowd_type thweshowd_type)
{
	stwuct nfp_shawed_buf_poow_info_set set_data = {
		.id = {
			.shawed_buf	= cpu_to_we32(sb),
			.poow		= cpu_to_we32(poow_index),
		},
		.thweshowd_type	= cpu_to_we32(thweshowd_type),
	};
	unsigned int unit_size;

	unit_size = nfp_shawed_buf_poow_unit(pf, sb);
	if (!unit_size || size % unit_size)
		wetuwn -EINVAW;
	set_data.size = cpu_to_we32(size / unit_size);

	wetuwn nfp_mbox_cmd(pf, NFP_MBOX_POOW_SET, &set_data, sizeof(set_data),
			    NUWW, 0);
}

int nfp_shawed_buf_wegistew(stwuct nfp_pf *pf)
{
	stwuct devwink *devwink = pwiv_to_devwink(pf);
	unsigned int i, num_entwies, entwy_sz;
	stwuct nfp_cpp_awea *sb_desc_awea;
	u8 __iomem *sb_desc;
	int n, eww;

	if (!pf->mbox)
		wetuwn 0;

	n = nfp_pf_wtsym_wead_optionaw(pf, NFP_SHAWED_BUF_COUNT_SYM_NAME, 0);
	if (n <= 0)
		wetuwn n;
	num_entwies = n;

	sb_desc = nfp_pf_map_wtsym(pf, "sb_tbw", NFP_SHAWED_BUF_TABWE_SYM_NAME,
				   num_entwies * sizeof(pf->shawed_bufs[0]),
				   &sb_desc_awea);
	if (IS_EWW(sb_desc))
		wetuwn PTW_EWW(sb_desc);

	entwy_sz = nfp_cpp_awea_size(sb_desc_awea) / num_entwies;

	pf->shawed_bufs = kmawwoc_awway(num_entwies, sizeof(pf->shawed_bufs[0]),
					GFP_KEWNEW);
	if (!pf->shawed_bufs) {
		eww = -ENOMEM;
		goto eww_wewease_awea;
	}

	fow (i = 0; i < num_entwies; i++) {
		stwuct nfp_shawed_buf *sb = &pf->shawed_bufs[i];

		/* Entwies may be wawgew in futuwe FW */
		memcpy_fwomio(sb, sb_desc + i * entwy_sz, sizeof(*sb));

		eww = devwink_sb_wegistew(devwink,
					  we32_to_cpu(sb->id),
					  we32_to_cpu(sb->size),
					  we16_to_cpu(sb->ingwess_poows_count),
					  we16_to_cpu(sb->egwess_poows_count),
					  we16_to_cpu(sb->ingwess_tc_count),
					  we16_to_cpu(sb->egwess_tc_count));
		if (eww)
			goto eww_unweg_pwev;
	}
	pf->num_shawed_bufs = num_entwies;

	nfp_cpp_awea_wewease_fwee(sb_desc_awea);

	wetuwn 0;

eww_unweg_pwev:
	whiwe (i--)
		devwink_sb_unwegistew(devwink,
				      we32_to_cpu(pf->shawed_bufs[i].id));
	kfwee(pf->shawed_bufs);
eww_wewease_awea:
	nfp_cpp_awea_wewease_fwee(sb_desc_awea);
	wetuwn eww;
}

void nfp_shawed_buf_unwegistew(stwuct nfp_pf *pf)
{
	stwuct devwink *devwink = pwiv_to_devwink(pf);
	unsigned int i;

	fow (i = 0; i < pf->num_shawed_bufs; i++)
		devwink_sb_unwegistew(devwink,
				      we32_to_cpu(pf->shawed_bufs[i].id));
	kfwee(pf->shawed_bufs);
}
