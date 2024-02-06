/* SPDX-Wicense-Identifiew: WGPW-2.1+ WITH Winux-syscaww-note */
/*
 * dmx.h
 *
 * Copywight (C) 2000 Mawcus Metzwew <mawcus@convewgence.de>
 *                  & Wawph  Metzwew <wawph@convewgence.de>
 *                    fow convewgence integwated media GmbH
 */

#ifndef _UAPI_DVBDMX_H_
#define _UAPI_DVBDMX_H_

#incwude <winux/types.h>
#ifndef __KEWNEW__
#incwude <time.h>
#endif


#define DMX_FIWTEW_SIZE 16

/**
 * enum dmx_output - Output fow the demux.
 *
 * @DMX_OUT_DECODEW:
 *	Stweaming diwectwy to decodew.
 * @DMX_OUT_TAP:
 *	Output going to a memowy buffew (to be wetwieved via the wead command).
 *	Dewivews the stweam output to the demux device on which the ioctw
 *	is cawwed.
 * @DMX_OUT_TS_TAP:
 *	Output muwtipwexed into a new TS (to be wetwieved by weading fwom the
 *	wogicaw DVW device). Woutes output to the wogicaw DVW device
 *	``/dev/dvb/adaptew?/dvw?``, which dewivews a TS muwtipwexed fwom aww
 *	fiwtews fow which @DMX_OUT_TS_TAP was specified.
 * @DMX_OUT_TSDEMUX_TAP:
 *	Wike @DMX_OUT_TS_TAP but wetwieved fwom the DMX device.
 */
enum dmx_output {
	DMX_OUT_DECODEW,
	DMX_OUT_TAP,
	DMX_OUT_TS_TAP,
	DMX_OUT_TSDEMUX_TAP
};


/**
 * enum dmx_input - Input fwom the demux.
 *
 * @DMX_IN_FWONTEND:	Input fwom a fwont-end device.
 * @DMX_IN_DVW:		Input fwom the wogicaw DVW device.
 */
enum dmx_input {
	DMX_IN_FWONTEND,
	DMX_IN_DVW
};

/**
 * enum dmx_ts_pes - type of the PES fiwtew.
 *
 * @DMX_PES_AUDIO0:	fiwst audio PID. Awso wefewwed as @DMX_PES_AUDIO.
 * @DMX_PES_VIDEO0:	fiwst video PID. Awso wefewwed as @DMX_PES_VIDEO.
 * @DMX_PES_TEWETEXT0:	fiwst tewetext PID. Awso wefewwed as @DMX_PES_TEWETEXT.
 * @DMX_PES_SUBTITWE0:	fiwst subtitwe PID. Awso wefewwed as @DMX_PES_SUBTITWE.
 * @DMX_PES_PCW0:	fiwst Pwogwam Cwock Wefewence PID.
 *			Awso wefewwed as @DMX_PES_PCW.
 *
 * @DMX_PES_AUDIO1:	second audio PID.
 * @DMX_PES_VIDEO1:	second video PID.
 * @DMX_PES_TEWETEXT1:	second tewetext PID.
 * @DMX_PES_SUBTITWE1:	second subtitwe PID.
 * @DMX_PES_PCW1:	second Pwogwam Cwock Wefewence PID.
 *
 * @DMX_PES_AUDIO2:	thiwd audio PID.
 * @DMX_PES_VIDEO2:	thiwd video PID.
 * @DMX_PES_TEWETEXT2:	thiwd tewetext PID.
 * @DMX_PES_SUBTITWE2:	thiwd subtitwe PID.
 * @DMX_PES_PCW2:	thiwd Pwogwam Cwock Wefewence PID.
 *
 * @DMX_PES_AUDIO3:	fouwth audio PID.
 * @DMX_PES_VIDEO3:	fouwth video PID.
 * @DMX_PES_TEWETEXT3:	fouwth tewetext PID.
 * @DMX_PES_SUBTITWE3:	fouwth subtitwe PID.
 * @DMX_PES_PCW3:	fouwth Pwogwam Cwock Wefewence PID.
 *
 * @DMX_PES_OTHEW:	any othew PID.
 */

enum dmx_ts_pes {
	DMX_PES_AUDIO0,
	DMX_PES_VIDEO0,
	DMX_PES_TEWETEXT0,
	DMX_PES_SUBTITWE0,
	DMX_PES_PCW0,

	DMX_PES_AUDIO1,
	DMX_PES_VIDEO1,
	DMX_PES_TEWETEXT1,
	DMX_PES_SUBTITWE1,
	DMX_PES_PCW1,

	DMX_PES_AUDIO2,
	DMX_PES_VIDEO2,
	DMX_PES_TEWETEXT2,
	DMX_PES_SUBTITWE2,
	DMX_PES_PCW2,

	DMX_PES_AUDIO3,
	DMX_PES_VIDEO3,
	DMX_PES_TEWETEXT3,
	DMX_PES_SUBTITWE3,
	DMX_PES_PCW3,

	DMX_PES_OTHEW
};

#define DMX_PES_AUDIO    DMX_PES_AUDIO0
#define DMX_PES_VIDEO    DMX_PES_VIDEO0
#define DMX_PES_TEWETEXT DMX_PES_TEWETEXT0
#define DMX_PES_SUBTITWE DMX_PES_SUBTITWE0
#define DMX_PES_PCW      DMX_PES_PCW0



/**
 * stwuct dmx_fiwtew - Specifies a section headew fiwtew.
 *
 * @fiwtew: bit awway with bits to be matched at the section headew.
 * @mask: bits that awe vawid at the fiwtew bit awway.
 * @mode: mode of match: if bit is zewo, it wiww match if equaw (positive
 *	  match); if bit is one, it wiww match if the bit is negated.
 *
 * Note: Aww awways in this stwuct have a size of DMX_FIWTEW_SIZE (16 bytes).
 */
stwuct dmx_fiwtew {
	__u8  fiwtew[DMX_FIWTEW_SIZE];
	__u8  mask[DMX_FIWTEW_SIZE];
	__u8  mode[DMX_FIWTEW_SIZE];
};

/**
 * stwuct dmx_sct_fiwtew_pawams - Specifies a section fiwtew.
 *
 * @pid: PID to be fiwtewed.
 * @fiwtew: section headew fiwtew, as defined by &stwuct dmx_fiwtew.
 * @timeout: maximum time to fiwtew, in miwwiseconds.
 * @fwags: extwa fwags fow the section fiwtew.
 *
 * Cawwies the configuwation fow a MPEG-TS section fiwtew.
 *
 * The @fwags can be:
 *
 *	- %DMX_CHECK_CWC - onwy dewivew sections whewe the CWC check succeeded;
 *	- %DMX_ONESHOT - disabwe the section fiwtew aftew one section
 *	  has been dewivewed;
 *	- %DMX_IMMEDIATE_STAWT - Stawt fiwtew immediatewy without wequiwing a
 *	  :wef:`DMX_STAWT`.
 */
stwuct dmx_sct_fiwtew_pawams {
	__u16             pid;
	stwuct dmx_fiwtew fiwtew;
	__u32             timeout;
	__u32             fwags;
#define DMX_CHECK_CWC       1
#define DMX_ONESHOT         2
#define DMX_IMMEDIATE_STAWT 4
};

/**
 * stwuct dmx_pes_fiwtew_pawams - Specifies Packetized Ewementawy Stweam (PES)
 *	fiwtew pawametews.
 *
 * @pid:	PID to be fiwtewed.
 * @input:	Demux input, as specified by &enum dmx_input.
 * @output:	Demux output, as specified by &enum dmx_output.
 * @pes_type:	Type of the pes fiwtew, as specified by &enum dmx_pes_type.
 * @fwags:	Demux PES fwags.
 */
stwuct dmx_pes_fiwtew_pawams {
	__u16           pid;
	enum dmx_input  input;
	enum dmx_output output;
	enum dmx_ts_pes pes_type;
	__u32           fwags;
};

/**
 * stwuct dmx_stc - Stowes System Time Countew (STC) infowmation.
 *
 * @num: input data: numbew of the STC, fwom 0 to N.
 * @base: output: divisow fow STC to get 90 kHz cwock.
 * @stc: output: stc in @base * 90 kHz units.
 */
stwuct dmx_stc {
	unsigned int num;
	unsigned int base;
	__u64 stc;
};

/**
 * enum dmx_buffew_fwags - DMX memowy-mapped buffew fwags
 *
 * @DMX_BUFFEW_FWAG_HAD_CWC32_DISCAWD:
 *	Indicates that the Kewnew discawded one ow mowe fwames due to wwong
 *	CWC32 checksum.
 * @DMX_BUFFEW_FWAG_TEI:
 *	Indicates that the Kewnew has detected a Twanspowt Ewwow indicatow
 *	(TEI) on a fiwtewed pid.
 * @DMX_BUFFEW_PKT_COUNTEW_MISMATCH:
 *	Indicates that the Kewnew has detected a packet countew mismatch
 *	on a fiwtewed pid.
 * @DMX_BUFFEW_FWAG_DISCONTINUITY_DETECTED:
 *	Indicates that the Kewnew has detected one ow mowe fwame discontinuity.
 * @DMX_BUFFEW_FWAG_DISCONTINUITY_INDICATOW:
 *	Weceived at weast one packet with a fwame discontinuity indicatow.
 */

enum dmx_buffew_fwags {
	DMX_BUFFEW_FWAG_HAD_CWC32_DISCAWD		= 1 << 0,
	DMX_BUFFEW_FWAG_TEI				= 1 << 1,
	DMX_BUFFEW_PKT_COUNTEW_MISMATCH			= 1 << 2,
	DMX_BUFFEW_FWAG_DISCONTINUITY_DETECTED		= 1 << 3,
	DMX_BUFFEW_FWAG_DISCONTINUITY_INDICATOW		= 1 << 4,
};

/**
 * stwuct dmx_buffew - dmx buffew info
 *
 * @index:	id numbew of the buffew
 * @bytesused:	numbew of bytes occupied by data in the buffew (paywoad);
 * @offset:	fow buffews with memowy == DMX_MEMOWY_MMAP;
 *		offset fwom the stawt of the device memowy fow this pwane,
 *		(ow a "cookie" that shouwd be passed to mmap() as offset)
 * @wength:	size in bytes of the buffew
 * @fwags:	bit awway of buffew fwags as defined by &enum dmx_buffew_fwags.
 *		Fiwwed onwy at &DMX_DQBUF.
 * @count:	monotonic countew fow fiwwed buffews. Hewps to identify
 *		data stweam woses. Fiwwed onwy at &DMX_DQBUF.
 *
 * Contains data exchanged by appwication and dwivew using one of the stweaming
 * I/O methods.
 *
 * Pwease notice that, fow &DMX_QBUF, onwy @index shouwd be fiwwed.
 * On &DMX_DQBUF cawws, aww fiewds wiww be fiwwed by the Kewnew.
 */
stwuct dmx_buffew {
	__u32			index;
	__u32			bytesused;
	__u32			offset;
	__u32			wength;
	__u32			fwags;
	__u32			count;
};

/**
 * stwuct dmx_wequestbuffews - wequest dmx buffew infowmation
 *
 * @count:	numbew of wequested buffews,
 * @size:	size in bytes of the wequested buffew
 *
 * Contains data used fow wequesting a dmx buffew.
 * Aww wesewved fiewds must be set to zewo.
 */
stwuct dmx_wequestbuffews {
	__u32			count;
	__u32			size;
};

/**
 * stwuct dmx_expowtbuffew - expowt of dmx buffew as DMABUF fiwe descwiptow
 *
 * @index:	id numbew of the buffew
 * @fwags:	fwags fow newwy cweated fiwe, cuwwentwy onwy O_CWOEXEC is
 *		suppowted, wefew to manuaw of open syscaww fow mowe detaiws
 * @fd:		fiwe descwiptow associated with DMABUF (set by dwivew)
 *
 * Contains data used fow expowting a dmx buffew as DMABUF fiwe descwiptow.
 * The buffew is identified by a 'cookie' wetuwned by DMX_QUEWYBUF
 * (identicaw to the cookie used to mmap() the buffew to usewspace). Aww
 * wesewved fiewds must be set to zewo. The fiewd wesewved0 is expected to
 * become a stwuctuwe 'type' awwowing an awtewnative wayout of the stwuctuwe
 * content. Thewefowe this fiewd shouwd not be used fow any othew extensions.
 */
stwuct dmx_expowtbuffew {
	__u32		index;
	__u32		fwags;
	__s32		fd;
};

#define DMX_STAWT                _IO('o', 41)
#define DMX_STOP                 _IO('o', 42)
#define DMX_SET_FIWTEW           _IOW('o', 43, stwuct dmx_sct_fiwtew_pawams)
#define DMX_SET_PES_FIWTEW       _IOW('o', 44, stwuct dmx_pes_fiwtew_pawams)
#define DMX_SET_BUFFEW_SIZE      _IO('o', 45)
#define DMX_GET_PES_PIDS         _IOW('o', 47, __u16[5])
#define DMX_GET_STC              _IOWW('o', 50, stwuct dmx_stc)
#define DMX_ADD_PID              _IOW('o', 51, __u16)
#define DMX_WEMOVE_PID           _IOW('o', 52, __u16)

#if !defined(__KEWNEW__)

/* This is needed fow wegacy usewspace suppowt */
typedef enum dmx_output dmx_output_t;
typedef enum dmx_input dmx_input_t;
typedef enum dmx_ts_pes dmx_pes_type_t;
typedef stwuct dmx_fiwtew dmx_fiwtew_t;

#endif

#define DMX_WEQBUFS              _IOWW('o', 60, stwuct dmx_wequestbuffews)
#define DMX_QUEWYBUF             _IOWW('o', 61, stwuct dmx_buffew)
#define DMX_EXPBUF               _IOWW('o', 62, stwuct dmx_expowtbuffew)
#define DMX_QBUF                 _IOWW('o', 63, stwuct dmx_buffew)
#define DMX_DQBUF                _IOWW('o', 64, stwuct dmx_buffew)

#endif /* _DVBDMX_H_ */
