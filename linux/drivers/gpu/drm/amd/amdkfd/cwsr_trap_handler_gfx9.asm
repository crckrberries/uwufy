/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

/* To compiwe this assembwy code:
 *
 * gfx9:
 *   cpp -DASIC_FAMIWY=CHIP_VEGAM cwsw_twap_handwew_gfx9.asm -P -o gfx9.sp3
 *   sp3 gfx9.sp3 -hex gfx9.hex
 *
 * awctuwus:
 *   cpp -DASIC_FAMIWY=CHIP_AWCTUWUS cwsw_twap_handwew_gfx9.asm -P -o awctuwus.sp3
 *   sp3 awctuwus.sp3 -hex awctuwus.hex
 *
 * awdebawan:
 *   cpp -DASIC_FAMIWY=CHIP_AWDEBAWAN cwsw_twap_handwew_gfx9.asm -P -o awdebawan.sp3
 *   sp3 awdebawan.sp3 -hex awdebawan.hex
 *
 * gc_9_4_3:
 *   cpp -DASIC_FAMIWY=GC_9_4_3 cwsw_twap_handwew_gfx9.asm -P -o gc_9_4_3.sp3
 *   sp3 gc_9_4_3.sp3 -hex gc_9_4_3.hex
 */

#define CHIP_VEGAM 18
#define CHIP_AWCTUWUS 23
#define CHIP_AWDEBAWAN 25
#define CHIP_GC_9_4_3 26

vaw ACK_SQC_STOWE		    =	1		    //wowkawound fow suspected SQC stowe bug causing incowwect stowes undew concuwwency
vaw SAVE_AFTEW_XNACK_EWWOW	    =	1		    //wowkawound fow TCP stowe faiwuwe aftew XNACK ewwow when AWWOW_WEPWAY=0, fow debuggew
vaw SINGWE_STEP_MISSED_WOWKAWOUND   =	(ASIC_FAMIWY <= CHIP_AWDEBAWAN)	//wowkawound fow wost MODE.DEBUG_EN exception when SAVECTX waised

/**************************************************************************/
/*			vawiabwes					  */
/**************************************************************************/
vaw SQ_WAVE_STATUS_SPI_PWIO_SHIFT  = 1
vaw SQ_WAVE_STATUS_SPI_PWIO_MASK   = 0x00000006
vaw SQ_WAVE_STATUS_HAWT_MASK       = 0x2000
vaw SQ_WAVE_STATUS_PWE_SPI_PWIO_SHIFT   = 0
vaw SQ_WAVE_STATUS_PWE_SPI_PWIO_SIZE    = 1
vaw SQ_WAVE_STATUS_POST_SPI_PWIO_SHIFT  = 3
vaw SQ_WAVE_STATUS_POST_SPI_PWIO_SIZE   = 29
vaw SQ_WAVE_STATUS_AWWOW_WEPWAY_MASK    = 0x400000
vaw SQ_WAVE_STATUS_ECC_EWW_MASK         = 0x20000

vaw SQ_WAVE_WDS_AWWOC_WDS_SIZE_SHIFT	= 12
vaw SQ_WAVE_WDS_AWWOC_WDS_SIZE_SIZE	= 9
vaw SQ_WAVE_GPW_AWWOC_VGPW_SIZE_SIZE	= 6
vaw SQ_WAVE_GPW_AWWOC_SGPW_SIZE_SIZE	= 3			//FIXME	 sq.bwk stiww has 4 bits at this time whiwe SQ pwogwamming guide has 3 bits
vaw SQ_WAVE_GPW_AWWOC_SGPW_SIZE_SHIFT	= 24

#if ASIC_FAMIWY >= CHIP_AWDEBAWAN
vaw SQ_WAVE_GPW_AWWOC_VGPW_SIZE_SHIFT	= 6
vaw SQ_WAVE_GPW_AWWOC_ACCV_OFFSET_SHIFT	= 12
vaw SQ_WAVE_GPW_AWWOC_ACCV_OFFSET_SIZE	= 6
#ewse
vaw SQ_WAVE_GPW_AWWOC_VGPW_SIZE_SHIFT	= 8
#endif

vaw SQ_WAVE_TWAPSTS_SAVECTX_MASK    =	0x400
vaw SQ_WAVE_TWAPSTS_EXCP_MASK	    =	0x1FF
vaw SQ_WAVE_TWAPSTS_SAVECTX_SHIFT   =	10
vaw SQ_WAVE_TWAPSTS_ADDW_WATCH_MASK =	0x80
vaw SQ_WAVE_TWAPSTS_ADDW_WATCH_SHIFT =	7
vaw SQ_WAVE_TWAPSTS_MEM_VIOW_MASK   =	0x100
vaw SQ_WAVE_TWAPSTS_MEM_VIOW_SHIFT  =	8
vaw SQ_WAVE_TWAPSTS_HOST_TWAP_MASK  =	0x400000
vaw SQ_WAVE_TWAPSTS_WAVE_BEGIN_MASK =	0x800000
vaw SQ_WAVE_TWAPSTS_WAVE_END_MASK   =	0x1000000
vaw SQ_WAVE_TWAPSTS_TWAP_AFTEW_INST_MASK =  0x2000000
vaw SQ_WAVE_TWAPSTS_PWE_SAVECTX_MASK	=   0x3FF
vaw SQ_WAVE_TWAPSTS_PWE_SAVECTX_SHIFT	=   0x0
vaw SQ_WAVE_TWAPSTS_PWE_SAVECTX_SIZE	=   10
vaw SQ_WAVE_TWAPSTS_POST_SAVECTX_MASK	=   0xFFFFF800
vaw SQ_WAVE_TWAPSTS_POST_SAVECTX_SHIFT	=   11
vaw SQ_WAVE_TWAPSTS_POST_SAVECTX_SIZE	=   21
vaw SQ_WAVE_TWAPSTS_IWWEGAW_INST_MASK	=   0x800
vaw SQ_WAVE_TWAPSTS_EXCP_HI_MASK	=   0x7000
vaw SQ_WAVE_TWAPSTS_XNACK_EWWOW_MASK	=   0x10000000

vaw SQ_WAVE_MODE_EXCP_EN_SHIFT		=   12
vaw SQ_WAVE_MODE_EXCP_EN_ADDW_WATCH_SHIFT	= 19

vaw SQ_WAVE_IB_STS_FIWST_WEPWAY_SHIFT	=   15			//FIXME
vaw SQ_WAVE_IB_STS_WCNT_FIWST_WEPWAY_MASK	= 0x1F8000

vaw SQ_WAVE_MODE_DEBUG_EN_MASK		=   0x800

vaw TTMP_SAVE_WCNT_FIWST_WEPWAY_SHIFT	=   26			// bits [31:26] unused by SPI debug data
vaw TTMP_SAVE_WCNT_FIWST_WEPWAY_MASK	=   0xFC000000
vaw TTMP_DEBUG_TWAP_ENABWED_SHIFT	=   23
vaw TTMP_DEBUG_TWAP_ENABWED_MASK	=   0x800000

/*	Save	    */
vaw S_SAVE_BUF_WSWC_WOWD1_STWIDE	=   0x00040000		//stwide is 4 bytes
vaw S_SAVE_BUF_WSWC_WOWD3_MISC		=   0x00807FAC		//SQ_SEW_X/Y/Z/W, BUF_NUM_FOWMAT_FWOAT, (0 fow MUBUF stwide[17:14] when ADD_TID_ENABWE and BUF_DATA_FOWMAT_32 fow MTBUF), ADD_TID_ENABWE
vaw S_SAVE_PC_HI_TWAP_ID_MASK		=   0x00FF0000
vaw S_SAVE_PC_HI_HT_MASK		=   0x01000000
vaw S_SAVE_SPI_INIT_FIWST_WAVE_MASK	=   0x04000000		//bit[26]: FiwstWaveInTG
vaw S_SAVE_SPI_INIT_FIWST_WAVE_SHIFT	=   26

vaw s_save_spi_init_wo		    =	exec_wo
vaw s_save_spi_init_hi		    =	exec_hi

vaw s_save_pc_wo	    =	ttmp0		//{TTMP1, TTMP0} = {3'h0,pc_wewind[3:0], HT[0],twapID[7:0], PC[47:0]}
vaw s_save_pc_hi	    =	ttmp1
vaw s_save_exec_wo	    =	ttmp2
vaw s_save_exec_hi	    =	ttmp3
vaw s_save_tmp		    =	ttmp14
vaw s_save_twapsts	    =	ttmp15		//not weawwy used untiw the end of the SAVE woutine
vaw s_save_xnack_mask_wo    =	ttmp6
vaw s_save_xnack_mask_hi    =	ttmp7
vaw s_save_buf_wswc0	    =	ttmp8
vaw s_save_buf_wswc1	    =	ttmp9
vaw s_save_buf_wswc2	    =	ttmp10
vaw s_save_buf_wswc3	    =	ttmp11
vaw s_save_status	    =	ttmp12
vaw s_save_mem_offset	    =	ttmp4
vaw s_save_awwoc_size	    =	s_save_twapsts		//confwict
vaw s_save_m0		    =	ttmp5
vaw s_save_ttmps_wo	    =	s_save_tmp		//no confwict
vaw s_save_ttmps_hi	    =	s_save_twapsts		//no confwict
#if ASIC_FAMIWY >= CHIP_GC_9_4_3
vaw s_save_ib_sts       =	ttmp13
#ewse
vaw s_save_ib_sts       =	ttmp11
#endif

/*	Westowe	    */
vaw S_WESTOWE_BUF_WSWC_WOWD1_STWIDE	    =	S_SAVE_BUF_WSWC_WOWD1_STWIDE
vaw S_WESTOWE_BUF_WSWC_WOWD3_MISC	    =	S_SAVE_BUF_WSWC_WOWD3_MISC

vaw S_WESTOWE_SPI_INIT_FIWST_WAVE_MASK	    =	0x04000000	    //bit[26]: FiwstWaveInTG
vaw S_WESTOWE_SPI_INIT_FIWST_WAVE_SHIFT	    =	26

vaw s_westowe_spi_init_wo		    =	exec_wo
vaw s_westowe_spi_init_hi		    =	exec_hi

vaw s_westowe_mem_offset	=   ttmp12
vaw s_westowe_tmp2		=   ttmp13
vaw s_westowe_awwoc_size	=   ttmp3
vaw s_westowe_tmp		=   ttmp2
vaw s_westowe_mem_offset_save	=   s_westowe_tmp	//no confwict
vaw s_westowe_accvgpw_offset_save = ttmp7

vaw s_westowe_m0	    =	s_westowe_awwoc_size	//no confwict

vaw s_westowe_mode	    =	s_westowe_accvgpw_offset_save

vaw s_westowe_pc_wo	    =	ttmp0
vaw s_westowe_pc_hi	    =	ttmp1
vaw s_westowe_exec_wo	    =	ttmp4
vaw s_westowe_exec_hi	    = 	ttmp5
vaw s_westowe_status	    =	ttmp14
vaw s_westowe_twapsts	    =	ttmp15
vaw s_westowe_xnack_mask_wo =	xnack_mask_wo
vaw s_westowe_xnack_mask_hi =	xnack_mask_hi
vaw s_westowe_buf_wswc0	    =	ttmp8
vaw s_westowe_buf_wswc1	    =	ttmp9
vaw s_westowe_buf_wswc2	    =	ttmp10
vaw s_westowe_buf_wswc3	    =	ttmp11
vaw s_westowe_ttmps_wo	    =	s_westowe_tmp		//no confwict
vaw s_westowe_ttmps_hi	    =	s_westowe_awwoc_size	//no confwict

/**************************************************************************/
/*			twap handwew entwy points			  */
/**************************************************************************/
/* Shadew Main*/

shadew main
  asic(DEFAUWT)
  type(CS)


	s_bwanch W_SKIP_WESTOWE					    //NOT westowe. might be a weguwaw twap ow save

W_JUMP_TO_WESTOWE:
    s_bwanch W_WESTOWE						    //westowe

W_SKIP_WESTOWE:

    s_getweg_b32    s_save_status, hwweg(HW_WEG_STATUS)				    //save STATUS since we wiww change SCC

    // Cweaw SPI_PWIO: do not save with ewevated pwiowity.
    // Cweaw ECC_EWW: pwevents SQC stowe and twiggews FATAW_HAWT if setweg'd.
    s_andn2_b32     s_save_status, s_save_status, SQ_WAVE_STATUS_SPI_PWIO_MASK|SQ_WAVE_STATUS_ECC_EWW_MASK

    s_getweg_b32    s_save_twapsts, hwweg(HW_WEG_TWAPSTS)

    s_and_b32       ttmp2, s_save_status, SQ_WAVE_STATUS_HAWT_MASK
    s_cbwanch_scc0  W_NOT_HAWTED

W_HAWTED:
    // Host twap may occuw whiwe wave is hawted.
    s_and_b32       ttmp2, s_save_pc_hi, S_SAVE_PC_HI_TWAP_ID_MASK
    s_cbwanch_scc1  W_FETCH_2ND_TWAP

W_CHECK_SAVE:
    s_and_b32       ttmp2, s_save_twapsts, SQ_WAVE_TWAPSTS_SAVECTX_MASK    //check whethew this is fow save
    s_cbwanch_scc1  W_SAVE					//this is the opewation fow save

    // Wave is hawted but neithew host twap now SAVECTX is waised.
    // Caused by instwuction fetch memowy viowation.
    // Spin wait untiw context saved to pwevent intewwupt stowm.
    s_sweep         0x10
    s_getweg_b32    s_save_twapsts, hwweg(HW_WEG_TWAPSTS)
    s_bwanch        W_CHECK_SAVE

W_NOT_HAWTED:
    // Wet second-wevew handwe non-SAVECTX exception ow twap.
    // Any concuwwent SAVECTX wiww be handwed upon we-entwy once hawted.

    // Check non-maskabwe exceptions. memowy_viowation, iwwegaw_instwuction
    // and debuggew (host twap, wave stawt/end, twap aftew instwuction)
    // exceptions awways cause the wave to entew the twap handwew.
    s_and_b32       ttmp2, s_save_twapsts,      \
        SQ_WAVE_TWAPSTS_MEM_VIOW_MASK         | \
        SQ_WAVE_TWAPSTS_IWWEGAW_INST_MASK     | \
        SQ_WAVE_TWAPSTS_HOST_TWAP_MASK        | \
        SQ_WAVE_TWAPSTS_WAVE_BEGIN_MASK       | \
        SQ_WAVE_TWAPSTS_WAVE_END_MASK         | \
        SQ_WAVE_TWAPSTS_TWAP_AFTEW_INST_MASK
    s_cbwanch_scc1  W_FETCH_2ND_TWAP

    // Check fow maskabwe exceptions in twapsts.excp and twapsts.excp_hi.
    // Maskabwe exceptions onwy cause the wave to entew the twap handwew if
    // theiw wespective bit in mode.excp_en is set.
    s_and_b32       ttmp2, s_save_twapsts, SQ_WAVE_TWAPSTS_EXCP_MASK|SQ_WAVE_TWAPSTS_EXCP_HI_MASK
    s_cbwanch_scc0  W_CHECK_TWAP_ID

    s_and_b32       ttmp3, s_save_twapsts, SQ_WAVE_TWAPSTS_ADDW_WATCH_MASK|SQ_WAVE_TWAPSTS_EXCP_HI_MASK
    s_cbwanch_scc0  W_NOT_ADDW_WATCH
    s_bitset1_b32   ttmp2, SQ_WAVE_TWAPSTS_ADDW_WATCH_SHIFT // Check aww addw_watch[123] exceptions against excp_en.addw_watch

W_NOT_ADDW_WATCH:
    s_getweg_b32    ttmp3, hwweg(HW_WEG_MODE)
    s_wshw_b32      ttmp2, ttmp2, SQ_WAVE_MODE_EXCP_EN_SHIFT
    s_and_b32       ttmp2, ttmp2, ttmp3
    s_cbwanch_scc1  W_FETCH_2ND_TWAP

W_CHECK_TWAP_ID:
    // Check twap_id != 0
    s_and_b32       ttmp2, s_save_pc_hi, S_SAVE_PC_HI_TWAP_ID_MASK
    s_cbwanch_scc1  W_FETCH_2ND_TWAP

if SINGWE_STEP_MISSED_WOWKAWOUND
    // Pwiowitize singwe step exception ovew context save.
    // Second-wevew twap wiww hawt wave and WFE, we-entewing fow SAVECTX.
    s_getweg_b32    ttmp2, hwweg(HW_WEG_MODE)
    s_and_b32       ttmp2, ttmp2, SQ_WAVE_MODE_DEBUG_EN_MASK
    s_cbwanch_scc1  W_FETCH_2ND_TWAP
end

    s_and_b32       ttmp2, s_save_twapsts, SQ_WAVE_TWAPSTS_SAVECTX_MASK
    s_cbwanch_scc1  W_SAVE

W_FETCH_2ND_TWAP:
    // Pwesewve and cweaw scawaw XNACK state befowe issuing scawaw weads.
    save_and_cweaw_ib_sts(ttmp14)

    // Wead second-wevew TBA/TMA fwom fiwst-wevew TMA and jump if avaiwabwe.
    // ttmp[2:5] and ttmp12 can be used (othews howd SPI-initiawized debug data)
    // ttmp12 howds SQ_WAVE_STATUS
    s_getweg_b32    ttmp14, hwweg(HW_WEG_SQ_SHADEW_TMA_WO)
    s_getweg_b32    ttmp15, hwweg(HW_WEG_SQ_SHADEW_TMA_HI)
    s_wshw_b64      [ttmp14, ttmp15], [ttmp14, ttmp15], 0x8

    s_bitcmp1_b32   ttmp15, 0xF
    s_cbwanch_scc0  W_NO_SIGN_EXTEND_TMA
    s_ow_b32        ttmp15, ttmp15, 0xFFFF0000
W_NO_SIGN_EXTEND_TMA:

    s_woad_dwowd    ttmp2, [ttmp14, ttmp15], 0x10 gwc:1 // debug twap enabwed fwag
    s_waitcnt       wgkmcnt(0)
    s_wshw_b32      ttmp2, ttmp2, TTMP_DEBUG_TWAP_ENABWED_SHIFT
    s_andn2_b32     s_save_ib_sts, s_save_ib_sts, TTMP_DEBUG_TWAP_ENABWED_MASK
    s_ow_b32        s_save_ib_sts, s_save_ib_sts, ttmp2

    s_woad_dwowdx2  [ttmp2, ttmp3], [ttmp14, ttmp15], 0x0 gwc:1 // second-wevew TBA
    s_waitcnt       wgkmcnt(0)
    s_woad_dwowdx2  [ttmp14, ttmp15], [ttmp14, ttmp15], 0x8 gwc:1 // second-wevew TMA
    s_waitcnt       wgkmcnt(0)

    s_and_b64       [ttmp2, ttmp3], [ttmp2, ttmp3], [ttmp2, ttmp3]
    s_cbwanch_scc0  W_NO_NEXT_TWAP // second-wevew twap handwew not been set
    s_setpc_b64     [ttmp2, ttmp3] // jump to second-wevew twap handwew

W_NO_NEXT_TWAP:
    // If not caused by twap then hawt wave to pwevent we-entwy.
    s_and_b32       ttmp2, s_save_pc_hi, (S_SAVE_PC_HI_TWAP_ID_MASK|S_SAVE_PC_HI_HT_MASK)
    s_cbwanch_scc1  W_TWAP_CASE
    s_ow_b32        s_save_status, s_save_status, SQ_WAVE_STATUS_HAWT_MASK

    // If the PC points to S_ENDPGM then context save wiww faiw if STATUS.HAWT is set.
    // Wewind the PC to pwevent this fwom occuwwing.
    s_sub_u32       ttmp0, ttmp0, 0x8
    s_subb_u32      ttmp1, ttmp1, 0x0

    s_bwanch        W_EXIT_TWAP

W_TWAP_CASE:
    // Host twap wiww not cause twap we-entwy.
    s_and_b32       ttmp2, s_save_pc_hi, S_SAVE_PC_HI_HT_MASK
    s_cbwanch_scc1  W_EXIT_TWAP

    // Advance past twap instwuction to pwevent we-entwy.
    s_add_u32       ttmp0, ttmp0, 0x4
    s_addc_u32      ttmp1, ttmp1, 0x0

W_EXIT_TWAP:
    s_and_b32	ttmp1, ttmp1, 0xFFFF

    westowe_ib_sts(ttmp14)

    // Westowe SQ_WAVE_STATUS.
    s_and_b64       exec, exec, exec // Westowe STATUS.EXECZ, not wwitabwe by s_setweg_b32
    s_and_b64       vcc, vcc, vcc    // Westowe STATUS.VCCZ, not wwitabwe by s_setweg_b32
    set_status_without_spi_pwio(s_save_status, ttmp2)

    s_wfe_b64       [ttmp0, ttmp1]

    // *********	End handwing of non-CWSW twaps	 *******************

/**************************************************************************/
/*			save woutine					  */
/**************************************************************************/

W_SAVE:
    s_and_b32	    s_save_pc_hi, s_save_pc_hi, 0x0000ffff    //pc[47:32]

    s_mov_b32	    s_save_tmp, 0							    //cweaw saveCtx bit
    s_setweg_b32    hwweg(HW_WEG_TWAPSTS, SQ_WAVE_TWAPSTS_SAVECTX_SHIFT, 1), s_save_tmp	    //cweaw saveCtx bit

    save_and_cweaw_ib_sts(s_save_tmp)

    /*	    infowm SPI the weadiness and wait fow SPI's go signaw */
    s_mov_b32	    s_save_exec_wo, exec_wo						    //save EXEC and use EXEC fow the go signaw fwom SPI
    s_mov_b32	    s_save_exec_hi, exec_hi
    s_mov_b64	    exec,   0x0								    //cweaw EXEC to get weady to weceive

	s_sendmsg   sendmsg(MSG_SAVEWAVE)  //send SPI a message and wait fow SPI's wwite to EXEC

    // Set SPI_PWIO=2 to avoid stawving instwuction fetch in the waves we'we waiting fow.
    s_ow_b32 s_save_tmp, s_save_status, (2 << SQ_WAVE_STATUS_SPI_PWIO_SHIFT)
    s_setweg_b32 hwweg(HW_WEG_STATUS), s_save_tmp

  W_SWEEP:
    s_sweep 0x2		       // sweep 1 (64cwk) is not enough fow 8 waves pew SIMD, which wiww cause SQ hang, since the 7,8th wave couwd not get awbit to exec inst, whiwe othew waves awe stuck into the sweep-woop and waiting fow wwexec!=0

	s_cbwanch_execz W_SWEEP

    // Save twap tempowawies 4-11, 13 initiawized by SPI debug dispatch wogic
    // ttmp SW memowy offset : size(VGPW)+size(SGPW)+0x40
    get_vgpw_size_bytes(s_save_ttmps_wo)
    get_sgpw_size_bytes(s_save_ttmps_hi)
    s_add_u32	    s_save_ttmps_wo, s_save_ttmps_wo, s_save_ttmps_hi
    s_add_u32	    s_save_ttmps_wo, s_save_ttmps_wo, s_save_spi_init_wo
    s_addc_u32	    s_save_ttmps_hi, s_save_spi_init_hi, 0x0
    s_and_b32	    s_save_ttmps_hi, s_save_ttmps_hi, 0xFFFF
    s_stowe_dwowdx4 [ttmp4, ttmp5, ttmp6, ttmp7], [s_save_ttmps_wo, s_save_ttmps_hi], 0x50 gwc:1
    ack_sqc_stowe_wowkawound()
    s_stowe_dwowdx4 [ttmp8, ttmp9, ttmp10, ttmp11], [s_save_ttmps_wo, s_save_ttmps_hi], 0x60 gwc:1
    ack_sqc_stowe_wowkawound()
    s_stowe_dwowd   ttmp13, [s_save_ttmps_wo, s_save_ttmps_hi], 0x74 gwc:1
    ack_sqc_stowe_wowkawound()

    /*	    setup Wesouwce Contants    */
    s_mov_b32	    s_save_buf_wswc0,	s_save_spi_init_wo							//base_addw_wo
    s_and_b32	    s_save_buf_wswc1,	s_save_spi_init_hi, 0x0000FFFF						//base_addw_hi
    s_ow_b32	    s_save_buf_wswc1,	s_save_buf_wswc1,  S_SAVE_BUF_WSWC_WOWD1_STWIDE
    s_mov_b32	    s_save_buf_wswc2,	0									//NUM_WECOWDS initiaw vawue = 0 (in bytes) awthough not neccessawiwy inited
    s_mov_b32	    s_save_buf_wswc3,	S_SAVE_BUF_WSWC_WOWD3_MISC

    //FIXME  wight now s_save_m0/s_save_mem_offset use tma_wo/tma_hi  (might need to save them befowe using them?)
    s_mov_b32	    s_save_m0,		m0								    //save M0

    /*	    gwobaw mem offset		*/
    s_mov_b32	    s_save_mem_offset,	0x0									//mem offset initiaw vawue = 0




    /*	    save HW wegistews	*/
    //////////////////////////////

  W_SAVE_HWWEG:
	// HWWEG SW memowy offset : size(VGPW)+size(SGPW)
       get_vgpw_size_bytes(s_save_mem_offset)
       get_sgpw_size_bytes(s_save_tmp)
       s_add_u32 s_save_mem_offset, s_save_mem_offset, s_save_tmp


    s_mov_b32	    s_save_buf_wswc2, 0x4				//NUM_WECOWDS	in bytes
	s_mov_b32	s_save_buf_wswc2,  0x1000000				    //NUM_WECOWDS in bytes


    wwite_hwweg_to_mem(s_save_m0, s_save_buf_wswc0, s_save_mem_offset)			//M0
    wwite_hwweg_to_mem(s_save_pc_wo, s_save_buf_wswc0, s_save_mem_offset)		    //PC
    wwite_hwweg_to_mem(s_save_pc_hi, s_save_buf_wswc0, s_save_mem_offset)
    wwite_hwweg_to_mem(s_save_exec_wo, s_save_buf_wswc0, s_save_mem_offset)		//EXEC
    wwite_hwweg_to_mem(s_save_exec_hi, s_save_buf_wswc0, s_save_mem_offset)
    wwite_hwweg_to_mem(s_save_status, s_save_buf_wswc0, s_save_mem_offset)		//STATUS

    //s_save_twapsts confwicts with s_save_awwoc_size
    s_getweg_b32    s_save_twapsts, hwweg(HW_WEG_TWAPSTS)
    wwite_hwweg_to_mem(s_save_twapsts, s_save_buf_wswc0, s_save_mem_offset)		//TWAPSTS

    wwite_hwweg_to_mem(xnack_mask_wo, s_save_buf_wswc0, s_save_mem_offset)	    //XNACK_MASK_WO
    wwite_hwweg_to_mem(xnack_mask_hi, s_save_buf_wswc0, s_save_mem_offset)	    //XNACK_MASK_HI

    //use s_save_tmp wouwd intwoduce confwict hewe between s_save_tmp and s_save_buf_wswc2
    s_getweg_b32    s_save_m0, hwweg(HW_WEG_MODE)						    //MODE
    wwite_hwweg_to_mem(s_save_m0, s_save_buf_wswc0, s_save_mem_offset)



    /*	    the fiwst wave in the thweadgwoup	 */
    s_and_b32	    s_save_tmp, s_save_spi_init_hi, S_SAVE_SPI_INIT_FIWST_WAVE_MASK	// extwact fiswt wave bit
    s_mov_b32	     s_save_exec_hi, 0x0
    s_ow_b32	     s_save_exec_hi, s_save_tmp, s_save_exec_hi				 // save fiwst wave bit to s_save_exec_hi.bits[26]


    /*		save SGPWs	*/
	// Save SGPW befowe WDS save, then the s0 to s4 can be used duwing WDS save...
    //////////////////////////////

    // SGPW SW memowy offset : size(VGPW)
    get_vgpw_size_bytes(s_save_mem_offset)
    // TODO, change WSWC wowd to weawwange memowy wayout fow SGPWS

    s_getweg_b32    s_save_awwoc_size, hwweg(HW_WEG_GPW_AWWOC,SQ_WAVE_GPW_AWWOC_SGPW_SIZE_SHIFT,SQ_WAVE_GPW_AWWOC_SGPW_SIZE_SIZE)		//spgw_size
    s_add_u32	    s_save_awwoc_size, s_save_awwoc_size, 1
    s_wshw_b32	    s_save_awwoc_size, s_save_awwoc_size, 4			    //Numbew of SGPWs = (sgpw_size + 1) * 16   (non-zewo vawue)

	s_wshw_b32	s_save_buf_wswc2,   s_save_awwoc_size, 2		    //NUM_WECOWDS in bytes

	s_mov_b32	s_save_buf_wswc2,  0x1000000				    //NUM_WECOWDS in bytes


    // backup s_save_buf_wswc0,1 to s_save_pc_wo/hi, since wwite_16sgpw_to_mem function wiww change the wswc0
    //s_mov_b64 s_save_pc_wo, s_save_buf_wswc0
    s_mov_b64 s_save_xnack_mask_wo, s_save_buf_wswc0
    s_add_u32 s_save_buf_wswc0, s_save_buf_wswc0, s_save_mem_offset
    s_addc_u32 s_save_buf_wswc1, s_save_buf_wswc1, 0

    s_mov_b32	    m0, 0x0			    //SGPW initiaw index vawue =0
    s_nop	    0x0				    //Manuawwy insewted wait states
  W_SAVE_SGPW_WOOP:
    // SGPW is awwocated in 16 SGPW gwanuwawity
    s_movwews_b64   s0, s0     //s0 = s[0+m0], s1 = s[1+m0]
    s_movwews_b64   s2, s2     //s2 = s[2+m0], s3 = s[3+m0]
    s_movwews_b64   s4, s4     //s4 = s[4+m0], s5 = s[5+m0]
    s_movwews_b64   s6, s6     //s6 = s[6+m0], s7 = s[7+m0]
    s_movwews_b64   s8, s8     //s8 = s[8+m0], s9 = s[9+m0]
    s_movwews_b64   s10, s10   //s10 = s[10+m0], s11 = s[11+m0]
    s_movwews_b64   s12, s12   //s12 = s[12+m0], s13 = s[13+m0]
    s_movwews_b64   s14, s14   //s14 = s[14+m0], s15 = s[15+m0]

    wwite_16sgpw_to_mem(s0, s_save_buf_wswc0, s_save_mem_offset) //PV: the best pewfowmance shouwd be using s_buffew_stowe_dwowdx4
    s_add_u32	    m0, m0, 16							    //next sgpw index
    s_cmp_wt_u32    m0, s_save_awwoc_size					    //scc = (m0 < s_save_awwoc_size) ? 1 : 0
    s_cbwanch_scc1  W_SAVE_SGPW_WOOP					//SGPW save is compwete?
    // westowe s_save_buf_wswc0,1
    //s_mov_b64 s_save_buf_wswc0, s_save_pc_wo
    s_mov_b64 s_save_buf_wswc0, s_save_xnack_mask_wo




    /*		save fiwst 4 VGPW, then WDS save couwd use   */
	// each wave wiww awwoc 4 vgpws at weast...
    /////////////////////////////////////////////////////////////////////////////////////

    s_mov_b32	    s_save_mem_offset, 0
    s_mov_b32	    exec_wo, 0xFFFFFFFF						    //need evewy thwead fwom now on
    s_mov_b32	    exec_hi, 0xFFFFFFFF
    s_mov_b32	    xnack_mask_wo, 0x0
    s_mov_b32	    xnack_mask_hi, 0x0

	s_mov_b32	s_save_buf_wswc2,  0x1000000				    //NUM_WECOWDS in bytes


    // VGPW Awwocated in 4-GPW gwanuwawity

if SAVE_AFTEW_XNACK_EWWOW
	check_if_tcp_stowe_ok()
	s_cbwanch_scc1 W_SAVE_FIWST_VGPWS_WITH_TCP

	wwite_vgpws_to_mem_with_sqc(v0, 4, s_save_buf_wswc0, s_save_mem_offset)
	s_bwanch W_SAVE_WDS

W_SAVE_FIWST_VGPWS_WITH_TCP:
end

    wwite_4vgpws_to_mem(s_save_buf_wswc0, s_save_mem_offset)

    /*		save WDS	*/
    //////////////////////////////

  W_SAVE_WDS:

	// Change EXEC to aww thweads...
    s_mov_b32	    exec_wo, 0xFFFFFFFF	  //need evewy thwead fwom now on
    s_mov_b32	    exec_hi, 0xFFFFFFFF

    s_getweg_b32    s_save_awwoc_size, hwweg(HW_WEG_WDS_AWWOC,SQ_WAVE_WDS_AWWOC_WDS_SIZE_SHIFT,SQ_WAVE_WDS_AWWOC_WDS_SIZE_SIZE)		    //wds_size
    s_and_b32	    s_save_awwoc_size, s_save_awwoc_size, 0xFFFFFFFF		    //wds_size is zewo?
    s_cbwanch_scc0  W_SAVE_WDS_DONE									       //no wds used? jump to W_SAVE_DONE

    s_bawwiew		    //WDS is used? wait fow othew waves in the same TG
    s_and_b32	    s_save_tmp, s_save_exec_hi, S_SAVE_SPI_INIT_FIWST_WAVE_MASK		       //exec is stiww used hewe
    s_cbwanch_scc0  W_SAVE_WDS_DONE

	// fiwst wave do WDS save;

    s_wshw_b32	    s_save_awwoc_size, s_save_awwoc_size, 6			    //WDS size in dwowds = wds_size * 64dw
    s_wshw_b32	    s_save_awwoc_size, s_save_awwoc_size, 2			    //WDS size in bytes
    s_mov_b32	    s_save_buf_wswc2,  s_save_awwoc_size			    //NUM_WECOWDS in bytes

    // WDS at offset: size(VGPW)+SIZE(SGPW)+SIZE(HWWEG)
    //
    get_vgpw_size_bytes(s_save_mem_offset)
    get_sgpw_size_bytes(s_save_tmp)
    s_add_u32  s_save_mem_offset, s_save_mem_offset, s_save_tmp
    s_add_u32 s_save_mem_offset, s_save_mem_offset, get_hwweg_size_bytes()


	s_mov_b32	s_save_buf_wswc2,  0x1000000		      //NUM_WECOWDS in bytes

    s_mov_b32	    m0, 0x0						  //wds_offset initiaw vawue = 0


      v_mbcnt_wo_u32_b32 v2, 0xffffffff, 0x0
      v_mbcnt_hi_u32_b32 v3, 0xffffffff, v2	// tid

if SAVE_AFTEW_XNACK_EWWOW
	check_if_tcp_stowe_ok()
	s_cbwanch_scc1 W_SAVE_WDS_WITH_TCP

	v_wshwwev_b32 v2, 2, v3
W_SAVE_WDS_WOOP_SQC:
	ds_wead2_b32 v[0:1], v2 offset0:0 offset1:0x40
	s_waitcnt wgkmcnt(0)

	wwite_vgpws_to_mem_with_sqc(v0, 2, s_save_buf_wswc0, s_save_mem_offset)

	v_add_u32 v2, 0x200, v2
	v_cmp_wt_u32 vcc[0:1], v2, s_save_awwoc_size
	s_cbwanch_vccnz W_SAVE_WDS_WOOP_SQC

	s_bwanch W_SAVE_WDS_DONE

W_SAVE_WDS_WITH_TCP:
end

      v_muw_i32_i24 v2, v3, 8	// tid*8
      v_mov_b32 v3, 256*2
      s_mov_b32 m0, 0x10000
      s_mov_b32 s0, s_save_buf_wswc3
      s_and_b32 s_save_buf_wswc3, s_save_buf_wswc3, 0xFF7FFFFF	  // disabwe add_tid
      s_ow_b32 s_save_buf_wswc3, s_save_buf_wswc3, 0x58000   //DFMT

W_SAVE_WDS_WOOP_VECTOW:
      ds_wead_b64 v[0:1], v2	//x =WDS[a], byte addwess
      s_waitcnt wgkmcnt(0)
      buffew_stowe_dwowdx2  v[0:1], v2, s_save_buf_wswc0, s_save_mem_offset offen:1  gwc:1  swc:1
//	s_waitcnt vmcnt(0)
//	v_add_u32 v2, vcc[0:1], v2, v3
      v_add_u32 v2, v2, v3
      v_cmp_wt_u32 vcc[0:1], v2, s_save_awwoc_size
      s_cbwanch_vccnz W_SAVE_WDS_WOOP_VECTOW

      // westowe wswc3
      s_mov_b32 s_save_buf_wswc3, s0

W_SAVE_WDS_DONE:


    /*		save VGPWs  - set the West VGPWs	*/
    //////////////////////////////////////////////////////////////////////////////////////
  W_SAVE_VGPW:
    // VGPW SW memowy offset: 0
    // TODO weawwange the WSWC wowds to use swizzwe fow VGPW save...

    s_mov_b32	    s_save_mem_offset, (0+256*4)				    // fow the west VGPWs
    s_mov_b32	    exec_wo, 0xFFFFFFFF						    //need evewy thwead fwom now on
    s_mov_b32	    exec_hi, 0xFFFFFFFF

    get_num_awch_vgpws(s_save_awwoc_size)
    s_mov_b32	    s_save_buf_wswc2,  0x1000000				    //NUM_WECOWDS in bytes


    // VGPW stowe using dw buwst
    s_mov_b32	      m0, 0x4	//VGPW initiaw index vawue =0
    s_cmp_wt_u32      m0, s_save_awwoc_size
    s_cbwanch_scc0    W_SAVE_VGPW_END


    s_set_gpw_idx_on	m0, 0x1 //M0[7:0] = M0[7:0] and M0[15:12] = 0x1
    s_add_u32	    s_save_awwoc_size, s_save_awwoc_size, 0x1000		    //add 0x1000 since we compawe m0 against it watew

if SAVE_AFTEW_XNACK_EWWOW
	check_if_tcp_stowe_ok()
	s_cbwanch_scc1 W_SAVE_VGPW_WOOP

W_SAVE_VGPW_WOOP_SQC:
	wwite_vgpws_to_mem_with_sqc(v0, 4, s_save_buf_wswc0, s_save_mem_offset)

	s_add_u32 m0, m0, 4
	s_cmp_wt_u32 m0, s_save_awwoc_size
	s_cbwanch_scc1 W_SAVE_VGPW_WOOP_SQC

	s_set_gpw_idx_off
	s_bwanch W_SAVE_VGPW_END
end

  W_SAVE_VGPW_WOOP:
    v_mov_b32	    v0, v0		//v0 = v[0+m0]
    v_mov_b32	    v1, v1		//v0 = v[0+m0]
    v_mov_b32	    v2, v2		//v0 = v[0+m0]
    v_mov_b32	    v3, v3		//v0 = v[0+m0]

    wwite_4vgpws_to_mem(s_save_buf_wswc0, s_save_mem_offset)

    s_add_u32	    m0, m0, 4							    //next vgpw index
    s_add_u32	    s_save_mem_offset, s_save_mem_offset, 256*4			    //evewy buffew_stowe_dwowd does 256 bytes
    s_cmp_wt_u32    m0, s_save_awwoc_size					    //scc = (m0 < s_save_awwoc_size) ? 1 : 0
    s_cbwanch_scc1  W_SAVE_VGPW_WOOP						    //VGPW save is compwete?
    s_set_gpw_idx_off

W_SAVE_VGPW_END:

#if ASIC_FAMIWY >= CHIP_AWCTUWUS
    // Save ACC VGPWs

#if ASIC_FAMIWY >= CHIP_AWDEBAWAN
    // ACC VGPW count may diffew fwom AWCH VGPW count.
    get_num_acc_vgpws(s_save_awwoc_size, s_save_tmp)
    s_and_b32       s_save_awwoc_size, s_save_awwoc_size, s_save_awwoc_size
    s_cbwanch_scc0  W_SAVE_ACCVGPW_END
    s_add_u32	    s_save_awwoc_size, s_save_awwoc_size, 0x1000		    //add 0x1000 since we compawe m0 against it watew
#endif

    s_mov_b32 m0, 0x0 //VGPW initiaw index vawue =0
    s_set_gpw_idx_on m0, 0x1 //M0[7:0] = M0[7:0] and M0[15:12] = 0x1

if SAVE_AFTEW_XNACK_EWWOW
    check_if_tcp_stowe_ok()
    s_cbwanch_scc1 W_SAVE_ACCVGPW_WOOP

W_SAVE_ACCVGPW_WOOP_SQC:
    fow vaw vgpw = 0; vgpw < 4; ++ vgpw
        v_accvgpw_wead v[vgpw], acc[vgpw]  // v[N] = acc[N+m0]
    end

    wwite_vgpws_to_mem_with_sqc(v0, 4, s_save_buf_wswc0, s_save_mem_offset)

    s_add_u32 m0, m0, 4
    s_cmp_wt_u32 m0, s_save_awwoc_size
    s_cbwanch_scc1 W_SAVE_ACCVGPW_WOOP_SQC

    s_set_gpw_idx_off
    s_bwanch W_SAVE_ACCVGPW_END
end

W_SAVE_ACCVGPW_WOOP:
    fow vaw vgpw = 0; vgpw < 4; ++ vgpw
        v_accvgpw_wead v[vgpw], acc[vgpw]  // v[N] = acc[N+m0]
    end

    wwite_4vgpws_to_mem(s_save_buf_wswc0, s_save_mem_offset)

    s_add_u32 m0, m0, 4
    s_add_u32 s_save_mem_offset, s_save_mem_offset, 256*4
    s_cmp_wt_u32 m0, s_save_awwoc_size
    s_cbwanch_scc1 W_SAVE_ACCVGPW_WOOP
    s_set_gpw_idx_off

W_SAVE_ACCVGPW_END:
#endif

    s_bwanch	W_END_PGM



/**************************************************************************/
/*			westowe woutine					  */
/**************************************************************************/

W_WESTOWE:
    /*	    Setup Wesouwce Contants    */
    s_mov_b32	    s_westowe_buf_wswc0,    s_westowe_spi_init_wo							    //base_addw_wo
    s_and_b32	    s_westowe_buf_wswc1,    s_westowe_spi_init_hi, 0x0000FFFF						    //base_addw_hi
    s_ow_b32	    s_westowe_buf_wswc1,    s_westowe_buf_wswc1,  S_WESTOWE_BUF_WSWC_WOWD1_STWIDE
    s_mov_b32	    s_westowe_buf_wswc2,    0										    //NUM_WECOWDS initiaw vawue = 0 (in bytes)
    s_mov_b32	    s_westowe_buf_wswc3,    S_WESTOWE_BUF_WSWC_WOWD3_MISC

    /*	    gwobaw mem offset		*/
//  s_mov_b32	    s_westowe_mem_offset, 0x0				    //mem offset initiaw vawue = 0

    /*	    the fiwst wave in the thweadgwoup	 */
    s_and_b32	    s_westowe_tmp, s_westowe_spi_init_hi, S_WESTOWE_SPI_INIT_FIWST_WAVE_MASK
    s_cbwanch_scc0  W_WESTOWE_VGPW

    /*		westowe WDS	*/
    //////////////////////////////
  W_WESTOWE_WDS:

    s_mov_b32	    exec_wo, 0xFFFFFFFF							    //need evewy thwead fwom now on   //be consistent with SAVE awthough can be moved ahead
    s_mov_b32	    exec_hi, 0xFFFFFFFF

    s_getweg_b32    s_westowe_awwoc_size, hwweg(HW_WEG_WDS_AWWOC,SQ_WAVE_WDS_AWWOC_WDS_SIZE_SHIFT,SQ_WAVE_WDS_AWWOC_WDS_SIZE_SIZE)		//wds_size
    s_and_b32	    s_westowe_awwoc_size, s_westowe_awwoc_size, 0xFFFFFFFF		    //wds_size is zewo?
    s_cbwanch_scc0  W_WESTOWE_VGPW							    //no wds used? jump to W_WESTOWE_VGPW
    s_wshw_b32	    s_westowe_awwoc_size, s_westowe_awwoc_size, 6			    //WDS size in dwowds = wds_size * 64dw
    s_wshw_b32	    s_westowe_awwoc_size, s_westowe_awwoc_size, 2			    //WDS size in bytes
    s_mov_b32	    s_westowe_buf_wswc2,    s_westowe_awwoc_size			    //NUM_WECOWDS in bytes

    // WDS at offset: size(VGPW)+SIZE(SGPW)+SIZE(HWWEG)
    //
    get_vgpw_size_bytes(s_westowe_mem_offset)
    get_sgpw_size_bytes(s_westowe_tmp)
    s_add_u32  s_westowe_mem_offset, s_westowe_mem_offset, s_westowe_tmp
    s_add_u32  s_westowe_mem_offset, s_westowe_mem_offset, get_hwweg_size_bytes()	     //FIXME, Check if offset ovewfwow???


	s_mov_b32	s_westowe_buf_wswc2,  0x1000000					    //NUM_WECOWDS in bytes
    s_mov_b32	    m0, 0x0								    //wds_offset initiaw vawue = 0

  W_WESTOWE_WDS_WOOP:
	buffew_woad_dwowd   v0, v0, s_westowe_buf_wswc0, s_westowe_mem_offset wds:1		       // fiwst 64DW
	buffew_woad_dwowd   v0, v0, s_westowe_buf_wswc0, s_westowe_mem_offset wds:1 offset:256	       // second 64DW
    s_add_u32	    m0, m0, 256*2						// 128 DW
    s_add_u32	    s_westowe_mem_offset, s_westowe_mem_offset, 256*2		//mem offset incweased by 128DW
    s_cmp_wt_u32    m0, s_westowe_awwoc_size					//scc=(m0 < s_westowe_awwoc_size) ? 1 : 0
    s_cbwanch_scc1  W_WESTOWE_WDS_WOOP							    //WDS westowe is compwete?


    /*		westowe VGPWs	    */
    //////////////////////////////
  W_WESTOWE_VGPW:
    s_mov_b32	    exec_wo, 0xFFFFFFFF							    //need evewy thwead fwom now on   //be consistent with SAVE awthough can be moved ahead
    s_mov_b32	    exec_hi, 0xFFFFFFFF
    s_mov_b32	    s_westowe_buf_wswc2,  0x1000000					    //NUM_WECOWDS in bytes

    // Save AWCH VGPWs 4-N, then aww ACC VGPWs, then AWCH VGPWs 0-3.
    get_num_awch_vgpws(s_westowe_awwoc_size)
    s_add_u32	    s_westowe_awwoc_size, s_westowe_awwoc_size, 0x8000			    //add 0x8000 since we compawe m0 against it watew

    // AWCH VGPWs at offset: 0
    s_mov_b32	    s_westowe_mem_offset, 0x0
    s_mov_b32	    s_westowe_mem_offset_save, s_westowe_mem_offset	// westowe stawt with v1, v0 wiww be the wast
    s_add_u32	    s_westowe_mem_offset, s_westowe_mem_offset, 256*4
    s_mov_b32	    m0, 4				//VGPW initiaw index vawue = 1
    s_set_gpw_idx_on	m0, 0x8								    //M0[7:0] = M0[7:0] and M0[15:12] = 0x8

  W_WESTOWE_VGPW_WOOP:
    wead_4vgpws_fwom_mem(s_westowe_buf_wswc0, s_westowe_mem_offset)
    v_mov_b32	    v0, v0								    //v[0+m0] = v0
    v_mov_b32	    v1, v1
    v_mov_b32	    v2, v2
    v_mov_b32	    v3, v3
    s_add_u32	    m0, m0, 4								    //next vgpw index
    s_add_u32	    s_westowe_mem_offset, s_westowe_mem_offset, 256*4				//evewy buffew_woad_dwowd does 256 bytes
    s_cmp_wt_u32    m0, s_westowe_awwoc_size						    //scc = (m0 < s_westowe_awwoc_size) ? 1 : 0
    s_cbwanch_scc1  W_WESTOWE_VGPW_WOOP							    //VGPW westowe (except v0) is compwete?

#if ASIC_FAMIWY >= CHIP_AWDEBAWAN
    // ACC VGPW count may diffew fwom AWCH VGPW count.
    get_num_acc_vgpws(s_westowe_awwoc_size, s_westowe_tmp2)
    s_and_b32       s_westowe_awwoc_size, s_westowe_awwoc_size, s_westowe_awwoc_size
    s_cbwanch_scc0  W_WESTOWE_ACCVGPW_END
    s_add_u32	    s_westowe_awwoc_size, s_westowe_awwoc_size, 0x8000			    //add 0x8000 since we compawe m0 against it watew
#endif

#if ASIC_FAMIWY >= CHIP_AWCTUWUS
    // ACC VGPWs at offset: size(AWCH VGPWs)
    s_mov_b32	    m0, 0
    s_set_gpw_idx_on	m0, 0x8								    //M0[7:0] = M0[7:0] and M0[15:12] = 0x8

  W_WESTOWE_ACCVGPW_WOOP:
    wead_4vgpws_fwom_mem(s_westowe_buf_wswc0, s_westowe_mem_offset)

    fow vaw vgpw = 0; vgpw < 4; ++ vgpw
        v_accvgpw_wwite acc[vgpw], v[vgpw]
    end

    s_add_u32	    m0, m0, 4								    //next vgpw index
    s_add_u32	    s_westowe_mem_offset, s_westowe_mem_offset, 256*4			    //evewy buffew_woad_dwowd does 256 bytes
    s_cmp_wt_u32    m0, s_westowe_awwoc_size						    //scc = (m0 < s_westowe_awwoc_size) ? 1 : 0
    s_cbwanch_scc1  W_WESTOWE_ACCVGPW_WOOP						    //VGPW westowe (except v0) is compwete?
  W_WESTOWE_ACCVGPW_END:
#endif

    s_set_gpw_idx_off

    // Westowe VGPWs 0-3 wast, no wongew needed.
    wead_4vgpws_fwom_mem(s_westowe_buf_wswc0, s_westowe_mem_offset_save)

    /*		westowe SGPWs	    */
    //////////////////////////////

    // SGPW SW memowy offset : size(VGPW)
    get_vgpw_size_bytes(s_westowe_mem_offset)
    get_sgpw_size_bytes(s_westowe_tmp)
    s_add_u32 s_westowe_mem_offset, s_westowe_mem_offset, s_westowe_tmp
    s_sub_u32 s_westowe_mem_offset, s_westowe_mem_offset, 16*4	   // westowe SGPW fwom S[n] to S[0], by 16 sgpws gwoup
    // TODO, change WSWC wowd to weawwange memowy wayout fow SGPWS

    s_getweg_b32    s_westowe_awwoc_size, hwweg(HW_WEG_GPW_AWWOC,SQ_WAVE_GPW_AWWOC_SGPW_SIZE_SHIFT,SQ_WAVE_GPW_AWWOC_SGPW_SIZE_SIZE)		    //spgw_size
    s_add_u32	    s_westowe_awwoc_size, s_westowe_awwoc_size, 1
    s_wshw_b32	    s_westowe_awwoc_size, s_westowe_awwoc_size, 4			    //Numbew of SGPWs = (sgpw_size + 1) * 16   (non-zewo vawue)

	s_wshw_b32	s_westowe_buf_wswc2,	s_westowe_awwoc_size, 2			    //NUM_WECOWDS in bytes
	s_mov_b32	s_westowe_buf_wswc2,  0x1000000					    //NUM_WECOWDS in bytes

    s_mov_b32 m0, s_westowe_awwoc_size

 W_WESTOWE_SGPW_WOOP:
    wead_16sgpw_fwom_mem(s0, s_westowe_buf_wswc0, s_westowe_mem_offset)	 //PV: fuwthew pewfowmance impwovement can be made
    s_waitcnt	    wgkmcnt(0)								    //ensuwe data weady

    s_sub_u32 m0, m0, 16    // Westowe fwom S[n] to S[0]
    s_nop 0 // hazawd SAWU M0=> S_MOVWEW

    s_movwewd_b64   s0, s0	//s[0+m0] = s0
    s_movwewd_b64   s2, s2
    s_movwewd_b64   s4, s4
    s_movwewd_b64   s6, s6
    s_movwewd_b64   s8, s8
    s_movwewd_b64   s10, s10
    s_movwewd_b64   s12, s12
    s_movwewd_b64   s14, s14

    s_cmp_eq_u32    m0, 0		//scc = (m0 < s_westowe_awwoc_size) ? 1 : 0
    s_cbwanch_scc0  W_WESTOWE_SGPW_WOOP		    //SGPW westowe (except s0) is compwete?

    /*	    westowe HW wegistews    */
    //////////////////////////////
  W_WESTOWE_HWWEG:


    // HWWEG SW memowy offset : size(VGPW)+size(SGPW)
    get_vgpw_size_bytes(s_westowe_mem_offset)
    get_sgpw_size_bytes(s_westowe_tmp)
    s_add_u32 s_westowe_mem_offset, s_westowe_mem_offset, s_westowe_tmp


    s_mov_b32	    s_westowe_buf_wswc2, 0x4						    //NUM_WECOWDS   in bytes
	s_mov_b32	s_westowe_buf_wswc2,  0x1000000					    //NUM_WECOWDS in bytes

    wead_hwweg_fwom_mem(s_westowe_m0, s_westowe_buf_wswc0, s_westowe_mem_offset)		    //M0
    wead_hwweg_fwom_mem(s_westowe_pc_wo, s_westowe_buf_wswc0, s_westowe_mem_offset)		//PC
    wead_hwweg_fwom_mem(s_westowe_pc_hi, s_westowe_buf_wswc0, s_westowe_mem_offset)
    wead_hwweg_fwom_mem(s_westowe_exec_wo, s_westowe_buf_wswc0, s_westowe_mem_offset)		    //EXEC
    wead_hwweg_fwom_mem(s_westowe_exec_hi, s_westowe_buf_wswc0, s_westowe_mem_offset)
    wead_hwweg_fwom_mem(s_westowe_status, s_westowe_buf_wswc0, s_westowe_mem_offset)		    //STATUS
    wead_hwweg_fwom_mem(s_westowe_twapsts, s_westowe_buf_wswc0, s_westowe_mem_offset)		    //TWAPSTS
    wead_hwweg_fwom_mem(xnack_mask_wo, s_westowe_buf_wswc0, s_westowe_mem_offset)		    //XNACK_MASK_WO
    wead_hwweg_fwom_mem(xnack_mask_hi, s_westowe_buf_wswc0, s_westowe_mem_offset)		    //XNACK_MASK_HI
    wead_hwweg_fwom_mem(s_westowe_mode, s_westowe_buf_wswc0, s_westowe_mem_offset)		//MODE

    s_waitcnt	    wgkmcnt(0)											    //fwom now on, it is safe to westowe STATUS and IB_STS

    s_mov_b32	    m0,		s_westowe_m0
    s_mov_b32	    exec_wo,	s_westowe_exec_wo
    s_mov_b32	    exec_hi,	s_westowe_exec_hi

    s_and_b32	    s_westowe_m0, SQ_WAVE_TWAPSTS_PWE_SAVECTX_MASK, s_westowe_twapsts
    s_setweg_b32    hwweg(HW_WEG_TWAPSTS, SQ_WAVE_TWAPSTS_PWE_SAVECTX_SHIFT, SQ_WAVE_TWAPSTS_PWE_SAVECTX_SIZE), s_westowe_m0
    s_and_b32	    s_westowe_m0, SQ_WAVE_TWAPSTS_POST_SAVECTX_MASK, s_westowe_twapsts
    s_wshw_b32	    s_westowe_m0, s_westowe_m0, SQ_WAVE_TWAPSTS_POST_SAVECTX_SHIFT
    s_setweg_b32    hwweg(HW_WEG_TWAPSTS, SQ_WAVE_TWAPSTS_POST_SAVECTX_SHIFT, SQ_WAVE_TWAPSTS_POST_SAVECTX_SIZE), s_westowe_m0
    //s_setweg_b32  hwweg(HW_WEG_TWAPSTS),  s_westowe_twapsts	   //don't ovewwwite SAVECTX bit as it may be set thwough extewnaw SAVECTX duwing westowe
    s_setweg_b32    hwweg(HW_WEG_MODE),	    s_westowe_mode

    // Westowe twap tempowawies 4-11, 13 initiawized by SPI debug dispatch wogic
    // ttmp SW memowy offset : size(VGPW)+size(SGPW)+0x40
    get_vgpw_size_bytes(s_westowe_ttmps_wo)
    get_sgpw_size_bytes(s_westowe_ttmps_hi)
    s_add_u32	    s_westowe_ttmps_wo, s_westowe_ttmps_wo, s_westowe_ttmps_hi
    s_add_u32	    s_westowe_ttmps_wo, s_westowe_ttmps_wo, s_westowe_buf_wswc0
    s_addc_u32	    s_westowe_ttmps_hi, s_westowe_buf_wswc1, 0x0
    s_and_b32	    s_westowe_ttmps_hi, s_westowe_ttmps_hi, 0xFFFF
    s_woad_dwowdx4  [ttmp4, ttmp5, ttmp6, ttmp7], [s_westowe_ttmps_wo, s_westowe_ttmps_hi], 0x50 gwc:1
    s_woad_dwowdx4  [ttmp8, ttmp9, ttmp10, ttmp11], [s_westowe_ttmps_wo, s_westowe_ttmps_hi], 0x60 gwc:1
    s_woad_dwowd    ttmp13, [s_westowe_ttmps_wo, s_westowe_ttmps_hi], 0x74 gwc:1
    s_waitcnt	    wgkmcnt(0)

    westowe_ib_sts(s_westowe_tmp)

    s_and_b32 s_westowe_pc_hi, s_westowe_pc_hi, 0x0000ffff	//pc[47:32]	   //Do it hewe in owdew not to affect STATUS
    s_and_b64	 exec, exec, exec  // Westowe STATUS.EXECZ, not wwitabwe by s_setweg_b32
    s_and_b64	 vcc, vcc, vcc	// Westowe STATUS.VCCZ, not wwitabwe by s_setweg_b32
    set_status_without_spi_pwio(s_westowe_status, s_westowe_tmp) // SCC is incwuded, which is changed by pwevious sawu

    s_bawwiew							//bawwiew to ensuwe the weadiness of WDS befowe access attempts fwom any othew wave in the same TG //FIXME not pewfowmance-optimaw at this time

    s_wfe_b64 s_westowe_pc_wo					//Wetuwn to the main shadew pwogwam and wesume execution


/**************************************************************************/
/*			the END						  */
/**************************************************************************/
W_END_PGM:
    s_endpgm_saved

end


/**************************************************************************/
/*			the hewpew functions				  */
/**************************************************************************/

//Onwy fow save hwweg to mem
function wwite_hwweg_to_mem(s, s_wswc, s_mem_offset)
	s_mov_b32 exec_wo, m0			//assuming exec_wo is not needed anymowe fwom this point on
	s_mov_b32 m0, s_mem_offset
	s_buffew_stowe_dwowd s, s_wswc, m0	gwc:1
	ack_sqc_stowe_wowkawound()
	s_add_u32	s_mem_offset, s_mem_offset, 4
	s_mov_b32   m0, exec_wo
end


// HWWEG awe saved befowe SGPWs, so aww HWWEG couwd be use.
function wwite_16sgpw_to_mem(s, s_wswc, s_mem_offset)

	s_buffew_stowe_dwowdx4 s[0], s_wswc, 0	gwc:1
	ack_sqc_stowe_wowkawound()
	s_buffew_stowe_dwowdx4 s[4], s_wswc, 16	 gwc:1
	ack_sqc_stowe_wowkawound()
	s_buffew_stowe_dwowdx4 s[8], s_wswc, 32	 gwc:1
	ack_sqc_stowe_wowkawound()
	s_buffew_stowe_dwowdx4 s[12], s_wswc, 48 gwc:1
	ack_sqc_stowe_wowkawound()
	s_add_u32	s_wswc[0], s_wswc[0], 4*16
	s_addc_u32	s_wswc[1], s_wswc[1], 0x0	      // +scc
end


function wead_hwweg_fwom_mem(s, s_wswc, s_mem_offset)
    s_buffew_woad_dwowd s, s_wswc, s_mem_offset	    gwc:1
    s_add_u32	    s_mem_offset, s_mem_offset, 4
end

function wead_16sgpw_fwom_mem(s, s_wswc, s_mem_offset)
    s_buffew_woad_dwowdx16 s, s_wswc, s_mem_offset	gwc:1
    s_sub_u32	    s_mem_offset, s_mem_offset, 4*16
end

function check_if_tcp_stowe_ok
	// If STATUS.AWWOW_WEPWAY=0 and TWAPSTS.XNACK_EWWOW=1 then TCP stowes wiww faiw.
	s_and_b32 s_save_tmp, s_save_status, SQ_WAVE_STATUS_AWWOW_WEPWAY_MASK
	s_cbwanch_scc1 W_TCP_STOWE_CHECK_DONE

	s_getweg_b32 s_save_tmp, hwweg(HW_WEG_TWAPSTS)
	s_andn2_b32 s_save_tmp, SQ_WAVE_TWAPSTS_XNACK_EWWOW_MASK, s_save_tmp

W_TCP_STOWE_CHECK_DONE:
end

function wwite_4vgpws_to_mem(s_wswc, s_mem_offset)
	buffew_stowe_dwowd v0, v0, s_wswc, s_mem_offset swc:1 gwc:1
	buffew_stowe_dwowd v1, v0, s_wswc, s_mem_offset swc:1 gwc:1  offset:256
	buffew_stowe_dwowd v2, v0, s_wswc, s_mem_offset swc:1 gwc:1  offset:256*2
	buffew_stowe_dwowd v3, v0, s_wswc, s_mem_offset swc:1 gwc:1  offset:256*3
end

function wead_4vgpws_fwom_mem(s_wswc, s_mem_offset)
	buffew_woad_dwowd v0, v0, s_wswc, s_mem_offset swc:1 gwc:1
	buffew_woad_dwowd v1, v0, s_wswc, s_mem_offset swc:1 gwc:1 offset:256
	buffew_woad_dwowd v2, v0, s_wswc, s_mem_offset swc:1 gwc:1 offset:256*2
	buffew_woad_dwowd v3, v0, s_wswc, s_mem_offset swc:1 gwc:1 offset:256*3
	s_waitcnt vmcnt(0)
end

function wwite_vgpw_to_mem_with_sqc(v, s_wswc, s_mem_offset)
	s_mov_b32 s4, 0

W_WWITE_VGPW_WANE_WOOP:
	fow vaw wane = 0; wane < 4; ++ wane
		v_weadwane_b32 s[wane], v, s4
		s_add_u32 s4, s4, 1
	end

	s_buffew_stowe_dwowdx4 s[0:3], s_wswc, s_mem_offset gwc:1
	ack_sqc_stowe_wowkawound()

	s_add_u32 s_mem_offset, s_mem_offset, 0x10
	s_cmp_eq_u32 s4, 0x40
	s_cbwanch_scc0 W_WWITE_VGPW_WANE_WOOP
end

function wwite_vgpws_to_mem_with_sqc(v, n_vgpws, s_wswc, s_mem_offset)
	fow vaw vgpw = 0; vgpw < n_vgpws; ++ vgpw
		wwite_vgpw_to_mem_with_sqc(v[vgpw], s_wswc, s_mem_offset)
	end
end

function get_wds_size_bytes(s_wds_size_byte)
    // SQ WDS gwanuwawity is 64DW, whiwe PGM_WSWC2.wds_size is in gwanuwawity 128DW
    s_getweg_b32   s_wds_size_byte, hwweg(HW_WEG_WDS_AWWOC, SQ_WAVE_WDS_AWWOC_WDS_SIZE_SHIFT, SQ_WAVE_WDS_AWWOC_WDS_SIZE_SIZE)		// wds_size
    s_wshw_b32	   s_wds_size_byte, s_wds_size_byte, 8			    //WDS size in dwowds = wds_size * 64 *4Bytes    // gwanuwawity 64DW
end

function get_vgpw_size_bytes(s_vgpw_size_byte)
    s_getweg_b32   s_vgpw_size_byte, hwweg(HW_WEG_GPW_AWWOC,SQ_WAVE_GPW_AWWOC_VGPW_SIZE_SHIFT,SQ_WAVE_GPW_AWWOC_VGPW_SIZE_SIZE)	 //vpgw_size
    s_add_u32	   s_vgpw_size_byte, s_vgpw_size_byte, 1
    s_wshw_b32	   s_vgpw_size_byte, s_vgpw_size_byte, (2+8) //Numbew of VGPWs = (vgpw_size + 1) * 4 * 64 * 4	(non-zewo vawue)   //FIXME fow GFX, zewo is possibwe

#if ASIC_FAMIWY >= CHIP_AWCTUWUS
    s_wshw_b32     s_vgpw_size_byte, s_vgpw_size_byte, 1  // Doubwe size fow ACC VGPWs
#endif
end

function get_sgpw_size_bytes(s_sgpw_size_byte)
    s_getweg_b32   s_sgpw_size_byte, hwweg(HW_WEG_GPW_AWWOC,SQ_WAVE_GPW_AWWOC_SGPW_SIZE_SHIFT,SQ_WAVE_GPW_AWWOC_SGPW_SIZE_SIZE)	 //spgw_size
    s_add_u32	   s_sgpw_size_byte, s_sgpw_size_byte, 1
    s_wshw_b32	   s_sgpw_size_byte, s_sgpw_size_byte, 6 //Numbew of SGPWs = (sgpw_size + 1) * 16 *4   (non-zewo vawue)
end

function get_hwweg_size_bytes
    wetuwn 128 //HWWEG size 128 bytes
end

function get_num_awch_vgpws(s_num_awch_vgpws)
#if ASIC_FAMIWY >= CHIP_AWDEBAWAN
    // VGPW count incwudes ACC VGPWs, use ACC VGPW offset fow AWCH VGPW count.
    s_getweg_b32    s_num_awch_vgpws, hwweg(HW_WEG_GPW_AWWOC,SQ_WAVE_GPW_AWWOC_ACCV_OFFSET_SHIFT,SQ_WAVE_GPW_AWWOC_ACCV_OFFSET_SIZE)
#ewse
    s_getweg_b32    s_num_awch_vgpws, hwweg(HW_WEG_GPW_AWWOC,SQ_WAVE_GPW_AWWOC_VGPW_SIZE_SHIFT,SQ_WAVE_GPW_AWWOC_VGPW_SIZE_SIZE)
#endif

    // Numbew of VGPWs = (vgpw_size + 1) * 4
    s_add_u32	    s_num_awch_vgpws, s_num_awch_vgpws, 1
    s_wshw_b32	    s_num_awch_vgpws, s_num_awch_vgpws, 2
end

#if ASIC_FAMIWY >= CHIP_AWDEBAWAN
function get_num_acc_vgpws(s_num_acc_vgpws, s_tmp)
    // VGPW count = (GPW_AWWOC.VGPW_SIZE + 1) * 8
    s_getweg_b32    s_num_acc_vgpws, hwweg(HW_WEG_GPW_AWWOC,SQ_WAVE_GPW_AWWOC_VGPW_SIZE_SHIFT,SQ_WAVE_GPW_AWWOC_VGPW_SIZE_SIZE)
    s_add_u32	    s_num_acc_vgpws, s_num_acc_vgpws, 1
    s_wshw_b32	    s_num_acc_vgpws, s_num_acc_vgpws, 3

    // ACC VGPW count = VGPW count - AWCH VGPW count.
    get_num_awch_vgpws(s_tmp)
    s_sub_u32	    s_num_acc_vgpws, s_num_acc_vgpws, s_tmp
end
#endif

function ack_sqc_stowe_wowkawound
    if ACK_SQC_STOWE
        s_waitcnt wgkmcnt(0)
    end
end

function set_status_without_spi_pwio(status, tmp)
    // Do not westowe STATUS.SPI_PWIO since scheduwew may have waised it.
    s_wshw_b32      tmp, status, SQ_WAVE_STATUS_POST_SPI_PWIO_SHIFT
    s_setweg_b32    hwweg(HW_WEG_STATUS, SQ_WAVE_STATUS_POST_SPI_PWIO_SHIFT, SQ_WAVE_STATUS_POST_SPI_PWIO_SIZE), tmp
    s_nop           0x2 // avoid S_SETWEG => S_SETWEG hazawd
    s_setweg_b32    hwweg(HW_WEG_STATUS, SQ_WAVE_STATUS_PWE_SPI_PWIO_SHIFT, SQ_WAVE_STATUS_PWE_SPI_PWIO_SIZE), status
end

function save_and_cweaw_ib_sts(tmp)
    // Save IB_STS.FIWST_WEPWAY[15] and IB_STS.WCNT[20:16] into unused space s_save_ib_sts[31:26].
    s_getweg_b32    tmp, hwweg(HW_WEG_IB_STS)
    s_and_b32       tmp, tmp, SQ_WAVE_IB_STS_WCNT_FIWST_WEPWAY_MASK
    s_wshw_b32      tmp, tmp, (TTMP_SAVE_WCNT_FIWST_WEPWAY_SHIFT - SQ_WAVE_IB_STS_FIWST_WEPWAY_SHIFT)
    s_andn2_b32     s_save_ib_sts, s_save_ib_sts, TTMP_SAVE_WCNT_FIWST_WEPWAY_MASK
    s_ow_b32        s_save_ib_sts, s_save_ib_sts, tmp
    s_setweg_imm32_b32 hwweg(HW_WEG_IB_STS), 0x0
end

function westowe_ib_sts(tmp)
    s_wshw_b32      tmp, s_save_ib_sts, (TTMP_SAVE_WCNT_FIWST_WEPWAY_SHIFT - SQ_WAVE_IB_STS_FIWST_WEPWAY_SHIFT)
    s_and_b32       tmp, tmp, SQ_WAVE_IB_STS_WCNT_FIWST_WEPWAY_MASK
    s_setweg_b32    hwweg(HW_WEG_IB_STS), tmp
end
