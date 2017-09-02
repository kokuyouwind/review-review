= はじめてのRe:VIEW

//lead{
「Hello, Re:VIEW.」
//}

== Re:VIEWとは

@<b>{Re:VIEW}は、EWBやRDあるいはWikiに似た簡易フォーマットで記述したテキストファイルを、目的に応じて各種の形式に変換するツールセットです。

平易な文法ながらも、コンピュータ関係のドキュメント作成のための多くの機能を備えており、次のような形式に変換できます。

 * テキスト（指示タグ付き）
 * LaTeX
 * HTML
 * XML

現在、入手手段としては次の3つがあります。

 1. Ruby gem
 2. Git
 3. Download from GitHub

ホームページは@<tt>{https://reviewml.org/}です。

以下はtextlintの設定テストです。

#@# textlint-disable

この行は行末に読点がありませんが、textlint-disableになっているため検査に通過します

#@# textlint-enable

以下はグラフ描画のテストです。

//graph[gnuplot_test][gnuplot]{
plot sin(x)
//}

//graph[graphviz_test][graphviz]{
digraph G {

  subgraph cluster_0 {
    style=filled;
    color=lightgrey;
    node [style=filled,color=white];
    a0 -> a1 -> a2 -> a3;
    label = "process #1";
  }

  subgraph cluster_1 {
    node [style=filled];
    b0 -> b1 -> b2 -> b3;
    label = "process #2";
    color=blue
  }
  start -> a0;
  start -> b0;
  a1 -> b3;
  b2 -> a3;
  a3 -> a0;
  a3 -> end;
  b3 -> end;

  start [shape=Mdiamond];
  end [shape=Msquare];
}
//}

//graph[aafigure_test][aafigure]{
    <-->  >->   --> <--
    >--<  o-->  -->+<--
    o--o          o=>
//}

//graph[blockdiag_test][blockdiag]{
blockdiag {
   A -> B -> C -> D;
   A -> E -> F -> G;
}
//}
