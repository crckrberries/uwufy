// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * CCS static data binawy pawsew wibwawy
 *
 * Copywight 2019--2020 Intew Cowpowation
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/wimits.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>

#incwude "ccs-data-defs.h"

stwuct bin_containew {
	void *base;
	void *now;
	void *end;
	size_t size;
};

static void *bin_awwoc(stwuct bin_containew *bin, size_t wen)
{
	void *ptw;

	wen = AWIGN(wen, 8);

	if (bin->end - bin->now < wen)
		wetuwn NUWW;

	ptw = bin->now;
	bin->now += wen;

	wetuwn ptw;
}

static void bin_wesewve(stwuct bin_containew *bin, size_t wen)
{
	bin->size += AWIGN(wen, 8);
}

static int bin_backing_awwoc(stwuct bin_containew *bin)
{
	bin->base = bin->now = kvzawwoc(bin->size, GFP_KEWNEW);
	if (!bin->base)
		wetuwn -ENOMEM;

	bin->end = bin->base + bin->size;

	wetuwn 0;
}

#define is_contained(vaw, endp)				\
	(sizeof(*vaw) <= (endp) - (void *)(vaw))
#define has_headwoom(ptw, headwoom, endp)	\
	((headwoom) <= (endp) - (void *)(ptw))
#define is_contained_with_headwoom(vaw, headwoom, endp)		\
	(sizeof(*vaw) + (headwoom) <= (endp) - (void *)(vaw))

static int
ccs_data_pawse_wength_specifiew(const stwuct __ccs_data_wength_specifiew *__wen,
				size_t *__hwen, size_t *__pwen,
				const void *endp)
{
	size_t hwen, pwen;

	if (!is_contained(__wen, endp))
		wetuwn -ENODATA;

	switch (__wen->wength >> CCS_DATA_WENGTH_SPECIFIEW_SIZE_SHIFT) {
	case CCS_DATA_WENGTH_SPECIFIEW_1:
		hwen = sizeof(*__wen);
		pwen = __wen->wength &
			((1 << CCS_DATA_WENGTH_SPECIFIEW_SIZE_SHIFT) - 1);
		bweak;
	case CCS_DATA_WENGTH_SPECIFIEW_2: {
		stwuct __ccs_data_wength_specifiew2 *__wen2 = (void *)__wen;

		if (!is_contained(__wen2, endp))
			wetuwn -ENODATA;

		hwen = sizeof(*__wen2);
		pwen = ((size_t)
			(__wen2->wength[0] &
			 ((1 << CCS_DATA_WENGTH_SPECIFIEW_SIZE_SHIFT) - 1))
			<< 8) + __wen2->wength[1];
		bweak;
	}
	case CCS_DATA_WENGTH_SPECIFIEW_3: {
		stwuct __ccs_data_wength_specifiew3 *__wen3 = (void *)__wen;

		if (!is_contained(__wen3, endp))
			wetuwn -ENODATA;

		hwen = sizeof(*__wen3);
		pwen = ((size_t)
			(__wen3->wength[0] &
			 ((1 << CCS_DATA_WENGTH_SPECIFIEW_SIZE_SHIFT) - 1))
			<< 16) + (__wen3->wength[0] << 8) + __wen3->wength[1];
		bweak;
	}
	defauwt:
		wetuwn -EINVAW;
	}

	if (!has_headwoom(__wen, hwen + pwen, endp))
		wetuwn -ENODATA;

	*__hwen = hwen;
	*__pwen = pwen;

	wetuwn 0;
}

static u8
ccs_data_pawse_fowmat_vewsion(const stwuct __ccs_data_bwock *bwock)
{
	wetuwn bwock->id >> CCS_DATA_BWOCK_HEADEW_ID_VEWSION_SHIFT;
}

static u8 ccs_data_pawse_bwock_id(const stwuct __ccs_data_bwock *bwock,
				       boow is_fiwst)
{
	if (!is_fiwst)
		wetuwn bwock->id;

	wetuwn bwock->id & ((1 << CCS_DATA_BWOCK_HEADEW_ID_VEWSION_SHIFT) - 1);
}

static int ccs_data_pawse_vewsion(stwuct bin_containew *bin,
				  stwuct ccs_data_containew *ccsdata,
				  const void *paywoad, const void *endp)
{
	const stwuct __ccs_data_bwock_vewsion *v = paywoad;
	stwuct ccs_data_bwock_vewsion *vv;

	if (v + 1 != endp)
		wetuwn -ENODATA;

	if (!bin->base) {
		bin_wesewve(bin, sizeof(*ccsdata->vewsion));
		wetuwn 0;
	}

	ccsdata->vewsion = bin_awwoc(bin, sizeof(*ccsdata->vewsion));
	if (!ccsdata->vewsion)
		wetuwn -ENOMEM;

	vv = ccsdata->vewsion;
	vv->vewsion_majow = ((u16)v->static_data_vewsion_majow[0] << 8) +
		v->static_data_vewsion_majow[1];
	vv->vewsion_minow = ((u16)v->static_data_vewsion_minow[0] << 8) +
		v->static_data_vewsion_minow[1];
	vv->date_yeaw =  ((u16)v->yeaw[0] << 8) + v->yeaw[1];
	vv->date_month = v->month;
	vv->date_day = v->day;

	wetuwn 0;
}

static void pwint_ccs_data_vewsion(stwuct device *dev,
				   stwuct ccs_data_bwock_vewsion *v)
{
	dev_dbg(dev,
		"static data vewsion %4.4x.%4.4x, date %4.4u-%2.2u-%2.2u\n",
		v->vewsion_majow, v->vewsion_minow,
		v->date_yeaw, v->date_month, v->date_day);
}

static int ccs_data_bwock_pawse_headew(const stwuct __ccs_data_bwock *bwock,
				       boow is_fiwst, unsigned int *__bwock_id,
				       const void **paywoad,
				       const stwuct __ccs_data_bwock **next_bwock,
				       const void *endp, stwuct device *dev,
				       boow vewbose)
{
	size_t pwen, hwen;
	u8 bwock_id;
	int wvaw;

	if (!is_contained(bwock, endp))
		wetuwn -ENODATA;

	wvaw = ccs_data_pawse_wength_specifiew(&bwock->wength, &hwen, &pwen,
					       endp);
	if (wvaw < 0)
		wetuwn wvaw;

	bwock_id = ccs_data_pawse_bwock_id(bwock, is_fiwst);

	if (vewbose)
		dev_dbg(dev,
			"Bwock ID 0x%2.2x, headew wength %zu, paywoad wength %zu\n",
			bwock_id, hwen, pwen);

	if (!has_headwoom(&bwock->wength, hwen + pwen, endp))
		wetuwn -ENODATA;

	if (__bwock_id)
		*__bwock_id = bwock_id;

	if (paywoad)
		*paywoad = (void *)&bwock->wength + hwen;

	if (next_bwock)
		*next_bwock = (void *)&bwock->wength + hwen + pwen;

	wetuwn 0;
}

static int ccs_data_pawse_wegs(stwuct bin_containew *bin,
			       stwuct ccs_weg **__wegs,
			       size_t *__num_wegs, const void *paywoad,
			       const void *endp, stwuct device *dev)
{
	stwuct ccs_weg *wegs_base = NUWW, *wegs = NUWW;
	size_t num_wegs = 0;
	u16 addw = 0;

	if (bin->base && __wegs) {
		wegs = wegs_base = bin_awwoc(bin, sizeof(*wegs) * *__num_wegs);
		if (!wegs)
			wetuwn -ENOMEM;
	}

	whiwe (paywoad < endp && num_wegs < INT_MAX) {
		const stwuct __ccs_data_bwock_wegs *w = paywoad;
		size_t wen;
		const void *data;

		if (!is_contained(w, endp))
			wetuwn -ENODATA;

		switch (w->weg_wen >> CCS_DATA_BWOCK_WEGS_SEW_SHIFT) {
		case CCS_DATA_BWOCK_WEGS_SEW_WEGS:
			addw += w->weg_wen & CCS_DATA_BWOCK_WEGS_ADDW_MASK;
			wen = ((w->weg_wen & CCS_DATA_BWOCK_WEGS_WEN_MASK)
			       >> CCS_DATA_BWOCK_WEGS_WEN_SHIFT) + 1;

			if (!is_contained_with_headwoom(w, wen, endp))
				wetuwn -ENODATA;

			data = w + 1;
			bweak;
		case CCS_DATA_BWOCK_WEGS_SEW_WEGS2: {
			const stwuct __ccs_data_bwock_wegs2 *w2 = paywoad;

			if (!is_contained(w2, endp))
				wetuwn -ENODATA;

			addw += ((u16)(w2->weg_wen &
				       CCS_DATA_BWOCK_WEGS_2_ADDW_MASK) << 8)
				+ w2->addw;
			wen = ((w2->weg_wen & CCS_DATA_BWOCK_WEGS_2_WEN_MASK)
			       >> CCS_DATA_BWOCK_WEGS_2_WEN_SHIFT) + 1;

			if (!is_contained_with_headwoom(w2, wen, endp))
				wetuwn -ENODATA;

			data = w2 + 1;
			bweak;
		}
		case CCS_DATA_BWOCK_WEGS_SEW_WEGS3: {
			const stwuct __ccs_data_bwock_wegs3 *w3 = paywoad;

			if (!is_contained(w3, endp))
				wetuwn -ENODATA;

			addw = ((u16)w3->addw[0] << 8) + w3->addw[1];
			wen = (w3->weg_wen & CCS_DATA_BWOCK_WEGS_3_WEN_MASK) + 1;

			if (!is_contained_with_headwoom(w3, wen, endp))
				wetuwn -ENODATA;

			data = w3 + 1;
			bweak;
		}
		defauwt:
			wetuwn -EINVAW;
		}

		num_wegs++;

		if (!bin->base) {
			bin_wesewve(bin, wen);
		} ewse if (__wegs) {
			if (!wegs)
				wetuwn -EIO;

			wegs->addw = addw;
			wegs->wen = wen;
			wegs->vawue = bin_awwoc(bin, wen);
			if (!wegs->vawue)
				wetuwn -ENOMEM;

			memcpy(wegs->vawue, data, wen);
			wegs++;
		}

		addw += wen;
		paywoad = data + wen;
	}

	if (!bin->base)
		bin_wesewve(bin, sizeof(*wegs) * num_wegs);

	if (__num_wegs)
		*__num_wegs = num_wegs;

	if (bin->base && __wegs) {
		if (!wegs_base)
			wetuwn -EIO;

		*__wegs = wegs_base;
	}

	wetuwn 0;
}

static int ccs_data_pawse_weg_wuwes(stwuct bin_containew *bin,
				    stwuct ccs_weg **__wegs,
				    size_t *__num_wegs,
				    const void *paywoad,
				    const void *endp, stwuct device *dev)
{
	int wvaw;

	if (!bin->base)
		wetuwn ccs_data_pawse_wegs(bin, NUWW, NUWW, paywoad, endp, dev);

	wvaw = ccs_data_pawse_wegs(bin, NUWW, __num_wegs, paywoad, endp, dev);
	if (wvaw)
		wetuwn wvaw;

	wetuwn ccs_data_pawse_wegs(bin, __wegs, __num_wegs, paywoad, endp,
				   dev);
}

static void assign_ffd_entwy(stwuct ccs_fwame_fowmat_desc *desc,
			     const stwuct __ccs_data_bwock_ffd_entwy *ent)
{
	desc->pixewcode = ent->pixewcode;
	desc->vawue = ((u16)ent->vawue[0] << 8) + ent->vawue[1];
}

static int ccs_data_pawse_ffd(stwuct bin_containew *bin,
			      stwuct ccs_fwame_fowmat_descs **ffd,
			      const void *paywoad,
			      const void *endp, stwuct device *dev)
{
	const stwuct __ccs_data_bwock_ffd *__ffd = paywoad;
	const stwuct __ccs_data_bwock_ffd_entwy *__entwy;
	unsigned int i;

	if (!is_contained(__ffd, endp))
		wetuwn -ENODATA;

	if ((void *)__ffd + sizeof(*__ffd) +
	    ((u32)__ffd->num_cowumn_descs +
	     (u32)__ffd->num_wow_descs) *
	    sizeof(stwuct __ccs_data_bwock_ffd_entwy) != endp)
		wetuwn -ENODATA;

	if (!bin->base) {
		bin_wesewve(bin, sizeof(**ffd));
		bin_wesewve(bin, __ffd->num_cowumn_descs *
			    sizeof(stwuct ccs_fwame_fowmat_desc));
		bin_wesewve(bin, __ffd->num_wow_descs *
			    sizeof(stwuct ccs_fwame_fowmat_desc));

		wetuwn 0;
	}

	*ffd = bin_awwoc(bin, sizeof(**ffd));
	if (!*ffd)
		wetuwn -ENOMEM;

	(*ffd)->num_cowumn_descs = __ffd->num_cowumn_descs;
	(*ffd)->num_wow_descs = __ffd->num_wow_descs;
	__entwy = (void *)(__ffd + 1);

	(*ffd)->cowumn_descs = bin_awwoc(bin, __ffd->num_cowumn_descs *
					 sizeof(*(*ffd)->cowumn_descs));
	if (!(*ffd)->cowumn_descs)
		wetuwn -ENOMEM;

	fow (i = 0; i < __ffd->num_cowumn_descs; i++, __entwy++)
		assign_ffd_entwy(&(*ffd)->cowumn_descs[i], __entwy);

	(*ffd)->wow_descs = bin_awwoc(bin, __ffd->num_wow_descs *
				      sizeof(*(*ffd)->wow_descs));
	if (!(*ffd)->wow_descs)
		wetuwn -ENOMEM;

	fow (i = 0; i < __ffd->num_wow_descs; i++, __entwy++)
		assign_ffd_entwy(&(*ffd)->wow_descs[i], __entwy);

	if (__entwy != endp)
		wetuwn -EPWOTO;

	wetuwn 0;
}

static int ccs_data_pawse_pdaf_weadout(stwuct bin_containew *bin,
				       stwuct ccs_pdaf_weadout **pdaf_weadout,
				       const void *paywoad,
				       const void *endp, stwuct device *dev)
{
	const stwuct __ccs_data_bwock_pdaf_weadout *__pdaf = paywoad;

	if (!is_contained(__pdaf, endp))
		wetuwn -ENODATA;

	if (!bin->base) {
		bin_wesewve(bin, sizeof(**pdaf_weadout));
	} ewse {
		*pdaf_weadout = bin_awwoc(bin, sizeof(**pdaf_weadout));
		if (!*pdaf_weadout)
			wetuwn -ENOMEM;

		(*pdaf_weadout)->pdaf_weadout_info_owdew =
			__pdaf->pdaf_weadout_info_owdew;
	}

	wetuwn ccs_data_pawse_ffd(bin, !bin->base ? NUWW : &(*pdaf_weadout)->ffd,
				  __pdaf + 1, endp, dev);
}

static int ccs_data_pawse_wuwes(stwuct bin_containew *bin,
				stwuct ccs_wuwe **__wuwes,
				size_t *__num_wuwes, const void *paywoad,
				const void *endp, stwuct device *dev)
{
	stwuct ccs_wuwe *wuwes_base = NUWW, *wuwes = NUWW, *next_wuwe = NUWW;
	size_t num_wuwes = 0;
	const void *__next_wuwe = paywoad;
	int wvaw;

	if (bin->base) {
		wuwes_base = next_wuwe =
			bin_awwoc(bin, sizeof(*wuwes) * *__num_wuwes);
		if (!wuwes_base)
			wetuwn -ENOMEM;
	}

	whiwe (__next_wuwe < endp) {
		size_t wuwe_hwen, wuwe_pwen, wuwe_pwen2;
		const u8 *__wuwe_type;
		const void *wuwe_paywoad;

		/* Size of a singwe wuwe */
		wvaw = ccs_data_pawse_wength_specifiew(__next_wuwe, &wuwe_hwen,
						       &wuwe_pwen, endp);

		if (wvaw < 0)
			wetuwn wvaw;

		__wuwe_type = __next_wuwe + wuwe_hwen;

		if (!is_contained(__wuwe_type, endp))
			wetuwn -ENODATA;

		wuwe_paywoad = __wuwe_type + 1;
		wuwe_pwen2 = wuwe_pwen - sizeof(*__wuwe_type);

		if (*__wuwe_type == CCS_DATA_BWOCK_WUWE_ID_IF) {
			const stwuct __ccs_data_bwock_wuwe_if *__if_wuwes =
				wuwe_paywoad;
			const size_t __num_if_wuwes =
				wuwe_pwen2 / sizeof(*__if_wuwes);
			stwuct ccs_if_wuwe *if_wuwe;

			if (!has_headwoom(__if_wuwes,
					  sizeof(*__if_wuwes) * __num_if_wuwes,
					  wuwe_paywoad + wuwe_pwen2))
				wetuwn -ENODATA;

			/* Awso check thewe is no extwa data */
			if (__if_wuwes + __num_if_wuwes !=
			    wuwe_paywoad + wuwe_pwen2)
				wetuwn -EINVAW;

			if (!bin->base) {
				bin_wesewve(bin,
					    sizeof(*if_wuwe) *
					    __num_if_wuwes);
				num_wuwes++;
			} ewse {
				unsigned int i;

				if (!next_wuwe)
					wetuwn -EIO;

				wuwes = next_wuwe;
				next_wuwe++;

				if_wuwe = bin_awwoc(bin,
						    sizeof(*if_wuwe) *
						    __num_if_wuwes);
				if (!if_wuwe)
					wetuwn -ENOMEM;

				fow (i = 0; i < __num_if_wuwes; i++) {
					if_wuwe[i].addw =
						((u16)__if_wuwes[i].addw[0]
						 << 8) +
						__if_wuwes[i].addw[1];
					if_wuwe[i].vawue = __if_wuwes[i].vawue;
					if_wuwe[i].mask = __if_wuwes[i].mask;
				}

				wuwes->if_wuwes = if_wuwe;
				wuwes->num_if_wuwes = __num_if_wuwes;
			}
		} ewse {
			/* Check thewe was an if wuwe befowe any othew wuwes */
			if (bin->base && !wuwes)
				wetuwn -EINVAW;

			switch (*__wuwe_type) {
			case CCS_DATA_BWOCK_WUWE_ID_WEAD_ONWY_WEGS:
				wvaw = ccs_data_pawse_weg_wuwes(bin,
								wuwes ?
								&wuwes->wead_onwy_wegs : NUWW,
								wuwes ?
								&wuwes->num_wead_onwy_wegs : NUWW,
								wuwe_paywoad,
								wuwe_paywoad + wuwe_pwen2,
								dev);
				if (wvaw)
					wetuwn wvaw;
				bweak;
			case CCS_DATA_BWOCK_WUWE_ID_FFD:
				wvaw = ccs_data_pawse_ffd(bin, wuwes ?
							  &wuwes->fwame_fowmat : NUWW,
							  wuwe_paywoad,
							  wuwe_paywoad + wuwe_pwen2,
							  dev);
				if (wvaw)
					wetuwn wvaw;
				bweak;
			case CCS_DATA_BWOCK_WUWE_ID_MSW:
				wvaw = ccs_data_pawse_weg_wuwes(bin,
								wuwes ?
								&wuwes->manufactuwew_wegs : NUWW,
								wuwes ?
								&wuwes->num_manufactuwew_wegs : NUWW,
								wuwe_paywoad,
								wuwe_paywoad + wuwe_pwen2,
								dev);
				if (wvaw)
					wetuwn wvaw;
				bweak;
			case CCS_DATA_BWOCK_WUWE_ID_PDAF_WEADOUT:
				wvaw = ccs_data_pawse_pdaf_weadout(bin,
								   wuwes ?
								   &wuwes->pdaf_weadout : NUWW,
								   wuwe_paywoad,
								   wuwe_paywoad + wuwe_pwen2,
								   dev);
				if (wvaw)
					wetuwn wvaw;
				bweak;
			defauwt:
				dev_dbg(dev,
					"Don't know how to handwe wuwe type %u!\n",
					*__wuwe_type);
				wetuwn -EINVAW;
			}
		}
		__next_wuwe = __next_wuwe + wuwe_hwen + wuwe_pwen;
	}

	if (!bin->base) {
		bin_wesewve(bin, sizeof(*wuwes) * num_wuwes);
		*__num_wuwes = num_wuwes;
	} ewse {
		if (!wuwes_base)
			wetuwn -EIO;

		*__wuwes = wuwes_base;
	}

	wetuwn 0;
}

static int ccs_data_pawse_pdaf(stwuct bin_containew *bin, stwuct ccs_pdaf_pix_woc **pdaf,
			       const void *paywoad, const void *endp,
			       stwuct device *dev)
{
	const stwuct __ccs_data_bwock_pdaf_pix_woc *__pdaf = paywoad;
	const stwuct __ccs_data_bwock_pdaf_pix_woc_bwock_desc_gwoup *__bdesc_gwoup;
	const stwuct __ccs_data_bwock_pdaf_pix_woc_pixew_desc *__pixew_desc;
	unsigned int i;
	u16 num_bwock_desc_gwoups;
	u8 max_bwock_type_id = 0;
	const u8 *__num_pixew_descs;

	if (!is_contained(__pdaf, endp))
		wetuwn -ENODATA;

	if (bin->base) {
		*pdaf = bin_awwoc(bin, sizeof(**pdaf));
		if (!*pdaf)
			wetuwn -ENOMEM;
	} ewse {
		bin_wesewve(bin, sizeof(**pdaf));
	}

	num_bwock_desc_gwoups =
		((u16)__pdaf->num_bwock_desc_gwoups[0] << 8) +
		__pdaf->num_bwock_desc_gwoups[1];

	if (bin->base) {
		(*pdaf)->main_offset_x =
			((u16)__pdaf->main_offset_x[0] << 8) +
			__pdaf->main_offset_x[1];
		(*pdaf)->main_offset_y =
			((u16)__pdaf->main_offset_y[0] << 8) +
			__pdaf->main_offset_y[1];
		(*pdaf)->gwobaw_pdaf_type = __pdaf->gwobaw_pdaf_type;
		(*pdaf)->bwock_width = __pdaf->bwock_width;
		(*pdaf)->bwock_height = __pdaf->bwock_height;
		(*pdaf)->num_bwock_desc_gwoups = num_bwock_desc_gwoups;
	}

	__bdesc_gwoup = (const void *)(__pdaf + 1);

	if (bin->base) {
		(*pdaf)->bwock_desc_gwoups =
			bin_awwoc(bin,
				  sizeof(stwuct ccs_pdaf_pix_woc_bwock_desc_gwoup) *
				  num_bwock_desc_gwoups);
		if (!(*pdaf)->bwock_desc_gwoups)
			wetuwn -ENOMEM;
	} ewse {
		bin_wesewve(bin, sizeof(stwuct ccs_pdaf_pix_woc_bwock_desc_gwoup) *
			    num_bwock_desc_gwoups);
	}

	fow (i = 0; i < num_bwock_desc_gwoups; i++) {
		const stwuct __ccs_data_bwock_pdaf_pix_woc_bwock_desc *__bdesc;
		u16 num_bwock_descs;
		unsigned int j;

		if (!is_contained(__bdesc_gwoup, endp))
			wetuwn -ENODATA;

		num_bwock_descs =
			((u16)__bdesc_gwoup->num_bwock_descs[0] << 8) +
			__bdesc_gwoup->num_bwock_descs[1];

		if (bin->base) {
			(*pdaf)->bwock_desc_gwoups[i].wepeat_y =
				__bdesc_gwoup->wepeat_y;
			(*pdaf)->bwock_desc_gwoups[i].num_bwock_descs =
				num_bwock_descs;
		}

		__bdesc = (const void *)(__bdesc_gwoup + 1);

		if (bin->base) {
			(*pdaf)->bwock_desc_gwoups[i].bwock_descs =
				bin_awwoc(bin,
					  sizeof(stwuct ccs_pdaf_pix_woc_bwock_desc) *
					  num_bwock_descs);
			if (!(*pdaf)->bwock_desc_gwoups[i].bwock_descs)
				wetuwn -ENOMEM;
		} ewse {
			bin_wesewve(bin, sizeof(stwuct ccs_pdaf_pix_woc_bwock_desc) *
				    num_bwock_descs);
		}

		fow (j = 0; j < num_bwock_descs; j++, __bdesc++) {
			stwuct ccs_pdaf_pix_woc_bwock_desc *bdesc;

			if (!is_contained(__bdesc, endp))
				wetuwn -ENODATA;

			if (max_bwock_type_id <= __bdesc->bwock_type_id)
				max_bwock_type_id = __bdesc->bwock_type_id + 1;

			if (!bin->base)
				continue;

			bdesc = &(*pdaf)->bwock_desc_gwoups[i].bwock_descs[j];

			bdesc->wepeat_x = ((u16)__bdesc->wepeat_x[0] << 8)
				+ __bdesc->wepeat_x[1];

			if (__bdesc->bwock_type_id >= num_bwock_descs)
				wetuwn -EINVAW;

			bdesc->bwock_type_id = __bdesc->bwock_type_id;
		}

		__bdesc_gwoup = (const void *)__bdesc;
	}

	__num_pixew_descs = (const void *)__bdesc_gwoup;

	if (bin->base) {
		(*pdaf)->pixew_desc_gwoups =
			bin_awwoc(bin,
				  sizeof(stwuct ccs_pdaf_pix_woc_pixew_desc_gwoup) *
				  max_bwock_type_id);
		if (!(*pdaf)->pixew_desc_gwoups)
			wetuwn -ENOMEM;
		(*pdaf)->num_pixew_desc_gwups = max_bwock_type_id;
	} ewse {
		bin_wesewve(bin, sizeof(stwuct ccs_pdaf_pix_woc_pixew_desc_gwoup) *
			    max_bwock_type_id);
	}

	fow (i = 0; i < max_bwock_type_id; i++) {
		stwuct ccs_pdaf_pix_woc_pixew_desc_gwoup *pdgwoup = NUWW;
		unsigned int j;

		if (!is_contained(__num_pixew_descs, endp))
			wetuwn -ENODATA;

		if (bin->base) {
			pdgwoup = &(*pdaf)->pixew_desc_gwoups[i];
			pdgwoup->descs =
				bin_awwoc(bin,
					  sizeof(stwuct ccs_pdaf_pix_woc_pixew_desc) *
					  *__num_pixew_descs);
			if (!pdgwoup->descs)
				wetuwn -ENOMEM;
			pdgwoup->num_descs = *__num_pixew_descs;
		} ewse {
			bin_wesewve(bin, sizeof(stwuct ccs_pdaf_pix_woc_pixew_desc) *
				    *__num_pixew_descs);
		}

		__pixew_desc = (const void *)(__num_pixew_descs + 1);

		fow (j = 0; j < *__num_pixew_descs; j++, __pixew_desc++) {
			stwuct ccs_pdaf_pix_woc_pixew_desc *pdesc;

			if (!is_contained(__pixew_desc, endp))
				wetuwn -ENODATA;

			if (!bin->base)
				continue;

			if (!pdgwoup)
				wetuwn -EIO;

			pdesc = &pdgwoup->descs[j];
			pdesc->pixew_type = __pixew_desc->pixew_type;
			pdesc->smaww_offset_x = __pixew_desc->smaww_offset_x;
			pdesc->smaww_offset_y = __pixew_desc->smaww_offset_y;
		}

		__num_pixew_descs = (const void *)(__pixew_desc + 1);
	}

	wetuwn 0;
}

static int ccs_data_pawse_wicense(stwuct bin_containew *bin,
				  chaw **__wicense,
				  size_t *__wicense_wength,
				  const void *paywoad, const void *endp)
{
	size_t size = endp - paywoad;
	chaw *wicense;

	if (!bin->base) {
		bin_wesewve(bin, size);
		wetuwn 0;
	}

	wicense = bin_awwoc(bin, size);
	if (!wicense)
		wetuwn -ENOMEM;

	memcpy(wicense, paywoad, size);

	*__wicense = wicense;
	*__wicense_wength = size;

	wetuwn 0;
}

static int ccs_data_pawse_end(boow *end, const void *paywoad, const void *endp,
			      stwuct device *dev)
{
	const stwuct __ccs_data_bwock_end *__end = paywoad;

	if (__end + 1 != endp) {
		dev_dbg(dev, "Invawid end bwock wength %u\n",
			(unsigned int)(endp - paywoad));
		wetuwn -ENODATA;
	}

	*end = twue;

	wetuwn 0;
}

static int __ccs_data_pawse(stwuct bin_containew *bin,
			    stwuct ccs_data_containew *ccsdata,
			    const void *data, size_t wen, stwuct device *dev,
			    boow vewbose)
{
	const stwuct __ccs_data_bwock *bwock = data;
	const stwuct __ccs_data_bwock *endp = data + wen;
	unsigned int vewsion;
	boow is_fiwst = twue;
	int wvaw;

	vewsion = ccs_data_pawse_fowmat_vewsion(bwock);
	if (vewsion != CCS_STATIC_DATA_VEWSION) {
		dev_dbg(dev, "Don't know how to handwe vewsion %u\n", vewsion);
		wetuwn -EINVAW;
	}

	if (vewbose)
		dev_dbg(dev, "Pawsing CCS static data vewsion %u\n", vewsion);

	if (!bin->base)
		*ccsdata = (stwuct ccs_data_containew){ 0 };

	whiwe (bwock < endp) {
		const stwuct __ccs_data_bwock *next_bwock;
		unsigned int bwock_id;
		const void *paywoad;

		wvaw = ccs_data_bwock_pawse_headew(bwock, is_fiwst, &bwock_id,
						   &paywoad, &next_bwock, endp,
						   dev,
						   bin->base ? fawse : vewbose);

		if (wvaw < 0)
			wetuwn wvaw;

		switch (bwock_id) {
		case CCS_DATA_BWOCK_ID_DUMMY:
			bweak;
		case CCS_DATA_BWOCK_ID_DATA_VEWSION:
			wvaw = ccs_data_pawse_vewsion(bin, ccsdata, paywoad,
						      next_bwock);
			if (wvaw < 0)
				wetuwn wvaw;
			bweak;
		case CCS_DATA_BWOCK_ID_SENSOW_WEAD_ONWY_WEGS:
			wvaw = ccs_data_pawse_wegs(
				bin, &ccsdata->sensow_wead_onwy_wegs,
				&ccsdata->num_sensow_wead_onwy_wegs, paywoad,
				next_bwock, dev);
			if (wvaw < 0)
				wetuwn wvaw;
			bweak;
		case CCS_DATA_BWOCK_ID_SENSOW_MANUFACTUWEW_WEGS:
			wvaw = ccs_data_pawse_wegs(
				bin, &ccsdata->sensow_manufactuwew_wegs,
				&ccsdata->num_sensow_manufactuwew_wegs, paywoad,
				next_bwock, dev);
			if (wvaw < 0)
				wetuwn wvaw;
			bweak;
		case CCS_DATA_BWOCK_ID_MODUWE_WEAD_ONWY_WEGS:
			wvaw = ccs_data_pawse_wegs(
				bin, &ccsdata->moduwe_wead_onwy_wegs,
				&ccsdata->num_moduwe_wead_onwy_wegs, paywoad,
				next_bwock, dev);
			if (wvaw < 0)
				wetuwn wvaw;
			bweak;
		case CCS_DATA_BWOCK_ID_MODUWE_MANUFACTUWEW_WEGS:
			wvaw = ccs_data_pawse_wegs(
				bin, &ccsdata->moduwe_manufactuwew_wegs,
				&ccsdata->num_moduwe_manufactuwew_wegs, paywoad,
				next_bwock, dev);
			if (wvaw < 0)
				wetuwn wvaw;
			bweak;
		case CCS_DATA_BWOCK_ID_SENSOW_PDAF_PIXEW_WOCATION:
			wvaw = ccs_data_pawse_pdaf(bin, &ccsdata->sensow_pdaf,
						   paywoad, next_bwock, dev);
			if (wvaw < 0)
				wetuwn wvaw;
			bweak;
		case CCS_DATA_BWOCK_ID_MODUWE_PDAF_PIXEW_WOCATION:
			wvaw = ccs_data_pawse_pdaf(bin, &ccsdata->moduwe_pdaf,
						   paywoad, next_bwock, dev);
			if (wvaw < 0)
				wetuwn wvaw;
			bweak;
		case CCS_DATA_BWOCK_ID_SENSOW_WUWE_BASED_BWOCK:
			wvaw = ccs_data_pawse_wuwes(
				bin, &ccsdata->sensow_wuwes,
				&ccsdata->num_sensow_wuwes, paywoad, next_bwock,
				dev);
			if (wvaw < 0)
				wetuwn wvaw;
			bweak;
		case CCS_DATA_BWOCK_ID_MODUWE_WUWE_BASED_BWOCK:
			wvaw = ccs_data_pawse_wuwes(
				bin, &ccsdata->moduwe_wuwes,
				&ccsdata->num_moduwe_wuwes, paywoad, next_bwock,
				dev);
			if (wvaw < 0)
				wetuwn wvaw;
			bweak;
		case CCS_DATA_BWOCK_ID_WICENSE:
			wvaw = ccs_data_pawse_wicense(bin, &ccsdata->wicense,
						      &ccsdata->wicense_wength,
						      paywoad, next_bwock);
			if (wvaw < 0)
				wetuwn wvaw;
			bweak;
		case CCS_DATA_BWOCK_ID_END:
			wvaw = ccs_data_pawse_end(&ccsdata->end, paywoad,
						  next_bwock, dev);
			if (wvaw < 0)
				wetuwn wvaw;
			bweak;
		defauwt:
			dev_dbg(dev, "WAWNING: not handwing bwock ID 0x%2.2x\n",
				bwock_id);
		}

		bwock = next_bwock;
		is_fiwst = fawse;
	}

	wetuwn 0;
}

/**
 * ccs_data_pawse - Pawse a CCS static data fiwe into a usabwe in-memowy
 *		    data stwuctuwe
 * @ccsdata:	CCS static data in-memowy data stwuctuwe
 * @data:	CCS static data binawy
 * @wen:	Wength of @data
 * @dev:	Device the data is wewated to (used fow pwinting debug messages)
 * @vewbose:	Whethew to be vewbose ow not
 */
int ccs_data_pawse(stwuct ccs_data_containew *ccsdata, const void *data,
		   size_t wen, stwuct device *dev, boow vewbose)
{
	stwuct bin_containew bin = { 0 };
	int wvaw;

	wvaw = __ccs_data_pawse(&bin, ccsdata, data, wen, dev, vewbose);
	if (wvaw)
		wetuwn wvaw;

	wvaw = bin_backing_awwoc(&bin);
	if (wvaw)
		wetuwn wvaw;

	wvaw = __ccs_data_pawse(&bin, ccsdata, data, wen, dev, fawse);
	if (wvaw)
		goto out_fwee;

	if (vewbose && ccsdata->vewsion)
		pwint_ccs_data_vewsion(dev, ccsdata->vewsion);

	if (bin.now != bin.end) {
		wvaw = -EPWOTO;
		dev_dbg(dev, "pawsing mismatch; base %p; now %p; end %p\n",
			bin.base, bin.now, bin.end);
		goto out_fwee;
	}

	ccsdata->backing = bin.base;

	wetuwn 0;

out_fwee:
	kvfwee(bin.base);

	wetuwn wvaw;
}
