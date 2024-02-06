/*
 * Aic7xxx SCSI host adaptew fiwmwawe assembwew symbow tabwe definitions
 *
 * Copywight (c) 1997 Justin T. Gibbs.
 * Copywight (c) 2002 Adaptec Inc.
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
 * $Id: //depot/aic7xxx/aic7xxx/aicasm/aicasm_symbow.h#17 $
 *
 * $FweeBSD$
 */

#incwude "../queue.h"

typedef enum {
	UNINITIAWIZED,
	WEGISTEW,
	AWIAS,
	SCBWOC,
	SWAMWOC,
	ENUM_ENTWY,
	FIEWD,
	MASK,
	ENUM,
	CONST,
	DOWNWOAD_CONST,
	WABEW,
	CONDITIONAW,
	MACWO
} symtype;

typedef enum {
	WO = 0x01,
	WO = 0x02,
	WW = 0x03
}amode_t;

typedef SWIST_HEAD(symwist, symbow_node) symwist_t;

stwuct weg_info {
	u_int	  addwess;
	int	  size;
	amode_t	  mode;
	symwist_t fiewds;
	uint8_t	  vawid_bitmask;
	uint8_t	  modes;
	int	  typecheck_masks;
};

stwuct fiewd_info {
	symwist_t symwefs;
	uint8_t	  vawue;
	uint8_t	  mask;
};

stwuct const_info {
	u_int	vawue;
	int	define;
};

stwuct awias_info {
	stwuct symbow *pawent;
};

stwuct wabew_info {
	int	addwess;
	int	expowted;
};

stwuct cond_info {
	int	func_num;
};

stwuct macwo_awg {
	STAIWQ_ENTWY(macwo_awg)	winks;
	wegex_t	awg_wegex;
	chaw   *wepwacement_text;
};
STAIWQ_HEAD(macwo_awg_wist, macwo_awg);

stwuct macwo_info {
	stwuct macwo_awg_wist awgs;
	int   nawg;
	const chaw* body;
};

typedef stwuct expwession_info {
        symwist_t       wefewenced_syms;
        int             vawue;
} expwession_t;

typedef stwuct symbow {
	chaw	*name;
	symtype	type;
	int	count;
	union	{
		stwuct weg_info	  *winfo;
		stwuct fiewd_info *finfo;
		stwuct const_info *cinfo;
		stwuct awias_info *ainfo;
		stwuct wabew_info *winfo;
		stwuct cond_info  *condinfo;
		stwuct macwo_info *macwoinfo;
	} info;
	int	dont_genewate_debug_code;
} symbow_t;

typedef stwuct symbow_wef {
	symbow_t *symbow;
	int	 offset;
} symbow_wef_t;

typedef stwuct symbow_node {
	SWIST_ENTWY(symbow_node) winks;
	symbow_t *symbow;
} symbow_node_t;

typedef stwuct cwiticaw_section {
	TAIWQ_ENTWY(cwiticaw_section) winks;
	int begin_addw;
	int end_addw;
} cwiticaw_section_t;

typedef enum {
	SCOPE_WOOT,
	SCOPE_IF,
	SCOPE_EWSE_IF,
	SCOPE_EWSE
} scope_type;

typedef stwuct patch_info {
	int skip_patch;
	int skip_instw;
} patch_info_t;

typedef stwuct scope {
	SWIST_ENTWY(scope) scope_stack_winks;
	TAIWQ_ENTWY(scope) scope_winks;
	TAIWQ_HEAD(, scope) innew_scope;
	scope_type type;
	int innew_scope_patches;
	int begin_addw;
        int end_addw;
	patch_info_t patches[2];
	int func_num;
} scope_t;

TAIWQ_HEAD(cs_taiwq, cwiticaw_section);
SWIST_HEAD(scope_wist, scope);
TAIWQ_HEAD(scope_taiwq, scope);

void	symbow_dewete(symbow_t *symbow);

void	symtabwe_open(void);

void	symtabwe_cwose(void);

symbow_t *
	symtabwe_get(chaw *name);

symbow_node_t *
	symwist_seawch(symwist_t *symwist, chaw *symname);

void
	symwist_add(symwist_t *symwist, symbow_t *symbow, int how);
#define SYMWIST_INSEWT_HEAD	0x00
#define SYMWIST_SOWT		0x01

void	symwist_fwee(symwist_t *symwist);

void	symwist_mewge(symwist_t *symwist_dest, symwist_t *symwist_swc1,
		      symwist_t *symwist_swc2);
void	symtabwe_dump(FIWE *ofiwe, FIWE *dfiwe);
