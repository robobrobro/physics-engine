base_env = Environment(
    CPPPATH = ['#include'],
)
base_env.Tool('base')

dbg_env = base_env.Clone()
dbg_env.Tool('debug')

rel_env = base_env.Clone()
rel_env.Tool('release')

envs = (
    dbg_env,
    rel_env,
)

dirs = (
    'example',
    'lib',
)

for d in dirs:
    dir_objs = []

    for env in envs:
        objs = SConscript(
            dirs = d,
            variant_dir = env.subst('$BUILD_DIR/' + d),
            duplicate = False,
            exports = {'env': env.Clone()},
        )
        dir_objs.extend(objs)

        env.Install('$STAGING_DIR', objs)

    env.Alias(d, dir_objs)

docs = base_env.Command('build/doc/html/index.html', ['include/physics.h'], 'doxygen doxygen.cfg')
base_env.Clean(docs, 'build/doc')
