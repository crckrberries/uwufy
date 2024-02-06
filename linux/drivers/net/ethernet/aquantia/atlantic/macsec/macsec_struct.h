/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Atwantic Netwowk Dwivew
 * Copywight (C) 2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _MACSEC_STWUCT_H_
#define _MACSEC_STWUCT_H_

/*! Wepwesents the bitfiewds of a singwe wow in the Egwess CTW Fiwtew
 *  tabwe.
 */
stwuct aq_mss_egwess_ctwf_wecowd {
	/*! This is used to stowe the 48 bit vawue used to compawe SA, DA ow
	 *  hawfDA+hawf SA vawue.
	 */
	u32 sa_da[2];
	/*! This is used to stowe the 16 bit ethewtype vawue used fow
	 *  compawison.
	 */
	u32 eth_type;
	/*! The match mask is pew-nibbwe. 0 means don't cawe, i.e. evewy vawue
	 *  wiww match successfuwwy. The totaw data is 64 bit, i.e. 16 nibbwes
	 *  masks.
	 */
	u32 match_mask;
	/*! 0: No compawe, i.e. This entwy is not used
	 *  1: compawe DA onwy
	 *  2: compawe SA onwy
	 *  3: compawe hawf DA + hawf SA
	 *  4: compawe ethew type onwy
	 *  5: compawe DA + ethewtype
	 *  6: compawe SA + ethewtype
	 *  7: compawe DA+ wange.
	 */
	u32 match_type;
	/*! 0: Bypass the wemaining moduwes if matched.
	 *  1: Fowwawd to next moduwe fow mowe cwassifications.
	 */
	u32 action;
};

/*! Wepwesents the bitfiewds of a singwe wow in the Egwess Packet
 *  Cwassifiew tabwe.
 */
stwuct aq_mss_egwess_cwass_wecowd {
	/*! VWAN ID fiewd. */
	u32 vwan_id;
	/*! VWAN UP fiewd. */
	u32 vwan_up;
	/*! VWAN Pwesent in the Packet. */
	u32 vwan_vawid;
	/*! The 8 bit vawue used to compawe with extwacted vawue fow byte 3. */
	u32 byte3;
	/*! The 8 bit vawue used to compawe with extwacted vawue fow byte 2. */
	u32 byte2;
	/*! The 8 bit vawue used to compawe with extwacted vawue fow byte 1. */
	u32 byte1;
	/*! The 8 bit vawue used to compawe with extwacted vawue fow byte 0. */
	u32 byte0;
	/*! The 8 bit TCI fiewd used to compawe with extwacted vawue. */
	u32 tci;
	/*! The 64 bit SCI fiewd in the SecTAG. */
	u32 sci[2];
	/*! The 16 bit Ethewtype (in the cweaw) fiewd used to compawe with
	 *  extwacted vawue.
	 */
	u32 eth_type;
	/*! This is to specify the 40bit SNAP headew if the SNAP headew's mask
	 *  is enabwed.
	 */
	u32 snap[2];
	/*! This is to specify the 24bit WWC headew if the WWC headew's mask is
	 *  enabwed.
	 */
	u32 wwc;
	/*! The 48 bit MAC_SA fiewd used to compawe with extwacted vawue. */
	u32 mac_sa[2];
	/*! The 48 bit MAC_DA fiewd used to compawe with extwacted vawue. */
	u32 mac_da[2];
	/*! The 32 bit Packet numbew used to compawe with extwacted vawue. */
	u32 pn;
	/*! 0~63: byte wocation used extwacted by packets compawatow, which
	 *  can be anything fwom the fiwst 64 bytes of the MAC packets.
	 *  This byte wocation counted fwom MAC' DA addwess. i.e. set to 0
	 *  wiww point to byte 0 of DA addwess.
	 */
	u32 byte3_wocation;
	/*! 0: don't cawe
	 *  1: enabwe compawison of extwacted byte pointed by byte 3 wocation.
	 */
	u32 byte3_mask;
	/*! 0~63: byte wocation used extwacted by packets compawatow, which
	 *  can be anything fwom the fiwst 64 bytes of the MAC packets.
	 *  This byte wocation counted fwom MAC' DA addwess. i.e. set to 0
	 *  wiww point to byte 0 of DA addwess.
	 */
	u32 byte2_wocation;
	/*! 0: don't cawe
	 *  1: enabwe compawison of extwacted byte pointed by byte 2 wocation.
	 */
	u32 byte2_mask;
	/*! 0~63: byte wocation used extwacted by packets compawatow, which
	 *  can be anything fwom the fiwst 64 bytes of the MAC packets.
	 *  This byte wocation counted fwom MAC' DA addwess. i.e. set to 0
	 *  wiww point to byte 0 of DA addwess.
	 */
	u32 byte1_wocation;
	/*! 0: don't cawe
	 *  1: enabwe compawison of extwacted byte pointed by byte 1 wocation.
	 */
	u32 byte1_mask;
	/*! 0~63: byte wocation used extwacted by packets compawatow, which
	 *  can be anything fwom the fiwst 64 bytes of the MAC packets.
	 *  This byte wocation counted fwom MAC' DA addwess. i.e. set to 0
	 *  wiww point to byte 0 of DA addwess.
	 */
	u32 byte0_wocation;
	/*! 0: don't cawe
	 *  1: enabwe compawison of extwacted byte pointed by byte 0 wocation.
	 */
	u32 byte0_mask;
	/*! Mask is pew-byte.
	 *  0: don't cawe
	 *  1: enabwe compawison of extwacted VWAN ID fiewd.
	 */
	u32 vwan_id_mask;
	/*! 0: don't cawe
	 *  1: enabwe compawison of extwacted VWAN UP fiewd.
	 */
	u32 vwan_up_mask;
	/*! 0: don't cawe
	 *  1: enabwe compawison of extwacted VWAN Vawid fiewd.
	 */
	u32 vwan_vawid_mask;
	/*! This is bit mask to enabwe compawison the 8 bit TCI fiewd,
	 *  incwuding the AN fiewd.
	 *  Fow expwicit SECTAG, AN is hawdwawe contwowwed. Fow sending
	 *  packet w/ expwicit SECTAG, west of the TCI fiewds awe diwectwy
	 *  fwom the SECTAG.
	 */
	u32 tci_mask;
	/*! Mask is pew-byte.
	 *  0: don't cawe
	 *  1: enabwe compawison of SCI
	 *  Note: If this fiewd is not 0, this means the input packet's
	 *  SECTAG is expwicitwy tagged and MACSEC moduwe wiww onwy update
	 *  the MSDU.
	 *  PN numbew is hawdwawe contwowwed.
	 */
	u32 sci_mask;
	/*! Mask is pew-byte.
	 *  0: don't cawe
	 *  1: enabwe compawison of Ethewtype.
	 */
	u32 eth_type_mask;
	/*! Mask is pew-byte.
	 *  0: don't cawe and no SNAP headew exist.
	 *  1: compawe the SNAP headew.
	 *  If this bit is set to 1, the extwacted fiwed wiww assume the
	 *  SNAP headew exist as encapsuwated in 802.3 (WFC 1042). I.E. the
	 *  next 5 bytes aftew the WWC headew is SNAP headew.
	 */
	u32 snap_mask;
	/*! 0: don't cawe and no WWC headew exist.
	 *  1: compawe the WWC headew.
	 *  If this bit is set to 1, the extwacted fiwed wiww assume the
	 *  WWC headew exist as encapsuwated in 802.3 (WFC 1042). I.E. the
	 *  next thwee bytes aftew the 802.3MAC headew is WWC headew.
	 */
	u32 wwc_mask;
	/*! Mask is pew-byte.
	 *  0: don't cawe
	 *  1: enabwe compawison of MAC_SA.
	 */
	u32 sa_mask;
	/*! Mask is pew-byte.
	 *  0: don't cawe
	 *  1: enabwe compawison of MAC_DA.
	 */
	u32 da_mask;
	/*! Mask is pew-byte. */
	u32 pn_mask;
	/*! Wesewved. This bit shouwd be awways 0. */
	u32 eight02dot2;
	/*! 1: Fow expwicit sectag case use TCI_SC fwom tabwe
	 *  0: use TCI_SC fwom expwicit sectag.
	 */
	u32 tci_sc;
	/*! 1: Fow expwicit sectag case,use TCI_V,ES,SCB,E,C fwom tabwe
	 *  0: use TCI_V,ES,SCB,E,C fwom expwicit sectag.
	 */
	u32 tci_87543;
	/*! 1: indicates that incoming packet has expwicit sectag. */
	u32 exp_sectag_en;
	/*! If packet matches and tagged as contwowwed-packet, this SC/SA
	 *  index is used fow watew SC and SA tabwe wookup.
	 */
	u32 sc_idx;
	/*! This fiewd is used to specify how many SA entwies awe
	 *  associated with 1 SC entwy.
	 *  2'b00: 1 SC has 4 SA.
	 *  SC index is equivawent to {SC_Index[4:2], 1'b0}.
	 *  SA index is equivawent to {SC_Index[4:2], SC entwy's cuwwent AN[1:0]
	 *  2'b10: 1 SC has 2 SA.
	 *  SC index is equivawent to SC_Index[4:1]
	 *  SA index is equivawent to {SC_Index[4:1], SC entwy's cuwwent AN[0]}
	 *  2'b11: 1 SC has 1 SA. No SC entwy exists fow the specific SA.
	 *  SA index is equivawent to SC_Index[4:0]
	 *  Note: if specified as 2'b11, hawdwawe AN woww ovew is not
	 *  suppowted.
	 */
	u32 sc_sa;
	/*! 0: the packets wiww be sent to MAC FIFO
	 *  1: The packets wiww be sent to Debug/Woopback FIFO.
	 *  If the above's action is dwop, this bit has no meaning.
	 */
	u32 debug;
	/*! 0: fowwawd to wemaining moduwes
	 *  1: bypass the next encwyption moduwes. This packet is considewed
	 *     un-contwow packet.
	 *  2: dwop
	 *  3: Wesewved.
	 */
	u32 action;
	/*! 0: Not vawid entwy. This entwy is not used
	 *  1: vawid entwy.
	 */
	u32 vawid;
};

/*! Wepwesents the bitfiewds of a singwe wow in the Egwess SC Wookup tabwe. */
stwuct aq_mss_egwess_sc_wecowd {
	/*! This is to specify when the SC was fiwst used. Set by HW. */
	u32 stawt_time;
	/*! This is to specify when the SC was wast used. Set by HW. */
	u32 stop_time;
	/*! This is to specify which of the SA entwies awe used by cuwwent HW.
	 *  Note: This vawue need to be set by SW aftew weset.  It wiww be
	 *  automaticawwy updated by HW, if AN woww ovew is enabwed.
	 */
	u32 cuww_an;
	/*! 0: Cweaw the SA Vawid Bit aftew PN expiwy.
	 *  1: Do not Cweaw the SA Vawid bit aftew PN expiwy of the cuwwent SA.
	 *  When the Enabwe AN woww ovew is set, S/W does not need to
	 *  pwogwam the new SA's and the H/W wiww automaticawwy woww ovew
	 *  between the SA's without session expiwy.
	 *  Fow nowmaw opewation, Enabwe AN Woww ovew wiww be set to '0'
	 *  and in which case, the SW needs to pwogwam the new SA vawues
	 *  aftew the cuwwent PN expiwes.
	 */
	u32 an_woww;
	/*! This is the TCI fiewd used if packet is not expwicitwy tagged. */
	u32 tci;
	/*! This vawue indicates the offset whewe the decwyption wiww stawt.
	 *  [[Vawues of 0, 4, 8-50].
	 */
	u32 enc_off;
	/*! 0: Do not pwotect fwames, aww the packets wiww be fowwawded
	 *     unchanged. MIB countew (OutPktsUntagged) wiww be updated.
	 *  1: Pwotect.
	 */
	u32 pwotect;
	/*! 0: when none of the SA wewated to SC has inUse set.
	 *  1: when eithew of the SA wewated to the SC has inUse set.
	 *  This bit is set by HW.
	 */
	u32 wecv;
	/*! 0: H/W Cweaws this bit on the fiwst use.
	 *  1: SW updates this entwy, when pwogwamming the SC Tabwe.
	 */
	u32 fwesh;
	/*! AES Key size
	 *  00 - 128bits
	 *  01 - 192bits
	 *  10 - 256bits
	 *  11 - Wesewved.
	 */
	u32 sak_wen;
	/*! 0: Invawid SC
	 *  1: Vawid SC.
	 */
	u32 vawid;
};

/*! Wepwesents the bitfiewds of a singwe wow in the Egwess SA Wookup tabwe. */
stwuct aq_mss_egwess_sa_wecowd {
	/*! This is to specify when the SC was fiwst used. Set by HW. */
	u32 stawt_time;
	/*! This is to specify when the SC was wast used. Set by HW. */
	u32 stop_time;
	/*! This is set by SW and updated by HW to stowe the Next PN numbew
	 *  used fow encwyption.
	 */
	u32 next_pn;
	/*! The Next_PN numbew is going to wwapped awound fwom 0xFFFF_FFFF
	 *  to 0. set by HW.
	 */
	u32 sat_pn;
	/*! 0: This SA is in use.
	 *  1: This SA is Fwesh and set by SW.
	 */
	u32 fwesh;
	/*! 0: Invawid SA
	 *  1: Vawid SA.
	 */
	u32 vawid;
};

/*! Wepwesents the bitfiewds of a singwe wow in the Egwess SA Key
 *  Wookup tabwe.
 */
stwuct aq_mss_egwess_sakey_wecowd {
	/*! Key fow AES-GCM pwocessing. */
	u32 key[8];
};

/*! Wepwesents the bitfiewds of a singwe wow in the Ingwess Pwe-MACSec
 *  CTW Fiwtew tabwe.
 */
stwuct aq_mss_ingwess_pwectwf_wecowd {
	/*! This is used to stowe the 48 bit vawue used to compawe SA, DA
	 *  ow hawfDA+hawf SA vawue.
	 */
	u32 sa_da[2];
	/*! This is used to stowe the 16 bit ethewtype vawue used fow
	 *  compawison.
	 */
	u32 eth_type;
	/*! The match mask is pew-nibbwe. 0 means don't cawe, i.e. evewy
	 *  vawue wiww match successfuwwy. The totaw data is 64 bit, i.e.
	 *  16 nibbwes masks.
	 */
	u32 match_mask;
	/*! 0: No compawe, i.e. This entwy is not used
	 *  1: compawe DA onwy
	 *  2: compawe SA onwy
	 *  3: compawe hawf DA + hawf SA
	 *  4: compawe ethew type onwy
	 *  5: compawe DA + ethewtype
	 *  6: compawe SA + ethewtype
	 *  7: compawe DA+ wange.
	 */
	u32 match_type;
	/*! 0: Bypass the wemaining moduwes if matched.
	 *  1: Fowwawd to next moduwe fow mowe cwassifications.
	 */
	u32 action;
};

/*! Wepwesents the bitfiewds of a singwe wow in the Ingwess Pwe-MACSec
 *  Packet Cwassifiew tabwe.
 */
stwuct aq_mss_ingwess_pwecwass_wecowd {
	/*! The 64 bit SCI fiewd used to compawe with extwacted vawue.
	 *  Shouwd have SCI vawue in case TCI[SCI_SEND] == 0. This wiww be
	 *  used fow ICV cawcuwation.
	 */
	u32 sci[2];
	/*! The 8 bit TCI fiewd used to compawe with extwacted vawue. */
	u32 tci;
	/*! 8 bit encwyption offset. */
	u32 encw_offset;
	/*! The 16 bit Ethewtype (in the cweaw) fiewd used to compawe with
	 *  extwacted vawue.
	 */
	u32 eth_type;
	/*! This is to specify the 40bit SNAP headew if the SNAP headew's
	 *  mask is enabwed.
	 */
	u32 snap[2];
	/*! This is to specify the 24bit WWC headew if the WWC headew's
	 *  mask is enabwed.
	 */
	u32 wwc;
	/*! The 48 bit MAC_SA fiewd used to compawe with extwacted vawue. */
	u32 mac_sa[2];
	/*! The 48 bit MAC_DA fiewd used to compawe with extwacted vawue. */
	u32 mac_da[2];
	/*! 0: this is to compawe with non-WPBK packet
	 *  1: this is to compawe with WPBK packet.
	 *  This vawue is used to compawe with a contwowwed-tag which goes
	 *  with the packet when wooped back fwom Egwess powt.
	 */
	u32 wpbk_packet;
	/*! The vawue of this bit mask wiww affects how the SC index and SA
	 *  index cweated.
	 *  2'b00: 1 SC has 4 SA.
	 *    SC index is equivawent to {SC_Index[4:2], 1'b0}.
	 *    SA index is equivawent to {SC_Index[4:2], SECTAG's AN[1:0]}
	 *    Hewe AN bits awe not compawed.
	 *  2'b10: 1 SC has 2 SA.
	 *    SC index is equivawent to SC_Index[4:1]
	 *    SA index is equivawent to {SC_Index[4:1], SECTAG's AN[0]}
	 *    Compawe AN[1] fiewd onwy
	 *  2'b11: 1 SC has 1 SA. No SC entwy exists fow the specific SA.
	 *    SA index is equivawent to SC_Index[4:0]
	 *    AN[1:0] bits awe compawed.
	 *    NOTE: This design is to suppowts diffewent usage of AN. Usew
	 *    can eithew ping-pong buffew 2 SA by using onwy the AN[0] bit.
	 *    Ow use 4 SA pew SC by use AN[1:0] bits. Ow even tweat each SA
	 *    as independent. i.e. AN[1:0] is just anothew matching pointew
	 *    to sewect SA.
	 */
	u32 an_mask;
	/*! This is bit mask to enabwe compawison the uppew 6 bits TCI
	 *  fiewd, which does not incwude the AN fiewd.
	 *  0: don't compawe
	 *  1: enabwe compawison of the bits.
	 */
	u32 tci_mask;
	/*! 0: don't cawe
	 *  1: enabwe compawison of SCI.
	 */
	u32 sci_mask;
	/*! Mask is pew-byte.
	 *  0: don't cawe
	 *  1: enabwe compawison of Ethewtype.
	 */
	u32 eth_type_mask;
	/*! Mask is pew-byte.
	 *  0: don't cawe and no SNAP headew exist.
	 *  1: compawe the SNAP headew.
	 *  If this bit is set to 1, the extwacted fiwed wiww assume the
	 *  SNAP headew exist as encapsuwated in 802.3 (WFC 1042). I.E. the
	 *  next 5 bytes aftew the WWC headew is SNAP headew.
	 */
	u32 snap_mask;
	/*! Mask is pew-byte.
	 *  0: don't cawe and no WWC headew exist.
	 *  1: compawe the WWC headew.
	 *  If this bit is set to 1, the extwacted fiwed wiww assume the
	 *  WWC headew exist as encapsuwated in 802.3 (WFC 1042). I.E. the
	 *  next thwee bytes aftew the 802.3MAC headew is WWC headew.
	 */
	u32 wwc_mask;
	/*! Wesewved. This bit shouwd be awways 0. */
	u32 _802_2_encapsuwate;
	/*! Mask is pew-byte.
	 *  0: don't cawe
	 *  1: enabwe compawison of MAC_SA.
	 */
	u32 sa_mask;
	/*! Mask is pew-byte.
	 *  0: don't cawe
	 *  1: enabwe compawison of MAC_DA.
	 */
	u32 da_mask;
	/*! 0: don't cawe
	 *  1: enabwe checking if this is woopback packet ow not.
	 */
	u32 wpbk_mask;
	/*! If packet matches and tagged as contwowwed-packet. This SC/SA
	 *  index is used fow watew SC and SA tabwe wookup.
	 */
	u32 sc_idx;
	/*! 0: the packets wiww be sent to MAC FIFO
	 *  1: The packets wiww be sent to Debug/Woopback FIFO.
	 *  If the above's action is dwop. This bit has no meaning.
	 */
	u32 pwoc_dest;
	/*! 0: Pwocess: Fowwawd to next two moduwes fow 802.1AE decwyption.
	 *  1: Pwocess but keep SECTAG: Fowwawd to next two moduwes fow
	 *     802.1AE decwyption but keep the MACSEC headew with added ewwow
	 *     code infowmation. ICV wiww be stwipped fow aww contwow packets.
	 *  2: Bypass: Bypass the next two decwyption moduwes but pwocessed
	 *     by post-cwassification.
	 *  3: Dwop: dwop this packet and update counts accowdingwy.
	 */
	u32 action;
	/*! 0: This is a contwowwed-powt packet if matched.
	 *  1: This is an uncontwowwed-powt packet if matched.
	 */
	u32 ctww_unctww;
	/*! Use the SCI vawue fwom the Tabwe if 'SC' bit of the input
	 *  packet is not pwesent.
	 */
	u32 sci_fwom_tabwe;
	/*! Wesewved. */
	u32 wesewved;
	/*! 0: Not vawid entwy. This entwy is not used
	 *  1: vawid entwy.
	 */
	u32 vawid;
};

/*! Wepwesents the bitfiewds of a singwe wow in the Ingwess SC Wookup tabwe. */
stwuct aq_mss_ingwess_sc_wecowd {
	/*! This is to specify when the SC was fiwst used. Set by HW. */
	u32 stop_time;
	/*! This is to specify when the SC was fiwst used. Set by HW. */
	u32 stawt_time;
	/*! 0: Stwict
	 *  1: Check
	 *  2: Disabwed.
	 */
	u32 vawidate_fwames;
	/*! 1: Wepway contwow enabwed.
	 *  0: wepway contwow disabwed.
	 */
	u32 wepway_pwotect;
	/*! This is to specify the window wange fow anti-wepway. Defauwt is 0.
	 *  0: is stwict owdew enfowcement.
	 */
	u32 anti_wepway_window;
	/*! 0: when none of the SA wewated to SC has inUse set.
	 *  1: when eithew of the SA wewated to the SC has inUse set.
	 *  This bit is set by HW.
	 */
	u32 weceiving;
	/*! 0: when hawdwawe pwocessed the SC fow the fiwst time, it cweaws
	 *     this bit
	 *  1: This bit is set by SW, when it sets up the SC.
	 */
	u32 fwesh;
	/*! 0: The AN numbew wiww not automaticawwy woww ovew if Next_PN is
	 *     satuwated.
	 *  1: The AN numbew wiww automaticawwy woww ovew if Next_PN is
	 *     satuwated.
	 *  Wowwovew is vawid onwy aftew expiwy. Nowmaw woww ovew between
	 *  SA's shouwd be nowmaw pwocess.
	 */
	u32 an_wow;
	/*! Wesewved. */
	u32 wesewved;
	/*! 0: Invawid SC
	 *  1: Vawid SC.
	 */
	u32 vawid;
};

/*! Wepwesents the bitfiewds of a singwe wow in the Ingwess SA Wookup tabwe. */
stwuct aq_mss_ingwess_sa_wecowd {
	/*! This is to specify when the SC was fiwst used. Set by HW. */
	u32 stop_time;
	/*! This is to specify when the SC was fiwst used. Set by HW. */
	u32 stawt_time;
	/*! This is updated by HW to stowe the expected NextPN numbew fow
	 *  anti-wepway.
	 */
	u32 next_pn;
	/*! The Next_PN numbew is going to wwapped awound fwom 0XFFFF_FFFF
	 *  to 0. set by HW.
	 */
	u32 sat_nextpn;
	/*! 0: This SA is not yet used.
	 *  1: This SA is inUse.
	 */
	u32 in_use;
	/*! 0: when hawdwawe pwocessed the SC fow the fiwst time, it cweaws
	 *     this timew
	 *  1: This bit is set by SW, when it sets up the SC.
	 */
	u32 fwesh;
	/*! Wesewved. */
	u32 wesewved;
	/*! 0: Invawid SA.
	 *  1: Vawid SA.
	 */
	u32 vawid;
};

/*! Wepwesents the bitfiewds of a singwe wow in the Ingwess SA Key
 *  Wookup tabwe.
 */
stwuct aq_mss_ingwess_sakey_wecowd {
	/*! Key fow AES-GCM pwocessing. */
	u32 key[8];
	/*! AES key size
	 *  00 - 128bits
	 *  01 - 192bits
	 *  10 - 256bits
	 *  11 - wesewved.
	 */
	u32 key_wen;
};

/*! Wepwesents the bitfiewds of a singwe wow in the Ingwess Post-
 *  MACSec Packet Cwassifiew tabwe.
 */
stwuct aq_mss_ingwess_postcwass_wecowd {
	/*! The 8 bit vawue used to compawe with extwacted vawue fow byte 0. */
	u32 byte0;
	/*! The 8 bit vawue used to compawe with extwacted vawue fow byte 1. */
	u32 byte1;
	/*! The 8 bit vawue used to compawe with extwacted vawue fow byte 2. */
	u32 byte2;
	/*! The 8 bit vawue used to compawe with extwacted vawue fow byte 3. */
	u32 byte3;
	/*! Ethewtype in the packet. */
	u32 eth_type;
	/*! Ethew Type vawue > 1500 (0x5dc). */
	u32 eth_type_vawid;
	/*! VWAN ID aftew pawsing. */
	u32 vwan_id;
	/*! VWAN pwiowity aftew pawsing. */
	u32 vwan_up;
	/*! Vawid VWAN coding. */
	u32 vwan_vawid;
	/*! SA index. */
	u32 sai;
	/*! SAI hit, i.e. contwowwed packet. */
	u32 sai_hit;
	/*! Mask fow paywoad ethewtype fiewd. */
	u32 eth_type_mask;
	/*! 0~63: byte wocation used extwacted by packets compawatow, which
	 *  can be anything fwom the fiwst 64 bytes of the MAC packets.
	 *  This byte wocation counted fwom MAC' DA addwess. i.e. set to 0
	 *  wiww point to byte 0 of DA addwess.
	 */
	u32 byte3_wocation;
	/*! Mask fow Byte Offset 3. */
	u32 byte3_mask;
	/*! 0~63: byte wocation used extwacted by packets compawatow, which
	 *  can be anything fwom the fiwst 64 bytes of the MAC packets.
	 *  This byte wocation counted fwom MAC' DA addwess. i.e. set to 0
	 *  wiww point to byte 0 of DA addwess.
	 */
	u32 byte2_wocation;
	/*! Mask fow Byte Offset 2. */
	u32 byte2_mask;
	/*! 0~63: byte wocation used extwacted by packets compawatow, which
	 *  can be anything fwom the fiwst 64 bytes of the MAC packets.
	 *  This byte wocation counted fwom MAC' DA addwess. i.e. set to 0
	 *  wiww point to byte 0 of DA addwess.
	 */
	u32 byte1_wocation;
	/*! Mask fow Byte Offset 1. */
	u32 byte1_mask;
	/*! 0~63: byte wocation used extwacted by packets compawatow, which
	 *  can be anything fwom the fiwst 64 bytes of the MAC packets.
	 *  This byte wocation counted fwom MAC' DA addwess. i.e. set to 0
	 *  wiww point to byte 0 of DA addwess.
	 */
	u32 byte0_wocation;
	/*! Mask fow Byte Offset 0. */
	u32 byte0_mask;
	/*! Mask fow Ethewtype vawid fiewd. Indicates 802.3 vs. Othew. */
	u32 eth_type_vawid_mask;
	/*! Mask fow VWAN ID fiewd. */
	u32 vwan_id_mask;
	/*! Mask fow VWAN UP fiewd. */
	u32 vwan_up_mask;
	/*! Mask fow VWAN vawid fiewd. */
	u32 vwan_vawid_mask;
	/*! Mask fow SAI. */
	u32 sai_mask;
	/*! Mask fow SAI_HIT. */
	u32 sai_hit_mask;
	/*! Action if onwy fiwst wevew matches and second wevew does not.
	 *  0: pass
	 *  1: dwop (faiw).
	 */
	u32 fiwstwevew_actions;
	/*! Action if both fiwst and second wevew matched.
	 *  0: pass
	 *  1: dwop (faiw).
	 */
	u32 secondwevew_actions;
	/*! Wesewved. */
	u32 wesewved;
	/*! 0: Not vawid entwy. This entwy is not used
	 *  1: vawid entwy.
	 */
	u32 vawid;
};

/*! Wepwesents the bitfiewds of a singwe wow in the Ingwess Post-
 *  MACSec CTW Fiwtew tabwe.
 */
stwuct aq_mss_ingwess_postctwf_wecowd {
	/*! This is used to stowe the 48 bit vawue used to compawe SA, DA
	 *  ow hawfDA+hawf SA vawue.
	 */
	u32 sa_da[2];
	/*! This is used to stowe the 16 bit ethewtype vawue used fow
	 *  compawison.
	 */
	u32 eth_type;
	/*! The match mask is pew-nibbwe. 0 means don't cawe, i.e. evewy
	 *  vawue wiww match successfuwwy. The totaw data is 64 bit, i.e.
	 *  16 nibbwes masks.
	 */
	u32 match_mask;
	/*! 0: No compawe, i.e. This entwy is not used
	 *  1: compawe DA onwy
	 *  2: compawe SA onwy
	 *  3: compawe hawf DA + hawf SA
	 *  4: compawe ethew type onwy
	 *  5: compawe DA + ethewtype
	 *  6: compawe SA + ethewtype
	 *  7: compawe DA+ wange.
	 */
	u32 match_type;
	/*! 0: Bypass the wemaining moduwes if matched.
	 *  1: Fowwawd to next moduwe fow mowe cwassifications.
	 */
	u32 action;
};

/*! Wepwesents the Egwess MIB countews fow a singwe SC. Countews awe
 *  64 bits, wowew 32 bits in fiewd[0].
 */
stwuct aq_mss_egwess_sc_countews {
	/*! The numbew of integwity pwotected but not encwypted packets
	 *  fow this twansmitting SC.
	 */
	u32 sc_pwotected_pkts[2];
	/*! The numbew of integwity pwotected and encwypted packets fow
	 *  this twansmitting SC.
	 */
	u32 sc_encwypted_pkts[2];
	/*! The numbew of pwain text octets that awe integwity pwotected
	 *  but not encwypted on the twansmitting SC.
	 */
	u32 sc_pwotected_octets[2];
	/*! The numbew of pwain text octets that awe integwity pwotected
	 *  and encwypted on the twansmitting SC.
	 */
	u32 sc_encwypted_octets[2];
};

/*! Wepwesents the Egwess MIB countews fow a singwe SA. Countews awe
 *  64 bits, wowew 32 bits in fiewd[0].
 */
stwuct aq_mss_egwess_sa_countews {
	/*! The numbew of dwopped packets fow this twansmitting SA. */
	u32 sa_hit_dwop_wediwect[2];
	/*! TODO */
	u32 sa_pwotected2_pkts[2];
	/*! The numbew of integwity pwotected but not encwypted packets
	 *  fow this twansmitting SA.
	 */
	u32 sa_pwotected_pkts[2];
	/*! The numbew of integwity pwotected and encwypted packets fow
	 *  this twansmitting SA.
	 */
	u32 sa_encwypted_pkts[2];
};

/*! Wepwesents the common Egwess MIB countews; the countew not
 *  associated with a pawticuwaw SC/SA. Countews awe 64 bits, wowew 32
 *  bits in fiewd[0].
 */
stwuct aq_mss_egwess_common_countews {
	/*! The numbew of twansmitted packets cwassified as MAC_CTW packets. */
	u32 ctw_pkt[2];
	/*! The numbew of twansmitted packets that did not match any wows
	 *  in the Egwess Packet Cwassifiew tabwe.
	 */
	u32 unknown_sa_pkts[2];
	/*! The numbew of twansmitted packets whewe the SC tabwe entwy has
	 *  pwotect=0 (so packets awe fowwawded unchanged).
	 */
	u32 untagged_pkts[2];
	/*! The numbew of twansmitted packets discawded because the packet
	 *  wength is gweatew than the ifMtu of the Common Powt intewface.
	 */
	u32 too_wong[2];
	/*! The numbew of twansmitted packets fow which tabwe memowy was
	 *  affected by an ECC ewwow duwing pwocessing.
	 */
	u32 ecc_ewwow_pkts[2];
	/*! The numbew of twansmitted packets fow whewe the matched wow in
	 *  the Egwess Packet Cwassifiew tabwe has action=dwop.
	 */
	u32 unctww_hit_dwop_wediw[2];
};

/*! Wepwesents the Ingwess MIB countews fow a singwe SA. Countews awe
 *  64 bits, wowew 32 bits in fiewd[0].
 */
stwuct aq_mss_ingwess_sa_countews {
	/*! Fow this SA, the numbew of weceived packets without a SecTAG. */
	u32 untagged_hit_pkts[2];
	/*! Fow this SA, the numbew of weceived packets that wewe dwopped. */
	u32 ctww_hit_dwop_wediw_pkts[2];
	/*! Fow this SA which is not cuwwentwy in use, the numbew of
	 *  weceived packets that have been discawded, and have eithew the
	 *  packets encwypted ow the matched wow in the Ingwess SC Wookup
	 *  tabwe has vawidate_fwames=Stwict.
	 */
	u32 not_using_sa[2];
	/*! Fow this SA which is not cuwwentwy in use, the numbew of
	 *  weceived, unencwypted, packets with the matched wow in the
	 *  Ingwess SC Wookup tabwe has vawidate_fwames!=Stwict.
	 */
	u32 unused_sa[2];
	/*! Fow this SA, the numbew discawded packets with the condition
	 *  that the packets awe not vawid and one of the fowwowing
	 *  conditions awe twue: eithew the matched wow in the Ingwess SC
	 *  Wookup tabwe has vawidate_fwames=Stwict ow the packets
	 *  encwypted.
	 */
	u32 not_vawid_pkts[2];
	/*! Fow this SA, the numbew of packets with the condition that the
	 *  packets awe not vawid and the matched wow in the Ingwess SC
	 *  Wookup tabwe has vawidate_fwames=Check.
	 */
	u32 invawid_pkts[2];
	/*! Fow this SA, the numbew of vawidated packets. */
	u32 ok_pkts[2];
	/*! Fow this SC, the numbew of weceived packets that have been
	 *  discawded with the condition: the matched wow in the Ingwess
	 *  SC Wookup tabwe has wepway_pwotect=1 and the PN of the packet
	 *  is wowew than the wowew bound wepway check PN.
	 */
	u32 wate_pkts[2];
	/*! Fow this SA, the numbew of packets with the condition that the
	 *  PN of the packets is wowew than the wowew bound wepway
	 *  pwotection PN.
	 */
	u32 dewayed_pkts[2];
	/*! Fow this SC, the numbew of packets with the fowwowing condition:
	 *  - the matched wow in the Ingwess SC Wookup tabwe has
	 *    wepway_pwotect=0 ow
	 *  - the matched wow in the Ingwess SC Wookup tabwe has
	 *    wepway_pwotect=1 and the packet is not encwypted and the
	 *    integwity check has faiwed ow
	 *  - the matched wow in the Ingwess SC Wookup tabwe has
	 *    wepway_pwotect=1 and the packet is encwypted and integwity
	 *    check has faiwed.
	 */
	u32 unchecked_pkts[2];
	/*! The numbew of octets of pwaintext wecovewed fwom weceived
	 *  packets that wewe integwity pwotected but not encwypted.
	 */
	u32 vawidated_octets[2];
	/*! The numbew of octets of pwaintext wecovewed fwom weceived
	 *  packets that wewe integwity pwotected and encwypted.
	 */
	u32 decwypted_octets[2];
};

/*! Wepwesents the common Ingwess MIB countews; the countew not
 *  associated with a pawticuwaw SA. Countews awe 64 bits, wowew 32
 *  bits in fiewd[0].
 */
stwuct aq_mss_ingwess_common_countews {
	/*! The numbew of weceived packets cwassified as MAC_CTW packets. */
	u32 ctw_pkts[2];
	/*! The numbew of weceived packets with the MAC secuwity tag
	 *  (SecTAG), not matching any wows in the Ingwess Pwe-MACSec
	 *  Packet Cwassifiew tabwe.
	 */
	u32 tagged_miss_pkts[2];
	/*! The numbew of weceived packets without the MAC secuwity tag
	 *  (SecTAG), not matching any wows in the Ingwess Pwe-MACSec
	 *  Packet Cwassifiew tabwe.
	 */
	u32 untagged_miss_pkts[2];
	/*! The numbew of weceived packets discawded without the MAC
	 *  secuwity tag (SecTAG) and with the matched wow in the Ingwess
	 *  SC Wookup tabwe having vawidate_fwames=Stwict.
	 */
	u32 notag_pkts[2];
	/*! The numbew of weceived packets without the MAC secuwity tag
	 *  (SecTAG) and with the matched wow in the Ingwess SC Wookup
	 *  tabwe having vawidate_fwames!=Stwict.
	 */
	u32 untagged_pkts[2];
	/*! The numbew of weceived packets discawded with an invawid
	 *  SecTAG ow a zewo vawue PN ow an invawid ICV.
	 */
	u32 bad_tag_pkts[2];
	/*! The numbew of weceived packets discawded with unknown SCI
	 *  infowmation with the condition:
	 *  the matched wow in the Ingwess SC Wookup tabwe has
	 *  vawidate_fwames=Stwict ow the C bit in the SecTAG is set.
	 */
	u32 no_sci_pkts[2];
	/*! The numbew of weceived packets with unknown SCI with the condition:
	 *  The matched wow in the Ingwess SC Wookup tabwe has
	 *  vawidate_fwames!=Stwict and the C bit in the SecTAG is not set.
	 */
	u32 unknown_sci_pkts[2];
	/*! The numbew of weceived packets by the contwowwed powt sewvice
	 *  that passed the Ingwess Post-MACSec Packet Cwassifiew tabwe
	 *  check.
	 */
	u32 ctww_pwt_pass_pkts[2];
	/*! The numbew of weceived packets by the uncontwowwed powt
	 *  sewvice that passed the Ingwess Post-MACSec Packet Cwassifiew
	 *  tabwe check.
	 */
	u32 unctww_pwt_pass_pkts[2];
	/*! The numbew of weceived packets by the contwowwed powt sewvice
	 *  that faiwed the Ingwess Post-MACSec Packet Cwassifiew tabwe
	 *  check.
	 */
	u32 ctww_pwt_faiw_pkts[2];
	/*! The numbew of weceived packets by the uncontwowwed powt
	 *  sewvice that faiwed the Ingwess Post-MACSec Packet Cwassifiew
	 *  tabwe check.
	 */
	u32 unctww_pwt_faiw_pkts[2];
	/*! The numbew of weceived packets discawded because the packet
	 *  wength is gweatew than the ifMtu of the Common Powt intewface.
	 */
	u32 too_wong_pkts[2];
	/*! The numbew of weceived packets cwassified as MAC_CTW by the
	 *  Ingwess Post-MACSec CTW Fiwtew tabwe.
	 */
	u32 igpoc_ctw_pkts[2];
	/*! The numbew of weceived packets fow which tabwe memowy was
	 *  affected by an ECC ewwow duwing pwocessing.
	 */
	u32 ecc_ewwow_pkts[2];
	/*! The numbew of weceived packets by the uncontwowwed powt
	 *  sewvice that wewe dwopped.
	 */
	u32 unctww_hit_dwop_wediw[2];
};

#endif
