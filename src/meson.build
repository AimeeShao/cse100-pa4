subdir('ActorGraph')

# Define pathfinder_exe to output executable file named 
# pathfinder.cpp.executable
pathfinder_exe = executable('pathfinder.cpp.executable',
    sources: ['pathfinder.cpp'],
    dependencies: [actorgraph_dep, actornode_dep, movieedge_dep],
    install: true)

# Define linkpredictor_exe to output executable file named 
# linkpredictor.cpp.executable
linkpredictor_exe = executable('linkpredictor.cpp.executable',
    sources: ['linkpredictor.cpp'],
    dependencies: [actorgraph_dep, actornode_dep, movieedge_dep],
    install: true)

# Define movietraveler_exe to output executable file named 
# movietraveler.cpp.executable
movietraveler_exe = executable('movietraveler.cpp.executable',
    sources: ['movietraveler.cpp'],
    dependencies: [actorgraph_dep, actornode_dep, movieedge_dep],
    install: true)
