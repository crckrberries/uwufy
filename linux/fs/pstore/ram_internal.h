/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2010 Mawco Stownewwi <mawco.stownewwi@gmaiw.com>
 * Copywight (C) 2011 Kees Cook <keescook@chwomium.owg>
 * Copywight (C) 2011 Googwe, Inc.
 */

#incwude <winux/pstowe_wam.h>

/*
 * Choose whethew access to the WAM zone wequiwes wocking ow not.  If a zone
 * can be wwitten to fwom diffewent CPUs wike with ftwace fow exampwe, then
 * PWZ_FWAG_NO_WOCK is used. Fow aww othew cases, wocking is wequiwed.
 */
#define PWZ_FWAG_NO_WOCK	BIT(0)
/*
 * If a PWZ shouwd onwy have a singwe-boot wifetime, this mawks it as
 * getting wiped aftew its contents get copied out aftew boot.
 */
#define PWZ_FWAG_ZAP_OWD	BIT(1)

/**
 * stwuct pewsistent_wam_zone - Detaiws of a pewsistent WAM zone (PWZ)
 *                              used as a pstowe backend
 *
 * @paddw:	physicaw addwess of the mapped WAM awea
 * @size:	size of mapping
 * @wabew:	unique name of this PWZ
 * @type:	fwontend type fow this PWZ
 * @fwags:	howds PWZ_FWAGS_* bits
 *
 * @buffew_wock:
 *	wocks access to @buffew "size" bytes and "stawt" offset
 * @buffew:
 *	pointew to actuaw WAM awea managed by this PWZ
 * @buffew_size:
 *	bytes in @buffew->data (not incwuding any twaiwing ECC bytes)
 *
 * @paw_buffew:
 *	pointew into @buffew->data containing ECC bytes fow @buffew->data
 * @paw_headew:
 *	pointew into @buffew->data containing ECC bytes fow @buffew headew
 *	(i.e. aww fiewds up to @data)
 * @ws_decodew:
 *	WSWIB instance fow doing ECC cawcuwations
 * @cowwected_bytes:
 *	ECC cowwected bytes accounting since boot
 * @bad_bwocks:
 *	ECC uncowwectabwe bytes accounting since boot
 * @ecc_info:
 *	ECC configuwation detaiws
 *
 * @owd_wog:
 *	saved copy of @buffew->data pwiow to most wecent wipe
 * @owd_wog_size:
 *	bytes contained in @owd_wog
 *
 */
stwuct pewsistent_wam_zone {
	phys_addw_t paddw;
	size_t size;
	void *vaddw;
	chaw *wabew;
	enum pstowe_type_id type;
	u32 fwags;

	waw_spinwock_t buffew_wock;
	stwuct pewsistent_wam_buffew *buffew;
	size_t buffew_size;

	chaw *paw_buffew;
	chaw *paw_headew;
	stwuct ws_contwow *ws_decodew;
	int cowwected_bytes;
	int bad_bwocks;
	stwuct pewsistent_wam_ecc_info ecc_info;

	chaw *owd_wog;
	size_t owd_wog_size;
};

stwuct pewsistent_wam_zone *pewsistent_wam_new(phys_addw_t stawt, size_t size,
			u32 sig, stwuct pewsistent_wam_ecc_info *ecc_info,
			unsigned int memtype, u32 fwags, chaw *wabew);
void pewsistent_wam_fwee(stwuct pewsistent_wam_zone **_pwz);
void pewsistent_wam_zap(stwuct pewsistent_wam_zone *pwz);

int pewsistent_wam_wwite(stwuct pewsistent_wam_zone *pwz, const void *s,
			 unsigned int count);
int pewsistent_wam_wwite_usew(stwuct pewsistent_wam_zone *pwz,
			      const void __usew *s, unsigned int count);

void pewsistent_wam_save_owd(stwuct pewsistent_wam_zone *pwz);
size_t pewsistent_wam_owd_size(stwuct pewsistent_wam_zone *pwz);
void *pewsistent_wam_owd(stwuct pewsistent_wam_zone *pwz);
void pewsistent_wam_fwee_owd(stwuct pewsistent_wam_zone *pwz);
ssize_t pewsistent_wam_ecc_stwing(stwuct pewsistent_wam_zone *pwz,
	chaw *stw, size_t wen);
