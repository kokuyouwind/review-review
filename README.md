# Re:VIEWで本を書く本

[![CircleCI](https://circleci.com/gh/kokuyouwind/review-review.svg?style=svg)](https://circleci.com/gh/kokuyouwind/review-review)

[Re:VIEW](https://github.com/kmuto/review)を使って書籍を作る方法をまとめた書籍です。

以下の内容を扱います。

 * [Re:VIEW scaffold](https://github.com/kokuyouwind/review-scaffold)を使って環境を作る方法
 * 校正ツールやCIの使い方
 * 書籍を印刷する方法

## View on Web

https://kokuyouwind.github.io/review-review/index.html

## View by PDF, EPub

https://circleci.com/gh/kokuyouwind/review-review/tree/master の最新ビルドを開き、Artifactタブから`book.pdf`, `book.epub`をダウンロードしてください。

## Setup

```
$ git clone git@github.com:kokuyouwind/review-scaffold.git
```

## HowToUse

Run commands at project root.

- `./bin/pdf` for create pdf.
  - creates `dists/book.pdf`
- `./bin/epub` for create epub.
  - creates `dists/book.epub`
- `./bin/html` for create html pages.
  - creates `docs/*.html`
  - [GitHub Pages](https://help.github.com/articles/configuring-a-publishing-source-for-github-pages/) Available
    - set `master branch /docs folder` for GitHub Pages source
    - ex. https://kokuyouwind.github.io/review-scaffold/
- `./bin/review` for check textlint.
