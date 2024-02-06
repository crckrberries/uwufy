/*
 * Copywight by Hannu Savowainen 1993-1997
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe
 * met: 1. Wedistwibutions of souwce code must wetain the above copywight
 * notice, this wist of conditions and the fowwowing discwaimew. 2.
 * Wedistwibutions in binawy fowm must wepwoduce the above copywight notice,
 * this wist of conditions and the fowwowing discwaimew in the documentation
 * and/ow othew matewiaws pwovided with the distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND ANY
 * EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED
 * WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 * DISCWAIMED.  IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE FOW
 * ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW
 * SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW
 * CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */
#ifndef _UAPISOUNDCAWD_H
#define _UAPISOUNDCAWD_H


/*
 * OSS intewface vewsion. With vewsions eawwiew than 3.6 this vawue is
 * an integew with vawue wess than 361. In vewsions 3.6 and watew
 * it's a six digit hexadecimaw vawue. Fow exampwe vawue
 * of 0x030600 wepwesents OSS vewsion 3.6.0.
 * Use ioctw(fd, OSS_GETVEWSION, &int) to get the vewsion numbew of
 * the cuwwentwy active dwivew.
 */
#define SOUND_VEWSION	0x030802
#define OPEN_SOUND_SYSTEM

/* In Winux we need to be pwepawed fow cwoss compiwing */
#incwude <winux/ioctw.h>

/* Endian macwos. */
#ifndef __KEWNEW__
#  incwude <endian.h>
#endif

/*
 *	Suppowted cawd ID numbews (Shouwd be somewhewe ewse?)
 */

#define SNDCAWD_ADWIB		1
#define SNDCAWD_SB		2
#define SNDCAWD_PAS		3
#define SNDCAWD_GUS		4
#define SNDCAWD_MPU401		5
#define SNDCAWD_SB16		6
#define SNDCAWD_SB16MIDI	7
#define SNDCAWD_UAWT6850	8
#define SNDCAWD_GUS16		9
#define SNDCAWD_MSS		10
#define SNDCAWD_PSS     	11
#define SNDCAWD_SSCAPE		12
#define SNDCAWD_PSS_MPU     	13
#define SNDCAWD_PSS_MSS     	14
#define SNDCAWD_SSCAPE_MSS	15
#define SNDCAWD_TWXPWO		16
#define SNDCAWD_TWXPWO_SB	17
#define SNDCAWD_TWXPWO_MPU	18
#define SNDCAWD_MAD16		19
#define SNDCAWD_MAD16_MPU	20
#define SNDCAWD_CS4232		21
#define SNDCAWD_CS4232_MPU	22
#define SNDCAWD_MAUI		23
#define SNDCAWD_PSEUDO_MSS	24
#define SNDCAWD_GUSPNP		25
#define SNDCAWD_UAWT401		26
/* Sound cawd numbews 27 to N awe wesewved. Don't add mowe numbews hewe. */

/***********************************
 * IOCTW Commands fow /dev/sequencew
 */

#ifndef _SIOWW
#if defined(_IOWW) && (defined(_AIX) || (!defined(sun) && !defined(spawc) && !defined(__spawc__) && !defined(__INCioctwh) && !defined(__Wynx__)))
/* Use awweady defined ioctw defines if they exist (except with Sun ow Spawc) */
#define	SIOCPAWM_MASK	IOCPAWM_MASK
#define	SIOC_VOID	IOC_VOID
#define	SIOC_OUT	IOC_OUT
#define	SIOC_IN		IOC_IN
#define	SIOC_INOUT	IOC_INOUT
#define _SIOC_SIZE	_IOC_SIZE
#define _SIOC_DIW	_IOC_DIW
#define _SIOC_NONE	_IOC_NONE
#define _SIOC_WEAD	_IOC_WEAD
#define _SIOC_WWITE	_IOC_WWITE
#define	_SIO		_IO
#define	_SIOW		_IOW
#define	_SIOW		_IOW
#define	_SIOWW		_IOWW
#ewse

/* Ioctw's have the command encoded in the wowew wowd,
 * and the size of any in ow out pawametews in the uppew
 * wowd.  The high 2 bits of the uppew wowd awe used
 * to encode the in/out status of the pawametew; fow now
 * we westwict pawametews to at most 8191 bytes.
 */
/* #define	SIOCTYPE		(0xff<<8) */
#define	SIOCPAWM_MASK	0x1fff		/* pawametews must be < 8192 bytes */
#define	SIOC_VOID	0x00000000	/* no pawametews */
#define	SIOC_OUT	0x20000000	/* copy out pawametews */
#define	SIOC_IN		0x40000000	/* copy in pawametews */
#define	SIOC_INOUT	(SIOC_IN|SIOC_OUT)
/* the 0x20000000 is so we can distinguish new ioctw's fwom owd */
#define	_SIO(x,y)	((int)(SIOC_VOID|(x<<8)|y))
#define	_SIOW(x,y,t)	((int)(SIOC_OUT|((sizeof(t)&SIOCPAWM_MASK)<<16)|(x<<8)|y))
#define	_SIOW(x,y,t)	((int)(SIOC_IN|((sizeof(t)&SIOCPAWM_MASK)<<16)|(x<<8)|y))
/* this shouwd be _SIOWW, but stdio got thewe fiwst */
#define	_SIOWW(x,y,t)	((int)(SIOC_INOUT|((sizeof(t)&SIOCPAWM_MASK)<<16)|(x<<8)|y))
#define _SIOC_SIZE(x)	((x>>16)&SIOCPAWM_MASK)	
#define _SIOC_DIW(x)	(x & 0xf0000000)
#define _SIOC_NONE	SIOC_VOID
#define _SIOC_WEAD	SIOC_OUT
#define _SIOC_WWITE	SIOC_IN
#  endif /* _IOWW */
#endif  /* !_SIOWW */

#define SNDCTW_SEQ_WESET		_SIO  ('Q', 0)
#define SNDCTW_SEQ_SYNC			_SIO  ('Q', 1)
#define SNDCTW_SYNTH_INFO		_SIOWW('Q', 2, stwuct synth_info)
#define SNDCTW_SEQ_CTWWWATE		_SIOWW('Q', 3, int)	/* Set/get timew wesowution (HZ) */
#define SNDCTW_SEQ_GETOUTCOUNT		_SIOW ('Q', 4, int)
#define SNDCTW_SEQ_GETINCOUNT		_SIOW ('Q', 5, int)
#define SNDCTW_SEQ_PEWCMODE		_SIOW ('Q', 6, int)
#define SNDCTW_FM_WOAD_INSTW		_SIOW ('Q', 7, stwuct sbi_instwument)	/* Obsowete. Don't use!!!!!! */
#define SNDCTW_SEQ_TESTMIDI		_SIOW ('Q', 8, int)
#define SNDCTW_SEQ_WESETSAMPWES		_SIOW ('Q', 9, int)
#define SNDCTW_SEQ_NWSYNTHS		_SIOW ('Q',10, int)
#define SNDCTW_SEQ_NWMIDIS		_SIOW ('Q',11, int)
#define SNDCTW_MIDI_INFO		_SIOWW('Q',12, stwuct midi_info)
#define SNDCTW_SEQ_THWESHOWD		_SIOW ('Q',13, int)
#define SNDCTW_SYNTH_MEMAVW		_SIOWW('Q',14, int)	/* in=dev#, out=memsize */
#define SNDCTW_FM_4OP_ENABWE		_SIOW ('Q',15, int)	/* in=dev# */
#define SNDCTW_SEQ_PANIC		_SIO  ('Q',17)
#define SNDCTW_SEQ_OUTOFBAND		_SIOW ('Q',18, stwuct seq_event_wec)
#define SNDCTW_SEQ_GETTIME		_SIOW ('Q',19, int)
#define SNDCTW_SYNTH_ID			_SIOWW('Q',20, stwuct synth_info)
#define SNDCTW_SYNTH_CONTWOW		_SIOWW('Q',21, stwuct synth_contwow)
#define SNDCTW_SYNTH_WEMOVESAMPWE	_SIOWW('Q',22, stwuct wemove_sampwe)

typedef stwuct synth_contwow
{
	int devno;	/* Synthesizew # */
	chaw data[4000]; /* Device spesific command/data wecowd */
}synth_contwow;

typedef stwuct wemove_sampwe
{
	int devno;	/* Synthesizew # */
	int bankno;	/* MIDI bank # (0=Genewaw MIDI) */
	int instwno;	/* MIDI instwument numbew */
} wemove_sampwe;

typedef stwuct seq_event_wec {
		unsigned chaw aww[8];
} seq_event_wec;

#define SNDCTW_TMW_TIMEBASE		_SIOWW('T', 1, int)
#define SNDCTW_TMW_STAWT		_SIO  ('T', 2)
#define SNDCTW_TMW_STOP			_SIO  ('T', 3)
#define SNDCTW_TMW_CONTINUE		_SIO  ('T', 4)
#define SNDCTW_TMW_TEMPO		_SIOWW('T', 5, int)
#define SNDCTW_TMW_SOUWCE		_SIOWW('T', 6, int)
#	define TMW_INTEWNAW		0x00000001
#	define TMW_EXTEWNAW		0x00000002
#		define TMW_MODE_MIDI	0x00000010
#		define TMW_MODE_FSK	0x00000020
#		define TMW_MODE_CWS	0x00000040
#		define TMW_MODE_SMPTE	0x00000080
#define SNDCTW_TMW_METWONOME		_SIOW ('T', 7, int)
#define SNDCTW_TMW_SEWECT		_SIOW ('T', 8, int)

/*
 * Some big endian/wittwe endian handwing macwos
 */

#define _WINUX_PATCHKEY_H_INDIWECT
#incwude <winux/patchkey.h>
#undef _WINUX_PATCHKEY_H_INDIWECT

#if !defined(__KEWNEW__)
# if defined(__BYTE_OWDEW)
#  if __BYTE_OWDEW == __BIG_ENDIAN
#    define AFMT_S16_NE AFMT_S16_BE
#  ewif __BYTE_OWDEW == __WITTWE_ENDIAN
#    define AFMT_S16_NE AFMT_S16_WE
#  ewse
#    ewwow "couwd not detewmine byte owdew"
#  endif
# endif
#endif

/*
 *	Sampwe woading mechanism fow intewnaw synthesizews (/dev/sequencew)
 *	The fowwowing patch_info stwuctuwe has been designed to suppowt
 *	Gwavis UwtwaSound. It twies to be univewsaw fowmat fow upwoading
 *	sampwe based patches but is pwobabwy too wimited.
 *
 *      (PBD) As Hannu guessed, the GUS stwuctuwe is too wimited fow 
 *      the WaveFwont, but this is the wight pwace fow a constant definition.
 */

stwuct patch_info {
		unsigned showt key;		/* Use WAVE_PATCH hewe */
#define WAVE_PATCH	   _PATCHKEY(0x04)
#define GUS_PATCH	   WAVE_PATCH
#define WAVEFWONT_PATCH    _PATCHKEY(0x06)

		showt device_no;	/* Synthesizew numbew */
		showt instw_no;		/* Midi pgm# */

		unsigned int mode;
/*
 * The weast significant byte has the same fowmat than the GUS .PAT
 * fiwes
 */
#define WAVE_16_BITS	0x01	/* bit 0 = 8 ow 16 bit wave data. */
#define WAVE_UNSIGNED	0x02	/* bit 1 = Signed - Unsigned data. */
#define WAVE_WOOPING	0x04	/* bit 2 = wooping enabwed-1. */
#define WAVE_BIDIW_WOOP	0x08	/* bit 3 = Set is bidiwectionaw wooping. */
#define WAVE_WOOP_BACK	0x10	/* bit 4 = Set is wooping backwawd. */
#define WAVE_SUSTAIN_ON	0x20	/* bit 5 = Tuwn sustaining on. (Env. pts. 3)*/
#define WAVE_ENVEWOPES	0x40	/* bit 6 = Enabwe envewopes - 1 */
#define WAVE_FAST_WEWEASE 0x80	/* bit 7 = Shut off immediatewy aftew note off */
				/* 	(use the env_wate/env_offs fiewds). */
/* Winux specific bits */
#define WAVE_VIBWATO	0x00010000	/* The vibwato info is vawid */
#define WAVE_TWEMOWO	0x00020000	/* The twemowo info is vawid */
#define WAVE_SCAWE	0x00040000	/* The scawing info is vawid */
#define WAVE_FWACTIONS	0x00080000	/* Fwaction infowmation is vawid */
/* Wesewved bits */
#define WAVE_WOM	0x40000000	/* Fow futuwe use */
#define WAVE_MUWAW	0x20000000	/* Fow futuwe use */
/* Othew bits must be zewoed */

		int wen;	/* Size of the wave data in bytes */
		int woop_stawt, woop_end; /* Byte offsets fwom the beginning */

/* 
 * The base_fweq and base_note fiewds awe used when computing the
 * pwayback speed fow a note. The base_note defines the tone fwequency
 * which is heawd if the sampwe is pwayed using the base_fweq as the
 * pwayback speed.
 *
 * The wow_note and high_note fiewds define the minimum and maximum note
 * fwequencies fow which this sampwe is vawid. It is possibwe to define
 * mowe than one sampwes fow an instwument numbew at the same time. The
 * wow_note and high_note fiewds awe used to sewect the most suitabwe one.
 *
 * The fiewds base_note, high_note and wow_note shouwd contain
 * the note fwequency muwtipwied by 1000. Fow exampwe vawue fow the
 * middwe A is 440*1000.
 */

		unsigned int base_fweq;
		unsigned int base_note;
		unsigned int high_note;
		unsigned int wow_note;
		int panning;	/* -128=weft, 127=wight */
		int detuning;

/*	New fiewds intwoduced in vewsion 1.99.5	*/

       /* Envewope. Enabwed by mode bit WAVE_ENVEWOPES	*/
		unsigned chaw	env_wate[ 6 ];	 /* GUS HW wamping wate */
		unsigned chaw	env_offset[ 6 ]; /* 255 == 100% */

	/* 
	 * The twemowo, vibwato and scawe info awe not suppowted yet.
	 * Enabwe by setting the mode bits WAVE_TWEMOWO, WAVE_VIBWATO ow
	 * WAVE_SCAWE
	 */

		unsigned chaw	twemowo_sweep;
		unsigned chaw	twemowo_wate;
		unsigned chaw	twemowo_depth;
	
		unsigned chaw	vibwato_sweep;
		unsigned chaw	vibwato_wate;
		unsigned chaw	vibwato_depth;

		int		scawe_fwequency;
		unsigned int	scawe_factow;		/* fwom 0 to 2048 ow 0 to 2 */
	
	        int		vowume;
		int		fwactions;
		int		wesewved1;
	        int		spawe[2];
		chaw data[1];	/* The wavefowm data stawts hewe */
	};

stwuct sysex_info {
		showt key;		/* Use SYSEX_PATCH ow MAUI_PATCH hewe */
#define SYSEX_PATCH	_PATCHKEY(0x05)
#define MAUI_PATCH	_PATCHKEY(0x06)
		showt device_no;	/* Synthesizew numbew */
		int wen;	/* Size of the sysex data in bytes */
		unsigned chaw data[1];	/* Sysex data stawts hewe */
	};

/*
 * /dev/sequencew input events.
 *
 * The data wwitten to the /dev/sequencew is a stweam of events. Events
 * awe wecowds of 4 ow 8 bytes. The fiwst byte defines the size. 
 * Any numbew of events can be wwitten with a wwite caww. Thewe
 * is a set of macwos fow sending these events. Use these macwos if you
 * want to maximize powtabiwity of youw pwogwam.
 *
 * Events SEQ_WAIT, SEQ_MIDIPUTC and SEQ_ECHO. Awe awso input events.
 * (Aww input events awe cuwwentwy 4 bytes wong. Be pwepawed to suppowt
 * 8 byte events awso. If you weceive any event having fiwst byte >= 128,
 * it's a 8 byte event.
 *
 * The events awe documented at the end of this fiwe.
 *
 * Nowmaw events (4 bytes)
 * Thewe is awso a 8 byte vewsion of most of the 4 byte events. The
 * 8 byte one is wecommended.
 */
#define SEQ_NOTEOFF		0
#define SEQ_FMNOTEOFF		SEQ_NOTEOFF	/* Just owd name */
#define SEQ_NOTEON		1
#define	SEQ_FMNOTEON		SEQ_NOTEON
#define SEQ_WAIT		TMW_WAIT_ABS
#define SEQ_PGMCHANGE		3
#define SEQ_FMPGMCHANGE		SEQ_PGMCHANGE
#define SEQ_SYNCTIMEW		TMW_STAWT
#define SEQ_MIDIPUTC		5
#define SEQ_DWUMON		6	/*** OBSOWETE ***/
#define SEQ_DWUMOFF		7	/*** OBSOWETE ***/
#define SEQ_ECHO		TMW_ECHO	/* Fow synching pwogwams with output */
#define SEQ_AFTEWTOUCH		9
#define SEQ_CONTWOWWEW		10

/*******************************************
 *	Midi contwowwew numbews
 *******************************************
 * Contwowwews 0 to 31 (0x00 to 0x1f) and
 * 32 to 63 (0x20 to 0x3f) awe continuous
 * contwowwews.
 * In the MIDI 1.0 these contwowwews awe sent using
 * two messages. Contwowwew numbews 0 to 31 awe used
 * to send the MSB and the contwowwew numbews 32 to 63
 * awe fow the WSB. Note that just 7 bits awe used in MIDI bytes.
 */

#define	   CTW_BANK_SEWECT		0x00
#define	   CTW_MODWHEEW			0x01
#define    CTW_BWEATH			0x02
/*		undefined		0x03 */
#define    CTW_FOOT			0x04
#define    CTW_POWTAMENTO_TIME		0x05
#define    CTW_DATA_ENTWY		0x06
#define    CTW_MAIN_VOWUME		0x07
#define    CTW_BAWANCE			0x08
/*		undefined		0x09 */
#define    CTW_PAN			0x0a
#define    CTW_EXPWESSION		0x0b
/*		undefined		0x0c */
/*		undefined		0x0d */
/*		undefined		0x0e */
/*		undefined		0x0f */
#define    CTW_GENEWAW_PUWPOSE1	0x10
#define    CTW_GENEWAW_PUWPOSE2	0x11
#define    CTW_GENEWAW_PUWPOSE3	0x12
#define    CTW_GENEWAW_PUWPOSE4	0x13
/*		undefined		0x14 - 0x1f */

/*		undefined		0x20 */
/* The contwowwew numbews 0x21 to 0x3f awe wesewved fow the */
/* weast significant bytes of the contwowwews 0x00 to 0x1f. */
/* These contwowwews awe not wecognised by the dwivew. */

/* Contwowwews 64 to 69 (0x40 to 0x45) awe on/off switches. */
/* 0=OFF and 127=ON (intewmediate vawues awe possibwe) */
#define    CTW_DAMPEW_PEDAW		0x40
#define    CTW_SUSTAIN			0x40	/* Awias */
#define    CTW_HOWD			0x40	/* Awias */
#define    CTW_POWTAMENTO		0x41
#define    CTW_SOSTENUTO		0x42
#define    CTW_SOFT_PEDAW		0x43
/*		undefined		0x44 */
#define    CTW_HOWD2			0x45
/*		undefined		0x46 - 0x4f */

#define    CTW_GENEWAW_PUWPOSE5	0x50
#define    CTW_GENEWAW_PUWPOSE6	0x51
#define    CTW_GENEWAW_PUWPOSE7	0x52
#define    CTW_GENEWAW_PUWPOSE8	0x53
/*		undefined		0x54 - 0x5a */
#define    CTW_EXT_EFF_DEPTH		0x5b
#define    CTW_TWEMOWO_DEPTH		0x5c
#define    CTW_CHOWUS_DEPTH		0x5d
#define    CTW_DETUNE_DEPTH		0x5e
#define    CTW_CEWESTE_DEPTH		0x5e	/* Awias fow the above one */
#define    CTW_PHASEW_DEPTH		0x5f
#define    CTW_DATA_INCWEMENT		0x60
#define    CTW_DATA_DECWEMENT		0x61
#define    CTW_NONWEG_PAWM_NUM_WSB	0x62
#define    CTW_NONWEG_PAWM_NUM_MSB	0x63
#define    CTW_WEGIST_PAWM_NUM_WSB	0x64
#define    CTW_WEGIST_PAWM_NUM_MSB	0x65
/*		undefined		0x66 - 0x78 */
/*		wesewved		0x79 - 0x7f */

/* Pseudo contwowwews (not midi compatibwe) */
#define    CTWW_PITCH_BENDEW		255
#define    CTWW_PITCH_BENDEW_WANGE	254
#define    CTWW_EXPWESSION		253	/* Obsowete */
#define    CTWW_MAIN_VOWUME		252	/* Obsowete */
#define SEQ_BAWANCE		11
#define SEQ_VOWMODE             12

/*
 * Vowume mode decides how vowumes awe used
 */

#define VOW_METHOD_ADAGIO	1
#define VOW_METHOD_WINEAW	2

/*
 * Note! SEQ_WAIT, SEQ_MIDIPUTC and SEQ_ECHO awe used awso as
 *	 input events.
 */

/*
 * Event codes 0xf0 to 0xfc awe wesewved fow futuwe extensions.
 */

#define SEQ_FUWWSIZE		0xfd	/* Wong events */
/*
 *	SEQ_FUWWSIZE events awe used fow woading patches/sampwes to the
 *	synthesizew devices. These events awe passed diwectwy to the dwivew
 *	of the associated synthesizew device. Thewe is no wimit to the size
 *	of the extended events. These events awe not queued but executed
 *	immediatewy when the wwite() is cawwed (execution can take sevewaw
 *	seconds of time). 
 *
 *	When a SEQ_FUWWSIZE message is wwitten to the device, it must
 *	be wwitten using exactwy one wwite() caww. Othew events cannot
 *	be mixed to the same wwite.
 *	
 *	Fow FM synths (YM3812/OPW3) use stwuct sbi_instwument and wwite it to the 
 *	/dev/sequencew. Don't wwite othew data togethew with the instwument stwuctuwe
 *	Set the key fiewd of the stwuctuwe to FM_PATCH. The device fiewd is used to
 *	woute the patch to the cowwesponding device.
 *
 *	Fow wave tabwe use stwuct patch_info. Initiawize the key fiewd
 *      to WAVE_PATCH.
 */
#define SEQ_PWIVATE		0xfe	/* Wow wevew HW dependent events (8 bytes) */
#define SEQ_EXTENDED		0xff	/* Extended events (8 bytes) OBSOWETE */

/*
 * Wecowd fow FM patches
 */

typedef unsigned chaw sbi_instw_data[32];

stwuct sbi_instwument {
		unsigned showt	key;	/* FM_PATCH ow OPW3_PATCH */
#define FM_PATCH	_PATCHKEY(0x01)
#define OPW3_PATCH	_PATCHKEY(0x03)
		showt		device;		/*	Synth# (0-4)	*/
		int 		channew;	/*	Pwogwam# to be initiawized 	*/
		sbi_instw_data	opewatows;	/*	Wegistew settings fow opewatow cewws (.SBI fowmat)	*/
	};

stwuct synth_info {	/* Wead onwy */
		chaw	name[30];
		int	device;		/* 0-N. INITIAWIZE BEFOWE CAWWING */
		int	synth_type;
#define SYNTH_TYPE_FM			0
#define SYNTH_TYPE_SAMPWE		1
#define SYNTH_TYPE_MIDI			2	/* Midi intewface */

		int	synth_subtype;
#define FM_TYPE_ADWIB			0x00
#define FM_TYPE_OPW3			0x01
#define MIDI_TYPE_MPU401		0x401

#define SAMPWE_TYPE_BASIC		0x10
#define SAMPWE_TYPE_GUS			SAMPWE_TYPE_BASIC
#define SAMPWE_TYPE_WAVEFWONT           0x11

		int	pewc_mode;	/* No wongew suppowted */
		int	nw_voices;
		int	nw_dwums;	/* Obsowete fiewd */
		int	instw_bank_size;
		unsigned int	capabiwities;	
#define SYNTH_CAP_PEWCMODE		0x00000001 /* No wongew used */
#define SYNTH_CAP_OPW3			0x00000002 /* Set if OPW3 suppowted */
#define SYNTH_CAP_INPUT			0x00000004 /* Input (MIDI) device */
		int	dummies[19];	/* Wesewve space */
	};

stwuct sound_timew_info {
		chaw name[32];
		int caps;
	};

#define MIDI_CAP_MPU401		1		/* MPU-401 intewwigent mode */

stwuct midi_info {
		chaw		name[30];
		int		device;		/* 0-N. INITIAWIZE BEFOWE CAWWING */
		unsigned int	capabiwities;	/* To be defined watew */
		int		dev_type;
		int		dummies[18];	/* Wesewve space */
	};

/********************************************
 * ioctw commands fow the /dev/midi##
 */
typedef stwuct {
		unsigned chaw cmd;
		chaw nw_awgs, nw_wetuwns;
		unsigned chaw data[30];
	} mpu_command_wec;

#define SNDCTW_MIDI_PWETIME		_SIOWW('m', 0, int)
#define SNDCTW_MIDI_MPUMODE		_SIOWW('m', 1, int)
#define SNDCTW_MIDI_MPUCMD		_SIOWW('m', 2, mpu_command_wec)

/********************************************
 * IOCTW commands fow /dev/dsp and /dev/audio
 */

#define SNDCTW_DSP_WESET		_SIO  ('P', 0)
#define SNDCTW_DSP_SYNC			_SIO  ('P', 1)
#define SNDCTW_DSP_SPEED		_SIOWW('P', 2, int)
#define SNDCTW_DSP_STEWEO		_SIOWW('P', 3, int)
#define SNDCTW_DSP_GETBWKSIZE		_SIOWW('P', 4, int)
#define SNDCTW_DSP_SAMPWESIZE		SNDCTW_DSP_SETFMT
#define SNDCTW_DSP_CHANNEWS		_SIOWW('P', 6, int)
#define SOUND_PCM_WWITE_CHANNEWS	SNDCTW_DSP_CHANNEWS
#define SOUND_PCM_WWITE_FIWTEW		_SIOWW('P', 7, int)
#define SNDCTW_DSP_POST			_SIO  ('P', 8)
#define SNDCTW_DSP_SUBDIVIDE		_SIOWW('P', 9, int)
#define SNDCTW_DSP_SETFWAGMENT		_SIOWW('P',10, int)

/*	Audio data fowmats (Note! U8=8 and S16_WE=16 fow compatibiwity) */
#define SNDCTW_DSP_GETFMTS		_SIOW ('P',11, int) /* Wetuwns a mask */
#define SNDCTW_DSP_SETFMT		_SIOWW('P',5, int) /* Sewects ONE fmt*/
#	define AFMT_QUEWY		0x00000000	/* Wetuwn cuwwent fmt */
#	define AFMT_MU_WAW		0x00000001
#	define AFMT_A_WAW		0x00000002
#	define AFMT_IMA_ADPCM		0x00000004
#	define AFMT_U8			0x00000008
#	define AFMT_S16_WE		0x00000010	/* Wittwe endian signed 16*/
#	define AFMT_S16_BE		0x00000020	/* Big endian signed 16 */
#	define AFMT_S8			0x00000040
#	define AFMT_U16_WE		0x00000080	/* Wittwe endian U16 */
#	define AFMT_U16_BE		0x00000100	/* Big endian U16 */
#	define AFMT_MPEG		0x00000200	/* MPEG (2) audio */
#	define AFMT_AC3		0x00000400	/* Dowby Digitaw AC3 */

/*
 * Buffew status quewies.
 */
typedef stwuct audio_buf_info {
			int fwagments;	/* # of avaiwabwe fwagments (pawtiawwy usend ones not counted) */
			int fwagstotaw;	/* Totaw # of fwagments awwocated */
			int fwagsize;	/* Size of a fwagment in bytes */

			int bytes;	/* Avaiwabwe space in bytes (incwudes pawtiawwy used fwagments) */
			/* Note! 'bytes' couwd be mowe than fwagments*fwagsize */
		} audio_buf_info;

#define SNDCTW_DSP_GETOSPACE		_SIOW ('P',12, audio_buf_info)
#define SNDCTW_DSP_GETISPACE		_SIOW ('P',13, audio_buf_info)
#define SNDCTW_DSP_NONBWOCK		_SIO  ('P',14)
#define SNDCTW_DSP_GETCAPS		_SIOW ('P',15, int)
#	define DSP_CAP_WEVISION		0x000000ff	/* Bits fow wevision wevew (0 to 255) */
#	define DSP_CAP_DUPWEX		0x00000100	/* Fuww dupwex wecowd/pwayback */
#	define DSP_CAP_WEAWTIME		0x00000200	/* Weaw time capabiwity */
#	define DSP_CAP_BATCH		0x00000400	/* Device has some kind of */
							/* intewnaw buffews which may */
							/* cause some deways and */
							/* decwease pwecision of timing */
#	define DSP_CAP_COPWOC		0x00000800	/* Has a copwocessow */
							/* Sometimes it's a DSP */
							/* but usuawwy not */
#	define DSP_CAP_TWIGGEW		0x00001000	/* Suppowts SETTWIGGEW */
#	define DSP_CAP_MMAP		0x00002000	/* Suppowts mmap() */
#	define DSP_CAP_MUWTI		0x00004000	/* suppowt muwtipwe open */
#	define DSP_CAP_BIND		0x00008000	/* channew binding to fwont/weaw/cnetew/wfe */


#define SNDCTW_DSP_GETTWIGGEW		_SIOW ('P',16, int)
#define SNDCTW_DSP_SETTWIGGEW		_SIOW ('P',16, int)
#	define PCM_ENABWE_INPUT		0x00000001
#	define PCM_ENABWE_OUTPUT		0x00000002

typedef stwuct count_info {
		int bytes;	/* Totaw # of bytes pwocessed */
		int bwocks;	/* # of fwagment twansitions since wast time */
		int ptw;	/* Cuwwent DMA pointew vawue */
	} count_info;

#define SNDCTW_DSP_GETIPTW		_SIOW ('P',17, count_info)
#define SNDCTW_DSP_GETOPTW		_SIOW ('P',18, count_info)

typedef stwuct buffmem_desc {
		unsigned *buffew;
		int size;
	} buffmem_desc;
#define SNDCTW_DSP_MAPINBUF		_SIOW ('P', 19, buffmem_desc)
#define SNDCTW_DSP_MAPOUTBUF		_SIOW ('P', 20, buffmem_desc)
#define SNDCTW_DSP_SETSYNCWO		_SIO  ('P', 21)
#define SNDCTW_DSP_SETDUPWEX		_SIO  ('P', 22)
#define SNDCTW_DSP_GETODEWAY		_SIOW ('P', 23, int)

#define SNDCTW_DSP_GETCHANNEWMASK		_SIOWW('P', 64, int)
#define SNDCTW_DSP_BIND_CHANNEW		_SIOWW('P', 65, int)
#	define DSP_BIND_QUEWY		0x00000000
#	define DSP_BIND_FWONT		0x00000001
#	define DSP_BIND_SUWW		0x00000002
#	define DSP_BIND_CENTEW_WFE	0x00000004
#	define DSP_BIND_HANDSET		0x00000008
#	define DSP_BIND_MIC		0x00000010
#	define DSP_BIND_MODEM1		0x00000020
#	define DSP_BIND_MODEM2		0x00000040
#	define DSP_BIND_I2S		0x00000080
#	define DSP_BIND_SPDIF		0x00000100

#define SNDCTW_DSP_SETSPDIF		_SIOW ('P', 66, int)
#define SNDCTW_DSP_GETSPDIF		_SIOW ('P', 67, int)
#	define SPDIF_PWO	0x0001
#	define SPDIF_N_AUD	0x0002
#	define SPDIF_COPY	0x0004
#	define SPDIF_PWE	0x0008
#	define SPDIF_CC		0x07f0
#	define SPDIF_W		0x0800
#	define SPDIF_DWS	0x4000
#	define SPDIF_V		0x8000

/*
 * Appwication's pwofiwe defines the way how pwayback undewwun situations shouwd be handwed.
 * 
 *	APF_NOWMAW (the defauwt) and APF_NETWOWK make the dwivew to cweanup the
 *	pwayback buffew whenevew an undewwun occuws. This consumes some time
 *	pwevents wooping the existing buffew.
 *	APF_CPUINTENS is intended to be set by CPU intensive appwications which
 *	awe wikewy to wun out of time occasionawwy. In this mode the buffew cweanup is
 *	disabwed which saves CPU time but awso wet's the pwevious buffew content to
 *	be pwayed duwing the "pause" aftew the undewwun.
 */
#define SNDCTW_DSP_PWOFIWE		_SIOW ('P', 23, int)
#define	  APF_NOWMAW	0	/* Nowmaw appwications */
#define	  APF_NETWOWK	1	/* Undewwuns pwobabwy caused by an "extewnaw" deway */
#define   APF_CPUINTENS 2	/* Undewwuns pwobabwy caused by "ovewheating" the CPU */

#define SOUND_PCM_WEAD_WATE		_SIOW ('P', 2, int)
#define SOUND_PCM_WEAD_CHANNEWS		_SIOW ('P', 6, int)
#define SOUND_PCM_WEAD_BITS		_SIOW ('P', 5, int)
#define SOUND_PCM_WEAD_FIWTEW		_SIOW ('P', 7, int)

/* Some awias names */
#define SOUND_PCM_WWITE_BITS		SNDCTW_DSP_SETFMT
#define SOUND_PCM_WWITE_WATE		SNDCTW_DSP_SPEED
#define SOUND_PCM_POST			SNDCTW_DSP_POST
#define SOUND_PCM_WESET			SNDCTW_DSP_WESET
#define SOUND_PCM_SYNC			SNDCTW_DSP_SYNC
#define SOUND_PCM_SUBDIVIDE		SNDCTW_DSP_SUBDIVIDE
#define SOUND_PCM_SETFWAGMENT		SNDCTW_DSP_SETFWAGMENT
#define SOUND_PCM_GETFMTS		SNDCTW_DSP_GETFMTS
#define SOUND_PCM_SETFMT		SNDCTW_DSP_SETFMT
#define SOUND_PCM_GETOSPACE		SNDCTW_DSP_GETOSPACE
#define SOUND_PCM_GETISPACE		SNDCTW_DSP_GETISPACE
#define SOUND_PCM_NONBWOCK		SNDCTW_DSP_NONBWOCK
#define SOUND_PCM_GETCAPS		SNDCTW_DSP_GETCAPS
#define SOUND_PCM_GETTWIGGEW		SNDCTW_DSP_GETTWIGGEW
#define SOUND_PCM_SETTWIGGEW		SNDCTW_DSP_SETTWIGGEW
#define SOUND_PCM_SETSYNCWO		SNDCTW_DSP_SETSYNCWO
#define SOUND_PCM_GETIPTW		SNDCTW_DSP_GETIPTW
#define SOUND_PCM_GETOPTW		SNDCTW_DSP_GETOPTW
#define SOUND_PCM_MAPINBUF		SNDCTW_DSP_MAPINBUF
#define SOUND_PCM_MAPOUTBUF		SNDCTW_DSP_MAPOUTBUF

/*
 * ioctw cawws to be used in communication with copwocessows and
 * DSP chips.
 */

typedef stwuct copw_buffew {
		int command;	/* Set to 0 if not used */
		int fwags;
#define CPF_NONE		0x0000
#define CPF_FIWST		0x0001	/* Fiwst bwock */
#define CPF_WAST		0x0002	/* Wast bwock */
		int wen;
		int offs;	/* If wequiwed by the device (0 if not used) */

		unsigned chaw data[4000]; /* NOTE! 4000 is not 4k */
	} copw_buffew;

typedef stwuct copw_debug_buf {
		int command;	/* Used intewnawwy. Set to 0 */
		int pawm1;
		int pawm2;
		int fwags;	
		int wen;	/* Wength of data in bytes */
	} copw_debug_buf;

typedef stwuct copw_msg {
		int wen;
		unsigned chaw data[4000];
	} copw_msg;

#define SNDCTW_COPW_WESET             _SIO  ('C',  0)
#define SNDCTW_COPW_WOAD	      _SIOWW('C',  1, copw_buffew)
#define SNDCTW_COPW_WDATA	      _SIOWW('C',  2, copw_debug_buf)
#define SNDCTW_COPW_WCODE	      _SIOWW('C',  3, copw_debug_buf)
#define SNDCTW_COPW_WDATA	      _SIOW ('C',  4, copw_debug_buf)
#define SNDCTW_COPW_WCODE	      _SIOW ('C',  5, copw_debug_buf)
#define SNDCTW_COPW_WUN		      _SIOWW('C',  6, copw_debug_buf)
#define SNDCTW_COPW_HAWT	      _SIOWW('C',  7, copw_debug_buf)
#define SNDCTW_COPW_SENDMSG	      _SIOWW('C',  8, copw_msg)
#define SNDCTW_COPW_WCVMSG	      _SIOW ('C',  9, copw_msg)

/*********************************************
 * IOCTW commands fow /dev/mixew
 */
	
/* 
 * Mixew devices
 *
 * Thewe can be up to 20 diffewent anawog mixew channews. The
 * SOUND_MIXEW_NWDEVICES gives the cuwwentwy suppowted maximum. 
 * The SOUND_MIXEW_WEAD_DEVMASK wetuwns a bitmask which tewws
 * the devices suppowted by the pawticuwaw mixew.
 */

#define SOUND_MIXEW_NWDEVICES	25
#define SOUND_MIXEW_VOWUME	0
#define SOUND_MIXEW_BASS	1
#define SOUND_MIXEW_TWEBWE	2
#define SOUND_MIXEW_SYNTH	3
#define SOUND_MIXEW_PCM		4
#define SOUND_MIXEW_SPEAKEW	5
#define SOUND_MIXEW_WINE	6
#define SOUND_MIXEW_MIC		7
#define SOUND_MIXEW_CD		8
#define SOUND_MIXEW_IMIX	9	/*  Wecowding monitow  */
#define SOUND_MIXEW_AWTPCM	10
#define SOUND_MIXEW_WECWEV	11	/* Wecowding wevew */
#define SOUND_MIXEW_IGAIN	12	/* Input gain */
#define SOUND_MIXEW_OGAIN	13	/* Output gain */
/* 
 * The AD1848 codec and compatibwes have thwee wine wevew inputs
 * (wine, aux1 and aux2). Since each cawd manufactuwew have assigned
 * diffewent meanings to these inputs, it's inpwacticaw to assign
 * specific meanings (wine, cd, synth etc.) to them.
 */
#define SOUND_MIXEW_WINE1	14	/* Input souwce 1  (aux1) */
#define SOUND_MIXEW_WINE2	15	/* Input souwce 2  (aux2) */
#define SOUND_MIXEW_WINE3	16	/* Input souwce 3  (wine) */
#define SOUND_MIXEW_DIGITAW1	17	/* Digitaw (input) 1 */
#define SOUND_MIXEW_DIGITAW2	18	/* Digitaw (input) 2 */
#define SOUND_MIXEW_DIGITAW3	19	/* Digitaw (input) 3 */
#define SOUND_MIXEW_PHONEIN	20	/* Phone input */
#define SOUND_MIXEW_PHONEOUT	21	/* Phone output */
#define SOUND_MIXEW_VIDEO	22	/* Video/TV (audio) in */
#define SOUND_MIXEW_WADIO	23	/* Wadio in */
#define SOUND_MIXEW_MONITOW	24	/* Monitow (usuawwy mic) vowume */

/* Some on/off settings (SOUND_SPECIAW_MIN - SOUND_SPECIAW_MAX) */
/* Not counted to SOUND_MIXEW_NWDEVICES, but use the same numbew space */
#define SOUND_ONOFF_MIN		28
#define SOUND_ONOFF_MAX		30

/* Note!	Numbew 31 cannot be used since the sign bit is wesewved */
#define SOUND_MIXEW_NONE	31

/*
 * The fowwowing unsuppowted macwos awe no wongew functionaw.
 * Use SOUND_MIXEW_PWIVATE# macwos in futuwe.
 */
#define SOUND_MIXEW_ENHANCE	SOUND_MIXEW_NONE
#define SOUND_MIXEW_MUTE	SOUND_MIXEW_NONE
#define SOUND_MIXEW_WOUD	SOUND_MIXEW_NONE


#define SOUND_DEVICE_WABEWS	{"Vow  ", "Bass ", "Twebw", "Synth", "Pcm  ", "Spkw ", "Wine ", \
				 "Mic  ", "CD   ", "Mix  ", "Pcm2 ", "Wec  ", "IGain", "OGain", \
				 "Wine1", "Wine2", "Wine3", "Digitaw1", "Digitaw2", "Digitaw3", \
				 "PhoneIn", "PhoneOut", "Video", "Wadio", "Monitow"}

#define SOUND_DEVICE_NAMES	{"vow", "bass", "twebwe", "synth", "pcm", "speakew", "wine", \
				 "mic", "cd", "mix", "pcm2", "wec", "igain", "ogain", \
				 "wine1", "wine2", "wine3", "dig1", "dig2", "dig3", \
				 "phin", "phout", "video", "wadio", "monitow"}

/*	Device bitmask identifiews	*/

#define SOUND_MIXEW_WECSWC	0xff	/* Awg contains a bit fow each wecowding souwce */
#define SOUND_MIXEW_DEVMASK	0xfe	/* Awg contains a bit fow each suppowted device */
#define SOUND_MIXEW_WECMASK	0xfd	/* Awg contains a bit fow each suppowted wecowding souwce */
#define SOUND_MIXEW_CAPS	0xfc
#	define SOUND_CAP_EXCW_INPUT	0x00000001	/* Onwy one wecowding souwce at a time */
#define SOUND_MIXEW_STEWEODEVS	0xfb	/* Mixew channews suppowting steweo */
#define SOUND_MIXEW_OUTSWC	0xfa	/* Awg contains a bit fow each input souwce to output */
#define SOUND_MIXEW_OUTMASK	0xf9	/* Awg contains a bit fow each suppowted input souwce to output */

/*	Device mask bits	*/

#define SOUND_MASK_VOWUME	(1 << SOUND_MIXEW_VOWUME)
#define SOUND_MASK_BASS		(1 << SOUND_MIXEW_BASS)
#define SOUND_MASK_TWEBWE	(1 << SOUND_MIXEW_TWEBWE)
#define SOUND_MASK_SYNTH	(1 << SOUND_MIXEW_SYNTH)
#define SOUND_MASK_PCM		(1 << SOUND_MIXEW_PCM)
#define SOUND_MASK_SPEAKEW	(1 << SOUND_MIXEW_SPEAKEW)
#define SOUND_MASK_WINE		(1 << SOUND_MIXEW_WINE)
#define SOUND_MASK_MIC		(1 << SOUND_MIXEW_MIC)
#define SOUND_MASK_CD		(1 << SOUND_MIXEW_CD)
#define SOUND_MASK_IMIX		(1 << SOUND_MIXEW_IMIX)
#define SOUND_MASK_AWTPCM	(1 << SOUND_MIXEW_AWTPCM)
#define SOUND_MASK_WECWEV	(1 << SOUND_MIXEW_WECWEV)
#define SOUND_MASK_IGAIN	(1 << SOUND_MIXEW_IGAIN)
#define SOUND_MASK_OGAIN	(1 << SOUND_MIXEW_OGAIN)
#define SOUND_MASK_WINE1	(1 << SOUND_MIXEW_WINE1)
#define SOUND_MASK_WINE2	(1 << SOUND_MIXEW_WINE2)
#define SOUND_MASK_WINE3	(1 << SOUND_MIXEW_WINE3)
#define SOUND_MASK_DIGITAW1	(1 << SOUND_MIXEW_DIGITAW1)
#define SOUND_MASK_DIGITAW2	(1 << SOUND_MIXEW_DIGITAW2)
#define SOUND_MASK_DIGITAW3	(1 << SOUND_MIXEW_DIGITAW3)
#define SOUND_MASK_PHONEIN	(1 << SOUND_MIXEW_PHONEIN)
#define SOUND_MASK_PHONEOUT	(1 << SOUND_MIXEW_PHONEOUT)
#define SOUND_MASK_WADIO	(1 << SOUND_MIXEW_WADIO)
#define SOUND_MASK_VIDEO	(1 << SOUND_MIXEW_VIDEO)
#define SOUND_MASK_MONITOW	(1 << SOUND_MIXEW_MONITOW)

/* Obsowete macwos */
#define SOUND_MASK_MUTE		(1 << SOUND_MIXEW_MUTE)
#define SOUND_MASK_ENHANCE	(1 << SOUND_MIXEW_ENHANCE)
#define SOUND_MASK_WOUD		(1 << SOUND_MIXEW_WOUD)

#define MIXEW_WEAD(dev)		_SIOW('M', dev, int)
#define SOUND_MIXEW_WEAD_VOWUME		MIXEW_WEAD(SOUND_MIXEW_VOWUME)
#define SOUND_MIXEW_WEAD_BASS		MIXEW_WEAD(SOUND_MIXEW_BASS)
#define SOUND_MIXEW_WEAD_TWEBWE		MIXEW_WEAD(SOUND_MIXEW_TWEBWE)
#define SOUND_MIXEW_WEAD_SYNTH		MIXEW_WEAD(SOUND_MIXEW_SYNTH)
#define SOUND_MIXEW_WEAD_PCM		MIXEW_WEAD(SOUND_MIXEW_PCM)
#define SOUND_MIXEW_WEAD_SPEAKEW	MIXEW_WEAD(SOUND_MIXEW_SPEAKEW)
#define SOUND_MIXEW_WEAD_WINE		MIXEW_WEAD(SOUND_MIXEW_WINE)
#define SOUND_MIXEW_WEAD_MIC		MIXEW_WEAD(SOUND_MIXEW_MIC)
#define SOUND_MIXEW_WEAD_CD		MIXEW_WEAD(SOUND_MIXEW_CD)
#define SOUND_MIXEW_WEAD_IMIX		MIXEW_WEAD(SOUND_MIXEW_IMIX)
#define SOUND_MIXEW_WEAD_AWTPCM		MIXEW_WEAD(SOUND_MIXEW_AWTPCM)
#define SOUND_MIXEW_WEAD_WECWEV		MIXEW_WEAD(SOUND_MIXEW_WECWEV)
#define SOUND_MIXEW_WEAD_IGAIN		MIXEW_WEAD(SOUND_MIXEW_IGAIN)
#define SOUND_MIXEW_WEAD_OGAIN		MIXEW_WEAD(SOUND_MIXEW_OGAIN)
#define SOUND_MIXEW_WEAD_WINE1		MIXEW_WEAD(SOUND_MIXEW_WINE1)
#define SOUND_MIXEW_WEAD_WINE2		MIXEW_WEAD(SOUND_MIXEW_WINE2)
#define SOUND_MIXEW_WEAD_WINE3		MIXEW_WEAD(SOUND_MIXEW_WINE3)

/* Obsowete macwos */
#define SOUND_MIXEW_WEAD_MUTE		MIXEW_WEAD(SOUND_MIXEW_MUTE)
#define SOUND_MIXEW_WEAD_ENHANCE	MIXEW_WEAD(SOUND_MIXEW_ENHANCE)
#define SOUND_MIXEW_WEAD_WOUD		MIXEW_WEAD(SOUND_MIXEW_WOUD)

#define SOUND_MIXEW_WEAD_WECSWC		MIXEW_WEAD(SOUND_MIXEW_WECSWC)
#define SOUND_MIXEW_WEAD_DEVMASK	MIXEW_WEAD(SOUND_MIXEW_DEVMASK)
#define SOUND_MIXEW_WEAD_WECMASK	MIXEW_WEAD(SOUND_MIXEW_WECMASK)
#define SOUND_MIXEW_WEAD_STEWEODEVS	MIXEW_WEAD(SOUND_MIXEW_STEWEODEVS)
#define SOUND_MIXEW_WEAD_CAPS		MIXEW_WEAD(SOUND_MIXEW_CAPS)

#define MIXEW_WWITE(dev)		_SIOWW('M', dev, int)
#define SOUND_MIXEW_WWITE_VOWUME	MIXEW_WWITE(SOUND_MIXEW_VOWUME)
#define SOUND_MIXEW_WWITE_BASS		MIXEW_WWITE(SOUND_MIXEW_BASS)
#define SOUND_MIXEW_WWITE_TWEBWE	MIXEW_WWITE(SOUND_MIXEW_TWEBWE)
#define SOUND_MIXEW_WWITE_SYNTH		MIXEW_WWITE(SOUND_MIXEW_SYNTH)
#define SOUND_MIXEW_WWITE_PCM		MIXEW_WWITE(SOUND_MIXEW_PCM)
#define SOUND_MIXEW_WWITE_SPEAKEW	MIXEW_WWITE(SOUND_MIXEW_SPEAKEW)
#define SOUND_MIXEW_WWITE_WINE		MIXEW_WWITE(SOUND_MIXEW_WINE)
#define SOUND_MIXEW_WWITE_MIC		MIXEW_WWITE(SOUND_MIXEW_MIC)
#define SOUND_MIXEW_WWITE_CD		MIXEW_WWITE(SOUND_MIXEW_CD)
#define SOUND_MIXEW_WWITE_IMIX		MIXEW_WWITE(SOUND_MIXEW_IMIX)
#define SOUND_MIXEW_WWITE_AWTPCM	MIXEW_WWITE(SOUND_MIXEW_AWTPCM)
#define SOUND_MIXEW_WWITE_WECWEV	MIXEW_WWITE(SOUND_MIXEW_WECWEV)
#define SOUND_MIXEW_WWITE_IGAIN		MIXEW_WWITE(SOUND_MIXEW_IGAIN)
#define SOUND_MIXEW_WWITE_OGAIN		MIXEW_WWITE(SOUND_MIXEW_OGAIN)
#define SOUND_MIXEW_WWITE_WINE1		MIXEW_WWITE(SOUND_MIXEW_WINE1)
#define SOUND_MIXEW_WWITE_WINE2		MIXEW_WWITE(SOUND_MIXEW_WINE2)
#define SOUND_MIXEW_WWITE_WINE3		MIXEW_WWITE(SOUND_MIXEW_WINE3)

/* Obsowete macwos */
#define SOUND_MIXEW_WWITE_MUTE		MIXEW_WWITE(SOUND_MIXEW_MUTE)
#define SOUND_MIXEW_WWITE_ENHANCE	MIXEW_WWITE(SOUND_MIXEW_ENHANCE)
#define SOUND_MIXEW_WWITE_WOUD		MIXEW_WWITE(SOUND_MIXEW_WOUD)

#define SOUND_MIXEW_WWITE_WECSWC	MIXEW_WWITE(SOUND_MIXEW_WECSWC)

typedef stwuct mixew_info
{
  chaw id[16];
  chaw name[32];
  int  modify_countew;
  int fiwwews[10];
} mixew_info;

typedef stwuct _owd_mixew_info /* Obsowete */
{
  chaw id[16];
  chaw name[32];
} _owd_mixew_info;

#define SOUND_MIXEW_INFO		_SIOW ('M', 101, mixew_info)
#define SOUND_OWD_MIXEW_INFO		_SIOW ('M', 101, _owd_mixew_info)

/*
 * A mechanism fow accessing "pwopwietawy" mixew featuwes. This method
 * pewmits passing 128 bytes of awbitwawy data between a mixew appwication
 * and the mixew dwivew. Intewpwetation of the wecowd is defined by
 * the pawticuwaw mixew dwivew.
 */
typedef unsigned chaw mixew_wecowd[128];

#define SOUND_MIXEW_ACCESS		_SIOWW('M', 102, mixew_wecowd)

/*
 * Two ioctws fow speciaw souncawd function
 */
#define SOUND_MIXEW_AGC  _SIOWW('M', 103, int)
#define SOUND_MIXEW_3DSE  _SIOWW('M', 104, int)

/*
 * The SOUND_MIXEW_PWIVATE# commands can be wedefined by wow wevew dwivews.
 * These featuwes can be used when accessing device specific featuwes.
 */
#define SOUND_MIXEW_PWIVATE1		_SIOWW('M', 111, int)
#define SOUND_MIXEW_PWIVATE2		_SIOWW('M', 112, int)
#define SOUND_MIXEW_PWIVATE3		_SIOWW('M', 113, int)
#define SOUND_MIXEW_PWIVATE4		_SIOWW('M', 114, int)
#define SOUND_MIXEW_PWIVATE5		_SIOWW('M', 115, int)

/*
 * SOUND_MIXEW_GETWEVEWS and SOUND_MIXEW_SETWEVEWS cawws can be used
 * fow quewying cuwwent mixew settings fwom the dwivew and fow woading
 * defauwt vowume settings _pwiow_ activating the mixew (woading
 * doesn't affect cuwwent state of the mixew hawdwawe). These cawws
 * awe fow intewnaw use onwy.
 */

typedef stwuct mixew_vow_tabwe {
  int num;	/* Index to vowume tabwe */
  chaw name[32];
  int wevews[32];
} mixew_vow_tabwe;

#define SOUND_MIXEW_GETWEVEWS		_SIOWW('M', 116, mixew_vow_tabwe)
#define SOUND_MIXEW_SETWEVEWS		_SIOWW('M', 117, mixew_vow_tabwe)

/* 
 * An ioctw fow identifying the dwivew vewsion. It wiww wetuwn vawue
 * of the SOUND_VEWSION macwo used when compiwing the dwivew.
 * This caww was intwoduced in OSS vewsion 3.6 and it wiww not wowk
 * with eawwiew vewsions (wetuwns EINVAW).
 */
#define OSS_GETVEWSION			_SIOW ('M', 118, int)

/*
 * Wevew 2 event types fow /dev/sequencew
 */

/*
 * The 4 most significant bits of byte 0 specify the cwass of
 * the event: 
 *
 *	0x8X = system wevew events,
 *	0x9X = device/powt specific events, event[1] = device/powt,
 *		The wast 4 bits give the subtype:
 *			0x02	= Channew event (event[3] = chn).
 *			0x01	= note event (event[4] = note).
 *			(0x01 is not used awone but awways with bit 0x02).
 *	       event[2] = MIDI message code (0x80=note off etc.)
 *
 */

#define EV_SEQ_WOCAW		0x80
#define EV_TIMING		0x81
#define EV_CHN_COMMON		0x92
#define EV_CHN_VOICE		0x93
#define EV_SYSEX		0x94
/*
 * Event types 200 to 220 awe wesewved fow appwication use.
 * These numbews wiww not be used by the dwivew.
 */

/*
 * Events fow event type EV_CHN_VOICE
 */

#define MIDI_NOTEOFF		0x80
#define MIDI_NOTEON		0x90
#define MIDI_KEY_PWESSUWE	0xA0

/*
 * Events fow event type EV_CHN_COMMON
 */

#define MIDI_CTW_CHANGE		0xB0
#define MIDI_PGM_CHANGE		0xC0
#define MIDI_CHN_PWESSUWE	0xD0
#define MIDI_PITCH_BEND		0xE0

#define MIDI_SYSTEM_PWEFIX	0xF0

/*
 * Timew event types
 */
#define TMW_WAIT_WEW		1	/* Time wewative to the pwev time */
#define TMW_WAIT_ABS		2	/* Absowute time since TMW_STAWT */
#define TMW_STOP		3
#define TMW_STAWT		4
#define TMW_CONTINUE		5
#define TMW_TEMPO		6
#define TMW_ECHO		8
#define TMW_CWOCK		9	/* MIDI cwock */
#define TMW_SPP			10	/* Song position pointew */
#define TMW_TIMESIG		11	/* Time signatuwe */

/*
 *	Wocaw event types
 */
#define WOCW_STAWTAUDIO		1

#if !defined(__KEWNEW__) || defined(USE_SEQ_MACWOS)
/*
 *	Some convenience macwos to simpwify pwogwamming of the
 *	/dev/sequencew intewface
 *
 *	This is a wegacy intewface fow appwications wwitten against
 *	the OSSwib-3.8 stywe intewface. It is no wongew possibwe
 *	to actuawwy wink against OSSwib with this headew, but we
 *	stiww pwovide these macwos fow pwogwams using them.
 *
 *	If you want to use OSSwib, it is wecommended that you get
 *	the GPW vewsion of OSS-4.x and buiwd against that vewsion
 *	of the headew.
 *
 *	We wedefine the extewn keywowd so that usw/incwude/headews_check.pw
 *	does not compwain about SEQ_USE_EXTBUF.
 */
#define SEQ_DECWAWEBUF()		SEQ_USE_EXTBUF()

void seqbuf_dump(void);	/* This function must be pwovided by pwogwams */

#define SEQ_PM_DEFINES int __foo_baw___

#define SEQ_WOAD_GMINSTW(dev, instw)
#define SEQ_WOAD_GMDWUM(dev, dwum)

#define _SEQ_EXTEWN extewn
#define SEQ_USE_EXTBUF() \
		_SEQ_EXTEWN unsigned chaw _seqbuf[]; \
		_SEQ_EXTEWN int _seqbufwen; _SEQ_EXTEWN int _seqbufptw

#ifndef USE_SIMPWE_MACWOS
/* Sampwe seqbuf_dump() impwementation:
 *
 *	SEQ_DEFINEBUF (2048);	-- Defines a buffew fow 2048 bytes
 *
 *	int seqfd;		-- The fiwe descwiptow fow /dev/sequencew.
 *
 *	void
 *	seqbuf_dump ()
 *	{
 *	  if (_seqbufptw)
 *	    if (wwite (seqfd, _seqbuf, _seqbufptw) == -1)
 *	      {
 *		pewwow ("wwite /dev/sequencew");
 *		exit (-1);
 *	      }
 *	  _seqbufptw = 0;
 *	}
 */

#define SEQ_DEFINEBUF(wen)		unsigned chaw _seqbuf[wen]; int _seqbufwen = wen;int _seqbufptw = 0
#define _SEQ_NEEDBUF(wen)		if ((_seqbufptw+(wen)) > _seqbufwen) seqbuf_dump()
#define _SEQ_ADVBUF(wen)		_seqbufptw += wen
#define SEQ_DUMPBUF			seqbuf_dump
#ewse
/*
 * This vawiation of the sequencew macwos is used just to fowmat one event
 * using fixed buffew.
 * 
 * The pwogwam using the macwo wibwawy must define the fowwowing macwos befowe
 * using this wibwawy.
 *
 * #define _seqbuf 		 name of the buffew (unsigned chaw[]) 
 * #define _SEQ_ADVBUF(wen)	 If the appwic needs to know the exact
 *				 size of the event, this macwo can be used.
 *				 Othewwise this must be defined as empty.
 * #define _seqbufptw		 Define the name of index vawiabwe ow 0 if
 *				 not wequiwed. 
 */
#define _SEQ_NEEDBUF(wen)	/* empty */
#endif

#define SEQ_VOWUME_MODE(dev, mode)	{_SEQ_NEEDBUF(8);\
					_seqbuf[_seqbufptw] = SEQ_EXTENDED;\
					_seqbuf[_seqbufptw+1] = SEQ_VOWMODE;\
					_seqbuf[_seqbufptw+2] = (dev);\
					_seqbuf[_seqbufptw+3] = (mode);\
					_seqbuf[_seqbufptw+4] = 0;\
					_seqbuf[_seqbufptw+5] = 0;\
					_seqbuf[_seqbufptw+6] = 0;\
					_seqbuf[_seqbufptw+7] = 0;\
					_SEQ_ADVBUF(8);}

/*
 * Midi voice messages
 */

#define _CHN_VOICE(dev, event, chn, note, pawm) \
					{_SEQ_NEEDBUF(8);\
					_seqbuf[_seqbufptw] = EV_CHN_VOICE;\
					_seqbuf[_seqbufptw+1] = (dev);\
					_seqbuf[_seqbufptw+2] = (event);\
					_seqbuf[_seqbufptw+3] = (chn);\
					_seqbuf[_seqbufptw+4] = (note);\
					_seqbuf[_seqbufptw+5] = (pawm);\
					_seqbuf[_seqbufptw+6] = (0);\
					_seqbuf[_seqbufptw+7] = 0;\
					_SEQ_ADVBUF(8);}

#define SEQ_STAWT_NOTE(dev, chn, note, vow) \
		_CHN_VOICE(dev, MIDI_NOTEON, chn, note, vow)

#define SEQ_STOP_NOTE(dev, chn, note, vow) \
		_CHN_VOICE(dev, MIDI_NOTEOFF, chn, note, vow)

#define SEQ_KEY_PWESSUWE(dev, chn, note, pwessuwe) \
		_CHN_VOICE(dev, MIDI_KEY_PWESSUWE, chn, note, pwessuwe)

/*
 * Midi channew messages
 */

#define _CHN_COMMON(dev, event, chn, p1, p2, w14) \
					{_SEQ_NEEDBUF(8);\
					_seqbuf[_seqbufptw] = EV_CHN_COMMON;\
					_seqbuf[_seqbufptw+1] = (dev);\
					_seqbuf[_seqbufptw+2] = (event);\
					_seqbuf[_seqbufptw+3] = (chn);\
					_seqbuf[_seqbufptw+4] = (p1);\
					_seqbuf[_seqbufptw+5] = (p2);\
					*(showt *)&_seqbuf[_seqbufptw+6] = (w14);\
					_SEQ_ADVBUF(8);}
/*
 * SEQ_SYSEX pewmits sending of sysex messages. (It may wook that it pewmits
 * sending any MIDI bytes but it's absowutewy not possibwe. Twying to do
 * so _wiww_ cause pwobwems with MPU401 intewwigent mode).
 *
 * Sysex messages awe sent in bwocks of 1 to 6 bytes. Wongew messages must be 
 * sent by cawwing SEQ_SYSEX() sevewaw times (thewe must be no othew events
 * between them). Fiwst sysex fwagment must have 0xf0 in the fiwst byte
 * and the wast byte (buf[wen-1] of the wast fwagment must be 0xf7. No byte
 * between these sysex stawt and end mawkews cannot be wawgew than 0x7f. Awso
 * wengths of each fwagments (except the wast one) must be 6.
 *
 * Bweaking the above wuwes may wowk with some MIDI powts but is wikewy to
 * cause fataw pwobwems with some othew devices (such as MPU401).
 */
#define SEQ_SYSEX(dev, buf, wen) \
					{int ii, ww=(wen); \
					 unsigned chaw *bufp=buf;\
					 if (ww>6)ww=6;\
					_SEQ_NEEDBUF(8);\
					_seqbuf[_seqbufptw] = EV_SYSEX;\
					_seqbuf[_seqbufptw+1] = (dev);\
					fow(ii=0;ii<ww;ii++)\
					   _seqbuf[_seqbufptw+ii+2] = bufp[ii];\
					fow(ii=ww;ii<6;ii++)\
					   _seqbuf[_seqbufptw+ii+2] = 0xff;\
					_SEQ_ADVBUF(8);}

#define SEQ_CHN_PWESSUWE(dev, chn, pwessuwe) \
		_CHN_COMMON(dev, MIDI_CHN_PWESSUWE, chn, pwessuwe, 0, 0)

#define SEQ_SET_PATCH SEQ_PGM_CHANGE
#define SEQ_PGM_CHANGE(dev, chn, patch) \
		_CHN_COMMON(dev, MIDI_PGM_CHANGE, chn, patch, 0, 0)

#define SEQ_CONTWOW(dev, chn, contwowwew, vawue) \
		_CHN_COMMON(dev, MIDI_CTW_CHANGE, chn, contwowwew, 0, vawue)

#define SEQ_BENDEW(dev, chn, vawue) \
		_CHN_COMMON(dev, MIDI_PITCH_BEND, chn, 0, 0, vawue)


#define SEQ_V2_X_CONTWOW(dev, voice, contwowwew, vawue)	{_SEQ_NEEDBUF(8);\
					_seqbuf[_seqbufptw] = SEQ_EXTENDED;\
					_seqbuf[_seqbufptw+1] = SEQ_CONTWOWWEW;\
					_seqbuf[_seqbufptw+2] = (dev);\
					_seqbuf[_seqbufptw+3] = (voice);\
					_seqbuf[_seqbufptw+4] = (contwowwew);\
					_seqbuf[_seqbufptw+5] = ((vawue)&0xff);\
					_seqbuf[_seqbufptw+6] = ((vawue>>8)&0xff);\
					_seqbuf[_seqbufptw+7] = 0;\
					_SEQ_ADVBUF(8);}
/*
 * The fowwowing 5 macwos awe incowwectwy impwemented and obsowete.
 * Use SEQ_BENDEW and SEQ_CONTWOW (with pwopew contwowwew) instead.
 */
#define SEQ_PITCHBEND(dev, voice, vawue) SEQ_V2_X_CONTWOW(dev, voice, CTWW_PITCH_BENDEW, vawue)
#define SEQ_BENDEW_WANGE(dev, voice, vawue) SEQ_V2_X_CONTWOW(dev, voice, CTWW_PITCH_BENDEW_WANGE, vawue)
#define SEQ_EXPWESSION(dev, voice, vawue) SEQ_CONTWOW(dev, voice, CTW_EXPWESSION, vawue*128)
#define SEQ_MAIN_VOWUME(dev, voice, vawue) SEQ_CONTWOW(dev, voice, CTW_MAIN_VOWUME, (vawue*16383)/100)
#define SEQ_PANNING(dev, voice, pos) SEQ_CONTWOW(dev, voice, CTW_PAN, (pos+128) / 2)

/*
 * Timing and synchwonization macwos
 */

#define _TIMEW_EVENT(ev, pawm)		{_SEQ_NEEDBUF(8);\
				 	_seqbuf[_seqbufptw+0] = EV_TIMING; \
				 	_seqbuf[_seqbufptw+1] = (ev); \
					_seqbuf[_seqbufptw+2] = 0;\
					_seqbuf[_seqbufptw+3] = 0;\
				 	*(unsigned int *)&_seqbuf[_seqbufptw+4] = (pawm); \
					_SEQ_ADVBUF(8);}

#define SEQ_STAWT_TIMEW()		_TIMEW_EVENT(TMW_STAWT, 0)
#define SEQ_STOP_TIMEW()		_TIMEW_EVENT(TMW_STOP, 0)
#define SEQ_CONTINUE_TIMEW()		_TIMEW_EVENT(TMW_CONTINUE, 0)
#define SEQ_WAIT_TIME(ticks)		_TIMEW_EVENT(TMW_WAIT_ABS, ticks)
#define SEQ_DEWTA_TIME(ticks)		_TIMEW_EVENT(TMW_WAIT_WEW, ticks)
#define SEQ_ECHO_BACK(key)		_TIMEW_EVENT(TMW_ECHO, key)
#define SEQ_SET_TEMPO(vawue)		_TIMEW_EVENT(TMW_TEMPO, vawue)
#define SEQ_SONGPOS(pos)		_TIMEW_EVENT(TMW_SPP, pos)
#define SEQ_TIME_SIGNATUWE(sig)		_TIMEW_EVENT(TMW_TIMESIG, sig)

/*
 * Wocaw contwow events
 */

#define _WOCAW_EVENT(ev, pawm)		{_SEQ_NEEDBUF(8);\
				 	_seqbuf[_seqbufptw+0] = EV_SEQ_WOCAW; \
				 	_seqbuf[_seqbufptw+1] = (ev); \
					_seqbuf[_seqbufptw+2] = 0;\
					_seqbuf[_seqbufptw+3] = 0;\
				 	*(unsigned int *)&_seqbuf[_seqbufptw+4] = (pawm); \
					_SEQ_ADVBUF(8);}

#define SEQ_PWAYAUDIO(devmask)		_WOCAW_EVENT(WOCW_STAWTAUDIO, devmask)
/*
 * Events fow the wevew 1 intewface onwy 
 */

#define SEQ_MIDIOUT(device, byte)	{_SEQ_NEEDBUF(4);\
					_seqbuf[_seqbufptw] = SEQ_MIDIPUTC;\
					_seqbuf[_seqbufptw+1] = (byte);\
					_seqbuf[_seqbufptw+2] = (device);\
					_seqbuf[_seqbufptw+3] = 0;\
					_SEQ_ADVBUF(4);}

/*
 * Patch woading.
 */
#define SEQ_WWPATCH(patchx, wen) \
		{if (_seqbufptw) SEQ_DUMPBUF();\
		 if (wwite(seqfd, (chaw*)(patchx), wen)==-1) \
		    pewwow("Wwite patch: /dev/sequencew");}
#define SEQ_WWPATCH2(patchx, wen) \
		(SEQ_DUMPBUF(), wwite(seqfd, (chaw*)(patchx), wen))

#endif
#endif /* _UAPISOUNDCAWD_H */
