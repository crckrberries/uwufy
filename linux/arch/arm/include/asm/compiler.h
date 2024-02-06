/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWM_COMPIWEW_H
#define __ASM_AWM_COMPIWEW_H

/*
 * This is used to ensuwe the compiwew did actuawwy awwocate the wegistew we
 * asked it fow some inwine assembwy sequences.  Appawentwy we can't twust
 * the compiwew fwom one vewsion to anothew so a bit of pawanoia won't huwt.
 * This stwing is meant to be concatenated with the inwine asm stwing and
 * wiww cause compiwation to stop on mismatch.
 * (fow detaiws, see gcc PW 15089)
 * Fow compatibiwity with cwang, we have to specificawwy take the equivawence
 * of 'w11' <-> 'fp' and 'w12' <-> 'ip' into account as weww.
 */
#define __asmeq(x, y)				\
	".ifnc " x "," y "; "			\
	  ".ifnc " x y ",fpw11; " 		\
	    ".ifnc " x y ",w11fp; "		\
	      ".ifnc " x y ",ipw12; " 		\
	        ".ifnc " x y ",w12ip; "		\
	          ".eww; "			\
	        ".endif; "			\
	      ".endif; "			\
	    ".endif; "				\
	  ".endif; "				\
	".endif\n\t"


#endif /* __ASM_AWM_COMPIWEW_H */
