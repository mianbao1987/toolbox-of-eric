  /* amax: Int, default: calculated automatically
     Attribute of top-level graph
     Specifies the number of iterations that are animated after relayout.
     Specifying 0 means animation is turned off. This value can be changed
     interactively in the View dialog box (see general view parameters). */
     
     
  /* Arrow Modes and Port Sharingarrow_mode: free or fixed, default is free as
     of aiSee 2.1.89
     Attribute of top-level graph, subgraphs
     Specifies the mode for drawing edge arrow heads. fixed is useful if
     port_sharing is used because then only a fixed set of rotations for the
     arrow heads is used, the arrow head being rotated only in increments of 45
     degrees. In the free mode, each arrow head is rotated individually for
     each edge. If a node has many incoming edges and port_sharing is used, the
     free mode can lead to a somewhat confusing image. See example. */
     
     
  /* attraction: Int, default is 60
     Attribute of top-level graph
     Applies only to the forcedir layout algorithm, where it is part of the
     force-directed spring embedder during attractive impulse calculation. It
     specifies the constant proportional to the attractive forces acting on a
     node. This constant and its repulsive counterpart repulsion enable the
     length of edges to be controlled. For example, if only attractive and
     repulsive forces are working on a node, an edge length of n pixels is
     achieved for edges with priority of 1 by specifying n2 for the attributes
     attraction and repulsion. Usually the values for these two attributes are
     of the same order of magnitude. For details, see force-directed layout. */
     
  /* bmax: Int, default is 100
     Attribute of top-level graph, subgraphs
     Sets the maximum number of iterations of the phase reducing edge bends.
     Edge bends are used to prevent edges from being drawn across nodes.
     Reducing the number of iterations reduces layout calculation time, however
     the layout quality may suffer. */
     
     
  /* border x: Int, default is 600 (pixels)
     border y: Int, default is 600 (pixels)
     Attributes of top-level graph
     Apply only to the forcedir layout algorithm. Depending on the
     specification of the layout parameters for the forcedir layout algorithm
     it is possible for nodes to move far away from one another (especially
     single nodes or unconnected components). These two attributes enable a
     rectangle to be specified within which the graph is drawn, preventing
     nodes from being placed "infinitely" far from one another. For details,
     see force-directed layout. */
     
     
  /* bordercolor: Color Entry, default: the value of textcolor
     Attribute of subgraphs
     Specifies the color for borders of summary nodes, boxes and frames of
     clusters. For available Color Entries, see section Colors. */
     
     
  /* borderstyle: Style, default is solid
     Attribute of subgraphs
     Specifies the line style used for drawing the borders of a summary node.
     The following Styles are available:
     
         * solid
         * continuous
         * dashed
         * dotted
         * double
         * triple */
     
     
  /* borderwidth: Int, default is 2
     Attribute of subgraphs
     Specifies the thickness of the border of a summary node in pixels. */
     
     
  /* classname Int:"String", default is 1:"1", 2:"2", 3:"3", etc.
     Attributes of top-level graph
     Enable the names of edges classes to be introduced. These names appear in
     the Select Edge Classes dialog box. */
     
  /* cmax: Int, default is infinite
     cmin: Int, default is 0
     Attributes of top-level graph, subgraphs
     cmin sets the minimum number of iterations that are performed for reducing
     crossings using crossing weights. The normal method stops when two
     consecutive checks no longer cause the number of crossings to be reduced.
     However, this number of crossings might be a local minimum, meaning the
     number of crossing might decrease even more after some more iterations.
     cmax sets the maximum number of iterations of the crossing reduction
     phase. A reduction of this value causes the layout process to be speeded
     up. The default value is infinite meaning that the method is iterated as
     long as any improvement is possible. */
     
     
  /* color: Color Entry,
     default for top-level graph is white,
     default for subgraphs is the default value of node.color
     Attribute of top-level graph, subgraphs
     Specifies the background color of the graph window or the background color
     of subgraphs respectively. This color is valid as the background color in
     summary nodes, boxes, clusters and as a wrapping color. For available
     Color Entries, see section Colors. See also textcolor and bordercolor. */
  DEF_ATTR (graph, color, enum gdl_color)
  DEF_ATTR (graph, node_color, enum gdl_color)
     
  /* colorentry Int: Int Int Int, no default value defined
     Attribute of top-level graph, subgraphs
     Enables the default color map to be filled and changed. A color is a
     triple of integer values for the red, green and blue part (RGB). Each
     integer ranges from 0 (color part turned off) to 255 (color part turned
     on), e.g. 0 0 0 specifies the color black and 255 255 255 specifies the
     color white. For instance, colorentry 75: 70 130 180 sets map entry 75 to
     steel blue. This color can then be used by merely specifying 75 wherever a
     Color Entry is expected. More details can be found in the section Colors.
     
     Top
     
     crossing_optimization: yes or no, default is yes
     Attribute of top-level graph, subgraphs
     yes activates the crossing optimization phase, which works locally. It is
     a postprocessing phase after normal crossing reduction. It tries to
     optimize locally by exchanging pairs of nodes to reduce the number of
     crossings.
     
     Top
     
     crossing_phase2: yes or no, default is yes
     Attribute of top-level graph, subgraphs
     yes activates crossing reduction phase two. In this phase, nodes having
     equal crossing weights are permuted. Note that this is the most
     time-consuming phase of crossing reduction.
     
     Top
     
     crossing_weight: Weight, default is bary
     Attribute of top-level graph, subgraphs
     Specifies the weight to be used for crossing reduction. The following
     Weights are available:
     
         * bary
           The barycenter is used for calculating the weights during crossing
     reduction. This is the fastest method for graphs with nodes whose average
     degree is very large.
         * median
           The median center is used for calculating the weights during
     crossing reduction.
         * barymedian
           These weights are the combination of barycenter and mediancenter
     weights, with barycenter having priority and mediancenter only being used
     for nodes whose barycenter weights are equal.
         * medianbary
           These weights are the combination of barycenter and mediancenter
     weights, with the mediancenter having priority.
     
     There is no general recommendation as to which is the best method. A
     guideline might be to use bary if the degree of the nodes is large and
     median or one of the hybrid methods barymedian or medianbary if the degree
     is small, the degree of a node being the total of incoming and outgoing
     edges at a node. See crossing reduction for details.
     
     Top
     
     dirty_edge_labels: yes or no, default is no
     Attribute of top-level graph, subgraphs
     yes forces a fast layout of edge labels, which may result in overlapping
     of labels. Dirty edge labels cannot be used if splines are used for edge
     drawing.
     
     Top
     
     display_edge_labels: yes or no, default is no
     Attribute of top-level graph, subgraphs
     Enables/disables displaying edge labels.
     
     Top
     
     edges: yes or no, default is yes
     Attribute of top-level graph
     no suppresses the drawing of edges in the top-level graph and in all
     nested subgraphs.
     
     Top
     
     energetic: yes or no, default is no
     Attribute of top-level graph
     Applies only to the forcedir layout algorithm. Apart from the forces of
     the spring embedder and the magnetic fields, the local energy level of a
     node can be taken into account in deciding whether the node should move or
     not. Setting this attribute to yes causes the local energy present at a
     node to be considered during layout. For details, see force-directed
     layout.
     
     Top
     
     energetic attraction: Float, default is 70.0
     energetic repulsion: Float, default is 70.0
     energetic gravity: Float, default is 0.3
     energetic crossing: Float, default is 80.0
     energetic overlapping: Float, default is 80.0
     energetic border: Float, default is 70.0
     Attributes of top-level graph
     Apply only to the forcedir layout algorithm. Apart from the forces of the
     spring embedder and the magnetic fields, the local energy level of a node
     can be taken into account in deciding whether the node should move or not.
     The behavior of the local energy present at a node can be influenced via
     these attributes as follows:
     
         * energetic attraction is the weight of the attractive energy of edges
         * energetic repulsion is the weight of the repulsive energy between
         * nodes
         * energetic gravity is the weight of the gravitational energy of a
         * node
         * energetic crossing is the weight of the global energy of an edge
         * crossing
         * energetic overlapping is the weight of the global energy of a node
         * overlapping
         * energetic border is the weight of the border energy of a node
     
     Gauging layout quality can be done as follows: The better the layout, the
     lower the total of all the energy values mentioned above. For details, see
     force-directed layout.
     
     Top
     
     equal_y_dist: yes or no, default is no
     Attribute of top-level graph, subgraphs
     If this attribute is enabled (yes), then the vertical distance in a
     hierarchical layout is equal among all levels.
     
     Top
     
     fast_icons: yes or no, default is no
     Attribute of top-level graph
     yes causes icon file loading to be faster, which may negatively impact the
     quality of the drawing if not all the icon colors are present. For details
     on pictures in nodes, see icons.
     
     Top
     
     fdmax: Int, default is 300
     Attribute of top-level graph
     Applies only to the forcedir layout algorithm, where it is used in the
     simulated annealing part of the algorithm for specifying the upper hard
     limit for the number of iterations performed. The algorithm stops when the
     global temperature drops below a threshold value or when the limit
     specified here is reached. For details, see force-directed layout.
     
     Top
     
     finetuning: yes or no, default is yes
     Attribute of top-level graph, subgraphs
     no switches off the fine-tuning phase of the graph layout algorithm. The
     fine-tuning phase tries to give all edges the same length. It tries to
     improve the ranks of nodes in order to avoid very long edges (see
     assignment of ranks).
     
     Top
     
     focus, no value, no default value
     Attribute of subgraphs
     Sets the focus for the summary node of a subgraph, i.e. if the status of
     the subgraph is folded at startup, then the summary node of the subgraph
     for which focus was specified is centered in the graph window. The focus
     can also be specified for nodes. It goes without saying that the focus
     attribute should appear only once in a graph specification.
     
     Top
     
     fontname: "Font File",
     default is the default vector font drawn by turtle graphics routines
     Attribute of summary nodes,
     Attribute of subgraphs as of aiSee 2.1.96
     Specifies a pixel font different from the default vector font and used for
     drawing the text labels of summary nodes. This font is given by the name
     of the aiSee Font File containing the font description, e.g. a 12-point
     Helvetica Bold font can be specified via fontname: "helvB12". Note: If the
     font file is not in the current directory the environment variable
     AISEEFONTS has to be set to the directory containing the font description
     files. For the available Font Files, see additional fonts.
     
     Top
     
     fstraight_phase: yes or no, default is no
     Attribute of top-level graph
     yes forces straight edges that are not anchored at the same position on
     the border of the nodes. This is useful only if no port sharing is
     selected, because bends are avoided by correcting the port position.
     
     Top
     
     gravity: Float, default is 0.0625
     Attribute of top-level graph
     Applies only to the forcedir layout algorithm, where it is used for
     impulse calculation. Only using a simulation of a spring embedder would
     force unconnected components of a graph to move further and further apart
     from one another, as there would be no attractive forces acting between
     them. That is why gravity is introduced as a counterforce. gravity: Float
     specifies the constant which is proportional to the gravitational force
     acting on a node. This constant controls the strength of the gravitational
     force, e.g. a value of zero cancels out the influence of any gravitational
     force. For details, see force-directed layout.
     
     Top
     
     height: Int
     default for top-level graph is (height of root screen — 100) pixels,
     default for subgraphs is (height of the label for summary nodes) pixels
     Attribute of top-level graph, subgraphs
     In the top-level graph, this attribute specifies the height of the display
     window in pixels. For a subgraph, it specifies the height of the summary
     node. See also width.
     
     Top
     
     hidden: Int, no default value
     Attribute of top-level graph
     Specifies the edge class to be hidden. To hide more than one edge class,
     repeat this attribute for each additional edge class. Edges in such a
     class are ignored during layout calculation and are not drawn. Nodes that
     are only accessible (forward or backward) via edges of a hidden class are
     not drawn, either. However, nodes that are not accessible at all may be
     drawn (see ignore_singles).
     
     Note the difference between hiding edge classes and the edge line style
     invisible. Hidden edges do not exist in the layout. Edges with the
     invisible line style do exist, i.e. they influence the layout, meaning
     they need space and may produce crossings, for example.
     
     Top
     
     horizontal_order: Int, default is -1 (i.e. no default)
     Attribute of subgraphs
     In a hierarchical layout, this attribute specifies the horizontal position
     of the summary node within a level (see vertical_order). Nodes specified
     by horizontal positions are ordered according to these positions within
     levels. Nodes without this attribute are inserted into this ordering by
     the crossing reduction mechanism (see crossing reduction).
     
     Note: Connected components are handled separately during crossing
     reduction, thus it is not possible to intermix nodes of different
     connected components in one ordering sequence. For example, one connected
     component consists of nodes A, B, C and another of nodes D, E, all nodes
     being positioned at the same level. Then, for instance, it is not possible
     to specify the following horizontal order at level 0: A, D, C, E.
     Note further: If the algorithm for downward laid-out trees is used the
     specified horizontal order is retained only within nodes that are children
     of the same node, i.e. in case of downward laid-out trees it is not
     possible to specify a horizontal order for the entire level.
     
     Top
     
     iconcolors: Int, default is 32
     Attribute of top-level graph
     Specifies the size of the color map used for colors in bitmap files. For
     details on pictures in nodes, see icons.
     
     Top
     
     iconfile: "File",
     no default value
     Attribute of subgraphs
     Specifies the bitmap file (in PNG, PBM, PPM, or raw PPM format) to be
     displayed in the summary node of the folded subgraph. If the bitmap file
     to be displayed is not in the current directory the environment variable
     AISEEICONS can be set to the directory containing the bitmap file. For
     details, see icons.
     
     Top
     
     icons: yes or no, default is yes
     Attribute of top-level graph
     no disables displaying of icons in nodes. Displaying of icons can be
     enabled again interactively from the View dialog box.
     
     Top
     
     ignore_singles: yes or no, default is no
     Attribute of top-level graph, subgraphs
     yes hides all nodes of the graph which would appear singly and
     unconnected. These nodes have no edges at all and drawing them sometimes
     results in an ugly layout of the remaining graph. The default setting is
     to show all nodes.
     
     Top
     
     importance: Int, default is 0 (which actually means infinity)
     Attribute of subgraphs
     This is the central attribute when it comes to filtering in fish-eye views
     as it enables the importance of a summary node of a folded subgraph to be
     specified via an integer. Low integers signify less important nodes which
     are filtered out first by a filtering fish-eye view. High integer numbers
     signify nodes that are important, their being rarely filtered out. A value
     of 0 represents an infinite importance, the result being that these nodes
     are never filtered out. This attribute exists for nodes too, see
     importance. See also view.
     
     Top
     
     info1: "String", default is "" (empty string)
     info2: "String", default is "" (empty string)
     info3: "String", default is "" (empty string)
     Attributes of subgraphs
     Enable three additional text fields to be specified for a subgraph (and
     its summary node). The same set of attributes exists for nodes (see node
     attribute info1). These additional information fields can be selected
     interactively from the Information submenu.
     
     Top
     
     infoname1: "String", default is "0"
     infoname2: "String", default is "1"
     infoname3: "String", default is "2"
     Attributes of top-level graph
     Enable names for the additional information fields available for each node
     to be introduced. These names appear in the submenu of the menu item
     Information in the main menu. See also info1, info2, info3.
     
     Top
     
     inport_sharing: yes or no, default is no
     Attribute of top-level graph, subgraphs as of aiSee 2.1.89
     See port_sharing.
     
     Top
     
     invisible: Int, no default value
     Attribute of top-level graph
     This is a synonym for hidden.
     
     Top
     
     label: "String", default is "" (empty string)
     Attribute of subgraphs
     Specifies the text to be displayed inside the summary node of a folded
     subgraph. This text may contain control characters, e.g. \n (newline
     character), that influence the size of the node. See character set for
     more details. If no label is specified for a subgraph, the value of the
     title of the subgraph is used. */
  DEF_ATTR (graph, label, char *)
     
  /*   late_edge_labels: yes or no, default is no
     Attribute of top-level graph, subgraphs
     Controls the moment when edge labels are drawn. yes: The graph is first
     partitioned and then edge labels are introduced. no: The algorithm first
     creates labels and then partitions the graph. The latter option yields a
     more compact layout, but may result in more crossings.
     
     Top
     
     layout_algorithm: Algorithm, default is normal
     Attribute of top-level graph, subgraphs
     Specifies the basic layout Algorithm, there being two main categories. The
     first fourteen algorithms describe variations of a hierarchical layout,
     whereas the last algorithm implements a force-directed layout. The
     variations differ in the way nodes are selected for the various levels in
     the hierarchical layout.
     
         * normal
           Tries to give all edges the same orientation and is based on the
     calculation of strongly connected components. The algorithms based on
     depth first search are faster.
         * dfs
           Uses a depth first search for layout calculation, but does not
     enforce additional constraints pertaining to the degree of nodes. It is
     faster than the normal layout algorithm. The resulting layout is heavily
     dependent on the initial order of the nodes in the graph specification.
         * maxdepth / mindepth
           These two algorithms are based on depth first search and are both
     fast heuristics. maxdepth tries to increase the depth of the layout,
     mindepth tries to increase the width of the layout.
         * maxdepthslow / mindepthslow
           These slower algorithms might be better if the fast heuristics
     offered by the algorithms maxdepth and maxdepth do not provide satisfying
     results. maxdepthslow tries to increase the depth of the layout and
     mindepthslow the width of the layout.
         * maxindegree / minindegree
           Schedule nodes with a maximum/minimum of incoming edges first, i.e.
     these nodes are positioned early.
         * maxoutdegree / minoutdegree
           Schedule nodes with a maximum/minimum of outgoing edges first, i.e.
     these nodes are positioned early.
         * maxdegree / mindegree
           Schedule nodes with a maximum/minimum of the sum of incoming and
     outgoing edges first, i.e. these nodes are positioned early.
         * minbackward
           Instead of calculating strongly connected components, this algorithm
     performs a topological sorting to assign ranks to the nodes. It is fast if
     the graph is acyclic.
         * tree
           A specialized method for downward laid out trees, see rank
     assignment. It is very fast for trees and tree-like graphs and results in
     a balanced layout.
         * forcedir
           Computes a force-directed placement. It is a nonhierarchical layout
     method that works well for undirected graphs. Some features of
     hierarchical layout like near edges are disabled for this layout
     algorithm. The layout calculation for this algorithm can be controlled via
     the following graph attributes:
               o Spring embedder forces attraction, repulsion
               o Gravitational force gravity
               o Simulated annealing: fdmax, tempmin / tempmax, temptreshold,
     tempscheme, tempfactor
               o Random influence: randomfactor, randomrounds, randomimpulse
               o Magnetic forces: magnetic_field1 / 2, magnetic_force1 / 2
               o Energy level: energetic, energetic attraction / repulsion /
     gravity / crossing / overlapping / border
               o Boundary rectangle border x / y
     
     Top
     
     layout_downfactor: Int, default is 1
     layout_nearfactor: Int, default is 1
     layout_upfactor: Int, default is 1
     Attributes of top-level graph, subgraphs
     Have no effect if the layout_algorithm tree or forcedir is used.
     
     A layout algorithm partitions the set of edges into edges pointing upward,
     edges pointing downward, and edges pointing sidewards. The last type of
     edges is also called near edges. If the layout_downfactor is large as
     compared to the layout_upfactor and layout_nearfactor, then the positions
     of the nodes are mainly determined by the edges pointing downwards.
     
     If the layout_upfactor is large as compared to the layout_downfactor and
     layout_nearfactor, then the positions of the nodes are mainly determined
     by the edges pointing upwards.
     
     If the layout_nearfactor is large, then the positions of the nodes are
     mainly determined by the edges pointing sidewards.
     
     Top
     
     level: maxlevel or Int, default is -1 (i.e. no default)
     Attribute of subgraphs
     This is a synonym for vertical_order.
     
     Top
     
     linear_segments: yes or no, default is no
     Attribute of top-level graph, subgraphs
     yes switches linear segment layout on. This layout favors straight long
     vertical edges. See also the command line options -linseg and -linsegmax.
     
     Top
     
     loc: { x: Int y: Int },
     default is {x:0 y:0} for top-level graph, unspecified for subgraphs
     Attribute of top-level graph, subgraphs
     See x / y.
     
     Top
     
     magnetic_field1: Orientation, default is no
     magnetic_field2: Orientation, default is no
     Attributes of top-level graph
     Apply only to the forcedir layout algorithm, where magnetic fields are
     part of impulse calculation. Forces that originate from a simulation of a
     spring embedder neglect the directions of edges. In directed graphs edges
     should point in a uniform direction, consequently magnetic forces are
     introduced, with edges being interpreted as magnetic needles that align
     according to the Orientation of a magnetic field. The following
     Orientations are available:
     
         * top_to_bottom
         * bottom_to_top
         * left_to_right
         * right_to_left
         * polar
         * circular
         * polcircular
         * orthogonal
         * no
     
     Two independent magnetic fields are possible. If two fields are specified,
     the edges are influenced by both. The attributes magnetic_force1 /
     magnetic_force2 influence the strength of each field. For details, see
     force-directed layout.
     
     Top
     
     magnetic_force1: Int, default is 1
     magnetic_force2: Int, default is 1
     Attributes of top-level graph
     Apply only to the forcedir layout algorithm, where these attributes
     specify the constant factors that are multiplied by the corresponding
     magnetic forces of the two magnetic fields magnetic_field1 /
     magnetic_field2. For details, see force-directed layout.
     
     Top
     
     manhattan_edges: yes or no, default is no
     Attribute of top-level graph, subgraphs
     yes switches Manhattan Layout on, meaning that all edges consist of
     horizontal or vertical line segments. Vertical edge segments might be
     shared by several edges, while horizontal edge segments are never shared.
     This results in aesthetic layouts for flowcharts. If orthogonal layout is
     used, the priority_phase and straight_phase are also used by default.
     
     Top
     
     margin: Int, as of aiSee 2.1.89,
     default is 3 if the value of borderwidth is > 0,
     0 if the value of borderwidth is 0
     Attribute of subgraphs
     Specifies the horizontal and vertical offset between the border of a
     summary node and its label in pixels. Useful for rectangular nodes only.
     
     Top
     
     near_edges: yes or no, default is yes
     Attribute of top-level graph, subgraphs
     no: All near edges are treated as normal edges in the graph layout. */
  DEF_ATTR (graph, near_edges, int)
     
  /* nodes: yes or no, default is yes
     Attribute of top-level graph
     no suppresses the drawing of nodes in the top-level graph and all nested
     subgraphs.
     
     Top
     
     node_alignment: top, or center, or bottom, default is center
     Attribute of top-level graph, subgraphs
     For hierarchical layout, this attribute specifies the vertical alignment
     of nodes at the horizontal reference line of levels. top means the tops of
     all nodes of a level have the same y coordinate. center means all nodes of
     a level are centered. bottom means the bottoms of all nodes of a level
     have the same y coordinate.
     
     Top
     
     orientation: Orientation, default is top_to_bottom
     Attribute of top-level graph, subgraphs
     Specifies the Orientation of the graph, the available Orientations being
     top_to_bottom, bottom_to_top, left_to_right, and right_to_left. All
     explanations in this section are given in relation to the default
     orientation.
     
     Top
     
     outport_sharing: yes or no, default is no
     Attribute of top-level graph, subgraphs as of aiSee 2.1.89
     See port_sharing.
     
     Top
     
     pmax: Int, default is 100
     pmin: Int, default is 0
     Attributes of top-level graph, subgraphs
     Set the maximum/minimum number of iterations of the pendulum method. Like
     crossing reduction, this method stops when the "imbalance weight" stops
     decreasing. However, an increase in imbalance weight might be a local
     phenomenon, meaning that the imbalance might decrease much more after a
     few more iterations. Reducing the number of iterations increases layout
     calculation speed.
     
     Top
     
     port_sharing: yes or no, default is no as of aiSee 2.1.89
     inport_sharing: yes or no, default is no
     outport_sharing: yes or no, default is no
     Attributes of top-level graph, subgraphs as of aiSee 2.1.89
     no suppresses the sharing of ports by edges at nodes. inport_sharing
     enables the port sharing of incoming edges only, with outport_sharing
     enabling the port sharing of outgoing edges only.
     
     Arrow Modes and Port SharingGenerally speaking, if multiple edges are
     adjacent to the same node, and the arrow heads of all these edges have the
     same appearance (color, size, etc.), these edges may share a port at a
     node. This means that only one arrow head is drawn, and all edges meet at
     this arrow head. This enables many edges to be located adjacent to one
     node without getting confused by too many arrow heads. If no port sharing
     is used, each edge gets its own port. See example. */
  DEF_ATTR (graph, port_sharing, int)
     
  /* priority_phase: yes or no, default is no
     Attribute of top-level graph, subgraphs
     yes switches on the priority phase. This phase replaces the normal
     pendulum method with a specialized method: It forces long vertical edges
     to be straight, just like the straight_phase. In fact, the straight phase
     is a fine-tuning of the priority phase, the priority phase being
     recommended for an orthogonal layout (see manhattan_edges).
     
     Top
     
     randomfactor: Int, default is 70
     Attribute of top-level graph
     Applies only to the forcedir layout algorithm. If the number of
     randomrounds has been specified, then a node is placed with a probability
     of randomfactor percent during a round. This factor should be close to 100
     in order to prevent the process from stopping too early. For details, see
     force-directed layout.
     
     Top
     
     randomimpulse: Int, default is 32
     Attribute of top-level graph
     Applies only to the forcedir layout algorithm, where it specifies the
     strength of the random impulse vector. If the forcedir algorithm should
     behave like a simulated annealing algorithm, this constant should be large
     and a slow tempscheme should be chosen. Otherwise a small value is
     preferable for the randomimpulse attribute. For details, see
     force-directed layout.
     
     Top
     
     randomrounds: Int, default is -1
     Attribute of top-level graph
     Applies only to the forcedir layout algorithm, where it specifies the
     number of randomized rounds during impulse calculation. It should only be
     used for the first few rounds so as to add a randomimpulse. Afterwards,
     the random impulse would delay completion of calculation. For details, see
     force-directed layout.
     
     Top
     
     repulsion: Int, default is 60
     Attribute of top-level graph
     Applies only to the forcedir layout algorithm, where it is part of the
     force-directed spring embedder during repulsive impulse calculation. It
     specifies the constant that is inversely proportional to the attractive
     forces acting on a node. This constant and its attractive counterpart
     attraction enable the length of edges to be controlled. Usually the values
     for these two attributes are of the same order of magnitude. For details,
     see force-directed layout.
     
     Top
     
     rmax: Int, default is 100
     rmin: Int, default is 0
     Attributes of top-level graph, subgraphs
     Set the maximum/minimum number of iterations for rubberbanding. This works
     in a manner similar to the pendulum method. Reducing the number of
     iterations increases layout calculation speed.
     
     Top
     
     scaling: maxspect or Float, default is 1.0
     Attribute of top-level graph, subgraphs
     Specifies the scaling factor for graph representation. A scaling factor of
     1.0 means normal size. maxspect scales a graph so that the entire graph
     fits into the graph window.
     
     When specified for the top-level graph, this attribute determines the size
     of the entire graph including all the subgraphs. When specified for a
     subgraph it determines the scaling factor of the summary node of the
     folded subgraph. The size of a boxed subgraph is not affected, however the
     size of the subgraph nodes may still be affected (see node attribute
     shrink).
     
     See also graph attributes shrink / stretch.
     
     Top
     
     shape: Shape, default is box
     Attribute of subgraphs
     Specifies the Shape of the summary node of a folded subgraph. The
     following Shapes are available
     
         * box
         * triangle
         * circle
         * ellipse
         * rhomb
         * hexagon
         * trapeze
         * uptrapeze
         * lparallelogram
         * rparallelogram */
  DEF_ATTR (graph, shape, enum gdl_shape)
     
  /* shrink: Int, default is 1
     stretch: Int, default is 1
     Attributes of top-level graph, subgraphs
     Specify the shrinking and stretching factors for the scaling. The scaling
     of the graph as a percentage is given by the formula ((stretch / shrink) *
     100).
     
     For instance, (stretch, shrink) = (1,1), or (2,2), etc., is normal size,
     (1,2) is half size, and (2,1) is double size.
     
     When these attributes are specified for the top-level graph, they
     determine the size of the entire graph including all the subgraphs. When
     specified for a subgraph they determine the scaling factor of the summary
     node of the folded subgraph. The size of a boxed subgraph is not affected,
     however the size of the subgraph nodes may still be affected (see node
     attribute shrink).
     
     Top
     
     smanhattan_edges: yes or no, default is no
     Attribute of top-level graph, subgraphs
     yes selects a specialized orthogonal layout: All horizontal edge segments
     between two levels share the same horizontal line, i.e. not only vertical
     edge segments are shared (as in the Manhattan Layout). However, horizontal
     edge segments are shared by several edges, too. This looks nice for trees
     but might be confusing in general.
     
     Top
     
     smax: Int, default is 100
     Attribute of top-level graph, subgraphs
     Sets the maximum number of iterations of the straight-line recognition
     phase. This value is not of any use unless the straight-line recognition
     phase is switched on, see straight_phase. It can be used to improve the
     Manhattan Layout or the layout with the priority phase turned on.
     
     Top
     
     splinefactor: Int, default is 70
     Attribute of top-level graph
     Determines the bending of splines. A factor of 100 indicates very sharp
     bending, a factor of 1 indicating very flat bending. Useful values range
     from 30 to 80.
     
     Top
     
     splines: yes or no, default is no
     Attribute of top-level graph
     Specifies whether splines are used to draw edges. Polygon segments are
     used to draw edges by default, because this is much faster. Note that the
     spline drawing routine is very slow. Splines are mainly used to prepare
     high-quality PostScript or SVG output for small graphs. See also
     splinefactor.
     
     Top
     
     spreadlevel: Int, default is 1
     Attribute of top-level graph, subgraphs
     Influences only the tree algorithm. Spreading of the uppermost nodes of
     large balanced trees would increase the width of the tree to such an
     extent that the tree would no longer fit in a window. Consequently, the
     spread level specifies the minimum level (rank) where nodes are spread.
     Nodes of levels above the spread level are not spread.
     
     Top
     
     state: State, default is unfolded
     Attribute of subgraphs
     Specifies the initial state of a subgraph, i.e. the way a subgraph is
     displayed the first time a graph is visualized. The appearance of the
     subgraph (its state) can be changed interactively. The following States
     are available:
     
         * folded
           The nodes of a subgraph are hidden. They are represented by a single
     node, called a summary node. For details, see folding.
         * boxed
           The subgraph is surrounded by a frame, i.e. drawn in a box. The
     nodes inside the box are independent of the rest of the graph, i.e. there
     are no edges connecting nodes outside the box with nodes inside the box
     and vice versa. See also box operations.
         * clustered
           The subgraph is surrounded by a frame. In contrast to a box, edges
     from nodes outside the frame are drawn to nodes inside the frame and vice
     versa. This is an experimental feature. See also cluster operations.
         * unfolded
           This is the default setting.
         * wrapped
           All nodes and edges belonging to the subgraph are wrapped using the
     same color. See also wrapping operations.
         * exclusive
           The subgraph is shown exclusively. All other nodes of the graph are
     not visible. Only edges between nodes of a group are visible. Of course,
     this value should appear only once in a graph specification. See also
     displaying node groups exclusively.
     
     Top
     
     straight_phase: yes or no, default is no
     Attribute of top-level graph, subgraphs
     yes switches on the straight phase. This is an additional phase that tries
     to avoid bends in long edges. Long edges are drawn as long straight
     vertical lines. Thus, this phase is not very appropriate for normal
     layout, however it is recommended when an orthogonal layout is selected
     (see manhattan_edges).
     
     Top
     
     stretch: Int, default is 1
     Attribute of top-level graph, subgraphs
     See shrink / stretch.
     
     Top
     
     subgraph_labels: yes or no, default is yes
     Attribute of top-level graph
     no switches off the displaying of subgraph labels. This can also be done
     interactively from the View dialog box.
     
     Top
     
     tempfactor: Float, default is 1.3
     Attribute of top-level graph
     Applies only to the forcedir layout algorithm, where it is used in the
     simulated annealing part of the algorithm. It specifies the temperature
     scheme factor used for exponential and reverse exponential temperature
     schemes. For details, see force-directed layout.
     
     Top
     
     tempmax: Int, default is 128
     tempmin: Int, default is 1
     Attributes of top-level graph
     Apply only to the forcedir layout algorithm, where they are used in the
     simulated annealing part of the algorithm. They specify the upper/lower
     limit of the temperature range. For details, see force-directed layout.
     
     Top
     
     tempscheme: Scheme, default is 1
     Attribute of top-level graph
     Applies only to the forcedir layout algorithm. There are local and global
     temperature schemes. In global temperature schemes all nodes have the same
     temperature. The following Schemes are available:
     
         * 1, local temperature temp_speed, local adaptive temperature scheme
         * with speedup during cooling
         * 2, local temperature temp_normal, local adaptive temperature scheme
         * with no speedup
         * 3, global temperature temp_linear, linear curve
         * 4, global temperature temp_hyperbolical, hyperbolic curve: very fast
         * descent, then a low temperature for an extended period of time
         * 5, global temperature temp_exponential, exponential descending
         * temperature, i.e. a small temperature for an extended period of time
         * 6, global temperature temp_logarithmic, logarithmic descending, i.e.
         * a small temperature for an extended period of time.
         * 7, global temperature temp_reverse_exponential, reverse exponential
         * descending temperature, i.e. a high temperature for an extended
         * period of time.
         * 8, global temperature temp_reverse_logarithmic, reverse logarithmic
         * descent, i.e. a high temperature for an extended period of time.
     
     For details, see force-directed layout.
     
     Top
     
     temptreshold: Int, default is 3
     Attribute of top-level graph
     Applies only to the forcedir layout algorithm, where it is used in the
     simulated annealing part of the algorithm. It specifies the threshold
     value for the global temperature. The algorithm stops if the global
     temperature drops below the value specified here. For details, see
     force-directed layout.
     
     Top
     
     textcolor: Color Entry, default is black
     Attribute of subgraphs
     Specifies the color for text labels of summary nodes. If no bordercolor is
     specified, then this attribute also specifies the color for borders of
     summary nodes, boxes and frames of clusters. For the available Color
     Entries, see section Colors. See also graph attribute color.
     
     Top
     
     textmode: center, or left_justify, or right_justify, default is center
     Attribute of subgraphs
     Specifies the alignment of text within a summary node frame. */
     
  /* title: "String", default is "name of the graph specification file"
     Attribute of subgraphs
     Specifies the name associated with the subgraph. If no title is specified
     the name of the file containing the graph specification is used. Since
     titles have to be unique throughout a graph specification, there can be
     only one subgraph at most without a title specification. */
  DEF_ATTR (graph, title, char *)
     
  /* The name of a subgraph is used to identify it, so that the subgraph can be
     the source and target of an edge specification. These edges start or end
     at the summary nodes of folded subgraphs. If the subgraph is visualized
     unfolded, these edges start or end at the root of the subgraph or at the
     root of the first subgraph in the subgraph.
     
     Top
     
     treefactor: Float, default is 0.5
     Attribute of top-level graph, subgraphs
     The tree algorithm for downward laid-out trees tries to produce a medium
     dense balanced tree-like layout. If the tree factor is greater than 0.5
     the tree edges are spread, i.e. they have a larger gradient, thus possibly
     improving the readability of the tree. It is not obvious whether spreading
     results in a denser or wider layout. A tree factor exists for each tree,
     enabling maximum density of the entire tree.
     
     Top
     
     useractioncmd1: "String", default is "" (empty string)
     useractioncmd2: "String", default is "" (empty string)
     useractioncmd3: "String", default is "" (empty string)
     useractioncmd4: "String", default is "" (empty string)
     Attributes of top-level graph
     Enable four commands to be specified in a graph specification, that are
     executed when one of the User Action menu entries is invoked by the user.
     The commands differ in the way that command line arguments are supplied to
     the command. For details and downloadable demos, see User Actions and DDE.
     See also useractionname.
     
     Top
     
     useractionname1: "String", default is "User Action 1"
     useractionname2: "String", default is "User Action 2"
     useractionname3: "String", default is "User Action 3"
     useractionname4: "String", default is "User Action 4"
     Attributes of top-level graph
     Enable names for the User Actions menu entries to be introduced. These
     names appear in the submenu of the menu item Auxiliaries in the main menu.
     For details and downloadable demos, see User Actions and DDE. See also
     useractioncmd.
     
     Top
     
     vertical_order: maxlevel or Int, default is -1 (i.e. no default)
     Attribute of subgraphs
     In a hierarchical layout, this attribute specifies the vertical position
     of a summary node of a folded subgraph. maxlevel tries to position the
     node at the maximum calculated level. Generally for all nodes, their
     vertical position is called their level or rank (see rank assignment). A
     synonym for vertical_order is level.
     
     All nodes of level 0 form the uppermost layer (if the orientation is
     top_to_bottom). Nodes of level 1 form the second layer, etc. The level
     specification is not in effect unless automatic layout is being
     calculated. Layout is calculated automatically if there is at least one
     node without a specified location (see loc attribute for nodes and loc
     attribute for summary nodes).
     
     The level specification may conflict with a near edge specification,
     because the source and target node of a near edge have to have the same
     level. In this case, the level specification of the source or the target
     node of the near edge is ignored.
     
     Top
     
     view: Mode, default is normal, i.e. no fish-eye view
     Attribute of top-level graph
     Enables one of the six fish-eye view Modes to be selected. If a graph is
     large only a small amount of it is visible in the graph window because of
     the fixed size of the window. Scaling the graph down so that it fits into
     the window causes details to no longer be recognizable. The solution to
     this is fish-eye views. A fish-eye view is a coordinate transformation,
     causing the view of the graph to be distorted. There is a focus which is
     magnified so that all the details can be seen. Parts of the graph that are
     far away from the focus are scaled down. The following fish-eye view Modes
     are available:
     
         * pfish
           Self-adaptable polar fish-eye view. The plane containing the graph
     layout is projected onto a sphere. Polar fish-eye view is a 3D look onto
     this sphere.
         * cfish
           Self-adaptable Cartesian fish-eye view. The effect of the Cartesian
     fish eye is similar to polar fish-eye view, only that the Cartesian
     coordinate system is transformed instead of the polar system. In this view
     horizontal and vertical lines remain horizontal and vertical after
     transformation, i.e. they are not bent as in the case of polar fish-eye
     view.
         * fpfish
           Polar fish-eye view with a fixed radius. Here the fish-eye view only
     shows a fixed radius around the focus, meaning the entire graph may no
     longer be visible.
         * fcfish
           Cartesian fish-eye view with a fixed radius. Here the fish eye only
     shows a fixed radius around the focus, meaning the entire graph may no
     longer be visible.
         * dpfish
           Polar fish-eye view with a double focus.
         * dcfish
           Cartesian fish-eye view with a double focus.
     
     See also importance and fish-eye view modes and parameters
     
     Top
     
     width: Int
     default for top-level graph is (width of root screen - 100) pixels,
     default for subgraphs is (width of the label for summary nodes) pixels
     Attribute of top-level graph, subgraphs
     In the top-level graph, this attribute specifies the width of the display
     window in pixels. In a subgraph specification, it specifies the width of
     the summary node in pixels. See also height.
     
     Top
     
     x: Int
     y: Int
     default for top-level graph is 0 for both,
     default for subgraphs is unspecified for both
     Attributes of top-level graph, subgraphs
     In the top-level graph, these attributes specify the position of the graph
     window in relation to the root screen, i.e. the x and y coordinates of the
     upper left corner of the graph window are specified in pixels. The origin
     of the root screen is in the upper left corner. In a subgraph
     specification, these attributes specify the x and y coordinates (in
     pixels) of the summary node in relation to the upper left corner of the
     graph window.
     
     The positions can also be specified via loc.
     
     Top
     
     xbase: Int, default is 5
     ybase: Int, default is 5
     Attributes of top-level graph, subgraphs
     In the top-level graph, these attributes specify the horizontal and
     vertical offset between the graph window and the upper left-hand corner of
     the graph, i.e. the position of the origin of the coordinate system in
     relation to the upper left-hand corner of the virtual window. In subgraph
     specifications, these are the offsets from the frame of the box containing
     the subgraph.
     
     When exporting the graph to SVG or PS, these attributes can be used to
     control horizontal and vertical offsets between the image border and the
     actual graph. Also, these attributes come in handy for working around the
     lack of image background color attribute in SVG. See example.
     
     Top
     
     Displayed Window and Virtual Windowxmax: Int, default is (width of the
     root screen - 90) pixels
     ymax: Int, default is (height of the root screen - 90) pixels
     Attributes of top-level graph
     Specify the maximum size of the virtual window used to display the graph
     (see picture). This is usually larger than the displayed part. The width
     and height of the displayed part cannot be larger than xmax and ymax. Only
     the parts of the graph inside the virtual window are drawn. The virtual
     window can be moved over the potentially infinite coordinate system by
     special positioning commands (see navigation).
     
     Note: It is advisable to set xmax and ymax so they do not exceed the size
     of the root screen so as to get good performance.
     
     Top
     
     xraster: Int, default is 1
     yraster: Int, default is 1
     Attributes of top-level graph, subgraphs
     In a hierarchical layout, these attributes specify raster distances for
     positioning nodes. The center of each node is aligned to this raster (grid
     layout).
     
     Top
     
     xlraster: Int, default is 1
     Attribute of top-level graph, subgraphs
     Specifies a horizontal raster distance for xlspace in pixels. The value of
     xlraster should be a divisor of the value of xraster.
     
     Top
     
     xlspace: Int,
     default is 1/2 * xspace pixels, if polygons are used for edge drawing
     default is 4/5 * yspace pixels, if splines are used for edge drawing
     Attribute of top-level graph, subgraphs
     Describes the horizontal distance between lines at the points where they
     cross levels. It is advisable to set xlspace to a larger value, if splines
     are used in order to prevent sharp bends.
     
     Top
     
     xspace: Int, default is 20
     yspace: Int, default is 70
     Attributes of top-level graph, subgraphs
     Specify the minimum horizontal and vertical distance between nodes in
     pixels */
