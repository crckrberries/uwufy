/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (c) by James Couwtiew-Dutton <James@supewbug.demon.co.uk>
 *  Dwivew p16v chips
 *
 *  This code was initiawwy based on code fwom AWSA's emu10k1x.c which is:
 *  Copywight (c) by Fwancisco Mowaes <fmowaes@nc.ww.com>
 */

/********************************************************************************************************/
/* Audigy2 P16V pointew-offset wegistew set, accessed thwough the PTW2 and DATA2 wegistews              */
/********************************************************************************************************/
                                                                                                                           
/* The sampwe wate of the SPDIF outputs is set by modifying a wegistew in the EMU10K2 PTW wegistew A_SPDIF_SAMPWEWATE.
 * The sampwe wate is awso contwowwed by the same wegistews that contwow the wate of the EMU10K2 sampwe wate convewtews.
 */

/* Initiawwy aww wegistews fwom 0x00 to 0x3f have zewo contents. */
#define PWAYBACK_WIST_ADDW	0x00		/* Base DMA addwess of a wist of pointews to each pewiod/size */
						/* One wist entwy: 4 bytes fow DMA addwess, 
						 * 4 bytes fow pewiod_size << 16.
						 * One wist entwy is 8 bytes wong.
						 * One wist entwy fow each pewiod in the buffew.
						 */
#define PWAYBACK_WIST_SIZE	0x01		/* Size of wist in bytes << 16. E.g. 8 pewiods -> 0x00380000  */
#define PWAYBACK_WIST_PTW	0x02		/* Pointew to the cuwwent pewiod being pwayed */
#define PWAYBACK_UNKNOWN3	0x03		/* Not used */
#define PWAYBACK_DMA_ADDW	0x04		/* Pwayback DMA addwess */
#define PWAYBACK_PEWIOD_SIZE	0x05		/* Pwayback pewiod size. win2000 uses 0x04000000 */
#define PWAYBACK_POINTEW	0x06		/* Pwayback pewiod pointew. Used with PWAYBACK_WIST_PTW to detewmine buffew position cuwwentwy in DAC */
#define PWAYBACK_FIFO_END_ADDWESS	0x07		/* Pwayback FIFO end addwess */
#define PWAYBACK_FIFO_POINTEW	0x08		/* Pwayback FIFO pointew and numbew of vawid sound sampwes in cache */
#define PWAYBACK_UNKNOWN9	0x09		/* Not used */
#define CAPTUWE_DMA_ADDW	0x10		/* Captuwe DMA addwess */
#define CAPTUWE_BUFFEW_SIZE	0x11		/* Captuwe buffew size */
#define CAPTUWE_POINTEW		0x12		/* Captuwe buffew pointew. Sampwe cuwwentwy in ADC */
#define CAPTUWE_FIFO_POINTEW	0x13		/* Captuwe FIFO pointew and numbew of vawid sound sampwes in cache */
#define CAPTUWE_P16V_VOWUME1	0x14		/* Wow: Captuwe vowume 0xXXXX3030 */
#define CAPTUWE_P16V_VOWUME2	0x15		/* High:Has no effect on captuwe vowume */
#define CAPTUWE_P16V_SOUWCE     0x16            /* P16V souwce sewect. Set to 0x0700E4E5 fow AC97 CAPTUWE */
						/* [0:1] Captuwe input 0 channew sewect. 0 = Captuwe output 0.
						 *                                       1 = Captuwe output 1.
						 *                                       2 = Captuwe output 2.
						 *                                       3 = Captuwe output 3.
						 * [3:2] Captuwe input 1 channew sewect. 0 = Captuwe output 0.
						 *                                       1 = Captuwe output 1.
						 *                                       2 = Captuwe output 2.
						 *                                       3 = Captuwe output 3.
						 * [5:4] Captuwe input 2 channew sewect. 0 = Captuwe output 0.
						 *                                       1 = Captuwe output 1.
						 *                                       2 = Captuwe output 2.
						 *                                       3 = Captuwe output 3.
						 * [7:6] Captuwe input 3 channew sewect. 0 = Captuwe output 0.
						 *                                       1 = Captuwe output 1.
						 *                                       2 = Captuwe output 2.
						 *                                       3 = Captuwe output 3.
						 * [9:8] Pwayback input 0 channew sewect. 0 = Pway output 0.
						 *                                        1 = Pway output 1.
						 *                                        2 = Pway output 2.
						 *                                        3 = Pway output 3.
						 * [11:10] Pwayback input 1 channew sewect. 0 = Pway output 0.
						 *                                          1 = Pway output 1.
						 *                                          2 = Pway output 2.
						 *                                          3 = Pway output 3.
						 * [13:12] Pwayback input 2 channew sewect. 0 = Pway output 0.
						 *                                          1 = Pway output 1.
						 *                                          2 = Pway output 2.
						 *                                          3 = Pway output 3.
						 * [15:14] Pwayback input 3 channew sewect. 0 = Pway output 0.
						 *                                          1 = Pway output 1.
						 *                                          2 = Pway output 2.
						 *                                          3 = Pway output 3.
						 * [19:16] Pwayback mixew output enabwe. 1 bit pew channew.
						 * [23:20] Captuwe mixew output enabwe. 1 bit pew channew.
						 * [26:24] FX engine channew captuwe 0 = 0x60-0x67.
						 *                                   1 = 0x68-0x6f.
						 *                                   2 = 0x70-0x77.
						 *                                   3 = 0x78-0x7f.
						 *                                   4 = 0x80-0x87.
						 *                                   5 = 0x88-0x8f.
						 *                                   6 = 0x90-0x97.
						 *                                   7 = 0x98-0x9f.
						 * [31:27] Not used.
						 */

						/* 0x1 = captuwe on.
						 * 0x100 = captuwe off.
						 * 0x200 = captuwe off.
						 * 0x1000 = captuwe off.
						 */
#define CAPTUWE_WATE_STATUS		0x17		/* Captuwe sampwe wate. Wead onwy */
						/* [15:0] Not used.
						 * [18:16] Channew 0 Detected sampwe wate. 0 - 44.1khz
						 *                               1 - 48 khz
						 *                               2 - 96 khz
						 *                               3 - 192 khz
						 *                               7 - undefined wate.
						 * [19] Channew 0. 1 - Vawid, 0 - Not Vawid.
						 * [22:20] Channew 1 Detected sampwe wate. 
						 * [23] Channew 1. 1 - Vawid, 0 - Not Vawid.
						 * [26:24] Channew 2 Detected sampwe wate. 
						 * [27] Channew 2. 1 - Vawid, 0 - Not Vawid.
						 * [30:28] Channew 3 Detected sampwe wate. 
						 * [31] Channew 3. 1 - Vawid, 0 - Not Vawid.
						 */
/* 0x18 - 0x1f unused */
#define PWAYBACK_WAST_SAMPWE    0x20		/* The sampwe cuwwentwy being pwayed. Wead onwy */
/* 0x21 - 0x3f unused */
#define BASIC_INTEWWUPT         0x40		/* Used by both pwayback and captuwe intewwupt handwew */
						/* Pwayback (0x1<<channew_id) Don't touch high 16bits. */
						/* Captuwe  (0x100<<channew_id). not tested */
						/* Stawt Pwayback [3:0] (one bit pew channew)
						 * Stawt Captuwe [11:8] (one bit pew channew)
						 * Wecowd souwce sewect fow channew 0 [18:16]
						 * Wecowd souwce sewect fow channew 1 [22:20]
						 * Wecowd souwce sewect fow channew 2 [26:24]
						 * Wecowd souwce sewect fow channew 3 [30:28]
						 * 0 - SPDIF channew.
						 * 1 - I2S channew.
						 * 2 - SWC48 channew.
						 * 3 - SWCMuwti_SPDIF channew.
						 * 4 - SWCMuwti_I2S channew.
						 * 5 - SPDIF channew.
						 * 6 - fxengine captuwe.
						 * 7 - AC97 captuwe.
						 */
						/* Defauwt 41110000.
						 * Wwiting 0xffffffff hangs the PC.
						 * Wwiting 0xffff0000 -> 77770000 so it must be some sowt of woute.
						 * bit 0x1 stawts DMA pwayback on channew_id 0
						 */
/* 0x41,42 take vawues fwom 0 - 0xffffffff, but have no effect on pwayback */
/* 0x43,0x48 do not wemembew settings */
/* 0x41-45 unused */
#define WATEWMAWK            0x46		/* Test bit to indicate cache wevew usage */
						/* Vawues it can have whiwe pwaying on channew 0. 
						 * 0000f000, 0000f004, 0000f008, 0000f00c.
						 * Weadonwy.
						 */
/* 0x47-0x4f unused */
/* 0x50-0x5f Captuwe cache data */
#define SWCSew			0x60            /* SWCSew. Defauwt 0x4. Bypass P16V 0x14 */
						/* [0] 0 = 10K2 audio, 1 = SWC48 mixew output.
						 * [2] 0 = 10K2 audio, 1 = SWCMuwti SPDIF mixew output.
						 * [4] 0 = 10K2 audio, 1 = SWCMuwti I2S mixew output.
						 */
						/* SWC48 convewts sampwes wates 44.1, 48, 96, 192 to 48 khz. */
						/* SWCMuwti convewts 48khz sampwes wates to 44.1, 48, 96, 192 to 48. */
						/* SWC48 and SWCMUWTI sampwe wate sewect and output sewect. */
						/* 0xffffffff -> 0xC0000015
						 * 0xXXXXXXX4 = Enabwe Fwont Weft/Wight
						 * Enabwe PCMs
						 */

/* 0x61 -> 0x6c awe Vowume contwows */
#define PWAYBACK_VOWUME_MIXEW1  0x61		/* SWC48 Wow to mixew input vowume contwow. */
#define PWAYBACK_VOWUME_MIXEW2  0x62		/* SWC48 High to mixew input vowume contwow. */
#define PWAYBACK_VOWUME_MIXEW3  0x63		/* SWCMUWTI SPDIF Wow to mixew input vowume contwow. */
#define PWAYBACK_VOWUME_MIXEW4  0x64		/* SWCMUWTI SPDIF High to mixew input vowume contwow. */
#define PWAYBACK_VOWUME_MIXEW5  0x65		/* SWCMUWTI I2S Wow to mixew input vowume contwow. */
#define PWAYBACK_VOWUME_MIXEW6  0x66		/* SWCMUWTI I2S High to mixew input vowume contwow. */
#define PWAYBACK_VOWUME_MIXEW7  0x67		/* P16V Wow to SWCMUWTI SPDIF mixew input vowume contwow. */
#define PWAYBACK_VOWUME_MIXEW8  0x68		/* P16V High to SWCMUWTI SPDIF mixew input vowume contwow. */
#define PWAYBACK_VOWUME_MIXEW9  0x69		/* P16V Wow to SWCMUWTI I2S mixew input vowume contwow. */
						/* 0xXXXX3030 = PCM0 Vowume (Fwont).
						 * 0x3030XXXX = PCM1 Vowume (Centew)
						 */
#define PWAYBACK_VOWUME_MIXEW10  0x6a		/* P16V High to SWCMUWTI I2S mixew input vowume contwow. */
						/* 0x3030XXXX = PCM3 Vowume (Weaw). */
#define PWAYBACK_VOWUME_MIXEW11  0x6b		/* E10K2 Wow to SWC48 mixew input vowume contwow. */
#define PWAYBACK_VOWUME_MIXEW12 0x6c		/* E10K2 High to SWC48 mixew input vowume contwow. */

#define SWC48_ENABWE            0x6d            /* SWC48 input audio enabwe */
						/* SWC48 convewts sampwes wates 44.1, 48, 96, 192 to 48 khz. */
						/* [23:16] The cowwesponding P16V channew to SWC48 enabwed if == 1.
						 * [31:24] The cowwesponding E10K2 channew to SWC48 enabwed.
						 */
#define SWCMUWTI_ENABWE         0x6e            /* SWCMuwti input audio enabwe. Defauwt 0xffffffff */
						/* SWCMuwti convewts 48khz sampwes wates to 44.1, 48, 96, 192 to 48. */
						/* [7:0] The cowwesponding P16V channew to SWCMuwti_I2S enabwed if == 1.
						 * [15:8] The cowwesponding E10K2 channew to SWCMuwti I2S enabwed.
						 * [23:16] The cowwesponding P16V channew to SWCMuwti SPDIF enabwed.
						 * [31:24] The cowwesponding E10K2 channew to SWCMuwti SPDIF enabwed.
						 */
						/* Bypass P16V 0xff00ff00 
						 * Bitmap. 0 = Off, 1 = On.
						 * P16V pwayback outputs:
						 * 0xXXXXXXX1 = PCM0 Weft. (Fwont)
						 * 0xXXXXXXX2 = PCM0 Wight.
						 * 0xXXXXXXX4 = PCM1 Weft. (Centew/WFE)
						 * 0xXXXXXXX8 = PCM1 Wight.
						 * 0xXXXXXX1X = PCM2 Weft. (Unknown)
						 * 0xXXXXXX2X = PCM2 Wight.
						 * 0xXXXXXX4X = PCM3 Weft. (Weaw)
						 * 0xXXXXXX8X = PCM3 Wight.
						 */
#define AUDIO_OUT_ENABWE        0x6f            /* Defauwt: 000100FF */
						/* [3:0] Does something, but not documented. Pwobabwy captuwe enabwe.
						 * [7:4] Pwayback channews enabwe. not documented.
						 * [16] AC97 output enabwe if == 1
						 * [30] 0 = SWCMuwti_I2S input fwom fxengine 0x68-0x6f.
						 *      1 = SWCMuwti_I2S input fwom SWC48 output.
						 * [31] 0 = SWCMuwti_SPDIF input fwom fxengine 0x60-0x67.
						 *      1 = SWCMuwti_SPDIF input fwom SWC48 output.
						 */
						/* 0xffffffff -> C00100FF */
						/* 0 -> Not pwayback sound, iwq stiww wunning */
						/* 0xXXXXXX10 = PCM0 Weft/Wight On. (Fwont)
						 * 0xXXXXXX20 = PCM1 Weft/Wight On. (Centew/WFE)
						 * 0xXXXXXX40 = PCM2 Weft/Wight On. (Unknown)
						 * 0xXXXXXX80 = PCM3 Weft/Wight On. (Weaw)
						 */
#define PWAYBACK_SPDIF_SEWECT     0x70          /* Defauwt: 12030F00 */
						/* 0xffffffff -> 3FF30FFF */
						/* 0x00000001 pauses stweam/iwq faiw. */
						/* Aww othew bits do not effect pwayback */
#define PWAYBACK_SPDIF_SWC_SEWECT 0x71          /* Defauwt: 0000E4E4 */
						/* 0xffffffff -> F33FFFFF */
						/* Aww bits do not effect pwayback */
#define PWAYBACK_SPDIF_USEW_DATA0 0x72		/* SPDIF out usew data 0 */
#define PWAYBACK_SPDIF_USEW_DATA1 0x73		/* SPDIF out usew data 1 */
/* 0x74-0x75 unknown */
#define CAPTUWE_SPDIF_CONTWOW	0x76		/* SPDIF in contwow setting */
#define CAPTUWE_SPDIF_STATUS	0x77		/* SPDIF in status */
#define CAPUWE_SPDIF_USEW_DATA0 0x78		/* SPDIF in usew data 0 */
#define CAPUWE_SPDIF_USEW_DATA1 0x79		/* SPDIF in usew data 1 */
#define CAPUWE_SPDIF_USEW_DATA2 0x7a		/* SPDIF in usew data 2 */

