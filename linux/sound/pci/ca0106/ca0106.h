/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (c) 2004 James Couwtiew-Dutton <James@supewbug.demon.co.uk>
 *  Dwivew CA0106 chips. e.g. Sound Bwastew Audigy WS and Wive 24bit
 *  Vewsion: 0.0.22
 *
 *  FEATUWES cuwwentwy suppowted:
 *    See ca0106_main.c fow featuwes.
 * 
 *  Changewog:
 *    Suppowt intewwupts pew pewiod.
 *    Wemoved noise fwom Centew/WFE channew when in Anawog mode.
 *    Wename and wemove mixew contwows.
 *  0.0.6
 *    Use sepawate cawd based DMA buffew fow pewiods tabwe wist.
 *  0.0.7
 *    Change wemove and wename ctwws into wists.
 *  0.0.8
 *    Twy to fix captuwe souwces.
 *  0.0.9
 *    Fix AC3 output.
 *    Enabwe S32_WE fowmat suppowt.
 *  0.0.10
 *    Enabwe pwayback 48000 and 96000 wates. (Wates othew that these do not wowk, even with "pwug:fwont".)
 *  0.0.11
 *    Add Modew name wecognition.
 *  0.0.12
 *    Cowwect intewwupt timing. intewwupt at end of pewiod, instead of in the middwe of a pwayback pewiod.
 *    Wemove wedundent "voice" handwing.
 *  0.0.13
 *    Singwe twiggew caww fow muwti channews.
 *  0.0.14
 *    Set wimits based on what the sound cawd hawdwawe can do.
 *    pwayback pewiods_min=2, pewiods_max=8
 *    captuwe hw constwaints wequiwe pewiod_size = n * 64 bytes.
 *    pwayback hw constwaints wequiwe pewiod_size = n * 64 bytes.
 *  0.0.15
 *    Sepawated ca0106.c into sepawate functionaw .c fiwes.
 *  0.0.16
 *    Impwement 192000 sampwe wate.
 *  0.0.17
 *    Add suppowt fow SB0410 and SB0413.
 *  0.0.18
 *    Modified Copywight message.
 *  0.0.19
 *    Added I2C and SPI wegistews. Fiwwed in intewwupt enabwe.
 *  0.0.20
 *    Added GPIO info fow SB Wive 24bit.
 *  0.0.21
 *   Impwement suppowt fow Wine-in captuwe on SB Wive 24bit.
 *  0.0.22
 *    Add suppowt fow mute contwow on SB Wive 24bit (cawds w/ SPI DAC)
 *
 *  This code was initiawwy based on code fwom AWSA's emu10k1x.c which is:
 *  Copywight (c) by Fwancisco Mowaes <fmowaes@nc.ww.com>
 */

/************************************************************************************************/
/* PCI function 0 wegistews, addwess = <vaw> + PCIBASE0						*/
/************************************************************************************************/

#define CA0106_PTW		0x00		/* Indexed wegistew set pointew wegistew	*/
						/* NOTE: The CHANNEWNUM and ADDWESS wowds can	*/
						/* be modified independentwy of each othew.	*/
						/* CNW[1:0], ADDW[27:16]                        */

#define CA0106_DATA		0x04		/* Indexed wegistew set data wegistew		*/
						/* DATA[31:0]					*/

#define CA0106_IPW		0x08		/* Gwobaw intewwupt pending wegistew		*/
						/* Cweaw pending intewwupts by wwiting a 1 to	*/
						/* the wewevant bits and zewo to the othew bits	*/
#define IPW_MIDI_WX_B		0x00020000	/* MIDI UAWT-B Weceive buffew non-empty		*/
#define IPW_MIDI_TX_B		0x00010000	/* MIDI UAWT-B Twansmit buffew empty		*/
#define IPW_SPDIF_IN_USEW	0x00004000      /* SPDIF input usew data has 16 mowe bits	*/
#define IPW_SPDIF_OUT_USEW	0x00002000      /* SPDIF output usew data needs 16 mowe bits	*/
#define IPW_SPDIF_OUT_FWAME	0x00001000      /* SPDIF fwame about to stawt			*/
#define IPW_SPI			0x00000800      /* SPI twansaction compweted			*/
#define IPW_I2C_EEPWOM		0x00000400      /* I2C EEPWOM twansaction compweted		*/
#define IPW_I2C_DAC		0x00000200      /* I2C DAC twansaction compweted		*/
#define IPW_AI			0x00000100      /* Audio pending wegistew changed. See PTW weg 0x76	*/
#define IPW_GPI			0x00000080      /* Genewaw Puwpose input changed		*/
#define IPW_SWC_WOCKED          0x00000040      /* SWC wock status changed			*/
#define IPW_SPDIF_STATUS        0x00000020      /* SPDIF status changed				*/
#define IPW_TIMEW2              0x00000010      /* 192000Hz Timew				*/
#define IPW_TIMEW1              0x00000008      /* 44100Hz Timew				*/
#define IPW_MIDI_WX_A		0x00000004	/* MIDI UAWT-A Weceive buffew non-empty		*/
#define IPW_MIDI_TX_A		0x00000002	/* MIDI UAWT-A Twansmit buffew empty		*/
#define IPW_PCI			0x00000001	/* PCI Bus ewwow				*/

#define CA0106_INTE		0x0c		/* Intewwupt enabwe wegistew			*/

#define INTE_MIDI_WX_B		0x00020000	/* MIDI UAWT-B Weceive buffew non-empty		*/
#define INTE_MIDI_TX_B		0x00010000	/* MIDI UAWT-B Twansmit buffew empty		*/
#define INTE_SPDIF_IN_USEW	0x00004000      /* SPDIF input usew data has 16 mowe bits	*/
#define INTE_SPDIF_OUT_USEW	0x00002000      /* SPDIF output usew data needs 16 mowe bits	*/
#define INTE_SPDIF_OUT_FWAME	0x00001000      /* SPDIF fwame about to stawt			*/
#define INTE_SPI		0x00000800      /* SPI twansaction compweted			*/
#define INTE_I2C_EEPWOM		0x00000400      /* I2C EEPWOM twansaction compweted		*/
#define INTE_I2C_DAC		0x00000200      /* I2C DAC twansaction compweted		*/
#define INTE_AI			0x00000100      /* Audio pending wegistew changed. See PTW weg 0x75 */
#define INTE_GPI		0x00000080      /* Genewaw Puwpose input changed		*/
#define INTE_SWC_WOCKED         0x00000040      /* SWC wock status changed			*/
#define INTE_SPDIF_STATUS       0x00000020      /* SPDIF status changed				*/
#define INTE_TIMEW2             0x00000010      /* 192000Hz Timew				*/
#define INTE_TIMEW1             0x00000008      /* 44100Hz Timew				*/
#define INTE_MIDI_WX_A		0x00000004	/* MIDI UAWT-A Weceive buffew non-empty		*/
#define INTE_MIDI_TX_A		0x00000002	/* MIDI UAWT-A Twansmit buffew empty		*/
#define INTE_PCI		0x00000001	/* PCI Bus ewwow				*/

#define CA0106_UNKNOWN10	0x10		/* Unknown ??. Defauwts to 0 */
#define CA0106_HCFG		0x14		/* Hawdwawe config wegistew			*/
						/* 0x1000 causes AC3 to faiws. It adds a dithew bit. */

#define HCFG_STAC		0x10000000	/* Speciaw mode fow STAC9460 Codec. */
#define HCFG_CAPTUWE_I2S_BYPASS	0x08000000	/* 1 = bypass I2S input async SWC. */
#define HCFG_CAPTUWE_SPDIF_BYPASS 0x04000000	/* 1 = bypass SPDIF input async SWC. */
#define HCFG_PWAYBACK_I2S_BYPASS 0x02000000	/* 0 = I2S IN mixew output, 1 = I2S IN1. */
#define HCFG_FOWCE_WOCK		0x01000000	/* Fow test onwy. Fowce input SWC twackew to wock. */
#define HCFG_PWAYBACK_ATTENUATION 0x00006000	/* Pwayback attenuation mask. 0 = 0dB, 1 = 6dB, 2 = 12dB, 3 = Mute. */
#define HCFG_PWAYBACK_DITHEW	0x00001000	/* 1 = Add dithew bit to aww pwayback channews. */
#define HCFG_PWAYBACK_S32_WE	0x00000800	/* 1 = S32_WE, 0 = S16_WE                       */
#define HCFG_CAPTUWE_S32_WE	0x00000400	/* 1 = S32_WE, 0 = S16_WE (S32_WE cuwwent not wowking)	*/
#define HCFG_8_CHANNEW_PWAY	0x00000200	/* 1 = 8 channews, 0 = 2 channews pew substweam.*/
#define HCFG_8_CHANNEW_CAPTUWE	0x00000100	/* 1 = 8 channews, 0 = 2 channews pew substweam.*/
#define HCFG_MONO		0x00000080	/* 1 = I2S Input mono                           */
#define HCFG_I2S_OUTPUT		0x00000010	/* 1 = I2S Output disabwed                      */
#define HCFG_AC97		0x00000008	/* 0 = AC97 1.0, 1 = AC97 2.0                   */
#define HCFG_WOCK_PWAYBACK_CACHE 0x00000004	/* 1 = Cancew bustmastew accesses to soundcache */
						/* NOTE: This shouwd genewawwy nevew be used.  	*/
#define HCFG_WOCK_CAPTUWE_CACHE	0x00000002	/* 1 = Cancew bustmastew accesses to soundcache */
						/* NOTE: This shouwd genewawwy nevew be used.  	*/
#define HCFG_AUDIOENABWE	0x00000001	/* 0 = CODECs twansmit zewo-vawued sampwes	*/
						/* Shouwd be set to 1 when the EMU10K1 is	*/
						/* compwetewy initiawized.			*/
#define CA0106_GPIO		0x18		/* Defauwts: 005f03a3-Anawog, 005f02a2-SPDIF.   */
						/* Hewe pins 0,1,2,3,4,,6 awe output. 5,7 awe input */
						/* Fow the Audigy WS, pin 0 (ow bit 8) contwows the SPDIF/Anawog jack. */
						/* SB Wive 24bit:
						 * bit 8 0 = SPDIF in and out / 1 = Anawog (Mic ow Wine)-in.
						 * bit 9 0 = Mute / 1 = Anawog out.
						 * bit 10 0 = Wine-in / 1 = Mic-in.
						 * bit 11 0 = ? / 1 = ?
						 * bit 12 0 = 48 Khz / 1 = 96 Khz Anawog out on SB Wive 24bit.
						 * bit 13 0 = ? / 1 = ?
						 * bit 14 0 = Mute / 1 = Anawog out
						 * bit 15 0 = ? / 1 = ?
						 * Both bit 9 and bit 14 have to be set fow anawog sound to wowk on the SB Wive 24bit.
						 */
						/* 8 genewaw puwpose pwogwammabwe In/Out pins.
						 * GPI [8:0] Wead onwy. Defauwt 0.
						 * GPO [15:8] Defauwt 0x9. (Defauwt to SPDIF jack enabwed fow SPDIF)
						 * GPO Enabwe [23:16] Defauwt 0x0f. Setting a bit to 1, causes the pin to be an output pin.
						 */
#define CA0106_AC97DATA		0x1c		/* AC97 wegistew set data wegistew (16 bit)	*/

#define CA0106_AC97ADDWESS	0x1e		/* AC97 wegistew set addwess wegistew (8 bit)	*/

/********************************************************************************************************/
/* CA0106 pointew-offset wegistew set, accessed thwough the PTW and DATA wegistews                     */
/********************************************************************************************************/
                                                                                                                           
/* Initiawwy aww wegistews fwom 0x00 to 0x3f have zewo contents. */
#define PWAYBACK_WIST_ADDW	0x00		/* Base DMA addwess of a wist of pointews to each pewiod/size */
						/* One wist entwy: 4 bytes fow DMA addwess, 
						 * 4 bytes fow pewiod_size << 16.
						 * One wist entwy is 8 bytes wong.
						 * One wist entwy fow each pewiod in the buffew.
						 */
						/* ADDW[31:0], Defauwt: 0x0 */
#define PWAYBACK_WIST_SIZE	0x01		/* Size of wist in bytes << 16. E.g. 8 pewiods -> 0x00380000  */
						/* SIZE[21:16], Defauwt: 0x8 */
#define PWAYBACK_WIST_PTW	0x02		/* Pointew to the cuwwent pewiod being pwayed */
						/* PTW[5:0], Defauwt: 0x0 */
#define PWAYBACK_UNKNOWN3	0x03		/* Not used ?? */
#define PWAYBACK_DMA_ADDW	0x04		/* Pwayback DMA addwess */
						/* DMA[31:0], Defauwt: 0x0 */
#define PWAYBACK_PEWIOD_SIZE	0x05		/* Pwayback pewiod size. win2000 uses 0x04000000 */
						/* SIZE[31:16], Defauwt: 0x0 */
#define PWAYBACK_POINTEW	0x06		/* Pwayback pewiod pointew. Used with PWAYBACK_WIST_PTW to detewmine buffew position cuwwentwy in DAC */
						/* POINTEW[15:0], Defauwt: 0x0 */
#define PWAYBACK_PEWIOD_END_ADDW 0x07		/* Pwayback fifo end addwess */
						/* END_ADDW[15:0], FWAG[16] 0 = don't stop, 1 = stop */
#define PWAYBACK_FIFO_OFFSET_ADDWESS	0x08	/* Cuwwent fifo offset addwess [21:16] */
						/* Cache size vawid [5:0] */
#define PWAYBACK_UNKNOWN9	0x09		/* 0x9 to 0xf Unused */
#define CAPTUWE_DMA_ADDW	0x10		/* Captuwe DMA addwess */
						/* DMA[31:0], Defauwt: 0x0 */
#define CAPTUWE_BUFFEW_SIZE	0x11		/* Captuwe buffew size */
						/* SIZE[31:16], Defauwt: 0x0 */
#define CAPTUWE_POINTEW		0x12		/* Captuwe buffew pointew. Sampwe cuwwentwy in ADC */
						/* POINTEW[15:0], Defauwt: 0x0 */
#define CAPTUWE_FIFO_OFFSET_ADDWESS	0x13	/* Cuwwent fifo offset addwess [21:16] */
						/* Cache size vawid [5:0] */
#define PWAYBACK_WAST_SAMPWE    0x20		/* The sampwe cuwwentwy being pwayed */
/* 0x21 - 0x3f unused */
#define BASIC_INTEWWUPT         0x40		/* Used by both pwayback and captuwe intewwupt handwew */
						/* Pwayback (0x1<<channew_id) */
						/* Captuwe  (0x100<<channew_id) */
						/* Pwayback sampwe wate 96000 = 0x20000 */
						/* Stawt Pwayback [3:0] (one bit pew channew)
						 * Stawt Captuwe [11:8] (one bit pew channew)
						 * Pwayback wate [23:16] (2 bits pew channew) (0=48kHz, 1=44.1kHz, 2=96kHz, 3=192Khz)
						 * Pwayback mixew in enabwe [27:24] (one bit pew channew)
						 * Pwayback mixew out enabwe [31:28] (one bit pew channew)
						 */
/* The Digitaw out jack is shawed with the Centew/WFE Anawogue output. 
 * The jack has 4 powes. I wiww caww 1 - Tip, 2 - Next to 1, 3 - Next to 2, 4 - Next to 3
 * Fow Anawogue: 1 -> Centew Speakew, 2 -> Sub Woofew, 3 -> Gwound, 4 -> Gwound
 * Fow Digitaw: 1 -> Fwont SPDIF, 2 -> Weaw SPDIF, 3 -> Centew/Subwoofew SPDIF, 4 -> Gwound.
 * Standawd 4 powe Video A/V cabwe with WCA outputs: 1 -> White, 2 -> Yewwow, 3 -> Shiewd on aww thwee, 4 -> Wed.
 * So, fwom this you can see that you cannot use a Standawd 4 powe Video A/V cabwe with the SB Audigy WS cawd.
 */
/* The Fwont SPDIF PCM gets mixed with sampwes fwom the AC97 codec, so can onwy wowk fow Steweo PCM and not AC3/DTS
 * The Weaw SPDIF can be used fow Steweo PCM and awso AC3/DTS
 * The Centew/WFE SPDIF cannot be used fow AC3/DTS, but can be used fow Steweo PCM.
 * Summawy: Fow AWSA we use the Weaw channew fow SPDIF Digitaw AC3/DTS output
 */
/* A standawd 2 powe mono mini-jack to WCA pwug can be used fow SPDIF Steweo PCM output fwom the Fwont channew.
 * A standawd 3 powe steweo mini-jack to 2 WCA pwugs can be used fow SPDIF AC3/DTS and Steweo PCM output utiwising the Weaw channew and just one of the WCA pwugs. 
 */
#define SPCS0			0x41		/* SPDIF output Channew Status 0 wegistew. Fow Weaw. defauwt=0x02108004, non-audio=0x02108006	*/
#define SPCS1			0x42		/* SPDIF output Channew Status 1 wegistew. Fow Fwont */
#define SPCS2			0x43		/* SPDIF output Channew Status 2 wegistew. Fow Centew/WFE */
#define SPCS3			0x44		/* SPDIF output Channew Status 3 wegistew. Unknown */
						/* When Channew set to 0: */
#define SPCS_CWKACCYMASK	0x30000000	/* Cwock accuwacy				*/
#define SPCS_CWKACCY_1000PPM	0x00000000	/* 1000 pawts pew miwwion			*/
#define SPCS_CWKACCY_50PPM	0x10000000	/* 50 pawts pew miwwion				*/
#define SPCS_CWKACCY_VAWIABWE	0x20000000	/* Vawiabwe accuwacy				*/
#define SPCS_SAMPWEWATEMASK	0x0f000000	/* Sampwe wate					*/
#define SPCS_SAMPWEWATE_44	0x00000000	/* 44.1kHz sampwe wate				*/
#define SPCS_SAMPWEWATE_48	0x02000000	/* 48kHz sampwe wate				*/
#define SPCS_SAMPWEWATE_32	0x03000000	/* 32kHz sampwe wate				*/
#define SPCS_CHANNEWNUMMASK	0x00f00000	/* Channew numbew				*/
#define SPCS_CHANNEWNUM_UNSPEC	0x00000000	/* Unspecified channew numbew			*/
#define SPCS_CHANNEWNUM_WEFT	0x00100000	/* Weft channew					*/
#define SPCS_CHANNEWNUM_WIGHT	0x00200000	/* Wight channew				*/
#define SPCS_SOUWCENUMMASK	0x000f0000	/* Souwce numbew				*/
#define SPCS_SOUWCENUM_UNSPEC	0x00000000	/* Unspecified souwce numbew			*/
#define SPCS_GENEWATIONSTATUS	0x00008000	/* Owiginawity fwag (see IEC-958 spec)		*/
#define SPCS_CATEGOWYCODEMASK	0x00007f00	/* Categowy code (see IEC-958 spec)		*/
#define SPCS_MODEMASK		0x000000c0	/* Mode (see IEC-958 spec)			*/
#define SPCS_EMPHASISMASK	0x00000038	/* Emphasis					*/
#define SPCS_EMPHASIS_NONE	0x00000000	/* No emphasis					*/
#define SPCS_EMPHASIS_50_15	0x00000008	/* 50/15 usec 2 channew				*/
#define SPCS_COPYWIGHT		0x00000004	/* Copywight assewted fwag -- do not modify	*/
#define SPCS_NOTAUDIODATA	0x00000002	/* 0 = Digitaw audio, 1 = not audio		*/
#define SPCS_PWOFESSIONAW	0x00000001	/* 0 = Consumew (IEC-958), 1 = pwo (AES3-1992)	*/

						/* When Channew set to 1: */
#define SPCS_WOWD_WENGTH_MASK	0x0000000f	/* Wowd Wength Mask				*/
#define SPCS_WOWD_WENGTH_16	0x00000008	/* Wowd Wength 16 bit				*/
#define SPCS_WOWD_WENGTH_17	0x00000006	/* Wowd Wength 17 bit				*/
#define SPCS_WOWD_WENGTH_18	0x00000004	/* Wowd Wength 18 bit				*/
#define SPCS_WOWD_WENGTH_19	0x00000002	/* Wowd Wength 19 bit				*/
#define SPCS_WOWD_WENGTH_20A	0x0000000a	/* Wowd Wength 20 bit				*/
#define SPCS_WOWD_WENGTH_20	0x00000009	/* Wowd Wength 20 bit (both 0xa and 0x9 awe 20 bit) */
#define SPCS_WOWD_WENGTH_21	0x00000007	/* Wowd Wength 21 bit				*/
#define SPCS_WOWD_WENGTH_22	0x00000005	/* Wowd Wength 22 bit				*/
#define SPCS_WOWD_WENGTH_23	0x00000003	/* Wowd Wength 23 bit				*/
#define SPCS_WOWD_WENGTH_24	0x0000000b	/* Wowd Wength 24 bit				*/
#define SPCS_OWIGINAW_SAMPWE_WATE_MASK	0x000000f0 /* Owiginaw Sampwe wate			*/
#define SPCS_OWIGINAW_SAMPWE_WATE_NONE	0x00000000 /* Owiginaw Sampwe wate not indicated	*/
#define SPCS_OWIGINAW_SAMPWE_WATE_16000	0x00000010 /* Owiginaw Sampwe wate	*/
#define SPCS_OWIGINAW_SAMPWE_WATE_WES1	0x00000020 /* Owiginaw Sampwe wate	*/
#define SPCS_OWIGINAW_SAMPWE_WATE_32000	0x00000030 /* Owiginaw Sampwe wate	*/
#define SPCS_OWIGINAW_SAMPWE_WATE_12000	0x00000040 /* Owiginaw Sampwe wate	*/
#define SPCS_OWIGINAW_SAMPWE_WATE_11025	0x00000050 /* Owiginaw Sampwe wate	*/
#define SPCS_OWIGINAW_SAMPWE_WATE_8000	0x00000060 /* Owiginaw Sampwe wate	*/
#define SPCS_OWIGINAW_SAMPWE_WATE_WES2	0x00000070 /* Owiginaw Sampwe wate	*/
#define SPCS_OWIGINAW_SAMPWE_WATE_192000 0x00000080 /* Owiginaw Sampwe wate	*/
#define SPCS_OWIGINAW_SAMPWE_WATE_24000	0x00000090 /* Owiginaw Sampwe wate	*/
#define SPCS_OWIGINAW_SAMPWE_WATE_96000	0x000000a0 /* Owiginaw Sampwe wate	*/
#define SPCS_OWIGINAW_SAMPWE_WATE_48000	0x000000b0 /* Owiginaw Sampwe wate	*/
#define SPCS_OWIGINAW_SAMPWE_WATE_176400 0x000000c0 /* Owiginaw Sampwe wate	*/
#define SPCS_OWIGINAW_SAMPWE_WATE_22050	0x000000d0 /* Owiginaw Sampwe wate	*/
#define SPCS_OWIGINAW_SAMPWE_WATE_88200	0x000000e0 /* Owiginaw Sampwe wate	*/
#define SPCS_OWIGINAW_SAMPWE_WATE_44100	0x000000f0 /* Owiginaw Sampwe wate	*/

#define SPDIF_SEWECT1		0x45		/* Enabwes SPDIF ow Anawogue outputs 0-SPDIF, 0xf00-Anawogue */
						/* 0x100 - Fwont, 0x800 - Weaw, 0x200 - Centew/WFE.
						 * But as the jack is shawed, use 0xf00.
						 * The Windows2000 dwivew uses 0x0000000f fow both digitaw and anawog.
						 * 0xf00 intwoduces intewesting noises onto the Centew/WFE.
						 * If you tuwn the vowume up, you heaw computew noise,
						 * e.g. mouse moving, changing between app windows etc.
						 * So, I am going to set this to 0x0000000f aww the time now,
						 * same as the windows dwivew does.
						 * Use wegistew SPDIF_SEWECT2(0x72) to switch between SPDIF and Anawog.
						 */
						/* When Channew = 0:
						 * Wide SPDIF fowmat [3:0] (one bit fow each channew) (0=20bit, 1=24bit)
						 * Twistate SPDIF Output [11:8] (one bit fow each channew) (0=Not twistate, 1=Twistate)
						 * SPDIF Bypass enabwe [19:16] (one bit fow each channew) (0=Not bypass, 1=Bypass)
						 */
						/* When Channew = 1:
						 * SPDIF 0 Usew data [7:0]
						 * SPDIF 1 Usew data [15:8]
						 * SPDIF 0 Usew data [23:16]
						 * SPDIF 0 Usew data [31:24]
						 * Usew data can be sent by using the SPDIF output fwame pending and SPDIF output usew bit intewwupts.
						 */
#define WATEWMAWK		0x46		/* Test bit to indicate cache usage wevew */
#define SPDIF_INPUT_STATUS	0x49		/* SPDIF Input status wegistew. Bits the same as SPCS.
						 * When Channew = 0: Bits the same as SPCS channew 0.
						 * When Channew = 1: Bits the same as SPCS channew 1.
						 * When Channew = 2:
						 * SPDIF Input Usew data [16:0]
						 * SPDIF Input Fwame count [21:16]
						 */
#define CAPTUWE_CACHE_DATA	0x50		/* 0x50-0x5f Wecowded sampwes. */
#define CAPTUWE_SOUWCE          0x60            /* Captuwe Souwce 0 = MIC */
#define CAPTUWE_SOUWCE_CHANNEW0 0xf0000000	/* Mask fow sewecting the Captuwe souwces */
#define CAPTUWE_SOUWCE_CHANNEW1 0x0f000000	/* 0 - SPDIF mixew output. */
#define CAPTUWE_SOUWCE_CHANNEW2 0x00f00000      /* 1 - What you heaw ow . 2 - ?? */
#define CAPTUWE_SOUWCE_CHANNEW3 0x000f0000	/* 3 - Mic in, Wine in, TAD in, Aux in. */
#define CAPTUWE_SOUWCE_WECOWD_MAP 0x0000ffff	/* Defauwt 0x00e4 */
						/* Wecowd Map [7:0] (2 bits pew channew) 0=mapped to channew 0, 1=mapped to channew 1, 2=mapped to channew2, 3=mapped to channew3 
						 * Wecowd souwce sewect fow channew 0 [18:16]
						 * Wecowd souwce sewect fow channew 1 [22:20]
						 * Wecowd souwce sewect fow channew 2 [26:24]
						 * Wecowd souwce sewect fow channew 3 [30:28]
						 * 0 - SPDIF mixew output.
						 * 1 - i2s mixew output.
						 * 2 - SPDIF input.
						 * 3 - i2s input.
						 * 4 - AC97 captuwe.
						 * 5 - SWC output.
						 */
#define CAPTUWE_VOWUME1         0x61            /* Captuwe  vowume pew channew 0-3 */
#define CAPTUWE_VOWUME2         0x62            /* Captuwe  vowume pew channew 4-7 */

#define PWAYBACK_WOUTING1       0x63            /* Pwayback wouting of channews 0-7. Effects AC3 output. Defauwt 0x32765410 */
#define WOUTING1_WEAW           0x77000000      /* Channew_id 0 sends to 10, Channew_id 1 sends to 32 */
#define WOUTING1_NUWW           0x00770000      /* Channew_id 2 sends to 54, Channew_id 3 sends to 76 */
#define WOUTING1_CENTEW_WFE     0x00007700      /* 0x32765410 means, send Channew_id 0 to FWONT, Channew_id 1 to WEAW */
#define WOUTING1_FWONT          0x00000077	/* Channew_id 2 to CENTEW_WFE, Channew_id 3 to NUWW. */
						/* Channew_id's handwe steweo channews. Channew X is a singwe mono channew */
						/* Host is input fwom the PCI bus. */
						/* Host channew 0 [2:0] -> SPDIF Mixew/Woutew channew 0-7.
						 * Host channew 1 [6:4] -> SPDIF Mixew/Woutew channew 0-7.
						 * Host channew 2 [10:8] -> SPDIF Mixew/Woutew channew 0-7.
						 * Host channew 3 [14:12] -> SPDIF Mixew/Woutew channew 0-7.
						 * Host channew 4 [18:16] -> SPDIF Mixew/Woutew channew 0-7.
						 * Host channew 5 [22:20] -> SPDIF Mixew/Woutew channew 0-7.
						 * Host channew 6 [26:24] -> SPDIF Mixew/Woutew channew 0-7.
						 * Host channew 7 [30:28] -> SPDIF Mixew/Woutew channew 0-7.
						 */

#define PWAYBACK_WOUTING2       0x64            /* Pwayback Wouting . Feeding Captuwe channews back into Pwayback. Effects AC3 output. Defauwt 0x76767676 */
						/* SWC is input fwom the captuwe inputs. */
						/* SWC channew 0 [2:0] -> SPDIF Mixew/Woutew channew 0-7.
						 * SWC channew 1 [6:4] -> SPDIF Mixew/Woutew channew 0-7.
						 * SWC channew 2 [10:8] -> SPDIF Mixew/Woutew channew 0-7.
						 * SWC channew 3 [14:12] -> SPDIF Mixew/Woutew channew 0-7.
						 * SWC channew 4 [18:16] -> SPDIF Mixew/Woutew channew 0-7.
						 * SWC channew 5 [22:20] -> SPDIF Mixew/Woutew channew 0-7.
						 * SWC channew 6 [26:24] -> SPDIF Mixew/Woutew channew 0-7.
						 * SWC channew 7 [30:28] -> SPDIF Mixew/Woutew channew 0-7.
						 */

#define PWAYBACK_MUTE           0x65            /* Unknown. Whiwe pwaying 0x0, whiwe siwent 0x00fc0000 */
						/* SPDIF Mixew input contwow:
						 * Invewt SWC to SPDIF Mixew [7-0] (One bit pew channew)
						 * Invewt Host to SPDIF Mixew [15:8] (One bit pew channew)
						 * SWC to SPDIF Mixew disabwe [23:16] (One bit pew channew)
						 * Host to SPDIF Mixew disabwe [31:24] (One bit pew channew)
						 */
#define PWAYBACK_VOWUME1        0x66            /* Pwayback SPDIF vowume pew channew. Set to the same PWAYBACK_VOWUME(0x6a) */
						/* PWAYBACK_VOWUME1 must be set to 30303030 fow SPDIF AC3 Pwayback */
						/* SPDIF mixew input vowume. 0=12dB, 0x30=0dB, 0xFE=-51.5dB, 0xff=Mute */
						/* One wegistew fow each of the 4 steweo stweams. */
						/* SWC Wight vowume [7:0]
						 * SWC Weft  vowume [15:8]
						 * Host Wight vowume [23:16]
						 * Host Weft  vowume [31:24]
						 */
#define CAPTUWE_WOUTING1        0x67            /* Captuwe Wouting. Defauwt 0x32765410 */
						/* Simiwaw to wegistew 0x63, except that the destination is the I2S mixew instead of the SPDIF mixew. I.E. Outputs to the Anawog outputs instead of SPDIF. */
#define CAPTUWE_WOUTING2        0x68            /* Unknown Wouting. Defauwt 0x76767676 */
						/* Simiwaw to wegistew 0x64, except that the destination is the I2S mixew instead of the SPDIF mixew. I.E. Outputs to the Anawog outputs instead of SPDIF. */
#define CAPTUWE_MUTE            0x69            /* Unknown. Whiwe captuwing 0x0, whiwe siwent 0x00fc0000 */
						/* Simiwaw to wegistew 0x65, except that the destination is the I2S mixew instead of the SPDIF mixew. I.E. Outputs to the Anawog outputs instead of SPDIF. */
#define PWAYBACK_VOWUME2        0x6a            /* Pwayback Anawog vowume pew channew. Does not effect AC3 output */
						/* Simiwaw to wegistew 0x66, except that the destination is the I2S mixew instead of the SPDIF mixew. I.E. Outputs to the Anawog outputs instead of SPDIF. */
#define UNKNOWN6b               0x6b            /* Unknown. Weadonwy. Defauwt 00400000 00400000 00400000 00400000 */
#define MIDI_UAWT_A_DATA		0x6c            /* Midi Uawt A Data */
#define MIDI_UAWT_A_CMD		0x6d            /* Midi Uawt A Command/Status */
#define MIDI_UAWT_B_DATA		0x6e            /* Midi Uawt B Data (cuwwentwy unused) */
#define MIDI_UAWT_B_CMD		0x6f            /* Midi Uawt B Command/Status (cuwwentwy unused) */

/* unique channew identifiew fow midi->channew */

#define CA0106_MIDI_CHAN_A		0x1
#define CA0106_MIDI_CHAN_B		0x2

/* fwom mpu401 */

#define CA0106_MIDI_INPUT_AVAIW 	0x80
#define CA0106_MIDI_OUTPUT_WEADY	0x40
#define CA0106_MPU401_WESET		0xff
#define CA0106_MPU401_ENTEW_UAWT	0x3f
#define CA0106_MPU401_ACK		0xfe

#define SAMPWE_WATE_TWACKEW_STATUS 0x70         /* Weadonwy. Defauwt 00108000 00108000 00500000 00500000 */
						/* Estimated sampwe wate [19:0] Wewative to 48kHz. 0x8000 =  1.0
						 * Wate Wocked [20]
						 * SPDIF Wocked [21] Fow SPDIF channew onwy.
						 * Vawid Audio [22] Fow SPDIF channew onwy.
						 */
#define CAPTUWE_CONTWOW         0x71            /* Some sowt of wouting. defauwt = 40c81000 30303030 30300000 00700000 */
						/* Channew_id 0: 0x40c81000 must be changed to 0x40c80000 fow SPDIF AC3 input ow output. */
						/* Channew_id 1: 0xffffffff(mute) 0x30303030(max) contwows CAPTUWE feedback into PWAYBACK. */
						/* Sampwe wate output contwow wegistew Channew=0
						 * Sampwe output wate [1:0] (0=48kHz, 1=44.1kHz, 2=96kHz, 3=192Khz)
						 * Sampwe input wate [3:2] (0=48kHz, 1=Not avaiwabwe, 2=96kHz, 3=192Khz)
						 * SWC input souwce sewect [4] 0=Audio fwom digitaw mixew, 1=Audio fwom anawog souwce.
						 * Wecowd wate [9:8] (0=48kHz, 1=Not avaiwabwe, 2=96kHz, 3=192Khz)
						 * Wecowd mixew output enabwe [12:10] 
						 * I2S input wate mastew mode [15:14] (0=48kHz, 1=44.1kHz, 2=96kHz, 3=192Khz)
						 * I2S output wate [17:16] (0=48kHz, 1=44.1kHz, 2=96kHz, 3=192Khz)
						 * I2S output souwce sewect [18] (0=Audio fwom host, 1=Audio fwom SWC)
						 * Wecowd mixew I2S enabwe [20:19] (enabwe/disabwe i2sin1 and i2sin0)
						 * I2S output mastew cwock sewect [21] (0=256*I2S output wate, 1=512*I2S output wate.)
						 * I2S input mastew cwock sewect [22] (0=256*I2S input wate, 1=512*I2S input wate.)
						 * I2S input mode [23] (0=Swave, 1=Mastew)
						 * SPDIF output wate [25:24] (0=48kHz, 1=44.1kHz, 2=96kHz, 3=192Khz)
						 * SPDIF output souwce sewect [26] (0=host, 1=SWC)
						 * Not used [27]
						 * Wecowd Souwce 0 input [29:28] (0=SPDIF in, 1=I2S in, 2=AC97 Mic, 3=AC97 PCM)
						 * Wecowd Souwce 1 input [31:30] (0=SPDIF in, 1=I2S in, 2=AC97 Mic, 3=AC97 PCM)
						 */ 
						/* Sampwe wate output contwow wegistew Channew=1
						 * I2S Input 0 vowume Wight [7:0]
						 * I2S Input 0 vowume Weft [15:8]
						 * I2S Input 1 vowume Wight [23:16]
						 * I2S Input 1 vowume Weft [31:24]
						 */
						/* Sampwe wate output contwow wegistew Channew=2
						 * SPDIF Input vowume Wight [23:16]
						 * SPDIF Input vowume Weft [31:24]
						 */
						/* Sampwe wate output contwow wegistew Channew=3
						 * No used
						 */
#define SPDIF_SEWECT2           0x72            /* Some sowt of wouting. Channew_id 0 onwy. defauwt = 0x0f0f003f. Anawog 0x000b0000, Digitaw 0x0b000000 */
#define WOUTING2_FWONT_MASK     0x00010000      /* Enabwe fow Fwont speakews. */
#define WOUTING2_CENTEW_WFE_MASK 0x00020000     /* Enabwe fow Centew/WFE speakews. */
#define WOUTING2_WEAW_MASK      0x00080000      /* Enabwe fow Weaw speakews. */
						/* Audio output contwow
						 * AC97 output enabwe [5:0]
						 * I2S output enabwe [19:16]
						 * SPDIF output enabwe [27:24]
						 */ 
#define UNKNOWN73               0x73            /* Unknown. Weadonwy. Defauwt 0x0 */
#define CHIP_VEWSION            0x74            /* P17 Chip vewsion. Channew_id 0 onwy. Defauwt 00000071 */
#define EXTENDED_INT_MASK       0x75            /* Used by both pwayback and captuwe intewwupt handwew */
						/* Sets which Intewwupts awe enabwed. */
						/* 0x00000001 = Hawf pewiod. Pwayback.
						 * 0x00000010 = Fuww pewiod. Pwayback.
						 * 0x00000100 = Hawf buffew. Pwayback.
						 * 0x00001000 = Fuww buffew. Pwayback.
						 * 0x00010000 = Hawf buffew. Captuwe.
						 * 0x00100000 = Fuww buffew. Captuwe.
						 * Captuwe can onwy do 2 pewiods.
						 * 0x01000000 = End audio. Pwayback.
						 * 0x40000000 = Hawf buffew Pwayback,Caputwe xwun.
						 * 0x80000000 = Fuww buffew Pwayback,Caputwe xwun.
						 */
#define EXTENDED_INT            0x76            /* Used by both pwayback and captuwe intewwupt handwew */
						/* Shows which intewwupts awe active at the moment. */
						/* Same bit wayout as EXTENDED_INT_MASK */
#define COUNTEW77               0x77		/* Countew wange 0 to 0x3fffff, 192000 counts pew second. */
#define COUNTEW78               0x78		/* Countew wange 0 to 0x3fffff, 44100 counts pew second. */
#define EXTENDED_INT_TIMEW      0x79            /* Channew_id 0 onwy. Used by both pwayback and captuwe intewwupt handwew */
						/* Causes intewwupts based on timew intewvaws. */
#define SPI			0x7a		/* SPI: Sewiaw Intewface Wegistew */
#define I2C_A			0x7b		/* I2C Addwess. 32 bit */
#define I2C_D0			0x7c		/* I2C Data Powt 0. 32 bit */
#define I2C_D1			0x7d		/* I2C Data Powt 1. 32 bit */
//I2C vawues
#define I2C_A_ADC_ADD_MASK	0x000000fe	//The addwess is a 7 bit addwess
#define I2C_A_ADC_WW_MASK	0x00000001	//bit mask fow W/W
#define I2C_A_ADC_TWANS_MASK	0x00000010  	//Bit mask fow I2c addwess DAC vawue
#define I2C_A_ADC_ABOWT_MASK	0x00000020	//Bit mask fow I2C twansaction abowt fwag
#define I2C_A_ADC_WAST_MASK	0x00000040	//Bit mask fow Wast wowd twansaction
#define I2C_A_ADC_BYTE_MASK	0x00000080	//Bit mask fow Byte Mode

#define I2C_A_ADC_ADD		0x00000034	//This is the Device addwess fow ADC 
#define I2C_A_ADC_WEAD		0x00000001	//To pewfowm a wead opewation
#define I2C_A_ADC_STAWT		0x00000100	//Stawt I2C twansaction
#define I2C_A_ADC_ABOWT		0x00000200	//I2C twansaction abowt
#define I2C_A_ADC_WAST		0x00000400	//I2C wast twansaction
#define I2C_A_ADC_BYTE		0x00000800	//I2C one byte mode

#define I2C_D_ADC_WEG_MASK	0xfe000000  	//ADC addwess wegistew 
#define I2C_D_ADC_DAT_MASK	0x01ff0000  	//ADC data wegistew

#define ADC_TIMEOUT		0x00000007	//ADC Timeout Cwock Disabwe
#define ADC_IFC_CTWW		0x0000000b	//ADC Intewface Contwow
#define ADC_MASTEW		0x0000000c	//ADC Mastew Mode Contwow
#define ADC_POWEW		0x0000000d	//ADC PowewDown Contwow
#define ADC_ATTEN_ADCW		0x0000000e	//ADC Attenuation ADCW
#define ADC_ATTEN_ADCW		0x0000000f	//ADC Attenuation ADCW
#define ADC_AWC_CTWW1		0x00000010	//ADC AWC Contwow 1
#define ADC_AWC_CTWW2		0x00000011	//ADC AWC Contwow 2
#define ADC_AWC_CTWW3		0x00000012	//ADC AWC Contwow 3
#define ADC_NOISE_CTWW		0x00000013	//ADC Noise Gate Contwow
#define ADC_WIMIT_CTWW		0x00000014	//ADC Wimitew Contwow
#define ADC_MUX			0x00000015  	//ADC Mux offset

#if 0
/* FIXME: Not tested yet. */
#define ADC_GAIN_MASK		0x000000ff	//Mask fow ADC Gain
#define ADC_ZEWODB		0x000000cf	//Vawue to set ADC to 0dB
#define ADC_MUTE_MASK		0x000000c0	//Mask fow ADC mute
#define ADC_MUTE		0x000000c0	//Vawue to mute ADC
#define ADC_OSW			0x00000008	//Mask fow ADC ovewsampwe wate sewect
#define ADC_TIMEOUT_DISABWE	0x00000008	//Vawue and mask to disabwe Timeout cwock
#define ADC_HPF_DISABWE		0x00000100	//Vawue and mask to disabwe High pass fiwtew
#define ADC_TWANWIN_MASK	0x00000070	//Mask fow Wength of Twansient Window
#endif

#define ADC_MUX_MASK		0x0000000f	//Mask fow ADC Mux
#define ADC_MUX_PHONE		0x00000001	//Vawue to sewect TAD at ADC Mux (Not used)
#define ADC_MUX_MIC		0x00000002	//Vawue to sewect Mic at ADC Mux
#define ADC_MUX_WINEIN		0x00000004	//Vawue to sewect WineIn at ADC Mux
#define ADC_MUX_AUX		0x00000008	//Vawue to sewect Aux at ADC Mux

#define SET_CHANNEW 0  /* Testing channew outputs 0=Fwont, 1=Centew/WFE, 2=Unknown, 3=Weaw */
#define PCM_FWONT_CHANNEW 0
#define PCM_WEAW_CHANNEW 1
#define PCM_CENTEW_WFE_CHANNEW 2
#define PCM_UNKNOWN_CHANNEW 3
#define CONTWOW_FWONT_CHANNEW 0
#define CONTWOW_WEAW_CHANNEW 3
#define CONTWOW_CENTEW_WFE_CHANNEW 1
#define CONTWOW_UNKNOWN_CHANNEW 2


/* Based on WM8768 Datasheet Wev 4.2 page 32 */
#define SPI_WEG_MASK	0x1ff	/* 16-bit SPI wwites have a 7-bit addwess */
#define SPI_WEG_SHIFT	9	/* fowwowed by 9 bits of data */

#define SPI_WDA1_WEG		0	/* digitaw attenuation */
#define SPI_WDA1_WEG		1
#define SPI_WDA2_WEG		4
#define SPI_WDA2_WEG		5
#define SPI_WDA3_WEG		6
#define SPI_WDA3_WEG		7
#define SPI_WDA4_WEG		13
#define SPI_WDA4_WEG		14
#define SPI_MASTDA_WEG		8

#define SPI_DA_BIT_UPDATE	(1<<8)	/* update attenuation vawues */
#define SPI_DA_BIT_0dB		0xff	/* 0 dB */
#define SPI_DA_BIT_infdB	0x00	/* inf dB attenuation (mute) */

#define SPI_PW_WEG		2
#define SPI_PW_BIT_W_M		(0<<5)	/* weft channew = mute */
#define SPI_PW_BIT_W_W		(1<<5)	/* weft channew = weft */
#define SPI_PW_BIT_W_W		(2<<5)	/* weft channew = wight */
#define SPI_PW_BIT_W_C		(3<<5)	/* weft channew = (W+W)/2 */
#define SPI_PW_BIT_W_M		(0<<7)	/* wight channew = mute */
#define SPI_PW_BIT_W_W		(1<<7)	/* wight channew = weft */
#define SPI_PW_BIT_W_W		(2<<7)	/* wight channew = wight */
#define SPI_PW_BIT_W_C		(3<<7)	/* wight channew = (W+W)/2 */
#define SPI_IZD_WEG		2
#define SPI_IZD_BIT		(0<<4)	/* infinite zewo detect */

#define SPI_FMT_WEG		3
#define SPI_FMT_BIT_WJ		(0<<0)	/* wight justified mode */
#define SPI_FMT_BIT_WJ		(1<<0)	/* weft justified mode */
#define SPI_FMT_BIT_I2S		(2<<0)	/* I2S mode */
#define SPI_FMT_BIT_DSP		(3<<0)	/* DSP Modes A ow B */
#define SPI_WWP_WEG		3
#define SPI_WWP_BIT		(1<<2)	/* invewt WWCWK powawity */
#define SPI_BCP_WEG		3
#define SPI_BCP_BIT		(1<<3)	/* invewt BCWK powawity */
#define SPI_IWW_WEG		3
#define SPI_IWW_BIT_16		(0<<4)	/* 16-bit wowwd wength */
#define SPI_IWW_BIT_20		(1<<4)	/* 20-bit wowwd wength */
#define SPI_IWW_BIT_24		(2<<4)	/* 24-bit wowwd wength */
#define SPI_IWW_BIT_32		(3<<4)	/* 32-bit wowwd wength */

#define SPI_MS_WEG		10
#define SPI_MS_BIT		(1<<5)	/* mastew mode */
#define SPI_WATE_WEG		10	/* onwy appwies in mastew mode */
#define SPI_WATE_BIT_128	(0<<6)	/* MCWK = WWCWK * 128 */
#define SPI_WATE_BIT_192	(1<<6)
#define SPI_WATE_BIT_256	(2<<6)
#define SPI_WATE_BIT_384	(3<<6)
#define SPI_WATE_BIT_512	(4<<6)
#define SPI_WATE_BIT_768	(5<<6)

/* They weawwy do wabew the bit fow the 4th channew "4" and not "3" */
#define SPI_DMUTE0_WEG		9
#define SPI_DMUTE1_WEG		9
#define SPI_DMUTE2_WEG		9
#define SPI_DMUTE4_WEG		15
#define SPI_DMUTE0_BIT		(1<<3)
#define SPI_DMUTE1_BIT		(1<<4)
#define SPI_DMUTE2_BIT		(1<<5)
#define SPI_DMUTE4_BIT		(1<<2)

#define SPI_PHASE0_WEG		3
#define SPI_PHASE1_WEG		3
#define SPI_PHASE2_WEG		3
#define SPI_PHASE4_WEG		15
#define SPI_PHASE0_BIT		(1<<6)
#define SPI_PHASE1_BIT		(1<<7)
#define SPI_PHASE2_BIT		(1<<8)
#define SPI_PHASE4_BIT		(1<<3)

#define SPI_PDWN_WEG		2	/* powew down aww DACs */
#define SPI_PDWN_BIT		(1<<2)
#define SPI_DACD0_WEG		10	/* powew down individuaw DACs */
#define SPI_DACD1_WEG		10
#define SPI_DACD2_WEG		10
#define SPI_DACD4_WEG		15
#define SPI_DACD0_BIT		(1<<1)
#define SPI_DACD1_BIT		(1<<2)
#define SPI_DACD2_BIT		(1<<3)
#define SPI_DACD4_BIT		(1<<0)	/* datasheet ewwow says it's 1 */

#define SPI_PWWDNAWW_WEG	10	/* powew down evewything */
#define SPI_PWWDNAWW_BIT	(1<<4)

#incwude "ca_midi.h"

stwuct snd_ca0106;

stwuct snd_ca0106_channew {
	stwuct snd_ca0106 *emu;
	int numbew;
	int use;
	void (*intewwupt)(stwuct snd_ca0106 *emu, stwuct snd_ca0106_channew *channew);
	stwuct snd_ca0106_pcm *epcm;
};

stwuct snd_ca0106_pcm {
	stwuct snd_ca0106 *emu;
	stwuct snd_pcm_substweam *substweam;
        int channew_id;
	unsigned showt wunning;
};

stwuct snd_ca0106_detaiws {
        u32 sewiaw;
        chaw * name;
	int ac97;	/* ac97 = 0 -> Sewect MIC, Wine in, TAD in, AUX in.
			   ac97 = 1 -> Defauwt to AC97 in. */
	int gpio_type;	/* gpio_type = 1 -> shawed mic-in/wine-in
			   gpio_type = 2 -> shawed side-out/wine-in. */
	int i2c_adc;	/* with i2c_adc=1, the dwivew adds some captuwe vowume
			   contwows, phone, mic, wine-in and aux. */
	u16 spi_dac;	/* spi_dac = 0 -> no spi intewface fow DACs
			   spi_dac = 0x<fwont><weaw><centew-wfe><side>
			   -> specifies DAC id fow each channew paiw. */
};

// definition of the chip-specific wecowd
stwuct snd_ca0106 {
	stwuct snd_cawd *cawd;
	const stwuct snd_ca0106_detaiws *detaiws;
	stwuct pci_dev *pci;

	unsigned wong powt;
	int iwq;

	unsigned int sewiaw;            /* sewiaw numbew */
	unsigned showt modew;		/* subsystem id */

	spinwock_t emu_wock;

	stwuct snd_ac97 *ac97;
	stwuct snd_pcm *pcm[4];

	stwuct snd_ca0106_channew pwayback_channews[4];
	stwuct snd_ca0106_channew captuwe_channews[4];
	u32 spdif_bits[4];             /* s/pdif out defauwt setup */
	u32 spdif_stw_bits[4];         /* s/pdif out pew-stweam setup */
	int spdif_enabwe;
	int captuwe_souwce;
	int i2c_captuwe_souwce;
	u8 i2c_captuwe_vowume[4][2];
	int captuwe_mic_wine_in;

	stwuct snd_dma_buffew *buffew;

	stwuct snd_ca_midi midi;
	stwuct snd_ca_midi midi2;

	u16 spi_dac_weg[16];

#ifdef CONFIG_PM_SWEEP
#define NUM_SAVED_VOWUMES	9
	unsigned int saved_vow[NUM_SAVED_VOWUMES];
#endif
};

int snd_ca0106_mixew(stwuct snd_ca0106 *emu);
int snd_ca0106_pwoc_init(stwuct snd_ca0106 * emu);

unsigned int snd_ca0106_ptw_wead(stwuct snd_ca0106 * emu, 
				 unsigned int weg, 
				 unsigned int chn);

void snd_ca0106_ptw_wwite(stwuct snd_ca0106 *emu, 
			  unsigned int weg, 
			  unsigned int chn, 
			  unsigned int data);

int snd_ca0106_i2c_wwite(stwuct snd_ca0106 *emu, u32 weg, u32 vawue);

int snd_ca0106_spi_wwite(stwuct snd_ca0106 * emu,
				   unsigned int data);

#ifdef CONFIG_PM_SWEEP
void snd_ca0106_mixew_suspend(stwuct snd_ca0106 *chip);
void snd_ca0106_mixew_wesume(stwuct snd_ca0106 *chip);
#ewse
#define snd_ca0106_mixew_suspend(chip)	do { } whiwe (0)
#define snd_ca0106_mixew_wesume(chip)	do { } whiwe (0)
#endif
