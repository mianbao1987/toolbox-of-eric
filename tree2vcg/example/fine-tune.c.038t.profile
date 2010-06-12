
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
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = ve_1)
(get_scalar_evolution 
  (scalar = ve_1)
  (scalar_evolution = ))
(analyze_initial_condition 
  (loop_phi_node = 
ve_1 = PHI <ve_3(2), ve_7(5)>
)
  (init_cond = ve_3))
(analyze_evolution_in_loop 
  (loop_phi_node = ve_1 = PHI <ve_3(2), ve_7(5)>
)
  (evolution_function = scev_not_known))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = ve_1)
  (scalar_evolution = ve_1))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = ve_1)
(get_scalar_evolution 
  (scalar = ve_1)
  (scalar_evolution = ve_1))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = ve_1)
  (scalar_evolution = ve_1))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = ve_1)
(get_scalar_evolution 
  (scalar = ve_1)
  (scalar_evolution = ve_1))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = ve_1)
  (scalar_evolution = ve_1))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = ve_1)
(get_scalar_evolution 
  (scalar = ve_1)
  (scalar_evolution = ve_1))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = ve_1)
  (scalar_evolution = ve_1))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = D.5604_6)
(get_scalar_evolution 
  (scalar = D.5604_6)
  (scalar_evolution = ))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = D.5604_6)
  (scalar_evolution = D.5604_6))
)
(instantiate_scev 
  (instantiate_below = 2)
  (evolution_loop = 1)
  (chrec = D.5604_6)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = D.5604_6)
(get_scalar_evolution 
  (scalar = D.5604_6)
  (scalar_evolution = D.5604_6))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = D.5604_6)
  (scalar_evolution = D.5604_6))
)
  (res = scev_not_known))
1 edges in bb 2 predicted to even probabilities
Predictions for bb 3
  DS theory heuristics: 29.0%
  first match heuristics (ignored): 29.0%
  combined heuristics: 29.0%
  call heuristics: 29.0%
1 edges in bb 4 predicted to even probabilities
1 edges in bb 5 predicted to even probabilities
Predictions for bb 6
  DS theory heuristics (ignored): 98.3%
  first match heuristics: 91.0%
  combined heuristics: 91.0%
  pointer (on trees) heuristics (ignored): 85.0%
  loop exit heuristics: 91.0%
1 edges in bb 7 predicted to even probabilities

;; Function search

;; 
8 basic blocks, 9 edges, last basic block 8.

Basic block 2 (new, reachable)
Predecessors:  ENTRY [100.0%]  (fallthru,exec)
Successors:  6 [100.0%]  (fallthru,exec)

Basic block 3 (new, reachable)
Predecessors:  6 [91.0%]  (true,exec)
Successors:  4 [29.0%]  (true,exec) 5 [71.0%]  (false,exec)

Basic block 4 (new, reachable)
Predecessors:  3 [29.0%]  (true,exec)
Successors:  5 [100.0%]  (fallthru,exec)

Basic block 5 (new, reachable)
Predecessors:  3 [71.0%]  (false,exec) 4 [100.0%]  (fallthru,exec)
Successors:  6 [100.0%]  (fallthru,dfs_back,exec)

Basic block 6 (new, reachable)
Predecessors:  2 [100.0%]  (fallthru,exec) 5 [100.0%]  (fallthru,dfs_back,exec)
Successors:  3 [91.0%]  (true,exec) 7 [9.0%]  (false,exec)

Basic block 7 (new, reachable)
Predecessors:  6 [9.0%]  (false,exec)
Successors:  EXIT [100.0%] 



CFG Statistics for search

---------------------------------------------------------
                                Number of        Memory
                                instances         used 
---------------------------------------------------------
Basic blocks                              8        512b
Edges                                     8        352b
---------------------------------------------------------
Total memory used by CFG data                      864b
---------------------------------------------------------

Coalesced label blocks: 0 (Max so far: 0)

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
  goto <bb 6>;
  # SUCC: 6 [100.0%]  (fallthru,exec)

  # BLOCK 3 freq:9100
  # PRED: 6 [91.0%]  (true,exec)
  # VUSE <.MEMD.5609_12>
  eD.4180_4 = veD.4179_1->edgeD.4138;
  # DEBUG eD.4180 => eD.4180_4
  # VUSE <.MEMD.5609_12>
  succ_bbD.4178_5 = eD.4180_4->targetD.4135;
  # DEBUG succ_bbD.4178 => succ_bbD.4178_5
  # VUSE <.MEMD.5609_12>
  D.5604_6 = succ_bbD.4178_5->visitedD.4144;
  if (D.5604_6 == 0)
    goto <bb 4>;
  else
    goto <bb 5>;
  # SUCC: 4 [29.0%]  (true,exec) 5 [71.0%]  (false,exec)

  # BLOCK 4 freq:2639
  # PRED: 3 [29.0%]  (true,exec)
  # .MEMD.5609_15 = VDEF <.MEMD.5609_12>
  eD.4180_4->typeD.4133 = 1;
  # .MEMD.5609_16 = VDEF <.MEMD.5609_15>
  searchD.4176 (succ_bbD.4178_5);
  # SUCC: 5 [100.0%]  (fallthru,exec)

  # BLOCK 5 freq:9100
  # PRED: 3 [71.0%]  (false,exec) 4 [100.0%]  (fallthru,exec)
  # .MEMD.5609_11 = PHI <.MEMD.5609_12(3), .MEMD.5609_16(4)>
  # VUSE <.MEMD.5609_11>
  veD.4179_7 = veD.4179_1->nextD.4139;
  # DEBUG veD.4179 => veD.4179_7
  # SUCC: 6 [100.0%]  (fallthru,dfs_back,exec)

  # BLOCK 6 freq:10000
  # PRED: 2 [100.0%]  (fallthru,exec) 5 [100.0%]  (fallthru,dfs_back,exec)
  # veD.4179_1 = PHI <veD.4179_3(2), veD.4179_7(5)>
  # .MEMD.5609_12 = PHI <.MEMD.5609_14(2), .MEMD.5609_11(5)>
  # DEBUG veD.4179 => veD.4179_1
  if (veD.4179_1 != 0B)
    goto <bb 3>;
  else
    goto <bb 7>;
  # SUCC: 3 [91.0%]  (true,exec) 7 [9.0%]  (false,exec)

  # BLOCK 7 freq:900
  # PRED: 6 [9.0%]  (false,exec)
  # VUSE <.MEMD.5609_12>
  count.10D.5607_8 = countD.4173;
  # .MEMD.5609_17 = VDEF <.MEMD.5609_12>
  bbD.4175_2(D)->dfs_orderD.4145 = count.10D.5607_8;
  # VUSE <.MEMD.5609_17>
  count.10D.5607_9 = countD.4173;
  count.11D.5608_10 = count.10D.5607_9 - 1;
  # .MEMD.5609_18 = VDEF <.MEMD.5609_17>
  countD.4173 = count.11D.5608_10;
  return;
  # SUCC: EXIT [100.0%] 

}



Pass statistics:
----------------


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
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = bb_1)
(get_scalar_evolution 
  (scalar = bb_1)
  (scalar_evolution = ))
(analyze_initial_condition 
  (loop_phi_node = 
bb_1 = PHI <bb_3(2), bb_4(3)>
)
  (init_cond = bb_3))
(analyze_evolution_in_loop 
  (loop_phi_node = bb_1 = PHI <bb_3(2), bb_4(3)>
)
  (evolution_function = scev_not_known))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = bb_1)
  (scalar_evolution = bb_1))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = bb_1)
(get_scalar_evolution 
  (scalar = bb_1)
  (scalar_evolution = bb_1))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = bb_1)
  (scalar_evolution = bb_1))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = bb_1)
(get_scalar_evolution 
  (scalar = bb_1)
  (scalar_evolution = bb_1))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = bb_1)
  (scalar_evolution = bb_1))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = bb_1)
(get_scalar_evolution 
  (scalar = bb_1)
  (scalar_evolution = bb_1))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = bb_1)
  (scalar_evolution = bb_1))
)
1 edges in bb 2 predicted to even probabilities
1 edges in bb 3 predicted to even probabilities
Predictions for bb 4
  DS theory heuristics (ignored): 98.3%
  first match heuristics: 91.0%
  combined heuristics: 91.0%
  pointer (on trees) heuristics (ignored): 85.0%
  loop exit heuristics: 91.0%
1 edges in bb 5 predicted to even probabilities

;; Function depth_first_search

;; 
6 basic blocks, 6 edges, last basic block 6.

Basic block 2 (new, reachable)
Predecessors:  ENTRY [100.0%]  (fallthru,exec)
Successors:  4 [100.0%]  (fallthru,exec)

Basic block 3 (new, reachable)
Predecessors:  4 [91.0%]  (true,exec)
Successors:  4 [100.0%]  (fallthru,dfs_back,exec)

Basic block 4 (new, reachable)
Predecessors:  2 [100.0%]  (fallthru,exec) 3 [100.0%]  (fallthru,dfs_back,exec)
Successors:  3 [91.0%]  (true,exec) 5 [9.0%]  (false,exec)

Basic block 5 (new, reachable)
Predecessors:  4 [9.0%]  (false,exec)
Successors:  EXIT [100.0%] 



CFG Statistics for depth_first_search

---------------------------------------------------------
                                Number of        Memory
                                instances         used 
---------------------------------------------------------
Basic blocks                              6        384b
Edges                                     5        220b
---------------------------------------------------------
Total memory used by CFG data                      604b
---------------------------------------------------------

Coalesced label blocks: 0 (Max so far: 0)

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
  goto <bb 4>;
  # SUCC: 4 [100.0%]  (fallthru,exec)

  # BLOCK 3 freq:9100
  # PRED: 4 [91.0%]  (true,exec)
  # .MEMD.5610_11 = VDEF <.MEMD.5610_9>
  bbD.4187_1->visitedD.4144 = 0;
  # VUSE <.MEMD.5610_11>
  bbD.4187_4 = bbD.4187_1->nextD.4151;
  # DEBUG bbD.4187 => bbD.4187_4
  # SUCC: 4 [100.0%]  (fallthru,dfs_back,exec)

  # BLOCK 4 freq:10000
  # PRED: 2 [100.0%]  (fallthru,exec) 3 [100.0%]  (fallthru,dfs_back,exec)
  # bbD.4187_1 = PHI <bbD.4187_3(2), bbD.4187_4(3)>
  # .MEMD.5610_9 = PHI <.MEMD.5610_10(D)(2), .MEMD.5610_11(3)>
  # DEBUG bbD.4187 => bbD.4187_1
  if (bbD.4187_1 != 0B)
    goto <bb 3>;
  else
    goto <bb 5>;
  # SUCC: 3 [91.0%]  (true,exec) 5 [9.0%]  (false,exec)

  # BLOCK 5 freq:900
  # PRED: 4 [9.0%]  (false,exec)
  # VUSE <.MEMD.5610_9>
  cfg.8D.5601_5 = cfgD.4174;
  # VUSE <.MEMD.5610_9>
  count.9D.5602_6 = cfg.8D.5601_5->bb_numD.4153;
  # .MEMD.5610_12 = VDEF <.MEMD.5610_9>
  countD.4173 = count.9D.5602_6;
  # VUSE <.MEMD.5610_12>
  cfg.8D.5601_7 = cfgD.4174;
  # VUSE <.MEMD.5610_12>
  D.5603_8 = cfg.8D.5601_7->entryD.4155;
  # .MEMD.5610_13 = VDEF <.MEMD.5610_12>
  searchD.4176 (D.5603_8);
  return;
  # SUCC: EXIT [100.0%] 

}



Pass statistics:
----------------


;; Function is_ancestor (is_ancestor)


Pass statistics:
----------------

;; 3 loops found
;;
;; Loop 0
;;  header 0, latch 1
;;  depth 0, outer -1
;;  nodes: 0 1 2 3 4 5 6 7 8 9 10
;;
;; Loop 1
;;  header 3, latch 9
;;  depth 1, outer 0
;;  nodes: 3 9 6 8 4 7 5
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
;; 9 succs { 3 10 }
;; 10 succs { 1 }
;; 3 loops found
;;
;; Loop 0
;;  header 0, latch 1
;;  depth 0, outer -1
;;  nodes: 0 1 2 3 4 5 6 7 8 9 10
;;
;; Loop 1
;;  header 3, latch 9
;;  depth 1, outer 0
;;  nodes: 3 9 6 8 4 7 5
;;
;; Loop 2
;;  header 8, latch 7
;;  depth 2, outer 1
;;  nodes: 8 7 5
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = D.5599_15)
(get_scalar_evolution 
  (scalar = D.5599_15)
  (scalar_evolution = ))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = D.5599_15)
  (scalar_evolution = D.5599_15))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = D.5599_15)
(get_scalar_evolution 
  (scalar = D.5599_15)
  (scalar_evolution = D.5599_15))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = D.5599_15)
  (scalar_evolution = D.5599_15))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = bb_1)
(get_scalar_evolution 
  (scalar = bb_1)
  (scalar_evolution = ))
(analyze_initial_condition 
  (loop_phi_node = 
bb_1 = PHI <target_5(D)(2), bb_2(9)>
)
  (init_cond = target_5(D)))
(analyze_evolution_in_loop 
  (loop_phi_node = bb_1 = PHI <target_5(D)(2), bb_2(9)>
)
  (evolution_function = scev_not_known))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = bb_1)
  (scalar_evolution = bb_1))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = bb_1)
(get_scalar_evolution 
  (scalar = bb_1)
  (scalar_evolution = bb_1))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = bb_1)
  (scalar_evolution = bb_1))
)
(analyze_scalar_evolution 
  (loop_nb = 2)
  (scalar = ve_3)
(get_scalar_evolution 
  (scalar = ve_3)
  (scalar_evolution = ))
(analyze_initial_condition 
  (loop_phi_node = 
ve_3 = PHI <ve_9(4), ve_13(7)>
)
  (init_cond = ve_9))
(analyze_evolution_in_loop 
  (loop_phi_node = ve_3 = PHI <ve_9(4), ve_13(7)>
)
  (evolution_function = scev_not_known))
(set_scalar_evolution 
  instantiated_below = 4 
  (scalar = ve_3)
  (scalar_evolution = ve_3))
)
(analyze_scalar_evolution 
  (loop_nb = 2)
  (scalar = ve_3)
(get_scalar_evolution 
  (scalar = ve_3)
  (scalar_evolution = ve_3))
(set_scalar_evolution 
  instantiated_below = 4 
  (scalar = ve_3)
  (scalar_evolution = ve_3))
)
1 edges in bb 2 predicted to even probabilities
Predictions for bb 3
  DS theory heuristics (ignored): 0.5%
  first match heuristics: 4.5%
  combined heuristics: 4.5%
  pointer (on trees) heuristics (ignored): 15.0%
  early return (on trees) heuristics (ignored): 39.0%
  loop exit heuristics: 4.5%
1 edges in bb 4 predicted to even probabilities
Predictions for bb 5
  DS theory heuristics (ignored): 1.8%
  first match heuristics: 4.5%
  combined heuristics: 4.5%
  opcode values nonequal (on trees) heuristics (ignored): 28.0%
  loop exit heuristics: 4.5%
1 edges in bb 6 predicted to even probabilities
1 edges in bb 7 predicted to even probabilities
Predictions for bb 8
  DS theory heuristics (ignored): 99.2%
  first match heuristics: 95.5%
  combined heuristics: 95.5%
  pointer (on trees) heuristics (ignored): 85.0%
  loop exit heuristics: 95.5%
Predictions for bb 9
  DS theory heuristics (ignored): 97.2%
  first match heuristics: 86.0%
  combined heuristics: 86.0%
  pointer (on trees) heuristics (ignored): 85.0%
  loop branch heuristics: 86.0%
1 edges in bb 10 predicted to even probabilities

;; Function is_ancestor

;; 
11 basic blocks, 14 edges, last basic block 11.

Basic block 2 (new, reachable)
Predecessors:  ENTRY [100.0%]  (fallthru,exec)
Successors:  3 [100.0%]  (fallthru,exec)

Basic block 3 (new, reachable)
Predecessors:  2 [100.0%]  (fallthru,exec) 9 [86.0%]  (dfs_back,true,exec)
Successors:  10 [4.5%]  (true,exec) 4 [95.5%]  (false,exec)

Basic block 4 (new, reachable)
Predecessors:  3 [95.5%]  (false,exec)
Successors:  8 [100.0%]  (fallthru,exec)

Basic block 5 (new, reachable)
Predecessors:  8 [95.5%]  (true,exec)
Successors:  6 [4.5%]  (true,exec) 7 [95.5%]  (false,exec)

Basic block 6 (new, reachable)
Predecessors:  5 [4.5%]  (true,exec)
Successors:  9 [100.0%]  (fallthru,exec)

Basic block 7 (new, reachable)
Predecessors:  5 [95.5%]  (false,exec)
Successors:  8 [100.0%]  (fallthru,dfs_back,exec)

Basic block 8 (new, reachable)
Predecessors:  4 [100.0%]  (fallthru,exec) 7 [100.0%]  (fallthru,dfs_back,exec)
Successors:  5 [95.5%]  (true,exec) 9 [4.5%]  (false,exec)

Basic block 9 (new, reachable)
Predecessors:  6 [100.0%]  (fallthru,exec) 8 [4.5%]  (false,exec)
Successors:  3 [86.0%]  (dfs_back,true,exec) 10 [14.0%]  (false,exec)

Basic block 10 (new, reachable)
Predecessors:  3 [4.5%]  (true,exec) 9 [14.0%]  (false,exec)
Successors:  EXIT [100.0%] 



CFG Statistics for is_ancestor

---------------------------------------------------------
                                Number of        Memory
                                instances         used 
---------------------------------------------------------
Basic blocks                             11        704b
Edges                                    13        572b
---------------------------------------------------------
Total memory used by CFG data                     1276b
---------------------------------------------------------

Coalesced label blocks: 0 (Max so far: 0)

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
  # SUCC: 3 [100.0%]  (fallthru,exec)

  # BLOCK 3 freq:921
  # PRED: 2 [100.0%]  (fallthru,exec) 9 [86.0%]  (dfs_back,true,exec)
  # bbD.4195_1 = PHI <targetD.4192_5(D)(2), bbD.4195_2(9)>
  # DEBUG bbD.4195 => bbD.4195_1
  if (bbD.4195_1 == sourceD.4191_7(D))
    goto <bb 10>;
  else
    goto <bb 4>;
  # SUCC: 10 [4.5%]  (true,exec) 4 [95.5%]  (false,exec)

  # BLOCK 4 freq:880
  # PRED: 3 [95.5%]  (false,exec)
  # VUSE <.MEMD.5611_17(D)>
  veD.4196_9 = bbD.4195_1->predD.4147;
  # DEBUG veD.4196 => veD.4196_9
  goto <bb 8>;
  # SUCC: 8 [100.0%]  (fallthru,exec)

  # BLOCK 5 freq:9550
  # PRED: 8 [95.5%]  (true,exec)
  # VUSE <.MEMD.5611_17(D)>
  eD.4197_10 = veD.4196_3->edgeD.4138;
  # DEBUG eD.4197 => eD.4197_10
  # VUSE <.MEMD.5611_17(D)>
  D.5595_11 = eD.4197_10->typeD.4133;
  if (D.5595_11 == 1)
    goto <bb 6>;
  else
    goto <bb 7>;
  # SUCC: 6 [4.5%]  (true,exec) 7 [95.5%]  (false,exec)

  # BLOCK 6 freq:430
  # PRED: 5 [4.5%]  (true,exec)
  # VUSE <.MEMD.5611_17(D)>
  bbD.4195_12 = eD.4197_10->sourceD.4134;
  # DEBUG bbD.4195 => bbD.4195_12
  goto <bb 9>;
  # SUCC: 9 [100.0%]  (fallthru,exec)

  # BLOCK 7 freq:9120
  # PRED: 5 [95.5%]  (false,exec)
  # VUSE <.MEMD.5611_17(D)>
  veD.4196_13 = veD.4196_3->nextD.4139;
  # DEBUG veD.4196 => veD.4196_13
  # SUCC: 8 [100.0%]  (fallthru,dfs_back,exec)

  # BLOCK 8 freq:10000
  # PRED: 4 [100.0%]  (fallthru,exec) 7 [100.0%]  (fallthru,dfs_back,exec)
  # veD.4196_3 = PHI <veD.4196_9(4), veD.4196_13(7)>
  # DEBUG veD.4196 => veD.4196_3
  if (veD.4196_3 != 0B)
    goto <bb 5>;
  else
    goto <bb 9>;
  # SUCC: 5 [95.5%]  (true,exec) 9 [4.5%]  (false,exec)

  # BLOCK 9 freq:880
  # PRED: 6 [100.0%]  (fallthru,exec) 8 [4.5%]  (false,exec)
  # bbD.4195_2 = PHI <bbD.4195_12(6), bbD.4195_1(8)>
  # DEBUG bbD.4195 => bbD.4195_2
  # VUSE <.MEMD.5611_17(D)>
  cfg.7D.5598_14 = cfgD.4174;
  # VUSE <.MEMD.5611_17(D)>
  D.5599_15 = cfg.7D.5598_14->entryD.4155;
  if (D.5599_15 != bbD.4195_2)
    goto <bb 3>;
  else
    goto <bb 10>;
  # SUCC: 3 [86.0%]  (dfs_back,true,exec) 10 [14.0%]  (false,exec)

  # BLOCK 10 freq:165
  # PRED: 3 [4.5%]  (true,exec) 9 [14.0%]  (false,exec)
  # D.5594_4 = PHI <1(3), 0(9)>
  return D.5594_4;
  # SUCC: EXIT [100.0%] 

}



Pass statistics:
----------------


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
;; 1 loops found
;;
;; Loop 0
;;  header 0, latch 1
;;  depth 0, outer -1
;;  nodes: 0 1 2 3 4 5 6 7
Predictions for bb 2
  DS theory heuristics: 61.0%
  first match heuristics (ignored): 71.0%
  combined heuristics: 61.0%
  early return (on trees) heuristics: 39.0%
  call heuristics: 71.0%
1 edges in bb 3 predicted to even probabilities
Predictions for bb 4
  DS theory heuristics: 39.0%
  first match heuristics (ignored): 39.0%
  combined heuristics: 39.0%
  early return (on trees) heuristics: 39.0%
1 edges in bb 5 predicted to even probabilities
1 edges in bb 6 predicted to even probabilities
1 edges in bb 7 predicted to even probabilities

;; Function mark_edge

;; 
8 basic blocks, 9 edges, last basic block 8.

Basic block 2 (new, reachable)
Predecessors:  ENTRY [100.0%]  (fallthru,exec)
Successors:  3 [61.0%]  (true,exec) 4 [39.0%]  (false,exec)

Basic block 3 (new, reachable)
Predecessors:  2 [61.0%]  (true,exec)
Successors:  7 [100.0%]  (fallthru,exec)

Basic block 4 (new, reachable)
Predecessors:  2 [39.0%]  (false,exec)
Successors:  5 [39.0%]  (true,exec) 6 [61.0%]  (false,exec)

Basic block 5 (new, reachable)
Predecessors:  4 [39.0%]  (true,exec)
Successors:  7 [100.0%]  (fallthru,exec)

Basic block 6 (new, reachable)
Predecessors:  4 [61.0%]  (false,exec)
Successors:  7 [100.0%]  (fallthru,exec)

Basic block 7 (new, reachable)
Predecessors:  3 [100.0%]  (fallthru,exec) 5 [100.0%]  (fallthru,exec) 6 [100.0%]  (fallthru,exec)
Successors:  EXIT [100.0%] 



CFG Statistics for mark_edge

---------------------------------------------------------
                                Number of        Memory
                                instances         used 
---------------------------------------------------------
Basic blocks                              8        512b
Edges                                     8        352b
---------------------------------------------------------
Total memory used by CFG data                      864b
---------------------------------------------------------

Coalesced label blocks: 0 (Max so far: 0)

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



Pass statistics:
----------------


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
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = e_1)
(get_scalar_evolution 
  (scalar = e_1)
  (scalar_evolution = ))
(analyze_initial_condition 
  (loop_phi_node = 
e_1 = PHI <e_4(2), e_6(5)>
)
  (init_cond = e_4))
(analyze_evolution_in_loop 
  (loop_phi_node = e_1 = PHI <e_4(2), e_6(5)>
)
  (evolution_function = scev_not_known))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = e_1)
  (scalar_evolution = e_1))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = e_1)
(get_scalar_evolution 
  (scalar = e_1)
  (scalar_evolution = e_1))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = e_1)
  (scalar_evolution = e_1))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = e_1)
(get_scalar_evolution 
  (scalar = e_1)
  (scalar_evolution = e_1))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = e_1)
  (scalar_evolution = e_1))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = e_1)
(get_scalar_evolution 
  (scalar = e_1)
  (scalar_evolution = e_1))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = e_1)
  (scalar_evolution = e_1))
)
1 edges in bb 2 predicted to even probabilities
Predictions for bb 3
  DS theory heuristics: 29.0%
  first match heuristics (ignored): 29.0%
  combined heuristics: 29.0%
  call heuristics: 29.0%
1 edges in bb 4 predicted to even probabilities
1 edges in bb 5 predicted to even probabilities
Predictions for bb 6
  DS theory heuristics (ignored): 98.3%
  first match heuristics: 91.0%
  combined heuristics: 91.0%
  pointer (on trees) heuristics (ignored): 85.0%
  loop exit heuristics: 91.0%
1 edges in bb 7 predicted to even probabilities

;; Function mark_edges

;; 
8 basic blocks, 9 edges, last basic block 8.

Basic block 2 (new, reachable)
Predecessors:  ENTRY [100.0%]  (fallthru,exec)
Successors:  6 [100.0%]  (fallthru,exec)

Basic block 3 (new, reachable)
Predecessors:  6 [91.0%]  (true,exec)
Successors:  4 [29.0%]  (true,exec) 5 [71.0%]  (false,exec)

Basic block 4 (new, reachable)
Predecessors:  3 [29.0%]  (true,exec)
Successors:  5 [100.0%]  (fallthru,exec)

Basic block 5 (new, reachable)
Predecessors:  3 [71.0%]  (false,exec) 4 [100.0%]  (fallthru,exec)
Successors:  6 [100.0%]  (fallthru,dfs_back,exec)

Basic block 6 (new, reachable)
Predecessors:  2 [100.0%]  (fallthru,exec) 5 [100.0%]  (fallthru,dfs_back,exec)
Successors:  3 [91.0%]  (true,exec) 7 [9.0%]  (false,exec)

Basic block 7 (new, reachable)
Predecessors:  6 [9.0%]  (false,exec)
Successors:  EXIT [100.0%] 



CFG Statistics for mark_edges

---------------------------------------------------------
                                Number of        Memory
                                instances         used 
---------------------------------------------------------
Basic blocks                              8        512b
Edges                                     8        352b
---------------------------------------------------------
Total memory used by CFG data                      864b
---------------------------------------------------------

Coalesced label blocks: 0 (Max so far: 0)

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
  goto <bb 6>;
  # SUCC: 6 [100.0%]  (fallthru,exec)

  # BLOCK 3 freq:9100
  # PRED: 6 [91.0%]  (true,exec)
  # VUSE <.MEMD.5613_8>
  D.5581_5 = eD.4212_1->typeD.4133;
  if (D.5581_5 == 0)
    goto <bb 4>;
  else
    goto <bb 5>;
  # SUCC: 4 [29.0%]  (true,exec) 5 [71.0%]  (false,exec)

  # BLOCK 4 freq:2639
  # PRED: 3 [29.0%]  (true,exec)
  # .MEMD.5613_10 = VDEF <.MEMD.5613_8>
  mark_edgeD.4204 (eD.4212_1);
  # SUCC: 5 [100.0%]  (fallthru,exec)

  # BLOCK 5 freq:9100
  # PRED: 3 [71.0%]  (false,exec) 4 [100.0%]  (fallthru,exec)
  # .MEMD.5613_7 = PHI <.MEMD.5613_8(3), .MEMD.5613_10(4)>
  # VUSE <.MEMD.5613_7>
  eD.4212_6 = eD.4212_1->nextD.4136;
  # DEBUG eD.4212 => eD.4212_6
  # SUCC: 6 [100.0%]  (fallthru,dfs_back,exec)

  # BLOCK 6 freq:10000
  # PRED: 2 [100.0%]  (fallthru,exec) 5 [100.0%]  (fallthru,dfs_back,exec)
  # eD.4212_1 = PHI <eD.4212_4(2), eD.4212_6(5)>
  # .MEMD.5613_8 = PHI <.MEMD.5613_9(D)(2), .MEMD.5613_7(5)>
  # DEBUG eD.4212 => eD.4212_1
  if (eD.4212_1 != 0B)
    goto <bb 3>;
  else
    goto <bb 7>;
  # SUCC: 3 [91.0%]  (true,exec) 7 [9.0%]  (false,exec)

  # BLOCK 7 freq:900
  # PRED: 6 [9.0%]  (false,exec)
  return;
  # SUCC: EXIT [100.0%] 

}



Pass statistics:
----------------


;; Function calc_max_distance_recursive (calc_max_distance_recursive)


Pass statistics:
----------------

;; 2 loops found
;;
;; Loop 0
;;  header 0, latch 1
;;  depth 0, outer -1
;;  nodes: 0 1 2 3 4 5 6 7 8 9 10
;;
;; Loop 1
;;  header 8, latch 7
;;  depth 1, outer 0
;;  nodes: 8 7 5 6 4
;; 2 succs { 3 10 }
;; 3 succs { 8 }
;; 4 succs { 5 6 }
;; 5 succs { 7 }
;; 6 succs { 7 }
;; 7 succs { 8 }
;; 8 succs { 4 9 }
;; 9 succs { 10 }
;; 10 succs { 1 }
;; 2 loops found
;;
;; Loop 0
;;  header 0, latch 1
;;  depth 0, outer -1
;;  nodes: 0 1 2 3 4 5 6 7 8 9 10
;;
;; Loop 1
;;  header 8, latch 7
;;  depth 1, outer 0
;;  nodes: 8 7 5 6 4
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = ve_3)
(get_scalar_evolution 
  (scalar = ve_3)
  (scalar_evolution = ))
(analyze_initial_condition 
  (loop_phi_node = 
ve_3 = PHI <ve_7(3), ve_13(7)>
)
  (init_cond = ve_7))
(analyze_evolution_in_loop 
  (loop_phi_node = ve_3 = PHI <ve_7(3), ve_13(7)>
)
  (evolution_function = scev_not_known))
(set_scalar_evolution 
  instantiated_below = 3 
  (scalar = ve_3)
  (scalar_evolution = ve_3))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = ve_3)
(get_scalar_evolution 
  (scalar = ve_3)
  (scalar_evolution = ve_3))
(set_scalar_evolution 
  instantiated_below = 3 
  (scalar = ve_3)
  (scalar_evolution = ve_3))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = ve_3)
(get_scalar_evolution 
  (scalar = ve_3)
  (scalar_evolution = ve_3))
(set_scalar_evolution 
  instantiated_below = 3 
  (scalar = ve_3)
  (scalar_evolution = ve_3))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = ve_3)
(get_scalar_evolution 
  (scalar = ve_3)
  (scalar_evolution = ve_3))
(set_scalar_evolution 
  instantiated_below = 3 
  (scalar = ve_3)
  (scalar_evolution = ve_3))
)
Predictions for bb 2
  DS theory heuristics: 61.0%
  first match heuristics (ignored): 61.0%
  combined heuristics: 61.0%
  early return (on trees) heuristics: 61.0%
1 edges in bb 3 predicted to even probabilities
Predictions for bb 4
  DS theory heuristics: 48.8%
  first match heuristics (ignored): 50.0%
  combined heuristics: 48.8%
  opcode values nonequal (on trees) heuristics: 28.0%
  call heuristics: 71.0%
  continue heuristics: 50.0%
1 edges in bb 5 predicted to even probabilities
1 edges in bb 6 predicted to even probabilities
1 edges in bb 7 predicted to even probabilities
Predictions for bb 8
  DS theory heuristics (ignored): 98.3%
  first match heuristics: 91.0%
  combined heuristics: 91.0%
  pointer (on trees) heuristics (ignored): 85.0%
  loop exit heuristics: 91.0%
1 edges in bb 9 predicted to even probabilities
1 edges in bb 10 predicted to even probabilities

;; Function calc_max_distance_recursive

;; 
11 basic blocks, 13 edges, last basic block 11.

Basic block 2 (new, reachable)
Predecessors:  ENTRY [100.0%]  (fallthru,exec)
Successors:  3 [61.0%]  (true,exec) 10 [39.0%]  (false,exec)

Basic block 3 (new, reachable)
Predecessors:  2 [61.0%]  (true,exec)
Successors:  8 [100.0%]  (fallthru,exec)

Basic block 4 (new, reachable)
Predecessors:  8 [91.0%]  (true,exec)
Successors:  5 [48.8%]  (true,exec) 6 [51.2%]  (false,exec)

Basic block 5 (new, reachable)
Predecessors:  4 [48.8%]  (true,exec)
Successors:  7 [100.0%]  (fallthru,exec)

Basic block 6 (new, reachable)
Predecessors:  4 [51.2%]  (false,exec)
Successors:  7 [100.0%]  (fallthru,exec)

Basic block 7 (new, reachable)
Predecessors:  5 [100.0%]  (fallthru,exec) 6 [100.0%]  (fallthru,exec)
Successors:  8 [100.0%]  (fallthru,dfs_back,exec)

Basic block 8 (new, reachable)
Predecessors:  3 [100.0%]  (fallthru,exec) 7 [100.0%]  (fallthru,dfs_back,exec)
Successors:  4 [91.0%]  (true,exec) 9 [9.0%]  (false,exec)

Basic block 9 (new, reachable)
Predecessors:  8 [9.0%]  (false,exec)
Successors:  10 [100.0%]  (fallthru,exec)

Basic block 10 (new, reachable)
Predecessors:  2 [39.0%]  (false,exec) 9 [100.0%]  (fallthru,exec)
Successors:  EXIT [100.0%] 



CFG Statistics for calc_max_distance_recursive

---------------------------------------------------------
                                Number of        Memory
                                instances         used 
---------------------------------------------------------
Basic blocks                             11        704b
Edges                                    12        528b
---------------------------------------------------------
Total memory used by CFG data                     1232b
---------------------------------------------------------

Coalesced label blocks: 0 (Max so far: 0)

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
    goto <bb 10>;
  # SUCC: 3 [61.0%]  (true,exec) 10 [39.0%]  (false,exec)

  # BLOCK 3 freq:900
  # PRED: 2 [61.0%]  (true,exec)
  # VUSE <.MEMD.5614_19(D)>
  veD.4221_7 = bbD.4216_5(D)->predD.4147;
  # DEBUG veD.4221 => veD.4221_7
  goto <bb 8>;
  # SUCC: 8 [100.0%]  (fallthru,exec)

  # BLOCK 4 freq:9100
  # PRED: 8 [91.0%]  (true,exec)
  # VUSE <.MEMD.5614_17>
  eD.4222_8 = veD.4221_3->edgeD.4138;
  # DEBUG eD.4222 => eD.4222_8
  # VUSE <.MEMD.5614_17>
  D.5573_9 = eD.4222_8->typeD.4133;
  if (D.5573_9 == 3)
    goto <bb 5>;
  else
    goto <bb 6>;
  # SUCC: 5 [48.8%]  (true,exec) 6 [51.2%]  (false,exec)

  # BLOCK 5 freq:4438
  # PRED: 4 [48.8%]  (true,exec)
  // predicted unlikely by continue predictor.
  goto <bb 7>;
  # SUCC: 7 [100.0%]  (fallthru,exec)

  # BLOCK 6 freq:4662
  # PRED: 4 [51.2%]  (false,exec)
  # VUSE <.MEMD.5614_17>
  D.5576_10 = eD.4222_8->sourceD.4134;
  # .MEMD.5614_20 = VDEF <.MEMD.5614_17>
  valD.4219_11 = calc_max_distance_recursiveD.4217 (D.5576_10);
  # DEBUG valD.4219 => valD.4219_11
  maxD.4220_12 = MAX_EXPR <valD.4219_11, maxD.4220_2>;
  # DEBUG maxD.4220 => maxD.4220_12
  # SUCC: 7 [100.0%]  (fallthru,exec)

  # BLOCK 7 freq:9100
  # PRED: 5 [100.0%]  (fallthru,exec) 6 [100.0%]  (fallthru,exec)
  # maxD.4220_1 = PHI <maxD.4220_2(5), maxD.4220_12(6)>
  # .MEMD.5614_16 = PHI <.MEMD.5614_17(5), .MEMD.5614_20(6)>
  # DEBUG maxD.4220 => maxD.4220_1
  # VUSE <.MEMD.5614_16>
  veD.4221_13 = veD.4221_3->nextD.4139;
  # DEBUG veD.4221 => veD.4221_13
  # SUCC: 8 [100.0%]  (fallthru,dfs_back,exec)

  # BLOCK 8 freq:10000
  # PRED: 3 [100.0%]  (fallthru,exec) 7 [100.0%]  (fallthru,dfs_back,exec)
  # maxD.4220_2 = PHI <0(3), maxD.4220_1(7)>
  # veD.4221_3 = PHI <veD.4221_7(3), veD.4221_13(7)>
  # .MEMD.5614_17 = PHI <.MEMD.5614_19(D)(3), .MEMD.5614_16(7)>
  # DEBUG veD.4221 => veD.4221_3
  # DEBUG maxD.4220 => maxD.4220_2
  if (veD.4221_3 != 0B)
    goto <bb 4>;
  else
    goto <bb 9>;
  # SUCC: 4 [91.0%]  (true,exec) 9 [9.0%]  (false,exec)

  # BLOCK 9 freq:900
  # PRED: 8 [9.0%]  (false,exec)
  D.5577_14 = maxD.4220_2 + 1;
  # .MEMD.5614_21 = VDEF <.MEMD.5614_17>
  bbD.4216_5(D)->max_distanceD.4146 = D.5577_14;
  # SUCC: 10 [100.0%]  (fallthru,exec)

  # BLOCK 10 freq:1475
  # PRED: 2 [39.0%]  (false,exec) 9 [100.0%]  (fallthru,exec)
  # .MEMD.5614_18 = PHI <.MEMD.5614_19(D)(2), .MEMD.5614_21(9)>
  # VUSE <.MEMD.5614_18>
  D.5578_15 = bbD.4216_5(D)->max_distanceD.4146;
  return D.5578_15;
  # SUCC: EXIT [100.0%] 

}



Pass statistics:
----------------


;; Function calc_max_distance (calc_max_distance)


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
;;  header 8, latch 7
;;  depth 1, outer 0
;;  nodes: 8 7 3 6 5 4
;; 2 succs { 8 }
;; 3 succs { 4 7 }
;; 4 succs { 5 6 }
;; 5 succs { 6 }
;; 6 succs { 7 }
;; 7 succs { 8 }
;; 8 succs { 3 9 }
;; 9 succs { 1 }
;; 2 loops found
;;
;; Loop 0
;;  header 0, latch 1
;;  depth 0, outer -1
;;  nodes: 0 1 2 3 4 5 6 7 8 9
;;
;; Loop 1
;;  header 8, latch 7
;;  depth 1, outer 0
;;  nodes: 8 7 3 6 5 4
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = bb_3)
(get_scalar_evolution 
  (scalar = bb_3)
  (scalar_evolution = ))
(analyze_initial_condition 
  (loop_phi_node = 
bb_3 = PHI <bb_10(2), bb_16(7)>
)
  (init_cond = bb_10))
(analyze_evolution_in_loop 
  (loop_phi_node = bb_3 = PHI <bb_10(2), bb_16(7)>
)
  (evolution_function = scev_not_known))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = bb_3)
  (scalar_evolution = bb_3))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = bb_3)
(get_scalar_evolution 
  (scalar = bb_3)
  (scalar_evolution = bb_3))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = bb_3)
  (scalar_evolution = bb_3))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = bb_3)
(get_scalar_evolution 
  (scalar = bb_3)
  (scalar_evolution = bb_3))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = bb_3)
  (scalar_evolution = bb_3))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = bb_3)
(get_scalar_evolution 
  (scalar = bb_3)
  (scalar_evolution = bb_3))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = bb_3)
  (scalar_evolution = bb_3))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = D.5563_11)
(get_scalar_evolution 
  (scalar = D.5563_11)
  (scalar_evolution = ))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = D.5563_11)
  (scalar_evolution = D.5563_11))
)
(instantiate_scev 
  (instantiate_below = 2)
  (evolution_loop = 1)
  (chrec = D.5563_11)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = D.5563_11)
(get_scalar_evolution 
  (scalar = D.5563_11)
  (scalar_evolution = D.5563_11))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = D.5563_11)
  (scalar_evolution = D.5563_11))
)
  (res = scev_not_known))
1 edges in bb 2 predicted to even probabilities
Predictions for bb 3
  DS theory heuristics: 29.0%
  first match heuristics (ignored): 29.0%
  combined heuristics: 29.0%
  call heuristics: 29.0%
Predictions for bb 4
  no prediction heuristics: 50.0%
  combined heuristics: 50.0%
1 edges in bb 5 predicted to even probabilities
1 edges in bb 6 predicted to even probabilities
1 edges in bb 7 predicted to even probabilities
Predictions for bb 8
  DS theory heuristics (ignored): 98.3%
  first match heuristics: 91.0%
  combined heuristics: 91.0%
  pointer (on trees) heuristics (ignored): 85.0%
  loop exit heuristics: 91.0%
1 edges in bb 9 predicted to even probabilities

;; Function calc_max_distance

;; 
10 basic blocks, 12 edges, last basic block 10.

Basic block 2 (new, reachable)
Predecessors:  ENTRY [100.0%]  (fallthru,exec)
Successors:  8 [100.0%]  (fallthru,exec)

Basic block 3 (new, reachable)
Predecessors:  8 [91.0%]  (true,exec)
Successors:  4 [29.0%]  (true,exec) 7 [71.0%]  (false,exec)

Basic block 4 (new, reachable)
Predecessors:  3 [29.0%]  (true,exec)
Successors:  5 [50.0%]  (true,exec) 6 [50.0%]  (false,exec)

Basic block 5 (new, reachable)
Predecessors:  4 [50.0%]  (true,exec)
Successors:  6 [100.0%]  (fallthru,exec)

Basic block 6 (new, reachable)
Predecessors:  5 [100.0%]  (fallthru,exec) 4 [50.0%]  (false,exec)
Successors:  7 [100.0%]  (fallthru,exec)

Basic block 7 (new, reachable)
Predecessors:  3 [71.0%]  (false,exec) 6 [100.0%]  (fallthru,exec)
Successors:  8 [100.0%]  (fallthru,dfs_back,exec)

Basic block 8 (new, reachable)
Predecessors:  2 [100.0%]  (fallthru,exec) 7 [100.0%]  (fallthru,dfs_back,exec)
Successors:  3 [91.0%]  (true,exec) 9 [9.0%]  (false,exec)

Basic block 9 (new, reachable)
Predecessors:  8 [9.0%]  (false,exec)
Successors:  EXIT [100.0%] 



CFG Statistics for calc_max_distance

---------------------------------------------------------
                                Number of        Memory
                                instances         used 
---------------------------------------------------------
Basic blocks                             10        640b
Edges                                    11        484b
---------------------------------------------------------
Total memory used by CFG data                     1124b
---------------------------------------------------------

Coalesced label blocks: 0 (Max so far: 0)

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
  cfg.4D.5561_9 = cfgD.4174;
  # VUSE <.MEMD.5615_24>
  bbD.4232_10 = cfg.4D.5561_9->bbD.4157;
  # DEBUG bbD.4232 => bbD.4232_10
  goto <bb 8>;
  # SUCC: 8 [100.0%]  (fallthru,exec)

  # BLOCK 3 freq:9100
  # PRED: 8 [91.0%]  (true,exec)
  # VUSE <.MEMD.5615_20>
  D.5563_11 = bbD.4232_3->max_distanceD.4146;
  if (D.5563_11 == 0)
    goto <bb 4>;
  else
    goto <bb 7>;
  # SUCC: 4 [29.0%]  (true,exec) 7 [71.0%]  (false,exec)

  # BLOCK 4 freq:2639
  # PRED: 3 [29.0%]  (true,exec)
  # .MEMD.5615_25 = VDEF <.MEMD.5615_20>
  valD.4230_12 = calc_max_distance_recursiveD.4217 (bbD.4232_3);
  # DEBUG valD.4230 => valD.4230_12
  if (maxD.4231_2 <= valD.4230_12)
    goto <bb 5>;
  else
    goto <bb 6>;
  # SUCC: 5 [50.0%]  (true,exec) 6 [50.0%]  (false,exec)

  # BLOCK 5 freq:1319
  # PRED: 4 [50.0%]  (true,exec)
  maxD.4231_13 = valD.4230_12 + 1;
  # SUCC: 6 [100.0%]  (fallthru,exec)

  # BLOCK 6 freq:2639
  # PRED: 5 [100.0%]  (fallthru,exec) 4 [50.0%]  (false,exec)
  # maxD.4231_4 = PHI <maxD.4231_13(5), maxD.4231_2(4)>
  # DEBUG maxD.4231 => maxD.4231_4
  # SUCC: 7 [100.0%]  (fallthru,exec)

  # BLOCK 7 freq:9100
  # PRED: 3 [71.0%]  (false,exec) 6 [100.0%]  (fallthru,exec)
  # maxD.4231_1 = PHI <maxD.4231_2(3), maxD.4231_4(6)>
  # .MEMD.5615_19 = PHI <.MEMD.5615_20(3), .MEMD.5615_25(6)>
  # DEBUG maxD.4231 => maxD.4231_1
  # VUSE <.MEMD.5615_19>
  bbD.4232_16 = bbD.4232_3->nextD.4151;
  # DEBUG bbD.4232 => bbD.4232_16
  # SUCC: 8 [100.0%]  (fallthru,dfs_back,exec)

  # BLOCK 8 freq:10000
  # PRED: 2 [100.0%]  (fallthru,exec) 7 [100.0%]  (fallthru,dfs_back,exec)
  # maxD.4231_2 = PHI <maxD.4231_8(2), maxD.4231_1(7)>
  # bbD.4232_3 = PHI <bbD.4232_10(2), bbD.4232_16(7)>
  # .MEMD.5615_20 = PHI <.MEMD.5615_24(2), .MEMD.5615_19(7)>
  # DEBUG bbD.4232 => bbD.4232_3
  # DEBUG maxD.4231 => maxD.4231_2
  if (bbD.4232_3 != 0B)
    goto <bb 3>;
  else
    goto <bb 9>;
  # SUCC: 3 [91.0%]  (true,exec) 9 [9.0%]  (false,exec)

  # BLOCK 9 freq:900
  # PRED: 8 [9.0%]  (false,exec)
  # VUSE <.MEMD.5615_20>
  cfg.4D.5561_17 = cfgD.4174;
  # VUSE <.MEMD.5615_20>
  D.5562_18 = cfg.4D.5561_17->exitD.4156;
  # .MEMD.5615_26 = VDEF <.MEMD.5615_20>
  D.5562_18->max_distanceD.4146 = maxD.4231_2;
  return;
  # SUCC: EXIT [100.0%] 

}



Pass statistics:
----------------


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
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = current_function.1_2)
(get_scalar_evolution 
  (scalar = current_function.1_2)
  (scalar_evolution = ))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = current_function.1_2)
  (scalar_evolution = current_function.1_2))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = current_function.1_2)
(get_scalar_evolution 
  (scalar = current_function.1_2)
  (scalar_evolution = current_function.1_2))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = current_function.1_2)
  (scalar_evolution = current_function.1_2))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = current_function.1_2)
(get_scalar_evolution 
  (scalar = current_function.1_2)
  (scalar_evolution = current_function.1_2))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = current_function.1_2)
  (scalar_evolution = current_function.1_2))
)
(analyze_scalar_evolution 
  (loop_nb = 1)
  (scalar = current_function.1_2)
(get_scalar_evolution 
  (scalar = current_function.1_2)
  (scalar_evolution = current_function.1_2))
(set_scalar_evolution 
  instantiated_below = 2 
  (scalar = current_function.1_2)
  (scalar_evolution = current_function.1_2))
)
1 edges in bb 2 predicted to even probabilities
1 edges in bb 3 predicted to even probabilities
Predictions for bb 4
  DS theory heuristics (ignored): 95.9%
  first match heuristics: 91.0%
  combined heuristics: 91.0%
  pointer (on trees) heuristics (ignored): 85.0%
  call heuristics (ignored): 29.0%
  loop exit heuristics: 91.0%
1 edges in bb 5 predicted to even probabilities

;; Function fine_tune_cfg

;; 
6 basic blocks, 6 edges, last basic block 6.

Basic block 2 (new, reachable)
Predecessors:  ENTRY [100.0%]  (fallthru,exec)
Successors:  4 [100.0%]  (fallthru,exec)

Basic block 3 (new, reachable)
Predecessors:  4 [91.0%]  (true,exec)
Successors:  4 [100.0%]  (fallthru,dfs_back,exec)

Basic block 4 (new, reachable)
Predecessors:  2 [100.0%]  (fallthru,exec) 3 [100.0%]  (fallthru,dfs_back,exec)
Successors:  3 [91.0%]  (true,exec) 5 [9.0%]  (false,exec)

Basic block 5 (new, reachable)
Predecessors:  4 [9.0%]  (false,exec)
Successors:  EXIT [100.0%] 



CFG Statistics for fine_tune_cfg

---------------------------------------------------------
                                Number of        Memory
                                instances         used 
---------------------------------------------------------
Basic blocks                              6        384b
Edges                                     5        220b
---------------------------------------------------------
Total memory used by CFG data                      604b
---------------------------------------------------------

Coalesced label blocks: 0 (Max so far: 0)

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
  goto <bb 4>;
  # SUCC: 4 [100.0%]  (fallthru,exec)

  # BLOCK 3 freq:9100
  # PRED: 4 [91.0%]  (true,exec)
  # VUSE <.MEMD.5616_7>
  current_function.1D.5558_3 = current_functionD.4113;
  # VUSE <.MEMD.5616_7>
  cfg.2D.5559_4 = current_function.1D.5558_3->cfgD.4162;
  # .MEMD.5616_10 = VDEF <.MEMD.5616_7>
  cfgD.4174 = cfg.2D.5559_4;
  # .MEMD.5616_11 = VDEF <.MEMD.5616_10>
  calc_max_distanceD.4228 ();
  # VUSE <.MEMD.5616_11>
  current_function.1D.5558_5 = current_functionD.4113;
  # VUSE <.MEMD.5616_11>
  current_function.3D.5560_6 = current_function.1D.5558_5->nextD.4163;
  # .MEMD.5616_12 = VDEF <.MEMD.5616_11>
  current_functionD.4113 = current_function.3D.5560_6;
  # SUCC: 4 [100.0%]  (fallthru,dfs_back,exec)

  # BLOCK 4 freq:10000
  # PRED: 2 [100.0%]  (fallthru,exec) 3 [100.0%]  (fallthru,dfs_back,exec)
  # .MEMD.5616_7 = PHI <.MEMD.5616_9(2), .MEMD.5616_12(3)>
  # VUSE <.MEMD.5616_7>
  current_function.1D.5558_2 = current_functionD.4113;
  if (current_function.1D.5558_2 != 0B)
    goto <bb 3>;
  else
    goto <bb 5>;
  # SUCC: 3 [91.0%]  (true,exec) 5 [9.0%]  (false,exec)

  # BLOCK 5 freq:900
  # PRED: 4 [9.0%]  (false,exec)
  return;
  # SUCC: EXIT [100.0%] 

}



Pass statistics:
----------------

