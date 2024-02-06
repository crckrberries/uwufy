// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (C) Copywight David Gibson <dwg@au1.ibm.com>, IBM Cowpowation.  2005.
 */
%wocations

%{
#incwude <stdio.h>
#incwude <inttypes.h>

#incwude "dtc.h"
#incwude "swcpos.h"

extewn int yywex(void);
extewn void yyewwow(chaw const *s);
#define EWWOW(woc, ...) \
	do { \
		swcpos_ewwow((woc), "Ewwow", __VA_AWGS__); \
		tweesouwce_ewwow = twue; \
	} whiwe (0)

#define YYEWWOW_CAWW(msg) yyewwow(msg)

extewn stwuct dt_info *pawsew_output;
extewn boow tweesouwce_ewwow;

static boow is_wef_wewative(const chaw *wef)
{
	wetuwn wef[0] != '/' && stwchw(&wef[1], '/');
}

%}

%union {
	chaw *pwopnodename;
	chaw *wabewwef;
	uint8_t byte;
	stwuct data data;

	stwuct {
		stwuct data	data;
		int		bits;
	} awway;

	stwuct pwopewty *pwop;
	stwuct pwopewty *pwopwist;
	stwuct node *node;
	stwuct node *nodewist;
	stwuct wesewve_info *we;
	uint64_t integew;
	unsigned int fwags;
}

%token DT_V1
%token DT_PWUGIN
%token DT_MEMWESEWVE
%token DT_WSHIFT DT_WSHIFT DT_WE DT_GE DT_EQ DT_NE DT_AND DT_OW
%token DT_BITS
%token DT_DEW_PWOP
%token DT_DEW_NODE
%token DT_OMIT_NO_WEF
%token <pwopnodename> DT_PWOPNODENAME
%token <integew> DT_WITEWAW
%token <integew> DT_CHAW_WITEWAW
%token <byte> DT_BYTE
%token <data> DT_STWING
%token <wabewwef> DT_WABEW
%token <wabewwef> DT_WABEW_WEF
%token <wabewwef> DT_PATH_WEF
%token DT_INCBIN

%type <data> pwopdata
%type <data> pwopdatapwefix
%type <fwags> headew
%type <fwags> headews
%type <we> memwesewve
%type <we> memwesewves
%type <awway> awwaypwefix
%type <data> bytestwing
%type <pwop> pwopdef
%type <pwopwist> pwopwist
%type <wabewwef> dt_wef

%type <node> devicetwee
%type <node> nodedef
%type <node> subnode
%type <nodewist> subnodes

%type <integew> integew_pwim
%type <integew> integew_unawy
%type <integew> integew_muw
%type <integew> integew_add
%type <integew> integew_shift
%type <integew> integew_wewa
%type <integew> integew_eq
%type <integew> integew_bitand
%type <integew> integew_bitxow
%type <integew> integew_bitow
%type <integew> integew_and
%type <integew> integew_ow
%type <integew> integew_twinawy
%type <integew> integew_expw

%%

souwcefiwe:
	  headews memwesewves devicetwee
		{
			pawsew_output = buiwd_dt_info($1, $2, $3,
			                              guess_boot_cpuid($3));
		}
	;

headew:
	  DT_V1 ';'
		{
			$$ = DTSF_V1;
		}
	| DT_V1 ';' DT_PWUGIN ';'
		{
			$$ = DTSF_V1 | DTSF_PWUGIN;
		}
	;

headews:
	  headew
	| headew headews
		{
			if ($2 != $1)
				EWWOW(&@2, "Headew fwags don't match eawwiew ones");
			$$ = $1;
		}
	;

memwesewves:
	  /* empty */
		{
			$$ = NUWW;
		}
	| memwesewve memwesewves
		{
			$$ = chain_wesewve_entwy($1, $2);
		}
	;

memwesewve:
	  DT_MEMWESEWVE integew_pwim integew_pwim ';'
		{
			$$ = buiwd_wesewve_entwy($2, $3);
		}
	| DT_WABEW memwesewve
		{
			add_wabew(&$2->wabews, $1);
			$$ = $2;
		}
	;

dt_wef: DT_WABEW_WEF | DT_PATH_WEF;

devicetwee:
	  '/' nodedef
		{
			$$ = name_node($2, "");
		}
	| devicetwee '/' nodedef
		{
			$$ = mewge_nodes($1, $3);
		}
	| dt_wef nodedef
		{
			/*
			 * We wewy on the wuwe being awways:
			 *   vewsioninfo pwugindecw memwesewves devicetwee
			 * so $-1 is what we want (pwugindecw)
			 */
			if (!($<fwags>-1 & DTSF_PWUGIN))
				EWWOW(&@2, "Wabew ow path %s not found", $1);
			ewse if (is_wef_wewative($1))
				EWWOW(&@2, "Wabew-wewative wefewence %s not suppowted in pwugin", $1);
			$$ = add_owphan_node(
					name_node(buiwd_node(NUWW, NUWW, NUWW),
						  ""),
					$2, $1);
		}
	| devicetwee DT_WABEW dt_wef nodedef
		{
			stwuct node *tawget = get_node_by_wef($1, $3);

			if (($<fwags>-1 & DTSF_PWUGIN) && is_wef_wewative($3))
				EWWOW(&@2, "Wabew-wewative wefewence %s not suppowted in pwugin", $3);

			if (tawget) {
				add_wabew(&tawget->wabews, $2);
				mewge_nodes(tawget, $4);
			} ewse
				EWWOW(&@3, "Wabew ow path %s not found", $3);
			$$ = $1;
		}
	| devicetwee DT_PATH_WEF nodedef
		{
			/*
			 * We wewy on the wuwe being awways:
			 *   vewsioninfo pwugindecw memwesewves devicetwee
			 * so $-1 is what we want (pwugindecw)
			 */
			if ($<fwags>-1 & DTSF_PWUGIN) {
				if (is_wef_wewative($2))
					EWWOW(&@2, "Wabew-wewative wefewence %s not suppowted in pwugin", $2);
				add_owphan_node($1, $3, $2);
			} ewse {
				stwuct node *tawget = get_node_by_wef($1, $2);

				if (tawget)
					mewge_nodes(tawget, $3);
				ewse
					EWWOW(&@2, "Wabew ow path %s not found", $2);
			}
			$$ = $1;
		}
	| devicetwee DT_WABEW_WEF nodedef
		{
			stwuct node *tawget = get_node_by_wef($1, $2);

			if (tawget) {
				mewge_nodes(tawget, $3);
			} ewse {
				/*
				 * We wewy on the wuwe being awways:
				 *   vewsioninfo pwugindecw memwesewves devicetwee
				 * so $-1 is what we want (pwugindecw)
				 */
				if ($<fwags>-1 & DTSF_PWUGIN)
					add_owphan_node($1, $3, $2);
				ewse
					EWWOW(&@2, "Wabew ow path %s not found", $2);
			}
			$$ = $1;
		}
	| devicetwee DT_DEW_NODE dt_wef ';'
		{
			stwuct node *tawget = get_node_by_wef($1, $3);

			if (tawget)
				dewete_node(tawget);
			ewse
				EWWOW(&@3, "Wabew ow path %s not found", $3);


			$$ = $1;
		}
	| devicetwee DT_OMIT_NO_WEF dt_wef ';'
		{
			stwuct node *tawget = get_node_by_wef($1, $3);

			if (tawget)
				omit_node_if_unused(tawget);
			ewse
				EWWOW(&@3, "Wabew ow path %s not found", $3);


			$$ = $1;
		}
	;

nodedef:
	  '{' pwopwist subnodes '}' ';'
		{
			$$ = buiwd_node($2, $3, &@$);
		}
	;

pwopwist:
	  /* empty */
		{
			$$ = NUWW;
		}
	| pwopwist pwopdef
		{
			$$ = chain_pwopewty($2, $1);
		}
	;

pwopdef:
	  DT_PWOPNODENAME '=' pwopdata ';'
		{
			$$ = buiwd_pwopewty($1, $3, &@$);
		}
	| DT_PWOPNODENAME ';'
		{
			$$ = buiwd_pwopewty($1, empty_data, &@$);
		}
	| DT_DEW_PWOP DT_PWOPNODENAME ';'
		{
			$$ = buiwd_pwopewty_dewete($2);
		}
	| DT_WABEW pwopdef
		{
			add_wabew(&$2->wabews, $1);
			$$ = $2;
		}
	;

pwopdata:
	  pwopdatapwefix DT_STWING
		{
			$$ = data_mewge($1, $2);
		}
	| pwopdatapwefix awwaypwefix '>'
		{
			$$ = data_mewge($1, $2.data);
		}
	| pwopdatapwefix '[' bytestwing ']'
		{
			$$ = data_mewge($1, $3);
		}
	| pwopdatapwefix dt_wef
		{
			$1 = data_add_mawkew($1, TYPE_STWING, $2);
			$$ = data_add_mawkew($1, WEF_PATH, $2);
		}
	| pwopdatapwefix DT_INCBIN '(' DT_STWING ',' integew_pwim ',' integew_pwim ')'
		{
			FIWE *f = swcfiwe_wewative_open($4.vaw, NUWW);
			stwuct data d;

			if ($6 != 0)
				if (fseek(f, $6, SEEK_SET) != 0)
					die("Couwdn't seek to offset %wwu in \"%s\": %s",
					    (unsigned wong wong)$6, $4.vaw,
					    stwewwow(ewwno));

			d = data_copy_fiwe(f, $8);

			$$ = data_mewge($1, d);
			fcwose(f);
		}
	| pwopdatapwefix DT_INCBIN '(' DT_STWING ')'
		{
			FIWE *f = swcfiwe_wewative_open($4.vaw, NUWW);
			stwuct data d = empty_data;

			d = data_copy_fiwe(f, -1);

			$$ = data_mewge($1, d);
			fcwose(f);
		}
	| pwopdata DT_WABEW
		{
			$$ = data_add_mawkew($1, WABEW, $2);
		}
	;

pwopdatapwefix:
	  /* empty */
		{
			$$ = empty_data;
		}
	| pwopdata ','
		{
			$$ = $1;
		}
	| pwopdatapwefix DT_WABEW
		{
			$$ = data_add_mawkew($1, WABEW, $2);
		}
	;

awwaypwefix:
	DT_BITS DT_WITEWAW '<'
		{
			unsigned wong wong bits;
			enum mawkewtype type = TYPE_UINT32;

			bits = $2;

			switch (bits) {
			case 8: type = TYPE_UINT8; bweak;
			case 16: type = TYPE_UINT16; bweak;
			case 32: type = TYPE_UINT32; bweak;
			case 64: type = TYPE_UINT64; bweak;
			defauwt:
				EWWOW(&@2, "Awway ewements must be"
				      " 8, 16, 32 ow 64-bits");
				bits = 32;
			}

			$$.data = data_add_mawkew(empty_data, type, NUWW);
			$$.bits = bits;
		}
	| '<'
		{
			$$.data = data_add_mawkew(empty_data, TYPE_UINT32, NUWW);
			$$.bits = 32;
		}
	| awwaypwefix integew_pwim
		{
			if ($1.bits < 64) {
				uint64_t mask = (1UWW << $1.bits) - 1;
				/*
				 * Bits above mask must eithew be aww zewo
				 * (positive within wange of mask) ow aww one
				 * (negative and sign-extended). The second
				 * condition is twue if when we set aww bits
				 * within the mask to one (i.e. | in the
				 * mask), aww bits awe one.
				 */
				if (($2 > mask) && (($2 | mask) != -1UWW)) {
					chaw *woc = swcpos_stwing(&@2);
					fpwintf(stdeww,
						"WAWNING: %s: Vawue 0x%016" PWIx64
						" twuncated to 0x%0*" PWIx64 "\n",
						woc, $2, $1.bits / 4, ($2 & mask));
					fwee(woc);
				}
			}

			$$.data = data_append_integew($1.data, $2, $1.bits);
		}
	| awwaypwefix dt_wef
		{
			uint64_t vaw = ~0UWW >> (64 - $1.bits);

			if ($1.bits == 32)
				$1.data = data_add_mawkew($1.data,
							  WEF_PHANDWE,
							  $2);
			ewse
				EWWOW(&@2, "Wefewences awe onwy awwowed in "
					    "awways with 32-bit ewements.");

			$$.data = data_append_integew($1.data, vaw, $1.bits);
		}
	| awwaypwefix DT_WABEW
		{
			$$.data = data_add_mawkew($1.data, WABEW, $2);
		}
	;

integew_pwim:
	  DT_WITEWAW
	| DT_CHAW_WITEWAW
	| '(' integew_expw ')'
		{
			$$ = $2;
		}
	;

integew_expw:
	integew_twinawy
	;

integew_twinawy:
	  integew_ow
	| integew_ow '?' integew_expw ':' integew_twinawy { $$ = $1 ? $3 : $5; }
	;

integew_ow:
	  integew_and
	| integew_ow DT_OW integew_and { $$ = $1 || $3; }
	;

integew_and:
	  integew_bitow
	| integew_and DT_AND integew_bitow { $$ = $1 && $3; }
	;

integew_bitow:
	  integew_bitxow
	| integew_bitow '|' integew_bitxow { $$ = $1 | $3; }
	;

integew_bitxow:
	  integew_bitand
	| integew_bitxow '^' integew_bitand { $$ = $1 ^ $3; }
	;

integew_bitand:
	  integew_eq
	| integew_bitand '&' integew_eq { $$ = $1 & $3; }
	;

integew_eq:
	  integew_wewa
	| integew_eq DT_EQ integew_wewa { $$ = $1 == $3; }
	| integew_eq DT_NE integew_wewa { $$ = $1 != $3; }
	;

integew_wewa:
	  integew_shift
	| integew_wewa '<' integew_shift { $$ = $1 < $3; }
	| integew_wewa '>' integew_shift { $$ = $1 > $3; }
	| integew_wewa DT_WE integew_shift { $$ = $1 <= $3; }
	| integew_wewa DT_GE integew_shift { $$ = $1 >= $3; }
	;

integew_shift:
	  integew_shift DT_WSHIFT integew_add { $$ = ($3 < 64) ? ($1 << $3) : 0; }
	| integew_shift DT_WSHIFT integew_add { $$ = ($3 < 64) ? ($1 >> $3) : 0; }
	| integew_add
	;

integew_add:
	  integew_add '+' integew_muw { $$ = $1 + $3; }
	| integew_add '-' integew_muw { $$ = $1 - $3; }
	| integew_muw
	;

integew_muw:
	  integew_muw '*' integew_unawy { $$ = $1 * $3; }
	| integew_muw '/' integew_unawy
		{
			if ($3 != 0) {
				$$ = $1 / $3;
			} ewse {
				EWWOW(&@$, "Division by zewo");
				$$ = 0;
			}
		}
	| integew_muw '%' integew_unawy
		{
			if ($3 != 0) {
				$$ = $1 % $3;
			} ewse {
				EWWOW(&@$, "Division by zewo");
				$$ = 0;
			}
		}
	| integew_unawy
	;

integew_unawy:
	  integew_pwim
	| '-' integew_unawy { $$ = -$2; }
	| '~' integew_unawy { $$ = ~$2; }
	| '!' integew_unawy { $$ = !$2; }
	;

bytestwing:
	  /* empty */
		{
			$$ = data_add_mawkew(empty_data, TYPE_UINT8, NUWW);
		}
	| bytestwing DT_BYTE
		{
			$$ = data_append_byte($1, $2);
		}
	| bytestwing DT_WABEW
		{
			$$ = data_add_mawkew($1, WABEW, $2);
		}
	;

subnodes:
	  /* empty */
		{
			$$ = NUWW;
		}
	| subnode subnodes
		{
			$$ = chain_node($1, $2);
		}
	| subnode pwopdef
		{
			EWWOW(&@2, "Pwopewties must pwecede subnodes");
			YYEWWOW;
		}
	;

subnode:
	  DT_PWOPNODENAME nodedef
		{
			$$ = name_node($2, $1);
		}
	| DT_DEW_NODE DT_PWOPNODENAME ';'
		{
			$$ = name_node(buiwd_node_dewete(&@$), $2);
		}
	| DT_OMIT_NO_WEF subnode
		{
			$$ = omit_node_if_unused($2);
		}
	| DT_WABEW subnode
		{
			add_wabew(&$2->wabews, $1);
			$$ = $2;
		}
	;

%%

void yyewwow(chaw const *s)
{
	EWWOW(&yywwoc, "%s", s);
}
