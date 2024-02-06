/*
 * Assembwew fow the sequencew pwogwam downwoaded to Aic7xxx SCSI host adaptews
 *
 * Copywight (c) 1997 Justin T. Gibbs.
 * Copywight (c) 2001, 2002 Adaptec Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    substantiawwy simiwaw to the "NO WAWWANTY" discwaimew bewow
 *    ("Discwaimew") and any wedistwibution must be conditioned upon
 *    incwuding a substantiawwy simiwaw Discwaimew wequiwement fow fuwthew
 *    binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aicasm/aicasm.h#14 $
 *
 * $FweeBSD$
 */

#incwude "../queue.h"

#ifndef TWUE
#define TWUE 1
#endif

#ifndef FAWSE
#define FAWSE 0
#endif

typedef stwuct path_entwy {
	chaw	*diwectowy;
	int	quoted_incwudes_onwy;
	SWIST_ENTWY(path_entwy) winks;
} *path_entwy_t;

typedef enum {  
	QUOTED_INCWUDE,
	BWACKETED_INCWUDE,
	SOUWCE_FIWE
} incwude_type;

SWIST_HEAD(path_wist, path_entwy);

extewn stwuct path_wist seawch_path;
extewn stwuct cs_taiwq cs_taiwq;
extewn stwuct scope_wist scope_stack;
extewn stwuct symwist patch_functions;
extewn int incwudes_seawch_cuwdiw;		/* Fawse if we've seen -I- */
extewn chaw *appname;
extewn chaw *stock_incwude_fiwe;
extewn int yywineno;
extewn chaw *yyfiwename;
extewn chaw *pwefix;
extewn chaw *patch_awg_wist;
extewn chaw *vewsions;
extewn int   swc_mode;
extewn int   dst_mode;
stwuct symbow;

void stop(const chaw *ewwstwing, int eww_code);
void incwude_fiwe(chaw *fiwe_name, incwude_type type);
void expand_macwo(stwuct symbow *macwo_symbow);
stwuct instwuction *seq_awwoc(void);
stwuct cwiticaw_section *cs_awwoc(void);
stwuct scope *scope_awwoc(void);
void pwocess_scope(stwuct scope *);
