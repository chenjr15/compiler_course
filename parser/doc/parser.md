# 语法分析

## CFG

P:
原始

```r
STATEMENT ->  id = EXP;
            | ? EXP ;

EXP       ->  FACTOR
            | - EXP
            | EXP * EXP
            | EXP / EXP
            | EXP ^ EXP
            | EXP + EXP
            | EXP - EXP

FACTOR    ->  num
            | ( EXP )
            | const
            | id
            | FUNC ( ARG )
            | num FACTOR

ARG       ->  EXP
            | EXP, ARG
```

P:
消除二义性

```r
STATEMENT ->  id = EXP ;
            | ? EXP ;

EXP       ->  EXP + EXP1
            | EXP - EXP1
            | EXP1

EXP1      ->  EXP1 * FACTOR
            | EXP1 / FACTOR
            | EXP1 ^ FACTOR
            | FACTOR

FACTOR    -> - FACTOR
            | num
            | ( EXP )
            | const
            | id
            | func ( ARG )
            | num FACTOR

ARG       ->  EXP
            | EXP, ARG
```

增广文法

```r
STATEMENT1->  STATEMENT     1
STATEMENT ->  id = EXP ;    2
            | ? EXP ;       3

EXP       ->  EXP + EXP1    4
            | EXP - EXP1    5
            | EXP1          6

EXP1      ->  EXP1 * FACTOR 7
            | EXP1 / FACTOR 8
            | EXP1 ^ FACTOR 9
            | FACTOR        10

FACTOR    -> - FACTOR       11
            | num           12
            | ( EXP )       13
            | const         14
            | id            15
            | func ( ARG )  16
            | num FACTOR

ARG       ->  EXP           17
            | EXP, ARG      18
```

FIRST FOLLOW 集

```R
FIRST(S1)     = {id,?}
FIRST(S)      = {id,?}
FIRST(EXP)    = {-,num,(,const,id,func}
FIRST(EXP1)   = {-,num,(,const,id,func}
FIRST(FACTOR) = {-,num,(,const,id,func}
FIRST(ARG)    = {-,num,(,const,id,func}

FOLLOW(S1)    = {#}
FOLLOW(S)     = {#}
FOLLOW(EXP)    = {;,+,-,),',',}
FOLLOW(EXP1)   = {*,/,^,,;,+,-,),',',}
FOLLOW(FACTOR) = {*,/,^,;,+,-,),',',}
FOLLOW(ARG)    = {)}

```
