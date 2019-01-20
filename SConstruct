base_env = Environment(
    BUILD_ROOT = '#build',
    BUILD_DIR = '$BUILD_ROOT/$MODE',
    STAGING_ROOT = '$BUILD_ROOT/bin',
    STAGING_DIR = '$STAGING_ROOT/$MODE',

    CCFLAGS = [
        '-Wall',
        '-Werror',
        '-Wextra',
    ],

    CPPPATH = [
        '#include',
    ],

    LIBPATH = [
        '$STAGING_DIR',
    ],
)

dbg_env = base_env.Clone(MODE='debug')
dbg_env.Append(
    CCFLAGS = [
        '-g',
    ],
)

rel_env = base_env.Clone(MODE='release')
rel_env.Append(
    CCFLAGS = [
        '-O3',
    ],
    LINKFLAGS = [
        '-s',
    ],
)

envs = (
    dbg_env,
    rel_env,
)

dirs = (
    'example',
    'lib',
)

for env in envs:
    for d in dirs:
        objs = SConscript(
            dirs = d,
            variant_dir = env.subst('$BUILD_DIR/' + d),
            duplicate = False,
            exports = {'env': env.Clone()},
        )
        env.Install('$STAGING_DIR', objs)

base_env.Command('build/doc/html/index.html', ['include/physics.h'], 'doxygen doxygen.cfg')
