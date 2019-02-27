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

all_objs = []

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
    all_objs.extend(dir_objs)

test_env = host_env.Clone()
test_env.Tool('test')
test_env.Tool('coverage')

test_lib = SConscript(
    dirs = 'lib',
    variant_dir = test_env.subst('$BUILD_DIR/lib'),
    duplicate = False,
    exports = {'env': test_env.Clone()},
)

staged_test_lib = test_env.Install('$STAGING_DIR', test_lib)

test_objs = SConscript(
    dirs = 'test',
    variant_dir = test_env.subst('$BUILD_DIR/test'),
    duplicate = False,
    exports = {'env': test_env.Clone()},
)

staged_test_objs = test_env.Install('$STAGING_DIR', test_objs)
test_env.Depends(test_objs, staged_test_lib)
test_env.Clean(test_objs, staged_test_objs)

test_objs.append(test_lib)
test_env.Alias('test', test_objs)
all_objs.extend(test_objs)

docs = base_env.Doxygen('lib/include/physics.h')
installed_docs = base_env.Install('#dist', docs)
base_env.Clean(docs, installed_docs)
all_objs.extend(installed_docs)

base_env.Clean(all_objs, '$BUILD_ROOT')
base_env.Clean(all_objs, '$STAGING_ROOT')
