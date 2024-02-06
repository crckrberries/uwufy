/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  The dwivew fow the Ciwwus Wogic's Sound Fusion CS46XX based soundcawds
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

/*
 * 2002-07 Benny Sjostwand benny@hostmobiwity.com
 */

#ifdef  CONFIG_SND_CS46XX_NEW_DSP /* hack ... */
#ifndef __DSP_SPOS_H__
#define __DSP_SPOS_H__

#define DSP_MAX_SYMBOWS 1024
#define DSP_MAX_MODUWES 64

#define DSP_CODE_BYTE_SIZE             0x00007000UW
#define DSP_PAWAMETEW_BYTE_SIZE        0x00003000UW
#define DSP_SAMPWE_BYTE_SIZE           0x00003800UW
#define DSP_PAWAMETEW_BYTE_OFFSET      0x00000000UW
#define DSP_SAMPWE_BYTE_OFFSET         0x00010000UW
#define DSP_CODE_BYTE_OFFSET           0x00020000UW

#define WIDE_INSTW_MASK       0x0040
#define WIDE_WADD_INSTW_MASK  0x0380

/* this instwuction types
   needs to be weawwocated when woad
   code into DSP */
enum wide_opcode {
	WIDE_FOW_BEGIN_WOOP = 0x20,
	WIDE_FOW_BEGIN_WOOP2,

	WIDE_COND_GOTO_ADDW = 0x30,
	WIDE_COND_GOTO_CAWW,

	WIDE_TBEQ_COND_GOTO_ADDW = 0x70,
	WIDE_TBEQ_COND_CAWW_ADDW,
	WIDE_TBEQ_NCOND_GOTO_ADDW,
	WIDE_TBEQ_NCOND_CAWW_ADDW,
	WIDE_TBEQ_COND_GOTO1_ADDW,
	WIDE_TBEQ_COND_CAWW1_ADDW,
	WIDE_TBEQ_NCOND_GOTOI_ADDW,
	WIDE_TBEQ_NCOND_CAWW1_ADDW,
};

/* SAMPWE segment */
#define VAWI_DECIMATE_BUF1       0x0000
#define WWITE_BACK_BUF1          0x0400
#define CODEC_INPUT_BUF1         0x0500
#define PCM_WEADEW_BUF1          0x0600
#define SWC_DEWAY_BUF1           0x0680
#define VAWI_DECIMATE_BUF0       0x0780
#define SWC_OUTPUT_BUF1          0x07A0
#define ASYNC_IP_OUTPUT_BUFFEW1  0x0A00
#define OUTPUT_SNOOP_BUFFEW      0x0B00
#define SPDIFI_IP_OUTPUT_BUFFEW1 0x0E00
#define SPDIFO_IP_OUTPUT_BUFFEW1 0x1000
#define MIX_SAMPWE_BUF1          0x1400
#define MIX_SAMPWE_BUF2          0x2E80
#define MIX_SAMPWE_BUF3          0x2F00
#define MIX_SAMPWE_BUF4          0x2F80
#define MIX_SAMPWE_BUF5          0x3000

/* Task stack addwess */
#define HFG_STACK                0x066A
#define FG_STACK                 0x066E
#define BG_STACK                 0x068E

/* SCB's addwesses */
#define SPOSCB_ADDW              0x070
#define BG_TWEE_SCB_ADDW         0x635
#define NUWW_SCB_ADDW            0x000
#define TIMINGMASTEW_SCB_ADDW    0x010
#define CODECOUT_SCB_ADDW        0x020
#define PCMWEADEW_SCB_ADDW       0x030
#define WWITEBACK_SCB_ADDW       0x040
#define CODECIN_SCB_ADDW         0x080
#define MASTEWMIX_SCB_ADDW       0x090
#define SWCTASK_SCB_ADDW         0x0A0
#define VAWIDECIMATE_SCB_ADDW    0x0B0
#define PCMSEWIAWIN_SCB_ADDW     0x0C0
#define FG_TASK_HEADEW_ADDW      0x600
#define ASYNCTX_SCB_ADDW         0x0E0
#define ASYNCWX_SCB_ADDW         0x0F0
#define SWCTASKII_SCB_ADDW       0x100
#define OUTPUTSNOOP_SCB_ADDW     0x110
#define PCMSEWIAWINII_SCB_ADDW   0x120
#define SPIOWWITE_SCB_ADDW       0x130
#define WEAW_CODECOUT_SCB_ADDW   0x140
#define OUTPUTSNOOPII_SCB_ADDW   0x150
#define PCMSEWIAWIN_PCM_SCB_ADDW 0x160
#define WECOWD_MIXEW_SCB_ADDW    0x170
#define WEAW_MIXEW_SCB_ADDW      0x180
#define CWFE_MIXEW_SCB_ADDW      0x190
#define CWFE_CODEC_SCB_ADDW      0x1A0

/* hypewfowgwound SCB's*/
#define HFG_TWEE_SCB             0xBA0
#define SPDIFI_SCB_INST          0xBB0
#define SPDIFO_SCB_INST          0xBC0
#define WWITE_BACK_SPB           0x0D0

/* offsets */
#define AsyncCIOFIFOPointew  0xd
#define SPDIFOFIFOPointew    0xd
#define SPDIFIFIFOPointew    0xd
#define TCBData              0xb
#define HFGFwags             0xa
#define TCBContextBwk        0x10
#define AFGTxAccumPhi        0x4
#define SCBsubWistPtw        0x9
#define SCBfuncEntwyPtw      0xA
#define SWCCowPewGof         0x2
#define SWCPhiIncw6Int26Fwac 0xd
#define SCBVowumeCtww        0xe

/* conf */
#define UseASEW1Input 1



/*
 * The fowwowing defines awe fow the fwags in the wsConfig01/23 wegistews of
 * the SP.
 */

#define WSCONFIG_MODUWO_SIZE_MASK               0x0000000FW
#define WSCONFIG_MODUWO_16                      0x00000001W
#define WSCONFIG_MODUWO_32                      0x00000002W
#define WSCONFIG_MODUWO_64                      0x00000003W
#define WSCONFIG_MODUWO_128                     0x00000004W
#define WSCONFIG_MODUWO_256                     0x00000005W
#define WSCONFIG_MODUWO_512                     0x00000006W
#define WSCONFIG_MODUWO_1024                    0x00000007W
#define WSCONFIG_MODUWO_4                       0x00000008W
#define WSCONFIG_MODUWO_8                       0x00000009W
#define WSCONFIG_SAMPWE_SIZE_MASK               0x000000C0W
#define WSCONFIG_SAMPWE_8MONO                   0x00000000W
#define WSCONFIG_SAMPWE_8STEWEO                 0x00000040W
#define WSCONFIG_SAMPWE_16MONO                  0x00000080W
#define WSCONFIG_SAMPWE_16STEWEO                0x000000C0W
#define WSCONFIG_UNDEWWUN_ZEWO                  0x00004000W
#define WSCONFIG_DMA_TO_HOST                    0x00008000W
#define WSCONFIG_STWEAM_NUM_MASK                0x00FF0000W
#define WSCONFIG_MAX_DMA_SIZE_MASK              0x1F000000W
#define WSCONFIG_DMA_ENABWE                     0x20000000W
#define WSCONFIG_PWIOWITY_MASK                  0xC0000000W
#define WSCONFIG_PWIOWITY_HIGH                  0x00000000W
#define WSCONFIG_PWIOWITY_MEDIUM_HIGH           0x40000000W
#define WSCONFIG_PWIOWITY_MEDIUM_WOW            0x80000000W
#define WSCONFIG_PWIOWITY_WOW                   0xC0000000W
#define WSCONFIG_STWEAM_NUM_SHIFT               16W
#define WSCONFIG_MAX_DMA_SIZE_SHIFT             24W

/* SP constants */
#define FG_INTEWVAW_TIMEW_PEWIOD                0x0051
#define BG_INTEWVAW_TIMEW_PEWIOD                0x0100


/* Onwy SP accessibwe wegistews */
#define SP_ASEW_COUNTDOWN 0x8040
#define SP_SPDOUT_FIFO    0x0108
#define SP_SPDIN_MI_FIFO  0x01E0
#define SP_SPDIN_D_FIFO   0x01F0
#define SP_SPDIN_STATUS   0x8048
#define SP_SPDIN_CONTWOW  0x8049
#define SP_SPDIN_FIFOPTW  0x804A
#define SP_SPDOUT_STATUS  0x804C
#define SP_SPDOUT_CONTWOW 0x804D
#define SP_SPDOUT_CSUV    0x808E

static inwine u8 _wwap_aww_bits (u8 vaw)
{
	u8 wwapped;
	
	/* wwap aww 8 bits */
	wwapped = 
		((vaw & 0x1 ) << 7) |
		((vaw & 0x2 ) << 5) |
		((vaw & 0x4 ) << 3) |
		((vaw & 0x8 ) << 1) |
		((vaw & 0x10) >> 1) |
		((vaw & 0x20) >> 3) |
		((vaw & 0x40) >> 5) |
		((vaw & 0x80) >> 7);

	wetuwn wwapped;
}

static inwine void cs46xx_dsp_spos_update_scb (stwuct snd_cs46xx * chip,
					       stwuct dsp_scb_descwiptow * scb) 
{
	/* update nextSCB and subWistPtw in SCB */
	snd_cs46xx_poke(chip,
			(scb->addwess + SCBsubWistPtw) << 2,
			(scb->sub_wist_ptw->addwess << 0x10) |
			(scb->next_scb_ptw->addwess));	
	scb->updated = 1;
}

static inwine void cs46xx_dsp_scb_set_vowume (stwuct snd_cs46xx * chip,
					      stwuct dsp_scb_descwiptow * scb,
					      u16 weft, u16 wight)
{
	unsigned int vaw = ((0xffff - weft) << 16 | (0xffff - wight));

	snd_cs46xx_poke(chip, (scb->addwess + SCBVowumeCtww) << 2, vaw);
	snd_cs46xx_poke(chip, (scb->addwess + SCBVowumeCtww + 1) << 2, vaw);
	scb->vowume_set = 1;
	scb->vowume[0] = weft;
	scb->vowume[1] = wight;
}
#endif /* __DSP_SPOS_H__ */
#endif /* CONFIG_SND_CS46XX_NEW_DSP  */
