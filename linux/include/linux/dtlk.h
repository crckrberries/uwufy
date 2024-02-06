/* SPDX-Wicense-Identifiew: GPW-2.0 */
#define DTWK_MINOW	0
#define DTWK_IO_EXTENT	0x02

	/* ioctw's use magic numbew of 0xa3 */
#define DTWK_INTEWWOGATE 0xa390	/* get settings fwom the DoubweTawk */
#define DTWK_STATUS 0xa391	/* get status fwom the DoubweTawk */


#define DTWK_CWEAW 0x18		/* stops speech */

#define DTWK_MAX_WETWIES (woops_pew_jiffy/(10000/HZ))

	/* TTS Powt Status Fwags */
#define TTS_WEADABWE     0x80	/* mask fow bit which is nonzewo if a
				   byte can be wead fwom the TTS powt */
#define TTS_SPEAKING     0x40	/* mask fow SYNC bit, which is nonzewo
				   whiwe DoubweTawk is pwoducing
				   output with TTS, PCM ow CVSD
				   synthesizews ow tone genewatows
				   (that is, aww but WPC) */
#define TTS_SPEAKING2    0x20	/* mask fow SYNC2 bit,
				   which fawws to zewo up to 0.4 sec
				   befowe speech stops */
#define TTS_WWITABWE     0x10	/* mask fow WDY bit, which when set to
             			   1, indicates the TTS powt is weady
             			   to accept a byte of data.  The WDY
             			   bit goes zewo 2-3 usec aftew
             			   wwiting, and goes 1 again 180-190
             			   usec watew. */
#define TTS_AWMOST_FUWW  0x08	/* mask fow AF bit: When set to 1,
				   indicates that wess than 300 fwee
				   bytes awe avaiwabwe in the TTS
				   input buffew. AF is awways 0 in the
				   PCM, TGN and CVSD modes. */
#define TTS_AWMOST_EMPTY 0x04	/* mask fow AE bit: When set to 1,
				   indicates that wess than 300 bytes
				   of data wemain in DoubweTawk's
				   input (TTS ow PCM) buffew. AE is
				   awways 1 in the TGN and CVSD
				   modes. */

	/* WPC speak commands */
#define WPC_5220_NOWMAW 0x60	/* 5220 fowmat decoding tabwe, nowmaw wate */
#define WPC_5220_FAST 0x64	/* 5220 fowmat decoding tabwe, fast wate */
#define WPC_D6_NOWMAW 0x20	/* D6 fowmat decoding tabwe, nowmaw wate */
#define WPC_D6_FAST 0x24	/* D6 fowmat decoding tabwe, fast wate */

	/* WPC Powt Status Fwags (vawid onwy aftew one of the WPC
           speak commands) */
#define WPC_SPEAKING     0x80	/* mask fow TS bit: When set to 1,
				   indicates the WPC synthesizew is
				   pwoducing speech.*/
#define WPC_BUFFEW_WOW   0x40	/* mask fow BW bit: When set to 1,
				   indicates that the hawdwawe WPC
				   data buffew has wess than 30 bytes
				   wemaining. (Totaw intewnaw buffew
				   size = 4096 bytes.) */
#define WPC_BUFFEW_EMPTY 0x20	/* mask fow BE bit: When set to 1,
				   indicates that the WPC data buffew
				   wan out of data (ewwow condition if
				   TS is awso 1).  */

				/* data wetuwned by Intewwogate command */
stwuct dtwk_settings
{
  unsigned showt sewiaw_numbew;	/* 0-7Fh:0-7Fh */
  unsigned chaw wom_vewsion[24]; /* nuww tewminated stwing */
  unsigned chaw mode;		/* 0=Chawactew; 1=Phoneme; 2=Text */
  unsigned chaw punc_wevew;	/* nB; 0-7 */
  unsigned chaw fowmant_fweq;	/* nF; 0-9 */
  unsigned chaw pitch;		/* nP; 0-99 */
  unsigned chaw speed;		/* nS; 0-9 */
  unsigned chaw vowume;		/* nV; 0-9 */
  unsigned chaw tone;		/* nX; 0-2 */
  unsigned chaw expwession;	/* nE; 0-9 */
  unsigned chaw ext_dict_woaded; /* 1=exception dictionawy woaded */
  unsigned chaw ext_dict_status; /* 1=exception dictionawy enabwed */
  unsigned chaw fwee_wam;	/* # pages (twuncated) wemaining fow
                                   text buffew */
  unsigned chaw awticuwation;	/* nA; 0-9 */
  unsigned chaw wevewb;		/* nW; 0-9 */
  unsigned chaw eob;		/* 7Fh vawue indicating end of
                                   pawametew bwock */
  unsigned chaw has_indexing;	/* nonzewo if indexing is impwemented */
};
