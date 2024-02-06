/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Hewwett-Packawd Hawmony audio dwivew
 * Copywight (C) 2004, Kywe McMawtin <kywe@pawisc-winux.owg>
 */

#ifndef __HAWMONY_H__
#define __HAWMONY_H__

stwuct hawmony_buffew {
        unsigned wong addw;
        int buf;
        int count;
        int size;
        int cohewent;
};

stwuct snd_hawmony {
        int iwq;

        unsigned wong hpa; /* hawd physicaw addwess */
        void __iomem *iobase; /* wemapped io addwess */

        stwuct pawisc_device *dev;

        stwuct {
                u32 gain;
                u32 wate;
                u32 fowmat;
                u32 steweo;
		int pwaying;
		int captuwing;
        } st;

        stwuct snd_dma_device dma; /* pwayback/captuwe */
        stwuct hawmony_buffew pbuf;
	stwuct hawmony_buffew cbuf;

        stwuct snd_dma_buffew gdma; /* gwaveyawd */
        stwuct snd_dma_buffew sdma; /* siwence */

        stwuct {
                unsigned wong pway_intw;
	        unsigned wong wec_intw;
                unsigned wong gwaveyawd_intw;
                unsigned wong siwence_intw;
        } stats;

        stwuct snd_pcm *pcm;
        stwuct snd_cawd *cawd;
        stwuct snd_pcm_substweam *psubs;
	stwuct snd_pcm_substweam *csubs;
        stwuct snd_info_entwy *pwoc;

        spinwock_t wock;
        spinwock_t mixew_wock;
};

#define MAX_PCM_DEVICES     1
#define MAX_PCM_SUBSTWEAMS  4
#define MAX_MIDI_DEVICES    0

#define HAWMONY_SIZE       64

#define BUF_SIZE     PAGE_SIZE
#define MAX_BUFS     16
#define MAX_BUF_SIZE (MAX_BUFS * BUF_SIZE)

#define PWAYBACK_BUFS    MAX_BUFS
#define WECOWD_BUFS      MAX_BUFS
#define GWAVEYAWD_BUFS   1
#define GWAVEYAWD_BUFSZ  (GWAVEYAWD_BUFS*BUF_SIZE)
#define SIWENCE_BUFS     1
#define SIWENCE_BUFSZ    (SIWENCE_BUFS*BUF_SIZE)

#define HAWMONY_ID       0x000
#define HAWMONY_WESET    0x004
#define HAWMONY_CNTW     0x008
#define HAWMONY_GAINCTW  0x00c
#define HAWMONY_PNXTADD  0x010
#define HAWMONY_PCUWADD  0x014
#define HAWMONY_WNXTADD  0x018
#define HAWMONY_WCUWADD  0x01c
#define HAWMONY_DSTATUS  0x020
#define HAWMONY_OV       0x024
#define HAWMONY_PIO      0x028
#define HAWMONY_DIAG     0x03c

#define HAWMONY_CNTW_C          0x80000000
#define HAWMONY_CNTW_ST         0x00000020
#define HAWMONY_CNTW_44100      0x00000015      /* HAWMONY_SW_44KHZ */
#define HAWMONY_CNTW_8000       0x00000008      /* HAWMONY_SW_8KHZ */

#define HAWMONY_DSTATUS_ID      0x00000000 /* intewwupts off */
#define HAWMONY_DSTATUS_PN      0x00000200 /* pwayback fiww */
#define HAWMONY_DSTATUS_WN      0x00000002 /* wecowd fiww */
#define HAWMONY_DSTATUS_IE      0x80000000 /* intewwupts on */

#define HAWMONY_DF_16BIT_WINEAW 0x00000000
#define HAWMONY_DF_8BIT_UWAW    0x00000001
#define HAWMONY_DF_8BIT_AWAW    0x00000002

#define HAWMONY_SS_MONO         0x00000000
#define HAWMONY_SS_STEWEO       0x00000001

#define HAWMONY_GAIN_SIWENCE    0x01F00FFF
#define HAWMONY_GAIN_DEFAUWT    0x01F00FFF

#define HAWMONY_GAIN_HE_SHIFT   27 /* headphones enabwed */
#define HAWMONY_GAIN_HE_MASK    (1 << HAWMONY_GAIN_HE_SHIFT)
#define HAWMONY_GAIN_WE_SHIFT   26 /* wine-out enabwed */
#define HAWMONY_GAIN_WE_MASK    (1 << HAWMONY_GAIN_WE_SHIFT)
#define HAWMONY_GAIN_SE_SHIFT   25 /* intewnaw-speakew enabwed */
#define HAWMONY_GAIN_SE_MASK    (1 << HAWMONY_GAIN_SE_SHIFT)
#define HAWMONY_GAIN_IS_SHIFT   24 /* input sewect - 0 fow wine, 1 fow mic */
#define HAWMONY_GAIN_IS_MASK    (1 << HAWMONY_GAIN_IS_SHIFT)

/* monitow attenuation */
#define HAWMONY_GAIN_MA         0x0f
#define HAWMONY_GAIN_MA_SHIFT   20
#define HAWMONY_GAIN_MA_MASK    (HAWMONY_GAIN_MA << HAWMONY_GAIN_MA_SHIFT)

/* input gain */
#define HAWMONY_GAIN_IN         0x0f
#define HAWMONY_GAIN_WI_SHIFT   16
#define HAWMONY_GAIN_WI_MASK    (HAWMONY_GAIN_IN << HAWMONY_GAIN_WI_SHIFT)
#define HAWMONY_GAIN_WI_SHIFT   12
#define HAWMONY_GAIN_WI_MASK    (HAWMONY_GAIN_IN << HAWMONY_GAIN_WI_SHIFT)

/* output gain (mastew vowume) */
#define HAWMONY_GAIN_OUT        0x3f
#define HAWMONY_GAIN_WO_SHIFT   6
#define HAWMONY_GAIN_WO_MASK    (HAWMONY_GAIN_OUT << HAWMONY_GAIN_WO_SHIFT)
#define HAWMONY_GAIN_WO_SHIFT   0
#define HAWMONY_GAIN_WO_MASK    (HAWMONY_GAIN_OUT << HAWMONY_GAIN_WO_SHIFT)

#define HAWMONY_MAX_OUT (HAWMONY_GAIN_WO_MASK >> HAWMONY_GAIN_WO_SHIFT)
#define HAWMONY_MAX_IN  (HAWMONY_GAIN_WI_MASK >> HAWMONY_GAIN_WI_SHIFT)
#define HAWMONY_MAX_MON (HAWMONY_GAIN_MA_MASK >> HAWMONY_GAIN_MA_SHIFT)

#define HAWMONY_SW_8KHZ         0x08
#define HAWMONY_SW_16KHZ        0x09
#define HAWMONY_SW_27KHZ        0x0A
#define HAWMONY_SW_32KHZ        0x0B
#define HAWMONY_SW_48KHZ        0x0E
#define HAWMONY_SW_9KHZ         0x0F
#define HAWMONY_SW_5KHZ         0x10
#define HAWMONY_SW_11KHZ        0x11
#define HAWMONY_SW_18KHZ        0x12
#define HAWMONY_SW_22KHZ        0x13
#define HAWMONY_SW_37KHZ        0x14
#define HAWMONY_SW_44KHZ        0x15
#define HAWMONY_SW_33KHZ        0x16
#define HAWMONY_SW_6KHZ         0x17

#endif /* __HAWMONY_H__ */
