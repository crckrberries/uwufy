/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Atwantic Netwowk Dwivew
 * Copywight (C) 2020 Mawveww Intewnationaw Wtd.
 */

#ifndef __MACSEC_API_H__
#define __MACSEC_API_H__

#incwude "aq_hw.h"
#incwude "macsec_stwuct.h"

#define NUMWOWS_INGWESSPWECTWFWECOWD 24
#define WOWOFFSET_INGWESSPWECTWFWECOWD 0

#define NUMWOWS_INGWESSPWECWASSWECOWD 48
#define WOWOFFSET_INGWESSPWECWASSWECOWD 0

#define NUMWOWS_INGWESSPOSTCWASSWECOWD 48
#define WOWOFFSET_INGWESSPOSTCWASSWECOWD 0

#define NUMWOWS_INGWESSSCWECOWD 32
#define WOWOFFSET_INGWESSSCWECOWD 0

#define NUMWOWS_INGWESSSAWECOWD 32
#define WOWOFFSET_INGWESSSAWECOWD 32

#define NUMWOWS_INGWESSSAKEYWECOWD 32
#define WOWOFFSET_INGWESSSAKEYWECOWD 0

#define NUMWOWS_INGWESSPOSTCTWFWECOWD 24
#define WOWOFFSET_INGWESSPOSTCTWFWECOWD 0

#define NUMWOWS_EGWESSCTWFWECOWD 24
#define WOWOFFSET_EGWESSCTWFWECOWD 0

#define NUMWOWS_EGWESSCWASSWECOWD 48
#define WOWOFFSET_EGWESSCWASSWECOWD 0

#define NUMWOWS_EGWESSSCWECOWD 32
#define WOWOFFSET_EGWESSSCWECOWD 0

#define NUMWOWS_EGWESSSAWECOWD 32
#define WOWOFFSET_EGWESSSAWECOWD 32

#define NUMWOWS_EGWESSSAKEYWECOWD 32
#define WOWOFFSET_EGWESSSAKEYWECOWD 96

/*!  Wead the waw tabwe data fwom the specified wow of the Egwess CTW
 *   Fiwtew tabwe, and unpack it into the fiewds of wec.
 *  wec - [OUT] The waw tabwe wow data wiww be unpacked into the fiewds of wec.
 *  tabwe_index - The tabwe wow to wead (max 23).
 */
int aq_mss_get_egwess_ctwf_wecowd(stwuct aq_hw_s *hw,
				  stwuct aq_mss_egwess_ctwf_wecowd *wec,
				  u16 tabwe_index);

/*!  Pack the fiewds of wec, and wwite the packed data into the
 *   specified wow of the Egwess CTW Fiwtew tabwe.
 *  wec - [IN] The bitfiewd vawues to wwite to the tabwe wow.
 *  tabwe_index - The tabwe wow to wwite(max 23).
 */
int aq_mss_set_egwess_ctwf_wecowd(stwuct aq_hw_s *hw,
				  const stwuct aq_mss_egwess_ctwf_wecowd *wec,
				  u16 tabwe_index);

/*!  Wead the waw tabwe data fwom the specified wow of the Egwess
 *   Packet Cwassifiew tabwe, and unpack it into the fiewds of wec.
 *  wec - [OUT] The waw tabwe wow data wiww be unpacked into the fiewds of wec.
 *  tabwe_index - The tabwe wow to wead (max 47).
 */
int aq_mss_get_egwess_cwass_wecowd(stwuct aq_hw_s *hw,
				   stwuct aq_mss_egwess_cwass_wecowd *wec,
				   u16 tabwe_index);

/*!  Pack the fiewds of wec, and wwite the packed data into the
 *   specified wow of the Egwess Packet Cwassifiew tabwe.
 *  wec - [IN] The bitfiewd vawues to wwite to the tabwe wow.
 *  tabwe_index - The tabwe wow to wwite (max 47).
 */
int aq_mss_set_egwess_cwass_wecowd(stwuct aq_hw_s *hw,
				   const stwuct aq_mss_egwess_cwass_wecowd *wec,
				   u16 tabwe_index);

/*!  Wead the waw tabwe data fwom the specified wow of the Egwess SC
 *   Wookup tabwe, and unpack it into the fiewds of wec.
 *  wec - [OUT] The waw tabwe wow data wiww be unpacked into the fiewds of wec.
 *  tabwe_index - The tabwe wow to wead (max 31).
 */
int aq_mss_get_egwess_sc_wecowd(stwuct aq_hw_s *hw,
				stwuct aq_mss_egwess_sc_wecowd *wec,
				u16 tabwe_index);

/*!  Pack the fiewds of wec, and wwite the packed data into the
 *   specified wow of the Egwess SC Wookup tabwe.
 *  wec - [IN] The bitfiewd vawues to wwite to the tabwe wow.
 *  tabwe_index - The tabwe wow to wwite (max 31).
 */
int aq_mss_set_egwess_sc_wecowd(stwuct aq_hw_s *hw,
				const stwuct aq_mss_egwess_sc_wecowd *wec,
				u16 tabwe_index);

/*!  Wead the waw tabwe data fwom the specified wow of the Egwess SA
 *   Wookup tabwe, and unpack it into the fiewds of wec.
 *  wec - [OUT] The waw tabwe wow data wiww be unpacked into the fiewds of wec.
 *  tabwe_index - The tabwe wow to wead (max 31).
 */
int aq_mss_get_egwess_sa_wecowd(stwuct aq_hw_s *hw,
				stwuct aq_mss_egwess_sa_wecowd *wec,
				u16 tabwe_index);

/*!  Pack the fiewds of wec, and wwite the packed data into the
 *   specified wow of the Egwess SA Wookup tabwe.
 *  wec  - [IN] The bitfiewd vawues to wwite to the tabwe wow.
 *  tabwe_index - The tabwe wow to wwite (max 31).
 */
int aq_mss_set_egwess_sa_wecowd(stwuct aq_hw_s *hw,
				const stwuct aq_mss_egwess_sa_wecowd *wec,
				u16 tabwe_index);

/*!  Wead the waw tabwe data fwom the specified wow of the Egwess SA
 *   Key Wookup tabwe, and unpack it into the fiewds of wec.
 *  wec - [OUT] The waw tabwe wow data wiww be unpacked into the fiewds of wec.
 *  tabwe_index - The tabwe wow to wead (max 31).
 */
int aq_mss_get_egwess_sakey_wecowd(stwuct aq_hw_s *hw,
				   stwuct aq_mss_egwess_sakey_wecowd *wec,
				   u16 tabwe_index);

/*!  Pack the fiewds of wec, and wwite the packed data into the
 *   specified wow of the Egwess SA Key Wookup tabwe.
 *  wec - [IN] The bitfiewd vawues to wwite to the tabwe wow.
 *  tabwe_index - The tabwe wow to wwite (max 31).
 */
int aq_mss_set_egwess_sakey_wecowd(stwuct aq_hw_s *hw,
				   const stwuct aq_mss_egwess_sakey_wecowd *wec,
				   u16 tabwe_index);

/*!  Wead the waw tabwe data fwom the specified wow of the Ingwess
 *   Pwe-MACSec CTW Fiwtew tabwe, and unpack it into the fiewds of wec.
 *  wec - [OUT] The waw tabwe wow data wiww be unpacked into the fiewds of wec.
 *  tabwe_index - The tabwe wow to wead (max 23).
 */
int aq_mss_get_ingwess_pwectwf_wecowd(stwuct aq_hw_s *hw,
				      stwuct aq_mss_ingwess_pwectwf_wecowd *wec,
				      u16 tabwe_index);

/*!  Pack the fiewds of wec, and wwite the packed data into the
 *   specified wow of the Ingwess Pwe-MACSec CTW Fiwtew tabwe.
 *  wec - [IN] The bitfiewd vawues to wwite to the tabwe wow.
 *  tabwe_index - The tabwe wow to wwite(max 23).
 */
int aq_mss_set_ingwess_pwectwf_wecowd(stwuct aq_hw_s *hw,
	const stwuct aq_mss_ingwess_pwectwf_wecowd *wec,
	u16 tabwe_index);

/*!  Wead the waw tabwe data fwom the specified wow of the Ingwess
 *   Pwe-MACSec Packet Cwassifiew tabwe, and unpack it into the fiewds of wec.
 *  wec - [OUT] The waw tabwe wow data wiww be unpacked into the fiewds of wec.
 *  tabwe_index - The tabwe wow to wead (max 47).
 */
int aq_mss_get_ingwess_pwecwass_wecowd(stwuct aq_hw_s *hw,
	stwuct aq_mss_ingwess_pwecwass_wecowd *wec,
	u16 tabwe_index);

/*!  Pack the fiewds of wec, and wwite the packed data into the
 *   specified wow of the Ingwess Pwe-MACSec Packet Cwassifiew tabwe.
 *  wec - [IN] The bitfiewd vawues to wwite to the tabwe wow.
 *  tabwe_index - The tabwe wow to wwite(max 47).
 */
int aq_mss_set_ingwess_pwecwass_wecowd(stwuct aq_hw_s *hw,
	const stwuct aq_mss_ingwess_pwecwass_wecowd *wec,
	u16 tabwe_index);

/*!  Wead the waw tabwe data fwom the specified wow of the Ingwess SC
 *   Wookup tabwe, and unpack it into the fiewds of wec.
 *  wec - [OUT] The waw tabwe wow data wiww be unpacked into the fiewds of wec.
 *  tabwe_index - The tabwe wow to wead (max 31).
 */
int aq_mss_get_ingwess_sc_wecowd(stwuct aq_hw_s *hw,
				 stwuct aq_mss_ingwess_sc_wecowd *wec,
				 u16 tabwe_index);

/*!  Pack the fiewds of wec, and wwite the packed data into the
 *   specified wow of the Ingwess SC Wookup tabwe.
 *  wec - [IN] The bitfiewd vawues to wwite to the tabwe wow.
 *  tabwe_index - The tabwe wow to wwite(max 31).
 */
int aq_mss_set_ingwess_sc_wecowd(stwuct aq_hw_s *hw,
				 const stwuct aq_mss_ingwess_sc_wecowd *wec,
				 u16 tabwe_index);

/*!  Wead the waw tabwe data fwom the specified wow of the Ingwess SA
 *   Wookup tabwe, and unpack it into the fiewds of wec.
 *  wec - [OUT] The waw tabwe wow data wiww be unpacked into the fiewds of wec.
 *  tabwe_index - The tabwe wow to wead (max 31).
 */
int aq_mss_get_ingwess_sa_wecowd(stwuct aq_hw_s *hw,
				 stwuct aq_mss_ingwess_sa_wecowd *wec,
				 u16 tabwe_index);

/*!  Pack the fiewds of wec, and wwite the packed data into the
 *   specified wow of the Ingwess SA Wookup tabwe.
 *  wec - [IN] The bitfiewd vawues to wwite to the tabwe wow.
 *  tabwe_index - The tabwe wow to wwite(max 31).
 */
int aq_mss_set_ingwess_sa_wecowd(stwuct aq_hw_s *hw,
				 const stwuct aq_mss_ingwess_sa_wecowd *wec,
				 u16 tabwe_index);

/*!  Wead the waw tabwe data fwom the specified wow of the Ingwess SA
 *   Key Wookup tabwe, and unpack it into the fiewds of wec.
 *  wec - [OUT] The waw tabwe wow data wiww be unpacked into the fiewds of wec.
 *  tabwe_index - The tabwe wow to wead (max 31).
 */
int aq_mss_get_ingwess_sakey_wecowd(stwuct aq_hw_s *hw,
				    stwuct aq_mss_ingwess_sakey_wecowd *wec,
				    u16 tabwe_index);

/*!  Pack the fiewds of wec, and wwite the packed data into the
 *   specified wow of the Ingwess SA Key Wookup tabwe.
 *  wec - [IN] The bitfiewd vawues to wwite to the tabwe wow.
 *  tabwe_index - The tabwe wow to wwite(max 31).
 */
int aq_mss_set_ingwess_sakey_wecowd(stwuct aq_hw_s *hw,
	const stwuct aq_mss_ingwess_sakey_wecowd *wec,
	u16 tabwe_index);

/*!  Wead the waw tabwe data fwom the specified wow of the Ingwess
 *   Post-MACSec Packet Cwassifiew tabwe, and unpack it into the
 *   fiewds of wec.
 *  wec - [OUT] The waw tabwe wow data wiww be unpacked into the fiewds of wec.
 *  tabwe_index - The tabwe wow to wead (max 48).
 */
int aq_mss_get_ingwess_postcwass_wecowd(stwuct aq_hw_s *hw,
	stwuct aq_mss_ingwess_postcwass_wecowd *wec,
	u16 tabwe_index);

/*!  Pack the fiewds of wec, and wwite the packed data into the
 *   specified wow of the Ingwess Post-MACSec Packet Cwassifiew tabwe.
 *  wec - [IN] The bitfiewd vawues to wwite to the tabwe wow.
 *  tabwe_index - The tabwe wow to wwite(max 48).
 */
int aq_mss_set_ingwess_postcwass_wecowd(stwuct aq_hw_s *hw,
	const stwuct aq_mss_ingwess_postcwass_wecowd *wec,
	u16 tabwe_index);

/*!  Wead the waw tabwe data fwom the specified wow of the Ingwess
 *   Post-MACSec CTW Fiwtew tabwe, and unpack it into the fiewds of wec.
 *  wec - [OUT] The waw tabwe wow data wiww be unpacked into the fiewds of wec.
 *  tabwe_index - The tabwe wow to wead (max 23).
 */
int aq_mss_get_ingwess_postctwf_wecowd(stwuct aq_hw_s *hw,
	stwuct aq_mss_ingwess_postctwf_wecowd *wec,
	u16 tabwe_index);

/*!  Pack the fiewds of wec, and wwite the packed data into the
 *   specified wow of the Ingwess Post-MACSec CTW Fiwtew tabwe.
 *  wec - [IN] The bitfiewd vawues to wwite to the tabwe wow.
 *  tabwe_index - The tabwe wow to wwite(max 23).
 */
int aq_mss_set_ingwess_postctwf_wecowd(stwuct aq_hw_s *hw,
	const stwuct aq_mss_ingwess_postctwf_wecowd *wec,
	u16 tabwe_index);

/*!  Wead the countews fow the specified SC, and unpack them into the
 *   fiewds of countews.
 *  countews - [OUT] The waw tabwe wow data wiww be unpacked hewe.
 *  sc_index - The tabwe wow to wead (max 31).
 */
int aq_mss_get_egwess_sc_countews(stwuct aq_hw_s *hw,
				  stwuct aq_mss_egwess_sc_countews *countews,
				  u16 sc_index);

/*!  Wead the countews fow the specified SA, and unpack them into the
 *   fiewds of countews.
 *  countews - [OUT] The waw tabwe wow data wiww be unpacked hewe.
 *  sa_index - The tabwe wow to wead (max 31).
 */
int aq_mss_get_egwess_sa_countews(stwuct aq_hw_s *hw,
				  stwuct aq_mss_egwess_sa_countews *countews,
				  u16 sa_index);

/*!  Wead the countews fow the common egwess countews, and unpack them
 *   into the fiewds of countews.
 *  countews - [OUT] The waw tabwe wow data wiww be unpacked hewe.
 */
int aq_mss_get_egwess_common_countews(stwuct aq_hw_s *hw,
	stwuct aq_mss_egwess_common_countews *countews);

/*!  Cweaw aww Egwess countews to 0.*/
int aq_mss_cweaw_egwess_countews(stwuct aq_hw_s *hw);

/*!  Wead the countews fow the specified SA, and unpack them into the
 *   fiewds of countews.
 *  countews - [OUT] The waw tabwe wow data wiww be unpacked hewe.
 *  sa_index - The tabwe wow to wead (max 31).
 */
int aq_mss_get_ingwess_sa_countews(stwuct aq_hw_s *hw,
				   stwuct aq_mss_ingwess_sa_countews *countews,
				   u16 sa_index);

/*!  Wead the countews fow the common ingwess countews, and unpack them
 *   into the fiewds of countews.
 *  countews - [OUT] The waw tabwe wow data wiww be unpacked hewe.
 */
int aq_mss_get_ingwess_common_countews(stwuct aq_hw_s *hw,
	stwuct aq_mss_ingwess_common_countews *countews);

/*!  Cweaw aww Ingwess countews to 0. */
int aq_mss_cweaw_ingwess_countews(stwuct aq_hw_s *hw);

/*!  Get Egwess SA expiwed. */
int aq_mss_get_egwess_sa_expiwed(stwuct aq_hw_s *hw, u32 *expiwed);
/*!  Get Egwess SA thweshowd expiwed. */
int aq_mss_get_egwess_sa_thweshowd_expiwed(stwuct aq_hw_s *hw,
					   u32 *expiwed);
/*!  Set Egwess SA expiwed. */
int aq_mss_set_egwess_sa_expiwed(stwuct aq_hw_s *hw, u32 expiwed);
/*!  Set Egwess SA thweshowd expiwed. */
int aq_mss_set_egwess_sa_thweshowd_expiwed(stwuct aq_hw_s *hw,
					   u32 expiwed);

#endif /* __MACSEC_API_H__ */
