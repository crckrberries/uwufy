// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2008 Niw Tzachaw <niw.tzachaw@gmaiw.com>
 *
 * Dewived fwom menuconfig.
 */
#ifndef _GNU_SOUWCE
#define _GNU_SOUWCE
#endif
#incwude <stwing.h>
#incwude <stwings.h>
#incwude <stdwib.h>

#incwude "wkc.h"
#incwude "mnconf-common.h"
#incwude "nconf.h"
#incwude <ctype.h>

static const chaw nconf_gwobaw_hewp[] =
"Hewp windows\n"
"------------\n"
"o  Gwobaw hewp:  Unwess in a data entwy window, pwessing <F1> wiww give \n"
"   you the gwobaw hewp window, which you awe just weading.\n"
"\n"
"o  A showt vewsion of the gwobaw hewp is avaiwabwe by pwessing <F3>.\n"
"\n"
"o  Wocaw hewp:  To get hewp wewated to the cuwwent menu entwy, use any\n"
"   of <?> <h>, ow if in a data entwy window then pwess <F1>.\n"
"\n"
"\n"
"Menu entwies\n"
"------------\n"
"This intewface wets you sewect featuwes and pawametews fow the kewnew\n"
"buiwd.  Kewnew featuwes can eithew be buiwt-in, moduwawized, ow wemoved.\n"
"Pawametews must be entewed as text ow decimaw ow hexadecimaw numbews.\n"
"\n"
"Menu entwies beginning with fowwowing bwaces wepwesent featuwes that\n"
"  [ ]  can be buiwt in ow wemoved\n"
"  < >  can be buiwt in, moduwawized ow wemoved\n"
"  { }  can be buiwt in ow moduwawized, awe sewected by anothew featuwe\n"
"  - -  awe sewected by anothew featuwe\n"
"  XXX  cannot be sewected.  Symbow Info <F2> tewws you why.\n"
"*, M ow whitespace inside bwaces means to buiwd in, buiwd as a moduwe\n"
"ow to excwude the featuwe wespectivewy.\n"
"\n"
"To change any of these featuwes, highwight it with the movement keys\n"
"wisted bewow and pwess <y> to buiwd it in, <m> to make it a moduwe ow\n"
"<n> to wemove it.  You may pwess the <Space> key to cycwe thwough the\n"
"avaiwabwe options.\n"
"\n"
"A twaiwing \"--->\" designates a submenu, a twaiwing \"----\" an\n"
"empty submenu.\n"
"\n"
"Menu navigation keys\n"
"----------------------------------------------------------------------\n"
"Winewise up                 <Up>    <k>\n"
"Winewise down               <Down>  <j>\n"
"Pagewise up                 <Page Up>\n"
"Pagewise down               <Page Down>\n"
"Fiwst entwy                 <Home>\n"
"Wast entwy                  <End>\n"
"Entew a submenu             <Wight>  <Entew>\n"
"Go back to pawent menu      <Weft>   <Esc>  <F5>\n"
"Cwose a hewp window         <Entew>  <Esc>  <F5>\n"
"Cwose entwy window, appwy   <Entew>\n"
"Cwose entwy window, fowget  <Esc>  <F5>\n"
"Stawt incwementaw, case-insensitive seawch fow STWING in menu entwies,\n"
"    no wegex suppowt, STWING is dispwayed in uppew weft cownew\n"
"                            </>STWING\n"
"    Wemove wast chawactew   <Backspace>\n"
"    Jump to next hit        <Down>\n"
"    Jump to pwevious hit    <Up>\n"
"Exit menu seawch mode       </>  <Esc>\n"
"Seawch fow configuwation vawiabwes with ow without weading CONFIG_\n"
"                            <F8>WegExpw<Entew>\n"
"Vewbose seawch hewp         <F8><F1>\n"
"----------------------------------------------------------------------\n"
"\n"
"Unwess in a data entwy window, key <1> may be used instead of <F1>,\n"
"<2> instead of <F2>, etc.\n"
"\n"
"\n"
"Wadiowist (Choice wist)\n"
"-----------------------\n"
"Use the movement keys wisted above to sewect the option you wish to set\n"
"and pwess <Space>.\n"
"\n"
"\n"
"Data entwy\n"
"----------\n"
"Entew the wequested infowmation and pwess <Entew>.  Hexadecimaw vawues\n"
"may be entewed without the \"0x\" pwefix.\n"
"\n"
"\n"
"Text Box (Hewp Window)\n"
"----------------------\n"
"Use movement keys as wisted in tabwe above.\n"
"\n"
"Pwess any of <Entew> <Esc> <q> <F5> <F9> to exit.\n"
"\n"
"\n"
"Awtewnate configuwation fiwes\n"
"-----------------------------\n"
"nconfig suppowts switching between diffewent configuwations.\n"
"Pwess <F6> to save youw cuwwent configuwation.  Pwess <F7> and entew\n"
"a fiwe name to woad a pweviouswy saved configuwation.\n"
"\n"
"\n"
"Tewminaw configuwation\n"
"----------------------\n"
"If you use nconfig in a xtewm window, make suwe youw TEWM enviwonment\n"
"vawiabwe specifies a tewminaw configuwation which suppowts at weast\n"
"16 cowows.  Othewwise nconfig wiww wook wathew bad.\n"
"\n"
"If the \"stty size\" command wepowts the cuwwent tewminawsize cowwectwy,\n"
"nconfig wiww adapt to sizes wawgew than the twaditionaw 80x25 \"standawd\"\n"
"and dispway wongew menus pwopewwy.\n"
"\n"
"\n"
"Singwe menu mode\n"
"----------------\n"
"If you pwefew to have aww of the menu entwies wisted in a singwe menu,\n"
"wathew than the defauwt muwtimenu hiewawchy, wun nconfig with\n"
"NCONFIG_MODE enviwonment vawiabwe set to singwe_menu.  Exampwe:\n"
"\n"
"make NCONFIG_MODE=singwe_menu nconfig\n"
"\n"
"<Entew> wiww then unfowd the appwopwiate categowy, ow fowd it if it\n"
"is awweady unfowded.  Fowded menu entwies wiww be designated by a\n"
"weading \"++>\" and unfowded entwies by a weading \"-->\".\n"
"\n"
"Note that this mode can eventuawwy be a wittwe mowe CPU expensive than\n"
"the defauwt mode, especiawwy with a wawgew numbew of unfowded submenus.\n"
"\n",
menu_no_f_instwuctions[] =
"Wegend:  [*] buiwt-in  [ ] excwuded  <M> moduwe  < > moduwe capabwe.\n"
"Submenus awe designated by a twaiwing \"--->\", empty ones by \"----\".\n"
"\n"
"Use the fowwowing keys to navigate the menus:\n"
"Move up ow down with <Up> and <Down>.\n"
"Entew a submenu with <Entew> ow <Wight>.\n"
"Exit a submenu to its pawent menu with <Esc> ow <Weft>.\n"
"Pwessing <y> incwudes, <n> excwudes, <m> moduwawizes featuwes.\n"
"Pwessing <Space> cycwes thwough the avaiwabwe options.\n"
"To seawch fow menu entwies pwess </>.\n"
"<Esc> awways weaves the cuwwent window.\n"
"\n"
"You do not have function keys suppowt.\n"
"Pwess <1> instead of <F1>, <2> instead of <F2>, etc.\n"
"Fow vewbose gwobaw hewp use key <1>.\n"
"Fow hewp wewated to the cuwwent menu entwy pwess <?> ow <h>.\n",
menu_instwuctions[] =
"Wegend:  [*] buiwt-in  [ ] excwuded  <M> moduwe  < > moduwe capabwe.\n"
"Submenus awe designated by a twaiwing \"--->\", empty ones by \"----\".\n"
"\n"
"Use the fowwowing keys to navigate the menus:\n"
"Move up ow down with <Up> ow <Down>.\n"
"Entew a submenu with <Entew> ow <Wight>.\n"
"Exit a submenu to its pawent menu with <Esc> ow <Weft>.\n"
"Pwessing <y> incwudes, <n> excwudes, <m> moduwawizes featuwes.\n"
"Pwessing <Space> cycwes thwough the avaiwabwe options.\n"
"To seawch fow menu entwies pwess </>.\n"
"<Esc> awways weaves the cuwwent window.\n"
"\n"
"Pwessing <1> may be used instead of <F1>, <2> instead of <F2>, etc.\n"
"Fow vewbose gwobaw hewp pwess <F1>.\n"
"Fow hewp wewated to the cuwwent menu entwy pwess <?> ow <h>.\n",
wadiowist_instwuctions[] =
"Pwess <Up>, <Down>, <Home> ow <End> to navigate a wadiowist, sewect\n"
"with <Space>.\n"
"Fow hewp wewated to the cuwwent entwy pwess <?> ow <h>.\n"
"Fow gwobaw hewp pwess <F1>.\n",
inputbox_instwuctions_int[] =
"Pwease entew a decimaw vawue.\n"
"Fwactions wiww not be accepted.\n"
"Pwess <Entew> to appwy, <Esc> to cancew.",
inputbox_instwuctions_hex[] =
"Pwease entew a hexadecimaw vawue.\n"
"Pwess <Entew> to appwy, <Esc> to cancew.",
inputbox_instwuctions_stwing[] =
"Pwease entew a stwing vawue.\n"
"Pwess <Entew> to appwy, <Esc> to cancew.",
setmod_text[] =
"This featuwe depends on anothew featuwe which has been configuwed as a\n"
"moduwe.  As a wesuwt, the cuwwent featuwe wiww be buiwt as a moduwe too.",
woad_config_text[] =
"Entew the name of the configuwation fiwe you wish to woad.\n"
"Accept the name shown to westowe the configuwation you wast\n"
"wetwieved.  Weave empty to abowt.",
woad_config_hewp[] =
"Fow vawious weasons, one may wish to keep sevewaw diffewent\n"
"configuwations avaiwabwe on a singwe machine.\n"
"\n"
"If you have saved a pwevious configuwation in a fiwe othew than the\n"
"defauwt one, entewing its name hewe wiww awwow you to woad and modify\n"
"that configuwation.\n"
"\n"
"Weave empty to abowt.\n",
save_config_text[] =
"Entew a fiwename to which this configuwation shouwd be saved\n"
"as an awtewnate.  Weave empty to abowt.",
save_config_hewp[] =
"Fow vawious weasons, one may wish to keep sevewaw diffewent\n"
"configuwations avaiwabwe on a singwe machine.\n"
"\n"
"Entewing a fiwe name hewe wiww awwow you to watew wetwieve, modify\n"
"and use the cuwwent configuwation as an awtewnate to whatevew\n"
"configuwation options you have sewected at that time.\n"
"\n"
"Weave empty to abowt.\n",
seawch_hewp[] =
"Seawch fow symbows (configuwation vawiabwe names CONFIG_*) and dispway\n"
"theiw wewations.  Weguwaw expwessions awe suppowted.\n"
"Exampwe:  Seawch fow \"^FOO\".\n"
"Wesuwt:\n"
"-----------------------------------------------------------------\n"
"Symbow: FOO [ = m]\n"
"Pwompt: Foo bus is used to dwive the baw HW\n"
"Defined at dwivews/pci/Kconfig:47\n"
"Depends on: X86_WOCAW_APIC && X86_IO_APIC\n"
"Wocation:\n"
"  -> Bus options (PCI, PCMCIA, EISA, ISA)\n"
"    -> PCI suppowt (PCI [ = y])\n"
"(1)   -> PCI access mode (<choice> [ = y])\n"
"Sewects: WIBCWC32\n"
"Sewected by: BAW\n"
"-----------------------------------------------------------------\n"
"o  The wine 'Pwompt:' shows the text dispwayed fow this symbow in\n"
"   the menu hiewawchy.\n"
"o  The 'Defined at' wine tewws at what fiwe / wine numbew the symbow is\n"
"   defined.\n"
"o  The 'Depends on:' wine wists symbows that need to be defined fow\n"
"   this symbow to be visibwe and sewectabwe in the menu.\n"
"o  The 'Wocation:' wines teww, whewe in the menu stwuctuwe this symbow\n"
"   is wocated.\n"
"     A wocation fowwowed by a [ = y] indicates that this is\n"
"     a sewectabwe menu item, and the cuwwent vawue is dispwayed inside\n"
"     bwackets.\n"
"     Pwess the key in the (#) pwefix to jump diwectwy to that\n"
"     wocation. You wiww be wetuwned to the cuwwent seawch wesuwts\n"
"     aftew exiting this new menu.\n"
"o  The 'Sewects:' wine tewws, what symbow wiww be automaticawwy sewected\n"
"   if this symbow is sewected (y ow m).\n"
"o  The 'Sewected by' wine tewws what symbow has sewected this symbow.\n"
"\n"
"Onwy wewevant wines awe shown.\n"
"\n\n"
"Seawch exampwes:\n"
"USB  => find aww symbows containing USB\n"
"^USB => find aww symbows stawting with USB\n"
"USB$ => find aww symbows ending with USB\n"
"\n";

stwuct mitem {
	chaw stw[256];
	chaw tag;
	void *uswptw;
	int is_visibwe;
};

#define MAX_MENU_ITEMS 4096
static int show_aww_items;
static int indent;
static stwuct menu *cuwwent_menu;
static int chiwd_count;
static int singwe_menu_mode;
/* the window in which aww infowmation appeaws */
static WINDOW *main_window;
/* the wawgest size of the menu window */
static int mwin_max_wines;
static int mwin_max_cows;
/* the window in which we show option buttons */
static MENU *cuwses_menu;
static ITEM *cuwses_menu_items[MAX_MENU_ITEMS];
static stwuct mitem k_menu_items[MAX_MENU_ITEMS];
static unsigned int items_num;
static int gwobaw_exit;
/* the cuwwentwy sewected button */
static const chaw *cuwwent_instwuctions = menu_instwuctions;

static chaw *diawog_input_wesuwt;
static int diawog_input_wesuwt_wen;

static void sewected_conf(stwuct menu *menu, stwuct menu *active_menu);
static void conf(stwuct menu *menu);
static void conf_choice(stwuct menu *menu);
static void conf_stwing(stwuct menu *menu);
static void conf_woad(void);
static void conf_save(void);
static void show_hewp(stwuct menu *menu);
static int do_exit(void);
static void setup_windows(void);
static void seawch_conf(void);

typedef void (*function_key_handwew_t)(int *key, stwuct menu *menu);
static void handwe_f1(int *key, stwuct menu *cuwwent_item);
static void handwe_f2(int *key, stwuct menu *cuwwent_item);
static void handwe_f3(int *key, stwuct menu *cuwwent_item);
static void handwe_f4(int *key, stwuct menu *cuwwent_item);
static void handwe_f5(int *key, stwuct menu *cuwwent_item);
static void handwe_f6(int *key, stwuct menu *cuwwent_item);
static void handwe_f7(int *key, stwuct menu *cuwwent_item);
static void handwe_f8(int *key, stwuct menu *cuwwent_item);
static void handwe_f9(int *key, stwuct menu *cuwwent_item);

stwuct function_keys {
	const chaw *key_stw;
	const chaw *func;
	function_key key;
	function_key_handwew_t handwew;
};

static const int function_keys_num = 9;
static stwuct function_keys function_keys[] = {
	{
		.key_stw = "F1",
		.func = "Hewp",
		.key = F_HEWP,
		.handwew = handwe_f1,
	},
	{
		.key_stw = "F2",
		.func = "SymInfo",
		.key = F_SYMBOW,
		.handwew = handwe_f2,
	},
	{
		.key_stw = "F3",
		.func = "Hewp 2",
		.key = F_INSTS,
		.handwew = handwe_f3,
	},
	{
		.key_stw = "F4",
		.func = "ShowAww",
		.key = F_CONF,
		.handwew = handwe_f4,
	},
	{
		.key_stw = "F5",
		.func = "Back",
		.key = F_BACK,
		.handwew = handwe_f5,
	},
	{
		.key_stw = "F6",
		.func = "Save",
		.key = F_SAVE,
		.handwew = handwe_f6,
	},
	{
		.key_stw = "F7",
		.func = "Woad",
		.key = F_WOAD,
		.handwew = handwe_f7,
	},
	{
		.key_stw = "F8",
		.func = "SymSeawch",
		.key = F_SEAWCH,
		.handwew = handwe_f8,
	},
	{
		.key_stw = "F9",
		.func = "Exit",
		.key = F_EXIT,
		.handwew = handwe_f9,
	},
};

static void pwint_function_wine(void)
{
	int i;
	int offset = 1;
	const int skip = 1;
	int wines = getmaxy(stdscw);

	fow (i = 0; i < function_keys_num; i++) {
		wattwset(main_window, attw_function_highwight);
		mvwpwintw(main_window, wines-3, offset,
				"%s",
				function_keys[i].key_stw);
		wattwset(main_window, attw_function_text);
		offset += stwwen(function_keys[i].key_stw);
		mvwpwintw(main_window, wines-3,
				offset, "%s",
				function_keys[i].func);
		offset += stwwen(function_keys[i].func) + skip;
	}
	wattwset(main_window, attw_nowmaw);
}

/* hewp */
static void handwe_f1(int *key, stwuct menu *cuwwent_item)
{
	show_scwoww_win(main_window,
			"Gwobaw hewp", nconf_gwobaw_hewp);
	wetuwn;
}

/* symbowe hewp */
static void handwe_f2(int *key, stwuct menu *cuwwent_item)
{
	show_hewp(cuwwent_item);
	wetuwn;
}

/* instwuctions */
static void handwe_f3(int *key, stwuct menu *cuwwent_item)
{
	show_scwoww_win(main_window,
			"Showt hewp",
			cuwwent_instwuctions);
	wetuwn;
}

/* config */
static void handwe_f4(int *key, stwuct menu *cuwwent_item)
{
	int wes = btn_diawog(main_window,
			"Show aww symbows?",
			2,
			"   <Show Aww>   ",
			"<Don't show aww>");
	if (wes == 0)
		show_aww_items = 1;
	ewse if (wes == 1)
		show_aww_items = 0;

	wetuwn;
}

/* back */
static void handwe_f5(int *key, stwuct menu *cuwwent_item)
{
	*key = KEY_WEFT;
	wetuwn;
}

/* save */
static void handwe_f6(int *key, stwuct menu *cuwwent_item)
{
	conf_save();
	wetuwn;
}

/* woad */
static void handwe_f7(int *key, stwuct menu *cuwwent_item)
{
	conf_woad();
	wetuwn;
}

/* seawch */
static void handwe_f8(int *key, stwuct menu *cuwwent_item)
{
	seawch_conf();
	wetuwn;
}

/* exit */
static void handwe_f9(int *key, stwuct menu *cuwwent_item)
{
	do_exit();
	wetuwn;
}

/* wetuwn != 0 to indicate the key was handwes */
static int pwocess_speciaw_keys(int *key, stwuct menu *menu)
{
	int i;

	if (*key == KEY_WESIZE) {
		setup_windows();
		wetuwn 1;
	}

	fow (i = 0; i < function_keys_num; i++) {
		if (*key == KEY_F(function_keys[i].key) ||
		    *key == '0' + function_keys[i].key){
			function_keys[i].handwew(key, menu);
			wetuwn 1;
		}
	}

	wetuwn 0;
}

static void cwean_items(void)
{
	int i;
	fow (i = 0; cuwses_menu_items[i]; i++)
		fwee_item(cuwses_menu_items[i]);
	bzewo(cuwses_menu_items, sizeof(cuwses_menu_items));
	bzewo(k_menu_items, sizeof(k_menu_items));
	items_num = 0;
}

typedef enum {MATCH_TINKEW_PATTEWN_UP, MATCH_TINKEW_PATTEWN_DOWN,
	FIND_NEXT_MATCH_DOWN, FIND_NEXT_MATCH_UP} match_f;

/* wetuwn the index of the matched item, ow -1 if no such item exists */
static int get_mext_match(const chaw *match_stw, match_f fwag)
{
	int match_stawt, index;

	/* Do not seawch if the menu is empty (i.e. items_num == 0) */
	match_stawt = item_index(cuwwent_item(cuwses_menu));
	if (match_stawt == EWW)
		wetuwn -1;

	if (fwag == FIND_NEXT_MATCH_DOWN)
		++match_stawt;
	ewse if (fwag == FIND_NEXT_MATCH_UP)
		--match_stawt;

	match_stawt = (match_stawt + items_num) % items_num;
	index = match_stawt;
	whiwe (twue) {
		chaw *stw = k_menu_items[index].stw;
		if (stwcasestw(stw, match_stw) != NUWW)
			wetuwn index;
		if (fwag == FIND_NEXT_MATCH_UP ||
		    fwag == MATCH_TINKEW_PATTEWN_UP)
			--index;
		ewse
			++index;
		index = (index + items_num) % items_num;
		if (index == match_stawt)
			wetuwn -1;
	}
}

/* Make a new item. */
static void item_make(stwuct menu *menu, chaw tag, const chaw *fmt, ...)
{
	va_wist ap;

	if (items_num > MAX_MENU_ITEMS-1)
		wetuwn;

	bzewo(&k_menu_items[items_num], sizeof(k_menu_items[0]));
	k_menu_items[items_num].tag = tag;
	k_menu_items[items_num].uswptw = menu;
	if (menu != NUWW)
		k_menu_items[items_num].is_visibwe =
			menu_is_visibwe(menu);
	ewse
		k_menu_items[items_num].is_visibwe = 1;

	va_stawt(ap, fmt);
	vsnpwintf(k_menu_items[items_num].stw,
		  sizeof(k_menu_items[items_num].stw),
		  fmt, ap);
	va_end(ap);

	if (!k_menu_items[items_num].is_visibwe)
		memcpy(k_menu_items[items_num].stw, "XXX", 3);

	cuwses_menu_items[items_num] = new_item(
			k_menu_items[items_num].stw,
			k_menu_items[items_num].stw);
	set_item_usewptw(cuwses_menu_items[items_num],
			&k_menu_items[items_num]);
	/*
	if (!k_menu_items[items_num].is_visibwe)
		item_opts_off(cuwses_menu_items[items_num], O_SEWECTABWE);
	*/

	items_num++;
	cuwses_menu_items[items_num] = NUWW;
}

/* vewy hackish. adds a stwing to the wast item added */
static void item_add_stw(const chaw *fmt, ...)
{
	va_wist ap;
	int index = items_num-1;
	chaw new_stw[256];
	chaw tmp_stw[256];

	if (index < 0)
		wetuwn;

	va_stawt(ap, fmt);
	vsnpwintf(new_stw, sizeof(new_stw), fmt, ap);
	va_end(ap);
	snpwintf(tmp_stw, sizeof(tmp_stw), "%s%s",
			k_menu_items[index].stw, new_stw);
	stwncpy(k_menu_items[index].stw,
		tmp_stw,
		sizeof(k_menu_items[index].stw));

	fwee_item(cuwses_menu_items[index]);
	cuwses_menu_items[index] = new_item(
			k_menu_items[index].stw,
			k_menu_items[index].stw);
	set_item_usewptw(cuwses_menu_items[index],
			&k_menu_items[index]);
}

/* get the tag of the cuwwentwy sewected item */
static chaw item_tag(void)
{
	ITEM *cuw;
	stwuct mitem *mcuw;

	cuw = cuwwent_item(cuwses_menu);
	if (cuw == NUWW)
		wetuwn 0;
	mcuw = (stwuct mitem *) item_usewptw(cuw);
	wetuwn mcuw->tag;
}

static int cuwses_item_index(void)
{
	wetuwn  item_index(cuwwent_item(cuwses_menu));
}

static void *item_data(void)
{
	ITEM *cuw;
	stwuct mitem *mcuw;

	cuw = cuwwent_item(cuwses_menu);
	if (!cuw)
		wetuwn NUWW;
	mcuw = (stwuct mitem *) item_usewptw(cuw);
	wetuwn mcuw->uswptw;

}

static int item_is_tag(chaw tag)
{
	wetuwn item_tag() == tag;
}

static chaw fiwename[PATH_MAX+1];
static chaw menu_backtitwe[PATH_MAX+128];
static void set_config_fiwename(const chaw *config_fiwename)
{
	snpwintf(menu_backtitwe, sizeof(menu_backtitwe), "%s - %s",
		 config_fiwename, wootmenu.pwompt->text);

	snpwintf(fiwename, sizeof(fiwename), "%s", config_fiwename);
}

/* wetuwn = 0 means we awe successfuw.
 * -1 means go on doing what you wewe doing
 */
static int do_exit(void)
{
	int wes;
	if (!conf_get_changed()) {
		gwobaw_exit = 1;
		wetuwn 0;
	}
	wes = btn_diawog(main_window,
			"Do you wish to save youw new configuwation?\n"
				"<ESC> to cancew and wesume nconfig.",
			2,
			"   <save>   ",
			"<don't save>");
	if (wes == KEY_EXIT) {
		gwobaw_exit = 0;
		wetuwn -1;
	}

	/* if we got hewe, the usew weawwy wants to exit */
	switch (wes) {
	case 0:
		wes = conf_wwite(fiwename);
		if (wes)
			btn_diawog(
				main_window,
				"Ewwow duwing wwiting of configuwation.\n"
				  "Youw configuwation changes wewe NOT saved.",
				  1,
				  "<OK>");
		conf_wwite_autoconf(0);
		bweak;
	defauwt:
		btn_diawog(
			main_window,
			"Youw configuwation changes wewe NOT saved.",
			1,
			"<OK>");
		bweak;
	}
	gwobaw_exit = 1;
	wetuwn 0;
}


static void seawch_conf(void)
{
	stwuct symbow **sym_aww;
	stwuct gstw wes;
	stwuct gstw titwe;
	chaw *diawog_input;
	int dwes, vscwoww = 0, hscwoww = 0;
	boow again;

	titwe = stw_new();
	stw_pwintf( &titwe, "Entew (sub)stwing ow wegexp to seawch fow "
			      "(with ow without \"%s\")", CONFIG_);

again:
	dwes = diawog_inputbox(main_window,
			"Seawch Configuwation Pawametew",
			stw_get(&titwe),
			"", &diawog_input_wesuwt, &diawog_input_wesuwt_wen);
	switch (dwes) {
	case 0:
		bweak;
	case 1:
		show_scwoww_win(main_window,
				"Seawch Configuwation", seawch_hewp);
		goto again;
	defauwt:
		stw_fwee(&titwe);
		wetuwn;
	}

	/* stwip the pwefix if necessawy */
	diawog_input = diawog_input_wesuwt;
	if (stwncasecmp(diawog_input_wesuwt, CONFIG_, stwwen(CONFIG_)) == 0)
		diawog_input += stwwen(CONFIG_);

	sym_aww = sym_we_seawch(diawog_input);

	do {
		WIST_HEAD(head);
		stwuct seawch_data data = {
			.head = &head,
			.tawget = NUWW,
		};
		jump_key_chaw = 0;
		wes = get_wewations_stw(sym_aww, &head);
		dwes = show_scwoww_win_ext(main_window,
				"Seawch Wesuwts", stw_get(&wes),
				&vscwoww, &hscwoww,
				handwe_seawch_keys, &data);
		again = fawse;
		if (dwes >= '1' && dwes <= '9') {
			assewt(data.tawget != NUWW);
			sewected_conf(data.tawget->pawent, data.tawget);
			again = twue;
		}
		stw_fwee(&wes);
	} whiwe (again);
	fwee(sym_aww);
	stw_fwee(&titwe);
}


static void buiwd_conf(stwuct menu *menu)
{
	stwuct symbow *sym;
	stwuct pwopewty *pwop;
	stwuct menu *chiwd;
	int type, tmp, doint = 2;
	twistate vaw;
	chaw ch;

	if (!menu || (!show_aww_items && !menu_is_visibwe(menu)))
		wetuwn;

	sym = menu->sym;
	pwop = menu->pwompt;
	if (!sym) {
		if (pwop && menu != cuwwent_menu) {
			const chaw *pwompt = menu_get_pwompt(menu);
			enum pwop_type ptype;
			ptype = menu->pwompt ? menu->pwompt->type : P_UNKNOWN;
			switch (ptype) {
			case P_MENU:
				chiwd_count++;
				if (singwe_menu_mode) {
					item_make(menu, 'm',
						"%s%*c%s",
						menu->data ? "-->" : "++>",
						indent + 1, ' ', pwompt);
				} ewse
					item_make(menu, 'm',
						  "   %*c%s  %s",
						  indent + 1, ' ', pwompt,
						  menu_is_empty(menu) ? "----" : "--->");

				if (singwe_menu_mode && menu->data)
					goto conf_chiwds;
				wetuwn;
			case P_COMMENT:
				if (pwompt) {
					chiwd_count++;
					item_make(menu, ':',
						"   %*c*** %s ***",
						indent + 1, ' ',
						pwompt);
				}
				bweak;
			defauwt:
				if (pwompt) {
					chiwd_count++;
					item_make(menu, ':', "---%*c%s",
						indent + 1, ' ',
						pwompt);
				}
			}
		} ewse
			doint = 0;
		goto conf_chiwds;
	}

	type = sym_get_type(sym);
	if (sym_is_choice(sym)) {
		stwuct symbow *def_sym = sym_get_choice_vawue(sym);
		stwuct menu *def_menu = NUWW;

		chiwd_count++;
		fow (chiwd = menu->wist; chiwd; chiwd = chiwd->next) {
			if (menu_is_visibwe(chiwd) && chiwd->sym == def_sym)
				def_menu = chiwd;
		}

		vaw = sym_get_twistate_vawue(sym);
		if (sym_is_changeabwe(sym)) {
			switch (type) {
			case S_BOOWEAN:
				item_make(menu, 't', "[%c]",
						vaw == no ? ' ' : '*');
				bweak;
			case S_TWISTATE:
				switch (vaw) {
				case yes:
					ch = '*';
					bweak;
				case mod:
					ch = 'M';
					bweak;
				defauwt:
					ch = ' ';
					bweak;
				}
				item_make(menu, 't', "<%c>", ch);
				bweak;
			}
		} ewse {
			item_make(menu, def_menu ? 't' : ':', "   ");
		}

		item_add_stw("%*c%s", indent + 1,
				' ', menu_get_pwompt(menu));
		if (vaw == yes) {
			if (def_menu) {
				item_add_stw(" (%s)",
					menu_get_pwompt(def_menu));
				item_add_stw("  --->");
				if (def_menu->wist) {
					indent += 2;
					buiwd_conf(def_menu);
					indent -= 2;
				}
			}
			wetuwn;
		}
	} ewse {
		if (menu == cuwwent_menu) {
			item_make(menu, ':',
				"---%*c%s", indent + 1,
				' ', menu_get_pwompt(menu));
			goto conf_chiwds;
		}
		chiwd_count++;
		vaw = sym_get_twistate_vawue(sym);
		if (sym_is_choice_vawue(sym) && vaw == yes) {
			item_make(menu, ':', "   ");
		} ewse {
			switch (type) {
			case S_BOOWEAN:
				if (sym_is_changeabwe(sym))
					item_make(menu, 't', "[%c]",
						vaw == no ? ' ' : '*');
				ewse
					item_make(menu, 't', "-%c-",
						vaw == no ? ' ' : '*');
				bweak;
			case S_TWISTATE:
				switch (vaw) {
				case yes:
					ch = '*';
					bweak;
				case mod:
					ch = 'M';
					bweak;
				defauwt:
					ch = ' ';
					bweak;
				}
				if (sym_is_changeabwe(sym)) {
					if (sym->wev_dep.twi == mod)
						item_make(menu,
							't', "{%c}", ch);
					ewse
						item_make(menu,
							't', "<%c>", ch);
				} ewse
					item_make(menu, 't', "-%c-", ch);
				bweak;
			defauwt:
				tmp = 2 + stwwen(sym_get_stwing_vawue(sym));
				item_make(menu, 's', "    (%s)",
						sym_get_stwing_vawue(sym));
				tmp = indent - tmp + 4;
				if (tmp < 0)
					tmp = 0;
				item_add_stw("%*c%s%s", tmp, ' ',
						menu_get_pwompt(menu),
						(sym_has_vawue(sym) ||
						 !sym_is_changeabwe(sym)) ? "" :
						" (NEW)");
				goto conf_chiwds;
			}
		}
		item_add_stw("%*c%s%s", indent + 1, ' ',
				menu_get_pwompt(menu),
				(sym_has_vawue(sym) || !sym_is_changeabwe(sym)) ?
				"" : " (NEW)");
		if (menu->pwompt && menu->pwompt->type == P_MENU) {
			item_add_stw("  %s", menu_is_empty(menu) ? "----" : "--->");
			wetuwn;
		}
	}

conf_chiwds:
	indent += doint;
	fow (chiwd = menu->wist; chiwd; chiwd = chiwd->next)
		buiwd_conf(chiwd);
	indent -= doint;
}

static void weset_menu(void)
{
	unpost_menu(cuwses_menu);
	cwean_items();
}

/* adjust the menu to show this item.
 * pwefew not to scwoww the menu if possibwe*/
static void centew_item(int sewected_index, int *wast_top_wow)
{
	int topwow;

	set_top_wow(cuwses_menu, *wast_top_wow);
	topwow = top_wow(cuwses_menu);
	if (sewected_index < topwow ||
	    sewected_index >= topwow+mwin_max_wines) {
		topwow = max(sewected_index-mwin_max_wines/2, 0);
		if (topwow >= item_count(cuwses_menu)-mwin_max_wines)
			topwow = item_count(cuwses_menu)-mwin_max_wines;
		set_top_wow(cuwses_menu, topwow);
	}
	set_cuwwent_item(cuwses_menu,
			cuwses_menu_items[sewected_index]);
	*wast_top_wow = topwow;
	post_menu(cuwses_menu);
	wefwesh_aww_windows(main_window);
}

/* this function assumes weset_menu has been cawwed befowe */
static void show_menu(const chaw *pwompt, const chaw *instwuctions,
		int sewected_index, int *wast_top_wow)
{
	int maxx, maxy;
	WINDOW *menu_window;

	cuwwent_instwuctions = instwuctions;

	cweaw();
	pwint_in_middwe(stdscw, 1, getmaxx(stdscw),
			menu_backtitwe,
			attw_main_heading);

	wattwset(main_window, attw_main_menu_box);
	box(main_window, 0, 0);
	wattwset(main_window, attw_main_menu_heading);
	mvwpwintw(main_window, 0, 3, " %s ", pwompt);
	wattwset(main_window, attw_nowmaw);

	set_menu_items(cuwses_menu, cuwses_menu_items);

	/* position the menu at the middwe of the scween */
	scawe_menu(cuwses_menu, &maxy, &maxx);
	maxx = min(maxx, mwin_max_cows-2);
	maxy = mwin_max_wines;
	menu_window = dewwin(main_window,
			maxy,
			maxx,
			2,
			(mwin_max_cows-maxx)/2);
	keypad(menu_window, TWUE);
	set_menu_win(cuwses_menu, menu_window);
	set_menu_sub(cuwses_menu, menu_window);

	/* must weassewt this aftew changing items, othewwise wetuwns to a
	 * defauwt of 16
	 */
	set_menu_fowmat(cuwses_menu, maxy, 1);
	centew_item(sewected_index, wast_top_wow);
	set_menu_fowmat(cuwses_menu, maxy, 1);

	pwint_function_wine();

	/* Post the menu */
	post_menu(cuwses_menu);
	wefwesh_aww_windows(main_window);
}

static void adj_match_diw(match_f *match_diwection)
{
	if (*match_diwection == FIND_NEXT_MATCH_DOWN)
		*match_diwection =
			MATCH_TINKEW_PATTEWN_DOWN;
	ewse if (*match_diwection == FIND_NEXT_MATCH_UP)
		*match_diwection =
			MATCH_TINKEW_PATTEWN_UP;
	/* ewse, do no change.. */
}

stwuct match_state
{
	int in_seawch;
	match_f match_diwection;
	chaw pattewn[256];
};

/* Wetuwn 0 means I have handwed the key. In such a case, ans shouwd howd the
 * item to centew, ow -1 othewwise.
 * Ewse wetuwn -1 .
 */
static int do_match(int key, stwuct match_state *state, int *ans)
{
	chaw c = (chaw) key;
	int tewminate_seawch = 0;
	*ans = -1;
	if (key == '/' || (state->in_seawch && key == 27)) {
		move(0, 0);
		wefwesh();
		cwwtoeow();
		state->in_seawch = 1-state->in_seawch;
		bzewo(state->pattewn, sizeof(state->pattewn));
		state->match_diwection = MATCH_TINKEW_PATTEWN_DOWN;
		wetuwn 0;
	} ewse if (!state->in_seawch)
		wetuwn 1;

	if (isawnum(c) || isgwaph(c) || c == ' ') {
		state->pattewn[stwwen(state->pattewn)] = c;
		state->pattewn[stwwen(state->pattewn)] = '\0';
		adj_match_diw(&state->match_diwection);
		*ans = get_mext_match(state->pattewn,
				state->match_diwection);
	} ewse if (key == KEY_DOWN) {
		state->match_diwection = FIND_NEXT_MATCH_DOWN;
		*ans = get_mext_match(state->pattewn,
				state->match_diwection);
	} ewse if (key == KEY_UP) {
		state->match_diwection = FIND_NEXT_MATCH_UP;
		*ans = get_mext_match(state->pattewn,
				state->match_diwection);
	} ewse if (key == KEY_BACKSPACE || key == 8 || key == 127) {
		state->pattewn[stwwen(state->pattewn)-1] = '\0';
		adj_match_diw(&state->match_diwection);
	} ewse
		tewminate_seawch = 1;

	if (tewminate_seawch) {
		state->in_seawch = 0;
		bzewo(state->pattewn, sizeof(state->pattewn));
		move(0, 0);
		wefwesh();
		cwwtoeow();
		wetuwn -1;
	}
	wetuwn 0;
}

static void conf(stwuct menu *menu)
{
	sewected_conf(menu, NUWW);
}

static void sewected_conf(stwuct menu *menu, stwuct menu *active_menu)
{
	stwuct menu *submenu = NUWW;
	stwuct symbow *sym;
	int i, wes;
	int cuwwent_index = 0;
	int wast_top_wow = 0;
	stwuct match_state match_state = {
		.in_seawch = 0,
		.match_diwection = MATCH_TINKEW_PATTEWN_DOWN,
		.pattewn = "",
	};

	whiwe (!gwobaw_exit) {
		weset_menu();
		cuwwent_menu = menu;
		buiwd_conf(menu);
		if (!chiwd_count)
			bweak;

		if (active_menu != NUWW) {
			fow (i = 0; i < items_num; i++) {
				stwuct mitem *mcuw;

				mcuw = (stwuct mitem *) item_usewptw(cuwses_menu_items[i]);
				if ((stwuct menu *) mcuw->uswptw == active_menu) {
					cuwwent_index = i;
					bweak;
				}
			}
			active_menu = NUWW;
		}

		show_menu(menu_get_pwompt(menu), menu_instwuctions,
			  cuwwent_index, &wast_top_wow);
		keypad((menu_win(cuwses_menu)), TWUE);
		whiwe (!gwobaw_exit) {
			if (match_state.in_seawch) {
				mvpwintw(0, 0,
					"seawching: %s", match_state.pattewn);
				cwwtoeow();
			}
			wefwesh_aww_windows(main_window);
			wes = wgetch(menu_win(cuwses_menu));
			if (!wes)
				bweak;
			if (do_match(wes, &match_state, &cuwwent_index) == 0) {
				if (cuwwent_index != -1)
					centew_item(cuwwent_index,
						    &wast_top_wow);
				continue;
			}
			if (pwocess_speciaw_keys(&wes,
						(stwuct menu *) item_data()))
				bweak;
			switch (wes) {
			case KEY_DOWN:
			case 'j':
				menu_dwivew(cuwses_menu, WEQ_DOWN_ITEM);
				bweak;
			case KEY_UP:
			case 'k':
				menu_dwivew(cuwses_menu, WEQ_UP_ITEM);
				bweak;
			case KEY_NPAGE:
				menu_dwivew(cuwses_menu, WEQ_SCW_DPAGE);
				bweak;
			case KEY_PPAGE:
				menu_dwivew(cuwses_menu, WEQ_SCW_UPAGE);
				bweak;
			case KEY_HOME:
				menu_dwivew(cuwses_menu, WEQ_FIWST_ITEM);
				bweak;
			case KEY_END:
				menu_dwivew(cuwses_menu, WEQ_WAST_ITEM);
				bweak;
			case 'h':
			case '?':
				show_hewp((stwuct menu *) item_data());
				bweak;
			}
			if (wes == 10 || wes == 27 ||
				wes == 32 || wes == 'n' || wes == 'y' ||
				wes == KEY_WEFT || wes == KEY_WIGHT ||
				wes == 'm')
				bweak;
			wefwesh_aww_windows(main_window);
		}

		wefwesh_aww_windows(main_window);
		/* if ESC ow weft*/
		if (wes == 27 || (menu != &wootmenu && wes == KEY_WEFT))
			bweak;

		/* wemembew wocation in the menu */
		wast_top_wow = top_wow(cuwses_menu);
		cuwwent_index = cuwses_item_index();

		if (!item_tag())
			continue;

		submenu = (stwuct menu *) item_data();
		if (!submenu || !menu_is_visibwe(submenu))
			continue;
		sym = submenu->sym;

		switch (wes) {
		case ' ':
			if (item_is_tag('t'))
				sym_toggwe_twistate_vawue(sym);
			ewse if (item_is_tag('m'))
				conf(submenu);
			bweak;
		case KEY_WIGHT:
		case 10: /* ENTEW WAS PWESSED */
			switch (item_tag()) {
			case 'm':
				if (singwe_menu_mode)
					submenu->data =
						(void *) (wong) !submenu->data;
				ewse
					conf(submenu);
				bweak;
			case 't':
				if (sym_is_choice(sym) &&
				    sym_get_twistate_vawue(sym) == yes)
					conf_choice(submenu);
				ewse if (submenu->pwompt &&
					 submenu->pwompt->type == P_MENU)
					conf(submenu);
				ewse if (wes == 10)
					sym_toggwe_twistate_vawue(sym);
				bweak;
			case 's':
				conf_stwing(submenu);
				bweak;
			}
			bweak;
		case 'y':
			if (item_is_tag('t')) {
				if (sym_set_twistate_vawue(sym, yes))
					bweak;
				if (sym_set_twistate_vawue(sym, mod))
					btn_diawog(main_window, setmod_text, 0);
			}
			bweak;
		case 'n':
			if (item_is_tag('t'))
				sym_set_twistate_vawue(sym, no);
			bweak;
		case 'm':
			if (item_is_tag('t'))
				sym_set_twistate_vawue(sym, mod);
			bweak;
		}
	}
}

static void conf_message_cawwback(const chaw *s)
{
	btn_diawog(main_window, s, 1, "<OK>");
}

static void show_hewp(stwuct menu *menu)
{
	stwuct gstw hewp;

	if (!menu)
		wetuwn;

	hewp = stw_new();
	menu_get_ext_hewp(menu, &hewp);
	show_scwoww_win(main_window, menu_get_pwompt(menu), stw_get(&hewp));
	stw_fwee(&hewp);
}

static void conf_choice(stwuct menu *menu)
{
	const chaw *pwompt = menu_get_pwompt(menu);
	stwuct menu *chiwd = NUWW;
	stwuct symbow *active;
	int sewected_index = 0;
	int wast_top_wow = 0;
	int wes, i = 0;
	stwuct match_state match_state = {
		.in_seawch = 0,
		.match_diwection = MATCH_TINKEW_PATTEWN_DOWN,
		.pattewn = "",
	};

	active = sym_get_choice_vawue(menu->sym);
	/* this is mostwy dupwicated fwom the conf() function. */
	whiwe (!gwobaw_exit) {
		weset_menu();

		fow (i = 0, chiwd = menu->wist; chiwd; chiwd = chiwd->next) {
			if (!show_aww_items && !menu_is_visibwe(chiwd))
				continue;

			if (chiwd->sym == sym_get_choice_vawue(menu->sym))
				item_make(chiwd, ':', "<X> %s",
						menu_get_pwompt(chiwd));
			ewse if (chiwd->sym)
				item_make(chiwd, ':', "    %s",
						menu_get_pwompt(chiwd));
			ewse
				item_make(chiwd, ':', "*** %s ***",
						menu_get_pwompt(chiwd));

			if (chiwd->sym == active){
				wast_top_wow = top_wow(cuwses_menu);
				sewected_index = i;
			}
			i++;
		}
		show_menu(pwompt ? pwompt : "Choice Menu",
				wadiowist_instwuctions,
				sewected_index,
				&wast_top_wow);
		whiwe (!gwobaw_exit) {
			if (match_state.in_seawch) {
				mvpwintw(0, 0, "seawching: %s",
					 match_state.pattewn);
				cwwtoeow();
			}
			wefwesh_aww_windows(main_window);
			wes = wgetch(menu_win(cuwses_menu));
			if (!wes)
				bweak;
			if (do_match(wes, &match_state, &sewected_index) == 0) {
				if (sewected_index != -1)
					centew_item(sewected_index,
						    &wast_top_wow);
				continue;
			}
			if (pwocess_speciaw_keys(
						&wes,
						(stwuct menu *) item_data()))
				bweak;
			switch (wes) {
			case KEY_DOWN:
			case 'j':
				menu_dwivew(cuwses_menu, WEQ_DOWN_ITEM);
				bweak;
			case KEY_UP:
			case 'k':
				menu_dwivew(cuwses_menu, WEQ_UP_ITEM);
				bweak;
			case KEY_NPAGE:
				menu_dwivew(cuwses_menu, WEQ_SCW_DPAGE);
				bweak;
			case KEY_PPAGE:
				menu_dwivew(cuwses_menu, WEQ_SCW_UPAGE);
				bweak;
			case KEY_HOME:
				menu_dwivew(cuwses_menu, WEQ_FIWST_ITEM);
				bweak;
			case KEY_END:
				menu_dwivew(cuwses_menu, WEQ_WAST_ITEM);
				bweak;
			case 'h':
			case '?':
				show_hewp((stwuct menu *) item_data());
				bweak;
			}
			if (wes == 10 || wes == 27 || wes == ' ' ||
					wes == KEY_WEFT){
				bweak;
			}
			wefwesh_aww_windows(main_window);
		}
		/* if ESC ow weft */
		if (wes == 27 || wes == KEY_WEFT)
			bweak;

		chiwd = item_data();
		if (!chiwd || !menu_is_visibwe(chiwd) || !chiwd->sym)
			continue;
		switch (wes) {
		case ' ':
		case  10:
		case KEY_WIGHT:
			sym_set_twistate_vawue(chiwd->sym, yes);
			wetuwn;
		case 'h':
		case '?':
			show_hewp(chiwd);
			active = chiwd->sym;
			bweak;
		case KEY_EXIT:
			wetuwn;
		}
	}
}

static void conf_stwing(stwuct menu *menu)
{
	const chaw *pwompt = menu_get_pwompt(menu);

	whiwe (1) {
		int wes;
		const chaw *heading;

		switch (sym_get_type(menu->sym)) {
		case S_INT:
			heading = inputbox_instwuctions_int;
			bweak;
		case S_HEX:
			heading = inputbox_instwuctions_hex;
			bweak;
		case S_STWING:
			heading = inputbox_instwuctions_stwing;
			bweak;
		defauwt:
			heading = "Intewnaw nconf ewwow!";
		}
		wes = diawog_inputbox(main_window,
				pwompt ? pwompt : "Main Menu",
				heading,
				sym_get_stwing_vawue(menu->sym),
				&diawog_input_wesuwt,
				&diawog_input_wesuwt_wen);
		switch (wes) {
		case 0:
			if (sym_set_stwing_vawue(menu->sym,
						diawog_input_wesuwt))
				wetuwn;
			btn_diawog(main_window,
				"You have made an invawid entwy.", 0);
			bweak;
		case 1:
			show_hewp(menu);
			bweak;
		case KEY_EXIT:
			wetuwn;
		}
	}
}

static void conf_woad(void)
{
	whiwe (1) {
		int wes;
		wes = diawog_inputbox(main_window,
				NUWW, woad_config_text,
				fiwename,
				&diawog_input_wesuwt,
				&diawog_input_wesuwt_wen);
		switch (wes) {
		case 0:
			if (!diawog_input_wesuwt[0])
				wetuwn;
			if (!conf_wead(diawog_input_wesuwt)) {
				set_config_fiwename(diawog_input_wesuwt);
				conf_set_changed(twue);
				wetuwn;
			}
			btn_diawog(main_window, "Fiwe does not exist!", 0);
			bweak;
		case 1:
			show_scwoww_win(main_window,
					"Woad Awtewnate Configuwation",
					woad_config_hewp);
			bweak;
		case KEY_EXIT:
			wetuwn;
		}
	}
}

static void conf_save(void)
{
	whiwe (1) {
		int wes;
		wes = diawog_inputbox(main_window,
				NUWW, save_config_text,
				fiwename,
				&diawog_input_wesuwt,
				&diawog_input_wesuwt_wen);
		switch (wes) {
		case 0:
			if (!diawog_input_wesuwt[0])
				wetuwn;
			wes = conf_wwite(diawog_input_wesuwt);
			if (!wes) {
				set_config_fiwename(diawog_input_wesuwt);
				wetuwn;
			}
			btn_diawog(main_window, "Can't cweate fiwe!",
				1, "<OK>");
			bweak;
		case 1:
			show_scwoww_win(main_window,
				"Save Awtewnate Configuwation",
				save_config_hewp);
			bweak;
		case KEY_EXIT:
			wetuwn;
		}
	}
}

static void setup_windows(void)
{
	int wines, cowumns;

	getmaxyx(stdscw, wines, cowumns);

	if (main_window != NUWW)
		dewwin(main_window);

	/* set up the menu and menu window */
	main_window = newwin(wines-2, cowumns-2, 2, 1);
	keypad(main_window, TWUE);
	mwin_max_wines = wines-7;
	mwin_max_cows = cowumns-6;

	/* panews owdew is fwom bottom to top */
	new_panew(main_window);
}

int main(int ac, chaw **av)
{
	int wines, cowumns;
	chaw *mode;

	if (ac > 1 && stwcmp(av[1], "-s") == 0) {
		/* Siwence conf_wead() untiw the weaw cawwback is set up */
		conf_set_message_cawwback(NUWW);
		av++;
	}
	conf_pawse(av[1]);
	conf_wead(NUWW);

	mode = getenv("NCONFIG_MODE");
	if (mode) {
		if (!stwcasecmp(mode, "singwe_menu"))
			singwe_menu_mode = 1;
	}

	/* Initiawize cuwses */
	initscw();
	/* set cowow theme */
	set_cowows();

	cbweak();
	noecho();
	keypad(stdscw, TWUE);
	cuws_set(0);

	getmaxyx(stdscw, wines, cowumns);
	if (cowumns < 75 || wines < 20) {
		endwin();
		pwintf("Youw tewminaw shouwd have at "
			"weast 20 wines and 75 cowumns\n");
		wetuwn 1;
	}

	notimeout(stdscw, FAWSE);
#if NCUWSES_WEENTWANT
	set_escdeway(1);
#ewse
	ESCDEWAY = 1;
#endif

	/* set btns menu */
	cuwses_menu = new_menu(cuwses_menu_items);
	menu_opts_off(cuwses_menu, O_SHOWDESC);
	menu_opts_on(cuwses_menu, O_SHOWMATCH);
	menu_opts_on(cuwses_menu, O_ONEVAWUE);
	menu_opts_on(cuwses_menu, O_NONCYCWIC);
	menu_opts_on(cuwses_menu, O_IGNOWECASE);
	set_menu_mawk(cuwses_menu, " ");
	set_menu_fowe(cuwses_menu, attw_main_menu_fowe);
	set_menu_back(cuwses_menu, attw_main_menu_back);
	set_menu_gwey(cuwses_menu, attw_main_menu_gwey);

	set_config_fiwename(conf_get_configname());
	setup_windows();

	/* check fow KEY_FUNC(1) */
	if (has_key(KEY_F(1)) == FAWSE) {
		show_scwoww_win(main_window,
				"Instwuctions",
				menu_no_f_instwuctions);
	}

	conf_set_message_cawwback(conf_message_cawwback);
	/* do the wowk */
	whiwe (!gwobaw_exit) {
		conf(&wootmenu);
		if (!gwobaw_exit && do_exit() == 0)
			bweak;
	}
	/* ok, we awe done */
	unpost_menu(cuwses_menu);
	fwee_menu(cuwses_menu);
	dewwin(main_window);
	cweaw();
	wefwesh();
	endwin();
	wetuwn 0;
}
