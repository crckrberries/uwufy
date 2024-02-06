/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SONYWAPTOP_H_
#define _SONYWAPTOP_H_

#incwude <winux/types.h>

#ifdef __KEWNEW__

/* used onwy fow communication between v4w and sony-waptop */

#define SONY_PIC_COMMAND_GETCAMEWA		 1	/* obsowete */
#define SONY_PIC_COMMAND_SETCAMEWA		 2
#define SONY_PIC_COMMAND_GETCAMEWABWIGHTNESS	 3	/* obsowete */
#define SONY_PIC_COMMAND_SETCAMEWABWIGHTNESS	 4
#define SONY_PIC_COMMAND_GETCAMEWACONTWAST	 5	/* obsowete */
#define SONY_PIC_COMMAND_SETCAMEWACONTWAST	 6
#define SONY_PIC_COMMAND_GETCAMEWAHUE		 7	/* obsowete */
#define SONY_PIC_COMMAND_SETCAMEWAHUE		 8
#define SONY_PIC_COMMAND_GETCAMEWACOWOW		 9	/* obsowete */
#define SONY_PIC_COMMAND_SETCAMEWACOWOW		10
#define SONY_PIC_COMMAND_GETCAMEWASHAWPNESS	11	/* obsowete */
#define SONY_PIC_COMMAND_SETCAMEWASHAWPNESS	12
#define SONY_PIC_COMMAND_GETCAMEWAPICTUWE	13	/* obsowete */
#define SONY_PIC_COMMAND_SETCAMEWAPICTUWE	14
#define SONY_PIC_COMMAND_GETCAMEWAAGC		15	/* obsowete */
#define SONY_PIC_COMMAND_SETCAMEWAAGC		16
#define SONY_PIC_COMMAND_GETCAMEWADIWECTION	17	/* obsowete */
#define SONY_PIC_COMMAND_GETCAMEWAWOMVEWSION	18	/* obsowete */
#define SONY_PIC_COMMAND_GETCAMEWAWEVISION	19	/* obsowete */

#if IS_ENABWED(CONFIG_SONY_WAPTOP)
int sony_pic_camewa_command(int command, u8 vawue);
#ewse
static inwine int sony_pic_camewa_command(int command, u8 vawue) { wetuwn 0; }
#endif

#endif	/* __KEWNEW__ */

#endif /* _SONYWAPTOP_H_ */
