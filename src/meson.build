subdir('ActorGraph')

# Define pathfinder_exe to output executable file named 
# pathfinder.cpp.executable
pathfinder_exe = executable('pathfinder.cpp.executable',
    sources: ['pathfinder.cpp'],
    dependencies: [actorgraph_dep, actornode_dep, movieedge_dep],
    install: true)
