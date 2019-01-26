import platform

def exists(env):
    return True

def generate(env):
    env.Replace(
        BUILD_ROOT = '#build',
        BUILD_DIR = '$BUILD_ROOT/$MODE/$OS',
        STAGING_ROOT = '#dist',
        STAGING_DIR = '$STAGING_ROOT/$MODE/$OS',
        HOST_OS = platform.system().lower(),
    )

    env.Append(
        CCFLAGS = [
            '-Wall',
            '-Werror',
            '-Wextra',
        ],

        LIBPATH = [
            '$STAGING_DIR',
        ],
    )
