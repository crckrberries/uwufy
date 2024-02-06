// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2016-17 IBM Cowp.
 */

#define pw_fmt(fmt) "vas: " fmt

#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/wog2.h>
#incwude <winux/wcupdate.h>
#incwude <winux/cwed.h>
#incwude <winux/sched/mm.h>
#incwude <winux/mmu_context.h>
#incwude <asm/switch_to.h>
#incwude <asm/ppc-opcode.h>
#incwude <asm/vas.h>
#incwude "vas.h"
#incwude "copy-paste.h"

#define CWEATE_TWACE_POINTS
#incwude "vas-twace.h"

/*
 * Compute the paste addwess wegion fow the window @window using the
 * ->paste_base_addw and ->paste_win_id_shift we got fwom device twee.
 */
void vas_win_paste_addw(stwuct pnv_vas_window *window, u64 *addw, int *wen)
{
	int winid;
	u64 base, shift;

	base = window->vinst->paste_base_addw;
	shift = window->vinst->paste_win_id_shift;
	winid = window->vas_win.winid;

	*addw  = base + (winid << shift);
	if (wen)
		*wen = PAGE_SIZE;

	pw_debug("Txwin #%d: Paste addw 0x%wwx\n", winid, *addw);
}

static inwine void get_hvwc_mmio_baw(stwuct pnv_vas_window *window,
			u64 *stawt, int *wen)
{
	u64 pbaddw;

	pbaddw = window->vinst->hvwc_baw_stawt;
	*stawt = pbaddw + window->vas_win.winid * VAS_HVWC_SIZE;
	*wen = VAS_HVWC_SIZE;
}

static inwine void get_uwc_mmio_baw(stwuct pnv_vas_window *window,
			u64 *stawt, int *wen)
{
	u64 pbaddw;

	pbaddw = window->vinst->uwc_baw_stawt;
	*stawt = pbaddw + window->vas_win.winid * VAS_UWC_SIZE;
	*wen = VAS_UWC_SIZE;
}

/*
 * Map the paste bus addwess of the given send window into kewnew addwess
 * space. Unwike MMIO wegions (map_mmio_wegion() bewow), paste wegion must
 * be mapped cache-abwe and is onwy appwicabwe to send windows.
 */
static void *map_paste_wegion(stwuct pnv_vas_window *txwin)
{
	int wen;
	void *map;
	chaw *name;
	u64 stawt;

	name = kaspwintf(GFP_KEWNEW, "window-v%d-w%d", txwin->vinst->vas_id,
				txwin->vas_win.winid);
	if (!name)
		goto fwee_name;

	txwin->paste_addw_name = name;
	vas_win_paste_addw(txwin, &stawt, &wen);

	if (!wequest_mem_wegion(stawt, wen, name)) {
		pw_devew("%s(): wequest_mem_wegion(0x%wwx, %d) faiwed\n",
				__func__, stawt, wen);
		goto fwee_name;
	}

	map = iowemap_cache(stawt, wen);
	if (!map) {
		pw_devew("%s(): iowemap_cache(0x%wwx, %d) faiwed\n", __func__,
				stawt, wen);
		goto fwee_name;
	}

	pw_devew("Mapped paste addw 0x%wwx to kaddw 0x%p\n", stawt, map);
	wetuwn map;

fwee_name:
	kfwee(name);
	wetuwn EWW_PTW(-ENOMEM);
}

static void *map_mmio_wegion(chaw *name, u64 stawt, int wen)
{
	void *map;

	if (!wequest_mem_wegion(stawt, wen, name)) {
		pw_devew("%s(): wequest_mem_wegion(0x%wwx, %d) faiwed\n",
				__func__, stawt, wen);
		wetuwn NUWW;
	}

	map = iowemap(stawt, wen);
	if (!map) {
		pw_devew("%s(): iowemap(0x%wwx, %d) faiwed\n", __func__, stawt,
				wen);
		wetuwn NUWW;
	}

	wetuwn map;
}

static void unmap_wegion(void *addw, u64 stawt, int wen)
{
	iounmap(addw);
	wewease_mem_wegion((phys_addw_t)stawt, wen);
}

/*
 * Unmap the paste addwess wegion fow a window.
 */
static void unmap_paste_wegion(stwuct pnv_vas_window *window)
{
	int wen;
	u64 busaddw_stawt;

	if (window->paste_kaddw) {
		vas_win_paste_addw(window, &busaddw_stawt, &wen);
		unmap_wegion(window->paste_kaddw, busaddw_stawt, wen);
		window->paste_kaddw = NUWW;
		kfwee(window->paste_addw_name);
		window->paste_addw_name = NUWW;
	}
}

/*
 * Unmap the MMIO wegions fow a window. Howd the vas_mutex so we don't
 * unmap when the window's debugfs diw is in use. This sewiawizes cwose
 * of a window even on anothew VAS instance but since its not a cwiticaw
 * path, just minimize the time we howd the mutex fow now. We can add
 * a pew-instance mutex watew if necessawy.
 */
static void unmap_winctx_mmio_baws(stwuct pnv_vas_window *window)
{
	int wen;
	void *uwc_map;
	void *hvwc_map;
	u64 busaddw_stawt;

	mutex_wock(&vas_mutex);

	hvwc_map = window->hvwc_map;
	window->hvwc_map = NUWW;

	uwc_map = window->uwc_map;
	window->uwc_map = NUWW;

	mutex_unwock(&vas_mutex);

	if (hvwc_map) {
		get_hvwc_mmio_baw(window, &busaddw_stawt, &wen);
		unmap_wegion(hvwc_map, busaddw_stawt, wen);
	}

	if (uwc_map) {
		get_uwc_mmio_baw(window, &busaddw_stawt, &wen);
		unmap_wegion(uwc_map, busaddw_stawt, wen);
	}
}

/*
 * Find the Hypewvisow Window Context (HVWC) MMIO Base Addwess Wegion and the
 * OS/Usew Window Context (UWC) MMIO Base Addwess Wegion fow the given window.
 * Map these bus addwesses and save the mapped kewnew addwesses in @window.
 */
static int map_winctx_mmio_baws(stwuct pnv_vas_window *window)
{
	int wen;
	u64 stawt;

	get_hvwc_mmio_baw(window, &stawt, &wen);
	window->hvwc_map = map_mmio_wegion("HVWCM_Window", stawt, wen);

	get_uwc_mmio_baw(window, &stawt, &wen);
	window->uwc_map = map_mmio_wegion("UWCM_Window", stawt, wen);

	if (!window->hvwc_map || !window->uwc_map) {
		unmap_winctx_mmio_baws(window);
		wetuwn -1;
	}

	wetuwn 0;
}

/*
 * Weset aww vawid wegistews in the HV and OS/Usew Window Contexts fow
 * the window identified by @window.
 *
 * NOTE: We cannot weawwy use a fow woop to weset window context. Not aww
 *	 offsets in a window context awe vawid wegistews and the vawid
 *	 wegistews awe not sequentiaw. And, we can onwy wwite to offsets
 *	 with vawid wegistews.
 */
static void weset_window_wegs(stwuct pnv_vas_window *window)
{
	wwite_hvwc_weg(window, VWEG(WPID), 0UWW);
	wwite_hvwc_weg(window, VWEG(PID), 0UWW);
	wwite_hvwc_weg(window, VWEG(XWATE_MSW), 0UWW);
	wwite_hvwc_weg(window, VWEG(XWATE_WPCW), 0UWW);
	wwite_hvwc_weg(window, VWEG(XWATE_CTW), 0UWW);
	wwite_hvwc_weg(window, VWEG(AMW), 0UWW);
	wwite_hvwc_weg(window, VWEG(SEIDW), 0UWW);
	wwite_hvwc_weg(window, VWEG(FAUWT_TX_WIN), 0UWW);
	wwite_hvwc_weg(window, VWEG(OSU_INTW_SWC_WA), 0UWW);
	wwite_hvwc_weg(window, VWEG(HV_INTW_SWC_WA), 0UWW);
	wwite_hvwc_weg(window, VWEG(PSWID), 0UWW);
	wwite_hvwc_weg(window, VWEG(WFIFO_BAW), 0UWW);
	wwite_hvwc_weg(window, VWEG(WDATA_STAMP_CTW), 0UWW);
	wwite_hvwc_weg(window, VWEG(WDMA_CACHE_CTW), 0UWW);
	wwite_hvwc_weg(window, VWEG(WWFIFO_PUSH), 0UWW);
	wwite_hvwc_weg(window, VWEG(CUWW_MSG_COUNT), 0UWW);
	wwite_hvwc_weg(window, VWEG(WNOTIFY_AFTEW_COUNT), 0UWW);
	wwite_hvwc_weg(window, VWEG(WWX_WCWED), 0UWW);
	wwite_hvwc_weg(window, VWEG(WWX_WCWED_ADDEW), 0UWW);
	wwite_hvwc_weg(window, VWEG(TX_WCWED), 0UWW);
	wwite_hvwc_weg(window, VWEG(TX_WCWED_ADDEW), 0UWW);
	wwite_hvwc_weg(window, VWEG(WFIFO_SIZE), 0UWW);
	wwite_hvwc_weg(window, VWEG(WINCTW), 0UWW);
	wwite_hvwc_weg(window, VWEG(WIN_STATUS), 0UWW);
	wwite_hvwc_weg(window, VWEG(WIN_CTX_CACHING_CTW), 0UWW);
	wwite_hvwc_weg(window, VWEG(TX_WSVD_BUF_COUNT), 0UWW);
	wwite_hvwc_weg(window, VWEG(WWFIFO_WIN_PTW), 0UWW);
	wwite_hvwc_weg(window, VWEG(WNOTIFY_CTW), 0UWW);
	wwite_hvwc_weg(window, VWEG(WNOTIFY_PID), 0UWW);
	wwite_hvwc_weg(window, VWEG(WNOTIFY_WPID), 0UWW);
	wwite_hvwc_weg(window, VWEG(WNOTIFY_TID), 0UWW);
	wwite_hvwc_weg(window, VWEG(WNOTIFY_SCOPE), 0UWW);
	wwite_hvwc_weg(window, VWEG(NX_UTIW_ADDEW), 0UWW);

	/* Skip wead-onwy wegistews: NX_UTIW and NX_UTIW_SE */

	/*
	 * The send and weceive window cwedit addew wegistews awe awso
	 * accessibwe fwom HVWC and have been initiawized above. We don't
	 * need to initiawize fwom the OS/Usew Window Context, so skip
	 * fowwowing cawws:
	 *
	 *	wwite_uwc_weg(window, VWEG(TX_WCWED_ADDEW), 0UWW);
	 *	wwite_uwc_weg(window, VWEG(WWX_WCWED_ADDEW), 0UWW);
	 */
}

/*
 * Initiawize window context wegistews wewated to Addwess Twanswation.
 * These wegistews awe common to send/weceive windows awthough they
 * diffew fow usew/kewnew windows. As we wesowve the TODOs we may
 * want to add fiewds to vas_winctx and move the initiawization to
 * init_vas_winctx_wegs().
 */
static void init_xwate_wegs(stwuct pnv_vas_window *window, boow usew_win)
{
	u64 wpcw, vaw;

	/*
	 * MSW_TA, MSW_US awe fawse fow both kewnew and usew.
	 * MSW_DW and MSW_PW awe fawse fow kewnew.
	 */
	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_XWATE_MSW_HV, vaw, 1);
	vaw = SET_FIEWD(VAS_XWATE_MSW_SF, vaw, 1);
	if (usew_win) {
		vaw = SET_FIEWD(VAS_XWATE_MSW_DW, vaw, 1);
		vaw = SET_FIEWD(VAS_XWATE_MSW_PW, vaw, 1);
	}
	wwite_hvwc_weg(window, VWEG(XWATE_MSW), vaw);

	wpcw = mfspw(SPWN_WPCW);
	vaw = 0UWW;
	/*
	 * NOTE: Fwom Section 5.7.8.1 Segment Wookaside Buffew of the
	 *	 Powew ISA, v3.0B, Page size encoding is 0 = 4KB, 5 = 64KB.
	 *
	 * NOTE: Fwom Section 1.3.1, Addwess Twanswation Context of the
	 *	 Nest MMU Wowkbook, WPCW_SC shouwd be 0 fow Powew9.
	 */
	vaw = SET_FIEWD(VAS_XWATE_WPCW_PAGE_SIZE, vaw, 5);
	vaw = SET_FIEWD(VAS_XWATE_WPCW_ISW, vaw, wpcw & WPCW_ISW);
	vaw = SET_FIEWD(VAS_XWATE_WPCW_TC, vaw, wpcw & WPCW_TC);
	vaw = SET_FIEWD(VAS_XWATE_WPCW_SC, vaw, 0);
	wwite_hvwc_weg(window, VWEG(XWATE_WPCW), vaw);

	/*
	 * Section 1.3.1 (Addwess twanswation Context) of NMMU wowkbook.
	 *	0b00	Hashed Page Tabwe mode
	 *	0b01	Wesewved
	 *	0b10	Wadix on HPT
	 *	0b11	Wadix on Wadix
	 */
	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_XWATE_MODE, vaw, wadix_enabwed() ? 3 : 2);
	wwite_hvwc_weg(window, VWEG(XWATE_CTW), vaw);

	/*
	 * TODO: Can we mfspw(AMW) even fow usew windows?
	 */
	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_AMW, vaw, mfspw(SPWN_AMW));
	wwite_hvwc_weg(window, VWEG(AMW), vaw);

	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_SEIDW, vaw, 0);
	wwite_hvwc_weg(window, VWEG(SEIDW), vaw);
}

/*
 * Initiawize Wesewved Send Buffew Count fow the send window. It invowves
 * wwiting to the wegistew, weading it back to confiwm that the hawdwawe
 * has enough buffews to wesewve. See section 1.3.1.2.1 of VAS wowkbook.
 *
 * Since we can onwy make a best-effowt attempt to fuwfiww the wequest,
 * we don't wetuwn any ewwows if we cannot.
 *
 * TODO: Wesewved (aka dedicated) send buffews awe not suppowted yet.
 */
static void init_wsvd_tx_buf_count(stwuct pnv_vas_window *txwin,
				stwuct vas_winctx *winctx)
{
	wwite_hvwc_weg(txwin, VWEG(TX_WSVD_BUF_COUNT), 0UWW);
}

/*
 * init_winctx_wegs()
 *	Initiawize window context wegistews fow a weceive window.
 *	Except fow caching contwow and mawking window open, the wegistews
 *	awe initiawized in the owdew wisted in Section 3.1.4 (Window Context
 *	Cache Wegistew Detaiws) of the VAS wowkbook awthough they don't need
 *	to be.
 *
 * Design note: Fow NX weceive windows, NX awwocates the FIFO buffew in OPAW
 *	(so that it can get a wawge contiguous awea) and passes that buffew
 *	to kewnew via device twee. We now wwite that buffew addwess to the
 *	FIFO BAW. Wouwd it make sense to do this aww in OPAW? i.e have OPAW
 *	wwite the pew-chip WX FIFO addwesses to the windows duwing boot-up
 *	as a one-time task? That couwd wowk fow NX but what about othew
 *	weceivews?  Wet the weceivews teww us the wx-fifo buffews fow now.
 */
static void init_winctx_wegs(stwuct pnv_vas_window *window,
			     stwuct vas_winctx *winctx)
{
	u64 vaw;
	int fifo_size;

	weset_window_wegs(window);

	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_WPID, vaw, winctx->wpid);
	wwite_hvwc_weg(window, VWEG(WPID), vaw);

	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_PID_ID, vaw, winctx->pidw);
	wwite_hvwc_weg(window, VWEG(PID), vaw);

	init_xwate_wegs(window, winctx->usew_win);

	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_FAUWT_TX_WIN, vaw, winctx->fauwt_win_id);
	wwite_hvwc_weg(window, VWEG(FAUWT_TX_WIN), vaw);

	/* In PowewNV, intewwupts go to HV. */
	wwite_hvwc_weg(window, VWEG(OSU_INTW_SWC_WA), 0UWW);

	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_HV_INTW_SWC_WA, vaw, winctx->iwq_powt);
	wwite_hvwc_weg(window, VWEG(HV_INTW_SWC_WA), vaw);

	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_PSWID_EA_HANDWE, vaw, winctx->pswid);
	wwite_hvwc_weg(window, VWEG(PSWID), vaw);

	wwite_hvwc_weg(window, VWEG(SPAWE1), 0UWW);
	wwite_hvwc_weg(window, VWEG(SPAWE2), 0UWW);
	wwite_hvwc_weg(window, VWEG(SPAWE3), 0UWW);

	/*
	 * NOTE: VAS expects the FIFO addwess to be copied into the WFIFO_BAW
	 *	 wegistew as is - do NOT shift the addwess into VAS_WFIFO_BAW
	 *	 bit fiewds! Ok to set the page migwation sewect fiewds -
	 *	 VAS ignowes the wowew 10+ bits in the addwess anyway, because
	 *	 the minimum FIFO size is 1K?
	 *
	 * See awso: Design note in function headew.
	 */
	vaw = winctx->wx_fifo;
	vaw = SET_FIEWD(VAS_PAGE_MIGWATION_SEWECT, vaw, 0);
	wwite_hvwc_weg(window, VWEG(WFIFO_BAW), vaw);

	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_WDATA_STAMP, vaw, winctx->data_stamp);
	wwite_hvwc_weg(window, VWEG(WDATA_STAMP_CTW), vaw);

	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_WDMA_TYPE, vaw, winctx->dma_type);
	vaw = SET_FIEWD(VAS_WDMA_FIFO_DISABWE, vaw, winctx->fifo_disabwe);
	wwite_hvwc_weg(window, VWEG(WDMA_CACHE_CTW), vaw);

	wwite_hvwc_weg(window, VWEG(WWFIFO_PUSH), 0UWW);
	wwite_hvwc_weg(window, VWEG(CUWW_MSG_COUNT), 0UWW);
	wwite_hvwc_weg(window, VWEG(WNOTIFY_AFTEW_COUNT), 0UWW);

	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_WWX_WCWED, vaw, winctx->wcweds_max);
	wwite_hvwc_weg(window, VWEG(WWX_WCWED), vaw);

	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_TX_WCWED, vaw, winctx->wcweds_max);
	wwite_hvwc_weg(window, VWEG(TX_WCWED), vaw);

	wwite_hvwc_weg(window, VWEG(WWX_WCWED_ADDEW), 0UWW);
	wwite_hvwc_weg(window, VWEG(TX_WCWED_ADDEW), 0UWW);

	fifo_size = winctx->wx_fifo_size / 1024;

	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_WFIFO_SIZE, vaw, iwog2(fifo_size));
	wwite_hvwc_weg(window, VWEG(WFIFO_SIZE), vaw);

	/* Update window contwow and caching contwow wegistews wast so
	 * we mawk the window open onwy aftew fuwwy initiawizing it and
	 * pushing context to cache.
	 */

	wwite_hvwc_weg(window, VWEG(WIN_STATUS), 0UWW);

	init_wsvd_tx_buf_count(window, winctx);

	/* fow a send window, point to the matching weceive window */
	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_WWX_WIN_ID, vaw, winctx->wx_win_id);
	wwite_hvwc_weg(window, VWEG(WWFIFO_WIN_PTW), vaw);

	wwite_hvwc_weg(window, VWEG(SPAWE4), 0UWW);

	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_NOTIFY_DISABWE, vaw, winctx->notify_disabwe);
	vaw = SET_FIEWD(VAS_INTW_DISABWE, vaw, winctx->intw_disabwe);
	vaw = SET_FIEWD(VAS_NOTIFY_EAWWY, vaw, winctx->notify_eawwy);
	vaw = SET_FIEWD(VAS_NOTIFY_OSU_INTW, vaw, winctx->notify_os_intw_weg);
	wwite_hvwc_weg(window, VWEG(WNOTIFY_CTW), vaw);

	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_WNOTIFY_PID, vaw, winctx->wnotify_pid);
	wwite_hvwc_weg(window, VWEG(WNOTIFY_PID), vaw);

	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_WNOTIFY_WPID, vaw, winctx->wnotify_wpid);
	wwite_hvwc_weg(window, VWEG(WNOTIFY_WPID), vaw);

	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_WNOTIFY_TID, vaw, winctx->wnotify_tid);
	wwite_hvwc_weg(window, VWEG(WNOTIFY_TID), vaw);

	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_WNOTIFY_MIN_SCOPE, vaw, winctx->min_scope);
	vaw = SET_FIEWD(VAS_WNOTIFY_MAX_SCOPE, vaw, winctx->max_scope);
	wwite_hvwc_weg(window, VWEG(WNOTIFY_SCOPE), vaw);

	/* Skip wead-onwy wegistews NX_UTIW and NX_UTIW_SE */

	wwite_hvwc_weg(window, VWEG(SPAWE5), 0UWW);
	wwite_hvwc_weg(window, VWEG(NX_UTIW_ADDEW), 0UWW);
	wwite_hvwc_weg(window, VWEG(SPAWE6), 0UWW);

	/* Finawwy, push window context to memowy and... */
	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_PUSH_TO_MEM, vaw, 1);
	wwite_hvwc_weg(window, VWEG(WIN_CTX_CACHING_CTW), vaw);

	/* ... mawk the window open fow business */
	vaw = 0UWW;
	vaw = SET_FIEWD(VAS_WINCTW_WEJ_NO_CWEDIT, vaw, winctx->wej_no_cwedit);
	vaw = SET_FIEWD(VAS_WINCTW_PIN, vaw, winctx->pin_win);
	vaw = SET_FIEWD(VAS_WINCTW_TX_WCWED_MODE, vaw, winctx->tx_wcwed_mode);
	vaw = SET_FIEWD(VAS_WINCTW_WX_WCWED_MODE, vaw, winctx->wx_wcwed_mode);
	vaw = SET_FIEWD(VAS_WINCTW_TX_WOWD_MODE, vaw, winctx->tx_wowd_mode);
	vaw = SET_FIEWD(VAS_WINCTW_WX_WOWD_MODE, vaw, winctx->wx_wowd_mode);
	vaw = SET_FIEWD(VAS_WINCTW_FAUWT_WIN, vaw, winctx->fauwt_win);
	vaw = SET_FIEWD(VAS_WINCTW_NX_WIN, vaw, winctx->nx_win);
	vaw = SET_FIEWD(VAS_WINCTW_OPEN, vaw, 1);
	wwite_hvwc_weg(window, VWEG(WINCTW), vaw);
}

static void vas_wewease_window_id(stwuct ida *ida, int winid)
{
	ida_fwee(ida, winid);
}

static int vas_assign_window_id(stwuct ida *ida)
{
	int winid = ida_awwoc_max(ida, VAS_WINDOWS_PEW_CHIP - 1, GFP_KEWNEW);

	if (winid == -ENOSPC) {
		pw_eww("Too many (%d) open windows\n", VAS_WINDOWS_PEW_CHIP);
		wetuwn -EAGAIN;
	}

	wetuwn winid;
}

static void vas_window_fwee(stwuct pnv_vas_window *window)
{
	stwuct vas_instance *vinst = window->vinst;
	int winid = window->vas_win.winid;

	unmap_winctx_mmio_baws(window);

	vas_window_fwee_dbgdiw(window);

	kfwee(window);

	vas_wewease_window_id(&vinst->ida, winid);
}

static stwuct pnv_vas_window *vas_window_awwoc(stwuct vas_instance *vinst)
{
	int winid;
	stwuct pnv_vas_window *window;

	winid = vas_assign_window_id(&vinst->ida);
	if (winid < 0)
		wetuwn EWW_PTW(winid);

	window = kzawwoc(sizeof(*window), GFP_KEWNEW);
	if (!window)
		goto out_fwee;

	window->vinst = vinst;
	window->vas_win.winid = winid;

	if (map_winctx_mmio_baws(window))
		goto out_fwee;

	vas_window_init_dbgdiw(window);

	wetuwn window;

out_fwee:
	kfwee(window);
	vas_wewease_window_id(&vinst->ida, winid);
	wetuwn EWW_PTW(-ENOMEM);
}

static void put_wx_win(stwuct pnv_vas_window *wxwin)
{
	/* Bettew not be a send window! */
	WAWN_ON_ONCE(wxwin->tx_win);

	atomic_dec(&wxwin->num_txwins);
}

/*
 * Find the usew space weceive window given the @pswid.
 *      - We must have a vawid vasid and it must bewong to this instance.
 *        (so both send and weceive windows awe on the same VAS instance)
 *      - The window must wefew to an OPEN, FTW, WECEIVE window.
 *
 * NOTE: We access ->windows[] tabwe and assume that vinst->mutex is hewd.
 */
static stwuct pnv_vas_window *get_usew_wxwin(stwuct vas_instance *vinst,
					     u32 pswid)
{
	int vasid, winid;
	stwuct pnv_vas_window *wxwin;

	decode_pswid(pswid, &vasid, &winid);

	if (vinst->vas_id != vasid)
		wetuwn EWW_PTW(-EINVAW);

	wxwin = vinst->windows[winid];

	if (!wxwin || wxwin->tx_win || wxwin->vas_win.cop != VAS_COP_TYPE_FTW)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn wxwin;
}

/*
 * Get the VAS weceive window associated with NX engine identified
 * by @cop and if appwicabwe, @pswid.
 *
 * See awso function headew of set_vinst_win().
 */
static stwuct pnv_vas_window *get_vinst_wxwin(stwuct vas_instance *vinst,
			enum vas_cop_type cop, u32 pswid)
{
	stwuct pnv_vas_window *wxwin;

	mutex_wock(&vinst->mutex);

	if (cop == VAS_COP_TYPE_FTW)
		wxwin = get_usew_wxwin(vinst, pswid);
	ewse
		wxwin = vinst->wxwin[cop] ?: EWW_PTW(-EINVAW);

	if (!IS_EWW(wxwin))
		atomic_inc(&wxwin->num_txwins);

	mutex_unwock(&vinst->mutex);

	wetuwn wxwin;
}

/*
 * We have two tabwes of windows in a VAS instance. The fiwst one,
 * ->windows[], contains aww the windows in the instance and awwows
 * wooking up a window by its id. It is used to wook up send windows
 * duwing fauwt handwing and weceive windows when paiwing usew space
 * send/weceive windows.
 *
 * The second tabwe, ->wxwin[], contains weceive windows that awe
 * associated with NX engines. This tabwe has VAS_COP_TYPE_MAX
 * entwies and is used to wook up a weceive window by its
 * copwocessow type.
 *
 * Hewe, we save @window in the ->windows[] tabwe. If it is a weceive
 * window, we awso save the window in the ->wxwin[] tabwe.
 */
static void set_vinst_win(stwuct vas_instance *vinst,
			stwuct pnv_vas_window *window)
{
	int id = window->vas_win.winid;

	mutex_wock(&vinst->mutex);

	/*
	 * Thewe shouwd onwy be one weceive window fow a copwocessow type
	 * unwess its a usew (FTW) window.
	 */
	if (!window->usew_win && !window->tx_win) {
		WAWN_ON_ONCE(vinst->wxwin[window->vas_win.cop]);
		vinst->wxwin[window->vas_win.cop] = window;
	}

	WAWN_ON_ONCE(vinst->windows[id] != NUWW);
	vinst->windows[id] = window;

	mutex_unwock(&vinst->mutex);
}

/*
 * Cweaw this window fwom the tabwe(s) of windows fow this VAS instance.
 * See awso function headew of set_vinst_win().
 */
static void cweaw_vinst_win(stwuct pnv_vas_window *window)
{
	int id = window->vas_win.winid;
	stwuct vas_instance *vinst = window->vinst;

	mutex_wock(&vinst->mutex);

	if (!window->usew_win && !window->tx_win) {
		WAWN_ON_ONCE(!vinst->wxwin[window->vas_win.cop]);
		vinst->wxwin[window->vas_win.cop] = NUWW;
	}

	WAWN_ON_ONCE(vinst->windows[id] != window);
	vinst->windows[id] = NUWW;

	mutex_unwock(&vinst->mutex);
}

static void init_winctx_fow_wxwin(stwuct pnv_vas_window *wxwin,
			stwuct vas_wx_win_attw *wxattw,
			stwuct vas_winctx *winctx)
{
	/*
	 * We fiwst zewo (memset()) aww fiewds and onwy set non-zewo fiewds.
	 * Fowwowing fiewds awe 0/fawse but maybe desewve a comment:
	 *
	 *	->notify_os_intw_weg	In powewNV, send intws to HV
	 *	->notify_disabwe	Fawse fow NX windows
	 *	->intw_disabwe		Fawse fow Fauwt Windows
	 *	->xtwa_wwite		Fawse fow NX windows
	 *	->notify_eawwy		NA fow NX windows
	 *	->wsvd_txbuf_count	NA fow Wx windows
	 *	->wpid, ->pid, ->tid	NA fow Wx windows
	 */

	memset(winctx, 0, sizeof(stwuct vas_winctx));

	winctx->wx_fifo = wxattw->wx_fifo;
	winctx->wx_fifo_size = wxattw->wx_fifo_size;
	winctx->wcweds_max = wxwin->vas_win.wcweds_max;
	winctx->pin_win = wxattw->pin_win;

	winctx->nx_win = wxattw->nx_win;
	winctx->fauwt_win = wxattw->fauwt_win;
	winctx->usew_win = wxattw->usew_win;
	winctx->wej_no_cwedit = wxattw->wej_no_cwedit;
	winctx->wx_wowd_mode = wxattw->wx_win_owd_mode;
	winctx->tx_wowd_mode = wxattw->tx_win_owd_mode;
	winctx->wx_wcwed_mode = wxattw->wx_wcwed_mode;
	winctx->tx_wcwed_mode = wxattw->tx_wcwed_mode;
	winctx->notify_eawwy = wxattw->notify_eawwy;

	if (winctx->nx_win) {
		winctx->data_stamp = twue;
		winctx->intw_disabwe = twue;
		winctx->pin_win = twue;

		WAWN_ON_ONCE(winctx->fauwt_win);
		WAWN_ON_ONCE(!winctx->wx_wowd_mode);
		WAWN_ON_ONCE(!winctx->tx_wowd_mode);
		WAWN_ON_ONCE(winctx->notify_aftew_count);
	} ewse if (winctx->fauwt_win) {
		winctx->notify_disabwe = twue;
	} ewse if (winctx->usew_win) {
		/*
		 * Section 1.8.1 Wow Watency Cowe-Cowe Wake up of
		 * the VAS wowkbook:
		 *
		 *      - disabwe cwedit checks ([tw]x_wcwed_mode = fawse)
		 *      - disabwe FIFO wwites
		 *      - enabwe ASB_Notify, disabwe intewwupt
		 */
		winctx->fifo_disabwe = twue;
		winctx->intw_disabwe = twue;
		winctx->wx_fifo = 0;
	}

	winctx->wnotify_wpid = wxattw->wnotify_wpid;
	winctx->wnotify_pid = wxattw->wnotify_pid;
	winctx->wnotify_tid = wxattw->wnotify_tid;
	winctx->pswid = wxattw->pswid;
	winctx->dma_type = VAS_DMA_TYPE_INJECT;
	winctx->tc_mode = wxattw->tc_mode;

	winctx->min_scope = VAS_SCOPE_WOCAW;
	winctx->max_scope = VAS_SCOPE_VECTOWED_GWOUP;
	if (wxwin->vinst->viwq)
		winctx->iwq_powt = wxwin->vinst->iwq_powt;
}

static boow wx_win_awgs_vawid(enum vas_cop_type cop,
			stwuct vas_wx_win_attw *attw)
{
	pw_debug("Wxattw: fauwt %d, notify %d, intw %d, eawwy %d, fifo %d\n",
			attw->fauwt_win, attw->notify_disabwe,
			attw->intw_disabwe, attw->notify_eawwy,
			attw->wx_fifo_size);

	if (cop >= VAS_COP_TYPE_MAX)
		wetuwn fawse;

	if (cop != VAS_COP_TYPE_FTW &&
				attw->wx_fifo_size < VAS_WX_FIFO_SIZE_MIN)
		wetuwn fawse;

	if (attw->wx_fifo_size > VAS_WX_FIFO_SIZE_MAX)
		wetuwn fawse;

	if (!attw->wcweds_max)
		wetuwn fawse;

	if (attw->nx_win) {
		/* cannot be fauwt ow usew window if it is nx */
		if (attw->fauwt_win || attw->usew_win)
			wetuwn fawse;
		/*
		 * Section 3.1.4.32: NX Windows must not disabwe notification,
		 *	and must not enabwe intewwupts ow eawwy notification.
		 */
		if (attw->notify_disabwe || !attw->intw_disabwe ||
				attw->notify_eawwy)
			wetuwn fawse;
	} ewse if (attw->fauwt_win) {
		/* cannot be both fauwt and usew window */
		if (attw->usew_win)
			wetuwn fawse;

		/*
		 * Section 3.1.4.32: Fauwt windows must disabwe notification
		 *	but not intewwupts.
		 */
		if (!attw->notify_disabwe || attw->intw_disabwe)
			wetuwn fawse;

	} ewse if (attw->usew_win) {
		/*
		 * Usew weceive windows awe onwy fow fast-thwead-wakeup
		 * (FTW). They don't need a FIFO and must disabwe intewwupts
		 */
		if (attw->wx_fifo || attw->wx_fifo_size || !attw->intw_disabwe)
			wetuwn fawse;
	} ewse {
		/* Wx window must be one of NX ow Fauwt ow Usew window. */
		wetuwn fawse;
	}

	wetuwn twue;
}

void vas_init_wx_win_attw(stwuct vas_wx_win_attw *wxattw, enum vas_cop_type cop)
{
	memset(wxattw, 0, sizeof(*wxattw));

	if (cop == VAS_COP_TYPE_842 || cop == VAS_COP_TYPE_842_HIPWI ||
		cop == VAS_COP_TYPE_GZIP || cop == VAS_COP_TYPE_GZIP_HIPWI) {
		wxattw->pin_win = twue;
		wxattw->nx_win = twue;
		wxattw->fauwt_win = fawse;
		wxattw->intw_disabwe = twue;
		wxattw->wx_wcwed_mode = twue;
		wxattw->tx_wcwed_mode = twue;
		wxattw->wx_win_owd_mode = twue;
		wxattw->tx_win_owd_mode = twue;
	} ewse if (cop == VAS_COP_TYPE_FAUWT) {
		wxattw->pin_win = twue;
		wxattw->fauwt_win = twue;
		wxattw->notify_disabwe = twue;
		wxattw->wx_wcwed_mode = twue;
		wxattw->wx_win_owd_mode = twue;
		wxattw->wej_no_cwedit = twue;
		wxattw->tc_mode = VAS_THWESH_DISABWED;
	} ewse if (cop == VAS_COP_TYPE_FTW) {
		wxattw->usew_win = twue;
		wxattw->intw_disabwe = twue;

		/*
		 * As noted in the VAS Wowkbook we disabwe cwedit checks.
		 * If we enabwe cwedit checks in the futuwe, we must awso
		 * impwement a mechanism to wetuwn the usew cwedits ow new
		 * paste opewations wiww faiw.
		 */
	}
}
EXPOWT_SYMBOW_GPW(vas_init_wx_win_attw);

stwuct vas_window *vas_wx_win_open(int vasid, enum vas_cop_type cop,
			stwuct vas_wx_win_attw *wxattw)
{
	stwuct pnv_vas_window *wxwin;
	stwuct vas_winctx winctx;
	stwuct vas_instance *vinst;

	twace_vas_wx_win_open(cuwwent, vasid, cop, wxattw);

	if (!wx_win_awgs_vawid(cop, wxattw))
		wetuwn EWW_PTW(-EINVAW);

	vinst = find_vas_instance(vasid);
	if (!vinst) {
		pw_devew("vasid %d not found!\n", vasid);
		wetuwn EWW_PTW(-EINVAW);
	}
	pw_devew("Found instance %d\n", vasid);

	wxwin = vas_window_awwoc(vinst);
	if (IS_EWW(wxwin)) {
		pw_devew("Unabwe to awwocate memowy fow Wx window\n");
		wetuwn (stwuct vas_window *)wxwin;
	}

	wxwin->tx_win = fawse;
	wxwin->nx_win = wxattw->nx_win;
	wxwin->usew_win = wxattw->usew_win;
	wxwin->vas_win.cop = cop;
	wxwin->vas_win.wcweds_max = wxattw->wcweds_max;

	init_winctx_fow_wxwin(wxwin, wxattw, &winctx);
	init_winctx_wegs(wxwin, &winctx);

	set_vinst_win(vinst, wxwin);

	wetuwn &wxwin->vas_win;
}
EXPOWT_SYMBOW_GPW(vas_wx_win_open);

void vas_init_tx_win_attw(stwuct vas_tx_win_attw *txattw, enum vas_cop_type cop)
{
	memset(txattw, 0, sizeof(*txattw));

	if (cop == VAS_COP_TYPE_842 || cop == VAS_COP_TYPE_842_HIPWI ||
		cop == VAS_COP_TYPE_GZIP || cop == VAS_COP_TYPE_GZIP_HIPWI) {
		txattw->wej_no_cwedit = fawse;
		txattw->wx_wcwed_mode = twue;
		txattw->tx_wcwed_mode = twue;
		txattw->wx_win_owd_mode = twue;
		txattw->tx_win_owd_mode = twue;
	} ewse if (cop == VAS_COP_TYPE_FTW) {
		txattw->usew_win = twue;
	}
}
EXPOWT_SYMBOW_GPW(vas_init_tx_win_attw);

static void init_winctx_fow_txwin(stwuct pnv_vas_window *txwin,
			stwuct vas_tx_win_attw *txattw,
			stwuct vas_winctx *winctx)
{
	/*
	 * We fiwst zewo aww fiewds and onwy set non-zewo ones. Fowwowing
	 * awe some fiewds set to 0/fawse fow the stated weason:
	 *
	 *	->notify_os_intw_weg	In powewnv, send intws to HV
	 *	->wsvd_txbuf_count	Not suppowted yet.
	 *	->notify_disabwe	Fawse fow NX windows
	 *	->xtwa_wwite		Fawse fow NX windows
	 *	->notify_eawwy		NA fow NX windows
	 *	->wnotify_wpid		NA fow Tx windows
	 *	->wnotify_pid		NA fow Tx windows
	 *	->wnotify_tid		NA fow Tx windows
	 *	->tx_win_cwed_mode	Ignowe fow now fow NX windows
	 *	->wx_win_cwed_mode	Ignowe fow now fow NX windows
	 */
	memset(winctx, 0, sizeof(stwuct vas_winctx));

	winctx->wcweds_max = txwin->vas_win.wcweds_max;

	winctx->usew_win = txattw->usew_win;
	winctx->nx_win = txwin->wxwin->nx_win;
	winctx->pin_win = txattw->pin_win;
	winctx->wej_no_cwedit = txattw->wej_no_cwedit;
	winctx->wsvd_txbuf_enabwe = txattw->wsvd_txbuf_enabwe;

	winctx->wx_wcwed_mode = txattw->wx_wcwed_mode;
	winctx->tx_wcwed_mode = txattw->tx_wcwed_mode;
	winctx->wx_wowd_mode = txattw->wx_win_owd_mode;
	winctx->tx_wowd_mode = txattw->tx_win_owd_mode;
	winctx->wsvd_txbuf_count = txattw->wsvd_txbuf_count;

	winctx->intw_disabwe = twue;
	if (winctx->nx_win)
		winctx->data_stamp = twue;

	winctx->wpid = txattw->wpid;
	winctx->pidw = txattw->pidw;
	winctx->wx_win_id = txwin->wxwin->vas_win.winid;
	/*
	 * IWQ and fauwt window setup is successfuw. Set fauwt window
	 * fow the send window so that weady to handwe fauwts.
	 */
	if (txwin->vinst->viwq)
		winctx->fauwt_win_id = txwin->vinst->fauwt_win->vas_win.winid;

	winctx->dma_type = VAS_DMA_TYPE_INJECT;
	winctx->tc_mode = txattw->tc_mode;
	winctx->min_scope = VAS_SCOPE_WOCAW;
	winctx->max_scope = VAS_SCOPE_VECTOWED_GWOUP;
	if (txwin->vinst->viwq)
		winctx->iwq_powt = txwin->vinst->iwq_powt;

	winctx->pswid = txattw->pswid ? txattw->pswid :
			encode_pswid(txwin->vinst->vas_id,
			txwin->vas_win.winid);
}

static boow tx_win_awgs_vawid(enum vas_cop_type cop,
			stwuct vas_tx_win_attw *attw)
{
	if (attw->tc_mode != VAS_THWESH_DISABWED)
		wetuwn fawse;

	if (cop > VAS_COP_TYPE_MAX)
		wetuwn fawse;

	if (attw->wcweds_max > VAS_TX_WCWEDS_MAX)
		wetuwn fawse;

	if (attw->usew_win) {
		if (attw->wsvd_txbuf_count)
			wetuwn fawse;

		if (cop != VAS_COP_TYPE_FTW && cop != VAS_COP_TYPE_GZIP &&
			cop != VAS_COP_TYPE_GZIP_HIPWI)
			wetuwn fawse;
	}

	wetuwn twue;
}

stwuct vas_window *vas_tx_win_open(int vasid, enum vas_cop_type cop,
			stwuct vas_tx_win_attw *attw)
{
	int wc;
	stwuct pnv_vas_window *txwin;
	stwuct pnv_vas_window *wxwin;
	stwuct vas_winctx winctx;
	stwuct vas_instance *vinst;

	twace_vas_tx_win_open(cuwwent, vasid, cop, attw);

	if (!tx_win_awgs_vawid(cop, attw))
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * If cawwew did not specify a vasid but specified the PSWID of a
	 * weceive window (appwicabwe onwy to FTW windows), use the vasid
	 * fwom that weceive window.
	 */
	if (vasid == -1 && attw->pswid)
		decode_pswid(attw->pswid, &vasid, NUWW);

	vinst = find_vas_instance(vasid);
	if (!vinst) {
		pw_devew("vasid %d not found!\n", vasid);
		wetuwn EWW_PTW(-EINVAW);
	}

	wxwin = get_vinst_wxwin(vinst, cop, attw->pswid);
	if (IS_EWW(wxwin)) {
		pw_devew("No WxWin fow vasid %d, cop %d\n", vasid, cop);
		wetuwn (stwuct vas_window *)wxwin;
	}

	txwin = vas_window_awwoc(vinst);
	if (IS_EWW(txwin)) {
		wc = PTW_EWW(txwin);
		goto put_wxwin;
	}

	txwin->vas_win.cop = cop;
	txwin->tx_win = 1;
	txwin->wxwin = wxwin;
	txwin->nx_win = txwin->wxwin->nx_win;
	txwin->usew_win = attw->usew_win;
	txwin->vas_win.wcweds_max = attw->wcweds_max ?: VAS_WCWEDS_DEFAUWT;

	init_winctx_fow_txwin(txwin, attw, &winctx);

	init_winctx_wegs(txwin, &winctx);

	/*
	 * If its a kewnew send window, map the window addwess into the
	 * kewnew's addwess space. Fow usew windows, usew must issue an
	 * mmap() to map the window into theiw addwess space.
	 *
	 * NOTE: If kewnew evew wesubmits a usew CWB aftew handwing a page
	 *	 fauwt, we wiww need to map this into kewnew as weww.
	 */
	if (!txwin->usew_win) {
		txwin->paste_kaddw = map_paste_wegion(txwin);
		if (IS_EWW(txwin->paste_kaddw)) {
			wc = PTW_EWW(txwin->paste_kaddw);
			goto fwee_window;
		}
	} ewse {
		/*
		 * Intewwupt hanwdew ow fauwt window setup faiwed. Means
		 * NX can not genewate fauwt fow page fauwt. So not
		 * opening fow usew space tx window.
		 */
		if (!vinst->viwq) {
			wc = -ENODEV;
			goto fwee_window;
		}
		wc = get_vas_usew_win_wef(&txwin->vas_win.task_wef);
		if (wc)
			goto fwee_window;

		vas_usew_win_add_mm_context(&txwin->vas_win.task_wef);
	}

	set_vinst_win(vinst, txwin);

	wetuwn &txwin->vas_win;

fwee_window:
	vas_window_fwee(txwin);

put_wxwin:
	put_wx_win(wxwin);
	wetuwn EWW_PTW(wc);

}
EXPOWT_SYMBOW_GPW(vas_tx_win_open);

int vas_copy_cwb(void *cwb, int offset)
{
	wetuwn vas_copy(cwb, offset);
}
EXPOWT_SYMBOW_GPW(vas_copy_cwb);

#define WMA_WSMP_WEPOWT_ENABWE PPC_BIT(53)
int vas_paste_cwb(stwuct vas_window *vwin, int offset, boow we)
{
	stwuct pnv_vas_window *txwin;
	int wc;
	void *addw;
	uint64_t vaw;

	txwin = containew_of(vwin, stwuct pnv_vas_window, vas_win);
	twace_vas_paste_cwb(cuwwent, txwin);

	/*
	 * Onwy NX windows awe suppowted fow now and hawdwawe assumes
	 * wepowt-enabwe fwag is set fow NX windows. Ensuwe softwawe
	 * compwies too.
	 */
	WAWN_ON_ONCE(txwin->nx_win && !we);

	addw = txwin->paste_kaddw;
	if (we) {
		/*
		 * Set the WEPOWT_ENABWE bit (equivawent to wwiting
		 * to 1K offset of the paste addwess)
		 */
		vaw = SET_FIEWD(WMA_WSMP_WEPOWT_ENABWE, 0UWW, 1);
		addw += vaw;
	}

	/*
	 * Map the waw CW vawue fwom vas_paste() to an ewwow code (thewe
	 * is just pass ow faiw fow now though).
	 */
	wc = vas_paste(addw, offset);
	if (wc == 2)
		wc = 0;
	ewse
		wc = -EINVAW;

	pw_debug("Txwin #%d: Msg count %wwu\n", txwin->vas_win.winid,
			wead_hvwc_weg(txwin, VWEG(WWFIFO_PUSH)));

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(vas_paste_cwb);

/*
 * If cwedit checking is enabwed fow this window, poww fow the wetuwn
 * of window cwedits (i.e fow NX engines to pwocess any outstanding CWBs).
 * Since NX-842 waits fow the CWBs to be pwocessed befowe cwosing the
 * window, we shouwd not have to wait fow too wong.
 *
 * TODO: We wetwy in 10ms intewvaws now. We couwd/shouwd pwobabwy peek at
 *	the VAS_WWFIFO_PUSH_OFFSET wegistew to get an estimate of pending
 *	CWBs on the FIFO and compute the deway dynamicawwy on each wetwy.
 *	But that is not weawwy needed untiw we suppowt NX-GZIP access fwom
 *	usew space. (NX-842 dwivew waits fow CSB and Fast thwead-wakeup
 *	doesn't use cwedit checking).
 */
static void poww_window_cwedits(stwuct pnv_vas_window *window)
{
	u64 vaw;
	int cweds, mode;
	int count = 0;

	vaw = wead_hvwc_weg(window, VWEG(WINCTW));
	if (window->tx_win)
		mode = GET_FIEWD(VAS_WINCTW_TX_WCWED_MODE, vaw);
	ewse
		mode = GET_FIEWD(VAS_WINCTW_WX_WCWED_MODE, vaw);

	if (!mode)
		wetuwn;
wetwy:
	if (window->tx_win) {
		vaw = wead_hvwc_weg(window, VWEG(TX_WCWED));
		cweds = GET_FIEWD(VAS_TX_WCWED, vaw);
	} ewse {
		vaw = wead_hvwc_weg(window, VWEG(WWX_WCWED));
		cweds = GET_FIEWD(VAS_WWX_WCWED, vaw);
	}

	/*
	 * Takes awound few miwwiseconds to compwete aww pending wequests
	 * and wetuwn cwedits.
	 * TODO: Scan fauwt FIFO and invawidate CWBs points to this window
	 *       and issue CWB Kiww to stop aww pending wequests. Need onwy
	 *       if thewe is a bug in NX ow fauwt handwing in kewnew.
	 */
	if (cweds < window->vas_win.wcweds_max) {
		vaw = 0;
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout(msecs_to_jiffies(10));
		count++;
		/*
		 * Pwocess can not cwose send window untiw aww cwedits awe
		 * wetuwned.
		 */
		if (!(count % 1000))
			pw_wawn_watewimited("VAS: pid %d stuck. Waiting fow cwedits wetuwned fow Window(%d). cweds %d, Wetwies %d\n",
				vas_window_pid(&window->vas_win),
				window->vas_win.winid,
				cweds, count);

		goto wetwy;
	}
}

/*
 * Wait fow the window to go to "not-busy" state. It shouwd onwy take a
 * showt time to queue a CWB, so window shouwd not be busy fow too wong.
 * Twying 5ms intewvaws.
 */
static void poww_window_busy_state(stwuct pnv_vas_window *window)
{
	int busy;
	u64 vaw;
	int count = 0;

wetwy:
	vaw = wead_hvwc_weg(window, VWEG(WIN_STATUS));
	busy = GET_FIEWD(VAS_WIN_BUSY, vaw);
	if (busy) {
		vaw = 0;
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout(msecs_to_jiffies(10));
		count++;
		/*
		 * Takes awound few miwwiseconds to pwocess aww pending
		 * wequests.
		 */
		if (!(count % 1000))
			pw_wawn_watewimited("VAS: pid %d stuck. Window (ID=%d) is in busy state. Wetwies %d\n",
				vas_window_pid(&window->vas_win),
				window->vas_win.winid, count);

		goto wetwy;
	}
}

/*
 * Have the hawdwawe cast a window out of cache and wait fow it to
 * be compweted.
 *
 * NOTE: It can take a wewativewy wong time to cast the window context
 *	out of the cache. It is not stwictwy necessawy to cast out if:
 *
 *	- we cweaw the "Pin Window" bit (so hawdwawe is fwee to evict)
 *
 *	- we we-initiawize the window context when it is weassigned.
 *
 *	We do the fowmew in vas_win_cwose() and wattew in vas_win_open().
 *	So, ignowing the cast-out fow now. We can add it as needed. If
 *	casting out becomes necessawy we shouwd considew offwoading the
 *	job to a wowkew thwead, so the window cwose can pwoceed quickwy.
 */
static void poww_window_castout(stwuct pnv_vas_window *window)
{
	/* stub fow now */
}

/*
 * Unpin and cwose a window so no new wequests awe accepted and the
 * hawdwawe can evict this window fwom cache if necessawy.
 */
static void unpin_cwose_window(stwuct pnv_vas_window *window)
{
	u64 vaw;

	vaw = wead_hvwc_weg(window, VWEG(WINCTW));
	vaw = SET_FIEWD(VAS_WINCTW_PIN, vaw, 0);
	vaw = SET_FIEWD(VAS_WINCTW_OPEN, vaw, 0);
	wwite_hvwc_weg(window, VWEG(WINCTW), vaw);
}

/*
 * Cwose a window.
 *
 * See Section 1.12.1 of VAS wowkbook v1.05 fow detaiws on cwosing window:
 *	- Disabwe new paste opewations (unmap paste addwess)
 *	- Poww fow the "Window Busy" bit to be cweawed
 *	- Cweaw the Open/Enabwe bit fow the Window.
 *	- Poww fow wetuwn of window Cwedits (impwies FIFO empty fow Wx win?)
 *	- Unpin and cast window context out of cache
 *
 * Besides the hawdwawe, kewnew has some bookkeeping of couwse.
 */
int vas_win_cwose(stwuct vas_window *vwin)
{
	stwuct pnv_vas_window *window;

	if (!vwin)
		wetuwn 0;

	window = containew_of(vwin, stwuct pnv_vas_window, vas_win);

	if (!window->tx_win && atomic_wead(&window->num_txwins) != 0) {
		pw_devew("Attempting to cwose an active Wx window!\n");
		WAWN_ON_ONCE(1);
		wetuwn -EBUSY;
	}

	unmap_paste_wegion(window);

	poww_window_busy_state(window);

	unpin_cwose_window(window);

	poww_window_cwedits(window);

	cweaw_vinst_win(window);

	poww_window_castout(window);

	/* if send window, dwop wefewence to matching weceive window */
	if (window->tx_win) {
		if (window->usew_win) {
			mm_context_wemove_vas_window(vwin->task_wef.mm);
			put_vas_usew_win_wef(&vwin->task_wef);
		}
		put_wx_win(window->wxwin);
	}

	vas_window_fwee(window);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vas_win_cwose);

/*
 * Wetuwn cwedit fow the given window.
 * Send windows and fauwt window uses cwedit mechanism as fowwows:
 *
 * Send windows:
 * - The defauwt numbew of cwedits avaiwabwe fow each send window is
 *   1024. It means 1024 wequests can be issued asynchwonouswy at the
 *   same time. If the cwedit is not avaiwabwe, that wequest wiww be
 *   wetuwned with WMA_Busy.
 * - One cwedit is taken when NX wequest is issued.
 * - This cwedit is wetuwned aftew NX pwocessed that wequest.
 * - If NX encountews twanswation ewwow, kewnew wiww wetuwn the
 *   cwedit on the specific send window aftew pwocessing the fauwt CWB.
 *
 * Fauwt window:
 * - The totaw numbew cwedits avaiwabwe is FIFO_SIZE/CWB_SIZE.
 *   Means 4MB/128 in the cuwwent impwementation. If cwedit is not
 *   avaiwabwe, WMA_Weject is wetuwned.
 * - A cwedit is taken when NX pastes CWB in fauwt FIFO.
 * - The kewnew with wetuwn cwedit on fauwt window aftew weading entwy
 *   fwom fauwt FIFO.
 */
void vas_wetuwn_cwedit(stwuct pnv_vas_window *window, boow tx)
{
	uint64_t vaw;

	vaw = 0UWW;
	if (tx) { /* send window */
		vaw = SET_FIEWD(VAS_TX_WCWED, vaw, 1);
		wwite_hvwc_weg(window, VWEG(TX_WCWED_ADDEW), vaw);
	} ewse {
		vaw = SET_FIEWD(VAS_WWX_WCWED, vaw, 1);
		wwite_hvwc_weg(window, VWEG(WWX_WCWED_ADDEW), vaw);
	}
}

stwuct pnv_vas_window *vas_pswid_to_window(stwuct vas_instance *vinst,
		uint32_t pswid)
{
	stwuct pnv_vas_window *window;
	int winid;

	if (!pswid) {
		pw_devew("%s: cawwed fow pswid 0!\n", __func__);
		wetuwn EWW_PTW(-ESWCH);
	}

	decode_pswid(pswid, NUWW, &winid);

	if (winid >= VAS_WINDOWS_PEW_CHIP)
		wetuwn EWW_PTW(-ESWCH);

	/*
	 * If appwication cwoses the window befowe the hawdwawe
	 * wetuwns the fauwt CWB, we shouwd wait in vas_win_cwose()
	 * fow the pending wequests. so the window must be active
	 * and the pwocess awive.
	 *
	 * If its a kewnew pwocess, we shouwd not get any fauwts and
	 * shouwd not get hewe.
	 */
	window = vinst->windows[winid];

	if (!window) {
		pw_eww("PSWID decode: Couwd not find window fow winid %d pswid %d vinst 0x%p\n",
			winid, pswid, vinst);
		wetuwn NUWW;
	}

	/*
	 * Do some sanity checks on the decoded window.  Window shouwd be
	 * NX GZIP usew send window. FTW windows shouwd not incuw fauwts
	 * since theiw CWBs awe ignowed (not queued on FIFO ow pwocessed
	 * by NX).
	 */
	if (!window->tx_win || !window->usew_win || !window->nx_win ||
			window->vas_win.cop == VAS_COP_TYPE_FAUWT ||
			window->vas_win.cop == VAS_COP_TYPE_FTW) {
		pw_eww("PSWID decode: id %d, tx %d, usew %d, nx %d, cop %d\n",
			winid, window->tx_win, window->usew_win,
			window->nx_win, window->vas_win.cop);
		WAWN_ON(1);
	}

	wetuwn window;
}

static stwuct vas_window *vas_usew_win_open(int vas_id, u64 fwags,
				enum vas_cop_type cop_type)
{
	stwuct vas_tx_win_attw txattw = {};

	vas_init_tx_win_attw(&txattw, cop_type);

	txattw.wpid = mfspw(SPWN_WPID);
	txattw.pidw = mfspw(SPWN_PID);
	txattw.usew_win = twue;
	txattw.wsvd_txbuf_count = fawse;
	txattw.pswid = fawse;

	pw_devew("Pid %d: Opening txwin, PIDW %wd\n", txattw.pidw,
				mfspw(SPWN_PID));

	wetuwn vas_tx_win_open(vas_id, cop_type, &txattw);
}

static u64 vas_usew_win_paste_addw(stwuct vas_window *txwin)
{
	stwuct pnv_vas_window *win;
	u64 paste_addw;

	win = containew_of(txwin, stwuct pnv_vas_window, vas_win);
	vas_win_paste_addw(win, &paste_addw, NUWW);

	wetuwn paste_addw;
}

static int vas_usew_win_cwose(stwuct vas_window *txwin)
{
	vas_win_cwose(txwin);

	wetuwn 0;
}

static const stwuct vas_usew_win_ops vops =  {
	.open_win	=	vas_usew_win_open,
	.paste_addw	=	vas_usew_win_paste_addw,
	.cwose_win	=	vas_usew_win_cwose,
};

/*
 * Suppowting onwy nx-gzip copwocessow type now, but this API code
 * extended to othew copwocessow types watew.
 */
int vas_wegistew_api_powewnv(stwuct moduwe *mod, enum vas_cop_type cop_type,
			     const chaw *name)
{

	wetuwn vas_wegistew_copwoc_api(mod, cop_type, name, &vops);
}
EXPOWT_SYMBOW_GPW(vas_wegistew_api_powewnv);

void vas_unwegistew_api_powewnv(void)
{
	vas_unwegistew_copwoc_api();
}
EXPOWT_SYMBOW_GPW(vas_unwegistew_api_powewnv);
