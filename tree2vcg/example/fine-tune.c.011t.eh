
;; Function fine_tune_cfg (fine_tune_cfg)


Pass statistics:
----------------


Pass statistics:
----------------

fine_tune_cfg ()
{
  struct function * current_function.3D.5560;
  struct control_flow_graph * cfg.2D.5559;
  struct function * current_function.1D.5558;
  struct function * first_function.0D.5557;

  first_function.0D.5557 = first_functionD.4111;
  current_functionD.4113 = first_function.0D.5557;
  goto <D.4240>;
  <D.4239>:
  current_function.1D.5558 = current_functionD.4113;
  cfg.2D.5559 = current_function.1D.5558->cfgD.4162;
  cfgD.4174 = cfg.2D.5559;
  calc_max_distanceD.4228 ();
  current_function.1D.5558 = current_functionD.4113;
  current_function.3D.5560 = current_function.1D.5558->nextD.4163;
  current_functionD.4113 = current_function.3D.5560;
  <D.4240>:
  current_function.1D.5558 = current_functionD.4113;
  if (current_function.1D.5558 != 0B) goto <D.4239>; else goto <D.4241>;
  <D.4241>:
  return;
}



;; Function calc_max_distance (calc_max_distance)


Pass statistics:
----------------


Pass statistics:
----------------

calc_max_distance ()
{
  struct basic_block * bbD.4232;
  intD.0 maxD.4231;
  intD.0 valD.4230;
  intD.0 iftmp.5D.5566;
  intD.0 D.5563;
  struct basic_block * D.5562;
  struct control_flow_graph * cfg.4D.5561;

  maxD.4231 = 0;
  depth_first_searchD.4185 ();
  mark_edgesD.4209 ();
  cfg.4D.5561 = cfgD.4174;
  D.5562 = cfg.4D.5561->exitD.4156;
  maxD.4231 = calc_max_distance_recursiveD.4217 (D.5562);
  cfg.4D.5561 = cfgD.4174;
  bbD.4232 = cfg.4D.5561->bbD.4157;
  goto <D.4234>;
  <D.4233>:
  D.5563 = bbD.4232->max_distanceD.4146;
  if (D.5563 == 0) goto <D.5564>; else goto <D.5565>;
  <D.5564>:
  valD.4230 = calc_max_distance_recursiveD.4217 (bbD.4232);
  if (maxD.4231 <= valD.4230) goto <D.5567>; else goto <D.5568>;
  <D.5567>:
  iftmp.5D.5566 = valD.4230 + 1;
  goto <D.5569>;
  <D.5568>:
  iftmp.5D.5566 = maxD.4231;
  <D.5569>:
  maxD.4231 = iftmp.5D.5566;
  <D.5565>:
  bbD.4232 = bbD.4232->nextD.4151;
  <D.4234>:
  if (bbD.4232 != 0B) goto <D.4233>; else goto <D.4235>;
  <D.4235>:
  cfg.4D.5561 = cfgD.4174;
  D.5562 = cfg.4D.5561->exitD.4156;
  D.5562->max_distanceD.4146 = maxD.4231;
  return;
}



;; Function calc_max_distance_recursive (calc_max_distance_recursive)


Pass statistics:
----------------


Pass statistics:
----------------

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

  maxD.4220 = 0;
  D.5570 = bbD.4216->max_distanceD.4146;
  if (D.5570 == 0) goto <D.5571>; else goto <D.5572>;
  <D.5571>:
  veD.4221 = bbD.4216->predD.4147;
  goto <D.4225>;
  <D.4224>:
  eD.4222 = veD.4221->edgeD.4138;
  D.5573 = eD.4222->typeD.4133;
  if (D.5573 == 3) goto <D.5574>; else goto <D.5575>;
  <D.5574>:
  // predicted unlikely by continue predictor.
  goto <D.4223>;
  <D.5575>:
  D.5576 = eD.4222->sourceD.4134;
  valD.4219 = calc_max_distance_recursiveD.4217 (D.5576);
  maxD.4220 = MAX_EXPR <valD.4219, maxD.4220>;
  <D.4223>:
  veD.4221 = veD.4221->nextD.4139;
  <D.4225>:
  if (veD.4221 != 0B) goto <D.4224>; else goto <D.4226>;
  <D.4226>:
  D.5577 = maxD.4220 + 1;
  bbD.4216->max_distanceD.4146 = D.5577;
  <D.5572>:
  D.5578 = bbD.4216->max_distanceD.4146;
  goto <D.5579>;
  <D.5579>:
  return D.5578;
}



;; Function mark_edges (mark_edges)


Pass statistics:
----------------


Pass statistics:
----------------

mark_edges ()
{
  struct edge * eD.4212;
  struct control_flow_graph * cfgD.4211;
  edge_type D.5581;
  struct function * current_function.6D.5580;

  current_function.6D.5580 = current_functionD.4113;
  cfgD.4211 = current_function.6D.5580->cfgD.4162;
  eD.4212 = cfgD.4211->edgeD.4159;
  goto <D.4214>;
  <D.4213>:
  D.5581 = eD.4212->typeD.4133;
  if (D.5581 == 0) goto <D.5582>; else goto <D.5583>;
  <D.5582>:
  mark_edgeD.4204 (eD.4212);
  <D.5583>:
  eD.4212 = eD.4212->nextD.4136;
  <D.4214>:
  if (eD.4212 != 0B) goto <D.4213>; else goto <D.4215>;
  <D.4215>:
  return;
}



;; Function mark_edge (mark_edge)


Pass statistics:
----------------


Pass statistics:
----------------

mark_edge (struct edge * eD.4203)
{
  struct basic_block * targetD.4207;
  struct basic_block * sourceD.4206;
  intD.0 D.5588;
  intD.0 D.5584;

  sourceD.4206 = eD.4203->sourceD.4134;
  targetD.4207 = eD.4203->targetD.4135;
  D.5584 = is_ancestorD.4193 (targetD.4207, sourceD.4206);
  if (D.5584 != 0) goto <D.5585>; else goto <D.5586>;
  <D.5585>:
  eD.4203->typeD.4133 = 3;
  goto <D.5587>;
  <D.5586>:
  D.5588 = is_ancestorD.4193 (sourceD.4206, targetD.4207);
  if (D.5588 != 0) goto <D.5589>; else goto <D.5590>;
  <D.5589>:
  eD.4203->typeD.4133 = 2;
  goto <D.5591>;
  <D.5590>:
  eD.4203->typeD.4133 = 4;
  <D.5591>:
  <D.5587>:
  return;
}



;; Function is_ancestor (is_ancestor)


Pass statistics:
----------------


Pass statistics:
----------------

is_ancestor (struct basic_block * sourceD.4191, struct basic_block * targetD.4192)
{
  struct edge * eD.4197;
  struct vec_edge * veD.4196;
  struct basic_block * bbD.4195;
  struct basic_block * D.5599;
  struct control_flow_graph * cfg.7D.5598;
  edge_type D.5595;
  intD.0 D.5594;

  bbD.4195 = targetD.4192;
  <D.4201>:
  if (bbD.4195 == sourceD.4191) goto <D.5592>; else goto <D.5593>;
  <D.5592>:
  D.5594 = 1;
  goto <D.5600>;
  <D.5593>:
  veD.4196 = bbD.4195->predD.4147;
  goto <D.4200>;
  <D.4199>:
  eD.4197 = veD.4196->edgeD.4138;
  D.5595 = eD.4197->typeD.4133;
  if (D.5595 == 1) goto <D.5596>; else goto <D.5597>;
  <D.5596>:
  bbD.4195 = eD.4197->sourceD.4134;
  goto <D.4198>;
  <D.5597>:
  veD.4196 = veD.4196->nextD.4139;
  <D.4200>:
  if (veD.4196 != 0B) goto <D.4199>; else goto <D.4198>;
  <D.4198>:
  cfg.7D.5598 = cfgD.4174;
  D.5599 = cfg.7D.5598->entryD.4155;
  if (D.5599 != bbD.4195) goto <D.4201>; else goto <D.4202>;
  <D.4202>:
  D.5594 = 0;
  goto <D.5600>;
  <D.5600>:
  return D.5594;
}



;; Function depth_first_search (depth_first_search)


Pass statistics:
----------------


Pass statistics:
----------------

depth_first_search ()
{
  struct basic_block * bbD.4187;
  struct basic_block * D.5603;
  intD.0 count.9D.5602;
  struct control_flow_graph * cfg.8D.5601;

  cfg.8D.5601 = cfgD.4174;
  bbD.4187 = cfg.8D.5601->bbD.4157;
  goto <D.4189>;
  <D.4188>:
  bbD.4187->visitedD.4144 = 0;
  bbD.4187 = bbD.4187->nextD.4151;
  <D.4189>:
  if (bbD.4187 != 0B) goto <D.4188>; else goto <D.4190>;
  <D.4190>:
  cfg.8D.5601 = cfgD.4174;
  count.9D.5602 = cfg.8D.5601->bb_numD.4153;
  countD.4173 = count.9D.5602;
  cfg.8D.5601 = cfgD.4174;
  D.5603 = cfg.8D.5601->entryD.4155;
  searchD.4176 (D.5603);
  return;
}



;; Function search (search)


Pass statistics:
----------------


Pass statistics:
----------------

search (struct basic_block * bbD.4175)
{
  struct edge * eD.4180;
  struct vec_edge * veD.4179;
  struct basic_block * succ_bbD.4178;
  intD.0 count.11D.5608;
  intD.0 count.10D.5607;
  intD.0 D.5604;

  bbD.4175->visitedD.4144 = 1;
  veD.4179 = bbD.4175->succD.4149;
  goto <D.4182>;
  <D.4181>:
  eD.4180 = veD.4179->edgeD.4138;
  succ_bbD.4178 = eD.4180->targetD.4135;
  D.5604 = succ_bbD.4178->visitedD.4144;
  if (D.5604 == 0) goto <D.5605>; else goto <D.5606>;
  <D.5605>:
  eD.4180->typeD.4133 = 1;
  searchD.4176 (succ_bbD.4178);
  <D.5606>:
  veD.4179 = veD.4179->nextD.4139;
  <D.4182>:
  if (veD.4179 != 0B) goto <D.4181>; else goto <D.4183>;
  <D.4183>:
  count.10D.5607 = countD.4173;
  bbD.4175->dfs_orderD.4145 = count.10D.5607;
  count.10D.5607 = countD.4173;
  count.11D.5608 = count.10D.5607 - 1;
  countD.4173 = count.11D.5608;
  return;
}


