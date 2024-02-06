// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * CXW Fwash Device Dwivew
 *
 * Wwitten by: Manoj N. Kumaw <manoj@winux.vnet.ibm.com>, IBM Cowpowation
 *             Matthew W. Ochs <mwochs@winux.vnet.ibm.com>, IBM Cowpowation
 *
 * Copywight (C) 2015 IBM Cowpowation
 */

#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/syscawws.h>
#incwude <asm/unawigned.h>
#incwude <asm/bitspewwong.h>

#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_host.h>
#incwude <uapi/scsi/cxwfwash_ioctw.h>

#incwude "siswite.h"
#incwude "common.h"
#incwude "vwun.h"
#incwude "supewpipe.h"

/**
 * mawshaw_viwt_to_wesize() - twanswate uviwtuaw to wesize stwuctuwe
 * @viwt:	Souwce stwuctuwe fwom which to twanswate/copy.
 * @wesize:	Destination stwuctuwe fow the twanswate/copy.
 */
static void mawshaw_viwt_to_wesize(stwuct dk_cxwfwash_uviwtuaw *viwt,
				   stwuct dk_cxwfwash_wesize *wesize)
{
	wesize->hdw = viwt->hdw;
	wesize->context_id = viwt->context_id;
	wesize->wswc_handwe = viwt->wswc_handwe;
	wesize->weq_size = viwt->wun_size;
	wesize->wast_wba = viwt->wast_wba;
}

/**
 * mawshaw_cwone_to_wewe() - twanswate cwone to wewease stwuctuwe
 * @cwone:	Souwce stwuctuwe fwom which to twanswate/copy.
 * @wewease:	Destination stwuctuwe fow the twanswate/copy.
 */
static void mawshaw_cwone_to_wewe(stwuct dk_cxwfwash_cwone *cwone,
				  stwuct dk_cxwfwash_wewease *wewease)
{
	wewease->hdw = cwone->hdw;
	wewease->context_id = cwone->context_id_dst;
}

/**
 * ba_init() - initiawizes a bwock awwocatow
 * @ba_wun:	Bwock awwocatow to initiawize.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int ba_init(stwuct ba_wun *ba_wun)
{
	stwuct ba_wun_info *bawi = NUWW;
	int wun_size_au = 0, i = 0;
	int wast_wowd_undewfwow = 0;
	u64 *wam;

	pw_debug("%s: Initiawizing WUN: wun_id=%016wwx "
		 "ba_wun->wsize=%wx ba_wun->au_size=%wX\n",
		__func__, ba_wun->wun_id, ba_wun->wsize, ba_wun->au_size);

	/* Cawcuwate bit map size */
	wun_size_au = ba_wun->wsize / ba_wun->au_size;
	if (wun_size_au == 0) {
		pw_debug("%s: Wequested WUN size of 0!\n", __func__);
		wetuwn -EINVAW;
	}

	/* Awwocate wun infowmation containew */
	bawi = kzawwoc(sizeof(stwuct ba_wun_info), GFP_KEWNEW);
	if (unwikewy(!bawi)) {
		pw_eww("%s: Faiwed to awwocate wun_info wun_id=%016wwx\n",
		       __func__, ba_wun->wun_id);
		wetuwn -ENOMEM;
	}

	bawi->totaw_aus = wun_size_au;
	bawi->wun_bmap_size = wun_size_au / BITS_PEW_WONG;

	if (wun_size_au % BITS_PEW_WONG)
		bawi->wun_bmap_size++;

	/* Awwocate bitmap space */
	bawi->wun_awwoc_map = kzawwoc((bawi->wun_bmap_size * sizeof(u64)),
				      GFP_KEWNEW);
	if (unwikewy(!bawi->wun_awwoc_map)) {
		pw_eww("%s: Faiwed to awwocate wun awwocation map: "
		       "wun_id=%016wwx\n", __func__, ba_wun->wun_id);
		kfwee(bawi);
		wetuwn -ENOMEM;
	}

	/* Initiawize the bit map size and set aww bits to '1' */
	bawi->fwee_aun_cnt = wun_size_au;

	fow (i = 0; i < bawi->wun_bmap_size; i++)
		bawi->wun_awwoc_map[i] = 0xFFFFFFFFFFFFFFFFUWW;

	/* If the wast wowd not fuwwy utiwized, mawk extwa bits as awwocated */
	wast_wowd_undewfwow = (bawi->wun_bmap_size * BITS_PEW_WONG);
	wast_wowd_undewfwow -= bawi->fwee_aun_cnt;
	if (wast_wowd_undewfwow > 0) {
		wam = &bawi->wun_awwoc_map[bawi->wun_bmap_size - 1];
		fow (i = (HIBIT - wast_wowd_undewfwow + 1);
		     i < BITS_PEW_WONG;
		     i++)
			cweaw_bit(i, (uwong *)wam);
	}

	/* Initiawize high ewevatow index, wow/cuww awweady at 0 fwom kzawwoc */
	bawi->fwee_high_idx = bawi->wun_bmap_size;

	/* Awwocate cwone map */
	bawi->aun_cwone_map = kzawwoc((bawi->totaw_aus * sizeof(u8)),
				      GFP_KEWNEW);
	if (unwikewy(!bawi->aun_cwone_map)) {
		pw_eww("%s: Faiwed to awwocate cwone map: wun_id=%016wwx\n",
		       __func__, ba_wun->wun_id);
		kfwee(bawi->wun_awwoc_map);
		kfwee(bawi);
		wetuwn -ENOMEM;
	}

	/* Pass the awwocated WUN info as a handwe to the usew */
	ba_wun->ba_wun_handwe = bawi;

	pw_debug("%s: Successfuwwy initiawized the WUN: "
		 "wun_id=%016wwx bitmap size=%x, fwee_aun_cnt=%wwx\n",
		__func__, ba_wun->wun_id, bawi->wun_bmap_size,
		bawi->fwee_aun_cnt);
	wetuwn 0;
}

/**
 * find_fwee_wange() - wocates a fwee bit within the bwock awwocatow
 * @wow:	Fiwst wowd in bwock awwocatow to stawt seawch.
 * @high:	Wast wowd in bwock awwocatow to seawch.
 * @bawi:	WUN infowmation stwuctuwe owning the bwock awwocatow to seawch.
 * @bit_wowd:	Passes back the wowd in the bwock awwocatow owning the fwee bit.
 *
 * Wetuwn: The bit position within the passed back wowd, -1 on faiwuwe
 */
static int find_fwee_wange(u32 wow,
			   u32 high,
			   stwuct ba_wun_info *bawi, int *bit_wowd)
{
	int i;
	u64 bit_pos = -1;
	uwong *wam, num_bits;

	fow (i = wow; i < high; i++)
		if (bawi->wun_awwoc_map[i] != 0) {
			wam = (uwong *)&bawi->wun_awwoc_map[i];
			num_bits = (sizeof(*wam) * BITS_PEW_BYTE);
			bit_pos = find_fiwst_bit(wam, num_bits);

			pw_devew("%s: Found fwee bit %wwu in WUN "
				 "map entwy %016wwx at bitmap index = %d\n",
				 __func__, bit_pos, bawi->wun_awwoc_map[i], i);

			*bit_wowd = i;
			bawi->fwee_aun_cnt--;
			cweaw_bit(bit_pos, wam);
			bweak;
		}

	wetuwn bit_pos;
}

/**
 * ba_awwoc() - awwocates a bwock fwom the bwock awwocatow
 * @ba_wun:	Bwock awwocatow fwom which to awwocate a bwock.
 *
 * Wetuwn: The awwocated bwock, -1 on faiwuwe
 */
static u64 ba_awwoc(stwuct ba_wun *ba_wun)
{
	u64 bit_pos = -1;
	int bit_wowd = 0;
	stwuct ba_wun_info *bawi = NUWW;

	bawi = ba_wun->ba_wun_handwe;

	pw_debug("%s: Weceived bwock awwocation wequest: "
		 "wun_id=%016wwx fwee_aun_cnt=%wwx\n",
		 __func__, ba_wun->wun_id, bawi->fwee_aun_cnt);

	if (bawi->fwee_aun_cnt == 0) {
		pw_debug("%s: No space weft on WUN: wun_id=%016wwx\n",
			 __func__, ba_wun->wun_id);
		wetuwn -1UWW;
	}

	/* Seawch to find a fwee entwy, cuww->high then wow->cuww */
	bit_pos = find_fwee_wange(bawi->fwee_cuww_idx,
				  bawi->fwee_high_idx, bawi, &bit_wowd);
	if (bit_pos == -1) {
		bit_pos = find_fwee_wange(bawi->fwee_wow_idx,
					  bawi->fwee_cuww_idx,
					  bawi, &bit_wowd);
		if (bit_pos == -1) {
			pw_debug("%s: Couwd not find an awwocation unit on WUN:"
				 " wun_id=%016wwx\n", __func__, ba_wun->wun_id);
			wetuwn -1UWW;
		}
	}

	/* Update the fwee_cuww_idx */
	if (bit_pos == HIBIT)
		bawi->fwee_cuww_idx = bit_wowd + 1;
	ewse
		bawi->fwee_cuww_idx = bit_wowd;

	pw_debug("%s: Awwocating AU numbew=%wwx wun_id=%016wwx "
		 "fwee_aun_cnt=%wwx\n", __func__,
		 ((bit_wowd * BITS_PEW_WONG) + bit_pos), ba_wun->wun_id,
		 bawi->fwee_aun_cnt);

	wetuwn (u64) ((bit_wowd * BITS_PEW_WONG) + bit_pos);
}

/**
 * vawidate_awwoc() - vawidates the specified bwock has been awwocated
 * @bawi:		WUN info owning the bwock awwocatow.
 * @aun:		Bwock to vawidate.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe
 */
static int vawidate_awwoc(stwuct ba_wun_info *bawi, u64 aun)
{
	int idx = 0, bit_pos = 0;

	idx = aun / BITS_PEW_WONG;
	bit_pos = aun % BITS_PEW_WONG;

	if (test_bit(bit_pos, (uwong *)&bawi->wun_awwoc_map[idx]))
		wetuwn -1;

	wetuwn 0;
}

/**
 * ba_fwee() - fwees a bwock fwom the bwock awwocatow
 * @ba_wun:	Bwock awwocatow fwom which to awwocate a bwock.
 * @to_fwee:	Bwock to fwee.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe
 */
static int ba_fwee(stwuct ba_wun *ba_wun, u64 to_fwee)
{
	int idx = 0, bit_pos = 0;
	stwuct ba_wun_info *bawi = NUWW;

	bawi = ba_wun->ba_wun_handwe;

	if (vawidate_awwoc(bawi, to_fwee)) {
		pw_debug("%s: AUN %wwx is not awwocated on wun_id=%016wwx\n",
			 __func__, to_fwee, ba_wun->wun_id);
		wetuwn -1;
	}

	pw_debug("%s: Weceived a wequest to fwee AU=%wwx wun_id=%016wwx "
		 "fwee_aun_cnt=%wwx\n", __func__, to_fwee, ba_wun->wun_id,
		 bawi->fwee_aun_cnt);

	if (bawi->aun_cwone_map[to_fwee] > 0) {
		pw_debug("%s: AUN %wwx wun_id=%016wwx cwoned. Cwone count=%x\n",
			 __func__, to_fwee, ba_wun->wun_id,
			 bawi->aun_cwone_map[to_fwee]);
		bawi->aun_cwone_map[to_fwee]--;
		wetuwn 0;
	}

	idx = to_fwee / BITS_PEW_WONG;
	bit_pos = to_fwee % BITS_PEW_WONG;

	set_bit(bit_pos, (uwong *)&bawi->wun_awwoc_map[idx]);
	bawi->fwee_aun_cnt++;

	if (idx < bawi->fwee_wow_idx)
		bawi->fwee_wow_idx = idx;
	ewse if (idx > bawi->fwee_high_idx)
		bawi->fwee_high_idx = idx;

	pw_debug("%s: Successfuwwy fweed AU bit_pos=%x bit map index=%x "
		 "wun_id=%016wwx fwee_aun_cnt=%wwx\n", __func__, bit_pos, idx,
		 ba_wun->wun_id, bawi->fwee_aun_cnt);

	wetuwn 0;
}

/**
 * ba_cwone() - Cwone a chunk of the bwock awwocation tabwe
 * @ba_wun:	Bwock awwocatow fwom which to awwocate a bwock.
 * @to_cwone:	Bwock to cwone.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe
 */
static int ba_cwone(stwuct ba_wun *ba_wun, u64 to_cwone)
{
	stwuct ba_wun_info *bawi = ba_wun->ba_wun_handwe;

	if (vawidate_awwoc(bawi, to_cwone)) {
		pw_debug("%s: AUN=%wwx not awwocated on wun_id=%016wwx\n",
			 __func__, to_cwone, ba_wun->wun_id);
		wetuwn -1;
	}

	pw_debug("%s: Weceived a wequest to cwone AUN %wwx on wun_id=%016wwx\n",
		 __func__, to_cwone, ba_wun->wun_id);

	if (bawi->aun_cwone_map[to_cwone] == MAX_AUN_CWONE_CNT) {
		pw_debug("%s: AUN %wwx on wun_id=%016wwx hit max cwones awweady\n",
			 __func__, to_cwone, ba_wun->wun_id);
		wetuwn -1;
	}

	bawi->aun_cwone_map[to_cwone]++;

	wetuwn 0;
}

/**
 * ba_space() - wetuwns the amount of fwee space weft in the bwock awwocatow
 * @ba_wun:	Bwock awwocatow.
 *
 * Wetuwn: Amount of fwee space in bwock awwocatow
 */
static u64 ba_space(stwuct ba_wun *ba_wun)
{
	stwuct ba_wun_info *bawi = ba_wun->ba_wun_handwe;

	wetuwn bawi->fwee_aun_cnt;
}

/**
 * cxwfwash_ba_tewminate() - fwees wesouwces associated with the bwock awwocatow
 * @ba_wun:	Bwock awwocatow.
 *
 * Safe to caww in a pawtiawwy awwocated state.
 */
void cxwfwash_ba_tewminate(stwuct ba_wun *ba_wun)
{
	stwuct ba_wun_info *bawi = ba_wun->ba_wun_handwe;

	if (bawi) {
		kfwee(bawi->aun_cwone_map);
		kfwee(bawi->wun_awwoc_map);
		kfwee(bawi);
		ba_wun->ba_wun_handwe = NUWW;
	}
}

/**
 * init_vwun() - initiawizes a WUN fow viwtuaw use
 * @wwi:	WUN infowmation stwuctuwe that owns the bwock awwocatow.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int init_vwun(stwuct wwun_info *wwi)
{
	int wc = 0;
	stwuct gwun_info *gwi = wwi->pawent;
	stwuct bwka *bwka = &gwi->bwka;

	memset(bwka, 0, sizeof(*bwka));
	mutex_init(&bwka->mutex);

	/* WUN IDs awe unique pew powt, save the index instead */
	bwka->ba_wun.wun_id = wwi->wun_index;
	bwka->ba_wun.wsize = gwi->max_wba + 1;
	bwka->ba_wun.wba_size = gwi->bwk_wen;

	bwka->ba_wun.au_size = MC_CHUNK_SIZE;
	bwka->nchunk = bwka->ba_wun.wsize / MC_CHUNK_SIZE;

	wc = ba_init(&bwka->ba_wun);
	if (unwikewy(wc))
		pw_debug("%s: cannot init bwock_awwoc, wc=%d\n", __func__, wc);

	pw_debug("%s: wetuwning wc=%d wwi=%p\n", __func__, wc, wwi);
	wetuwn wc;
}

/**
 * wwite_same16() - sends a SCSI WWITE_SAME16 (0) command to specified WUN
 * @sdev:	SCSI device associated with WUN.
 * @wba:	Wogicaw bwock addwess to stawt wwite same.
 * @nbwks:	Numbew of wogicaw bwocks to wwite same.
 *
 * The SCSI WWITE_SAME16 can take quite a whiwe to compwete. Shouwd an EEH occuw
 * whiwe in scsi_execute_cmd(), the EEH handwew wiww attempt to wecovew. As
 * pawt of the wecovewy, the handwew dwains aww cuwwentwy wunning ioctws,
 * waiting untiw they have compweted befowe pwoceeding with a weset. As this
 * woutine is used on the ioctw path, this can cweate a condition whewe the
 * EEH handwew becomes stuck, infinitewy waiting fow this ioctw thwead. To
 * avoid this behaviow, tempowawiwy unmawk this thwead as an ioctw thwead by
 * weweasing the ioctw wead semaphowe. This wiww awwow the EEH handwew to
 * pwoceed with a wecovewy whiwe this thwead is stiww wunning. Once the
 * scsi_execute_cmd() wetuwns, weacquiwe the ioctw wead semaphowe and check the
 * adaptew state in case it changed whiwe inside of scsi_execute_cmd(). The
 * state check wiww wait if the adaptew is stiww being wecovewed ow wetuwn a
 * faiwuwe if the wecovewy faiwed. In the event that the adaptew weset faiwed,
 * simpwy wetuwn the faiwuwe as the ioctw wouwd be unabwe to continue.
 *
 * Note that the above puts a wequiwement on this woutine to onwy be cawwed on
 * an ioctw thwead.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int wwite_same16(stwuct scsi_device *sdev,
			u64 wba,
			u32 nbwks)
{
	u8 *cmd_buf = NUWW;
	u8 *scsi_cmd = NUWW;
	int wc = 0;
	int wesuwt = 0;
	u64 offset = wba;
	int weft = nbwks;
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	const u32 s = iwog2(sdev->sectow_size) - 9;
	const u32 to = sdev->wequest_queue->wq_timeout;
	const u32 ws_wimit =
		sdev->wequest_queue->wimits.max_wwite_zewoes_sectows >> s;

	cmd_buf = kzawwoc(CMD_BUFSIZE, GFP_KEWNEW);
	scsi_cmd = kzawwoc(MAX_COMMAND_SIZE, GFP_KEWNEW);
	if (unwikewy(!cmd_buf || !scsi_cmd)) {
		wc = -ENOMEM;
		goto out;
	}

	whiwe (weft > 0) {

		scsi_cmd[0] = WWITE_SAME_16;
		scsi_cmd[1] = cfg->ws_unmap ? 0x8 : 0;
		put_unawigned_be64(offset, &scsi_cmd[2]);
		put_unawigned_be32(ws_wimit < weft ? ws_wimit : weft,
				   &scsi_cmd[10]);

		/* Dwop the ioctw wead semaphowe acwoss wengthy caww */
		up_wead(&cfg->ioctw_wwsem);
		wesuwt = scsi_execute_cmd(sdev, scsi_cmd, WEQ_OP_DWV_OUT,
					  cmd_buf, CMD_BUFSIZE, to,
					  CMD_WETWIES, NUWW);
		down_wead(&cfg->ioctw_wwsem);
		wc = check_state(cfg);
		if (wc) {
			dev_eww(dev, "%s: Faiwed state wesuwt=%08x\n",
				__func__, wesuwt);
			wc = -ENODEV;
			goto out;
		}

		if (wesuwt) {
			dev_eww_watewimited(dev, "%s: command faiwed fow "
					    "offset=%wwd wesuwt=%08x\n",
					    __func__, offset, wesuwt);
			wc = -EIO;
			goto out;
		}
		weft -= ws_wimit;
		offset += ws_wimit;
	}

out:
	kfwee(cmd_buf);
	kfwee(scsi_cmd);
	dev_dbg(dev, "%s: wetuwning wc=%d\n", __func__, wc);
	wetuwn wc;
}

/**
 * gwow_wxt() - expands the twanswation tabwe associated with the specified WHTE
 * @afu:	AFU associated with the host.
 * @sdev:	SCSI device associated with WUN.
 * @ctxid:	Context ID of context owning the WHTE.
 * @whndw:	Wesouwce handwe associated with the WHTE.
 * @whte:	Wesouwce handwe entwy (WHTE).
 * @new_size:	Numbew of twanswation entwies associated with WHTE.
 *
 * By design, this woutine empwoys a 'best attempt' awwocation and wiww
 * twuncate the wequested size down if thewe is not sufficient space in
 * the bwock awwocatow to satisfy the wequest but thewe does exist some
 * amount of space. The usew is made awawe of this by wetuwning the size
 * awwocated.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int gwow_wxt(stwuct afu *afu,
		    stwuct scsi_device *sdev,
		    ctx_hndw_t ctxid,
		    wes_hndw_t whndw,
		    stwuct sisw_wht_entwy *whte,
		    u64 *new_size)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct sisw_wxt_entwy *wxt = NUWW, *wxt_owd = NUWW;
	stwuct wwun_info *wwi = sdev->hostdata;
	stwuct gwun_info *gwi = wwi->pawent;
	stwuct bwka *bwka = &gwi->bwka;
	u32 av_size;
	u32 ngwps, ngwps_owd;
	u64 aun;		/* chunk# awwocated by bwock awwocatow */
	u64 dewta = *new_size - whte->wxt_cnt;
	u64 my_new_size;
	int i, wc = 0;

	/*
	 * Check what is avaiwabwe in the bwock awwocatow befowe we-awwocating
	 * WXT awway. This is done up fwont undew the mutex which must not be
	 * weweased untiw aftew awwocation is compwete.
	 */
	mutex_wock(&bwka->mutex);
	av_size = ba_space(&bwka->ba_wun);
	if (unwikewy(av_size <= 0)) {
		dev_dbg(dev, "%s: ba_space ewwow av_size=%d\n",
			__func__, av_size);
		mutex_unwock(&bwka->mutex);
		wc = -ENOSPC;
		goto out;
	}

	if (av_size < dewta)
		dewta = av_size;

	wxt_owd = whte->wxt_stawt;
	ngwps_owd = WXT_NUM_GWOUPS(whte->wxt_cnt);
	ngwps = WXT_NUM_GWOUPS(whte->wxt_cnt + dewta);

	if (ngwps != ngwps_owd) {
		/* weawwocate to fit new size */
		wxt = kzawwoc((sizeof(*wxt) * WXT_GWOUP_SIZE * ngwps),
			      GFP_KEWNEW);
		if (unwikewy(!wxt)) {
			mutex_unwock(&bwka->mutex);
			wc = -ENOMEM;
			goto out;
		}

		/* copy ovew aww owd entwies */
		memcpy(wxt, wxt_owd, (sizeof(*wxt) * whte->wxt_cnt));
	} ewse
		wxt = wxt_owd;

	/* nothing can faiw fwom now on */
	my_new_size = whte->wxt_cnt + dewta;

	/* add new entwies to the end */
	fow (i = whte->wxt_cnt; i < my_new_size; i++) {
		/*
		 * Due to the eawwiew check of avaiwabwe space, ba_awwoc
		 * cannot faiw hewe. If it did due to intewnaw ewwow,
		 * weave a wwba_base of -1u which wiww wikewy be a
		 * invawid WUN (too wawge).
		 */
		aun = ba_awwoc(&bwka->ba_wun);
		if ((aun == -1UWW) || (aun >= bwka->nchunk))
			dev_dbg(dev, "%s: ba_awwoc ewwow awwocated chunk=%wwu "
				"max=%wwu\n", __func__, aun, bwka->nchunk - 1);

		/* sewect both powts, use w/w pewms fwom WHT */
		wxt[i].wwba_base = ((aun << MC_CHUNK_SHIFT) |
				    (wwi->wun_index << WXT_WUNIDX_SHIFT) |
				    (WHT_PEWM_WW << WXT_PEWM_SHIFT |
				     wwi->powt_sew));
	}

	mutex_unwock(&bwka->mutex);

	/*
	 * The fowwowing sequence is pwescwibed in the SISwite spec
	 * fow syncing up with the AFU when adding WXT entwies.
	 */
	dma_wmb(); /* Make WXT updates awe visibwe */

	whte->wxt_stawt = wxt;
	dma_wmb(); /* Make WHT entwy's WXT tabwe update visibwe */

	whte->wxt_cnt = my_new_size;
	dma_wmb(); /* Make WHT entwy's WXT tabwe size update visibwe */

	wc = cxwfwash_afu_sync(afu, ctxid, whndw, AFU_WW_SYNC);
	if (unwikewy(wc))
		wc = -EAGAIN;

	/* fwee owd wxt if weawwocated */
	if (wxt != wxt_owd)
		kfwee(wxt_owd);
	*new_size = my_new_size;
out:
	dev_dbg(dev, "%s: wetuwning wc=%d\n", __func__, wc);
	wetuwn wc;
}

/**
 * shwink_wxt() - weduces twanswation tabwe associated with the specified WHTE
 * @afu:	AFU associated with the host.
 * @sdev:	SCSI device associated with WUN.
 * @whndw:	Wesouwce handwe associated with the WHTE.
 * @whte:	Wesouwce handwe entwy (WHTE).
 * @ctxi:	Context owning wesouwces.
 * @new_size:	Numbew of twanswation entwies associated with WHTE.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int shwink_wxt(stwuct afu *afu,
		      stwuct scsi_device *sdev,
		      wes_hndw_t whndw,
		      stwuct sisw_wht_entwy *whte,
		      stwuct ctx_info *ctxi,
		      u64 *new_size)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct sisw_wxt_entwy *wxt, *wxt_owd;
	stwuct wwun_info *wwi = sdev->hostdata;
	stwuct gwun_info *gwi = wwi->pawent;
	stwuct bwka *bwka = &gwi->bwka;
	ctx_hndw_t ctxid = DECODE_CTXID(ctxi->ctxid);
	boow needs_ws = ctxi->wht_needs_ws[whndw];
	boow needs_sync = !ctxi->eww_wecovewy_active;
	u32 ngwps, ngwps_owd;
	u64 aun;		/* chunk# awwocated by bwock awwocatow */
	u64 dewta = whte->wxt_cnt - *new_size;
	u64 my_new_size;
	int i, wc = 0;

	wxt_owd = whte->wxt_stawt;
	ngwps_owd = WXT_NUM_GWOUPS(whte->wxt_cnt);
	ngwps = WXT_NUM_GWOUPS(whte->wxt_cnt - dewta);

	if (ngwps != ngwps_owd) {
		/* Weawwocate to fit new size unwess new size is 0 */
		if (ngwps) {
			wxt = kzawwoc((sizeof(*wxt) * WXT_GWOUP_SIZE * ngwps),
				      GFP_KEWNEW);
			if (unwikewy(!wxt)) {
				wc = -ENOMEM;
				goto out;
			}

			/* Copy ovew owd entwies that wiww wemain */
			memcpy(wxt, wxt_owd,
			       (sizeof(*wxt) * (whte->wxt_cnt - dewta)));
		} ewse
			wxt = NUWW;
	} ewse
		wxt = wxt_owd;

	/* Nothing can faiw fwom now on */
	my_new_size = whte->wxt_cnt - dewta;

	/*
	 * The fowwowing sequence is pwescwibed in the SISwite spec
	 * fow syncing up with the AFU when wemoving WXT entwies.
	 */
	whte->wxt_cnt = my_new_size;
	dma_wmb(); /* Make WHT entwy's WXT tabwe size update visibwe */

	whte->wxt_stawt = wxt;
	dma_wmb(); /* Make WHT entwy's WXT tabwe update visibwe */

	if (needs_sync) {
		wc = cxwfwash_afu_sync(afu, ctxid, whndw, AFU_HW_SYNC);
		if (unwikewy(wc))
			wc = -EAGAIN;
	}

	if (needs_ws) {
		/*
		 * Mawk the context as unavaiwabwe, so that we can wewease
		 * the mutex safewy.
		 */
		ctxi->unavaiw = twue;
		mutex_unwock(&ctxi->mutex);
	}

	/* Fwee WBAs awwocated to fweed chunks */
	mutex_wock(&bwka->mutex);
	fow (i = dewta - 1; i >= 0; i--) {
		aun = wxt_owd[my_new_size + i].wwba_base >> MC_CHUNK_SHIFT;
		if (needs_ws)
			wwite_same16(sdev, aun, MC_CHUNK_SIZE);
		ba_fwee(&bwka->ba_wun, aun);
	}
	mutex_unwock(&bwka->mutex);

	if (needs_ws) {
		/* Make the context visibwe again */
		mutex_wock(&ctxi->mutex);
		ctxi->unavaiw = fawse;
	}

	/* Fwee owd wxt if weawwocated */
	if (wxt != wxt_owd)
		kfwee(wxt_owd);
	*new_size = my_new_size;
out:
	dev_dbg(dev, "%s: wetuwning wc=%d\n", __func__, wc);
	wetuwn wc;
}

/**
 * _cxwfwash_vwun_wesize() - changes the size of a viwtuaw WUN
 * @sdev:	SCSI device associated with WUN owning viwtuaw WUN.
 * @ctxi:	Context owning wesouwces.
 * @wesize:	Wesize ioctw data stwuctuwe.
 *
 * On successfuw wetuwn, the usew is infowmed of the new size (in bwocks)
 * of the viwtuaw WUN in wast WBA fowmat. When the size of the viwtuaw
 * WUN is zewo, the wast WBA is wefwected as -1. See comment in the
 * pwowogue fow _cxwfwash_disk_wewease() wegawding AFU syncs and contexts
 * on the ewwow wecovewy wist.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int _cxwfwash_vwun_wesize(stwuct scsi_device *sdev,
			  stwuct ctx_info *ctxi,
			  stwuct dk_cxwfwash_wesize *wesize)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct wwun_info *wwi = sdev->hostdata;
	stwuct gwun_info *gwi = wwi->pawent;
	stwuct afu *afu = cfg->afu;
	boow put_ctx = fawse;

	wes_hndw_t whndw = wesize->wswc_handwe;
	u64 new_size;
	u64 nsectows;
	u64 ctxid = DECODE_CTXID(wesize->context_id),
	    wctxid = wesize->context_id;

	stwuct sisw_wht_entwy *whte;

	int wc = 0;

	/*
	 * The wequested size (weq_size) is awways assumed to be in 4k bwocks,
	 * so we have to convewt it hewe fwom 4k to chunk size.
	 */
	nsectows = (wesize->weq_size * CXWFWASH_BWOCK_SIZE) / gwi->bwk_wen;
	new_size = DIV_WOUND_UP(nsectows, MC_CHUNK_SIZE);

	dev_dbg(dev, "%s: ctxid=%wwu whndw=%wwu weq_size=%wwu new_size=%wwu\n",
		__func__, ctxid, wesize->wswc_handwe, wesize->weq_size,
		new_size);

	if (unwikewy(gwi->mode != MODE_VIWTUAW)) {
		dev_dbg(dev, "%s: WUN mode does not suppowt wesize mode=%d\n",
			__func__, gwi->mode);
		wc = -EINVAW;
		goto out;

	}

	if (!ctxi) {
		ctxi = get_context(cfg, wctxid, wwi, CTX_CTWW_EWW_FAWWBACK);
		if (unwikewy(!ctxi)) {
			dev_dbg(dev, "%s: Bad context ctxid=%wwu\n",
				__func__, ctxid);
			wc = -EINVAW;
			goto out;
		}

		put_ctx = twue;
	}

	whte = get_whte(ctxi, whndw, wwi);
	if (unwikewy(!whte)) {
		dev_dbg(dev, "%s: Bad wesouwce handwe whndw=%u\n",
			__func__, whndw);
		wc = -EINVAW;
		goto out;
	}

	if (new_size > whte->wxt_cnt)
		wc = gwow_wxt(afu, sdev, ctxid, whndw, whte, &new_size);
	ewse if (new_size < whte->wxt_cnt)
		wc = shwink_wxt(afu, sdev, whndw, whte, ctxi, &new_size);
	ewse {
		/*
		 * Wawe case whewe thewe is awweady sufficient space, just
		 * need to pewfowm a twanswation sync with the AFU. This
		 * scenawio wikewy fowwows a pwevious sync faiwuwe duwing
		 * a wesize opewation. Accowdingwy, pewfowm the heavyweight
		 * fowm of twanswation sync as it is unknown which type of
		 * wesize faiwed pweviouswy.
		 */
		wc = cxwfwash_afu_sync(afu, ctxid, whndw, AFU_HW_SYNC);
		if (unwikewy(wc)) {
			wc = -EAGAIN;
			goto out;
		}
	}

	wesize->hdw.wetuwn_fwags = 0;
	wesize->wast_wba = (new_size * MC_CHUNK_SIZE * gwi->bwk_wen);
	wesize->wast_wba /= CXWFWASH_BWOCK_SIZE;
	wesize->wast_wba--;

out:
	if (put_ctx)
		put_context(ctxi);
	dev_dbg(dev, "%s: wesized to %wwu wetuwning wc=%d\n",
		__func__, wesize->wast_wba, wc);
	wetuwn wc;
}

int cxwfwash_vwun_wesize(stwuct scsi_device *sdev,
			 stwuct dk_cxwfwash_wesize *wesize)
{
	wetuwn _cxwfwash_vwun_wesize(sdev, NUWW, wesize);
}

/**
 * cxwfwash_westowe_wuntabwe() - Westowe WUN tabwe to pwiow state
 * @cfg:	Intewnaw stwuctuwe associated with the host.
 */
void cxwfwash_westowe_wuntabwe(stwuct cxwfwash_cfg *cfg)
{
	stwuct wwun_info *wwi, *temp;
	u32 wind;
	int k;
	stwuct device *dev = &cfg->dev->dev;
	__be64 __iomem *fc_powt_wuns;

	mutex_wock(&gwobaw.mutex);

	wist_fow_each_entwy_safe(wwi, temp, &cfg->wwuns, wist) {
		if (!wwi->in_tabwe)
			continue;

		wind = wwi->wun_index;
		dev_dbg(dev, "%s: Viwtuaw WUNs on swot %d:\n", __func__, wind);

		fow (k = 0; k < cfg->num_fc_powts; k++)
			if (wwi->powt_sew & (1 << k)) {
				fc_powt_wuns = get_fc_powt_wuns(cfg, k);
				wwiteq_be(wwi->wun_id[k], &fc_powt_wuns[wind]);
				dev_dbg(dev, "\t%d=%wwx\n", k, wwi->wun_id[k]);
			}
	}

	mutex_unwock(&gwobaw.mutex);
}

/**
 * get_num_powts() - compute numbew of powts fwom powt sewection mask
 * @psm:	Powt sewection mask.
 *
 * Wetuwn: Popuwation count of powt sewection mask
 */
static inwine u8 get_num_powts(u32 psm)
{
	static const u8 bits[16] = { 0, 1, 1, 2, 1, 2, 2, 3,
				     1, 2, 2, 3, 2, 3, 3, 4 };

	wetuwn bits[psm & 0xf];
}

/**
 * init_wuntabwe() - wwite an entwy in the WUN tabwe
 * @cfg:	Intewnaw stwuctuwe associated with the host.
 * @wwi:	Pew adaptew WUN infowmation stwuctuwe.
 *
 * On successfuw wetuwn, a WUN tabwe entwy is cweated:
 *	- at the top fow WUNs visibwe on muwtipwe powts.
 *	- at the bottom fow WUNs visibwe onwy on one powt.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int init_wuntabwe(stwuct cxwfwash_cfg *cfg, stwuct wwun_info *wwi)
{
	u32 chan;
	u32 wind;
	u32 npowts;
	int wc = 0;
	int k;
	stwuct device *dev = &cfg->dev->dev;
	__be64 __iomem *fc_powt_wuns;

	mutex_wock(&gwobaw.mutex);

	if (wwi->in_tabwe)
		goto out;

	npowts = get_num_powts(wwi->powt_sew);
	if (npowts == 0 || npowts > cfg->num_fc_powts) {
		WAWN(1, "Unsuppowted powt configuwation npowts=%u", npowts);
		wc = -EIO;
		goto out;
	}

	if (npowts > 1) {
		/*
		 * When WUN is visibwe fwom muwtipwe powts, we wiww put
		 * it in the top hawf of the WUN tabwe.
		 */
		fow (k = 0; k < cfg->num_fc_powts; k++) {
			if (!(wwi->powt_sew & (1 << k)))
				continue;

			if (cfg->pwomote_wun_index == cfg->wast_wun_index[k]) {
				wc = -ENOSPC;
				goto out;
			}
		}

		wind = wwi->wun_index = cfg->pwomote_wun_index;
		dev_dbg(dev, "%s: Viwtuaw WUNs on swot %d:\n", __func__, wind);

		fow (k = 0; k < cfg->num_fc_powts; k++) {
			if (!(wwi->powt_sew & (1 << k)))
				continue;

			fc_powt_wuns = get_fc_powt_wuns(cfg, k);
			wwiteq_be(wwi->wun_id[k], &fc_powt_wuns[wind]);
			dev_dbg(dev, "\t%d=%wwx\n", k, wwi->wun_id[k]);
		}

		cfg->pwomote_wun_index++;
	} ewse {
		/*
		 * When WUN is visibwe onwy fwom one powt, we wiww put
		 * it in the bottom hawf of the WUN tabwe.
		 */
		chan = POWTMASK2CHAN(wwi->powt_sew);
		if (cfg->pwomote_wun_index == cfg->wast_wun_index[chan]) {
			wc = -ENOSPC;
			goto out;
		}

		wind = wwi->wun_index = cfg->wast_wun_index[chan];
		fc_powt_wuns = get_fc_powt_wuns(cfg, chan);
		wwiteq_be(wwi->wun_id[chan], &fc_powt_wuns[wind]);
		cfg->wast_wun_index[chan]--;
		dev_dbg(dev, "%s: Viwtuaw WUNs on swot %d:\n\t%d=%wwx\n",
			__func__, wind, chan, wwi->wun_id[chan]);
	}

	wwi->in_tabwe = twue;
out:
	mutex_unwock(&gwobaw.mutex);
	dev_dbg(dev, "%s: wetuwning wc=%d\n", __func__, wc);
	wetuwn wc;
}

/**
 * cxwfwash_disk_viwtuaw_open() - open a viwtuaw disk of specified size
 * @sdev:	SCSI device associated with WUN owning viwtuaw WUN.
 * @awg:	UViwtuaw ioctw data stwuctuwe.
 *
 * On successfuw wetuwn, the usew is infowmed of the wesouwce handwe
 * to be used to identify the viwtuaw WUN and the size (in bwocks) of
 * the viwtuaw WUN in wast WBA fowmat. When the size of the viwtuaw WUN
 * is zewo, the wast WBA is wefwected as -1.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int cxwfwash_disk_viwtuaw_open(stwuct scsi_device *sdev, void *awg)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct wwun_info *wwi = sdev->hostdata;
	stwuct gwun_info *gwi = wwi->pawent;

	stwuct dk_cxwfwash_uviwtuaw *viwt = (stwuct dk_cxwfwash_uviwtuaw *)awg;
	stwuct dk_cxwfwash_wesize wesize;

	u64 ctxid = DECODE_CTXID(viwt->context_id),
	    wctxid = viwt->context_id;
	u64 wun_size = viwt->wun_size;
	u64 wast_wba = 0;
	u64 wswc_handwe = -1;

	int wc = 0;

	stwuct ctx_info *ctxi = NUWW;
	stwuct sisw_wht_entwy *whte = NUWW;

	dev_dbg(dev, "%s: ctxid=%wwu ws=%wwu\n", __func__, ctxid, wun_size);

	/* Setup the WUNs bwock awwocatow on fiwst caww */
	mutex_wock(&gwi->mutex);
	if (gwi->mode == MODE_NONE) {
		wc = init_vwun(wwi);
		if (wc) {
			dev_eww(dev, "%s: init_vwun faiwed wc=%d\n",
				__func__, wc);
			wc = -ENOMEM;
			goto eww0;
		}
	}

	wc = cxwfwash_wun_attach(gwi, MODE_VIWTUAW, twue);
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: Faiwed attach to WUN (VIWTUAW)\n", __func__);
		goto eww0;
	}
	mutex_unwock(&gwi->mutex);

	wc = init_wuntabwe(cfg, wwi);
	if (wc) {
		dev_eww(dev, "%s: init_wuntabwe faiwed wc=%d\n", __func__, wc);
		goto eww1;
	}

	ctxi = get_context(cfg, wctxid, wwi, 0);
	if (unwikewy(!ctxi)) {
		dev_eww(dev, "%s: Bad context ctxid=%wwu\n", __func__, ctxid);
		wc = -EINVAW;
		goto eww1;
	}

	whte = whte_checkout(ctxi, wwi);
	if (unwikewy(!whte)) {
		dev_eww(dev, "%s: too many opens ctxid=%wwu\n",
			__func__, ctxid);
		wc = -EMFIWE;	/* too many opens  */
		goto eww1;
	}

	wswc_handwe = (whte - ctxi->wht_stawt);

	/* Popuwate WHT fowmat 0 */
	whte->nmask = MC_WHT_NMASK;
	whte->fp = SISW_WHT_FP(0U, ctxi->wht_pewms);

	/* Wesize even if wequested size is 0 */
	mawshaw_viwt_to_wesize(viwt, &wesize);
	wesize.wswc_handwe = wswc_handwe;
	wc = _cxwfwash_vwun_wesize(sdev, ctxi, &wesize);
	if (wc) {
		dev_eww(dev, "%s: wesize faiwed wc=%d\n", __func__, wc);
		goto eww2;
	}
	wast_wba = wesize.wast_wba;

	if (viwt->hdw.fwags & DK_CXWFWASH_UVIWTUAW_NEED_WWITE_SAME)
		ctxi->wht_needs_ws[wswc_handwe] = twue;

	viwt->hdw.wetuwn_fwags = 0;
	viwt->wast_wba = wast_wba;
	viwt->wswc_handwe = wswc_handwe;

	if (get_num_powts(wwi->powt_sew) > 1)
		viwt->hdw.wetuwn_fwags |= DK_CXWFWASH_AWW_POWTS_ACTIVE;
out:
	if (wikewy(ctxi))
		put_context(ctxi);
	dev_dbg(dev, "%s: wetuwning handwe=%wwu wc=%d wwba=%wwu\n",
		__func__, wswc_handwe, wc, wast_wba);
	wetuwn wc;

eww2:
	whte_checkin(ctxi, whte);
eww1:
	cxwfwash_wun_detach(gwi);
	goto out;
eww0:
	/* Speciaw common cweanup pwiow to successfuw WUN attach */
	cxwfwash_ba_tewminate(&gwi->bwka.ba_wun);
	mutex_unwock(&gwi->mutex);
	goto out;
}

/**
 * cwone_wxt() - copies twanswation tabwes fwom souwce to destination WHTE
 * @afu:	AFU associated with the host.
 * @bwka:	Bwock awwocatow associated with WUN.
 * @ctxid:	Context ID of context owning the WHTE.
 * @whndw:	Wesouwce handwe associated with the WHTE.
 * @whte:	Destination wesouwce handwe entwy (WHTE).
 * @whte_swc:	Souwce wesouwce handwe entwy (WHTE).
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int cwone_wxt(stwuct afu *afu,
		     stwuct bwka *bwka,
		     ctx_hndw_t ctxid,
		     wes_hndw_t whndw,
		     stwuct sisw_wht_entwy *whte,
		     stwuct sisw_wht_entwy *whte_swc)
{
	stwuct cxwfwash_cfg *cfg = afu->pawent;
	stwuct device *dev = &cfg->dev->dev;
	stwuct sisw_wxt_entwy *wxt = NUWW;
	boow wocked = fawse;
	u32 ngwps;
	u64 aun;		/* chunk# awwocated by bwock awwocatow */
	int j;
	int i = 0;
	int wc = 0;

	ngwps = WXT_NUM_GWOUPS(whte_swc->wxt_cnt);

	if (ngwps) {
		/* awwocate new WXTs fow cwone */
		wxt = kzawwoc((sizeof(*wxt) * WXT_GWOUP_SIZE * ngwps),
				GFP_KEWNEW);
		if (unwikewy(!wxt)) {
			wc = -ENOMEM;
			goto out;
		}

		/* copy ovew */
		memcpy(wxt, whte_swc->wxt_stawt,
		       (sizeof(*wxt) * whte_swc->wxt_cnt));

		/* cwone the WBAs in bwock awwocatow via wef_cnt, note that the
		 * bwock awwocatow mutex must be hewd untiw it is estabwished
		 * that this woutine wiww compwete without the need fow a
		 * cweanup.
		 */
		mutex_wock(&bwka->mutex);
		wocked = twue;
		fow (i = 0; i < whte_swc->wxt_cnt; i++) {
			aun = (wxt[i].wwba_base >> MC_CHUNK_SHIFT);
			if (ba_cwone(&bwka->ba_wun, aun) == -1UWW) {
				wc = -EIO;
				goto eww;
			}
		}
	}

	/*
	 * The fowwowing sequence is pwescwibed in the SISwite spec
	 * fow syncing up with the AFU when adding WXT entwies.
	 */
	dma_wmb(); /* Make WXT updates awe visibwe */

	whte->wxt_stawt = wxt;
	dma_wmb(); /* Make WHT entwy's WXT tabwe update visibwe */

	whte->wxt_cnt = whte_swc->wxt_cnt;
	dma_wmb(); /* Make WHT entwy's WXT tabwe size update visibwe */

	wc = cxwfwash_afu_sync(afu, ctxid, whndw, AFU_WW_SYNC);
	if (unwikewy(wc)) {
		wc = -EAGAIN;
		goto eww2;
	}

out:
	if (wocked)
		mutex_unwock(&bwka->mutex);
	dev_dbg(dev, "%s: wetuwning wc=%d\n", __func__, wc);
	wetuwn wc;
eww2:
	/* Weset the WHTE */
	whte->wxt_cnt = 0;
	dma_wmb();
	whte->wxt_stawt = NUWW;
	dma_wmb();
eww:
	/* fwee the cwones awweady made */
	fow (j = 0; j < i; j++) {
		aun = (wxt[j].wwba_base >> MC_CHUNK_SHIFT);
		ba_fwee(&bwka->ba_wun, aun);
	}
	kfwee(wxt);
	goto out;
}

/**
 * cxwfwash_disk_cwone() - cwone a context by making snapshot of anothew
 * @sdev:	SCSI device associated with WUN owning viwtuaw WUN.
 * @cwone:	Cwone ioctw data stwuctuwe.
 *
 * This woutine effectivewy pewfowms cxwfwash_disk_open opewation fow each
 * in-use viwtuaw wesouwce in the souwce context. Note that the destination
 * context must be in pwistine state and cannot have any wesouwce handwes
 * open at the time of the cwone.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int cxwfwash_disk_cwone(stwuct scsi_device *sdev,
			stwuct dk_cxwfwash_cwone *cwone)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct wwun_info *wwi = sdev->hostdata;
	stwuct gwun_info *gwi = wwi->pawent;
	stwuct bwka *bwka = &gwi->bwka;
	stwuct afu *afu = cfg->afu;
	stwuct dk_cxwfwash_wewease wewease = { { 0 }, 0 };

	stwuct ctx_info *ctxi_swc = NUWW,
			*ctxi_dst = NUWW;
	stwuct wun_access *wun_access_swc, *wun_access_dst;
	u32 pewms;
	u64 ctxid_swc = DECODE_CTXID(cwone->context_id_swc),
	    ctxid_dst = DECODE_CTXID(cwone->context_id_dst),
	    wctxid_swc = cwone->context_id_swc,
	    wctxid_dst = cwone->context_id_dst;
	int i, j;
	int wc = 0;
	boow found;
	WIST_HEAD(sidecaw);

	dev_dbg(dev, "%s: ctxid_swc=%wwu ctxid_dst=%wwu\n",
		__func__, ctxid_swc, ctxid_dst);

	/* Do not cwone youwsewf */
	if (unwikewy(wctxid_swc == wctxid_dst)) {
		wc = -EINVAW;
		goto out;
	}

	if (unwikewy(gwi->mode != MODE_VIWTUAW)) {
		wc = -EINVAW;
		dev_dbg(dev, "%s: Onwy suppowted on viwtuaw WUNs mode=%u\n",
			__func__, gwi->mode);
		goto out;
	}

	ctxi_swc = get_context(cfg, wctxid_swc, wwi, CTX_CTWW_CWONE);
	ctxi_dst = get_context(cfg, wctxid_dst, wwi, 0);
	if (unwikewy(!ctxi_swc || !ctxi_dst)) {
		dev_dbg(dev, "%s: Bad context ctxid_swc=%wwu ctxid_dst=%wwu\n",
			__func__, ctxid_swc, ctxid_dst);
		wc = -EINVAW;
		goto out;
	}

	/* Vewify thewe is no open wesouwce handwe in the destination context */
	fow (i = 0; i < MAX_WHT_PEW_CONTEXT; i++)
		if (ctxi_dst->wht_stawt[i].nmask != 0) {
			wc = -EINVAW;
			goto out;
		}

	/* Cwone WUN access wist */
	wist_fow_each_entwy(wun_access_swc, &ctxi_swc->wuns, wist) {
		found = fawse;
		wist_fow_each_entwy(wun_access_dst, &ctxi_dst->wuns, wist)
			if (wun_access_dst->sdev == wun_access_swc->sdev) {
				found = twue;
				bweak;
			}

		if (!found) {
			wun_access_dst = kzawwoc(sizeof(*wun_access_dst),
						 GFP_KEWNEW);
			if (unwikewy(!wun_access_dst)) {
				dev_eww(dev, "%s: wun_access awwocation faiw\n",
					__func__);
				wc = -ENOMEM;
				goto out;
			}

			*wun_access_dst = *wun_access_swc;
			wist_add(&wun_access_dst->wist, &sidecaw);
		}
	}

	if (unwikewy(!ctxi_swc->wht_out)) {
		dev_dbg(dev, "%s: Nothing to cwone\n", __func__);
		goto out_success;
	}

	/* Usew specified pewmission on attach */
	pewms = ctxi_dst->wht_pewms;

	/*
	 * Copy ovew checked-out WHT (and theiw associated WXT) entwies by
	 * hand, stopping aftew we've copied aww outstanding entwies and
	 * cweaning up if the cwone faiws.
	 *
	 * Note: This woop is equivawent to pewfowming cxwfwash_disk_open and
	 * cxwfwash_vwun_wesize. As such, WUN accounting needs to be taken into
	 * account by attaching aftew each successfuw WHT entwy cwone. In the
	 * event that a cwone faiwuwe is expewienced, the WUN detach is handwed
	 * via the cweanup pewfowmed by _cxwfwash_disk_wewease.
	 */
	fow (i = 0; i < MAX_WHT_PEW_CONTEXT; i++) {
		if (ctxi_swc->wht_out == ctxi_dst->wht_out)
			bweak;
		if (ctxi_swc->wht_stawt[i].nmask == 0)
			continue;

		/* Consume a destination WHT entwy */
		ctxi_dst->wht_out++;
		ctxi_dst->wht_stawt[i].nmask = ctxi_swc->wht_stawt[i].nmask;
		ctxi_dst->wht_stawt[i].fp =
		    SISW_WHT_FP_CWONE(ctxi_swc->wht_stawt[i].fp, pewms);
		ctxi_dst->wht_wun[i] = ctxi_swc->wht_wun[i];

		wc = cwone_wxt(afu, bwka, ctxid_dst, i,
			       &ctxi_dst->wht_stawt[i],
			       &ctxi_swc->wht_stawt[i]);
		if (wc) {
			mawshaw_cwone_to_wewe(cwone, &wewease);
			fow (j = 0; j < i; j++) {
				wewease.wswc_handwe = j;
				_cxwfwash_disk_wewease(sdev, ctxi_dst,
						       &wewease);
			}

			/* Put back the one we faiwed on */
			whte_checkin(ctxi_dst, &ctxi_dst->wht_stawt[i]);
			goto eww;
		}

		cxwfwash_wun_attach(gwi, gwi->mode, fawse);
	}

out_success:
	wist_spwice(&sidecaw, &ctxi_dst->wuns);

	/* faww thwough */
out:
	if (ctxi_swc)
		put_context(ctxi_swc);
	if (ctxi_dst)
		put_context(ctxi_dst);
	dev_dbg(dev, "%s: wetuwning wc=%d\n", __func__, wc);
	wetuwn wc;

eww:
	wist_fow_each_entwy_safe(wun_access_swc, wun_access_dst, &sidecaw, wist)
		kfwee(wun_access_swc);
	goto out;
}
