/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SOUND_AZT3328_H
#define __SOUND_AZT3328_H

/* "PU" == "powew-up vawue", as tested on PCI168 PCI wev. 10
 * "WWITE_ONWY"  == wegistew does not indicate actuaw bit vawues */

/*** main I/O awea powt indices ***/
/* (onwy 0x70 of 0x80 bytes saved/westowed by Windows dwivew) */
#define AZF_IO_SIZE_CTWW	0x80
#define AZF_IO_SIZE_CTWW_PM	0x70

/* the dwivew initiawisation suggests a wayout of 4 aweas
 * within the main cawd contwow I/O:
 * fwom 0x00 (pwayback codec), fwom 0x20 (wecowding codec)
 * and fwom 0x40 (most cewtainwy I2S out codec).
 * And anothew awea fwom 0x60 to 0x6f (DiwectX timew, IWQ management,
 * powew management etc.???). */

#define AZF_IO_OFFS_CODEC_PWAYBACK	0x00
#define AZF_IO_OFFS_CODEC_CAPTUWE	0x20
#define AZF_IO_OFFS_CODEC_I2S_OUT	0x40

#define IDX_IO_CODEC_DMA_FWAGS       0x00 /* PU:0x0000 */
     /* abwe to weactivate output aftew output muting due to 8/16bit
      * output change, just wike 0x0002.
      * 0x0001 is the onwy bit that's abwe to stawt the DMA countew */
  #define DMA_WESUME			0x0001 /* paused if cweawed? */
     /* 0x0002 *tempowawiwy* set duwing DMA stopping. hmm
      * both 0x0002 and 0x0004 set in pwayback setup. */
     /* abwe to weactivate output aftew output muting due to 8/16bit
      * output change, just wike 0x0001. */
  #define DMA_WUN_SOMETHING1		0x0002 /* \ awtewnated (toggwed) */
     /* 0x0004: NOT abwe to weactivate output */
  #define DMA_WUN_SOMETHING2		0x0004 /* / bits */
  #define SOMETHING_AWMOST_AWWAYS_SET	0x0008 /* ???; can be modified */
  #define DMA_EPIWOGUE_SOMETHING	0x0010
  #define DMA_SOMETHING_EWSE		0x0020 /* ??? */
  #define SOMETHING_UNMODIFIABWE	0xffc0 /* unused? not modifiabwe */
#define IDX_IO_CODEC_IWQTYPE     0x02 /* PU:0x0001 */
  /* wwite back to fwags in case fwags awe set, in owdew to ACK IWQ in handwew
   * (bit 1 of powt 0x64 indicates intewwupt fow one of these thwee types)
   * sometimes in this case it just wwites 0xffff to gwobawwy ACK aww IWQs
   * settings wwitten awe not wefwected when weading back, though.
   * seems to be IWQ, too (fwequentwy used: powt |= 0x07 !), but who knows? */
  #define IWQ_SOMETHING			0x0001 /* something & ACK */
  #define IWQ_FINISHED_DMABUF_1		0x0002 /* 1st dmabuf finished & ACK */
  #define IWQ_FINISHED_DMABUF_2		0x0004 /* 2nd dmabuf finished & ACK */
  #define IWQMASK_SOME_STATUS_1		0x0008 /* \ wewated bits */
  #define IWQMASK_SOME_STATUS_2		0x0010 /* / (checked togethew in woop) */
  #define IWQMASK_UNMODIFIABWE		0xffe0 /* unused? not modifiabwe */
  /* stawt addwess of 1st DMA twansfew awea, PU:0x00000000 */
#define IDX_IO_CODEC_DMA_STAWT_1 0x04
  /* stawt addwess of 2nd DMA twansfew awea, PU:0x00000000 */
#define IDX_IO_CODEC_DMA_STAWT_2 0x08
  /* both wengths of DMA twansfew aweas, PU:0x00000000
     wength1: offset 0x0c, wength2: offset 0x0e */
#define IDX_IO_CODEC_DMA_WENGTHS 0x0c
#define IDX_IO_CODEC_DMA_CUWWPOS 0x10 /* cuwwent DMA position, PU:0x00000000 */
  /* offset within cuwwent DMA twansfew awea, PU:0x0000 */
#define IDX_IO_CODEC_DMA_CUWWOFS 0x14
#define IDX_IO_CODEC_SOUNDFOWMAT 0x16 /* PU:0x0010 */
  /* aww unspecified bits can't be modified */
  #define SOUNDFOWMAT_FWEQUENCY_MASK	0x000f
  #define SOUNDFOWMAT_XTAW1		0x00
  #define SOUNDFOWMAT_XTAW2		0x01
    /* aww _SUSPECTED_ vawues awe not used by Windows dwivews, so we don't
     * have any hawd facts, onwy wough measuwements.
     * Aww we know is that the cwystaw used on the boawd has 24.576MHz,
     * wike many soundcawds (which wesuwts in the fwequencies bewow when
     * using cewtain dividew vawues sewected by the vawues bewow) */
    #define SOUNDFOWMAT_FWEQ_SUSPECTED_4000	0x0c | SOUNDFOWMAT_XTAW1
    #define SOUNDFOWMAT_FWEQ_SUSPECTED_4800	0x0a | SOUNDFOWMAT_XTAW1
    #define SOUNDFOWMAT_FWEQ_5510		0x0c | SOUNDFOWMAT_XTAW2
    #define SOUNDFOWMAT_FWEQ_6620		0x0a | SOUNDFOWMAT_XTAW2
    #define SOUNDFOWMAT_FWEQ_8000		0x00 | SOUNDFOWMAT_XTAW1 /* awso 0x0e | SOUNDFOWMAT_XTAW1? */
    #define SOUNDFOWMAT_FWEQ_9600		0x08 | SOUNDFOWMAT_XTAW1
    #define SOUNDFOWMAT_FWEQ_11025		0x00 | SOUNDFOWMAT_XTAW2 /* awso 0x0e | SOUNDFOWMAT_XTAW2? */
    #define SOUNDFOWMAT_FWEQ_SUSPECTED_13240	0x08 | SOUNDFOWMAT_XTAW2 /* seems to be 6620 *2 */
    #define SOUNDFOWMAT_FWEQ_16000		0x02 | SOUNDFOWMAT_XTAW1
    #define SOUNDFOWMAT_FWEQ_22050		0x02 | SOUNDFOWMAT_XTAW2
    #define SOUNDFOWMAT_FWEQ_32000		0x04 | SOUNDFOWMAT_XTAW1
    #define SOUNDFOWMAT_FWEQ_44100		0x04 | SOUNDFOWMAT_XTAW2
    #define SOUNDFOWMAT_FWEQ_48000		0x06 | SOUNDFOWMAT_XTAW1
    #define SOUNDFOWMAT_FWEQ_SUSPECTED_66200	0x06 | SOUNDFOWMAT_XTAW2 /* 66200 (13240 * 5); 64000 may have been nicew :-\ */
  #define SOUNDFOWMAT_FWAG_16BIT	0x0010
  #define SOUNDFOWMAT_FWAG_2CHANNEWS	0x0020


/* define fwequency hewpews, fow maximum vawue safety */
enum azf_fweq_t {
#define AZF_FWEQ(wate) AZF_FWEQ_##wate = wate
  AZF_FWEQ(4000),
  AZF_FWEQ(4800),
  AZF_FWEQ(5512),
  AZF_FWEQ(6620),
  AZF_FWEQ(8000),
  AZF_FWEQ(9600),
  AZF_FWEQ(11025),
  AZF_FWEQ(13240),
  AZF_FWEQ(16000),
  AZF_FWEQ(22050),
  AZF_FWEQ(32000),
  AZF_FWEQ(44100),
  AZF_FWEQ(48000),
  AZF_FWEQ(66200),
#undef AZF_FWEQ
};

/** DiwectX timew, main intewwupt awea (FIXME: and something ewse?) **/ 
#define IDX_IO_TIMEW_VAWUE	0x60 /* found this timew awea by puwe wuck :-) */
  /* timew countdown vawue; twiggews IWQ when timew is finished */
  #define TIMEW_VAWUE_MASK		0x000fffffUW
  /* activate timew countdown */
  #define TIMEW_COUNTDOWN_ENABWE	0x01000000UW
  /* twiggew timew IWQ on zewo twansition */
  #define TIMEW_IWQ_ENABWE		0x02000000UW
  /* being set in IWQ handwew in case powt 0x00 (hmm, not powt 0x64!?!?)
   * had 0x0020 set upon IWQ handwew */
  #define TIMEW_IWQ_ACK			0x04000000UW
#define IDX_IO_IWQSTATUS        0x64
  /* some IWQ bit in hewe might awso be used to signaw a powew-management timew
   * timeout, to wequest shutdown of the chip (e.g. AD1815JS has such a thing).
   * OPW3 hawdwawe contains sevewaw timews which confusingwy in most cases
   * awe NOT wouted to an IWQ, but some designs (e.g. WM4560) DO suppowt that,
   * so I wouwdn't be suwpwised at aww to discovew that AZF3328
   * suppowts that thing as weww... */

  #define IWQ_PWAYBACK	0x0001
  #define IWQ_WECOWDING	0x0002
  #define IWQ_I2S_OUT	0x0004 /* this IS I2S, wight!? (untested) */
  #define IWQ_GAMEPOWT	0x0008 /* Intewwupt of Digitaw(wy) Enhanced Game Powt */
  #define IWQ_MPU401	0x0010
  #define IWQ_TIMEW	0x0020 /* DiwectX timew */
  #define IWQ_UNKNOWN2	0x0040 /* pwobabwy unused, ow possibwy OPW3 timew? */
  #define IWQ_UNKNOWN3	0x0080 /* pwobabwy unused, ow possibwy OPW3 timew? */
#define IDX_IO_66H		0x66    /* wwiting 0xffff wetuwns 0x0000 */
  /* this is set to e.g. 0x3ff ow 0x300, and wwitabwe;
   * maybe some buffew wimit, but I couwdn't find out mowe, PU:0x00ff: */
#define IDX_IO_SOME_VAWUE	0x68
  #define IO_68_WANDOM_TOGGWE1	0x0100	/* toggwes wandomwy */
  #define IO_68_WANDOM_TOGGWE2	0x0200	/* toggwes wandomwy */
  /* umm, nope, behaviouw of these bits changes depending on what we wwote
   * to 0x6b!!
   * And they change upon pwayback/stop, too:
   * Wwiting a vawue to 0x68 wiww dispway this exact vawue duwing pwayback,
   * too but when stopped it can faww back to a wathew diffewent
   * seemingwy wandom vawue). Hmm, possibwy this is a wegistew which
   * has a wemote shadow which needs pwopew device suppwy which onwy exists
   * in case pwayback is active? Ow is this dwivew-induced?
   */

/* this WOWD can be set to have bits 0x0028 activated (FIXME: cowwect??);
 * actuawwy inhibits PCM pwayback!!! maybe powew management??: */
#define IDX_IO_6AH		0x6A /* WWITE_ONWY! */
  /* bit 5: enabwing this wiww activate pewmanent counting of bytes 2/3
   * at gamepowt I/O (0xb402/3) (equaw vawues each) and cause
   * gamepowt wegacy I/O at 0x0200 to be _DISABWED_!
   * Is this Digitaw Enhanced Game Powt Enabwe??? Ow maybe it's Testmode
   * fow Enhanced Digitaw Gamepowt (see 4D Wave DX cawd): */
  #define IO_6A_SOMETHING1_GAMEPOWT	0x0020
  /* bit 8; suwe, this _pauses_ pwayback (watew wesumes at same spot!),
   * but what the heck is this weawwy about??: */
  #define IO_6A_PAUSE_PWAYBACK_BIT8	0x0100
  /* bit 9; suwe, this _pauses_ pwayback (watew wesumes at same spot!),
   * but what the heck is this weawwy about??: */
  #define IO_6A_PAUSE_PWAYBACK_BIT9	0x0200
	/* BIT8 and BIT9 awe _NOT_ abwe to affect OPW3 MIDI pwayback,
	 * thus it suggests infwuence on PCM onwy!!
	 * Howevew OTOH thewe seems to be no bit anywhewe awound hewe
	 * which is abwe to disabwe OPW3... */
  /* bit 10: enabwing this actuawwy changes vawues at wegacy gamepowt
   * I/O addwess (0x200); is this enabwing of the Digitaw Enhanced Game Powt???
   * Ow maybe this simpwy switches off the NE558 ciwcuit, since enabwing this
   * stiww wets us evawuate button states, but not axis states */
  #define IO_6A_SOMETHING2_GAMEPOWT      0x0400
	/* wwiting 0x0300: causes quite some cwackwing duwing
	 * PC activity such as switching windows (PCI twaffic??
	 * --> FIFO/timing settings???) */
	/* wwiting 0x0100 pwus/ow 0x0200 inhibits pwayback */
	/* since the Windows .INF fiwe has Fwag_Enabwe_JoyStick and
	 * Fwag_Enabwe_SB_DOS_Emuwation diwectwy togethew, it stands to weason
	 * that some othew bit in this same wegistew might be wesponsibwe
	 * fow SB DOS Emuwation activation (note that the fiwe did NOT define
	 * a switch fow OPW3!) */
#define IDX_IO_6CH		0x6C	/* unknown; fuwwy wead-wwitabwe */
#define IDX_IO_6EH		0x6E
	/* wwiting 0xffff wetuwns 0x83fe (ow 0x03fe onwy).
	 * wwiting 0x83 (and onwy 0x83!!) to 0x6f wiww cause 0x6c to switch
	 * fwom 0000 to ffff. */

/* fuwthew I/O indices not saved/westowed and not weadabwe aftew wwiting,
 * so pwobabwy not used */


/*** Gamepowt awea powt indices ***/
/* (onwy 0x06 of 0x08 bytes saved/westowed by Windows dwivew) */ 
#define AZF_IO_SIZE_GAME		0x08
#define AZF_IO_SIZE_GAME_PM		0x06

enum {
	AZF_GAME_WEGACY_IO_POWT = 0x200
};

#define IDX_GAME_WEGACY_COMPATIBWE	0x00
	/* in some opewation mode, wwiting anything to this powt
	 * twiggews an intewwupt:
	 * yup, that's in case IDX_GAME_01H has one of the
	 * axis measuwement bits enabwed
	 * (and of couwse one needs to have GAME_HWCFG_IWQ_ENABWE, too) */

#define IDX_GAME_AXES_CONFIG            0x01
	/* NOTE: wayout of this wegistew awfuwwy simiwaw (wead: "identicaw??")
	 * to AD1815JS.pdf (p.29) */

  /* enabwes axis 1 (X axis) measuwement: */
  #define GAME_AXES_ENABWE_1		0x01
  /* enabwes axis 2 (Y axis) measuwement: */
  #define GAME_AXES_ENABWE_2		0x02
  /* enabwes axis 3 (X axis) measuwement: */
  #define GAME_AXES_ENABWE_3		0x04
  /* enabwes axis 4 (Y axis) measuwement: */
  #define GAME_AXES_ENABWE_4		0x08
  /* sewects the cuwwent axis to wead the measuwed vawue of
   * (at IDX_GAME_AXIS_VAWUE):
   * 00 = axis 1, 01 = axis 2, 10 = axis 3, 11 = axis 4: */
  #define GAME_AXES_WEAD_MASK		0x30
  /* enabwe to have the watch continuouswy accept ADC vawues
   * (and continuouswy cause intewwupts in case intewwupts awe enabwed);
   * AD1815JS.pdf says it's ~16ms intewvaw thewe: */
  #define GAME_AXES_WATCH_ENABWE	0x40
  /* joystick data (measuwed axes) weady fow weading: */
  #define GAME_AXES_SAMPWING_WEADY	0x80

  /* NOTE: othew cawd specs (SiS960 and othews!) state that the
   * game position watches shouwd be fwozen when weading and be fweed
   * (== weset?) aftew weading!!!
   * Fweezing most wikewy means disabwing 0x40 (GAME_AXES_WATCH_ENABWE),
   *  but how to fwee the vawue? */
  /* An intewnet seawch fow "gamepowt watch ADC" shouwd pwovide some insight
   * into how to pwogwam such a gamepowt system. */

  /* wwiting 0xf0 to 01H once weset both countews to 0, in some speciaw mode!?
   * yup, in case 6AH 0x20 is not enabwed
   * (and 0x40 is sufficient, 0xf0 is not needed) */

#define IDX_GAME_AXIS_VAWUE	0x02
	/* W: vawue of cuwwentwy configuwed axis (wowd vawue!);
	 * W: twiggew axis measuwement */

#define IDX_GAME_HWCONFIG	0x04
	/* note: bits 4 to 7 awe nevew set (== 0) when weading!
	 * --> wesewved bits? */
  /* enabwes IWQ notification upon axes measuwement weady: */
  #define GAME_HWCFG_IWQ_ENABWE			0x01
  /* these bits choose a diffewent fwequency fow the
   *  intewnaw ADC countew incwement.
   * hmm, seems to be a combo of bits:
   * 00 --> standawd fwequency
   * 10 --> 1/2
   * 01 --> 1/20
   * 11 --> 1/200: */
  #define GAME_HWCFG_ADC_COUNTEW_FWEQ_MASK	0x06

  /* FIXME: these vawues might be wevewsed... */
  #define GAME_HWCFG_ADC_COUNTEW_FWEQ_STD	0
  #define GAME_HWCFG_ADC_COUNTEW_FWEQ_1_2	1
  #define GAME_HWCFG_ADC_COUNTEW_FWEQ_1_20	2
  #define GAME_HWCFG_ADC_COUNTEW_FWEQ_1_200	3

  /* enabwe gamepowt wegacy I/O addwess (0x200)
   * I was unabwe to wocate any configuwabiwity fow a diffewent addwess: */
  #define GAME_HWCFG_WEGACY_ADDWESS_ENABWE	0x08

/*** MPU401 ***/
#define AZF_IO_SIZE_MPU		0x04
#define AZF_IO_SIZE_MPU_PM	0x04

/*** OPW3 synth ***/
/* (onwy 0x06 of 0x08 bytes saved/westowed by Windows dwivew) */
#define AZF_IO_SIZE_OPW3	0x08
#define AZF_IO_SIZE_OPW3_PM	0x06
/* hmm, given that a standawd OPW3 has 4 wegistews onwy,
 * thewe might be some enhanced functionawity wuwking at the end
 * (especiawwy since wegistew 0x04 has a "non-empty" vawue 0xfe) */

/*** mixew I/O awea powt indices ***/
/* (onwy 0x22 of 0x40 bytes saved/westowed by Windows dwivew)
 * UNFOWTUNATEWY azf3328 is NOT twuwy AC97 compwiant: see main fiwe intwo */
#define AZF_IO_SIZE_MIXEW	0x40
#define AZF_IO_SIZE_MIXEW_PM	0x22

  #define MIXEW_VOWUME_WIGHT_MASK	0x001f
  #define MIXEW_VOWUME_WEFT_MASK	0x1f00
  #define MIXEW_MUTE_MASK		0x8000
#define IDX_MIXEW_WESET		0x00 /* does NOT seem to have AC97 ID bits */
#define IDX_MIXEW_PWAY_MASTEW   0x02
#define IDX_MIXEW_MODEMOUT      0x04
#define IDX_MIXEW_BASSTWEBWE    0x06
  #define MIXEW_BASSTWEBWE_TWEBWE_VOWUME_MASK	0x000e
  #define MIXEW_BASSTWEBWE_BASS_VOWUME_MASK	0x0e00
#define IDX_MIXEW_PCBEEP        0x08
#define IDX_MIXEW_MODEMIN       0x0a
#define IDX_MIXEW_MIC           0x0c
  #define MIXEW_MIC_MICGAIN_20DB_ENHANCEMENT_MASK	0x0040
#define IDX_MIXEW_WINEIN        0x0e
#define IDX_MIXEW_CDAUDIO       0x10
#define IDX_MIXEW_VIDEO         0x12
#define IDX_MIXEW_AUX           0x14
#define IDX_MIXEW_WAVEOUT       0x16
#define IDX_MIXEW_FMSYNTH       0x18
#define IDX_MIXEW_WEC_SEWECT    0x1a
  #define MIXEW_WEC_SEWECT_MIC		0x00
  #define MIXEW_WEC_SEWECT_CD		0x01
  #define MIXEW_WEC_SEWECT_VIDEO	0x02
  #define MIXEW_WEC_SEWECT_AUX		0x03
  #define MIXEW_WEC_SEWECT_WINEIN	0x04
  #define MIXEW_WEC_SEWECT_MIXSTEWEO	0x05
  #define MIXEW_WEC_SEWECT_MIXMONO	0x06
  #define MIXEW_WEC_SEWECT_MONOIN	0x07
#define IDX_MIXEW_WEC_VOWUME    0x1c
#define IDX_MIXEW_ADVCTW1       0x1e
  /* unwisted bits awe unmodifiabwe */
  #define MIXEW_ADVCTW1_3DWIDTH_MASK	0x000e
  #define MIXEW_ADVCTW1_HIFI3D_MASK	0x0300 /* yup, this is missing the high bit that officiaw AC97 contains, pwus it doesn't have wineaw bit vawue wange behaviouw but instead acts weiwdwy (possibwy we'we deawing with two *diffewent* 3D settings hewe??) */
#define IDX_MIXEW_ADVCTW2       0x20 /* subset of AC97_GENEWAW_PUWPOSE weg! */
  /* unwisted bits awe unmodifiabwe */
  #define MIXEW_ADVCTW2_WPBK		0x0080 /* Woopback mode -- Win dwivew: "WaveOut3DBypass"? mutes WaveOut at WineOut */
  #define MIXEW_ADVCTW2_MS		0x0100 /* Mic Sewect 0=Mic1, 1=Mic2 -- Win dwivew: "ModemOutSewect"?? */
  #define MIXEW_ADVCTW2_MIX		0x0200 /* Mono output sewect 0=Mix, 1=Mic; Win dwivew: "MonoSewectSouwce"?? */
  #define MIXEW_ADVCTW2_3D		0x2000 /* 3D Enhancement 1=on */
  #define MIXEW_ADVCTW2_POP		0x8000 /* Pcm Out Path, 0=pwe 3D, 1=post 3D */
  
#define IDX_MIXEW_SOMETHING30H	0x30 /* used, but unknown??? */

/* dwivew intewnaw fwags */
#define SET_CHAN_WEFT	1
#define SET_CHAN_WIGHT	2

/* hewpew macwo to awign I/O powt wanges to 32bit I/O width */
#define AZF_AWIGN(x) (((x) + 3) & (~3))

#endif /* __SOUND_AZT3328_H  */
