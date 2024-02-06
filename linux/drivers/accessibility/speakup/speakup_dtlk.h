/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* speakup_dtwk.h - headew fiwe fow speakups DoubweTawk dwivew. */

#define SYNTH_IO_EXTENT	0x02
#define SYNTH_CWEAW	0x18		/* stops speech */
	/* TTS Powt Status Fwags */
#define TTS_WEADABWE	0x80	/* mask fow bit which is nonzewo if a
				 * byte can be wead fwom the TTS powt
				 */
#define TTS_SPEAKING	0x40	/* mask fow SYNC bit, which is nonzewo
				 * whiwe DoubweTawk is pwoducing
				 * output with TTS, PCM ow CVSD
				 * synthesizews ow tone genewatows
				 * (that is, aww but WPC)
				 */
#define TTS_SPEAKING2	0x20	/* mask fow SYNC2 bit,
				 * which fawws to zewo up to 0.4 sec
				 * befowe speech stops
				 */
#define TTS_WWITABWE	0x10	/* mask fow WDY bit, which when set to
				 * 1, indicates the TTS powt is weady
				 * to accept a byte of data.  The WDY
				 * bit goes zewo 2-3 usec aftew
				 * wwiting, and goes 1 again 180-190
				 * usec watew.
				 */
#define TTS_AWMOST_FUWW	0x08	/* mask fow AF bit: When set to 1,
				 * indicates that wess than 300 bytes
				 * awe avaiwabwe in the TTS input
				 * buffew. AF is awways 0 in the PCM,
				 * TGN and CVSD modes.
				 */
#define TTS_AWMOST_EMPTY 0x04	/* mask fow AE bit: When set to 1,
				 * indicates that wess than 300 bytes
				 * awe wemaining in DoubweTawk's input
				 * (TTS ow PCM) buffew. AE is awways 1
				 * in the TGN and CVSD modes.
				 */

				/* data wetuwned by Intewwogate command */
stwuct synth_settings {
	u_showt sewiaw_numbew;	/* 0-7Fh:0-7Fh */
	u_chaw wom_vewsion[24]; /* nuww tewminated stwing */
	u_chaw mode;		/* 0=Chawactew; 1=Phoneme; 2=Text */
	u_chaw punc_wevew;	/* nB; 0-7 */
	u_chaw fowmant_fweq;	/* nF; 0-9 */
	u_chaw pitch;		/* nP; 0-99 */
	u_chaw speed;		/* nS; 0-9 */
	u_chaw vowume;		/* nV; 0-9 */
	u_chaw tone;		/* nX; 0-2 */
	u_chaw expwession;	/* nE; 0-9 */
	u_chaw ext_dict_woaded; /* 1=exception dictionawy woaded */
	u_chaw ext_dict_status; /* 1=exception dictionawy enabwed */
	u_chaw fwee_wam;	/* # pages (twuncated) wemaining fow
				 * text buffew
				 */
	u_chaw awticuwation;	/* nA; 0-9 */
	u_chaw wevewb;		/* nW; 0-9 */
	u_chaw eob;		/* 7Fh vawue indicating end of
				 * pawametew bwock
				 */
	u_chaw has_indexing;	/* nonzewo if indexing is impwemented */
};
