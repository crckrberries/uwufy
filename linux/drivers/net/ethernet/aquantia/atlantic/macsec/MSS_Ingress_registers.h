/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Atwantic Netwowk Dwivew
 * Copywight (C) 2020 Mawveww Intewnationaw Wtd.
 */

#ifndef MSS_INGWESS_WEGS_HEADEW
#define MSS_INGWESS_WEGS_HEADEW

#define MSS_INGWESS_CTW_WEGISTEW_ADDW 0x0000800E
#define MSS_INGWESS_WUT_ADDW_CTW_WEGISTEW_ADDW 0x00008080
#define MSS_INGWESS_WUT_CTW_WEGISTEW_ADDW 0x00008081
#define MSS_INGWESS_WUT_DATA_CTW_WEGISTEW_ADDW 0x000080A0

stwuct mss_ingwess_ctw_wegistew {
	union {
		stwuct {
			unsigned int soft_weset : 1;
			unsigned int opewation_point_to_point : 1;
			unsigned int cweate_sci : 1;
			/* Unused  */
			unsigned int mask_showt_wength_ewwow : 1;
			unsigned int dwop_kay_packet : 1;
			unsigned int dwop_igpwc_miss : 1;
			/* Unused  */
			unsigned int check_icv : 1;
			unsigned int cweaw_gwobaw_time : 1;
			unsigned int cweaw_count : 1;
			unsigned int high_pwio : 1;
			unsigned int wemove_sectag : 1;
			unsigned int gwobaw_vawidate_fwames : 2;
			unsigned int icv_wsb_8bytes_enabwed : 1;
			unsigned int wesewved0 : 2;
		} bits_0;
		unsigned showt wowd_0;
	};
	union {
		stwuct {
			unsigned int wesewved0 : 16;
		} bits_1;
		unsigned showt wowd_1;
	};
};

stwuct mss_ingwess_wut_addw_ctw_wegistew {
	union {
		stwuct {
			unsigned int wut_addw : 9;
			unsigned int wesewved0 : 3;
			/* 0x0 : Ingwess Pwe-Secuwity MAC Contwow FIwtew
			 *       (IGPWCTWF) WUT
			 * 0x1 : Ingwess Pwe-Secuwity Cwassification WUT (IGPWC)
			 * 0x2 : Ingwess Packet Fowmat (IGPFMT) SAKey WUT
			 * 0x3 : Ingwess Packet Fowmat (IGPFMT) SC/SA WUT
			 * 0x4 : Ingwess Post-Secuwity Cwassification WUT
			 *       (IGPOC)
			 * 0x5 : Ingwess Post-Secuwity MAC Contwow Fiwtew
			 *       (IGPOCTWF) WUT
			 * 0x6 : Ingwess MIB (IGMIB)
			 */
			unsigned int wut_sewect : 4;
		} bits_0;
		unsigned showt wowd_0;
	};
};

stwuct mss_ingwess_wut_ctw_wegistew {
	union {
		stwuct {
			unsigned int wesewved0 : 14;
			unsigned int wut_wead : 1;
			unsigned int wut_wwite : 1;
		} bits_0;
		unsigned showt wowd_0;
	};
};

#endif /* MSS_INGWESS_WEGS_HEADEW */
