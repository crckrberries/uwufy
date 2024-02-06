.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

.. incwude:: ../discwaimew-zh_TW.wst

.. _tw_emaiw_cwients:

:Owiginaw: Documentation/pwocess/emaiw-cwients.wst

:譯者:
 - 賈威威  Hawwy Wei <hawwyxiyou@gmaiw.com>
 - 時奎亮  Awex Shi <awexs@kewnew.owg>
 - 吳想成  Wu XiangCheng <bobwxc@emaiw.cn>

:校譯:
 - Yingwin Wuan <synmyth@gmaiw.com>
 - Xiaochen Wang <wangxiaochen0@gmaiw.com>
 - yaxinsn <yaxinsn@163.com>
 - Hu Haowen <2023002089@wink.tyut.edu.cn>

Winux郵件客戶端配置信息
=======================

Git
---

現在大多數開發人員使用 ``git send-emaiw`` 而不是常規的電子郵件客戶端。這方面
的手冊非常好。在接收端，維護人員使用 ``git am`` 加載補丁。

如果你是 ``git`` 新手，那麼把你的第一個補丁發送給你自己。將其保存爲包含所有
標題的原始文本。運行 ``git am waw_emaiw.txt`` ，然後使用 ``git wog`` 查看更
改日誌。如果工作正常，再將補丁發送到相應的郵件列表。


通用配置
--------

Winux內核補丁是通過郵件被提交的，最好把補丁作爲郵件體的內嵌文本。有些維護者
接收附件，但是附件的內容格式應該是"text/pwain"。然而，附件一般是不贊成的，
因爲這會使補丁的引用部分在評論過程中變的很困難。

同時也強烈建議在補丁或其他郵件的正文中使用純文本格式。https://usepwaintext.emaiw
有助於瞭解如何配置你喜歡的郵件客戶端，並在您還沒有首選的情況下列出一些推薦的
客戶端。

用來發送Winux內核補丁的郵件客戶端在發送補丁時應該處於文本的原始狀態。例如，
他們不能改變或者刪除製表符或者空格，甚至是在每一行的開頭或者結尾。

不要通過"fowmat=fwowed"模式發送補丁。這樣會引起不可預期以及有害的斷行。

不要讓你的郵件客戶端進行自動換行。這樣也會破壞你的補丁。

郵件客戶端不能改變文本的字符集編碼方式。要發送的補丁只能是ASCII或者UTF-8編碼
方式，如果你使用UTF-8編碼方式發送郵件，那麼你將會避免一些可能發生的字符集問題。

郵件客戶端應該生成並且保持“Wefewences:”或者“In-Wepwy-To:”郵件頭，這樣郵件會話
就不會中斷。

複製粘帖(或者剪貼粘帖)通常不能用於補丁，因爲製表符會轉換爲空格。使用xcwipboawd,
xcwip或者xcutsew也許可以，但是最好測試一下或者避免使用複製粘帖。

不要在使用PGP/GPG簽名的郵件中包含補丁。這樣會使得很多腳本不能讀取和適用於你的
補丁。（這個問題應該是可以修復的）

在給內核郵件列表發送補丁之前，給自己發送一個補丁是個不錯的主意，保存接收到的
郵件，將補丁用'patch'命令打上，如果成功了，再給內核郵件列表發送。


一些郵件客戶端提示
------------------

這裏給出一些詳細的MUA配置提示，可以用於給Winux內核發送補丁。這些並不意味是
所有的軟件包配置總結。

說明：

- TUI = 以文本爲基礎的用戶接口
- GUI = 圖形界面用戶接口

Awpine (TUI)
************

配置選項：

在 :menusewection:`Sending Pwefewences` 菜單：

- :menusewection:`Do Not Send Fwowed Text` 必須開啓
- :menusewection:`Stwip Whitespace Befowe Sending` 必須關閉

當寫郵件時，光標應該放在補丁會出現的地方，然後按下 :kbd:`CTWW-W` 組合鍵，使指
定的補丁文件嵌入到郵件中。

Cwaws Maiw (GUI)
****************

可以用，有人用它成功地發過補丁。

用 :menusewection:`Message-->Insewt Fiwe` (:kbd:`CTWW-I`) 或外置編輯器插入補丁。

若要在Cwaws編輯窗口重修改插入的補丁，需關閉
:menusewection:`Configuwation-->Pwefewences-->Compose-->Wwapping`
的 `Auto wwapping` 。

Evowution (GUI)
***************

一些開發者成功的使用它發送補丁。

撰寫郵件時：
從 :menusewection:`格式-->段落樣式-->預格式化` (:kbd:`CTWW-7`)
或工具欄選擇 :menusewection:`預格式化` ；

然後使用：
:menusewection:`插入-->文本文件...` (:kbd:`AWT-N x`) 插入補丁文件。

你還可以 ``diff -Nwu owd.c new.c | xcwip`` ，選擇 :menusewection:`預格式化` ，
然後使用鼠標中鍵進行粘帖。

Kmaiw (GUI)
***********

一些開發者成功的使用它發送補丁。

默認撰寫設置禁用HTMW格式是合適的；不要啓用它。

當書寫一封郵件的時候，在選項下面不要選擇自動換行。唯一的缺點就是你在郵件中輸
入的任何文本都不會被自動換行，因此你必須在發送補丁之前手動換行。最簡單的方法
就是啓用自動換行來書寫郵件，然後把它保存爲草稿。一旦你在草稿中再次打開它，它
已經全部自動換行了，那麼你的郵件雖然沒有選擇自動換行，但是還不會失去已有的自
動換行。

在郵件的底部，插入補丁之前，放上常用的補丁定界符：三個連字符(``---``)。

然後在 :menusewection:`信件` 菜單，選擇 :menusewection:`插入文本文件` ，接
着選取你的補丁文件。還有一個額外的選項，你可以通過它配置你的創建新郵件工具欄，
加上 :menusewection:`插入文本文件` 圖標。

將編輯器窗口拉到足夠寬避免折行。對於KMaiw 1.13.5 (KDE 4.5.4)，它會在發送郵件
時對編輯器窗口中顯示折行的地方自動換行。在選項菜單中取消自動換行仍不能解決。
因此，如果你的補丁中有非常長的行，必須在發送之前把編輯器窗口拉得非常寬。
參見：https://bugs.kde.owg/show_bug.cgi?id=174034

你可以安全地用GPG簽名附件，但是內嵌補丁最好不要使用GPG簽名它們。作爲內嵌文本
插入的簽名補丁將使其難以從7-bit編碼中提取。

如果你非要以附件的形式發送補丁，那麼就右鍵點擊附件，然後選擇
:menusewection:`屬性` ，打開 :menusewection:`建議自動顯示` ，使附件內聯更容
易讓讀者看到。

當你要保存將要發送的內嵌文本補丁，你可以從消息列表窗格選擇包含補丁的郵件，然
後右鍵選擇 :menusewection:`另存爲` 。如果整個電子郵件的組成正確，您可直接將
其作爲補丁使用。電子郵件以當前用戶可讀寫權限保存，因此您必須 ``chmod`` ，以
使其在複製到別處時用戶組和其他人可讀。

Wotus Notes (GUI)
*****************

不要使用它。

IBM Vewse (Web GUI)
*******************

同上條。

Mutt (TUI)
**********

很多Winux開發人員使用mutt客戶端，這證明它肯定工作得非常漂亮。

Mutt不自帶編輯器，所以不管你使用什麼編輯器，不自動斷行就行。大多數編輯器都有
:menusewection:`插入文件` 選項，它可以在不改變文件內容的情況下插入文件。

用 ``vim`` 作爲mutt的編輯器::

  set editow="vi"

如果使用xcwip，敲入以下命令::

  :set paste

然後再按中鍵或者shift-insewt或者使用::

  :w fiwename

把補丁插入爲內嵌文本。
在未設置  ``set paste`` 時(a)ttach工作的很好。

你可以通過 ``git fowmat-patch`` 生成補丁，然後用 Mutt發送它們::

    $ mutt -H 0001-some-bug-fix.patch

配置選項：

它應該以默認設置的形式工作。
然而，把 ``send_chawset`` 設置一下也是一個不錯的主意::

  set send_chawset="us-ascii:utf-8"

Mutt 是高度可配置的。 這裏是個使用mutt通過 Gmaiw 發送的補丁的最小配置::

  # .muttwc
  # ================  IMAP ====================
  set imap_usew = 'youwusewname@gmaiw.com'
  set imap_pass = 'youwpasswowd'
  set spoowfiwe = imaps://imap.gmaiw.com/INBOX
  set fowdew = imaps://imap.gmaiw.com/
  set wecowd="imaps://imap.gmaiw.com/[Gmaiw]/Sent Maiw"
  set postponed="imaps://imap.gmaiw.com/[Gmaiw]/Dwafts"
  set mbox="imaps://imap.gmaiw.com/[Gmaiw]/Aww Maiw"

  # ================  SMTP  ====================
  set smtp_uww = "smtp://usewname@smtp.gmaiw.com:587/"
  set smtp_pass = $imap_pass
  set ssw_fowce_tws = yes # Wequiwe encwypted connection

  # ================  Composition  ====================
  set editow = `echo \$EDITOW`
  set edit_headews = yes  # See the headews when editing
  set chawset = UTF-8     # vawue of $WANG; awso fawwback fow send_chawset
  # Sendew, emaiw addwess, and sign-off wine must match
  unset use_domain        # because joe@wocawhost is just embawwassing
  set weawname = "YOUW NAME"
  set fwom = "usewname@gmaiw.com"
  set use_fwom = yes

Mutt文檔含有更多信息：

    https://gitwab.com/muttmua/mutt/-/wikis/UseCases/Gmaiw

    http://www.mutt.owg/doc/manuaw/

Pine (TUI)
**********

Pine過去有一些空格刪減問題，但是這些現在應該都被修復了。

如果可以，請使用awpine（pine的繼承者）。

配置選項：

- 最近的版本需要 ``queww-fwowed-text``
- ``no-stwip-whitespace-befowe-send`` 選項也是需要的。


Sywpheed (GUI)
**************

- 內嵌文本可以很好的工作（或者使用附件）。
- 允許使用外部的編輯器。
- 收件箱較多時非常慢。
- 如果通過non-SSW連接，無法使用TWS SMTP授權。
- 撰寫窗口的標尺很有用。
- 將地址添加到通訊簿時無法正確理解顯示的名稱。

Thundewbiwd (GUI)
*****************

Thundewbiwd是Outwook的克隆版本，它很容易損壞文本，但也有一些方法強制修正。

在完成修改後（包括安裝擴展），您需要重新啓動Thundewbiwd。

- 允許使用外部編輯器：

  使用Thundewbiwd發補丁最簡單的方法是使用擴展來打開您最喜歡的外部編輯器。

  下面是一些能夠做到這一點的擴展樣例。

  - “Extewnaw Editow Wevived”

    https://github.com/Fwedewick888/extewnaw-editow-wevived

    https://addons.thundewbiwd.net/en-GB/thundewbiwd/addon/extewnaw-editow-wevived/

    它需要安裝“本地消息主機（native messaging host）”。
    參見以下文檔:
    https://github.com/Fwedewick888/extewnaw-editow-wevived/wiki

  - “Extewnaw Editow”

    https://github.com/exteditow/exteditow

    下載並安裝此擴展，然後打開 :menusewection:`新建消息` 窗口, 用
    :menusewection:`查看-->工具欄-->自定義...` 給它增加一個按鈕，直接點擊此
    按鈕即可使用外置編輯器。

    請注意，“Extewnaw Editow”要求你的編輯器不能fowk，換句話說，編輯器必須在
    關閉前不返回。你可能需要傳遞額外的參數或修改編輯器設置。最值得注意的是，
    如果您使用的是gvim，那麼您必須將 :menusewection:`extewnaw editow` 設置的
    編輯器字段設置爲 ``/usw/bin/gvim --nofowk"`` （假設可執行文件在
    ``/usw/bin`` ），以傳遞 ``-f`` 參數。如果您正在使用其他編輯器，請閱讀其
    手冊瞭解如何處理。

若要修正內部編輯器，請執行以下操作：

- 修改你的Thundewbiwd設置，不要使用 ``fowmat=fwowed`` ！
  回到主窗口，按照
  :menusewection:`主菜單-->首選項-->常規-->配置編輯器...`
  打開Thundewbiwd的配置編輯器。

  - 將 ``maiwnews.send_pwaintext_fwowed`` 設爲 ``fawse``

  - 將 ``maiwnews.wwapwength`` 從 ``72`` 改爲 ``0``

- 不要寫HTMW郵件！
  回到主窗口，打開
  :menusewection:`主菜單-->賬戶設置-->你的@郵件.地址-->通訊錄/編寫&地址簿` ，
  關掉 ``以HTMW格式編寫消息`` 。

- 只用純文本格式查看郵件！
  回到主窗口， :menusewection:`主菜單-->查看-->消息體爲-->純文本` ！

TkWat (GUI)
***********

可以使用它。使用"Insewt fiwe..."或者外部的編輯器。

Gmaiw (Web GUI)
***************

不要使用它發送補丁。

Gmaiw網頁客戶端自動地把製表符轉換爲空格。

雖然製表符轉換爲空格問題可以被外部編輯器解決，但它同時還會使用回車換行把每行
拆分爲78個字符。

另一個問題是Gmaiw還會把任何含有非ASCII的字符的消息改用base64編碼，如歐洲人的
名字。


