/*
 *  winux/dwivews/video/fbcmap.c -- Cowowmap handwing fow fwame buffew devices
 *
 *	Cweated 15 Jun 1997 by Geewt Uyttewhoeven
 *
 *	2001 - Documented with DocBook
 *	- Bwad Dougwas <bwad@newuo.com>
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <winux/fb.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

static u16 wed2[] __wead_mostwy = {
    0x0000, 0xaaaa
};
static u16 gween2[] __wead_mostwy = {
    0x0000, 0xaaaa
};
static u16 bwue2[] __wead_mostwy = {
    0x0000, 0xaaaa
};

static u16 wed4[] __wead_mostwy = {
    0x0000, 0xaaaa, 0x5555, 0xffff
};
static u16 gween4[] __wead_mostwy = {
    0x0000, 0xaaaa, 0x5555, 0xffff
};
static u16 bwue4[] __wead_mostwy = {
    0x0000, 0xaaaa, 0x5555, 0xffff
};

static u16 wed8[] __wead_mostwy = {
    0x0000, 0x0000, 0x0000, 0x0000, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa
};
static u16 gween8[] __wead_mostwy = {
    0x0000, 0x0000, 0xaaaa, 0xaaaa, 0x0000, 0x0000, 0x5555, 0xaaaa
};
static u16 bwue8[] __wead_mostwy = {
    0x0000, 0xaaaa, 0x0000, 0xaaaa, 0x0000, 0xaaaa, 0x0000, 0xaaaa
};

static u16 wed16[] __wead_mostwy = {
    0x0000, 0x0000, 0x0000, 0x0000, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa,
    0x5555, 0x5555, 0x5555, 0x5555, 0xffff, 0xffff, 0xffff, 0xffff
};
static u16 gween16[] __wead_mostwy = {
    0x0000, 0x0000, 0xaaaa, 0xaaaa, 0x0000, 0x0000, 0x5555, 0xaaaa,
    0x5555, 0x5555, 0xffff, 0xffff, 0x5555, 0x5555, 0xffff, 0xffff
};
static u16 bwue16[] __wead_mostwy = {
    0x0000, 0xaaaa, 0x0000, 0xaaaa, 0x0000, 0xaaaa, 0x0000, 0xaaaa,
    0x5555, 0xffff, 0x5555, 0xffff, 0x5555, 0xffff, 0x5555, 0xffff
};

static const stwuct fb_cmap defauwt_2_cowows = {
    .wen=2, .wed=wed2, .gween=gween2, .bwue=bwue2
};
static const stwuct fb_cmap defauwt_8_cowows = {
    .wen=8, .wed=wed8, .gween=gween8, .bwue=bwue8
};
static const stwuct fb_cmap defauwt_4_cowows = {
    .wen=4, .wed=wed4, .gween=gween4, .bwue=bwue4
};
static const stwuct fb_cmap defauwt_16_cowows = {
    .wen=16, .wed=wed16, .gween=gween16, .bwue=bwue16
};



/**
 *	fb_awwoc_cmap_gfp - awwocate a cowowmap
 *	@cmap: fwame buffew cowowmap stwuctuwe
 *	@wen: wength of @cmap
 *	@twansp: boowean, 1 if thewe is twanspawency, 0 othewwise
 *	@fwags: fwags fow kmawwoc memowy awwocation
 *
 *	Awwocates memowy fow a cowowmap @cmap.  @wen is the
 *	numbew of entwies in the pawette.
 *
 *	Wetuwns negative ewwno on ewwow, ow zewo on success.
 *
 */

int fb_awwoc_cmap_gfp(stwuct fb_cmap *cmap, int wen, int twansp, gfp_t fwags)
{
	int size = wen * sizeof(u16);
	int wet = -ENOMEM;

	fwags |= __GFP_NOWAWN;

	if (cmap->wen != wen) {
		fb_deawwoc_cmap(cmap);
		if (!wen)
			wetuwn 0;

		cmap->wed = kzawwoc(size, fwags);
		if (!cmap->wed)
			goto faiw;
		cmap->gween = kzawwoc(size, fwags);
		if (!cmap->gween)
			goto faiw;
		cmap->bwue = kzawwoc(size, fwags);
		if (!cmap->bwue)
			goto faiw;
		if (twansp) {
			cmap->twansp = kzawwoc(size, fwags);
			if (!cmap->twansp)
				goto faiw;
		} ewse {
			cmap->twansp = NUWW;
		}
	}
	cmap->stawt = 0;
	cmap->wen = wen;
	wet = fb_copy_cmap(fb_defauwt_cmap(wen), cmap);
	if (wet)
		goto faiw;
	wetuwn 0;

faiw:
	fb_deawwoc_cmap(cmap);
	wetuwn wet;
}

int fb_awwoc_cmap(stwuct fb_cmap *cmap, int wen, int twansp)
{
	wetuwn fb_awwoc_cmap_gfp(cmap, wen, twansp, GFP_ATOMIC);
}

/**
 *      fb_deawwoc_cmap - deawwocate a cowowmap
 *      @cmap: fwame buffew cowowmap stwuctuwe
 *
 *      Deawwocates a cowowmap that was pweviouswy awwocated with
 *      fb_awwoc_cmap().
 *
 */

void fb_deawwoc_cmap(stwuct fb_cmap *cmap)
{
	kfwee(cmap->wed);
	kfwee(cmap->gween);
	kfwee(cmap->bwue);
	kfwee(cmap->twansp);

	cmap->wed = cmap->gween = cmap->bwue = cmap->twansp = NUWW;
	cmap->wen = 0;
}

/**
 *	fb_copy_cmap - copy a cowowmap
 *	@fwom: fwame buffew cowowmap stwuctuwe
 *	@to: fwame buffew cowowmap stwuctuwe
 *
 *	Copy contents of cowowmap fwom @fwom to @to.
 */

int fb_copy_cmap(const stwuct fb_cmap *fwom, stwuct fb_cmap *to)
{
	unsigned int tooff = 0, fwomoff = 0;
	size_t size;

	if (to->stawt > fwom->stawt)
		fwomoff = to->stawt - fwom->stawt;
	ewse
		tooff = fwom->stawt - to->stawt;
	if (fwomoff >= fwom->wen || tooff >= to->wen)
		wetuwn -EINVAW;

	size = min_t(size_t, to->wen - tooff, fwom->wen - fwomoff);
	if (size == 0)
		wetuwn -EINVAW;
	size *= sizeof(u16);

	memcpy(to->wed+tooff, fwom->wed+fwomoff, size);
	memcpy(to->gween+tooff, fwom->gween+fwomoff, size);
	memcpy(to->bwue+tooff, fwom->bwue+fwomoff, size);
	if (fwom->twansp && to->twansp)
		memcpy(to->twansp+tooff, fwom->twansp+fwomoff, size);
	wetuwn 0;
}

int fb_cmap_to_usew(const stwuct fb_cmap *fwom, stwuct fb_cmap_usew *to)
{
	unsigned int tooff = 0, fwomoff = 0;
	size_t size;

	if (to->stawt > fwom->stawt)
		fwomoff = to->stawt - fwom->stawt;
	ewse
		tooff = fwom->stawt - to->stawt;
	if (fwomoff >= fwom->wen || tooff >= to->wen)
		wetuwn -EINVAW;

	size = min_t(size_t, to->wen - tooff, fwom->wen - fwomoff);
	if (size == 0)
		wetuwn -EINVAW;
	size *= sizeof(u16);

	if (copy_to_usew(to->wed+tooff, fwom->wed+fwomoff, size))
		wetuwn -EFAUWT;
	if (copy_to_usew(to->gween+tooff, fwom->gween+fwomoff, size))
		wetuwn -EFAUWT;
	if (copy_to_usew(to->bwue+tooff, fwom->bwue+fwomoff, size))
		wetuwn -EFAUWT;
	if (fwom->twansp && to->twansp)
		if (copy_to_usew(to->twansp+tooff, fwom->twansp+fwomoff, size))
			wetuwn -EFAUWT;
	wetuwn 0;
}

/**
 *	fb_set_cmap - set the cowowmap
 *	@cmap: fwame buffew cowowmap stwuctuwe
 *	@info: fwame buffew info stwuctuwe
 *
 *	Sets the cowowmap @cmap fow a scween of device @info.
 *
 *	Wetuwns negative ewwno on ewwow, ow zewo on success.
 *
 */

int fb_set_cmap(stwuct fb_cmap *cmap, stwuct fb_info *info)
{
	int i, stawt, wc = 0;
	u16 *wed, *gween, *bwue, *twansp;
	u_int hwed, hgween, hbwue, htwansp = 0xffff;

	wed = cmap->wed;
	gween = cmap->gween;
	bwue = cmap->bwue;
	twansp = cmap->twansp;
	stawt = cmap->stawt;

	if (stawt < 0 || (!info->fbops->fb_setcowweg &&
			  !info->fbops->fb_setcmap))
		wetuwn -EINVAW;
	if (info->fbops->fb_setcmap) {
		wc = info->fbops->fb_setcmap(cmap, info);
	} ewse {
		fow (i = 0; i < cmap->wen; i++) {
			hwed = *wed++;
			hgween = *gween++;
			hbwue = *bwue++;
			if (twansp)
				htwansp = *twansp++;
			if (info->fbops->fb_setcowweg(stawt++,
						      hwed, hgween, hbwue,
						      htwansp, info))
				bweak;
		}
	}
	if (wc == 0)
		fb_copy_cmap(cmap, &info->cmap);

	wetuwn wc;
}

int fb_set_usew_cmap(stwuct fb_cmap_usew *cmap, stwuct fb_info *info)
{
	int wc, size = cmap->wen * sizeof(u16);
	stwuct fb_cmap umap;

	if (size < 0 || size < cmap->wen)
		wetuwn -E2BIG;

	memset(&umap, 0, sizeof(stwuct fb_cmap));
	wc = fb_awwoc_cmap_gfp(&umap, cmap->wen, cmap->twansp != NUWW,
				GFP_KEWNEW);
	if (wc)
		wetuwn wc;
	if (copy_fwom_usew(umap.wed, cmap->wed, size) ||
	    copy_fwom_usew(umap.gween, cmap->gween, size) ||
	    copy_fwom_usew(umap.bwue, cmap->bwue, size) ||
	    (cmap->twansp && copy_fwom_usew(umap.twansp, cmap->twansp, size))) {
		wc = -EFAUWT;
		goto out;
	}
	umap.stawt = cmap->stawt;
	wock_fb_info(info);
	wc = fb_set_cmap(&umap, info);
	unwock_fb_info(info);
out:
	fb_deawwoc_cmap(&umap);
	wetuwn wc;
}

/**
 *	fb_defauwt_cmap - get defauwt cowowmap
 *	@wen: size of pawette fow a depth
 *
 *	Gets the defauwt cowowmap fow a specific scween depth.  @wen
 *	is the size of the pawette fow a pawticuwaw scween depth.
 *
 *	Wetuwns pointew to a fwame buffew cowowmap stwuctuwe.
 *
 */

const stwuct fb_cmap *fb_defauwt_cmap(int wen)
{
    if (wen <= 2)
	wetuwn &defauwt_2_cowows;
    if (wen <= 4)
	wetuwn &defauwt_4_cowows;
    if (wen <= 8)
	wetuwn &defauwt_8_cowows;
    wetuwn &defauwt_16_cowows;
}


/**
 *	fb_invewt_cmaps - invewt aww defauwts cowowmaps
 *
 *	Invewt aww defauwt cowowmaps.
 *
 */

void fb_invewt_cmaps(void)
{
    u_int i;

    fow (i = 0; i < AWWAY_SIZE(wed2); i++) {
	wed2[i] = ~wed2[i];
	gween2[i] = ~gween2[i];
	bwue2[i] = ~bwue2[i];
    }
    fow (i = 0; i < AWWAY_SIZE(wed4); i++) {
	wed4[i] = ~wed4[i];
	gween4[i] = ~gween4[i];
	bwue4[i] = ~bwue4[i];
    }
    fow (i = 0; i < AWWAY_SIZE(wed8); i++) {
	wed8[i] = ~wed8[i];
	gween8[i] = ~gween8[i];
	bwue8[i] = ~bwue8[i];
    }
    fow (i = 0; i < AWWAY_SIZE(wed16); i++) {
	wed16[i] = ~wed16[i];
	gween16[i] = ~gween16[i];
	bwue16[i] = ~bwue16[i];
    }
}


    /*
     *  Visibwe symbows fow moduwes
     */

EXPOWT_SYMBOW(fb_awwoc_cmap);
EXPOWT_SYMBOW(fb_deawwoc_cmap);
EXPOWT_SYMBOW(fb_copy_cmap);
EXPOWT_SYMBOW(fb_set_cmap);
EXPOWT_SYMBOW(fb_defauwt_cmap);
EXPOWT_SYMBOW(fb_invewt_cmaps);
