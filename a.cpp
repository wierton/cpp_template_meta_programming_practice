WHILE<cond, stat<1, 0>>

IF<cond<stat<1, 0>>::ret, WHILE<cond, stat<1, 0>::Next>, STOP<stat<1, 0>>>
|
IF<cond<stat<1, 0>>::ret, WHILE<cond, stat<2, 1>::Next>, STOP<stat<1, 0>>>

IF<cond<stat<2, 1>>::ret, WHILE<cond, stat<3, 3>::Next>, STOP<stat<2, 1>>>

IF<cond<stat<3, 3>>::ret, WHILE<cond, stat<4, 7>::Next>, STOP<stat<3, 3>>>

typedef STOP<stat<3, 3>> reType;
typedef stat<3, 3> reType;
