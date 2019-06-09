# 语法分析

## CFG

P:

```lisp
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
