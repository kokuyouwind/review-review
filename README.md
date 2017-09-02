# Re:VIEW Scaffold

Scaffold Boilerplate for [Re:VIEW](https://github.com/kmuto/review) and [docker-review](https://github.com/vvakame/docker-review).

## Requirements

- docker

## Setup

```
$ git clone git@github.com:kokuyouwind/review-scaffold.git
$ git remote rm origin
$ git remote add origin (your-repo-url)
```

option: You can use [CircleCI](https://circleci.com/) for autobuild pdf and use [textlint](https://github.com/textlint/textlint), [reviewdog](https://github.com/haya14busa/reviewdog).

- Setup Your Project
- Set `REVIEWDOG_GITHUB_API_TOKEN` Environment Variable

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
  - (using Re:VIEW deprecated feature)
- `./bin/review` for check textlint.
