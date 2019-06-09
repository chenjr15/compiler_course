# 词法分析设计

## 实数

```re
(0| ([1-9] (0|[1-9])* ) )  (\.(0|[1-9])* [1-9] )?
```

NFA:

| 状态   | .    | 0    | 1-9  | ε     |
| ------ | ---- | ---- | ---- | ----- |
| 0      |      |      |      | 1,3   |
| 1      |      | 2    |      |       |
| 2      |      |      |      | 12    |
| 3      | 4    |      |      |       |
| 4      |      |      |      | 5,11  |
| 5      |      |      |      | 6,8   |
| 6      |      |      | 7    |       |
| 7      |      |      |      | 10    |
| 8      |      | 9    |      |       |
| 9      |      |      |      | 10    |
| 10     |      |      |      | 5,11  |
| 11     |      |      |      | 12    |
| 12     |      |      |      | 13,24 |
| 13     | 15   |      |      |       |
| 14     |      |      |      | 15,21 |
| 15     |      |      |      | 16,18 |
| 16     |      |      | 17   |       |
| 17     |      |      |      | 20    |
| 18     |      | 19   |      |       |
| 19     |      |      |      | 20    |
| 20     |      |      |      | 15,21 |
| 21     |      |      |      | 22    |
| 22     |      |      | 23   |       |
| 23     |      |      |      | 24    |
| **24** |      |      |      |       |

DFA:

| DFA状态 | NFA状态                       |
| ------- | ----------------------------- |
| S0      | 1,3                           |
| S1      | 2,12,13,24                    |
| S2      | 4,5,6,8,11,12,13,24           |
| S3      | 15,16,18,21,22                |
| S4      | 7,10,5,6,8,11,12,13,24        |
| S5      | 9,10,5,6,8,11,12,13,24        |
| S6      | 17,20,15,16,18,21,22,23,13,24 |
| S7      | 19,2,15,16,18,21,22           |

| 状态 | .    | 0    | 1-9  |
| ---- | ---- | ---- | ---- |
| S0   |      | S1   | S2   |
| S1   | S3   |      |      |
| S2   | S3   | S5   | S4   |
| S3   |      | S7   | S6   |
| S4   | S3   | S5   | S4   |
| S5   | S3   | S5   | S4   |
| S6   | S3   | S7   | S6   |
| S7   |      | S7   | S6   |

## id

```re
^[_a-zA-Z]([_a-zA-Z]|[0-9]){0,31}
```

NFA:

| 状态  | 0-9  | _a-zA-Z | ε    |
| ----- | ---- | ------- | ---- |
| 0     |      | 1       |      |
| 1     |      |         | 2,8  |
| 2     |      |         | 3,5  |
| 3     |      | 4       |      |
| 4     |      |         | 7    |
| 5     | 6    |         |      |
| 6     |      |         | 7    |
| 7     |      |         | 2,8  |
| 8     |      |         | 9    |
| **9** |      |         |      |

DFA:

| DFA状态 | NFA状态       |
| ------- | ------------- |
| S0      | 0             |
| S1      | 1,2,3,5,8,9   |
| S2      | 4,7,8,2,3,5,9 |
| S3      | 6,7,8,2,3,5,9 |

| 状态   | 0-9  | _a-zA-Z |
| ------ | ---- | ------- |
| S0     |      | S1      |
| **S1** | S2   | S3      |
| **S2** | S2   | S3      |
| **S3** | S2   | S3      |