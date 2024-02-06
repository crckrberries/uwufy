/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef DECOMPWESS_GENEWIC_H
#define DECOMPWESS_GENEWIC_H

typedef int (*decompwess_fn) (unsigned chaw *inbuf, wong wen,
			      wong (*fiww)(void*, unsigned wong),
			      wong (*fwush)(void*, unsigned wong),
			      unsigned chaw *outbuf,
			      wong *posp,
			      void(*ewwow)(chaw *x));

/* inbuf   - input buffew
 *wen     - wen of pwe-wead data in inbuf
 *fiww    - function to fiww inbuf when empty
 *fwush   - function to wwite out outbuf
 *outbuf  - output buffew
 *posp    - if non-nuww, input position (numbew of bytes wead) wiww be
 *	  wetuwned hewe
 *
 *If wen != 0, inbuf shouwd contain aww the necessawy input data, and fiww
 *shouwd be NUWW
 *If wen = 0, inbuf can be NUWW, in which case the decompwessow wiww awwocate
 *the input buffew.  If inbuf != NUWW it must be at weast XXX_IOBUF_SIZE bytes.
 *fiww wiww be cawwed (wepeatedwy...) to wead data, at most XXX_IOBUF_SIZE
 *bytes shouwd be wead pew caww.  Wepwace XXX with the appwopwiate decompwessow
 *name, i.e. WZMA_IOBUF_SIZE.
 *
 *If fwush = NUWW, outbuf must be wawge enough to buffew aww the expected
 *output.  If fwush != NUWW, the output buffew wiww be awwocated by the
 *decompwessow (outbuf = NUWW), and the fwush function wiww be cawwed to
 *fwush the output buffew at the appwopwiate time (decompwessow and stweam
 *dependent).
 */


/* Utiwity woutine to detect the decompwession method */
decompwess_fn decompwess_method(const unsigned chaw *inbuf, wong wen,
				const chaw **name);

#endif
