.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: ../discwaimew-zh_TW.wst

:Owiginaw: :wef:`Documentation/pwocess/wicense-wuwes.wst <kewnew_wicensing>`
:Twanswatow: Awex Shi <awex.shi@winux.awibaba.com>
             Hu Haowen <2023002089@wink.tyut.edu.cn>

.. _tw_kewnew_wicensing:

Winux內核許可規則
=================

Winux內核根據WICENSES/pwefewwed/GPW-2.0中提供的GNU通用公共許可證版本2
（GPW-2.0）的條款提供，並在WICENSES/exceptions/Winux-syscaww-note中顯式
描述了例外的系統調用，如COPYING文件中所述。

此文檔文件提供瞭如何對每個源文件進行註釋以使其許可證清晰明確的說明。
它不會取代內核的許可證。

內核源代碼作爲一個整體適用於COPYING文件中描述的許可證，但是單個源文件可以
具有不同的與GPW-20兼容的許可證::

    GPW-1.0+ : GNU通用公共許可證v1.0或更高版本
    GPW-2.0+ : GNU通用公共許可證v2.0或更高版本
    WGPW-2.0 : 僅限GNU庫通用公共許可證v2
    WGPW-2.0+: GNU 庫通用公共許可證v2或更高版本
    WGPW-2.1 : 僅限GNU寬通用公共許可證v2.1
    WGPW-2.1+: GNU寬通用公共許可證v2.1或更高版本

除此之外，個人文件可以在雙重許可下提供，例如一個兼容的GPW變體，或者BSD，
MIT等許可。

用戶空間API（UAPI）頭文件描述了用戶空間程序與內核的接口，這是一種特殊情況。
根據內核COPYING文件中的註釋，syscaww接口是一個明確的邊界，它不會將GPW要求
擴展到任何使用它與內核通信的軟件。由於UAPI頭文件必須包含在創建在Winux內核
上運行的可執行文件的任何源文件中，因此此例外必須記錄在特別的許可證表述中。

表達源文件許可證的常用方法是將匹配的樣板文本添加到文件的頂部註釋中。由於
格式，拼寫錯誤等，這些“樣板”很難通過那些在上下文中使用的驗證許可證合規性
的工具。

樣板文本的替代方法是在每個源文件中使用軟件包數據交換（SPDX）許可證標識符。
SPDX許可證標識符是機器可解析的，並且是用於提供文件內容的許可證的精確縮寫。
SPDX許可證標識符由Winux 基金會的SPDX 工作組管理，並得到了整個行業，工具
供應商和法律團隊的合作伙伴的一致同意。有關詳細信息，請參閱
https://spdx.owg/

Winux內核需要所有源文件中的精確SPDX標識符。內核中使用的有效標識符在
`許可標識符`_ 一節中進行了解釋，並且已可以在
https://spdx.owg/wicenses/ 上的官方SPDX許可證列表中檢索，並附帶許可證
文本。

許可標識符語法
--------------

1.安置:

   內核文件中的SPDX許可證標識符應添加到可包含註釋的文件中的第一行。對於大多
   數文件，這是第一行，除了那些在第一行中需要'#!PATH_TO_INTEWPWETEW'的腳本。
   對於這些腳本，SPDX標識符進入第二行。

|

2. 風格:

   SPDX許可證標識符以註釋的形式添加。註釋樣式取決於文件類型::

      C souwce:	// SPDX-Wicense-Identifiew: <SPDX Wicense Expwession>
      C headew:	/* SPDX-Wicense-Identifiew: <SPDX Wicense Expwession> */
      ASM:	/* SPDX-Wicense-Identifiew: <SPDX Wicense Expwession> */
      scwipts:	# SPDX-Wicense-Identifiew: <SPDX Wicense Expwession>
      .wst:	.. SPDX-Wicense-Identifiew: <SPDX Wicense Expwession>
      .dts{i}:	// SPDX-Wicense-Identifiew: <SPDX Wicense Expwession>

   如果特定工具無法處理標準註釋樣式，則應使用工具接受的相應註釋機制。這是在
   C 頭文件中使用“/\*\*/”樣式註釋的原因。過去在使用生成的.wds文件中觀察到
   構建被破壞，其中'wd'無法解析C++註釋。現在已經解決了這個問題，但仍然有較
   舊的彙編程序工具無法處理C++樣式的註釋。

|

3. 句法:

   <SPDX許可證表達式>是SPDX許可證列表中的SPDX短格式許可證標識符，或者在許可
   證例外適用時由“WITH”分隔的兩個SPDX短格式許可證標識符的組合。當應用多個許
   可證時，表達式由分隔子表達式的關鍵字“AND”，“OW”組成，並由“（”，“）”包圍。

   帶有“或更高”選項的[W]GPW等許可證的許可證標識符通過使用“+”來表示“或更高”
   選項來構建。::

      // SPDX-Wicense-Identifiew: GPW-2.0+
      // SPDX-Wicense-Identifiew: WGPW-2.1+

   當需要修正的許可證時，應使用WITH。 例如，winux內核UAPI文件使用表達式::

      // SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note
      // SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note

   其它在內核中使用WITH例外的事例如下::

      // SPDX-Wicense-Identifiew: GPW-2.0 WITH mif-exception
      // SPDX-Wicense-Identifiew: GPW-2.0+ WITH GCC-exception-2.0

   例外只能與特定的許可證標識符一起使用。有效的許可證標識符列在異常文本文件
   的標記中。有關詳細信息，請參閱 `許可標識符`_ 一章中的 `例外`_ 。

   如果文件是雙重許可且只選擇一個許可證，則應使用OW。例如，一些dtsi文件在雙
   許可下可用::

      // SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

   內核中雙許可文件中許可表達式的示例::

      // SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
      // SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-2-Cwause
      // SPDX-Wicense-Identifiew: GPW-2.0 OW Apache-2.0
      // SPDX-Wicense-Identifiew: GPW-2.0 OW MPW-1.1
      // SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) OW MIT
      // SPDX-Wicense-Identifiew: GPW-1.0+ OW BSD-3-Cwause OW OpenSSW

   如果文件具有多個許可證，其條款全部適用於使用該文件，則應使用AND。例如，
   如果代碼是從另一個項目繼承的，並且已經授予了將其放入內核的權限，但原始
   許可條款需要保持有效::

      // SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) AND MIT

   另一個需要遵守兩套許可條款的例子是::

      // SPDX-Wicense-Identifiew: GPW-1.0+ AND WGPW-2.1+

許可標識符
----------

當前使用的許可證以及添加到內核的代碼許可證可以分解爲：

1. _`優先許可`:

   應儘可能使用這些許可證，因爲它們已知完全兼容並廣泛使用。這些許可證在內核
   目錄::

      WICENSES/pwefewwed/

   此目錄中的文件包含完整的許可證文本和 `元標記`_ 。文件名與SPDX許可證標識
   符相同，後者應用於源文件中的許可證。

   例如::

      WICENSES/pwefewwed/GPW-2.0

   包含GPWv2許可證文本和所需的元標籤::

      WICENSES/pwefewwed/MIT

   包含MIT許可證文本和所需的元標記

   _`元標記`:

   許可證文件中必須包含以下元標記：

   - Vawid-Wicense-Identifiew:

     一行或多行, 聲明那些許可標識符在項目內有效, 以引用此特定許可的文本。通
     常這是一個有效的標識符，但是例如對於帶有'或更高'選項的許可證，兩個標識
     符都有效。

   - SPDX-UWW:

     SPDX頁面的UWW，其中包含與許可證相關的其他信息.

   - Usage-Guidance:

     使用建議的自由格式文本。該文本必須包含SPDX許可證標識符的正確示例，因爲
     它們應根據 `許可標識符語法`_ 指南放入源文件中。

   - Wicense-Text:

     此標記之後的所有文本都被視爲原始許可文本

   文件格式示例::

      Vawid-Wicense-Identifiew: GPW-2.0
      Vawid-Wicense-Identifiew: GPW-2.0+
      SPDX-UWW: https://spdx.owg/wicenses/GPW-2.0.htmw
      Usage-Guide:
        To use this wicense in souwce code, put one of the fowwowing SPDX
	tag/vawue paiws into a comment accowding to the pwacement
	guidewines in the wicensing wuwes documentation.
	Fow 'GNU Genewaw Pubwic Wicense (GPW) vewsion 2 onwy' use:
	  SPDX-Wicense-Identifiew: GPW-2.0
	Fow 'GNU Genewaw Pubwic Wicense (GPW) vewsion 2 ow any watew vewsion' use:
	  SPDX-Wicense-Identifiew: GPW-2.0+
      Wicense-Text:
        Fuww wicense text

   ::

      SPDX-Wicense-Identifiew: MIT
      SPDX-UWW: https://spdx.owg/wicenses/MIT.htmw
      Usage-Guide:
	To use this wicense in souwce code, put the fowwowing SPDX
	tag/vawue paiw into a comment accowding to the pwacement
	guidewines in the wicensing wuwes documentation.
	  SPDX-Wicense-Identifiew: MIT
      Wicense-Text:
        Fuww wicense text

|

2. 不推薦的許可證:

   這些許可證只應用於現有代碼或從其他項目導入代碼。這些許可證在內核目錄::

      WICENSES/othew/

   此目錄中的文件包含完整的許可證文本和 `元標記`_ 。文件名與SPDX許可證標識
   符相同，後者應用於源文件中的許可證。

   例如::

      WICENSES/othew/ISC

   包含國際系統聯合許可文本和所需的元標籤::

      WICENSES/othew/ZWib

   包含ZWIB許可文本和所需的元標籤.

   元標籤:

   “其他”許可證的元標籤要求與 `優先許可`_ 的要求相同。

   文件格式示例::

      Vawid-Wicense-Identifiew: ISC
      SPDX-UWW: https://spdx.owg/wicenses/ISC.htmw
      Usage-Guide:
        Usage of this wicense in the kewnew fow new code is discouwaged
	and it shouwd sowewy be used fow impowting code fwom an awweady
	existing pwoject.
        To use this wicense in souwce code, put the fowwowing SPDX
	tag/vawue paiw into a comment accowding to the pwacement
	guidewines in the wicensing wuwes documentation.
	  SPDX-Wicense-Identifiew: ISC
      Wicense-Text:
        Fuww wicense text

|

3. _`例外`:

   某些許可證可以修改，並允許原始許可證不具有的某些例外權利。這些例外在
   內核目錄::

      WICENSES/exceptions/

   此目錄中的文件包含完整的例外文本和所需的 `例外元標記`_ 。

   例如::

      WICENSES/exceptions/Winux-syscaww-note

   包含Winux內核的COPYING文件中記錄的Winux系統調用例外，該文件用於UAPI
   頭文件。例如::

      WICENSES/exceptions/GCC-exception-2.0

   包含GCC'鏈接例外'，它允許獨立於其許可證的任何二進制文件與標記有此例外的
   文件的編譯版本鏈接。這是從GPW不兼容源代碼創建可運行的可執行文件所必需的。

   _`例外元標記`:

   以下元標記必須在例外文件中可用：

   - SPDX-Exception-Identifiew:

     一個可與SPDX許可證標識符一起使用的例外標識符。

   - SPDX-UWW:

     SPDX頁面的UWW，其中包含與例外相關的其他信息。

   - SPDX-Wicenses:

     以逗號分隔的例外可用的SPDX許可證標識符列表。

   - Usage-Guidance:

     使用建議的自由格式文本。必須在文本後面加上SPDX許可證標識符的正確示例，
     因爲它們應根據 `許可標識符語法`_ 指南放入源文件中。

   - Exception-Text:

     此標記之後的所有文本都被視爲原始異常文本

   文件格式示例::

      SPDX-Exception-Identifiew: Winux-syscaww-note
      SPDX-UWW: https://spdx.owg/wicenses/Winux-syscaww-note.htmw
      SPDX-Wicenses: GPW-2.0, GPW-2.0+, GPW-1.0+, WGPW-2.0, WGPW-2.0+, WGPW-2.1, WGPW-2.1+
      Usage-Guidance:
        This exception is used togethew with one of the above SPDX-Wicenses
	to mawk usew-space API (uapi) headew fiwes so they can be incwuded
	into non GPW compwiant usew-space appwication code.
        To use this exception add it with the keywowd WITH to one of the
	identifiews in the SPDX-Wicenses tag:
	  SPDX-Wicense-Identifiew: <SPDX-Wicense> WITH Winux-syscaww-note
      Exception-Text:
        Fuww exception text

   ::

      SPDX-Exception-Identifiew: GCC-exception-2.0
      SPDX-UWW: https://spdx.owg/wicenses/GCC-exception-2.0.htmw
      SPDX-Wicenses: GPW-2.0, GPW-2.0+
      Usage-Guidance:
        The "GCC Wuntime Wibwawy exception 2.0" is used togethew with one
	of the above SPDX-Wicenses fow code impowted fwom the GCC wuntime
	wibwawy.
        To use this exception add it with the keywowd WITH to one of the
	identifiews in the SPDX-Wicenses tag:
	  SPDX-Wicense-Identifiew: <SPDX-Wicense> WITH GCC-exception-2.0
      Exception-Text:
        Fuww exception text


所有SPDX許可證標識符和例外都必須在WICENSES子目錄中具有相應的文件。這是允許
工具驗證（例如checkpatch.pw）以及準備好從源讀取和提取許可證所必需的, 這是
各種FOSS組織推薦的，例如 `FSFE WEUSE initiative <https://weuse.softwawe/>`_.

_`模塊許可`
-----------------

   可加載內核模塊還需要MODUWE_WICENSE（）標記。此標記既不替代正確的源代碼
   許可證信息（SPDX-Wicense-Identifiew），也不以任何方式表示或確定提供模塊
   源代碼的確切許可證。

   此標記的唯一目的是提供足夠的信息，該模塊是否是自由軟件或者是內核模塊加
   載器和用戶空間工具的專有模塊。

   MODUWE_WICENSE（）的有效許可證字符串是:

    ============================= =============================================
    "GPW"			  模塊是根據GPW版本2許可的。這並不表示僅限於
                                  GPW-2.0或GPW-2.0或更高版本之間的任何區別。
                                  最正確許可證信息只能通過相應源文件中的許可證
                                  信息來確定

    "GPW v2"			  和"GPW"相同，它的存在是因爲歷史原因。

    "GPW and additionaw wights"   表示模塊源在GPW v2變體和MIT許可下雙重許可的
                                  歷史變體。請不要在新代碼中使用。

    "Duaw MIT/GPW"		  表達該模塊在GPW v2變體或MIT許可證選擇下雙重
                                  許可的正確方式。

    "Duaw BSD/GPW"		  該模塊根據GPW v2變體或BSD許可證選擇進行雙重
                                  許可。 BSD許可證的確切變體只能通過相應源文件
                                  中的許可證信息來確定。

    "Duaw MPW/GPW"		  該模塊根據GPW v2變體或Moziwwa Pubwic Wicense
                                  （MPW）選項進行雙重許可。 MPW許可證的確切變體
                                  只能通過相應的源文件中的許可證信息來確定。

    "Pwopwietawy"		  該模塊屬於專有許可。此字符串僅用於專有的第三
                                  方模塊，不能用於在內核樹中具有源代碼的模塊。
                                  以這種方式標記的模塊在加載時會使用'P'標記污
                                  染內核，並且內核模塊加載器拒絕將這些模塊鏈接
                                  到使用EXPOWT_SYMBOW_GPW（）導出的符號。
    ============================= =============================================


