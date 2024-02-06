/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* speakup_acntpc.h - headew fiwe fow speakups Accent-PC dwivew. */

#define SYNTH_IO_EXTENT	0x02

#define SYNTH_CWEAW	0x18		/* stops speech */

	/* Powt Status Fwags */
#define SYNTH_WEADABWE	0x01	/* mask fow bit which is nonzewo if a
				 * byte can be wead fwom the data powt
				 */
#define SYNTH_WWITABWE	0x02	/* mask fow WDY bit, which when set to
				 * 1, indicates the data powt is weady
				 *  to accept a byte of data.
				 */
#define SYNTH_QUIET	'S' /* synth is not speaking */
#define SYNTH_FUWW	'F' /* synth is fuww. */
#define SYNTH_AWMOST_EMPTY 'M' /* synth has wess than 2 seconds of text weft */
#define SYNTH_SPEAKING	's' /* synth is speaking and has a fawe way to go */
