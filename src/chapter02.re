= 便利なツールを使ってみよう！

せっかくRe:VIEWで本を書くのなら、周辺の便利なツールについても役立てたいところです。

本章では執筆に使ったツールを紹介します。

== textlint

textlint@<fn>{textlint}はテキストファイルやマークダウンの校正ツールです。
表記ゆれや長過ぎる文章、繰り返し表現などを検出することができ、これらの指摘を修正することでより良い文章へ修正することができます。
//footnote[textlint][https://github.com/textlint/textlint]

類似のツールにRedPen@<fn>{redpen}があります。
また表記ゆれを検出できるツールにproofread-helper@<fn>{prh}があり、こちらはtextlint-rule-prh@<fn>{textlint-prh}経由でtextlintから使用することができます。
//footnote[redpen][http://redpen.cc/]
//footnote[prh][https://github.com/prh/prh]
//footnote[textlint-prh][https://github.com/textlint-rule/textlint-rule-prh]

textlintはプラグインを使用してルールの追加や入力フォーマットの追加が行えるようになっています。

今回は技術文書向けのルールをまとめたtextlint-rule-preset-ja-technical-writing@<fn>{textlint-ja}を使用します。
またRe:VIEW形式に対応するため、textlint-plugin-review@<fn>{textlint-review}も使用します。
//footnote[textlint-ja][https://github.com/textlint-ja/textlint-rule-preset-ja-technical-writing]
//footnote[textlint-review][https://github.com/orangain/textlint-plugin-review]

これらのツールセットアップはnpmで行うのですが、ボイラープレートには既に導入済みです。
@<code>{bin/lint}でtextlintでの校正を実行することができます。

//cmd{
$ @<b>{bin/lint}
yarn run v0.27.5
$ yarn --pure-lockfile && textlint src/*.re
Done in 9.29s.
//}

もし校正で問題が検出された場合、以下のように問題のある箇所と指摘内容が表示されます。

//cmd{
$ @<b>{bin/lint}
yarn run v0.27.5
$ yarn --pure-lockfile && textlint src/*.re

/work/src/chapter02.re
  27:42  ✓ error  文末が"。"で終わっていません。  preset-ja-technical-writing/ja-no-mixed-period

✖ 1 problem (1 error, 0 warnings)
✓ 1 fixable problem.
Try to run: $ textlint --fix [file]

error Command failed with exit code 1.
//}

ルールごとの設定は@<code>{.textlintrc}ファイルに記述します。
プリセットはかなり厳しく校正を行うため、書籍の特性に応じて緩めて使用するといいでしょう。

本書で使っている設定を以下に示します。

//emlist{
{
  "plugins": [
    "review"
  ],
  "filters": {
    "whitelist": {
      "allow": ["文字以上連続"]
    },
    "comments": true
  },
  "rules": {
    "preset-ja-technical-writing": {
      "no-exclamation-question-mark": false,
      "ja-no-weak-phrase": false
    }
  }
}
//}

@<code>{filters}には校正を無視するためのフィルタールールを設定します。

@<code>{whitelist}は単語単位で校正を無視するためのものです。
例えば漢字が6文字以上連続しないというルールで「文字以上連続」という部分だけは無視したい、という場合にこのような設定を行います。

@<code>{comments}はコメントで校正を無視する文章の指定を行えるものです。
@<code>{#@# textlint-disable}と@<code>{#@# textlint-enable}で挟んだ箇所を校正対象外とします。

@<code>{rules}には校正ルールの設定を記述します。

この本では、！や？を使わないようにする@<code>{no-exclamation-question-mark}ルールと、「思います」などの弱い表現を使わない@<code>{ja-no-weak-phrase}を無効にしています。

== CircleCI

せっかく文章校正をコマンドで行えるのなら、自動で流したくなりますよね。
CircleCI@<fn>[circleci]を使って自動で校正を行うようにしましょう。
//footnote[circleci][https://circleci.com/]

まずはGitHubリポジトリを作り、原稿をpushする必要があります。
新規リポジトリを作成した上でgitリポジトリのoriginに設定しましょう。

以下は本書の例ですので、git urlを新しく作ったリポジトリのものに変えて実行してください。

//cmd{
$ @<b>{git remote add origin git@github.com:kokuyouwind/review-review.git}
$ @<b>{git push origin master}
//}

このリポジトリに対してCircleCIを設定しましょう。
ボイラープレートでは既に設定ファイルが存在するので、CircleCIからプロジェクトを作成するだけでOKです。

CircleCIにログインし、「Add Proejct」からプロジェクトを追加します。
プロジェクトを追加すると、自動でビルドが始まり校正と書籍ファイルの作成が行われるようになります。

ビルドに成功すると、@<img>{circleci_artifact}のようにArtifactが生成され、PDFなどを確認することができます。

//image[circleci_artifact][CircleCIでのArtifact生成]

CircleCIの設定は@<code>{.circleci/config.yml}に記述されています。
追加のテストなどを行いたい場合はこのファイルを編集してください。

== reviewdog

textlintの結果を確認するためにいちいちCircleCIの画面を見るのは面倒ですね。

reviewdog@<fn>{reviewdog}を使うと、校正内容をGitHubのプルリクエストにコメントで書き込んでくれます。

//footnote[reviewdog][https://github.com/haya14busa/reviewdog]

@<code>{.circleci/config.yml}で既にreviewdogを使うよう設定されているため、CircleCIのプロジェクトに以下を設定するだけで使えるようになります。

 * @<href>{https://github.com/settings/tokens} からGitHubアクセストークンを発行する
 * CircleCIのプロジェクト設定で、BuildSetting > Environment Variablesから環境変数を設定する
 ** @<code>{REVIEWDOG_GITHUB_API_TOKEN}に先ほど発行したGitHubアクセストークンを設定する
 * 同じくプロジェクト設定で、Advanced Settings > Only build pull requestsを有効にする

これらの設定を行った上で、textlintに違反したコードを含むプルリクエストを作成すると、@<img>{reviewdog}のようにプルリクエストコメントで指摘が行われます。

//image[reviewdog][reviewdogでの指摘コメント]
