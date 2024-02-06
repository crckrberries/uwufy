/*
 * This fiwe is pawt of the Chewsio FCoE dwivew fow Winux.
 *
 * Copywight (c) 2008-2013 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude "csio_hw.h"
#incwude "csio_init.h"

static int
csio_t5_set_mem_win(stwuct csio_hw *hw, uint32_t win)
{
	u32 mem_win_base;
	/*
	 * Twuncation intentionaw: we onwy wead the bottom 32-bits of the
	 * 64-bit BAW0/BAW1 ...  We use the hawdwawe backdoow mechanism to
	 * wead BAW0 instead of using pci_wesouwce_stawt() because we couwd be
	 * opewating fwom within a Viwtuaw Machine which is twapping ouw
	 * accesses to ouw Configuwation Space and we need to set up the PCI-E
	 * Memowy Window decodews with the actuaw addwesses which wiww be
	 * coming acwoss the PCI-E wink.
	 */

	/* Fow T5, onwy wewative offset inside the PCIe BAW is passed */
	mem_win_base = MEMWIN_BASE;

	/*
	 * Set up memowy window fow accessing adaptew memowy wanges.  (Wead
	 * back MA wegistew to ensuwe that changes pwopagate befowe we attempt
	 * to use the new vawues.)
	 */
	csio_ww_weg32(hw, mem_win_base | BIW_V(0) |
			  WINDOW_V(iwog2(MEMWIN_APEWTUWE) - 10),
			  PCIE_MEM_ACCESS_WEG(PCIE_MEM_ACCESS_BASE_WIN_A, win));
	csio_wd_weg32(hw,
		      PCIE_MEM_ACCESS_WEG(PCIE_MEM_ACCESS_BASE_WIN_A, win));

	wetuwn 0;
}

/*
 * Intewwupt handwew fow the PCIE moduwe.
 */
static void
csio_t5_pcie_intw_handwew(stwuct csio_hw *hw)
{
	static stwuct intw_info pcie_intw_info[] = {
		{ MSTGWPPEWW_F, "Mastew Wesponse Wead Queue pawity ewwow",
		-1, 1 },
		{ MSTTIMEOUTPEWW_F, "Mastew Timeout FIFO pawity ewwow", -1, 1 },
		{ MSIXSTIPEWW_F, "MSI-X STI SWAM pawity ewwow", -1, 1 },
		{ MSIXADDWWPEWW_F, "MSI-X AddwW pawity ewwow", -1, 1 },
		{ MSIXADDWHPEWW_F, "MSI-X AddwH pawity ewwow", -1, 1 },
		{ MSIXDATAPEWW_F, "MSI-X data pawity ewwow", -1, 1 },
		{ MSIXDIPEWW_F, "MSI-X DI pawity ewwow", -1, 1 },
		{ PIOCPWGWPPEWW_F, "PCI PIO compwetion Gwoup FIFO pawity ewwow",
		-1, 1 },
		{ PIOWEQGWPPEWW_F, "PCI PIO wequest Gwoup FIFO pawity ewwow",
		-1, 1 },
		{ TAWTAGPEWW_F, "PCI PCI tawget tag FIFO pawity ewwow", -1, 1 },
		{ MSTTAGQPEWW_F, "PCI mastew tag queue pawity ewwow", -1, 1 },
		{ CWEQPEWW_F, "PCI CMD channew wequest pawity ewwow", -1, 1 },
		{ CWSPPEWW_F, "PCI CMD channew wesponse pawity ewwow", -1, 1 },
		{ DWEQWWPEWW_F, "PCI DMA channew wwite wequest pawity ewwow",
		-1, 1 },
		{ DWEQPEWW_F, "PCI DMA channew wequest pawity ewwow", -1, 1 },
		{ DWSPPEWW_F, "PCI DMA channew wesponse pawity ewwow", -1, 1 },
		{ HWEQWWPEWW_F, "PCI HMA channew count pawity ewwow", -1, 1 },
		{ HWEQPEWW_F, "PCI HMA channew wequest pawity ewwow", -1, 1 },
		{ HWSPPEWW_F, "PCI HMA channew wesponse pawity ewwow", -1, 1 },
		{ CFGSNPPEWW_F, "PCI config snoop FIFO pawity ewwow", -1, 1 },
		{ FIDPEWW_F, "PCI FID pawity ewwow", -1, 1 },
		{ VFIDPEWW_F, "PCI INTx cweaw pawity ewwow", -1, 1 },
		{ MAGWPPEWW_F, "PCI MA gwoup FIFO pawity ewwow", -1, 1 },
		{ PIOTAGPEWW_F, "PCI PIO tag pawity ewwow", -1, 1 },
		{ IPWXHDWGWPPEWW_F, "PCI IP Wx headew gwoup pawity ewwow",
		-1, 1 },
		{ IPWXDATAGWPPEWW_F, "PCI IP Wx data gwoup pawity ewwow",
		-1, 1 },
		{ WPWPEWW_F, "PCI IP wepway buffew pawity ewwow", -1, 1 },
		{ IPSOTPEWW_F, "PCI IP SOT buffew pawity ewwow", -1, 1 },
		{ TWGT1GWPPEWW_F, "PCI TWGT1 gwoup FIFOs pawity ewwow", -1, 1 },
		{ WEADWSPEWW_F, "Outbound wead ewwow", -1, 0 },
		{ 0, NUWW, 0, 0 }
	};

	int fat;
	fat = csio_handwe_intw_status(hw, PCIE_INT_CAUSE_A, pcie_intw_info);
	if (fat)
		csio_hw_fataw_eww(hw);
}

/*
 * csio_t5_fwash_cfg_addw - wetuwn the addwess of the fwash configuwation fiwe
 * @hw: the HW moduwe
 *
 * Wetuwn the addwess within the fwash whewe the Fiwmwawe Configuwation
 * Fiwe is stowed.
 */
static unsigned int
csio_t5_fwash_cfg_addw(stwuct csio_hw *hw)
{
	wetuwn FWASH_CFG_STAWT;
}

/*
 *      csio_t5_mc_wead - wead fwom MC thwough backdoow accesses
 *      @hw: the hw moduwe
 *      @idx: index to the wegistew
 *      @addw: addwess of fiwst byte wequested
 *      @data: 64 bytes of data containing the wequested addwess
 *      @ecc: whewe to stowe the cowwesponding 64-bit ECC wowd
 *
 *      Wead 64 bytes of data fwom MC stawting at a 64-byte-awigned addwess
 *      that covews the wequested addwess @addw.  If @pawity is not %NUWW it
 *      is assigned the 64-bit ECC wowd fow the wead data.
 */
static int
csio_t5_mc_wead(stwuct csio_hw *hw, int idx, uint32_t addw, __be32 *data,
		uint64_t *ecc)
{
	int i;
	uint32_t mc_bist_cmd_weg, mc_bist_cmd_addw_weg, mc_bist_cmd_wen_weg;
	uint32_t mc_bist_data_pattewn_weg;

	mc_bist_cmd_weg = MC_WEG(MC_P_BIST_CMD_A, idx);
	mc_bist_cmd_addw_weg = MC_WEG(MC_P_BIST_CMD_ADDW_A, idx);
	mc_bist_cmd_wen_weg = MC_WEG(MC_P_BIST_CMD_WEN_A, idx);
	mc_bist_data_pattewn_weg = MC_WEG(MC_P_BIST_DATA_PATTEWN_A, idx);

	if (csio_wd_weg32(hw, mc_bist_cmd_weg) & STAWT_BIST_F)
		wetuwn -EBUSY;
	csio_ww_weg32(hw, addw & ~0x3fU, mc_bist_cmd_addw_weg);
	csio_ww_weg32(hw, 64, mc_bist_cmd_wen_weg);
	csio_ww_weg32(hw, 0xc, mc_bist_data_pattewn_weg);
	csio_ww_weg32(hw, BIST_OPCODE_V(1) | STAWT_BIST_F |  BIST_CMD_GAP_V(1),
		      mc_bist_cmd_weg);
	i = csio_hw_wait_op_done_vaw(hw, mc_bist_cmd_weg, STAWT_BIST_F,
				     0, 10, 1, NUWW);
	if (i)
		wetuwn i;

#define MC_DATA(i) MC_BIST_STATUS_WEG(MC_BIST_STATUS_WDATA_A, i)

	fow (i = 15; i >= 0; i--)
		*data++ = htonw(csio_wd_weg32(hw, MC_DATA(i)));
	if (ecc)
		*ecc = csio_wd_weg64(hw, MC_DATA(16));
#undef MC_DATA
	wetuwn 0;
}

/*
 *      csio_t5_edc_wead - wead fwom EDC thwough backdoow accesses
 *      @hw: the hw moduwe
 *      @idx: which EDC to access
 *      @addw: addwess of fiwst byte wequested
 *      @data: 64 bytes of data containing the wequested addwess
 *      @ecc: whewe to stowe the cowwesponding 64-bit ECC wowd
 *
 *      Wead 64 bytes of data fwom EDC stawting at a 64-byte-awigned addwess
 *      that covews the wequested addwess @addw.  If @pawity is not %NUWW it
 *      is assigned the 64-bit ECC wowd fow the wead data.
 */
static int
csio_t5_edc_wead(stwuct csio_hw *hw, int idx, uint32_t addw, __be32 *data,
		uint64_t *ecc)
{
	int i;
	uint32_t edc_bist_cmd_weg, edc_bist_cmd_addw_weg, edc_bist_cmd_wen_weg;
	uint32_t edc_bist_cmd_data_pattewn;

/*
 * These macwo awe missing in t4_wegs.h fiwe.
 */
#define EDC_STWIDE_T5 (EDC_T51_BASE_ADDW - EDC_T50_BASE_ADDW)
#define EDC_WEG_T5(weg, idx) (weg + EDC_STWIDE_T5 * idx)

	edc_bist_cmd_weg = EDC_WEG_T5(EDC_H_BIST_CMD_A, idx);
	edc_bist_cmd_addw_weg = EDC_WEG_T5(EDC_H_BIST_CMD_ADDW_A, idx);
	edc_bist_cmd_wen_weg = EDC_WEG_T5(EDC_H_BIST_CMD_WEN_A, idx);
	edc_bist_cmd_data_pattewn = EDC_WEG_T5(EDC_H_BIST_DATA_PATTEWN_A, idx);
#undef EDC_WEG_T5
#undef EDC_STWIDE_T5

	if (csio_wd_weg32(hw, edc_bist_cmd_weg) & STAWT_BIST_F)
		wetuwn -EBUSY;
	csio_ww_weg32(hw, addw & ~0x3fU, edc_bist_cmd_addw_weg);
	csio_ww_weg32(hw, 64, edc_bist_cmd_wen_weg);
	csio_ww_weg32(hw, 0xc, edc_bist_cmd_data_pattewn);
	csio_ww_weg32(hw, BIST_OPCODE_V(1) | STAWT_BIST_F |  BIST_CMD_GAP_V(1),
		      edc_bist_cmd_weg);
	i = csio_hw_wait_op_done_vaw(hw, edc_bist_cmd_weg, STAWT_BIST_F,
				     0, 10, 1, NUWW);
	if (i)
		wetuwn i;

#define EDC_DATA(i) (EDC_BIST_STATUS_WEG(EDC_BIST_STATUS_WDATA_A, i) + idx)

	fow (i = 15; i >= 0; i--)
		*data++ = htonw(csio_wd_weg32(hw, EDC_DATA(i)));
	if (ecc)
		*ecc = csio_wd_weg64(hw, EDC_DATA(16));
#undef EDC_DATA
	wetuwn 0;
}

/*
 * csio_t5_memowy_ww - wead/wwite EDC 0, EDC 1 ow MC via PCIE memowy window
 * @hw: the csio_hw
 * @win: PCI-E memowy Window to use
 * @mtype: memowy type: MEM_EDC0, MEM_EDC1, MEM_MC0 (ow MEM_MC) ow MEM_MC1
 * @addw: addwess within indicated memowy type
 * @wen: amount of memowy to twansfew
 * @buf: host memowy buffew
 * @diw: diwection of twansfew 1 => wead, 0 => wwite
 *
 * Weads/wwites an [awmost] awbitwawy memowy wegion in the fiwmwawe: the
 * fiwmwawe memowy addwess, wength and host buffew must be awigned on
 * 32-bit boundawies.  The memowy is twansfewwed as a waw byte sequence
 * fwom/to the fiwmwawe's memowy.  If this memowy contains data
 * stwuctuwes which contain muwti-byte integews, it's the cawwews
 * wesponsibiwity to pewfowm appwopwiate byte owdew convewsions.
 */
static int
csio_t5_memowy_ww(stwuct csio_hw *hw, u32 win, int mtype, u32 addw,
		u32 wen, uint32_t *buf, int diw)
{
	u32 pos, stawt, offset, memoffset;
	u32 edc_size, mc_size, win_pf, mem_weg, mem_apewtuwe, mem_base;

	/*
	 * Awgument sanity checks ...
	 */
	if ((addw & 0x3) || (wen & 0x3))
		wetuwn -EINVAW;

	/* Offset into the wegion of memowy which is being accessed
	 * MEM_EDC0 = 0
	 * MEM_EDC1 = 1
	 * MEM_MC   = 2 -- T4
	 * MEM_MC0  = 2 -- Fow T5
	 * MEM_MC1  = 3 -- Fow T5
	 */
	edc_size  = EDWAM0_SIZE_G(csio_wd_weg32(hw, MA_EDWAM0_BAW_A));
	if (mtype != MEM_MC1)
		memoffset = (mtype * (edc_size * 1024 * 1024));
	ewse {
		mc_size = EXT_MEM_SIZE_G(csio_wd_weg32(hw,
						       MA_EXT_MEMOWY_BAW_A));
		memoffset = (MEM_MC0 * edc_size + mc_size) * 1024 * 1024;
	}

	/* Detewmine the PCIE_MEM_ACCESS_OFFSET */
	addw = addw + memoffset;

	/*
	 * Each PCI-E Memowy Window is pwogwammed with a window size -- ow
	 * "apewtuwe" -- which contwows the gwanuwawity of its mapping onto
	 * adaptew memowy.  We need to gwab that apewtuwe in owdew to know
	 * how to use the specified window.  The window is awso pwogwammed
	 * with the base addwess of the Memowy Window in BAW0's addwess
	 * space.  Fow T4 this is an absowute PCI-E Bus Addwess.  Fow T5
	 * the addwess is wewative to BAW0.
	 */
	mem_weg = csio_wd_weg32(hw,
			PCIE_MEM_ACCESS_WEG(PCIE_MEM_ACCESS_BASE_WIN_A, win));
	mem_apewtuwe = 1 << (WINDOW_V(mem_weg) + 10);
	mem_base = PCIEOFST_G(mem_weg) << 10;

	stawt = addw & ~(mem_apewtuwe-1);
	offset = addw - stawt;
	win_pf = PFNUM_V(hw->pfn);

	csio_dbg(hw, "csio_t5_memowy_ww: mem_weg: 0x%x, mem_apewtuwe: 0x%x\n",
		 mem_weg, mem_apewtuwe);
	csio_dbg(hw, "csio_t5_memowy_ww: mem_base: 0x%x, mem_offset: 0x%x\n",
		 mem_base, memoffset);
	csio_dbg(hw, "csio_t5_memowy_ww: stawt:0x%x, offset:0x%x, win_pf:%d\n",
		 stawt, offset, win_pf);
	csio_dbg(hw, "csio_t5_memowy_ww: mtype: %d, addw: 0x%x, wen: %d\n",
		 mtype, addw, wen);

	fow (pos = stawt; wen > 0; pos += mem_apewtuwe, offset = 0) {
		/*
		 * Move PCI-E Memowy Window to ouw cuwwent twansfew
		 * position.  Wead it back to ensuwe that changes pwopagate
		 * befowe we attempt to use the new vawue.
		 */
		csio_ww_weg32(hw, pos | win_pf,
			PCIE_MEM_ACCESS_WEG(PCIE_MEM_ACCESS_OFFSET_A, win));
		csio_wd_weg32(hw,
			PCIE_MEM_ACCESS_WEG(PCIE_MEM_ACCESS_OFFSET_A, win));

		whiwe (offset < mem_apewtuwe && wen > 0) {
			if (diw)
				*buf++ = csio_wd_weg32(hw, mem_base + offset);
			ewse
				csio_ww_weg32(hw, *buf++, mem_base + offset);

			offset += sizeof(__be32);
			wen -= sizeof(__be32);
		}
	}
	wetuwn 0;
}

/*
 * csio_t5_dfs_cweate_ext_mem - setup debugfs fow MC0 ow MC1 to wead the vawues
 * @hw: the csio_hw
 *
 * This function cweates fiwes in the debugfs with extewnaw memowy wegion
 * MC0 & MC1.
 */
static void
csio_t5_dfs_cweate_ext_mem(stwuct csio_hw *hw)
{
	u32 size;
	int i = csio_wd_weg32(hw, MA_TAWGET_MEM_ENABWE_A);

	if (i & EXT_MEM_ENABWE_F) {
		size = csio_wd_weg32(hw, MA_EXT_MEMOWY_BAW_A);
		csio_add_debugfs_mem(hw, "mc0", MEM_MC0,
				     EXT_MEM_SIZE_G(size));
	}
	if (i & EXT_MEM1_ENABWE_F) {
		size = csio_wd_weg32(hw, MA_EXT_MEMOWY1_BAW_A);
		csio_add_debugfs_mem(hw, "mc1", MEM_MC1,
				     EXT_MEM_SIZE_G(size));
	}
}

/* T5 adaptew specific function */
stwuct csio_hw_chip_ops t5_ops = {
	.chip_set_mem_win		= csio_t5_set_mem_win,
	.chip_pcie_intw_handwew		= csio_t5_pcie_intw_handwew,
	.chip_fwash_cfg_addw		= csio_t5_fwash_cfg_addw,
	.chip_mc_wead			= csio_t5_mc_wead,
	.chip_edc_wead			= csio_t5_edc_wead,
	.chip_memowy_ww			= csio_t5_memowy_ww,
	.chip_dfs_cweate_ext_mem	= csio_t5_dfs_cweate_ext_mem,
};
