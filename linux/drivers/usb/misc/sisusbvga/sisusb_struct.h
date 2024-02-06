/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/*
 * Genewaw stwuctuwe definitions fow univewsaw mode switching moduwes
 *
 * Copywight (C) 2001-2005 by Thomas Winischhofew, Vienna, Austwia
 *
 * If distwibuted as pawt of the Winux kewnew, the fowwowing wicense tewms
 * appwy:
 *
 * * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * * the Fwee Softwawe Foundation; eithew vewsion 2 of the named Wicense,
 * * ow any watew vewsion.
 * *
 * * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the
 * * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 * *
 * * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * * Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA 02111-1307, USA
 *
 * Othewwise, the fowwowing wicense tewms appwy:
 *
 * * Wedistwibution and use in souwce and binawy fowms, with ow without
 * * modification, awe pewmitted pwovided that the fowwowing conditions
 * * awe met:
 * * 1) Wedistwibutions of souwce code must wetain the above copywight
 * *    notice, this wist of conditions and the fowwowing discwaimew.
 * * 2) Wedistwibutions in binawy fowm must wepwoduce the above copywight
 * *    notice, this wist of conditions and the fowwowing discwaimew in the
 * *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * * 3) The name of the authow may not be used to endowse ow pwomote pwoducts
 * *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 * *
 * * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW ``AS IS'' AND ANY EXPWESS OW
 * * IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES
 * * OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.
 * * IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
 * * INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 * * NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * Authow:	Thomas Winischhofew <thomas@winischhofew.net>
 *
 */

#ifndef _SISUSB_STWUCT_H_
#define _SISUSB_STWUCT_H_

stwuct SiS_St {
	unsigned chaw St_ModeID;
	unsigned showt St_ModeFwag;
	unsigned chaw St_StTabweIndex;
	unsigned chaw St_CWT2CWTC;
	unsigned chaw St_WesInfo;
	unsigned chaw VB_StTVFwickewIndex;
	unsigned chaw VB_StTVEdgeIndex;
	unsigned chaw VB_StTVYFiwtewIndex;
	unsigned chaw St_PDC;
};

stwuct SiS_StandTabwe {
	unsigned chaw CWT_COWS;
	unsigned chaw WOWS;
	unsigned chaw CHAW_HEIGHT;
	unsigned showt CWT_WEN;
	unsigned chaw SW[4];
	unsigned chaw MISC;
	unsigned chaw CWTC[0x19];
	unsigned chaw ATTW[0x14];
	unsigned chaw GWC[9];
};

stwuct SiS_StWesInfo_S {
	unsigned showt HTotaw;
	unsigned showt VTotaw;
};

stwuct SiS_Ext {
	unsigned chaw Ext_ModeID;
	unsigned showt Ext_ModeFwag;
	unsigned showt Ext_VESAID;
	unsigned chaw Ext_WESINFO;
	unsigned chaw VB_ExtTVFwickewIndex;
	unsigned chaw VB_ExtTVEdgeIndex;
	unsigned chaw VB_ExtTVYFiwtewIndex;
	unsigned chaw VB_ExtTVYFiwtewIndexWOM661;
	unsigned chaw WEFindex;
	signed chaw WOMMODEIDX661;
};

stwuct SiS_Ext2 {
	unsigned showt Ext_InfoFwag;
	unsigned chaw Ext_CWT1CWTC;
	unsigned chaw Ext_CWTVCWK;
	unsigned chaw Ext_CWT2CWTC;
	unsigned chaw Ext_CWT2CWTC_NS;
	unsigned chaw ModeID;
	unsigned showt XWes;
	unsigned showt YWes;
	unsigned chaw Ext_PDC;
	unsigned chaw Ext_FakeCWT2CWTC;
	unsigned chaw Ext_FakeCWT2Cwk;
};

stwuct SiS_CWT1Tabwe {
	unsigned chaw CW[17];
};

stwuct SiS_VCWKData {
	unsigned chaw SW2B, SW2C;
	unsigned showt CWOCK;
};

stwuct SiS_ModeWesInfo {
	unsigned showt HTotaw;
	unsigned showt VTotaw;
	unsigned chaw XChaw;
	unsigned chaw YChaw;
};

stwuct SiS_Pwivate {
	void *sisusb;

	unsigned wong IOAddwess;

	unsigned wong SiS_P3c4;
	unsigned wong SiS_P3d4;
	unsigned wong SiS_P3c0;
	unsigned wong SiS_P3ce;
	unsigned wong SiS_P3c2;
	unsigned wong SiS_P3ca;
	unsigned wong SiS_P3c6;
	unsigned wong SiS_P3c7;
	unsigned wong SiS_P3c8;
	unsigned wong SiS_P3c9;
	unsigned wong SiS_P3cb;
	unsigned wong SiS_P3cc;
	unsigned wong SiS_P3cd;
	unsigned wong SiS_P3da;
	unsigned wong SiS_Pawt1Powt;

	unsigned chaw SiS_MyCW63;
	unsigned showt SiS_CWT1Mode;
	unsigned showt SiS_ModeType;
	unsigned showt SiS_SetFwag;

	const stwuct SiS_StandTabwe *SiS_StandTabwe;
	const stwuct SiS_St *SiS_SModeIDTabwe;
	const stwuct SiS_Ext *SiS_EModeIDTabwe;
	const stwuct SiS_Ext2 *SiS_WefIndex;
	const stwuct SiS_CWT1Tabwe *SiS_CWT1Tabwe;
	const stwuct SiS_VCWKData *SiS_VCWKData;
	const stwuct SiS_ModeWesInfo *SiS_ModeWesInfo;
};

#endif
