
;; Function search (search)


Pass statistics:
----------------

;; 2 loops found
;;
;; Loop 0
;;  header 0, latch 1
;;  depth 0, outer -1
;;  nodes: 0 1 2 3 4 5 6 7
;;
;; Loop 1
;;  header 6, latch 5
;;  depth 1, outer 0
;;  nodes: 6 5 3 4
;; 2 succs { 6 }
;; 3 succs { 4 5 }
;; 4 succs { 5 }
;; 5 succs { 6 }
;; 6 succs { 3 7 }
;; 7 succs { 1 }
Duplicating header of the loop 1 up to edge 6->3.


Registering new PHI nodes in block #8

Updating SSA information for statement # DEBUG ve => ve_1

Updating SSA information for statement if (ve_1 != 0B)



Registering new PHI nodes in block #3

Updating SSA information for statement e_4 = ve_1->edge;

Updating SSA information for statement succ_bb_5 = e_4->target;

Updating SSA information for statement D.5604_6 = succ_bb_5->visited;



Registering new PHI nodes in block #4

Updating SSA information for statement e_4->type = 1;



Registering new PHI nodes in block #5

Updating SSA information for statement ve_7 = ve_1->next;



Registering new PHI nodes in block #6

Updating SSA information for statement # DEBUG ve => ve_1

Updating SSA information for statement if (ve_1 != 0B)



Registering new PHI nodes in block #7

Updating SSA information for statement count.10_8 = count;

Updating SSA information for statement bb_2(D)->dfs_order = count.10_8;


DFA Statistics for search

---------------------------------------------------------
                                Number of        Memory
                                instances         used 
---------------------------------------------------------
Referenced variables                      9         36b
Variables annotated                       9        108b
USE operands                             21         84b
DEF operands                              7         28b
VUSE operands                            11         44b
VDEF operands                             5         20b
PHI nodes                                 8        480b
PHI arguments                            12        288b
---------------------------------------------------------
Total memory used by DFA/SSA data                 1088b
---------------------------------------------------------

Average number of arguments per PHI node: 1.5 (max: 2)


Hash table statistics:
    def_blocks:   size 31, 4 elements, 0.000000 collision/search ratio
    repl_tbl:     size 31, 5 elements, 0.000000 collision/search ratio


SSA replacement table
N_i -> { O_1 ... O_j } means that N_i replaces O_1, ..., O_j

ve_9 -> { ve_1 }
.MEM_19 -> { .MEM_12 }
.MEM_20 -> { .MEM_12 }
ve_21 -> { ve_1 }
.MEM_22 -> { .MEM_12 }

Number of virtual NEW -> OLD mappings:       3
Number of real NEW -> OLD mappings:          2
Number of total NEW -> OLD mappings:         5

Number of virtual symbols: 3


Incremental SSA update started at block: 8

Number of blocks in CFG: 9
Number of blocks to update: 6 ( 67%)

Affected blocks: 3 4 5 6 7 8 



Pass statistics:
----------------

Merging blocks 2 and 8
Merging blocks 5 and 6
Removing basic block 9
;; basic block 9, loop depth 1, count 0
;; prev block 2, next block 3
;; pred:      
;; succ:       3 [100.0%]  (fallthru)
<bb 9>:
Invalid sum of incoming frequencies 0, should be 819


Removing basic block 10
;; basic block 10, loop depth 1, count 0
;; prev block 5, next block 7
;; pred:      
;; succ:       3 [100.0%]  (fallthru)
<bb 10>:
Invalid sum of incoming frequencies 0, should be 8281
goto <bb 3>;


Scope blocks after cleanups:

{ Scope block #0 
  struct basic_block * succ_bbD.4178;
  struct vec_edge * veD.4179;
  struct edge * eD.4180;

}
search (struct basic_block * bbD.4175)
{
  struct edge * eD.4180;
  struct vec_edge * veD.4179;
  struct basic_block * succ_bbD.4178;
  intD.0 count.11D.5608;
  intD.0 count.10D.5607;
  intD.0 D.5604;

  # BLOCK 2 freq:900
  # PRED: ENTRY [100.0%]  (fallthru,exec)
  # .MEMD.5609_14 = VDEF <.MEMD.5609_13(D)>
  bbD.4175_2(D)->visitedD.4144 = 1;
  # VUSE <.MEMD.5609_14>
  veD.4179_3 = bbD.4175_2(D)->succD.4149;
  # DEBUG veD.4179 => veD.4179_3
  # DEBUG veD.4179 => veD.4179_3
  if (veD.4179_3 != 0B)
    goto <bb 3>;
  else
    goto <bb 6>;
  # SUCC: 3 [91.0%]  (true,exec) 6 [9.0%]  (false,exec)

  # BLOCK 3 freq:9100
  # PRED: 5 [91.0%]  (true,exec) 2 [91.0%]  (true,exec)
  # veD.4179_9 = PHI <veD.4179_7(5), veD.4179_3(2)>
  # .MEMD.5609_19 = PHI <.MEMD.5609_11(5), .MEMD.5609_14(2)>
  # VUSE <.MEMD.5609_19>
  eD.4180_4 = veD.4179_9->edgeD.4138;
  # DEBUG eD.4180 => eD.4180_4
  # VUSE <.MEMD.5609_19>
  succ_bbD.4178_5 = eD.4180_4->targetD.4135;
  # DEBUG succ_bbD.4178 => succ_bbD.4178_5
  # VUSE <.MEMD.5609_19>
  D.5604_6 = succ_bbD.4178_5->visitedD.4144;
  if (D.5604_6 == 0)
    goto <bb 4>;
  else
    goto <bb 5>;
  # SUCC: 4 [29.0%]  (true,exec) 5 [71.0%]  (false,exec)

  # BLOCK 4 freq:2639
  # PRED: 3 [29.0%]  (true,exec)
  # .MEMD.5609_15 = VDEF <.MEMD.5609_19>
  eD.4180_4->typeD.4133 = 1;
  # .MEMD.5609_16 = VDEF <.MEMD.5609_15>
  searchD.4176 (succ_bbD.4178_5);
  # SUCC: 5 [100.0%]  (fallthru,exec)

  # BLOCK 5 freq:9100
  # PRED: 3 [71.0%]  (false,exec) 4 [100.0%]  (fallthru,exec)
  # .MEMD.5609_11 = PHI <.MEMD.5609_19(3), .MEMD.5609_16(4)>
  # VUSE <.MEMD.5609_11>
  veD.4179_7 = veD.4179_9->nextD.4139;
  # DEBUG veD.4179 => veD.4179_7
  # DEBUG veD.4179 => veD.4179_7
  if (veD.4179_7 != 0B)
    goto <bb 3>;
  else
    goto <bb 6>;
  # SUCC: 3 [91.0%]  (true,exec) 6 [9.0%]  (false,exec)

  # BLOCK 6 freq:900
  # PRED: 5 [9.0%]  (false,exec) 2 [9.0%]  (false,exec)
  # .MEMD.5609_22 = PHI <.MEMD.5609_11(5), .MEMD.5609_14(2)>
  # VUSE <.MEMD.5609_22>
  count.10D.5607_8 = countD.4173;
  # .MEMD.5609_17 = VDEF <.MEMD.5609_22>
  bbD.4175_2(D)->dfs_orderD.4145 = count.10D.5607_8;
  count.11D.5608_10 = count.10D.5607_8 + -1;
  # .MEMD.5609_18 = VDEF <.MEMD.5609_17>
  countD.4173 = count.11D.5608_10;
  return;
  # SUCC: EXIT [100.0%] 

}



;; Function depth_first_search (depth_first_search)


Pass statistics:
----------------

;; 2 loops found
;;
;; Loop 0
;;  header 0, latch 1
;;  depth 0, outer -1
;;  nodes: 0 1 2 3 4 5
;;
;; Loop 1
;;  header 4, latch 3
;;  depth 1, outer 0
;;  nodes: 4 3
;; 2 succs { 4 }
;; 3 succs { 4 }
;; 4 succs { 3 5 }
;; 5 succs { 1 }
Duplicating header of the loop 1 up to edge 4->3.


Registering new PHI nodes in block #6

Updating SSA information for statement # DEBUG bb => bb_1

Updating SSA information for statement if (bb_1 != 0B)



Registering new PHI nodes in block #3

Updating SSA information for statement bb_1->visited = 0;

Updating SSA information for statement bb_4 = bb_1->next;



Registering new PHI nodes in block #4

Updating SSA information for statement # DEBUG bb => bb_1

Updating SSA information for statement if (bb_1 != 0B)



Registering new PHI nodes in block #5

Updating SSA information for statement count.9_6 = cfg.8_2->bb_num;

Updating SSA information for statement count = count.9_6;


DFA Statistics for depth_first_search

---------------------------------------------------------
                                Number of        Memory
                                instances         used 
---------------------------------------------------------
Referenced variables                      7         28b
Variables annotated                       7         84b
USE operands                             13         52b
DEF operands                              5         20b
VUSE operands                             8         32b
VDEF operands                             3         12b
PHI nodes                                 7        420b
PHI arguments                            10        240b
---------------------------------------------------------
Total memory used by DFA/SSA data                  888b
---------------------------------------------------------

Average number of arguments per PHI node: 1.4 (max: 2)


Hash table statistics:
    def_blocks:   size 31, 4 elements, 0.000000 collision/search ratio
    repl_tbl:     size 31, 5 elements, 0.000000 collision/search ratio


SSA replacement table
N_i -> { O_1 ... O_j } means that N_i replaces O_1, ..., O_j

bb_5 -> { bb_1 }
.MEM_7 -> { .MEM_9 }
bb_14 -> { bb_1 }
.MEM_15 -> { .MEM_9 }
.MEM_16 -> { .MEM_9 }

Number of virtual NEW -> OLD mappings:       3
Number of real NEW -> OLD mappings:          2
Number of total NEW -> OLD mappings:         5

Number of virtual symbols: 3


Incremental SSA update started at block: 6

Number of blocks in CFG: 7
Number of blocks to update: 4 ( 57%)

Affected blocks: 3 4 5 6 



Pass statistics:
----------------

Merging blocks 2 and 6
Merging blocks 3 and 4
Removing basic block 7
;; basic block 7, loop depth 1, count 0
;; prev block 2, next block 3
;; pred:      
;; succ:       3 [100.0%]  (fallthru)
<bb 7>:
Invalid sum of incoming frequencies 0, should be 819


Removing basic block 8
;; basic block 8, loop depth 1, count 0
;; prev block 3, next block 5
;; pred:      
;; succ:       3 [100.0%]  (fallthru)
<bb 8>:
Invalid sum of incoming frequencies 0, should be 8281
goto <bb 3>;


Scope blocks after cleanups:

{ Scope block #0 
  struct basic_block * bbD.4187;

}
depth_first_search ()
{
  struct basic_block * bbD.4187;
  struct basic_block * D.5603;
  intD.0 count.9D.5602;
  struct control_flow_graph * cfg.8D.5601;

  # BLOCK 2 freq:900
  # PRED: ENTRY [100.0%]  (fallthru,exec)
  # VUSE <.MEMD.5610_10(D)>
  cfg.8D.5601_2 = cfgD.4174;
  # VUSE <.MEMD.5610_10(D)>
  bbD.4187_3 = cfg.8D.5601_2->bbD.4157;
  # DEBUG bbD.4187 => bbD.4187_3
  # DEBUG bbD.4187 => bbD.4187_3
  if (bbD.4187_3 != 0B)
    goto <bb 3>;
  else
    goto <bb 4>;
  # SUCC: 3 [91.0%]  (true,exec) 4 [9.0%]  (false,exec)

  # BLOCK 3 freq:9100
  # PRED: 3 [91.0%]  (true,exec) 2 [91.0%]  (true,exec)
  # bbD.4187_14 = PHI <bbD.4187_4(3), bbD.4187_3(2)>
  # .MEMD.5610_15 = PHI <.MEMD.5610_11(3), .MEMD.5610_10(D)(2)>
  # .MEMD.5610_11 = VDEF <.MEMD.5610_15>
  bbD.4187_14->visitedD.4144 = 0;
  # VUSE <.MEMD.5610_11>
  bbD.4187_4 = bbD.4187_14->nextD.4151;
  # DEBUG bbD.4187 => bbD.4187_4
  # DEBUG bbD.4187 => bbD.4187_4
  if (bbD.4187_4 != 0B)
    goto <bb 3>;
  else
    goto <bb 4>;
  # SUCC: 3 [91.0%]  (true,exec) 4 [9.0%]  (false,exec)

  # BLOCK 4 freq:900
  # PRED: 3 [9.0%]  (false,exec) 2 [9.0%]  (false,exec)
  # .MEMD.5610_16 = PHI <.MEMD.5610_11(3), .MEMD.5610_10(D)(2)>
  # VUSE <.MEMD.5610_16>
  count.9D.5602_6 = cfg.8D.5601_2->bb_numD.4153;
  # .MEMD.5610_12 = VDEF <.MEMD.5610_16>
  countD.4173 = count.9D.5602_6;
  # VUSE <.MEMD.5610_12>
  D.5603_8 = cfg.8D.5601_2->entryD.4155;
  # .MEMD.5610_13 = VDEF <.MEMD.5610_12>
  searchD.4176 (D.5603_8);
  return;
  # SUCC: EXIT [100.0%] 

}



;; Function is_ancestor (is_ancestor)


Pass statistics:
----------------

;; 3 loops found
;;
;; Loop 0
;;  header 0, latch 1
;;  depth 0, outer -1
;;  nodes: 0 1 2 3 4 5 6 7 8 9 11 10
;;
;; Loop 1
;;  header 3, latch 11
;;  depth 1, outer 0
;;  nodes: 3 11 9 6 8 4 7 5
;;
;; Loop 2
;;  header 8, latch 7
;;  depth 2, outer 1
;;  nodes: 8 7 5
;; 2 succs { 3 }
;; 3 succs { 10 4 }
;; 4 succs { 8 }
;; 5 succs { 6 7 }
;; 6 succs { 9 }
;; 7 succs { 8 }
;; 8 succs { 5 9 }
;; 9 succs { 11 10 }
;; 11 succs { 3 }
;; 10 succs { 1 }
Duplicating header of the loop 1 up to edge 3->4.


Registering new PHI nodes in block #12

Updating SSA information for statement # DEBUG bb => bb_1

Updating SSA information for statement if (bb_1 == source_7(D))



Registering new PHI nodes in block #4

Updating SSA information for statement ve_9 = bb_1->pred;



Registering new PHI nodes in block #8



Registering new PHI nodes in block #5



Registering new PHI nodes in block #6



Registering new PHI nodes in block #7



Registering new PHI nodes in block #9



Registering new PHI nodes in block #11



Registering new PHI nodes in block #3

Updating SSA information for statement # DEBUG bb => bb_1

Updating SSA information for statement if (bb_1 == source_7(D))



Registering new PHI nodes in block #10

Updating SSA information for statement return D.5594_4;


DFA Statistics for is_ancestor

---------------------------------------------------------
                                Number of        Memory
                                instances         used 
---------------------------------------------------------
Referenced variables                     11         44b
Variables annotated                      11        132b
USE operands                             24         96b
DEF operands                              7         28b
VUSE operands                             7         28b
VDEF operands                             0          0b
PHI nodes                                 7        420b
PHI arguments                            12        288b
---------------------------------------------------------
Total memory used by DFA/SSA data                 1036b
---------------------------------------------------------

Average number of arguments per PHI node: 1.7 (max: 3)


Hash table statistics:
    def_blocks:   size 31, 2 elements, 0.000000 collision/search ratio
    repl_tbl:     size 31, 2 elements, 0.000000 collision/search ratio


SSA replacement table
N_i -> { O_1 ... O_j } means that N_i replaces O_1, ..., O_j

bb_21 -> { bb_1 }
bb_22 -> { bb_1 }

Number of virtual NEW -> OLD mappings:       0
Number of real NEW -> OLD mappings:          2
Number of total NEW -> OLD mappings:         2

Number of virtual symbols: 0


Incremental SSA update started at block: 12

Number of blocks in CFG: 13
Number of blocks to update: 6 ( 46%)

Affected blocks: 3 4 8 9 10 12 


Duplicating header of the loop 2 up to edge 5->7.


Registering new PHI nodes in block #15

Updating SSA information for statement # DEBUG ve => ve_3

Updating SSA information for statement if (ve_3 != 0B)



Registering new PHI nodes in block #16

Updating SSA information for statement e_20 = ve_3->edge;

Updating SSA information for statement # DEBUG e => e_10

Updating SSA information for statement D.5595_23 = e_10->type;

Updating SSA information for statement if (D.5595_11 == 1)



Registering new PHI nodes in block #7

Updating SSA information for statement ve_13 = ve_3->next;



Registering new PHI nodes in block #8

Updating SSA information for statement # DEBUG ve => ve_3

Updating SSA information for statement if (ve_3 != 0B)



Registering new PHI nodes in block #5

Updating SSA information for statement e_10 = ve_3->edge;

Updating SSA information for statement # DEBUG e => e_10

Updating SSA information for statement D.5595_11 = e_10->type;

Updating SSA information for statement if (D.5595_11 == 1)



Registering new PHI nodes in block #6



Registering new PHI nodes in block #9



Registering new PHI nodes in block #11



Registering new PHI nodes in block #3



Registering new PHI nodes in block #14


DFA Statistics for is_ancestor

---------------------------------------------------------
                                Number of        Memory
                                instances         used 
---------------------------------------------------------
Referenced variables                     11         44b
Variables annotated                      11        132b
USE operands                             30        120b
DEF operands                              9         36b
VUSE operands                             9         36b
VDEF operands                             0          0b
PHI nodes                                 9        540b
PHI arguments                            16        384b
---------------------------------------------------------
Total memory used by DFA/SSA data                 1292b
---------------------------------------------------------

Average number of arguments per PHI node: 1.8 (max: 3)


Hash table statistics:
    def_blocks:   size 31, 6 elements, 0.000000 collision/search ratio
    repl_tbl:     size 31, 4 elements, 0.000000 collision/search ratio


SSA replacement table
N_i -> { O_1 ... O_j } means that N_i replaces O_1, ..., O_j

ve_19 -> { ve_3 }
e_20 -> { e_10 }
D.5595_23 -> { D.5595_11 }
ve_24 -> { ve_3 }

Number of virtual NEW -> OLD mappings:       0
Number of real NEW -> OLD mappings:          4
Number of total NEW -> OLD mappings:         4

Number of virtual symbols: 0


Incremental SSA update started at block: 15

Number of blocks in CFG: 17
Number of blocks to update: 7 ( 41%)

Affected blocks: 5 6 7 8 9 15 16 



Pass statistics:
----------------

Merging blocks 2 and 12
Merging blocks 4 and 15
Merging blocks 7 and 8
Removing basic block 11
;; basic block 11, loop depth 1, count 0
;; prev block 9, next block 10
;; pred:      
;; succ:       3 [100.0%]  (fallthru)
<bb 11>:
Invalid sum of incoming frequencies 0, should be 757
goto <bb 3>;


Removing basic block 13
;; basic block 13, loop depth 1, count 0
;; prev block 2, next block 3
;; pred:      
;; succ:       4 [100.0%]  (fallthru)
<bb 13>:
Invalid sum of incoming frequencies 0, should be 158
goto <bb 4>;


Removing basic block 14
;; basic block 14, loop depth 1, count 0
;; prev block 3, next block 4
;; pred:      
;; succ:       4 [100.0%]  (fallthru)
<bb 14>:
Invalid sum of incoming frequencies 0, should be 722


Removing basic block 17
;; basic block 17, loop depth 2, count 0
;; prev block 6, next block 7
;; pred:      
;; succ:       7 [100.0%]  (fallthru)
<bb 17>:
Invalid sum of incoming frequencies 0, should be 802


Removing basic block 18
;; basic block 18, loop depth 2, count 0
;; prev block 5, next block 6
;; pred:      
;; succ:       7 [100.0%]  (fallthru)
<bb 18>:
Invalid sum of incoming frequencies 0, should be 8318
goto <bb 7>;


Scope blocks after cleanups:

{ Scope block #0 
  struct basic_block * bbD.4195;
  struct vec_edge * veD.4196;
  struct edge * eD.4197;

}
is_ancestor (struct basic_block * sourceD.4191, struct basic_block * targetD.4192)
{
  struct edge * eD.4197;
  struct vec_edge * veD.4196;
  struct basic_block * bbD.4195;
  struct basic_block * D.5599;
  struct control_flow_graph * cfg.7D.5598;
  edge_type D.5595;
  intD.0 D.5594;

  # BLOCK 2 freq:165
  # PRED: ENTRY [100.0%]  (fallthru,exec)
  # DEBUG bbD.4195 => targetD.4192_5(D)
  # DEBUG bbD.4195 => targetD.4192_5(D)
  if (targetD.4192_5(D) == sourceD.4191_7(D))
    goto <bb 10>;
  else
    goto <bb 4>;
  # SUCC: 10 [4.5%]  (true,exec) 4 [95.5%]  (false,exec)

  # BLOCK 3 freq:756
  # PRED: 9 [86.0%]  (true,exec)
  # bbD.4195_1 = PHI <bbD.4195_2(9)>
  # DEBUG bbD.4195 => bbD.4195_1
  if (bbD.4195_1 == sourceD.4191_7(D))
    goto <bb 10>;
  else
    goto <bb 4>;
  # SUCC: 10 [4.5%]  (true,exec) 4 [95.5%]  (false,exec)

  # BLOCK 4 freq:880
  # PRED: 3 [95.5%]  (false,exec) 2 [95.5%]  (false,exec)
  # bbD.4195_21 = PHI <bbD.4195_1(3), targetD.4192_5(D)(2)>
  # VUSE <.MEMD.5611_17(D)>
  veD.4196_9 = bbD.4195_21->predD.4147;
  # DEBUG veD.4196 => veD.4196_9
  # DEBUG veD.4196 => veD.4196_9
  if (veD.4196_9 != 0B)
    goto <bb 5>;
  else
    goto <bb 9>;
  # SUCC: 5 [95.5%]  (true,exec) 9 [4.5%]  (false,exec)

  # BLOCK 5 freq:840
  # PRED: 4 [95.5%]  (true,exec)
  # VUSE <.MEMD.5611_17(D)>
  eD.4197_20 = veD.4196_9->edgeD.4138;
  # DEBUG eD.4197 => eD.4197_20
  # VUSE <.MEMD.5611_17(D)>
  D.5595_23 = eD.4197_20->typeD.4133;
  if (D.5595_23 == 1)
    goto <bb 7>;
  else
    goto <bb 8>;
  # SUCC: 7 [4.5%]  (true,exec) 8 [95.5%]  (false,exec)

  # BLOCK 6 freq:8710
  # PRED: 8 [95.5%]  (true,exec)
  # VUSE <.MEMD.5611_17(D)>
  eD.4197_10 = veD.4196_13->edgeD.4138;
  # DEBUG eD.4197 => eD.4197_10
  # VUSE <.MEMD.5611_17(D)>
  D.5595_11 = eD.4197_10->typeD.4133;
  if (D.5595_11 == 1)
    goto <bb 7>;
  else
    goto <bb 8>;
  # SUCC: 7 [4.5%]  (true,exec) 8 [95.5%]  (false,exec)

  # BLOCK 7 freq:430
  # PRED: 6 [4.5%]  (true,exec) 5 [4.5%]  (true,exec)
  # eD.4197_18 = PHI <eD.4197_10(6), eD.4197_20(5)>
  # VUSE <.MEMD.5611_17(D)>
  bbD.4195_12 = eD.4197_18->sourceD.4134;
  # DEBUG bbD.4195 => bbD.4195_12
  goto <bb 9>;
  # SUCC: 9 [100.0%]  (fallthru,exec)

  # BLOCK 8 freq:9120
  # PRED: 6 [95.5%]  (false,exec) 5 [95.5%]  (false,exec)
  # veD.4196_24 = PHI <veD.4196_13(6), veD.4196_9(5)>
  # VUSE <.MEMD.5611_17(D)>
  veD.4196_13 = veD.4196_24->nextD.4139;
  # DEBUG veD.4196 => veD.4196_13
  # DEBUG veD.4196 => veD.4196_13
  if (veD.4196_13 != 0B)
    goto <bb 6>;
  else
    goto <bb 9>;
  # SUCC: 6 [95.5%]  (true,exec) 9 [4.5%]  (false,exec)

  # BLOCK 9 freq:880
  # PRED: 7 [100.0%]  (fallthru,exec) 8 [4.5%]  (false,exec) 4 [4.5%]  (false,exec)
  # bbD.4195_2 = PHI <bbD.4195_12(7), bbD.4195_21(8), bbD.4195_21(4)>
  # DEBUG bbD.4195 => bbD.4195_2
  # VUSE <.MEMD.5611_17(D)>
  cfg.7D.5598_14 = cfgD.4174;
  # VUSE <.MEMD.5611_17(D)>
  D.5599_15 = cfg.7D.5598_14->entryD.4155;
  if (D.5599_15 != bbD.4195_2)
    goto <bb 3>;
  else
    goto <bb 10>;
  # SUCC: 3 [86.0%]  (true,exec) 10 [14.0%]  (false,exec)

  # BLOCK 10 freq:165
  # PRED: 3 [4.5%]  (true,exec) 9 [14.0%]  (false,exec) 2 [4.5%]  (true,exec)
  # D.5594_4 = PHI <1(3), 0(9), 1(2)>
  return D.5594_4;
  # SUCC: EXIT [100.0%] 

}



;; Function mark_edge (mark_edge)


Pass statistics:
----------------

;; 1 loops found
;;
;; Loop 0
;;  header 0, latch 1
;;  depth 0, outer -1
;;  nodes: 0 1 2 3 4 5 6 7
;; 2 succs { 3 4 }
;; 3 succs { 7 }
;; 4 succs { 5 6 }
;; 5 succs { 7 }
;; 6 succs { 7 }
;; 7 succs { 1 }

Pass statistics:
----------------

mark_edge (struct edge * eD.4203)
{
  struct basic_block * targetD.4207;
  struct basic_block * sourceD.4206;
  intD.0 D.5588;
  intD.0 D.5584;

  # BLOCK 2 freq:10000
  # PRED: ENTRY [100.0%]  (fallthru,exec)
  # VUSE <.MEMD.5612_6(D)>
  sourceD.4206_2 = eD.4203_1(D)->sourceD.4134;
  # DEBUG sourceD.4206 => sourceD.4206_2
  # VUSE <.MEMD.5612_6(D)>
  targetD.4207_3 = eD.4203_1(D)->targetD.4135;
  # DEBUG targetD.4207 => targetD.4207_3
  # VUSE <.MEMD.5612_6(D)>
  D.5584_4 = is_ancestorD.4193 (targetD.4207_3, sourceD.4206_2);
  if (D.5584_4 != 0)
    goto <bb 3>;
  else
    goto <bb 4>;
  # SUCC: 3 [61.0%]  (true,exec) 4 [39.0%]  (false,exec)

  # BLOCK 3 freq:6102
  # PRED: 2 [61.0%]  (true,exec)
  # .MEMD.5612_7 = VDEF <.MEMD.5612_6(D)>
  eD.4203_1(D)->typeD.4133 = 3;
  goto <bb 7>;
  # SUCC: 7 [100.0%]  (fallthru,exec)

  # BLOCK 4 freq:3898
  # PRED: 2 [39.0%]  (false,exec)
  # VUSE <.MEMD.5612_6(D)>
  D.5588_5 = is_ancestorD.4193 (sourceD.4206_2, targetD.4207_3);
  if (D.5588_5 != 0)
    goto <bb 5>;
  else
    goto <bb 6>;
  # SUCC: 5 [39.0%]  (true,exec) 6 [61.0%]  (false,exec)

  # BLOCK 5 freq:1520
  # PRED: 4 [39.0%]  (true,exec)
  # .MEMD.5612_8 = VDEF <.MEMD.5612_6(D)>
  eD.4203_1(D)->typeD.4133 = 2;
  goto <bb 7>;
  # SUCC: 7 [100.0%]  (fallthru,exec)

  # BLOCK 6 freq:2378
  # PRED: 4 [61.0%]  (false,exec)
  # .MEMD.5612_9 = VDEF <.MEMD.5612_6(D)>
  eD.4203_1(D)->typeD.4133 = 4;
  # SUCC: 7 [100.0%]  (fallthru,exec)

  # BLOCK 7 freq:10000
  # PRED: 3 [100.0%]  (fallthru,exec) 5 [100.0%]  (fallthru,exec) 6 [100.0%]  (fallthru,exec)
  return;
  # SUCC: EXIT [100.0%] 

}



;; Function mark_edges (mark_edges)


Pass statistics:
----------------

;; 2 loops found
;;
;; Loop 0
;;  header 0, latch 1
;;  depth 0, outer -1
;;  nodes: 0 1 2 3 4 5 6 7
;;
;; Loop 1
;;  header 6, latch 5
;;  depth 1, outer 0
;;  nodes: 6 5 3 4
;; 2 succs { 6 }
;; 3 succs { 4 5 }
;; 4 succs { 5 }
;; 5 succs { 6 }
;; 6 succs { 3 7 }
;; 7 succs { 1 }
Duplicating header of the loop 1 up to edge 6->3.


Registering new PHI nodes in block #8

Updating SSA information for statement # DEBUG e => e_1

Updating SSA information for statement if (e_1 != 0B)



Registering new PHI nodes in block #3

Updating SSA information for statement D.5581_5 = e_1->type;



Registering new PHI nodes in block #4

Updating SSA information for statement mark_edge (e_1);



Registering new PHI nodes in block #5

Updating SSA information for statement e_6 = e_1->next;



Registering new PHI nodes in block #6

Updating SSA information for statement # DEBUG e => e_1

Updating SSA information for statement if (e_1 != 0B)



Registering new PHI nodes in block #7

Updating SSA information for statement return;


DFA Statistics for mark_edges

---------------------------------------------------------
                                Number of        Memory
                                instances         used 
---------------------------------------------------------
Referenced variables                      6         24b
Variables annotated                       6         72b
USE operands                             13         52b
DEF operands                              5         20b
VUSE operands                             6         24b
VDEF operands                             1          4b
PHI nodes                                 7        420b
PHI arguments                            10        240b
---------------------------------------------------------
Total memory used by DFA/SSA data                  856b
---------------------------------------------------------

Average number of arguments per PHI node: 1.4 (max: 2)


Hash table statistics:
    def_blocks:   size 13, 4 elements, 0.000000 collision/search ratio
    repl_tbl:     size 31, 4 elements, 0.000000 collision/search ratio


SSA replacement table
N_i -> { O_1 ... O_j } means that N_i replaces O_1, ..., O_j

e_11 -> { e_1 }
.MEM_12 -> { .MEM_8 }
e_13 -> { e_1 }
.MEM_14 -> { .MEM_8 }

Number of virtual NEW -> OLD mappings:       2
Number of real NEW -> OLD mappings:          2
Number of total NEW -> OLD mappings:         4

Number of virtual symbols: 2


Incremental SSA update started at block: 8

Number of blocks in CFG: 9
Number of blocks to update: 6 ( 67%)

Affected blocks: 3 4 5 6 7 8 



Pass statistics:
----------------

Merging blocks 2 and 8
Merging blocks 5 and 6
Removing basic block 9
;; basic block 9, loop depth 1, count 0
;; prev block 2, next block 3
;; pred:      
;; succ:       3 [100.0%]  (fallthru)
<bb 9>:
Invalid sum of incoming frequencies 0, should be 819


Removing basic block 10
;; basic block 10, loop depth 1, count 0
;; prev block 5, next block 7
;; pred:      
;; succ:       3 [100.0%]  (fallthru)
<bb 10>:
Invalid sum of incoming frequencies 0, should be 8281
goto <bb 3>;


Scope blocks after cleanups:

{ Scope block #0 
  struct control_flow_graph * cfgD.4211;
  struct edge * eD.4212;

}
mark_edges ()
{
  struct edge * eD.4212;
  struct control_flow_graph * cfgD.4211;
  edge_type D.5581;
  struct function * current_function.6D.5580;

  # BLOCK 2 freq:900
  # PRED: ENTRY [100.0%]  (fallthru,exec)
  # VUSE <.MEMD.5613_9(D)>
  current_function.6D.5580_2 = current_functionD.4113;
  # VUSE <.MEMD.5613_9(D)>
  cfgD.4211_3 = current_function.6D.5580_2->cfgD.4162;
  # DEBUG cfgD.4211 => cfgD.4211_3
  # VUSE <.MEMD.5613_9(D)>
  eD.4212_4 = cfgD.4211_3->edgeD.4159;
  # DEBUG eD.4212 => eD.4212_4
  # DEBUG eD.4212 => eD.4212_4
  if (eD.4212_4 != 0B)
    goto <bb 3>;
  else
    goto <bb 6>;
  # SUCC: 3 [91.0%]  (true,exec) 6 [9.0%]  (false,exec)

  # BLOCK 3 freq:9100
  # PRED: 5 [91.0%]  (true,exec) 2 [91.0%]  (true,exec)
  # eD.4212_13 = PHI <eD.4212_6(5), eD.4212_4(2)>
  # .MEMD.5613_14 = PHI <.MEMD.5613_7(5), .MEMD.5613_9(D)(2)>
  # VUSE <.MEMD.5613_14>
  D.5581_5 = eD.4212_13->typeD.4133;
  if (D.5581_5 == 0)
    goto <bb 4>;
  else
    goto <bb 5>;
  # SUCC: 4 [29.0%]  (true,exec) 5 [71.0%]  (false,exec)

  # BLOCK 4 freq:2639
  # PRED: 3 [29.0%]  (true,exec)
  # .MEMD.5613_10 = VDEF <.MEMD.5613_14>
  mark_edgeD.4204 (eD.4212_13);
  # SUCC: 5 [100.0%]  (fallthru,exec)

  # BLOCK 5 freq:9100
  # PRED: 3 [71.0%]  (false,exec) 4 [100.0%]  (fallthru,exec)
  # .MEMD.5613_7 = PHI <.MEMD.5613_14(3), .MEMD.5613_10(4)>
  # VUSE <.MEMD.5613_7>
  eD.4212_6 = eD.4212_13->nextD.4136;
  # DEBUG eD.4212 => eD.4212_6
  # DEBUG eD.4212 => eD.4212_6
  if (eD.4212_6 != 0B)
    goto <bb 3>;
  else
    goto <bb 6>;
  # SUCC: 3 [91.0%]  (true,exec) 6 [9.0%]  (false,exec)

  # BLOCK 6 freq:900
  # PRED: 5 [9.0%]  (false,exec) 2 [9.0%]  (false,exec)
  return;
  # SUCC: EXIT [100.0%] 

}



;; Function calc_max_distance_recursive (calc_max_distance_recursive)


Pass statistics:
----------------

;; 2 loops found
;;
;; Loop 0
;;  header 0, latch 1
;;  depth 0, outer -1
;;  nodes: 0 1 2 3 4 5 6 7 8 9
;;
;; Loop 1
;;  header 7, latch 6
;;  depth 1, outer 0
;;  nodes: 7 6 4 5
;; 2 succs { 3 9 }
;; 3 succs { 7 }
;; 4 succs { 6 5 }
;; 5 succs { 6 }
;; 6 succs { 7 }
;; 7 succs { 4 8 }
;; 8 succs { 9 }
;; 9 succs { 1 }
Duplicating header of the loop 1 up to edge 7->4.


Registering new PHI nodes in block #10

Updating SSA information for statement # DEBUG ve => ve_3

Updating SSA information for statement # DEBUG max => max_2

Updating SSA information for statement if (ve_3 != 0B)



Registering new PHI nodes in block #4

Updating SSA information for statement e_8 = ve_3->edge;

Updating SSA information for statement D.5573_9 = e_8->type;



Registering new PHI nodes in block #5

Updating SSA information for statement D.5576_10 = e_8->source;

Updating SSA information for statement val_11 = calc_max_distance_recursive (D.5576_10);

Updating SSA information for statement max_12 = MAX_EXPR <val_11, max_2>;



Registering new PHI nodes in block #6

Updating SSA information for statement ve_13 = ve_3->next;



Registering new PHI nodes in block #7

Updating SSA information for statement # DEBUG ve => ve_3

Updating SSA information for statement # DEBUG max => max_2

Updating SSA information for statement if (ve_3 != 0B)



Registering new PHI nodes in block #8

Updating SSA information for statement bb_5(D)->max_distance = D.5577_14;


DFA Statistics for calc_max_distance_recursive

---------------------------------------------------------
                                Number of        Memory
                                instances         used 
---------------------------------------------------------
Referenced variables                     11         44b
Variables annotated                      11        132b
USE operands                             28        112b
DEF operands                             10         40b
VUSE operands                             9         36b
VDEF operands                             2          8b
PHI nodes                                14        840b
PHI arguments                            22        528b
---------------------------------------------------------
Total memory used by DFA/SSA data                 1740b
---------------------------------------------------------

Average number of arguments per PHI node: 1.6 (max: 2)


Hash table statistics:
    def_blocks:   size 31, 6 elements, 0.256410 collision/search ratio
    repl_tbl:     size 31, 7 elements, 0.117647 collision/search ratio


SSA replacement table
N_i -> { O_1 ... O_j } means that N_i replaces O_1, ..., O_j

ve_23 -> { ve_3 }
max_24 -> { max_2 }
.MEM_25 -> { .MEM_17 }
max_26 -> { max_2 }
ve_27 -> { ve_3 }
.MEM_28 -> { .MEM_17 }
.MEM_29 -> { .MEM_17 }

Number of virtual NEW -> OLD mappings:       3
Number of real NEW -> OLD mappings:          4
Number of total NEW -> OLD mappings:         7

Number of virtual symbols: 3


Incremental SSA update started at block: 10

Number of blocks in CFG: 11
Number of blocks to update: 6 ( 55%)

Affected blocks: 4 5 6 7 8 10 



Pass statistics:
----------------

Merging blocks 3 and 10
Merging blocks 6 and 7
Removing basic block 11
;; basic block 11, loop depth 1, count 0
;; prev block 3, next block 4
;; pred:      
;; succ:       4 [100.0%]  (fallthru)
<bb 11>:
Invalid sum of incoming frequencies 0, should be 819


Removing basic block 12
;; basic block 12, loop depth 1, count 0
;; prev block 6, next block 8
;; pred:      
;; succ:       4 [100.0%]  (fallthru)
<bb 12>:
Invalid sum of incoming frequencies 0, should be 8281
goto <bb 4>;


Scope blocks after cleanups:

{ Scope block #0 
  intD.0 valD.4219;
  intD.0 maxD.4220;
  struct vec_edge * veD.4221;
  struct edge * eD.4222;

}
calc_max_distance_recursive (struct basic_block * bbD.4216)
{
  struct edge * eD.4222;
  struct vec_edge * veD.4221;
  intD.0 maxD.4220;
  intD.0 valD.4219;
  intD.0 D.5578;
  intD.0 D.5577;
  struct basic_block * D.5576;
  edge_type D.5573;
  intD.0 D.5570;

  # BLOCK 2 freq:1475
  # PRED: ENTRY [100.0%]  (fallthru,exec)
  # DEBUG maxD.4220 => 0
  # VUSE <.MEMD.5614_19(D)>
  D.5570_6 = bbD.4216_5(D)->max_distanceD.4146;
  if (D.5570_6 == 0)
    goto <bb 3>;
  else
    goto <bb 8>;
  # SUCC: 3 [61.0%]  (true,exec) 8 [39.0%]  (false,exec)

  # BLOCK 3 freq:900
  # PRED: 2 [61.0%]  (true,exec)
  # VUSE <.MEMD.5614_19(D)>
  veD.4221_7 = bbD.4216_5(D)->predD.4147;
  # DEBUG veD.4221 => veD.4221_7
  # DEBUG veD.4221 => veD.4221_7
  # DEBUG maxD.4220 => 0
  if (veD.4221_7 != 0B)
    goto <bb 4>;
  else
    goto <bb 7>;
  # SUCC: 4 [91.0%]  (true,exec) 7 [9.0%]  (false,exec)

  # BLOCK 4 freq:9100
  # PRED: 6 [91.0%]  (true,exec) 3 [91.0%]  (true,exec)
  # maxD.4220_24 = PHI <maxD.4220_1(6), 0(3)>
  # veD.4221_27 = PHI <veD.4221_13(6), veD.4221_7(3)>
  # .MEMD.5614_28 = PHI <.MEMD.5614_16(6), .MEMD.5614_19(D)(3)>
  # VUSE <.MEMD.5614_28>
  eD.4222_8 = veD.4221_27->edgeD.4138;
  # DEBUG eD.4222 => eD.4222_8
  # VUSE <.MEMD.5614_28>
  D.5573_9 = eD.4222_8->typeD.4133;
  if (D.5573_9 == 3)
    goto <bb 6>;
  else
    goto <bb 5>;
  # SUCC: 6 [48.8%]  (true,exec) 5 [51.2%]  (false,exec)

  # BLOCK 5 freq:4662
  # PRED: 4 [51.2%]  (false,exec)
  # VUSE <.MEMD.5614_28>
  D.5576_10 = eD.4222_8->sourceD.4134;
  # .MEMD.5614_20 = VDEF <.MEMD.5614_28>
  valD.4219_11 = calc_max_distance_recursiveD.4217 (D.5576_10);
  # DEBUG valD.4219 => valD.4219_11
  maxD.4220_12 = MAX_EXPR <valD.4219_11, maxD.4220_24>;
  # DEBUG maxD.4220 => maxD.4220_12
  # SUCC: 6 [100.0%]  (fallthru,exec)

  # BLOCK 6 freq:9100
  # PRED: 4 [48.8%]  (true,exec) 5 [100.0%]  (fallthru,exec)
  # maxD.4220_1 = PHI <maxD.4220_24(4), maxD.4220_12(5)>
  # .MEMD.5614_16 = PHI <.MEMD.5614_28(4), .MEMD.5614_20(5)>
  # DEBUG maxD.4220 => maxD.4220_1
  # VUSE <.MEMD.5614_16>
  veD.4221_13 = veD.4221_27->nextD.4139;
  # DEBUG veD.4221 => veD.4221_13
  # DEBUG veD.4221 => veD.4221_13
  # DEBUG maxD.4220 => maxD.4220_1
  if (veD.4221_13 != 0B)
    goto <bb 4>;
  else
    goto <bb 7>;
  # SUCC: 4 [91.0%]  (true,exec) 7 [9.0%]  (false,exec)

  # BLOCK 7 freq:900
  # PRED: 6 [9.0%]  (false,exec) 3 [9.0%]  (false,exec)
  # maxD.4220_22 = PHI <maxD.4220_1(6), 0(3)>
  # .MEMD.5614_29 = PHI <.MEMD.5614_16(6), .MEMD.5614_19(D)(3)>
  D.5577_14 = maxD.4220_22 + 1;
  # .MEMD.5614_21 = VDEF <.MEMD.5614_29>
  bbD.4216_5(D)->max_distanceD.4146 = D.5577_14;
  # SUCC: 8 [100.0%]  (fallthru,exec)

  # BLOCK 8 freq:1475
  # PRED: 2 [39.0%]  (false,exec) 7 [100.0%]  (fallthru,exec)
  # .MEMD.5614_18 = PHI <.MEMD.5614_19(D)(2), .MEMD.5614_21(7)>
  # VUSE <.MEMD.5614_18>
  D.5578_15 = bbD.4216_5(D)->max_distanceD.4146;
  return D.5578_15;
  # SUCC: EXIT [100.0%] 

}



;; Function calc_max_distance (calc_max_distance)


Pass statistics:
----------------

;; 2 loops found
;;
;; Loop 0
;;  header 0, latch 1
;;  depth 0, outer -1
;;  nodes: 0 1 2 3 4 5 6 7 8
;;
;; Loop 1
;;  header 7, latch 6
;;  depth 1, outer 0
;;  nodes: 7 6 3 4 5
;; 2 succs { 7 }
;; 3 succs { 4 6 }
;; 4 succs { 5 6 }
;; 5 succs { 6 }
;; 6 succs { 7 }
;; 7 succs { 3 8 }
;; 8 succs { 1 }
Duplicating header of the loop 1 up to edge 7->3.


Registering new PHI nodes in block #9

Updating SSA information for statement # DEBUG bb => bb_3

Updating SSA information for statement # DEBUG max => max_2

Updating SSA information for statement if (bb_3 != 0B)



Registering new PHI nodes in block #3

Updating SSA information for statement D.5563_11 = bb_3->max_distance;



Registering new PHI nodes in block #4

Updating SSA information for statement val_12 = calc_max_distance_recursive (bb_3);

Updating SSA information for statement if (max_2 <= val_12)



Registering new PHI nodes in block #5



Registering new PHI nodes in block #6

Updating SSA information for statement bb_16 = bb_3->next;



Registering new PHI nodes in block #7

Updating SSA information for statement # DEBUG bb => bb_3

Updating SSA information for statement # DEBUG max => max_2

Updating SSA information for statement if (bb_3 != 0B)



Registering new PHI nodes in block #8

Updating SSA information for statement D.5562_18 = cfg.4_6->exit;

Updating SSA information for statement D.5562_18->max_distance = max_4;


DFA Statistics for calc_max_distance

---------------------------------------------------------
                                Number of        Memory
                                instances         used 
---------------------------------------------------------
Referenced variables                      8         32b
Variables annotated                       8         96b
USE operands                             24         96b
DEF operands                              9         36b
VUSE operands                            11         44b
VDEF operands                             5         20b
PHI nodes                                13        780b
PHI arguments                            22        528b
---------------------------------------------------------
Total memory used by DFA/SSA data                 1632b
---------------------------------------------------------

Average number of arguments per PHI node: 1.7 (max: 3)


Hash table statistics:
    def_blocks:   size 31, 6 elements, 0.000000 collision/search ratio
    repl_tbl:     size 31, 7 elements, 0.117647 collision/search ratio


SSA replacement table
N_i -> { O_1 ... O_j } means that N_i replaces O_1, ..., O_j

.MEM_9 -> { .MEM_20 }
bb_17 -> { bb_3 }
max_27 -> { max_2 }
bb_28 -> { bb_3 }
max_29 -> { max_2 }
.MEM_30 -> { .MEM_20 }
.MEM_31 -> { .MEM_20 }

Number of virtual NEW -> OLD mappings:       3
Number of real NEW -> OLD mappings:          4
Number of total NEW -> OLD mappings:         7

Number of virtual symbols: 3


Incremental SSA update started at block: 9

Number of blocks in CFG: 10
Number of blocks to update: 6 ( 60%)

Affected blocks: 3 4 6 7 8 9 



Pass statistics:
----------------

Merging blocks 2 and 9
Merging blocks 6 and 7
Removing basic block 10
;; basic block 10, loop depth 1, count 0
;; prev block 2, next block 3
;; pred:      
;; succ:       3 [100.0%]  (fallthru)
<bb 10>:
Invalid sum of incoming frequencies 0, should be 819


Removing basic block 11
;; basic block 11, loop depth 1, count 0
;; prev block 6, next block 8
;; pred:      
;; succ:       3 [100.0%]  (fallthru)
<bb 11>:
Invalid sum of incoming frequencies 0, should be 8281
goto <bb 3>;


Scope blocks after cleanups:

{ Scope block #0 
  intD.0 valD.4230;
  intD.0 maxD.4231;
  struct basic_block * bbD.4232;

}
calc_max_distance ()
{
  struct basic_block * bbD.4232;
  intD.0 maxD.4231;
  intD.0 valD.4230;
  intD.0 D.5563;
  struct basic_block * D.5562;
  struct control_flow_graph * cfg.4D.5561;

  # BLOCK 2 freq:900
  # PRED: ENTRY [100.0%]  (fallthru,exec)
  # DEBUG maxD.4231 => 0
  # .MEMD.5615_22 = VDEF <.MEMD.5615_21(D)>
  depth_first_searchD.4185 ();
  # .MEMD.5615_23 = VDEF <.MEMD.5615_22>
  mark_edgesD.4209 ();
  # VUSE <.MEMD.5615_23>
  cfg.4D.5561_6 = cfgD.4174;
  # VUSE <.MEMD.5615_23>
  D.5562_7 = cfg.4D.5561_6->exitD.4156;
  # .MEMD.5615_24 = VDEF <.MEMD.5615_23>
  maxD.4231_8 = calc_max_distance_recursiveD.4217 (D.5562_7);
  # DEBUG maxD.4231 => maxD.4231_8
  # VUSE <.MEMD.5615_24>
  bbD.4232_10 = cfg.4D.5561_6->bbD.4157;
  # DEBUG bbD.4232 => bbD.4232_10
  # DEBUG bbD.4232 => bbD.4232_10
  # DEBUG maxD.4231 => maxD.4231_8
  if (bbD.4232_10 != 0B)
    goto <bb 3>;
  else
    goto <bb 7>;
  # SUCC: 3 [91.0%]  (true,exec) 7 [9.0%]  (false,exec)

  # BLOCK 3 freq:9100
  # PRED: 6 [91.0%]  (true,exec) 2 [91.0%]  (true,exec)
  # maxD.4231_27 = PHI <maxD.4231_1(6), maxD.4231_8(2)>
  # bbD.4232_28 = PHI <bbD.4232_16(6), bbD.4232_10(2)>
  # .MEMD.5615_30 = PHI <.MEMD.5615_19(6), .MEMD.5615_24(2)>
  # VUSE <.MEMD.5615_30>
  D.5563_11 = bbD.4232_28->max_distanceD.4146;
  if (D.5563_11 == 0)
    goto <bb 4>;
  else
    goto <bb 6>;
  # SUCC: 4 [29.0%]  (true,exec) 6 [71.0%]  (false,exec)

  # BLOCK 4 freq:2639
  # PRED: 3 [29.0%]  (true,exec)
  # .MEMD.5615_25 = VDEF <.MEMD.5615_30>
  valD.4230_12 = calc_max_distance_recursiveD.4217 (bbD.4232_28);
  # DEBUG valD.4230 => valD.4230_12
  if (maxD.4231_27 <= valD.4230_12)
    goto <bb 5>;
  else
    goto <bb 6>;
  # SUCC: 5 [50.0%]  (true,exec) 6 [50.0%]  (false,exec)

  # BLOCK 5 freq:1319
  # PRED: 4 [50.0%]  (true,exec)
  maxD.4231_13 = valD.4230_12 + 1;
  # SUCC: 6 [100.0%]  (fallthru,exec)

  # BLOCK 6 freq:9100
  # PRED: 3 [71.0%]  (false,exec) 4 [50.0%]  (false,exec) 5 [100.0%]  (fallthru,exec)
  # maxD.4231_1 = PHI <maxD.4231_27(3), maxD.4231_27(4), maxD.4231_13(5)>
  # .MEMD.5615_19 = PHI <.MEMD.5615_30(3), .MEMD.5615_25(4), .MEMD.5615_25(5)>
  # DEBUG maxD.4231 => maxD.4231_1
  # VUSE <.MEMD.5615_19>
  bbD.4232_16 = bbD.4232_28->nextD.4151;
  # DEBUG bbD.4232 => bbD.4232_16
  # DEBUG bbD.4232 => bbD.4232_16
  # DEBUG maxD.4231 => maxD.4231_1
  if (bbD.4232_16 != 0B)
    goto <bb 3>;
  else
    goto <bb 7>;
  # SUCC: 3 [91.0%]  (true,exec) 7 [9.0%]  (false,exec)

  # BLOCK 7 freq:900
  # PRED: 6 [9.0%]  (false,exec) 2 [9.0%]  (false,exec)
  # maxD.4231_4 = PHI <maxD.4231_1(6), maxD.4231_8(2)>
  # .MEMD.5615_31 = PHI <.MEMD.5615_19(6), .MEMD.5615_24(2)>
  # VUSE <.MEMD.5615_31>
  D.5562_18 = cfg.4D.5561_6->exitD.4156;
  # .MEMD.5615_26 = VDEF <.MEMD.5615_31>
  D.5562_18->max_distanceD.4146 = maxD.4231_4;
  return;
  # SUCC: EXIT [100.0%] 

}



;; Function fine_tune_cfg (fine_tune_cfg)


Pass statistics:
----------------

;; 2 loops found
;;
;; Loop 0
;;  header 0, latch 1
;;  depth 0, outer -1
;;  nodes: 0 1 2 3 4 5
;;
;; Loop 1
;;  header 4, latch 3
;;  depth 1, outer 0
;;  nodes: 4 3
;; 2 succs { 4 }
;; 3 succs { 4 }
;; 4 succs { 3 5 }
;; 5 succs { 1 }
Duplicating header of the loop 1 up to edge 4->3.


Registering new PHI nodes in block #6

Updating SSA information for statement current_function.1_13 = current_function;

Updating SSA information for statement if (current_function.1_2 != 0B)



Registering new PHI nodes in block #3

Updating SSA information for statement cfg.2_4 = current_function.1_2->cfg;

Updating SSA information for statement cfg = cfg.2_4;



Registering new PHI nodes in block #4

Updating SSA information for statement current_function.1_2 = current_function;

Updating SSA information for statement if (current_function.1_2 != 0B)



Registering new PHI nodes in block #5

Updating SSA information for statement return;


DFA Statistics for fine_tune_cfg

---------------------------------------------------------
                                Number of        Memory
                                instances         used 
---------------------------------------------------------
Referenced variables                      8         32b
Variables annotated                       8         96b
USE operands                              7         28b
DEF operands                              6         24b
VUSE operands                            10         40b
VDEF operands                             4         16b
PHI nodes                                 4        240b
PHI arguments                             6        144b
---------------------------------------------------------
Total memory used by DFA/SSA data                  620b
---------------------------------------------------------

Average number of arguments per PHI node: 1.5 (max: 2)


Hash table statistics:
    def_blocks:   size 31, 4 elements, 0.000000 collision/search ratio
    repl_tbl:     size 31, 4 elements, 0.000000 collision/search ratio


SSA replacement table
N_i -> { O_1 ... O_j } means that N_i replaces O_1, ..., O_j

.MEM_3 -> { .MEM_7 }
current_function.1_13 -> { current_function.1_2 }
current_function.1_14 -> { current_function.1_2 }
.MEM_15 -> { .MEM_7 }

Number of virtual NEW -> OLD mappings:       2
Number of real NEW -> OLD mappings:          2
Number of total NEW -> OLD mappings:         4

Number of virtual symbols: 2


Incremental SSA update started at block: 6

Number of blocks in CFG: 7
Number of blocks to update: 4 ( 57%)

Affected blocks: 3 4 5 6 



Pass statistics:
----------------

Merging blocks 2 and 6
Merging blocks 3 and 4
Removing basic block 7
;; basic block 7, loop depth 1, count 0
;; prev block 2, next block 3
;; pred:      
;; succ:       3 [100.0%]  (fallthru)
<bb 7>:
Invalid sum of incoming frequencies 0, should be 819


Removing basic block 8
;; basic block 8, loop depth 1, count 0
;; prev block 3, next block 5
;; pred:      
;; succ:       3 [100.0%]  (fallthru)
<bb 8>:
Invalid sum of incoming frequencies 0, should be 8281
goto <bb 3>;


Scope blocks after cleanups:

{ Scope block #0 

}
fine_tune_cfg ()
{
  struct function * current_function.3D.5560;
  struct control_flow_graph * cfg.2D.5559;
  struct function * current_function.1D.5558;
  struct function * first_function.0D.5557;

  # BLOCK 2 freq:900
  # PRED: ENTRY [100.0%]  (fallthru,exec)
  # VUSE <.MEMD.5616_8(D)>
  first_function.0D.5557_1 = first_functionD.4111;
  # .MEMD.5616_9 = VDEF <.MEMD.5616_8(D)>
  current_functionD.4113 = first_function.0D.5557_1;
  # VUSE <.MEMD.5616_9>
  current_function.1D.5558_13 = current_functionD.4113;
  if (current_function.1D.5558_13 != 0B)
    goto <bb 3>;
  else
    goto <bb 4>;
  # SUCC: 3 [91.0%]  (true,exec) 4 [9.0%]  (false,exec)

  # BLOCK 3 freq:9100
  # PRED: 3 [91.0%]  (true,exec) 2 [91.0%]  (true,exec)
  # current_function.1D.5558_14 = PHI <current_function.1D.5558_2(3), current_function.1D.5558_13(2)>
  # .MEMD.5616_15 = PHI <.MEMD.5616_12(3), .MEMD.5616_9(2)>
  # VUSE <.MEMD.5616_15>
  cfg.2D.5559_4 = current_function.1D.5558_14->cfgD.4162;
  # .MEMD.5616_10 = VDEF <.MEMD.5616_15>
  cfgD.4174 = cfg.2D.5559_4;
  # .MEMD.5616_11 = VDEF <.MEMD.5616_10>
  calc_max_distanceD.4228 ();
  # VUSE <.MEMD.5616_11>
  current_function.1D.5558_5 = current_functionD.4113;
  # VUSE <.MEMD.5616_11>
  current_function.3D.5560_6 = current_function.1D.5558_5->nextD.4163;
  # .MEMD.5616_12 = VDEF <.MEMD.5616_11>
  current_functionD.4113 = current_function.3D.5560_6;
  # VUSE <.MEMD.5616_12>
  current_function.1D.5558_2 = current_functionD.4113;
  if (current_function.1D.5558_2 != 0B)
    goto <bb 3>;
  else
    goto <bb 4>;
  # SUCC: 3 [91.0%]  (true,exec) 4 [9.0%]  (false,exec)

  # BLOCK 4 freq:900
  # PRED: 3 [9.0%]  (false,exec) 2 [9.0%]  (false,exec)
  return;
  # SUCC: EXIT [100.0%] 

}


