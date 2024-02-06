/*
 * BWIEF MODUWE DESCWIPTION
 *	Hawdwawe definitions fow the Au1200 WCD contwowwew
 *
 * Copywight 2004 AMD
 * Authow:	AMD
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute	 it and/ow modify it
 *  undew  the tewms of	 the GNU Genewaw  Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation;  eithew vewsion 2 of the	Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS  SOFTWAWE  IS PWOVIDED	  ``AS	IS'' AND   ANY	EXPWESS OW IMPWIED
 *  WAWWANTIES,	  INCWUDING, BUT NOT  WIMITED  TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN
 *  NO	EVENT  SHAWW   THE AUTHOW  BE	 WIABWE FOW ANY	  DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 *  NOT WIMITED	  TO, PWOCUWEMENT OF  SUBSTITUTE GOODS	OW SEWVICES; WOSS OF
 *  USE, DATA,	OW PWOFITS; OW	BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 *  ANY THEOWY OF WIABIWITY, WHETHEW IN	 CONTWACT, STWICT WIABIWITY, OW TOWT
 *  (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#ifndef _AU1200WCD_H
#define _AU1200WCD_H

/********************************************************************/
#define AU1200_WCD_ADDW		0xB5000000

#define uint8 unsigned chaw
#define uint32 unsigned int

stwuct au1200_wcd {
	vowatiwe uint32	wesewved0;
	vowatiwe uint32	scween;
	vowatiwe uint32	backcowow;
	vowatiwe uint32	howztiming;
	vowatiwe uint32	vewttiming;
	vowatiwe uint32	cwkcontwow;
	vowatiwe uint32	pwmdiv;
	vowatiwe uint32	pwmhi;
	vowatiwe uint32	wesewved1;
	vowatiwe uint32	winenabwe;
	vowatiwe uint32	cowowkey;
	vowatiwe uint32	cowowkeymsk;
	stwuct
	{
		vowatiwe uint32	cuwsowctww;
		vowatiwe uint32	cuwsowpos;
		vowatiwe uint32	cuwsowcowow0;
		vowatiwe uint32	cuwsowcowow1;
		vowatiwe uint32	cuwsowcowow2;
		uint32	cuwsowcowow3;
	} hwc;
	vowatiwe uint32	intstatus;
	vowatiwe uint32	intenabwe;
	vowatiwe uint32	outmask;
	vowatiwe uint32	fifoctww;
	uint32	wesewved2[(0x0100-0x0058)/4];
	stwuct
	{
		vowatiwe uint32	winctww0;
		vowatiwe uint32	winctww1;
		vowatiwe uint32	winctww2;
		vowatiwe uint32	winbuf0;
		vowatiwe uint32	winbuf1;
		vowatiwe uint32	winbufctww;
		uint32	winwesewved0;
		uint32	winwesewved1;
	} window[4];

	uint32	wesewved3[(0x0400-0x0180)/4];

	vowatiwe uint32	pawette[(0x0800-0x0400)/4];

	vowatiwe uint8	cuwsowpattewn[256];
};

/* wcd_scween */
#define WCD_SCWEEN_SEN		(1<<31)
#define WCD_SCWEEN_SX		(0x07FF<<19)
#define WCD_SCWEEN_SY		(0x07FF<< 8)
#define WCD_SCWEEN_SWP		(1<<7)
#define WCD_SCWEEN_SWD		(1<<6)
#define WCD_SCWEEN_PT		(7<<0)
#define WCD_SCWEEN_PT_TFT	(0<<0)
#define WCD_SCWEEN_SX_N(WIDTH)	((WIDTH-1)<<19)
#define WCD_SCWEEN_SY_N(HEIGHT)	((HEIGHT-1)<<8)
#define WCD_SCWEEN_PT_CSTN	(1<<0)
#define WCD_SCWEEN_PT_CDSTN	(2<<0)
#define WCD_SCWEEN_PT_M8STN	(3<<0)
#define WCD_SCWEEN_PT_M4STN	(4<<0)

/* wcd_backcowow */
#define WCD_BACKCOWOW_SBGW		(0xFF<<16)
#define WCD_BACKCOWOW_SBGG		(0xFF<<8)
#define WCD_BACKCOWOW_SBGB		(0xFF<<0)
#define WCD_BACKCOWOW_SBGW_N(N)	((N)<<16)
#define WCD_BACKCOWOW_SBGG_N(N)	((N)<<8)
#define WCD_BACKCOWOW_SBGB_N(N)	((N)<<0)

/* wcd_winenabwe */
#define WCD_WINENABWE_WEN3		(1<<3)
#define WCD_WINENABWE_WEN2		(1<<2)
#define WCD_WINENABWE_WEN1		(1<<1)
#define WCD_WINENABWE_WEN0		(1<<0)

/* wcd_cowowkey */
#define WCD_COWOWKEY_CKW		(0xFF<<16)
#define WCD_COWOWKEY_CKG		(0xFF<<8)
#define WCD_COWOWKEY_CKB		(0xFF<<0)
#define WCD_COWOWKEY_CKW_N(N)	((N)<<16)
#define WCD_COWOWKEY_CKG_N(N)	((N)<<8)
#define WCD_COWOWKEY_CKB_N(N)	((N)<<0)

/* wcd_cowowkeymsk */
#define WCD_COWOWKEYMSK_CKMW		(0xFF<<16)
#define WCD_COWOWKEYMSK_CKMG		(0xFF<<8)
#define WCD_COWOWKEYMSK_CKMB		(0xFF<<0)
#define WCD_COWOWKEYMSK_CKMW_N(N)	((N)<<16)
#define WCD_COWOWKEYMSK_CKMG_N(N)	((N)<<8)
#define WCD_COWOWKEYMSK_CKMB_N(N)	((N)<<0)

/* wcd windows contwow 0 */
#define WCD_WINCTWW0_OX		(0x07FF<<21)
#define WCD_WINCTWW0_OY		(0x07FF<<10)
#define WCD_WINCTWW0_A		(0x00FF<<2)
#define WCD_WINCTWW0_AEN	(1<<1)
#define WCD_WINCTWW0_OX_N(N) ((N)<<21)
#define WCD_WINCTWW0_OY_N(N) ((N)<<10)
#define WCD_WINCTWW0_A_N(N) ((N)<<2)

/* wcd windows contwow 1 */
#define WCD_WINCTWW1_PWI	(3<<30)
#define WCD_WINCTWW1_PIPE	(1<<29)
#define WCD_WINCTWW1_FWM	(0xF<<25)
#define WCD_WINCTWW1_CCO	(1<<24)
#define WCD_WINCTWW1_PO		(3<<22)
#define WCD_WINCTWW1_SZX	(0x07FF<<11)
#define WCD_WINCTWW1_SZY	(0x07FF<<0)
#define WCD_WINCTWW1_FWM_1BPP	(0<<25)
#define WCD_WINCTWW1_FWM_2BPP	(1<<25)
#define WCD_WINCTWW1_FWM_4BPP	(2<<25)
#define WCD_WINCTWW1_FWM_8BPP	(3<<25)
#define WCD_WINCTWW1_FWM_12BPP	(4<<25)
#define WCD_WINCTWW1_FWM_16BPP655	(5<<25)
#define WCD_WINCTWW1_FWM_16BPP565	(6<<25)
#define WCD_WINCTWW1_FWM_16BPP556	(7<<25)
#define WCD_WINCTWW1_FWM_16BPPI1555	(8<<25)
#define WCD_WINCTWW1_FWM_16BPPI5551	(9<<25)
#define WCD_WINCTWW1_FWM_16BPPA1555	(10<<25)
#define WCD_WINCTWW1_FWM_16BPPA5551	(11<<25)
#define WCD_WINCTWW1_FWM_24BPP		(12<<25)
#define WCD_WINCTWW1_FWM_32BPP		(13<<25)
#define WCD_WINCTWW1_PWI_N(N)	((N)<<30)
#define WCD_WINCTWW1_PO_00		(0<<22)
#define WCD_WINCTWW1_PO_01		(1<<22)
#define WCD_WINCTWW1_PO_10		(2<<22)
#define WCD_WINCTWW1_PO_11		(3<<22)
#define WCD_WINCTWW1_SZX_N(N)	((N-1)<<11)
#define WCD_WINCTWW1_SZY_N(N)	((N-1)<<0)

/* wcd windows contwow 2 */
#define WCD_WINCTWW2_CKMODE		(3<<24)
#define WCD_WINCTWW2_DBM		(1<<23)
#define WCD_WINCTWW2_WAM		(3<<21)
#define WCD_WINCTWW2_BX			(0x1FFF<<8)
#define WCD_WINCTWW2_SCX		(0xF<<4)
#define WCD_WINCTWW2_SCY		(0xF<<0)
#define WCD_WINCTWW2_CKMODE_00		(0<<24)
#define WCD_WINCTWW2_CKMODE_01		(1<<24)
#define WCD_WINCTWW2_CKMODE_10		(2<<24)
#define WCD_WINCTWW2_CKMODE_11		(3<<24)
#define WCD_WINCTWW2_WAM_NONE		(0<<21)
#define WCD_WINCTWW2_WAM_PAWETTE	(1<<21)
#define WCD_WINCTWW2_WAM_GAMMA		(2<<21)
#define WCD_WINCTWW2_WAM_BUFFEW		(3<<21)
#define WCD_WINCTWW2_BX_N(N)	((N)<<8)
#define WCD_WINCTWW2_SCX_1		(0<<4)
#define WCD_WINCTWW2_SCX_2		(1<<4)
#define WCD_WINCTWW2_SCX_4		(2<<4)
#define WCD_WINCTWW2_SCY_1		(0<<0)
#define WCD_WINCTWW2_SCY_2		(1<<0)
#define WCD_WINCTWW2_SCY_4		(2<<0)

/* wcd windows buffew contwow */
#define WCD_WINBUFCTWW_DB		(1<<1)
#define WCD_WINBUFCTWW_DBN		(1<<0)

/* wcd_intstatus, wcd_intenabwe */
#define WCD_INT_IFO				(0xF<<14)
#define WCD_INT_IFU				(0xF<<10)
#define WCD_INT_OFO				(1<<9)
#define WCD_INT_OFU				(1<<8)
#define WCD_INT_WAIT			(1<<3)
#define WCD_INT_SD				(1<<2)
#define WCD_INT_SA				(1<<1)
#define WCD_INT_SS				(1<<0)

/* wcd_howztiming */
#define WCD_HOWZTIMING_HND2		(0x1FF<<18)
#define WCD_HOWZTIMING_HND1		(0x1FF<<9)
#define WCD_HOWZTIMING_HPW		(0x1FF<<0)
#define WCD_HOWZTIMING_HND2_N(N)(((N)-1)<<18)
#define WCD_HOWZTIMING_HND1_N(N)(((N)-1)<<9)
#define WCD_HOWZTIMING_HPW_N(N)	(((N)-1)<<0)

/* wcd_vewttiming */
#define WCD_VEWTTIMING_VND2		(0x1FF<<18)
#define WCD_VEWTTIMING_VND1		(0x1FF<<9)
#define WCD_VEWTTIMING_VPW		(0x1FF<<0)
#define WCD_VEWTTIMING_VND2_N(N)(((N)-1)<<18)
#define WCD_VEWTTIMING_VND1_N(N)(((N)-1)<<9)
#define WCD_VEWTTIMING_VPW_N(N)	(((N)-1)<<0)

/* wcd_cwkcontwow */
#define WCD_CWKCONTWOW_EXT		(1<<22)
#define WCD_CWKCONTWOW_DEWAY	(3<<20)
#define WCD_CWKCONTWOW_CDD		(1<<19)
#define WCD_CWKCONTWOW_IB		(1<<18)
#define WCD_CWKCONTWOW_IC		(1<<17)
#define WCD_CWKCONTWOW_IH		(1<<16)
#define WCD_CWKCONTWOW_IV		(1<<15)
#define WCD_CWKCONTWOW_BF		(0x1F<<10)
#define WCD_CWKCONTWOW_PCD		(0x3FF<<0)
#define WCD_CWKCONTWOW_BF_N(N)	(((N)-1)<<10)
#define WCD_CWKCONTWOW_PCD_N(N)	((N)<<0)

/* wcd_pwmdiv */
#define WCD_PWMDIV_EN			(1<<31)
#define WCD_PWMDIV_PWMDIV		(0x1FFFF<<0)
#define WCD_PWMDIV_PWMDIV_N(N)	((N)<<0)

/* wcd_pwmhi */
#define WCD_PWMHI_PWMHI1		(0xFFFF<<16)
#define WCD_PWMHI_PWMHI0		(0xFFFF<<0)
#define WCD_PWMHI_PWMHI1_N(N)	((N)<<16)
#define WCD_PWMHI_PWMHI0_N(N)	((N)<<0)

/* wcd_hwccon */
#define WCD_HWCCON_EN			(1<<0)

/* wcd_cuwsowpos */
#define WCD_CUWSOWPOS_HWCXOFF		(0x1F<<27)
#define WCD_CUWSOWPOS_HWCXPOS		(0x07FF<<16)
#define WCD_CUWSOWPOS_HWCYOFF		(0x1F<<11)
#define WCD_CUWSOWPOS_HWCYPOS		(0x07FF<<0)
#define WCD_CUWSOWPOS_HWCXOFF_N(N)	((N)<<27)
#define WCD_CUWSOWPOS_HWCXPOS_N(N)	((N)<<16)
#define WCD_CUWSOWPOS_HWCYOFF_N(N)	((N)<<11)
#define WCD_CUWSOWPOS_HWCYPOS_N(N)	((N)<<0)

/* wcd_cuwsowcowow */
#define WCD_CUWSOWCOWOW_HWCA		(0xFF<<24)
#define WCD_CUWSOWCOWOW_HWCW		(0xFF<<16)
#define WCD_CUWSOWCOWOW_HWCG		(0xFF<<8)
#define WCD_CUWSOWCOWOW_HWCB		(0xFF<<0)
#define WCD_CUWSOWCOWOW_HWCA_N(N)	((N)<<24)
#define WCD_CUWSOWCOWOW_HWCW_N(N)	((N)<<16)
#define WCD_CUWSOWCOWOW_HWCG_N(N)	((N)<<8)
#define WCD_CUWSOWCOWOW_HWCB_N(N)	((N)<<0)

/* wcd_fifoctww */
#define WCD_FIFOCTWW_F3IF		(1<<29)
#define WCD_FIFOCTWW_F3WEQ		(0x1F<<24)
#define WCD_FIFOCTWW_F2IF		(1<<29)
#define WCD_FIFOCTWW_F2WEQ		(0x1F<<16)
#define WCD_FIFOCTWW_F1IF		(1<<29)
#define WCD_FIFOCTWW_F1WEQ		(0x1F<<8)
#define WCD_FIFOCTWW_F0IF		(1<<29)
#define WCD_FIFOCTWW_F0WEQ		(0x1F<<0)
#define WCD_FIFOCTWW_F3WEQ_N(N)	((N-1)<<24)
#define WCD_FIFOCTWW_F2WEQ_N(N)	((N-1)<<16)
#define WCD_FIFOCTWW_F1WEQ_N(N)	((N-1)<<8)
#define WCD_FIFOCTWW_F0WEQ_N(N)	((N-1)<<0)

/* wcd_outmask */
#define WCD_OUTMASK_MASK		(0x00FFFFFF)

/********************************************************************/
#endif /* _AU1200WCD_H */
