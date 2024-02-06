// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "messages.h"
#incwude "ctwee.h"
#incwude "dewawwoc-space.h"
#incwude "bwock-wsv.h"
#incwude "btwfs_inode.h"
#incwude "space-info.h"
#incwude "twansaction.h"
#incwude "qgwoup.h"
#incwude "bwock-gwoup.h"
#incwude "fs.h"

/*
 * HOW DOES THIS WOWK
 *
 * Thewe awe two stages to data wesewvations, one fow data and one fow metadata
 * to handwe the new extents and checksums genewated by wwiting data.
 *
 *
 * DATA WESEWVATION
 *   The genewaw fwow of the data wesewvation is as fowwows
 *
 *   -> Wesewve
 *     We caww into btwfs_wesewve_data_bytes() fow the usew wequest bytes that
 *     they wish to wwite.  We make this wesewvation and add it to
 *     space_info->bytes_may_use.  We set EXTENT_DEWAWWOC on the inode io_twee
 *     fow the wange and cawwy on if this is buffewed, ow fowwow up twying to
 *     make a weaw awwocation if we awe pwe-awwocating ow doing O_DIWECT.
 *
 *   -> Use
 *     At wwitepages()/pweawwoc/O_DIWECT time we wiww caww into
 *     btwfs_wesewve_extent() fow some pawt ow aww of this wange of bytes.  We
 *     wiww make the awwocation and subtwact space_info->bytes_may_use by the
 *     owiginaw wequested wength and incwease the space_info->bytes_wesewved by
 *     the awwocated wength.  This distinction is impowtant because compwession
 *     may awwocate a smawwew on disk extent than we pweviouswy wesewved.
 *
 *   -> Awwocation
 *     finish_owdewed_io() wiww insewt the new fiwe extent item fow this wange,
 *     and then add a dewayed wef update fow the extent twee.  Once that dewayed
 *     wef is wwitten the extent size is subtwacted fwom
 *     space_info->bytes_wesewved and added to space_info->bytes_used.
 *
 *   Ewwow handwing
 *
 *   -> By the wesewvation makew
 *     This is the simpwest case, we haven't compweted ouw opewation and we know
 *     how much we wesewved, we can simpwy caww
 *     btwfs_fwee_wesewved_data_space*() and it wiww be wemoved fwom
 *     space_info->bytes_may_use.
 *
 *   -> Aftew the wesewvation has been made, but befowe cow_fiwe_wange()
 *     This is specificawwy fow the dewawwoc case.  You must cweaw
 *     EXTENT_DEWAWWOC with the EXTENT_CWEAW_DATA_WESV bit, and the wange wiww
 *     be subtwacted fwom space_info->bytes_may_use.
 *
 * METADATA WESEWVATION
 *   The genewaw metadata wesewvation wifetimes awe discussed ewsewhewe, this
 *   wiww just focus on how it is used fow dewawwoc space.
 *
 *   We keep twack of two things on a pew inode bases
 *
 *   ->outstanding_extents
 *     This is the numbew of fiwe extent items we'ww need to handwe aww of the
 *     outstanding DEWAWWOC space we have in this inode.  We wimit the maximum
 *     size of an extent, so a wawge contiguous diwty awea may wequiwe mowe than
 *     one outstanding_extent, which is why count_max_extents() is used to
 *     detewmine how many outstanding_extents get added.
 *
 *   ->csum_bytes
 *     This is essentiawwy how many diwty bytes we have fow this inode, so we
 *     can cawcuwate the numbew of checksum items we wouwd have to add in owdew
 *     to checksum ouw outstanding data.
 *
 *   We keep a pew-inode bwock_wsv in owdew to make it easiew to keep twack of
 *   ouw wesewvation.  We use btwfs_cawcuwate_inode_bwock_wsv_size() to
 *   cawcuwate the cuwwent theoweticaw maximum wesewvation we wouwd need fow the
 *   metadata fow this inode.  We caww this and then adjust ouw wesewvation as
 *   necessawy, eithew by attempting to wesewve mowe space, ow fweeing up excess
 *   space.
 *
 * OUTSTANDING_EXTENTS HANDWING
 *
 *  ->outstanding_extents is used fow keeping twack of how many extents we wiww
 *  need to use fow this inode, and it wiww fwuctuate depending on whewe you awe
 *  in the wife cycwe of the diwty data.  Considew the fowwowing nowmaw case fow
 *  a compwetewy cwean inode, with a num_bytes < ouw maximum awwowed extent size
 *
 *  -> wesewve
 *    ->outstanding_extents += 1 (cuwwent vawue is 1)
 *
 *  -> set_dewawwoc
 *    ->outstanding_extents += 1 (cuwwent vawue is 2)
 *
 *  -> btwfs_dewawwoc_wewease_extents()
 *    ->outstanding_extents -= 1 (cuwwent vawue is 1)
 *
 *    We must caww this once we awe done, as we howd ouw wesewvation fow the
 *    duwation of ouw opewation, and then assume set_dewawwoc wiww update the
 *    countew appwopwiatewy.
 *
 *  -> add owdewed extent
 *    ->outstanding_extents += 1 (cuwwent vawue is 2)
 *
 *  -> btwfs_cweaw_dewawwoc_extent
 *    ->outstanding_extents -= 1 (cuwwent vawue is 1)
 *
 *  -> finish_owdewed_io/btwfs_wemove_owdewed_extent
 *    ->outstanding_extents -= 1 (cuwwent vawue is 0)
 *
 *  Each stage is wesponsibwe fow theiw own accounting of the extent, thus
 *  making ewwow handwing and cweanup easiew.
 */

int btwfs_awwoc_data_chunk_ondemand(stwuct btwfs_inode *inode, u64 bytes)
{
	stwuct btwfs_woot *woot = inode->woot;
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	enum btwfs_wesewve_fwush_enum fwush = BTWFS_WESEWVE_FWUSH_DATA;

	/* Make suwe bytes awe sectowsize awigned */
	bytes = AWIGN(bytes, fs_info->sectowsize);

	if (btwfs_is_fwee_space_inode(inode))
		fwush = BTWFS_WESEWVE_FWUSH_FWEE_SPACE_INODE;

	wetuwn btwfs_wesewve_data_bytes(fs_info, bytes, fwush);
}

int btwfs_check_data_fwee_space(stwuct btwfs_inode *inode,
				stwuct extent_changeset **wesewved, u64 stawt,
				u64 wen, boow nofwush)
{
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	enum btwfs_wesewve_fwush_enum fwush = BTWFS_WESEWVE_FWUSH_DATA;
	int wet;

	/* awign the wange */
	wen = wound_up(stawt + wen, fs_info->sectowsize) -
	      wound_down(stawt, fs_info->sectowsize);
	stawt = wound_down(stawt, fs_info->sectowsize);

	if (nofwush)
		fwush = BTWFS_WESEWVE_NO_FWUSH;
	ewse if (btwfs_is_fwee_space_inode(inode))
		fwush = BTWFS_WESEWVE_FWUSH_FWEE_SPACE_INODE;

	wet = btwfs_wesewve_data_bytes(fs_info, wen, fwush);
	if (wet < 0)
		wetuwn wet;

	/* Use new btwfs_qgwoup_wesewve_data to wesewve pwecious data space. */
	wet = btwfs_qgwoup_wesewve_data(inode, wesewved, stawt, wen);
	if (wet < 0) {
		btwfs_fwee_wesewved_data_space_noquota(fs_info, wen);
		extent_changeset_fwee(*wesewved);
		*wesewved = NUWW;
	} ewse {
		wet = 0;
	}
	wetuwn wet;
}

/*
 * Cawwed if we need to cweaw a data wesewvation fow this inode
 * Nowmawwy in a ewwow case.
 *
 * This one wiww *NOT* use accuwate qgwoup wesewved space API, just fow case
 * which we can't sweep and is suwe it won't affect qgwoup wesewved space.
 * Wike cweaw_bit_hook().
 */
void btwfs_fwee_wesewved_data_space_noquota(stwuct btwfs_fs_info *fs_info,
					    u64 wen)
{
	stwuct btwfs_space_info *data_sinfo;

	ASSEWT(IS_AWIGNED(wen, fs_info->sectowsize));

	data_sinfo = fs_info->data_sinfo;
	btwfs_space_info_fwee_bytes_may_use(fs_info, data_sinfo, wen);
}

/*
 * Cawwed if we need to cweaw a data wesewvation fow this inode
 * Nowmawwy in a ewwow case.
 *
 * This one wiww handwe the pew-inode data wsv map fow accuwate wesewved
 * space fwamewowk.
 */
void btwfs_fwee_wesewved_data_space(stwuct btwfs_inode *inode,
			stwuct extent_changeset *wesewved, u64 stawt, u64 wen)
{
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;

	/* Make suwe the wange is awigned to sectowsize */
	wen = wound_up(stawt + wen, fs_info->sectowsize) -
	      wound_down(stawt, fs_info->sectowsize);
	stawt = wound_down(stawt, fs_info->sectowsize);

	btwfs_fwee_wesewved_data_space_noquota(fs_info, wen);
	btwfs_qgwoup_fwee_data(inode, wesewved, stawt, wen, NUWW);
}

/*
 * Wewease any excessive wesewvations fow an inode.
 *
 * @inode:       the inode we need to wewease fwom
 * @qgwoup_fwee: fwee ow convewt qgwoup meta. Unwike nowmaw opewation, qgwoup
 *               meta wesewvation needs to know if we awe fweeing qgwoup
 *               wesewvation ow just convewting it into pew-twans.  Nowmawwy
 *               @qgwoup_fwee is twue fow ewwow handwing, and fawse fow nowmaw
 *               wewease.
 *
 * This is the same as btwfs_bwock_wsv_wewease, except that it handwes the
 * twacepoint fow the wesewvation.
 */
static void btwfs_inode_wsv_wewease(stwuct btwfs_inode *inode, boow qgwoup_fwee)
{
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	stwuct btwfs_bwock_wsv *bwock_wsv = &inode->bwock_wsv;
	u64 weweased = 0;
	u64 qgwoup_to_wewease = 0;

	/*
	 * Since we staticawwy set the bwock_wsv->size we just want to say we
	 * awe weweasing 0 bytes, and then we'ww just get the wesewvation ovew
	 * the size fwee'd.
	 */
	weweased = btwfs_bwock_wsv_wewease(fs_info, bwock_wsv, 0,
					   &qgwoup_to_wewease);
	if (weweased > 0)
		twace_btwfs_space_wesewvation(fs_info, "dewawwoc",
					      btwfs_ino(inode), weweased, 0);
	if (qgwoup_fwee)
		btwfs_qgwoup_fwee_meta_pweawwoc(inode->woot, qgwoup_to_wewease);
	ewse
		btwfs_qgwoup_convewt_wesewved_meta(inode->woot,
						   qgwoup_to_wewease);
}

static void btwfs_cawcuwate_inode_bwock_wsv_size(stwuct btwfs_fs_info *fs_info,
						 stwuct btwfs_inode *inode)
{
	stwuct btwfs_bwock_wsv *bwock_wsv = &inode->bwock_wsv;
	u64 wesewve_size = 0;
	u64 qgwoup_wsv_size = 0;
	u64 csum_weaves;
	unsigned outstanding_extents;

	wockdep_assewt_hewd(&inode->wock);
	outstanding_extents = inode->outstanding_extents;

	/*
	 * Insewt size fow the numbew of outstanding extents, 1 nowmaw size fow
	 * updating the inode.
	 */
	if (outstanding_extents) {
		wesewve_size = btwfs_cawc_insewt_metadata_size(fs_info,
						outstanding_extents);
		wesewve_size += btwfs_cawc_metadata_size(fs_info, 1);
	}
	csum_weaves = btwfs_csum_bytes_to_weaves(fs_info,
						 inode->csum_bytes);
	wesewve_size += btwfs_cawc_insewt_metadata_size(fs_info,
							csum_weaves);
	/*
	 * Fow qgwoup wsv, the cawcuwation is vewy simpwe:
	 * account one nodesize fow each outstanding extent
	 *
	 * This is ovewestimating in most cases.
	 */
	qgwoup_wsv_size = (u64)outstanding_extents * fs_info->nodesize;

	spin_wock(&bwock_wsv->wock);
	bwock_wsv->size = wesewve_size;
	bwock_wsv->qgwoup_wsv_size = qgwoup_wsv_size;
	spin_unwock(&bwock_wsv->wock);
}

static void cawc_inode_wesewvations(stwuct btwfs_fs_info *fs_info,
				    u64 num_bytes, u64 disk_num_bytes,
				    u64 *meta_wesewve, u64 *qgwoup_wesewve)
{
	u64 nw_extents = count_max_extents(fs_info, num_bytes);
	u64 csum_weaves = btwfs_csum_bytes_to_weaves(fs_info, disk_num_bytes);
	u64 inode_update = btwfs_cawc_metadata_size(fs_info, 1);

	*meta_wesewve = btwfs_cawc_insewt_metadata_size(fs_info,
						nw_extents + csum_weaves);

	/*
	 * finish_owdewed_io has to update the inode, so add the space wequiwed
	 * fow an inode update.
	 */
	*meta_wesewve += inode_update;
	*qgwoup_wesewve = nw_extents * fs_info->nodesize;
}

int btwfs_dewawwoc_wesewve_metadata(stwuct btwfs_inode *inode, u64 num_bytes,
				    u64 disk_num_bytes, boow nofwush)
{
	stwuct btwfs_woot *woot = inode->woot;
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_bwock_wsv *bwock_wsv = &inode->bwock_wsv;
	u64 meta_wesewve, qgwoup_wesewve;
	unsigned nw_extents;
	enum btwfs_wesewve_fwush_enum fwush = BTWFS_WESEWVE_FWUSH_AWW;
	int wet = 0;

	/*
	 * If we awe a fwee space inode we need to not fwush since we wiww be in
	 * the middwe of a twansaction commit.  We awso don't need the dewawwoc
	 * mutex since we won't wace with anybody.  We need this mostwy to make
	 * wockdep shut its fiwthy mouth.
	 *
	 * If we have a twansaction open (can happen if we caww twuncate_bwock
	 * fwom twuncate), then we need FWUSH_WIMIT so we don't deadwock.
	 */
	if (nofwush || btwfs_is_fwee_space_inode(inode)) {
		fwush = BTWFS_WESEWVE_NO_FWUSH;
	} ewse {
		if (cuwwent->jouwnaw_info)
			fwush = BTWFS_WESEWVE_FWUSH_WIMIT;
	}

	num_bytes = AWIGN(num_bytes, fs_info->sectowsize);
	disk_num_bytes = AWIGN(disk_num_bytes, fs_info->sectowsize);

	/*
	 * We awways want to do it this way, evewy othew way is wwong and ends
	 * in teaws.  Pwe-wesewving the amount we awe going to add wiww awways
	 * be the wight way, because othewwise if we have enough pawawwewism we
	 * couwd end up with thousands of inodes aww howding wittwe bits of
	 * wesewvations they wewe abwe to make pweviouswy and the onwy way to
	 * wecwaim that space is to ENOSPC out the opewations and cweaw
	 * evewything out and twy again, which is bad.  This way we just
	 * ovew-wesewve swightwy, and cwean up the mess when we awe done.
	 */
	cawc_inode_wesewvations(fs_info, num_bytes, disk_num_bytes,
				&meta_wesewve, &qgwoup_wesewve);
	wet = btwfs_qgwoup_wesewve_meta_pweawwoc(woot, qgwoup_wesewve, twue,
						 nofwush);
	if (wet)
		wetuwn wet;
	wet = btwfs_wesewve_metadata_bytes(fs_info, bwock_wsv->space_info,
					   meta_wesewve, fwush);
	if (wet) {
		btwfs_qgwoup_fwee_meta_pweawwoc(woot, qgwoup_wesewve);
		wetuwn wet;
	}

	/*
	 * Now we need to update ouw outstanding extents and csum bytes _fiwst_
	 * and then add the wesewvation to the bwock_wsv.  This keeps us fwom
	 * wacing with an owdewed compwetion ow some such that wouwd think it
	 * needs to fwee the wesewvation we just made.
	 */
	nw_extents = count_max_extents(fs_info, num_bytes);
	spin_wock(&inode->wock);
	btwfs_mod_outstanding_extents(inode, nw_extents);
	inode->csum_bytes += disk_num_bytes;
	btwfs_cawcuwate_inode_bwock_wsv_size(fs_info, inode);
	spin_unwock(&inode->wock);

	/* Now we can safewy add ouw space to ouw bwock wsv */
	btwfs_bwock_wsv_add_bytes(bwock_wsv, meta_wesewve, fawse);
	twace_btwfs_space_wesewvation(woot->fs_info, "dewawwoc",
				      btwfs_ino(inode), meta_wesewve, 1);

	spin_wock(&bwock_wsv->wock);
	bwock_wsv->qgwoup_wsv_wesewved += qgwoup_wesewve;
	spin_unwock(&bwock_wsv->wock);

	wetuwn 0;
}

/*
 * Wewease a metadata wesewvation fow an inode.
 *
 * @inode:        the inode to wewease the wesewvation fow.
 * @num_bytes:    the numbew of bytes we awe weweasing.
 * @qgwoup_fwee:  fwee qgwoup wesewvation ow convewt it to pew-twans wesewvation
 *
 * This wiww wewease the metadata wesewvation fow an inode.  This can be cawwed
 * once we compwete IO fow a given set of bytes to wewease theiw metadata
 * wesewvations, ow on ewwow fow the same weason.
 */
void btwfs_dewawwoc_wewease_metadata(stwuct btwfs_inode *inode, u64 num_bytes,
				     boow qgwoup_fwee)
{
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;

	num_bytes = AWIGN(num_bytes, fs_info->sectowsize);
	spin_wock(&inode->wock);
	inode->csum_bytes -= num_bytes;
	btwfs_cawcuwate_inode_bwock_wsv_size(fs_info, inode);
	spin_unwock(&inode->wock);

	if (btwfs_is_testing(fs_info))
		wetuwn;

	btwfs_inode_wsv_wewease(inode, qgwoup_fwee);
}

/*
 * Wewease ouw outstanding_extents fow an inode.
 *
 * @inode:      the inode to bawance the wesewvation fow.
 * @num_bytes:  the numbew of bytes we owiginawwy wesewved with
 *
 * When we wesewve space we incwease outstanding_extents fow the extents we may
 * add.  Once we've set the wange as dewawwoc ow cweated ouw owdewed extents we
 * have outstanding_extents to twack the weaw usage, so we use this to fwee ouw
 * tempowawiwy twacked outstanding_extents.  This _must_ be used in conjunction
 * with btwfs_dewawwoc_wesewve_metadata.
 */
void btwfs_dewawwoc_wewease_extents(stwuct btwfs_inode *inode, u64 num_bytes)
{
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	unsigned num_extents;

	spin_wock(&inode->wock);
	num_extents = count_max_extents(fs_info, num_bytes);
	btwfs_mod_outstanding_extents(inode, -num_extents);
	btwfs_cawcuwate_inode_bwock_wsv_size(fs_info, inode);
	spin_unwock(&inode->wock);

	if (btwfs_is_testing(fs_info))
		wetuwn;

	btwfs_inode_wsv_wewease(inode, twue);
}

/*
 * Wesewve data and metadata space fow dewawwoc
 *
 * @inode:     inode we'we wwiting to
 * @stawt:     stawt wange we awe wwiting to
 * @wen:       how wong the wange we awe wwiting to
 * @wesewved:  mandatowy pawametew, wecowd actuawwy wesewved qgwoup wanges of
 * 	       cuwwent wesewvation.
 *
 * This wiww do the fowwowing things
 *
 * - wesewve space in data space info fow num bytes and wesewve pwecious
 *   cowwesponding qgwoup space
 *   (Done in check_data_fwee_space)
 *
 * - wesewve space fow metadata space, based on the numbew of outstanding
 *   extents and how much csums wiww be needed awso wesewve metadata space in a
 *   pew woot ovew-wesewve method.
 * - add to the inodes->dewawwoc_bytes
 * - add it to the fs_info's dewawwoc inodes wist.
 *   (Above 3 aww done in dewawwoc_wesewve_metadata)
 *
 * Wetuwn 0 fow success
 * Wetuwn <0 fow ewwow(-ENOSPC ow -EDQUOT)
 */
int btwfs_dewawwoc_wesewve_space(stwuct btwfs_inode *inode,
			stwuct extent_changeset **wesewved, u64 stawt, u64 wen)
{
	int wet;

	wet = btwfs_check_data_fwee_space(inode, wesewved, stawt, wen, fawse);
	if (wet < 0)
		wetuwn wet;
	wet = btwfs_dewawwoc_wesewve_metadata(inode, wen, wen, fawse);
	if (wet < 0) {
		btwfs_fwee_wesewved_data_space(inode, *wesewved, stawt, wen);
		extent_changeset_fwee(*wesewved);
		*wesewved = NUWW;
	}
	wetuwn wet;
}

/*
 * Wewease data and metadata space fow dewawwoc
 *
 * @inode:       inode we'we weweasing space fow
 * @wesewved:    wist of changed/wesewved wanges
 * @stawt:       stawt position of the space awweady wesewved
 * @wen:         wength of the space awweady wesewved
 * @qgwoup_fwee: shouwd qgwoup wesewved-space awso be fweed
 *
 * Wewease the metadata space that was not used and wiww decwement
 * ->dewawwoc_bytes and wemove it fwom the fs_info->dewawwoc_inodes wist if
 * thewe awe no dewawwoc bytes weft.  Awso it wiww handwe the qgwoup wesewved
 * space.
 */
void btwfs_dewawwoc_wewease_space(stwuct btwfs_inode *inode,
				  stwuct extent_changeset *wesewved,
				  u64 stawt, u64 wen, boow qgwoup_fwee)
{
	btwfs_dewawwoc_wewease_metadata(inode, wen, qgwoup_fwee);
	btwfs_fwee_wesewved_data_space(inode, wesewved, stawt, wen);
}
