test_ActorGraph_exe = executable('test_ActorGraph.cpp.executable', 
    sources: ['test_ActorGraph.cpp'], 
    dependencies : [actorgraph_dep, actornode_dep, movieedge_dep, gtest_dep])
test('my ActorGraph test', test_ActorGraph_exe)

test_ActorNode_exe = executable('test_ActorNode.cpp.executable', 
    sources: ['test_ActorNode.cpp'], 
    dependencies : [actornode_dep, movieedge_dep, gtest_dep])
test('my ActorNode test', test_ActorNode_exe)

test_MovieEdge_exe = executable('test_MovieEdge.cpp.executable', 
    sources: ['test_MovieEdge.cpp'], 
    dependencies : [actornode_dep, movieedge_dep, gtest_dep])
test('my MovieEdge test', test_MovieEdge_exe)