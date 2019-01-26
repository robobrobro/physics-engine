base_env = Environment(
    CPPPATH = ['#lib/include'],
)
base_env.Tool('base')
base_env.Tool('doxygen')

host_env = base_env.Clone()
host_env.Tool('host')

os_envs = (
    host_env,
)

envs = []

for env in os_envs:
    dbg_env = env.Clone()
    dbg_env.Tool('debug')
    envs.append(dbg_env)

    rel_env = env.Clone()
    rel_env.Tool('release')
    envs.append(rel_env)

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

docs = base_env.Doxygen('lib/include/physics.h')
base_env.Install('#dist', docs)
