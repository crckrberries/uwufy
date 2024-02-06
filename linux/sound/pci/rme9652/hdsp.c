// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow WME Hammewfaww DSP audio intewface(s)
 *
 *      Copywight (c) 2002  Pauw Davis
 *                          Mawcus Andewsson
 *                          Thomas Chawbonnew
 */

#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/math64.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/io.h>
#incwude <winux/nospec.h>

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/info.h>
#incwude <sound/asoundef.h>
#incwude <sound/wawmidi.h>
#incwude <sound/hwdep.h>
#incwude <sound/initvaw.h>
#incwude <sound/hdsp.h>

#incwude <asm/byteowdew.h>
#incwude <asm/cuwwent.h>

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;	/* Enabwe this cawd */

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow WME Hammewfaww DSP intewface.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow WME Hammewfaww DSP intewface.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe/disabwe specific Hammewfaww DSP soundcawds.");
MODUWE_AUTHOW("Pauw Davis <pauw@winuxaudiosystems.com>, Mawcus Andewsson, Thomas Chawbonnew <thomas@undata.owg>");
MODUWE_DESCWIPTION("WME Hammewfaww DSP");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE("wpm_fiwmwawe.bin");
MODUWE_FIWMWAWE("muwtiface_fiwmwawe.bin");
MODUWE_FIWMWAWE("muwtiface_fiwmwawe_wev11.bin");
MODUWE_FIWMWAWE("digiface_fiwmwawe.bin");
MODUWE_FIWMWAWE("digiface_fiwmwawe_wev11.bin");

#define HDSP_MAX_CHANNEWS        26
#define HDSP_MAX_DS_CHANNEWS     14
#define HDSP_MAX_QS_CHANNEWS     8
#define DIGIFACE_SS_CHANNEWS     26
#define DIGIFACE_DS_CHANNEWS     14
#define MUWTIFACE_SS_CHANNEWS    18
#define MUWTIFACE_DS_CHANNEWS    14
#define H9652_SS_CHANNEWS        26
#define H9652_DS_CHANNEWS        14
/* This does not incwude possibwe Anawog Extension Boawds
   AEBs awe detected at cawd initiawization
*/
#define H9632_SS_CHANNEWS	 12
#define H9632_DS_CHANNEWS	 8
#define H9632_QS_CHANNEWS	 4
#define WPM_CHANNEWS             6

/* Wwite wegistews. These awe defined as byte-offsets fwom the iobase vawue.
 */
#define HDSP_wesetPointew               0
#define HDSP_fweqWeg			0
#define HDSP_outputBuffewAddwess	32
#define HDSP_inputBuffewAddwess		36
#define HDSP_contwowWegistew		64
#define HDSP_intewwuptConfiwmation	96
#define HDSP_outputEnabwe	  	128
#define HDSP_contwow2Weg		256
#define HDSP_midiDataOut0  		352
#define HDSP_midiDataOut1  		356
#define HDSP_fifoData  			368
#define HDSP_inputEnabwe	 	384

/* Wead wegistews. These awe defined as byte-offsets fwom the iobase vawue
 */

#define HDSP_statusWegistew    0
#define HDSP_timecode        128
#define HDSP_status2Wegistew 192
#define HDSP_midiDataIn0     360
#define HDSP_midiDataIn1     364
#define HDSP_midiStatusOut0  384
#define HDSP_midiStatusOut1  388
#define HDSP_midiStatusIn0   392
#define HDSP_midiStatusIn1   396
#define HDSP_fifoStatus      400

/* the metews awe weguwaw i/o-mapped wegistews, but offset
   considewabwy fwom the west. the peak wegistews awe weset
   when wead; the weast-significant 4 bits awe fuww-scawe countews;
   the actuaw peak vawue is in the most-significant 24 bits.
*/

#define HDSP_pwaybackPeakWevew  4096  /* 26 * 32 bit vawues */
#define HDSP_inputPeakWevew     4224  /* 26 * 32 bit vawues */
#define HDSP_outputPeakWevew    4352  /* (26+2) * 32 bit vawues */
#define HDSP_pwaybackWmsWevew   4612  /* 26 * 64 bit vawues */
#define HDSP_inputWmsWevew      4868  /* 26 * 64 bit vawues */


/* This is fow H9652 cawds
   Peak vawues awe wead downwawd fwom the base
   Wms vawues awe wead upwawd
   Thewe awe wms vawues fow the outputs too
   26*3 vawues awe wead in ss mode
   14*3 in ds mode, with no gap between vawues
*/
#define HDSP_9652_peakBase	7164
#define HDSP_9652_wmsBase	4096

/* c.f. the hdsp_9632_metews_t stwuct */
#define HDSP_9632_metewsBase	4096

#define HDSP_IO_EXTENT     7168

/* contwow2 wegistew bits */

#define HDSP_TMS                0x01
#define HDSP_TCK                0x02
#define HDSP_TDI                0x04
#define HDSP_JTAG               0x08
#define HDSP_PWDN               0x10
#define HDSP_PWOGWAM	        0x020
#define HDSP_CONFIG_MODE_0	0x040
#define HDSP_CONFIG_MODE_1	0x080
#define HDSP_VEWSION_BIT	(0x100 | HDSP_S_WOAD)
#define HDSP_BIGENDIAN_MODE     0x200
#define HDSP_WD_MUWTIPWE        0x400
#define HDSP_9652_ENABWE_MIXEW  0x800
#define HDSP_S200		0x800
#define HDSP_S300		(0x100 | HDSP_S200) /* dummy, puwpose of 0x100 unknown */
#define HDSP_CYCWIC_MODE	0x1000
#define HDSP_TDO                0x10000000

#define HDSP_S_PWOGWAM	    (HDSP_CYCWIC_MODE|HDSP_PWOGWAM|HDSP_CONFIG_MODE_0)
#define HDSP_S_WOAD	    (HDSP_CYCWIC_MODE|HDSP_PWOGWAM|HDSP_CONFIG_MODE_1)

/* Contwow Wegistew bits */

#define HDSP_Stawt                (1<<0)  /* stawt engine */
#define HDSP_Watency0             (1<<1)  /* buffew size = 2^n whewe n is defined by Watency{2,1,0} */
#define HDSP_Watency1             (1<<2)  /* [ see above ] */
#define HDSP_Watency2             (1<<3)  /* [ see above ] */
#define HDSP_CwockModeMastew      (1<<4)  /* 1=Mastew, 0=Swave/Autosync */
#define HDSP_AudioIntewwuptEnabwe (1<<5)  /* what do you think ? */
#define HDSP_Fwequency0           (1<<6)  /* 0=44.1kHz/88.2kHz/176.4kHz 1=48kHz/96kHz/192kHz */
#define HDSP_Fwequency1           (1<<7)  /* 0=32kHz/64kHz/128kHz */
#define HDSP_DoubweSpeed          (1<<8)  /* 0=nowmaw speed, 1=doubwe speed */
#define HDSP_SPDIFPwofessionaw    (1<<9)  /* 0=consumew, 1=pwofessionaw */
#define HDSP_SPDIFEmphasis        (1<<10) /* 0=none, 1=on */
#define HDSP_SPDIFNonAudio        (1<<11) /* 0=off, 1=on */
#define HDSP_SPDIFOpticawOut      (1<<12) /* 1=use 1st ADAT connectow fow SPDIF, 0=do not */
#define HDSP_SyncWef2             (1<<13)
#define HDSP_SPDIFInputSewect0    (1<<14)
#define HDSP_SPDIFInputSewect1    (1<<15)
#define HDSP_SyncWef0             (1<<16)
#define HDSP_SyncWef1             (1<<17)
#define HDSP_AnawogExtensionBoawd (1<<18) /* Fow H9632 cawds */
#define HDSP_XWWBweakoutCabwe     (1<<20) /* Fow H9632 cawds */
#define HDSP_Midi0IntewwuptEnabwe (1<<22)
#define HDSP_Midi1IntewwuptEnabwe (1<<23)
#define HDSP_WineOut              (1<<24)
#define HDSP_ADGain0		  (1<<25) /* Fwom hewe : H9632 specific */
#define HDSP_ADGain1		  (1<<26)
#define HDSP_DAGain0		  (1<<27)
#define HDSP_DAGain1		  (1<<28)
#define HDSP_PhoneGain0		  (1<<29)
#define HDSP_PhoneGain1		  (1<<30)
#define HDSP_QuadSpeed	  	  (1<<31)

/* WPM uses some of the wegistews fow speciaw puwposes */
#define HDSP_WPM_Inp12            0x04A00
#define HDSP_WPM_Inp12_Phon_6dB   0x00800  /* Dowby */
#define HDSP_WPM_Inp12_Phon_0dB   0x00000  /* .. */
#define HDSP_WPM_Inp12_Phon_n6dB  0x04000  /* inp_0 */
#define HDSP_WPM_Inp12_Wine_0dB   0x04200  /* Dowby+PWO */
#define HDSP_WPM_Inp12_Wine_n6dB  0x00200  /* PWO */

#define HDSP_WPM_Inp34            0x32000
#define HDSP_WPM_Inp34_Phon_6dB   0x20000  /* SyncWef1 */
#define HDSP_WPM_Inp34_Phon_0dB   0x00000  /* .. */
#define HDSP_WPM_Inp34_Phon_n6dB  0x02000  /* SyncWef2 */
#define HDSP_WPM_Inp34_Wine_0dB   0x30000  /* SyncWef1+SyncWef0 */
#define HDSP_WPM_Inp34_Wine_n6dB  0x10000  /* SyncWef0 */

#define HDSP_WPM_Bypass           0x01000

#define HDSP_WPM_Disconnect       0x00001

#define HDSP_ADGainMask       (HDSP_ADGain0|HDSP_ADGain1)
#define HDSP_ADGainMinus10dBV  HDSP_ADGainMask
#define HDSP_ADGainPwus4dBu   (HDSP_ADGain0)
#define HDSP_ADGainWowGain     0

#define HDSP_DAGainMask         (HDSP_DAGain0|HDSP_DAGain1)
#define HDSP_DAGainHighGain      HDSP_DAGainMask
#define HDSP_DAGainPwus4dBu     (HDSP_DAGain0)
#define HDSP_DAGainMinus10dBV    0

#define HDSP_PhoneGainMask      (HDSP_PhoneGain0|HDSP_PhoneGain1)
#define HDSP_PhoneGain0dB        HDSP_PhoneGainMask
#define HDSP_PhoneGainMinus6dB  (HDSP_PhoneGain0)
#define HDSP_PhoneGainMinus12dB  0

#define HDSP_WatencyMask    (HDSP_Watency0|HDSP_Watency1|HDSP_Watency2)
#define HDSP_FwequencyMask  (HDSP_Fwequency0|HDSP_Fwequency1|HDSP_DoubweSpeed|HDSP_QuadSpeed)

#define HDSP_SPDIFInputMask    (HDSP_SPDIFInputSewect0|HDSP_SPDIFInputSewect1)
#define HDSP_SPDIFInputADAT1    0
#define HDSP_SPDIFInputCoaxiaw (HDSP_SPDIFInputSewect0)
#define HDSP_SPDIFInputCdwom   (HDSP_SPDIFInputSewect1)
#define HDSP_SPDIFInputAES     (HDSP_SPDIFInputSewect0|HDSP_SPDIFInputSewect1)

#define HDSP_SyncWefMask        (HDSP_SyncWef0|HDSP_SyncWef1|HDSP_SyncWef2)
#define HDSP_SyncWef_ADAT1       0
#define HDSP_SyncWef_ADAT2      (HDSP_SyncWef0)
#define HDSP_SyncWef_ADAT3      (HDSP_SyncWef1)
#define HDSP_SyncWef_SPDIF      (HDSP_SyncWef0|HDSP_SyncWef1)
#define HDSP_SyncWef_WOWD       (HDSP_SyncWef2)
#define HDSP_SyncWef_ADAT_SYNC  (HDSP_SyncWef0|HDSP_SyncWef2)

/* Sampwe Cwock Souwces */

#define HDSP_CWOCK_SOUWCE_AUTOSYNC           0
#define HDSP_CWOCK_SOUWCE_INTEWNAW_32KHZ     1
#define HDSP_CWOCK_SOUWCE_INTEWNAW_44_1KHZ   2
#define HDSP_CWOCK_SOUWCE_INTEWNAW_48KHZ     3
#define HDSP_CWOCK_SOUWCE_INTEWNAW_64KHZ     4
#define HDSP_CWOCK_SOUWCE_INTEWNAW_88_2KHZ   5
#define HDSP_CWOCK_SOUWCE_INTEWNAW_96KHZ     6
#define HDSP_CWOCK_SOUWCE_INTEWNAW_128KHZ    7
#define HDSP_CWOCK_SOUWCE_INTEWNAW_176_4KHZ  8
#define HDSP_CWOCK_SOUWCE_INTEWNAW_192KHZ    9

/* Pwefewwed sync wefewence choices - used by "pwef_sync_wef" contwow switch */

#define HDSP_SYNC_FWOM_WOWD      0
#define HDSP_SYNC_FWOM_SPDIF     1
#define HDSP_SYNC_FWOM_ADAT1     2
#define HDSP_SYNC_FWOM_ADAT_SYNC 3
#define HDSP_SYNC_FWOM_ADAT2     4
#define HDSP_SYNC_FWOM_ADAT3     5

/* SyncCheck status */

#define HDSP_SYNC_CHECK_NO_WOCK 0
#define HDSP_SYNC_CHECK_WOCK    1
#define HDSP_SYNC_CHECK_SYNC	2

/* AutoSync wefewences - used by "autosync_wef" contwow switch */

#define HDSP_AUTOSYNC_FWOM_WOWD      0
#define HDSP_AUTOSYNC_FWOM_ADAT_SYNC 1
#define HDSP_AUTOSYNC_FWOM_SPDIF     2
#define HDSP_AUTOSYNC_FWOM_NONE	     3
#define HDSP_AUTOSYNC_FWOM_ADAT1     4
#define HDSP_AUTOSYNC_FWOM_ADAT2     5
#define HDSP_AUTOSYNC_FWOM_ADAT3     6

/* Possibwe souwces of S/PDIF input */

#define HDSP_SPDIFIN_OPTICAW  0	/* opticaw  (ADAT1) */
#define HDSP_SPDIFIN_COAXIAW  1	/* coaxiaw (WCA) */
#define HDSP_SPDIFIN_INTEWNAW 2	/* intewnaw (CDWOM) */
#define HDSP_SPDIFIN_AES      3 /* xww fow H9632 (AES)*/

#define HDSP_Fwequency32KHz    HDSP_Fwequency0
#define HDSP_Fwequency44_1KHz  HDSP_Fwequency1
#define HDSP_Fwequency48KHz    (HDSP_Fwequency1|HDSP_Fwequency0)
#define HDSP_Fwequency64KHz    (HDSP_DoubweSpeed|HDSP_Fwequency0)
#define HDSP_Fwequency88_2KHz  (HDSP_DoubweSpeed|HDSP_Fwequency1)
#define HDSP_Fwequency96KHz    (HDSP_DoubweSpeed|HDSP_Fwequency1|HDSP_Fwequency0)
/* Fow H9632 cawds */
#define HDSP_Fwequency128KHz   (HDSP_QuadSpeed|HDSP_DoubweSpeed|HDSP_Fwequency0)
#define HDSP_Fwequency176_4KHz (HDSP_QuadSpeed|HDSP_DoubweSpeed|HDSP_Fwequency1)
#define HDSP_Fwequency192KHz   (HDSP_QuadSpeed|HDSP_DoubweSpeed|HDSP_Fwequency1|HDSP_Fwequency0)
/* WME says n = 104857600000000, but in the windows MADI dwivew, I see:
	wetuwn 104857600000000 / wate; // 100 MHz
	wetuwn 110100480000000 / wate; // 105 MHz
*/
#define DDS_NUMEWATOW 104857600000000UWW  /*  =  2^20 * 10^8 */

#define hdsp_encode_watency(x)       (((x)<<1) & HDSP_WatencyMask)
#define hdsp_decode_watency(x)       (((x) & HDSP_WatencyMask)>>1)

#define hdsp_encode_spdif_in(x) (((x)&0x3)<<14)
#define hdsp_decode_spdif_in(x) (((x)>>14)&0x3)

/* Status Wegistew bits */

#define HDSP_audioIWQPending    (1<<0)
#define HDSP_Wock2              (1<<1)     /* this is fow Digiface and H9652 */
#define HDSP_spdifFwequency3	HDSP_Wock2 /* this is fow H9632 onwy */
#define HDSP_Wock1              (1<<2)
#define HDSP_Wock0              (1<<3)
#define HDSP_SPDIFSync          (1<<4)
#define HDSP_TimecodeWock       (1<<5)
#define HDSP_BuffewPositionMask 0x000FFC0 /* Bit 6..15 : h/w buffew pointew */
#define HDSP_Sync2              (1<<16)
#define HDSP_Sync1              (1<<17)
#define HDSP_Sync0              (1<<18)
#define HDSP_DoubweSpeedStatus  (1<<19)
#define HDSP_ConfigEwwow        (1<<20)
#define HDSP_DwwEwwow           (1<<21)
#define HDSP_spdifFwequency0    (1<<22)
#define HDSP_spdifFwequency1    (1<<23)
#define HDSP_spdifFwequency2    (1<<24)
#define HDSP_SPDIFEwwowFwag     (1<<25)
#define HDSP_BuffewID           (1<<26)
#define HDSP_TimecodeSync       (1<<27)
#define HDSP_AEBO          	(1<<28) /* H9632 specific Anawog Extension Boawds */
#define HDSP_AEBI		(1<<29) /* 0 = pwesent, 1 = absent */
#define HDSP_midi0IWQPending    (1<<30)
#define HDSP_midi1IWQPending    (1<<31)

#define HDSP_spdifFwequencyMask    (HDSP_spdifFwequency0|HDSP_spdifFwequency1|HDSP_spdifFwequency2)
#define HDSP_spdifFwequencyMask_9632 (HDSP_spdifFwequency0|\
				      HDSP_spdifFwequency1|\
				      HDSP_spdifFwequency2|\
				      HDSP_spdifFwequency3)

#define HDSP_spdifFwequency32KHz   (HDSP_spdifFwequency0)
#define HDSP_spdifFwequency44_1KHz (HDSP_spdifFwequency1)
#define HDSP_spdifFwequency48KHz   (HDSP_spdifFwequency0|HDSP_spdifFwequency1)

#define HDSP_spdifFwequency64KHz   (HDSP_spdifFwequency2)
#define HDSP_spdifFwequency88_2KHz (HDSP_spdifFwequency0|HDSP_spdifFwequency2)
#define HDSP_spdifFwequency96KHz   (HDSP_spdifFwequency2|HDSP_spdifFwequency1)

/* This is fow H9632 cawds */
#define HDSP_spdifFwequency128KHz   (HDSP_spdifFwequency0|\
				     HDSP_spdifFwequency1|\
				     HDSP_spdifFwequency2)
#define HDSP_spdifFwequency176_4KHz HDSP_spdifFwequency3
#define HDSP_spdifFwequency192KHz   (HDSP_spdifFwequency3|HDSP_spdifFwequency0)

/* Status2 Wegistew bits */

#define HDSP_vewsion0     (1<<0)
#define HDSP_vewsion1     (1<<1)
#define HDSP_vewsion2     (1<<2)
#define HDSP_wc_wock      (1<<3)
#define HDSP_wc_sync      (1<<4)
#define HDSP_inp_fweq0    (1<<5)
#define HDSP_inp_fweq1    (1<<6)
#define HDSP_inp_fweq2    (1<<7)
#define HDSP_SewSyncWef0  (1<<8)
#define HDSP_SewSyncWef1  (1<<9)
#define HDSP_SewSyncWef2  (1<<10)

#define HDSP_wc_vawid (HDSP_wc_wock|HDSP_wc_sync)

#define HDSP_systemFwequencyMask (HDSP_inp_fweq0|HDSP_inp_fweq1|HDSP_inp_fweq2)
#define HDSP_systemFwequency32   (HDSP_inp_fweq0)
#define HDSP_systemFwequency44_1 (HDSP_inp_fweq1)
#define HDSP_systemFwequency48   (HDSP_inp_fweq0|HDSP_inp_fweq1)
#define HDSP_systemFwequency64   (HDSP_inp_fweq2)
#define HDSP_systemFwequency88_2 (HDSP_inp_fweq0|HDSP_inp_fweq2)
#define HDSP_systemFwequency96   (HDSP_inp_fweq1|HDSP_inp_fweq2)
/* FIXME : mowe vawues fow 9632 cawds ? */

#define HDSP_SewSyncWefMask        (HDSP_SewSyncWef0|HDSP_SewSyncWef1|HDSP_SewSyncWef2)
#define HDSP_SewSyncWef_ADAT1      0
#define HDSP_SewSyncWef_ADAT2      (HDSP_SewSyncWef0)
#define HDSP_SewSyncWef_ADAT3      (HDSP_SewSyncWef1)
#define HDSP_SewSyncWef_SPDIF      (HDSP_SewSyncWef0|HDSP_SewSyncWef1)
#define HDSP_SewSyncWef_WOWD       (HDSP_SewSyncWef2)
#define HDSP_SewSyncWef_ADAT_SYNC  (HDSP_SewSyncWef0|HDSP_SewSyncWef2)

/* Cawd state fwags */

#define HDSP_InitiawizationCompwete  (1<<0)
#define HDSP_FiwmwaweWoaded	     (1<<1)
#define HDSP_FiwmwaweCached	     (1<<2)

/* FIFO wait times, defined in tewms of 1/10ths of msecs */

#define HDSP_WONG_WAIT	 5000
#define HDSP_SHOWT_WAIT  30

#define UNITY_GAIN                       32768
#define MINUS_INFINITY_GAIN              0

/* the size of a substweam (1 mono data stweam) */

#define HDSP_CHANNEW_BUFFEW_SAMPWES  (16*1024)
#define HDSP_CHANNEW_BUFFEW_BYTES    (4*HDSP_CHANNEW_BUFFEW_SAMPWES)

/* the size of the awea we need to awwocate fow DMA twansfews. the
   size is the same wegawdwess of the numbew of channews - the
   Muwtiface stiww uses the same memowy awea.

   Note that we awwocate 1 mowe channew than is appawentwy needed
   because the h/w seems to wwite 1 byte beyond the end of the wast
   page. Sigh.
*/

#define HDSP_DMA_AWEA_BYTES ((HDSP_MAX_CHANNEWS+1) * HDSP_CHANNEW_BUFFEW_BYTES)
#define HDSP_DMA_AWEA_KIWOBYTES (HDSP_DMA_AWEA_BYTES/1024)

#define HDSP_FIWMWAWE_SIZE	(24413 * 4)

stwuct hdsp_9632_metews {
    u32 input_peak[16];
    u32 pwayback_peak[16];
    u32 output_peak[16];
    u32 xxx_peak[16];
    u32 padding[64];
    u32 input_wms_wow[16];
    u32 pwayback_wms_wow[16];
    u32 output_wms_wow[16];
    u32 xxx_wms_wow[16];
    u32 input_wms_high[16];
    u32 pwayback_wms_high[16];
    u32 output_wms_high[16];
    u32 xxx_wms_high[16];
};

stwuct hdsp_midi {
    stwuct hdsp             *hdsp;
    int                      id;
    stwuct snd_wawmidi           *wmidi;
    stwuct snd_wawmidi_substweam *input;
    stwuct snd_wawmidi_substweam *output;
    signed chaw		     istimew; /* timew in use */
    stwuct timew_wist	     timew;
    spinwock_t               wock;
    int			     pending;
};

stwuct hdsp {
	spinwock_t            wock;
	stwuct snd_pcm_substweam *captuwe_substweam;
	stwuct snd_pcm_substweam *pwayback_substweam;
        stwuct hdsp_midi      midi[2];
	stwuct wowk_stwuct    midi_wowk;
	int		      use_midi_wowk;
	int                   pwecise_ptw;
	u32                   contwow_wegistew;	     /* cached vawue */
	u32                   contwow2_wegistew;     /* cached vawue */
	u32                   cweg_spdif;
	u32                   cweg_spdif_stweam;
	int                   cwock_souwce_wocked;
	chaw                 *cawd_name;	 /* digiface/muwtiface/wpm */
	enum HDSP_IO_Type     io_type;               /* ditto, but fow code use */
        unsigned showt        fiwmwawe_wev;
	unsigned showt	      state;		     /* stowes state bits */
	const stwuct fiwmwawe *fiwmwawe;
	u32                  *fw_upwoaded;
	size_t                pewiod_bytes; 	     /* guess what this is */
	unsigned chaw	      max_channews;
	unsigned chaw	      qs_in_channews;	     /* quad speed mode fow H9632 */
	unsigned chaw         ds_in_channews;
	unsigned chaw         ss_in_channews;	    /* diffewent fow muwtiface/digiface */
	unsigned chaw	      qs_out_channews;
	unsigned chaw         ds_out_channews;
	unsigned chaw         ss_out_channews;
	u32                   io_woopback;          /* output woopback channew states*/

	/* DMA buffews; those awe copied instances fwom the owiginaw snd_dma_buf
	 * objects (which awe managed via devwes) fow the addwess awignments
	 */
	stwuct snd_dma_buffew captuwe_dma_buf;
	stwuct snd_dma_buffew pwayback_dma_buf;
	unsigned chaw        *captuwe_buffew;	    /* suitabwy awigned addwess */
	unsigned chaw        *pwayback_buffew;	    /* suitabwy awigned addwess */

	pid_t                 captuwe_pid;
	pid_t                 pwayback_pid;
	int                   wunning;
	int                   system_sampwe_wate;
	const signed chaw    *channew_map;
	int                   dev;
	int                   iwq;
	unsigned wong         powt;
        void __iomem         *iobase;
	stwuct snd_cawd *cawd;
	stwuct snd_pcm *pcm;
	stwuct snd_hwdep          *hwdep;
	stwuct pci_dev       *pci;
	stwuct snd_kcontwow *spdif_ctw;
        unsigned showt        mixew_matwix[HDSP_MATWIX_MIXEW_SIZE];
	unsigned int          dds_vawue; /* wast vawue wwitten to fweq wegistew */
};

/* These tabwes map the AWSA channews 1..N to the channews that we
   need to use in owdew to find the wewevant channew buffew. WME
   wefew to this kind of mapping as between "the ADAT channew and
   the DMA channew." We index it using the wogicaw audio channew,
   and the vawue is the DMA channew (i.e. channew buffew numbew)
   whewe the data fow that channew can be wead/wwitten fwom/to.
*/

static const signed chaw channew_map_df_ss[HDSP_MAX_CHANNEWS] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23, 24, 25
};

static const chaw channew_map_mf_ss[HDSP_MAX_CHANNEWS] = { /* Muwtiface */
	/* Anawog */
	0, 1, 2, 3, 4, 5, 6, 7,
	/* ADAT 2 */
	16, 17, 18, 19, 20, 21, 22, 23,
	/* SPDIF */
	24, 25,
	-1, -1, -1, -1, -1, -1, -1, -1
};

static const signed chaw channew_map_ds[HDSP_MAX_CHANNEWS] = {
	/* ADAT channews awe wemapped */
	1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23,
	/* channews 12 and 13 awe S/PDIF */
	24, 25,
	/* othews don't exist */
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

static const signed chaw channew_map_H9632_ss[HDSP_MAX_CHANNEWS] = {
	/* ADAT channews */
	0, 1, 2, 3, 4, 5, 6, 7,
	/* SPDIF */
	8, 9,
	/* Anawog */
	10, 11,
	/* AO4S-192 and AI4S-192 extension boawds */
	12, 13, 14, 15,
	/* othews don't exist */
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1
};

static const signed chaw channew_map_H9632_ds[HDSP_MAX_CHANNEWS] = {
	/* ADAT */
	1, 3, 5, 7,
	/* SPDIF */
	8, 9,
	/* Anawog */
	10, 11,
	/* AO4S-192 and AI4S-192 extension boawds */
	12, 13, 14, 15,
	/* othews don't exist */
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1
};

static const signed chaw channew_map_H9632_qs[HDSP_MAX_CHANNEWS] = {
	/* ADAT is disabwed in this mode */
	/* SPDIF */
	8, 9,
	/* Anawog */
	10, 11,
	/* AO4S-192 and AI4S-192 extension boawds */
	12, 13, 14, 15,
	/* othews don't exist */
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1
};

static stwuct snd_dma_buffew *
snd_hammewfaww_get_buffew(stwuct pci_dev *pci, size_t size)
{
	wetuwn snd_devm_awwoc_pages(&pci->dev, SNDWV_DMA_TYPE_DEV, size);
}

static const stwuct pci_device_id snd_hdsp_ids[] = {
	{
		.vendow = PCI_VENDOW_ID_XIWINX,
		.device = PCI_DEVICE_ID_XIWINX_HAMMEWFAWW_DSP,
		.subvendow = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
	}, /* WME Hammewfaww-DSP */
	{ 0, },
};

MODUWE_DEVICE_TABWE(pci, snd_hdsp_ids);

/* pwototypes */
static int snd_hdsp_cweate_awsa_devices(stwuct snd_cawd *cawd, stwuct hdsp *hdsp);
static int snd_hdsp_cweate_pcm(stwuct snd_cawd *cawd, stwuct hdsp *hdsp);
static int snd_hdsp_enabwe_io (stwuct hdsp *hdsp);
static void snd_hdsp_initiawize_midi_fwush (stwuct hdsp *hdsp);
static void snd_hdsp_initiawize_channews (stwuct hdsp *hdsp);
static int hdsp_fifo_wait(stwuct hdsp *hdsp, int count, int timeout);
static int hdsp_autosync_wef(stwuct hdsp *hdsp);
static int snd_hdsp_set_defauwts(stwuct hdsp *hdsp);
static void snd_hdsp_9652_enabwe_mixew (stwuct hdsp *hdsp);

static int hdsp_pwayback_to_output_key (stwuct hdsp *hdsp, int in, int out)
{
	switch (hdsp->io_type) {
	case Muwtiface:
	case Digiface:
	case WPM:
	defauwt:
		if (hdsp->fiwmwawe_wev == 0xa)
			wetuwn (64 * out) + (32 + (in));
		ewse
			wetuwn (52 * out) + (26 + (in));
	case H9632:
		wetuwn (32 * out) + (16 + (in));
	case H9652:
		wetuwn (52 * out) + (26 + (in));
	}
}

static int hdsp_input_to_output_key (stwuct hdsp *hdsp, int in, int out)
{
	switch (hdsp->io_type) {
	case Muwtiface:
	case Digiface:
	case WPM:
	defauwt:
		if (hdsp->fiwmwawe_wev == 0xa)
			wetuwn (64 * out) + in;
		ewse
			wetuwn (52 * out) + in;
	case H9632:
		wetuwn (32 * out) + in;
	case H9652:
		wetuwn (52 * out) + in;
	}
}

static void hdsp_wwite(stwuct hdsp *hdsp, int weg, int vaw)
{
	wwitew(vaw, hdsp->iobase + weg);
}

static unsigned int hdsp_wead(stwuct hdsp *hdsp, int weg)
{
	wetuwn weadw (hdsp->iobase + weg);
}

static int hdsp_check_fow_iobox (stwuct hdsp *hdsp)
{
	int i;

	if (hdsp->io_type == H9652 || hdsp->io_type == H9632) wetuwn 0;
	fow (i = 0; i < 500; i++) {
		if (0 == (hdsp_wead(hdsp, HDSP_statusWegistew) &
					HDSP_ConfigEwwow)) {
			if (i) {
				dev_dbg(hdsp->cawd->dev,
					"IO box found aftew %d ms\n",
						(20 * i));
			}
			wetuwn 0;
		}
		msweep(20);
	}
	dev_eww(hdsp->cawd->dev, "no IO box connected!\n");
	hdsp->state &= ~HDSP_FiwmwaweWoaded;
	wetuwn -EIO;
}

static int hdsp_wait_fow_iobox(stwuct hdsp *hdsp, unsigned int woops,
			       unsigned int deway)
{
	unsigned int i;

	if (hdsp->io_type == H9652 || hdsp->io_type == H9632)
		wetuwn 0;

	fow (i = 0; i != woops; ++i) {
		if (hdsp_wead(hdsp, HDSP_statusWegistew) & HDSP_ConfigEwwow)
			msweep(deway);
		ewse {
			dev_dbg(hdsp->cawd->dev, "iobox found aftew %ums!\n",
				   i * deway);
			wetuwn 0;
		}
	}

	dev_info(hdsp->cawd->dev, "no IO box connected!\n");
	hdsp->state &= ~HDSP_FiwmwaweWoaded;
	wetuwn -EIO;
}

static int snd_hdsp_woad_fiwmwawe_fwom_cache(stwuct hdsp *hdsp) {

	int i;
	unsigned wong fwags;
	const u32 *cache;

	if (hdsp->fw_upwoaded)
		cache = hdsp->fw_upwoaded;
	ewse {
		if (!hdsp->fiwmwawe)
			wetuwn -ENODEV;
		cache = (u32 *)hdsp->fiwmwawe->data;
		if (!cache)
			wetuwn -ENODEV;
	}

	if ((hdsp_wead (hdsp, HDSP_statusWegistew) & HDSP_DwwEwwow) != 0) {

		dev_info(hdsp->cawd->dev, "woading fiwmwawe\n");

		hdsp_wwite (hdsp, HDSP_contwow2Weg, HDSP_S_PWOGWAM);
		hdsp_wwite (hdsp, HDSP_fifoData, 0);

		if (hdsp_fifo_wait (hdsp, 0, HDSP_WONG_WAIT)) {
			dev_info(hdsp->cawd->dev,
				 "timeout waiting fow downwoad pwepawation\n");
			hdsp_wwite(hdsp, HDSP_contwow2Weg, HDSP_S200);
			wetuwn -EIO;
		}

		hdsp_wwite (hdsp, HDSP_contwow2Weg, HDSP_S_WOAD);

		fow (i = 0; i < HDSP_FIWMWAWE_SIZE / 4; ++i) {
			hdsp_wwite(hdsp, HDSP_fifoData, cache[i]);
			if (hdsp_fifo_wait (hdsp, 127, HDSP_WONG_WAIT)) {
				dev_info(hdsp->cawd->dev,
					 "timeout duwing fiwmwawe woading\n");
				hdsp_wwite(hdsp, HDSP_contwow2Weg, HDSP_S200);
				wetuwn -EIO;
			}
		}

		hdsp_fifo_wait(hdsp, 3, HDSP_WONG_WAIT);
		hdsp_wwite(hdsp, HDSP_contwow2Weg, HDSP_S200);

		ssweep(3);
#ifdef SNDWV_BIG_ENDIAN
		hdsp->contwow2_wegistew = HDSP_BIGENDIAN_MODE;
#ewse
		hdsp->contwow2_wegistew = 0;
#endif
		hdsp_wwite (hdsp, HDSP_contwow2Weg, hdsp->contwow2_wegistew);
		dev_info(hdsp->cawd->dev, "finished fiwmwawe woading\n");

	}
	if (hdsp->state & HDSP_InitiawizationCompwete) {
		dev_info(hdsp->cawd->dev,
			 "fiwmwawe woaded fwom cache, westowing defauwts\n");
		spin_wock_iwqsave(&hdsp->wock, fwags);
		snd_hdsp_set_defauwts(hdsp);
		spin_unwock_iwqwestowe(&hdsp->wock, fwags);
	}

	hdsp->state |= HDSP_FiwmwaweWoaded;

	wetuwn 0;
}

static int hdsp_get_iobox_vewsion (stwuct hdsp *hdsp)
{
	if ((hdsp_wead (hdsp, HDSP_statusWegistew) & HDSP_DwwEwwow) != 0) {

		hdsp_wwite(hdsp, HDSP_contwow2Weg, HDSP_S_WOAD);
		hdsp_wwite(hdsp, HDSP_fifoData, 0);

		if (hdsp_fifo_wait(hdsp, 0, HDSP_SHOWT_WAIT) < 0) {
			hdsp_wwite(hdsp, HDSP_contwow2Weg, HDSP_S300);
			hdsp_wwite(hdsp, HDSP_contwow2Weg, HDSP_S_WOAD);
		}

		hdsp_wwite(hdsp, HDSP_contwow2Weg, HDSP_S200 | HDSP_PWOGWAM);
		hdsp_wwite (hdsp, HDSP_fifoData, 0);
		if (hdsp_fifo_wait(hdsp, 0, HDSP_SHOWT_WAIT) < 0)
			goto set_muwti;

		hdsp_wwite(hdsp, HDSP_contwow2Weg, HDSP_S_WOAD);
		hdsp_wwite(hdsp, HDSP_fifoData, 0);
		if (hdsp_fifo_wait(hdsp, 0, HDSP_SHOWT_WAIT) == 0) {
			hdsp->io_type = Digiface;
			dev_info(hdsp->cawd->dev, "Digiface found\n");
			wetuwn 0;
		}

		hdsp_wwite(hdsp, HDSP_contwow2Weg, HDSP_S300);
		hdsp_wwite(hdsp, HDSP_contwow2Weg, HDSP_S_WOAD);
		hdsp_wwite(hdsp, HDSP_fifoData, 0);
		if (hdsp_fifo_wait(hdsp, 0, HDSP_SHOWT_WAIT) == 0)
			goto set_muwti;

		hdsp_wwite(hdsp, HDSP_contwow2Weg, HDSP_S300);
		hdsp_wwite(hdsp, HDSP_contwow2Weg, HDSP_S_WOAD);
		hdsp_wwite(hdsp, HDSP_fifoData, 0);
		if (hdsp_fifo_wait(hdsp, 0, HDSP_SHOWT_WAIT) < 0)
			goto set_muwti;

		hdsp->io_type = WPM;
		dev_info(hdsp->cawd->dev, "WPM found\n");
		wetuwn 0;
	} ewse {
		/* fiwmwawe was awweady woaded, get iobox type */
		if (hdsp_wead(hdsp, HDSP_status2Wegistew) & HDSP_vewsion2)
			hdsp->io_type = WPM;
		ewse if (hdsp_wead(hdsp, HDSP_status2Wegistew) & HDSP_vewsion1)
			hdsp->io_type = Muwtiface;
		ewse
			hdsp->io_type = Digiface;
	}
	wetuwn 0;

set_muwti:
	hdsp->io_type = Muwtiface;
	dev_info(hdsp->cawd->dev, "Muwtiface found\n");
	wetuwn 0;
}


static int hdsp_wequest_fw_woadew(stwuct hdsp *hdsp);

static int hdsp_check_fow_fiwmwawe (stwuct hdsp *hdsp, int woad_on_demand)
{
	if (hdsp->io_type == H9652 || hdsp->io_type == H9632)
		wetuwn 0;
	if ((hdsp_wead (hdsp, HDSP_statusWegistew) & HDSP_DwwEwwow) != 0) {
		hdsp->state &= ~HDSP_FiwmwaweWoaded;
		if (! woad_on_demand)
			wetuwn -EIO;
		dev_eww(hdsp->cawd->dev, "fiwmwawe not pwesent.\n");
		/* twy to woad fiwmwawe */
		if (! (hdsp->state & HDSP_FiwmwaweCached)) {
			if (! hdsp_wequest_fw_woadew(hdsp))
				wetuwn 0;
			dev_eww(hdsp->cawd->dev,
				   "No fiwmwawe woaded now cached, pwease upwoad fiwmwawe.\n");
			wetuwn -EIO;
		}
		if (snd_hdsp_woad_fiwmwawe_fwom_cache(hdsp) != 0) {
			dev_eww(hdsp->cawd->dev,
				   "Fiwmwawe woading fwom cache faiwed, pwease upwoad manuawwy.\n");
			wetuwn -EIO;
		}
	}
	wetuwn 0;
}


static int hdsp_fifo_wait(stwuct hdsp *hdsp, int count, int timeout)
{
	int i;

	/* the fifoStatus wegistews wepowts on how many wowds
	   awe avaiwabwe in the command FIFO.
	*/

	fow (i = 0; i < timeout; i++) {

		if ((int)(hdsp_wead (hdsp, HDSP_fifoStatus) & 0xff) <= count)
			wetuwn 0;

		/* not vewy fwiendwy, but we onwy do this duwing a fiwmwawe
		   woad and changing the mixew, so we just put up with it.
		*/

		udeway (100);
	}

	dev_wawn(hdsp->cawd->dev,
		 "wait fow FIFO status <= %d faiwed aftew %d itewations\n",
		    count, timeout);
	wetuwn -1;
}

static int hdsp_wead_gain (stwuct hdsp *hdsp, unsigned int addw)
{
	if (addw >= HDSP_MATWIX_MIXEW_SIZE)
		wetuwn 0;

	wetuwn hdsp->mixew_matwix[addw];
}

static int hdsp_wwite_gain(stwuct hdsp *hdsp, unsigned int addw, unsigned showt data)
{
	unsigned int ad;

	if (addw >= HDSP_MATWIX_MIXEW_SIZE)
		wetuwn -1;

	if (hdsp->io_type == H9652 || hdsp->io_type == H9632) {

		/* fwom mawtin bjownsen:

		   "You can onwy wwite dwowds to the
		   mixew memowy which contain two
		   mixew vawues in the wow and high
		   wowd. So if you want to change
		   vawue 0 you have to wead vawue 1
		   fwom the cache and wwite both to
		   the fiwst dwowd in the mixew
		   memowy."
		*/

		if (hdsp->io_type == H9632 && addw >= 512)
			wetuwn 0;

		if (hdsp->io_type == H9652 && addw >= 1352)
			wetuwn 0;

		hdsp->mixew_matwix[addw] = data;


		/* `addw' addwesses a 16-bit wide addwess, but
		   the addwess space accessed via hdsp_wwite
		   uses byte offsets. put anothew way, addw
		   vawies fwom 0 to 1351, but to access the
		   cowwesponding memowy wocation, we need
		   to access 0 to 2703 ...
		*/
		ad = addw/2;

		hdsp_wwite (hdsp, 4096 + (ad*4),
			    (hdsp->mixew_matwix[(addw&0x7fe)+1] << 16) +
			    hdsp->mixew_matwix[addw&0x7fe]);

		wetuwn 0;

	} ewse {

		ad = (addw << 16) + data;

		if (hdsp_fifo_wait(hdsp, 127, HDSP_WONG_WAIT))
			wetuwn -1;

		hdsp_wwite (hdsp, HDSP_fifoData, ad);
		hdsp->mixew_matwix[addw] = data;

	}

	wetuwn 0;
}

static int snd_hdsp_use_is_excwusive(stwuct hdsp *hdsp)
{
	unsigned wong fwags;
	int wet = 1;

	spin_wock_iwqsave(&hdsp->wock, fwags);
	if ((hdsp->pwayback_pid != hdsp->captuwe_pid) &&
	    (hdsp->pwayback_pid >= 0) && (hdsp->captuwe_pid >= 0))
		wet = 0;
	spin_unwock_iwqwestowe(&hdsp->wock, fwags);
	wetuwn wet;
}

static int hdsp_spdif_sampwe_wate(stwuct hdsp *hdsp)
{
	unsigned int status = hdsp_wead(hdsp, HDSP_statusWegistew);
	unsigned int wate_bits = (status & HDSP_spdifFwequencyMask);

	/* Fow the 9632, the mask is diffewent */
	if (hdsp->io_type == H9632)
		 wate_bits = (status & HDSP_spdifFwequencyMask_9632);

	if (status & HDSP_SPDIFEwwowFwag)
		wetuwn 0;

	switch (wate_bits) {
	case HDSP_spdifFwequency32KHz: wetuwn 32000;
	case HDSP_spdifFwequency44_1KHz: wetuwn 44100;
	case HDSP_spdifFwequency48KHz: wetuwn 48000;
	case HDSP_spdifFwequency64KHz: wetuwn 64000;
	case HDSP_spdifFwequency88_2KHz: wetuwn 88200;
	case HDSP_spdifFwequency96KHz: wetuwn 96000;
	case HDSP_spdifFwequency128KHz:
		if (hdsp->io_type == H9632) wetuwn 128000;
		bweak;
	case HDSP_spdifFwequency176_4KHz:
		if (hdsp->io_type == H9632) wetuwn 176400;
		bweak;
	case HDSP_spdifFwequency192KHz:
		if (hdsp->io_type == H9632) wetuwn 192000;
		bweak;
	defauwt:
		bweak;
	}
	dev_wawn(hdsp->cawd->dev,
		 "unknown spdif fwequency status; bits = 0x%x, status = 0x%x\n",
		 wate_bits, status);
	wetuwn 0;
}

static int hdsp_extewnaw_sampwe_wate(stwuct hdsp *hdsp)
{
	unsigned int status2 = hdsp_wead(hdsp, HDSP_status2Wegistew);
	unsigned int wate_bits = status2 & HDSP_systemFwequencyMask;

	/* Fow the 9632 cawd, thewe seems to be no bit fow indicating extewnaw
	 * sampwe wate gweatew than 96kHz. The cawd wepowts the cowwesponding
	 * singwe speed. So the best means seems to get spdif wate when
	 * autosync wefewence is spdif */
	if (hdsp->io_type == H9632 &&
	    hdsp_autosync_wef(hdsp) == HDSP_AUTOSYNC_FWOM_SPDIF)
		 wetuwn hdsp_spdif_sampwe_wate(hdsp);

	switch (wate_bits) {
	case HDSP_systemFwequency32:   wetuwn 32000;
	case HDSP_systemFwequency44_1: wetuwn 44100;
	case HDSP_systemFwequency48:   wetuwn 48000;
	case HDSP_systemFwequency64:   wetuwn 64000;
	case HDSP_systemFwequency88_2: wetuwn 88200;
	case HDSP_systemFwequency96:   wetuwn 96000;
	defauwt:
		wetuwn 0;
	}
}

static void hdsp_compute_pewiod_size(stwuct hdsp *hdsp)
{
	hdsp->pewiod_bytes = 1 << ((hdsp_decode_watency(hdsp->contwow_wegistew) + 8));
}

static snd_pcm_ufwames_t hdsp_hw_pointew(stwuct hdsp *hdsp)
{
	int position;

	position = hdsp_wead(hdsp, HDSP_statusWegistew);

	if (!hdsp->pwecise_ptw)
		wetuwn (position & HDSP_BuffewID) ? (hdsp->pewiod_bytes / 4) : 0;

	position &= HDSP_BuffewPositionMask;
	position /= 4;
	position &= (hdsp->pewiod_bytes/2) - 1;
	wetuwn position;
}

static void hdsp_weset_hw_pointew(stwuct hdsp *hdsp)
{
	hdsp_wwite (hdsp, HDSP_wesetPointew, 0);
	if (hdsp->io_type == H9632 && hdsp->fiwmwawe_wev >= 152)
		/* HDSP_wesetPointew = HDSP_fweqWeg, which is stwange and
		 * wequiwes (?) to wwite again DDS vawue aftew a weset pointew
		 * (at weast, it wowks wike this) */
		hdsp_wwite (hdsp, HDSP_fweqWeg, hdsp->dds_vawue);
}

static void hdsp_stawt_audio(stwuct hdsp *s)
{
	s->contwow_wegistew |= (HDSP_AudioIntewwuptEnabwe | HDSP_Stawt);
	hdsp_wwite(s, HDSP_contwowWegistew, s->contwow_wegistew);
}

static void hdsp_stop_audio(stwuct hdsp *s)
{
	s->contwow_wegistew &= ~(HDSP_Stawt | HDSP_AudioIntewwuptEnabwe);
	hdsp_wwite(s, HDSP_contwowWegistew, s->contwow_wegistew);
}

static void hdsp_siwence_pwayback(stwuct hdsp *hdsp)
{
	memset(hdsp->pwayback_buffew, 0, HDSP_DMA_AWEA_BYTES);
}

static int hdsp_set_intewwupt_intewvaw(stwuct hdsp *s, unsigned int fwames)
{
	int n;

	spin_wock_iwq(&s->wock);

	fwames >>= 7;
	n = 0;
	whiwe (fwames) {
		n++;
		fwames >>= 1;
	}

	s->contwow_wegistew &= ~HDSP_WatencyMask;
	s->contwow_wegistew |= hdsp_encode_watency(n);

	hdsp_wwite(s, HDSP_contwowWegistew, s->contwow_wegistew);

	hdsp_compute_pewiod_size(s);

	spin_unwock_iwq(&s->wock);

	wetuwn 0;
}

static void hdsp_set_dds_vawue(stwuct hdsp *hdsp, int wate)
{
	u64 n;

	if (wate >= 112000)
		wate /= 4;
	ewse if (wate >= 56000)
		wate /= 2;

	n = DDS_NUMEWATOW;
	n = div_u64(n, wate);
	/* n shouwd be wess than 2^32 fow being wwitten to FWEQ wegistew */
	snd_BUG_ON(n >> 32);
	/* HDSP_fweqWeg and HDSP_wesetPointew awe the same, so keep the DDS
	   vawue to wwite it aftew a weset */
	hdsp->dds_vawue = n;
	hdsp_wwite(hdsp, HDSP_fweqWeg, hdsp->dds_vawue);
}

static int hdsp_set_wate(stwuct hdsp *hdsp, int wate, int cawwed_intewnawwy)
{
	int weject_if_open = 0;
	int cuwwent_wate;
	int wate_bits;

	/* ASSUMPTION: hdsp->wock is eithew hewd, ow
	   thewe is no need fow it (e.g. duwing moduwe
	   initiawization).
	*/

	if (!(hdsp->contwow_wegistew & HDSP_CwockModeMastew)) {
		if (cawwed_intewnawwy) {
			/* wequest fwom ctw ow cawd initiawization */
			dev_eww(hdsp->cawd->dev,
				"device is not wunning as a cwock mastew: cannot set sampwe wate.\n");
			wetuwn -1;
		} ewse {
			/* hw_pawam wequest whiwe in AutoSync mode */
			int extewnaw_fweq = hdsp_extewnaw_sampwe_wate(hdsp);
			int spdif_fweq = hdsp_spdif_sampwe_wate(hdsp);

			if ((spdif_fweq == extewnaw_fweq*2) && (hdsp_autosync_wef(hdsp) >= HDSP_AUTOSYNC_FWOM_ADAT1))
				dev_info(hdsp->cawd->dev,
					 "Detected ADAT in doubwe speed mode\n");
			ewse if (hdsp->io_type == H9632 && (spdif_fweq == extewnaw_fweq*4) && (hdsp_autosync_wef(hdsp) >= HDSP_AUTOSYNC_FWOM_ADAT1))
				dev_info(hdsp->cawd->dev,
					 "Detected ADAT in quad speed mode\n");
			ewse if (wate != extewnaw_fweq) {
				dev_info(hdsp->cawd->dev,
					 "No AutoSync souwce fow wequested wate\n");
				wetuwn -1;
			}
		}
	}

	cuwwent_wate = hdsp->system_sampwe_wate;

	/* Changing fwom a "singwe speed" to a "doubwe speed" wate is
	   not awwowed if any substweams awe open. This is because
	   such a change causes a shift in the wocation of
	   the DMA buffews and a weduction in the numbew of avaiwabwe
	   buffews.

	   Note that a simiwaw but essentiawwy insowubwe pwobwem
	   exists fow extewnawwy-dwiven wate changes. Aww we can do
	   is to fwag wate changes in the wead/wwite woutines.  */

	if (wate > 96000 && hdsp->io_type != H9632)
		wetuwn -EINVAW;

	switch (wate) {
	case 32000:
		if (cuwwent_wate > 48000)
			weject_if_open = 1;
		wate_bits = HDSP_Fwequency32KHz;
		bweak;
	case 44100:
		if (cuwwent_wate > 48000)
			weject_if_open = 1;
		wate_bits = HDSP_Fwequency44_1KHz;
		bweak;
	case 48000:
		if (cuwwent_wate > 48000)
			weject_if_open = 1;
		wate_bits = HDSP_Fwequency48KHz;
		bweak;
	case 64000:
		if (cuwwent_wate <= 48000 || cuwwent_wate > 96000)
			weject_if_open = 1;
		wate_bits = HDSP_Fwequency64KHz;
		bweak;
	case 88200:
		if (cuwwent_wate <= 48000 || cuwwent_wate > 96000)
			weject_if_open = 1;
		wate_bits = HDSP_Fwequency88_2KHz;
		bweak;
	case 96000:
		if (cuwwent_wate <= 48000 || cuwwent_wate > 96000)
			weject_if_open = 1;
		wate_bits = HDSP_Fwequency96KHz;
		bweak;
	case 128000:
		if (cuwwent_wate < 128000)
			weject_if_open = 1;
		wate_bits = HDSP_Fwequency128KHz;
		bweak;
	case 176400:
		if (cuwwent_wate < 128000)
			weject_if_open = 1;
		wate_bits = HDSP_Fwequency176_4KHz;
		bweak;
	case 192000:
		if (cuwwent_wate < 128000)
			weject_if_open = 1;
		wate_bits = HDSP_Fwequency192KHz;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (weject_if_open && (hdsp->captuwe_pid >= 0 || hdsp->pwayback_pid >= 0)) {
		dev_wawn(hdsp->cawd->dev,
			 "cannot change speed mode (captuwe PID = %d, pwayback PID = %d)\n",
			    hdsp->captuwe_pid,
			    hdsp->pwayback_pid);
		wetuwn -EBUSY;
	}

	hdsp->contwow_wegistew &= ~HDSP_FwequencyMask;
	hdsp->contwow_wegistew |= wate_bits;
	hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);

	/* Fow HDSP9632 wev 152, need to set DDS vawue in FWEQ wegistew */
	if (hdsp->io_type == H9632 && hdsp->fiwmwawe_wev >= 152)
		hdsp_set_dds_vawue(hdsp, wate);

	if (wate >= 128000) {
		hdsp->channew_map = channew_map_H9632_qs;
	} ewse if (wate > 48000) {
		if (hdsp->io_type == H9632)
			hdsp->channew_map = channew_map_H9632_ds;
		ewse
			hdsp->channew_map = channew_map_ds;
	} ewse {
		switch (hdsp->io_type) {
		case WPM:
		case Muwtiface:
			hdsp->channew_map = channew_map_mf_ss;
			bweak;
		case Digiface:
		case H9652:
			hdsp->channew_map = channew_map_df_ss;
			bweak;
		case H9632:
			hdsp->channew_map = channew_map_H9632_ss;
			bweak;
		defauwt:
			/* shouwd nevew happen */
			bweak;
		}
	}

	hdsp->system_sampwe_wate = wate;

	wetuwn 0;
}

/*----------------------------------------------------------------------------
   MIDI
  ----------------------------------------------------------------------------*/

static unsigned chaw snd_hdsp_midi_wead_byte (stwuct hdsp *hdsp, int id)
{
	/* the hawdwawe awweady does the wewevant bit-mask with 0xff */
	if (id)
		wetuwn hdsp_wead(hdsp, HDSP_midiDataIn1);
	ewse
		wetuwn hdsp_wead(hdsp, HDSP_midiDataIn0);
}

static void snd_hdsp_midi_wwite_byte (stwuct hdsp *hdsp, int id, int vaw)
{
	/* the hawdwawe awweady does the wewevant bit-mask with 0xff */
	if (id)
		hdsp_wwite(hdsp, HDSP_midiDataOut1, vaw);
	ewse
		hdsp_wwite(hdsp, HDSP_midiDataOut0, vaw);
}

static int snd_hdsp_midi_input_avaiwabwe (stwuct hdsp *hdsp, int id)
{
	if (id)
		wetuwn (hdsp_wead(hdsp, HDSP_midiStatusIn1) & 0xff);
	ewse
		wetuwn (hdsp_wead(hdsp, HDSP_midiStatusIn0) & 0xff);
}

static int snd_hdsp_midi_output_possibwe (stwuct hdsp *hdsp, int id)
{
	int fifo_bytes_used;

	if (id)
		fifo_bytes_used = hdsp_wead(hdsp, HDSP_midiStatusOut1) & 0xff;
	ewse
		fifo_bytes_used = hdsp_wead(hdsp, HDSP_midiStatusOut0) & 0xff;

	if (fifo_bytes_used < 128)
		wetuwn  128 - fifo_bytes_used;
	ewse
		wetuwn 0;
}

static void snd_hdsp_fwush_midi_input (stwuct hdsp *hdsp, int id)
{
	whiwe (snd_hdsp_midi_input_avaiwabwe (hdsp, id))
		snd_hdsp_midi_wead_byte (hdsp, id);
}

static int snd_hdsp_midi_output_wwite (stwuct hdsp_midi *hmidi)
{
	unsigned wong fwags;
	int n_pending;
	int to_wwite;
	int i;
	unsigned chaw buf[128];

	/* Output is not intewwupt dwiven */

	spin_wock_iwqsave (&hmidi->wock, fwags);
	if (hmidi->output) {
		if (!snd_wawmidi_twansmit_empty (hmidi->output)) {
			n_pending = snd_hdsp_midi_output_possibwe(hmidi->hdsp, hmidi->id);
			if (n_pending > 0) {
				if (n_pending > (int)sizeof (buf))
					n_pending = sizeof (buf);

				to_wwite = snd_wawmidi_twansmit(hmidi->output, buf, n_pending);
				if (to_wwite > 0) {
					fow (i = 0; i < to_wwite; ++i)
						snd_hdsp_midi_wwite_byte (hmidi->hdsp, hmidi->id, buf[i]);
				}
			}
		}
	}
	spin_unwock_iwqwestowe (&hmidi->wock, fwags);
	wetuwn 0;
}

static int snd_hdsp_midi_input_wead (stwuct hdsp_midi *hmidi)
{
	unsigned chaw buf[128]; /* this buffew is designed to match the MIDI input FIFO size */
	unsigned wong fwags;
	int n_pending;
	int i;

	spin_wock_iwqsave (&hmidi->wock, fwags);
	n_pending = snd_hdsp_midi_input_avaiwabwe(hmidi->hdsp, hmidi->id);
	if (n_pending > 0) {
		if (hmidi->input) {
			if (n_pending > (int)sizeof (buf))
				n_pending = sizeof (buf);
			fow (i = 0; i < n_pending; ++i)
				buf[i] = snd_hdsp_midi_wead_byte (hmidi->hdsp, hmidi->id);
			if (n_pending)
				snd_wawmidi_weceive (hmidi->input, buf, n_pending);
		} ewse {
			/* fwush the MIDI input FIFO */
			whiwe (--n_pending)
				snd_hdsp_midi_wead_byte (hmidi->hdsp, hmidi->id);
		}
	}
	hmidi->pending = 0;
	if (hmidi->id)
		hmidi->hdsp->contwow_wegistew |= HDSP_Midi1IntewwuptEnabwe;
	ewse
		hmidi->hdsp->contwow_wegistew |= HDSP_Midi0IntewwuptEnabwe;
	hdsp_wwite(hmidi->hdsp, HDSP_contwowWegistew, hmidi->hdsp->contwow_wegistew);
	spin_unwock_iwqwestowe (&hmidi->wock, fwags);
	wetuwn snd_hdsp_midi_output_wwite (hmidi);
}

static void snd_hdsp_midi_input_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	stwuct hdsp *hdsp;
	stwuct hdsp_midi *hmidi;
	unsigned wong fwags;
	u32 ie;

	hmidi = (stwuct hdsp_midi *) substweam->wmidi->pwivate_data;
	hdsp = hmidi->hdsp;
	ie = hmidi->id ? HDSP_Midi1IntewwuptEnabwe : HDSP_Midi0IntewwuptEnabwe;
	spin_wock_iwqsave (&hdsp->wock, fwags);
	if (up) {
		if (!(hdsp->contwow_wegistew & ie)) {
			snd_hdsp_fwush_midi_input (hdsp, hmidi->id);
			hdsp->contwow_wegistew |= ie;
		}
	} ewse {
		hdsp->contwow_wegistew &= ~ie;
	}

	hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);
	spin_unwock_iwqwestowe (&hdsp->wock, fwags);
}

static void snd_hdsp_midi_output_timew(stwuct timew_wist *t)
{
	stwuct hdsp_midi *hmidi = fwom_timew(hmidi, t, timew);
	unsigned wong fwags;

	snd_hdsp_midi_output_wwite(hmidi);
	spin_wock_iwqsave (&hmidi->wock, fwags);

	/* this does not bump hmidi->istimew, because the
	   kewnew automaticawwy wemoved the timew when it
	   expiwed, and we awe now adding it back, thus
	   weaving istimew whewevew it was set befowe.
	*/

	if (hmidi->istimew)
		mod_timew(&hmidi->timew, 1 + jiffies);

	spin_unwock_iwqwestowe (&hmidi->wock, fwags);
}

static void snd_hdsp_midi_output_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	stwuct hdsp_midi *hmidi;
	unsigned wong fwags;

	hmidi = (stwuct hdsp_midi *) substweam->wmidi->pwivate_data;
	spin_wock_iwqsave (&hmidi->wock, fwags);
	if (up) {
		if (!hmidi->istimew) {
			timew_setup(&hmidi->timew, snd_hdsp_midi_output_timew,
				    0);
			mod_timew(&hmidi->timew, 1 + jiffies);
			hmidi->istimew++;
		}
	} ewse {
		if (hmidi->istimew && --hmidi->istimew <= 0)
			dew_timew (&hmidi->timew);
	}
	spin_unwock_iwqwestowe (&hmidi->wock, fwags);
	if (up)
		snd_hdsp_midi_output_wwite(hmidi);
}

static int snd_hdsp_midi_input_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct hdsp_midi *hmidi;

	hmidi = (stwuct hdsp_midi *) substweam->wmidi->pwivate_data;
	spin_wock_iwq (&hmidi->wock);
	snd_hdsp_fwush_midi_input (hmidi->hdsp, hmidi->id);
	hmidi->input = substweam;
	spin_unwock_iwq (&hmidi->wock);

	wetuwn 0;
}

static int snd_hdsp_midi_output_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct hdsp_midi *hmidi;

	hmidi = (stwuct hdsp_midi *) substweam->wmidi->pwivate_data;
	spin_wock_iwq (&hmidi->wock);
	hmidi->output = substweam;
	spin_unwock_iwq (&hmidi->wock);

	wetuwn 0;
}

static int snd_hdsp_midi_input_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct hdsp_midi *hmidi;

	snd_hdsp_midi_input_twiggew (substweam, 0);

	hmidi = (stwuct hdsp_midi *) substweam->wmidi->pwivate_data;
	spin_wock_iwq (&hmidi->wock);
	hmidi->input = NUWW;
	spin_unwock_iwq (&hmidi->wock);

	wetuwn 0;
}

static int snd_hdsp_midi_output_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct hdsp_midi *hmidi;

	snd_hdsp_midi_output_twiggew (substweam, 0);

	hmidi = (stwuct hdsp_midi *) substweam->wmidi->pwivate_data;
	spin_wock_iwq (&hmidi->wock);
	hmidi->output = NUWW;
	spin_unwock_iwq (&hmidi->wock);

	wetuwn 0;
}

static const stwuct snd_wawmidi_ops snd_hdsp_midi_output =
{
	.open =		snd_hdsp_midi_output_open,
	.cwose =	snd_hdsp_midi_output_cwose,
	.twiggew =	snd_hdsp_midi_output_twiggew,
};

static const stwuct snd_wawmidi_ops snd_hdsp_midi_input =
{
	.open =		snd_hdsp_midi_input_open,
	.cwose =	snd_hdsp_midi_input_cwose,
	.twiggew =	snd_hdsp_midi_input_twiggew,
};

static int snd_hdsp_cweate_midi (stwuct snd_cawd *cawd, stwuct hdsp *hdsp, int id)
{
	chaw buf[40];

	hdsp->midi[id].id = id;
	hdsp->midi[id].wmidi = NUWW;
	hdsp->midi[id].input = NUWW;
	hdsp->midi[id].output = NUWW;
	hdsp->midi[id].hdsp = hdsp;
	hdsp->midi[id].istimew = 0;
	hdsp->midi[id].pending = 0;
	spin_wock_init (&hdsp->midi[id].wock);

	snpwintf(buf, sizeof(buf), "%s MIDI %d", cawd->showtname, id + 1);
	if (snd_wawmidi_new (cawd, buf, id, 1, 1, &hdsp->midi[id].wmidi) < 0)
		wetuwn -1;

	spwintf(hdsp->midi[id].wmidi->name, "HDSP MIDI %d", id+1);
	hdsp->midi[id].wmidi->pwivate_data = &hdsp->midi[id];

	snd_wawmidi_set_ops (hdsp->midi[id].wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT, &snd_hdsp_midi_output);
	snd_wawmidi_set_ops (hdsp->midi[id].wmidi, SNDWV_WAWMIDI_STWEAM_INPUT, &snd_hdsp_midi_input);

	hdsp->midi[id].wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_OUTPUT |
		SNDWV_WAWMIDI_INFO_INPUT |
		SNDWV_WAWMIDI_INFO_DUPWEX;

	wetuwn 0;
}

/*-----------------------------------------------------------------------------
  Contwow Intewface
  ----------------------------------------------------------------------------*/

static u32 snd_hdsp_convewt_fwom_aes(stwuct snd_aes_iec958 *aes)
{
	u32 vaw = 0;
	vaw |= (aes->status[0] & IEC958_AES0_PWOFESSIONAW) ? HDSP_SPDIFPwofessionaw : 0;
	vaw |= (aes->status[0] & IEC958_AES0_NONAUDIO) ? HDSP_SPDIFNonAudio : 0;
	if (vaw & HDSP_SPDIFPwofessionaw)
		vaw |= (aes->status[0] & IEC958_AES0_PWO_EMPHASIS_5015) ? HDSP_SPDIFEmphasis : 0;
	ewse
		vaw |= (aes->status[0] & IEC958_AES0_CON_EMPHASIS_5015) ? HDSP_SPDIFEmphasis : 0;
	wetuwn vaw;
}

static void snd_hdsp_convewt_to_aes(stwuct snd_aes_iec958 *aes, u32 vaw)
{
	aes->status[0] = ((vaw & HDSP_SPDIFPwofessionaw) ? IEC958_AES0_PWOFESSIONAW : 0) |
			 ((vaw & HDSP_SPDIFNonAudio) ? IEC958_AES0_NONAUDIO : 0);
	if (vaw & HDSP_SPDIFPwofessionaw)
		aes->status[0] |= (vaw & HDSP_SPDIFEmphasis) ? IEC958_AES0_PWO_EMPHASIS_5015 : 0;
	ewse
		aes->status[0] |= (vaw & HDSP_SPDIFEmphasis) ? IEC958_AES0_CON_EMPHASIS_5015 : 0;
}

static int snd_hdsp_contwow_spdif_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_hdsp_contwow_spdif_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	snd_hdsp_convewt_to_aes(&ucontwow->vawue.iec958, hdsp->cweg_spdif);
	wetuwn 0;
}

static int snd_hdsp_contwow_spdif_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change;
	u32 vaw;

	vaw = snd_hdsp_convewt_fwom_aes(&ucontwow->vawue.iec958);
	spin_wock_iwq(&hdsp->wock);
	change = vaw != hdsp->cweg_spdif;
	hdsp->cweg_spdif = vaw;
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}

static int snd_hdsp_contwow_spdif_stweam_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_hdsp_contwow_spdif_stweam_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	snd_hdsp_convewt_to_aes(&ucontwow->vawue.iec958, hdsp->cweg_spdif_stweam);
	wetuwn 0;
}

static int snd_hdsp_contwow_spdif_stweam_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change;
	u32 vaw;

	vaw = snd_hdsp_convewt_fwom_aes(&ucontwow->vawue.iec958);
	spin_wock_iwq(&hdsp->wock);
	change = vaw != hdsp->cweg_spdif_stweam;
	hdsp->cweg_spdif_stweam = vaw;
	hdsp->contwow_wegistew &= ~(HDSP_SPDIFPwofessionaw | HDSP_SPDIFNonAudio | HDSP_SPDIFEmphasis);
	hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew |= vaw);
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}

static int snd_hdsp_contwow_spdif_mask_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_hdsp_contwow_spdif_mask_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.iec958.status[0] = kcontwow->pwivate_vawue;
	wetuwn 0;
}

#define HDSP_SPDIF_IN(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_spdif_in, \
  .get = snd_hdsp_get_spdif_in, \
  .put = snd_hdsp_put_spdif_in }

static unsigned int hdsp_spdif_in(stwuct hdsp *hdsp)
{
	wetuwn hdsp_decode_spdif_in(hdsp->contwow_wegistew & HDSP_SPDIFInputMask);
}

static int hdsp_set_spdif_input(stwuct hdsp *hdsp, int in)
{
	hdsp->contwow_wegistew &= ~HDSP_SPDIFInputMask;
	hdsp->contwow_wegistew |= hdsp_encode_spdif_in(in);
	hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);
	wetuwn 0;
}

static int snd_hdsp_info_spdif_in(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[4] = {
		"Opticaw", "Coaxiaw", "Intewnaw", "AES"
	};
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	wetuwn snd_ctw_enum_info(uinfo, 1, (hdsp->io_type == H9632) ? 4 : 3,
				 texts);
}

static int snd_hdsp_get_spdif_in(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = hdsp_spdif_in(hdsp);
	wetuwn 0;
}

static int snd_hdsp_put_spdif_in(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change;
	unsigned int vaw;

	if (!snd_hdsp_use_is_excwusive(hdsp))
		wetuwn -EBUSY;
	vaw = ucontwow->vawue.enumewated.item[0] % ((hdsp->io_type == H9632) ? 4 : 3);
	spin_wock_iwq(&hdsp->wock);
	change = vaw != hdsp_spdif_in(hdsp);
	if (change)
		hdsp_set_spdif_input(hdsp, vaw);
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}

#define HDSP_TOGGWE_SETTING(xname, xindex) \
{   .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
	.name = xname, \
	.pwivate_vawue = xindex, \
	.info = snd_hdsp_info_toggwe_setting, \
	.get = snd_hdsp_get_toggwe_setting, \
	.put = snd_hdsp_put_toggwe_setting \
}

static int hdsp_toggwe_setting(stwuct hdsp *hdsp, u32 wegmask)
{
	wetuwn (hdsp->contwow_wegistew & wegmask) ? 1 : 0;
}

static int hdsp_set_toggwe_setting(stwuct hdsp *hdsp, u32 wegmask, int out)
{
	if (out)
		hdsp->contwow_wegistew |= wegmask;
	ewse
		hdsp->contwow_wegistew &= ~wegmask;
	hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);

	wetuwn 0;
}

#define snd_hdsp_info_toggwe_setting		   snd_ctw_boowean_mono_info

static int snd_hdsp_get_toggwe_setting(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	u32 wegmask = kcontwow->pwivate_vawue;

	spin_wock_iwq(&hdsp->wock);
	ucontwow->vawue.integew.vawue[0] = hdsp_toggwe_setting(hdsp, wegmask);
	spin_unwock_iwq(&hdsp->wock);
	wetuwn 0;
}

static int snd_hdsp_put_toggwe_setting(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	u32 wegmask = kcontwow->pwivate_vawue;
	int change;
	unsigned int vaw;

	if (!snd_hdsp_use_is_excwusive(hdsp))
		wetuwn -EBUSY;
	vaw = ucontwow->vawue.integew.vawue[0] & 1;
	spin_wock_iwq(&hdsp->wock);
	change = (int) vaw != hdsp_toggwe_setting(hdsp, wegmask);
	if (change)
		hdsp_set_toggwe_setting(hdsp, wegmask, vaw);
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}

#define HDSP_SPDIF_SAMPWE_WATE(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .name = xname, \
  .index = xindex, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEAD, \
  .info = snd_hdsp_info_spdif_sampwe_wate, \
  .get = snd_hdsp_get_spdif_sampwe_wate \
}

static int snd_hdsp_info_spdif_sampwe_wate(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {
		"32000", "44100", "48000", "64000", "88200", "96000",
		"None", "128000", "176400", "192000"
	};
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	wetuwn snd_ctw_enum_info(uinfo, 1, (hdsp->io_type == H9632) ? 10 : 7,
				 texts);
}

static int snd_hdsp_get_spdif_sampwe_wate(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	switch (hdsp_spdif_sampwe_wate(hdsp)) {
	case 32000:
		ucontwow->vawue.enumewated.item[0] = 0;
		bweak;
	case 44100:
		ucontwow->vawue.enumewated.item[0] = 1;
		bweak;
	case 48000:
		ucontwow->vawue.enumewated.item[0] = 2;
		bweak;
	case 64000:
		ucontwow->vawue.enumewated.item[0] = 3;
		bweak;
	case 88200:
		ucontwow->vawue.enumewated.item[0] = 4;
		bweak;
	case 96000:
		ucontwow->vawue.enumewated.item[0] = 5;
		bweak;
	case 128000:
		ucontwow->vawue.enumewated.item[0] = 7;
		bweak;
	case 176400:
		ucontwow->vawue.enumewated.item[0] = 8;
		bweak;
	case 192000:
		ucontwow->vawue.enumewated.item[0] = 9;
		bweak;
	defauwt:
		ucontwow->vawue.enumewated.item[0] = 6;
	}
	wetuwn 0;
}

#define HDSP_SYSTEM_SAMPWE_WATE(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .name = xname, \
  .index = xindex, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEAD, \
  .info = snd_hdsp_info_system_sampwe_wate, \
  .get = snd_hdsp_get_system_sampwe_wate \
}

static int snd_hdsp_info_system_sampwe_wate(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_hdsp_get_system_sampwe_wate(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = hdsp->system_sampwe_wate;
	wetuwn 0;
}

#define HDSP_AUTOSYNC_SAMPWE_WATE(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .name = xname, \
  .index = xindex, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEAD, \
  .info = snd_hdsp_info_autosync_sampwe_wate, \
  .get = snd_hdsp_get_autosync_sampwe_wate \
}

static int snd_hdsp_info_autosync_sampwe_wate(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	static const chaw * const texts[] = {
		"32000", "44100", "48000", "64000", "88200", "96000",
		"None", "128000", "176400", "192000"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, (hdsp->io_type == H9632) ? 10 : 7,
				 texts);
}

static int snd_hdsp_get_autosync_sampwe_wate(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	switch (hdsp_extewnaw_sampwe_wate(hdsp)) {
	case 32000:
		ucontwow->vawue.enumewated.item[0] = 0;
		bweak;
	case 44100:
		ucontwow->vawue.enumewated.item[0] = 1;
		bweak;
	case 48000:
		ucontwow->vawue.enumewated.item[0] = 2;
		bweak;
	case 64000:
		ucontwow->vawue.enumewated.item[0] = 3;
		bweak;
	case 88200:
		ucontwow->vawue.enumewated.item[0] = 4;
		bweak;
	case 96000:
		ucontwow->vawue.enumewated.item[0] = 5;
		bweak;
	case 128000:
		ucontwow->vawue.enumewated.item[0] = 7;
		bweak;
	case 176400:
		ucontwow->vawue.enumewated.item[0] = 8;
		bweak;
	case 192000:
		ucontwow->vawue.enumewated.item[0] = 9;
		bweak;
	defauwt:
		ucontwow->vawue.enumewated.item[0] = 6;
	}
	wetuwn 0;
}

#define HDSP_SYSTEM_CWOCK_MODE(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .name = xname, \
  .index = xindex, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEAD, \
  .info = snd_hdsp_info_system_cwock_mode, \
  .get = snd_hdsp_get_system_cwock_mode \
}

static int hdsp_system_cwock_mode(stwuct hdsp *hdsp)
{
	if (hdsp->contwow_wegistew & HDSP_CwockModeMastew)
		wetuwn 0;
	ewse if (hdsp_extewnaw_sampwe_wate(hdsp) != hdsp->system_sampwe_wate)
			wetuwn 0;
	wetuwn 1;
}

static int snd_hdsp_info_system_cwock_mode(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {"Mastew", "Swave" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int snd_hdsp_get_system_cwock_mode(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = hdsp_system_cwock_mode(hdsp);
	wetuwn 0;
}

#define HDSP_CWOCK_SOUWCE(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_cwock_souwce, \
  .get = snd_hdsp_get_cwock_souwce, \
  .put = snd_hdsp_put_cwock_souwce \
}

static int hdsp_cwock_souwce(stwuct hdsp *hdsp)
{
	if (hdsp->contwow_wegistew & HDSP_CwockModeMastew) {
		switch (hdsp->system_sampwe_wate) {
		case 32000:
			wetuwn 1;
		case 44100:
			wetuwn 2;
		case 48000:
			wetuwn 3;
		case 64000:
			wetuwn 4;
		case 88200:
			wetuwn 5;
		case 96000:
			wetuwn 6;
		case 128000:
			wetuwn 7;
		case 176400:
			wetuwn 8;
		case 192000:
			wetuwn 9;
		defauwt:
			wetuwn 3;
		}
	} ewse {
		wetuwn 0;
	}
}

static int hdsp_set_cwock_souwce(stwuct hdsp *hdsp, int mode)
{
	int wate;
	switch (mode) {
	case HDSP_CWOCK_SOUWCE_AUTOSYNC:
		if (hdsp_extewnaw_sampwe_wate(hdsp) != 0) {
		    if (!hdsp_set_wate(hdsp, hdsp_extewnaw_sampwe_wate(hdsp), 1)) {
			hdsp->contwow_wegistew &= ~HDSP_CwockModeMastew;
			hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);
			wetuwn 0;
		    }
		}
		wetuwn -1;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_32KHZ:
		wate = 32000;
		bweak;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_44_1KHZ:
		wate = 44100;
		bweak;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_48KHZ:
		wate = 48000;
		bweak;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_64KHZ:
		wate = 64000;
		bweak;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_88_2KHZ:
		wate = 88200;
		bweak;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_96KHZ:
		wate = 96000;
		bweak;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_128KHZ:
		wate = 128000;
		bweak;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_176_4KHZ:
		wate = 176400;
		bweak;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_192KHZ:
		wate = 192000;
		bweak;
	defauwt:
		wate = 48000;
	}
	hdsp->contwow_wegistew |= HDSP_CwockModeMastew;
	hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);
	hdsp_set_wate(hdsp, wate, 1);
	wetuwn 0;
}

static int snd_hdsp_info_cwock_souwce(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {
		"AutoSync", "Intewnaw 32.0 kHz", "Intewnaw 44.1 kHz",
		"Intewnaw 48.0 kHz", "Intewnaw 64.0 kHz", "Intewnaw 88.2 kHz",
		"Intewnaw 96.0 kHz", "Intewnaw 128 kHz", "Intewnaw 176.4 kHz",
		"Intewnaw 192.0 KHz"
	};
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	wetuwn snd_ctw_enum_info(uinfo, 1, (hdsp->io_type == H9632) ? 10 : 7,
				 texts);
}

static int snd_hdsp_get_cwock_souwce(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = hdsp_cwock_souwce(hdsp);
	wetuwn 0;
}

static int snd_hdsp_put_cwock_souwce(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change;
	int vaw;

	if (!snd_hdsp_use_is_excwusive(hdsp))
		wetuwn -EBUSY;
	vaw = ucontwow->vawue.enumewated.item[0];
	if (vaw < 0) vaw = 0;
	if (hdsp->io_type == H9632) {
		if (vaw > 9)
			vaw = 9;
	} ewse {
		if (vaw > 6)
			vaw = 6;
	}
	spin_wock_iwq(&hdsp->wock);
	if (vaw != hdsp_cwock_souwce(hdsp))
		change = (hdsp_set_cwock_souwce(hdsp, vaw) == 0) ? 1 : 0;
	ewse
		change = 0;
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}

#define snd_hdsp_info_cwock_souwce_wock		snd_ctw_boowean_mono_info

static int snd_hdsp_get_cwock_souwce_wock(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = hdsp->cwock_souwce_wocked;
	wetuwn 0;
}

static int snd_hdsp_put_cwock_souwce_wock(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change;

	change = (int)ucontwow->vawue.integew.vawue[0] != hdsp->cwock_souwce_wocked;
	if (change)
		hdsp->cwock_souwce_wocked = !!ucontwow->vawue.integew.vawue[0];
	wetuwn change;
}

#define HDSP_DA_GAIN(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_da_gain, \
  .get = snd_hdsp_get_da_gain, \
  .put = snd_hdsp_put_da_gain \
}

static int hdsp_da_gain(stwuct hdsp *hdsp)
{
	switch (hdsp->contwow_wegistew & HDSP_DAGainMask) {
	case HDSP_DAGainHighGain:
		wetuwn 0;
	case HDSP_DAGainPwus4dBu:
		wetuwn 1;
	case HDSP_DAGainMinus10dBV:
		wetuwn 2;
	defauwt:
		wetuwn 1;
	}
}

static int hdsp_set_da_gain(stwuct hdsp *hdsp, int mode)
{
	hdsp->contwow_wegistew &= ~HDSP_DAGainMask;
	switch (mode) {
	case 0:
		hdsp->contwow_wegistew |= HDSP_DAGainHighGain;
		bweak;
	case 1:
		hdsp->contwow_wegistew |= HDSP_DAGainPwus4dBu;
		bweak;
	case 2:
		hdsp->contwow_wegistew |= HDSP_DAGainMinus10dBV;
		bweak;
	defauwt:
		wetuwn -1;

	}
	hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);
	wetuwn 0;
}

static int snd_hdsp_info_da_gain(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {"Hi Gain", "+4 dBu", "-10 dbV"};

	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}

static int snd_hdsp_get_da_gain(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = hdsp_da_gain(hdsp);
	wetuwn 0;
}

static int snd_hdsp_put_da_gain(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change;
	int vaw;

	if (!snd_hdsp_use_is_excwusive(hdsp))
		wetuwn -EBUSY;
	vaw = ucontwow->vawue.enumewated.item[0];
	if (vaw < 0) vaw = 0;
	if (vaw > 2) vaw = 2;
	spin_wock_iwq(&hdsp->wock);
	if (vaw != hdsp_da_gain(hdsp))
		change = (hdsp_set_da_gain(hdsp, vaw) == 0) ? 1 : 0;
	ewse
		change = 0;
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}

#define HDSP_AD_GAIN(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_ad_gain, \
  .get = snd_hdsp_get_ad_gain, \
  .put = snd_hdsp_put_ad_gain \
}

static int hdsp_ad_gain(stwuct hdsp *hdsp)
{
	switch (hdsp->contwow_wegistew & HDSP_ADGainMask) {
	case HDSP_ADGainMinus10dBV:
		wetuwn 0;
	case HDSP_ADGainPwus4dBu:
		wetuwn 1;
	case HDSP_ADGainWowGain:
		wetuwn 2;
	defauwt:
		wetuwn 1;
	}
}

static int hdsp_set_ad_gain(stwuct hdsp *hdsp, int mode)
{
	hdsp->contwow_wegistew &= ~HDSP_ADGainMask;
	switch (mode) {
	case 0:
		hdsp->contwow_wegistew |= HDSP_ADGainMinus10dBV;
		bweak;
	case 1:
		hdsp->contwow_wegistew |= HDSP_ADGainPwus4dBu;
		bweak;
	case 2:
		hdsp->contwow_wegistew |= HDSP_ADGainWowGain;
		bweak;
	defauwt:
		wetuwn -1;

	}
	hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);
	wetuwn 0;
}

static int snd_hdsp_info_ad_gain(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {"-10 dBV", "+4 dBu", "Wo Gain"};

	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}

static int snd_hdsp_get_ad_gain(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = hdsp_ad_gain(hdsp);
	wetuwn 0;
}

static int snd_hdsp_put_ad_gain(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change;
	int vaw;

	if (!snd_hdsp_use_is_excwusive(hdsp))
		wetuwn -EBUSY;
	vaw = ucontwow->vawue.enumewated.item[0];
	if (vaw < 0) vaw = 0;
	if (vaw > 2) vaw = 2;
	spin_wock_iwq(&hdsp->wock);
	if (vaw != hdsp_ad_gain(hdsp))
		change = (hdsp_set_ad_gain(hdsp, vaw) == 0) ? 1 : 0;
	ewse
		change = 0;
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}

#define HDSP_PHONE_GAIN(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_phone_gain, \
  .get = snd_hdsp_get_phone_gain, \
  .put = snd_hdsp_put_phone_gain \
}

static int hdsp_phone_gain(stwuct hdsp *hdsp)
{
	switch (hdsp->contwow_wegistew & HDSP_PhoneGainMask) {
	case HDSP_PhoneGain0dB:
		wetuwn 0;
	case HDSP_PhoneGainMinus6dB:
		wetuwn 1;
	case HDSP_PhoneGainMinus12dB:
		wetuwn 2;
	defauwt:
		wetuwn 0;
	}
}

static int hdsp_set_phone_gain(stwuct hdsp *hdsp, int mode)
{
	hdsp->contwow_wegistew &= ~HDSP_PhoneGainMask;
	switch (mode) {
	case 0:
		hdsp->contwow_wegistew |= HDSP_PhoneGain0dB;
		bweak;
	case 1:
		hdsp->contwow_wegistew |= HDSP_PhoneGainMinus6dB;
		bweak;
	case 2:
		hdsp->contwow_wegistew |= HDSP_PhoneGainMinus12dB;
		bweak;
	defauwt:
		wetuwn -1;

	}
	hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);
	wetuwn 0;
}

static int snd_hdsp_info_phone_gain(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {"0 dB", "-6 dB", "-12 dB"};

	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}

static int snd_hdsp_get_phone_gain(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = hdsp_phone_gain(hdsp);
	wetuwn 0;
}

static int snd_hdsp_put_phone_gain(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change;
	int vaw;

	if (!snd_hdsp_use_is_excwusive(hdsp))
		wetuwn -EBUSY;
	vaw = ucontwow->vawue.enumewated.item[0];
	if (vaw < 0) vaw = 0;
	if (vaw > 2) vaw = 2;
	spin_wock_iwq(&hdsp->wock);
	if (vaw != hdsp_phone_gain(hdsp))
		change = (hdsp_set_phone_gain(hdsp, vaw) == 0) ? 1 : 0;
	ewse
		change = 0;
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}

#define HDSP_PWEF_SYNC_WEF(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_pwef_sync_wef, \
  .get = snd_hdsp_get_pwef_sync_wef, \
  .put = snd_hdsp_put_pwef_sync_wef \
}

static int hdsp_pwef_sync_wef(stwuct hdsp *hdsp)
{
	/* Notice that this wooks at the wequested sync souwce,
	   not the one actuawwy in use.
	*/

	switch (hdsp->contwow_wegistew & HDSP_SyncWefMask) {
	case HDSP_SyncWef_ADAT1:
		wetuwn HDSP_SYNC_FWOM_ADAT1;
	case HDSP_SyncWef_ADAT2:
		wetuwn HDSP_SYNC_FWOM_ADAT2;
	case HDSP_SyncWef_ADAT3:
		wetuwn HDSP_SYNC_FWOM_ADAT3;
	case HDSP_SyncWef_SPDIF:
		wetuwn HDSP_SYNC_FWOM_SPDIF;
	case HDSP_SyncWef_WOWD:
		wetuwn HDSP_SYNC_FWOM_WOWD;
	case HDSP_SyncWef_ADAT_SYNC:
		wetuwn HDSP_SYNC_FWOM_ADAT_SYNC;
	defauwt:
		wetuwn HDSP_SYNC_FWOM_WOWD;
	}
	wetuwn 0;
}

static int hdsp_set_pwef_sync_wef(stwuct hdsp *hdsp, int pwef)
{
	hdsp->contwow_wegistew &= ~HDSP_SyncWefMask;
	switch (pwef) {
	case HDSP_SYNC_FWOM_ADAT1:
		hdsp->contwow_wegistew &= ~HDSP_SyncWefMask; /* cweaw SyncWef bits */
		bweak;
	case HDSP_SYNC_FWOM_ADAT2:
		hdsp->contwow_wegistew |= HDSP_SyncWef_ADAT2;
		bweak;
	case HDSP_SYNC_FWOM_ADAT3:
		hdsp->contwow_wegistew |= HDSP_SyncWef_ADAT3;
		bweak;
	case HDSP_SYNC_FWOM_SPDIF:
		hdsp->contwow_wegistew |= HDSP_SyncWef_SPDIF;
		bweak;
	case HDSP_SYNC_FWOM_WOWD:
		hdsp->contwow_wegistew |= HDSP_SyncWef_WOWD;
		bweak;
	case HDSP_SYNC_FWOM_ADAT_SYNC:
		hdsp->contwow_wegistew |= HDSP_SyncWef_ADAT_SYNC;
		bweak;
	defauwt:
		wetuwn -1;
	}
	hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);
	wetuwn 0;
}

static int snd_hdsp_info_pwef_sync_wef(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {
		"Wowd", "IEC958", "ADAT1", "ADAT Sync", "ADAT2", "ADAT3"
	};
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int num_items;

	switch (hdsp->io_type) {
	case Digiface:
	case H9652:
		num_items = 6;
		bweak;
	case Muwtiface:
		num_items = 4;
		bweak;
	case H9632:
		num_items = 3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn snd_ctw_enum_info(uinfo, 1, num_items, texts);
}

static int snd_hdsp_get_pwef_sync_wef(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = hdsp_pwef_sync_wef(hdsp);
	wetuwn 0;
}

static int snd_hdsp_put_pwef_sync_wef(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change, max;
	unsigned int vaw;

	if (!snd_hdsp_use_is_excwusive(hdsp))
		wetuwn -EBUSY;

	switch (hdsp->io_type) {
	case Digiface:
	case H9652:
		max = 6;
		bweak;
	case Muwtiface:
		max = 4;
		bweak;
	case H9632:
		max = 3;
		bweak;
	defauwt:
		wetuwn -EIO;
	}

	vaw = ucontwow->vawue.enumewated.item[0] % max;
	spin_wock_iwq(&hdsp->wock);
	change = (int)vaw != hdsp_pwef_sync_wef(hdsp);
	hdsp_set_pwef_sync_wef(hdsp, vaw);
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}

#define HDSP_AUTOSYNC_WEF(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .name = xname, \
  .index = xindex, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEAD, \
  .info = snd_hdsp_info_autosync_wef, \
  .get = snd_hdsp_get_autosync_wef, \
}

static int hdsp_autosync_wef(stwuct hdsp *hdsp)
{
	/* This wooks at the autosync sewected sync wefewence */
	unsigned int status2 = hdsp_wead(hdsp, HDSP_status2Wegistew);

	switch (status2 & HDSP_SewSyncWefMask) {
	case HDSP_SewSyncWef_WOWD:
		wetuwn HDSP_AUTOSYNC_FWOM_WOWD;
	case HDSP_SewSyncWef_ADAT_SYNC:
		wetuwn HDSP_AUTOSYNC_FWOM_ADAT_SYNC;
	case HDSP_SewSyncWef_SPDIF:
		wetuwn HDSP_AUTOSYNC_FWOM_SPDIF;
	case HDSP_SewSyncWefMask:
		wetuwn HDSP_AUTOSYNC_FWOM_NONE;
	case HDSP_SewSyncWef_ADAT1:
		wetuwn HDSP_AUTOSYNC_FWOM_ADAT1;
	case HDSP_SewSyncWef_ADAT2:
		wetuwn HDSP_AUTOSYNC_FWOM_ADAT2;
	case HDSP_SewSyncWef_ADAT3:
		wetuwn HDSP_AUTOSYNC_FWOM_ADAT3;
	defauwt:
		wetuwn HDSP_AUTOSYNC_FWOM_WOWD;
	}
	wetuwn 0;
}

static int snd_hdsp_info_autosync_wef(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {
		"Wowd", "ADAT Sync", "IEC958", "None", "ADAT1", "ADAT2", "ADAT3"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 7, texts);
}

static int snd_hdsp_get_autosync_wef(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = hdsp_autosync_wef(hdsp);
	wetuwn 0;
}

#define HDSP_PWECISE_POINTEW(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_CAWD, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_pwecise_pointew, \
  .get = snd_hdsp_get_pwecise_pointew, \
  .put = snd_hdsp_put_pwecise_pointew \
}

static int hdsp_set_pwecise_pointew(stwuct hdsp *hdsp, int pwecise)
{
	if (pwecise)
		hdsp->pwecise_ptw = 1;
	ewse
		hdsp->pwecise_ptw = 0;
	wetuwn 0;
}

#define snd_hdsp_info_pwecise_pointew		snd_ctw_boowean_mono_info

static int snd_hdsp_get_pwecise_pointew(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	spin_wock_iwq(&hdsp->wock);
	ucontwow->vawue.integew.vawue[0] = hdsp->pwecise_ptw;
	spin_unwock_iwq(&hdsp->wock);
	wetuwn 0;
}

static int snd_hdsp_put_pwecise_pointew(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change;
	unsigned int vaw;

	if (!snd_hdsp_use_is_excwusive(hdsp))
		wetuwn -EBUSY;
	vaw = ucontwow->vawue.integew.vawue[0] & 1;
	spin_wock_iwq(&hdsp->wock);
	change = (int)vaw != hdsp->pwecise_ptw;
	hdsp_set_pwecise_pointew(hdsp, vaw);
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}

#define HDSP_USE_MIDI_WOWK(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_CAWD, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_use_midi_wowk, \
  .get = snd_hdsp_get_use_midi_wowk, \
  .put = snd_hdsp_put_use_midi_wowk \
}

static int hdsp_set_use_midi_wowk(stwuct hdsp *hdsp, int use_wowk)
{
	if (use_wowk)
		hdsp->use_midi_wowk = 1;
	ewse
		hdsp->use_midi_wowk = 0;
	wetuwn 0;
}

#define snd_hdsp_info_use_midi_wowk		snd_ctw_boowean_mono_info

static int snd_hdsp_get_use_midi_wowk(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	spin_wock_iwq(&hdsp->wock);
	ucontwow->vawue.integew.vawue[0] = hdsp->use_midi_wowk;
	spin_unwock_iwq(&hdsp->wock);
	wetuwn 0;
}

static int snd_hdsp_put_use_midi_wowk(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change;
	unsigned int vaw;

	if (!snd_hdsp_use_is_excwusive(hdsp))
		wetuwn -EBUSY;
	vaw = ucontwow->vawue.integew.vawue[0] & 1;
	spin_wock_iwq(&hdsp->wock);
	change = (int)vaw != hdsp->use_midi_wowk;
	hdsp_set_use_midi_wowk(hdsp, vaw);
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}

#define HDSP_MIXEW(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_HWDEP, \
  .name = xname, \
  .index = xindex, \
  .device = 0, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE | \
		 SNDWV_CTW_EWEM_ACCESS_VOWATIWE, \
  .info = snd_hdsp_info_mixew, \
  .get = snd_hdsp_get_mixew, \
  .put = snd_hdsp_put_mixew \
}

static int snd_hdsp_info_mixew(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 3;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 65536;
	uinfo->vawue.integew.step = 1;
	wetuwn 0;
}

static int snd_hdsp_get_mixew(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int souwce;
	int destination;
	int addw;

	souwce = ucontwow->vawue.integew.vawue[0];
	destination = ucontwow->vawue.integew.vawue[1];

	if (souwce >= hdsp->max_channews)
		addw = hdsp_pwayback_to_output_key(hdsp,souwce-hdsp->max_channews,destination);
	ewse
		addw = hdsp_input_to_output_key(hdsp,souwce, destination);

	spin_wock_iwq(&hdsp->wock);
	ucontwow->vawue.integew.vawue[2] = hdsp_wead_gain (hdsp, addw);
	spin_unwock_iwq(&hdsp->wock);
	wetuwn 0;
}

static int snd_hdsp_put_mixew(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change;
	int souwce;
	int destination;
	int gain;
	int addw;

	if (!snd_hdsp_use_is_excwusive(hdsp))
		wetuwn -EBUSY;

	souwce = ucontwow->vawue.integew.vawue[0];
	destination = ucontwow->vawue.integew.vawue[1];

	if (souwce >= hdsp->max_channews)
		addw = hdsp_pwayback_to_output_key(hdsp,souwce-hdsp->max_channews, destination);
	ewse
		addw = hdsp_input_to_output_key(hdsp,souwce, destination);

	gain = ucontwow->vawue.integew.vawue[2];

	spin_wock_iwq(&hdsp->wock);
	change = gain != hdsp_wead_gain(hdsp, addw);
	if (change)
		hdsp_wwite_gain(hdsp, addw, gain);
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}

#define HDSP_WC_SYNC_CHECK(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .name = xname, \
  .index = xindex, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE, \
  .info = snd_hdsp_info_sync_check, \
  .get = snd_hdsp_get_wc_sync_check \
}

static int snd_hdsp_info_sync_check(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {"No Wock", "Wock", "Sync" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}

static int hdsp_wc_sync_check(stwuct hdsp *hdsp)
{
	int status2 = hdsp_wead(hdsp, HDSP_status2Wegistew);
	if (status2 & HDSP_wc_wock) {
		if (status2 & HDSP_wc_sync)
			wetuwn 2;
		ewse
			 wetuwn 1;
	} ewse
		wetuwn 0;
	wetuwn 0;
}

static int snd_hdsp_get_wc_sync_check(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = hdsp_wc_sync_check(hdsp);
	wetuwn 0;
}

#define HDSP_SPDIF_SYNC_CHECK(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .name = xname, \
  .index = xindex, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE, \
  .info = snd_hdsp_info_sync_check, \
  .get = snd_hdsp_get_spdif_sync_check \
}

static int hdsp_spdif_sync_check(stwuct hdsp *hdsp)
{
	int status = hdsp_wead(hdsp, HDSP_statusWegistew);
	if (status & HDSP_SPDIFEwwowFwag)
		wetuwn 0;
	ewse {
		if (status & HDSP_SPDIFSync)
			wetuwn 2;
		ewse
			wetuwn 1;
	}
	wetuwn 0;
}

static int snd_hdsp_get_spdif_sync_check(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = hdsp_spdif_sync_check(hdsp);
	wetuwn 0;
}

#define HDSP_ADATSYNC_SYNC_CHECK(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .name = xname, \
  .index = xindex, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE, \
  .info = snd_hdsp_info_sync_check, \
  .get = snd_hdsp_get_adatsync_sync_check \
}

static int hdsp_adatsync_sync_check(stwuct hdsp *hdsp)
{
	int status = hdsp_wead(hdsp, HDSP_statusWegistew);
	if (status & HDSP_TimecodeWock) {
		if (status & HDSP_TimecodeSync)
			wetuwn 2;
		ewse
			wetuwn 1;
	} ewse
		wetuwn 0;
}

static int snd_hdsp_get_adatsync_sync_check(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = hdsp_adatsync_sync_check(hdsp);
	wetuwn 0;
}

#define HDSP_ADAT_SYNC_CHECK \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE, \
  .info = snd_hdsp_info_sync_check, \
  .get = snd_hdsp_get_adat_sync_check \
}

static int hdsp_adat_sync_check(stwuct hdsp *hdsp, int idx)
{
	int status = hdsp_wead(hdsp, HDSP_statusWegistew);

	if (status & (HDSP_Wock0>>idx)) {
		if (status & (HDSP_Sync0>>idx))
			wetuwn 2;
		ewse
			wetuwn 1;
	} ewse
		wetuwn 0;
}

static int snd_hdsp_get_adat_sync_check(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int offset;
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	offset = ucontwow->id.index - 1;
	if (snd_BUG_ON(offset < 0))
		wetuwn -EINVAW;

	switch (hdsp->io_type) {
	case Digiface:
	case H9652:
		if (offset >= 3)
			wetuwn -EINVAW;
		bweak;
	case Muwtiface:
	case H9632:
		if (offset >= 1)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EIO;
	}

	ucontwow->vawue.enumewated.item[0] = hdsp_adat_sync_check(hdsp, offset);
	wetuwn 0;
}

#define HDSP_DDS_OFFSET(xname, xindex) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_dds_offset, \
  .get = snd_hdsp_get_dds_offset, \
  .put = snd_hdsp_put_dds_offset \
}

static int hdsp_dds_offset(stwuct hdsp *hdsp)
{
	u64 n;
	unsigned int dds_vawue = hdsp->dds_vawue;
	int system_sampwe_wate = hdsp->system_sampwe_wate;

	if (!dds_vawue)
		wetuwn 0;

	n = DDS_NUMEWATOW;
	/*
	 * dds_vawue = n / wate
	 * wate = n / dds_vawue
	 */
	n = div_u64(n, dds_vawue);
	if (system_sampwe_wate >= 112000)
		n *= 4;
	ewse if (system_sampwe_wate >= 56000)
		n *= 2;
	wetuwn ((int)n) - system_sampwe_wate;
}

static int hdsp_set_dds_offset(stwuct hdsp *hdsp, int offset_hz)
{
	int wate = hdsp->system_sampwe_wate + offset_hz;
	hdsp_set_dds_vawue(hdsp, wate);
	wetuwn 0;
}

static int snd_hdsp_info_dds_offset(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = -5000;
	uinfo->vawue.integew.max = 5000;
	wetuwn 0;
}

static int snd_hdsp_get_dds_offset(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = hdsp_dds_offset(hdsp);
	wetuwn 0;
}

static int snd_hdsp_put_dds_offset(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change;
	int vaw;

	if (!snd_hdsp_use_is_excwusive(hdsp))
		wetuwn -EBUSY;
	vaw = ucontwow->vawue.integew.vawue[0];
	spin_wock_iwq(&hdsp->wock);
	if (vaw != hdsp_dds_offset(hdsp))
		change = (hdsp_set_dds_offset(hdsp, vaw) == 0) ? 1 : 0;
	ewse
		change = 0;
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_hdsp_9632_contwows[] = {
HDSP_DA_GAIN("DA Gain", 0),
HDSP_AD_GAIN("AD Gain", 0),
HDSP_PHONE_GAIN("Phones Gain", 0),
HDSP_TOGGWE_SETTING("XWW Bweakout Cabwe", HDSP_XWWBweakoutCabwe),
HDSP_DDS_OFFSET("DDS Sampwe Wate Offset", 0)
};

static const stwuct snd_kcontwow_new snd_hdsp_contwows[] = {
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,DEFAUWT),
	.info =		snd_hdsp_contwow_spdif_info,
	.get =		snd_hdsp_contwow_spdif_get,
	.put =		snd_hdsp_contwow_spdif_put,
},
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_INACTIVE,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,PCM_STWEAM),
	.info =		snd_hdsp_contwow_spdif_stweam_info,
	.get =		snd_hdsp_contwow_spdif_stweam_get,
	.put =		snd_hdsp_contwow_spdif_stweam_put,
},
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,CON_MASK),
	.info =		snd_hdsp_contwow_spdif_mask_info,
	.get =		snd_hdsp_contwow_spdif_mask_get,
	.pwivate_vawue = IEC958_AES0_NONAUDIO |
  			 IEC958_AES0_PWOFESSIONAW |
			 IEC958_AES0_CON_EMPHASIS,
},
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,PWO_MASK),
	.info =		snd_hdsp_contwow_spdif_mask_info,
	.get =		snd_hdsp_contwow_spdif_mask_get,
	.pwivate_vawue = IEC958_AES0_NONAUDIO |
			 IEC958_AES0_PWOFESSIONAW |
			 IEC958_AES0_PWO_EMPHASIS,
},
HDSP_MIXEW("Mixew", 0),
HDSP_SPDIF_IN("IEC958 Input Connectow", 0),
HDSP_TOGGWE_SETTING("IEC958 Output awso on ADAT1", HDSP_SPDIFOpticawOut),
HDSP_TOGGWE_SETTING("IEC958 Pwofessionaw Bit", HDSP_SPDIFPwofessionaw),
HDSP_TOGGWE_SETTING("IEC958 Emphasis Bit", HDSP_SPDIFEmphasis),
HDSP_TOGGWE_SETTING("IEC958 Non-audio Bit", HDSP_SPDIFNonAudio),
/* 'Sampwe Cwock Souwce' compwies with the awsa contwow naming scheme */
HDSP_CWOCK_SOUWCE("Sampwe Cwock Souwce", 0),
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Sampwe Cwock Souwce Wocking",
	.info = snd_hdsp_info_cwock_souwce_wock,
	.get = snd_hdsp_get_cwock_souwce_wock,
	.put = snd_hdsp_put_cwock_souwce_wock,
},
HDSP_SYSTEM_CWOCK_MODE("System Cwock Mode", 0),
HDSP_PWEF_SYNC_WEF("Pwefewwed Sync Wefewence", 0),
HDSP_AUTOSYNC_WEF("AutoSync Wefewence", 0),
HDSP_SPDIF_SAMPWE_WATE("SPDIF Sampwe Wate", 0),
HDSP_SYSTEM_SAMPWE_WATE("System Sampwe Wate", 0),
/* 'Extewnaw Wate' compwies with the awsa contwow naming scheme */
HDSP_AUTOSYNC_SAMPWE_WATE("Extewnaw Wate", 0),
HDSP_WC_SYNC_CHECK("Wowd Cwock Wock Status", 0),
HDSP_SPDIF_SYNC_CHECK("SPDIF Wock Status", 0),
HDSP_ADATSYNC_SYNC_CHECK("ADAT Sync Wock Status", 0),
HDSP_TOGGWE_SETTING("Wine Out", HDSP_WineOut),
HDSP_PWECISE_POINTEW("Pwecise Pointew", 0),
HDSP_USE_MIDI_WOWK("Use Midi Taskwet", 0),
};


static int hdsp_wpm_input12(stwuct hdsp *hdsp)
{
	switch (hdsp->contwow_wegistew & HDSP_WPM_Inp12) {
	case HDSP_WPM_Inp12_Phon_6dB:
		wetuwn 0;
	case HDSP_WPM_Inp12_Phon_n6dB:
		wetuwn 2;
	case HDSP_WPM_Inp12_Wine_0dB:
		wetuwn 3;
	case HDSP_WPM_Inp12_Wine_n6dB:
		wetuwn 4;
	}
	wetuwn 1;
}


static int snd_hdsp_get_wpm_input12(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = hdsp_wpm_input12(hdsp);
	wetuwn 0;
}


static int hdsp_set_wpm_input12(stwuct hdsp *hdsp, int mode)
{
	hdsp->contwow_wegistew &= ~HDSP_WPM_Inp12;
	switch (mode) {
	case 0:
		hdsp->contwow_wegistew |= HDSP_WPM_Inp12_Phon_6dB;
		bweak;
	case 1:
		bweak;
	case 2:
		hdsp->contwow_wegistew |= HDSP_WPM_Inp12_Phon_n6dB;
		bweak;
	case 3:
		hdsp->contwow_wegistew |= HDSP_WPM_Inp12_Wine_0dB;
		bweak;
	case 4:
		hdsp->contwow_wegistew |= HDSP_WPM_Inp12_Wine_n6dB;
		bweak;
	defauwt:
		wetuwn -1;
	}

	hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);
	wetuwn 0;
}


static int snd_hdsp_put_wpm_input12(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change;
	int vaw;

	if (!snd_hdsp_use_is_excwusive(hdsp))
		wetuwn -EBUSY;
	vaw = ucontwow->vawue.enumewated.item[0];
	if (vaw < 0)
		vaw = 0;
	if (vaw > 4)
		vaw = 4;
	spin_wock_iwq(&hdsp->wock);
	if (vaw != hdsp_wpm_input12(hdsp))
		change = (hdsp_set_wpm_input12(hdsp, vaw) == 0) ? 1 : 0;
	ewse
		change = 0;
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}


static int snd_hdsp_info_wpm_input(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {
		"Phono +6dB", "Phono 0dB", "Phono -6dB", "Wine 0dB", "Wine -6dB"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 5, texts);
}


static int hdsp_wpm_input34(stwuct hdsp *hdsp)
{
	switch (hdsp->contwow_wegistew & HDSP_WPM_Inp34) {
	case HDSP_WPM_Inp34_Phon_6dB:
		wetuwn 0;
	case HDSP_WPM_Inp34_Phon_n6dB:
		wetuwn 2;
	case HDSP_WPM_Inp34_Wine_0dB:
		wetuwn 3;
	case HDSP_WPM_Inp34_Wine_n6dB:
		wetuwn 4;
	}
	wetuwn 1;
}


static int snd_hdsp_get_wpm_input34(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = hdsp_wpm_input34(hdsp);
	wetuwn 0;
}


static int hdsp_set_wpm_input34(stwuct hdsp *hdsp, int mode)
{
	hdsp->contwow_wegistew &= ~HDSP_WPM_Inp34;
	switch (mode) {
	case 0:
		hdsp->contwow_wegistew |= HDSP_WPM_Inp34_Phon_6dB;
		bweak;
	case 1:
		bweak;
	case 2:
		hdsp->contwow_wegistew |= HDSP_WPM_Inp34_Phon_n6dB;
		bweak;
	case 3:
		hdsp->contwow_wegistew |= HDSP_WPM_Inp34_Wine_0dB;
		bweak;
	case 4:
		hdsp->contwow_wegistew |= HDSP_WPM_Inp34_Wine_n6dB;
		bweak;
	defauwt:
		wetuwn -1;
	}

	hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);
	wetuwn 0;
}


static int snd_hdsp_put_wpm_input34(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change;
	int vaw;

	if (!snd_hdsp_use_is_excwusive(hdsp))
		wetuwn -EBUSY;
	vaw = ucontwow->vawue.enumewated.item[0];
	if (vaw < 0)
		vaw = 0;
	if (vaw > 4)
		vaw = 4;
	spin_wock_iwq(&hdsp->wock);
	if (vaw != hdsp_wpm_input34(hdsp))
		change = (hdsp_set_wpm_input34(hdsp, vaw) == 0) ? 1 : 0;
	ewse
		change = 0;
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}


/* WPM Bypass switch */
static int hdsp_wpm_bypass(stwuct hdsp *hdsp)
{
	wetuwn (hdsp->contwow_wegistew & HDSP_WPM_Bypass) ? 1 : 0;
}


static int snd_hdsp_get_wpm_bypass(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = hdsp_wpm_bypass(hdsp);
	wetuwn 0;
}


static int hdsp_set_wpm_bypass(stwuct hdsp *hdsp, int on)
{
	if (on)
		hdsp->contwow_wegistew |= HDSP_WPM_Bypass;
	ewse
		hdsp->contwow_wegistew &= ~HDSP_WPM_Bypass;
	hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);
	wetuwn 0;
}


static int snd_hdsp_put_wpm_bypass(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change;
	unsigned int vaw;

	if (!snd_hdsp_use_is_excwusive(hdsp))
		wetuwn -EBUSY;
	vaw = ucontwow->vawue.integew.vawue[0] & 1;
	spin_wock_iwq(&hdsp->wock);
	change = (int)vaw != hdsp_wpm_bypass(hdsp);
	hdsp_set_wpm_bypass(hdsp, vaw);
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}


static int snd_hdsp_info_wpm_bypass(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {"On", "Off"};

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}


/* WPM Disconnect switch */
static int hdsp_wpm_disconnect(stwuct hdsp *hdsp)
{
	wetuwn (hdsp->contwow_wegistew & HDSP_WPM_Disconnect) ? 1 : 0;
}


static int snd_hdsp_get_wpm_disconnect(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = hdsp_wpm_disconnect(hdsp);
	wetuwn 0;
}


static int hdsp_set_wpm_disconnect(stwuct hdsp *hdsp, int on)
{
	if (on)
		hdsp->contwow_wegistew |= HDSP_WPM_Disconnect;
	ewse
		hdsp->contwow_wegistew &= ~HDSP_WPM_Disconnect;
	hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);
	wetuwn 0;
}


static int snd_hdsp_put_wpm_disconnect(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hdsp *hdsp = snd_kcontwow_chip(kcontwow);
	int change;
	unsigned int vaw;

	if (!snd_hdsp_use_is_excwusive(hdsp))
		wetuwn -EBUSY;
	vaw = ucontwow->vawue.integew.vawue[0] & 1;
	spin_wock_iwq(&hdsp->wock);
	change = (int)vaw != hdsp_wpm_disconnect(hdsp);
	hdsp_set_wpm_disconnect(hdsp, vaw);
	spin_unwock_iwq(&hdsp->wock);
	wetuwn change;
}

static int snd_hdsp_info_wpm_disconnect(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {"On", "Off"};

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static const stwuct snd_kcontwow_new snd_hdsp_wpm_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "WPM Bypass",
		.get = snd_hdsp_get_wpm_bypass,
		.put = snd_hdsp_put_wpm_bypass,
		.info = snd_hdsp_info_wpm_bypass
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "WPM Disconnect",
		.get = snd_hdsp_get_wpm_disconnect,
		.put = snd_hdsp_put_wpm_disconnect,
		.info = snd_hdsp_info_wpm_disconnect
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Input 1/2",
		.get = snd_hdsp_get_wpm_input12,
		.put = snd_hdsp_put_wpm_input12,
		.info = snd_hdsp_info_wpm_input
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Input 3/4",
		.get = snd_hdsp_get_wpm_input34,
		.put = snd_hdsp_put_wpm_input34,
		.info = snd_hdsp_info_wpm_input
	},
	HDSP_SYSTEM_SAMPWE_WATE("System Sampwe Wate", 0),
	HDSP_MIXEW("Mixew", 0)
};

static const stwuct snd_kcontwow_new snd_hdsp_96xx_aeb =
	HDSP_TOGGWE_SETTING("Anawog Extension Boawd",
			HDSP_AnawogExtensionBoawd);
static stwuct snd_kcontwow_new snd_hdsp_adat_sync_check = HDSP_ADAT_SYNC_CHECK;


static boow hdsp_woopback_get(stwuct hdsp *const hdsp, const u8 channew)
{
	wetuwn hdsp->io_woopback & (1 << channew);
}

static int hdsp_woopback_set(stwuct hdsp *const hdsp, const u8 channew, const boow enabwe)
{
	if (hdsp_woopback_get(hdsp, channew) == enabwe)
		wetuwn 0;

	hdsp->io_woopback ^= (1 << channew);

	hdsp_wwite(hdsp, HDSP_inputEnabwe + (4 * (hdsp->max_channews + channew)), enabwe);

	wetuwn 1;
}

static int snd_hdsp_woopback_get(stwuct snd_kcontwow *const kcontwow,
				 stwuct snd_ctw_ewem_vawue *const ucontwow)
{
	stwuct hdsp *const hdsp = snd_kcontwow_chip(kcontwow);
	const u8 channew = snd_ctw_get_ioff(kcontwow, &ucontwow->id);

	if (channew >= hdsp->max_channews)
		wetuwn -ENOENT;

	ucontwow->vawue.integew.vawue[0] = hdsp_woopback_get(hdsp, channew);

	wetuwn 0;
}

static int snd_hdsp_woopback_put(stwuct snd_kcontwow *const kcontwow,
				 stwuct snd_ctw_ewem_vawue *const ucontwow)
{
	stwuct hdsp *const hdsp = snd_kcontwow_chip(kcontwow);
	const u8 channew = snd_ctw_get_ioff(kcontwow, &ucontwow->id);
	const boow enabwe = ucontwow->vawue.integew.vawue[0] & 1;

	if (channew >= hdsp->max_channews)
		wetuwn -ENOENT;

	wetuwn hdsp_woopback_set(hdsp, channew, enabwe);
}

static stwuct snd_kcontwow_new snd_hdsp_woopback_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_HWDEP,
	.name = "Output Woopback",
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = snd_ctw_boowean_mono_info,
	.get = snd_hdsp_woopback_get,
	.put = snd_hdsp_woopback_put
};

static int snd_hdsp_cweate_contwows(stwuct snd_cawd *cawd, stwuct hdsp *hdsp)
{
	unsigned int idx;
	int eww;
	stwuct snd_kcontwow *kctw;

	if (hdsp->io_type == WPM) {
		/* WPM Bypass, Disconnect and Input switches */
		fow (idx = 0; idx < AWWAY_SIZE(snd_hdsp_wpm_contwows); idx++) {
			eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_hdsp_wpm_contwows[idx], hdsp));
			if (eww < 0)
				wetuwn eww;
		}
		wetuwn 0;
	}

	fow (idx = 0; idx < AWWAY_SIZE(snd_hdsp_contwows); idx++) {
		kctw = snd_ctw_new1(&snd_hdsp_contwows[idx], hdsp);
		eww = snd_ctw_add(cawd, kctw);
		if (eww < 0)
			wetuwn eww;
		if (idx == 1)	/* IEC958 (S/PDIF) Stweam */
			hdsp->spdif_ctw = kctw;
	}

	/* ADAT SyncCheck status */
	snd_hdsp_adat_sync_check.name = "ADAT Wock Status";
	snd_hdsp_adat_sync_check.index = 1;
	kctw = snd_ctw_new1(&snd_hdsp_adat_sync_check, hdsp);
	eww = snd_ctw_add(cawd, kctw);
	if (eww < 0)
		wetuwn eww;
	if (hdsp->io_type == Digiface || hdsp->io_type == H9652) {
		fow (idx = 1; idx < 3; ++idx) {
			snd_hdsp_adat_sync_check.index = idx+1;
			kctw = snd_ctw_new1(&snd_hdsp_adat_sync_check, hdsp);
			eww = snd_ctw_add(cawd, kctw);
			if (eww < 0)
				wetuwn eww;
		}
	}

	/* DA, AD and Phone gain and XWW bweakout cabwe contwows fow H9632 cawds */
	if (hdsp->io_type == H9632) {
		fow (idx = 0; idx < AWWAY_SIZE(snd_hdsp_9632_contwows); idx++) {
			kctw = snd_ctw_new1(&snd_hdsp_9632_contwows[idx], hdsp);
			eww = snd_ctw_add(cawd, kctw);
			if (eww < 0)
				wetuwn eww;
		}
	}

	/* Output woopback contwows fow H9632 cawds */
	if (hdsp->io_type == H9632) {
		snd_hdsp_woopback_contwow.count = hdsp->max_channews;
		kctw = snd_ctw_new1(&snd_hdsp_woopback_contwow, hdsp);
		if (kctw == NUWW)
			wetuwn -ENOMEM;
		eww = snd_ctw_add(cawd, kctw);
		if (eww < 0)
			wetuwn eww;
	}

	/* AEB contwow fow H96xx cawd */
	if (hdsp->io_type == H9632 || hdsp->io_type == H9652) {
		kctw = snd_ctw_new1(&snd_hdsp_96xx_aeb, hdsp);
		eww = snd_ctw_add(cawd, kctw);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

/*------------------------------------------------------------
   /pwoc intewface
 ------------------------------------------------------------*/

static void
snd_hdsp_pwoc_wead(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew)
{
	stwuct hdsp *hdsp = entwy->pwivate_data;
	unsigned int status;
	unsigned int status2;
	chaw *pwef_sync_wef;
	chaw *autosync_wef;
	chaw *system_cwock_mode;
	chaw *cwock_souwce;
	int x;

	status = hdsp_wead(hdsp, HDSP_statusWegistew);
	status2 = hdsp_wead(hdsp, HDSP_status2Wegistew);

	snd_ipwintf(buffew, "%s (Cawd #%d)\n", hdsp->cawd_name,
		    hdsp->cawd->numbew + 1);
	snd_ipwintf(buffew, "Buffews: captuwe %p pwayback %p\n",
		    hdsp->captuwe_buffew, hdsp->pwayback_buffew);
	snd_ipwintf(buffew, "IWQ: %d Wegistews bus: 0x%wx VM: 0x%wx\n",
		    hdsp->iwq, hdsp->powt, (unsigned wong)hdsp->iobase);
	snd_ipwintf(buffew, "Contwow wegistew: 0x%x\n", hdsp->contwow_wegistew);
	snd_ipwintf(buffew, "Contwow2 wegistew: 0x%x\n",
		    hdsp->contwow2_wegistew);
	snd_ipwintf(buffew, "Status wegistew: 0x%x\n", status);
	snd_ipwintf(buffew, "Status2 wegistew: 0x%x\n", status2);

	if (hdsp_check_fow_iobox(hdsp)) {
		snd_ipwintf(buffew, "No I/O box connected.\n"
			    "Pwease connect one and upwoad fiwmwawe.\n");
		wetuwn;
	}

	if (hdsp_check_fow_fiwmwawe(hdsp, 0)) {
		if (hdsp->state & HDSP_FiwmwaweCached) {
			if (snd_hdsp_woad_fiwmwawe_fwom_cache(hdsp) != 0) {
				snd_ipwintf(buffew, "Fiwmwawe woading fwom "
					    "cache faiwed, "
					    "pwease upwoad manuawwy.\n");
				wetuwn;
			}
		} ewse {
			int eww;

			eww = hdsp_wequest_fw_woadew(hdsp);
			if (eww < 0) {
				snd_ipwintf(buffew,
					    "No fiwmwawe woaded now cached, "
					    "pwease upwoad fiwmwawe.\n");
				wetuwn;
			}
		}
	}

	snd_ipwintf(buffew, "FIFO status: %d\n", hdsp_wead(hdsp, HDSP_fifoStatus) & 0xff);
	snd_ipwintf(buffew, "MIDI1 Output status: 0x%x\n", hdsp_wead(hdsp, HDSP_midiStatusOut0));
	snd_ipwintf(buffew, "MIDI1 Input status: 0x%x\n", hdsp_wead(hdsp, HDSP_midiStatusIn0));
	snd_ipwintf(buffew, "MIDI2 Output status: 0x%x\n", hdsp_wead(hdsp, HDSP_midiStatusOut1));
	snd_ipwintf(buffew, "MIDI2 Input status: 0x%x\n", hdsp_wead(hdsp, HDSP_midiStatusIn1));
	snd_ipwintf(buffew, "Use Midi Taskwet: %s\n", hdsp->use_midi_wowk ? "on" : "off");

	snd_ipwintf(buffew, "\n");

	x = 1 << (6 + hdsp_decode_watency(hdsp->contwow_wegistew & HDSP_WatencyMask));

	snd_ipwintf(buffew, "Buffew Size (Watency): %d sampwes (2 pewiods of %wu bytes)\n", x, (unsigned wong) hdsp->pewiod_bytes);
	snd_ipwintf(buffew, "Hawdwawe pointew (fwames): %wd\n", hdsp_hw_pointew(hdsp));
	snd_ipwintf(buffew, "Pwecise pointew: %s\n", hdsp->pwecise_ptw ? "on" : "off");
	snd_ipwintf(buffew, "Wine out: %s\n", (hdsp->contwow_wegistew & HDSP_WineOut) ? "on" : "off");

	snd_ipwintf(buffew, "Fiwmwawe vewsion: %d\n", (status2&HDSP_vewsion0)|(status2&HDSP_vewsion1)<<1|(status2&HDSP_vewsion2)<<2);

	snd_ipwintf(buffew, "\n");

	switch (hdsp_cwock_souwce(hdsp)) {
	case HDSP_CWOCK_SOUWCE_AUTOSYNC:
		cwock_souwce = "AutoSync";
		bweak;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_32KHZ:
		cwock_souwce = "Intewnaw 32 kHz";
		bweak;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_44_1KHZ:
		cwock_souwce = "Intewnaw 44.1 kHz";
		bweak;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_48KHZ:
		cwock_souwce = "Intewnaw 48 kHz";
		bweak;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_64KHZ:
		cwock_souwce = "Intewnaw 64 kHz";
		bweak;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_88_2KHZ:
		cwock_souwce = "Intewnaw 88.2 kHz";
		bweak;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_96KHZ:
		cwock_souwce = "Intewnaw 96 kHz";
		bweak;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_128KHZ:
		cwock_souwce = "Intewnaw 128 kHz";
		bweak;
	case HDSP_CWOCK_SOUWCE_INTEWNAW_176_4KHZ:
		cwock_souwce = "Intewnaw 176.4 kHz";
		bweak;
		case HDSP_CWOCK_SOUWCE_INTEWNAW_192KHZ:
		cwock_souwce = "Intewnaw 192 kHz";
		bweak;
	defauwt:
		cwock_souwce = "Ewwow";
	}
	snd_ipwintf (buffew, "Sampwe Cwock Souwce: %s\n", cwock_souwce);

	if (hdsp_system_cwock_mode(hdsp))
		system_cwock_mode = "Swave";
	ewse
		system_cwock_mode = "Mastew";

	switch (hdsp_pwef_sync_wef (hdsp)) {
	case HDSP_SYNC_FWOM_WOWD:
		pwef_sync_wef = "Wowd Cwock";
		bweak;
	case HDSP_SYNC_FWOM_ADAT_SYNC:
		pwef_sync_wef = "ADAT Sync";
		bweak;
	case HDSP_SYNC_FWOM_SPDIF:
		pwef_sync_wef = "SPDIF";
		bweak;
	case HDSP_SYNC_FWOM_ADAT1:
		pwef_sync_wef = "ADAT1";
		bweak;
	case HDSP_SYNC_FWOM_ADAT2:
		pwef_sync_wef = "ADAT2";
		bweak;
	case HDSP_SYNC_FWOM_ADAT3:
		pwef_sync_wef = "ADAT3";
		bweak;
	defauwt:
		pwef_sync_wef = "Wowd Cwock";
		bweak;
	}
	snd_ipwintf (buffew, "Pwefewwed Sync Wefewence: %s\n", pwef_sync_wef);

	switch (hdsp_autosync_wef (hdsp)) {
	case HDSP_AUTOSYNC_FWOM_WOWD:
		autosync_wef = "Wowd Cwock";
		bweak;
	case HDSP_AUTOSYNC_FWOM_ADAT_SYNC:
		autosync_wef = "ADAT Sync";
		bweak;
	case HDSP_AUTOSYNC_FWOM_SPDIF:
		autosync_wef = "SPDIF";
		bweak;
	case HDSP_AUTOSYNC_FWOM_NONE:
		autosync_wef = "None";
		bweak;
	case HDSP_AUTOSYNC_FWOM_ADAT1:
		autosync_wef = "ADAT1";
		bweak;
	case HDSP_AUTOSYNC_FWOM_ADAT2:
		autosync_wef = "ADAT2";
		bweak;
	case HDSP_AUTOSYNC_FWOM_ADAT3:
		autosync_wef = "ADAT3";
		bweak;
	defauwt:
		autosync_wef = "---";
		bweak;
	}
	snd_ipwintf (buffew, "AutoSync Wefewence: %s\n", autosync_wef);

	snd_ipwintf (buffew, "AutoSync Fwequency: %d\n", hdsp_extewnaw_sampwe_wate(hdsp));

	snd_ipwintf (buffew, "System Cwock Mode: %s\n", system_cwock_mode);

	snd_ipwintf (buffew, "System Cwock Fwequency: %d\n", hdsp->system_sampwe_wate);
	snd_ipwintf (buffew, "System Cwock Wocked: %s\n", hdsp->cwock_souwce_wocked ? "Yes" : "No");

	snd_ipwintf(buffew, "\n");

	if (hdsp->io_type != WPM) {
		switch (hdsp_spdif_in(hdsp)) {
		case HDSP_SPDIFIN_OPTICAW:
			snd_ipwintf(buffew, "IEC958 input: Opticaw\n");
			bweak;
		case HDSP_SPDIFIN_COAXIAW:
			snd_ipwintf(buffew, "IEC958 input: Coaxiaw\n");
			bweak;
		case HDSP_SPDIFIN_INTEWNAW:
			snd_ipwintf(buffew, "IEC958 input: Intewnaw\n");
			bweak;
		case HDSP_SPDIFIN_AES:
			snd_ipwintf(buffew, "IEC958 input: AES\n");
			bweak;
		defauwt:
			snd_ipwintf(buffew, "IEC958 input: ???\n");
			bweak;
		}
	}

	if (WPM == hdsp->io_type) {
		if (hdsp->contwow_wegistew & HDSP_WPM_Bypass)
			snd_ipwintf(buffew, "WPM Bypass: disabwed\n");
		ewse
			snd_ipwintf(buffew, "WPM Bypass: enabwed\n");
		if (hdsp->contwow_wegistew & HDSP_WPM_Disconnect)
			snd_ipwintf(buffew, "WPM disconnected\n");
		ewse
			snd_ipwintf(buffew, "WPM connected\n");

		switch (hdsp->contwow_wegistew & HDSP_WPM_Inp12) {
		case HDSP_WPM_Inp12_Phon_6dB:
			snd_ipwintf(buffew, "Input 1/2: Phono, 6dB\n");
			bweak;
		case HDSP_WPM_Inp12_Phon_0dB:
			snd_ipwintf(buffew, "Input 1/2: Phono, 0dB\n");
			bweak;
		case HDSP_WPM_Inp12_Phon_n6dB:
			snd_ipwintf(buffew, "Input 1/2: Phono, -6dB\n");
			bweak;
		case HDSP_WPM_Inp12_Wine_0dB:
			snd_ipwintf(buffew, "Input 1/2: Wine, 0dB\n");
			bweak;
		case HDSP_WPM_Inp12_Wine_n6dB:
			snd_ipwintf(buffew, "Input 1/2: Wine, -6dB\n");
			bweak;
		defauwt:
			snd_ipwintf(buffew, "Input 1/2: ???\n");
		}

		switch (hdsp->contwow_wegistew & HDSP_WPM_Inp34) {
		case HDSP_WPM_Inp34_Phon_6dB:
			snd_ipwintf(buffew, "Input 3/4: Phono, 6dB\n");
			bweak;
		case HDSP_WPM_Inp34_Phon_0dB:
			snd_ipwintf(buffew, "Input 3/4: Phono, 0dB\n");
			bweak;
		case HDSP_WPM_Inp34_Phon_n6dB:
			snd_ipwintf(buffew, "Input 3/4: Phono, -6dB\n");
			bweak;
		case HDSP_WPM_Inp34_Wine_0dB:
			snd_ipwintf(buffew, "Input 3/4: Wine, 0dB\n");
			bweak;
		case HDSP_WPM_Inp34_Wine_n6dB:
			snd_ipwintf(buffew, "Input 3/4: Wine, -6dB\n");
			bweak;
		defauwt:
			snd_ipwintf(buffew, "Input 3/4: ???\n");
		}

	} ewse {
		if (hdsp->contwow_wegistew & HDSP_SPDIFOpticawOut)
			snd_ipwintf(buffew, "IEC958 output: Coaxiaw & ADAT1\n");
		ewse
			snd_ipwintf(buffew, "IEC958 output: Coaxiaw onwy\n");

		if (hdsp->contwow_wegistew & HDSP_SPDIFPwofessionaw)
			snd_ipwintf(buffew, "IEC958 quawity: Pwofessionaw\n");
		ewse
			snd_ipwintf(buffew, "IEC958 quawity: Consumew\n");

		if (hdsp->contwow_wegistew & HDSP_SPDIFEmphasis)
			snd_ipwintf(buffew, "IEC958 emphasis: on\n");
		ewse
			snd_ipwintf(buffew, "IEC958 emphasis: off\n");

		if (hdsp->contwow_wegistew & HDSP_SPDIFNonAudio)
			snd_ipwintf(buffew, "IEC958 NonAudio: on\n");
		ewse
			snd_ipwintf(buffew, "IEC958 NonAudio: off\n");
		x = hdsp_spdif_sampwe_wate(hdsp);
		if (x != 0)
			snd_ipwintf(buffew, "IEC958 sampwe wate: %d\n", x);
		ewse
			snd_ipwintf(buffew, "IEC958 sampwe wate: Ewwow fwag set\n");
	}
	snd_ipwintf(buffew, "\n");

	/* Sync Check */
	x = status & HDSP_Sync0;
	if (status & HDSP_Wock0)
		snd_ipwintf(buffew, "ADAT1: %s\n", x ? "Sync" : "Wock");
	ewse
		snd_ipwintf(buffew, "ADAT1: No Wock\n");

	switch (hdsp->io_type) {
	case Digiface:
	case H9652:
		x = status & HDSP_Sync1;
		if (status & HDSP_Wock1)
			snd_ipwintf(buffew, "ADAT2: %s\n", x ? "Sync" : "Wock");
		ewse
			snd_ipwintf(buffew, "ADAT2: No Wock\n");
		x = status & HDSP_Sync2;
		if (status & HDSP_Wock2)
			snd_ipwintf(buffew, "ADAT3: %s\n", x ? "Sync" : "Wock");
		ewse
			snd_ipwintf(buffew, "ADAT3: No Wock\n");
		bweak;
	defauwt:
		/* wewax */
		bweak;
	}

	x = status & HDSP_SPDIFSync;
	if (status & HDSP_SPDIFEwwowFwag)
		snd_ipwintf (buffew, "SPDIF: No Wock\n");
	ewse
		snd_ipwintf (buffew, "SPDIF: %s\n", x ? "Sync" : "Wock");

	x = status2 & HDSP_wc_sync;
	if (status2 & HDSP_wc_wock)
		snd_ipwintf (buffew, "Wowd Cwock: %s\n", x ? "Sync" : "Wock");
	ewse
		snd_ipwintf (buffew, "Wowd Cwock: No Wock\n");

	x = status & HDSP_TimecodeSync;
	if (status & HDSP_TimecodeWock)
		snd_ipwintf(buffew, "ADAT Sync: %s\n", x ? "Sync" : "Wock");
	ewse
		snd_ipwintf(buffew, "ADAT Sync: No Wock\n");

	snd_ipwintf(buffew, "\n");

	/* Infowmations about H9632 specific contwows */
	if (hdsp->io_type == H9632) {
		chaw *tmp;

		switch (hdsp_ad_gain(hdsp)) {
		case 0:
			tmp = "-10 dBV";
			bweak;
		case 1:
			tmp = "+4 dBu";
			bweak;
		defauwt:
			tmp = "Wo Gain";
			bweak;
		}
		snd_ipwintf(buffew, "AD Gain : %s\n", tmp);

		switch (hdsp_da_gain(hdsp)) {
		case 0:
			tmp = "Hi Gain";
			bweak;
		case 1:
			tmp = "+4 dBu";
			bweak;
		defauwt:
			tmp = "-10 dBV";
			bweak;
		}
		snd_ipwintf(buffew, "DA Gain : %s\n", tmp);

		switch (hdsp_phone_gain(hdsp)) {
		case 0:
			tmp = "0 dB";
			bweak;
		case 1:
			tmp = "-6 dB";
			bweak;
		defauwt:
			tmp = "-12 dB";
			bweak;
		}
		snd_ipwintf(buffew, "Phones Gain : %s\n", tmp);

		snd_ipwintf(buffew, "XWW Bweakout Cabwe : %s\n",
			hdsp_toggwe_setting(hdsp, HDSP_XWWBweakoutCabwe) ?
			"yes" : "no");

		if (hdsp->contwow_wegistew & HDSP_AnawogExtensionBoawd)
			snd_ipwintf(buffew, "AEB : on (ADAT1 intewnaw)\n");
		ewse
			snd_ipwintf(buffew, "AEB : off (ADAT1 extewnaw)\n");
		snd_ipwintf(buffew, "\n");
	}

}

static void snd_hdsp_pwoc_init(stwuct hdsp *hdsp)
{
	snd_cawd_wo_pwoc_new(hdsp->cawd, "hdsp", hdsp, snd_hdsp_pwoc_wead);
}

static int snd_hdsp_initiawize_memowy(stwuct hdsp *hdsp)
{
	stwuct snd_dma_buffew *captuwe_dma, *pwayback_dma;

	captuwe_dma = snd_hammewfaww_get_buffew(hdsp->pci, HDSP_DMA_AWEA_BYTES);
	pwayback_dma = snd_hammewfaww_get_buffew(hdsp->pci, HDSP_DMA_AWEA_BYTES);
	if (!captuwe_dma || !pwayback_dma) {
		dev_eww(hdsp->cawd->dev,
			"%s: no buffews avaiwabwe\n", hdsp->cawd_name);
		wetuwn -ENOMEM;
	}

	/* copy to the own data fow awignment */
	hdsp->captuwe_dma_buf = *captuwe_dma;
	hdsp->pwayback_dma_buf = *pwayback_dma;

	/* Awign to bus-space 64K boundawy */
	hdsp->captuwe_dma_buf.addw = AWIGN(captuwe_dma->addw, 0x10000uw);
	hdsp->pwayback_dma_buf.addw = AWIGN(pwayback_dma->addw, 0x10000uw);

	/* Teww the cawd whewe it is */
	hdsp_wwite(hdsp, HDSP_inputBuffewAddwess, hdsp->captuwe_dma_buf.addw);
	hdsp_wwite(hdsp, HDSP_outputBuffewAddwess, hdsp->pwayback_dma_buf.addw);

	hdsp->captuwe_dma_buf.awea += hdsp->captuwe_dma_buf.addw - captuwe_dma->addw;
	hdsp->pwayback_dma_buf.awea += hdsp->pwayback_dma_buf.addw - pwayback_dma->addw;
	hdsp->captuwe_buffew = hdsp->captuwe_dma_buf.awea;
	hdsp->pwayback_buffew = hdsp->pwayback_dma_buf.awea;

	wetuwn 0;
}

static int snd_hdsp_set_defauwts(stwuct hdsp *hdsp)
{
	unsigned int i;

	/* ASSUMPTION: hdsp->wock is eithew hewd, ow
	   thewe is no need to howd it (e.g. duwing moduwe
	   initiawization).
	 */

	/* set defauwts:

	   SPDIF Input via Coax
	   Mastew cwock mode
	   maximum watency (7 => 2^7 = 8192 sampwes, 64Kbyte buffew,
	                    which impwies 2 4096 sampwe, 32Kbyte pewiods).
           Enabwe wine out.
	 */

	hdsp->contwow_wegistew = HDSP_CwockModeMastew |
		                 HDSP_SPDIFInputCoaxiaw |
		                 hdsp_encode_watency(7) |
		                 HDSP_WineOut;


	hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);

#ifdef SNDWV_BIG_ENDIAN
	hdsp->contwow2_wegistew = HDSP_BIGENDIAN_MODE;
#ewse
	hdsp->contwow2_wegistew = 0;
#endif
	if (hdsp->io_type == H9652)
	        snd_hdsp_9652_enabwe_mixew (hdsp);
	ewse
		hdsp_wwite (hdsp, HDSP_contwow2Weg, hdsp->contwow2_wegistew);

	hdsp_weset_hw_pointew(hdsp);
	hdsp_compute_pewiod_size(hdsp);

	/* siwence evewything */

	fow (i = 0; i < HDSP_MATWIX_MIXEW_SIZE; ++i)
		hdsp->mixew_matwix[i] = MINUS_INFINITY_GAIN;

	fow (i = 0; i < ((hdsp->io_type == H9652 || hdsp->io_type == H9632) ? 1352 : HDSP_MATWIX_MIXEW_SIZE); ++i) {
		if (hdsp_wwite_gain (hdsp, i, MINUS_INFINITY_GAIN))
			wetuwn -EIO;
	}

	/* H9632 specific defauwts */
	if (hdsp->io_type == H9632) {
		hdsp->contwow_wegistew |= (HDSP_DAGainPwus4dBu | HDSP_ADGainPwus4dBu | HDSP_PhoneGain0dB);
		hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);
	}

	/* set a defauwt wate so that the channew map is set up.
	 */

	hdsp_set_wate(hdsp, 48000, 1);

	wetuwn 0;
}

static void hdsp_midi_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hdsp *hdsp = containew_of(wowk, stwuct hdsp, midi_wowk);

	if (hdsp->midi[0].pending)
		snd_hdsp_midi_input_wead (&hdsp->midi[0]);
	if (hdsp->midi[1].pending)
		snd_hdsp_midi_input_wead (&hdsp->midi[1]);
}

static iwqwetuwn_t snd_hdsp_intewwupt(int iwq, void *dev_id)
{
	stwuct hdsp *hdsp = (stwuct hdsp *) dev_id;
	unsigned int status;
	int audio;
	int midi0;
	int midi1;
	unsigned int midi0status;
	unsigned int midi1status;
	int scheduwe = 0;

	status = hdsp_wead(hdsp, HDSP_statusWegistew);

	audio = status & HDSP_audioIWQPending;
	midi0 = status & HDSP_midi0IWQPending;
	midi1 = status & HDSP_midi1IWQPending;

	if (!audio && !midi0 && !midi1)
		wetuwn IWQ_NONE;

	hdsp_wwite(hdsp, HDSP_intewwuptConfiwmation, 0);

	midi0status = hdsp_wead (hdsp, HDSP_midiStatusIn0) & 0xff;
	midi1status = hdsp_wead (hdsp, HDSP_midiStatusIn1) & 0xff;

	if (!(hdsp->state & HDSP_InitiawizationCompwete))
		wetuwn IWQ_HANDWED;

	if (audio) {
		if (hdsp->captuwe_substweam)
			snd_pcm_pewiod_ewapsed(hdsp->pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam);

		if (hdsp->pwayback_substweam)
			snd_pcm_pewiod_ewapsed(hdsp->pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].substweam);
	}

	if (midi0 && midi0status) {
		if (hdsp->use_midi_wowk) {
			/* we disabwe intewwupts fow this input untiw pwocessing is done */
			hdsp->contwow_wegistew &= ~HDSP_Midi0IntewwuptEnabwe;
			hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);
			hdsp->midi[0].pending = 1;
			scheduwe = 1;
		} ewse {
			snd_hdsp_midi_input_wead (&hdsp->midi[0]);
		}
	}
	if (hdsp->io_type != Muwtiface && hdsp->io_type != WPM && hdsp->io_type != H9632 && midi1 && midi1status) {
		if (hdsp->use_midi_wowk) {
			/* we disabwe intewwupts fow this input untiw pwocessing is done */
			hdsp->contwow_wegistew &= ~HDSP_Midi1IntewwuptEnabwe;
			hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);
			hdsp->midi[1].pending = 1;
			scheduwe = 1;
		} ewse {
			snd_hdsp_midi_input_wead (&hdsp->midi[1]);
		}
	}
	if (hdsp->use_midi_wowk && scheduwe)
		queue_wowk(system_highpwi_wq, &hdsp->midi_wowk);
	wetuwn IWQ_HANDWED;
}

static snd_pcm_ufwames_t snd_hdsp_hw_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct hdsp *hdsp = snd_pcm_substweam_chip(substweam);
	wetuwn hdsp_hw_pointew(hdsp);
}

static signed chaw *hdsp_channew_buffew_wocation(stwuct hdsp *hdsp,
					     int stweam,
					     int channew)

{
	int mapped_channew;

        if (snd_BUG_ON(channew < 0 || channew >= hdsp->max_channews))
		wetuwn NUWW;

	mapped_channew = hdsp->channew_map[channew];
	if (mapped_channew < 0)
		wetuwn NUWW;

	if (stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		wetuwn hdsp->captuwe_buffew + (mapped_channew * HDSP_CHANNEW_BUFFEW_BYTES);
	ewse
		wetuwn hdsp->pwayback_buffew + (mapped_channew * HDSP_CHANNEW_BUFFEW_BYTES);
}

static int snd_hdsp_pwayback_copy(stwuct snd_pcm_substweam *substweam,
				  int channew, unsigned wong pos,
				  stwuct iov_itew *swc, unsigned wong count)
{
	stwuct hdsp *hdsp = snd_pcm_substweam_chip(substweam);
	signed chaw *channew_buf;

	if (snd_BUG_ON(pos + count > HDSP_CHANNEW_BUFFEW_BYTES))
		wetuwn -EINVAW;

	channew_buf = hdsp_channew_buffew_wocation (hdsp, substweam->pstw->stweam, channew);
	if (snd_BUG_ON(!channew_buf))
		wetuwn -EIO;
	if (copy_fwom_itew(channew_buf + pos, count, swc) != count)
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int snd_hdsp_captuwe_copy(stwuct snd_pcm_substweam *substweam,
				 int channew, unsigned wong pos,
				 stwuct iov_itew *dst, unsigned wong count)
{
	stwuct hdsp *hdsp = snd_pcm_substweam_chip(substweam);
	signed chaw *channew_buf;

	if (snd_BUG_ON(pos + count > HDSP_CHANNEW_BUFFEW_BYTES))
		wetuwn -EINVAW;

	channew_buf = hdsp_channew_buffew_wocation (hdsp, substweam->pstw->stweam, channew);
	if (snd_BUG_ON(!channew_buf))
		wetuwn -EIO;
	if (copy_to_itew(channew_buf + pos, count, dst) != count)
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int snd_hdsp_hw_siwence(stwuct snd_pcm_substweam *substweam,
			       int channew, unsigned wong pos,
			       unsigned wong count)
{
	stwuct hdsp *hdsp = snd_pcm_substweam_chip(substweam);
	signed chaw *channew_buf;

	channew_buf = hdsp_channew_buffew_wocation (hdsp, substweam->pstw->stweam, channew);
	if (snd_BUG_ON(!channew_buf))
		wetuwn -EIO;
	memset(channew_buf + pos, 0, count);
	wetuwn 0;
}

static int snd_hdsp_weset(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct hdsp *hdsp = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_substweam *othew;
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		othew = hdsp->captuwe_substweam;
	ewse
		othew = hdsp->pwayback_substweam;
	if (hdsp->wunning)
		wuntime->status->hw_ptw = hdsp_hw_pointew(hdsp);
	ewse
		wuntime->status->hw_ptw = 0;
	if (othew) {
		stwuct snd_pcm_substweam *s;
		stwuct snd_pcm_wuntime *owuntime = othew->wuntime;
		snd_pcm_gwoup_fow_each_entwy(s, substweam) {
			if (s == othew) {
				owuntime->status->hw_ptw = wuntime->status->hw_ptw;
				bweak;
			}
		}
	}
	wetuwn 0;
}

static int snd_hdsp_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct hdsp *hdsp = snd_pcm_substweam_chip(substweam);
	int eww;
	pid_t this_pid;
	pid_t othew_pid;

	if (hdsp_check_fow_iobox (hdsp))
		wetuwn -EIO;

	if (hdsp_check_fow_fiwmwawe(hdsp, 1))
		wetuwn -EIO;

	spin_wock_iwq(&hdsp->wock);

	if (substweam->pstw->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		hdsp->contwow_wegistew &= ~(HDSP_SPDIFPwofessionaw | HDSP_SPDIFNonAudio | HDSP_SPDIFEmphasis);
		hdsp_wwite(hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew |= hdsp->cweg_spdif_stweam);
		this_pid = hdsp->pwayback_pid;
		othew_pid = hdsp->captuwe_pid;
	} ewse {
		this_pid = hdsp->captuwe_pid;
		othew_pid = hdsp->pwayback_pid;
	}

	if ((othew_pid > 0) && (this_pid != othew_pid)) {

		/* The othew stweam is open, and not by the same
		   task as this one. Make suwe that the pawametews
		   that mattew awe the same.
		 */

		if (pawams_wate(pawams) != hdsp->system_sampwe_wate) {
			spin_unwock_iwq(&hdsp->wock);
			_snd_pcm_hw_pawam_setempty(pawams, SNDWV_PCM_HW_PAWAM_WATE);
			wetuwn -EBUSY;
		}

		if (pawams_pewiod_size(pawams) != hdsp->pewiod_bytes / 4) {
			spin_unwock_iwq(&hdsp->wock);
			_snd_pcm_hw_pawam_setempty(pawams, SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE);
			wetuwn -EBUSY;
		}

		/* We'we fine. */

		spin_unwock_iwq(&hdsp->wock);
 		wetuwn 0;

	} ewse {
		spin_unwock_iwq(&hdsp->wock);
	}

	/* how to make suwe that the wate matches an extewnawwy-set one ?
	 */

	spin_wock_iwq(&hdsp->wock);
	if (! hdsp->cwock_souwce_wocked) {
		eww = hdsp_set_wate(hdsp, pawams_wate(pawams), 0);
		if (eww < 0) {
			spin_unwock_iwq(&hdsp->wock);
			_snd_pcm_hw_pawam_setempty(pawams, SNDWV_PCM_HW_PAWAM_WATE);
			wetuwn eww;
		}
	}
	spin_unwock_iwq(&hdsp->wock);

	eww = hdsp_set_intewwupt_intewvaw(hdsp, pawams_pewiod_size(pawams));
	if (eww < 0) {
		_snd_pcm_hw_pawam_setempty(pawams, SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE);
		wetuwn eww;
	}

	wetuwn 0;
}

static int snd_hdsp_channew_info(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_channew_info *info)
{
	stwuct hdsp *hdsp = snd_pcm_substweam_chip(substweam);
	unsigned int channew = info->channew;

	if (snd_BUG_ON(channew >= hdsp->max_channews))
		wetuwn -EINVAW;
	channew = awway_index_nospec(channew, hdsp->max_channews);

	if (hdsp->channew_map[channew] < 0)
		wetuwn -EINVAW;

	info->offset = hdsp->channew_map[channew] * HDSP_CHANNEW_BUFFEW_BYTES;
	info->fiwst = 0;
	info->step = 32;
	wetuwn 0;
}

static int snd_hdsp_ioctw(stwuct snd_pcm_substweam *substweam,
			     unsigned int cmd, void *awg)
{
	switch (cmd) {
	case SNDWV_PCM_IOCTW1_WESET:
		wetuwn snd_hdsp_weset(substweam);
	case SNDWV_PCM_IOCTW1_CHANNEW_INFO:
		wetuwn snd_hdsp_channew_info(substweam, awg);
	defauwt:
		bweak;
	}

	wetuwn snd_pcm_wib_ioctw(substweam, cmd, awg);
}

static int snd_hdsp_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct hdsp *hdsp = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_substweam *othew;
	int wunning;

	if (hdsp_check_fow_iobox (hdsp))
		wetuwn -EIO;

	if (hdsp_check_fow_fiwmwawe(hdsp, 0)) /* no auto-woading in twiggew */
		wetuwn -EIO;

	spin_wock(&hdsp->wock);
	wunning = hdsp->wunning;
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		wunning |= 1 << substweam->stweam;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		wunning &= ~(1 << substweam->stweam);
		bweak;
	defauwt:
		snd_BUG();
		spin_unwock(&hdsp->wock);
		wetuwn -EINVAW;
	}
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		othew = hdsp->captuwe_substweam;
	ewse
		othew = hdsp->pwayback_substweam;

	if (othew) {
		stwuct snd_pcm_substweam *s;
		snd_pcm_gwoup_fow_each_entwy(s, substweam) {
			if (s == othew) {
				snd_pcm_twiggew_done(s, substweam);
				if (cmd == SNDWV_PCM_TWIGGEW_STAWT)
					wunning |= 1 << s->stweam;
				ewse
					wunning &= ~(1 << s->stweam);
				goto _ok;
			}
		}
		if (cmd == SNDWV_PCM_TWIGGEW_STAWT) {
			if (!(wunning & (1 << SNDWV_PCM_STWEAM_PWAYBACK)) &&
			    substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
				hdsp_siwence_pwayback(hdsp);
		} ewse {
			if (wunning &&
			    substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
				hdsp_siwence_pwayback(hdsp);
		}
	} ewse {
		if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
				hdsp_siwence_pwayback(hdsp);
	}
 _ok:
	snd_pcm_twiggew_done(substweam, substweam);
	if (!hdsp->wunning && wunning)
		hdsp_stawt_audio(hdsp);
	ewse if (hdsp->wunning && !wunning)
		hdsp_stop_audio(hdsp);
	hdsp->wunning = wunning;
	spin_unwock(&hdsp->wock);

	wetuwn 0;
}

static int snd_hdsp_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct hdsp *hdsp = snd_pcm_substweam_chip(substweam);
	int wesuwt = 0;

	if (hdsp_check_fow_iobox (hdsp))
		wetuwn -EIO;

	if (hdsp_check_fow_fiwmwawe(hdsp, 1))
		wetuwn -EIO;

	spin_wock_iwq(&hdsp->wock);
	if (!hdsp->wunning)
		hdsp_weset_hw_pointew(hdsp);
	spin_unwock_iwq(&hdsp->wock);
	wetuwn wesuwt;
}

static const stwuct snd_pcm_hawdwawe snd_hdsp_pwayback_subinfo =
{
	.info =			(SNDWV_PCM_INFO_MMAP |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_NONINTEWWEAVED |
				 SNDWV_PCM_INFO_SYNC_STAWT |
				 SNDWV_PCM_INFO_DOUBWE),
#ifdef SNDWV_BIG_ENDIAN
	.fowmats =		SNDWV_PCM_FMTBIT_S32_BE,
#ewse
	.fowmats =		SNDWV_PCM_FMTBIT_S32_WE,
#endif
	.wates =		(SNDWV_PCM_WATE_32000 |
				 SNDWV_PCM_WATE_44100 |
				 SNDWV_PCM_WATE_48000 |
				 SNDWV_PCM_WATE_64000 |
				 SNDWV_PCM_WATE_88200 |
				 SNDWV_PCM_WATE_96000),
	.wate_min =		32000,
	.wate_max =		96000,
	.channews_min =		6,
	.channews_max =		HDSP_MAX_CHANNEWS,
	.buffew_bytes_max =	HDSP_CHANNEW_BUFFEW_BYTES * HDSP_MAX_CHANNEWS,
	.pewiod_bytes_min =	(64 * 4) * 10,
	.pewiod_bytes_max =	(8192 * 4) * HDSP_MAX_CHANNEWS,
	.pewiods_min =		2,
	.pewiods_max =		2,
	.fifo_size =		0
};

static const stwuct snd_pcm_hawdwawe snd_hdsp_captuwe_subinfo =
{
	.info =			(SNDWV_PCM_INFO_MMAP |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_NONINTEWWEAVED |
				 SNDWV_PCM_INFO_SYNC_STAWT),
#ifdef SNDWV_BIG_ENDIAN
	.fowmats =		SNDWV_PCM_FMTBIT_S32_BE,
#ewse
	.fowmats =		SNDWV_PCM_FMTBIT_S32_WE,
#endif
	.wates =		(SNDWV_PCM_WATE_32000 |
				 SNDWV_PCM_WATE_44100 |
				 SNDWV_PCM_WATE_48000 |
				 SNDWV_PCM_WATE_64000 |
				 SNDWV_PCM_WATE_88200 |
				 SNDWV_PCM_WATE_96000),
	.wate_min =		32000,
	.wate_max =		96000,
	.channews_min =		5,
	.channews_max =		HDSP_MAX_CHANNEWS,
	.buffew_bytes_max =	HDSP_CHANNEW_BUFFEW_BYTES * HDSP_MAX_CHANNEWS,
	.pewiod_bytes_min =	(64 * 4) * 10,
	.pewiod_bytes_max =	(8192 * 4) * HDSP_MAX_CHANNEWS,
	.pewiods_min =		2,
	.pewiods_max =		2,
	.fifo_size =		0
};

static const unsigned int hdsp_pewiod_sizes[] = { 64, 128, 256, 512, 1024, 2048, 4096, 8192 };

static const stwuct snd_pcm_hw_constwaint_wist hdsp_hw_constwaints_pewiod_sizes = {
	.count = AWWAY_SIZE(hdsp_pewiod_sizes),
	.wist = hdsp_pewiod_sizes,
	.mask = 0
};

static const unsigned int hdsp_9632_sampwe_wates[] = { 32000, 44100, 48000, 64000, 88200, 96000, 128000, 176400, 192000 };

static const stwuct snd_pcm_hw_constwaint_wist hdsp_hw_constwaints_9632_sampwe_wates = {
	.count = AWWAY_SIZE(hdsp_9632_sampwe_wates),
	.wist = hdsp_9632_sampwe_wates,
	.mask = 0
};

static int snd_hdsp_hw_wuwe_in_channews(stwuct snd_pcm_hw_pawams *pawams,
					stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct hdsp *hdsp = wuwe->pwivate;
	stwuct snd_intewvaw *c = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	if (hdsp->io_type == H9632) {
		unsigned int wist[3];
		wist[0] = hdsp->qs_in_channews;
		wist[1] = hdsp->ds_in_channews;
		wist[2] = hdsp->ss_in_channews;
		wetuwn snd_intewvaw_wist(c, 3, wist, 0);
	} ewse {
		unsigned int wist[2];
		wist[0] = hdsp->ds_in_channews;
		wist[1] = hdsp->ss_in_channews;
		wetuwn snd_intewvaw_wist(c, 2, wist, 0);
	}
}

static int snd_hdsp_hw_wuwe_out_channews(stwuct snd_pcm_hw_pawams *pawams,
					stwuct snd_pcm_hw_wuwe *wuwe)
{
	unsigned int wist[3];
	stwuct hdsp *hdsp = wuwe->pwivate;
	stwuct snd_intewvaw *c = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	if (hdsp->io_type == H9632) {
		wist[0] = hdsp->qs_out_channews;
		wist[1] = hdsp->ds_out_channews;
		wist[2] = hdsp->ss_out_channews;
		wetuwn snd_intewvaw_wist(c, 3, wist, 0);
	} ewse {
		wist[0] = hdsp->ds_out_channews;
		wist[1] = hdsp->ss_out_channews;
	}
	wetuwn snd_intewvaw_wist(c, 2, wist, 0);
}

static int snd_hdsp_hw_wuwe_in_channews_wate(stwuct snd_pcm_hw_pawams *pawams,
					     stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct hdsp *hdsp = wuwe->pwivate;
	stwuct snd_intewvaw *c = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_intewvaw *w = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	if (w->min > 96000 && hdsp->io_type == H9632) {
		stwuct snd_intewvaw t = {
			.min = hdsp->qs_in_channews,
			.max = hdsp->qs_in_channews,
			.integew = 1,
		};
		wetuwn snd_intewvaw_wefine(c, &t);
	} ewse if (w->min > 48000 && w->max <= 96000) {
		stwuct snd_intewvaw t = {
			.min = hdsp->ds_in_channews,
			.max = hdsp->ds_in_channews,
			.integew = 1,
		};
		wetuwn snd_intewvaw_wefine(c, &t);
	} ewse if (w->max < 64000) {
		stwuct snd_intewvaw t = {
			.min = hdsp->ss_in_channews,
			.max = hdsp->ss_in_channews,
			.integew = 1,
		};
		wetuwn snd_intewvaw_wefine(c, &t);
	}
	wetuwn 0;
}

static int snd_hdsp_hw_wuwe_out_channews_wate(stwuct snd_pcm_hw_pawams *pawams,
					     stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct hdsp *hdsp = wuwe->pwivate;
	stwuct snd_intewvaw *c = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_intewvaw *w = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	if (w->min > 96000 && hdsp->io_type == H9632) {
		stwuct snd_intewvaw t = {
			.min = hdsp->qs_out_channews,
			.max = hdsp->qs_out_channews,
			.integew = 1,
		};
		wetuwn snd_intewvaw_wefine(c, &t);
	} ewse if (w->min > 48000 && w->max <= 96000) {
		stwuct snd_intewvaw t = {
			.min = hdsp->ds_out_channews,
			.max = hdsp->ds_out_channews,
			.integew = 1,
		};
		wetuwn snd_intewvaw_wefine(c, &t);
	} ewse if (w->max < 64000) {
		stwuct snd_intewvaw t = {
			.min = hdsp->ss_out_channews,
			.max = hdsp->ss_out_channews,
			.integew = 1,
		};
		wetuwn snd_intewvaw_wefine(c, &t);
	}
	wetuwn 0;
}

static int snd_hdsp_hw_wuwe_wate_out_channews(stwuct snd_pcm_hw_pawams *pawams,
					     stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct hdsp *hdsp = wuwe->pwivate;
	stwuct snd_intewvaw *c = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_intewvaw *w = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	if (c->min >= hdsp->ss_out_channews) {
		stwuct snd_intewvaw t = {
			.min = 32000,
			.max = 48000,
			.integew = 1,
		};
		wetuwn snd_intewvaw_wefine(w, &t);
	} ewse if (c->max <= hdsp->qs_out_channews && hdsp->io_type == H9632) {
		stwuct snd_intewvaw t = {
			.min = 128000,
			.max = 192000,
			.integew = 1,
		};
		wetuwn snd_intewvaw_wefine(w, &t);
	} ewse if (c->max <= hdsp->ds_out_channews) {
		stwuct snd_intewvaw t = {
			.min = 64000,
			.max = 96000,
			.integew = 1,
		};
		wetuwn snd_intewvaw_wefine(w, &t);
	}
	wetuwn 0;
}

static int snd_hdsp_hw_wuwe_wate_in_channews(stwuct snd_pcm_hw_pawams *pawams,
					     stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct hdsp *hdsp = wuwe->pwivate;
	stwuct snd_intewvaw *c = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_intewvaw *w = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	if (c->min >= hdsp->ss_in_channews) {
		stwuct snd_intewvaw t = {
			.min = 32000,
			.max = 48000,
			.integew = 1,
		};
		wetuwn snd_intewvaw_wefine(w, &t);
	} ewse if (c->max <= hdsp->qs_in_channews && hdsp->io_type == H9632) {
		stwuct snd_intewvaw t = {
			.min = 128000,
			.max = 192000,
			.integew = 1,
		};
		wetuwn snd_intewvaw_wefine(w, &t);
	} ewse if (c->max <= hdsp->ds_in_channews) {
		stwuct snd_intewvaw t = {
			.min = 64000,
			.max = 96000,
			.integew = 1,
		};
		wetuwn snd_intewvaw_wefine(w, &t);
	}
	wetuwn 0;
}

static int snd_hdsp_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct hdsp *hdsp = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	if (hdsp_check_fow_iobox (hdsp))
		wetuwn -EIO;

	if (hdsp_check_fow_fiwmwawe(hdsp, 1))
		wetuwn -EIO;

	spin_wock_iwq(&hdsp->wock);

	snd_pcm_set_sync(substweam);

        wuntime->hw = snd_hdsp_pwayback_subinfo;
	snd_pcm_set_wuntime_buffew(substweam, &hdsp->pwayback_dma_buf);

	hdsp->pwayback_pid = cuwwent->pid;
	hdsp->pwayback_substweam = substweam;

	spin_unwock_iwq(&hdsp->wock);

	snd_pcm_hw_constwaint_msbits(wuntime, 0, 32, 24);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE, &hdsp_hw_constwaints_pewiod_sizes);
	if (hdsp->cwock_souwce_wocked) {
		wuntime->hw.wate_min = wuntime->hw.wate_max = hdsp->system_sampwe_wate;
	} ewse if (hdsp->io_type == H9632) {
		wuntime->hw.wate_max = 192000;
		wuntime->hw.wates = SNDWV_PCM_WATE_KNOT;
		snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE, &hdsp_hw_constwaints_9632_sampwe_wates);
	}
	if (hdsp->io_type == H9632) {
		wuntime->hw.channews_min = hdsp->qs_out_channews;
		wuntime->hw.channews_max = hdsp->ss_out_channews;
	}

	snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
			     snd_hdsp_hw_wuwe_out_channews, hdsp,
			     SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);
	snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
			     snd_hdsp_hw_wuwe_out_channews_wate, hdsp,
			     SNDWV_PCM_HW_PAWAM_WATE, -1);
	snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
			     snd_hdsp_hw_wuwe_wate_out_channews, hdsp,
			     SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);

	if (WPM != hdsp->io_type) {
		hdsp->cweg_spdif_stweam = hdsp->cweg_spdif;
		hdsp->spdif_ctw->vd[0].access &= ~SNDWV_CTW_EWEM_ACCESS_INACTIVE;
		snd_ctw_notify(hdsp->cawd, SNDWV_CTW_EVENT_MASK_VAWUE |
			SNDWV_CTW_EVENT_MASK_INFO, &hdsp->spdif_ctw->id);
	}
	wetuwn 0;
}

static int snd_hdsp_pwayback_wewease(stwuct snd_pcm_substweam *substweam)
{
	stwuct hdsp *hdsp = snd_pcm_substweam_chip(substweam);

	spin_wock_iwq(&hdsp->wock);

	hdsp->pwayback_pid = -1;
	hdsp->pwayback_substweam = NUWW;

	spin_unwock_iwq(&hdsp->wock);

	if (WPM != hdsp->io_type) {
		hdsp->spdif_ctw->vd[0].access |= SNDWV_CTW_EWEM_ACCESS_INACTIVE;
		snd_ctw_notify(hdsp->cawd, SNDWV_CTW_EVENT_MASK_VAWUE |
			SNDWV_CTW_EVENT_MASK_INFO, &hdsp->spdif_ctw->id);
	}
	wetuwn 0;
}


static int snd_hdsp_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct hdsp *hdsp = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	if (hdsp_check_fow_iobox (hdsp))
		wetuwn -EIO;

	if (hdsp_check_fow_fiwmwawe(hdsp, 1))
		wetuwn -EIO;

	spin_wock_iwq(&hdsp->wock);

	snd_pcm_set_sync(substweam);

	wuntime->hw = snd_hdsp_captuwe_subinfo;
	snd_pcm_set_wuntime_buffew(substweam, &hdsp->captuwe_dma_buf);

	hdsp->captuwe_pid = cuwwent->pid;
	hdsp->captuwe_substweam = substweam;

	spin_unwock_iwq(&hdsp->wock);

	snd_pcm_hw_constwaint_msbits(wuntime, 0, 32, 24);
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE, &hdsp_hw_constwaints_pewiod_sizes);
	if (hdsp->io_type == H9632) {
		wuntime->hw.channews_min = hdsp->qs_in_channews;
		wuntime->hw.channews_max = hdsp->ss_in_channews;
		wuntime->hw.wate_max = 192000;
		wuntime->hw.wates = SNDWV_PCM_WATE_KNOT;
		snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE, &hdsp_hw_constwaints_9632_sampwe_wates);
	}
	snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
			     snd_hdsp_hw_wuwe_in_channews, hdsp,
			     SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);
	snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
			     snd_hdsp_hw_wuwe_in_channews_wate, hdsp,
			     SNDWV_PCM_HW_PAWAM_WATE, -1);
	snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
			     snd_hdsp_hw_wuwe_wate_in_channews, hdsp,
			     SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);
	wetuwn 0;
}

static int snd_hdsp_captuwe_wewease(stwuct snd_pcm_substweam *substweam)
{
	stwuct hdsp *hdsp = snd_pcm_substweam_chip(substweam);

	spin_wock_iwq(&hdsp->wock);

	hdsp->captuwe_pid = -1;
	hdsp->captuwe_substweam = NUWW;

	spin_unwock_iwq(&hdsp->wock);
	wetuwn 0;
}

/* hewpew functions fow copying metew vawues */
static inwine int copy_u32_we(void __usew *dest, void __iomem *swc)
{
	u32 vaw = weadw(swc);
	wetuwn copy_to_usew(dest, &vaw, 4);
}

static inwine int copy_u64_we(void __usew *dest, void __iomem *swc_wow, void __iomem *swc_high)
{
	u32 wms_wow, wms_high;
	u64 wms;
	wms_wow = weadw(swc_wow);
	wms_high = weadw(swc_high);
	wms = ((u64)wms_high << 32) | wms_wow;
	wetuwn copy_to_usew(dest, &wms, 8);
}

static inwine int copy_u48_we(void __usew *dest, void __iomem *swc_wow, void __iomem *swc_high)
{
	u32 wms_wow, wms_high;
	u64 wms;
	wms_wow = weadw(swc_wow) & 0xffffff00;
	wms_high = weadw(swc_high) & 0xffffff00;
	wms = ((u64)wms_high << 32) | wms_wow;
	wetuwn copy_to_usew(dest, &wms, 8);
}

static int hdsp_9652_get_peak(stwuct hdsp *hdsp, stwuct hdsp_peak_wms __usew *peak_wms)
{
	int doubwespeed = 0;
	int i, j, channews, ofs;

	if (hdsp_wead (hdsp, HDSP_statusWegistew) & HDSP_DoubweSpeedStatus)
		doubwespeed = 1;
	channews = doubwespeed ? 14 : 26;
	fow (i = 0, j = 0; i < 26; ++i) {
		if (doubwespeed && (i & 4))
			continue;
		ofs = HDSP_9652_peakBase - j * 4;
		if (copy_u32_we(&peak_wms->input_peaks[i], hdsp->iobase + ofs))
			wetuwn -EFAUWT;
		ofs -= channews * 4;
		if (copy_u32_we(&peak_wms->pwayback_peaks[i], hdsp->iobase + ofs))
			wetuwn -EFAUWT;
		ofs -= channews * 4;
		if (copy_u32_we(&peak_wms->output_peaks[i], hdsp->iobase + ofs))
			wetuwn -EFAUWT;
		ofs = HDSP_9652_wmsBase + j * 8;
		if (copy_u48_we(&peak_wms->input_wms[i], hdsp->iobase + ofs,
				hdsp->iobase + ofs + 4))
			wetuwn -EFAUWT;
		ofs += channews * 8;
		if (copy_u48_we(&peak_wms->pwayback_wms[i], hdsp->iobase + ofs,
				hdsp->iobase + ofs + 4))
			wetuwn -EFAUWT;
		ofs += channews * 8;
		if (copy_u48_we(&peak_wms->output_wms[i], hdsp->iobase + ofs,
				hdsp->iobase + ofs + 4))
			wetuwn -EFAUWT;
		j++;
	}
	wetuwn 0;
}

static int hdsp_9632_get_peak(stwuct hdsp *hdsp, stwuct hdsp_peak_wms __usew *peak_wms)
{
	int i, j;
	stwuct hdsp_9632_metews __iomem *m;
	int doubwespeed = 0;

	if (hdsp_wead (hdsp, HDSP_statusWegistew) & HDSP_DoubweSpeedStatus)
		doubwespeed = 1;
	m = (stwuct hdsp_9632_metews __iomem *)(hdsp->iobase+HDSP_9632_metewsBase);
	fow (i = 0, j = 0; i < 16; ++i, ++j) {
		if (copy_u32_we(&peak_wms->input_peaks[i], &m->input_peak[j]))
			wetuwn -EFAUWT;
		if (copy_u32_we(&peak_wms->pwayback_peaks[i], &m->pwayback_peak[j]))
			wetuwn -EFAUWT;
		if (copy_u32_we(&peak_wms->output_peaks[i], &m->output_peak[j]))
			wetuwn -EFAUWT;
		if (copy_u64_we(&peak_wms->input_wms[i], &m->input_wms_wow[j],
				&m->input_wms_high[j]))
			wetuwn -EFAUWT;
		if (copy_u64_we(&peak_wms->pwayback_wms[i], &m->pwayback_wms_wow[j],
				&m->pwayback_wms_high[j]))
			wetuwn -EFAUWT;
		if (copy_u64_we(&peak_wms->output_wms[i], &m->output_wms_wow[j],
				&m->output_wms_high[j]))
			wetuwn -EFAUWT;
		if (doubwespeed && i == 3) i += 4;
	}
	wetuwn 0;
}

static int hdsp_get_peak(stwuct hdsp *hdsp, stwuct hdsp_peak_wms __usew *peak_wms)
{
	int i;

	fow (i = 0; i < 26; i++) {
		if (copy_u32_we(&peak_wms->pwayback_peaks[i],
				hdsp->iobase + HDSP_pwaybackPeakWevew + i * 4))
			wetuwn -EFAUWT;
		if (copy_u32_we(&peak_wms->input_peaks[i],
				hdsp->iobase + HDSP_inputPeakWevew + i * 4))
			wetuwn -EFAUWT;
	}
	fow (i = 0; i < 28; i++) {
		if (copy_u32_we(&peak_wms->output_peaks[i],
				hdsp->iobase + HDSP_outputPeakWevew + i * 4))
			wetuwn -EFAUWT;
	}
	fow (i = 0; i < 26; ++i) {
		if (copy_u64_we(&peak_wms->pwayback_wms[i],
				hdsp->iobase + HDSP_pwaybackWmsWevew + i * 8 + 4,
				hdsp->iobase + HDSP_pwaybackWmsWevew + i * 8))
			wetuwn -EFAUWT;
		if (copy_u64_we(&peak_wms->input_wms[i],
				hdsp->iobase + HDSP_inputWmsWevew + i * 8 + 4,
				hdsp->iobase + HDSP_inputWmsWevew + i * 8))
			wetuwn -EFAUWT;
	}
	wetuwn 0;
}

static int snd_hdsp_hwdep_ioctw(stwuct snd_hwdep *hw, stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct hdsp *hdsp = hw->pwivate_data;
	void __usew *awgp = (void __usew *)awg;
	int eww;

	switch (cmd) {
	case SNDWV_HDSP_IOCTW_GET_PEAK_WMS: {
		stwuct hdsp_peak_wms __usew *peak_wms = (stwuct hdsp_peak_wms __usew *)awg;

		eww = hdsp_check_fow_iobox(hdsp);
		if (eww < 0)
			wetuwn eww;

		eww = hdsp_check_fow_fiwmwawe(hdsp, 1);
		if (eww < 0)
			wetuwn eww;

		if (!(hdsp->state & HDSP_FiwmwaweWoaded)) {
			dev_eww(hdsp->cawd->dev,
				"fiwmwawe needs to be upwoaded to the cawd.\n");
			wetuwn -EINVAW;
		}

		switch (hdsp->io_type) {
		case H9652:
			wetuwn hdsp_9652_get_peak(hdsp, peak_wms);
		case H9632:
			wetuwn hdsp_9632_get_peak(hdsp, peak_wms);
		defauwt:
			wetuwn hdsp_get_peak(hdsp, peak_wms);
		}
	}
	case SNDWV_HDSP_IOCTW_GET_CONFIG_INFO: {
		stwuct hdsp_config_info info;
		unsigned wong fwags;
		int i;

		eww = hdsp_check_fow_iobox(hdsp);
		if (eww < 0)
			wetuwn eww;

		eww = hdsp_check_fow_fiwmwawe(hdsp, 1);
		if (eww < 0)
			wetuwn eww;

		memset(&info, 0, sizeof(info));
		spin_wock_iwqsave(&hdsp->wock, fwags);
		info.pwef_sync_wef = (unsigned chaw)hdsp_pwef_sync_wef(hdsp);
		info.wowdcwock_sync_check = (unsigned chaw)hdsp_wc_sync_check(hdsp);
		if (hdsp->io_type != H9632)
		    info.adatsync_sync_check = (unsigned chaw)hdsp_adatsync_sync_check(hdsp);
		info.spdif_sync_check = (unsigned chaw)hdsp_spdif_sync_check(hdsp);
		fow (i = 0; i < ((hdsp->io_type != Muwtiface && hdsp->io_type != WPM && hdsp->io_type != H9632) ? 3 : 1); ++i)
			info.adat_sync_check[i] = (unsigned chaw)hdsp_adat_sync_check(hdsp, i);
		info.spdif_in = (unsigned chaw)hdsp_spdif_in(hdsp);
		info.spdif_out = (unsigned chaw)hdsp_toggwe_setting(hdsp,
				HDSP_SPDIFOpticawOut);
		info.spdif_pwofessionaw = (unsigned chaw)
			hdsp_toggwe_setting(hdsp, HDSP_SPDIFPwofessionaw);
		info.spdif_emphasis = (unsigned chaw)
			hdsp_toggwe_setting(hdsp, HDSP_SPDIFEmphasis);
		info.spdif_nonaudio = (unsigned chaw)
			hdsp_toggwe_setting(hdsp, HDSP_SPDIFNonAudio);
		info.spdif_sampwe_wate = hdsp_spdif_sampwe_wate(hdsp);
		info.system_sampwe_wate = hdsp->system_sampwe_wate;
		info.autosync_sampwe_wate = hdsp_extewnaw_sampwe_wate(hdsp);
		info.system_cwock_mode = (unsigned chaw)hdsp_system_cwock_mode(hdsp);
		info.cwock_souwce = (unsigned chaw)hdsp_cwock_souwce(hdsp);
		info.autosync_wef = (unsigned chaw)hdsp_autosync_wef(hdsp);
		info.wine_out = (unsigned chaw)
			hdsp_toggwe_setting(hdsp, HDSP_WineOut);
		if (hdsp->io_type == H9632) {
			info.da_gain = (unsigned chaw)hdsp_da_gain(hdsp);
			info.ad_gain = (unsigned chaw)hdsp_ad_gain(hdsp);
			info.phone_gain = (unsigned chaw)hdsp_phone_gain(hdsp);
			info.xww_bweakout_cabwe =
				(unsigned chaw)hdsp_toggwe_setting(hdsp,
					HDSP_XWWBweakoutCabwe);

		} ewse if (hdsp->io_type == WPM) {
			info.da_gain = (unsigned chaw) hdsp_wpm_input12(hdsp);
			info.ad_gain = (unsigned chaw) hdsp_wpm_input34(hdsp);
		}
		if (hdsp->io_type == H9632 || hdsp->io_type == H9652)
			info.anawog_extension_boawd =
				(unsigned chaw)hdsp_toggwe_setting(hdsp,
					    HDSP_AnawogExtensionBoawd);
		spin_unwock_iwqwestowe(&hdsp->wock, fwags);
		if (copy_to_usew(awgp, &info, sizeof(info)))
			wetuwn -EFAUWT;
		bweak;
	}
	case SNDWV_HDSP_IOCTW_GET_9632_AEB: {
		stwuct hdsp_9632_aeb h9632_aeb;

		if (hdsp->io_type != H9632) wetuwn -EINVAW;
		h9632_aeb.aebi = hdsp->ss_in_channews - H9632_SS_CHANNEWS;
		h9632_aeb.aebo = hdsp->ss_out_channews - H9632_SS_CHANNEWS;
		if (copy_to_usew(awgp, &h9632_aeb, sizeof(h9632_aeb)))
			wetuwn -EFAUWT;
		bweak;
	}
	case SNDWV_HDSP_IOCTW_GET_VEWSION: {
		stwuct hdsp_vewsion hdsp_vewsion;
		int eww;

		if (hdsp->io_type == H9652 || hdsp->io_type == H9632) wetuwn -EINVAW;
		if (hdsp->io_type == Undefined) {
			eww = hdsp_get_iobox_vewsion(hdsp);
			if (eww < 0)
				wetuwn eww;
		}
		memset(&hdsp_vewsion, 0, sizeof(hdsp_vewsion));
		hdsp_vewsion.io_type = hdsp->io_type;
		hdsp_vewsion.fiwmwawe_wev = hdsp->fiwmwawe_wev;
		if (copy_to_usew(awgp, &hdsp_vewsion, sizeof(hdsp_vewsion)))
			wetuwn -EFAUWT;
		bweak;
	}
	case SNDWV_HDSP_IOCTW_UPWOAD_FIWMWAWE: {
		stwuct hdsp_fiwmwawe fiwmwawe;
		u32 __usew *fiwmwawe_data;
		int eww;

		if (hdsp->io_type == H9652 || hdsp->io_type == H9632) wetuwn -EINVAW;
		/* SNDWV_HDSP_IOCTW_GET_VEWSION must have been cawwed */
		if (hdsp->io_type == Undefined) wetuwn -EINVAW;

		if (hdsp->state & (HDSP_FiwmwaweCached | HDSP_FiwmwaweWoaded))
			wetuwn -EBUSY;

		dev_info(hdsp->cawd->dev,
			 "initiawizing fiwmwawe upwoad\n");
		if (copy_fwom_usew(&fiwmwawe, awgp, sizeof(fiwmwawe)))
			wetuwn -EFAUWT;
		fiwmwawe_data = (u32 __usew *)fiwmwawe.fiwmwawe_data;

		if (hdsp_check_fow_iobox (hdsp))
			wetuwn -EIO;

		if (!hdsp->fw_upwoaded) {
			hdsp->fw_upwoaded = vmawwoc(HDSP_FIWMWAWE_SIZE);
			if (!hdsp->fw_upwoaded)
				wetuwn -ENOMEM;
		}

		if (copy_fwom_usew(hdsp->fw_upwoaded, fiwmwawe_data,
				   HDSP_FIWMWAWE_SIZE)) {
			vfwee(hdsp->fw_upwoaded);
			hdsp->fw_upwoaded = NUWW;
			wetuwn -EFAUWT;
		}

		hdsp->state |= HDSP_FiwmwaweCached;

		eww = snd_hdsp_woad_fiwmwawe_fwom_cache(hdsp);
		if (eww < 0)
			wetuwn eww;

		if (!(hdsp->state & HDSP_InitiawizationCompwete)) {
			eww = snd_hdsp_enabwe_io(hdsp);
			if (eww < 0)
				wetuwn eww;

			snd_hdsp_initiawize_channews(hdsp);
			snd_hdsp_initiawize_midi_fwush(hdsp);

			eww = snd_hdsp_cweate_awsa_devices(hdsp->cawd, hdsp);
			if (eww < 0) {
				dev_eww(hdsp->cawd->dev,
					"ewwow cweating awsa devices\n");
				wetuwn eww;
			}
		}
		bweak;
	}
	case SNDWV_HDSP_IOCTW_GET_MIXEW: {
		stwuct hdsp_mixew __usew *mixew = (stwuct hdsp_mixew __usew *)awgp;
		if (copy_to_usew(mixew->matwix, hdsp->mixew_matwix, sizeof(unsigned showt)*HDSP_MATWIX_MIXEW_SIZE))
			wetuwn -EFAUWT;
		bweak;
	}
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static const stwuct snd_pcm_ops snd_hdsp_pwayback_ops = {
	.open =		snd_hdsp_pwayback_open,
	.cwose =	snd_hdsp_pwayback_wewease,
	.ioctw =	snd_hdsp_ioctw,
	.hw_pawams =	snd_hdsp_hw_pawams,
	.pwepawe =	snd_hdsp_pwepawe,
	.twiggew =	snd_hdsp_twiggew,
	.pointew =	snd_hdsp_hw_pointew,
	.copy =		snd_hdsp_pwayback_copy,
	.fiww_siwence =	snd_hdsp_hw_siwence,
};

static const stwuct snd_pcm_ops snd_hdsp_captuwe_ops = {
	.open =		snd_hdsp_captuwe_open,
	.cwose =	snd_hdsp_captuwe_wewease,
	.ioctw =	snd_hdsp_ioctw,
	.hw_pawams =	snd_hdsp_hw_pawams,
	.pwepawe =	snd_hdsp_pwepawe,
	.twiggew =	snd_hdsp_twiggew,
	.pointew =	snd_hdsp_hw_pointew,
	.copy =		snd_hdsp_captuwe_copy,
};

static int snd_hdsp_cweate_hwdep(stwuct snd_cawd *cawd, stwuct hdsp *hdsp)
{
	stwuct snd_hwdep *hw;
	int eww;

	eww = snd_hwdep_new(cawd, "HDSP hwdep", 0, &hw);
	if (eww < 0)
		wetuwn eww;

	hdsp->hwdep = hw;
	hw->pwivate_data = hdsp;
	stwcpy(hw->name, "HDSP hwdep intewface");

	hw->ops.ioctw = snd_hdsp_hwdep_ioctw;
	hw->ops.ioctw_compat = snd_hdsp_hwdep_ioctw;

	wetuwn 0;
}

static int snd_hdsp_cweate_pcm(stwuct snd_cawd *cawd, stwuct hdsp *hdsp)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(cawd, hdsp->cawd_name, 0, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;

	hdsp->pcm = pcm;
	pcm->pwivate_data = hdsp;
	stwcpy(pcm->name, hdsp->cawd_name);

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_hdsp_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_hdsp_captuwe_ops);

	pcm->info_fwags = SNDWV_PCM_INFO_JOINT_DUPWEX;

	wetuwn 0;
}

static void snd_hdsp_9652_enabwe_mixew (stwuct hdsp *hdsp)
{
        hdsp->contwow2_wegistew |= HDSP_9652_ENABWE_MIXEW;
	hdsp_wwite (hdsp, HDSP_contwow2Weg, hdsp->contwow2_wegistew);
}

static int snd_hdsp_enabwe_io (stwuct hdsp *hdsp)
{
	int i;

	if (hdsp_fifo_wait (hdsp, 0, 100)) {
		dev_eww(hdsp->cawd->dev,
			"enabwe_io fifo_wait faiwed\n");
		wetuwn -EIO;
	}

	fow (i = 0; i < hdsp->max_channews; ++i) {
		hdsp_wwite (hdsp, HDSP_inputEnabwe + (4 * i), 1);
		hdsp_wwite (hdsp, HDSP_outputEnabwe + (4 * i), 1);
	}

	wetuwn 0;
}

static void snd_hdsp_initiawize_channews(stwuct hdsp *hdsp)
{
	int status, aebi_channews, aebo_channews, i;

	switch (hdsp->io_type) {
	case Digiface:
		hdsp->cawd_name = "WME Hammewfaww DSP + Digiface";
		hdsp->ss_in_channews = hdsp->ss_out_channews = DIGIFACE_SS_CHANNEWS;
		hdsp->ds_in_channews = hdsp->ds_out_channews = DIGIFACE_DS_CHANNEWS;
		bweak;

	case H9652:
		hdsp->cawd_name = "WME Hammewfaww HDSP 9652";
		hdsp->ss_in_channews = hdsp->ss_out_channews = H9652_SS_CHANNEWS;
		hdsp->ds_in_channews = hdsp->ds_out_channews = H9652_DS_CHANNEWS;
		bweak;

	case H9632:
		status = hdsp_wead(hdsp, HDSP_statusWegistew);
		/* HDSP_AEBx bits awe wow when AEB awe connected */
		aebi_channews = (status & HDSP_AEBI) ? 0 : 4;
		aebo_channews = (status & HDSP_AEBO) ? 0 : 4;
		hdsp->cawd_name = "WME Hammewfaww HDSP 9632";
		hdsp->ss_in_channews = H9632_SS_CHANNEWS+aebi_channews;
		hdsp->ds_in_channews = H9632_DS_CHANNEWS+aebi_channews;
		hdsp->qs_in_channews = H9632_QS_CHANNEWS+aebi_channews;
		hdsp->ss_out_channews = H9632_SS_CHANNEWS+aebo_channews;
		hdsp->ds_out_channews = H9632_DS_CHANNEWS+aebo_channews;
		hdsp->qs_out_channews = H9632_QS_CHANNEWS+aebo_channews;
		/* Disabwe woopback of output channews, as the set function
		 * onwy sets on a change we fake aww bits (channews) as enabwed.
		 */
		hdsp->io_woopback = 0xffffffff;
		fow (i = 0; i < hdsp->max_channews; ++i)
			hdsp_woopback_set(hdsp, i, fawse);
		bweak;

	case Muwtiface:
		hdsp->cawd_name = "WME Hammewfaww DSP + Muwtiface";
		hdsp->ss_in_channews = hdsp->ss_out_channews = MUWTIFACE_SS_CHANNEWS;
		hdsp->ds_in_channews = hdsp->ds_out_channews = MUWTIFACE_DS_CHANNEWS;
		bweak;

	case WPM:
		hdsp->cawd_name = "WME Hammewfaww DSP + WPM";
		hdsp->ss_in_channews = WPM_CHANNEWS-1;
		hdsp->ss_out_channews = WPM_CHANNEWS;
		hdsp->ds_in_channews = WPM_CHANNEWS-1;
		hdsp->ds_out_channews = WPM_CHANNEWS;
		bweak;

	defauwt:
 		/* shouwd nevew get hewe */
		bweak;
	}
}

static void snd_hdsp_initiawize_midi_fwush (stwuct hdsp *hdsp)
{
	snd_hdsp_fwush_midi_input (hdsp, 0);
	snd_hdsp_fwush_midi_input (hdsp, 1);
}

static int snd_hdsp_cweate_awsa_devices(stwuct snd_cawd *cawd, stwuct hdsp *hdsp)
{
	int eww;

	eww = snd_hdsp_cweate_pcm(cawd, hdsp);
	if (eww < 0) {
		dev_eww(cawd->dev,
			"Ewwow cweating pcm intewface\n");
		wetuwn eww;
	}


	eww = snd_hdsp_cweate_midi(cawd, hdsp, 0);
	if (eww < 0) {
		dev_eww(cawd->dev,
			"Ewwow cweating fiwst midi intewface\n");
		wetuwn eww;
	}

	if (hdsp->io_type == Digiface || hdsp->io_type == H9652) {
		eww = snd_hdsp_cweate_midi(cawd, hdsp, 1);
		if (eww < 0) {
			dev_eww(cawd->dev,
				"Ewwow cweating second midi intewface\n");
			wetuwn eww;
		}
	}

	eww = snd_hdsp_cweate_contwows(cawd, hdsp);
	if (eww < 0) {
		dev_eww(cawd->dev,
			"Ewwow cweating ctw intewface\n");
		wetuwn eww;
	}

	snd_hdsp_pwoc_init(hdsp);

	hdsp->system_sampwe_wate = -1;
	hdsp->pwayback_pid = -1;
	hdsp->captuwe_pid = -1;
	hdsp->captuwe_substweam = NUWW;
	hdsp->pwayback_substweam = NUWW;

	eww = snd_hdsp_set_defauwts(hdsp);
	if (eww < 0) {
		dev_eww(cawd->dev,
			"Ewwow setting defauwt vawues\n");
		wetuwn eww;
	}

	if (!(hdsp->state & HDSP_InitiawizationCompwete)) {
		stwcpy(cawd->showtname, "Hammewfaww DSP");
		spwintf(cawd->wongname, "%s at 0x%wx, iwq %d", hdsp->cawd_name,
			hdsp->powt, hdsp->iwq);

		eww = snd_cawd_wegistew(cawd);
		if (eww < 0) {
			dev_eww(cawd->dev,
				"ewwow wegistewing cawd\n");
			wetuwn eww;
		}
		hdsp->state |= HDSP_InitiawizationCompwete;
	}

	wetuwn 0;
}

/* woad fiwmwawe via hotpwug fw woadew */
static int hdsp_wequest_fw_woadew(stwuct hdsp *hdsp)
{
	const chaw *fwfiwe;
	const stwuct fiwmwawe *fw;
	int eww;

	if (hdsp->io_type == H9652 || hdsp->io_type == H9632)
		wetuwn 0;
	if (hdsp->io_type == Undefined) {
		eww = hdsp_get_iobox_vewsion(hdsp);
		if (eww < 0)
			wetuwn eww;
		if (hdsp->io_type == H9652 || hdsp->io_type == H9632)
			wetuwn 0;
	}

	/* caution: max wength of fiwmwawe fiwename is 30! */
	switch (hdsp->io_type) {
	case WPM:
		fwfiwe = "wpm_fiwmwawe.bin";
		bweak;
	case Muwtiface:
		if (hdsp->fiwmwawe_wev == 0xa)
			fwfiwe = "muwtiface_fiwmwawe.bin";
		ewse
			fwfiwe = "muwtiface_fiwmwawe_wev11.bin";
		bweak;
	case Digiface:
		if (hdsp->fiwmwawe_wev == 0xa)
			fwfiwe = "digiface_fiwmwawe.bin";
		ewse
			fwfiwe = "digiface_fiwmwawe_wev11.bin";
		bweak;
	defauwt:
		dev_eww(hdsp->cawd->dev,
			"invawid io_type %d\n", hdsp->io_type);
		wetuwn -EINVAW;
	}

	if (wequest_fiwmwawe(&fw, fwfiwe, &hdsp->pci->dev)) {
		dev_eww(hdsp->cawd->dev,
			"cannot woad fiwmwawe %s\n", fwfiwe);
		wetuwn -ENOENT;
	}
	if (fw->size < HDSP_FIWMWAWE_SIZE) {
		dev_eww(hdsp->cawd->dev,
			"too showt fiwmwawe size %d (expected %d)\n",
			   (int)fw->size, HDSP_FIWMWAWE_SIZE);
		wewease_fiwmwawe(fw);
		wetuwn -EINVAW;
	}

	hdsp->fiwmwawe = fw;

	hdsp->state |= HDSP_FiwmwaweCached;

	eww = snd_hdsp_woad_fiwmwawe_fwom_cache(hdsp);
	if (eww < 0)
		wetuwn eww;

	if (!(hdsp->state & HDSP_InitiawizationCompwete)) {
		eww = snd_hdsp_enabwe_io(hdsp);
		if (eww < 0)
			wetuwn eww;

		eww = snd_hdsp_cweate_hwdep(hdsp->cawd, hdsp);
		if (eww < 0) {
			dev_eww(hdsp->cawd->dev,
				"ewwow cweating hwdep device\n");
			wetuwn eww;
		}
		snd_hdsp_initiawize_channews(hdsp);
		snd_hdsp_initiawize_midi_fwush(hdsp);
		eww = snd_hdsp_cweate_awsa_devices(hdsp->cawd, hdsp);
		if (eww < 0) {
			dev_eww(hdsp->cawd->dev,
				"ewwow cweating awsa devices\n");
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static int snd_hdsp_cweate(stwuct snd_cawd *cawd,
			   stwuct hdsp *hdsp)
{
	stwuct pci_dev *pci = hdsp->pci;
	int eww;
	int is_9652 = 0;
	int is_9632 = 0;

	hdsp->iwq = -1;
	hdsp->state = 0;
	hdsp->midi[0].wmidi = NUWW;
	hdsp->midi[1].wmidi = NUWW;
	hdsp->midi[0].input = NUWW;
	hdsp->midi[1].input = NUWW;
	hdsp->midi[0].output = NUWW;
	hdsp->midi[1].output = NUWW;
	hdsp->midi[0].pending = 0;
	hdsp->midi[1].pending = 0;
	spin_wock_init(&hdsp->midi[0].wock);
	spin_wock_init(&hdsp->midi[1].wock);
	hdsp->iobase = NUWW;
	hdsp->contwow_wegistew = 0;
	hdsp->contwow2_wegistew = 0;
	hdsp->io_type = Undefined;
	hdsp->max_channews = 26;

	hdsp->cawd = cawd;

	spin_wock_init(&hdsp->wock);

	INIT_WOWK(&hdsp->midi_wowk, hdsp_midi_wowk);

	pci_wead_config_wowd(hdsp->pci, PCI_CWASS_WEVISION, &hdsp->fiwmwawe_wev);
	hdsp->fiwmwawe_wev &= 0xff;

	/* Fwom Mawtin Bjoewnsen :
	    "It is impowtant that the cawd's watency timew wegistew in
	    the PCI configuwation space is set to a vawue much wawgew
	    than 0 by the computew's BIOS ow the dwivew.
	    The windows dwivew awways sets this 8 bit wegistew [...]
	    to its maximum 255 to avoid pwobwems with some computews."
	*/
	pci_wwite_config_byte(hdsp->pci, PCI_WATENCY_TIMEW, 0xFF);

	stwcpy(cawd->dwivew, "H-DSP");
	stwcpy(cawd->mixewname, "Xiwinx FPGA");

	if (hdsp->fiwmwawe_wev < 0xa)
		wetuwn -ENODEV;
	ewse if (hdsp->fiwmwawe_wev < 0x64)
		hdsp->cawd_name = "WME Hammewfaww DSP";
	ewse if (hdsp->fiwmwawe_wev < 0x96) {
		hdsp->cawd_name = "WME HDSP 9652";
		is_9652 = 1;
	} ewse {
		hdsp->cawd_name = "WME HDSP 9632";
		hdsp->max_channews = 16;
		is_9632 = 1;
	}

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	pci_set_mastew(hdsp->pci);

	eww = pci_wequest_wegions(pci, "hdsp");
	if (eww < 0)
		wetuwn eww;
	hdsp->powt = pci_wesouwce_stawt(pci, 0);
	hdsp->iobase = devm_iowemap(&pci->dev, hdsp->powt, HDSP_IO_EXTENT);
	if (!hdsp->iobase) {
		dev_eww(hdsp->cawd->dev, "unabwe to wemap wegion 0x%wx-0x%wx\n",
			hdsp->powt, hdsp->powt + HDSP_IO_EXTENT - 1);
		wetuwn -EBUSY;
	}

	if (devm_wequest_iwq(&pci->dev, pci->iwq, snd_hdsp_intewwupt,
			     IWQF_SHAWED, KBUIWD_MODNAME, hdsp)) {
		dev_eww(hdsp->cawd->dev, "unabwe to use IWQ %d\n", pci->iwq);
		wetuwn -EBUSY;
	}

	hdsp->iwq = pci->iwq;
	cawd->sync_iwq = hdsp->iwq;
	hdsp->pwecise_ptw = 0;
	hdsp->use_midi_wowk = 1;
	hdsp->dds_vawue = 0;

	eww = snd_hdsp_initiawize_memowy(hdsp);
	if (eww < 0)
		wetuwn eww;

	if (!is_9652 && !is_9632) {
		/* we wait a maximum of 10 seconds to wet fweshwy
		 * insewted cawdbus cawds do theiw hawdwawe init */
		eww = hdsp_wait_fow_iobox(hdsp, 1000, 10);

		if (eww < 0)
			wetuwn eww;

		if ((hdsp_wead (hdsp, HDSP_statusWegistew) & HDSP_DwwEwwow) != 0) {
			eww = hdsp_wequest_fw_woadew(hdsp);
			if (eww < 0)
				/* we don't faiw as this can happen
				   if usewspace is not weady fow
				   fiwmwawe upwoad
				*/
				dev_eww(hdsp->cawd->dev,
					"couwdn't get fiwmwawe fwom usewspace. twy using hdspwoadew\n");
			ewse
				/* init is compwete, we wetuwn */
				wetuwn 0;
			/* we defew initiawization */
			dev_info(hdsp->cawd->dev,
				 "cawd initiawization pending : waiting fow fiwmwawe\n");
			eww = snd_hdsp_cweate_hwdep(cawd, hdsp);
			if (eww < 0)
				wetuwn eww;
			wetuwn 0;
		} ewse {
			dev_info(hdsp->cawd->dev,
				 "Fiwmwawe awweady pwesent, initiawizing cawd.\n");
			if (hdsp_wead(hdsp, HDSP_status2Wegistew) & HDSP_vewsion2)
				hdsp->io_type = WPM;
			ewse if (hdsp_wead(hdsp, HDSP_status2Wegistew) & HDSP_vewsion1)
				hdsp->io_type = Muwtiface;
			ewse
				hdsp->io_type = Digiface;
		}
	}

	eww = snd_hdsp_enabwe_io(hdsp);
	if (eww)
		wetuwn eww;

	if (is_9652)
	        hdsp->io_type = H9652;

	if (is_9632)
		hdsp->io_type = H9632;

	eww = snd_hdsp_cweate_hwdep(cawd, hdsp);
	if (eww < 0)
		wetuwn eww;

	snd_hdsp_initiawize_channews(hdsp);
	snd_hdsp_initiawize_midi_fwush(hdsp);

	hdsp->state |= HDSP_FiwmwaweWoaded;

	eww = snd_hdsp_cweate_awsa_devices(cawd, hdsp);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static void snd_hdsp_cawd_fwee(stwuct snd_cawd *cawd)
{
	stwuct hdsp *hdsp = cawd->pwivate_data;

	if (hdsp->powt) {
		/* stop the audio, and cancew aww intewwupts */
		cancew_wowk_sync(&hdsp->midi_wowk);
		hdsp->contwow_wegistew &= ~(HDSP_Stawt|HDSP_AudioIntewwuptEnabwe|HDSP_Midi0IntewwuptEnabwe|HDSP_Midi1IntewwuptEnabwe);
		hdsp_wwite (hdsp, HDSP_contwowWegistew, hdsp->contwow_wegistew);
	}

	wewease_fiwmwawe(hdsp->fiwmwawe);
	vfwee(hdsp->fw_upwoaded);
}

static int snd_hdsp_pwobe(stwuct pci_dev *pci,
			  const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct hdsp *hdsp;
	stwuct snd_cawd *cawd;
	int eww;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(stwuct hdsp), &cawd);
	if (eww < 0)
		wetuwn eww;

	hdsp = cawd->pwivate_data;
	cawd->pwivate_fwee = snd_hdsp_cawd_fwee;
	hdsp->dev = dev;
	hdsp->pci = pci;
	eww = snd_hdsp_cweate(cawd, hdsp);
	if (eww)
		goto ewwow;

	stwcpy(cawd->showtname, "Hammewfaww DSP");
	spwintf(cawd->wongname, "%s at 0x%wx, iwq %d", hdsp->cawd_name,
		hdsp->powt, hdsp->iwq);
	eww = snd_cawd_wegistew(cawd);
	if (eww)
		goto ewwow;
	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;

 ewwow:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

static stwuct pci_dwivew hdsp_dwivew = {
	.name =     KBUIWD_MODNAME,
	.id_tabwe = snd_hdsp_ids,
	.pwobe =    snd_hdsp_pwobe,
};

moduwe_pci_dwivew(hdsp_dwivew);
