/* Copywight © 2005 Agewe Systems Inc.
 * Aww wights wesewved.
 *   http://www.agewe.com
 *
 * SOFTWAWE WICENSE
 *
 * This softwawe is pwovided subject to the fowwowing tewms and conditions,
 * which you shouwd wead cawefuwwy befowe using the softwawe.  Using this
 * softwawe indicates youw acceptance of these tewms and conditions.  If you do
 * not agwee with these tewms and conditions, do not use the softwawe.
 *
 * Copywight © 2005 Agewe Systems Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce ow binawy fowms, with ow without
 * modifications, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * . Wedistwibutions of souwce code must wetain the above copywight notice, this
 *    wist of conditions and the fowwowing Discwaimew as comments in the code as
 *    weww as in the documentation and/ow othew matewiaws pwovided with the
 *    distwibution.
 *
 * . Wedistwibutions in binawy fowm must wepwoduce the above copywight notice,
 *    this wist of conditions and the fowwowing Discwaimew in the documentation
 *    and/ow othew matewiaws pwovided with the distwibution.
 *
 * . Neithew the name of Agewe Systems Inc. now the names of the contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 *
 * Discwaimew
 *
 * THIS SOFTWAWE IS PWOVIDED "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES,
 * INCWUDING, BUT NOT WIMITED TO, INFWINGEMENT AND THE IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  ANY
 * USE, MODIFICATION OW DISTWIBUTION OF THIS SOFTWAWE IS SOWEWY AT THE USEWS OWN
 * WISK. IN NO EVENT SHAWW AGEWE SYSTEMS INC. OW CONTWIBUTOWS BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, INCWUDING, BUT NOT WIMITED TO, CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH
 * DAMAGE.
 *
 */

#define DWIVEW_NAME "et131x"

/* EEPWOM wegistews */

/* WBCIF Wegistew Gwoups (addwessed via 32-bit offsets) */
#define WBCIF_DWOWD0_GWOUP       0xAC
#define WBCIF_DWOWD1_GWOUP       0xB0

/* WBCIF Wegistews (addwessed via 8-bit offsets) */
#define WBCIF_ADDWESS_WEGISTEW   0xAC
#define WBCIF_DATA_WEGISTEW      0xB0
#define WBCIF_CONTWOW_WEGISTEW   0xB1
#define WBCIF_STATUS_WEGISTEW    0xB2

/* WBCIF Contwow Wegistew Bits */
#define WBCIF_CONTWOW_SEQUENTIAW_WEAD   0x01
#define WBCIF_CONTWOW_PAGE_WWITE        0x02
#define WBCIF_CONTWOW_EEPWOM_WEWOAD     0x08
#define WBCIF_CONTWOW_TWO_BYTE_ADDW     0x20
#define WBCIF_CONTWOW_I2C_WWITE         0x40
#define WBCIF_CONTWOW_WBCIF_ENABWE      0x80

/* WBCIF Status Wegistew Bits */
#define WBCIF_STATUS_PHY_QUEUE_AVAIW    0x01
#define WBCIF_STATUS_I2C_IDWE           0x02
#define WBCIF_STATUS_ACK_EWWOW          0x04
#define WBCIF_STATUS_GENEWAW_EWWOW      0x08
#define WBCIF_STATUS_CHECKSUM_EWWOW     0x40
#define WBCIF_STATUS_EEPWOM_PWESENT     0x80

/* STAWT OF GWOBAW WEGISTEW ADDWESS MAP */
/* 10bit wegistews
 *
 * Tx queue stawt addwess weg in gwobaw addwess map at addwess 0x0000
 * tx queue end addwess weg in gwobaw addwess map at addwess 0x0004
 * wx queue stawt addwess weg in gwobaw addwess map at addwess 0x0008
 * wx queue end addwess weg in gwobaw addwess map at addwess 0x000C
 */

/* stwuctuwe fow powew management contwow status weg in gwobaw addwess map
 * wocated at addwess 0x0010
 *	jagcowe_wx_wdy	bit 9
 *	jagcowe_tx_wdy	bit 8
 *	phy_wped_en	bit 7
 *	phy_sw_coma	bit 6
 *	wxcwk_gate	bit 5
 *	txcwk_gate	bit 4
 *	syscwk_gate	bit 3
 *	jagcowe_wx_en	bit 2
 *	jagcowe_tx_en	bit 1
 *	gigephy_en	bit 0
 */
#define ET_PM_PHY_SW_COMA		0x40
#define ET_PMCSW_INIT			0x38

/* Intewwupt status weg at addwess 0x0018
 */
#define	ET_INTW_TXDMA_ISW	0x00000008
#define ET_INTW_TXDMA_EWW	0x00000010
#define ET_INTW_WXDMA_XFW_DONE	0x00000020
#define ET_INTW_WXDMA_FB_W0_WOW	0x00000040
#define ET_INTW_WXDMA_FB_W1_WOW	0x00000080
#define ET_INTW_WXDMA_STAT_WOW	0x00000100
#define ET_INTW_WXDMA_EWW	0x00000200
#define ET_INTW_WATCHDOG	0x00004000
#define ET_INTW_WOW		0x00008000
#define ET_INTW_PHY		0x00010000
#define ET_INTW_TXMAC		0x00020000
#define ET_INTW_WXMAC		0x00040000
#define ET_INTW_MAC_STAT	0x00080000
#define ET_INTW_SWV_TIMEOUT	0x00100000

/* Intewwupt mask wegistew at addwess 0x001C
 * Intewwupt awias cweaw mask weg at addwess 0x0020
 * Intewwupt status awias weg at addwess 0x0024
 *
 * Same masks as above
 */

/* Softwawe weset weg at addwess 0x0028
 * 0:	txdma_sw_weset
 * 1:	wxdma_sw_weset
 * 2:	txmac_sw_weset
 * 3:	wxmac_sw_weset
 * 4:	mac_sw_weset
 * 5:	mac_stat_sw_weset
 * 6:	mmc_sw_weset
 *31:	sewfcww_disabwe
 */
#define ET_WESET_AWW	0x007F

/* SWV Timew weg at addwess 0x002C (wow 24 bits)
 */

/* MSI Configuwation weg at addwess 0x0030
 */
#define ET_MSI_VECTOW	0x0000001F
#define ET_MSI_TC	0x00070000

/* Woopback weg wocated at addwess 0x0034
 */
#define ET_WOOP_MAC	0x00000001
#define ET_WOOP_DMA	0x00000002

/* GWOBAW Moduwe of JAGCowe Addwess Mapping
 * Wocated at addwess 0x0000
 */
stwuct gwobaw_wegs {				/* Wocation: */
	u32 txq_stawt_addw;			/*  0x0000 */
	u32 txq_end_addw;			/*  0x0004 */
	u32 wxq_stawt_addw;			/*  0x0008 */
	u32 wxq_end_addw;			/*  0x000C */
	u32 pm_csw;				/*  0x0010 */
	u32 unused;				/*  0x0014 */
	u32 int_status;				/*  0x0018 */
	u32 int_mask;				/*  0x001C */
	u32 int_awias_cww_en;			/*  0x0020 */
	u32 int_status_awias;			/*  0x0024 */
	u32 sw_weset;				/*  0x0028 */
	u32 swv_timew;				/*  0x002C */
	u32 msi_config;				/*  0x0030 */
	u32 woopback;				/*  0x0034 */
	u32 watchdog_timew;			/*  0x0038 */
};

/* STAWT OF TXDMA WEGISTEW ADDWESS MAP */
/* txdma contwow status weg at addwess 0x1000
 */
#define ET_TXDMA_CSW_HAWT	0x00000001
#define ET_TXDMA_DWOP_TWP	0x00000002
#define ET_TXDMA_CACHE_THWS	0x000000F0
#define ET_TXDMA_CACHE_SHIFT	4
#define ET_TXDMA_SNGW_EPKT	0x00000100
#define ET_TXDMA_CWASS		0x00001E00

/* stwuctuwe fow txdma packet wing base addwess hi weg in txdma addwess map
 * wocated at addwess 0x1004
 * Defined eawwiew (u32)
 */

/* stwuctuwe fow txdma packet wing base addwess wow weg in txdma addwess map
 * wocated at addwess 0x1008
 * Defined eawwiew (u32)
 */

/* stwuctuwe fow txdma packet wing numbew of descwiptow weg in txdma addwess
 * map.  Wocated at addwess 0x100C
 *
 * 31-10: unused
 * 9-0: pw ndes
 */
#define ET_DMA12_MASK		0x0FFF	/* 12 bit mask fow DMA12W types */
#define ET_DMA12_WWAP		0x1000
#define ET_DMA10_MASK		0x03FF	/* 10 bit mask fow DMA10W types */
#define ET_DMA10_WWAP		0x0400
#define ET_DMA4_MASK		0x000F	/* 4 bit mask fow DMA4W types */
#define ET_DMA4_WWAP		0x0010

#define INDEX12(x)	((x) & ET_DMA12_MASK)
#define INDEX10(x)	((x) & ET_DMA10_MASK)
#define INDEX4(x)	((x) & ET_DMA4_MASK)

/* 10bit DMA with wwap
 * txdma tx queue wwite addwess weg in txdma addwess map at 0x1010
 * txdma tx queue wwite addwess extewnaw weg in txdma addwess map at 0x1014
 * txdma tx queue wead addwess weg in txdma addwess map at 0x1018
 *
 * u32
 * txdma status wwiteback addwess hi weg in txdma addwess map at0x101C
 * txdma status wwiteback addwess wo weg in txdma addwess map at 0x1020
 *
 * 10bit DMA with wwap
 * txdma sewvice wequest weg in txdma addwess map at 0x1024
 * stwuctuwe fow txdma sewvice compwete weg in txdma addwess map at 0x1028
 *
 * 4bit DMA with wwap
 * txdma tx descwiptow cache wead index weg in txdma addwess map at 0x102C
 * txdma tx descwiptow cache wwite index weg in txdma addwess map at 0x1030
 *
 * txdma ewwow weg in txdma addwess map at addwess 0x1034
 * 0: PywdWesend
 * 1: PywdWewind
 * 4: DescwWesend
 * 5: DescwWewind
 * 8: WwbkWesend
 * 9: WwbkWewind
 */

/* Tx DMA Moduwe of JAGCowe Addwess Mapping
 * Wocated at addwess 0x1000
 */
stwuct txdma_wegs {			/* Wocation: */
	u32 csw;			/*  0x1000 */
	u32 pw_base_hi;			/*  0x1004 */
	u32 pw_base_wo;			/*  0x1008 */
	u32 pw_num_des;			/*  0x100C */
	u32 txq_ww_addw;		/*  0x1010 */
	u32 txq_ww_addw_ext;		/*  0x1014 */
	u32 txq_wd_addw;		/*  0x1018 */
	u32 dma_wb_base_hi;		/*  0x101C */
	u32 dma_wb_base_wo;		/*  0x1020 */
	u32 sewvice_wequest;		/*  0x1024 */
	u32 sewvice_compwete;		/*  0x1028 */
	u32 cache_wd_index;		/*  0x102C */
	u32 cache_ww_index;		/*  0x1030 */
	u32 tx_dma_ewwow;		/*  0x1034 */
	u32 desc_abowt_cnt;		/*  0x1038 */
	u32 paywoad_abowt_cnt;		/*  0x103c */
	u32 wwiteback_abowt_cnt;	/*  0x1040 */
	u32 desc_timeout_cnt;		/*  0x1044 */
	u32 paywoad_timeout_cnt;	/*  0x1048 */
	u32 wwiteback_timeout_cnt;	/*  0x104c */
	u32 desc_ewwow_cnt;		/*  0x1050 */
	u32 paywoad_ewwow_cnt;		/*  0x1054 */
	u32 wwiteback_ewwow_cnt;	/*  0x1058 */
	u32 dwopped_twp_cnt;		/*  0x105c */
	u32 new_sewvice_compwete;	/*  0x1060 */
	u32 ethewnet_packet_cnt;	/*  0x1064 */
};

/* END OF TXDMA WEGISTEW ADDWESS MAP */

/* STAWT OF WXDMA WEGISTEW ADDWESS MAP */
/* stwuctuwe fow contwow status weg in wxdma addwess map
 * Wocated at addwess 0x2000
 *
 * CSW
 * 0: hawt
 * 1-3: tc
 * 4: fbw_big_endian
 * 5: psw_big_endian
 * 6: pkt_big_endian
 * 7: dma_big_endian
 * 8-9: fbw0_size
 * 10: fbw0_enabwe
 * 11-12: fbw1_size
 * 13: fbw1_enabwe
 * 14: unused
 * 15: pkt_dwop_disabwe
 * 16: pkt_done_fwush
 * 17: hawt_status
 * 18-31: unused
 */
#define ET_WXDMA_CSW_HAWT		0x0001
#define ET_WXDMA_CSW_FBW0_SIZE_WO	0x0100
#define ET_WXDMA_CSW_FBW0_SIZE_HI	0x0200
#define ET_WXDMA_CSW_FBW0_ENABWE	0x0400
#define ET_WXDMA_CSW_FBW1_SIZE_WO	0x0800
#define ET_WXDMA_CSW_FBW1_SIZE_HI	0x1000
#define ET_WXDMA_CSW_FBW1_ENABWE	0x2000
#define ET_WXDMA_CSW_HAWT_STATUS	0x00020000

/* stwuctuwe fow dma wwiteback wo weg in wxdma addwess map
 * wocated at addwess 0x2004
 * Defined eawwiew (u32)
 */

/* stwuctuwe fow dma wwiteback hi weg in wxdma addwess map
 * wocated at addwess 0x2008
 * Defined eawwiew (u32)
 */

/* stwuctuwe fow numbew of packets done weg in wxdma addwess map
 * wocated at addwess 0x200C
 *
 * 31-8: unused
 * 7-0: num done
 */

/* stwuctuwe fow max packet time weg in wxdma addwess map
 * wocated at addwess 0x2010
 *
 * 31-18: unused
 * 17-0: time done
 */

/* stwuctuwe fow wx queue wead addwess weg in wxdma addwess map
 * wocated at addwess 0x2014
 * Defined eawwiew (u32)
 */

/* stwuctuwe fow wx queue wead addwess extewnaw weg in wxdma addwess map
 * wocated at addwess 0x2018
 * Defined eawwiew (u32)
 */

/* stwuctuwe fow wx queue wwite addwess weg in wxdma addwess map
 * wocated at addwess 0x201C
 * Defined eawwiew (u32)
 */

/* stwuctuwe fow packet status wing base addwess wo weg in wxdma addwess map
 * wocated at addwess 0x2020
 * Defined eawwiew (u32)
 */

/* stwuctuwe fow packet status wing base addwess hi weg in wxdma addwess map
 * wocated at addwess 0x2024
 * Defined eawwiew (u32)
 */

/* stwuctuwe fow packet status wing numbew of descwiptows weg in wxdma addwess
 * map.  Wocated at addwess 0x2028
 *
 * 31-12: unused
 * 11-0: psw ndes
 */
#define ET_WXDMA_PSW_NUM_DES_MASK	0xFFF

/* stwuctuwe fow packet status wing avaiwabwe offset weg in wxdma addwess map
 * wocated at addwess 0x202C
 *
 * 31-13: unused
 * 12: psw avaiw wwap
 * 11-0: psw avaiw
 */

/* stwuctuwe fow packet status wing fuww offset weg in wxdma addwess map
 * wocated at addwess 0x2030
 *
 * 31-13: unused
 * 12: psw fuww wwap
 * 11-0: psw fuww
 */

/* stwuctuwe fow packet status wing access index weg in wxdma addwess map
 * wocated at addwess 0x2034
 *
 * 31-5: unused
 * 4-0: psw_ai
 */

/* stwuctuwe fow packet status wing minimum descwiptows weg in wxdma addwess
 * map.  Wocated at addwess 0x2038
 *
 * 31-12: unused
 * 11-0: psw_min
 */

/* stwuctuwe fow fwee buffew wing base wo addwess weg in wxdma addwess map
 * wocated at addwess 0x203C
 * Defined eawwiew (u32)
 */

/* stwuctuwe fow fwee buffew wing base hi addwess weg in wxdma addwess map
 * wocated at addwess 0x2040
 * Defined eawwiew (u32)
 */

/* stwuctuwe fow fwee buffew wing numbew of descwiptows weg in wxdma addwess
 * map.  Wocated at addwess 0x2044
 *
 * 31-10: unused
 * 9-0: fbw ndesc
 */

/* stwuctuwe fow fwee buffew wing 0 avaiwabwe offset weg in wxdma addwess map
 * wocated at addwess 0x2048
 * Defined eawwiew (u32)
 */

/* stwuctuwe fow fwee buffew wing 0 fuww offset weg in wxdma addwess map
 * wocated at addwess 0x204C
 * Defined eawwiew (u32)
 */

/* stwuctuwe fow fwee buffew cache 0 fuww offset weg in wxdma addwess map
 * wocated at addwess 0x2050
 *
 * 31-5: unused
 * 4-0: fbc wdi
 */

/* stwuctuwe fow fwee buffew wing 0 minimum descwiptow weg in wxdma addwess map
 * wocated at addwess 0x2054
 *
 * 31-10: unused
 * 9-0: fbw min
 */

/* stwuctuwe fow fwee buffew wing 1 base addwess wo weg in wxdma addwess map
 * wocated at addwess 0x2058 - 0x205C
 * Defined eawwiew (WXDMA_FBW_BASE_WO_t and WXDMA_FBW_BASE_HI_t)
 */

/* stwuctuwe fow fwee buffew wing 1 numbew of descwiptows weg in wxdma addwess
 * map.  Wocated at addwess 0x2060
 * Defined eawwiew (WXDMA_FBW_NUM_DES_t)
 */

/* stwuctuwe fow fwee buffew wing 1 avaiwabwe offset weg in wxdma addwess map
 * wocated at addwess 0x2064
 * Defined Eawwiew (WXDMA_FBW_AVAIW_OFFSET_t)
 */

/* stwuctuwe fow fwee buffew wing 1 fuww offset weg in wxdma addwess map
 * wocated at addwess 0x2068
 * Defined Eawwiew (WXDMA_FBW_FUWW_OFFSET_t)
 */

/* stwuctuwe fow fwee buffew cache 1 wead index weg in wxdma addwess map
 * wocated at addwess 0x206C
 * Defined Eawwiew (WXDMA_FBC_WD_INDEX_t)
 */

/* stwuctuwe fow fwee buffew wing 1 minimum descwiptow weg in wxdma addwess map
 * wocated at addwess 0x2070
 * Defined Eawwiew (WXDMA_FBW_MIN_DES_t)
 */

/* Wx DMA Moduwe of JAGCowe Addwess Mapping
 * Wocated at addwess 0x2000
 */
stwuct wxdma_wegs {					/* Wocation: */
	u32 csw;					/*  0x2000 */
	u32 dma_wb_base_wo;				/*  0x2004 */
	u32 dma_wb_base_hi;				/*  0x2008 */
	u32 num_pkt_done;				/*  0x200C */
	u32 max_pkt_time;				/*  0x2010 */
	u32 wxq_wd_addw;				/*  0x2014 */
	u32 wxq_wd_addw_ext;				/*  0x2018 */
	u32 wxq_ww_addw;				/*  0x201C */
	u32 psw_base_wo;				/*  0x2020 */
	u32 psw_base_hi;				/*  0x2024 */
	u32 psw_num_des;				/*  0x2028 */
	u32 psw_avaiw_offset;				/*  0x202C */
	u32 psw_fuww_offset;				/*  0x2030 */
	u32 psw_access_index;				/*  0x2034 */
	u32 psw_min_des;				/*  0x2038 */
	u32 fbw0_base_wo;				/*  0x203C */
	u32 fbw0_base_hi;				/*  0x2040 */
	u32 fbw0_num_des;				/*  0x2044 */
	u32 fbw0_avaiw_offset;				/*  0x2048 */
	u32 fbw0_fuww_offset;				/*  0x204C */
	u32 fbw0_wd_index;				/*  0x2050 */
	u32 fbw0_min_des;				/*  0x2054 */
	u32 fbw1_base_wo;				/*  0x2058 */
	u32 fbw1_base_hi;				/*  0x205C */
	u32 fbw1_num_des;				/*  0x2060 */
	u32 fbw1_avaiw_offset;				/*  0x2064 */
	u32 fbw1_fuww_offset;				/*  0x2068 */
	u32 fbw1_wd_index;				/*  0x206C */
	u32 fbw1_min_des;				/*  0x2070 */
};

/* END OF WXDMA WEGISTEW ADDWESS MAP */

/* STAWT OF TXMAC WEGISTEW ADDWESS MAP */
/* stwuctuwe fow contwow weg in txmac addwess map
 * wocated at addwess 0x3000
 *
 * bits
 * 31-8: unused
 * 7: ckwseg_disabwe
 * 6: ckbcnt_disabwe
 * 5: cksegnum
 * 4: async_disabwe
 * 3: fc_disabwe
 * 2: mcif_disabwe
 * 1: mif_disabwe
 * 0: txmac_en
 */
#define ET_TX_CTWW_FC_DISABWE	0x0008
#define ET_TX_CTWW_TXMAC_ENABWE	0x0001

/* stwuctuwe fow shadow pointew weg in txmac addwess map
 * wocated at addwess 0x3004
 * 31-27: wesewved
 * 26-16: txq wd ptw
 * 15-11: wesewved
 * 10-0: txq ww ptw
 */

/* stwuctuwe fow ewwow count weg in txmac addwess map
 * wocated at addwess 0x3008
 *
 * 31-12: unused
 * 11-8: wesewved
 * 7-4: txq_undewwun
 * 3-0: fifo_undewwun
 */

/* stwuctuwe fow max fiww weg in txmac addwess map
 * wocated at addwess 0x300C
 * 31-12: unused
 * 11-0: max fiww
 */

/* stwuctuwe fow cf pawametew weg in txmac addwess map
 * wocated at addwess 0x3010
 * 31-16: cfep
 * 15-0: cfpt
 */

/* stwuctuwe fow tx test weg in txmac addwess map
 * wocated at addwess 0x3014
 * 31-17: unused
 * 16: wesewved
 * 15: txtest_en
 * 14-11: unused
 * 10-0: txq test pointew
 */

/* stwuctuwe fow ewwow weg in txmac addwess map
 * wocated at addwess 0x3018
 *
 * 31-9: unused
 * 8: fifo_undewwun
 * 7-6: unused
 * 5: ctww2_eww
 * 4: txq_undewwun
 * 3: bcnt_eww
 * 2: wseg_eww
 * 1: segnum_eww
 * 0: seg0_eww
 */

/* stwuctuwe fow ewwow intewwupt weg in txmac addwess map
 * wocated at addwess 0x301C
 *
 * 31-9: unused
 * 8: fifo_undewwun
 * 7-6: unused
 * 5: ctww2_eww
 * 4: txq_undewwun
 * 3: bcnt_eww
 * 2: wseg_eww
 * 1: segnum_eww
 * 0: seg0_eww
 */

/* stwuctuwe fow ewwow intewwupt weg in txmac addwess map
 * wocated at addwess 0x3020
 *
 * 31-2: unused
 * 1: bp_weq
 * 0: bp_xonxoff
 */

/* Tx MAC Moduwe of JAGCowe Addwess Mapping
 */
stwuct txmac_wegs {			/* Wocation: */
	u32 ctw;			/*  0x3000 */
	u32 shadow_ptw;			/*  0x3004 */
	u32 eww_cnt;			/*  0x3008 */
	u32 max_fiww;			/*  0x300C */
	u32 cf_pawam;			/*  0x3010 */
	u32 tx_test;			/*  0x3014 */
	u32 eww;			/*  0x3018 */
	u32 eww_int;			/*  0x301C */
	u32 bp_ctww;			/*  0x3020 */
};

/* END OF TXMAC WEGISTEW ADDWESS MAP */

/* STAWT OF WXMAC WEGISTEW ADDWESS MAP */

/* stwuctuwe fow wxmac contwow weg in wxmac addwess map
 * wocated at addwess 0x4000
 *
 * 31-7: wesewved
 * 6: wxmac_int_disabwe
 * 5: async_disabwe
 * 4: mif_disabwe
 * 3: wow_disabwe
 * 2: pkt_fiwtew_disabwe
 * 1: mcif_disabwe
 * 0: wxmac_en
 */
#define ET_WX_CTWW_WOW_DISABWE	0x0008
#define ET_WX_CTWW_WXMAC_ENABWE	0x0001

/* stwuctuwe fow Wake On Wan Contwow and CWC 0 weg in wxmac addwess map
 * wocated at addwess 0x4004
 * 31-16: cwc
 * 15-12: wesewved
 * 11: ignowe_pp
 * 10: ignowe_mp
 * 9: cww_intw
 * 8: ignowe_wink_chg
 * 7: ignowe_uni
 * 6: ignowe_muwti
 * 5: ignowe_bwoad
 * 4-0: vawid_cwc 4-0
 */

/* stwuctuwe fow CWC 1 and CWC 2 weg in wxmac addwess map
 * wocated at addwess 0x4008
 *
 * 31-16: cwc2
 * 15-0: cwc1
 */

/* stwuctuwe fow CWC 3 and CWC 4 weg in wxmac addwess map
 * wocated at addwess 0x400C
 *
 * 31-16: cwc4
 * 15-0: cwc3
 */

/* stwuctuwe fow Wake On Wan Souwce Addwess Wo weg in wxmac addwess map
 * wocated at addwess 0x4010
 *
 * 31-24: sa3
 * 23-16: sa4
 * 15-8: sa5
 * 7-0: sa6
 */
#define ET_WX_WOW_WO_SA3_SHIFT 24
#define ET_WX_WOW_WO_SA4_SHIFT 16
#define ET_WX_WOW_WO_SA5_SHIFT 8

/* stwuctuwe fow Wake On Wan Souwce Addwess Hi weg in wxmac addwess map
 * wocated at addwess 0x4014
 *
 * 31-16: wesewved
 * 15-8: sa1
 * 7-0: sa2
 */
#define ET_WX_WOW_HI_SA1_SHIFT 8

/* stwuctuwe fow Wake On Wan mask weg in wxmac addwess map
 * wocated at addwess 0x4018 - 0x4064
 * Defined eawwiew (u32)
 */

/* stwuctuwe fow Unicast Packet Fiwtew Addwess 1 weg in wxmac addwess map
 * wocated at addwess 0x4068
 *
 * 31-24: addw1_3
 * 23-16: addw1_4
 * 15-8: addw1_5
 * 7-0: addw1_6
 */
#define ET_WX_UNI_PF_ADDW1_3_SHIFT 24
#define ET_WX_UNI_PF_ADDW1_4_SHIFT 16
#define ET_WX_UNI_PF_ADDW1_5_SHIFT 8

/* stwuctuwe fow Unicast Packet Fiwtew Addwess 2 weg in wxmac addwess map
 * wocated at addwess 0x406C
 *
 * 31-24: addw2_3
 * 23-16: addw2_4
 * 15-8: addw2_5
 * 7-0: addw2_6
 */
#define ET_WX_UNI_PF_ADDW2_3_SHIFT 24
#define ET_WX_UNI_PF_ADDW2_4_SHIFT 16
#define ET_WX_UNI_PF_ADDW2_5_SHIFT 8

/* stwuctuwe fow Unicast Packet Fiwtew Addwess 1 & 2 weg in wxmac addwess map
 * wocated at addwess 0x4070
 *
 * 31-24: addw2_1
 * 23-16: addw2_2
 * 15-8: addw1_1
 * 7-0: addw1_2
 */
#define ET_WX_UNI_PF_ADDW2_1_SHIFT 24
#define ET_WX_UNI_PF_ADDW2_2_SHIFT 16
#define ET_WX_UNI_PF_ADDW1_1_SHIFT 8

/* stwuctuwe fow Muwticast Hash weg in wxmac addwess map
 * wocated at addwess 0x4074 - 0x4080
 * Defined eawwiew (u32)
 */

/* stwuctuwe fow Packet Fiwtew Contwow weg in wxmac addwess map
 * wocated at addwess 0x4084
 *
 * 31-23: unused
 * 22-16: min_pkt_size
 * 15-4: unused
 * 3: fiwtew_fwag_en
 * 2: fiwtew_uni_en
 * 1: fiwtew_muwti_en
 * 0: fiwtew_bwoad_en
 */
#define ET_WX_PFCTWW_MIN_PKT_SZ_SHIFT		16
#define ET_WX_PFCTWW_FWAG_FIWTEW_ENABWE		0x0008
#define ET_WX_PFCTWW_UNICST_FIWTEW_ENABWE	0x0004
#define ET_WX_PFCTWW_MWTCST_FIWTEW_ENABWE	0x0002
#define ET_WX_PFCTWW_BWDCST_FIWTEW_ENABWE	0x0001

/* stwuctuwe fow Memowy Contwowwew Intewface Contwow Max Segment weg in wxmac
 * addwess map.  Wocated at addwess 0x4088
 *
 * 31-10: wesewved
 * 9-2: max_size
 * 1: fc_en
 * 0: seg_en
 */
#define ET_WX_MCIF_CTWW_MAX_SEG_SIZE_SHIFT	2
#define ET_WX_MCIF_CTWW_MAX_SEG_FC_ENABWE	0x0002
#define ET_WX_MCIF_CTWW_MAX_SEG_ENABWE		0x0001

/* stwuctuwe fow Memowy Contwowwew Intewface Watew Mawk weg in wxmac addwess
 * map.  Wocated at addwess 0x408C
 *
 * 31-26: unused
 * 25-16: mawk_hi
 * 15-10: unused
 * 9-0: mawk_wo
 */

/* stwuctuwe fow Wx Queue Diawog weg in wxmac addwess map.
 * wocated at addwess 0x4090
 *
 * 31-26: wesewved
 * 25-16: wd_ptw
 * 15-10: wesewved
 * 9-0: ww_ptw
 */

/* stwuctuwe fow space avaiwabwe weg in wxmac addwess map.
 * wocated at addwess 0x4094
 *
 * 31-17: wesewved
 * 16: space_avaiw_en
 * 15-10: wesewved
 * 9-0: space_avaiw
 */

/* stwuctuwe fow management intewface weg in wxmac addwess map.
 * wocated at addwess 0x4098
 *
 * 31-18: wesewved
 * 17: dwop_pkt_en
 * 16-0: dwop_pkt_mask
 */

/* stwuctuwe fow Ewwow weg in wxmac addwess map.
 * wocated at addwess 0x409C
 *
 * 31-4: unused
 * 3: mif
 * 2: async
 * 1: pkt_fiwtew
 * 0: mcif
 */

/* Wx MAC Moduwe of JAGCowe Addwess Mapping
 */
stwuct wxmac_wegs {					/* Wocation: */
	u32 ctww;					/*  0x4000 */
	u32 cwc0;					/*  0x4004 */
	u32 cwc12;					/*  0x4008 */
	u32 cwc34;					/*  0x400C */
	u32 sa_wo;					/*  0x4010 */
	u32 sa_hi;					/*  0x4014 */
	u32 mask0_wowd0;				/*  0x4018 */
	u32 mask0_wowd1;				/*  0x401C */
	u32 mask0_wowd2;				/*  0x4020 */
	u32 mask0_wowd3;				/*  0x4024 */
	u32 mask1_wowd0;				/*  0x4028 */
	u32 mask1_wowd1;				/*  0x402C */
	u32 mask1_wowd2;				/*  0x4030 */
	u32 mask1_wowd3;				/*  0x4034 */
	u32 mask2_wowd0;				/*  0x4038 */
	u32 mask2_wowd1;				/*  0x403C */
	u32 mask2_wowd2;				/*  0x4040 */
	u32 mask2_wowd3;				/*  0x4044 */
	u32 mask3_wowd0;				/*  0x4048 */
	u32 mask3_wowd1;				/*  0x404C */
	u32 mask3_wowd2;				/*  0x4050 */
	u32 mask3_wowd3;				/*  0x4054 */
	u32 mask4_wowd0;				/*  0x4058 */
	u32 mask4_wowd1;				/*  0x405C */
	u32 mask4_wowd2;				/*  0x4060 */
	u32 mask4_wowd3;				/*  0x4064 */
	u32 uni_pf_addw1;				/*  0x4068 */
	u32 uni_pf_addw2;				/*  0x406C */
	u32 uni_pf_addw3;				/*  0x4070 */
	u32 muwti_hash1;				/*  0x4074 */
	u32 muwti_hash2;				/*  0x4078 */
	u32 muwti_hash3;				/*  0x407C */
	u32 muwti_hash4;				/*  0x4080 */
	u32 pf_ctww;					/*  0x4084 */
	u32 mcif_ctww_max_seg;				/*  0x4088 */
	u32 mcif_watew_mawk;				/*  0x408C */
	u32 wxq_diag;					/*  0x4090 */
	u32 space_avaiw;				/*  0x4094 */

	u32 mif_ctww;					/*  0x4098 */
	u32 eww_weg;					/*  0x409C */
};

/* END OF WXMAC WEGISTEW ADDWESS MAP */

/* STAWT OF MAC WEGISTEW ADDWESS MAP */
/* stwuctuwe fow configuwation #1 weg in mac addwess map.
 * wocated at addwess 0x5000
 *
 * 31: soft weset
 * 30: sim weset
 * 29-20: wesewved
 * 19: weset wx mc
 * 18: weset tx mc
 * 17: weset wx func
 * 16: weset tx fnc
 * 15-9: wesewved
 * 8: woopback
 * 7-6: wesewved
 * 5: wx fwow
 * 4: tx fwow
 * 3: syncd wx en
 * 2: wx enabwe
 * 1: syncd tx en
 * 0: tx enabwe
 */
#define ET_MAC_CFG1_SOFT_WESET		0x80000000
#define ET_MAC_CFG1_SIM_WESET		0x40000000
#define ET_MAC_CFG1_WESET_WXMC		0x00080000
#define ET_MAC_CFG1_WESET_TXMC		0x00040000
#define ET_MAC_CFG1_WESET_WXFUNC	0x00020000
#define ET_MAC_CFG1_WESET_TXFUNC	0x00010000
#define ET_MAC_CFG1_WOOPBACK		0x00000100
#define ET_MAC_CFG1_WX_FWOW		0x00000020
#define ET_MAC_CFG1_TX_FWOW		0x00000010
#define ET_MAC_CFG1_WX_ENABWE		0x00000004
#define ET_MAC_CFG1_TX_ENABWE		0x00000001
#define ET_MAC_CFG1_WAIT		0x0000000A	/* WX & TX syncd */

/* stwuctuwe fow configuwation #2 weg in mac addwess map.
 * wocated at addwess 0x5004
 * 31-16: wesewved
 * 15-12: pweambwe
 * 11-10: wesewved
 * 9-8: if mode
 * 7-6: wesewved
 * 5: huge fwame
 * 4: wength check
 * 3: undefined
 * 2: pad cwc
 * 1: cwc enabwe
 * 0: fuww dupwex
 */
#define ET_MAC_CFG2_PWEAMBWE_SHIFT	12
#define ET_MAC_CFG2_IFMODE_MASK		0x0300
#define ET_MAC_CFG2_IFMODE_1000		0x0200
#define ET_MAC_CFG2_IFMODE_100		0x0100
#define ET_MAC_CFG2_IFMODE_HUGE_FWAME	0x0020
#define ET_MAC_CFG2_IFMODE_WEN_CHECK	0x0010
#define ET_MAC_CFG2_IFMODE_PAD_CWC	0x0004
#define ET_MAC_CFG2_IFMODE_CWC_ENABWE	0x0002
#define ET_MAC_CFG2_IFMODE_FUWW_DPWX	0x0001

/* stwuctuwe fow Intewpacket gap weg in mac addwess map.
 * wocated at addwess 0x5008
 *
 * 31: wesewved
 * 30-24: non B2B ipg 1
 * 23: undefined
 * 22-16: non B2B ipg 2
 * 15-8: Min ifg enfowce
 * 7-0: B2B ipg
 *
 * stwuctuwe fow hawf dupwex weg in mac addwess map.
 * wocated at addwess 0x500C
 * 31-24: wesewved
 * 23-20: Awt BEB twunc
 * 19: Awt BEB enabwe
 * 18: BP no backoff
 * 17: no backoff
 * 16: excess defew
 * 15-12: we-xmit max
 * 11-10: wesewved
 * 9-0: cowwision window
 */

/* stwuctuwe fow Maximum Fwame Wength weg in mac addwess map.
 * wocated at addwess 0x5010: bits 0-15 howd the wength.
 */

/* stwuctuwe fow Wesewve 1 weg in mac addwess map.
 * wocated at addwess 0x5014 - 0x5018
 * Defined eawwiew (u32)
 */

/* stwuctuwe fow Test weg in mac addwess map.
 * wocated at addwess 0x501C
 * test: bits 0-2, west unused
 */

/* stwuctuwe fow MII Management Configuwation weg in mac addwess map.
 * wocated at addwess 0x5020
 *
 * 31: weset MII mgmt
 * 30-6: unused
 * 5: scan auto incwement
 * 4: pweambwe suppwess
 * 3: undefined
 * 2-0: mgmt cwock weset
 */
#define ET_MAC_MIIMGMT_CWK_WST	0x0007

/* stwuctuwe fow MII Management Command weg in mac addwess map.
 * wocated at addwess 0x5024
 * bit 1: scan cycwe
 * bit 0: wead cycwe
 */

/* stwuctuwe fow MII Management Addwess weg in mac addwess map.
 * wocated at addwess 0x5028
 * 31-13: wesewved
 * 12-8: phy addw
 * 7-5: wesewved
 * 4-0: wegistew
 */
#define ET_MAC_MII_ADDW(phy, weg)	((phy) << 8 | (weg))

/* stwuctuwe fow MII Management Contwow weg in mac addwess map.
 * wocated at addwess 0x502C
 * 31-16: wesewved
 * 15-0: phy contwow
 */

/* stwuctuwe fow MII Management Status weg in mac addwess map.
 * wocated at addwess 0x5030
 * 31-16: wesewved
 * 15-0: phy contwow
 */
#define ET_MAC_MIIMGMT_STAT_PHYCWTW_MASK 0xFFFF

/* stwuctuwe fow MII Management Indicatows weg in mac addwess map.
 * wocated at addwess 0x5034
 * 31-3: wesewved
 * 2: not vawid
 * 1: scanning
 * 0: busy
 */
#define ET_MAC_MGMT_BUSY	0x00000001	/* busy */
#define ET_MAC_MGMT_WAIT	0x00000005	/* busy | not vawid */

/* stwuctuwe fow Intewface Contwow weg in mac addwess map.
 * wocated at addwess 0x5038
 *
 * 31: weset if moduwe
 * 30-28: wesewved
 * 27: tbi mode
 * 26: ghd mode
 * 25: whd mode
 * 24: phy mode
 * 23: weset pew mii
 * 22-17: wesewved
 * 16: speed
 * 15: weset pe100x
 * 14-11: wesewved
 * 10: fowce quiet
 * 9: no ciphew
 * 8: disabwe wink faiw
 * 7: weset gpsi
 * 6-1: wesewved
 * 0: enabwe jabbew pwotection
 */
#define ET_MAC_IFCTWW_GHDMODE	(1 << 26)
#define ET_MAC_IFCTWW_PHYMODE	(1 << 24)

/* stwuctuwe fow Intewface Status weg in mac addwess map.
 * wocated at addwess 0x503C
 *
 * 31-10: wesewved
 * 9: excess_defew
 * 8: cwash
 * 7: phy_jabbew
 * 6: phy_wink_ok
 * 5: phy_fuww_dupwex
 * 4: phy_speed
 * 3: pe100x_wink_faiw
 * 2: pe10t_woss_cawwiew
 * 1: pe10t_sqe_ewwow
 * 0: pe10t_jabbew
 */

/* stwuctuwe fow Mac Station Addwess, Pawt 1 weg in mac addwess map.
 * wocated at addwess 0x5040
 *
 * 31-24: Octet6
 * 23-16: Octet5
 * 15-8: Octet4
 * 7-0: Octet3
 */
#define ET_MAC_STATION_ADDW1_OC6_SHIFT 24
#define ET_MAC_STATION_ADDW1_OC5_SHIFT 16
#define ET_MAC_STATION_ADDW1_OC4_SHIFT 8

/* stwuctuwe fow Mac Station Addwess, Pawt 2 weg in mac addwess map.
 * wocated at addwess 0x5044
 *
 * 31-24: Octet2
 * 23-16: Octet1
 * 15-0: wesewved
 */
#define ET_MAC_STATION_ADDW2_OC2_SHIFT 24
#define ET_MAC_STATION_ADDW2_OC1_SHIFT 16

/* MAC Moduwe of JAGCowe Addwess Mapping
 */
stwuct mac_wegs {					/* Wocation: */
	u32 cfg1;					/*  0x5000 */
	u32 cfg2;					/*  0x5004 */
	u32 ipg;					/*  0x5008 */
	u32 hfdp;					/*  0x500C */
	u32 max_fm_wen;					/*  0x5010 */
	u32 wsv1;					/*  0x5014 */
	u32 wsv2;					/*  0x5018 */
	u32 mac_test;					/*  0x501C */
	u32 mii_mgmt_cfg;				/*  0x5020 */
	u32 mii_mgmt_cmd;				/*  0x5024 */
	u32 mii_mgmt_addw;				/*  0x5028 */
	u32 mii_mgmt_ctww;				/*  0x502C */
	u32 mii_mgmt_stat;				/*  0x5030 */
	u32 mii_mgmt_indicatow;				/*  0x5034 */
	u32 if_ctww;					/*  0x5038 */
	u32 if_stat;					/*  0x503C */
	u32 station_addw_1;				/*  0x5040 */
	u32 station_addw_2;				/*  0x5044 */
};

/* END OF MAC WEGISTEW ADDWESS MAP */

/* STAWT OF MAC STAT WEGISTEW ADDWESS MAP */
/* stwuctuwe fow Cawwy Wegistew One and it's Mask Wegistew weg wocated in mac
 * stat addwess map addwess 0x6130 and 0x6138.
 *
 * 31: tw64
 * 30: tw127
 * 29: tw255
 * 28: tw511
 * 27: tw1k
 * 26: twmax
 * 25: twmgv
 * 24-17: unused
 * 16: wbyt
 * 15: wpkt
 * 14: wfcs
 * 13: wmca
 * 12: wbca
 * 11: wxcf
 * 10: wxpf
 * 9: wxuo
 * 8: wawn
 * 7: wfww
 * 6: wcde
 * 5: wcse
 * 4: wund
 * 3: wovw
 * 2: wfwg
 * 1: wjbw
 * 0: wdwp
 */

/* stwuctuwe fow Cawwy Wegistew Two Mask Wegistew weg in mac stat addwess map.
 * wocated at addwess 0x613C
 *
 * 31-20: unused
 * 19: tjbw
 * 18: tfcs
 * 17: txcf
 * 16: tovw
 * 15: tund
 * 14: twfg
 * 13: tbyt
 * 12: tpkt
 * 11: tmca
 * 10: tbca
 * 9: txpf
 * 8: tdfw
 * 7: tedf
 * 6: tscw
 * 5: tmcw
 * 4: twcw
 * 3: txcw
 * 2: tncw
 * 1: tpfh
 * 0: tdwp
 */

/* MAC STATS Moduwe of JAGCowe Addwess Mapping
 */
stwuct macstat_wegs {			/* Wocation: */
	u32 pad[32];			/*  0x6000 - 607C */

	/* countews */
	u32 txwx_0_64_byte_fwames;	/*  0x6080 */
	u32 txwx_65_127_byte_fwames;	/*  0x6084 */
	u32 txwx_128_255_byte_fwames;	/*  0x6088 */
	u32 txwx_256_511_byte_fwames;	/*  0x608C */
	u32 txwx_512_1023_byte_fwames;	/*  0x6090 */
	u32 txwx_1024_1518_byte_fwames;	/*  0x6094 */
	u32 txwx_1519_1522_gvwn_fwames;	/*  0x6098 */
	u32 wx_bytes;			/*  0x609C */
	u32 wx_packets;			/*  0x60A0 */
	u32 wx_fcs_ewws;		/*  0x60A4 */
	u32 wx_muwticast_packets;	/*  0x60A8 */
	u32 wx_bwoadcast_packets;	/*  0x60AC */
	u32 wx_contwow_fwames;		/*  0x60B0 */
	u32 wx_pause_fwames;		/*  0x60B4 */
	u32 wx_unknown_opcodes;		/*  0x60B8 */
	u32 wx_awign_ewws;		/*  0x60BC */
	u32 wx_fwame_wen_ewws;		/*  0x60C0 */
	u32 wx_code_ewws;		/*  0x60C4 */
	u32 wx_cawwiew_sense_ewws;	/*  0x60C8 */
	u32 wx_undewsize_packets;	/*  0x60CC */
	u32 wx_ovewsize_packets;	/*  0x60D0 */
	u32 wx_fwagment_packets;	/*  0x60D4 */
	u32 wx_jabbews;			/*  0x60D8 */
	u32 wx_dwops;			/*  0x60DC */
	u32 tx_bytes;			/*  0x60E0 */
	u32 tx_packets;			/*  0x60E4 */
	u32 tx_muwticast_packets;	/*  0x60E8 */
	u32 tx_bwoadcast_packets;	/*  0x60EC */
	u32 tx_pause_fwames;		/*  0x60F0 */
	u32 tx_defewwed;		/*  0x60F4 */
	u32 tx_excessive_defewwed;	/*  0x60F8 */
	u32 tx_singwe_cowwisions;	/*  0x60FC */
	u32 tx_muwtipwe_cowwisions;	/*  0x6100 */
	u32 tx_wate_cowwisions;		/*  0x6104 */
	u32 tx_excessive_cowwisions;	/*  0x6108 */
	u32 tx_totaw_cowwisions;	/*  0x610C */
	u32 tx_pause_honowed_fwames;	/*  0x6110 */
	u32 tx_dwops;			/*  0x6114 */
	u32 tx_jabbews;			/*  0x6118 */
	u32 tx_fcs_ewws;		/*  0x611C */
	u32 tx_contwow_fwames;		/*  0x6120 */
	u32 tx_ovewsize_fwames;		/*  0x6124 */
	u32 tx_undewsize_fwames;	/*  0x6128 */
	u32 tx_fwagments;		/*  0x612C */
	u32 cawwy_weg1;			/*  0x6130 */
	u32 cawwy_weg2;			/*  0x6134 */
	u32 cawwy_weg1_mask;		/*  0x6138 */
	u32 cawwy_weg2_mask;		/*  0x613C */
};

/* END OF MAC STAT WEGISTEW ADDWESS MAP */

/* STAWT OF MMC WEGISTEW ADDWESS MAP */
/* Main Memowy Contwowwew Contwow weg in mmc addwess map.
 * wocated at addwess 0x7000
 */
#define ET_MMC_ENABWE		1
#define ET_MMC_AWB_DISABWE	2
#define ET_MMC_WXMAC_DISABWE	4
#define ET_MMC_TXMAC_DISABWE	8
#define ET_MMC_TXDMA_DISABWE	16
#define ET_MMC_WXDMA_DISABWE	32
#define ET_MMC_FOWCE_CE		64

/* Main Memowy Contwowwew Host Memowy Access Addwess weg in mmc
 * addwess map.  Wocated at addwess 0x7004. Top 16 bits howd the addwess bits
 */
#define ET_SWAM_WEQ_ACCESS	1
#define ET_SWAM_WW_ACCESS	2
#define ET_SWAM_IS_CTWW		4

/* stwuctuwe fow Main Memowy Contwowwew Host Memowy Access Data weg in mmc
 * addwess map.  Wocated at addwess 0x7008 - 0x7014
 * Defined eawwiew (u32)
 */

/* Memowy Contwow Moduwe of JAGCowe Addwess Mapping
 */
stwuct mmc_wegs {		/* Wocation: */
	u32 mmc_ctww;		/*  0x7000 */
	u32 swam_access;	/*  0x7004 */
	u32 swam_wowd1;		/*  0x7008 */
	u32 swam_wowd2;		/*  0x700C */
	u32 swam_wowd3;		/*  0x7010 */
	u32 swam_wowd4;		/*  0x7014 */
};

/* END OF MMC WEGISTEW ADDWESS MAP */

/* JAGCowe Addwess Mapping
 */
stwuct addwess_map {
	stwuct gwobaw_wegs gwobaw;
	/* unused section of gwobaw addwess map */
	u8 unused_gwobaw[4096 - sizeof(stwuct gwobaw_wegs)];
	stwuct txdma_wegs txdma;
	/* unused section of txdma addwess map */
	u8 unused_txdma[4096 - sizeof(stwuct txdma_wegs)];
	stwuct wxdma_wegs wxdma;
	/* unused section of wxdma addwess map */
	u8 unused_wxdma[4096 - sizeof(stwuct wxdma_wegs)];
	stwuct txmac_wegs txmac;
	/* unused section of txmac addwess map */
	u8 unused_txmac[4096 - sizeof(stwuct txmac_wegs)];
	stwuct wxmac_wegs wxmac;
	/* unused section of wxmac addwess map */
	u8 unused_wxmac[4096 - sizeof(stwuct wxmac_wegs)];
	stwuct mac_wegs mac;
	/* unused section of mac addwess map */
	u8 unused_mac[4096 - sizeof(stwuct mac_wegs)];
	stwuct macstat_wegs macstat;
	/* unused section of mac stat addwess map */
	u8 unused_mac_stat[4096 - sizeof(stwuct macstat_wegs)];
	stwuct mmc_wegs mmc;
	/* unused section of mmc addwess map */
	u8 unused_mmc[4096 - sizeof(stwuct mmc_wegs)];
	/* unused section of addwess map */
	u8 unused_[1015808];
	u8 unused_exp_wom[4096];	/* MGS-size TBD */
	u8 unused__[524288];	/* unused section of addwess map */
};

/* Defines fow genewic MII wegistews 0x00 -> 0x0F can be found in
 * incwude/winux/mii.h
 */
/* some defines fow modem wegistews that seem to be 'wesewved' */
#define PHY_INDEX_WEG              0x10
#define PHY_DATA_WEG               0x11
#define PHY_MPHY_CONTWOW_WEG       0x12

/* defines fow specified wegistews */
#define PHY_WOOPBACK_CONTWOW       0x13	/* TWU_VMI_WOOPBACK_CONTWOW_1_WEG 19 */
					/* TWU_VMI_WOOPBACK_CONTWOW_2_WEG 20 */
#define PHY_WEGISTEW_MGMT_CONTWOW  0x15	/* TWU_VMI_MI_SEQ_CONTWOW_WEG     21 */
#define PHY_CONFIG                 0x16	/* TWU_VMI_CONFIGUWATION_WEG      22 */
#define PHY_PHY_CONTWOW            0x17	/* TWU_VMI_PHY_CONTWOW_WEG        23 */
#define PHY_INTEWWUPT_MASK         0x18	/* TWU_VMI_INTEWWUPT_MASK_WEG     24 */
#define PHY_INTEWWUPT_STATUS       0x19	/* TWU_VMI_INTEWWUPT_STATUS_WEG   25 */
#define PHY_PHY_STATUS             0x1A	/* TWU_VMI_PHY_STATUS_WEG         26 */
#define PHY_WED_1                  0x1B	/* TWU_VMI_WED_CONTWOW_1_WEG      27 */
#define PHY_WED_2                  0x1C	/* TWU_VMI_WED_CONTWOW_2_WEG      28 */
					/* TWU_VMI_WINK_CONTWOW_WEG       29 */
					/* TWU_VMI_TIMING_CONTWOW_WEG        */

/* MI Wegistew 10: Gigabit basic mode status weg(Weg 0x0A) */
#define ET_1000BT_MSTW_SWV 0x4000

/* MI Wegistew 16 - 18: Wesewved Weg(0x10-0x12) */

/* MI Wegistew 19: Woopback Contwow Weg(0x13)
 *	15:	mii_en
 *	14:	pcs_en
 *	13:	pmd_en
 *	12:	aww_digitaw_en
 *	11:	wepwica_en
 *	10:	wine_dwivew_en
 *	9-0:	wesewved
 */

/* MI Wegistew 20: Wesewved Weg(0x14) */

/* MI Wegistew 21: Management Intewface Contwow Weg(0x15)
 *	15-11:	wesewved
 *	10-4:	mi_ewwow_count
 *	3:	wesewved
 *	2:	ignowe_10g_fw
 *	1:	wesewved
 *	0:	pweambwe_suppwess_en
 */

/* MI Wegistew 22: PHY Configuwation Weg(0x16)
 *	15:	cws_tx_en
 *	14:	wesewved
 *	13-12:	tx_fifo_depth
 *	11-10:	speed_downshift
 *	9:	pbi_detect
 *	8:	tbi_wate
 *	7:	awtewnate_np
 *	6:	gwoup_mdio_en
 *	5:	tx_cwock_en
 *	4:	sys_cwock_en
 *	3:	wesewved
 *	2-0:	mac_if_mode
 */
#define ET_PHY_CONFIG_TX_FIFO_DEPTH	0x3000

#define ET_PHY_CONFIG_FIFO_DEPTH_8	0x0000
#define ET_PHY_CONFIG_FIFO_DEPTH_16	0x1000
#define ET_PHY_CONFIG_FIFO_DEPTH_32	0x2000
#define ET_PHY_CONFIG_FIFO_DEPTH_64	0x3000

/* MI Wegistew 23: PHY CONTWOW Weg(0x17)
 *	15:	wesewved
 *	14:	tdw_en
 *	13:	wesewved
 *	12-11:	downshift_attempts
 *	10-6:	wesewved
 *	5:	jabbew_10baseT
 *	4:	sqe_10baseT
 *	3:	tp_woopback_10baseT
 *	2:	pweambwe_gen_en
 *	1:	wesewved
 *	0:	fowce_int
 */

/* MI Wegistew 24: Intewwupt Mask Weg(0x18)
 *	15-10:	wesewved
 *	9:	mdio_sync_wost
 *	8:	autoneg_status
 *	7:	hi_bit_eww
 *	6:	np_wx
 *	5:	eww_countew_fuww
 *	4:	fifo_ovew_undewfwow
 *	3:	wx_status
 *	2:	wink_status
 *	1:	automatic_speed
 *	0:	int_en
 */

/* MI Wegistew 25: Intewwupt Status Weg(0x19)
 *	15-10:	wesewved
 *	9:	mdio_sync_wost
 *	8:	autoneg_status
 *	7:	hi_bit_eww
 *	6:	np_wx
 *	5:	eww_countew_fuww
 *	4:	fifo_ovew_undewfwow
 *	3:	wx_status
 *	2:	wink_status
 *	1:	automatic_speed
 *	0:	int_en
 */

/* MI Wegistew 26: PHY Status Weg(0x1A)
 *	15:	wesewved
 *	14-13:	autoneg_fauwt
 *	12:	autoneg_status
 *	11:	mdi_x_status
 *	10:	powawity_status
 *	9-8:	speed_status
 *	7:	dupwex_status
 *	6:	wink_status
 *	5:	tx_status
 *	4:	wx_status
 *	3:	cowwision_status
 *	2:	autoneg_en
 *	1:	pause_en
 *	0:	asymmetwic_diw
 */
#define ET_PHY_AUTONEG_STATUS	0x1000
#define ET_PHY_POWAWITY_STATUS	0x0400
#define ET_PHY_SPEED_STATUS	0x0300
#define ET_PHY_DUPWEX_STATUS	0x0080
#define ET_PHY_WSTATUS		0x0040
#define ET_PHY_AUTONEG_ENABWE	0x0020

/* MI Wegistew 27: WED Contwow Weg 1(0x1B)
 *	15-14:	wesewved
 *	13-12:	wed_dup_indicate
 *	11-10:	wed_10baseT
 *	9-8:	wed_cowwision
 *	7-4:	wesewved
 *	3-2:	puwse_duw
 *	1:	puwse_stwetch1
 *	0:	puwse_stwetch0
 */

/* MI Wegistew 28: WED Contwow Weg 2(0x1C)
 *	15-12:	wed_wink
 *	11-8:	wed_tx_wx
 *	7-4:	wed_100BaseTX
 *	3-0:	wed_1000BaseT
 */
#define ET_WED2_WED_WINK	0xF000
#define ET_WED2_WED_TXWX	0x0F00
#define ET_WED2_WED_100TX	0x00F0
#define ET_WED2_WED_1000T	0x000F

/* defines fow WED contwow weg 2 vawues */
#define WED_VAW_1000BT			0x0
#define WED_VAW_100BTX			0x1
#define WED_VAW_10BT			0x2
#define WED_VAW_1000BT_100BTX		0x3 /* 1000BT on, 100BTX bwink */
#define WED_VAW_WINKON			0x4
#define WED_VAW_TX			0x5
#define WED_VAW_WX			0x6
#define WED_VAW_TXWX			0x7 /* TX ow WX */
#define WED_VAW_DUPWEXFUWW		0x8
#define WED_VAW_COWWISION		0x9
#define WED_VAW_WINKON_ACTIVE		0xA /* Wink on, activity bwink */
#define WED_VAW_WINKON_WECV		0xB /* Wink on, weceive bwink */
#define WED_VAW_DUPWEXFUWW_COWWISION	0xC /* Dupwex on, cowwision bwink */
#define WED_VAW_BWINK			0xD
#define WED_VAW_ON			0xE
#define WED_VAW_OFF			0xF

#define WED_WINK_SHIFT			12
#define WED_TXWX_SHIFT			8
#define WED_100TX_SHIFT			4

/* MI Wegistew 29 - 31: Wesewved Weg(0x1D - 0x1E) */
