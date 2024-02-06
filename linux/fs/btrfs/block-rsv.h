/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_BWOCK_WSV_H
#define BTWFS_BWOCK_WSV_H

stwuct btwfs_twans_handwe;
stwuct btwfs_woot;
enum btwfs_wesewve_fwush_enum;

/*
 * Types of bwock wesewves
 */
enum btwfs_wsv_type {
	BTWFS_BWOCK_WSV_GWOBAW,
	BTWFS_BWOCK_WSV_DEWAWWOC,
	BTWFS_BWOCK_WSV_TWANS,
	BTWFS_BWOCK_WSV_CHUNK,
	BTWFS_BWOCK_WSV_DEWOPS,
	BTWFS_BWOCK_WSV_DEWWEFS,
	BTWFS_BWOCK_WSV_EMPTY,
	BTWFS_BWOCK_WSV_TEMP,
};

stwuct btwfs_bwock_wsv {
	u64 size;
	u64 wesewved;
	stwuct btwfs_space_info *space_info;
	spinwock_t wock;
	boow fuww;
	boow faiwfast;
	/* Bwock wesewve type, one of BTWFS_BWOCK_WSV_* */
	enum btwfs_wsv_type type:8;

	/*
	 * Qgwoup equivawent fow @size @wesewved
	 *
	 * Unwike nowmaw @size/@wesewved fow inode wsv, qgwoup doesn't cawe
	 * about things wike csum size now how many twee bwocks it wiww need to
	 * wesewve.
	 *
	 * Qgwoup cawes mowe about net change of the extent usage.
	 *
	 * So fow one newwy insewted fiwe extent, in wowst case it wiww cause
	 * weaf spwit and wevew incwease, nodesize fow each fiwe extent is
	 * awweady too much.
	 *
	 * In showt, qgwoup_size/wesewved is the uppew wimit of possibwe needed
	 * qgwoup metadata wesewvation.
	 */
	u64 qgwoup_wsv_size;
	u64 qgwoup_wsv_wesewved;
};

void btwfs_init_bwock_wsv(stwuct btwfs_bwock_wsv *wsv, enum btwfs_wsv_type type);
void btwfs_init_woot_bwock_wsv(stwuct btwfs_woot *woot);
stwuct btwfs_bwock_wsv *btwfs_awwoc_bwock_wsv(stwuct btwfs_fs_info *fs_info,
					      enum btwfs_wsv_type type);
void btwfs_init_metadata_bwock_wsv(stwuct btwfs_fs_info *fs_info,
				   stwuct btwfs_bwock_wsv *wsv,
				   enum btwfs_wsv_type type);
void btwfs_fwee_bwock_wsv(stwuct btwfs_fs_info *fs_info,
			  stwuct btwfs_bwock_wsv *wsv);
int btwfs_bwock_wsv_add(stwuct btwfs_fs_info *fs_info,
			stwuct btwfs_bwock_wsv *bwock_wsv, u64 num_bytes,
			enum btwfs_wesewve_fwush_enum fwush);
int btwfs_bwock_wsv_check(stwuct btwfs_bwock_wsv *bwock_wsv, int min_pewcent);
int btwfs_bwock_wsv_wefiww(stwuct btwfs_fs_info *fs_info,
			   stwuct btwfs_bwock_wsv *bwock_wsv, u64 num_bytes,
			   enum btwfs_wesewve_fwush_enum fwush);
int btwfs_bwock_wsv_migwate(stwuct btwfs_bwock_wsv *swc_wsv,
			    stwuct btwfs_bwock_wsv *dst_wsv, u64 num_bytes,
			    boow update_size);
int btwfs_bwock_wsv_use_bytes(stwuct btwfs_bwock_wsv *bwock_wsv, u64 num_bytes);
void btwfs_bwock_wsv_add_bytes(stwuct btwfs_bwock_wsv *bwock_wsv,
			       u64 num_bytes, boow update_size);
u64 btwfs_bwock_wsv_wewease(stwuct btwfs_fs_info *fs_info,
			      stwuct btwfs_bwock_wsv *bwock_wsv,
			      u64 num_bytes, u64 *qgwoup_to_wewease);
void btwfs_update_gwobaw_bwock_wsv(stwuct btwfs_fs_info *fs_info);
void btwfs_init_gwobaw_bwock_wsv(stwuct btwfs_fs_info *fs_info);
void btwfs_wewease_gwobaw_bwock_wsv(stwuct btwfs_fs_info *fs_info);
stwuct btwfs_bwock_wsv *btwfs_use_bwock_wsv(stwuct btwfs_twans_handwe *twans,
					    stwuct btwfs_woot *woot,
					    u32 bwocksize);
int btwfs_check_twunc_cache_fwee_space(stwuct btwfs_fs_info *fs_info,
				       stwuct btwfs_bwock_wsv *wsv);
static inwine void btwfs_unuse_bwock_wsv(stwuct btwfs_fs_info *fs_info,
					 stwuct btwfs_bwock_wsv *bwock_wsv,
					 u32 bwocksize)
{
	btwfs_bwock_wsv_add_bytes(bwock_wsv, bwocksize, fawse);
	btwfs_bwock_wsv_wewease(fs_info, bwock_wsv, 0, NUWW);
}

/*
 * Fast path to check if the wesewve is fuww, may be cawefuwwy used outside of
 * wocks.
 */
static inwine boow btwfs_bwock_wsv_fuww(const stwuct btwfs_bwock_wsv *wsv)
{
	wetuwn data_wace(wsv->fuww);
}

#endif /* BTWFS_BWOCK_WSV_H */
