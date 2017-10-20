= Re:VIEWに触れてみよう！

とりあえず、何はともあれRe:VIEWに触ってみましょう。

本章ではRe:VIEW環境の構築とビルドの仕方、ファイル構成などを簡単に解説します。

== 環境構築

通常、Re:VIEWを実行するにはRubyの実行環境が必要です。
またPDFファイルを生成するにはTeX環境の設定も必要となります。

しかしこのあたりは面倒でハマりやすい部分です。
そこで、今回はDocker@<fn>{docker}を使用して仮想コンテナ内でRe:VIEWを実行することにしましょう。
//footnote[docker][https://www.docker.com/]

Dockerが未インストールの場合、公式サイトを参照してインストールしてください。
メニューのGet Dockerから環境に合わせたインストールバイナリを使用すれば簡単にインストールできるはずです。

Dockerが正しく動いているかの確認が必要な場合、@<code>{docker run hello-world}をコンソールから入力してください。
以下のような表示が出ていれば、Dockerが正常に起動しています。

//cmd{
$ @<b>{docker run hello-world}

Hello from Docker!
This message shows that your installation appears to be working correctly.
//}

Dockerの動作が確認できたらRe:VIEWの環境を構築していきましょう。
こちらも1から作るのは面倒なので、著者の用意したボイラープレート@<fn>{boiler-plate}を利用することにします。
//footnote[boiler-plate][https://github.com/kokuyouwind/review-scaffold]

ボイラープレートの取得にはGitを使用します@<fn>{no-git}。
環境を構築したいディレクトリで、以下のコマンドを打ち込んでください。
ディレクトリ名は@<code>{your_book}になるので、好きな識別子に変更しても構いません。

//footnote[no-git][もしGitがインストールされていない場合はZipで取得することも可能ですが、原稿のバージョン管理を行うためにもGitを使用することを強く推奨します。]

//cmd{
$ @<b>{git clone git@github.com:kokuyouwind/review-scaffold.git your_book}
$ @<b>{cd your_book}
$ @<b>{git remote rm origin}
//}

ボイラープレートには既にサンプル原稿が配置されていますので、試しにPDFファイルを出力してみましょう。

@<code>{your_book}ディレクトリの直下で、@<code>{bin/pdf}コマンドを実行してください@<fn>{bin-windows}。
なお、初回実行時にはDockerコンテナを取得するため750MB程度のダウンロードが発生します。
気長に待ちましょう。

//footnote[bin-windows][シェルスクリプトなので、Windows環境ではMinGWなどから実行してください。]

成功すると大量のログが流れますが、以下のように@<code>{XXX bytes written}と表示されていれば書き出し成功です。

//cmd{
$ @<b>{bin/pdf}
compiling chapter01.tex
// ～省略～
97794 bytes written
//}

PDFファイルは@<code>{dists/book.pdf}に書き出されます。開いて内容を確認してみましょう。

これで、書籍をPDFに出力するための環境構築が完了しました。簡単でしたよね？

== ファイル構成

準備が整ったところで、まずはディレクトリ構成を確認していきましょう。

重要なディレクトリ・ファイルのみを以下に示します。

//emlist{
your_book
├── bin
├── dists
├── docs
└── src
   ├── catalog.yml
   ├── chapter01.re
   ├── config.yml
   └── images
//}

 : bin
   PDF生成などの実行可能スクリプトが格納されています。
 : dists
   生成したPDF及びePubファイルが配置されます。このディレクトリはGit管理対象外になっています。
 : docs
   生成したHTMLファイルが配置されます。GitHub Pagesの利用を考え、このディレクトリはGit管理対象になっています。
 : src
   Re:VIEWの設定や原稿を配置するディレクトリです。書籍を書く際はこのディレクトリ以下のファイルを編集することになります。
 : catalog.yml
   書籍の構成を設定するファイルです。いわゆる目次相当の設定をここに記述します。
 : chapter01.re
   catalog.ymlから参照される、本文を記述するファイルです。拡張子がreであればファイル名は任意で、章構成に合わせていくつかのファイルに分けて本文を書いていくことになります。
 : config.yml
   書籍全体の設定を記述するファイルです。書籍タイトルや奥付の設定などが含まれます。
 : images
   画像ファイルを配置するディレクトリです。本文中から参照する画像は基本的に全てこのディレクトリ内に配置します。

== config.yml

YAMLで書籍全体の設定が記述されています。
各設定の意味がコメントで記述されている@<fn>{config_comment}ため、必要に応じて変更すると良いでしょう。
//footnote[config_comment][コメント間違いもあるため、設定後は挙動を確認しましょう。また間違いを見つけたらIssueを作ったりPull Requestを送るとよいでしょう。]

特に重要と思う設定を以下に挙げていきます。

 : booktitle, aut
   書籍タイトルと著者名。大扉や奥付に使用されます。好きなものに変更しましょう。
 : date, history
   刊行日と発行年月。実際に頒布するときには頒布日に変更すると良いでしょう。
 : toc
   目次ページを作成するかのフラグ。よほど短い書籍でない限りはtrueにしましょう。
 : coverimage
   表紙に使用する画像ファイル。指定すると見栄えが良くなります。
 : titlepage
   表紙の後の大扉を作成するかのフラグ。ページ数は印刷料金に直結するため、表紙がある場合は大扉を作らないようfalseにすることが多いです。
 : colophon
   奥付を作成するかのフラグ。印刷所を使用する場合は必ず作成しましょう。
 : texdocumentclass
   デフォルトではA4サイズのPDFが作成されますが、一般的な同人誌はB5サイズです。このサイズを指定するにはTeXの詳細に立ち入ってしまいますが、@<code>{texdocumentclass: ["jsbook", "b5j,twoside,openany,uplatex"]}を指定してください。

その他の詳細な設定については公式の解説@<fn>[config_guide]を参照してください。
//footnote[config_guide][https://github.com/kmuto/review/wiki/config.yml]

== catalog.yml

YAMLで書籍の構成と、本文ファイルの対応を記述します。最初に章構成を考える際、ここを編集してファイルも作っておくと見通しがよくなります。

本書であれば以下のような記述になっています。

//emlist{
PREDEF:
  - preface.re

CHAPS:
  - chapter01.re
  - chapter02.re
  - chapter03.re

APPENDIX:

POSTDEF:
//}

各項目の意味は以下のとおりです。

 : PREDEF
   前付け(目次より前に入る文章)を指定します。一般的には「前書き」「序文」などが該当します。トップレベル見出しに章番号などはつきません。
 : CHAPS
   本文を指定します。この項目のみ指定必須になっています。トップレベル見出しは「第1章」などになります。
 : APPENDIX
   付録を指定します。トップレベル見出しは「付録A」などになります。
 : POSTDEF
   後付けを指定します。一般的には「後書き」「索引」などが該当します。トップレベル見出しに章番号などはつきません。

== 本文の書き方

拡張子reのファイルはRe:VIEWフォーマットで記述する必要があります。

基本的には何も考えずに文章を書けば、全てそのまま出力されます。
改行は1つだけだと同じ段落で文章が続き、空行が入る場合は別段落になります。

上記の文章であれば、ファイル中には以下のように記述されています。
//emlist{
拡張子reのファイルはRe:VIEWフォーマットで記述する必要があります。

基本的には何も考えずに文章を書けば、全てそのまま出力されます。
改行は1つだけだと同じ段落で文章が続き、空行が入る場合は別段落になります。
//}

見出しは@<code>{=}を付け、サブ見出しは数を増やして表現します。

本書であれば以下のような見出しを使っています。

//emlist{
= Re:VIEWに触れてみよう！
== 環境構築
//}

箇条書きは@<code>{*}を使います。ネスト項目は数を増やして表現します。

また番号つき箇条書きは@<code>{1.}を使います。こちらはネストできないので注意してください。

いずれも先頭に1文字以上のスペースが必要です。

//emlist{
 * 項目1
 ** 項目1のサブ項目
 * 項目2

 1. 手順1
 2. 手順2
//}

用語リストは空白、@<code>{:}、空白で始まる行を使って表現します。
本書ではconfig.ymlの説明などで使用しています。

//emlist{
 : booktitle, aut
   書籍タイトルと著者名。大扉や奥付に使用されます。好きなものに変更しましょう。
 : date, history
   刊行日と発行年月。実際に頒布するときには頒布日に変更すると良いでしょう。
//}

ソースコードのリストには @<code>{//list} を使います。参照用の連番を付けない場合は@<code>{emlist}を、行番号を付ける場合は@<code>{listnum}を使います。本書では@<code>{emlist}を多用しています。

図の挿入には @<code>{//image} を使用します。例えば@<code>{sample.jpg}を「サンプル画像」というキャプションで挿入する場合には@<code>{//image[sample][サンプル画像]}といった記述になります。

このあたりを抑えておけばある程度の文章を書けるはずです。

これ以外にも図表の参照やコラムなど様々なコマンドがありますので、詳細については公式のフォーマットガイド@<fn>{format_guide}を参照してください。
//footnote[format_guide][https://github.com/kmuto/review/blob/master/doc/format.ja.md]
